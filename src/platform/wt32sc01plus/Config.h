#define ST7796_DRIVER 1
#define TOUCH_DRIVER 0x6336
#define HASP_USE_LGFX_TOUCH 1

#define LV_COLOR_16_SWAP 0

// Portrait
#define TFT_WIDTH   320
#define TFT_HEIGHT  480

#define SPI_FREQUENCY 20000000

#define TFT_RD -1
#define TFT_WR 47
#define TFT_RS 0

#define SP32_PARALLEL
#define TFT_D0 9
#define TFT_D1 46
#define TFT_D2 3
#define TFT_D3 8
#define TFT_D4 18
#define TFT_D5 17
#define TFT_D6 16
#define TFT_D7 15
#define TFT_CS -1
#define TFT_RST 4
#define TFT_BUSY -1
#define TFT_BL 45

#define I2C_TOUCH_FREQUENCY 400000
#define I2C_TOUCH_ADDRESS 0x38
#define I2C_TOUCH_PORT 1

#define TOUCH_SDA 6
#define TOUCH_SCL 5

// SD CARD - SPI
#define SDSPI_HOST_ID SPI3_HOST
#define SD_MISO       GPIO_NUM_38 
#define SD_MOSI       GPIO_NUM_40
#define SD_SCLK       GPIO_NUM_39
#define SD_CS         GPIO_NUM_41
