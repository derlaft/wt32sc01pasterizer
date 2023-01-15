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
  noInterrupts();
  sensors.requestTemperaturesByAddress(deviceAddress);
  interrupts();
  lastTempRequest = millis();
}

void temperature_setup() {

  // Configure 18B20
  // TODO
  while (sensors.getDS18Count() == 0) {
      noInterrupts();
      sensors.begin();
      interrupts();
      delay(250);
  }

  noInterrupts();
  // Get address, set resultion
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, PROBE_RESOLUTION);
  // Manually wait for conversion to happen
  sensors.setWaitForConversion(false);
  interrupts();

  // Calculate delay time
  delayInMillis = sensors.millisToWaitForConversion();

  Serial.println("===");
  Serial.println("Temperature init");

  Serial.print("Device count: ");
  Serial.println(sensors.getDeviceCount());
  Serial.print("DS18Count: ");
  Serial.println(sensors.getDS18Count());

  Serial.print("Resolution: ");
  Serial.println(PROBE_RESOLUTION);
  Serial.print("Parasite mode: ");
  Serial.println(sensors.isParasitePowerMode());
  Serial.print("Delay: ");
  Serial.println(delayInMillis);
  Serial.print("Address: ");
  Serial.printf("%08X\n\r", deviceAddress);
  Serial.print("Supported: ");
  Serial.println(sensors.validFamily(deviceAddress));
  Serial.println("===");

  // Send first request
  poll();
}

int temperature_loop() {
  if (millis() - lastTempRequest > delayInMillis) {
    noInterrupts();
    lastTemp = sensors.getTempC(deviceAddress);
    interrupts();

    Serial.print("Temp: ");
    Serial.println(lastTemp);
    poll();
    return true;
  }
  return false;
}

float temperature_get() {
  return lastTemp;
}
