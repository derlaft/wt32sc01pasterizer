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

#define _TO_MS(BODY) ((BODY) * 60ll * 1000ll)

#ifdef LOGIC_DEBUG
#define _DEBUG(...) { \
    char buf[256]; \
    snprintf(buf, sizeof(buf), __VA_ARGS__); \
    Serial.println(buf); \
};
#else
#define _DEBUG(...) {}
#endif

bool need_state_backup = false;
bool fatal_error = true;
bool need_shutdown = false;

bool channel_status[NUM_CHANNEL] = {false};
bool want_channel_status[NUM_CHANNEL] = {false};

static int64_t cycles_in_state = 0;
LogicState state = LogicState::Idle;

SemaphoreHandle_t xLogicSemaphore;
EventGroupHandle_t xLogicGroup;

#define EV_UI_INTERRUPT (1<<0)

void logic_setup() {
  xLogicSemaphore = xSemaphoreCreateMutex();
  xLogicGroup = xEventGroupCreate();

  logic_restore_state();

  xTaskCreatePinnedToCore(logic_task, "logic", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

void logic_wakeup() {
    BaseType_t xHigherPriorityTaskWoken, xResult;
    xHigherPriorityTaskWoken = pdFALSE;

    // отправить событие
    xResult = xEventGroupSetBitsFromISR(
            xLogicGroup, 
            EV_UI_INTERRUPT,
            &xHigherPriorityTaskWoken
    );

    // если успешно, попросить freeRTOS пробудить таск с логикой
    if(xResult != pdFAIL) {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

}

void logic_task(void *pvParameter) {

  // инициализировать начальное состояние интерфейса
  _GUI_LOCK(logic_sync_ui());

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  EventBits_t uxBits;

  // попытаться отправить первый сброс, до трех раз перед тем, как сдаться
  _LOGIC_LOCK({
          int attempts = 3;
          while (attempts > 0 && !logic_reset()) {
              vTaskDelay(pdMS_TO_TICKS(500));
              attempts--;
          }
  });

  int64_t prev_start = esp_timer_get_time();

  while(1) {

    // посмотреть, сколько нужно ждать
    int64_t last_iter = (esp_timer_get_time() - prev_start);
    int64_t block_ms = LOGIC_TASK_INTERVAL_MS - last_iter;
    if (block_ms < LOGIC_TASK_INTERVAL_MIN_MS || block_ms > LOGIC_TASK_INTERVAL_MS) {
        _DEBUG("_logic_task: %lldms block is invalid", block_ms);
        block_ms = LOGIC_TASK_INTERVAL_MS;
    }
    TickType_t xDelay = pdMS_TO_TICKS(block_ms);
    _DEBUG("_logic_task: %lldms block", block_ms);

    uxBits = xEventGroupWaitBits(
            xLogicGroup,
            EV_UI_INTERRUPT,
            pdTRUE,          // сбросить бит события
            pdFALSE,         // не ждать установки всех битов
            xDelay           // максимальное время ожидания
    );    

    _LOGIC_LOCK(
        logic_tick();
        logic_safety_check();
    );

    _GUI_LOCK(logic_sync_ui())
    // дать интерфейсу шанс обновиться

    if (need_state_backup) {
      logic_backup_state();
      need_state_backup = false;
    }

    prev_start = esp_timer_get_time();
  }

  vTaskDelete(NULL);
} 

bool logic_write_internal(Channel_t c, bool on) {
    char cmd = commands[c*2+on];
    Serial2.write(cmd);
    Serial2.flush();

    _DEBUG("logic_write_internal write %02x", cmd);

    char buf[2] = {cmd, 0};
    if (!Serial2.find(buf)) {
        _DEBUG("logic_write: failed to ack %02x", cmd);
        return false;
    }

    channel_status[c] = on;
    // не дать отправить следующую команду слишком быстро
    vTaskDelay(pdMS_TO_TICKS(10));

    _DEBUG("logic_write_internal write %02x ok", cmd);
    return true;

}

bool logic_write(Channel_t c, bool on) {
    if (want_channel_status[c] == on) {
        return true;
    }

    bool r = logic_write_internal(c, on);
    if (!r) {
        return logic_reset();
    }

    want_channel_status[c] = on;
    return true;
}

bool logic_after_reset() {
    // сбросить состояние с контроллера
    for (int c = 0; c < NUM_CHANNEL; c++) {
        channel_status[c] = false;
    }

    // восстановить состояние
    for (int c = 0; c < NUM_CHANNEL; c++) {
        if (want_channel_status[c]) {
            bool r = logic_write_internal((Channel_t)c, true);
            if (!r) {
                _DEBUG("logic_after_reset failed");
                return false;
            }

        }
    }

    return true;
}

bool logic_send_changed() {
    for (int c = 0; c < NUM_CHANNEL; c++) {
        if (want_channel_status[c] != channel_status[c]) {
            bool r = logic_write_internal((Channel_t)c, want_channel_status[c]);
            if (!r) {
                _DEBUG("logic_send_changed failed");
                return logic_reset();
            }

        }
    }
    return true;
}

bool is_manual_delayed_cmd = false;

void logic_flip_delayed(Channel_t c) {
    want_channel_status[c] = !want_channel_status[c];
    is_manual_delayed_cmd = true;
    logic_wakeup();
}

bool logic_reset() {

    // отправить команду перезагрузки
    Serial2.write(reset_seq);
    Serial2.flush();

    if (!Serial2.find(reset_seq)) {
        _DEBUG("logic_reset failed to get response");
        fatal_error = true;
        return false;
    }

    if (!logic_after_reset()) {
        fatal_error = true;
        return false;
    }

    fatal_error = false;
    return true;
}

void logic_check_for_reset() {
    while (Serial2.available() > 0) {
        char n = Serial2.read();

        if (n != 0xAA && n != 'X') {
            _DEBUG("logic_check_for_reset #1: dicarding %02x", n);
            return;
        }

        n = Serial2.read();
        if (n != 0x55 && n != 'X') {
            _DEBUG("logic_check_for_reset #2: dicarding %02x", n);
            return;
        }

        if (n == 0x55) {
            _DEBUG("logic_check_for_reset: reset");
            if (logic_after_reset()) {
                fatal_error = false;
            }
        } else if (n == 'X') {
            if (state == Acid) {
                logic_change_state(Acid_Done);
                want_channel_status[AcidCleaning] = false;
                channel_status[AcidCleaning] = false;
            } else if (state == Base) {
                logic_change_state(Base_Done);
                want_channel_status[BaseCleaning] = false;
                channel_status[BaseCleaning] = false;
            }
        }
    }
}

void logic_tick() {

  float temp = temperature_get();
  float target_temp = ((float) cool_temp_value)/10.0;

  _DEBUG("State=%d, comp=%d, mixer=%d, cnt=%lld", state, channel_status[Compressor], channel_status[Mixer], cycles_in_state);

  int64_t ct_ms;
  int64_t d_ms;
  int64_t a;

  if (is_manual_delayed_cmd) {
      if (!logic_send_changed()) {
          // не дать логике возможность затормозить интерфейс и другие таски
          vTaskDelay(pdMS_TO_TICKS(1000));
          return;
      }
      is_manual_delayed_cmd = false;
  }

  switch (state) {
    
    // текущее состояние: ожидание начала программы
    case LogicState::Idle:
      if (need_shutdown) {
          logic_write(Compressor, false);
          logic_write(Mixer, false);

          if (channel_status[AcidCleaning]) {
              logic_reset();
          }

          if (channel_status[BaseCleaning]) {
              logic_reset();
          }

          need_shutdown = false;
      }

      // ничего не нужно делать: ждем
      break;

    case LogicState::Cooling_Start:

      // молоко уже холодное, перейти в режим хранения
      if (temp > LOGIC_SAFE_TEMP_MIN && temp <= target_temp) {
          logic_change_state(Cooling_Store);
          // избежать изначального включения перемешивания
          cycles_in_state = _TO_MS(mix_delay_value) / LOGIC_TASK_INTERVAL_MS + 1;
          break;
      }

      // включить компрессор, включить перемешивание (один раз)
      if (!logic_write(Compressor, true)) {
          logic_change_state(Idle);
          // не дать логике возможность затормозить интерфейс и другие таски
          vTaskDelay(pdMS_TO_TICKS(1000));
          return;
      }
      if (!logic_write(Mixer, true)) {
          logic_change_state(Idle);
          // не дать логике возможность затормозить интерфейс и другие таски
          vTaskDelay(pdMS_TO_TICKS(1000));
          return;
      }

      // все включено - перейти в активное охлаждение
      logic_change_state(Cooling_Cooling);

    case LogicState::Cooling_Cooling:

      // успешное охлаждение, перейти в хранение
      if (temp > LOGIC_SAFE_TEMP_MIN && temp <= target_temp) {
          logic_change_state(Cooling_Store);
          return;
      }

      // включить компрессор и мешалку, если они были выключены ранее
      logic_write(Compressor, true);
      logic_write(Mixer, true);

      break;

    case LogicState::Cooling_Store:

      // поднялась температура: перейти обратно
      if (temp < LOGIC_SAFE_TEMP_MAX && temp > target_temp + TEMPERATURE_DELTA) {
          logic_change_state(Cooling_Cooling);
          return;
      }

      // компрессор должен быть выключен
      if (!logic_write(Compressor, false)) {
          // игорировать ошику, но не продолжать
          cycles_in_state ++;
          // не дать логике возможность затормозить интерфейс и другие таски
          vTaskDelay(pdMS_TO_TICKS(1000));
          return;
      }

      ct_ms = LOGIC_TASK_INTERVAL_MS * cycles_in_state;
      d_ms = _TO_MS(mix_delay_value);
      a = (ct_ms - d_ms) % _TO_MS(mix_value + before_mix_value);

      _DEBUG("test ct_ms=%lld, d_ms=%lld, a=%lld", ct_ms, d_ms, a);

      if (ct_ms < d_ms) {
          // начальная задержка
          // включить перемешивание (оставить его включенным)
          if (!logic_write(Mixer, true)) {
              // игорировать ошику, но не продолжать
              cycles_in_state ++;
              // не дать логике возможность затормозить интерфейс и другие таски
              vTaskDelay(pdMS_TO_TICKS(1000));
              return;
          }
      } else if (a < _TO_MS(before_mix_value)) {
          // выключить перемешивание
          if (!logic_write(Mixer, false)) {
              // игорировать ошику, но не продолжать
              cycles_in_state ++;
              // не дать логике возможность затормозить интерфейс и другие таски
              vTaskDelay(pdMS_TO_TICKS(1000));
              return;
          }
      } else {
          // (снова) включить перемешивание
          if (!logic_write(Mixer, true)) {
              // игорировать ошику, но не продолжать
              cycles_in_state ++;
              // не дать логике возможность затормозить интерфейс и другие таски
              vTaskDelay(pdMS_TO_TICKS(1000));
              return;
          }
      }

      break;

    case Mixing_Start:
      if (!logic_write(Mixer, true)) {
          logic_change_state(Idle);
          return;
      }
      logic_change_state(Mixing);
      break;

    case Mixing:
      logic_write(Mixer, true);
      break;

    case Acid_Start:
      if (!logic_write(AcidCleaning, true)) {
          logic_change_state(Idle);
          return;
      }
      logic_change_state(Acid);
      break;

    case Base_Start:
      if (!logic_write(BaseCleaning, true)) {
          logic_change_state(Idle);
          return;
      }
      logic_change_state(Base);
      break;

    case Acid:
    case Acid_Done:
    case Base:
    case Base_Done:
      break;

  }

  if (state != Idle) {
      cycles_in_state ++;
  }

  logic_check_for_reset();
}

void logic_change_state(LogicState_t n) {
    if (state == Fatal) {
        return;
    }
    _DEBUG("logic_change_state to %d", n);
    state = n;
    cycles_in_state = 0;
    need_state_backup = true;
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
          logic_change_state(Cooling_Start);
          break;
      case Cooling_Cooling:
      case Cooling_Store:
          // завершить программу
          logic_change_state(Idle);
          need_shutdown = true;
          break;
      case Cooling_Start:
          // повторный тык, игнорировать нажатие
          break;
      }
  });
  logic_wakeup();
}

