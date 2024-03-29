#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "settings.hpp"
#include "ui_events.hpp"
#include "ui_hal.h"
#include "Config.h"
#include "temperature_graph.hpp"

lv_chart_series_t * ui_Screen1_Chart1_Series;

void on_main_button_pressed(lv_event_t * e)
{
  on_main_switch_pressed();
}

void on_manual_heating(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    set_heat(lv_obj_has_state(obj, LV_STATE_CHECKED));
  }
}

void on_manual_cooling(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    set_cool(lv_obj_has_state(obj, LV_STATE_CHECKED));
  }
}

void on_manual_mixing(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = lv_event_get_target(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    set_mixer(lv_obj_has_state(obj, LV_STATE_CHECKED));
  }
}

void update_manual_heating_button(bool value) {
  if (value) {
    lv_obj_add_state(ui_HeatingButton, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(ui_HeatingButton, LV_STATE_CHECKED);
  }
}

void update_manual_cooling_button(bool value) {
  if (value) {
    lv_obj_add_state(ui_CoolingButton, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(ui_CoolingButton, LV_STATE_CHECKED);
  }
}

void update_manual_mixing_button(bool value) {
  if (value) {
    lv_obj_add_state(ui_MixingButton, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(ui_MixingButton, LV_STATE_CHECKED);
  }
}

void on_past_temp_incr(lv_event_t * e)
{
  past_temp_value += 1;
  if (past_temp_value > MAX_PAST_TEMP) {
    past_temp_value = MAX_PAST_TEMP;
  }
  lv_textarea_set_text(ui_PastTemp, String(past_temp_value).c_str());
}

void on_past_temp_decr(lv_event_t * e)
{
  past_temp_value -= 1;
  if (past_temp_value < MIN_PAST_TEMP) {
    past_temp_value = MIN_PAST_TEMP;
  }
  lv_textarea_set_text(ui_PastTemp, String(past_temp_value).c_str());
}

void on_past_time_incr(lv_event_t * e)
{
  past_time_value += 1;
  if (past_time_value > MAX_PAST_TIME) {
    past_time_value = MAX_PAST_TIME;
  }
  lv_textarea_set_text(ui_PastTime, String(past_time_value).c_str());
}

void on_past_time_decr(lv_event_t * e)
{
  past_time_value -= 1;
  if (past_time_value < MIN_PAST_TIME) {
    past_time_value = MIN_PAST_TIME;
  }
  lv_textarea_set_text(ui_PastTime, String(past_time_value).c_str());
}

void update_settings_values() {
  lv_textarea_set_text(ui_PastTemp, String(past_temp_value).c_str());
  lv_textarea_set_text(ui_PastTime, String(past_time_value).c_str());
  lv_textarea_set_text(ui_StorageTemp1, String(store_temp_value).c_str());

  lv_textarea_set_text(ui_WifiName, wifi_ap);
  lv_textarea_set_text(ui_WifiPassword, wifi_pw);
}

void on_save_settings(lv_event_t * e)
{
  strcpy(wifi_ap, lv_textarea_get_text(ui_WifiName));
  strcpy(wifi_pw, lv_textarea_get_text(ui_WifiPassword));
  settings_update();
}

void on_keyboard_press(lv_event_t * e)
{
  strcpy(wifi_ap, lv_textarea_get_text(ui_WifiName));
  strcpy(wifi_pw, lv_textarea_get_text(ui_WifiPassword));
  settings_update();
}

void on_storage_temp_incr(lv_event_t * e)
{
  store_temp_value += 1;
  if (store_temp_value > MAX_STORAGE_TEMP) {
    store_temp_value = MAX_STORAGE_TEMP;
  }
  lv_textarea_set_text(ui_StorageTemp1, String(store_temp_value).c_str());
}

void on_storage_temp_decr(lv_event_t * e)
{
  store_temp_value -= 1;
  if (store_temp_value < MIN_STORAGE_TEMP) {
    store_temp_value = MIN_STORAGE_TEMP;
  }
  lv_textarea_set_text(ui_StorageTemp1, String(store_temp_value).c_str());
}

void on_ap_focused(lv_event_t * e)
{
  lv_keyboard_set_textarea(ui_WifiKeyboard,ui_WifiName);
}

void on_password_focused(lv_event_t * e)
{
  lv_keyboard_set_textarea(ui_WifiKeyboard,ui_WifiPassword);
}

void on_main_screen_loaded(lv_event_t * e)
{
  settings_setup();
}

void on_manual_control_screen_loaded(lv_event_t * e)
{
}

void on_settings_screen_loaded(lv_event_t * e)
{
}

void on_settings_screen_2_loaded(lv_event_t * e)
{
}

void on_wireless_screen_loaded(lv_event_t * e)
{
}

lv_coord_t temperature_data[TEMP_CHART_POINT_COUNT];
int16_t point_count = 0;
int16_t chart_ptr = 0;

void on_chart_init() {
  lv_chart_set_type(ui_Screen1_Chart1, LV_CHART_TYPE_LINE);
  // lv_obj_set_style_pad_right(ui_Screen1_Chart1, 30, LV_PART_MAIN| LV_STATE_DEFAULT);
  lv_obj_set_height(ui_Screen1_Chart1, 140);
  lv_obj_set_align(ui_Screen1_Chart1, LV_ALIGN_TOP_LEFT );
  lv_obj_set_width(ui_Screen1_Chart1, lv_pct(88));
  lv_obj_set_x(ui_Screen1_Chart1, 15);
  lv_chart_set_range(ui_Screen1_Chart1, LV_CHART_AXIS_SECONDARY_Y, 0, 1000);
  lv_chart_set_div_line_count(ui_Screen1_Chart1, 100, 0);
  lv_obj_set_style_size(ui_Screen1_Chart1, 1, LV_PART_INDICATOR);

  // init all the points
  ui_Screen1_Chart1_Series = lv_chart_add_series(ui_Screen1_Chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_SECONDARY_Y);

  // set tempdata array
  lv_chart_set_ext_y_array(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, (lv_coord_t*)&temperature_data);
  lv_chart_set_x_start_point(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, 0);

  // reset data
  temperature_graph_reset();

  // configure ticks
  lv_chart_set_axis_tick(ui_Screen1_Chart1, LV_CHART_AXIS_PRIMARY_X, 10, 5, TEMP_CHART_MAJOR_TICKS_X, 5, true, 60);
  lv_chart_set_axis_tick(ui_Screen1_Chart1, LV_CHART_AXIS_SECONDARY_Y, 10, 5, TEMP_CHART_MAJOR_TICKS_Y, 2, true, 50);

  lv_obj_add_event_cb(ui_Screen1_Chart1, on_chart_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
}

void on_chart_draw_x_label(lv_obj_draw_part_dsc_t * dsc) {


  if (graph_last_update <= 1600000000){
    // fallback to relative mode
    // rightmost: 00:00
    // leftmost: hour:minutes since start

    uint64_t tick_time_ms = TEMP_CHART_RESOLUTION_MS * point_count * ((uint64_t)dsc->value) / (TEMP_CHART_MAJOR_TICKS_X-1);
    uint16_t mins = (uint16_t) ((tick_time_ms / 60000ll ) % 60);
    uint16_t hrs = (uint16_t) (tick_time_ms / 60000ll / 60l);
    lv_snprintf(dsc->text, dsc->text_length, " %02d:%02d ", hrs, mins);

    return;
  }

  // fallback to relative mode
  // rightmost: hour:minutes (approx program start)
  // leftmost: hour:minutes (current time)

  uint64_t tick_time_ms = TEMP_CHART_RESOLUTION_MS * point_count * (TEMP_CHART_MAJOR_TICKS_X - (uint64_t)dsc->value - 1) / (TEMP_CHART_MAJOR_TICKS_X-1);

  // calculate delta-time
  time_t gt = graph_last_update - tick_time_ms/1000ll;
  struct tm t;
  localtime_r(&gt, &t);

  // substract time
  strftime(dsc->text, dsc->text_length, "%H:%M", &t);
}

void on_chart_draw_cb(lv_event_t * e)
{
  lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
  if (lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL)) {
    if (dsc->id == LV_CHART_AXIS_SECONDARY_Y && dsc->text) {
      lv_snprintf(dsc->text, dsc->text_length, "%d", ((lv_coord_t)dsc->value)/10);
      return;
    }

    if (dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {

      on_chart_draw_x_label(dsc);
      return;
    }
  }

  if (dsc->part == LV_PART_MAIN) {
    if (dsc->line_dsc == NULL || dsc->p1 == NULL || dsc->p2 == NULL) {
      return;
    }
    if (dsc->p1->x == dsc->p2->x) {
      return;
    }
    if (dsc->id == (100-past_temp_value)) {
      dsc->line_dsc->color = lv_palette_main(LV_PALETTE_RED);
      dsc->line_dsc->opa = LV_OPA_50;
      dsc->line_dsc->width = 1;
    } else if (dsc->id == (100-store_temp_value)) {
      dsc->line_dsc->color = lv_palette_main(LV_PALETTE_BLUE);
      dsc->line_dsc->opa = LV_OPA_50;
      dsc->line_dsc->width = 1;
    } else if (dsc->line_dsc->width > 0){
      dsc->line_dsc->opa = LV_OPA_TRANSP;
      dsc->line_dsc->width = 0;
    }

  }
}

void display_temperature(float v)
{
  if (pdTRUE != xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
    return;
  }

  String stringValue;

  if (v < -100.0) {
    stringValue = String("");
  } else {
    stringValue = String(v, 1) + String("°");
    if (v > 0) {
      stringValue = String("+") + stringValue;
    }
  }

  lv_label_set_text(ui_TemperatureDisplay, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay1, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay2, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay3, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay4, stringValue.c_str());

  xSemaphoreGive(xGuiSemaphore);
  return;
}

void temperature_graph_reset() {
  point_count = 0;
  chart_ptr = 0;

  lv_chart_set_point_count(ui_Screen1_Chart1, 0);

  for (int i = 0; i < TEMP_CHART_POINT_COUNT; i++) {
    temperature_data[i] = LV_CHART_POINT_NONE;
  }

  lv_chart_refresh(ui_Screen1_Chart1);
}

void activate_state_idle() {
  lv_obj_set_style_bg_color(ui_StartStopButton, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_label_set_text(ui_StartStopLabel,"Пастеризация");
}

void activate_state_work() {
  lv_obj_set_style_bg_color(ui_StartStopButton, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_label_set_text(ui_StartStopLabel,"Стоп");
}

void activate_state_done() {
  lv_obj_set_style_bg_color(ui_StartStopButton, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN | LV_STATE_DEFAULT );
  lv_label_set_text(ui_StartStopLabel,"Завершить хранение");
}

void update_state_label(LogicState state, int64_t past_time_left_ms) {
  int mins;
  int secs;

  switch (state) {

    case LogicState::Idle:
      lv_label_set_text(ui_ChartCommentLabel,"Готов к работе");
      activate_state_idle();
      break;
    case LogicState::Heating:
      lv_label_set_text(ui_ChartCommentLabel,"Нагрев");
      activate_state_work();
      break;
    case LogicState::Pasterizing:
      mins = (uint16_t) (past_time_left_ms / 60000ll);
      secs = (uint16_t) ((past_time_left_ms / 1000L) % 60l);
      lv_label_set_text_fmt(ui_ChartCommentLabel, "Пастеризация (%02d:%02d)", mins, secs);
      activate_state_work();
      break;
    case LogicState::Cooling:
      lv_label_set_text(ui_ChartCommentLabel,"Охлаждение");
      activate_state_work();
      break;
    case LogicState::Storing:
      lv_label_set_text(ui_ChartCommentLabel,"Хранение");
      activate_state_done();
      break;
  }
}

void wifi_sync_ui(bool connected) {
  if (connected) {
    lv_obj_clear_state( ui_SettingsButton4, LV_STATE_DISABLED);
  } else {
    lv_obj_add_state( ui_SettingsButton4, LV_STATE_DISABLED);
  }
}
