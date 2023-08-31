/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#pragma once
 
/**
 * \file pins_arduino.h
 *
 * Based on arduino-pico generic pins_arduino.h
 *
 * CONTROLLINO NEO I/O
 * Note: All pins with value >= 32 are of course not directly connected
 * to the RP2040 and they required to be translated in the source
 * code to perform their function. Using an integer definition
 * offers better compatibillity with Arduino API.
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
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
#ifndef PIN_SERIAL1_TX
#define PIN_SERIAL1_TX              (0u)
#endif
#ifndef PIN_SERIAL1_RX
#define PIN_SERIAL1_RX              (1u)
#endif
 
/* Serial 2 */
#ifndef PIN_SERIAL2_TX
#define PIN_SERIAL2_TX              (8u)
#endif
#ifndef PIN_SERIAL2_RX
#define PIN_SERIAL2_RX              (9u)
#endif
 
/* SPI */
#ifndef __SPI0_DEVICE
#define __SPI0_DEVICE spi0
#endif
#ifndef __SPI1_DEVICE
#define __SPI1_DEVICE spi1
 
/* SPI 0 */
#endif
#ifndef PIN_SPI0_MISO
#define PIN_SPI0_MISO               (16u)
#endif
#ifndef PIN_SPI0_MOSI
#define PIN_SPI0_MOSI               (19u)
#endif
#ifndef PIN_SPI0_SCK
#define PIN_SPI0_SCK                (18u)
#endif
#ifndef PIN_SPI0_SS
#define PIN_SPI0_SS                 (17u)
#endif
 
/* SPI 1 */
#ifndef PIN_SPI1_MISO
#define PIN_SPI1_MISO               (8u)
#endif
#ifndef PIN_SPI1_MOSI
#define PIN_SPI1_MOSI               (11u)
#endif
#ifndef PIN_SPI1_SCK
#define PIN_SPI1_SCK                (10u)
#endif
#ifndef PIN_SPI1_SS
#define PIN_SPI1_SS                 (9u)
#endif
 
/* Wire(I2C) */
#ifndef __WIRE0_DEVICE
#define __WIRE0_DEVICE i2c0
#endif
#ifndef __WIRE1_DEVICE
#define __WIRE1_DEVICE i2c1
#endif
 
/* Wire(I2C) 0 */
#ifndef PIN_WIRE0_SDA
#define PIN_WIRE0_SDA               (4u)
#endif
#ifndef PIN_WIRE0_SCL
#define PIN_WIRE0_SCL               (5u)
#endif
 
/* Wire(I2C) 1 */
#ifndef PIN_WIRE1_SDA
#define PIN_WIRE1_SDA               (10u)
#endif
#ifndef PIN_WIRE1_SCL
#define PIN_WIRE1_SCL               (11u)
#endif
 
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
#ifndef LED_BUILTIN
#define PIN_LED                     (25u)
#endif
#ifndef LED_BUILTIN
#define LED_BUILTIN                 PIN_LED
#endif
 
/* For Arduino RS485 library */
#ifndef RS485_SERIAL_PORT
#define RS485_SERIAL_PORT           Serial1
#endif
#ifndef RS485_DEFAULT_TX_PIN
#define RS485_DEFAULT_TX_PIN        PIN_SERIAL1_TX
#endif
#ifndef RS485_DEFAULT_RE_PIN
#define RS485_DEFAULT_RE_PIN        (42u)
#endif
#ifndef RS485_DEFAULT_DE_PIN
#define RS485_DEFAULT_DE_PIN        (43u)
#endif
 
/* For Arduino SD library */
#ifndef SDCARD_SS_PIN
#define SDCARD_SS_PIN               (20u)
#endif
 
/* For Arduino ETHERNET library */
#ifndef PIN_SPI_SS_ETHERNET_LIB
#define PIN_SPI_SS_ETHERNET_LIB     (17u)
#endif
 
/* For Arduino CAN library */
#ifndef MCP2515_DEFAULT_SPI
#define MCP2515_DEFAULT_SPI         SPI
#endif
#ifndef MCP2515_DEFAULT_CS_PIN
#define MCP2515_DEFAULT_CS_PIN      (15u)
#endif
#ifndef MCP2515_DEFAULT_INT_PIN
#define MCP2515_DEFAULT_INT_PIN     (21u)
#endif
 
/* Other pins used on internal components */
#ifndef _MCP3564_CS_PIN
#define _MCP3564_CS_PIN             (3u)
#endif
#ifndef _AD5664_CS_PIN
#define _AD5664_CS_PIN              (2u)
#endif
 
/* Analog inputs connected to MCP3564 24 bits ADC */
static const uint8_t CONTROLLINO_NEO_AI0 = (50u);
static const uint8_t CONTROLLINO_NEO_AI1 = (51u);
static const uint8_t CONTROLLINO_NEO_AI2 = (52u);
static const uint8_t CONTROLLINO_NEO_AI3 = (53u);
static const uint8_t CONTROLLINO_NEO_AI4 = (54u);
static const uint8_t CONTROLLINO_NEO_AI5 = (55u);
static const uint8_t CONTROLLINO_NEO_AI6 = (56u);
static const uint8_t CONTROLLINO_NEO_AI7 = (57u);
 
/* Analog outputs connected to AD5664 16 bits DAC */
static const uint8_t CONTROLLINO_NEO_AO0 = (60u);
static const uint8_t CONTROLLINO_NEO_AO1 = (61u);
static const uint8_t CONTROLLINO_NEO_AO2 = (62u);
static const uint8_t CONTROLLINO_NEO_AO3 = (63u);
 
/*
Digital outputs connected to CY8C9520 and drived by
BTS71220 high side output controller
*/
static const uint8_t CONTROLLINO_NEO_DO4 = (70u);
static const uint8_t CONTROLLINO_NEO_DO5 = (71u);
static const uint8_t CONTROLLINO_NEO_DO6 = (72u);
static const uint8_t CONTROLLINO_NEO_DO7 = (73u);
 
/* Digital inputs connected to RP2040 */
static const uint8_t CONTROLLINO_NEO_DI0 = (6u);
static const uint8_t CONTROLLINO_NEO_DI1 = (7u);
static const uint8_t CONTROLLINO_NEO_DI2 = (12u);
static const uint8_t CONTROLLINO_NEO_DI3 = (13u);
 
/*
Digital outputs connected to RP2040 and drived by
BTS71220 high side output controller
*/
static const uint8_t CONTROLLINO_NEO_DO0 = (24u);
static const uint8_t CONTROLLINO_NEO_DO1 = (23u);
static const uint8_t CONTROLLINO_NEO_DO2 = (22u);
static const uint8_t CONTROLLINO_NEO_DO3 = (14u);
 
/* ControllinoRp2040Pin API */
#include "controllino_wiring.h"
 
/* NEO core internal diagnosys API */
#include "controllino_diag.h"


