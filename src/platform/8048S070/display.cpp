#include "display.h"

RGBDisplay8048S070:: RGBDisplay8048S070() {

}

void RGBDisplay8048S070::begin(bool psram_fb, int32_t speed)
{
  if (speed == GFX_NOT_DEFINED)
  {
#ifdef CONFIG_SPIRAM_MODE_QUAD
    _speed = 6000000L;
#else
    _speed = 12000000L;
#endif
  }
  else
  {
    _speed = speed;
  }

  _framebuffer = getFramebuffer();
  _framebuffer_size = _w * _h * 2;
}

uint16_t *RGBDisplay8048S070::getFramebuffer() {

  esp_lcd_rgb_panel_config_t *_panel_config = (esp_lcd_rgb_panel_config_t *)heap_caps_calloc(1, sizeof(esp_lcd_rgb_panel_config_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);

  _panel_config->clk_src = LCD_CLK_SRC_PLL160M;

  _panel_config->timings.pclk_hz = (_prefer_speed == GFX_NOT_DEFINED) ? _speed : _prefer_speed;
  _panel_config->timings.h_res = _w;
  _panel_config->timings.v_res = _h;
  // The following parameters should refer to LCD spec
  _panel_config->timings.hsync_pulse_width = _hsync_pulse_width;
  _panel_config->timings.hsync_back_porch = _hsync_back_porch;
  _panel_config->timings.hsync_front_porch = _hsync_front_porch;
  _panel_config->timings.vsync_pulse_width = _vsync_pulse_width;
  _panel_config->timings.vsync_back_porch = _vsync_back_porch;
  _panel_config->timings.vsync_front_porch = _vsync_front_porch;
  _panel_config->timings.flags.hsync_idle_low = (_hsync_polarity == 0) ? 1 : 0;
  _panel_config->timings.flags.vsync_idle_low = (_vsync_polarity == 0) ? 1 : 0;
  _panel_config->timings.flags.de_idle_high = 0;
  _panel_config->timings.flags.pclk_active_neg = _pclk_active_neg;
  _panel_config->timings.flags.pclk_idle_high = 0;

  _panel_config->data_width = 16; // RGB565 in parallel mode, thus 16bit in width
  _panel_config->sram_trans_align = 8;
  _panel_config->psram_trans_align = 64;
  _panel_config->hsync_gpio_num = _hsync;
  _panel_config->vsync_gpio_num = _vsync;
  _panel_config->de_gpio_num = _de;
  _panel_config->pclk_gpio_num = _pclk;

  if (_useBigEndian)
  {
    _panel_config->data_gpio_nums[0] = _g3;
    _panel_config->data_gpio_nums[1] = _g4;
    _panel_config->data_gpio_nums[2] = _g5;
    _panel_config->data_gpio_nums[3] = _r0;
    _panel_config->data_gpio_nums[4] = _r1;
    _panel_config->data_gpio_nums[5] = _r2;
    _panel_config->data_gpio_nums[6] = _r3;
    _panel_config->data_gpio_nums[7] = _r4;
    _panel_config->data_gpio_nums[8] = _b0;
    _panel_config->data_gpio_nums[9] = _b1;
    _panel_config->data_gpio_nums[10] = _b2;
    _panel_config->data_gpio_nums[11] = _b3;
    _panel_config->data_gpio_nums[12] = _b4;
    _panel_config->data_gpio_nums[13] = _g0;
    _panel_config->data_gpio_nums[14] = _g1;
    _panel_config->data_gpio_nums[15] = _g2;
  }
  else
  {
    _panel_config->data_gpio_nums[0] = _b0;
    _panel_config->data_gpio_nums[1] = _b1;
    _panel_config->data_gpio_nums[2] = _b2;
    _panel_config->data_gpio_nums[3] = _b3;
    _panel_config->data_gpio_nums[4] = _b4;
    _panel_config->data_gpio_nums[5] = _g0;
    _panel_config->data_gpio_nums[6] = _g1;
    _panel_config->data_gpio_nums[7] = _g2;
    _panel_config->data_gpio_nums[8] = _g3;
    _panel_config->data_gpio_nums[9] = _g4;
    _panel_config->data_gpio_nums[10] = _g5;
    _panel_config->data_gpio_nums[11] = _r0;
    _panel_config->data_gpio_nums[12] = _r1;
    _panel_config->data_gpio_nums[13] = _r2;
    _panel_config->data_gpio_nums[14] = _r3;
    _panel_config->data_gpio_nums[15] = _r4;
  }

  _panel_config->disp_gpio_num = GPIO_NUM_NC;

  _panel_config->flags.disp_active_low = 0;
  _panel_config->flags.relax_on_idle = 0;
  _panel_config->flags.fb_in_psram = 1;

  ESP_ERROR_CHECK(esp_lcd_new_rgb_panel(_panel_config, &_panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_reset(_panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_init(_panel_handle));

  uint16_t color = random(0xffff);
  ESP_ERROR_CHECK(_panel_handle->draw_bitmap(_panel_handle, 0, 0, 1, 1, &color));

  _rgb_panel = __containerof(_panel_handle, esp_rgb_panel_t, base);

  //auto _framebuffer_size = _w * _h * 2;
  //Cache_WriteBack_Addr((uint32_t)_rgb_panel->fb, _framebuffer_size);

  return (uint16_t *)_rgb_panel->fb;
}

void RGBDisplay8048S070::draw16bitRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
{
    auto _max_x = _w;
    auto _max_y = _h;

    if (
        ((x + w - 1) < 0) || // Outside left
        ((y + h - 1) < 0) || // Outside top
        (x > _max_x) ||      // Outside right
        (y > _max_y)         // Outside bottom
    )
    {
        return;
    }
    else
    {
        int16_t xskip = 0;
        if ((y + h - 1) > _max_y)
        {
            h -= (y + h - 1) - _max_y;
        }
        if (y < 0)
        {
            bitmap -= y * w;
            h += y;
            y = 0;
        }
        if ((x + w - 1) > _max_x)
        {
            xskip = (x + w - 1) - _max_x;
            w -= xskip;
        }
        if (x < 0)
        {
            bitmap -= x;
            xskip -= x;
            w += x;
            x = 0;
        }
        uint16_t *row = _framebuffer;
        row += y * _w;
        uint32_t cachePos = (uint32_t)row;
        row += x;
        uint16_t color;
        for (int j = 0; j < h; j++)
        {
            for (int i = 0; i < w; i++)
            {
                color = *bitmap++;
                MSB_16_SET(row[i], color);
            }
            bitmap += xskip;
            row += _w;
        }
        if (_auto_flush)
        {
            Cache_WriteBack_Addr(cachePos, _w* h * 2);
        }
    }
}

void RGBDisplay8048S070::flush() {
    Cache_WriteBack_Addr((uint32_t)_framebuffer, _framebuffer_size);
}
