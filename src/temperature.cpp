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
  // TODO
  delay(1000);
  sensors.begin();

  // Get address, set resultion
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, PROBE_RESOLUTION);

  // Manually wait for conversion to happen
  sensors.setWaitForConversion(false);

  // Calculate delay time
  delayInMillis = sensors.millisToWaitForConversion();

  Serial.println("===");
  Serial.println("Temperature init");
  Serial.print("Resolution: ");
  Serial.println(PROBE_RESOLUTION);
  Serial.print("Parasite mode: ");
  Serial.println(sensors.isParasitePowerMode());
  Serial.print("Delay: ");
  Serial.println(delayInMillis);
  Serial.print("Address: ");
  Serial.printf("%08X\n", deviceAddress);
  Serial.print("Supported: ");
  Serial.println(sensors.validFamily(deviceAddress));
  Serial.println("===");

  // Send first request
  poll();
}

int temperature_loop() {
  if (millis() - lastTempRequest >= delayInMillis) {
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
