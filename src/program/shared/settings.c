#include "settings.h"

void on_setting_incr(lv_event_t * e)
{
	setting_decl *opts = lv_event_get_user_data(e);
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);

	opts->value += 1;
	if (opts->value > opts->max) {
		opts->value = opts->max;
	}

	// lv_textarea_set_text(obj, String(opts->value).c_str());
	lv_label_set_text_fmt(obj, "%d", opts->value);
}

void on_setting_decr(lv_event_t * e)
{
	setting_decl *opts = lv_event_get_user_data(e);
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);

	opts->value -= 1;
	if (opts->value < opts->min) {
		opts->value = opts->min;
	}

	lv_label_set_text_fmt(obj, "%d", opts->value);
}


void ui_setting_add(const char *name, setting_decl opts) {

	lv_obj_t *Panel;
	lv_obj_t *InfoLabel;
	lv_obj_t *Decr;
	lv_obj_t *DecrLabel;
	lv_obj_t *Incr;
	lv_obj_t *IncrLabel;
	lv_obj_t *Setting;

    Panel = lv_label_create(ui_SettingsScreen);
    lv_obj_set_width(Panel, lv_pct(100));
    lv_obj_set_height(Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(Panel, 0);
    lv_obj_set_y(Panel, 20);
    lv_obj_set_align(Panel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(Panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(Panel, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(Panel, "");
    lv_obj_set_style_text_align(Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(Panel, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

	if (opts.odd) {
		lv_obj_set_style_bg_color(Panel, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(Panel, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

    InfoLabel = lv_label_create(Panel);
    lv_obj_set_width(InfoLabel, lv_pct(50));
    lv_obj_set_height(InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(InfoLabel, 15);
    lv_obj_set_y(InfoLabel, 0);
    lv_obj_set_align(InfoLabel, LV_ALIGN_CENTER);
    lv_label_set_text(InfoLabel, name);
    lv_obj_set_style_text_font(InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    Decr = lv_btn_create(Panel);
    lv_obj_set_width(Decr, 60);
    lv_obj_set_height(Decr, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(Decr, 20);
    lv_obj_set_y(Decr, 0);
    lv_obj_set_align(Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    DecrLabel = lv_label_create(Decr);
    lv_obj_set_width(DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(DecrLabel, "-");
    lv_obj_set_style_text_font(DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    Setting = lv_textarea_create(Panel);
    lv_obj_set_width(Setting, 80);
    lv_obj_set_height(Setting, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(Setting, 100);
    lv_obj_set_y(Setting, 0);
    lv_obj_set_align(Setting, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(Setting, 128);
    lv_textarea_set_text(Setting, "4");
    lv_textarea_set_placeholder_text(Setting, "");
    lv_obj_clear_flag(Setting, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(Setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(Setting, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    Incr = lv_btn_create(Panel);
    lv_obj_set_width(Incr, 60);
    lv_obj_set_height(Incr, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(Incr, 185);
    lv_obj_set_y(Incr, 0);
    lv_obj_set_align(Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    IncrLabel = lv_label_create(Incr);
    lv_obj_set_width(IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(IncrLabel, "+");
    lv_obj_set_style_text_font(IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_setting_add_apply() {
    ui_ApplyButton = lv_btn_create(ui_SettingsScreen);
    lv_obj_set_width(ui_ApplyButton, lv_pct(100));
    lv_obj_set_height(ui_ApplyButton, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ApplyButton, -1);
    lv_obj_set_y(ui_ApplyButton, -1);
    lv_obj_set_align(ui_ApplyButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_ApplyButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ApplyButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_ApplyButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StartStopLabel1 = lv_label_create(ui_ApplyButton);
    lv_obj_set_width(ui_StartStopLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StartStopLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_StartStopLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_StartStopLabel1, "Сохранить");
    lv_obj_set_style_text_font(ui_StartStopLabel1, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_StartStopLabel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_StartStopLabel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_StartStopLabel1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_StartStopLabel1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
}