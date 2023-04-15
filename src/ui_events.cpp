#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "settings.hpp"
#include "ui_events.hpp"
#include "ui_hal.h"
#include "Config.h"

static const char *btnm_map[] = {
	"1", "2", "3", "4", "\n",
	"5", "6", "7", "8", "\n",
	"9", "10", "11", "12", "",
};

void on_button_map_click(lv_event_t * e) {
	Serial.println("button map click");
}

void setup_button_map(lv_event_t * e) {
    lv_obj_t * btnm1 = lv_btnmatrix_create(ui_MainScreenPanel);
    lv_btnmatrix_set_map(btnm1, btnm_map);
    lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btnm1, on_button_map_click, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_width(btnm1, lv_pct(100));
    lv_obj_set_height(btnm1, lv_pct(100));
    lv_btnmatrix_set_btn_ctrl_all(btnm1, LV_BTNMATRIX_CTRL_CHECKABLE); // TODO
    lv_obj_set_style_bg_color(btnm1, lv_color_hex(0x1499FF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btnm1, lv_color_hex(0x800000), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(btnm1, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(btnm1, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_CHECKED);
}

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
  update_temp_value();
}

void on_setting_1_decr(lv_event_t * e)
{
  cool_temp_value -= 1;
  if (cool_temp_value < MIN_COOL_TEMP) {
    cool_temp_value = MIN_COOL_TEMP;
  }
  update_temp_value();
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

void update_temp_value() {
  int16_t ta = cool_temp_value / 10;
  int16_t tb = cool_temp_value % 10;

  char buf[10];
  lv_snprintf(buf, sizeof(buf), "%hd.%hd", ta, tb);
  lv_textarea_set_text(ui_Setting1, buf);
}

void update_settings_values() {
  lv_textarea_set_text(ui_Setting4, String(mix_delay_value).c_str());
  lv_textarea_set_text(ui_Setting3, String(mix_value).c_str());
  lv_textarea_set_text(ui_Setting2, String(before_mix_value).c_str());
  update_temp_value();

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
    on_mixing_pressed();
}

void on_main_acid(lv_event_t * e)
{
	Serial.println("acid button");
    on_acid_pressed();
}

void on_main_cooling(lv_event_t * e)
{
	Serial.println("cooling button");
	on_cooling_pressed();
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
