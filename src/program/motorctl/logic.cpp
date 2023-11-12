#include "logic.hpp"
#include <ModbusRTU.h>
#include <Arduino.h>
#include "../shared/settings.h"

ModbusRTU mb;
HardwareSerial sp(1);

// TODO
static uint16_t res = 0;

extern setting_decl freq_base;
extern setting_decl freq_delta;

SemaphoreHandle_t xLogicSemaphore;
EventGroupHandle_t xLogicGroup;

LogicState state = LogicState::Idle;

#define _LOGIC_LOCK(BODY) if (pdTRUE == xSemaphoreTake(xLogicSemaphore, portMAX_DELAY)) { \
      BODY; \
      xSemaphoreGive(xLogicSemaphore); \
    } else { ESP.restart(); }

#define _TO_MS(BODY) ((BODY) * 60ll * 1000ll)

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
  if (event != Modbus::EX_SUCCESS)                  // If transaction got an error
    Serial.printf("Modbus result: %02X\n", event);  // Display Modbus error code
  if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
    Serial.printf("Modbus timeout\n");
  }
  return true;
}

void logic_setup() {
	sp.begin(RS485_BAUD, SERIAL_8N2, RS485_RXD, RS485_TXD);

	mb.begin(&sp, RS485_RTS);
	mb.setBaudrate(RS485_BAUD);
	mb.master();

	pinMode(MOTORCTL_IN, INPUT);

	xTaskCreatePinnedToCore(logic_task, "logic", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

void logic_task(void *pvParameter) {
	while (1) {
		mb.task();

		/*
		Serial.println("debug logic_task");
		bool a = digitalRead(MOTORCTL_IN) == HIGH;
		if (a) {
			int v = freq_base.value * 2;
			mb.writeHreg(CTL_ADDR, MODBUS_FREQ_ADDR, (uint16_t)v, cb);
		} else {
			int v = (freq_base.value + freq_delta.value) * 2;
			mb.writeHreg(CTL_ADDR, MODBUS_FREQ_ADDR, (uint16_t)v, cb);
		}
		*/

		vTaskDelay(pdMS_TO_TICKS(LOGIC_INTERVAL_MS));
	}
	vTaskDelete(NULL);
}

void logic_debug_send_write(uint16_t reg, uint16_t value) {
	Serial.println("debugwrite");
	mb.writeHreg(CTL_ADDR, reg, value, cb);
}

void logic_debug_send_read(uint16_t reg) {
	Serial.println("debugread");
	mb.readHreg(CTL_ADDR, reg, &res, 1, cb);
}
