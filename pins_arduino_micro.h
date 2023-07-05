/**
 * CONTROLLINO NEO I/O
 * Note: All pins with value >= 32 are of course not directly connected
 * to the RP2040 and they required to be translated in the source
 * code to perform their function. Using an integer definition
 * offers better compatibillity with Arduino API.
 */

#pragma once

#ifndef CONTROLLINO_NEO_CORE
#define CONTROLLINO_NEO_CORE
#endif

 /* RP2040 */
#define SERIAL_HOWMANY              (3u)
#define SPI_HOWMANY                 (2u)
#define WIRE_HOWMANY                (2u)
#define PINS_COUNT                  (30u)
#define NUM_DIGITAL_PINS            (30u)
#define NUM_ANALOG_INPUTS           (4u)
#define NUM_ANALOG_OUTPUTS          (0u)
#define ADC_RESOLUTION              (12u)

/* Serial = USB */
 
/* Serial 1 */
// #define PIN_SERIAL1_TX              (0u)
// #define PIN_SERIAL1_RX              (1u)
#define PIN_SERIAL1_TX              (12u)
#define PIN_SERIAL1_RX              (13u)
 
/* Serial 2 */
#define PIN_SERIAL2_TX              (8u)
#define PIN_SERIAL2_RX              (9u)
 
/* SPI 0 */
#define PIN_SPI0_MISO               (16u)
#define PIN_SPI0_MOSI               (19u)
#define PIN_SPI0_SCK                (18u)
#define PIN_SPI0_SS                 (17u)
 
/* SPI 1 */
// #define PIN_SPI1_MISO               (8u)
// #define PIN_SPI1_MOSI               (11u)
// #define PIN_SPI1_SCK                (10u)
// #define PIN_SPI1_SS                 (9u)
#define PIN_SPI1_MISO               (12u)
#define PIN_SPI1_MOSI               (11u)
#define PIN_SPI1_SCK                (10u)
#define PIN_SPI1_SS                 (13u)

/* Wire(I2C) 0 */
#define PIN_WIRE0_SDA               (4u)
#define PIN_WIRE0_SCL               (5u)
 
/* Wire(I2C) 1 */
#define PIN_WIRE1_SDA               (10u)
#define PIN_WIRE1_SCL               (11u)
 
/* Default SPI pins */
static const uint8_t SS =           PIN_SPI0_SS;
static const uint8_t MOSI =         PIN_SPI0_MOSI;
static const uint8_t MISO =         PIN_SPI0_MISO;
static const uint8_t SCK =          PIN_SPI0_SCK;
 
/* Default I2C pins */
static const uint8_t SDA =          PIN_WIRE0_SDA;
static const uint8_t SCL =          PIN_WIRE0_SCL;
 
/* Exposed on pin header */
static const uint8_t D0 =           (0u);
static const uint8_t D1 =           (1u);
static const uint8_t D8 =           (8u);
static const uint8_t D9 =           (9u);
static const uint8_t D10 =          (10u);
static const uint8_t D11 =          (11u);
 
/* Analog pins these pins have especific internal functions */
static const uint8_t A0 =           (26u);
static const uint8_t A1 =           (27u);
static const uint8_t A2 =           (28u);
static const uint8_t A3 =           (29u);
 
/* Build in LED */
#define PIN_LED                     (25u)
#define LED_BUILTIN                 PIN_LED
 
/* For Arduino RS485 library */
#define RS485_SERIAL_PORT           Serial1
#define RS485_DEFAULT_TX_PIN        PIN_SERIAL1_TX
// #define RS485_DEFAULT_RE_PIN        (42u)
// #define RS485_DEFAULT_DE_PIN        (43u)
#define RS485_DEFAULT_RE_PIN        (10u)
#define RS485_DEFAULT_DE_PIN        (11u)

/* For Arduino SD library */
#define SDCARD_SS_PIN               (40u)

/* For Arduino ETHERNET library */
#define PIN_SPI_SS_ETHERNET_LIB     (41u)

