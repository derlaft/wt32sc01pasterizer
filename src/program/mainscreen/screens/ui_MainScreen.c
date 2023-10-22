
#include "../ui.h"

void ui_MainScreen_screen_init(void)
{
    ui_MainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_MainScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_MainScreen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    ui_TopPanel = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_TopPanel, lv_pct(100));
    lv_obj_set_height(ui_TopPanel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TopPanel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_TopPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_TopPanel, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(ui_TopPanel, "");
    lv_obj_set_style_text_color(ui_TopPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TopPanel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_TopPanel, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TopPanel, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TopPanel, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TopPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TopPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TopPanel, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TopPanel, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackButton = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_BackButton, LV_SIZE_CONTENT);   /// 70
    lv_obj_set_height(ui_BackButton, LV_SIZE_CONTENT);    /// 63
    lv_obj_set_x(ui_BackButton, 19);
    lv_obj_set_y(ui_BackButton, -12);
    lv_label_set_text(ui_BackButton, "F");
    lv_obj_add_flag(ui_BackButton, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_BackButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BackButton, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_ManualControlButton, LV_SIZE_CONTENT);   /// 70
    lv_obj_set_height(ui_ManualControlButton, LV_SIZE_CONTENT);    /// 63
    lv_obj_set_x(ui_ManualControlButton, 19);
    lv_obj_set_y(ui_ManualControlButton, -12);
    lv_label_set_text(ui_ManualControlButton, "C");
    lv_obj_add_flag(ui_ManualControlButton, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TempAndWarningGroup = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_TempAndWarningGroup, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempAndWarningGroup, LV_SIZE_CONTENT);    /// 85
    lv_obj_set_align(ui_TempAndWarningGroup, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_TempAndWarningGroup, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_TempAndWarningGroup, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_label_set_text(ui_TempAndWarningGroup, "");

    ui_TemperatureDisplay = lv_label_create(ui_TempAndWarningGroup);
    lv_obj_set_width(ui_TemperatureDisplay, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TemperatureDisplay, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WarningIndicator = lv_label_create(ui_TempAndWarningGroup);
    lv_obj_set_width(ui_WarningIndicator, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WarningIndicator, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_WarningIndicator, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WarningIndicator, "G");
    lv_obj_add_flag(ui_WarningIndicator, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WarningIndicator, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_WarningIndicator, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WarningIndicator, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingsButton = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_SettingsButton, LV_SIZE_CONTENT);   /// 70
    lv_obj_set_height(ui_SettingsButton, LV_SIZE_CONTENT);    /// 63
    lv_obj_set_x(ui_SettingsButton, -19);
    lv_obj_set_y(ui_SettingsButton, -12);
    lv_obj_set_align(ui_SettingsButton, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_SettingsButton, "B");
    lv_obj_add_flag(ui_SettingsButton, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_SettingsButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsButton, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ForwardButton = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_ForwardButton, LV_SIZE_CONTENT);   /// 70
    lv_obj_set_height(ui_ForwardButton, LV_SIZE_CONTENT);    /// 63
    lv_obj_set_x(ui_ForwardButton, -19);
    lv_obj_set_y(ui_ForwardButton, -12);
    lv_obj_set_align(ui_ForwardButton, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_ForwardButton, "E");
    lv_obj_add_flag(ui_ForwardButton, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ForwardButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ForwardButton, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MainPanel = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_MainPanel, lv_pct(96));
    lv_obj_set_flex_grow(ui_MainPanel, 1);
    lv_obj_set_x(ui_MainPanel, -1);
    lv_obj_set_y(ui_MainPanel, -10);
    lv_obj_set_align(ui_MainPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_MainPanel, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_MainPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_clear_flag(ui_MainPanel, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_pad_left(ui_MainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_MainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_MainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_MainPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_BackButton, ui_event_BackButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlButton, ui_event_ManualControlButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WarningIndicator, ui_event_WarningIndicator, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SettingsButton, ui_event_SettingsButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ForwardButton, ui_event_ForwardButton, LV_EVENT_ALL, NULL);

}