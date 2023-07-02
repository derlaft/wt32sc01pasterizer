
#include "../ui.h"

void ui_WirelessConnectionScreen_screen_init(lv_obj_t *root)
{
    ui_WirelessConnectionScreen = lv_obj_create(root);
    lv_obj_clear_flag(ui_WirelessConnectionScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_WirelessConnectionScreen, LV_FLEX_FLOW_COLUMN_REVERSE);
    lv_obj_set_flex_align(ui_WirelessConnectionScreen, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_START);

    ui_SettingsPanel1 = lv_obj_create(ui_WirelessConnectionScreen);
    lv_obj_set_width(ui_SettingsPanel1, lv_pct(96));
    lv_obj_set_flex_grow(ui_SettingsPanel1, 1);
    lv_obj_set_x(ui_SettingsPanel1, 0);
    lv_obj_set_y(ui_SettingsPanel1, -11);
    lv_obj_set_align(ui_SettingsPanel1, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_SettingsPanel1, LV_FLEX_FLOW_COLUMN_REVERSE);
    lv_obj_set_flex_align(ui_SettingsPanel1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_SettingsPanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsPanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiKeyboard = lv_keyboard_create(ui_SettingsPanel1);
    lv_obj_set_width(ui_WifiKeyboard, lv_pct(100));
    lv_obj_set_flex_grow(ui_WifiKeyboard, 1);
    lv_obj_set_align(ui_WifiKeyboard, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_scrollbar_mode(ui_WifiKeyboard, LV_SCROLLBAR_MODE_OFF);

    ui_WiFiPasswordPanel = lv_label_create(ui_SettingsPanel1);
    lv_obj_set_width(ui_WiFiPasswordPanel, lv_pct(100));
    lv_obj_set_height(ui_WiFiPasswordPanel, LV_SIZE_CONTENT);    /// 40
    lv_obj_set_x(ui_WiFiPasswordPanel, 0);
    lv_obj_set_y(ui_WiFiPasswordPanel, -1);
    lv_obj_set_align(ui_WiFiPasswordPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_WiFiPasswordPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_WiFiPasswordPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_label_set_text(ui_WiFiPasswordPanel, "");
    lv_obj_set_style_text_align(ui_WiFiPasswordPanel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_WiFiPasswordPanel, lv_color_hex(0x0000FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WiFiPasswordPanel, 17, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_WiFiPasswordPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_WiFiPasswordPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_WiFiPasswordPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_WiFiPasswordPanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen3_Label13 = lv_label_create(ui_WiFiPasswordPanel);
    lv_obj_set_height(ui_Screen3_Label13, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_flex_grow(ui_Screen3_Label13, 8);
    lv_obj_set_x(ui_Screen3_Label13, 15);
    lv_obj_set_y(ui_Screen3_Label13, 55);
    lv_label_set_text(ui_Screen3_Label13, "Пароль");
    lv_obj_set_style_text_align(ui_Screen3_Label13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen3_Label13, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen3_Label13, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen3_Label13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen3_Label13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen3_Label13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiPassword = lv_textarea_create(ui_WiFiPasswordPanel);
    lv_obj_set_height(ui_WifiPassword, LV_SIZE_CONTENT);    /// 37
    lv_obj_set_flex_grow(ui_WifiPassword, 15);
    lv_obj_set_x(ui_WifiPassword, -10);
    lv_obj_set_y(ui_WifiPassword, 60);
    lv_obj_set_align(ui_WifiPassword, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_max_length(ui_WifiPassword, 128);
    lv_textarea_set_one_line(ui_WifiPassword, true);
    lv_textarea_set_password_mode(ui_WifiPassword, true);
    lv_obj_clear_flag(ui_WifiPassword, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_scrollbar_mode(ui_WifiPassword, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(ui_WifiPassword, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WiFINamePanel = lv_label_create(ui_SettingsPanel1);
    lv_obj_set_width(ui_WiFINamePanel, lv_pct(100));
    lv_obj_set_height(ui_WiFINamePanel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WiFINamePanel, 0);
    lv_obj_set_y(ui_WiFINamePanel, -2);
    lv_obj_set_align(ui_WiFINamePanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_WiFINamePanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_WiFINamePanel, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_label_set_text(ui_WiFINamePanel, "");
    lv_obj_set_style_pad_left(ui_WiFINamePanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_WiFINamePanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_WiFINamePanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_WiFINamePanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen3_Label14 = lv_label_create(ui_WiFINamePanel);
    lv_obj_set_height(ui_Screen3_Label14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_flex_grow(ui_Screen3_Label14, 8);
    lv_label_set_text(ui_Screen3_Label14, "Точка доступа");
    lv_obj_set_style_text_align(ui_Screen3_Label14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Screen3_Label14, &ui_font_hack, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Screen3_Label14, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Screen3_Label14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Screen3_Label14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Screen3_Label14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiName = lv_textarea_create(ui_WiFINamePanel);
    lv_obj_set_height(ui_WifiName, LV_SIZE_CONTENT);    /// 37
    lv_obj_set_flex_grow(ui_WifiName, 15);
    lv_obj_set_x(ui_WifiName, -10);
    lv_obj_set_y(ui_WifiName, 10);
    lv_obj_set_align(ui_WifiName, LV_ALIGN_CENTER);
    lv_textarea_set_max_length(ui_WifiName, 128);
    lv_textarea_set_one_line(ui_WifiName, true);
    lv_obj_clear_flag(ui_WifiName, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_scrollbar_mode(ui_WifiName, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(ui_WifiName, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_keyboard_set_textarea(ui_WifiKeyboard, ui_WifiName);
    lv_obj_add_event_cb(ui_WifiKeyboard, ui_event_WifiKeyboard, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiPassword, ui_event_WifiPassword, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiName, ui_event_WifiName, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WirelessConnectionScreen, ui_event_WirelessConnectionScreen, LV_EVENT_ALL, NULL);

}
