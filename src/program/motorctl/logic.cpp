#include "logic.hpp"
#include <ModbusRTU.h>
#include <Arduino.h>

ModbusRTU mb;
HardwareSerial sp(1);

// TODO
static uint16_t res = 0;

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
  return true;
}

void logic_setup() {
	Serial.println("watin");

	sp.begin(RS485_BAUD, SERIAL_8N1, RS485_RXD, RS485_TXD);

	mb.begin(&sp, RS485_RTS);
	mb.setBaudrate(RS485_BAUD);
	mb.master();

	Serial.println("watout");
}

void logic_debug_send_write(uint8_t reg, uint16_t value) {
	mb.writeHreg(CTL_ADDR, reg, &value);
}

void logic_debug_send_read(uint8_t reg) {
	mb.readHreg(CTL_ADDR, reg, &res, 1, cbWrite);
}
