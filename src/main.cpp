#include <Arduino.h>
#include <esp_freertos_hooks.h>
#include <lvgl.h>

#include "Config.h"
#include "temperature.hpp"
#include "temperature_graph.hpp"
#include "ui_events.hpp"
#include "ui_hal.h"
#include "ui.h"
#include "logic.hpp"
#include "settings.hpp"

#ifdef DEBUG_WIPE_PREFERENCES
#include <nvs_flash.h>
#endif

void setup()
{

#ifdef DEBUG_WIPE_PREFERENCES
  nvs_flash_erase(); // erase the NVS partition and...
  nvs_flash_init(); // initialize the NVS partition.
  while(true);
#endif

  // enable serial
  Serial.begin(115200);

  // setup lgvl hardware
  hal_setup();

  // read settings
  _GUI_LOCK(settings_setup());

  // Initialize logic
  logic_setup();

  // configure temperature readings
  temperature_task_setup();

  // setup temperature graph
  temperature_graph_task_setup();
}


void loop()
{
    vTaskDelay(pdMS_TO_TICKS(100));
}
