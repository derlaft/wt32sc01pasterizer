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

bool heat_enabled = false;
bool cool_enabled = false;
bool mixer_enabled = false;
bool need_state_backup = false;

static int64_t cycles_in_pasterization = 0;
LogicState state = LogicState::Idle;

SemaphoreHandle_t xLogicSemaphore;

void logic_setup() {
  xLogicSemaphore = xSemaphoreCreateMutex();

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
    );
    _GUI_LOCK(logic_sync_ui());

    if (need_state_backup) {
      logic_backup_state();
      need_state_backup = false;
    }
  }

  vTaskDelete(NULL);
}

void logic_tick() {

  float temp = temperature_get();
  // float past_temp = (float) past_temp_value;
  // float store_temp = (float) store_temp_value;
  // bool is_heating = heat_enabled;
  // bool is_cooling = cool_enabled;

  // int64_t past_time_ms = ((int64_t)past_time_value) * 60ll * 1000ll;

  // TODO: проверка безопасности температуры
  // если температура выше нормы, запретить нагрев

  switch (state) {
    
    // текущее состояние: ожидание начала программы
    case LogicState::Idle:
      // ничего не нужно делать: ждем
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

      }
  });
  logic_sync_ui();
}

void logic_safety_check() {
  if (temperature_get() > LOGIC_SAFE_TEMP_MAX) {
#ifdef LOGIC_DEBUG
    Serial.println("overheating, turning the heater off");
#endif
    heat_enabled = false;
  }
  if (temperature_get() < LOGIC_SAFE_TEMP_MIN) {
#ifdef LOGIC_DEBUG
    Serial.println("invalid measurement, turning the heater off for now");
#endif
    heat_enabled = false;
  }
}

void logic_sync_ui() {
  // синхронизировать состояние логического модуля с интерфейсом пользователя
  // int64_t past_time_left_ms = ((int64_t)past_time_value) * 60ll * 1000ll - cycles_in_pasterization * LOGIC_TASK_INTERVAL_MS;
  // TODO
}

Preferences backup;

void logic_backup_state() {
  int16_t v = (int16_t) ((cycles_in_pasterization)/LOGIC_BACKUP_EVERY_N_TICK);

  if (!backup.begin("logic", false)) {
    return;
  }

  backup.putShort(_BACKUP_STATE_KEY, (int16_t) state);
  backup.putShort(_BACKUP_STATE_PAST_CYCLES, v);
  backup.end();
}


void logic_restore_state() {

  if (!backup.begin("logic", true)) {
    return;
  }

  int16_t v;
  state = (LogicState_t) backup.getShort(_BACKUP_STATE_KEY, (int16_t) LogicState::Idle);
  switch (state) {
    case Idle:
      break;
    case Unknown:
    default:
      state = LogicState::Idle;
      break;
  }

  backup.end();
}

bool is_idle() {
  return state == Idle;
}

