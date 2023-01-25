#ifndef _LOGIC_H
#define _LOGIC_H

#include "ui_events.hpp"

void logic_setup();

extern void logic_task(void *pvParameter);
extern void logic_tick();

extern void on_main_switch_pressed();


extern void set_heat(bool value);
extern void set_cool(bool value);
extern void set_mixer(bool value, bool gui_lock);

extern void on_heat_override(bool value);
extern void on_cool_override(bool value);
extern void on_mixer_override(bool value);

enum LogicState {
  Idle,
  Heating,
  Pasterizing,
  Cooling,
  Storing,
};

#endif
