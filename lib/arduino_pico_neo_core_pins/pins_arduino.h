#pragma once

class ControllinoNeoPin;
extern ControllinoNeoPin  NEO_AI0;
extern ControllinoNeoPin  NEO_AI1;
extern ControllinoNeoPin  NEO_AI2;
extern ControllinoNeoPin  NEO_AI3;
extern ControllinoNeoPin  NEO_AI4;
extern ControllinoNeoPin  NEO_AI5;
extern ControllinoNeoPin  NEO_AI6;
extern ControllinoNeoPin  NEO_AI9;

extern ControllinoNeoPin  NEO_AO0;
extern ControllinoNeoPin  NEO_AO1;
extern ControllinoNeoPin  NEO_AO2;
extern ControllinoNeoPin  NEO_AO3;

extern ControllinoNeoPin  NEO_DI0;
extern ControllinoNeoPin  NEO_DI1;
extern ControllinoNeoPin  NEO_DI2;
extern ControllinoNeoPin  NEO_DI3;

extern ControllinoNeoPin  NEO_DO0;
extern ControllinoNeoPin  NEO_DO1;
extern ControllinoNeoPin  NEO_DO2;
extern ControllinoNeoPin  NEO_DO3;
extern ControllinoNeoPin  NEO_DO4;
extern ControllinoNeoPin  NEO_DO5;
extern ControllinoNeoPin  NEO_DO6;
extern ControllinoNeoPin  NEO_DO7;

/* LEDs */
#define PIN_LED        (25u)
 
/* Serial */
#define PIN_SERIAL1_TX (0u)
#define PIN_SERIAL1_RX (1u)

#define PIN_SERIAL2_TX (8u)
#define PIN_SERIAL2_RX (9u)
 
/* SPI */
#define PIN_SPI0_MISO  (16u)
#define PIN_SPI0_MOSI  (19u)
#define PIN_SPI0_SCK   (18u)
#define PIN_SPI0_SS    (17u)

#define PIN_SPI1_MISO  (8u)
#define PIN_SPI1_MOSI  (11u)
#define PIN_SPI1_SCK   (10u)
#define PIN_SPI1_SS    (9u)
 
/* Wire */
#define PIN_WIRE0_SDA  (4u)
#define PIN_WIRE0_SCL  (5u)

#define PIN_WIRE1_SDA  (10u)
#define PIN_WIRE1_SCL  (11u)

#define SERIAL_HOWMANY (3u)
#define SPI_HOWMANY    (2u)
#define WIRE_HOWMANY   (2u)
 
#include "../generic/common.h"
#include "neo_pin.h"

