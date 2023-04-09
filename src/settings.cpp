#include "settings.hpp"

Preferences preferences;

int16_t DRAM_ATTR cool_temp_value = DEF_COOL_TEMP;
int16_t DRAM_ATTR before_mix_value = DEF_BEFORE_MIX_TIME;
int16_t DRAM_ATTR mix_value = DEF_MIX_TIME;
int16_t DRAM_ATTR mix_delay_value = DEF_MIX_DELAY_TIME;

char DRAM_ATTR wifi_ap[128] = WIFI_DEF_AP;
char DRAM_ATTR wifi_pw[128] = WIFI_DEF_PW;

void settings_setup() {
#ifdef SETTINGS_DEBUG
  Serial.println("settings: reloading");
#endif

  if (!preferences.begin("cleaner", true)) {
#ifdef SETTINGS_DEBUG
    Serial.println("settings: no settings present");
#endif
    return;
  }

  cool_temp_value = (int16_t) preferences.getShort(_COOL_TEMP_KEY);
  if (cool_temp_value < MIN_COOL_TEMP || cool_temp_value > MAX_COOL_TEMP) {
	  cool_temp_value = DEF_COOL_TEMP;
  }

  before_mix_value = (int16_t) preferences.getShort(_BEFORE_MIX_KEY);
  if (before_mix_value < MIN_BEFORE_MIX_TIME || before_mix_value > MAX_BEFORE_MIX_TIME) {
	  before_mix_value = DEF_BEFORE_MIX_TIME;
  }

  mix_value = (int16_t) preferences.getShort(_MIX_KEY);
  if (mix_value < MIN_MIX_TIME || mix_value > MAX_MIX_TIME) {
	  mix_value = DEF_MIX_TIME;
  }

  mix_delay_value = (int16_t) preferences.getShort(_MIX_DELAY_KEY);
  if (mix_delay_value < MIN_MIX_DELAY_TIME || mix_delay_value > MAX_MIX_DELAY_TIME) {
	  mix_delay_value = DEF_MIX_DELAY_TIME;
  }

  preferences.getString(_WIFI_AP_KEY, wifi_ap, 128);
  preferences.getString(_WIFI_PW_KEY, wifi_pw, 128);

  preferences.end();

  update_settings_values();
}

void settings_update() {

  // запретить прерывания на время работы с flash
  if (!preferences.begin("cleaner", false)) {
    return;
  }

  preferences.putShort(_COOL_TEMP_KEY, cool_temp_value);
  preferences.putShort(_BEFORE_MIX_KEY, before_mix_value);
  preferences.putShort(_MIX_KEY, mix_value);
  preferences.putShort(_MIX_DELAY_KEY, mix_delay_value);
  
  preferences.putString(_WIFI_AP_KEY, wifi_ap);
  preferences.putString(_WIFI_PW_KEY, wifi_pw);

  preferences.end();
}
