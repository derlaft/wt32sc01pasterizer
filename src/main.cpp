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

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

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
  tft.setRotation(1);
}

/*Change to your screen resolution*/
static const uint16_t screenWidth  = TFT_HEIGHT;
static const uint16_t screenHeight = TFT_WIDTH;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

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

static lv_obj_t * meter;
static lv_meter_indicator_t * indic;

static void display_temperature(int32_t v)
{
    lv_meter_set_indicator_value(meter, indic, v);
}

void setup()
{

    setupPlatform();

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

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

    // управление нагревом
    lv_obj_t * sw_heat;
    sw_heat = lv_switch_create(lv_scr_act());
    lv_obj_add_event_cb(sw_heat, on_heat_override, LV_EVENT_ALL, NULL);
    lv_obj_align(sw_heat, LV_ALIGN_TOP_LEFT, 40, 40);
    
    lv_obj_t * lbl_heat = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_align(lbl_heat, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(lbl_heat, LV_ALIGN_TOP_LEFT, 100, 40);
    lv_label_set_text(lbl_heat, "TEST Нагреватель");

    // управление охлаждением
    lv_obj_t * sw_cool;
    sw_cool = lv_switch_create(lv_scr_act());
    lv_obj_add_event_cb(sw_cool, on_cool_override, LV_EVENT_ALL, NULL);
    lv_obj_align(sw_cool, LV_ALIGN_TOP_LEFT, 40, 80);
    
    lv_obj_t * lbl_cool = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_align(lbl_cool, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(lbl_cool, LV_ALIGN_TOP_LEFT, 100, 80);
    lv_label_set_text(lbl_cool, "TEST Охлаждение");

    // управление перемешиванием
    lv_obj_t * sw_mixer;
    sw_mixer = lv_switch_create(lv_scr_act());
    lv_obj_add_event_cb(sw_mixer, on_mixer_override, LV_EVENT_ALL, NULL);
    lv_obj_align(sw_mixer, LV_ALIGN_TOP_LEFT, 40, 120);
    
    lv_obj_t * lbl_mixer = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_align(lbl_mixer, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(lbl_mixer, LV_ALIGN_TOP_LEFT, 100, 120);
    lv_label_set_text(lbl_mixer, "TEST Перемешивание");

    // индикатор температуры
    //
    // scale
    meter = lv_meter_create(lv_scr_act());
    lv_obj_set_size(meter, 200, 200);
    lv_obj_set_align(meter, LV_ALIGN_TOP_RIGHT);

    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);


    // синяя зона
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    // отметки в синей зоне
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 0);
    lv_meter_set_indicator_end_value(meter, indic, 20);

    // красная линия
    indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    // отметки в красной зоне
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
    lv_meter_set_indicator_start_value(meter, indic, 80);
    lv_meter_set_indicator_end_value(meter, indic, 100);

    // стрелка
    indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

    // Установить глобальный шрифт
    lv_obj_set_style_text_font(lv_scr_act(), &hack_14_cyr, 0);

    /* setup done */
    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    
    if (temperature_loop()) {
      float t = temperature_get();
      display_temperature((int)t);
      Serial.printf("Temperature: %f", temperature_get());
      Serial.println();
    }

    delay(1);
}
