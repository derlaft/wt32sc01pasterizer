#ifndef CONFIG_H
#define CONFIG_H

// пин, включающий перемешивание
#define PIN_MIXER 5

// пин, включающий нагрев
#define PIN_HEATER 33

// таймаут попыток работы с датчиком температуры
#define TEMP_PROBE_TIMEOUT_MS 2000
// пин с датчиком температуры 18В20
#define PIN_PROBE 25
// разрешение измерений температуры
#define PROBE_RESOLUTION 12
// отладка температурного датчика
#define PROBE_DEBUG
// период измерений температуры 
#define PROBE_INTERVAL_MS 1000
// дельта сравнения температур
#define TEMPERATURE_DELTA 1.0

// DEBUG
// #define DEBUG_SERIAL_TEMPERATURE

// разрешение графика температуры
#define TEMP_CHART_RESOLUTION_MS (1000 * 60)
// количество отметок на оси X
#define TEMP_CHART_MAJOR_TICKS_X 4
// количество отметок на оси Y
#define TEMP_CHART_MAJOR_TICKS_Y 5
// отладка температурного графика
#define TEMP_CHART_DEBUG

// максимальное количество точек в графике температуры
#define TEMP_CHART_POINT_COUNT (60 * 12)

// пин, включающий охлаждение
#define PIN_COOLER 27

// Диапазон температуры пастеризации
#define DEF_PAST_TEMP 70
#define MIN_PAST_TEMP 0
#define MAX_PAST_TEMP 94

// Диапазон времени пастеризации
#define DEF_PAST_TIME 30
#define MIN_PAST_TIME 0
#define MAX_PAST_TIME 60

// Диапазон температуры хранения
#define DEF_STORAGE_TEMP 42
#define MIN_STORAGE_TEMP 4
#define MAX_STORAGE_TEMP 90

// Интервал работы логики
#define LOGIC_TASK_INTERVAL_MS 500
#define LOGIC_SAFE_TEMP_MAX 95
#define LOGIC_SAFE_TEMP_MIN -50
#define LOGIC_DEBUG
#define LOGIC_BACKUP_EVERY_N_TICK 120

// Отладка настроек
#define SETTINGS_DEBUG

// Данные подключения к wifi по умолчанию
#define WIFI_DEF_AP ""
#define WIFI_DEF_PW ""
// Отладка WIFI
#define WIFI_DEBUG

// UTC+3
#define NTP_OFFSET (3 * 3600) 
#define NTP_SERVER "europe.pool.ntp.org"
#define NTP_UPDATE_INTERVAL_MS (3600000ul)

// #define DEBUG_WIPE_PREFERENCES

#endif
