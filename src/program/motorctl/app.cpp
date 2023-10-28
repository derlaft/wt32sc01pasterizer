#include "ui.h"
#include "logic.hpp"
#include "../mainscreen/ui_events.h"
#include "../mainscreen/ui.h"
#include "../shared/ui.h"
#include <Arduino.h>

lv_obj_t *ui_TabView;
lv_obj_t *ui_TabProgram;
lv_obj_t *ui_TabSettings;
lv_obj_t *ui_TabWifiSettings;

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

void on_manual_write(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_SHORT_CLICKED) {
	    return;
    }

    uint8_t reg = (uint8_t) lv_spinbox_get_value(ui_Register);
    uint16_t value = (uint16_t) lv_spinbox_get_value(ui_Value);

    logic_debug_send_write(reg, value);
}

void app_init() {
	// спрятать все лишнее для этой программы
	lv_obj_add_flag(ui_TempAndWarningGroup, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ManualControlButton, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_ForwardButton, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui_BackButton, LV_OBJ_FLAG_HIDDEN);

	// создать tab view для содержимого
	ui_TabView = lv_tabview_create(ui_MainPanel, LV_DIR_LEFT, 50);

	// спрятать кнопки
	// lv_obj_add_flag(lv_tabview_get_tab_btns(ui_TabView), LV_OBJ_FLAG_HIDDEN);

	// создать tab для главного экрана
	ui_TabProgram = lv_tabview_add_tab(ui_TabView, "1");
	ui_MainControlScreen_screen_init(ui_TabProgram);
	// костыли: установить размеры, убрать отступы
	lv_obj_set_width(ui_MainControlScreen, lv_pct(100));
	lv_obj_set_height(ui_MainControlScreen, lv_pct(100));
	lv_obj_set_style_pad_left(ui_TabProgram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_TabProgram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_TabProgram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_TabProgram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	// создать tab
	ui_TabSettings = lv_tabview_add_tab(ui_TabView, "2");
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
	lv_obj_add_event_cb(ui_WriteButton, on_manual_write, LV_EVENT_ALL, NULL);
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
