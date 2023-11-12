#include "logic.hpp"
#include <ModbusRTU.h>
#include <Arduino.h>
#include "../shared/settings.h"
#include "ui.h"

ModbusRTU mb;
HardwareSerial sp(1);

// TODO
static uint16_t res = 0;

extern setting_decl freq_base;
extern setting_decl freq_delta;

SemaphoreHandle_t xLogicSemaphore;
EventGroupHandle_t xLogicGroup;

const int modbusQueueLength = 16;
QueueHandle_t modbusQueue;

LogicState state = LogicState::Idle;

#define _LOGIC_LOCK(BODY) if (pdTRUE == xSemaphoreTake(xLogicSemaphore, portMAX_DELAY)) { \
      BODY; \
      xSemaphoreGive(xLogicSemaphore); \
    } else { ESP.restart(); }

#define _TO_MS(BODY) ((BODY) * 60ll * 1000ll)

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
  if (event != Modbus::EX_SUCCESS)                  // If transaction got an error
    _DEBUG("Modbus result: %02X\n", event);  // Display Modbus error code
  if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
    _DEBUG("Modbus timeout\n");
  }
  logic_modbus_on_cb();
  return true;
}

void logic_interrupt(LogicEvent_t evt) {
    BaseType_t xHigherPriorityTaskWoken, xResult;
    xHigherPriorityTaskWoken = pdFALSE;

    // отправить событие
    xResult = xEventGroupSetBitsFromISR(
            xLogicGroup,
            (EventBits_t) evt,
            &xHigherPriorityTaskWoken
    );

    // если успешно, попросить freeRTOS пробудить таск с логикой
    if(xResult != pdFAIL) {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

}

void logic_setup() {
	sp.begin(RS485_BAUD, SERIAL_8N2, RS485_RXD, RS485_TXD);

	mb.begin(&sp, RS485_RTS);
	mb.setBaudrate(RS485_BAUD);
	mb.master();

	pinMode(MOTORCTL_IN, INPUT);

	modbusQueue = xQueueCreate(modbusQueueLength, sizeof(LambdaRequest));
	xLogicGroup = xEventGroupCreate();

	xTaskCreatePinnedToCore(logic_task, "logic", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
	xTaskCreatePinnedToCore(logic_modbus_task, "modbus", 4096*2, NULL, tskIDLE_PRIORITY+11, NULL, 1);
}

void logic_task(void *pvParameter) {
	// инициализировать начальное состояние интерфейса
	// _GUI_LOCK(logic_sync_ui());

	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	EventBits_t uxBits;

	int64_t prev_start = esp_timer_get_time();

	while(1) {

		// посмотреть, сколько нужно ждать
		int64_t last_iter = (esp_timer_get_time() - prev_start);
		int64_t block_ms = LOGIC_INTERVAL_MS - last_iter;
		if (block_ms > LOGIC_INTERVAL_MS || block_ms < 0) {
			_DEBUG("_logic_task: %lldms block is invalid", block_ms);
			block_ms = LOGIC_INTERVAL_MS;
		}

		TickType_t xDelay = pdMS_TO_TICKS(block_ms);
		uxBits = xEventGroupWaitBits(
				xLogicGroup,
				LogicEvent::Any,   // ждать любого события
				pdTRUE,            // сбросить бит события
				pdFALSE,           // не ждать установки всех битов
				xDelay             // максимальное время ожидания
		);

		if (uxBits) {
			_DEBUG("uxBits %d", uxBits);
		}

		// _GUI_LOCK(logic_sync_ui())

		prev_start = esp_timer_get_time();
	}

	vTaskDelete(NULL);
}

bool modbusWait = false;

void logic_modbus_on_cb() {
	modbusWait = false;
}

void logic_modbus_send(lambda_t req) {
    LambdaRequest msg = {.lambda = req};
    BaseType_t xStatus;
	xStatus = xQueueSend(modbusQueue, &msg, pdMS_TO_TICKS(LOGIC_MODBUS_QUEUE_TIMEOUT_MS));
	if (xStatus != pdPASS) {
		_DEBUG("logic_modbus_send_task error: %d", xStatus);
	}
	_DEBUG("enqueue");
}

void logic_modbus_task(void *pvParameter) {
    LambdaRequest msg;
    BaseType_t xStatus;
	while (1) {
		mb.task();
		if (modbusWait) {
			vTaskDelay(pdMS_TO_TICKS(LOGIC_MODBUS_QUEUE_WAIT_MS));
			continue;
		}
        xStatus = xQueueReceive(modbusQueue, &msg, portMAX_DELAY);
		_DEBUG("dequeue");
        if (xStatus == pdPASS) {
			modbusWait = true;
			msg.lambda();
		} else {
			_DEBUG("logic_modbus_send_task error: %d", xStatus);
			continue;
		}
	}
	vTaskDelete(NULL);
}

void logic_debug_send_write(uint16_t reg, uint16_t value) {
	_DEBUG("debugwrite");
	mb.writeHreg(CTL_ADDR, reg, value, cb);
}

void logic_debug_send_read(uint16_t reg) {
	_DEBUG("debugread");
	mb.readHreg(CTL_ADDR, reg, &res, 1, cb);
}
