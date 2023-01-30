#include "wifi.hpp"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, NTP_OFFSET, NTP_UPDATE_INTERVAL_MS);

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
#ifdef WIFI_DEBUG
    Serial.println("wifi: still waiting to be connected");
#endif
  }

  timeClient.begin();

  while(1) {
    vTaskDelay(pdMS_TO_TICKS(5000));

#ifdef WIFI_DEBUG
    Serial.print("Current wifi status: ");
    Serial.println(WiFi.status());
    Serial.flush();
#endif

    bool wifi_ok = WiFi.status() == WL_CONNECTED;

    if (wifi_ok) {
        timeClient.update();
#ifdef WIFI_DEBUG
        Serial.print("time: ");
        Serial.println(timeClient.getFormattedTime());
#endif
    }

    _GUI_LOCK(wifi_sync_ui(wifi_ok));
  }

  vTaskDelete(NULL);
}
