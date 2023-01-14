#ifndef CONFIG_H
#define CONFIG_H

// пин, включающий перемешивание
#define PIN_MIXER 5

// пин, включающий нагрев
#define PIN_HEATER 33

// пин с датчиком температуры 18В20
#define PIN_PROBE 25
// разрешение измерений температуры
#define PROBE_RESOLUTION 9
// разрешение графика температуры (в ms)
#define TEMP_CHART_RESOLUTION (1000)

// максимальное количество точек в графике температуры
#define TEMP_CHART_POINT_COUNT 60
// начальное количество точек (похоже не может быть меньше 10?)
#define TEMP_CHART_POINT_COUNT_START 10

// пин, включающий охлаждение
#define PIN_COOLER 27

// Диапазон температуры пастеризации
#define MIN_PAST_TEMP 0
#define MAX_PAST_TEMP 99

// Диапазон времени пастеризации
#define MIN_PAST_TIME 0
#define MAX_PAST_TIME 60

// Диапазон температуры хранения
#define MIN_STORAGE_TEMP 4
#define MAX_STORAGE_TEMP 90

#endif
