#include <Arduino.h>

#include "ui.h"
#include "Config.h"
#include "ui_hal.h"
#include "temperature.hpp"
#include "temperature_graph.hpp"

bool temperature_graph_enabled = false;

time_t graph_last_update = 0;

void temperature_graph_task_setup() {
  xTaskCreatePinnedToCore(temperature_graph_task, "temp_graph", 4096*2, NULL, tskIDLE_PRIORITY+5, NULL, 1);
}

void temperature_graph_task(void *pvParameter) {

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(TEMP_CHART_RESOLUTION_MS);

  xLastWakeTime = xTaskGetTickCount();

  while(1) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    if (temperature_graph_enabled) {
      temperature_graph_add_new_point();
    } else if (is_idle()){
      // обновить время на графике
      time(&graph_last_update);
    }
  }
}

void temperature_graph_add_new_point() {

  float current_temp = temperature_get();

  if (chart_ptr == TEMP_CHART_POINT_COUNT) {
    // конец измерений
    return;
  }

  // insert the point
  temperature_data[chart_ptr] = (int) (current_temp*10);
  chart_ptr = chart_ptr+1;
  // set update of the last insertion
  time(&graph_last_update);

  _GUI_LOCK(
      lv_chart_set_x_start_point(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, chart_ptr);

      if (chart_ptr > point_count) {
      point_count = chart_ptr;
      lv_chart_set_point_count(ui_Screen1_Chart1, point_count);
#ifdef TEMP_CHART_DEBUG
      Serial.print("point count: ");
      Serial.println(point_count);
#endif
      }

      lv_chart_refresh(ui_Screen1_Chart1);
  );

}
