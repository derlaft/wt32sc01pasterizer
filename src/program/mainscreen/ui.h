
#ifndef _UNIVERSALMAINSCREEN_UI_H
#define _UNIVERSALMAINSCREEN_UI_H

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
// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
extern lv_obj_t * ui_MainScreen;
extern lv_obj_t * ui_TopPanel;
void ui_event_BackButton(lv_event_t * e);
extern lv_obj_t * ui_BackButton;
void ui_event_ManualControlButton(lv_event_t * e);
extern lv_obj_t * ui_ManualControlButton;
extern lv_obj_t * ui_TempAndWarningGroup;
extern lv_obj_t * ui_TemperatureDisplay;
void ui_event_WarningIndicator(lv_event_t * e);
extern lv_obj_t * ui_WarningIndicator;
void ui_event_SettingsButton(lv_event_t * e);
extern lv_obj_t * ui_SettingsButton;
void ui_event_ForwardButton(lv_event_t * e);
extern lv_obj_t * ui_ForwardButton;
extern lv_obj_t * ui_MainPanel;
extern lv_obj_t * ui____initial_actions0;

LV_FONT_DECLARE(ui_font_bigfont);
LV_FONT_DECLARE(ui_font_hack);
LV_FONT_DECLARE(ui_font_symbols);
LV_FONT_DECLARE(ui_font_tempfont);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
