#ifndef HAL_H
#define HAL_H

#include "lvgl.h"

void hal_setup();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data);

#endif
