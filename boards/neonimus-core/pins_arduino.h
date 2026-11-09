#ifndef Pins_Arduino_h
#define Pins_Arduino_h
/*
 * Neonimus Firmware - board pin map
 * Target: ESP32-S3-DevKitC-1 N16R8 (16MB flash, 8MB octal PSRAM)
 *
 * !! READ BEFORE WIRING !!
 * On the N16R8 variant the flash AND PSRAM are both wired internally to:
 *   GPIO 26-32  (quad flash SPI)
 *   GPIO 33-37  (octal PSRAM - this is the part generic S3 pin-out charts
 *                often forget; it only applies to -R8/-R16 "octal PSRAM"
 *                SKUs, not the plain -R2 quad-PSRAM ones)
 * GPIO 26-37 are therefore permanently unavailable. Also avoid:
 *   GPIO 0        - BOOT strap pin
 *   GPIO 3,45,46  - strapping pins (45/46 also set flash/PSRAM voltage)
 *   GPIO 19,20    - native USB D-/D+ (used for USB-CDC serial + flashing)
 *   GPIO 43,44    - broken out as secondary TX/RX on the DevKitC-1 header
 * Every pin below was chosen to avoid that list. If you change a
 * pin, re-check it against this comment.
 */

#include <stdint.h>
#include "soc/soc_caps.h"

#ifndef DEVICE_NAME
#define DEVICE_NAME "Neonimus"
#endif

#define USB_VID 0x303A
#define USB_PID 0x1001

// ---------------------------------------------------------------------
// Shared SPI bus: TFT + microSD share CLK/MOSI/MISO, each with its own CS.
// (User chose shared bus - no dedicated SD SPI pins requested.)
// ---------------------------------------------------------------------
#define SPI_SCK_PIN  12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN   10 // generic default CS, mirrors ESP-General convention

static const uint8_t SCK  = SPI_SCK_PIN;
static const uint8_t MOSI = SPI_MOSI_PIN;
static const uint8_t MISO = SPI_MISO_PIN;
static const uint8_t SS   = SPI_SS_PIN;

// ---------------------------------------------------------------------
// Display: 1.8" TFT, ST7735 driver (128x160) - TFT_eSPI config
// !! VERIFY TAB COLOR VARIANT ON REAL HARDWARE !!
// Generic 1.8" ST7735 boards ship with different internal offsets
// (BLACKTAB / GREENTAB / REDTAB). Default guess below is BLACKTAB,
// the most common for this exact style of module. If colors look
// shifted/inverted or the image is offset, try GREENTAB / GREENTAB2
// instead - see lib/TFT_eSPI/TFT_Drivers/ST7735_Defines.h in upstream.
// ---------------------------------------------------------------------
#define USER_SETUP_LOADED 1
#define ST7735_DRIVER      1
#define ST7735_BLACKTAB    1 // TODO verify against physical panel
#define TFT_WIDTH   128
#define TFT_HEIGHT  160
#define TFT_RGB_ORDER 1

#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  14
#define TFT_BL   15 // backlight, PWM-capable pin
#define TFT_BACKLIGHT_ON 1
#define TFT_MOSI SPI_MOSI_PIN
#define TFT_SCLK SPI_SCK_PIN
#define TOUCH_CS -1 // no touch on this panel

#define ROTATION   1
#define BACKLIGHT  TFT_BL
#define MINBRIGHT  160
#define SMOOTH_FONT 1
#define SPI_FREQUENCY       27000000
#define SPI_READ_FREQUENCY  16000000
#define SPI_TOUCH_FREQUENCY 2500000

#define FP 1
#define FM 2
#define FG 3

#define HAS_SCREEN 1

// ---------------------------------------------------------------------
// microSD (SPI, shares SCK/MOSI/MISO above, own CS)
// ---------------------------------------------------------------------
#define SDCARD_CS   21
#define SDCARD_SCK  SPI_SCK_PIN
#define SDCARD_MOSI SPI_MOSI_PIN
#define SDCARD_MISO SPI_MISO_PIN

// ---------------------------------------------------------------------
// I2S mic - INMP441 (voice command input, Phase 3)
// Matches macro names expected by src/modules/others/mic.cpp upstream
// (PIN_CLK=BCLK, PIN_WS=LRCLK/WS, PIN_DATA=SD/DOUT-from-mic)
// ---------------------------------------------------------------------
#define MIC_INMP441 1
#define PIN_CLK   4  // BCLK
#define PIN_BCLK  PIN_CLK
#define PIN_WS    5  // LRCLK / word select
#define PIN_DATA  6  // SD (mic data out -> ESP32 in)

// ---------------------------------------------------------------------
// I2S amp - MAX98357A (voice feedback output, Phase 3)
// Matches macro names expected by src/modules/others/audio.cpp upstream
// (audioout->SetPinout(BCLK, WCLK, DOUT, MCLK))
// Separate I2S peripheral/pins from the mic above - do NOT share with
// the mic pins, the two run as independent I2S channels (RX vs TX).
// ---------------------------------------------------------------------
#define BCLK 16
#define WCLK 17
#define DOUT 18
#define MCLK -1 // not used by MAX98357A

// ---------------------------------------------------------------------
// I2C (Grove-style) bus - used by default for PN532 (I2C variant chosen)
// ---------------------------------------------------------------------
#define GROVE_SDA 1
#define GROVE_SCL 2
static const uint8_t SDA = GROVE_SDA;
static const uint8_t SCL = GROVE_SCL;

// ---------------------------------------------------------------------
// Optional: CC1101 (Sub-GHz) - Phase 6, feature-gated
// Shares the SPI bus above, own SS + GDO0
// ---------------------------------------------------------------------
#define USE_CC1101_VIA_SPI
#define CC1101_SS_PIN   38
#define CC1101_GDO0_PIN 39
#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_SCK_PIN  SPI_SCK_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

// ---------------------------------------------------------------------
// Optional: IR TX/RX - Phase 6, feature-gated
// ---------------------------------------------------------------------
#define TXLED 40
#define LED_ON  HIGH
#define LED_OFF LOW
#define IR_TX_PINS '{{"Neonimus IR", 41}}'
#define IR_RX_PINS '{{"Neonimus IR", 42}}'

// ---------------------------------------------------------------------
// Optional: NRF24L01 (2.4GHz - mousejacking/spectrum) - Phase 6, feature-gated
// Shares the SPI bus above, own CE + CS (matches configPins.h's NRF24_bus,
// which only gets built #ifdef NRF24_SCK_PIN)
// ---------------------------------------------------------------------
#define NRF24_CE_PIN   7
#define NRF24_SS_PIN   8
#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN  SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

// ---------------------------------------------------------------------
// Optional: GPS (NEO-6M / ATGM336H, UART) - Phase 6, feature-gated
// Matches configPins.h's gps_bus = {GPS_SERIAL_RX, GPS_SERIAL_TX}
// ---------------------------------------------------------------------
#define GPS_SERIAL_TX 47 // ESP32 TX -> GPS module RX
#define GPS_SERIAL_RX 48 // ESP32 RX <- GPS module TX

// ---------------------------------------------------------------------
// NOTE: with NRF24L01 + GPS added, every available GPIO on this N16R8
// devkit is now spoken for (0 spare left: see the reserved-pin list at
// the top of this file). If you add anything else, you'll need to
// reuse an existing pin (e.g. move IR off 41/42) or drop one of the
// Phase 6 modules.
// ---------------------------------------------------------------------

#endif /* Pins_Arduino_h */
