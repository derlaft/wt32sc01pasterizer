#include "temperature.hpp"
#include "Config.h"

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(PIN_PROBE);
DallasTemperature sensors(&oneWire);
DeviceAddress deviceAddress;

int64_t lastTempRequest = 0;
int64_t delayInMicros = 0;
float lastTemp = 0;

#define BUG_DELAY vTaskDelay(100 / portTICK_PERIOD_MS)

void poll() {
  Serial.print("poll@\t");
  Serial.println(esp_timer_get_time());

  while (!sensors.isConnected(deviceAddress)) {
#ifdef TEMP_DEBUG
    Serial.println("BUG2");
    BUG_DELAY;
#endif
  }
  sensors.requestTemperaturesByAddress(deviceAddress);
  lastTempRequest = esp_timer_get_time();
}

void temperature_setup() {

  {
    // Configure 18B20 with limited timeout
    uint32_t init_at = millis();
    while (sensors.getDS18Count() == 0 && millis() - init_at < TEMP_PROBE_TIMEOUT_MS) {
      sensors.begin();
      BUG_DELAY;
    }
  }

  // Get address, set resultion
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, PROBE_RESOLUTION);
  // Manually wait for conversion to happen
  sensors.setWaitForConversion(false);

  // Calculate delay time
  delayInMicros = ((int64_t) sensors.millisToWaitForConversion()) * 1000ULL;
  Serial.println("WAT");
  Serial.println(delayInMicros);


#ifdef TEMP_DEBUG
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
  Serial.println(delayInMicros);
  Serial.print("Address:");
  for(uint8_t i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
  Serial.print("Supported: ");
  Serial.println(sensors.validFamily(deviceAddress));
  Serial.println("===");
#endif

  // Send first request
  poll();
}

int temperature_loop() {
  if  (esp_timer_get_time() - lastTempRequest > delayInMicros) {

    if (!sensors.isConnected(deviceAddress)) {
#ifdef TEMP_DEBUG
      Serial.print("BUG1 \t");
      Serial.println(esp_timer_get_time());
#endif
      BUG_DELAY;
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
