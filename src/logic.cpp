#include "Config.h"
#include "settings.hpp"
#include "logic.hpp"
#include "ui_hal.h"
#include "ui_events.hpp"
#include "temperature.hpp"

#include <Arduino.h>

#define _LOGIC_LOCK(BODY) if (pdTRUE == xSemaphoreTake(xLogicSemaphore, portMAX_DELAY)) { \
      BODY; \
      xSemaphoreGive(xLogicSemaphore); \
    } else { ESP.restart(); }

LogicState state = LogicState::Idle;
SemaphoreHandle_t xLogicSemaphore;

void logic_setup() {
  xLogicSemaphore = xSemaphoreCreateMutex();

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

    _LOGIC_LOCK({
        logic_tick();
    });
  }

  vTaskDelete(NULL);
}

void logic_tick() {

  float temp = temperature_get();

  // TODO: проверка безопасности температуры
  // если температура выше нормы, запретить нагрев

  switch (state) {
    case LogicState::Idle:
      // ничего не нужно делать: ждем начала программы
      break;
    case LogicState::Heating:
      if (is_temperature_lt((float) past_temp_value)) {
          // если температура ниже нормы, включить нагреватель
          set_heat(true);
      } else {
          // если температура такая, как нужно, выключить нагреватель и перейти к пастеризации
          set_heat(false);
          state = LogicState::Pasterizing;
#ifdef LOGIC_DEBUG
          Serial.println("logic: heating -> pasterizing");
#endif
      }
      // если температура выше нормы, ???
      break;
    case LogicState::Pasterizing:
      // если температура ниже нормы, включить нагреватель
      // если температура выше нормы, выключить нагреватель
      set_heat(is_temperature_lt((float) past_temp_value));
      // если температура такая, как нужно, перейти к следующему этапу
      // TODO: счетчик времени пастеризации
      if (is_temperature_eq((float) past_temp_value) || is_temperature_gt((float) past_temp_value)) {
          set_heat(false);
          state = LogicState::Cooling;
#ifdef LOGIC_DEBUG
          Serial.println("logic: pasterizing -> cooling");
#endif
      }
      break;
    case LogicState::Cooling:
      // если температура выше нормы, включить охлаждение
      set_heat(false);
      set_cool(is_temperature_gt((float) store_temp_value));
      // если температура ниже или равна норме, перейти ко хранению
      if (is_temperature_eq((float) store_temp_value) || is_temperature_lt((float) store_temp_value)) {
        state = LogicState::Storing;
        activate_state_done();
#ifdef LOGIC_DEBUG
          Serial.println("logic: cooling -> storing");
#endif
      }
      break;
    case LogicState::Storing:
      // если температура ниже нормы, включить нагреватель
      // если температура выше нормы, выключить нагреватель
      set_heat(is_temperature_lt((float) store_temp_value));
      break;
  }
}

// следующие методы вызываются из таска интерфейса
// следовательно, нужно взять logic lock, 
// но не нужно брать gui lock

void on_main_switch_pressed() {
  _LOGIC_LOCK({
      switch (state) {
      case LogicState::Idle:
#ifdef LOGIC_DEBUG
          Serial.println("logic: idle -> heating");
#endif
          state = LogicState::Heating;
          set_mixer(true, false);
          activate_state_work();
          break;
      case LogicState::Heating:
      case LogicState::Pasterizing:
      case LogicState::Cooling:
#ifdef LOGIC_DEBUG
          Serial.println("logic: emergency abort");
#endif
      case LogicState::Storing:
          state = LogicState::Idle;
          activate_state_idle();
          set_mixer(false, false);
          break;
      }
  });
}

void set_heat(bool value) {
#ifdef LOGIC_DEBUG
  Serial.print("set_heat: ");
  Serial.println(value);
#endif
  digitalWrite(PIN_HEATER, value ? HIGH : LOW);
  _GUI_LOCK(update_manual_heating_button(value));
}

void set_cool(bool value) {
#ifdef LOGIC_DEBUG
  Serial.print("set_cool: ");
  Serial.println(value);
#endif
  digitalWrite(PIN_COOLER, value ? HIGH : LOW);
  _GUI_LOCK(update_manual_cooling_button(value));
}

void set_mixer(bool value, bool gui_lock=true) {
#ifdef LOGIC_DEBUG
  Serial.print("set_mixer: ");
  Serial.println(value);
#endif
  digitalWrite(PIN_MIXER, value ? HIGH : LOW);
  if (gui_lock) {
    _GUI_LOCK(update_manual_mixing_button(value));
  } else {
    update_manual_mixing_button(value);
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
