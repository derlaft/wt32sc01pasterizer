#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h> 
#include <Adafruit_FT6206.h>
#include "esp_freertos_hooks.h"

#include "lvgl.h"
#include "Config.h"
#include "temperature.hpp"
#include "logic.hpp"
#include "ui.h"
#include "ui_hal.h"


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

unsigned long last_series_insert = 0;
/*
static lv_obj_t * label_temp;
lv_obj_t * temp_chart;
lv_chart_series_t * temp_series;
*/

static void display_temperature(float v)
{
    char buf[6];
    sprintf(buf, v < 0 ? "%04.1f" : "!%04.1f", v);
    // lv_label_set_text(label_temp, buf);

    if (millis() - last_series_insert > TEMP_CHART_RESOLUTION) {
      last_series_insert = millis();
      // lv_chart_set_next_value(temp_chart, temp_series, (int)v);
    }
}

void setup()
{

    setupPlatform();

    // setup lgvl hardware
    hal_setup();

    // инициализация интерфейса
    ui_init();
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    
    if (temperature_loop()) {
      float t = temperature_get();
      display_temperature(t);
      //Serial.printf("Temperature: %f", temperature_get());
      //Serial.println();
    }

    delay(1);
}
