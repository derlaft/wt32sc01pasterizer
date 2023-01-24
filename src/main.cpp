#include <Arduino.h>
#include <esp_freertos_hooks.h>
#include <lvgl.h>

#include "Config.h"
#include "temperature.hpp"
#include "temperature_graph.hpp"
#include "logic.hpp"
#include "ui_hal.h"
#include "ui_events.h"
#include "ui.h"

static void on_heat_override(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    LV_UNUSED(obj);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Heater override: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
        digitalWrite(PIN_HEATER, lv_obj_has_state(obj, LV_STATE_CHECKED) ? HIGH : LOW);
    }
}

static void on_cool_override(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    LV_UNUSED(obj);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Cooler override: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
        digitalWrite(PIN_COOLER, lv_obj_has_state(obj, LV_STATE_CHECKED) ? HIGH : LOW);
    }
}

static void on_mixer_override(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    LV_UNUSED(obj);
    if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Mixer override: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
        digitalWrite(PIN_MIXER, lv_obj_has_state(obj, LV_STATE_CHECKED) ? HIGH : LOW);
    }
}

void setup()
{

  // enable serial
  Serial.begin(115200);

  // Configure custom pins
  logic_setup();

  // setup lgvl hardware
  hal_setup();

  // configure temperature readings
  temperature_task_setup();

  // setup temperature graph
  temperature_graph_task_setup();
}


void loop()
{
    vTaskDelay(pdMS_TO_TICKS(100));
}
