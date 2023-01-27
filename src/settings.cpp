#include "settings.hpp"

Preferences preferences;

int16_t past_temp_value;
int16_t past_time_value;
int16_t store_temp_value;

char wifi_ap[128];
char wifi_pw[128];

void settings_setup() {
#ifdef SETTINGS_DEBUG
  Serial.println("settings: reloading");
#endif
  preferences.begin("pasterizer", true);

  past_temp_value = (int16_t) preferences.getShort(_PAST_TEMP_KEY, DEF_PAST_TEMP);
  if (past_temp_value < MIN_PAST_TEMP || past_temp_value > MAX_PAST_TEMP) {
    past_temp_value = DEF_PAST_TEMP;
  }

  past_time_value = (int16_t) preferences.getShort(_PAST_TIME_KEY, DEF_PAST_TIME);
  if (past_time_value < MIN_PAST_TIME || past_time_value > MAX_PAST_TIME) {
    past_time_value = DEF_PAST_TIME;
  }

  store_temp_value = (int16_t) preferences.getShort(_STORE_TEMP_KEY, DEF_STORAGE_TEMP);
  if (store_temp_value < MIN_STORAGE_TEMP || store_temp_value > MAX_STORAGE_TEMP) {
    store_temp_value = DEF_STORAGE_TEMP;
  }

  preferences.getString(_WIFI_AP_KEY, wifi_ap, 128);
  preferences.getString(_WIFI_PW_KEY, wifi_pw, 128);

  preferences.end();

  update_settings_values();
}

void settings_update() {
#ifdef SETTINGS_DEBUG
  Serial.println("settings: saving");
#endif
  preferences.begin("pasterizer", false);
  preferences.putShort(_PAST_TEMP_KEY, past_temp_value);
  preferences.putShort(_PAST_TIME_KEY, past_time_value);
  preferences.putShort(_STORE_TEMP_KEY, store_temp_value);
  preferences.putString(_WIFI_AP_KEY, wifi_ap);
  preferences.putString(_WIFI_PW_KEY, wifi_pw);
  preferences.end();
}
