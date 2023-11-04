
#include "../ui.h"

void ui_SettingsScreen_screen_init(lv_obj_t *root)
{
    ui_SettingsScreen = lv_obj_create(root);
    lv_obj_clear_flag(ui_SettingsScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_SettingsScreen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_SettingsScreen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    lv_obj_set_style_pad_left(ui_SettingsScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SettingsScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SettingsScreen, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SettingsScreen, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

}
