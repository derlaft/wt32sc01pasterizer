
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ui_event_MainScreen( lv_event_t * e);
lv_obj_t *ui_MainScreen;
lv_obj_t *ui_MainScreenPanel;
lv_obj_t *ui_Screen1_Chart1;
lv_obj_t *ui_ChartCommentLabel;
void ui_event_StartStopButton( lv_event_t * e);
lv_obj_t *ui_StartStopButton;
lv_obj_t *ui_StartStopLabel;
lv_obj_t *ui_TopPanel;
lv_obj_t *ui_TemperatureDisplay;
void ui_event_SettingsButton1( lv_event_t * e);
lv_obj_t *ui_SettingsButton1;
void ui_event_ManualControlButton( lv_event_t * e);
lv_obj_t *ui_ManualControlButton;
void ui_event_ManualControlScreen( lv_event_t * e);
lv_obj_t *ui_ManualControlScreen;
lv_obj_t *ui_ManualControlPanel;
void ui_event_HeatingButton( lv_event_t * e);
lv_obj_t *ui_HeatingButton;
lv_obj_t *ui_HeatingButtonLabel;
void ui_event_CoolingButton( lv_event_t * e);
lv_obj_t *ui_CoolingButton;
lv_obj_t *ui_CoolingButtonLabel;
void ui_event_MixingButton( lv_event_t * e);
lv_obj_t *ui_MixingButton;
lv_obj_t *ui_MixingButtonLabel;
lv_obj_t *ui_ManualControlLabel;
lv_obj_t *ui_TopPanel1;
lv_obj_t *ui_TemperatureDisplay1;
void ui_event_ManualControlButton1( lv_event_t * e);
lv_obj_t *ui_ManualControlButton1;
void ui_event_SettingsScreen( lv_event_t * e);
lv_obj_t *ui_SettingsScreen;
lv_obj_t *ui_SettingsPanel;
lv_obj_t *ui_PastTempPanel;
lv_obj_t *ui_PastTemp;
void ui_event_PastTempDecr( lv_event_t * e);
lv_obj_t *ui_PastTempDecr;
lv_obj_t *ui_PastTempDecrLabel;
void ui_event_PastTempIncr( lv_event_t * e);
lv_obj_t *ui_PastTempIncr;
lv_obj_t *ui_PastTempIncrLabel;
lv_obj_t *ui_PastTempTextLabel;
lv_obj_t *ui_PastTimePanel;
lv_obj_t *ui_PastTime;
void ui_event_PastTimeDec( lv_event_t * e);
lv_obj_t *ui_PastTimeDec;
lv_obj_t *ui_PastTimeDecLabel;
void ui_event_PastTimeIncr( lv_event_t * e);
lv_obj_t *ui_PastTimeIncr;
lv_obj_t *ui_PastTimeIncrLabel;
lv_obj_t *ui_PastTimeTextLabel;
void ui_event_ApplyButton( lv_event_t * e);
lv_obj_t *ui_ApplyButton;
lv_obj_t *ui_StartStopLabel1;
lv_obj_t *ui_TopPanel2;
lv_obj_t *ui_TemperatureDisplay2;
void ui_event_SettingsButton2( lv_event_t * e);
lv_obj_t *ui_SettingsButton2;
void ui_event_ManualControlButton2( lv_event_t * e);
lv_obj_t *ui_ManualControlButton2;
void ui_event_SettingsScreen2( lv_event_t * e);
lv_obj_t *ui_SettingsScreen2;
lv_obj_t *ui_SettingsPanel2;
lv_obj_t *ui_StoreTimePanel;
lv_obj_t *ui_StorageTemp1;
void ui_event_StorageTempDecr1( lv_event_t * e);
lv_obj_t *ui_StorageTempDecr1;
lv_obj_t *ui_StoreTempDecrLabel;
void ui_event_StorageTempIncr1( lv_event_t * e);
lv_obj_t *ui_StorageTempIncr1;
lv_obj_t *ui_StoreTempIncrLabel;
lv_obj_t *ui_Screen3_Label22;
void ui_event_ApplyButton1( lv_event_t * e);
lv_obj_t *ui_ApplyButton1;
lv_obj_t *ui_StartStopLabel2;
lv_obj_t *ui_TopPanel3;
lv_obj_t *ui_TemperatureDisplay3;
void ui_event_SettingsButton3( lv_event_t * e);
lv_obj_t *ui_SettingsButton3;
void ui_event_ManualControlButton3( lv_event_t * e);
lv_obj_t *ui_ManualControlButton3;
void ui_event_WirelessConnectionScreen( lv_event_t * e);
lv_obj_t *ui_WirelessConnectionScreen;
lv_obj_t *ui_SettingsPanel1;
void ui_event_WifiKeyboard( lv_event_t * e);
lv_obj_t *ui_WifiKeyboard;
void ui_event_WifiName( lv_event_t * e);
lv_obj_t *ui_WifiName;
void ui_event_WifiPassword( lv_event_t * e);
lv_obj_t *ui_WifiPassword;
lv_obj_t *ui_Screen3_Label13;
lv_obj_t *ui_Screen3_Label14;
lv_obj_t *ui_TopPanel4;
lv_obj_t *ui_TemperatureDisplay4;
lv_obj_t *ui_SettingsButton4;
void ui_event_ManualControlButton4( lv_event_t * e);
lv_obj_t *ui_ManualControlButton4;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_MainScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      on_main_screen_loaded( e );
}
}
void ui_event_StartStopButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_main_button_pressed( e );
}
}
void ui_event_SettingsButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_SettingsScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
}
}
void ui_event_ManualControlButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_ManualControlScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
}
}
void ui_event_ManualControlScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      on_manual_control_screen_loaded( e );
}
}
void ui_event_HeatingButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      on_manual_heating( e );
}
}
void ui_event_CoolingButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      on_manual_cooling( e );
}
}
void ui_event_MixingButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      on_manual_mixing( e );
}
}
void ui_event_ManualControlButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_MainScreen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
}
}
void ui_event_SettingsScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      on_settings_screen_loaded( e );
}
}
void ui_event_PastTempDecr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_temp_incr( e );
}
}
void ui_event_PastTempIncr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_temp_decr( e );
}
}
void ui_event_PastTimeDec( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_time_incr( e );
}
}
void ui_event_PastTimeIncr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_time_decr( e );
}
}
void ui_event_ApplyButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_save_settings( e );
}
}
void ui_event_SettingsButton2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_SettingsScreen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
}
}
void ui_event_ManualControlButton2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_MainScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
}
}
void ui_event_SettingsScreen2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      on_settings_screen_2_loaded( e );
}
}
void ui_event_StorageTempDecr1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_storage_temp_incr( e );
}
}
void ui_event_StorageTempIncr1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_storage_temp_decr( e );
}
}
void ui_event_ApplyButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_save_settings( e );
}
}
void ui_event_SettingsButton3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_WirelessConnectionScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
}
}
void ui_event_ManualControlButton3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_SettingsScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
}
}
void ui_event_WirelessConnectionScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      on_wireless_screen_loaded( e );
}
}
void ui_event_WifiKeyboard( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_READY) {
      on_keyboard_press( e );
}
}
void ui_event_WifiName( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_FOCUSED) {
      on_ap_focused( e );
}
}
void ui_event_WifiPassword( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_FOCUSED) {
      on_password_focused( e );
}
}
void ui_event_ManualControlButton4( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( ui_SettingsScreen2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
}
}

