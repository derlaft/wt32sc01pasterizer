#pragma once

#include <Adafruit_FT6206.h>
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <esp_freertos_hooks.h>
#include <lvgl.h>

extern void hw_setup();

extern void hw_lvgl_setup();

extern void hw_enable_backlight();

extern void update_display(lv_disp_drv_t *disp, const lv_area_t *area,
                           lv_color_t *color_p);

extern void update_touch_position(lv_indev_drv_t *drv, lv_indev_data_t *data);
