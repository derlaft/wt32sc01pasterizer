
#ifndef _UI_SHARED_EVENTS_H
#define _UI_SHARED_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void setup_button_map(lv_event_t * e);
void on_manual_control_screen_loaded(lv_event_t * e);
void on_settings_screen_loaded(lv_event_t * e);
void on_setting_1_decr(lv_event_t * e);
void on_setting1_incr(lv_event_t * e);
void on_setting_2_decr(lv_event_t * e);
void on_setting_2_incr(lv_event_t * e);
void on_save_settings(lv_event_t * e);
void on_wireless_screen_loaded(lv_event_t * e);
void on_keyboard_press(lv_event_t * e);
void on_password_focused(lv_event_t * e);
void on_ap_focused(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
