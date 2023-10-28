#include "ui.h"
#include "../mainscreen/ui_events.h"
#include "../mainscreen/ui.h"
#include "../shared/ui.h"
#include <Arduino.h>

lv_obj_t *ui_TabView;
lv_obj_t *ui_TabProgram;
lv_obj_t *ui_TabSettings;
lv_obj_t *ui_TabWifiSettings;

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
