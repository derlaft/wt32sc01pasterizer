#include "ui_hal.h"
#include "demos/lv_demos.h"

SemaphoreHandle_t xGuiSemaphore;

void hal_setup() {

  xGuiSemaphore = xSemaphoreCreateMutex();

  // Инициализировать железо
  hw_setup();

  // Инициализировать lvgl
  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(
      my_print); /* register print function for debugging */
#endif

  // Инициализировать драйверы для железа
  hw_lvgl_setup();

  // инициализация интерфейса
  ui_init();

  // Включить подсветку
  hw_enable_backlight();

  /* If you want to use a task to create the graphic, you NEED to create a
   * Pinned task Otherwise there can be problem such as memory corruption and so
   * on. NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to
   * core 0 */
  xTaskCreatePinnedToCore(gui_task, "gui", 4096 * 2, NULL, 0, NULL, 1);

  // LVGL необходимо уведомлять о течении времени (в основном для анимаций)
  ESP_ERROR_CHECK(
      esp_register_freertos_tick_hook((esp_freertos_tick_cb_t)lv_tick_task));
}

void gui_task(void *pvParameter) {

  while (1) {
    /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
    vTaskDelay(pdMS_TO_TICKS(10));

    /* Try to take the semaphore, call lvgl related function on success */
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }
  }

  vTaskDelete(NULL);
}

IRAM_ATTR static void lv_tick_task(void) { lv_tick_inc(portTICK_RATE_MS); }

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif
