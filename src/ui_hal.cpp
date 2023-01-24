#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h> 
#include <Adafruit_FT6206.h>

#include "ui.h"
#include "ui_hal.h"
#include "esp_freertos_hooks.h"

// Интерфейсы экрана и тачскрина
TFT_eSPI tft = TFT_eSPI();
Adafruit_FT6206 touchScreen = Adafruit_FT6206();

bool is_display_open = false;

// Области памяти для отрисовки
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ TFT_WIDTH * 10 ];
static lv_color_t buf2[ TFT_WIDTH * 10 ];

SemaphoreHandle_t xGuiSemaphore;

void hal_setup() {

  xGuiSemaphore = xSemaphoreCreateMutex();

  // Включить экран
  tft.begin();
  tft.initDMA(false);
  tft.setSwapBytes(true);
  tft.setRotation(1);

  // Включить тачскрин на кастомных пинах
  Wire.begin(TOUCH_SDA, TOUCH_SCL);
  if (!touchScreen.begin(40)) { 
    Serial.println("hal: unable to start touchscreen");
  }

  // Инициализировать lvgl
  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

  lv_disp_draw_buf_init( &draw_buf, buf1, buf2, TFT_WIDTH * 10 );

  // Создание дисплея
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );

  // Установка корректного размера дисплея
  disp_drv.hor_res = TFT_HEIGHT;
  disp_drv.ver_res = TFT_WIDTH;
  disp_drv.flush_cb = update_display;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  // Драйвер тачскрина
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = update_touch_position;
  lv_indev_drv_register( &indev_drv );

  // инициализация интерфейса
  ui_init();

  /* If you want to use a task to create the graphic, you NEED to create a Pinned task
   * Otherwise there can be problem such as memory corruption and so on.
   * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */
  xTaskCreatePinnedToCore(gui_task, "gui", 4096*2, NULL, 0, NULL, 1);
}

void gui_task(void *pvParameter) {

  // LVGL необходимо уведомлять о течении времени (в основном для анимаций)
  ESP_ERROR_CHECK(esp_register_freertos_tick_hook((esp_freertos_tick_cb_t)lv_tick_task));

  // Включить подсветку экрана
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, 1);

  while (1) {
    /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
    // vTaskDelay(pdMS_TO_TICKS(10));

    /* Try to take the semaphore, call lvgl related function on success */
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }
  }
  
  vTaskDelete(NULL);
}

void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data) {
#ifdef TOUCH_DEBUG
  Serial.println("#");
#endif

  static uint16_t lastx = 0;
  static uint16_t lasty = 0;

  if (!touchScreen.touched()) {
     data->state = LV_INDEV_STATE_REL;
     data->point.x = lastx;
     data->point.y = lasty;
     return;
  }

  TS_Point touchPos = touchScreen.getPoint();
  data->state = LV_INDEV_STATE_PR;

#ifdef TOUCH_DEBUG
  Serial.println("touch at " + String(touchPos.x) + "x" + String(touchPos.y));
#endif
  auto xpos = touchPos.y;
  auto ypos = TFT_WIDTH - touchPos.x;
#ifdef TOUCH_DEBUG
  Serial.println("mapped to " + String(xpos) + "x" + String(ypos));
#endif

  data->point.x = xpos;
  data->point.y = ypos;
  lastx = xpos;
  lasty = ypos;

  return;
}

static void lv_tick_task(void)
{
  lv_tick_inc(portTICK_RATE_MS);
}

void update_display(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{

  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  if (!is_display_open) {
    tft.startWrite();
    is_display_open = true;
    vTaskPrioritySet(NULL, tskIDLE_PRIORITY + 2);
  }

  if (tft.dmaBusy()) {
    vTaskDelay(2);
    tft.dmaWait();
#ifdef DISPLAY_DEBUG
    Serial.println("DMA busy, wasting CPU cycles");
#endif
  } else {
#ifdef DISPLAY_DEBUG
    Serial.println("DMA ready, neat");
#endif
  }

  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushPixelsDMA(&color_p->full, w * h);

  if (lv_disp_flush_is_last(disp)) {
    tft.endWrite();
    is_display_open = false;
    vTaskPrioritySet( NULL, tskIDLE_PRIORITY);
  }

  lv_disp_flush_ready(disp);
}

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif
