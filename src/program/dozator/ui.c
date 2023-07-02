
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_MainControlScreen
void ui_MainControlScreen_screen_init(lv_obj_t *root);
lv_obj_t * ui_MainControlScreen;
void ui_event_StartStopButton(lv_event_t * e);
lv_obj_t * ui_StartStopButton;
lv_obj_t * ui_StartStopLabel;
lv_obj_t * ui_Spinner;
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
void ui_event_StartStopButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        on_main_button_pressed(e);
    }
}

