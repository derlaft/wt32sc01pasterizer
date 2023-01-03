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


// platform-related code
TFT_eSPI tft = TFT_eSPI();
Adafruit_FT6206 touchScreen = Adafruit_FT6206();
void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {
#ifdef TOUCH_DEBUG
  Serial.println("#");
#endif

  static uint16_t lastx = 0;
  static uint16_t lasty = 0;

  if (!touchScreen.touched()) {
     data->state = LV_INDEV_STATE_REL;
     data->point.x = lastx;
     data->point.y = lasty;
     return;
  }

  TS_Point touchPos = touchScreen.getPoint();
  data->state = LV_INDEV_STATE_PR;

#ifdef TOUCH_DEBUG
  Serial.println("touch at " + String(touchPos.x) + "x" + String(touchPos.y));
#endif
  auto xpos = touchPos.y;
  auto ypos = TFT_WIDTH - touchPos.x;
#ifdef TOUCH_DEBUG
  Serial.println("mapped to " + String(xpos) + "x" + String(ypos));
#endif

  data->point.x = xpos;
  data->point.y = ypos;
  lastx = xpos;
  lasty = ypos;

  return;
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.dmaWait();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushPixelsDMA(&color_p->full, w * h);

    lv_disp_flush_ready(disp);
}

static void lv_tick_task(void)
{
 lv_tick_inc(portTICK_RATE_MS);
}

void setupPlatform() {

  // Configure custom pins
  logic_setup();

  // configure temperature readings
  temperature_setup();

  // enable serial
  Serial.begin(115200);

  esp_err_t err = esp_register_freertos_tick_hook((esp_freertos_tick_cb_t)lv_tick_task); 
  // TODO: check err

  // Enable Backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL,1);

  // Start TouchScreen
  // requires custom I2C pinout
  Wire.begin(TOUCH_SDA, TOUCH_SCL);
  if (!touchScreen.begin(40)) { 
    Serial.println("Unable to start touchscreen.");
  }

  // Enable TFT
  tft.begin();
  tft.initDMA(false);
  tft.setSwapBytes(true);
  tft.setRotation(1);
  tft.startWrite();
}

/*Change to your screen resolution*/
static const uint16_t screenWidth  = TFT_HEIGHT;
static const uint16_t screenHeight = TFT_WIDTH;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * 10 ];
static lv_color_t buf2[ screenWidth * 10 ];

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

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

void disable_border(struct _lv_obj_t *obj) {
  //lv_obj_set_style_border_opa(obj, LV_OPA_COVER, LV_STATE_DEFAULT);
  //lv_obj_set_style_border_color(obj, lv_palette_main(LV_PALETTE_RED), LV_STATE_DEFAULT);
  lv_obj_set_style_border_opa(obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);

  lv_obj_set_style_pad_left(obj, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(obj, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(obj, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(obj, 0, LV_STATE_DEFAULT);
}

void setup()
{

    setupPlatform();

    String LVGL_Arduino = "lvgl ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    lv_disp_draw_buf_init( &draw_buf, buf1, buf2, screenWidth * 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );

    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /* Initialize the input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_input_read;
    lv_indev_drv_register( &indev_drv );

    // Инициализировать генерированный код
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
