#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "ui_variables.h"
#include "Config.h"

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
