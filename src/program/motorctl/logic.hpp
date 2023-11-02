#ifndef _UI_LOGIC_EVENTS_H
#define _UI_LOGIC_EVENTS_H

#include <Arduino.h>

void logic_setup();
void logic_debug_send_write(uint16_t reg, uint16_t value);
void logic_debug_send_read(uint16_t reg);

#endif
