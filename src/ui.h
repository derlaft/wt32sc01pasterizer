
#ifndef _PAST_UI_H
#define _PAST_UI_H

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

#include "ui_events.h"
void ui_event_MainScreen(lv_event_t * e);
extern lv_obj_t * ui_MainScreen;
extern lv_obj_t * ui_TopPanel;
extern lv_obj_t * ui_TemperatureDisplay;
void ui_event_SettingsButton1(lv_event_t * e);
extern lv_obj_t * ui_SettingsButton1;
void ui_event_ManualControlButton(lv_event_t * e);
extern lv_obj_t * ui_ManualControlButton;
void ui_event_WarningIndicator(lv_event_t * e);
extern lv_obj_t * ui_WarningIndicator;
extern lv_obj_t * ui_ManualControlPanel;
void ui_event_CoolingButton(lv_event_t * e);
extern lv_obj_t * ui_CoolingButton;
extern lv_obj_t * ui_CoolingButtonLabel;
void ui_event_MixingButton(lv_event_t * e);
extern lv_obj_t * ui_MixingButton;
extern lv_obj_t * ui_MixingButtonLabel;
void ui_event_CleaningAcidButton(lv_event_t * e);
extern lv_obj_t * ui_CleaningAcidButton;
extern lv_obj_t * ui_CleaningAcidButtonLabel;
void ui_event_CleaningBaseButton(lv_event_t * e);
extern lv_obj_t * ui_CleaningBaseButton;
extern lv_obj_t * ui_CleaningBaseButtonLabel;
void ui_event_ManualControlScreen(lv_event_t * e);
extern lv_obj_t * ui_ManualControlScreen;
extern lv_obj_t * ui_TopPanel1;
extern lv_obj_t * ui_TemperatureDisplay1;
void ui_event_ManualControlButton1(lv_event_t * e);
extern lv_obj_t * ui_ManualControlButton1;
extern lv_obj_t * ui_MainScreenPanel;
void ui_event_SettingsScreen(lv_event_t * e);
extern lv_obj_t * ui_SettingsScreen;
extern lv_obj_t * ui_SettingsPanel;
extern lv_obj_t * ui_Setting1Panel;
extern lv_obj_t * ui_Setting1;
void ui_event_Setting1Incr(lv_event_t * e);
extern lv_obj_t * ui_Setting1Incr;
extern lv_obj_t * ui_Setting1IncrLabel;
void ui_event_Setting1Decr(lv_event_t * e);
extern lv_obj_t * ui_Setting1Decr;
extern lv_obj_t * ui_Setting1DecrLabel;
extern lv_obj_t * ui_Setting1InfoLabel;
extern lv_obj_t * ui_Setting2Panel;
extern lv_obj_t * ui_Setting2;
void ui_event_Setting2Incr(lv_event_t * e);
extern lv_obj_t * ui_Setting2Incr;
extern lv_obj_t * ui_Setting2IncrLabel;
void ui_event_Setting2Decr(lv_event_t * e);
extern lv_obj_t * ui_Setting2Decr;
extern lv_obj_t * ui_Setting2DecrLabel;
extern lv_obj_t * ui_Setting2InfoLabel;
void ui_event_ApplyButton(lv_event_t * e);
extern lv_obj_t * ui_ApplyButton;
extern lv_obj_t * ui_StartStopLabel1;
extern lv_obj_t * ui_TopPanel2;
extern lv_obj_t * ui_TemperatureDisplay2;
void ui_event_SettingsButton2(lv_event_t * e);
extern lv_obj_t * ui_SettingsButton2;
void ui_event_ManualControlButton2(lv_event_t * e);
extern lv_obj_t * ui_ManualControlButton2;
void ui_event_SettingsScreen2(lv_event_t * e);
extern lv_obj_t * ui_SettingsScreen2;
extern lv_obj_t * ui_SettingsPanel2;
extern lv_obj_t * ui_Setting3Panel;
extern lv_obj_t * ui_Setting3;
void ui_event_Setting3Incr(lv_event_t * e);
extern lv_obj_t * ui_Setting3Incr;
extern lv_obj_t * ui_Setting3IncrLabel;
void ui_event_Setting3Decr(lv_event_t * e);
extern lv_obj_t * ui_Setting3Decr;
extern lv_obj_t * ui_Setting3DecrLabel;
extern lv_obj_t * ui_Setting3InfoLabel;
void ui_event_ApplyButton1(lv_event_t * e);
extern lv_obj_t * ui_ApplyButton1;
extern lv_obj_t * ui_StartStopLabel2;
extern lv_obj_t * ui_Setting4Panel;
extern lv_obj_t * ui_Setting4;
void ui_event_Setting4Incr(lv_event_t * e);
extern lv_obj_t * ui_Setting4Incr;
extern lv_obj_t * ui_Setting4IncrLabel;
void ui_event_Setting4Decr(lv_event_t * e);
extern lv_obj_t * ui_Setting4Decr;
extern lv_obj_t * ui_Setting4DecrLabel;
extern lv_obj_t * ui_Setting4InfoLabel;
extern lv_obj_t * ui_TopPanel3;
extern lv_obj_t * ui_TemperatureDisplay3;
void ui_event_SettingsButton3(lv_event_t * e);
extern lv_obj_t * ui_SettingsButton3;
void ui_event_ManualControlButton3(lv_event_t * e);
extern lv_obj_t * ui_ManualControlButton3;
void ui_event_WirelessConnectionScreen(lv_event_t * e);
extern lv_obj_t * ui_WirelessConnectionScreen;
extern lv_obj_t * ui_SettingsPanel1;
void ui_event_WifiKeyboard(lv_event_t * e);
extern lv_obj_t * ui_WifiKeyboard;
void ui_event_WifiName(lv_event_t * e);
extern lv_obj_t * ui_WifiName;
void ui_event_WifiPassword(lv_event_t * e);
extern lv_obj_t * ui_WifiPassword;
extern lv_obj_t * ui_Screen3_Label13;
extern lv_obj_t * ui_Screen3_Label14;
extern lv_obj_t * ui_TopPanel4;
extern lv_obj_t * ui_TemperatureDisplay4;
extern lv_obj_t * ui_SettingsButton4;
void ui_event_ManualControlButton4(lv_event_t * e);
extern lv_obj_t * ui_ManualControlButton4;
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
