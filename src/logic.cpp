#include "Config.h"
#include "logic.hpp"
#include "ui_hal.h"
#include "ui_events.hpp"

#include <Arduino.h>

LogicState state = LogicState::Idle;

void logic_setup() {
  pinMode(PIN_MIXER, OUTPUT);
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_COOLER, OUTPUT);

  xTaskCreatePinnedToCore(logic_task, "logic", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

void logic_task(void *pvParameter) {

  // инициализация
  xSemaphoreTake(xGuiSemaphore, portMAX_DELAY); // TODO
  activate_state_idle();
  xSemaphoreGive(xGuiSemaphore);

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(LOGIC_TASK_INTERVAL_MS);
  xLastWakeTime = xTaskGetTickCount();

  while(1) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    Serial.println("DEBUG");
  }
}

void on_heat_override(bool value) {
  digitalWrite(PIN_HEATER, value ? HIGH : LOW);
}

void on_cool_override(bool value) {
  digitalWrite(PIN_COOLER, value ? HIGH : LOW);
}

void on_mixer_override(bool value) {
  digitalWrite(PIN_MIXER, value ? HIGH : LOW);
}

void state_machine() {

}
