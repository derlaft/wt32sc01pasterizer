#ifndef _HAL_H
#define _HAL_H

#include <Arduino.h>
#include <lvgl.h>
#include <esp_freertos_hooks.h>
#include <SPI.h>

#include "ui.h"

#ifdef _DEVICE_WT32SC01
#include "platform/wt32sc01/hal.h"
#elif _DEVICE_8048S070
#include "platform/8048S070/hal.h"
#elif _DEVICE_WT32SC01PLUS
#include "platform/wt32sc01plus/hal.h"
#endif

extern SemaphoreHandle_t xGuiSemaphore;

void hal_setup();

void gui_task(void *pvParameter);

IRAM_ATTR static void lv_tick_task(void);

#endif
