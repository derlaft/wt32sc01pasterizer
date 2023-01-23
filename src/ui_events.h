#ifndef _PAST_UI_EVENTS_H
#define _PAST_UI_EVENTS_H

#include <lvgl.h>
#include "Config.h"

extern lv_chart_series_t * ui_Screen1_Chart1_Series;
extern lv_coord_t temperature_data[TEMP_CHART_POINT_COUNT];
extern int16_t point_count;
extern int16_t chart_ptr;

extern void on_main_button_pressed(lv_event_t * e);
extern void on_manual_heating(lv_event_t * e);
extern void on_manual_cooling(lv_event_t * e);
extern void on_manual_mixing(lv_event_t * e);
extern void on_past_temp_incr(lv_event_t * e);
extern void on_past_temp_decr(lv_event_t * e);
extern void on_past_time_incr(lv_event_t * e);
extern void on_past_time_decr(lv_event_t * e);
extern void on_save_settings(lv_event_t * e);
extern void on_abort_settings(lv_event_t * e);
extern void on_storage_temp_incr(lv_event_t * e);
extern void on_storage_temp_decr(lv_event_t * e);
extern void on_keyboard_press(lv_event_t * e);
extern void on_ap_focused(lv_event_t * e);
extern void on_password_focused(lv_event_t * e);
extern void on_main_screen_loaded(lv_event_t * e);
extern void on_settings_screen_loaded(lv_event_t * e);
extern void on_settings_screen_2_loaded(lv_event_t * e);
extern void on_manual_control_screen_loaded(lv_event_t * e);
extern void on_wireless_screen_loaded(lv_event_t * e);
extern void on_chart_init();
extern void on_next_temperature(float data);
extern void on_chart_draw_cb(lv_event_t * e);

#endif
