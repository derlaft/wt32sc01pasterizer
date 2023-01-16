#include "temperature.hpp"
#include "Config.h"
#include <lvgl.h>
#include "ui.h"
#include "ui_events.h"
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(PIN_PROBE);
DallasTemperature sensors(&oneWire);
DeviceAddress deviceAddress;

int64_t lastTempRequest = 0;
int64_t delayInMicros = 0;
float lastTemp = 0;

#define BUG_DELAY vTaskDelay(100 / portTICK_PERIOD_MS)

void poll() {
  while (!sensors.isConnected(deviceAddress)) {
#ifdef TEMP_DEBUG
    Serial.println("BUG2");
    BUG_DELAY;
#endif
  }
  sensors.requestTemperaturesByAddress(deviceAddress);
  lastTempRequest = esp_timer_get_time();
}

void temperature_setup() {

  {
    // Configure 18B20 with limited timeout
    uint32_t init_at = millis();
    while (sensors.getDS18Count() == 0 && millis() - init_at < TEMP_PROBE_TIMEOUT_MS) {
      sensors.begin();
      BUG_DELAY;
    }
  }

  // Get address, set resultion
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, PROBE_RESOLUTION);
  // Manually wait for conversion to happen
  sensors.setWaitForConversion(false);

  // Calculate delay time
  delayInMicros = ((int64_t) sensors.millisToWaitForConversion()) * 1000ULL;


#ifdef TEMP_DEBUG
  Serial.println("===");
  Serial.println("Temperature init");

  Serial.print("Device count: ");
  Serial.println(sensors.getDeviceCount());
  Serial.print("DS18Count: ");
  Serial.println(sensors.getDS18Count());
;
  Serial.print("Resolution: ");
  Serial.println(PROBE_RESOLUTION);
  Serial.print("Parasite mode: ");
  Serial.println(sensors.isParasitePowerMode());
  Serial.print("Delay: ");
  Serial.println(delayInMicros);
  Serial.print("Address:");
  for(uint8_t i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
  Serial.print("Supported: ");
  Serial.println(sensors.validFamily(deviceAddress));
  Serial.println("===");
#endif

  // Send first request
  poll();
}

int temperature_loop() {
  if  (esp_timer_get_time() - lastTempRequest > delayInMicros) {

    if (!sensors.isConnected(deviceAddress)) {
      BUG_DELAY;
      return false;
    }

    lastTemp = sensors.getTempC(deviceAddress);

    poll();
    return true;
  }
  return false;
}

float temperature_get() {
  return lastTemp;
}

unsigned long last_series_insert = 0;
int16_t chart_ptr = 0;
int16_t point_count = 10;

void display_temperature(float v)
{

  String stringValue = String(v, 1) + String("°");
  if (v > 0) {
    stringValue = String("+") + stringValue;
  }
  lv_label_set_text(ui_TemperatureDisplay, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay1, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay2, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay3, stringValue.c_str());
  lv_label_set_text(ui_TemperatureDisplay4, stringValue.c_str());

  if (millis() - last_series_insert > TEMP_CHART_RESOLUTION) {
    last_series_insert = millis();
    // lv_chart_set_next_value(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, (int)v);
    lv_coord_t * chart_data = lv_chart_get_y_array(ui_Screen1_Chart1, ui_Screen1_Chart1_Series);
    chart_data[chart_ptr] = (int) (v*10);
    chart_ptr = (chart_ptr+1)%TEMP_CHART_POINT_COUNT;

    lv_chart_set_x_start_point(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, chart_ptr);

    if (chart_ptr > point_count) {
      point_count = chart_ptr;
      lv_chart_set_point_count(ui_Screen1_Chart1, point_count);
      Serial.print("point count: ");
      Serial.println(point_count);
    }

    // lv_chart_set_point_count(ui_Screen1_Chart1, point_count);
    lv_chart_refresh(ui_Screen1_Chart1);
  }
}
