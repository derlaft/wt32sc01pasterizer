#ifndef _HAL_H
#define _HAL_H

#include <Arduino.h>
#include <lvgl.h>
#include <esp_freertos_hooks.h>
#include <SPI.h>
#include <TFT_eSPI.h> 
#include <Adafruit_FT6206.h>

#include "ui.h"

#if _DEVICE == WT32SC01
#include "platform/wt32sc01/hal.h"
#endif

extern SemaphoreHandle_t xGuiSemaphore;

void hal_setup();

void gui_task(void *pvParameter);

IRAM_ATTR static void lv_tick_task(void);

#endif
