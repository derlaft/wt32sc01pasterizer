#include "wifi.hpp"
#include <WiFi.h>

void wifi_setup() {
  WiFi.useStaticBuffers(true);
  WiFi.setAutoReconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.persistent(false);

  xTaskCreatePinnedToCore(wifi_task, "wifimon", 4096*2, NULL, tskIDLE_PRIORITY, NULL, 1);
}

void print_time() {

  struct tm time;
  if(!getLocalTime(&time)){
    Serial.println("Could not obtain time info");
    return;
  }

  char buffer[80];
  strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", &time);

  Serial.println("\n---------TIME----------");
  Serial.println(buffer);
  Serial.println("-----------------------");

}

void wifi_task(void *pvParameter) {

  WiFi.begin(wifi_ap, wifi_pw);

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(1000));
#ifdef WIFI_DEBUG
    Serial.println("wifi: still waiting to be connected");
#endif
  }

  configTime(NTP_OFFSET, 0, NTP_SERVER);

  while(1) {
    vTaskDelay(pdMS_TO_TICKS(5000));

#ifdef WIFI_DEBUG
    Serial.print("Current wifi status: ");
    Serial.println(WiFi.status());
    Serial.flush();
#endif

    bool wifi_ok = WiFi.status() == WL_CONNECTED;

    if (wifi_ok) {
      configTime(NTP_OFFSET, 0, NTP_SERVER);
    }

#ifdef WIFI_DEBUG
    print_time();
#endif

    _GUI_LOCK(wifi_sync_ui(wifi_ok));
  }

  vTaskDelete(NULL);
}
