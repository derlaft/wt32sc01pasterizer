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

static lv_obj_t * label_temp;
lv_obj_t * temp_chart;
lv_chart_series_t * temp_series;
unsigned long last_series_insert = 0;

static void display_temperature(float v)
{
    char buf[6];
    sprintf(buf, v < 0 ? "%04.1f" : "!%04.1f", v);
    lv_label_set_text(label_temp, buf);

    if (millis() - last_series_insert > TEMP_CHART_RESOLUTION) {
      last_series_insert = millis();
      lv_chart_set_next_value(temp_chart, temp_series, (int)v);
    }
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

    // flex-раскладка: вертикальные айтемы
    lv_obj_t * flex = lv_obj_create(lv_scr_act());
    lv_obj_set_size(flex, lv_pct(100), lv_pct(100));
    lv_obj_center(flex);
    lv_obj_set_flex_flow(flex, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(flex, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END);

    // общие переменные
    lv_obj_t * label;

    // индикатор температуры
    label_temp = lv_label_create(flex);
    lv_label_set_text(label_temp, "!00.0");
    // lv_obj_align(label_temp, LV_ALIGN_TOP_LEFT, 0, 180);
    lv_obj_set_style_text_font(label_temp, &dseg_bold_italic, 0);

    // График температуры
    temp_chart = lv_chart_create(flex);
    lv_chart_set_update_mode(temp_chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_obj_align(temp_chart, LV_ALIGN_LEFT_MID, 0, 20);
    lv_chart_set_point_count(temp_chart, 60);
    lv_obj_set_size(temp_chart, lv_pct(50), lv_pct(40));
    lv_chart_set_type(temp_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(temp_chart, LV_CHART_AXIS_SECONDARY_Y, 0, 100);
    lv_chart_set_axis_tick(temp_chart, LV_CHART_AXIS_SECONDARY_Y, 10, 6, 3, 2, true, 35);
    temp_series = lv_chart_add_series(temp_chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_SECONDARY_Y);

    // flex-раскладка для нижнего ряда кнопок
    lv_obj_t * bottom_buttons = lv_obj_create(flex);
    lv_obj_set_size(bottom_buttons, lv_pct(100), lv_pct(30));
    lv_obj_align(bottom_buttons, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_flex_flow(bottom_buttons, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_border_opa(bottom_buttons, LV_OPA_100, LV_STATE_DEFAULT);

    // управление нагревом
    lv_obj_t * btn_heat = lv_btn_create(bottom_buttons);
    lv_obj_add_event_cb(btn_heat, on_heat_override, LV_EVENT_ALL, NULL);
    // lv_obj_align(btn_heat, LV_ALIGN_TOP_LEFT, 100, 40);
    lv_obj_add_flag(btn_heat, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn_heat, lv_pct(100));
    lv_obj_set_width(btn_heat, lv_pct(30));
    lv_obj_set_style_bg_color(btn_heat, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn_heat, lv_palette_main(LV_PALETTE_LIGHT_BLUE), LV_STATE_CHECKED);
    lv_obj_set_style_text_font(btn_heat, &hack_14_cyr, 0);


    label = lv_label_create(btn_heat);
    lv_label_set_text(label, "Нагреватель");
    lv_obj_center(label);

    // управление охлаждением
    lv_obj_t * btn_cool = lv_btn_create(bottom_buttons);
    lv_obj_add_event_cb(btn_cool, on_cool_override, LV_EVENT_ALL, NULL);
    // lv_obj_align(btn_cool, LV_ALIGN_TOP_LEFT, 100, 80);
    lv_obj_add_flag(btn_cool, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn_cool, lv_pct(100));
    lv_obj_set_width(btn_cool, lv_pct(30));
    lv_obj_set_style_bg_color(btn_cool, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn_cool, lv_palette_main(LV_PALETTE_LIGHT_BLUE), LV_STATE_CHECKED);
    lv_obj_set_style_text_font(btn_cool, &hack_14_cyr, 0);


    label = lv_label_create(btn_cool);
    lv_label_set_text(label, "Охлаждение");
    lv_obj_center(label);


    // управление перемешиванием
    lv_obj_t * btn_mixer = lv_btn_create(bottom_buttons);
    lv_obj_add_event_cb(btn_mixer, on_mixer_override, LV_EVENT_ALL, NULL);
    // lv_obj_align(btn_mixer, LV_ALIGN_TOP_LEFT, 100, 120);
    lv_obj_add_flag(btn_mixer, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn_mixer, lv_pct(100));
    lv_obj_set_width(btn_mixer, lv_pct(30));

    lv_obj_set_style_bg_color(btn_mixer, lv_palette_main(LV_PALETTE_GREY), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn_mixer, lv_palette_main(LV_PALETTE_LIGHT_BLUE), LV_STATE_CHECKED);
    label = lv_label_create(btn_mixer);
    lv_label_set_text(label, "Перемешивание");
    lv_obj_center(label);
    lv_obj_set_style_text_font(btn_mixer, &hack_14_cyr, 0);

    
    // Установить глобальный шрифт
    // lv_obj_set_style_text_font(lv_scr_act(), &hack_14_cyr, 0);

    /* setup done */
    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    
    if (temperature_loop()) {
      float t = temperature_get();
      display_temperature(t);
      Serial.printf("Temperature: %f", temperature_get());
      Serial.println();
    }

    delay(1);
}
