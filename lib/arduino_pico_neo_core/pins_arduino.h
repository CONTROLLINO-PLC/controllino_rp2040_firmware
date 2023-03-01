#pragma once
 
/* Arduino pins API for NEO */
#include "neo_core_pin.h"
 
/* NEO core I/O */
class ControllinoNeoPin;
extern ControllinoNeoPin    NEO_CORE_AI0;
extern ControllinoNeoPin    NEO_CORE_AI1;
extern ControllinoNeoPin    NEO_CORE_AI2;
extern ControllinoNeoPin    NEO_CORE_AI3;
extern ControllinoNeoPin    NEO_CORE_AI4;
extern ControllinoNeoPin    NEO_CORE_AI5;
extern ControllinoNeoPin    NEO_CORE_AI6;
extern ControllinoNeoPin    NEO_CORE_AI9;

extern ControllinoNeoPin    NEO_CORE_AO0;
extern ControllinoNeoPin    NEO_CORE_AO1;
extern ControllinoNeoPin    NEO_CORE_AO2;
extern ControllinoNeoPin    NEO_CORE_AO3;

extern ControllinoNeoPin    NEO_CORE_DI0;
extern ControllinoNeoPin    NEO_CORE_DI1;
extern ControllinoNeoPin    NEO_CORE_DI2;
extern ControllinoNeoPin    NEO_CORE_DI3;

extern ControllinoNeoPin    NEO_CORE_DO0;
extern ControllinoNeoPin    NEO_CORE_DO1;
extern ControllinoNeoPin    NEO_CORE_DO2;
extern ControllinoNeoPin    NEO_CORE_DO3;
extern ControllinoNeoPin    NEO_CORE_DO4;
extern ControllinoNeoPin    NEO_CORE_DO5;
extern ControllinoNeoPin    NEO_CORE_DO6;
extern ControllinoNeoPin    NEO_CORE_DO7;
 
/* LEDs */
#define PIN_LED             (25u)
 
/* Serial */
#define PIN_SERIAL1_TX      (0u)
#define PIN_SERIAL1_RX      (1u)

#define PIN_SERIAL2_TX      (8u)
#define PIN_SERIAL2_RX      (9u)
 
/* SPI */
#define PIN_SPI0_MISO       (16u)
#define PIN_SPI0_MOSI       (19u)
#define PIN_SPI0_SCK        (18u)
#define PIN_SPI0_SS         (17u)

#define PIN_SPI1_MISO       (8u)
#define PIN_SPI1_MOSI       (11u)
#define PIN_SPI1_SCK        (10u)
#define PIN_SPI1_SS         (9u)
 
/* Wire */
#define PIN_WIRE0_SDA       (4u)
#define PIN_WIRE0_SCL       (5u)

#define PIN_WIRE1_SDA       (10u)
#define PIN_WIRE1_SCL       (11u)

#define SERIAL_HOWMANY      (3u)
#define SPI_HOWMANY         (2u)
#define WIRE_HOWMANY        (2u)

/* RP2040 */
#define PINS_COUNT          (30u)
#define NUM_DIGITAL_PINS    (30u)
#define NUM_ANALOG_INPUTS   (4u)
#define NUM_ANALOG_OUTPUTS  (0u)
#define ADC_RESOLUTION      (12u)

#define LED_BUILTIN PIN_LED

/* Exposed on pin header */
static const uint8_t D0 =   (0u);
static const uint8_t D1 =   (1u);
static const uint8_t D8 =   (8u);
static const uint8_t D9 =   (9u);
static const uint8_t D10 =  (10u);
static const uint8_t D11 =  (11u);

static const uint8_t A0 =   (26u);
static const uint8_t A1 =   (27u);
static const uint8_t A2 =   (28u);
static const uint8_t A3 =   (29u);

static const uint8_t SS = PIN_SPI0_SS;
static const uint8_t MOSI = PIN_SPI0_MOSI;
static const uint8_t MISO = PIN_SPI0_MISO;
static const uint8_t SCK =  PIN_SPI0_SCK;

static const uint8_t SDA = PIN_WIRE0_SDA;
static const uint8_t SCL =  PIN_WIRE0_SCL;

