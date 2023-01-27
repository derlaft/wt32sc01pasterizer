#ifndef _PAST_SETTINGS_H
#define _PAST_SETTINGS_H

#include <Arduino.h>
#include <Preferences.h>
#include "Config.h"
#include "ui_events.hpp"

extern int16_t past_temp_value;
extern int16_t past_time_value;
extern int16_t store_temp_value;

extern void settings_setup();
extern void settings_update();

extern char wifi_ap[128];
extern char wifi_pw[128];

#define _PAST_TEMP_KEY "past_temp"
#define _PAST_TIME_KEY "past_time"
#define _STORE_TEMP_KEY "store_temp"
#define _WIFI_AP_KEY "wifi_ap"
#define _WIFI_PW_KEY "wifi_pw"

#endif
