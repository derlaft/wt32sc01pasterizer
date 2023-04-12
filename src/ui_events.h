
#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void setup_button_map(lv_event_t * e);
void on_main_screen_loaded(lv_event_t * e);
void on_main_cooling(lv_event_t * e);
void on_main_mixing(lv_event_t * e);
void on_main_acid(lv_event_t * e);
void on_main_base(lv_event_t * e);
void on_manual_control_screen_loaded(lv_event_t * e);
void on_settings_screen_loaded(lv_event_t * e);
void on_setting1_incr(lv_event_t * e);
void on_setting_1_decr(lv_event_t * e);
void on_setting_2_incr(lv_event_t * e);
void on_setting_2_decr(lv_event_t * e);
void on_save_settings(lv_event_t * e);
void on_settings_screen_2_loaded(lv_event_t * e);
void on_setting_3_incr(lv_event_t * e);
void on_setting_3_decr(lv_event_t * e);
void on_save_settings(lv_event_t * e);
void on_setting_4_incr(lv_event_t * e);
void on_setting_4_decr(lv_event_t * e);
void on_wireless_screen_loaded(lv_event_t * e);
void on_keyboard_press(lv_event_t * e);
void on_ap_focused(lv_event_t * e);
void on_password_focused(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
