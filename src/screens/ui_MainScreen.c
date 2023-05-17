
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

    ui_TemperatureDisplay = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_TemperatureDisplay, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureDisplay, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TemperatureDisplay, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_TemperatureDisplay, "+125°");
    lv_obj_set_style_text_align(ui_TemperatureDisplay, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureDisplay, &ui_font_tempfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingsButton1 = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_SettingsButton1, 70);
    lv_obj_set_height(ui_SettingsButton1, 63);
    lv_obj_set_x(ui_SettingsButton1, -19);
    lv_obj_set_y(ui_SettingsButton1, -12);
    lv_obj_set_align(ui_SettingsButton1, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_SettingsButton1, "B");
    lv_obj_add_flag(ui_SettingsButton1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_SettingsButton1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SettingsButton1, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SettingsButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsButton1, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlButton = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_ManualControlButton, 70);
    lv_obj_set_height(ui_ManualControlButton, 63);
    lv_obj_set_x(ui_ManualControlButton, 19);
    lv_obj_set_y(ui_ManualControlButton, -12);
    lv_label_set_text(ui_ManualControlButton, "C");
    lv_obj_add_flag(ui_ManualControlButton, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_align(ui_ManualControlButton, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ManualControlButton, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ManualControlButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlButton, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WarningIndicator = lv_label_create(ui_TopPanel);
    lv_obj_set_width(ui_WarningIndicator, 70);
    lv_obj_set_height(ui_WarningIndicator, 63);
    lv_obj_set_x(ui_WarningIndicator, -80);
    lv_obj_set_y(ui_WarningIndicator, -12);
    lv_obj_set_align(ui_WarningIndicator, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_WarningIndicator, "G");
    lv_obj_add_flag(ui_WarningIndicator, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_WarningIndicator, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WarningIndicator, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_WarningIndicator, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WarningIndicator, &ui_font_symbols, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_WarningIndicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_WarningIndicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_WarningIndicator, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_WarningIndicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ManualControlPanel = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_ManualControlPanel, lv_pct(96));
    lv_obj_set_flex_grow(ui_ManualControlPanel, 1);
    lv_obj_set_x(ui_ManualControlPanel, 0);
    lv_obj_set_y(ui_ManualControlPanel, -10);
    lv_obj_set_align(ui_ManualControlPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_ManualControlPanel, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_ManualControlPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_clear_flag(ui_ManualControlPanel,
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_pad_left(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ManualControlPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CoolingButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_CoolingButton, lv_pct(99));
    lv_obj_set_height(ui_CoolingButton, lv_pct(24));
    lv_obj_set_x(ui_CoolingButton, 0);
    lv_obj_set_y(ui_CoolingButton, -180);
    lv_obj_set_align(ui_CoolingButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CoolingButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CoolingButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_CoolingButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CoolingButtonLabel = lv_label_create(ui_CoolingButton);
    lv_obj_set_width(ui_CoolingButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CoolingButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_CoolingButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CoolingButtonLabel, "Охлаждение");
    lv_obj_set_style_text_font(ui_CoolingButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MixingButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_MixingButton, lv_pct(99));
    lv_obj_set_height(ui_MixingButton, lv_pct(24));
    lv_obj_set_x(ui_MixingButton, -2);
    lv_obj_set_y(ui_MixingButton, -208);
    lv_obj_set_align(ui_MixingButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MixingButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MixingButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_MixingButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MixingButtonLabel = lv_label_create(ui_MixingButton);
    lv_obj_set_width(ui_MixingButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MixingButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MixingButtonLabel, 0);
    lv_obj_set_y(ui_MixingButtonLabel, 1);
    lv_obj_set_align(ui_MixingButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MixingButtonLabel, "Перемешивание");
    lv_obj_set_style_text_font(ui_MixingButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningAcidButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_CleaningAcidButton, lv_pct(99));
    lv_obj_set_height(ui_CleaningAcidButton, lv_pct(24));
    lv_obj_set_align(ui_CleaningAcidButton, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_CleaningAcidButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CleaningAcidButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_CleaningAcidButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningAcidButtonLabel = lv_label_create(ui_CleaningAcidButton);
    lv_obj_set_width(ui_CleaningAcidButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CleaningAcidButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CleaningAcidButtonLabel, 0);
    lv_obj_set_y(ui_CleaningAcidButtonLabel, 1);
    lv_obj_set_align(ui_CleaningAcidButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_CleaningAcidButtonLabel, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_CleaningAcidButtonLabel, "Промывка кислотой");
    lv_obj_set_style_text_font(ui_CleaningAcidButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningBaseButton = lv_btn_create(ui_ManualControlPanel);
    lv_obj_set_width(ui_CleaningBaseButton, lv_pct(99));
    lv_obj_set_height(ui_CleaningBaseButton, lv_pct(24));
    lv_obj_set_x(ui_CleaningBaseButton, 1);
    lv_obj_set_y(ui_CleaningBaseButton, -40);
    lv_obj_set_align(ui_CleaningBaseButton, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_CleaningBaseButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CleaningBaseButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_CleaningBaseButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CleaningBaseButtonLabel = lv_label_create(ui_CleaningBaseButton);
    lv_obj_set_width(ui_CleaningBaseButtonLabel, LV_SIZE_CONTENT);   /// 200
    lv_obj_set_height(ui_CleaningBaseButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CleaningBaseButtonLabel, 0);
    lv_obj_set_y(ui_CleaningBaseButtonLabel, 1);
    lv_obj_set_align(ui_CleaningBaseButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_CleaningBaseButtonLabel, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(ui_CleaningBaseButtonLabel, "Промывка щелочью");
    lv_obj_set_style_text_font(ui_CleaningBaseButtonLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_SettingsButton1, ui_event_SettingsButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ManualControlButton, ui_event_ManualControlButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WarningIndicator, ui_event_WarningIndicator, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CoolingButton, ui_event_CoolingButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MixingButton, ui_event_MixingButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CleaningAcidButton, ui_event_CleaningAcidButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CleaningBaseButton, ui_event_CleaningBaseButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MainScreen, ui_event_MainScreen, LV_EVENT_ALL, NULL);

}
