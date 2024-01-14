#include "../mainscreen/ui.h"
#include "../mainscreen/ui_events.h"
#include "../shared/settings.h"
#include "../shared/ui.h"
#include "logic.hpp"
#include "ui.h"
#include <Arduino.h>
#include <Preferences.h>

lv_obj_t *ui_TabView;
lv_obj_t *ui_TabMainPanel;
lv_obj_t *ui_TabManualControl;
lv_obj_t *ui_TabSettings;
lv_obj_t *ui_TabWifiSettings;
lv_obj_t *ui_ManualControlMatrix;

static const char *btnm_map[] = {
    "0", "1",  "2", "3", "\n", "4",  "5", "6",
    "7", "\n", "8", "9", "10", "11", "",
};

Preferences preferences;

setting_decl pause_time = setting_decl{
    .value = PAUSE_TIME_DEF,
    .min = PAUSE_TIME_MIN,
    .max = PAUSE_TIME_MAX,
    .digits = 0,
    .fmt = "%2.0f",
};

void on_start_stop(lv_event_t *e) {
  logic_interrupt(LogicEvent::StartStopProg);
}

void on_apply_button(lv_event_t *e) {
  settings_update();
  lv_tabview_set_act(ui_TabView, 0, LV_ANIM_OFF);
}

void on_manual_control_button(lv_event_t *e) {
  lv_tabview_set_act(ui_TabView, 1, LV_ANIM_OFF);
}

void on_settings_button(lv_event_t *e) {
  lv_tabview_set_act(ui_TabView, 2, LV_ANIM_OFF);
}

void on_back_button(lv_event_t *e) {
  lv_tabview_set_act(ui_TabView, 0, LV_ANIM_OFF);
}

void on_button_map_click(lv_event_t *e) {
  _DEBUG("on_button_map_click");
  uint32_t id = lv_btnmatrix_get_selected_btn(ui_ManualControlMatrix);
  logic_flip_delayed((Channel_t)id);
}

