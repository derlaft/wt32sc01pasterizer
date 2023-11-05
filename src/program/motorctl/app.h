#ifndef _MOTORCTL_APP_H
#define _MOTORCTL_APP_H

#include "../shared/settings.h"

// Настройки
#define CTL_ADDR 0x1
#define CTRL_REG 0x0
#define DEF_FREQ_BASE 15
#define DEF_FREQ_DELTA 5

#define MODBUS_FREQ_MULTIPLIER 200
#define MODBUS_FREQ_ADDR 0x1000
#define LOGIC_INTERVAL_MS 200

void app_init();

extern setting_decl freq_base;
extern setting_decl freq_delta;

#endif
