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
  if (!sensors.isConnected()) {
    Serial.println("BUG");
  }
  sensors.requestTemperaturesByAddress(deviceAddress);
  lastTempRequest = millis();
}

void temperature_setup() {

  // Configure 18B20
  // TODO
  while (sensors.getDS18Count() == 0) {
      sensors.begin();
      delay(250);
  }

  // Get address, set resultion
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, PROBE_RESOLUTION);
  // Manually wait for conversion to happen
  sensors.setWaitForConversion(false);

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
  Serial.print("Address:");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.print("Supported: ");
  Serial.println(sensors.validFamily(deviceAddress));
  Serial.println("===");

  // Send first request
  poll();
}

int temperature_loop() {
  if (millis() - lastTempRequest > delayInMillis) {
    lastTemp = sensors.getTempC(deviceAddress);

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
