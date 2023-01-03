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
extern lv_obj_t *ui_ManualControlScreen;
extern lv_obj_t *ui_ManualControlPanel;
void ui_event_HeatingButton( lv_event_t * e);
extern lv_obj_t *ui_HeatingButton;
extern lv_obj_t *ui_Screen1_Label11;
void ui_event_CoolingButton( lv_event_t * e);
extern lv_obj_t *ui_CoolingButton;
extern lv_obj_t *ui_Screen1_Label13;
void ui_event_MixingButton( lv_event_t * e);
extern lv_obj_t *ui_MixingButton;
extern lv_obj_t *ui_Screen1_Label14;
extern lv_obj_t *ui_Screen2_Label10;
extern lv_obj_t *ui_TopPanel1;
extern lv_obj_t *ui_TemperatureDisplay1;
void ui_event_BackButton1( lv_event_t * e);
extern lv_obj_t *ui_BackButton1;
extern lv_obj_t *ui_SettingsScreen;
extern lv_obj_t *ui_SettingsPanel;
extern lv_obj_t *ui_Screen3_Label7;
extern lv_obj_t *ui_PastTemp;
void ui_event_PastTempDecr( lv_event_t * e);
extern lv_obj_t *ui_PastTempDecr;
extern lv_obj_t *ui_Screen3_Label8;
void ui_event_PastTempIncr( lv_event_t * e);
extern lv_obj_t *ui_PastTempIncr;
extern lv_obj_t *ui_Screen3_Label1;
extern lv_obj_t *ui_Screen3_Label9;
extern lv_obj_t *ui_Screen3_Label2;
extern lv_obj_t *ui_StorageTemp;
void ui_event_StorageTempDecr( lv_event_t * e);
extern lv_obj_t *ui_StorageTempDecr;
extern lv_obj_t *ui_Screen3_Label3;
void ui_event_StorageTempIncr( lv_event_t * e);
extern lv_obj_t *ui_StorageTempIncr;
extern lv_obj_t *ui_Screen3_Label4;
extern lv_obj_t *ui_Screen3_Label5;
extern lv_obj_t *ui_Screen3_Label6;
extern lv_obj_t *ui_PastTime;
void ui_event_PastTimeDec( lv_event_t * e);
extern lv_obj_t *ui_PastTimeDec;
extern lv_obj_t *ui_Screen3_Label10;
void ui_event_PastTimeIncr( lv_event_t * e);
extern lv_obj_t *ui_PastTimeIncr;
extern lv_obj_t *ui_Screen3_Label11;
extern lv_obj_t *ui_Screen3_Label12;
extern lv_obj_t *ui_TopPanel2;
extern lv_obj_t *ui_TemperatureDisplay2;
void ui_event_BackButton2( lv_event_t * e);
extern lv_obj_t *ui_BackButton2;
void ui_event_WifiSettingsButton( lv_event_t * e);
extern lv_obj_t *ui_WifiSettingsButton;
extern lv_obj_t *ui_WirelessConnectionScreen;
extern lv_obj_t *ui_SettingsPanel1;
extern lv_obj_t *ui_WIfiKeyboard;
void ui_event_WifiName( lv_event_t * e);
extern lv_obj_t *ui_WifiName;
void ui_event_WifiPassword( lv_event_t * e);
extern lv_obj_t *ui_WifiPassword;
extern lv_obj_t *ui_Screen3_Label13;
extern lv_obj_t *ui_Screen3_Label14;
extern lv_obj_t *ui_TopPanel3;
extern lv_obj_t *ui_TemperatureDisplay3;
void ui_event_BackButton3( lv_event_t * e);
extern lv_obj_t *ui_BackButton3;

void on_main_button_pressed(lv_event_t * e);
void go_to_settings(lv_event_t * e);
void go_to_manual_control(lv_event_t * e);
void on_manual_heating(lv_event_t * e);
void on_manual_cooling(lv_event_t * e);
void on_manual_mixing(lv_event_t * e);
void go_back_1(lv_event_t * e);
void on_past_temp_decr(lv_event_t * e);
void on_past_temp_incr(lv_event_t * e);
void on_storage_temp_decr(lv_event_t * e);
void on_storage_temp_incr(lv_event_t * e);
void on_past_time_decr(lv_event_t * e);
void on_past_time_incr(lv_event_t * e);
void go_back_1(lv_event_t * e);
void go_to_settings(lv_event_t * e);
void on_ap_focused(lv_event_t * e);
void on_password_focused(lv_event_t * e);
void go_back_1(lv_event_t * e);



LV_FONT_DECLARE( ui_font_bigfont);
LV_FONT_DECLARE( ui_font_hack);
LV_FONT_DECLARE( ui_font_tempfont);
LV_FONT_DECLARE( ui_font_symbols);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
