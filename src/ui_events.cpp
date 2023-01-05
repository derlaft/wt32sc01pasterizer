#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "ui_variables.h"
#include "ui_events.h"
#include "Config.h"

lv_chart_series_t * ui_Screen1_Chart1_Series;

void on_main_button_pressed(lv_event_t * e)
{
  Serial.println("main button pressed");
}

void on_manual_heating(lv_event_t * e)
{
  Serial.println("manual heating override");
}

void on_manual_cooling(lv_event_t * e)
{
  Serial.println("manual cooling override");
}

void on_manual_mixing(lv_event_t * e)
{
  Serial.println("manual mixing override");
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

void on_save_settings(lv_event_t * e)
{
  Serial.println("test: applied settings");
}

void on_abort_settings(lv_event_t * e)
{
  Serial.println("test: aborted settings");
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

void on_keyboard_press(lv_event_t * e)
{
  Serial.println("test: applied wifi settings");
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

void on_chart_init() {
  lv_chart_set_type(ui_Screen1_Chart1, LV_CHART_TYPE_LINE);
  lv_chart_set_point_count(ui_Screen1_Chart1, TEMP_CHART_POINT_COUNT);
  lv_chart_set_range(ui_Screen1_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
  lv_chart_set_div_line_count(ui_Screen1_Chart1, 0, 0);
  lv_obj_set_style_size(ui_Screen1_Chart1, 0, LV_PART_INDICATOR);
  ui_Screen1_Chart1_Series = lv_chart_add_series(ui_Screen1_Chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_set_x_start_point(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, TEMP_CHART_POINT_COUNT-1);
}
