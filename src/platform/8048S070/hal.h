#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include <esp_freertos_hooks.h>
#include <SPI.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <TAMC_GT911.h>

extern void hw_setup();

extern void hw_lvgl_setup();

extern void hw_enable_backlight();

extern void update_display(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

extern void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data);
