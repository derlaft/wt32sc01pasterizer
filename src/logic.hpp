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
extern void logic_safety_check();

extern void logic_restore_state();
extern void logic_backup_state();

extern bool is_idle();

enum LogicState {
  Unknown = 0,
  Idle = 1,
  Heating = 2,
  Pasterizing = 3,
  Cooling = 4,
  Storing = 5,
};
typedef enum LogicState LogicState_t;

#define _BACKUP_STATE_KEY "s"
#define _BACKUP_STATE_PAST_CYCLES "c"

#ifdef __cplusplus
}
#endif

#endif
