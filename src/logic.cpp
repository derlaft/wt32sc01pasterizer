#include "Config.h"
#include "settings.hpp"
#include "logic.hpp"
#include "ui_hal.h"
#include "ui_events.hpp"
#include "temperature.hpp"
#include "temperature_graph.hpp"

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

  // инициализировать начальное состояние интерфейса
  _GUI_LOCK(logic_sync_ui());

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(LOGIC_TASK_INTERVAL_MS);
  xLastWakeTime = xTaskGetTickCount();

  while(1) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    // TODO: more granular lock control?
    _LOGIC_LOCK(
          logic_tick();
    );
    _GUI_LOCK(
        logic_sync_ui();
    );
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
      set_heat(true);
      if (temperature_get() >= (float) past_temp_value) {
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
#ifdef LOGIC_DEBUG
          Serial.println("logic: cooling -> storing");
#endif
      }
      break;
    case LogicState::Storing:
      // если температура выше нормы, включить охлаждение
      set_cool(temperature_get() > (float) store_temp_value + TEMPERATURE_DELTA);
      // если температура ниже нормы, включить нагреватель
      set_heat(temperature_get() < (float) store_temp_value - TEMPERATURE_DELTA);
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
          set_cool(false);
          set_mixer(true);
          temperature_graph_reset();
          temperature_graph_enabled = true;
          break;
      case LogicState::Heating:
      case LogicState::Pasterizing:
      case LogicState::Cooling:
#ifdef LOGIC_DEBUG
          Serial.println("logic: emergency abort");
#endif
          set_cool(false);
          set_heat(false);
          set_mixer(false);
          temperature_graph_enabled = false;
      case LogicState::Storing:
          state = LogicState::Idle;
          set_mixer(false);
          set_heat(false);
          temperature_graph_reset();
          temperature_graph_enabled = false;
          break;
      }
  });
}

bool heat_enabled = false;
bool cool_enabled = false;
bool mixer_enabled = false;

void set_heat(bool value) {
#ifdef LOGIC_DEBUG
  Serial.print("set_heat: ");
  Serial.println(value);
#endif
  heat_enabled = value;
}

void set_cool(bool value) {
#ifdef LOGIC_DEBUG
  Serial.print("set_cool: ");
  Serial.println(value);
#endif
  cool_enabled = value;
}

void set_mixer(bool value) {
#ifdef LOGIC_DEBUG
  Serial.print("set_mixer: ");
  Serial.println(value);
#endif
  mixer_enabled = value;
}

void logic_sync_ui() {
  update_state_label(state);
  update_manual_heating_button(heat_enabled);
  update_manual_cooling_button(cool_enabled);
  update_manual_mixing_button(mixer_enabled);
}
