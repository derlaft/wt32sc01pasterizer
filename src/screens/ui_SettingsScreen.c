
#include "../ui.h"

void ui_SettingsScreen_screen_init(void)
{
    ui_SettingsScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SettingsScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_SettingsScreen, LV_FLEX_FLOW_COLUMN_REVERSE);
    lv_obj_set_flex_align(ui_SettingsScreen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    ui_SettingsPanel = lv_obj_create(ui_SettingsScreen);
    lv_obj_set_width(ui_SettingsPanel, lv_pct(96));
    lv_obj_set_flex_grow(ui_SettingsPanel, 1);
    lv_obj_set_x(ui_SettingsPanel, -9);
    lv_obj_set_y(ui_SettingsPanel, -19);
    lv_obj_set_align(ui_SettingsPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_SettingsPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_SettingsPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_left(ui_SettingsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsPanel, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_SettingsPanel, 5, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsPanel, 5, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsPanel, 5, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsPanel, 5, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    ui_Setting1Panel = lv_label_create(ui_SettingsPanel);
    lv_obj_set_width(ui_Setting1Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting1Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1Panel, 0);
    lv_obj_set_y(ui_Setting1Panel, 20);
    lv_obj_set_align(ui_Setting1Panel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_Setting1Panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Setting1Panel, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(ui_Setting1Panel, "");
    lv_obj_set_style_text_align(ui_Setting1Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting1Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting1Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting1Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting1Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting1Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1InfoLabel = lv_label_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1InfoLabel, lv_pct(50));
    lv_obj_set_height(ui_Setting1InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1InfoLabel, 15);
    lv_obj_set_y(ui_Setting1InfoLabel, 0);
    lv_obj_set_align(ui_Setting1InfoLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting1InfoLabel, "Температура охлаждения");
    lv_obj_set_style_text_font(ui_Setting1InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting1InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting1InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting1InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting1InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1Decr = lv_btn_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1Decr, 60);
    lv_obj_set_height(ui_Setting1Decr, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Setting1Decr, 20);
    lv_obj_set_y(ui_Setting1Decr, 0);
    lv_obj_set_align(ui_Setting1Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting1Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting1Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting1DecrLabel = lv_label_create(ui_Setting1Decr);
    lv_obj_set_width(ui_Setting1DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting1DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting1DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting1DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting1DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1 = lv_textarea_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1, 80);
    lv_obj_set_height(ui_Setting1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting1, 100);
    lv_obj_set_y(ui_Setting1, 0);
    lv_obj_set_align(ui_Setting1, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting1, 128);
    lv_textarea_set_text(ui_Setting1, "4");
    lv_textarea_set_placeholder_text(ui_Setting1, "Placeholder...");
    lv_obj_clear_flag(ui_Setting1, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting1, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting1Incr = lv_btn_create(ui_Setting1Panel);
    lv_obj_set_width(ui_Setting1Incr, 60);
    lv_obj_set_height(ui_Setting1Incr, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Setting1Incr, 185);
    lv_obj_set_y(ui_Setting1Incr, 0);
    lv_obj_set_align(ui_Setting1Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting1Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting1Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting2IncrLabel = lv_label_create(ui_Setting1Incr);
    lv_obj_set_width(ui_Setting2IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting2IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting2IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting2IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting2IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2Panel = lv_label_create(ui_SettingsPanel);
    lv_obj_set_width(ui_Setting2Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting2Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting2Panel, -1);
    lv_obj_set_y(ui_Setting2Panel, 95);
    lv_obj_set_align(ui_Setting2Panel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_Setting2Panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Setting2Panel, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(ui_Setting2Panel, "");
    lv_obj_set_style_text_align(ui_Setting2Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting2Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Setting2Panel, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Setting2Panel, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting2Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting2Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting2Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting2Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2InfoLabel = lv_label_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2InfoLabel, lv_pct(50));
    lv_obj_set_height(ui_Setting2InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting2InfoLabel, 16);
    lv_obj_set_y(ui_Setting2InfoLabel, -16);
    lv_label_set_text(ui_Setting2InfoLabel,
                      "Время (мин) до перемешивания в режиме  хранения");
    lv_obj_set_style_text_font(ui_Setting2InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting2InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting2InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting2InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting2InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2Decr = lv_btn_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2Decr, 60);
    lv_obj_set_height(ui_Setting2Decr, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Setting2Decr, 20);
    lv_obj_set_y(ui_Setting2Decr, 0);
    lv_obj_set_align(ui_Setting2Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting2Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting2Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting2DecrLabel = lv_label_create(ui_Setting2Decr);
    lv_obj_set_width(ui_Setting2DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting2DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting2DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting2DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting2DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2 = lv_textarea_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2, 80);
    lv_obj_set_height(ui_Setting2, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Setting2, 102);
    lv_obj_set_y(ui_Setting2, 0);
    lv_obj_set_align(ui_Setting2, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting2, 128);
    lv_textarea_set_text(ui_Setting2, "15");
    lv_textarea_set_placeholder_text(ui_Setting2, "Placeholder...");
    lv_obj_clear_flag(ui_Setting2, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting2, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting2Incr = lv_btn_create(ui_Setting2Panel);
    lv_obj_set_width(ui_Setting2Incr, 60);
    lv_obj_set_height(ui_Setting2Incr, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Setting2Incr, 185);
    lv_obj_set_y(ui_Setting2Incr, 0);
    lv_obj_set_align(ui_Setting2Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting2Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting2Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting1IncrLabel = lv_label_create(ui_Setting2Incr);
    lv_obj_set_width(ui_Setting1IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting1IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting1IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting1IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting1IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3Panel = lv_label_create(ui_SettingsPanel);
    lv_obj_set_width(ui_Setting3Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting3Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3Panel, -1);
    lv_obj_set_y(ui_Setting3Panel, 95);
    lv_obj_set_align(ui_Setting3Panel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_Setting3Panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Setting3Panel, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(ui_Setting3Panel, "");
    lv_obj_set_style_text_align(ui_Setting3Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting3Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting3Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting3Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting3Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting3Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3InfoLabel = lv_label_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3InfoLabel, lv_pct(50));
    lv_obj_set_height(ui_Setting3InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3InfoLabel, 15);
    lv_obj_set_y(ui_Setting3InfoLabel, -16);
    lv_label_set_text(ui_Setting3InfoLabel,
                      "Время (мин) перемешивания в режиме хранения");
    lv_obj_set_style_text_font(ui_Setting3InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting3InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting3InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting3InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting3InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3Decr = lv_btn_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3Decr, 60);
    lv_obj_set_height(ui_Setting3Decr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3Decr, 20);
    lv_obj_set_y(ui_Setting3Decr, 0);
    lv_obj_set_align(ui_Setting3Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting3Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting3Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting3DecrLabel = lv_label_create(ui_Setting3Decr);
    lv_obj_set_width(ui_Setting3DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting3DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting3DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting3DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting3DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3 = lv_textarea_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3, 80);
    lv_obj_set_height(ui_Setting3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3, 100);
    lv_obj_set_y(ui_Setting3, 0);
    lv_obj_set_align(ui_Setting3, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting3, 128);
    lv_textarea_set_text(ui_Setting3, "2");
    lv_textarea_set_placeholder_text(ui_Setting3, "Placeholder...");
    lv_obj_clear_flag(ui_Setting3, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting3, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting3Incr = lv_btn_create(ui_Setting3Panel);
    lv_obj_set_width(ui_Setting3Incr, 60);
    lv_obj_set_height(ui_Setting3Incr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting3Incr, 185);
    lv_obj_set_y(ui_Setting3Incr, 0);
    lv_obj_set_align(ui_Setting3Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting3Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting3Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting3IncrLabel = lv_label_create(ui_Setting3Incr);
    lv_obj_set_width(ui_Setting3IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting3IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting3IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting3IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting3IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4Panel = lv_label_create(ui_SettingsPanel);
    lv_obj_set_width(ui_Setting4Panel, lv_pct(100));
    lv_obj_set_height(ui_Setting4Panel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4Panel, -1);
    lv_obj_set_y(ui_Setting4Panel, 95);
    lv_obj_set_align(ui_Setting4Panel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_Setting4Panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Setting4Panel, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(ui_Setting4Panel, "");
    lv_obj_set_style_text_align(ui_Setting4Panel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting4Panel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Setting4Panel, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Setting4Panel, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting4Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting4Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting4Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting4Panel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4InfoLabel = lv_label_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4InfoLabel, lv_pct(50));
    lv_obj_set_height(ui_Setting4InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4InfoLabel, 16);
    lv_obj_set_y(ui_Setting4InfoLabel, -6);
    lv_label_set_text(ui_Setting4InfoLabel, "Задержка (мин) выключения перемешивания");
    lv_obj_set_style_text_font(ui_Setting4InfoLabel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Setting4InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Setting4InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Setting4InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Setting4InfoLabel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4Decr = lv_btn_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4Decr, 60);
    lv_obj_set_height(ui_Setting4Decr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4Decr, 20);
    lv_obj_set_y(ui_Setting4Decr, 0);
    lv_obj_set_align(ui_Setting4Decr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting4Decr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting4Decr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting4DecrLabel = lv_label_create(ui_Setting4Decr);
    lv_obj_set_width(ui_Setting4DecrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting4DecrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting4DecrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting4DecrLabel, "-");
    lv_obj_set_style_text_font(ui_Setting4DecrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4 = lv_textarea_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4, 80);
    lv_obj_set_height(ui_Setting4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4, 102);
    lv_obj_set_y(ui_Setting4, 0);
    lv_obj_set_align(ui_Setting4, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_Setting4, 128);
    lv_textarea_set_text(ui_Setting4, "1");
    lv_textarea_set_placeholder_text(ui_Setting4, "Placeholder...");
    lv_obj_clear_flag(ui_Setting4, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Setting4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Setting4, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Setting4Incr = lv_btn_create(ui_Setting4Panel);
    lv_obj_set_width(ui_Setting4Incr, 60);
    lv_obj_set_height(ui_Setting4Incr, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Setting4Incr, 185);
    lv_obj_set_y(ui_Setting4Incr, 0);
    lv_obj_set_align(ui_Setting4Incr, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Setting4Incr, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Setting4Incr, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Setting4IncrLabel = lv_label_create(ui_Setting4Incr);
    lv_obj_set_width(ui_Setting4IncrLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Setting4IncrLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Setting4IncrLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Setting4IncrLabel, "+");
    lv_obj_set_style_text_font(ui_Setting4IncrLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ApplyButton = lv_btn_create(ui_SettingsPanel);
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

    ui_TopPanel2 = lv_label_create(ui_SettingsScreen);
    lv_obj_set_width(ui_TopPanel2, lv_pct(100));
    lv_obj_set_height(ui_TopPanel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TopPanel2, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TopPanel2, "");
    lv_obj_set_style_text_color(ui_TopPanel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel2, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel2, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel2, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureDisplay2 = lv_label_create(ui_TopPanel2);
    lv_obj_set_width(ui_TemperatureDisplay2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay2, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay2, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay2, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingsButton2 = lv_label_create(ui_TopPanel2);
    lv_obj_set_width(ui_SettingsButton2, 70);
    lv_obj_set_height(ui_SettingsButton2, 63);
    lv_obj_set_x(ui_SettingsButton2, -19);
    lv_obj_set_y(ui_SettingsButton2, -12);
    lv_obj_set_align(ui_SettingsButton2, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_SettingsButton2, "E");
    lv_obj_add_flag(ui_SettingsButton2, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_SettingsButton2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsButton2, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingsButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsButton2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton2 = lv_label_create(ui_TopPanel2);
    lv_obj_set_width(ui_ManualControlButton2, 70);
    lv_obj_set_height(ui_ManualControlButton2, 63);
    lv_obj_set_x(ui_ManualControlButton2, 19);
    lv_obj_set_y(ui_ManualControlButton2, -12);
    lv_label_set_text(ui_ManualControlButton2, "F");
    lv_obj_add_flag(ui_ManualControlButton2, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton2, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Setting1Decr, ui_event_Setting1Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting1Incr, ui_event_Setting1Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting2Decr, ui_event_Setting2Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting2Incr, ui_event_Setting2Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting3Decr, ui_event_Setting3Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting3Incr, ui_event_Setting3Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting4Decr, ui_event_Setting4Decr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Setting4Incr, ui_event_Setting4Incr, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ApplyButton, ui_event_ApplyButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsButton2, ui_event_SettingsButton2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlButton2, ui_event_ManualControlButton2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsScreen, ui_event_SettingsScreen, LV_EVENT_ALL, NULL);

}
