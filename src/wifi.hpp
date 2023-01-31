#ifndef _WIFI_H
#define _WIFI_H

#include <Arduino.h>
#include "settings.hpp"
#include "Config.h"
#include "ui_events.hpp"
#include "ui_hal.h"
#include "logic.hpp"

#include <WiFi.h>
#include <WiFiClient.h>

extern void wifi_setup();
extern void wifi_task(void *pvParameter);

#endif
