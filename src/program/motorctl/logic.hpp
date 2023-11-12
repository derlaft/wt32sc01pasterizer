#ifndef _UI_LOGIC_EVENTS_H
#define _UI_LOGIC_EVENTS_H

#include <Arduino.h>

#ifdef LOGIC_DEBUG
#define _DEBUG(...) { \
    char buf[256]; \
    snprintf(buf, sizeof(buf), __VA_ARGS__); \
    Serial.println(buf); \
};
#else
#define _DEBUG(...) {}
#endif

enum LogicState {
  Unknown = 0,
  Idle = 1,
  Activating = 2,
  Freq_Control = 3,
};
typedef enum LogicState LogicState_t;

enum LogicEvent {
	// normal interrupt
	Interrupt = (1 << 0),
	// start/stop button pressed
	StartStopProg = (1 << 1),
	// "Any" selector
	Any = 0b11,
};
typedef enum LogicEvent LogicEvent_t;

typedef void (*lambda_t)();
struct LambdaRequest {
	lambda_t lambda;
};

void logic_setup();
void logic_debug_send_write(uint16_t reg, uint16_t value);
void logic_debug_send_read(uint16_t reg);
void logic_task(void *pvParameter);

void logic_sync_ui();

void logic_interrupt(LogicEvent_t evt);

void logic_modbus_send(lambda_t req);
void logic_modbus_task(void *pvParameter);
void logic_modbus_on_cb();


#endif
