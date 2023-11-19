#include "ui.h"
#include "logic.hpp"
#include "../mainscreen/ui_events.h"
#include "../mainscreen/ui.h"
#include "../shared/ui.h"
#include "../shared/settings.h"
#include <Arduino.h>
#include <Preferences.h>

lv_obj_t *ui_TabView;
lv_obj_t *ui_TabMainPanel;
lv_obj_t *ui_TabManualControl;
lv_obj_t *ui_TabSettings;
lv_obj_t *ui_TabWifiSettings;

Preferences preferences;

uint8_t freq = 0;
uint8_t delta_freq = 0;

setting_decl freq_base = setting_decl{
		.value = DEF_FREQ_BASE * 100,
		.min = FREQ_BASE_MIN,
		.max = FREQ_BASE_MAX,
		.digits = 2,
		.fmt = "%2.2f",
};

setting_decl freq_delta = setting_decl{
		.value = DEF_FREQ_DELTA * 100,
		.min = FREQ_DELTA_MIN,
		.max = FREQ_DELTA_MAX,
		.digits = 2,
		.fmt = "%2.2f",
		.odd = true,
};

void inc_register(lv_event_t *e) {
   lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(ui_Register);
    }
}

void inc_value(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_increment(ui_Value);
    }
}

void dec_register(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(ui_Register);
    }
}

void dec_value(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_spinbox_decrement(ui_Value);
    }
}

uint16_t manual_reg = 0;
uint16_t manual_value = 0;

void do_manual_send() {
    logic_debug_send_write(manual_reg, manual_value);
}

void on_manual_write(lv_event_t *e) {
    manual_reg = (uint16_t) lv_spinbox_get_value(ui_Register);
    manual_value = (uint16_t) lv_spinbox_get_value(ui_Value);
	logic_modbus_send(do_manual_send);
}

void do_manual_read() {
    logic_debug_send_read(manual_reg);
}

void on_manual_read(lv_event_t *e) {
    manual_reg = (uint16_t) lv_spinbox_get_value(ui_Register);
	logic_modbus_send(do_manual_read);
}

void on_start_stop(lv_event_t *e) {
	logic_interrupt(LogicEvent::StartStopProg);
}

void on_apply_button(lv_event_t *e) {
	settings_update();
	lv_tabview_set_act(ui_TabView, 0, LV_ANIM_OFF);
}

void app_init() {
	// спрятать все лишнее для этой программы
	lv_obj_add_flag(ui_TemperatureDisplay, LV_OBJ_FLAG_HIDDEN);
	//lv_obj_add_flag(ui_ManualControlButton, LV_OBJ_FLAG_HIDDEN);
	//lv_obj_add_flag(ui_ForwardButton, LV_OBJ_FLAG_HIDDEN);
	//lv_obj_add_flag(ui_BackButton, LV_OBJ_FLAG_HIDDEN);
	// lv_obj_add_flag(ui_WarningIndicator, LV_OBJ_FLAG_HIDDEN);
	
	lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);

	// создать tab view для содержимого
	ui_TabView = lv_tabview_create(ui_MainPanel, LV_DIR_LEFT, 50);

	// спрятать кнопки
	lv_obj_add_flag(lv_tabview_get_tab_btns(ui_TabView), LV_OBJ_FLAG_HIDDEN);

	// создать tab для главного экрана
	ui_TabMainPanel = lv_tabview_add_tab(ui_TabView, "1");
	ui_MainPanelScreen_screen_init(ui_TabMainPanel);

	// костыли: установить размеры, убрать отступы
	lv_obj_set_width(ui_MainPanelScreen, lv_pct(100));
	lv_obj_set_height(ui_MainPanelScreen, lv_pct(100));
	lv_obj_set_style_pad_left(ui_TabMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_TabMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_TabMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_TabMainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// создать tab для ручного управления
	ui_TabManualControl = lv_tabview_add_tab(ui_TabView, "2");
	ui_ManualControlScreen_screen_init(ui_TabManualControl);

	// костыли: установить размеры, убрать отступы
	lv_obj_set_width(ui_ManualControlScreen, lv_pct(100));
	lv_obj_set_height(ui_ManualControlScreen, lv_pct(100));
	lv_obj_set_style_pad_left(ui_TabManualControl, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_TabManualControl, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_TabManualControl, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_TabManualControl, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// создать tab для настроек
	ui_TabSettings = lv_tabview_add_tab(ui_TabView, "3");
	ui_SettingsScreen_screen_init(ui_TabSettings);

	// костыли: установить размеры, убрать отступы
	lv_obj_set_width(ui_SettingsScreen, lv_pct(100));
	lv_obj_set_height(ui_SettingsScreen, lv_pct(100));
	lv_obj_set_style_pad_left(ui_TabSettings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_TabSettings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_TabSettings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_TabSettings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// increment/decrement
	lv_obj_add_event_cb(ui_Inc, inc_register, LV_EVENT_ALL,  NULL);
	lv_obj_add_event_cb(ui_Dec, dec_register, LV_EVENT_ALL,  NULL);
	lv_obj_add_event_cb(ui_Inc1, inc_value, LV_EVENT_ALL,  NULL);
	lv_obj_add_event_cb(ui_Dec1, dec_value, LV_EVENT_ALL,  NULL);

	// write
	lv_obj_add_event_cb(ui_WriteButton, on_manual_write, LV_EVENT_SHORT_CLICKED, NULL);
	lv_obj_add_event_cb(ui_ReadButton, on_manual_read, LV_EVENT_SHORT_CLICKED, NULL);

	// start/stop
	lv_obj_add_event_cb(ui_StartStopButton, on_start_stop, LV_EVENT_SHORT_CLICKED, NULL);
   
	// настройки
	settings_setup();
	ui_setting_add("Базовая частота", &freq_base);
	ui_setting_add("Дельта частоты", &freq_delta);

	lv_obj_t *ApplyButton = ui_setting_add_apply();
	lv_obj_add_event_cb(ApplyButton, on_apply_button, LV_EVENT_SHORT_CLICKED, NULL);
}

void on_back_button(lv_event_t * e) {
}

void on_manual_control_button(lv_event_t * e) {
}

void on_warn_button_clicked(lv_event_t * e) {
}

void on_settings_button(lv_event_t * e) {
}

void on_forward_button(lv_event_t * e) {
}

void on_main_button_pressed(lv_event_t * e) {

}

void settings_setup() {
  if (!preferences.begin("motorctl", true)) {
    return;
  }

  freq_base.value = (int) preferences.getInt("freq_base");
  if (freq_base.value < FREQ_BASE_MIN * 100 || freq_base.value > FREQ_BASE_MAX * 100) {
	  freq_base.value = DEF_FREQ_BASE * 100;
  }

  freq_delta.value = (int) preferences.getInt("freq_delta");
  if (freq_delta.value < FREQ_DELTA_MIN * 100 || freq_delta.value > FREQ_DELTA_MAX * 100) {
	  freq_delta.value = DEF_FREQ_DELTA * 100;
  }

  preferences.end();
}

void settings_update() {

  if (!preferences.begin("motorctl", false)) {
    return;
  }

  preferences.putInt("freq_base", freq_base.value);
  preferences.putInt("freq_delta", freq_delta.value);

  preferences.end();
}
