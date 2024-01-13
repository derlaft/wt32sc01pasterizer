#ifndef _SKREPPER_APP_H
#define _SKREPPER_APP_H

// Настройки
#define CTL_ADDR 0x1
#define CTRL_REG 0x0

#define DEF_FREQ_BASE 15
#define FREQ_BASE_MIN 0
#define FREQ_BASE_MAX 50

#define DEF_FREQ_DELTA 5
#define FREQ_DELTA_MIN 0
#define FREQ_DELTA_MAX 50

#define MODBUS_FREQ_MULTIPLIER 200

#define MODBUS_FREQ_ADDR 0x1000
#define MODBUS_EN_ADDR 0x2000

#define LOGIC_INTERVAL_MS 200
#define LOGIC_MODBUS_QUEUE_TIMEOUT_MS 100
#define LOGIC_MODBUS_QUEUE_WAIT_MS 10

void app_init();
void settings_setup();
void settings_update();

#endif
