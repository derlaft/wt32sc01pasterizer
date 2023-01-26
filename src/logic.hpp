#ifndef _LOGIC_H
#define _LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

void logic_setup();

extern void logic_task(void *pvParameter);
extern void logic_tick();

extern void on_main_switch_pressed();

extern void set_heat(bool value);
extern void set_cool(bool value);
extern void set_mixer(bool value);

extern void logic_sync_ui();
extern void logic_sync_pins();

enum LogicState {
  Idle,
  Heating,
  Pasterizing,
  Cooling,
  Storing,
};
typedef enum LogicState LogicState_t;

#ifdef __cplusplus
}
#endif

#endif
