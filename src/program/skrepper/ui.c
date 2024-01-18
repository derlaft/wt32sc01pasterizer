
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_ManualControlScreen
void ui_ManualControlScreen_screen_init(lv_obj_t *root);
lv_obj_t *ui_ManualControlScreen;


// SCREEN: ui_MainPanelScreen
void ui_MainPanelScreen_screen_init(lv_obj_t *root);
lv_obj_t *ui_MainPanelScreen;
lv_obj_t *ui_RootPanel;
lv_obj_t *ui_MainButtonPanel;
lv_obj_t *ui_StartStopButton;
lv_obj_t *ui_ReadButtonLabel2;
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

