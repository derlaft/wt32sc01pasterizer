#ifndef _PAST_SETTINGS_H
#define _PAST_SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>
#include "Config.h"
#include "ui_events.hpp"

extern int16_t DRAM_ATTR past_temp_value;
extern int16_t DRAM_ATTR past_time_value;
extern int16_t DRAM_ATTR store_temp_value;

extern void IRAM_ATTR settings_setup();
extern void IRAM_ATTR settings_update();

extern char DRAM_ATTR wifi_ap[128];
extern char DRAM_ATTR wifi_pw[128];

#define _PAST_TEMP_KEY "ptemp"
#define _PAST_TIME_KEY "ptime"
#define _STORE_TEMP_KEY "stemp"
#define _WIFI_AP_KEY "wssid"
#define _WIFI_PW_KEY "wpwd"

#endif
