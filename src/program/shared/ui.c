
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_SettingsScreen
void ui_SettingsScreen_screen_init(lv_obj_t *root);
void ui_event_SettingsScreen( lv_event_t * e);
lv_obj_t *ui_SettingsScreen;


// SCREEN: ui_WirelessConnectionScreen
void ui_WirelessConnectionScreen_screen_init(lv_obj_t *root);
void ui_event_WirelessConnectionScreen( lv_event_t * e);
lv_obj_t *ui_WirelessConnectionScreen;
lv_obj_t *ui_WifiSettingsPanel;
void ui_event_WifiKeyboard( lv_event_t * e);
lv_obj_t *ui_WifiKeyboard;
lv_obj_t *ui_WiFiPasswordPanel;
lv_obj_t *ui_WifiPasswordLabel;
void ui_event_WifiPassword( lv_event_t * e);
lv_obj_t *ui_WifiPassword;
lv_obj_t *ui_WiFINamePanel;
lv_obj_t *ui_WifiNameLabel;
void ui_event_WifiName( lv_event_t * e);
lv_obj_t *ui_WifiName;
void ui_event____initial_actions0( lv_event_t * e);
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_SettingsScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      // on_settings_screen_loaded( e );
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
void ui_event_WifiPassword( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_FOCUSED) {
      on_password_focused( e );
}
}
void ui_event_WifiName( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_FOCUSED) {
      on_ap_focused( e );
}
}
void ui_event____initial_actions0( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOAD_START) {
      setup_button_map( e );
}
}

