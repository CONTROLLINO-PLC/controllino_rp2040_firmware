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
#include "wsen_temp.h"
 
/**
 * \brief Controllino Neo pin class
 */
class ControllinoNeoPin{
public:
	typedef enum { CY8C95XX_PIN, MCP356X_PIN, AD56X4_PIN, RP2040_PIN } _pin_type_t;
	ControllinoNeoPin(int pin, _pin_type_t type): _pin(pin), _type(type)
	{
		setMode(INPUT);
		_setDigitalThreshold(~0U);
	};

	bool operator== (ControllinoNeoPin const& other) const { return _pin == other._pin; };

	pin_size_t getPin(void) { return _pin; };
	_pin_type_t getType(void) { return _type; };

	void setMode(PinMode mode) { _mode = mode; };
	PinMode getMode(void) { return _mode; };

	void _setDigitalThreshold(uint32_t threshold) { _digitalThreshold = threshold; };
	uint32_t _getDigitalThreshold(void) { return _digitalThreshold; };
private:
	pin_size_t _pin;
	_pin_type_t _type;
	PinMode _mode;
	uint32_t _digitalThreshold;
};

/**
 *\brief Get the ControllinoNeoPin* from integer pin definition
 * 
 * \param pin Integer pin definition
 * \return ControllinoNeoPin* or nullptr
 */
ControllinoNeoPin* getControllinoNeoPin(int pin);

/**
 *\brief Similar to Arduino API functions for compatibility with ControllinoNeoPin*
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
void setDigitalThreshold(pin_size_t pin, uint32_t threshold); // From integer pin definition
uint32_t getDigitalThreshold(pin_size_t pin); // From integer pin definition
 
/**
 * \brief User can access peripherals interfaces
 */
extern cy8c95xx_t* neo_cy8c95xx;
extern mcp356x_t* neo_mcp356x;
extern ad56x4_t* neo_ad56x4;
extern bts71220_t* neo_bts71220;
extern wsen_temp_t* neo_wsen_temp;
 
/**
 * \brief User can access the pin definitions for ControllinoNeoPin API
 */
extern ControllinoNeoPin* _NEO_CORE_AI0;
extern ControllinoNeoPin* _NEO_CORE_AI1;
extern ControllinoNeoPin* _NEO_CORE_AI2;
extern ControllinoNeoPin* _NEO_CORE_AI3;
extern ControllinoNeoPin* _NEO_CORE_AI4;
extern ControllinoNeoPin* _NEO_CORE_AI5;
extern ControllinoNeoPin* _NEO_CORE_AI6;
extern ControllinoNeoPin* _NEO_CORE_AI7;

extern ControllinoNeoPin* _NEO_CORE_AO0;
extern ControllinoNeoPin* _NEO_CORE_AO1;
extern ControllinoNeoPin* _NEO_CORE_AO2;
extern ControllinoNeoPin* _NEO_CORE_AO3;

extern ControllinoNeoPin* _NEO_CORE_DO4;
extern ControllinoNeoPin* _NEO_CORE_DO5;
extern ControllinoNeoPin* _NEO_CORE_DO6;
extern ControllinoNeoPin* _NEO_CORE_DO7;

extern ControllinoNeoPin* _NEO_CORE_DI0;
extern ControllinoNeoPin* _NEO_CORE_DI1;
extern ControllinoNeoPin* _NEO_CORE_DI2;
extern ControllinoNeoPin* _NEO_CORE_DI3;

extern ControllinoNeoPin* _NEO_CORE_DO0;
extern ControllinoNeoPin* _NEO_CORE_DO1;
extern ControllinoNeoPin* _NEO_CORE_DO2;
extern ControllinoNeoPin* _NEO_CORE_DO3;
 
#endif  // NEO_CORE_PIN_H