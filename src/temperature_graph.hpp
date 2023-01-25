#ifndef _TEMP_GRAPH_H
#define _TEMP_GRAPH_H

extern void temperature_graph_task_setup();

extern void temperature_graph_task(void *pvParameter);

extern void temperature_graph_add_new_point();

extern bool temperature_graph_enabled;

#endif