void on_mixing_pressed() {
  _LOGIC_LOCK({
      // проверяем текущее состояние
      switch (state) {
      case Idle:
          // начать программу
          logic_change_state(Mixing_Start);
          break;
      case Mixing:
          // закончить программу
          logic_change_state(Idle);
          need_shutdown = true;
          break;
      }
  });
  logic_wakeup();
}

void on_acid_pressed() {
  _LOGIC_LOCK({
      // проверяем текущее состояние
      switch (state) {
      case Idle:
          // начать программу
          logic_change_state(Acid_Start);
          break;
      case Acid:
      case Acid_Done:
          // не восстанавливать программу после сброса
          want_channel_status[AcidCleaning] = false;
          // закончить программу
          logic_change_state(Idle);
          need_shutdown = true;
          break;
      }
  });
  logic_wakeup();
}

void on_base_pressed() {
  _LOGIC_LOCK({
      // проверяем текущее состояние
      switch (state) {
      case Idle:
          // начать программу
          logic_change_state(Base_Start);
          break;
      case Base:
      case Base_Done:
          // не восстанавливать программу после сброса
          want_channel_status[BaseCleaning] = false;
          // сброс
          need_shutdown = true;
          // закончить программу
          logic_change_state(Idle);
          break;
      }
  });
  logic_wakeup();
}


