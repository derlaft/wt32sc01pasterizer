#ifndef _PAST_UI_EVENTS_H
#define _PAST_UI_EVENTS_H

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

#endif
