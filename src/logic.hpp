#ifndef _LOGIC_H
#define _LOGIC_H

#include "ui_events.hpp"

void logic_setup();

extern void logic_task(void *pvParameter);


enum LogicState {
  Idle,
  Heating,
  Pasterizing,
  Cooling,
  Storing,
};

#endif