/* For Arduino CAN library */
// #define MCP2515_DEFAULT_SPI         SPI
// #define MCP2515_DEFAULT_CS_PIN      (15u)
// #define MCP2515_DEFAULT_INT_PIN     (21u)
#define MCP2515_DEFAULT_SPI         SPI1
#define MCP2515_DEFAULT_CS_PIN      PIN_SPI1_SS
#define MCP2515_DEFAULT_INT_PIN     (15u)

/* Analog inputs connected to MCP356X 24 bits ADC */
static const uint8_t NEO_CORE_AI0 = (50u);
static const uint8_t NEO_CORE_AI1 = (51u);
static const uint8_t NEO_CORE_AI2 = (52u);
static const uint8_t NEO_CORE_AI3 = (53u);
static const uint8_t NEO_CORE_AI4 = (54u);
static const uint8_t NEO_CORE_AI5 = (55u);
static const uint8_t NEO_CORE_AI6 = (56u);
static const uint8_t NEO_CORE_AI7 = (57u);
 
/* Analog outputs connected to AD56X4 16 bits DAC */
static const uint8_t NEO_CORE_AO0 = (60u);
static const uint8_t NEO_CORE_AO1 = (61u);
static const uint8_t NEO_CORE_AO2 = (62u);
static const uint8_t NEO_CORE_AO3 = (63u);
 
/*
Digital outputs connected to CY8C95XX and drived by
BTS71220 high side output controller
*/
static const uint8_t NEO_CORE_DO4 = (70u);
static const uint8_t NEO_CORE_DO5 = (71u);
static const uint8_t NEO_CORE_DO6 = (72u);
static const uint8_t NEO_CORE_DO7 = (73u);
 
/* Digital inputs connected to RP2040 */
static const uint8_t NEO_CORE_DI0 = (80u);
static const uint8_t NEO_CORE_DI1 = (81u);
static const uint8_t NEO_CORE_DI2 = (82u);
static const uint8_t NEO_CORE_DI3 = (83u);
// static const uint8_t _NEO_CORE_DI0_RP2040_GPIO = (6u);
// static const uint8_t _NEO_CORE_DI1_RP2040_GPIO = (7u);
// static const uint8_t _NEO_CORE_DI2_RP2040_GPIO = (12u);
// static const uint8_t _NEO_CORE_DI3_RP2040_GPIO = (13u);
static const uint8_t _NEO_CORE_DI0_RP2040_GPIO = (0u);
static const uint8_t _NEO_CORE_DI1_RP2040_GPIO = (1u);
static const uint8_t _NEO_CORE_DI2_RP2040_GPIO = (2u);
static const uint8_t _NEO_CORE_DI3_RP2040_GPIO = (3u);

/*
Digital outputs connected to RP2040 and drived by
BTS71220 high side output controller
*/
static const uint8_t NEO_CORE_DO0 = (90u);
static const uint8_t NEO_CORE_DO1 = (91u);
static const uint8_t NEO_CORE_DO2 = (92u);
static const uint8_t NEO_CORE_DO3 = (93u);
// static const uint8_t _NEO_CORE_DO0_RP2040_GPIO = (24u);
// static const uint8_t _NEO_CORE_DO1_RP2040_GPIO = (23u);
// static const uint8_t _NEO_CORE_DO2_RP2040_GPIO = (22u);
// static const uint8_t _NEO_CORE_DO3_RP2040_GPIO = (14u);
static const uint8_t _NEO_CORE_DO0_RP2040_GPIO = (20u);
static const uint8_t _NEO_CORE_DO1_RP2040_GPIO = (21u);
static const uint8_t _NEO_CORE_DO2_RP2040_GPIO = (22u);
static const uint8_t _NEO_CORE_DO3_RP2040_GPIO = (23u);
static const uint8_t _NEO_CORE_DO4_RP2040_GPIO = (24u);
static const uint8_t _NEO_CORE_DO5_RP2040_GPIO = (26u);
static const uint8_t _NEO_CORE_DO6_RP2040_GPIO = (27u);
static const uint8_t _NEO_CORE_DO7_RP2040_GPIO = (28u);


/* ControllinoNeoPin API */
#include "neo_core_pin.h"
 
/* NEO core internal diagnosys API */
#include "neo_core_diag.h"


