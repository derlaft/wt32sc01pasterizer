#pragma once

#include <Arduino.h>
#define INLINE __attribute__((always_inline)) inline

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_interface.h"
#include "esp_private/gdma.h"
#include "esp_pm.h"
#include "hal/dma_types.h"
#include "hal/lcd_hal.h"
#include "hal/lcd_ll.h"

#define GFX_NOT_DEFINED (-1)

class RGBDisplay8048S070
{
public:
  RGBDisplay8048S070();
  void begin(bool psram_fb = true, int32_t speed = GFX_NOT_DEFINED);
  void draw16bitRGBBitmap(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t *bitmap);

protected:
private:
  uint16_t _hsync_polarity = 0;
  uint16_t _hsync_front_porch = 180;
  uint16_t _hsync_pulse_width = 30;
  uint16_t _hsync_back_porch = 16;
  uint16_t _vsync_polarity = 0;
  uint16_t _vsync_front_porch = 12;
  uint16_t _vsync_pulse_width = 13;
  uint16_t _vsync_back_porch = 10;
  uint16_t _pclk_active_neg = 1;
  int32_t _pclk_hz = 14000000L;
  bool _auto_flush = false;

  uint16_t _w = 800;
  uint16_t _h = 480;

  int32_t _speed;
  int8_t _de = 41, _vsync = 40, _hsync = 39, _pclk = 42;
  int8_t _r0 = 14, _r1 = 21, _r2 = 47, _r3 = 48, _r4 = 45;
  int8_t _g0 = 9, _g1 = 46, _g2 = 3, _g3 = 9, _g4 = 16, _g5 = 1;
  int8_t _b0 = 15, _b1 = 7, _b2 = 6, _b3 = 5, _b4 = 4;
  bool _useBigEndian = false;

  esp_lcd_panel_handle_t _panel_handle = NULL;
};

