
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

void ui_event_MainScreen( lv_event_t * e);
extern lv_obj_t *ui_MainScreen;
extern lv_obj_t *ui_MainScreenPanel;
extern lv_obj_t *ui_Screen1_Chart1;
void ui_event_StartStopButton( lv_event_t * e);
extern lv_obj_t *ui_StartStopButton;
extern lv_obj_t *ui_StartStopLabel;
extern lv_obj_t *ui_TopPanel;
extern lv_obj_t *ui_TemperatureDisplay;
void ui_event_SettingsButton1( lv_event_t * e);
extern lv_obj_t *ui_SettingsButton1;
void ui_event_ManualControlButton( lv_event_t * e);
extern lv_obj_t *ui_ManualControlButton;
void ui_event_ManualControlScreen( lv_event_t * e);
extern lv_obj_t *ui_ManualControlScreen;
extern lv_obj_t *ui_ManualControlPanel;
void ui_event_HeatingButton( lv_event_t * e);
extern lv_obj_t *ui_HeatingButton;
extern lv_obj_t *ui_HeatingButtonLabel;
void ui_event_CoolingButton( lv_event_t * e);
extern lv_obj_t *ui_CoolingButton;
extern lv_obj_t *ui_CoolingButtonLabel;
void ui_event_MixingButton( lv_event_t * e);
extern lv_obj_t *ui_MixingButton;
extern lv_obj_t *ui_MixingButtonLabel;
extern lv_obj_t *ui_ManualControlLabel;
extern lv_obj_t *ui_TopPanel1;
extern lv_obj_t *ui_TemperatureDisplay1;
void ui_event_ManualControlButton1( lv_event_t * e);
extern lv_obj_t *ui_ManualControlButton1;
void ui_event_SettingsScreen( lv_event_t * e);
extern lv_obj_t *ui_SettingsScreen;
extern lv_obj_t *ui_SettingsPanel;
extern lv_obj_t *ui_PastTempPanel;
extern lv_obj_t *ui_PastTemp;
void ui_event_PastTempDecr( lv_event_t * e);
extern lv_obj_t *ui_PastTempDecr;
extern lv_obj_t *ui_PastTempDecrLabel;
void ui_event_PastTempIncr( lv_event_t * e);
extern lv_obj_t *ui_PastTempIncr;
extern lv_obj_t *ui_PastTempIncrLabel;
extern lv_obj_t *ui_PastTempTextLabel;
extern lv_obj_t *ui_PastTimePanel;
extern lv_obj_t *ui_PastTime;
void ui_event_PastTimeDec( lv_event_t * e);
extern lv_obj_t *ui_PastTimeDec;
extern lv_obj_t *ui_PastTimeDecLabel;
void ui_event_PastTimeIncr( lv_event_t * e);
extern lv_obj_t *ui_PastTimeIncr;
extern lv_obj_t *ui_PastTimeIncrLabel;
extern lv_obj_t *ui_PastTimeTextLabel;
void ui_event_ApplyButton( lv_event_t * e);
extern lv_obj_t *ui_ApplyButton;
extern lv_obj_t *ui_StartStopLabel1;
extern lv_obj_t *ui_TopPanel2;
extern lv_obj_t *ui_TemperatureDisplay2;
void ui_event_SettingsButton2( lv_event_t * e);
extern lv_obj_t *ui_SettingsButton2;
void ui_event_ManualControlButton2( lv_event_t * e);
extern lv_obj_t *ui_ManualControlButton2;
void ui_event_SettingsScreen2( lv_event_t * e);
extern lv_obj_t *ui_SettingsScreen2;
extern lv_obj_t *ui_SettingsPanel2;
extern lv_obj_t *ui_StoreTimePanel;
extern lv_obj_t *ui_StorageTemp1;
void ui_event_StorageTempDecr1( lv_event_t * e);
extern lv_obj_t *ui_StorageTempDecr1;
extern lv_obj_t *ui_StoreTempDecrLabel;
void ui_event_StorageTempIncr1( lv_event_t * e);
extern lv_obj_t *ui_StorageTempIncr1;
extern lv_obj_t *ui_StoreTempIncrLabel;
extern lv_obj_t *ui_Screen3_Label22;
void ui_event_ApplyButton1( lv_event_t * e);
extern lv_obj_t *ui_ApplyButton1;
extern lv_obj_t *ui_StartStopLabel2;
extern lv_obj_t *ui_TopPanel3;
extern lv_obj_t *ui_TemperatureDisplay3;
void ui_event_SettingsButton3( lv_event_t * e);
extern lv_obj_t *ui_SettingsButton3;
void ui_event_ManualControlButton3( lv_event_t * e);
extern lv_obj_t *ui_ManualControlButton3;
void ui_event_WirelessConnectionScreen( lv_event_t * e);
extern lv_obj_t *ui_WirelessConnectionScreen;
extern lv_obj_t *ui_SettingsPanel1;
void ui_event_WifiKeyboard( lv_event_t * e);
extern lv_obj_t *ui_WifiKeyboard;
void ui_event_WifiName( lv_event_t * e);
extern lv_obj_t *ui_WifiName;
void ui_event_WifiPassword( lv_event_t * e);
extern lv_obj_t *ui_WifiPassword;
extern lv_obj_t *ui_Screen3_Label13;
extern lv_obj_t *ui_Screen3_Label14;
extern lv_obj_t *ui_TopPanel4;
extern lv_obj_t *ui_TemperatureDisplay4;
extern lv_obj_t *ui_SettingsButton4;
void ui_event_ManualControlButton4( lv_event_t * e);
extern lv_obj_t *ui_ManualControlButton4;




LV_FONT_DECLARE( ui_font_bigfont);
LV_FONT_DECLARE( ui_font_hack);
LV_FONT_DECLARE( ui_font_tempfont);
LV_FONT_DECLARE( ui_font_symbols);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
