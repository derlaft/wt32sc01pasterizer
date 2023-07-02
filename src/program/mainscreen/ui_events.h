
#ifndef _UI_MAINSCREEN_EVENTS_H
#define _UI_MAINSCREEN_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void on_back_button(lv_event_t * e);
void on_manual_control_button(lv_event_t * e);
void on_warn_button_clicked(lv_event_t * e);
void on_settings_button(lv_event_t * e);
void on_forward_button(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
