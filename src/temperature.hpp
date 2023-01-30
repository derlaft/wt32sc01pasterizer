#ifndef _TEMP_H
#define _TEMP_H

extern void temperature_task_setup();

void temperature_task(void *pvParameter);

extern float temperature_get();

#endif
