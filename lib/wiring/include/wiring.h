/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef CONTROLLINO_WIRING_H
#define CONTROLLINO_WIRING_H
 
/**
 * \file controlino_pin_driver.h
 *
 * Arduino pins API for Controllino RP2040 boards
 * Based on https://github.com/arduino/ArduinoCore-mbed/tree/master/variants/NANO_RP2040_CONNECT
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include "Arduino.h"
 
#include "cy8c9520.h"
#include "mcp3564.h"
#include "ad5664.h"
 
/**
 * \brief Controllino Rp2040 pin class
 */
class ControllinoPin{
public:
	typedef enum { CY8C9520_PIN, MCP3564_PIN, AD5664_PIN, RP2040_PIN} _pin_type_t;
	ControllinoPin(int pin, _pin_type_t type): _pin(pin), _type(type)
	{
		setMode(INPUT);
		_setDigitalThreshold(~0U);
	};

	bool operator== (ControllinoPin const& other) const { return _pin == other._pin; };

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
 *\brief Get the ControllinoPin* from integer pin definition
 * 
 * \param pin Integer pin definition
 * \return ControllinoPin* or nullptr
 */
extern ControllinoPin* getControllinoPin(int pin);
 
/**
 *\brief Similar to Arduino API functions for compatibility with ControllinoPin*
 */
extern void pinMode(ControllinoPin* pin, PinMode mode);
extern PinStatus digitalRead(ControllinoPin* pin);
extern void digitalWrite(ControllinoPin* pin, PinStatus value);
extern int analogRead(ControllinoPin* pin);
extern void analogWrite(ControllinoPin* pin, int value);
 
/**
 *\brief Digital threshold API to implement a digital input with an analog input only pin 
 */
extern void setDigitalThreshold(ControllinoPin* pin, uint32_t threshold);
extern uint32_t getDigitalThreshold(ControllinoPin* pin);
extern void setDigitalThreshold(pin_size_t pin, uint32_t threshold); // From integer pin definition
extern uint32_t getDigitalThreshold(pin_size_t pin); // From integer pin definition
 
/**
 * \brief Peripherals interfaces
 */
extern cy8c9520_t* dev_cy8c9520;
extern mcp3564_t* dev_mcp3564;
extern ad5664_t* dev_ad5664;
 
#endif  // CONTROLLINO_WIRING_H