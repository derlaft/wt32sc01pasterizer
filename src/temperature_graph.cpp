#include <Arduino.h>

#include "ui.h"
#include "Config.h"
#include "ui_hal.h"
#include "temperature.hpp"
#include "temperature_graph.hpp"

void temperature_graph_task_setup() {
  xTaskCreatePinnedToCore(temperature_graph_task, "temp_graph", 4096*2, NULL, tskIDLE_PRIORITY+5, NULL, 1);
}

void temperature_graph_task(void *pvParameter) {

  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(TEMP_CHART_RESOLUTION_MS);

  xLastWakeTime = xTaskGetTickCount();

  while(1) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    temperature_graph_add_new_point();
  }

}

void temperature_graph_add_new_point() {

  float current_temp = temperature_get();

  if (chart_ptr == TEMP_CHART_POINT_COUNT) {
    // конец измерений
    return;
  }

  temperature_data[chart_ptr] = (int) (current_temp*10);
  chart_ptr = chart_ptr+1;

  if (pdTRUE != xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
    return;
  }

  lv_chart_set_x_start_point(ui_Screen1_Chart1, ui_Screen1_Chart1_Series, chart_ptr);

  if (chart_ptr > point_count) {
    point_count = chart_ptr;
    lv_chart_set_point_count(ui_Screen1_Chart1, point_count);
    Serial.print("point count: ");
    Serial.println(point_count);
  }

  // lv_chart_set_point_count(ui_Screen1_Chart1, point_count);
  lv_chart_refresh(ui_Screen1_Chart1);

  xSemaphoreGive(xGuiSemaphore);
}
