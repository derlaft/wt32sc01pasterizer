#ifndef _UI_LOGIC_EVENTS_H
#define _UI_LOGIC_EVENTS_H

#include <Arduino.h>

#ifdef LOGIC_DEBUG
#define _DEBUG(...)                                                            \
  {                                                                            \
    char buf[256];                                                             \
    snprintf(buf, sizeof(buf), __VA_ARGS__);                                   \
    Serial.println(buf);                                                       \
  };
#else
#define _DEBUG(...)                                                            \
  {}
#endif

enum LogicState {
  Unknown = 0,
  Startup = 1,
  Forward = 2,
  SwitchPause = 3,
  Backward = 4,
  Wait = 5,
};
typedef enum LogicState LogicState_t;

enum LogicEvent {
  // normal interrupt
  Interrupt = (1 << 0),
  // manual control request
  ManualControl = (1 << 1),
  // "Any" selector
  Any = 0b11,
};
typedef enum LogicEvent LogicEvent_t;

enum Channel {
  MotorFordward = 0,
  MotorBackward = 1,
};
typedef enum Channel Channel_t;
#define NUM_CHANNEL 12

static char commands[NUM_CHANNEL * 2] = {
    'a', '0', // Канал 0   вкл /выкл  Мотор вперед
    'b', '1', // Канал 1   вкл /выкл  Мотор назад
    'c', '2', // Канал 2   вкл /выкл
    'd', '3', // Канал 3   вкл /выкл
    'g', '4', // Канал 4   вкл /выкл
    'f', '5', // Канал 5   вкл /выкл
    'h', '6', // Канал 6   вкл /выкл
    'j', '7', // Канал 7   вкл /выкл
    'k', '8', // Канал 8   вкл /выкл
    'l', '9', // Канал 9   вкл /выкл
    'o', 'O', // Канал 10  вкл /выкл
    'q', 'Q', // Канал 11  вкл /выкл
};

// 0xAA55 - код сброса ПЛС и ответ после сброса
static char reset_seq[3] = "\xAA\x55";

typedef void (*lambda_t)();
struct LambdaRequest {
  lambda_t lambda;
};
void logic_early_setup();
void logic_setup();
void logic_debug_send_write(uint16_t reg, uint16_t value);
void logic_debug_send_read(uint16_t reg);
void logic_task(void *pvParameter);
void logic_tick(EventBits_t uxBits);
bool logic_send_changed();
void logic_flip_delayed(Channel_t c);

void logic_sync_ui();

void logic_interrupt(LogicEvent_t evt);

bool logic_write(Channel_t c, bool on);
bool logic_reset();
bool logic_restore();

#endif
