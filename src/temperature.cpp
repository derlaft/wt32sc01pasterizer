#include "temperature.hpp"
#include "Config.h"
#include <lvgl.h>
#include "ui.h"
#include "ui_hal.h"
#include "ui_events.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(PIN_PROBE);
DallasTemperature sensor(&oneWire);
DeviceAddress addr;

void temperature_task_setup() {
  sensor.setResolution(PROBE_RESOLUTION);
  xTaskCreatePinnedToCore(temperature_task, "temp", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

float last_temp = -127.0;

bool lazy_setup() {

  sensor.begin();

  if (sensor.getDeviceCount() == 0) {
 #ifdef TEMP_DEBUG
    Serial.println("NEWBUG1: init failed, will retry later");
 #endif
    vTaskDelay(pdMS_TO_TICKS(1000));
    return false;
  }

  sensor.getAddress(addr, 0);
  sensor.setResolution(PROBE_RESOLUTION);
  sensor.setWaitForConversion(false);

  return true;
}

void temperature_measure() {

  if (!lazy_setup()) {
    last_temp = -131.0;
    return;
  }

  if (!sensor.isConnected(addr)) {
    last_temp = -130.0;
    return;
  }

  if (!sensor.isConversionComplete()) {
    last_temp = -130.5;
    return;
  }

  sensor.requestTemperaturesByAddress(addr);
  vTaskDelay(pdMS_TO_TICKS(PROBE_INTERVAL_MS));

  last_temp = sensor.getTempC(addr);
#ifdef PROBE_DEBUG
  Serial.print("Measured ");
  Serial.print(last_temp);
  Serial.println(" degrees C");
#endif
}

void temperature_task(void *pvParameter) {
#ifdef DEBUG_SERIAL_TEMPERATURE
  while (1) {
    while (Serial.available () == 0) {
      vTaskDelay(pdMS_TO_TICKS(100));
    }
    float n = Serial.parseFloat();
    if (n != 0) {
      last_temp = n;
      display_temperature(last_temp);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
#else
  while(1) {
    temperature_measure();
    display_temperature(last_temp);
  }
#endif
}

float temperature_get() {
  return last_temp;
}

bool is_temperature_gt(float other) {
  return last_temp - other > TEMPERATURE_DELTA;
}

bool is_temperature_lt(float other) {
  return other - last_temp > TEMPERATURE_DELTA;
}

bool is_temperature_eq(float other) {
  return (other > last_temp ? other - last_temp : last_temp - other) < TEMPERATURE_DELTA;
}
