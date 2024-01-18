
#include "../ui.h"

void ui_MainPanelScreen_screen_init(lv_obj_t *root)
{
ui_MainPanelScreen = lv_obj_create(root);
lv_obj_clear_flag( ui_MainPanelScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

lv_obj_set_style_pad_left(ui_MainPanelScreen, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainPanelScreen, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainPanelScreen, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainPanelScreen, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);

ui_ProgressBar = lv_bar_create(ui_MainPanelScreen);
lv_bar_set_value(ui_ProgressBar,25,LV_ANIM_OFF);
lv_obj_set_height( ui_ProgressBar, 10);
lv_obj_set_width( ui_ProgressBar, lv_pct(100));
lv_obj_set_align( ui_ProgressBar, LV_ALIGN_TOP_MID );
lv_obj_set_style_radius(ui_ProgressBar, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_ProgressBar, 0, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_RootPanel = lv_label_create(ui_MainPanelScreen);
lv_obj_set_width( ui_RootPanel, lv_pct(100));
lv_obj_set_height( ui_RootPanel, lv_pct(100));
lv_obj_set_align( ui_RootPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_RootPanel,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_RootPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_label_set_text(ui_RootPanel,"");
lv_obj_set_style_pad_left(ui_RootPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_RootPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_RootPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_RootPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainButtonPanel = lv_label_create(ui_RootPanel);
lv_obj_set_width( ui_MainButtonPanel, lv_pct(100));
lv_obj_set_height( ui_MainButtonPanel, LV_SIZE_CONTENT);   /// 20
lv_obj_set_x( ui_MainButtonPanel, -1 );
lv_obj_set_y( ui_MainButtonPanel, -1 );
lv_obj_set_align( ui_MainButtonPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_MainButtonPanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_MainButtonPanel, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_BETWEEN);
lv_label_set_text(ui_MainButtonPanel,"");
lv_obj_set_style_pad_left(ui_MainButtonPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_MainButtonPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_MainButtonPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_MainButtonPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_StartStopButton = lv_btn_create(ui_MainButtonPanel);
lv_obj_set_width( ui_StartStopButton, lv_pct(80));
lv_obj_set_height( ui_StartStopButton, LV_SIZE_CONTENT);   /// 60
lv_obj_set_align( ui_StartStopButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_StartStopButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_StartStopButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_StartStopButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_StartStopButton, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_StartStopButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ReadButtonLabel2 = lv_label_create(ui_StartStopButton);
lv_obj_set_width( ui_ReadButtonLabel2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ReadButtonLabel2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ReadButtonLabel2, 0 );
lv_obj_set_y( ui_ReadButtonLabel2, 3 );
lv_obj_set_align( ui_ReadButtonLabel2, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_ReadButtonLabel2,"Старт");
lv_obj_set_style_text_font(ui_ReadButtonLabel2, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

}
