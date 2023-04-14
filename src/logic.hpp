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

};
typedef enum LogicState LogicState_t;

enum Channel {
    Compressor = 0,
    Mixer = 1,
};
typedef enum Channel Channel_t;
#define NUM_CHANNEL 2

/* Встроенные команды 
'0' 'a' ;Канал 0   вкл /выкл  Компрессор 
'1' 'b' ;Канал 1   вкл /выкл  Мешалка
'2' 'c' ;Канал 2   вкл /выкл  Компрессор
'3' 'd' ;Канал 3   вкл /выкл  Компрессор
'4' 'g' ;Канал 4   вкл /выкл  Компрессор
'5' 'f' ;Канал 5   вкл /выкл  Компрессор
'6' 'h' ;Канал 6   вкл /выкл  Компрессор
'7' 'j' ;Канал 7   вкл /выкл  Компрессор
'8' 'j' ;Канал 8   вкл /выкл  Компрессор
'9' 'j' ;Канал 9   вкл /выкл  Компрессор
'O' 'o' ;Канал 10   вкл /выкл  Компрессор
'Q' 'q' ;Канал 11   вкл /выкл  Компрессор
'W'             ;Запуск встроенной программы промывки кислотой
'w'             ;Запуск встроенной программы промывки кислотой
'F'             ;Запуск встроенной программы охлаждения выход - '0' 
'P'             ;Запуск встроенной программы полоскания
0xAA55 - код сброса ПЛС и ответ после сброса
*/
static char commands[NUM_CHANNEL*2] = {
    'a', '0',
    'b', '1',
};

static char reset_seq[3] = "\xAA\x55";

void logic_setup();

extern void logic_task(void *pvParameter);
extern void logic_tick();

extern void on_cooling_pressed();

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
