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

bool heat_enabled = false;
bool cool_enabled = false;
bool mixer_enabled = false;
int64_t cycles_in_pasterization = 0;

LogicState state = LogicState::Idle;
SemaphoreHandle_t xLogicSemaphore;

void logic_setup() {
  xLogicSemaphore = xSemaphoreCreateMutex();

  pinMode(PIN_MIXER, OUTPUT);
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_COOLER, OUTPUT);

  logic_restore_state();

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

    _LOGIC_LOCK(
        logic_tick();
        logic_safety_check();
        logic_sync_pins();
    );
    _GUI_LOCK(logic_sync_ui());
  }

  vTaskDelete(NULL);
}

void logic_tick() {

  float temp = temperature_get();
  float past_temp = (float) past_temp_value;
  float store_temp = (float) store_temp_value;
  bool is_heating = heat_enabled;
  bool is_cooling = cool_enabled;

  int64_t past_time_ms = ((int64_t)past_time_value) * 60ll * 1000ll;

  // TODO: проверка безопасности температуры
  // если температура выше нормы, запретить нагрев

  switch (state) {
    
    // текущее состояние: ожидание начала программы
    case LogicState::Idle:
      // ничего не нужно делать: ждем
      break;

    // текущее состояние: нагрев
    case LogicState::Heating:
      // нагреватель в этом режиме постоянно включен
      set_heat(true);
      // как только достигли температуры пастеризации, переходим в следующее состояние
      if (temp >= past_temp) {
          // выключаем нагреватель
          set_heat(false);
          // переходим в следующее состояние
          state = LogicState::Pasterizing;
          logic_backup_state();
#ifdef LOGIC_DEBUG
          Serial.println("logic: heating -> pasterizing");
#endif
      }
      break;
    case LogicState::Pasterizing:

      cycles_in_pasterization++;

      // время пастеризации истекло, переход в режим охлаждения
      if (cycles_in_pasterization * LOGIC_TASK_INTERVAL_MS >= past_time_ms) {
#ifdef LOGIC_DEBUG
        Serial.println("logic: pasterizing -> cooling");
#endif
        set_heat(false);
        state = LogicState::Cooling;
        cycles_in_pasterization = 0;
        logic_backup_state();
        break;
      }

      // нагреватель уже включен, выключить по достижении температуры чуть выше
      if (is_heating && temp > past_temp + TEMPERATURE_DELTA/2) {
        set_heat(false);
      }
      // нагреватель выключен, температура упала ниже допустимой
      else if (!is_heating && temp < past_temp - TEMPERATURE_DELTA/2) {
        set_heat(true);
      } 
      // в ином случае - продолжить делать то, что уже было сделано
      
      logic_backup_state();
      break;
    case LogicState::Cooling:
      // если температура выше нормы, включить охлаждение
      set_heat(false);
      // в этом режиме постоянно включено охлаждение
      set_cool(true);
      // если температура хранения достигнута, перейти ко хранению
      if (temp <= store_temp) {
        state = LogicState::Storing;
        logic_backup_state();
        set_cool(false);
#ifdef LOGIC_DEBUG
          Serial.println("logic: cooling -> storing");
#endif
      }
      break;
    case LogicState::Storing:
      if (is_heating && temp >= store_temp) {
        // если нагреватель был включен, и мы перепрыгнули цель,
        // то нужно выключить нагреватель
        set_heat(false);
      } else if (!is_heating && temp < store_temp - TEMPERATURE_DELTA) {
        // если нагреватель был выключен, и мы перепрыгнули цель больше, чем на дельту
        // то нужно включить нагреватель
        set_heat(true);
      }

      if (is_cooling && temp <= store_temp) {
        // если охлаждение было включено, и мы перепрыгнули цель,
        // то нужно выключить охлаждение
        set_cool(false);
      } else if (!is_cooling && temp > store_temp + TEMPERATURE_DELTA) {
        // если охладитель был выключен, и мы перепрыгнули цель больше, чем на дельту
        // то нужно выключить охладитель
        set_cool(true);
      }

      break;
  }
}

void on_main_switch_pressed() {
  // этот метод вызывается из таска интерфейса
  // когда нажата "главная кнопка"
  // следовательно, нужно взять logic lock, 
  // но не нужно брать gui lock
  _LOGIC_LOCK({
      // проверяем текущее состояние
      switch (state) {
      // кнопка нажата в режиме простоя
      case LogicState::Idle:
#ifdef LOGIC_DEBUG
          Serial.println("logic: idle -> heating");
#endif
          // инициализация и начало программы
          cycles_in_pasterization = 0;
          // первый этап: нагрев
          state = LogicState::Heating;
          logic_backup_state();
          // на всякий случай выключить охлаждение
          set_cool(false);
          // включить перемешивание (будет включено практически до конца)
          set_mixer(true);
          // сбросить график, включить его
          temperature_graph_reset();
          temperature_graph_enabled = true;
          break;

      // кнопка нажата в одном из рабочих состояний
      case LogicState::Heating:
      case LogicState::Pasterizing:
      case LogicState::Cooling:
#ifdef LOGIC_DEBUG
          Serial.println("logic: emergency abort");
#endif
          // была нажата кнопка "стоп", экстренная остановка
          state = LogicState::Idle;
          logic_backup_state();
          // выключить все
          set_cool(false);
          set_heat(false);
          set_mixer(false);
          break;

      // кнопка нажата в режиме хранения
      case LogicState::Storing:
          // была нажата кнопка "готово"
          state = LogicState::Idle;
          logic_backup_state();
          // выключить все
          set_mixer(false);
          set_heat(false);
          break;
      }
  });
}

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

void logic_safety_check() {
  if (temperature_get() > LOGIC_SAFE_TEMP_MAX) {
#ifdef LOGIC_DEBUG
    Serial.println("overheating, turning the heater off");
#endif
    heat_enabled = false;
  }
}

void logic_sync_pins() {
  // синхронизировать желаемое состояние пинов с реальным
  digitalWrite(PIN_HEATER, heat_enabled ? HIGH : LOW);
  digitalWrite(PIN_MIXER, mixer_enabled ? HIGH : LOW);
  digitalWrite(PIN_COOLER, cool_enabled ? HIGH : LOW);
}

void logic_sync_ui() {
  // синхронизировать состояние логического модуля с интерфейсом пользователя
  int64_t past_time_left_ms = ((int64_t)past_time_value) * 60ll * 1000ll - cycles_in_pasterization * LOGIC_TASK_INTERVAL_MS;
  update_state_label(state, past_time_left_ms);
  update_manual_heating_button(heat_enabled);
  update_manual_cooling_button(cool_enabled);
  update_manual_mixing_button(mixer_enabled);
}

Preferences backup;

void logic_backup_state() {
  backup.begin("logic", false);
  backup.putShort(_BACKUP_STATE_KEY, (int16_t) state);
  //backup.putLong64(_BACKUP_STATE_PAST_CYCLES, cycles_in_pasterization);
  backup.end();
}

void logic_restore_state() {
  backup.begin("logic", true);
  state = (LogicState_t) backup.getShort(_BACKUP_STATE_KEY, (int16_t) LogicState::Idle);
  // cycles_in_pasterization = backup.getLong64(_BACKUP_STATE_PAST_CYCLES, 0);
  backup.end();
}


