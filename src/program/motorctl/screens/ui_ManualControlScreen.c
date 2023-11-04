
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

ui_RegisterPanel = lv_label_create(ui_ManualControlScreen);
lv_obj_set_width( ui_RegisterPanel, lv_pct(80));
lv_obj_set_height( ui_RegisterPanel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_RegisterPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_RegisterPanel,LV_FLEX_FLOW_ROW_REVERSE);
lv_obj_set_flex_align(ui_RegisterPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
lv_label_set_text(ui_RegisterPanel,"");

ui_RegisterSelector = lv_label_create(ui_RegisterPanel);
lv_obj_set_width( ui_RegisterSelector, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_RegisterSelector, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_RegisterSelector, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_RegisterSelector,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_RegisterSelector, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_label_set_text(ui_RegisterSelector,"");

ui_Dec = lv_btn_create(ui_RegisterSelector);
lv_obj_set_width( ui_Dec, 42);
lv_obj_set_height( ui_Dec, 42);
lv_obj_set_align( ui_Dec, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Dec, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Dec, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Dec, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Dec, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_DecLabel = lv_label_create(ui_Dec);
lv_obj_set_width( ui_DecLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_DecLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_DecLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_DecLabel,"-");

ui_Register = lv_spinbox_create(ui_RegisterSelector);
lv_obj_set_width( ui_Register, 70);
lv_obj_set_height( ui_Register, 42);
lv_obj_set_align( ui_Register, LV_ALIGN_CENTER );
lv_spinbox_set_digit_format( ui_Register, 5, 0);
lv_spinbox_set_range( ui_Register, 0,65535 );
lv_spinbox_set_step( ui_Register, round(pow(10, 1 - 1)) );


ui_Inc = lv_btn_create(ui_RegisterSelector);
lv_obj_set_width( ui_Inc, 42);
lv_obj_set_height( ui_Inc, 42);
lv_obj_set_align( ui_Inc, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Inc, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Inc, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Inc, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Inc, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_IncLabel = lv_label_create(ui_Inc);
lv_obj_set_width( ui_IncLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_IncLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_IncLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_IncLabel,"+");

ui_RegisterLabel = lv_label_create(ui_RegisterPanel);
lv_obj_set_width( ui_RegisterLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_RegisterLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_RegisterLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_RegisterLabel,"Регистр");
lv_obj_set_style_text_font(ui_RegisterLabel, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_RegisterPanel1 = lv_label_create(ui_ManualControlScreen);
lv_obj_set_width( ui_RegisterPanel1, lv_pct(80));
lv_obj_set_height( ui_RegisterPanel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_RegisterPanel1, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_RegisterPanel1,LV_FLEX_FLOW_ROW_REVERSE);
lv_obj_set_flex_align(ui_RegisterPanel1, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
lv_label_set_text(ui_RegisterPanel1,"");

ui_ValueSelector = lv_label_create(ui_RegisterPanel1);
lv_obj_set_width( ui_ValueSelector, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ValueSelector, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ValueSelector, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ValueSelector,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_ValueSelector, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_label_set_text(ui_ValueSelector,"");

ui_Dec1 = lv_btn_create(ui_ValueSelector);
lv_obj_set_width( ui_Dec1, 42);
lv_obj_set_height( ui_Dec1, 42);
lv_obj_set_align( ui_Dec1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Dec1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Dec1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Dec1, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Dec1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_DecLabel1 = lv_label_create(ui_Dec1);
lv_obj_set_width( ui_DecLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_DecLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_DecLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_DecLabel1,"-");

ui_Value = lv_spinbox_create(ui_ValueSelector);
lv_obj_set_width( ui_Value, 70);
lv_obj_set_height( ui_Value, 42);
lv_obj_set_align( ui_Value, LV_ALIGN_CENTER );
lv_spinbox_set_digit_format( ui_Value, 5, 0);
lv_spinbox_set_range( ui_Value, 0,65535 );
lv_spinbox_set_step( ui_Value, round(pow(10, 1 - 1)) );


ui_Inc1 = lv_btn_create(ui_ValueSelector);
lv_obj_set_width( ui_Inc1, 42);
lv_obj_set_height( ui_Inc1, 42);
lv_obj_set_align( ui_Inc1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Inc1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Inc1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Inc1, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Inc1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_IncLabel1 = lv_label_create(ui_Inc1);
lv_obj_set_width( ui_IncLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_IncLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_IncLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_IncLabel1,"+");

ui_RegisterLabel1 = lv_label_create(ui_RegisterPanel1);
lv_obj_set_width( ui_RegisterLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_RegisterLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_RegisterLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_RegisterLabel1,"Значение");
lv_obj_set_style_text_font(ui_RegisterLabel1, &ui_font_hack, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ReadWritePanel = lv_label_create(ui_ManualControlScreen);
lv_obj_set_width( ui_ReadWritePanel, lv_pct(100));
lv_obj_set_height( ui_ReadWritePanel, LV_SIZE_CONTENT);   /// 20
lv_obj_set_align( ui_ReadWritePanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ReadWritePanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_ReadWritePanel, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_BETWEEN);
lv_label_set_text(ui_ReadWritePanel,"");

ui_ReadButton1 = lv_btn_create(ui_ReadWritePanel);
lv_obj_set_width( ui_ReadButton1, lv_pct(40));
lv_obj_set_height( ui_ReadButton1, LV_SIZE_CONTENT);   /// 60
lv_obj_set_align( ui_ReadButton1, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_ReadButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ReadButton1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_ReadButton1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_ReadButton1, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ReadButton1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ReadButtonLabel1 = lv_label_create(ui_ReadButton1);
lv_obj_set_width( ui_ReadButtonLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ReadButtonLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ReadButtonLabel1, 0 );
lv_obj_set_y( ui_ReadButtonLabel1, 3 );
lv_obj_set_align( ui_ReadButtonLabel1, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_ReadButtonLabel1,"Чтение");
lv_obj_set_style_text_font(ui_ReadButtonLabel1, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_WriteButton = lv_btn_create(ui_ReadWritePanel);
lv_obj_set_width( ui_WriteButton, lv_pct(40));
lv_obj_set_height( ui_WriteButton, LV_SIZE_CONTENT);   /// 25
lv_obj_set_align( ui_WriteButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_WriteButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_WriteButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_WriteButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_WriteButton, lv_color_hex(0x1499FF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_WriteButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_WriteButtonLabel = lv_label_create(ui_WriteButton);
lv_obj_set_width( ui_WriteButtonLabel, LV_SIZE_CONTENT);  /// 40
lv_obj_set_height( ui_WriteButtonLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_WriteButtonLabel, 0 );
lv_obj_set_y( ui_WriteButtonLabel, 3 );
lv_obj_set_align( ui_WriteButtonLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_WriteButtonLabel,"Запись");
lv_obj_set_style_text_font(ui_WriteButtonLabel, &ui_font_bigfont, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_ReadButton1, ui_event_ReadButton1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WriteButton, ui_event_WriteButton, LV_EVENT_ALL, NULL);

}
