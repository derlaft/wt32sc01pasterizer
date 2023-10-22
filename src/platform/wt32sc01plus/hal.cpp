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
  lcd.setRotation(1);
  lcd.setColorDepth(16);
}

void hw_lvgl_setup() {

  // Буфер для отрисовки
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
}

void hw_enable_backlight() {
}


void update_display(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t h = (area->x2 - area->x1 + 1);
    uint32_t w = (area->y2 - area->y1 + 1);

    /* Without DMA */
    // lcd.startWrite();
    // lcd.setAddrWindow(area->x1, area->y1, w, h);
    // lcd.pushPixels((uint16_t *)&color_p->full, w * h, true);
    // lcd.endWrite();

  if (!is_display_open) {
    lcd.startWrite();
    is_display_open = true;
    vTaskPrioritySet(NULL, tskIDLE_PRIORITY + 2);
  }

  if (lcd.dmaBusy()) {
    vTaskDelay(2);
    lcd.waitDMA();
#ifdef DISPLAY_DEBUG
    Serial.println("DMA busy, wasting CPU cycles");
#endif
  } else {
#ifdef DISPLAY_DEBUG
    Serial.println("DMA ready, neat");
#endif
  }

  /* With DMA */
  // TODO: Yet to do performance test
  lcd.setAddrWindow(area->x1, area->y1, w, h);
  lcd.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);


  if (lv_disp_flush_is_last(disp)) {
    lcd.endWrite();
    is_display_open = false;
    vTaskPrioritySet( NULL, tskIDLE_PRIORITY);
  }

  lv_disp_flush_ready(disp);
}

void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data) {
#ifdef TOUCH_DEBUG
  Serial.println("#");
#endif

    uint16_t touchX, touchY;
    bool touched = lcd.getTouch(&touchX, &touchY);

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        // Set the coordinates
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

