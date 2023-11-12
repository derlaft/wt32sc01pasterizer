#include "logic.hpp"
#include <ModbusRTU.h>
#include <Arduino.h>
#include "../shared/settings.h"
#include "ui.h"
#include "../../ui_hal.h"

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

bool fatal_error = false;

// frequency
int16_t want_freq = 0;
int16_t remote_freq = 0;

LogicState state = LogicState::Idle;

#define _LOGIC_LOCK(BODY) if (pdTRUE == xSemaphoreTake(xLogicSemaphore, portMAX_DELAY)) { \
      BODY; \
      xSemaphoreGive(xLogicSemaphore); \
    } else { ESP.restart(); }

#define _TO_MS(BODY) ((BODY) * 60ll * 1000ll)

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  if (event != Modbus::EX_SUCCESS) {
    _DEBUG("Modbus result: %02X\n", event);
	fatal_error = true;
  } else {
	fatal_error = false;
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
	_GUI_LOCK(logic_sync_ui());

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

		logic_tick(uxBits);

		_GUI_LOCK(logic_sync_ui())

		prev_start = esp_timer_get_time();
	}

	vTaskDelete(NULL);
}

bool update_remote_freq_cb(Modbus::ResultCode event, uint16_t transactionId, void* data) {
	if (event == Modbus::EX_SUCCESS) {
		remote_freq = ((TRegister*)data)->value;
	}
	return cb(event, transactionId, data);
}

void update_remote_freq() {
	mb.writeHreg(CTL_ADDR, MODBUS_FREQ_ADDR, want_freq, update_remote_freq_cb);
}

void logic_tick(EventBits_t uxBits) {

	switch (state) {
		case LogicState::Idle:
			if (uxBits & LogicEvent::StartStopProg) {
				state = LogicState::FreqControl;
			}
			break;

		case LogicState::Activating:
		case LogicState::FreqControl:

			if (uxBits & LogicEvent::StartStopProg) {
				// state = LogicState::Deactivating;
				state = LogicState::Idle;
				break;
			}

			// freq control
			if (digitalRead(MOTORCTL_IN) == HIGH) {
				want_freq = (uint16_t) (freq_base.value * MODBUS_FREQ_MULTIPLIER / 100);
			} else {
				want_freq = (uint16_t) ((freq_base.value + freq_delta.value) * MODBUS_FREQ_MULTIPLIER / 100);
			}

			if (want_freq != remote_freq) {
				_DEBUG("%d!=%d", want_freq, remote_freq);
				logic_modbus_send(update_remote_freq);
			}

			break;
	}

}

void logic_sync_ui() {
    // синхронизировать состояние логического модуля с интерфейсом пользователя
    auto const disabled_color = lv_color_hex(0x1499FF);
    auto const enabled_color = lv_color_hex(0x800000);
    auto const done_color = lv_color_hex(0x008000);

    // состояние кнопки охлаждения
    switch (state) {
        case FreqControl:
        case Deactivating:
            lv_obj_set_style_bg_color(ui_StartStopButton, enabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
			lv_label_set_text(ui_ReadButtonLabel2,"Стоп");
            break;
        default:
            lv_obj_set_style_bg_color(ui_StartStopButton, disabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
			lv_label_set_text(ui_ReadButtonLabel2,"Старт");
            break;
    }

    // состояния индикатора ошибки
    switch (fatal_error) {
        case false:
            lv_obj_add_flag(ui_WarningIndicator, LV_OBJ_FLAG_HIDDEN);
            break;
        case true:
            lv_obj_clear_flag(ui_WarningIndicator, LV_OBJ_FLAG_HIDDEN);
            break;
    }
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
