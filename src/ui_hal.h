#ifndef _HAL_H
#define _HAL_H

#include "lvgl.h"
#include <Arduino.h>
#include "esp_freertos_hooks.h"

#define _GUI_LOCK(BODY) if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) { \
      BODY; \
      xSemaphoreGive(xGuiSemaphore); \
    } else { ESP.restart(); }

extern SemaphoreHandle_t xGuiSemaphore;

void hal_setup();

void gui_task(void *pvParameter);

void update_display(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data);

static void lv_tick_task(void);

#endif
