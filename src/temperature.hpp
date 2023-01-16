#ifndef TEMP_H
#define TEMP_H

extern void temperature_setup();

extern int temperature_loop();

extern float temperature_get();

extern void display_temperature(float v);

#endif
