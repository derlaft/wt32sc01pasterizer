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

  void begin(int32_t speed = GFX_NOT_DEFINED, int8_t dataMode = GFX_NOT_DEFINED);
  void beginWrite();
  void endWrite();
  void writeCommand(uint8_t);
  void write(uint8_t);

protected:
  uint16_t *_framebuffer;
  size_t _framebuffer_size;
private:
  uint16_t _hsync_polarity;
  uint16_t _hsync_front_porch;
  uint16_t _hsync_pulse_width;
  uint16_t _hsync_back_porch;
  uint16_t _vsync_polarity;
  uint16_t _vsync_front_porch;
  uint16_t _vsync_pulse_width;
  uint16_t _vsync_back_porch;
  uint16_t _pclk_active_neg;
  int32_t _prefer_speed;
  bool _auto_flush;

  uint16_t _w;
  uint16_t _h;

  int32_t _speed;
  int8_t _cs, _sck, _sda;
  int8_t _de, _vsync, _hsync, _pclk;
  int8_t _r0, _r1, _r2, _r3, _r4;
  int8_t _g0, _g1, _g2, _g3, _g4, _g5;
  int8_t _b0, _b1, _b2, _b3, _b4;
  bool _useBigEndian;

  PORTreg_t _csPortSet;  ///< PORT register for chip select SET
  PORTreg_t _csPortClr;  ///< PORT register for chip select CLEAR
  PORTreg_t _sckPortSet; ///< PORT register for SCK SET
  PORTreg_t _sckPortClr; ///< PORT register for SCK CLEAR
  PORTreg_t _sdaPortSet; ///< PORT register for SCK SET
  PORTreg_t _sdaPortClr; ///< PORT register for SCK CLEAR
  uint32_t _csPinMask;   ///< Bitmask for chip select
  uint32_t _sckPinMask;  ///< Bitmask for SCK
  uint32_t _sdaPinMask;  ///< Bitmask for SCK

  INLINE void CS_HIGH(void);
  INLINE void CS_LOW(void);
  INLINE void SCK_HIGH(void);
  INLINE void SCK_LOW(void);
  INLINE void SDA_HIGH(void);
  INLINE void SDA_LOW(void);

  esp_lcd_panel_handle_t _panel_handle = NULL;
  esp_rgb_panel_t *_rgb_panel;
};

