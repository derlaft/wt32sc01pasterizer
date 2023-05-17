
#include "../ui.h"

void ui_ManualControlScreen_screen_init(void)
{
    ui_ManualControlScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ManualControlScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_ManualControlScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_ManualControlScreen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    ui_TopPanel1 = lv_label_create(ui_ManualControlScreen);
    lv_obj_set_width(ui_TopPanel1, lv_pct(100));
    lv_obj_set_height(ui_TopPanel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TopPanel1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TopPanel1, "");
    lv_obj_set_style_text_color(ui_TopPanel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel1, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel1, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel1, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureDisplay1 = lv_label_create(ui_TopPanel1);
    lv_obj_set_width(ui_TemperatureDisplay1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay1, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay1, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay1, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton1 = lv_label_create(ui_TopPanel1);
    lv_obj_set_width(ui_ManualControlButton1, 70);
    lv_obj_set_height(ui_ManualControlButton1, 63);
    lv_obj_set_x(ui_ManualControlButton1, 19);
    lv_obj_set_y(ui_ManualControlButton1, -12);
    lv_label_set_text(ui_ManualControlButton1, "F");
    lv_obj_add_flag(ui_ManualControlButton1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton1, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MainScreenPanel = lv_obj_create(ui_ManualControlScreen);
    lv_obj_set_width(ui_MainScreenPanel, lv_pct(96));
    lv_obj_set_flex_grow(ui_MainScreenPanel, 1);
    lv_obj_set_x(ui_MainScreenPanel, 0);
    lv_obj_set_y(ui_MainScreenPanel, -10);
    lv_obj_set_align(ui_MainScreenPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_MainScreenPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_MainScreenPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ManualControlButton1, ui_event_ManualControlButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlScreen, ui_event_ManualControlScreen, LV_EVENT_ALL, NULL);

}
