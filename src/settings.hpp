#ifndef _PAST_SETTINGS_H
#define _PAST_SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>
#include "Config.h"
#include "ui_events.hpp"

extern int16_t DRAM_ATTR cool_temp_value;
extern int16_t DRAM_ATTR before_mix_value;
extern int16_t DRAM_ATTR mix_value;
extern int16_t DRAM_ATTR mix_delay_value;

extern void IRAM_ATTR settings_setup();
extern void IRAM_ATTR settings_update();

extern char DRAM_ATTR wifi_ap[128];
extern char DRAM_ATTR wifi_pw[128];

#define _COOL_TEMP_KEY "cool_temp"
#define _BEFORE_MIX_KEY "before_mix"
#define _MIX_KEY "mix"
#define _MIX_DELAY_KEY "mix_delay"

#define _WIFI_AP_KEY "wssid"
#define _WIFI_PW_KEY "wpwd"

#endif
