#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h> 
#include <Adafruit_FT6206.h>
#include "esp_freertos_hooks.h"

#include "lvgl.h"
#include "Config.h"

static const char * btnm_map[] PROGMEM = {
    LV_SYMBOL_LEFT,
    LV_SYMBOL_PAUSE,
    LV_SYMBOL_RIGHT,
    "00:00",
    "",
};

static const lv_btnmatrix_ctrl_t btnm_control[] PROGMEM = {
    0,
    0,
    0,
    LV_BTNMATRIX_CTRL_DISABLED,
    0,
};


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
  pinMode(PIN_MIXER, OUTPUT);
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_COOLER, OUTPUT);

  // Configure 18B20
  // TODO

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

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Тыкнуто: %d", cnt);
    }
}

static lv_obj_t * meter;

static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_value(meter, (lv_meter_indicator_t*) indic, v);
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

    lv_obj_set_style_text_font(lv_scr_act(), &hack_14_cyr, 0);

    lv_obj_t * btnm = lv_btnmatrix_create(lv_scr_act());
    lv_btnmatrix_set_map(btnm, btnm_map);
    lv_btnmatrix_set_ctrl_map(btnm, btnm_control);
    //lv_btnmatrix_set_btn_width(btnm, 10, 2);
    lv_obj_align(btnm, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_height(btnm, lv_pct(30));
    lv_obj_set_width(btnm, lv_pct(90));

    // шрифт
    lv_obj_set_style_text_font(btnm, &lv_font_montserrat_30, 0);
    // изменить стиль кнопок
    lv_obj_set_style_bg_opa(btnm, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_opa(btnm, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btnm, lv_color_white(), LV_PART_ITEMS);

    // lv_obj_add_event_cb(btnm1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_t * chart;
    chart = lv_chart_create(lv_scr_act());
    lv_obj_align(chart, LV_ALIGN_BOTTOM_MID, -40, -15);
    lv_obj_set_height(chart, lv_pct(65));
    lv_obj_set_width(chart, lv_pct(80));
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);

    lv_chart_set_range(chart, LV_CHART_AXIS_SECONDARY_Y, 0, 10000);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 6, 2, true, 60);

    /*Add two data series*/
    lv_chart_series_t * ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_YELLOW), LV_CHART_AXIS_SECONDARY_Y);
    lv_chart_series_t * ser2 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);
    lv_chart_series_t * ser3 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_SECONDARY_Y);

    /*Set the next points on 'ser1'*/
    lv_chart_set_next_value(chart, ser1, 1000);
    lv_chart_set_next_value(chart, ser1, 1000);
    lv_chart_set_next_value(chart, ser1, 1000);
    lv_chart_set_next_value(chart, ser1, 1000);
    lv_chart_set_next_value(chart, ser1, 1000);
    lv_chart_set_next_value(chart, ser1, 1000);
    lv_chart_set_next_value(chart, ser1, 1000);
    lv_chart_set_next_value(chart, ser1, 3000);
    lv_chart_set_next_value(chart, ser1, 7000);
    lv_chart_set_next_value(chart, ser1, 9000);

    lv_chart_set_next_value(chart, ser2, 9000);
    lv_chart_set_next_value(chart, ser2, 7000);
    lv_chart_set_next_value(chart, ser2, 6500);
    lv_chart_set_next_value(chart, ser2, 6500);
    lv_chart_set_next_value(chart, ser2, 6500);
    lv_chart_set_next_value(chart, ser2, 6500);
    lv_chart_set_next_value(chart, ser2, 6500);
    lv_chart_set_next_value(chart, ser2, 6500);
    lv_chart_set_next_value(chart, ser2, 6500);
    lv_chart_set_next_value(chart, ser2, 6500);

    lv_chart_set_next_value(chart, ser3, 9000);
    lv_chart_set_next_value(chart, ser3, 8000);
    lv_chart_set_next_value(chart, ser3, 7000);
    lv_chart_set_next_value(chart, ser3, 6000);
    lv_chart_set_next_value(chart, ser3, 5000);
    lv_chart_set_next_value(chart, ser3, 4000);
    lv_chart_set_next_value(chart, ser3, 5500);
    lv_chart_set_next_value(chart, ser3, 7600);
    lv_chart_set_next_value(chart, ser3, 9900);
    lv_chart_set_next_value(chart, ser3, 9900);

    lv_chart_refresh(chart); /*Required after direct set*/

    lv_obj_t * btn = lv_btn_create(lv_scr_act());
    lv_obj_set_style_text_font(btn, &lv_font_montserrat_30, 0);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(btn, lv_color_white(), LV_STATE_CHECKED);
    lv_obj_set_style_pad_all(btn, 10, 0);
    lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_shadow_width(btn, 0, 0);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_SETTINGS, 0);

    //lv_obj_add_event_cb(btn, color_changer_event_cb, LV_EVENT_ALL, color_cont);

    lv_obj_set_size(btn, LV_DPX(42), LV_DPX(42));
    lv_obj_align(btn, LV_ALIGN_BOTTOM_RIGHT, -LV_DPX(15), -LV_DPX(15));

    /* setup done */
    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(1);
}
