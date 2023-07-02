
#ifndef _SHAREDSETTINGS_UI_H
#define _SHAREDSETTINGS_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_ManualControlScreen
void ui_ManualControlScreen_screen_init(lv_obj_t *root);
void ui_event_ManualControlScreen(lv_event_t * e);
extern lv_obj_t * ui_ManualControlScreen;
extern lv_obj_t * ui_MainScreenPanel;
// SCREEN: ui_SettingsScreen
void ui_SettingsScreen_screen_init(lv_obj_t *root);
void ui_event_SettingsScreen(lv_event_t * e);
extern lv_obj_t * ui_SettingsScreen;
extern lv_obj_t * ui_Setting1Panel;
extern lv_obj_t * ui_Setting1InfoLabel;
void ui_event_Setting1Decr(lv_event_t * e);
extern lv_obj_t * ui_Setting1Decr;
extern lv_obj_t * ui_Setting1DecrLabel;
extern lv_obj_t * ui_Setting1;
void ui_event_Setting1Incr(lv_event_t * e);
extern lv_obj_t * ui_Setting1Incr;
extern lv_obj_t * ui_Setting2IncrLabel;
extern lv_obj_t * ui_Setting2Panel;
extern lv_obj_t * ui_Setting2InfoLabel;
void ui_event_Setting2Decr(lv_event_t * e);
extern lv_obj_t * ui_Setting2Decr;
extern lv_obj_t * ui_Setting2DecrLabel;
extern lv_obj_t * ui_Setting2;
void ui_event_Setting2Incr(lv_event_t * e);
extern lv_obj_t * ui_Setting2Incr;
extern lv_obj_t * ui_Setting1IncrLabel;
void ui_event_ApplyButton(lv_event_t * e);
extern lv_obj_t * ui_ApplyButton;
extern lv_obj_t * ui_StartStopLabel1;
// SCREEN: ui_WirelessConnectionScreen
void ui_WirelessConnectionScreen_screen_init(lv_obj_t *root);
void ui_event_WirelessConnectionScreen(lv_event_t * e);
extern lv_obj_t * ui_WirelessConnectionScreen;
extern lv_obj_t * ui_SettingsPanel1;
void ui_event_WifiKeyboard(lv_event_t * e);
extern lv_obj_t * ui_WifiKeyboard;
extern lv_obj_t * ui_WiFiPasswordPanel;
extern lv_obj_t * ui_Screen3_Label13;
void ui_event_WifiPassword(lv_event_t * e);
extern lv_obj_t * ui_WifiPassword;
extern lv_obj_t * ui_WiFINamePanel;
extern lv_obj_t * ui_Screen3_Label14;
void ui_event_WifiName(lv_event_t * e);
extern lv_obj_t * ui_WifiName;
void ui_event____initial_actions0(lv_event_t * e);
extern lv_obj_t * ui____initial_actions0;

LV_FONT_DECLARE(ui_font_bigfont);
LV_FONT_DECLARE(ui_font_hack);
LV_FONT_DECLARE(ui_font_symbols);
LV_FONT_DECLARE(ui_font_tempfont);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
