
#ifndef _DOZATOR_UI_H
#define _DOZATOR_UI_H

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

#include "ui_events.h"
#include "ui_helpers.h"
// SCREEN: ui_MainControlScreen
void ui_MainControlScreen_screen_init(lv_obj_t *root);
extern lv_obj_t *ui_MainControlScreen;
void ui_event_StartStopButton(lv_event_t *e);
extern lv_obj_t *ui_StartStopButton;
extern lv_obj_t *ui_StartStopLabel;
extern lv_obj_t *ui_Spinner;
extern lv_obj_t *ui____initial_actions0;

LV_FONT_DECLARE(ui_font_bigfont);
LV_FONT_DECLARE(ui_font_hack);
LV_FONT_DECLARE(ui_font_symbols);
LV_FONT_DECLARE(ui_font_tempfont);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
