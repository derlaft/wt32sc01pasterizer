#include "temperature.hpp"
#include "Config.h"
#include "ui.h"
#include "ui_hal.h"
#include "ui_events.hpp"

#include <lvgl.h>
#include <OneWire.h>

OneWire  ds(PIN_PROBE);

void temperature_task_setup() {
  xTaskCreatePinnedToCore(temperature_task, "temp", 4096*2, NULL, tskIDLE_PRIORITY+10, NULL, 1);
}

float last_temp = -127.0;

float temperature_measure() {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[9];
  byte addr[8];
  float celsius;

  ds.reset_search();
#ifdef PROBE_DEBUG
  if (!ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
#endif
    return -127.1;
  }

#ifdef PROBE_DEBUG
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }
#endif

  if (OneWire::crc8(addr, 7) != addr[7]) {
#ifdef PROBE_DEBUG
      Serial.println("CRC is not valid!");
#endif
      return -127.2;
  }
#ifdef PROBE_DEBUG
  Serial.println();
#endif
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
#ifdef PROBE_DEBUG
      Serial.println("  Chip = DS18S20");  // or old DS1820
#endif
      type_s = 1;
      break;
    case 0x28:
#ifdef PROBE_DEBUG
      Serial.println("  Chip = DS18B20");
#endif
      type_s = 0;
      break;
    case 0x22:
#ifdef PROBE_DEBUG
      Serial.println("  Chip = DS1822");
#endif
      type_s = 0;
      break;
    default:
#ifdef PROBE_DEBUG
      Serial.println("Device is not a DS18x20 family device.");
#endif
      return -127.3;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  vTaskDelay(pdMS_TO_TICKS(1000));
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  uint8_t crc = OneWire::crc8(data, 8);
#ifdef PROBE_DEBUG
  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(crc, HEX);
  Serial.println();
#endif

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;

  if (celsius == 85.0 && data[6] == 0xC) {
#ifdef PROBE_DEBUG
    Serial.println("temperature: request lost");
#endif
    return -127.4;
  }


#ifdef PROBE_DEBUG
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.println(" Celsius");
#endif

  return celsius;
}

void temperature_task(void *pvParameter) {
#ifdef DEBUG_SERIAL_TEMPERATURE
  while (1) {
    while (Serial.available () == 0) {
      vTaskDelay(pdMS_TO_TICKS(100));
    }
    float n = Serial.parseFloat();
    if (n != 0) {
      last_temp = n;
      display_temperature(last_temp);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
#else
  while(1) {
    last_temp = temperature_measure();
    display_temperature(last_temp);
    vTaskDelay(pdMS_TO_TICKS(250));
  }
#endif
}

float temperature_get() {
  return last_temp;
}
