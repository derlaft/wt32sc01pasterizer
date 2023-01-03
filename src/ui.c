#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Screen1;
lv_obj_t *ui_MainScreenPanel;
lv_obj_t *ui_Screen1_Chart1;
void ui_event_StartStopButton( lv_event_t * e);
lv_obj_t *ui_StartStopButton;
lv_obj_t *ui_StartStopLabel;
lv_obj_t *ui_TopPanel;
lv_obj_t *ui_TemperatureDisplay;
void ui_event_SettingsButton1( lv_event_t * e);
lv_obj_t *ui_SettingsButton1;
void ui_event_ManualControlButton( lv_event_t * e);
lv_obj_t *ui_ManualControlButton;
lv_obj_t *ui_Screen2;
lv_obj_t *ui_ManualControlPanel;
void ui_event_HeatingButton( lv_event_t * e);
lv_obj_t *ui_HeatingButton;
lv_obj_t *ui_Screen1_Label11;
void ui_event_CoolingButton( lv_event_t * e);
lv_obj_t *ui_CoolingButton;
lv_obj_t *ui_Screen1_Label13;
void ui_event_MixingButton( lv_event_t * e);
lv_obj_t *ui_MixingButton;
lv_obj_t *ui_Screen1_Label14;
lv_obj_t *ui_Screen2_Label10;
lv_obj_t *ui_TopPanel1;
lv_obj_t *ui_TemperatureDisplay1;
void ui_event_BackButton1( lv_event_t * e);
lv_obj_t *ui_BackButton1;
lv_obj_t *ui_Screen3;
lv_obj_t *ui_SettingsPanel;
lv_obj_t *ui_Screen3_Label7;
lv_obj_t *ui_PastTemp;
void ui_event_PastTempDecr( lv_event_t * e);
lv_obj_t *ui_PastTempDecr;
lv_obj_t *ui_Screen3_Label8;
void ui_event_PastTempIncr( lv_event_t * e);
lv_obj_t *ui_PastTempIncr;
lv_obj_t *ui_Screen3_Label1;
lv_obj_t *ui_Screen3_Label9;
lv_obj_t *ui_Screen3_Label2;
lv_obj_t *ui_StorageTemp;
void ui_event_StorageTempDecr( lv_event_t * e);
lv_obj_t *ui_StorageTempDecr;
lv_obj_t *ui_Screen3_Label3;
void ui_event_StorageTempIncr( lv_event_t * e);
lv_obj_t *ui_StorageTempIncr;
lv_obj_t *ui_Screen3_Label4;
lv_obj_t *ui_Screen3_Label5;
lv_obj_t *ui_Screen3_Label6;
lv_obj_t *ui_PastTime;
void ui_event_PastTimeDec( lv_event_t * e);
lv_obj_t *ui_PastTimeDec;
lv_obj_t *ui_Screen3_Label10;
void ui_event_PastTimeIncr( lv_event_t * e);
lv_obj_t *ui_PastTimeIncr;
lv_obj_t *ui_Screen3_Label11;
lv_obj_t *ui_Screen3_Label12;
lv_obj_t *ui_TopPanel2;
lv_obj_t *ui_TemperatureDisplay2;
void ui_event_BackButton2( lv_event_t * e);
lv_obj_t *ui_BackButton2;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_StartStopButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_main_button_pressed( e );
}
}
void ui_event_SettingsButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      go_to_settings( e );
      _ui_screen_change( ui_Screen3, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
}
}
void ui_event_ManualControlButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      go_to_manual_control( e );
      _ui_screen_change( ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
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
void ui_event_BackButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      go_back_1( e );
      _ui_screen_change( ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
}
}
void ui_event_PastTempDecr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_temp_decr( e );
}
}
void ui_event_PastTempIncr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_temp_incr( e );
}
}
void ui_event_StorageTempDecr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_storage_temp_decr( e );
}
}
void ui_event_StorageTempIncr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_storage_temp_incr( e );
}
}
void ui_event_PastTimeDec( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_time_decr( e );
}
}
void ui_event_PastTimeIncr( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_past_time_incr( e );
}
}
void ui_event_BackButton2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      go_back_1( e );
      _ui_screen_change( ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
}
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_MainScreenPanel = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_MainScreenPanel, lv_pct(96));
lv_obj_set_height( ui_MainScreenPanel, lv_pct(74));
lv_obj_set_x( ui_MainScreenPanel, 0 );
lv_obj_set_y( ui_MainScreenPanel, -8 );
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
lv_label_set_text(ui_StartStopLabel,"Завершить хранение");
lv_obj_set_style_text_font(ui_StartStopLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel = lv_label_create(ui_Screen1);
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
lv_label_set_text(ui_ManualControlButton,"A");
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

}
void ui_Screen2_screen_init(void)
{
ui_Screen2 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_ManualControlPanel = lv_obj_create(ui_Screen2);
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

ui_Screen1_Label11 = lv_label_create(ui_HeatingButton);
lv_obj_set_width( ui_Screen1_Label11, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen1_Label11, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen1_Label11, 0 );
lv_obj_set_y( ui_Screen1_Label11, 3 );
lv_obj_set_align( ui_Screen1_Label11, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_Screen1_Label11,"Нагрев");
lv_obj_set_style_text_font(ui_Screen1_Label11, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CoolingButton = lv_btn_create(ui_ManualControlPanel);
lv_obj_set_width( ui_CoolingButton, lv_pct(100));
lv_obj_set_height( ui_CoolingButton, lv_pct(25));
lv_obj_set_x( ui_CoolingButton, 0 );
lv_obj_set_y( ui_CoolingButton, -120 );
lv_obj_set_align( ui_CoolingButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_CoolingButton, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_CoolingButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_CoolingButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen1_Label13 = lv_label_create(ui_CoolingButton);
lv_obj_set_width( ui_Screen1_Label13, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen1_Label13, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen1_Label13, 0 );
lv_obj_set_y( ui_Screen1_Label13, 3 );
lv_obj_set_align( ui_Screen1_Label13, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_Screen1_Label13,"Охлаждение");
lv_obj_set_style_text_font(ui_Screen1_Label13, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MixingButton = lv_btn_create(ui_ManualControlPanel);
lv_obj_set_width( ui_MixingButton, lv_pct(100));
lv_obj_set_height( ui_MixingButton, lv_pct(25));
lv_obj_set_align( ui_MixingButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_MixingButton, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_MixingButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_MixingButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen1_Label14 = lv_label_create(ui_MixingButton);
lv_obj_set_width( ui_Screen1_Label14, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen1_Label14, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen1_Label14, 0 );
lv_obj_set_y( ui_Screen1_Label14, 3 );
lv_obj_set_align( ui_Screen1_Label14, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_Screen1_Label14,"Перемешивание");
lv_obj_set_style_text_font(ui_Screen1_Label14, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen2_Label10 = lv_label_create(ui_Screen2);
lv_obj_set_width( ui_Screen2_Label10, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen2_Label10, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen2_Label10, -3 );
lv_obj_set_y( ui_Screen2_Label10, -57 );
lv_obj_set_align( ui_Screen2_Label10, LV_ALIGN_CENTER );
lv_label_set_text(ui_Screen2_Label10,"Ручное управление");
lv_obj_set_style_text_font(ui_Screen2_Label10, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel1 = lv_label_create(ui_Screen2);
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

ui_BackButton1 = lv_label_create(ui_TopPanel1);
lv_obj_set_width( ui_BackButton1, 70);
lv_obj_set_height( ui_BackButton1, 63);
lv_obj_set_x( ui_BackButton1, 19 );
lv_obj_set_y( ui_BackButton1, -12 );
lv_label_set_text(ui_BackButton1,"C");
lv_obj_add_flag( ui_BackButton1, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_BackButton1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_BackButton1, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_BackButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_BackButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_BackButton1, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_BackButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_HeatingButton, ui_event_HeatingButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_CoolingButton, ui_event_CoolingButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_MixingButton, ui_event_MixingButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_BackButton1, ui_event_BackButton1, LV_EVENT_ALL, NULL);

}
void ui_Screen3_screen_init(void)
{
ui_Screen3 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SettingsPanel = lv_obj_create(ui_Screen3);
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

ui_Screen3_Label7 = lv_label_create(ui_SettingsPanel);
lv_obj_set_width( ui_Screen3_Label7, lv_pct(100));
lv_obj_set_height( ui_Screen3_Label7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label7, 0 );
lv_obj_set_y( ui_Screen3_Label7, 20 );
lv_obj_set_align( ui_Screen3_Label7, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_Screen3_Label7,"");
lv_obj_set_style_text_align(ui_Screen3_Label7, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Screen3_Label7, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTemp = lv_textarea_create(ui_Screen3_Label7);
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

ui_PastTempDecr = lv_btn_create(ui_Screen3_Label7);
lv_obj_set_width( ui_PastTempDecr, 60);
lv_obj_set_height( ui_PastTempDecr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTempDecr, 185 );
lv_obj_set_y( ui_PastTempDecr, 0 );
lv_obj_set_align( ui_PastTempDecr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTempDecr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTempDecr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Screen3_Label8 = lv_label_create(ui_PastTempDecr);
lv_obj_set_width( ui_Screen3_Label8, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen3_Label8, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Screen3_Label8, LV_ALIGN_CENTER );
lv_label_set_text(ui_Screen3_Label8,"-");
lv_obj_set_style_text_font(ui_Screen3_Label8, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTempIncr = lv_btn_create(ui_Screen3_Label7);
lv_obj_set_width( ui_PastTempIncr, 60);
lv_obj_set_height( ui_PastTempIncr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTempIncr, 20 );
lv_obj_set_y( ui_PastTempIncr, 0 );
lv_obj_set_align( ui_PastTempIncr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTempIncr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTempIncr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Screen3_Label1 = lv_label_create(ui_PastTempIncr);
lv_obj_set_width( ui_Screen3_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen3_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Screen3_Label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Screen3_Label1,"+");
lv_obj_set_style_text_font(ui_Screen3_Label1, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen3_Label9 = lv_label_create(ui_Screen3_Label7);
lv_obj_set_width( ui_Screen3_Label9, lv_pct(50));
lv_obj_set_height( ui_Screen3_Label9, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label9, 15 );
lv_obj_set_y( ui_Screen3_Label9, 0 );
lv_label_set_text(ui_Screen3_Label9,"Температура\nпастеризации");
lv_obj_set_style_text_font(ui_Screen3_Label9, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Screen3_Label9, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Screen3_Label9, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Screen3_Label9, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Screen3_Label9, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen3_Label2 = lv_label_create(ui_SettingsPanel);
lv_obj_set_width( ui_Screen3_Label2, lv_pct(100));
lv_obj_set_height( ui_Screen3_Label2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label2, 0 );
lv_obj_set_y( ui_Screen3_Label2, 88 );
lv_obj_set_align( ui_Screen3_Label2, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_Screen3_Label2,"");
lv_obj_set_style_text_align(ui_Screen3_Label2, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Screen3_Label2, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StorageTemp = lv_textarea_create(ui_Screen3_Label2);
lv_obj_set_width( ui_StorageTemp, 75);
lv_obj_set_height( ui_StorageTemp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StorageTemp, 100 );
lv_obj_set_y( ui_StorageTemp, 0 );
lv_obj_set_align( ui_StorageTemp, LV_ALIGN_CENTER );
lv_textarea_set_text(ui_StorageTemp,"42");
lv_textarea_set_placeholder_text(ui_StorageTemp,"Placeholder...");
lv_obj_clear_flag( ui_StorageTemp, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_align(ui_StorageTemp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_StorageTemp, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StorageTempDecr = lv_btn_create(ui_Screen3_Label2);
lv_obj_set_width( ui_StorageTempDecr, 60);
lv_obj_set_height( ui_StorageTempDecr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StorageTempDecr, 185 );
lv_obj_set_y( ui_StorageTempDecr, 0 );
lv_obj_set_align( ui_StorageTempDecr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_StorageTempDecr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_StorageTempDecr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Screen3_Label3 = lv_label_create(ui_StorageTempDecr);
lv_obj_set_width( ui_Screen3_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen3_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Screen3_Label3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Screen3_Label3,"-");
lv_obj_set_style_text_font(ui_Screen3_Label3, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StorageTempIncr = lv_btn_create(ui_Screen3_Label2);
lv_obj_set_width( ui_StorageTempIncr, 60);
lv_obj_set_height( ui_StorageTempIncr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_StorageTempIncr, 20 );
lv_obj_set_y( ui_StorageTempIncr, 0 );
lv_obj_set_align( ui_StorageTempIncr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_StorageTempIncr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_StorageTempIncr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Screen3_Label4 = lv_label_create(ui_StorageTempIncr);
lv_obj_set_width( ui_Screen3_Label4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen3_Label4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Screen3_Label4, LV_ALIGN_CENTER );
lv_label_set_text(ui_Screen3_Label4,"+");
lv_obj_set_style_text_font(ui_Screen3_Label4, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen3_Label5 = lv_label_create(ui_Screen3_Label2);
lv_obj_set_width( ui_Screen3_Label5, lv_pct(50));
lv_obj_set_height( ui_Screen3_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label5, 17 );
lv_obj_set_y( ui_Screen3_Label5, 2 );
lv_label_set_text(ui_Screen3_Label5,"Температура\nхранения");
lv_obj_set_style_text_font(ui_Screen3_Label5, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Screen3_Label5, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Screen3_Label5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Screen3_Label5, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Screen3_Label5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen3_Label6 = lv_label_create(ui_SettingsPanel);
lv_obj_set_width( ui_Screen3_Label6, lv_pct(100));
lv_obj_set_height( ui_Screen3_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label6, 0 );
lv_obj_set_y( ui_Screen3_Label6, 157 );
lv_obj_set_align( ui_Screen3_Label6, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_Screen3_Label6,"");
lv_obj_set_style_text_align(ui_Screen3_Label6, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Screen3_Label6, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTime = lv_textarea_create(ui_Screen3_Label6);
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

ui_PastTimeDec = lv_btn_create(ui_Screen3_Label6);
lv_obj_set_width( ui_PastTimeDec, 60);
lv_obj_set_height( ui_PastTimeDec, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTimeDec, 185 );
lv_obj_set_y( ui_PastTimeDec, 0 );
lv_obj_set_align( ui_PastTimeDec, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTimeDec, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTimeDec, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Screen3_Label10 = lv_label_create(ui_PastTimeDec);
lv_obj_set_width( ui_Screen3_Label10, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen3_Label10, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Screen3_Label10, LV_ALIGN_CENTER );
lv_label_set_text(ui_Screen3_Label10,"-");
lv_obj_set_style_text_font(ui_Screen3_Label10, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PastTimeIncr = lv_btn_create(ui_Screen3_Label6);
lv_obj_set_width( ui_PastTimeIncr, 60);
lv_obj_set_height( ui_PastTimeIncr, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PastTimeIncr, 20 );
lv_obj_set_y( ui_PastTimeIncr, 0 );
lv_obj_set_align( ui_PastTimeIncr, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PastTimeIncr, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_PastTimeIncr, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Screen3_Label11 = lv_label_create(ui_PastTimeIncr);
lv_obj_set_width( ui_Screen3_Label11, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Screen3_Label11, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Screen3_Label11, LV_ALIGN_CENTER );
lv_label_set_text(ui_Screen3_Label11,"+");
lv_obj_set_style_text_font(ui_Screen3_Label11, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Screen3_Label12 = lv_label_create(ui_Screen3_Label6);
lv_obj_set_width( ui_Screen3_Label12, lv_pct(50));
lv_obj_set_height( ui_Screen3_Label12, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Screen3_Label12, 16 );
lv_obj_set_y( ui_Screen3_Label12, 0 );
lv_label_set_text(ui_Screen3_Label12,"Время пастеризации\nминуты");
lv_obj_set_style_text_font(ui_Screen3_Label12, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Screen3_Label12, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Screen3_Label12, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Screen3_Label12, 13, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Screen3_Label12, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TopPanel2 = lv_label_create(ui_Screen3);
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

ui_BackButton2 = lv_label_create(ui_TopPanel2);
lv_obj_set_width( ui_BackButton2, 70);
lv_obj_set_height( ui_BackButton2, 63);
lv_obj_set_x( ui_BackButton2, 19 );
lv_obj_set_y( ui_BackButton2, -12 );
lv_label_set_text(ui_BackButton2,"C");
lv_obj_add_flag( ui_BackButton2, LV_OBJ_FLAG_CLICKABLE );   /// Flags
lv_obj_set_style_text_align(ui_BackButton2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_BackButton2, &ui_font_symbols, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_BackButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_BackButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_BackButton2, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_BackButton2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_PastTempDecr, ui_event_PastTempDecr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_PastTempIncr, ui_event_PastTempIncr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_StorageTempDecr, ui_event_StorageTempDecr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_StorageTempIncr, ui_event_StorageTempIncr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_PastTimeDec, ui_event_PastTimeDec, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_PastTimeIncr, ui_event_PastTimeIncr, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_BackButton2, ui_event_BackButton2, LV_EVENT_ALL, NULL);

}

void ui_init( void )
{LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Screen1_screen_init();
ui_Screen2_screen_init();
ui_Screen3_screen_init();
lv_disp_load_scr( ui_Screen1);
}
