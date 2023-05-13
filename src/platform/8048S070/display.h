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


#include "esp32s3/rom/cache.h"
// This function is located in ROM (also see esp_rom/${target}/ld/${target}.rom.ld)
extern int Cache_WriteBack_Addr(uint32_t addr, uint32_t size);

#define MSB_16_SET(var, val)                                 \
    {                                                        \
        (var) = (((val)&0xFF00) >> 8) | (((val)&0xFF) << 8); \
    }

typedef volatile uint32_t *PORTreg_t;

// extract from esp-idf esp_lcd_rgb_panel.c
struct esp_rgb_panel_t
{
  esp_lcd_panel_t base;                                        // Base class of generic lcd panel
  int panel_id;                                                // LCD panel ID
  lcd_hal_context_t hal;                                       // Hal layer object
  size_t data_width;                                           // Number of data lines (e.g. for RGB565, the data width is 16)
  size_t sram_trans_align;                                     // Alignment for framebuffer that allocated in SRAM
  size_t psram_trans_align;                                    // Alignment for framebuffer that allocated in PSRAM
  int disp_gpio_num;                                           // Display control GPIO, which is used to perform action like "disp_off"
  intr_handle_t intr;                                          // LCD peripheral interrupt handle
  esp_pm_lock_handle_t pm_lock;                                // Power management lock
  size_t num_dma_nodes;                                        // Number of DMA descriptors that used to carry the frame buffer
  uint8_t *fb;                                                 // Frame buffer
  size_t fb_size;                                              // Size of frame buffer
  int data_gpio_nums[SOC_LCD_RGB_DATA_WIDTH];                  // GPIOs used for data lines, we keep these GPIOs for action like "invert_color"
  size_t resolution_hz;                                        // Peripheral clock resolution
  esp_lcd_rgb_timing_t timings;                                // RGB timing parameters (e.g. pclk, sync pulse, porch width)
  gdma_channel_handle_t dma_chan;                              // DMA channel handle
  esp_lcd_rgb_panel_frame_trans_done_cb_t on_frame_trans_done; // Callback, invoked after frame trans done
  void *user_ctx;                                              // Reserved user's data of callback functions
  int x_gap;                                                   // Extra gap in x coordinate, it's used when calculate the flush window
  int y_gap;                                                   // Extra gap in y coordinate, it's used when calculate the flush window
  struct
  {
    unsigned int disp_en_level : 1; // The level which can turn on the screen by `disp_gpio_num`
    unsigned int stream_mode : 1;   // If set, the LCD transfers data continuously, otherwise, it stops refreshing the LCD when transaction done
    unsigned int fb_in_psram : 1;   // Whether the frame buffer is in PSRAM
  } flags;
  dma_descriptor_t dma_nodes[]; // DMA descriptor pool of size `num_dma_nodes`
};

class RGBDisplay8048S070
{
public:
  RGBDisplay8048S070();
  void begin(bool psram_fb = true, int32_t speed = GFX_NOT_DEFINED);
  void draw16bitRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
  void flush(void);

  uint16_t *getFramebuffer();

protected:
  uint16_t *_framebuffer;
  size_t _framebuffer_size;
private:
  uint16_t _hsync_polarity = 0;
  uint16_t _hsync_front_porch = 8;
  uint16_t _hsync_pulse_width = 2;
  uint16_t _hsync_back_porch = 43;
  uint16_t _vsync_polarity = 0;
  uint16_t _vsync_front_porch = 8;
  uint16_t _vsync_pulse_width = 2;
  uint16_t _vsync_back_porch = 12;
  uint16_t _pclk_active_neg = 1;
  int32_t _prefer_speed = 16000000;
  bool _auto_flush = false;

  uint16_t _w = 800;
  uint16_t _h = 480;

  int32_t _speed;
  int8_t _de = 41, _vsync = 40, _hsync = 39, _pclk = 42;
  int8_t _r0 = 14, _r1 = 21, _r2 = 47, _r3 = 48, _r4 = 45;
  int8_t _g0 = 9, _g1 = 46, _g2 = 3, _g3 = 9, _g4 = 16, _g5 = 1;
  int8_t _b0 = 15, _b1 = 7, _b2 = 6, _b3 = 5, _b4 = 4;
  bool _useBigEndian = true;

  esp_lcd_panel_handle_t _panel_handle = NULL;
  esp_rgb_panel_t *_rgb_panel;
};

