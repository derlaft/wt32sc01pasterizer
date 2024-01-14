// тач
#define TOUCH_SDA 18
#define TOUCH_SCL 19
// SPI
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 40000000
#define USE_HSPI_PORT 1
// экран
#define CONFIG_TOUCH_CS -1
#define ST7796_DRIVER 1
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS 15
#define TFT_DC 21
#define TFT_RST 22
// подсветка
#define TFT_BL 23
// датчик температуры
#define DS_CHECK_CRC 1
#define DS_CRC_USE_TABLE 1

#ifdef _APP_SKREPPER

#define LOGIC_DEBUG

// (софтварный) серийный порт для общения со вторым контроллером
#define LOGIC_SERIAL_SPEED 1200
#define LOGIC_SERIAL_RX 5
#define LOGIC_SERIAL_TX 33
#define LOGIC_SERIAL_TIMEOUT 500

// пин с датчиком температуры 18В20
#define PIN_PROBE 25

#endif
