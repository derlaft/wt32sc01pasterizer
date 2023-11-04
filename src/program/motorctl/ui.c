
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_ManualControlScreen
void ui_ManualControlScreen_screen_init(lv_obj_t *root);
lv_obj_t *ui_ManualControlScreen;
lv_obj_t *ui_RegisterPanel;
lv_obj_t *ui_RegisterSelector;
lv_obj_t *ui_Dec;
lv_obj_t *ui_DecLabel;
lv_obj_t *ui_Register;
lv_obj_t *ui_Inc;
lv_obj_t *ui_IncLabel;
lv_obj_t *ui_RegisterLabel;
lv_obj_t *ui_RegisterPanel1;
lv_obj_t *ui_ValueSelector;
lv_obj_t *ui_Dec1;
lv_obj_t *ui_DecLabel1;
lv_obj_t *ui_Value;
lv_obj_t *ui_Inc1;
lv_obj_t *ui_IncLabel1;
lv_obj_t *ui_RegisterLabel1;
lv_obj_t *ui_ReadWritePanel;
void ui_event_ReadButton1( lv_event_t * e);
lv_obj_t *ui_ReadButton1;
lv_obj_t *ui_ReadButtonLabel1;
void ui_event_WriteButton( lv_event_t * e);
lv_obj_t *ui_WriteButton;
lv_obj_t *ui_WriteButtonLabel;


// SCREEN: ui_MainPanelScreen
void ui_MainPanelScreen_screen_init(lv_obj_t *root);
lv_obj_t *ui_MainPanelScreen;
lv_obj_t *ui_MainButtonPanel;
void ui_event_ReadButton2( lv_event_t * e);
lv_obj_t *ui_ReadButton2;
lv_obj_t *ui_ReadButtonLabel2;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_ReadButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_main_button_pressed( e );
}
}
void ui_event_WriteButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_main_button_pressed( e );
}
}
void ui_event_ReadButton2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      on_main_button_pressed( e );
}
}

