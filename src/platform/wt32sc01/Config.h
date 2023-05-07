#define _DEVICE WT32SC01

// конфигурация различных пинов, связанных в основном с дисплеем и тачем
#define CONFIG_TOUCH_CS -1
#define TOUCH_SDA 18
#define TOUCH_SCL 19
#define ST7796_DRIVER 1
#define USE_HSPI_PORT 1
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS 15
#define TFT_DC 21
#define TFT_RST 22
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 40000000
#define TFT_BL 23
#define DS_CHECK_CRC 1
#define DS_CRC_USE_TABLE 1
