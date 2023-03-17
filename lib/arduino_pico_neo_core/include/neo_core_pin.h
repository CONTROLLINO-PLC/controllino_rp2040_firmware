/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef NEO_CORE_PIN_H
#define NEO_CORE_PIN_H
 
/**
 * \file neo_core_pin.h
 *
 * Arduino pins API for NEO core
 * Based on https://github.com/arduino/ArduinoCore-mbed/tree/master/variants/NANO_RP2040_CONNECT
 */
 
#include "Arduino.h"
 
#include "cy8c95xx.h"
#include "mcp356x.h"
#include "ad56x4.h"
#include "bts71220.h"
 
extern cy8c95xx_t* neo_cy8c95xx;
extern mcp356x_t* neo_mcp356x;
extern ad56x4_t* neo_ad56x4;
extern bts71220_t* neo_bts71220;
 
/**
 * \brief Controllino Neo pin class
 */
class ControllinoNeoPin{
public:
	typedef enum { CY8C95XX_PIN, MCP356X_PIN, AD56X4_PIN, NATIVE_PIN } _pin_type_t;
	ControllinoNeoPin(int pin, _pin_type_t type): _pin(pin), _type(type)
	{
		setMode(INPUT);
		_setDigitalThreshold(~0U);
	};

	bool operator== (ControllinoNeoPin const& other) const { return _pin == other._pin; };

	pin_size_t getPin() { return _pin; };
	_pin_type_t getType() { return _type; };

	void setMode(PinMode mode) { _mode = mode; };
	PinMode getMode() { return _mode; };

	void _setDigitalThreshold(uint32_t threshold) { _digitalThreshold = threshold; };
	uint32_t _getDigitalThreshold() { return _digitalThreshold; };
private:
	pin_size_t _pin;
	_pin_type_t _type;
	PinMode _mode;
	uint32_t _digitalThreshold;
};
 
/**
 *\brief Arduino API functions for compatibility with Controllino Neo
 */
 
void pinMode(ControllinoNeoPin* pin, PinMode mode);
PinStatus digitalRead(ControllinoNeoPin* pin);
void digitalWrite(ControllinoNeoPin* pin, PinStatus value);
int analogRead(ControllinoNeoPin* pin);
void analogWrite(ControllinoNeoPin* pin, int value);
 
/**
 *\brief Digital threshold API to implement a digital input with an analog input only pin 
 */
void setDigitalThreshold(ControllinoNeoPin* pin, uint32_t threshold);
uint32_t getDigitalThreshold(ControllinoNeoPin* pin);
 
#endif  // NEO_CORE_PIN_H