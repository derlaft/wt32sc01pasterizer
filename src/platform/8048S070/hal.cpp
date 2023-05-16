#include "hal.h"


// Интерфейc экрана
RGBDisplay8048S070 *screen;

// Интерфейс тачскрина
TAMC_GT911 *touch;

bool is_display_open = false;

// Области памяти для отрисовки
static lv_disp_draw_buf_t draw_buf;
const auto buf_size = TFT_WIDTH*60;
DRAM_ATTR static lv_color_t disp_draw_buf[buf_size];

void hw_setup() {

    screen = new RGBDisplay8048S070();
    screen->begin();

    touch = new TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, TFT_WIDTH, TFT_HEIGHT);

    Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);

    touch->begin();
    touch->setRotation(TOUCH_GT911_ROTATION);
}

void hw_lvgl_setup() {

    // Буфер для отрисовки
    lv_disp_draw_buf_init( &draw_buf, disp_draw_buf, NULL, buf_size);

    // Создание дисплея
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );

    // Установка корректного размера дисплея
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
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
    // Включить подсветку экрана (в последнюю очередь, чтобы не было видно никаких морганий при запуске)
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, 1);
}


IRAM_ATTR void update_display(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    if (!is_display_open) {
        is_display_open = true;
        vTaskPrioritySet(NULL, tskIDLE_PRIORITY + 2);
    }

    screen->draw16bitRGBBitmap(area->x1, area->y1, area->x2+1, area->y2+1, (uint16_t *)&color_p->full);
    if (lv_disp_flush_is_last(disp)) {
        vTaskPrioritySet( NULL, tskIDLE_PRIORITY);
    }

    lv_disp_flush_ready(disp);
}

void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data) {
#ifdef TOUCH_DEBUG
  Serial.println("#");
#endif

  static uint16_t lastx = 0;
  static uint16_t lasty = 0;

  touch->read();
  if (!touch->isTouched) {
     data->state = LV_INDEV_STATE_REL;
     data->point.x = lastx;
     data->point.y = lasty;
     return;
  }

  TP_Point touchPos = touch->points[0];
  data->state = LV_INDEV_STATE_PR;

#ifdef TOUCH_DEBUG
  Serial.println("touch at " + String(touchPos.x) + "x" + String(touchPos.y));
#endif
#if defined(TOUCH_SWAP_XY)
    lastx = map(touchPos.y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, TFT_WIDTH - 1);
    lasty = map(touchPos.x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, TFT_HEIGHT - 1);
#else
    lastx = map(touchPos.x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, TFT_WIDTH - 1);
    lasty = map(touchPos.y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, TFT_HEIGHT - 1);
#endif
#ifdef TOUCH_DEBUG
  Serial.println("mapped to " + String(xpos) + "x" + String(ypos));
#endif

  data->point.x = lastx;
  data->point.y = lasty;

  return;
}

