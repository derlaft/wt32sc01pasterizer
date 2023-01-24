#include "temperature.hpp"
#include "Config.h"
#include <lvgl.h>
#include "ui.h"
#include "ui_hal.h"
#include "ui_events.h"
#include <OneWire.h>
#include <DS18B20.h>

OneWire oneWire(PIN_PROBE);
DS18B20 sensor(&oneWire);

void temperature_task_setup() {
  xTaskCreatePinnedToCore(temperature_task, "temp", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

float last_temp = 0;

void lazy_setup() {

  while (!sensor.begin()) {
#ifdef TEMP_DEBUG
    Serial.println("NEWBUG1: init failed, will retry later");
#endif
    vTaskDelay(pdMS_TO_TICKS(100));
  }

#ifdef TEMP_DEBUG
  Serial.println("Temperature sensor init complete");
#endif
  sensor.setResolution(12);
}

void temperature_measure() {

  sensor.requestTemperatures();
  vTaskDelay(pdMS_TO_TICKS(PROBE_INTERVAL_MS));

  while (!sensor.isConversionComplete()) {
#ifdef TEMP_DEBUG
      Serial.println("NEWBUG2: sensor is not yet ready, waiting");
#endif
      vTaskDelay(pdMS_TO_TICKS(10));
  }

  last_temp = sensor.getTempC();
#ifdef TEMP_DEBUG
  Serial.print("Measured ");
  Serial.print(last_temp);
  Serial.println(" degrees C");
#endif
}

void temperature_task(void *pvParameter) {

  lazy_setup();

  while(1) {
    temperature_measure();
    display_temperature(last_temp);
  }
}


float temperature_get() {
  return last_temp;
}
