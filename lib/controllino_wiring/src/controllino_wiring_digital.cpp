/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "controllino_wiring.h"
 
/* Controllino RP2040 digital API */
void pinMode(ControllinoRp2040Pin* pin, PinMode mode)
{
    switch (pin->getType())
    {
    case ControllinoRp2040Pin::RP2040_PIN:
        pinMode(pin->getPin(), mode);
        break;
    case ControllinoRp2040Pin::CY8C9520_PIN: // cy8c9520.h
        cy8c9520_dir_mode_t dir;
        cy8c9520_drv_mode_t drv;
        switch (mode)
        {
        case OUTPUT:
        case OUTPUT_2MA:
        case OUTPUT_4MA:
        case OUTPUT_8MA:
        case OUTPUT_12MA:
            mode = OUTPUT;
        case INPUT_PULLDOWN:
            dir = CY8C9520_GPIO_IN;
            drv = CY8C9520_DRV_PULL_DOWN;
            break;
        default:
            mode = INPUT_PULLUP;
            dir = CY8C9520_GPIO_IN;
            drv = CY8C9520_DRV_PULL_UP;
            break;
        }
        cy8c9520_dis_pin_pwm(dev_cy8c9520, (int)pin->getPin()); // Disable PWM
        cy8c9520_pin_mode(dev_cy8c9520, (int)pin->getPin(), dir, drv);
        break;
        // Other pin types has fixed modes 
    case ControllinoRp2040Pin::MCP3564_PIN:
        mode = INPUT;
        break;
    case ControllinoRp2040Pin::AD5664_PIN:
        mode = OUTPUT;
        break;
    }
    pin->setMode(mode);
}

PinStatus digitalRead(ControllinoRp2040Pin* pin)
{
    PinStatus pinStatus = LOW;
    switch (pin->getType())
    {
    case ControllinoRp2040Pin::RP2040_PIN:
        pinStatus = digitalRead(pin->getPin());
        break;
    case ControllinoRp2040Pin::CY8C9520_PIN: // cy8c9520.h
        uint8_t pinState;
        switch (pin->getMode())
        {
        case OUTPUT:
        case OUTPUT_4MA:
        case OUTPUT_2MA:
        case OUTPUT_8MA:
        case OUTPUT_12MA:
            cy8c9520_read_pin_out_lvl(dev_cy8c9520, (int)pin->getPin(), &pinState);
            break;
        default:
            cy8c9520_read_pin(dev_cy8c9520, (int)pin->getPin(), &pinState);
            break;
        }
        pinStatus = pinState ? HIGH : LOW;
        break;
    case ControllinoRp2040Pin::MCP3564_PIN:
        pinStatus = (analogRead(pin) >= pin->_getDigitalThreshold()) ? HIGH : LOW;
        break;
    default:
        // In other pins digitalRead does not make sense
        break;
    }
    return pinStatus;
}

void digitalWrite(ControllinoRp2040Pin* pin, PinStatus value)
{
    switch (pin->getType())
    {
    case ControllinoRp2040Pin::RP2040_PIN:
        digitalWrite(pin->getPin(), value);
        break;
    case ControllinoRp2040Pin::CY8C9520_PIN: // cy8c9520.h
        if (pin->getMode() == OUTPUT) {
            if (value == HIGH)
                cy8c9520_pin_mode(dev_cy8c9520, (int)pin->getPin(), CY8C9520_GPIO_OUT, CY8C9520_DRV_STRONG);
            else
                cy8c9520_pin_mode(dev_cy8c9520, (int)pin->getPin(), CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);
            cy8c9520_write_pin(dev_cy8c9520, (int)pin->getPin(), (uint8_t)value);
            cy8c9520_dis_pin_pwm(dev_cy8c9520, (int)pin->getPin()); // Disable PWM
        }
        break;
    default:
        // Other pin types are analog only
        break;
    }
}
 
/* Set the digital threshold to implement a digital input with an analog input only pin */
void setDigitalThreshold(ControllinoRp2040Pin* pin, uint32_t threshold)
{
    switch (pin->getType())
    {
    case ControllinoRp2040Pin::MCP3564_PIN:
        pin->_setDigitalThreshold(threshold);
        break;
    default:
        // Other pin types are not analog inputs
        break;
    }
}
 
void setDigitalThreshold(pin_size_t pin, uint32_t threshold) {
    if (getControllinoRp2040Pin(pin) != nullptr)
        setDigitalThreshold(getControllinoRp2040Pin(pin), threshold);
}
 
/* Get current digital threshold */
uint32_t getDigitalThreshold(ControllinoRp2040Pin* pin)
{
    return pin->_getDigitalThreshold();
}

uint32_t getDigitalThreshold(pin_size_t pin) {
    if (getControllinoRp2040Pin(pin) != nullptr)
        return getDigitalThreshold(getControllinoRp2040Pin(pin));
    return 0;
}
 
/* Trick arduino API to handle NEO pins */ 
extern "C" void __pinMode(pin_size_t pin, PinMode mode);
extern "C" void __digitalWrite(pin_size_t pin, PinStatus val);
extern "C" PinStatus __digitalRead(pin_size_t pin);
 
void pinMode(pin_size_t pin, PinMode mode) {
    if (pin < 32) { // Call Arduino API because is an RP2040 pin
        gpio_set_input_hysteresis_enabled(pin, false); // Disable input histerisys
        __pinMode(pin, mode);
    }
    else if (getControllinoRp2040Pin(pin) != nullptr) {
        pinMode(getControllinoRp2040Pin(pin), mode);
    }
    else {
        asm volatile("nop");
    }
}
 
void digitalWrite(pin_size_t pin, PinStatus val) {
    if (pin < 32) {
        __digitalWrite(pin, val);
    }
    else if (getControllinoRp2040Pin(pin) != nullptr) {
        digitalWrite(getControllinoRp2040Pin(pin), val);
    }
}
 
PinStatus digitalRead(pin_size_t pin) {
    if (pin < 32) {
        return __digitalRead(pin);
    }
    else if (getControllinoRp2040Pin(pin) != nullptr) {
        return digitalRead(getControllinoRp2040Pin(pin));
    }
    return LOW;
}