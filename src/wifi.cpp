#include "wifi.hpp"


void wifi_setup() {
  WiFi.useStaticBuffers(true);
  WiFi.setAutoReconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.persistent(false);

  xTaskCreatePinnedToCore(wifi_task, "wifimon", 4096*2, NULL, tskIDLE_PRIORITY, NULL, 1);
}

void wifi_task(void *pvParameter) {

  WiFi.begin(wifi_ap, wifi_pw);

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(1000));
    Serial.println("WIFI conn..");
  }

  while(1) {
    vTaskDelay(pdMS_TO_TICKS(5000));

    Serial.print("Current wifi status: ");
    Serial.println(WiFi.status());
    Serial.flush();
    _GUI_LOCK(wifi_sync_ui(WiFi.status() == WL_CONNECTED));
  }

  vTaskDelete(NULL);
}
