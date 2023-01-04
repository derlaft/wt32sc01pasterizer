#ifndef _HAL_H
#define _HAL_H

#include "lvgl.h"

void hal_setup();

static void hal_loop(void *pvParameter);

void update_display(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

void update_touch_position(lv_indev_drv_t * drv, lv_indev_data_t*data);

static void lv_tick_task(void);

#endif
