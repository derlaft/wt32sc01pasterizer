#include <Arduino.h>
#include <esp_freertos_hooks.h>
#include <lvgl.h>

#include "Config.h"
#include "temperature.hpp"
#include "logic.hpp"
#include "ui_hal.h"
#include "ui_events.h"
#include "ui.h"


void setupPlatform() {

  // enable serial
  Serial.begin(115200);

  // Configure custom pins
  logic_setup();

  // configure temperature readings
  temperature_setup();
}


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

    setupPlatform();

    // setup lgvl hardware
    hal_setup();
}

void loop()
{
    if (temperature_loop()) {
      float t = temperature_get();
      display_temperature(t);
    }

    hal_loop();
    delay(1);
}
