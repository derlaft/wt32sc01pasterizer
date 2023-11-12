
#ifndef _MOTORCTL_UI_H
#define _MOTORCTL_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
  #if __has_include("lvgl.h")
    #include "lvgl.h"
  #elif __has_include("lvgl/lvgl.h")
    #include "lvgl/lvgl.h"
  #else
    #include "lvgl.h"
  #endif
#else
  #include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_ManualControlScreen
void ui_ManualControlScreen_screen_init(lv_obj_t *root);
extern lv_obj_t *ui_ManualControlScreen;
extern lv_obj_t *ui_RegisterPanel;
extern lv_obj_t *ui_RegisterSelector;
extern lv_obj_t *ui_Dec;
extern lv_obj_t *ui_DecLabel;
extern lv_obj_t *ui_Register;
extern lv_obj_t *ui_Inc;
extern lv_obj_t *ui_IncLabel;
extern lv_obj_t *ui_RegisterLabel;
extern lv_obj_t *ui_RegisterPanel1;
extern lv_obj_t *ui_ValueSelector;
extern lv_obj_t *ui_Dec1;
extern lv_obj_t *ui_DecLabel1;
extern lv_obj_t *ui_Value;
extern lv_obj_t *ui_Inc1;
extern lv_obj_t *ui_IncLabel1;
extern lv_obj_t *ui_RegisterLabel1;
extern lv_obj_t *ui_ReadWritePanel;
void ui_event_ReadButton( lv_event_t * e);
extern lv_obj_t *ui_ReadButton;
extern lv_obj_t *ui_ReadButtonLabel1;
void ui_event_WriteButton( lv_event_t * e);
extern lv_obj_t *ui_WriteButton;
extern lv_obj_t *ui_WriteButtonLabel;
// SCREEN: ui_MainPanelScreen
void ui_MainPanelScreen_screen_init(lv_obj_t *root);
extern lv_obj_t *ui_MainPanelScreen;
extern lv_obj_t *ui_MainButtonPanel;
void ui_event_StartStopButton( lv_event_t * e);
extern lv_obj_t *ui_StartStopButton;
extern lv_obj_t *ui_ReadButtonLabel2;
extern lv_obj_t *ui____initial_actions0;



LV_FONT_DECLARE( ui_font_bigfont);
LV_FONT_DECLARE( ui_font_hack);
LV_FONT_DECLARE( ui_font_symbols);
LV_FONT_DECLARE( ui_font_tempfont);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
