#include "logic.hpp"
#include "../../ui_hal.h"
#include "../shared/settings.h"
#include "app.h"
#include "ui.h"
#include <Arduino.h>

extern setting_decl freq_base;
extern setting_decl freq_delta;

SemaphoreHandle_t xLogicSemaphore;
EventGroupHandle_t xLogicGroup;

bool fatal_error = false;

LogicState state = LogicState::Idle;

bool channel_status[NUM_CHANNEL] = {false};
bool want_channel_status[NUM_CHANNEL] = {false};

#define _TO_MS(BODY) ((BODY)*60ll * 1000ll)

static int64_t cycles_in_state = 0;

void logic_interrupt(LogicEvent_t evt) {
  BaseType_t xHigherPriorityTaskWoken, xResult;
  xHigherPriorityTaskWoken = pdFALSE;

  // отправить событие
  xResult = xEventGroupSetBitsFromISR(xLogicGroup, (EventBits_t)evt,
                                      &xHigherPriorityTaskWoken);

  // если успешно, попросить freeRTOS пробудить таск с логикой
  if (xResult != pdFAIL) {
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}

void logic_early_setup() {
  Serial2.begin(LOGIC_SERIAL_SPEED, SERIAL_8N2, LOGIC_SERIAL_RX,
                LOGIC_SERIAL_TX);
  Serial2.setTimeout(LOGIC_SERIAL_TIMEOUT);
}

void logic_boot_reset() {
  _DEBUG("logic_boot_reset");
  // попытаться отправить первый сброс, до трех раз перед тем, как сдаться
  int attempts = 3;
  while (attempts > 0 && !logic_reset()) {
    _DEBUG("logic_boot_reset attempt");
    vTaskDelay(pdMS_TO_TICKS(500));
    attempts--;
  }
}

void logic_setup() {

  xLogicGroup = xEventGroupCreate();

  xTaskCreatePinnedToCore(logic_task, "logic", 4096 * 2, NULL,
                          tskIDLE_PRIORITY + 10, NULL, 1);
}

bool is_manual_delayed_cmd = false;

void logic_flip_delayed(Channel_t c) {
  want_channel_status[c] = !want_channel_status[c];
  is_manual_delayed_cmd = true;
  logic_interrupt(LogicEvent::ManualControl);
}

void logic_task(void *pvParameter) {
  // инициализировать начальное состояние интерфейса
  _GUI_LOCK(logic_sync_ui());

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  EventBits_t uxBits;

  // инициализировать ПЛС
  logic_boot_reset();

  int64_t prev_start = esp_timer_get_time();

  while (1) {

    // посмотреть, сколько нужно ждать
    int64_t last_iter = (esp_timer_get_time() - prev_start);
    int64_t block_ms = LOGIC_INTERVAL_MS - last_iter;
    if (block_ms > LOGIC_INTERVAL_MS || block_ms < 0) {
      _DEBUG("_logic_task: %lldms block is invalid", block_ms);
      block_ms = LOGIC_INTERVAL_MS;
    }

    TickType_t xDelay = pdMS_TO_TICKS(block_ms);
    uxBits = xEventGroupWaitBits(xLogicGroup,
                                 LogicEvent::Any, // ждать любого события
                                 pdTRUE, // сбросить бит события
                                 pdFALSE, // не ждать установки всех битов
                                 xDelay // максимальное время ожидания
    );

    logic_tick(uxBits);

    _GUI_LOCK(logic_sync_ui())

    prev_start = esp_timer_get_time();
  }

  vTaskDelete(NULL);
}

void logic_tick(EventBits_t uxBits) {

  if (is_manual_delayed_cmd) {
    if (!logic_send_changed()) {
      // не дать логике возможность затормозить интерфейс и другие таски
      vTaskDelay(pdMS_TO_TICKS(1000));
      return;
    }
    is_manual_delayed_cmd = false;
  }

  switch (state) {
  case LogicState::Idle:
    if (uxBits & LogicEvent::StartStopProg) {
      state = LogicState::Activating;
    }

    break;

    // TODO
  }
}

void logic_sync_ui() {
  // синхронизировать состояние логического модуля с интерфейсом пользователя
  auto const disabled_color = lv_color_hex(0x1499FF);
  auto const enabled_color = lv_color_hex(0x800000);
  auto const done_color = lv_color_hex(0x008000);

  // состояние кнопки охлаждения
  switch (state) {
  case FreqControl:
  case Deactivating:
    lv_obj_set_style_bg_color(ui_StartStopButton, enabled_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_ReadButtonLabel2, "Стоп");
    break;
  default:
    lv_obj_set_style_bg_color(ui_StartStopButton, disabled_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_ReadButtonLabel2, "Старт");
    break;
  }

  // состояния индикатора ошибки
  if (fatal_error) {
    lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0xFF0000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0x1499FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  }

  // состояние кнопок в ручном управлении
  // показать первые 12 каналов
  for (int c = 0; c < NUM_CHANNEL && c < 12; c++) {
    if (channel_status[c]) {
      lv_btnmatrix_set_btn_ctrl(ui_ManualControlMatrix, c,
                                LV_BTNMATRIX_CTRL_CHECKED);
    } else {
      lv_btnmatrix_clear_btn_ctrl(ui_ManualControlMatrix, c,
                                  LV_BTNMATRIX_CTRL_CHECKED);
    }
  }
}

bool logic_write_internal(Channel_t c, bool on) {
  char cmd = commands[c * 2 + on];
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
    uint8_t n = Serial2.read();

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
      // сигнал о конце обработке долгой команды
      // не нужно
    }
  }
}