///////////////////// SCREENS ////////////////////
void ui_MainScreen_screen_init(void)
{
ui_MainScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_MainScreenPanel = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_MainScreenPanel, lv_pct(96));
lv_obj_set_height( ui_MainScreenPanel, lv_pct(74));
lv_obj_set_x( ui_MainScreenPanel, 0 );
lv_obj_set_y( ui_MainScreenPanel, -7 );
lv_obj_set_align( ui_MainScreenPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_MainScreenPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_MainScreenPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainScreenPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainScreenPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainScreenPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen1_Chart1 = lv_chart_create(ui_MainScreenPanel);
lv_obj_set_height( ui_Screen1_Chart1, 170);
lv_obj_set_width( ui_Screen1_Chart1, lv_pct(100));
lv_obj_set_align( ui_Screen1_Chart1, LV_ALIGN_TOP_MID );
lv_obj_set_style_radius(ui_Screen1_Chart1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_Screen1_Chart1, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
on_chart_init();

ui_ChartCommentLabel = lv_label_create(ui_Screen1_Chart1);
lv_obj_set_width( ui_ChartCommentLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ChartCommentLabel, LV_SIZE_CONTENT);   /// 1
lv_label_set_text(ui_ChartCommentLabel,"Готов к работе");
lv_obj_set_style_text_color(ui_ChartCommentLabel, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ChartCommentLabel, 240, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ChartCommentLabel, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StartStopButton = lv_btn_create(ui_MainScreenPanel);
lv_obj_set_width( ui_StartStopButton, lv_pct(100));
lv_obj_set_height( ui_StartStopButton, lv_pct(25));
lv_obj_set_align( ui_StartStopButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_StartStopButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_StartStopButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_StartStopButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_StartStopButton, lv_color_hex(0x007B00), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_StartStopButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StartStopLabel = lv_label_create(ui_StartStopButton);
lv_obj_set_width( ui_StartStopLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_StartStopLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StartStopLabel, 0 );
lv_obj_set_y( ui_StartStopLabel, 3 );
lv_obj_set_align( ui_StartStopLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_StartStopLabel,"");
lv_obj_set_style_text_font(ui_StartStopLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_TopPanel, lv_pct(100));
lv_obj_set_height( ui_TopPanel, lv_pct(22));
lv_obj_set_align( ui_TopPanel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TopPanel,"");
lv_obj_set_style_text_color(ui_TopPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TopPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_TopPanel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_TopPanel, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TopPanel, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_TopPanel, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_TopPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_TopPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_TopPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_TopPanel, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_TopPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TemperatureDisplay = lv_label_create(ui_TopPanel);
lv_obj_set_width( ui_TemperatureDisplay, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TemperatureDisplay, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_TemperatureDisplay, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TemperatureDisplay,"+125°");
lv_obj_set_style_text_align(ui_TemperatureDisplay, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TemperatureDisplay, &ui_font_tempfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SettingsButton1 = lv_label_create(ui_TopPanel);
lv_obj_set_width( ui_SettingsButton1, 70);
lv_obj_set_height( ui_SettingsButton1, 63);
lv_obj_set_x( ui_SettingsButton1, -19 );
lv_obj_set_y( ui_SettingsButton1, -12 );
lv_obj_set_align( ui_SettingsButton1, LV_ALIGN_TOP_RIGHT );
lv_label_set_text(ui_SettingsButton1,"B");
lv_obj_add_flag( ui_SettingsButton1, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_SettingsButton1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SettingsButton1, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SettingsButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsButton1, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ManualControlButton = lv_label_create(ui_TopPanel);
lv_obj_set_width( ui_ManualControlButton, 70);
lv_obj_set_height( ui_ManualControlButton, 63);
lv_obj_set_x( ui_ManualControlButton, 19 );
lv_obj_set_y( ui_ManualControlButton, -12 );
lv_label_set_text(ui_ManualControlButton,"C");
lv_obj_add_flag( ui_ManualControlButton, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_ManualControlButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ManualControlButton, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_ManualControlButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_ManualControlButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_ManualControlButton, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_ManualControlButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_StartStopButton, ui_event_StartStopButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsButton1, ui_event_SettingsButton1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ManualControlButton, ui_event_ManualControlButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_MainScreen, ui_event_MainScreen, LV_EVENT_ALL, NULL);

}
void ui_ManualControlScreen_screen_init(void)
{
ui_ManualControlScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_ManualControlScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_ManualControlPanel = lv_obj_create(ui_ManualControlScreen);
lv_obj_set_width( ui_ManualControlPanel, lv_pct(96));
lv_obj_set_height( ui_ManualControlPanel, lv_pct(74));
lv_obj_set_x( ui_ManualControlPanel, 0 );
lv_obj_set_y( ui_ManualControlPanel, -9 );
lv_obj_set_align( ui_ManualControlPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_ManualControlPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_ManualControlPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_ManualControlPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_ManualControlPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_ManualControlPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_HeatingButton = lv_btn_create(ui_ManualControlPanel);
lv_obj_set_width( ui_HeatingButton, lv_pct(100));
lv_obj_set_height( ui_HeatingButton, lv_pct(25));
lv_obj_set_x( ui_HeatingButton, 0 );
lv_obj_set_y( ui_HeatingButton, -60 );
lv_obj_set_align( ui_HeatingButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_HeatingButton, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_HeatingButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_HeatingButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_HeatingButtonLabel = lv_label_create(ui_HeatingButton);
lv_obj_set_width( ui_HeatingButtonLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_HeatingButtonLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_HeatingButtonLabel, 0 );
lv_obj_set_y( ui_HeatingButtonLabel, 3 );
lv_obj_set_align( ui_HeatingButtonLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_HeatingButtonLabel,"Нагрев");
lv_obj_set_style_text_font(ui_HeatingButtonLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CoolingButton = lv_btn_create(ui_ManualControlPanel);
lv_obj_set_width( ui_CoolingButton, lv_pct(100));
lv_obj_set_height( ui_CoolingButton, lv_pct(25));
lv_obj_set_x( ui_CoolingButton, 0 );
lv_obj_set_y( ui_CoolingButton, -120 );
lv_obj_set_align( ui_CoolingButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_CoolingButton, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_CoolingButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_CoolingButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CoolingButtonLabel = lv_label_create(ui_CoolingButton);
lv_obj_set_width( ui_CoolingButtonLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CoolingButtonLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CoolingButtonLabel, 0 );
lv_obj_set_y( ui_CoolingButtonLabel, 3 );
lv_obj_set_align( ui_CoolingButtonLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_CoolingButtonLabel,"Охлаждение");
lv_obj_set_style_text_font(ui_CoolingButtonLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MixingButton = lv_btn_create(ui_ManualControlPanel);
lv_obj_set_width( ui_MixingButton, lv_pct(100));
lv_obj_set_height( ui_MixingButton, lv_pct(25));
lv_obj_set_align( ui_MixingButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_MixingButton, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_MixingButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_MixingButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MixingButtonLabel = lv_label_create(ui_MixingButton);
lv_obj_set_width( ui_MixingButtonLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_MixingButtonLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_MixingButtonLabel, 0 );
lv_obj_set_y( ui_MixingButtonLabel, 3 );
lv_obj_set_align( ui_MixingButtonLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_MixingButtonLabel,"Перемешивание");
lv_obj_set_style_text_font(ui_MixingButtonLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ManualControlLabel = lv_label_create(ui_ManualControlScreen);
lv_obj_set_width( ui_ManualControlLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ManualControlLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ManualControlLabel, -3 );
lv_obj_set_y( ui_ManualControlLabel, -57 );
lv_obj_set_align( ui_ManualControlLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_ManualControlLabel,"Ручное управление");
lv_obj_set_style_text_font(ui_ManualControlLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel1 = lv_label_create(ui_ManualControlScreen);
lv_obj_set_width( ui_TopPanel1, lv_pct(100));
lv_obj_set_height( ui_TopPanel1, lv_pct(22));
lv_obj_set_align( ui_TopPanel1, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TopPanel1,"");
lv_obj_set_style_text_color(ui_TopPanel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TopPanel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_TopPanel1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_TopPanel1, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TopPanel1, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_TopPanel1, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_TopPanel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_TopPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_TopPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_TopPanel1, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_TopPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TemperatureDisplay1 = lv_label_create(ui_TopPanel1);
lv_obj_set_width( ui_TemperatureDisplay1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TemperatureDisplay1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_TemperatureDisplay1, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TemperatureDisplay1,"+125°");
lv_obj_set_style_text_align(ui_TemperatureDisplay1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TemperatureDisplay1, &ui_font_tempfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ManualControlButton1 = lv_label_create(ui_TopPanel1);
lv_obj_set_width( ui_ManualControlButton1, 70);
lv_obj_set_height( ui_ManualControlButton1, 63);
lv_obj_set_x( ui_ManualControlButton1, 19 );
lv_obj_set_y( ui_ManualControlButton1, -12 );
lv_label_set_text(ui_ManualControlButton1,"F");
lv_obj_add_flag( ui_ManualControlButton1, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_ManualControlButton1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ManualControlButton1, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_ManualControlButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_ManualControlButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_ManualControlButton1, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_ManualControlButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_HeatingButton, ui_event_HeatingButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_CoolingButton, ui_event_CoolingButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_MixingButton, ui_event_MixingButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ManualControlButton1, ui_event_ManualControlButton1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ManualControlScreen, ui_event_ManualControlScreen, LV_EVENT_ALL, NULL);

}
void ui_SettingsScreen_screen_init(void)
{
ui_SettingsScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_SettingsScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SettingsPanel = lv_obj_create(ui_SettingsScreen);
lv_obj_set_width( ui_SettingsPanel, lv_pct(96));
lv_obj_set_height( ui_SettingsPanel, lv_pct(74));
lv_obj_set_x( ui_SettingsPanel, -1 );
lv_obj_set_y( ui_SettingsPanel, -10 );
lv_obj_set_align( ui_SettingsPanel, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_SettingsPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_SettingsPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTempPanel = lv_label_create(ui_SettingsPanel);
lv_obj_set_width( ui_PastTempPanel, lv_pct(100));
lv_obj_set_height( ui_PastTempPanel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTempPanel, 0 );
lv_obj_set_y( ui_PastTempPanel, 20 );
lv_obj_set_align( ui_PastTempPanel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_PastTempPanel,"");
lv_obj_set_style_text_align(ui_PastTempPanel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_PastTempPanel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTemp = lv_textarea_create(ui_PastTempPanel);
lv_obj_set_width( ui_PastTemp, 75);
lv_obj_set_height( ui_PastTemp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTemp, 100 );
lv_obj_set_y( ui_PastTemp, 0 );
lv_obj_set_align( ui_PastTemp, LV_ALIGN_CENTER );
lv_textarea_set_text(ui_PastTemp,"70");
lv_textarea_set_placeholder_text(ui_PastTemp,"Placeholder...");
lv_obj_clear_flag( ui_PastTemp, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_align(ui_PastTemp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_PastTemp, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTempDecr = lv_btn_create(ui_PastTempPanel);
lv_obj_set_width( ui_PastTempDecr, 60);
lv_obj_set_height( ui_PastTempDecr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTempDecr, 185 );
lv_obj_set_y( ui_PastTempDecr, 0 );
lv_obj_set_align( ui_PastTempDecr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTempDecr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTempDecr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_PastTempDecrLabel = lv_label_create(ui_PastTempDecr);
lv_obj_set_width( ui_PastTempDecrLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_PastTempDecrLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_PastTempDecrLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_PastTempDecrLabel,"+");
lv_obj_set_style_text_font(ui_PastTempDecrLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTempIncr = lv_btn_create(ui_PastTempPanel);
lv_obj_set_width( ui_PastTempIncr, 60);
lv_obj_set_height( ui_PastTempIncr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTempIncr, 20 );
lv_obj_set_y( ui_PastTempIncr, 0 );
lv_obj_set_align( ui_PastTempIncr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTempIncr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTempIncr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_PastTempIncrLabel = lv_label_create(ui_PastTempIncr);
lv_obj_set_width( ui_PastTempIncrLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_PastTempIncrLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_PastTempIncrLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_PastTempIncrLabel,"-");
lv_obj_set_style_text_font(ui_PastTempIncrLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTempTextLabel = lv_label_create(ui_PastTempPanel);
lv_obj_set_width( ui_PastTempTextLabel, lv_pct(50));
lv_obj_set_height( ui_PastTempTextLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTempTextLabel, 15 );
lv_obj_set_y( ui_PastTempTextLabel, 0 );
lv_label_set_text(ui_PastTempTextLabel,"Температура\nпастеризации");
lv_obj_set_style_text_font(ui_PastTempTextLabel, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_PastTempTextLabel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_PastTempTextLabel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_PastTempTextLabel, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_PastTempTextLabel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTimePanel = lv_label_create(ui_SettingsPanel);
lv_obj_set_width( ui_PastTimePanel, lv_pct(100));
lv_obj_set_height( ui_PastTimePanel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTimePanel, 0 );
lv_obj_set_y( ui_PastTimePanel, 95 );
lv_obj_set_align( ui_PastTimePanel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_PastTimePanel,"");
lv_obj_set_style_text_align(ui_PastTimePanel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_PastTimePanel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTime = lv_textarea_create(ui_PastTimePanel);
lv_obj_set_width( ui_PastTime, 80);
lv_obj_set_height( ui_PastTime, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTime, 102 );
lv_obj_set_y( ui_PastTime, 0 );
lv_obj_set_align( ui_PastTime, LV_ALIGN_CENTER );
lv_textarea_set_text(ui_PastTime,"30");
lv_textarea_set_placeholder_text(ui_PastTime,"Placeholder...");
lv_obj_clear_flag( ui_PastTime, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_align(ui_PastTime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_PastTime, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTimeDec = lv_btn_create(ui_PastTimePanel);
lv_obj_set_width( ui_PastTimeDec, 60);
lv_obj_set_height( ui_PastTimeDec, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTimeDec, 185 );
lv_obj_set_y( ui_PastTimeDec, 0 );
lv_obj_set_align( ui_PastTimeDec, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTimeDec, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTimeDec, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_PastTimeDecLabel = lv_label_create(ui_PastTimeDec);
lv_obj_set_width( ui_PastTimeDecLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_PastTimeDecLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_PastTimeDecLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_PastTimeDecLabel,"+");
lv_obj_set_style_text_font(ui_PastTimeDecLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTimeIncr = lv_btn_create(ui_PastTimePanel);
lv_obj_set_width( ui_PastTimeIncr, 60);
lv_obj_set_height( ui_PastTimeIncr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTimeIncr, 20 );
lv_obj_set_y( ui_PastTimeIncr, 0 );
lv_obj_set_align( ui_PastTimeIncr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTimeIncr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTimeIncr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_PastTimeIncrLabel = lv_label_create(ui_PastTimeIncr);
lv_obj_set_width( ui_PastTimeIncrLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_PastTimeIncrLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_PastTimeIncrLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_PastTimeIncrLabel,"-");
lv_obj_set_style_text_font(ui_PastTimeIncrLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTimeTextLabel = lv_label_create(ui_PastTimePanel);
lv_obj_set_width( ui_PastTimeTextLabel, lv_pct(50));
lv_obj_set_height( ui_PastTimeTextLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTimeTextLabel, 16 );
lv_obj_set_y( ui_PastTimeTextLabel, 0 );
lv_label_set_text(ui_PastTimeTextLabel,"Время пастеризации\nминуты");
lv_obj_set_style_text_font(ui_PastTimeTextLabel, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_PastTimeTextLabel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_PastTimeTextLabel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_PastTimeTextLabel, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_PastTimeTextLabel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ApplyButton = lv_btn_create(ui_SettingsPanel);
lv_obj_set_width( ui_ApplyButton, lv_pct(100));
lv_obj_set_height( ui_ApplyButton, lv_pct(25));
lv_obj_set_x( ui_ApplyButton, 0 );
lv_obj_set_y( ui_ApplyButton, -1 );
lv_obj_set_align( ui_ApplyButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_ApplyButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ApplyButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_ApplyButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StartStopLabel1 = lv_label_create(ui_ApplyButton);
lv_obj_set_width( ui_StartStopLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_StartStopLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StartStopLabel1, 0 );
lv_obj_set_y( ui_StartStopLabel1, 3 );
lv_obj_set_align( ui_StartStopLabel1, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_StartStopLabel1,"Сохранить");
lv_obj_set_style_text_font(ui_StartStopLabel1, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel2 = lv_label_create(ui_SettingsScreen);
lv_obj_set_width( ui_TopPanel2, lv_pct(100));
lv_obj_set_height( ui_TopPanel2, lv_pct(22));
lv_obj_set_align( ui_TopPanel2, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TopPanel2,"");
lv_obj_set_style_text_color(ui_TopPanel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TopPanel2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_TopPanel2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_TopPanel2, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TopPanel2, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_TopPanel2, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_TopPanel2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_TopPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_TopPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_TopPanel2, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_TopPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TemperatureDisplay2 = lv_label_create(ui_TopPanel2);
lv_obj_set_width( ui_TemperatureDisplay2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TemperatureDisplay2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_TemperatureDisplay2, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TemperatureDisplay2,"+125°");
lv_obj_set_style_text_align(ui_TemperatureDisplay2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TemperatureDisplay2, &ui_font_tempfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SettingsButton2 = lv_label_create(ui_TopPanel2);
lv_obj_set_width( ui_SettingsButton2, 70);
lv_obj_set_height( ui_SettingsButton2, 63);
lv_obj_set_x( ui_SettingsButton2, -19 );
lv_obj_set_y( ui_SettingsButton2, -12 );
lv_obj_set_align( ui_SettingsButton2, LV_ALIGN_TOP_RIGHT );
lv_label_set_text(ui_SettingsButton2,"E");
lv_obj_add_flag( ui_SettingsButton2, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_SettingsButton2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SettingsButton2, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SettingsButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsButton2, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ManualControlButton2 = lv_label_create(ui_TopPanel2);
lv_obj_set_width( ui_ManualControlButton2, 70);
lv_obj_set_height( ui_ManualControlButton2, 63);
lv_obj_set_x( ui_ManualControlButton2, 19 );
lv_obj_set_y( ui_ManualControlButton2, -12 );
lv_label_set_text(ui_ManualControlButton2,"F");
lv_obj_add_flag( ui_ManualControlButton2, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_ManualControlButton2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ManualControlButton2, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_ManualControlButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_ManualControlButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_ManualControlButton2, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_ManualControlButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_PastTempDecr, ui_event_PastTempDecr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_PastTempIncr, ui_event_PastTempIncr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_PastTimeDec, ui_event_PastTimeDec, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_PastTimeIncr, ui_event_PastTimeIncr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ApplyButton, ui_event_ApplyButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsButton2, ui_event_SettingsButton2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ManualControlButton2, ui_event_ManualControlButton2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsScreen, ui_event_SettingsScreen, LV_EVENT_ALL, NULL);

}
void ui_SettingsScreen2_screen_init(void)
{
ui_SettingsScreen2 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_SettingsScreen2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SettingsPanel2 = lv_obj_create(ui_SettingsScreen2);
lv_obj_set_width( ui_SettingsPanel2, lv_pct(96));
lv_obj_set_height( ui_SettingsPanel2, lv_pct(74));
lv_obj_set_x( ui_SettingsPanel2, -1 );
lv_obj_set_y( ui_SettingsPanel2, -10 );
lv_obj_set_align( ui_SettingsPanel2, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_SettingsPanel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_SettingsPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsPanel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StoreTimePanel = lv_label_create(ui_SettingsPanel2);
lv_obj_set_width( ui_StoreTimePanel, lv_pct(100));
lv_obj_set_height( ui_StoreTimePanel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StoreTimePanel, 0 );
lv_obj_set_y( ui_StoreTimePanel, 20 );
lv_obj_set_align( ui_StoreTimePanel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_StoreTimePanel,"");
lv_obj_set_style_text_align(ui_StoreTimePanel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_StoreTimePanel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StorageTemp1 = lv_textarea_create(ui_StoreTimePanel);
lv_obj_set_width( ui_StorageTemp1, 75);
lv_obj_set_height( ui_StorageTemp1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StorageTemp1, 100 );
lv_obj_set_y( ui_StorageTemp1, 0 );
lv_obj_set_align( ui_StorageTemp1, LV_ALIGN_CENTER );
lv_textarea_set_text(ui_StorageTemp1,"42");
lv_textarea_set_placeholder_text(ui_StorageTemp1,"Placeholder...");
lv_obj_clear_flag( ui_StorageTemp1, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_align(ui_StorageTemp1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_StorageTemp1, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StorageTempDecr1 = lv_btn_create(ui_StoreTimePanel);
lv_obj_set_width( ui_StorageTempDecr1, 60);
lv_obj_set_height( ui_StorageTempDecr1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StorageTempDecr1, 185 );
lv_obj_set_y( ui_StorageTempDecr1, 0 );
lv_obj_set_align( ui_StorageTempDecr1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_StorageTempDecr1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_StorageTempDecr1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_StoreTempDecrLabel = lv_label_create(ui_StorageTempDecr1);
lv_obj_set_width( ui_StoreTempDecrLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_StoreTempDecrLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_StoreTempDecrLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_StoreTempDecrLabel,"+");
lv_obj_set_style_text_font(ui_StoreTempDecrLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StorageTempIncr1 = lv_btn_create(ui_StoreTimePanel);
lv_obj_set_width( ui_StorageTempIncr1, 60);
lv_obj_set_height( ui_StorageTempIncr1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StorageTempIncr1, 20 );
lv_obj_set_y( ui_StorageTempIncr1, 0 );
lv_obj_set_align( ui_StorageTempIncr1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_StorageTempIncr1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_StorageTempIncr1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_StoreTempIncrLabel = lv_label_create(ui_StorageTempIncr1);
lv_obj_set_width( ui_StoreTempIncrLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_StoreTempIncrLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_StoreTempIncrLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_StoreTempIncrLabel,"-");
lv_obj_set_style_text_font(ui_StoreTempIncrLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen3_Label22 = lv_label_create(ui_StoreTimePanel);
lv_obj_set_width( ui_Screen3_Label22, lv_pct(50));
lv_obj_set_height( ui_Screen3_Label22, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label22, 15 );
lv_obj_set_y( ui_Screen3_Label22, 0 );
lv_label_set_text(ui_Screen3_Label22,"Температура\nхранения");
lv_obj_set_style_text_font(ui_Screen3_Label22, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Screen3_Label22, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Screen3_Label22, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Screen3_Label22, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Screen3_Label22, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ApplyButton1 = lv_btn_create(ui_SettingsPanel2);
lv_obj_set_width( ui_ApplyButton1, lv_pct(100));
lv_obj_set_height( ui_ApplyButton1, lv_pct(25));
lv_obj_set_x( ui_ApplyButton1, 0 );
lv_obj_set_y( ui_ApplyButton1, -1 );
lv_obj_set_align( ui_ApplyButton1, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_ApplyButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ApplyButton1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_ApplyButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StartStopLabel2 = lv_label_create(ui_ApplyButton1);
lv_obj_set_width( ui_StartStopLabel2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_StartStopLabel2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StartStopLabel2, 0 );
lv_obj_set_y( ui_StartStopLabel2, 3 );
lv_obj_set_align( ui_StartStopLabel2, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_StartStopLabel2,"Сохранить");
lv_obj_set_style_text_font(ui_StartStopLabel2, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel3 = lv_label_create(ui_SettingsScreen2);
lv_obj_set_width( ui_TopPanel3, lv_pct(100));
lv_obj_set_height( ui_TopPanel3, lv_pct(22));
lv_obj_set_align( ui_TopPanel3, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TopPanel3,"");
lv_obj_set_style_text_color(ui_TopPanel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TopPanel3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_TopPanel3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_TopPanel3, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TopPanel3, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_TopPanel3, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_TopPanel3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_TopPanel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_TopPanel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_TopPanel3, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_TopPanel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TemperatureDisplay3 = lv_label_create(ui_TopPanel3);
lv_obj_set_width( ui_TemperatureDisplay3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TemperatureDisplay3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_TemperatureDisplay3, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TemperatureDisplay3,"+125°");
lv_obj_set_style_text_align(ui_TemperatureDisplay3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TemperatureDisplay3, &ui_font_tempfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SettingsButton3 = lv_label_create(ui_TopPanel3);
lv_obj_set_width( ui_SettingsButton3, 70);
lv_obj_set_height( ui_SettingsButton3, 63);
lv_obj_set_x( ui_SettingsButton3, -19 );
lv_obj_set_y( ui_SettingsButton3, -12 );
lv_obj_set_align( ui_SettingsButton3, LV_ALIGN_TOP_RIGHT );
lv_label_set_text(ui_SettingsButton3,"E");
lv_obj_add_flag( ui_SettingsButton3, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_SettingsButton3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SettingsButton3, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SettingsButton3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsButton3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsButton3, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsButton3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ManualControlButton3 = lv_label_create(ui_TopPanel3);
lv_obj_set_width( ui_ManualControlButton3, 70);
lv_obj_set_height( ui_ManualControlButton3, 63);
lv_obj_set_x( ui_ManualControlButton3, 19 );
lv_obj_set_y( ui_ManualControlButton3, -12 );
lv_label_set_text(ui_ManualControlButton3,"F");
lv_obj_add_flag( ui_ManualControlButton3, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_ManualControlButton3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ManualControlButton3, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_ManualControlButton3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_ManualControlButton3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_ManualControlButton3, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_ManualControlButton3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_StorageTempDecr1, ui_event_StorageTempDecr1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_StorageTempIncr1, ui_event_StorageTempIncr1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ApplyButton1, ui_event_ApplyButton1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsButton3, ui_event_SettingsButton3, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ManualControlButton3, ui_event_ManualControlButton3, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsScreen2, ui_event_SettingsScreen2, LV_EVENT_ALL, NULL);

}
void ui_WirelessConnectionScreen_screen_init(void)
{
ui_WirelessConnectionScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_WirelessConnectionScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SettingsPanel1 = lv_obj_create(ui_WirelessConnectionScreen);
lv_obj_set_width( ui_SettingsPanel1, lv_pct(96));
lv_obj_set_height( ui_SettingsPanel1, lv_pct(74));
lv_obj_set_x( ui_SettingsPanel1, -1 );
lv_obj_set_y( ui_SettingsPanel1, -10 );
lv_obj_set_align( ui_SettingsPanel1, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_SettingsPanel1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_SettingsPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsPanel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_WifiKeyboard = lv_keyboard_create(ui_SettingsPanel1);
lv_obj_set_height( ui_WifiKeyboard, 120);
lv_obj_set_width( ui_WifiKeyboard, lv_pct(100));
lv_obj_set_align( ui_WifiKeyboard, LV_ALIGN_BOTTOM_MID );
lv_obj_set_scrollbar_mode(ui_WifiKeyboard, LV_SCROLLBAR_MODE_OFF);

ui_WifiName = lv_textarea_create(ui_SettingsPanel1);
lv_obj_set_width( ui_WifiName, lv_pct(50));
lv_obj_set_height( ui_WifiName, LV_SIZE_CONTENT);   /// 37
lv_obj_set_x( ui_WifiName, -10 );
lv_obj_set_y( ui_WifiName, 10 );
lv_obj_set_align( ui_WifiName, LV_ALIGN_TOP_RIGHT );
lv_textarea_set_text(ui_WifiName,"");
lv_textarea_set_placeholder_text(ui_WifiName,"SSID...");
lv_textarea_set_one_line(ui_WifiName,true);
lv_obj_clear_flag( ui_WifiName, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_scrollbar_mode(ui_WifiName, LV_SCROLLBAR_MODE_OFF);

ui_WifiPassword = lv_textarea_create(ui_SettingsPanel1);
lv_obj_set_width( ui_WifiPassword, lv_pct(50));
lv_obj_set_height( ui_WifiPassword, LV_SIZE_CONTENT);   /// 37
lv_obj_set_x( ui_WifiPassword, -10 );
lv_obj_set_y( ui_WifiPassword, 60 );
lv_obj_set_align( ui_WifiPassword, LV_ALIGN_TOP_RIGHT );
lv_textarea_set_text(ui_WifiPassword,"");
lv_textarea_set_placeholder_text(ui_WifiPassword,"Password...");
lv_textarea_set_one_line(ui_WifiPassword,true);
lv_textarea_set_password_mode(ui_WifiPassword, true);
lv_obj_clear_flag( ui_WifiPassword, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_scrollbar_mode(ui_WifiPassword, LV_SCROLLBAR_MODE_OFF);

ui_Screen3_Label13 = lv_label_create(ui_SettingsPanel1);
lv_obj_set_width( ui_Screen3_Label13, lv_pct(50));
lv_obj_set_height( ui_Screen3_Label13, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label13, 15 );
lv_obj_set_y( ui_Screen3_Label13, 56 );
lv_label_set_text(ui_Screen3_Label13,"Пароль");
lv_obj_set_style_text_font(ui_Screen3_Label13, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Screen3_Label13, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Screen3_Label13, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Screen3_Label13, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Screen3_Label13, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen3_Label14 = lv_label_create(ui_SettingsPanel1);
lv_obj_set_width( ui_Screen3_Label14, lv_pct(50));
lv_obj_set_height( ui_Screen3_Label14, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label14, 15 );
lv_obj_set_y( ui_Screen3_Label14, 4 );
lv_label_set_text(ui_Screen3_Label14,"Точка доступа");
lv_obj_set_style_text_font(ui_Screen3_Label14, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Screen3_Label14, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Screen3_Label14, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Screen3_Label14, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Screen3_Label14, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel4 = lv_label_create(ui_WirelessConnectionScreen);
lv_obj_set_width( ui_TopPanel4, lv_pct(100));
lv_obj_set_height( ui_TopPanel4, lv_pct(22));
lv_obj_set_align( ui_TopPanel4, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TopPanel4,"");
lv_obj_set_style_text_color(ui_TopPanel4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TopPanel4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_TopPanel4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_decor(ui_TopPanel4, LV_TEXT_DECOR_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TopPanel4, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_TopPanel4, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_TopPanel4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_TopPanel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_TopPanel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_TopPanel4, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_TopPanel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TemperatureDisplay4 = lv_label_create(ui_TopPanel4);
lv_obj_set_width( ui_TemperatureDisplay4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TemperatureDisplay4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_TemperatureDisplay4, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_TemperatureDisplay4,"+125°");
lv_obj_set_style_text_align(ui_TemperatureDisplay4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TemperatureDisplay4, &ui_font_tempfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SettingsButton4 = lv_label_create(ui_TopPanel4);
lv_obj_set_width( ui_SettingsButton4, 70);
lv_obj_set_height( ui_SettingsButton4, 63);
lv_obj_set_x( ui_SettingsButton4, -19 );
lv_obj_set_y( ui_SettingsButton4, -12 );
lv_obj_set_align( ui_SettingsButton4, LV_ALIGN_TOP_RIGHT );
lv_label_set_text(ui_SettingsButton4,"A");
lv_obj_add_state( ui_SettingsButton4, LV_STATE_DISABLED );     /// States
lv_obj_set_style_text_align(ui_SettingsButton4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_SettingsButton4, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_SettingsButton4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsButton4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsButton4, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsButton4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_color(ui_SettingsButton4, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED );
lv_obj_set_style_text_opa(ui_SettingsButton4, 128, LV_PART_MAIN| LV_STATE_DISABLED);

ui_ManualControlButton4 = lv_label_create(ui_TopPanel4);
lv_obj_set_width( ui_ManualControlButton4, 70);
lv_obj_set_height( ui_ManualControlButton4, 63);
lv_obj_set_x( ui_ManualControlButton4, 19 );
lv_obj_set_y( ui_ManualControlButton4, -12 );
lv_label_set_text(ui_ManualControlButton4,"F");
lv_obj_add_flag( ui_ManualControlButton4, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_ManualControlButton4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ManualControlButton4, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_ManualControlButton4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_ManualControlButton4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_ManualControlButton4, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_ManualControlButton4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_keyboard_set_textarea(ui_WifiKeyboard,ui_WifiName);
lv_obj_add_event_cb(ui_WifiKeyboard, ui_event_WifiKeyboard, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiName, ui_event_WifiName, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiPassword, ui_event_WifiPassword, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ManualControlButton4, ui_event_ManualControlButton4, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WirelessConnectionScreen, ui_event_WirelessConnectionScreen, LV_EVENT_ALL, NULL);

}

void ui_init( void )
{

lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_MainScreen_screen_init();
ui_ManualControlScreen_screen_init();
ui_SettingsScreen_screen_init();
ui_SettingsScreen2_screen_init();
ui_WirelessConnectionScreen_screen_init();
lv_disp_load_scr( ui_MainScreen);
}
