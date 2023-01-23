#include "temperature.hpp"
#include "Config.h"
#include <lvgl.h>
#include "ui.h"
#include "ui_hal.h"
#include "ui_events.h"
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(PIN_PROBE);
DallasTemperature sensors(&oneWire);
DeviceAddress deviceAddress;

int64_t lastTempRequest = 0;
int64_t lastTempResponse = 0;
int64_t delayInMicros = 0;
float lastTemp = 0;

#define BUG_DELAY vTaskDelay(100 / portTICK_PERIOD_MS)

void poll() {
  uint32_t init_at = millis();
  while (!sensors.isConnected(deviceAddress) && millis() - init_at < TEMP_PROBE_TIMEOUT_MS) {
#ifdef TEMP_DEBUG
    Serial.println("BUG2");
    BUG_DELAY;
#endif
  }
  sensors.requestTemperaturesByAddress(deviceAddress);
  lastTempRequest = esp_timer_get_time();
}

void temperature_setup() {

  // Initialize lib
  sensors.begin();

  // Get address, set resultion
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, PROBE_RESOLUTION);
  // Manually wait for conversion to happen
  sensors.setWaitForConversion(false);

  // Calculate delay time
  delayInMicros = ((int64_t) sensors.millisToWaitForConversion()) * 1000ULL;

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
  if (sensors.getDeviceCount() > 0) {
    poll();
  }
}

int temperature_loop() {

  if (esp_timer_get_time() - lastTempResponse > TEMP_PROBE_TIMEOUT_MS * 1000ll) {
    // слишком давно не было температуры: сбросить
    lastTemp = -251.0;
  }

  if (esp_timer_get_time() - lastTempRequest > delayInMicros) {

    if (sensors.getDS18Count() == 0) {
      BUG_DELAY;
      temperature_setup();
      // do not try to init too often
      lastTempRequest = esp_timer_get_time();
      return false;
    }

    if (!sensors.isConnected(deviceAddress)) {
      BUG_DELAY;
      return false;
    }

    lastTemp = sensors.getTempC(deviceAddress);
    lastTempResponse = esp_timer_get_time();

    poll();
    return true;
  }
  return false;
}

float temperature_get() {
  return lastTemp;
}

void display_temperature(float v)
{
  if (pdTRUE != xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
    return;
  }

  String stringValue = String(v, 1) + String("°");
  if (v > 0) {
    stringValue = String("+") + stringValue;
  }
  lv_label_set_text(ui_TemperatureDisplay, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay1, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay2, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay3, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay4, stringValue.c_str());

  xSemaphoreGive(xGuiSemaphore);
  return;
}
