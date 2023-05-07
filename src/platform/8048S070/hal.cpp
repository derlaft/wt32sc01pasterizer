#include "hal.h"


// Интерфейсы экрана и тачскрина
Arduino_ESP32RGBPanel *bus;
Arduino_RGB_Display *gfx;

bool is_display_open = false;

// Области памяти для отрисовки
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;

void hw_setup() {
    bus = new Arduino_ESP32RGBPanel(
            41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
            14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
            9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
            15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */,
            0 /* hsync_polarity */, 180 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
            0 /* vsync_polarity */, 12 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */);
    gfx = new Arduino_RGB_Display(
            TFT_WIDTH /* width */, TFT_HEIGHT /* height */, bus, 0 /* rotation */, true /* auto_flush */);

    gfx->begin();

}

void hw_lvgl_setup() {

    // Буфер для отрисовки
    auto buf_size = TFT_WIDTH*TFT_HEIGHT/4;
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t)* buf_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
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
    /*
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

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);

}

void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data) {
    // TODO
    return;
}

