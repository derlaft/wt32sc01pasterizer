
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
void ui_event_MainScreen(lv_event_t * e);
lv_obj_t * ui_MainScreen;
lv_obj_t * ui_TopPanel;
lv_obj_t * ui_TemperatureDisplay;
void ui_event_SettingsButton1(lv_event_t * e);
lv_obj_t * ui_SettingsButton1;
void ui_event_ManualControlButton(lv_event_t * e);
lv_obj_t * ui_ManualControlButton;
void ui_event_WarningIndicator(lv_event_t * e);
lv_obj_t * ui_WarningIndicator;
lv_obj_t * ui_ManualControlPanel;
void ui_event_CoolingButton(lv_event_t * e);
lv_obj_t * ui_CoolingButton;
lv_obj_t * ui_CoolingButtonLabel;
void ui_event_MixingButton(lv_event_t * e);
lv_obj_t * ui_MixingButton;
lv_obj_t * ui_MixingButtonLabel;
void ui_event_CleaningAcidButton(lv_event_t * e);
lv_obj_t * ui_CleaningAcidButton;
lv_obj_t * ui_CleaningAcidButtonLabel;
void ui_event_CleaningBaseButton(lv_event_t * e);
lv_obj_t * ui_CleaningBaseButton;
lv_obj_t * ui_CleaningBaseButtonLabel;

// SCREEN: ui_ManualControlScreen
void ui_ManualControlScreen_screen_init(void);
void ui_event_ManualControlScreen(lv_event_t * e);
lv_obj_t * ui_ManualControlScreen;
lv_obj_t * ui_TopPanel1;
lv_obj_t * ui_TemperatureDisplay1;
void ui_event_ManualControlButton1(lv_event_t * e);
lv_obj_t * ui_ManualControlButton1;
lv_obj_t * ui_MainScreenPanel;

// SCREEN: ui_SettingsScreen
void ui_SettingsScreen_screen_init(void);
void ui_event_SettingsScreen(lv_event_t * e);
lv_obj_t * ui_SettingsScreen;
lv_obj_t * ui_SettingsPanel;
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
lv_obj_t * ui_Setting3Panel;
lv_obj_t * ui_Setting3InfoLabel;
void ui_event_Setting3Decr(lv_event_t * e);
lv_obj_t * ui_Setting3Decr;
lv_obj_t * ui_Setting3DecrLabel;
lv_obj_t * ui_Setting3;
void ui_event_Setting3Incr(lv_event_t * e);
lv_obj_t * ui_Setting3Incr;
lv_obj_t * ui_Setting3IncrLabel;
lv_obj_t * ui_Setting4Panel;
lv_obj_t * ui_Setting4InfoLabel;
void ui_event_Setting4Decr(lv_event_t * e);
lv_obj_t * ui_Setting4Decr;
lv_obj_t * ui_Setting4DecrLabel;
lv_obj_t * ui_Setting4;
void ui_event_Setting4Incr(lv_event_t * e);
lv_obj_t * ui_Setting4Incr;
lv_obj_t * ui_Setting4IncrLabel;
void ui_event_ApplyButton(lv_event_t * e);
lv_obj_t * ui_ApplyButton;
lv_obj_t * ui_StartStopLabel1;
lv_obj_t * ui_TopPanel2;
lv_obj_t * ui_TemperatureDisplay2;
void ui_event_SettingsButton2(lv_event_t * e);
lv_obj_t * ui_SettingsButton2;
void ui_event_ManualControlButton2(lv_event_t * e);
lv_obj_t * ui_ManualControlButton2;

// SCREEN: ui_WirelessConnectionScreen
void ui_WirelessConnectionScreen_screen_init(void);
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
void ui_event_WarningIndicator(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_warn_button_clicked(e);
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
void ui_event_MixingButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_main_mixing(e);
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
void ui_event_Setting1Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_1_decr(e);
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
void ui_event_Setting2Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_2_decr(e);
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
void ui_event_Setting3Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_3_decr(e);
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
void ui_event_Setting4Decr(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_setting_4_decr(e);
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
        _ui_screen_change(ui_WirelessConnectionScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0);
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
void ui_event_WifiPassword(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        on_password_focused(e);
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
void ui_event_ManualControlButton4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_SettingsScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0);
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

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    ui_ManualControlScreen_screen_init();
    ui_SettingsScreen_screen_init();
    ui_WirelessConnectionScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui____initial_actions0, ui_event____initial_actions0, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui____initial_actions0);
    lv_disp_load_scr(ui_MainScreen);
}
