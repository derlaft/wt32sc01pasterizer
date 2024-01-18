
#ifndef _SKREPPER_UI_H
#define _SKREPPER_UI_H

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
// SCREEN: ui_MainPanelScreen
void ui_MainPanelScreen_screen_init(lv_obj_t *root);
extern lv_obj_t *ui_MainPanelScreen;
extern lv_obj_t *ui_RootPanel;
extern lv_obj_t *ui_MainButtonPanel;
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
