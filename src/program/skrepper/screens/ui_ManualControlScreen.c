
#include "../ui.h"

void ui_ManualControlScreen_screen_init(lv_obj_t *root)
{
ui_ManualControlScreen = lv_obj_create(root);
lv_obj_clear_flag( ui_ManualControlScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_flex_flow(ui_ManualControlScreen,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_ManualControlScreen, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
lv_obj_set_style_border_width(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_ofs_x(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_ofs_y(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_ManualControlScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);


}
