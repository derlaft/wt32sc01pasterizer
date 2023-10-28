#ifndef _PAST_UI_EVENTS_H
#define _PAST_UI_EVENTS_H

#include <lvgl.h>

#include "Config.h"

#ifdef __cplusplus
extern "C" {
#endif

extern lv_obj_t * ui_ManualControlMatrix;

extern void display_temperature(float v);
extern void update_settings_values();
extern void wifi_sync_ui(bool connected);
extern void on_main_button_pressed(lv_event_t * e);
extern void update_temp_value();

#ifdef __cplusplus
}
#endif

#endif