void setup_button_map() {
  ui_ManualControlMatrix = lv_btnmatrix_create(ui_ManualControlScreen);
  lv_btnmatrix_set_map(ui_ManualControlMatrix, btnm_map);
  lv_obj_align(ui_ManualControlMatrix, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(ui_ManualControlMatrix, on_button_map_click,
                      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_width(ui_ManualControlMatrix, lv_pct(100));
  lv_obj_set_height(ui_ManualControlMatrix, lv_pct(100));
  lv_obj_set_style_bg_color(ui_ManualControlMatrix, lv_color_hex(0x1499FF),
                            LV_PART_ITEMS | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_ManualControlMatrix, lv_color_hex(0x800000),
                            LV_PART_ITEMS | LV_STATE_CHECKED);
  lv_obj_set_style_text_color(ui_ManualControlMatrix, lv_color_hex(0xFFFFFF),
                              LV_PART_ITEMS | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_ManualControlMatrix, lv_color_hex(0xFFFFFF),
                              LV_PART_ITEMS | LV_STATE_CHECKED);
  lv_obj_set_style_text_font(ui_ManualControlMatrix, &ui_font_bigfont,
                             LV_PART_ITEMS | LV_STATE_DEFAULT);
}

void on_tab_change(lv_event_t *e) {
  switch (lv_tabview_get_tab_act(ui_TabView)) {
  case 0:
    lv_obj_set_style_text_color(ui_BackButton, lv_color_hex(0x1499FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SettingsButton, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ManualControlButton, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    break;
  case 1:
    lv_obj_set_style_text_color(ui_BackButton, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SettingsButton, lv_color_hex(0x1499FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ManualControlButton, lv_color_hex(0x1499FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    break;
  case 2:
    lv_obj_set_style_text_color(ui_BackButton, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_SettingsButton, lv_color_hex(0x1499FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ManualControlButton, lv_color_hex(0x1499FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    break;
  }
}

void app_init() {
  // спрятать все лишнее для этой программы
  lv_obj_add_flag(ui_TemperatureDisplay, LV_OBJ_FLAG_HIDDEN);
  // lv_obj_add_flag(ui_ManualControlButton, LV_OBJ_FLAG_HIDDEN);
  // lv_obj_add_flag(ui_ForwardButton, LV_OBJ_FLAG_HIDDEN);
  // lv_obj_add_flag(ui_BackButton, LV_OBJ_FLAG_HIDDEN);
  //  lv_obj_add_flag(ui_WarningIndicator, LV_OBJ_FLAG_HIDDEN);

  lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0x1499FF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_ForwardButton, lv_color_hex(0x1499FF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);

  // создать tab view для содержимого
  ui_TabView = lv_tabview_create(ui_MainPanel, LV_DIR_LEFT, 50);
  lv_obj_clear_flag(lv_tabview_get_content(ui_TabView), LV_OBJ_FLAG_SCROLLABLE);

  // спрятать кнопки
  lv_obj_add_flag(lv_tabview_get_tab_btns(ui_TabView), LV_OBJ_FLAG_HIDDEN);

  // создать tab для главного экрана
  ui_TabMainPanel = lv_tabview_add_tab(ui_TabView, "1");
  ui_MainPanelScreen_screen_init(ui_TabMainPanel);

  // костыли: установить размеры, убрать отступы
  lv_obj_set_width(ui_MainPanelScreen, lv_pct(100));
  lv_obj_set_height(ui_MainPanelScreen, lv_pct(100));
  lv_obj_set_style_pad_left(ui_TabMainPanel, 0,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui_TabMainPanel, 0,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_TabMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui_TabMainPanel, 0,
                              LV_PART_MAIN | LV_STATE_DEFAULT);

  // создать tab для ручного управления
  ui_TabManualControl = lv_tabview_add_tab(ui_TabView, "2");
  ui_ManualControlScreen_screen_init(ui_TabManualControl);
  setup_button_map();

  // костыли: установить размеры, убрать отступы
  lv_obj_set_width(ui_ManualControlScreen, lv_pct(100));
  lv_obj_set_height(ui_ManualControlScreen, lv_pct(100));
  lv_obj_set_style_pad_left(ui_TabManualControl, 0,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui_TabManualControl, 0,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_TabManualControl, 0,
                           LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui_TabManualControl, 0,
                              LV_PART_MAIN | LV_STATE_DEFAULT);

  // создать tab для настроек
  ui_TabSettings = lv_tabview_add_tab(ui_TabView, "3");
  ui_SettingsScreen_screen_init(ui_TabSettings);

  // костыли: установить размеры, убрать отступы
  lv_obj_set_width(ui_SettingsScreen, lv_pct(100));
  lv_obj_set_height(ui_SettingsScreen, lv_pct(100));
  lv_obj_set_style_pad_left(ui_TabSettings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui_TabSettings, 0,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_TabSettings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui_TabSettings, 0,
                              LV_PART_MAIN | LV_STATE_DEFAULT);

  // start/stop
  lv_obj_add_event_cb(ui_StartStopButton, on_start_stop, LV_EVENT_SHORT_CLICKED,
                      NULL);

  // настройки
  settings_setup();
  ui_setting_add("Время выдержки (мин)", &pause_time);

  lv_obj_t *ApplyButton = ui_setting_add_apply();
  lv_obj_add_event_cb(ApplyButton, on_apply_button, LV_EVENT_SHORT_CLICKED,
                      NULL);

  // навигация
  lv_obj_add_event_cb(ui_BackButton, on_back_button, LV_EVENT_SHORT_CLICKED,
                      NULL);
  lv_obj_add_event_cb(ui_SettingsButton, on_settings_button,
                      LV_EVENT_SHORT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_ManualControlButton, on_manual_control_button,
                      LV_EVENT_SHORT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_TabView, on_tab_change, LV_EVENT_VALUE_CHANGED, NULL);
  on_tab_change(NULL);
}

void on_warn_button_clicked(lv_event_t *e) {}

void on_forward_button(lv_event_t *e) {}

void on_main_button_pressed(lv_event_t *e) {}

void settings_setup() {
  if (!preferences.begin("skrepper", true)) {
    return;
  }

  pause_time.value = (int)preferences.getInt("pause_time");
  if (pause_time.value < PAUSE_TIME_MIN * 100 ||
      pause_time.value > PAUSE_TIME_MAX * 100) {
    pause_time.value = PAUSE_TIME_DEF;
  }

  preferences.end();
}

void settings_update() {

  if (!preferences.begin("skrepper", false)) {
    return;
  }

  preferences.putInt("pause_time", pause_time.value);

  preferences.end();
}
