#ifndef _LOGIC_H
#define _LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

enum LogicState {
  Unknown = 0,
  Idle = 1,

  Fatal = 2,

  Cooling_Start = 3,
  Cooling_Cooling = 4,
  Cooling_Store = 5,

  Mixing_Start = 6,
  Mixing = 7,

  Acid_Start = 8,
  Acid = 9,
  Acid_Done = 10,
};
typedef enum LogicState LogicState_t;

enum Channel {
    Compressor = 0,
    Mixer = 1,
    Compressor2 = 2,
    Compressor3 = 3,
    Compressor4 = 4,
    Compressor5 = 5,
    Compressor6 = 6,
    Compressor7 = 7,
    Compressor8 = 8,
    Compressor9 = 9,
    Compressor10 = 10,
    Compressor11 = 11,
    AcidCleaning = 12,
    BaseCleaning = 13,
};
typedef enum Channel Channel_t;
#define NUM_CHANNEL 14

static char commands[NUM_CHANNEL*2] = {
    'a', '0', // Канал 0   вкл /выкл  Компрессор 
    'b', '1', // Канал 1   вкл /выкл  Мешалка
    '2', 'c', // Канал 2   вкл /выкл  Компрессор
    '3', 'd', // Канал 3   вкл /выкл  Компрессор
    '4', 'g', // Канал 4   вкл /выкл  Компрессор
    '5', 'f', // Канал 5   вкл /выкл  Компрессор
    '6', 'h', // Канал 6   вкл /выкл  Компрессор
    '7', 'j', // Канал 7   вкл /выкл  Компрессор
    '8', 'j', // Канал 8   вкл /выкл  Компрессор
    '9', 'j', // Канал 9   вкл /выкл  Компрессор
    'O', 'o', // Канал 10   вкл /выкл  Компрессор
    'Q', 'q', // Канал 11   вкл /выкл  Компрессор
    '_', 'W', // Запуск встроенной программы промывки кислотой
              // Остановка через reset
    '_', 'w', // Запуск встроенной программы промывки щелочью
              // Остановка через reset
};

// 0xAA55 - код сброса ПЛС и ответ после сброса
static char reset_seq[3] = "\xAA\x55";

void logic_setup();

extern void logic_task(void *pvParameter);
extern void logic_tick();

extern void on_cooling_pressed();
extern void on_mixing_pressed();
extern void on_acid_pressed();

extern void logic_sync_ui();
extern void logic_safety_check();

extern void logic_restore_state();
extern void logic_backup_state();

extern bool logic_write(Channel_t c, bool on);
extern bool logic_reset();
extern bool logic_restore();

extern bool is_idle();


extern void logic_change_state(LogicState_t n);

#define _BACKUP_STATE_KEY "s"
#define _BACKUP_STATE_PAST_CYCLES "c"

#ifdef __cplusplus
}
#endif

#endif
