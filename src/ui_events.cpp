#include <Arduino.h>
#include <lvgl.h>
#include "ui.h"
#include "settings.hpp"
#include "ui_events.hpp"
#include "ui_hal.h"
#include "Config.h"

#ifdef UI_EVENTS_DEBUG
#define _DEBUG(...) { \
    char buf[256]; \
    snprintf(buf, sizeof(buf), __VA_ARGS__); \
    Serial.println(buf); \
};
#else
#define _DEBUG(...) {}
#endif

lv_obj_t * ui_ManualControlMatrix;

static const char *btnm_map[] = {
	"0", "1", "2", "3", "\n",
	"4", "5", "6", "7", "\n",
	"8", "9", "10", "11", "",
};

void on_button_map_click(lv_event_t * e) {
	_DEBUG("on_button_map_click");
    uint32_t id = lv_btnmatrix_get_selected_btn(ui_ManualControlMatrix);
    logic_flip_delayed((Channel_t)id);
}

void setup_button_map(lv_event_t * e) {
    ui_ManualControlMatrix = lv_btnmatrix_create(ui_MainScreenPanel);
    lv_btnmatrix_set_map(ui_ManualControlMatrix, btnm_map);
    lv_obj_align(ui_ManualControlMatrix, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(ui_ManualControlMatrix, on_button_map_click, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_width(ui_ManualControlMatrix, lv_pct(100));
    lv_obj_set_height(ui_ManualControlMatrix, lv_pct(100));
    lv_obj_set_style_bg_color(ui_ManualControlMatrix, lv_color_hex(0x1499FF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ManualControlMatrix, lv_color_hex(0x800000), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui_ManualControlMatrix, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ManualControlMatrix, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui_ManualControlMatrix, &ui_font_bigfont, LV_PART_ITEMS | LV_STATE_DEFAULT);
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
	_DEBUG("on_main_base");
    on_base_pressed();
}


void on_main_mixing(lv_event_t * e)
{
	_DEBUG("on_main_mixing");
    on_mixing_pressed();
}

void on_main_acid(lv_event_t * e)
{
	_DEBUG("on_main_acid");
    on_acid_pressed();
}

void on_main_cooling(lv_event_t * e)
{
	_DEBUG("on_main_cooling");
	on_cooling_pressed();
}

void on_warn_button_clicked(lv_event_t * e)
{
	_DEBUG("on_warn_button_clicked");

    lv_obj_t * ui_WarningMsgbox = lv_msgbox_create(NULL, "Ошибка", "Нарушена связь с ПЛС", NULL, true);

    lv_obj_t * title = lv_msgbox_get_title(ui_WarningMsgbox);
    lv_obj_set_style_text_font(title, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * body = lv_msgbox_get_text(ui_WarningMsgbox);
    lv_obj_set_style_text_font(body, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_center(ui_WarningMsgbox);
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
