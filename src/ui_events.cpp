#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "settings.hpp"
#include "ui_events.hpp"
#include "ui_hal.h"
#include "Config.h"

lv_chart_series_t * ui_Screen1_Chart1_Series;

void update_manual_cooling_button(bool value) {
  if (value) {
    lv_obj_add_state(ui_CoolingButton, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(ui_CoolingButton, LV_STATE_CHECKED);
  }
}


void on_setting1_incr(lv_event_t * e)
{
  cool_temp_value += 1;
  if (cool_temp_value > MAX_COOL_TEMP) {
    cool_temp_value = MAX_COOL_TEMP;
  }
  lv_textarea_set_text(ui_Setting1, String(cool_temp_value).c_str());
}

void on_setting_1_decr(lv_event_t * e)
{
  cool_temp_value -= 1;
  if (cool_temp_value < MIN_COOL_TEMP) {
    cool_temp_value = MIN_COOL_TEMP;
  }
  lv_textarea_set_text(ui_Setting1, String(cool_temp_value).c_str());
}

void on_setting_2_incr(lv_event_t * e)
{
  before_mix_value += 1;
  if (before_mix_value > MAX_BEFORE_MIX_TIME) {
    before_mix_value = MAX_BEFORE_MIX_TIME;
  }
  lv_textarea_set_text(ui_Setting2, String(before_mix_value).c_str());
}

void on_setting_2_decr(lv_event_t * e)
{
  before_mix_value -= 1;
  if (before_mix_value < MIN_BEFORE_MIX_TIME) {
    before_mix_value = MIN_BEFORE_MIX_TIME;
  }
  lv_textarea_set_text(ui_Setting2, String(before_mix_value).c_str());
}

void on_setting_3_incr(lv_event_t * e)
{
  mix_value += 1;
  if (mix_value > MAX_MIX_TIME) {
    mix_value = MAX_MIX_TIME;
  }
  lv_textarea_set_text(ui_Setting3, String(mix_value).c_str());
}

void on_setting_3_decr(lv_event_t * e)
{
  mix_value -= 1;
  if (mix_value < MIN_MIX_TIME) {
    mix_value = MIN_MIX_TIME;
  }
  lv_textarea_set_text(ui_Setting3, String(mix_value).c_str());
}

void on_setting_4_incr(lv_event_t * e)
{
  mix_delay_value += 1;
  if (mix_delay_value > MAX_MIX_DELAY_TIME) {
    mix_delay_value = MAX_MIX_DELAY_TIME;
  }
  lv_textarea_set_text(ui_Setting4, String(mix_delay_value).c_str());
}

void on_setting_4_decr(lv_event_t * e)
{
  mix_delay_value -= 1;
  if (mix_delay_value < MIN_MIX_DELAY_TIME) {
    mix_delay_value = MIN_MIX_DELAY_TIME;
  }
  lv_textarea_set_text(ui_Setting4, String(mix_delay_value).c_str());
}

void update_settings_values() {
  lv_textarea_set_text(ui_Setting4, String(mix_delay_value).c_str());
  lv_textarea_set_text(ui_Setting3, String(mix_value).c_str());
  lv_textarea_set_text(ui_Setting2, String(before_mix_value).c_str());
  lv_textarea_set_text(ui_Setting1, String(cool_temp_value).c_str());

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

void on_main_base(lv_event_t * e)
{
	Serial.println("base button");
}


void on_main_mixing(lv_event_t * e)
{
	Serial.println("mixing button");
}

void on_main_rinsing(lv_event_t * e)
{
	Serial.println("rinsing button");
}

void on_main_acid(lv_event_t * e)
{
	Serial.println("acid button");
}

void on_main_cooling(lv_event_t * e)
{
	Serial.println("cooling button");
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

void wifi_sync_ui(bool connected) {
  if (connected) {
    lv_obj_clear_state( ui_SettingsButton4, LV_STATE_DISABLED);
  } else {
    lv_obj_add_state( ui_SettingsButton4, LV_STATE_DISABLED);
  }
}
