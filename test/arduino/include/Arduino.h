/**
 * \file Arduino.h
 * \author Mock some arduino defines and functions to run native tests
 * 
 */
 
#pragma once
 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
 
typedef uint8_t pin_size_t;
typedef unsigned int uint;
 
typedef enum {
    LOW = 0,
    HIGH = 1,
    CHANGE = 2,
    FALLING = 3,
    RISING = 4,
} PinStatus;
 
typedef enum {
    INPUT = 0x0,
    OUTPUT = 0x1,
    INPUT_PULLUP = 0x2,
    INPUT_PULLDOWN = 0x3,
    OUTPUT_2MA = 0x4,
    OUTPUT_4MA = 0x5,
    OUTPUT_8MA = 0x6,
    OUTPUT_12MA = 0x7,
} PinMode;
 
/* Pin API */
extern "C" void pinMode(pin_size_t ulPin, PinMode ulMode);
extern "C" void digitalWrite(pin_size_t ulPin, PinStatus ulVal);
extern "C" PinStatus digitalRead(pin_size_t ulPin);
extern "C" void analogWrite(pin_size_t pin, int val);
extern "C" int analogRead(pin_size_t pin);

/* RP2040 GPIO API */
extern "C" void gpio_set_input_hysteresis_enabled(uint gpio, bool enabled);
extern "C" bool gpio_is_input_hysteresis_enabled(uint gpio);

/* Arduino-pico API */
void initVariant();
 
#include "pins_arduino.h"	