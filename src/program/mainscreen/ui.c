
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
lv_obj_t *ui_MainScreen;
lv_obj_t *ui_TopPanelWithProgressBar;
lv_obj_t *ui_TopPanel;
void ui_event_BackButton( lv_event_t * e);
lv_obj_t *ui_BackButton;
void ui_event_ManualControlButton( lv_event_t * e);
lv_obj_t *ui_ManualControlButton;
lv_obj_t *ui_TempAndWarningGroup;
lv_obj_t *ui_TemperatureDisplay;
void ui_event_WarningIndicator( lv_event_t * e);
lv_obj_t *ui_WarningIndicator;
void ui_event_SettingsButton( lv_event_t * e);
lv_obj_t *ui_SettingsButton;
void ui_event_ForwardButton( lv_event_t * e);
lv_obj_t *ui_ForwardButton;
lv_obj_t *ui_ProgressBar;
lv_obj_t *ui_MainPanel;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_BackButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_back_button( e );
}
}
void ui_event_ManualControlButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_manual_control_button( e );
}
}
void ui_event_WarningIndicator( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_warn_button_clicked( e );
}
}
void ui_event_SettingsButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_settings_button( e );
}
}
void ui_event_ForwardButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_forward_button( e );
}
}

