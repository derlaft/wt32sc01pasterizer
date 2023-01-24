#include "temperature.hpp"
#include "Config.h"
#include <lvgl.h>
#include "ui.h"
#include "ui_hal.h"
#include "ui_events.h"
#include <microDS18B20.h>

MicroDS18B20<PIN_PROBE> sensor;

void temperature_task_setup() {
  sensor.setResolution(PROBE_RESOLUTION);
  xTaskCreatePinnedToCore(temperature_task, "temp", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

float last_temp = 0;

void temperature_measure() {

  if (!sensor.online()) {
#ifdef TEMP_DEBUG
    Serial.println("NEWBUG1: sensor offline");
#endif
  }

  sensor.requestTemp();
  vTaskDelay(pdMS_TO_TICKS(PROBE_INTERVAL_MS));

  if (sensor.readTemp()) {
    last_temp = sensor.getTemp();
#ifdef TEMP_DEBUG
  Serial.print("Measured ");
  Serial.print(last_temp);
  Serial.println(" degrees C");
#endif
  } else {
#ifdef TEMP_DEBUG
    Serial.println("NEWBUG3: read temp fail");
#endif
    last_temp = -127;
  }
}

void temperature_task(void *pvParameter) {

  while(1) {
    temperature_measure();
    display_temperature(last_temp);
  }
}


float temperature_get() {
  return last_temp;
}
