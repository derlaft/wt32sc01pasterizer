#include "temperature.hpp"
#include "Config.h"
#include <lvgl.h>
#include "ui.h"
#include "ui_hal.h"
#include "ui_events.hpp"
#include <microDS18B20.h>

MicroDS18B20<PIN_PROBE> sensor;

void temperature_task_setup() {
  sensor.setResolution(PROBE_RESOLUTION);
  xTaskCreatePinnedToCore(temperature_task, "temp", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

float last_temp = 0;

void temperature_measure() {

  if (!sensor.online()) {
#ifdef PROBE_DEBUG
    Serial.println("NEWBUG1: sensor offline");
#endif
  }

  sensor.requestTemp();
  vTaskDelay(pdMS_TO_TICKS(PROBE_INTERVAL_MS));

  if (sensor.readTemp()) {
    last_temp = sensor.getTemp();
#ifdef PROBE_DEBUG
  Serial.print("Measured ");
  Serial.print(last_temp);
  Serial.println(" degrees C");
#endif
  } else {
#ifdef PROBE_DEBUG
    Serial.println("NEWBUG3: read temp fail");
    last_temp = -127.0;
    // TODO debug
    // last_temp = 40 + random(-20, 20);
#endif
  }
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
