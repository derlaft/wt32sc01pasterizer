#ifndef _PAST_UI_COMP_H
#define _PAST_UI_COMP_H

#include "ui.h"

lv_obj_t * ui_comp_get_child(lv_obj_t *comp, uint32_t child_idx);
extern uint32_t LV_EVENT_GET_COMP_CHILD;

// COMPONENT Chart
#define UI_COMP_CHART_CHART 0
#define _UI_COMP_CHART_NUM 1
lv_obj_t *ui_Chart_create(lv_obj_t *comp_parent);

#endif
