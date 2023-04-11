
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ui_event_MainScreen(lv_event_t * e);
lv_obj_t * ui_MainScreen;
lv_obj_t * ui_TopPanel;
lv_obj_t * ui_TemperatureDisplay;
void ui_event_SettingsButton1(lv_event_t * e);
lv_obj_t * ui_SettingsButton1;
void ui_event_ManualControlButton(lv_event_t * e);
lv_obj_t * ui_ManualControlButton;
lv_obj_t * ui_ManualControlPanel;
void ui_event_CoolingButton(lv_event_t * e);
lv_obj_t * ui_CoolingButton;
lv_obj_t * ui_CoolingButtonLabel;
void ui_event_CleaningAcidButton(lv_event_t * e);
lv_obj_t * ui_CleaningAcidButton;
lv_obj_t * ui_CleaningAcidButtonLabel;
void ui_event_CleaningBaseButton(lv_event_t * e);
lv_obj_t * ui_CleaningBaseButton;
lv_obj_t * ui_CleaningBaseButtonLabel;
void ui_event_RinsingButton(lv_event_t * e);
lv_obj_t * ui_RinsingButton;
lv_obj_t * ui_RinsingButtonLabel;
void ui_event_MixingButton(lv_event_t * e);
lv_obj_t * ui_MixingButton;
lv_obj_t * ui_MixingButtonLabel;
void ui_event_ManualControlScreen(lv_event_t * e);
lv_obj_t * ui_ManualControlScreen;
lv_obj_t * ui_TopPanel1;
lv_obj_t * ui_TemperatureDisplay1;
void ui_event_ManualControlButton1(lv_event_t * e);
lv_obj_t * ui_ManualControlButton1;
lv_obj_t * ui_MainScreenPanel;
void ui_event_SettingsScreen(lv_event_t * e);
lv_obj_t * ui_SettingsScreen;
lv_obj_t * ui_SettingsPanel;
lv_obj_t * ui_Setting1Panel;
lv_obj_t * ui_Setting1;
void ui_event_Setting1Incr(lv_event_t * e);
lv_obj_t * ui_Setting1Incr;
lv_obj_t * ui_Setting1IncrLabel;
void ui_event_Setting1Decr(lv_event_t * e);
lv_obj_t * ui_Setting1Decr;
lv_obj_t * ui_Setting1DecrLabel;
lv_obj_t * ui_Setting1InfoLabel;
lv_obj_t * ui_Setting2Panel;
lv_obj_t * ui_Setting2;
void ui_event_Setting2Incr(lv_event_t * e);
lv_obj_t * ui_Setting2Incr;
lv_obj_t * ui_Setting2IncrLabel;
void ui_event_Setting2Decr(lv_event_t * e);
lv_obj_t * ui_Setting2Decr;
lv_obj_t * ui_Setting2DecrLabel;
lv_obj_t * ui_Setting2InfoLabel;
void ui_event_ApplyButton(lv_event_t * e);
lv_obj_t * ui_ApplyButton;
lv_obj_t * ui_StartStopLabel1;
lv_obj_t * ui_TopPanel2;
lv_obj_t * ui_TemperatureDisplay2;
void ui_event_SettingsButton2(lv_event_t * e);
lv_obj_t * ui_SettingsButton2;
void ui_event_ManualControlButton2(lv_event_t * e);
lv_obj_t * ui_ManualControlButton2;
void ui_event_SettingsScreen2(lv_event_t * e);
lv_obj_t * ui_SettingsScreen2;
lv_obj_t * ui_SettingsPanel2;
lv_obj_t * ui_Setting3Panel;
lv_obj_t * ui_Setting3;
void ui_event_Setting3Incr(lv_event_t * e);
lv_obj_t * ui_Setting3Incr;
lv_obj_t * ui_Setting3IncrLabel;
void ui_event_Setting3Decr(lv_event_t * e);
lv_obj_t * ui_Setting3Decr;
lv_obj_t * ui_Setting3DecrLabel;
lv_obj_t * ui_Setting3InfoLabel;
void ui_event_ApplyButton1(lv_event_t * e);
lv_obj_t * ui_ApplyButton1;
lv_obj_t * ui_StartStopLabel2;
lv_obj_t * ui_Setting4Panel;
lv_obj_t * ui_Setting4;
void ui_event_Setting4Incr(lv_event_t * e);
lv_obj_t * ui_Setting4Incr;
lv_obj_t * ui_Setting4IncrLabel;
void ui_event_Setting4Decr(lv_event_t * e);
lv_obj_t * ui_Setting4Decr;
lv_obj_t * ui_Setting4DecrLabel;
lv_obj_t * ui_Setting4InfoLabel;
lv_obj_t * ui_TopPanel3;
lv_obj_t * ui_TemperatureDisplay3;
void ui_event_SettingsButton3(lv_event_t * e);
lv_obj_t * ui_SettingsButton3;
void ui_event_ManualControlButton3(lv_event_t * e);
lv_obj_t * ui_ManualControlButton3;
void ui_event_WirelessConnectionScreen(lv_event_t * e);
lv_obj_t * ui_WirelessConnectionScreen;
lv_obj_t * ui_SettingsPanel1;
void ui_event_WifiKeyboard(lv_event_t * e);
lv_obj_t * ui_WifiKeyboard;
void ui_event_WifiName(lv_event_t * e);
lv_obj_t * ui_WifiName;
void ui_event_WifiPassword(lv_event_t * e);
lv_obj_t * ui_WifiPassword;
lv_obj_t * ui_Screen3_Label13;
lv_obj_t * ui_Screen3_Label14;
lv_obj_t * ui_TopPanel4;
lv_obj_t * ui_TemperatureDisplay4;
lv_obj_t * ui_SettingsButton4;
void ui_event_ManualControlButton4(lv_event_t * e);
lv_obj_t * ui_ManualControlButton4;
void ui_event____initial_actions0(lv_event_t * e);
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_MainScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        on_main_screen_loaded(e);
    }
}
void ui_event_SettingsButton1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_SettingsScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
    }
}
void ui_event_ManualControlButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ManualControlScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
    }
}
void ui_event_CoolingButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_main_cooling(e);
    }
}
void ui_event_CleaningAcidButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_main_acid(e);
    }
}
void ui_event_CleaningBaseButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_main_base(e);
    }
}
void ui_event_RinsingButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_main_rinsing(e);
    }
}
void ui_event_MixingButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_main_mixing(e);
    }
}
void ui_event_ManualControlScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        on_manual_control_screen_loaded(e);
    }
}
void ui_event_ManualControlButton1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_MainScreen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
void ui_event_SettingsScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        on_settings_screen_loaded(e);
    }
}
void ui_event_Setting1Incr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting1_incr(e);
    }
}
void ui_event_Setting1Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_1_decr(e);
    }
}
void ui_event_Setting2Incr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_2_incr(e);
    }
}
void ui_event_Setting2Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_2_decr(e);
    }
}
void ui_event_ApplyButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_save_settings(e);
    }
}
void ui_event_SettingsButton2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_SettingsScreen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
    }
}
void ui_event_ManualControlButton2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_MainScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
    }
}
void ui_event_SettingsScreen2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        on_settings_screen_2_loaded(e);
    }
}
void ui_event_Setting3Incr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_3_incr(e);
    }
}
void ui_event_Setting3Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_3_decr(e);
    }
}
void ui_event_ApplyButton1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_save_settings(e);
    }
}
void ui_event_Setting4Incr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_4_incr(e);
    }
}
void ui_event_Setting4Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_4_decr(e);
    }
}
void ui_event_SettingsButton3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_WirelessConnectionScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
    }
}
void ui_event_ManualControlButton3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_SettingsScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
    }
}
void ui_event_WirelessConnectionScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        on_wireless_screen_loaded(e);
    }
}
void ui_event_WifiKeyboard(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_READY) {
        on_keyboard_press(e);
    }
}
void ui_event_WifiName(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        on_ap_focused(e);
    }
}
void ui_event_WifiPassword(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        on_password_focused(e);
    }
}
void ui_event_ManualControlButton4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_SettingsScreen2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
    }
}
void ui_event____initial_actions0(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        setup_button_map(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_MainScreen_screen_init(void)
{
    ui_MainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TopPanel = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_TopPanel, lv_pct(100));
    lv_obj_set_height(ui_TopPanel, lv_pct(22));
    lv_obj_set_align(ui_TopPanel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TopPanel, "");
    lv_obj_set_style_text_color(ui_TopPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureDisplay = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_TemperatureDisplay, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingsButton1 = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_SettingsButton1, 70);
    lv_obj_set_height(ui_SettingsButton1, 63);
    lv_obj_set_x(ui_SettingsButton1, -19);
    lv_obj_set_y(ui_SettingsButton1, -12);
    lv_obj_set_align(ui_SettingsButton1, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_SettingsButton1, "B");
    lv_obj_add_flag(ui_SettingsButton1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_SettingsButton1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsButton1, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingsButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsButton1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_ManualControlButton, 70);
    lv_obj_set_height(ui_ManualControlButton, 63);
    lv_obj_set_x(ui_ManualControlButton, 19);
    lv_obj_set_y(ui_ManualControlButton, -12);
    lv_label_set_text(ui_ManualControlButton, "C");
    lv_obj_add_flag(ui_ManualControlButton, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlPanel = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_ManualControlPanel, lv_pct(96));
    lv_obj_set_height(ui_ManualControlPanel, lv_pct(74));
    lv_obj_set_x(ui_ManualControlPanel, 0);
    lv_obj_set_y(ui_ManualControlPanel, -9);
    lv_obj_set_align(ui_ManualControlPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_ManualControlPanel, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_ManualControlPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_clear_flag(ui_ManualControlPanel,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_pad_left(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CoolingButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_CoolingButton, lv_pct(99));
    lv_obj_set_height(ui_CoolingButton, lv_pct(24));
    lv_obj_set_x(ui_CoolingButton, 0);
    lv_obj_set_y(ui_CoolingButton, -180);
    lv_obj_set_align(ui_CoolingButton, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_CoolingButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CoolingButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_CoolingButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CoolingButtonLabel = lv_label_create(ui_CoolingButton);
    lv_obj_set_width(ui_CoolingButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CoolingButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_CoolingButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CoolingButtonLabel, "Охлаждение");
    lv_obj_set_style_text_font(ui_CoolingButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningAcidButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_CleaningAcidButton, lv_pct(99));
    lv_obj_set_height(ui_CleaningAcidButton, lv_pct(24));
    lv_obj_set_align(ui_CleaningAcidButton, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_CleaningAcidButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CleaningAcidButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_CleaningAcidButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningAcidButtonLabel = lv_label_create(ui_CleaningAcidButton);
    lv_obj_set_height(ui_CleaningAcidButtonLabel, lv_pct(100));
    lv_obj_set_width(ui_CleaningAcidButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_CleaningAcidButtonLabel, 0);
    lv_obj_set_y(ui_CleaningAcidButtonLabel, 1);
    lv_obj_set_align(ui_CleaningAcidButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_CleaningAcidButtonLabel, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_CleaningAcidButtonLabel, "Промывка кислотой");
    lv_obj_set_style_text_font(ui_CleaningAcidButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningBaseButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_CleaningBaseButton, lv_pct(99));
    lv_obj_set_height(ui_CleaningBaseButton, lv_pct(24));
    lv_obj_set_x(ui_CleaningBaseButton, 1);
    lv_obj_set_y(ui_CleaningBaseButton, -40);
    lv_obj_set_align(ui_CleaningBaseButton, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_CleaningBaseButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CleaningBaseButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_CleaningBaseButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningBaseButtonLabel = lv_label_create(ui_CleaningBaseButton);
    lv_obj_set_height(ui_CleaningBaseButtonLabel, lv_pct(100));
    lv_obj_set_width(ui_CleaningBaseButtonLabel, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_x(ui_CleaningBaseButtonLabel, 0);
    lv_obj_set_y(ui_CleaningBaseButtonLabel, 1);
    lv_obj_set_align(ui_CleaningBaseButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_CleaningBaseButtonLabel, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_CleaningBaseButtonLabel, "Промывка щелочью");
    lv_obj_set_style_text_font(ui_CleaningBaseButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RinsingButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_RinsingButton, lv_pct(42));
    lv_obj_set_height(ui_RinsingButton, lv_pct(24));
    lv_obj_set_x(ui_RinsingButton, 0);
    lv_obj_set_y(ui_RinsingButton, -60);
    lv_obj_set_align(ui_RinsingButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_RinsingButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_RinsingButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_RinsingButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RinsingButtonLabel = lv_label_create(ui_RinsingButton);
    lv_obj_set_width(ui_RinsingButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RinsingButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RinsingButtonLabel, 0);
    lv_obj_set_y(ui_RinsingButtonLabel, 1);
    lv_obj_set_align(ui_RinsingButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_RinsingButtonLabel, "Полоскание");
    lv_obj_set_style_text_font(ui_RinsingButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MixingButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_MixingButton, lv_pct(55));
    lv_obj_set_height(ui_MixingButton, lv_pct(24));
    lv_obj_set_x(ui_MixingButton, 0);
    lv_obj_set_y(ui_MixingButton, -120);
    lv_obj_set_align(ui_MixingButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MixingButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MixingButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_MixingButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MixingButtonLabel = lv_label_create(ui_MixingButton);
    lv_obj_set_width(ui_MixingButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MixingButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MixingButtonLabel, 0);
    lv_obj_set_y(ui_MixingButtonLabel, 1);
    lv_obj_set_align(ui_MixingButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MixingButtonLabel, "Перемешивание");
    lv_obj_set_style_text_font(ui_MixingButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_SettingsButton1, ui_event_SettingsButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlButton, ui_event_ManualControlButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CoolingButton, ui_event_CoolingButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CleaningAcidButton, ui_event_CleaningAcidButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CleaningBaseButton, ui_event_CleaningBaseButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_RinsingButton, ui_event_RinsingButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MixingButton, ui_event_MixingButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MainScreen, ui_event_MainScreen, LV_EVENT_ALL, NULL);

}
void ui_ManualControlScreen_screen_init(void)
{
    ui_ManualControlScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ManualControlScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TopPanel1 = lv_label_create(ui_ManualControlScreen);
    lv_obj_set_width(ui_TopPanel1, lv_pct(100));
    lv_obj_set_height(ui_TopPanel1, lv_pct(22));
    lv_obj_set_align(ui_TopPanel1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TopPanel1, "");
    lv_obj_set_style_text_color(ui_TopPanel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel1, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel1, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel1, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureDisplay1 = lv_label_create(ui_TopPanel1);
    lv_obj_set_width(ui_TemperatureDisplay1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay1, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay1, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton1 = lv_label_create(ui_TopPanel1);
    lv_obj_set_width(ui_ManualControlButton1, 70);
    lv_obj_set_height(ui_ManualControlButton1, 63);
    lv_obj_set_x(ui_ManualControlButton1, 19);
    lv_obj_set_y(ui_ManualControlButton1, -12);
    lv_label_set_text(ui_ManualControlButton1, "F");
    lv_obj_add_flag(ui_ManualControlButton1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton1, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MainScreenPanel = lv_obj_create(ui_ManualControlScreen);
    lv_obj_set_width(ui_MainScreenPanel, lv_pct(96));
    lv_obj_set_height(ui_MainScreenPanel, lv_pct(74));
    lv_obj_set_x(ui_MainScreenPanel, 0);
    lv_obj_set_y(ui_MainScreenPanel, -7);
    lv_obj_set_align(ui_MainScreenPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_MainScreenPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ManualControlButton1, ui_event_ManualControlButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlScreen, ui_event_ManualControlScreen, LV_EVENT_ALL, NULL);

}
void ui_SettingsScreen_screen_init(void)
{
    ui_SettingsScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SettingsScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SettingsPanel = lv_obj_create(ui_SettingsScreen);
    lv_obj_set_width(ui_SettingsPanel, lv_pct(96));
    lv_obj_set_height(ui_SettingsPanel, lv_pct(74));
    lv_obj_set_x(ui_SettingsPanel, -1);
    lv_obj_set_y(ui_SettingsPanel, -10);
    lv_obj_set_align(ui_SettingsPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_SettingsPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_SettingsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1Panel = lv_label_create(ui_SettingsPanel);
    lv_obj_set_width(ui_Setting1Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting1Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1Panel, 0);
    lv_obj_set_y(ui_Setting1Panel, 20);
    lv_obj_set_align(ui_Setting1Panel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Setting1Panel, "");
    lv_obj_set_style_text_align(ui_Setting1Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting1Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1 = lv_textarea_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1, 75);
    lv_obj_set_height(ui_Setting1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1, 100);
    lv_obj_set_y(ui_Setting1, 0);
    lv_obj_set_align(ui_Setting1, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting1, 128);
    lv_textarea_set_text(ui_Setting1, "4");
    lv_textarea_set_placeholder_text(ui_Setting1, "Placeholder...");
    lv_obj_clear_flag(ui_Setting1, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting1, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1Incr = lv_btn_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1Incr, 60);
    lv_obj_set_height(ui_Setting1Incr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1Incr, 185);
    lv_obj_set_y(ui_Setting1Incr, 0);
    lv_obj_set_align(ui_Setting1Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting1Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting1Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting1IncrLabel = lv_label_create(ui_Setting1Incr);
    lv_obj_set_width(ui_Setting1IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting1IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting1IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting1IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting1IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1Decr = lv_btn_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1Decr, 60);
    lv_obj_set_height(ui_Setting1Decr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1Decr, 20);
    lv_obj_set_y(ui_Setting1Decr, 0);
    lv_obj_set_align(ui_Setting1Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting1Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting1Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting1DecrLabel = lv_label_create(ui_Setting1Decr);
    lv_obj_set_width(ui_Setting1DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting1DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting1DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting1DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting1DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1InfoLabel = lv_label_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1InfoLabel, lv_pct(45));
    lv_obj_set_height(ui_Setting1InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1InfoLabel, 15);
    lv_obj_set_y(ui_Setting1InfoLabel, 0);
    lv_label_set_text(ui_Setting1InfoLabel, "Температура\nохлаждения");
    lv_obj_set_style_text_font(ui_Setting1InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting1InfoLabel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting1InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting1InfoLabel, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting1InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2Panel = lv_label_create(ui_SettingsPanel);
    lv_obj_set_width(ui_Setting2Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting2Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting2Panel, 0);
    lv_obj_set_y(ui_Setting2Panel, 95);
    lv_obj_set_align(ui_Setting2Panel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Setting2Panel, "");
    lv_obj_set_style_text_align(ui_Setting2Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting2Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2 = lv_textarea_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2, 80);
    lv_obj_set_height(ui_Setting2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting2, 102);
    lv_obj_set_y(ui_Setting2, 0);
    lv_obj_set_align(ui_Setting2, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting2, 128);
    lv_textarea_set_text(ui_Setting2, "15");
    lv_textarea_set_placeholder_text(ui_Setting2, "Placeholder...");
    lv_obj_clear_flag(ui_Setting2, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting2, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2Incr = lv_btn_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2Incr, 60);
    lv_obj_set_height(ui_Setting2Incr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting2Incr, 185);
    lv_obj_set_y(ui_Setting2Incr, 0);
    lv_obj_set_align(ui_Setting2Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting2Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting2Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting2IncrLabel = lv_label_create(ui_Setting2Incr);
    lv_obj_set_width(ui_Setting2IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting2IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting2IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting2IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting2IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2Decr = lv_btn_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2Decr, 60);
    lv_obj_set_height(ui_Setting2Decr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting2Decr, 20);
    lv_obj_set_y(ui_Setting2Decr, 0);
    lv_obj_set_align(ui_Setting2Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting2Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting2Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting2DecrLabel = lv_label_create(ui_Setting2Decr);
    lv_obj_set_width(ui_Setting2DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting2DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting2DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting2DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting2DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2InfoLabel = lv_label_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2InfoLabel, lv_pct(45));
    lv_obj_set_height(ui_Setting2InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting2InfoLabel, 16);
    lv_obj_set_y(ui_Setting2InfoLabel, -16);
    lv_label_set_text(ui_Setting2InfoLabel,
                      "Время (мин) до перемешивания в режиме  хранения");
    lv_obj_set_style_text_font(ui_Setting2InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting2InfoLabel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting2InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting2InfoLabel, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting2InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ApplyButton = lv_btn_create(ui_SettingsPanel);
    lv_obj_set_width(ui_ApplyButton, lv_pct(100));
    lv_obj_set_height(ui_ApplyButton, lv_pct(25));
    lv_obj_set_x(ui_ApplyButton, 0);
    lv_obj_set_y(ui_ApplyButton, -1);
    lv_obj_set_align(ui_ApplyButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_ApplyButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ApplyButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_ApplyButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StartStopLabel1 = lv_label_create(ui_ApplyButton);
    lv_obj_set_width(ui_StartStopLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StartStopLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_StartStopLabel1, 0);
    lv_obj_set_y(ui_StartStopLabel1, 3);
    lv_obj_set_align(ui_StartStopLabel1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_StartStopLabel1, "Сохранить");
    lv_obj_set_style_text_font(ui_StartStopLabel1, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TopPanel2 = lv_label_create(ui_SettingsScreen);
    lv_obj_set_width(ui_TopPanel2, lv_pct(100));
    lv_obj_set_height(ui_TopPanel2, lv_pct(22));
    lv_obj_set_align(ui_TopPanel2, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TopPanel2, "");
    lv_obj_set_style_text_color(ui_TopPanel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel2, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel2, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel2, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureDisplay2 = lv_label_create(ui_TopPanel2);
    lv_obj_set_width(ui_TemperatureDisplay2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay2, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay2, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay2, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingsButton2 = lv_label_create(ui_TopPanel2);
    lv_obj_set_width(ui_SettingsButton2, 70);
    lv_obj_set_height(ui_SettingsButton2, 63);
    lv_obj_set_x(ui_SettingsButton2, -19);
    lv_obj_set_y(ui_SettingsButton2, -12);
    lv_obj_set_align(ui_SettingsButton2, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_SettingsButton2, "E");
    lv_obj_add_flag(ui_SettingsButton2, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_SettingsButton2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsButton2, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingsButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsButton2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton2 = lv_label_create(ui_TopPanel2);
    lv_obj_set_width(ui_ManualControlButton2, 70);
    lv_obj_set_height(ui_ManualControlButton2, 63);
    lv_obj_set_x(ui_ManualControlButton2, 19);
    lv_obj_set_y(ui_ManualControlButton2, -12);
    lv_label_set_text(ui_ManualControlButton2, "F");
    lv_obj_add_flag(ui_ManualControlButton2, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton2, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Setting1Incr, ui_event_Setting1Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting1Decr, ui_event_Setting1Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting2Incr, ui_event_Setting2Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting2Decr, ui_event_Setting2Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ApplyButton, ui_event_ApplyButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsButton2, ui_event_SettingsButton2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlButton2, ui_event_ManualControlButton2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsScreen, ui_event_SettingsScreen, LV_EVENT_ALL, NULL);

}
void ui_SettingsScreen2_screen_init(void)
{
    ui_SettingsScreen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SettingsScreen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SettingsPanel2 = lv_obj_create(ui_SettingsScreen2);
    lv_obj_set_width(ui_SettingsPanel2, lv_pct(96));
    lv_obj_set_height(ui_SettingsPanel2, lv_pct(74));
    lv_obj_set_x(ui_SettingsPanel2, -1);
    lv_obj_set_y(ui_SettingsPanel2, -11);
    lv_obj_set_align(ui_SettingsPanel2, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_SettingsPanel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_SettingsPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3Panel = lv_label_create(ui_SettingsPanel2);
    lv_obj_set_width(ui_Setting3Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting3Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3Panel, 0);
    lv_obj_set_y(ui_Setting3Panel, 20);
    lv_obj_set_align(ui_Setting3Panel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Setting3Panel, "");
    lv_obj_set_style_text_align(ui_Setting3Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting3Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3 = lv_textarea_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3, 75);
    lv_obj_set_height(ui_Setting3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3, 100);
    lv_obj_set_y(ui_Setting3, 0);
    lv_obj_set_align(ui_Setting3, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting3, 128);
    lv_textarea_set_text(ui_Setting3, "2");
    lv_textarea_set_placeholder_text(ui_Setting3, "Placeholder...");
    lv_obj_clear_flag(ui_Setting3, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting3, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3Incr = lv_btn_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3Incr, 60);
    lv_obj_set_height(ui_Setting3Incr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3Incr, 185);
    lv_obj_set_y(ui_Setting3Incr, 0);
    lv_obj_set_align(ui_Setting3Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting3Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting3Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting3IncrLabel = lv_label_create(ui_Setting3Incr);
    lv_obj_set_width(ui_Setting3IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting3IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting3IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting3IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting3IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3Decr = lv_btn_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3Decr, 60);
    lv_obj_set_height(ui_Setting3Decr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3Decr, 20);
    lv_obj_set_y(ui_Setting3Decr, 0);
    lv_obj_set_align(ui_Setting3Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting3Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting3Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting3DecrLabel = lv_label_create(ui_Setting3Decr);
    lv_obj_set_width(ui_Setting3DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting3DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting3DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting3DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting3DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3InfoLabel = lv_label_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3InfoLabel, lv_pct(45));
    lv_obj_set_height(ui_Setting3InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3InfoLabel, 15);
    lv_obj_set_y(ui_Setting3InfoLabel, -16);
    lv_label_set_text(ui_Setting3InfoLabel,
                      "Время (мин) перемешивания в режиме хранения");
    lv_obj_set_style_text_font(ui_Setting3InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting3InfoLabel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting3InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting3InfoLabel, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting3InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ApplyButton1 = lv_btn_create(ui_SettingsPanel2);
    lv_obj_set_width(ui_ApplyButton1, lv_pct(100));
    lv_obj_set_height(ui_ApplyButton1, lv_pct(25));
    lv_obj_set_x(ui_ApplyButton1, 0);
    lv_obj_set_y(ui_ApplyButton1, -1);
    lv_obj_set_align(ui_ApplyButton1, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_ApplyButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ApplyButton1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_ApplyButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StartStopLabel2 = lv_label_create(ui_ApplyButton1);
    lv_obj_set_width(ui_StartStopLabel2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StartStopLabel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_StartStopLabel2, 0);
    lv_obj_set_y(ui_StartStopLabel2, 3);
    lv_obj_set_align(ui_StartStopLabel2, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_StartStopLabel2, "Сохранить");
    lv_obj_set_style_text_font(ui_StartStopLabel2, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4Panel = lv_label_create(ui_SettingsPanel2);
    lv_obj_set_width(ui_Setting4Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting4Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4Panel, 0);
    lv_obj_set_y(ui_Setting4Panel, 95);
    lv_obj_set_align(ui_Setting4Panel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Setting4Panel, "");
    lv_obj_set_style_text_align(ui_Setting4Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting4Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4 = lv_textarea_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4, 80);
    lv_obj_set_height(ui_Setting4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4, 102);
    lv_obj_set_y(ui_Setting4, 0);
    lv_obj_set_align(ui_Setting4, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting4, 128);
    lv_textarea_set_text(ui_Setting4, "1");
    lv_textarea_set_placeholder_text(ui_Setting4, "Placeholder...");
    lv_obj_clear_flag(ui_Setting4, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting4, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4Incr = lv_btn_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4Incr, 60);
    lv_obj_set_height(ui_Setting4Incr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4Incr, 185);
    lv_obj_set_y(ui_Setting4Incr, 0);
    lv_obj_set_align(ui_Setting4Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting4Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting4Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting4IncrLabel = lv_label_create(ui_Setting4Incr);
    lv_obj_set_width(ui_Setting4IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting4IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting4IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting4IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting4IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4Decr = lv_btn_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4Decr, 60);
    lv_obj_set_height(ui_Setting4Decr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4Decr, 20);
    lv_obj_set_y(ui_Setting4Decr, 0);
    lv_obj_set_align(ui_Setting4Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting4Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting4Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting4DecrLabel = lv_label_create(ui_Setting4Decr);
    lv_obj_set_width(ui_Setting4DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting4DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting4DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting4DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting4DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4InfoLabel = lv_label_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4InfoLabel, lv_pct(45));
    lv_obj_set_height(ui_Setting4InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4InfoLabel, 16);
    lv_obj_set_y(ui_Setting4InfoLabel, -6);
    lv_label_set_text(ui_Setting4InfoLabel, "Задержка (мин) выключения перемешивания");
    lv_obj_set_style_text_font(ui_Setting4InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting4InfoLabel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting4InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting4InfoLabel, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting4InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TopPanel3 = lv_label_create(ui_SettingsScreen2);
    lv_obj_set_width(ui_TopPanel3, lv_pct(100));
    lv_obj_set_height(ui_TopPanel3, lv_pct(22));
    lv_obj_set_align(ui_TopPanel3, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TopPanel3, "");
    lv_obj_set_style_text_color(ui_TopPanel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel3, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel3, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel3, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel3, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureDisplay3 = lv_label_create(ui_TopPanel3);
    lv_obj_set_width(ui_TemperatureDisplay3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay3, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay3, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay3, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingsButton3 = lv_label_create(ui_TopPanel3);
    lv_obj_set_width(ui_SettingsButton3, 70);
    lv_obj_set_height(ui_SettingsButton3, 63);
    lv_obj_set_x(ui_SettingsButton3, -19);
    lv_obj_set_y(ui_SettingsButton3, -12);
    lv_obj_set_align(ui_SettingsButton3, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_SettingsButton3, "E");
    lv_obj_add_flag(ui_SettingsButton3, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_SettingsButton3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsButton3, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingsButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsButton3, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton3 = lv_label_create(ui_TopPanel3);
    lv_obj_set_width(ui_ManualControlButton3, 70);
    lv_obj_set_height(ui_ManualControlButton3, 63);
    lv_obj_set_x(ui_ManualControlButton3, 19);
    lv_obj_set_y(ui_ManualControlButton3, -12);
    lv_label_set_text(ui_ManualControlButton3, "F");
    lv_obj_add_flag(ui_ManualControlButton3, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton3, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton3, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Setting3Incr, ui_event_Setting3Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting3Decr, ui_event_Setting3Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ApplyButton1, ui_event_ApplyButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting4Incr, ui_event_Setting4Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting4Decr, ui_event_Setting4Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsButton3, ui_event_SettingsButton3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlButton3, ui_event_ManualControlButton3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsScreen2, ui_event_SettingsScreen2, LV_EVENT_ALL, NULL);

}
void ui_WirelessConnectionScreen_screen_init(void)
{
    ui_WirelessConnectionScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_WirelessConnectionScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SettingsPanel1 = lv_obj_create(ui_WirelessConnectionScreen);
    lv_obj_set_width(ui_SettingsPanel1, lv_pct(96));
    lv_obj_set_height(ui_SettingsPanel1, lv_pct(74));
    lv_obj_set_x(ui_SettingsPanel1, -1);
    lv_obj_set_y(ui_SettingsPanel1, -10);
    lv_obj_set_align(ui_SettingsPanel1, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_SettingsPanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiKeyboard = lv_keyboard_create(ui_SettingsPanel1);
    lv_obj_set_height(ui_WifiKeyboard, 120);
    lv_obj_set_width(ui_WifiKeyboard, lv_pct(100));
    lv_obj_set_align(ui_WifiKeyboard, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_scrollbar_mode(ui_WifiKeyboard, LV_SCROLLBAR_MODE_OFF);

    ui_WifiName = lv_textarea_create(ui_SettingsPanel1);
    lv_obj_set_width(ui_WifiName, lv_pct(50));
    lv_obj_set_height(ui_WifiName, LV_SIZE_CONTENT);    /// 37
    lv_obj_set_x(ui_WifiName, -10);
    lv_obj_set_y(ui_WifiName, 10);
    lv_obj_set_align(ui_WifiName, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_max_length(ui_WifiName, 128);
    lv_textarea_set_one_line(ui_WifiName, true);
    lv_obj_clear_flag(ui_WifiName, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_scrollbar_mode(ui_WifiName, LV_SCROLLBAR_MODE_OFF);

    ui_WifiPassword = lv_textarea_create(ui_SettingsPanel1);
    lv_obj_set_width(ui_WifiPassword, lv_pct(50));
    lv_obj_set_height(ui_WifiPassword, LV_SIZE_CONTENT);    /// 37
    lv_obj_set_x(ui_WifiPassword, -10);
    lv_obj_set_y(ui_WifiPassword, 60);
    lv_obj_set_align(ui_WifiPassword, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_max_length(ui_WifiPassword, 128);
    lv_textarea_set_one_line(ui_WifiPassword, true);
    lv_textarea_set_password_mode(ui_WifiPassword, true);
    lv_obj_clear_flag(ui_WifiPassword, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_scrollbar_mode(ui_WifiPassword, LV_SCROLLBAR_MODE_OFF);

    ui_Screen3_Label13 = lv_label_create(ui_SettingsPanel1);
    lv_obj_set_width(ui_Screen3_Label13, lv_pct(50));
    lv_obj_set_height(ui_Screen3_Label13, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen3_Label13, 15);
    lv_obj_set_y(ui_Screen3_Label13, 56);
    lv_label_set_text(ui_Screen3_Label13, "Пароль");
    lv_obj_set_style_text_font(ui_Screen3_Label13, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen3_Label13, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen3_Label13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen3_Label13, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen3_Label13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen3_Label14 = lv_label_create(ui_SettingsPanel1);
    lv_obj_set_width(ui_Screen3_Label14, lv_pct(50));
    lv_obj_set_height(ui_Screen3_Label14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen3_Label14, 15);
    lv_obj_set_y(ui_Screen3_Label14, 4);
    lv_label_set_text(ui_Screen3_Label14, "Точка доступа");
    lv_obj_set_style_text_font(ui_Screen3_Label14, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen3_Label14, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen3_Label14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen3_Label14, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen3_Label14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TopPanel4 = lv_label_create(ui_WirelessConnectionScreen);
    lv_obj_set_width(ui_TopPanel4, lv_pct(100));
    lv_obj_set_height(ui_TopPanel4, lv_pct(22));
    lv_obj_set_align(ui_TopPanel4, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TopPanel4, "");
    lv_obj_set_style_text_color(ui_TopPanel4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel4, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel4, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel4, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel4, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureDisplay4 = lv_label_create(ui_TopPanel4);
    lv_obj_set_width(ui_TemperatureDisplay4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay4, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay4, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay4, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingsButton4 = lv_label_create(ui_TopPanel4);
    lv_obj_set_width(ui_SettingsButton4, 70);
    lv_obj_set_height(ui_SettingsButton4, 63);
    lv_obj_set_x(ui_SettingsButton4, -19);
    lv_obj_set_y(ui_SettingsButton4, -12);
    lv_obj_set_align(ui_SettingsButton4, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_SettingsButton4, "A");
    lv_obj_add_state(ui_SettingsButton4, LV_STATE_DISABLED);       /// States
    lv_obj_set_style_text_align(ui_SettingsButton4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsButton4, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingsButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsButton4, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SettingsButton4, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_opa(ui_SettingsButton4, 128, LV_PART_MAIN | LV_STATE_DISABLED);

    ui_ManualControlButton4 = lv_label_create(ui_TopPanel4);
    lv_obj_set_width(ui_ManualControlButton4, 70);
    lv_obj_set_height(ui_ManualControlButton4, 63);
    lv_obj_set_x(ui_ManualControlButton4, 19);
    lv_obj_set_y(ui_ManualControlButton4, -12);
    lv_label_set_text(ui_ManualControlButton4, "F");
    lv_obj_add_flag(ui_ManualControlButton4, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton4, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton4, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_keyboard_set_textarea(ui_WifiKeyboard, ui_WifiName);
    lv_obj_add_event_cb(ui_WifiKeyboard, ui_event_WifiKeyboard, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiName, ui_event_WifiName, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiPassword, ui_event_WifiPassword, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlButton4, ui_event_ManualControlButton4, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WirelessConnectionScreen, ui_event_WirelessConnectionScreen, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    ui_ManualControlScreen_screen_init();
    ui_SettingsScreen_screen_init();
    ui_SettingsScreen2_screen_init();
    ui_WirelessConnectionScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui____initial_actions0, ui_event____initial_actions0, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui____initial_actions0);
    lv_disp_load_scr(ui_MainScreen);
}
