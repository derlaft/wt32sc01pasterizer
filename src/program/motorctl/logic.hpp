#ifndef _UI_LOGIC_EVENTS_H
#define _UI_LOGIC_EVENTS_H

#include <Arduino.h>

enum LogicState {
  Unknown = 0,
  Idle = 1,
  Ativating = 2,

  Freq_Control = 3,
};
typedef enum LogicState LogicState_t;

void logic_setup();
void logic_debug_send_write(uint16_t reg, uint16_t value);
void logic_debug_send_read(uint16_t reg);
void logic_task(void *pvParameter);

#endif
