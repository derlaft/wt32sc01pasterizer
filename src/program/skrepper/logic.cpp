#include "logic.hpp"
#include "../../ui_hal.h"
#include "../shared/settings.h"
#include "ui.h"
#include <Arduino.h>

extern setting_decl freq_base;
extern setting_decl freq_delta;

SemaphoreHandle_t xLogicSemaphore;
EventGroupHandle_t xLogicGroup;

bool fatal_error = false;

LogicState state = LogicState::Idle;

#define _LOGIC_LOCK(BODY)                                                      \
  if (pdTRUE == xSemaphoreTake(xLogicSemaphore, portMAX_DELAY)) {              \
    BODY;                                                                      \
    xSemaphoreGive(xLogicSemaphore);                                           \
  } else {                                                                     \
    ESP.restart();                                                             \
  }

#define _TO_MS(BODY) ((BODY)*60ll * 1000ll)

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

void logic_setup() {
  // sp.begin(RS485_BAUD, SERIAL_8N2, RS485_RXD, RS485_TXD);

  // pinMode(MOTORCTL_IN, INPUT);

  xLogicGroup = xEventGroupCreate();

  xTaskCreatePinnedToCore(logic_task, "logic", 4096 * 2, NULL,
                          tskIDLE_PRIORITY + 10, NULL, 1);
}

void logic_task(void *pvParameter) {
  // инициализировать начальное состояние интерфейса
  _GUI_LOCK(logic_sync_ui());

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  EventBits_t uxBits;

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
  switch (fatal_error) {
  case false:
    lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0x1499FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    break;
  case true:
    lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0xFF0000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    break;
  }
}
