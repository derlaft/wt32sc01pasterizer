#ifndef _LOGIC_H
#define _LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

void logic_setup();

extern void logic_task(void *pvParameter);
extern void logic_tick();

extern void on_cooling_pressed();

extern void logic_sync_ui();
extern void logic_safety_check();

extern void logic_restore_state();
extern void logic_backup_state();

extern void logic_read_serial();

extern bool is_idle();

enum LogicState {
  Unknown = 0,
  Idle = 1,
  Cooling_Start = 2,
  Cooling_Cooling = 3,
  Cooling_Store = 4,
};
typedef enum LogicState LogicState_t;

extern void logic_change_state(LogicState_t n);

#define _BACKUP_STATE_KEY "s"
#define _BACKUP_STATE_PAST_CYCLES "c"

enum Channel {
    Compressor = 0,
    Mixer = 1,
};
typedef enum Channel Channel_t;
#define NUM_CHANNEL 2

static char commands[NUM_CHANNEL*2] = {
    'a', '0',
    'b', '1',
};

#ifdef __cplusplus
}
#endif

#endif
