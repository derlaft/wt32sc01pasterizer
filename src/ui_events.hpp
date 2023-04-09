#ifndef _PAST_UI_EVENTS_H
#define _PAST_UI_EVENTS_H

#include <lvgl.h>

#include "Config.h"
#include "logic.hpp"

#ifdef __cplusplus
extern "C" {
#endif

extern void display_temperature(float v);
extern void update_state_label(LogicState_t state, int64_t in_past_ms);
extern void update_settings_values();
extern void wifi_sync_ui(bool connected);
extern void on_main_button_pressed(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif
