#include "temperature.hpp"
#include "Config.h"

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(PIN_PROBE);
DallasTemperature sensors(&oneWire);
DeviceAddress deviceAddress;
unsigned long lastTempRequest = 0;
int delayInMillis = 0;
float lastTemp = 0;

void poll() {
  sensors.requestTemperaturesByAddress(deviceAddress);
  lastTempRequest = millis();
}

void temperature_setup() {
  // Configure 18B20
  sensors.begin();

  // Get address, set resultion
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, PROBE_RESOLUTION);

  // Calculate delay time
  delayInMillis = 750 / (1 << (12 - PROBE_RESOLUTION));

  // Send first request
  poll();
}

int temperature_loop() {
  if (millis() - lastTempRequest >= delayInMillis) {
    lastTemp = sensors.getTempC(deviceAddress);
    poll();
    return true;
  }
  return false;
}

float temperature_get() {
  return lastTemp;
}
