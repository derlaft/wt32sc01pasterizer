#include "temperature.hpp"
#include "Config.h"

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(PIN_PROBE);
DallasTemperature sensors(&oneWire);
DeviceAddress deviceAddress;

uint32_t lastTempRequest = 0;
uint32_t delayInMillis = 0;
float lastTemp = 0;

void poll() {
  Serial.print("poll@\t");
  Serial.println(millis());

  while (!sensors.isConnected(deviceAddress)) {
    Serial.println("BUG2");
    delay(25);
  }
  sensors.requestTemperaturesByAddress(deviceAddress);
  lastTempRequest = millis();
}

void temperature_setup() {

  // Configure 18B20
  // TODO
  uint32_t init_at = millis();
  while (sensors.getDS18Count() == 0 && millis() - init_at < TEMP_PROBE_TIMEOUT_MS) {
      sensors.begin();
      delay(50);
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
;
  Serial.print("Resolution: ");
  Serial.println(PROBE_RESOLUTION);
  Serial.print("Parasite mode: ");
  Serial.println(sensors.isParasitePowerMode());
  Serial.print("Delay: ");
  Serial.println(delayInMillis);
  Serial.print("Address:");
  for(uint8_t i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
  Serial.print("Supported: ");
  Serial.println(sensors.validFamily(deviceAddress));
  Serial.println("===");

  // Send first request
  poll();
}

int temperature_loop() {
  if (millis() - lastTempRequest > delayInMillis) {

    if (!sensors.isConnected(deviceAddress)) {
      Serial.print("BUG1 \t");
      Serial.println(millis());
      delay(25);
      return false;
    }

    lastTemp = sensors.getTempC(deviceAddress);

    poll();
    return true;
  }
  return false;
}

float temperature_get() {
  return lastTemp;
}