void logic_safety_check() {
}

void logic_sync_ui() {
/*
    // синхронизировать состояние логического модуля с интерфейсом пользователя
    auto const disabled_color = lv_color_hex(0x1499FF);
    auto const enabled_color = lv_color_hex(0x800000);
    auto const done_color = lv_color_hex(0x008000);

    // состояние кнопки охлаждения
    switch (state) {
        case Cooling_Cooling:
            lv_obj_set_style_bg_color(ui_CoolingButton, enabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        case Cooling_Store:
            lv_obj_set_style_bg_color(ui_CoolingButton, done_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        default:
            lv_obj_set_style_bg_color(ui_CoolingButton, disabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
    }

    // состояние кнопки перемешивания
    switch (state) {
        case Mixing:

            lv_obj_set_style_bg_color(ui_MixingButton, enabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        default:
            lv_obj_set_style_bg_color(ui_MixingButton, disabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
    }

    // состояние кнопки кислоты
    switch (state) {
        case Acid:
            lv_obj_set_style_bg_color(ui_CleaningAcidButton, enabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        case Acid_Done:
            lv_obj_set_style_bg_color(ui_CleaningAcidButton, done_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        default:
            lv_obj_set_style_bg_color(ui_CleaningAcidButton, disabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
    }

    // состояние кнопки щелочи
    switch (state) {
        case Base:
            lv_obj_set_style_bg_color(ui_CleaningBaseButton, enabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        case Base_Done:
            lv_obj_set_style_bg_color(ui_CleaningBaseButton, done_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        default:
            lv_obj_set_style_bg_color(ui_CleaningBaseButton, disabled_color, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
    }

    // состояния индикатора ошибки
    switch (fatal_error) {
        case false:
            lv_obj_add_flag(ui_WarningIndicator, LV_OBJ_FLAG_HIDDEN);
            break;
        case true:
            lv_obj_clear_flag(ui_WarningIndicator, LV_OBJ_FLAG_HIDDEN);
            break;
    }

    // состояние кнопок в ручном управлении
    // показать первые 12 каналов
    for (int c = 0; c < NUM_CHANNEL && c < 12; c++) {
        if (channel_status[c]) {
            lv_btnmatrix_set_btn_ctrl(ui_ManualControlMatrix, c, LV_BTNMATRIX_CTRL_CHECKED);
        } else {
            lv_btnmatrix_clear_btn_ctrl(ui_ManualControlMatrix, c, LV_BTNMATRIX_CTRL_CHECKED);
        }
    }
*/
}

Preferences backup;

void logic_backup_state() {
  if (!backup.begin("logic", false)) {
    return;
  }

  backup.putShort(_BACKUP_STATE_KEY, (int16_t) state);
  backup.end();
}


void logic_restore_state() {

  if (!backup.begin("logic", true)) {
      _DEBUG("logic_restore_state failed");
      return;
  }

  state = (LogicState_t) backup.getShort(_BACKUP_STATE_KEY, (int16_t) LogicState::Idle);
  switch (state) {
    case Idle:
      break;
    case Cooling_Start:
    case Cooling_Cooling:
    case Cooling_Store:
      // переход в состояние хранения (чтобы не включить компрессор сразу)
      state = Cooling_Store;
      // избежать изначального включения перемешивания
      cycles_in_state = _TO_MS(mix_delay_value) / LOGIC_TASK_INTERVAL_MS + 1;
      break;
    default:
      state = Idle;
      break;
  }

  backup.end();
}

bool is_idle() {
  return state == Idle;
}

