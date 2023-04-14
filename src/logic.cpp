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
bool fatal_error = false;

bool channel_status[NUM_CHANNEL] = {false};
bool want_channel_status[NUM_CHANNEL] = {false};

static int64_t cycles_in_state = 0;
LogicState state = LogicState::Idle;

SemaphoreHandle_t xLogicSemaphore;

void logic_setup() {
  xLogicSemaphore = xSemaphoreCreateMutex();

  logic_restore_state();

  // enable second serial
  Serial2.begin(LOGIC_SERIAL_SPEED, SERIAL_8N2, LOGIC_SERIAL_RX, LOGIC_SERIAL_TX);
  Serial2.setTimeout(LOGIC_SERIAL_TIMEOUT);

  xTaskCreatePinnedToCore(logic_task, "logic", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

void logic_task(void *pvParameter) {

  // инициализировать начальное состояние интерфейса
  _GUI_LOCK(logic_sync_ui());

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(LOGIC_TASK_INTERVAL_MS);
  xLastWakeTime = xTaskGetTickCount();

  _LOGIC_LOCK(logic_reset());

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

bool logic_write_internal(Channel_t c, bool on) {
    _DEBUG("logic_write_internal: available for write: %d", Serial2.availableForWrite());

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
                _DEBUG("logic_reset failed to restore state");
                return false;
            }

        }
    }

    return true;
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

    return true;
}

void logic_check_for_reset() {
    while (Serial2.available() > 0) {
        char n = Serial2.read();

        if (n != 0xAA) {
            _DEBUG("logic_check_for_reset: dicarding %02x", n);
            return;
        }

        n = Serial2.read();
        if (n != 0x55) {
            _DEBUG("logic_check_for_reset: dicarding %02x", n);
            return;
        }

        if (n == 0x55) {
            _DEBUG("logic_check_for_reset: reset");
            logic_after_reset();
        }
    }
}

void logic_tick() {

  float temp = temperature_get();

  _DEBUG("State=%d, comp=%d, mixer=%d, cnt=%lld", state, channel_status[Compressor], channel_status[Mixer], cycles_in_state);

  int64_t ct_ms;
  int64_t d_ms;
  int64_t a;

  switch (state) {
    
    // текущее состояние: ожидание начала программы
    case LogicState::Idle:
      // ничего не нужно делать: ждем
      break;

    case LogicState::Cooling_Start:

      // молоко уже холодное, перейти в режим хранения
      if (temp <= (float) cool_temp_value) {
          logic_change_state(Cooling_Store);
          // избежать изначального включения перемешивания
          cycles_in_state = _TO_MS(mix_delay_value) / LOGIC_TASK_INTERVAL_MS + 1;
          return;
      }

      // включить компрессор, включить перемешивание (один раз)
      if (!logic_write(Compressor, true)) {
          logic_change_state(Idle);
          return;
      }
      if (!logic_write(Mixer, true)) {
          logic_change_state(Idle);
          return;
      }

      // все включено - перейти в активное охлаждение
      logic_change_state(Cooling_Cooling);

    case LogicState::Cooling_Cooling:

      // успешное охлаждение, перейти в хранение
      if (temp <= (float) cool_temp_value) {
          logic_change_state(Cooling_Store);
          return;
      }

      // включить компрессор и мешалку, если они были выключены ранее
      logic_write(Compressor, true);
      logic_write(Mixer, true);

      break;

    case LogicState::Cooling_Store:

      // поднялась температура: перейти обратно
      if (temp > (float) cool_temp_value + TEMPERATURE_DELTA) {
          logic_change_state(Cooling_Cooling);
          return;
      }

      // компрессор должен быть выключен
      if (!logic_write(Compressor, false)) {
          // игорировать ошику, но не продолжать
          break;
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
              break;
          }
      } else if (a < _TO_MS(before_mix_value)) {
          // выключить перемешивание
          if (!logic_write(Mixer, false)) {
              // игорировать ошику, но не продолжать
              break;
          }
      } else {
          // (снова) включить перемешивание
          if (!logic_write(Mixer, true)) {
              // игорировать ошику, но не продолжать
              break;
          }
      }

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
          // выключив оба пина
          logic_write(Compressor, false);
          logic_write(Mixer, false);
          break;
      case Cooling_Start:
          // повторный тык, игнорировать нажатие
          break;
      }
  });
  logic_sync_ui();
}

void logic_safety_check() {
}

void logic_sync_ui() {

    if (fatal_error) {
        lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Ошибка", "Нарушена связь с ПЛС", NULL, true);

        lv_obj_t * title = lv_msgbox_get_title(mbox1);
        lv_obj_set_style_text_font(title, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_t * body = lv_msgbox_get_text(mbox1);
        lv_obj_set_style_text_font(body, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_center(mbox1);

        fatal_error = false;
    }

    // синхронизировать состояние логического модуля с интерфейсом пользователя
    // int64_t past_time_left_ms = ((int64_t)past_time_value) * 60ll * 1000ll - cycles_in_pasterization * LOGIC_TASK_INTERVAL_MS;
    // TODO
    auto const disabled_color = lv_color_hex(0x1499FF);
    auto const enabled_color = lv_color_hex(0x800000);
    auto const done_color = lv_color_hex(0x008000);

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

    lv_obj_clear_state(ui_CleaningAcidButton, LV_STATE_CHECKED);
    lv_obj_clear_state(ui_CleaningBaseButton, LV_STATE_CHECKED);
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
  // TODO
  switch (state) {
    case Idle:
      break;
    case Cooling_Start:
    case Cooling_Cooling:
    case Cooling_Store:
      state = Cooling_Cooling;
    default:
      state = Idle;
      break;
  }

  backup.end();
}

bool is_idle() {
  return state == Idle;
}

