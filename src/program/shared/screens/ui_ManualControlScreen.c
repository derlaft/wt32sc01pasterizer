
#include "../ui.h"

void ui_ManualControlScreen_screen_init(lv_obj_t *root)
{
    ui_ManualControlScreen = lv_obj_create(root);
    lv_obj_clear_flag(ui_ManualControlScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_ManualControlScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_ManualControlScreen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

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

    lv_obj_add_event_cb(ui_ManualControlScreen, ui_event_ManualControlScreen, LV_EVENT_ALL, NULL);

}
