
#include "../ui.h"

void ui_MainControlScreen_screen_init(lv_obj_t *root)
{
    ui_MainControlScreen = lv_obj_create(root);
    lv_obj_clear_flag(ui_MainControlScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_MainControlScreen, LV_FLEX_FLOW_COLUMN_REVERSE);
    lv_obj_set_flex_align(ui_MainControlScreen, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_set_style_border_width(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_MainControlScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_width(ui_MainControlScreen, lv_pct(100));
    lv_obj_set_height(ui_MainControlScreen, lv_pct(100));

    ui_StartStopButton = lv_btn_create(ui_MainControlScreen);
    lv_obj_set_width(ui_StartStopButton, lv_pct(100));
    lv_obj_set_height(ui_StartStopButton, lv_pct(25));
    lv_obj_set_align(ui_StartStopButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_StartStopButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_StartStopButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_StartStopButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_StartStopButton, lv_color_hex(0x007B00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StartStopButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StartStopLabel = lv_label_create(ui_StartStopButton);
    lv_obj_set_width(ui_StartStopLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StartStopLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_StartStopLabel, 0);
    lv_obj_set_y(ui_StartStopLabel, 3);
    lv_obj_set_align(ui_StartStopLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_StartStopLabel, "Ожидание");
    lv_obj_set_style_text_font(ui_StartStopLabel, &ui_font_bigfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Spinner = lv_spinner_create(ui_MainControlScreen, 1000, 90);
    lv_obj_set_width(ui_Spinner, 70);
    lv_obj_set_height(ui_Spinner, 70);
    lv_obj_set_align(ui_Spinner, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Spinner, LV_OBJ_FLAG_CLICKABLE);      /// Flags

    lv_obj_add_event_cb(ui_StartStopButton, ui_event_StartStopButton, LV_EVENT_ALL, NULL);

}
