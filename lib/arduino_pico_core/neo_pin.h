/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef NEO_PIN_H
#define NEO_PIN_H
 
/**
 * \file neo_pins.h
 *
 * Arduino pins API for NEO boards
 * Based on https://github.com/arduino/ArduinoCore-mbed/tree/master/variants/NANO_RP2040_CONNECT
 */
 
#include "Arduino.h"
#include "cy8c95xx.h"
#include "mcp356x.h"
#include "ad56x4.h"
 
/**
 * \brief Class to diferenciate CONTROLLINO NEO pins
 */
class ControllinoNeoPin{
public:
	typedef enum {
		NATIVE_PIN,
		CY8C95XX_PIN,
		MCP356X_PIN,
		AD56X4_PIN
	} _pin_type_t;
	ControllinoNeoPin(int pin, _pin_type_t type): _pin(pin), _type(type) { _mode = INPUT; };
	pin_size_t getPin() { return _pin; };
	_pin_type_t getType() { return _type; };
	void setMode(PinMode mode) { _mode = mode; };
	PinMode getMode() { return _mode; };
	bool operator== (ControllinoNeoPin const& other) const { return _pin == other._pin; };
	__attribute__((error("Change to a #define"))) operator int();
private:
	pin_size_t _pin;
	_pin_type_t _type;
	PinMode _mode;
};
 
/**
 *\brief Arduino API functions for compatibility with CONTROLLINO NEO
 */
void pinMode(ControllinoNeoPin pin, PinMode mode);
PinStatus digitalRead(ControllinoNeoPin pin);
void digitalWrite(ControllinoNeoPin pin, PinStatus value);
int analogRead(ControllinoNeoPin pin);
void analogWrite(ControllinoNeoPin pin, int value);
 
/* Public instances of internal peripherals drivers */
extern cy8c95xx_t neo_cy8c9520; 
extern mcp356x_t neo_mcp3564;
extern ad56x4_t neo_ad5664;
 
/* Neo core pins */
extern ControllinoNeoPin  AI0;
extern ControllinoNeoPin  AI1;
extern ControllinoNeoPin  AI2;
extern ControllinoNeoPin  AI3;
extern ControllinoNeoPin  AI4;
extern ControllinoNeoPin  AI5;
extern ControllinoNeoPin  AI6;
extern ControllinoNeoPin  AI9;

extern ControllinoNeoPin  AO0;
extern ControllinoNeoPin  AO1;
extern ControllinoNeoPin  AO2;
extern ControllinoNeoPin  AO3;

extern ControllinoNeoPin  DI0;
extern ControllinoNeoPin  DI1;
extern ControllinoNeoPin  DI2;
extern ControllinoNeoPin  DI3;

extern ControllinoNeoPin  DO0;
extern ControllinoNeoPin  DO1;
extern ControllinoNeoPin  DO2;
extern ControllinoNeoPin  DO3;
extern ControllinoNeoPin  DO4;
extern ControllinoNeoPin  DO5;
extern ControllinoNeoPin  DO6;
extern ControllinoNeoPin  DO7;
 
#endif  // BTS71220_H