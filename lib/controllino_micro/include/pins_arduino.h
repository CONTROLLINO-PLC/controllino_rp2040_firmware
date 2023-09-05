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
 * CONTROLLINO MICRO I/O
 * Note: All pins with value >= 32 are of course not directly connected
 * to the RP2040 and they required to be translated in the source
 * code to perform their function. Using an integer definition
 * offers better compatibillity with Arduino API.
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */

#ifndef CONTROLLINO_MICRO_CORE
#define CONTROLLINO_MICRO_CORE
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
 
/* Serial(UART) */
#ifndef __SERIAL1_DEVICE
#define __SERIAL1_DEVICE uart0
#endif
#ifndef __SERIAL2_DEVICE
#define __SERIAL2_DEVICE uart1
#endif
 
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
#define __WIRE0_DEVICE i2c1
#endif
#ifndef __WIRE1_DEVICE
#define __WIRE1_DEVICE i2c0
#endif
 
/* Wire(I2C) 0 */
#ifndef PIN_WIRE0_SDA
#define PIN_WIRE0_SDA               (2u)
#endif
#ifndef PIN_WIRE0_SCL
#define PIN_WIRE0_SCL               (3u)
#endif
 
/* Wire(I2C) 1 */
#ifndef PIN_WIRE1_SDA
#define PIN_WIRE1_SDA               (0u)
#endif
#ifndef PIN_WIRE1_SCL
#define PIN_WIRE1_SCL               (1u)
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
#define RS485_SERIAL_PORT           Serial2
#endif
#ifndef RS485_DEFAULT_TX_PIN
#define RS485_DEFAULT_TX_PIN        PIN_SERIAL2_TX
#endif
#ifndef RS485_DEFAULT_RE_PIN
#define RS485_DEFAULT_RE_PIN        (10u)
#endif
#ifndef RS485_DEFAULT_DE_PIN
#define RS485_DEFAULT_DE_PIN        (11u)
#endif
 
/* For Arduino ETHERNET library */
#ifndef PIN_SPI_SS_ETHERNET_LIB
#define PIN_SPI_SS_ETHERNET_LIB     (17u)
#endif
 
/* For Arduino CAN library */
#ifndef MCP2515_DEFAULT_SPI
#define MCP2515_DEFAULT_SPI         SPI1
#endif
#ifndef MCP2515_DEFAULT_CS_PIN
#define MCP2515_DEFAULT_CS_PIN      (9u)
#endif
#ifndef MCP2515_DEFAULT_INT_PIN
#define MCP2515_DEFAULT_INT_PIN     (12u)
#endif
 
/* Analog inputs connected to MCP3564 24 bits ADC */
static const uint8_t CONTROLLINO_MICRO_AI0 = (50u);
static const uint8_t CONTROLLINO_MICRO_AI1 = (51u);
static const uint8_t CONTROLLINO_MICRO_AI2 = (52u);
static const uint8_t CONTROLLINO_MICRO_AI3 = (53u);
static const uint8_t CONTROLLINO_MICRO_AI4 = (54u);
static const uint8_t CONTROLLINO_MICRO_AI5 = (55u);
 
/* Digital inputs connected to RP2040 */
static const uint8_t CONTROLLINO_MICRO_DI0 = (26u);
static const uint8_t CONTROLLINO_MICRO_DI1 = (27u);
static const uint8_t CONTROLLINO_MICRO_DI2 = (28u);
static const uint8_t CONTROLLINO_MICRO_DI3 = (29u);
 
/* Digital outputs connected to RP2040 */
static const uint8_t CONTROLLINO_MICRO_DO0 = (5u);
static const uint8_t CONTROLLINO_MICRO_DO1 = (6u);
static const uint8_t CONTROLLINO_MICRO_DO2 = (7u);
static const uint8_t CONTROLLINO_MICRO_DO3 = (20u);
static const uint8_t CONTROLLINO_MICRO_DO4 = (21u);
static const uint8_t CONTROLLINO_MICRO_DO5 = (22u);
static const uint8_t CONTROLLINO_MICRO_DO6 = (23u);
static const uint8_t CONTROLLINO_MICRO_DO7 = (24u);
 
/* ControllinoRp2040Pin API */
#include "controllino_wiring.h"

/* Enable digital output doPin -> CONTROLLINO_MICRO_DO0...D07 */
extern "C" void enableOut(uint8_t doPin);

/* Disable digital output doPin -> CONTROLLINO_MICRO_DO0...D07 */
extern "C" void disableOut(uint8_t doPin);

/* Micro internal diagnosys API */
#include "controllino_diag.h"


