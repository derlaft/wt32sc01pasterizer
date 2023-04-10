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

#define _TO_MS(BODY) (BODY * 60ll * 1000ll)

bool need_state_backup = false;

bool compressor_is_on = false;
bool mixer_is_on = false;

static int64_t cycles_in_state = 0;
LogicState state = LogicState::Idle;

SemaphoreHandle_t xLogicSemaphore;

void logic_setup() {
  xLogicSemaphore = xSemaphoreCreateMutex();

  logic_restore_state();

  // enable second serial
  Serial2.begin(LOGIC_SERIAL_SPEED, SERIAL_8N1, LOGIC_SERIAL_RX, LOGIC_SERIAL_TX);

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
  
  Serial.print("STATE:");
  Serial.println(state);

  Serial.print("SERIAL TEST: ");
  while (Serial2.available() > 0) {

    char report = Serial2.read();
    switch (report) {
        case '0':
            compressor_is_on = true;
            break;
        case 'a':
            compressor_is_on = false;
            break;
        case '1':
            mixer_is_on = true;
            break;
        case 'b':
            mixer_is_on = false;
            break;
    }

    // say what you got:
    Serial.print(report);
  }
  Serial.println();

  Serial.print("comp=");
  Serial.println(compressor_is_on);
  Serial.print("mixer=");
  Serial.println(mixer_is_on);
  Serial.print("cnt=");
  Serial.println(cycles_in_state);

  int64_t ct_ms;
  int64_t d_ms;

  switch (state) {
    
    // текущее состояние: ожидание начала программы
    case LogicState::Idle:
      // ничего не нужно делать: ждем
      break;

    case LogicState::Cooling_Cooling:
      // нагрев
      if (!compressor_is_on || !mixer_is_on) {
          Serial2.print('0'); // включить компрессор
          Serial2.print('1'); // включить перемешивание
      }

      // успешное охлаждение, перейти в хранение
      if (temp < (float) cool_temp_value) {
          Serial2.print('a'); // выключить компрессор
          state = Cooling_Store;
          cycles_in_state = 0;
      }

      break;

    case LogicState::Cooling_Store:
      // охлаждение
      if (compressor_is_on) {
          Serial2.print('a'); // выключить компрессор
      }

      if (temp > (float) cool_temp_value + TEMPERATURE_DELTA) {
          // перейти обратно в охлаждение
          state = Cooling_Cooling;
          cycles_in_state = 0;
          // включить компрессор
          Serial2.print('0'); 
      }

      ct_ms = LOGIC_TASK_INTERVAL_MS * cycles_in_state;
      d_ms = _TO_MS(mix_delay_value);

      if (ct_ms < d_ms) {
          // начальная задержка
          // включить перемешивание (оставить его включенным)
          Serial2.print('1'); 
      } else if ((ct_ms - d_ms) % _TO_MS(mix_value + before_mix_value) < _TO_MS(before_mix_value)) {
          // выключить перемешивание
          Serial2.print('b'); 
      } else {
          // (снова) включить перемешивание
          Serial2.print('1'); 
      }

      break;
  }

  if (state != Idle) {
      cycles_in_state ++;
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

void on_cooling_pressed() {
  // этот метод вызывается из таска интерфейса
  // когда нажата "главная кнопка"
  // следовательно, нужно взять logic lock, 
  // но не нужно брать gui lock
  _LOGIC_LOCK({
      // проверяем текущее состояние
      switch (state) {
      case Idle:
          // начать программу
          state = Cooling_Cooling;
          cycles_in_state = 0;
          // включить компрессор
          Serial2.print('0'); 
          // включить перемешивание
          Serial2.print('1'); 
          break;
      case Cooling_Cooling:
      case Cooling_Store:
          // завершить программу
          state = Idle;
          cycles_in_state = 0;
          Serial2.print('a'); // выключить компрессор
          Serial2.print('b'); // выключить перемешивание
          break;
      }
  });
  logic_sync_ui();
}

void logic_safety_check() {
}

void logic_sync_ui() {
    // синхронизировать состояние логического модуля с интерфейсом пользователя
    // int64_t past_time_left_ms = ((int64_t)past_time_value) * 60ll * 1000ll - cycles_in_pasterization * LOGIC_TASK_INTERVAL_MS;
    // TODO
    switch (state) {
        case Cooling_Cooling:
        case Cooling_Store:
            lv_obj_add_state(ui_CoolingButton, LV_STATE_CHECKED);
            break;
        default:
            lv_obj_clear_state(ui_CoolingButton, LV_STATE_CHECKED);
            break;
    }

    lv_obj_clear_state(ui_CleaningAcidButton, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_CleaningBaseButton, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_RinsingButton, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_MixingButton, LV_STATE_CHECKED);
}

Preferences backup;

void logic_backup_state() {
  int16_t v = (int16_t) ((cycles_in_state)/LOGIC_BACKUP_EVERY_N_TICK);

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

  int16_t v = backup.getShort(_BACKUP_STATE_PAST_CYCLES, 0);
  if (v > 0) {
      cycles_in_state = ((int64_t)v) * LOGIC_BACKUP_EVERY_N_TICK;
  }

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

