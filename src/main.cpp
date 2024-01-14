#include <Arduino.h>
#include <esp_freertos_hooks.h>
#include <lvgl.h>

#include "Config.h"
#include "settings.hpp"
#include "temperature.hpp"
#include "ui.h"
#include "ui_events.hpp"
#include "ui_hal.h"
#include "wifi.hpp"

#ifdef _APP_MOTORCTL
#include "program/motorctl/logic.hpp"
#endif

#ifdef _APP_SKREPPER
#include "program/skrepper/logic.hpp"
#endif

#ifdef DEBUG_WIPE_PREFERENCES
#include <nvs_flash.h>
#endif

void setup() {

  // early init: enable software serial ASAP
  logic_early_setup();

#ifdef DEBUG_WIPE_PREFERENCES
  nvs_flash_erase(); // erase the NVS partition and...
  nvs_flash_init();  // initialize the NVS partition.
  while (true)
    ;
#endif

  // enable serial
  Serial.begin(115200);

  // setup lgvl hardware
  hal_setup();

  // initialize wifi
  // wifi_setup();

  // read settings
  // _GUI_LOCK(settings_setup());

  // Initialize logic
  logic_setup();

  // configure temperature readings
  // temperature_task_setup();
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(100));
  esp_rom_delay_us(1);
}
