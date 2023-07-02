
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_ManualControlScreen
void ui_ManualControlScreen_screen_init(lv_obj_t *root);
void ui_event_ManualControlScreen(lv_event_t * e);
lv_obj_t * ui_ManualControlScreen;
lv_obj_t * ui_MainScreenPanel;

// SCREEN: ui_SettingsScreen
void ui_SettingsScreen_screen_init(lv_obj_t *root);
void ui_event_SettingsScreen(lv_event_t * e);
lv_obj_t * ui_SettingsScreen;
lv_obj_t * ui_Setting1Panel;
lv_obj_t * ui_Setting1InfoLabel;
void ui_event_Setting1Decr(lv_event_t * e);
lv_obj_t * ui_Setting1Decr;
lv_obj_t * ui_Setting1DecrLabel;
lv_obj_t * ui_Setting1;
void ui_event_Setting1Incr(lv_event_t * e);
lv_obj_t * ui_Setting1Incr;
lv_obj_t * ui_Setting2IncrLabel;
lv_obj_t * ui_Setting2Panel;
lv_obj_t * ui_Setting2InfoLabel;
void ui_event_Setting2Decr(lv_event_t * e);
lv_obj_t * ui_Setting2Decr;
lv_obj_t * ui_Setting2DecrLabel;
lv_obj_t * ui_Setting2;
void ui_event_Setting2Incr(lv_event_t * e);
lv_obj_t * ui_Setting2Incr;
lv_obj_t * ui_Setting1IncrLabel;
void ui_event_ApplyButton(lv_event_t * e);
lv_obj_t * ui_ApplyButton;
lv_obj_t * ui_StartStopLabel1;

// SCREEN: ui_WirelessConnectionScreen
void ui_WirelessConnectionScreen_screen_init(lv_obj_t *root);
void ui_event_WirelessConnectionScreen(lv_event_t * e);
lv_obj_t * ui_WirelessConnectionScreen;
lv_obj_t * ui_SettingsPanel1;
void ui_event_WifiKeyboard(lv_event_t * e);
lv_obj_t * ui_WifiKeyboard;
lv_obj_t * ui_WiFiPasswordPanel;
lv_obj_t * ui_Screen3_Label13;
void ui_event_WifiPassword(lv_event_t * e);
lv_obj_t * ui_WifiPassword;
lv_obj_t * ui_WiFINamePanel;
lv_obj_t * ui_Screen3_Label14;
void ui_event_WifiName(lv_event_t * e);
lv_obj_t * ui_WifiName;
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
void ui_event_ManualControlScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
//        on_manual_control_screen_loaded(e);
    }
}
void ui_event_SettingsScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
//        on_settings_screen_loaded(e);
    }
}
void ui_event_Setting1Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
//        on_setting_1_decr(e);
    }
}
void ui_event_Setting1Incr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
//        on_setting1_incr(e);
    }
}
void ui_event_Setting2Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
//        on_setting_2_decr(e);
    }
}
void ui_event_Setting2Incr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
//        on_setting_2_incr(e);
    }
}
void ui_event_ApplyButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
//        on_save_settings(e);
    }
}
void ui_event_WirelessConnectionScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
//        on_wireless_screen_loaded(e);
    }
}
void ui_event_WifiKeyboard(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_READY) {
//        on_keyboard_press(e);
    }
}
void ui_event_WifiPassword(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
//        on_password_focused(e);
    }
}
void ui_event_WifiName(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
//        on_ap_focused(e);
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

