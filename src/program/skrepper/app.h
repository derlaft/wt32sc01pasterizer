#ifndef _SKREPPER_APP_H
#define _SKREPPER_APP_H

#include <lvgl.h>

// Настройки
#define CTL_ADDR 0x1
#define CTRL_REG 0x0

#define PAUSE_TIME_DEF 45
#define PAUSE_TIME_MIN 0
#define PAUSE_TIME_MAX 120

#define LOGIC_INTERVAL_MS 200

void app_init();
void settings_setup();
void settings_update();

extern lv_obj_t *ui_ManualControlMatrix;

#endif
