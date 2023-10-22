#include "hal.h"


// Интерфейсы экрана и тачскрина
static LGFX lcd;

bool is_display_open = false;

// Области памяти для отрисовки
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ TFT_WIDTH * 10 ];
static lv_color_t buf2[ TFT_WIDTH * 10 ];

void hw_setup() {
  // Включить тачскрин на кастомных пинах
  lcd.init();         // Initialize LovyanGFX
  lcd.initDMA();      // Init DMA
  lcd.setRotation(2);
  lcd.setColorDepth(16);
  lcd.setBrightness(128);

}

void hw_lvgl_setup() {

  // Буфер для отрисовки
  lv_disp_draw_buf_init( &draw_buf, buf1, buf2, TFT_WIDTH * 10 );

  // Создание дисплея
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );

  // Установка корректного размера дисплея
  disp_drv.hor_res = TFT_WIDTH;
  disp_drv.ver_res = TFT_HEIGHT;
  disp_drv.flush_cb = update_display;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*

  // Драйвер тачскрина
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = update_touch_position;
  lv_indev_drv_register( &indev_drv );

  */
}

void hw_enable_backlight() {
  // Включить подсветку экрана (в последнюю очередь, чтобы не было видно никаких морганий при запуске)
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, 1);
}


void update_display(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    /* Without DMA */
    // lcd.startWrite();
    // lcd.setAddrWindow(area->x1, area->y1, w, h);
    // lcd.pushPixels((uint16_t *)&color_p->full, w * h, true);
    // lcd.endWrite();

    /* With DMA */
    // TODO: Yet to do performance test
    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);
    lcd.endWrite();

	/*
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
  */

  lv_disp_flush_ready(disp);
}

void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data) {
	/*
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
  */
}

