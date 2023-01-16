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

lv_coord_t temperature_data[TEMP_CHART_POINT_COUNT];
int16_t point_count = 10;

void on_chart_init() {
  lv_chart_set_type(ui_Screen1_Chart1, LV_CHART_TYPE_LINE);
  lv_obj_set_height( ui_Screen1_Chart1, 140);
  lv_chart_set_point_count(ui_Screen1_Chart1, point_count);
  lv_chart_set_range(ui_Screen1_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 1000);
  lv_chart_set_div_line_count(ui_Screen1_Chart1, 0, 0);
  lv_obj_set_style_size(ui_Screen1_Chart1, 0, LV_PART_INDICATOR);

  ui_Screen1_Chart1_Series = lv_chart_add_series(ui_Screen1_Chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
  for (int i = 0; i < TEMP_CHART_POINT_COUNT; i++) {
    temperature_data[i] = LV_CHART_POINT_NONE;
  }
  lv_chart_set_ext_y_array(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, (lv_coord_t*)&temperature_data);
  lv_chart_set_x_start_point(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, 0);

  lv_chart_set_axis_tick(ui_Screen1_Chart1, LV_CHART_AXIS_PRIMARY_X, 10, 5, TEMP_CHART_MAJOR_TICKS, 5, true, 60);
  lv_obj_add_event_cb(ui_Screen1_Chart1, on_chart_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

  lv_obj_set_style_pad_right(ui_Screen1_Chart1, 30, LV_PART_MAIN| LV_STATE_DEFAULT);
}

void on_chart_draw_cb(lv_event_t * e)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
    if (!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL)) {
      return;
    }

    if(dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {

      if (dsc->value == 0) {
        lv_snprintf(dsc->text, dsc->text_length, "0");
        return;
      }

      uint64_t tick_time_ms = TEMP_CHART_RESOLUTION * point_count * ((uint64_t)dsc->value) / TEMP_CHART_MAJOR_TICKS;
      uint16_t mins = (uint16_t) ((tick_time_ms / 60000ll ) % 60);
      uint16_t hrs = (uint16_t) (tick_time_ms / 60000ll / 60l);

      lv_snprintf(dsc->text, dsc->text_length, " %02d:%02d ", hrs, mins);
    }
}
