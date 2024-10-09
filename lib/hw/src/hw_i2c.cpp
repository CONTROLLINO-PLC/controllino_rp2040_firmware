/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
#include "Wire.h"

#ifndef PLATFORM_I2C_HW_CUSTOM
hw_i2c_t PLATFORM_I2C_HW = (hw_i2c_t)&Wire;
#else
hw_i2c_t PLATFORM_I2C_HW = (hw_i2c_t)PLATFORM_I2C_HW_CUSTOM;
#endif
#ifndef PLATFORM_I2C_SPEED
const unsigned int PLATFORM_I2C_SPEED = 100000;
#endif
#ifndef PLATFORM_I2C_SDA
const int PLATFORM_I2C_SDA = 2;
#endif
#ifndef PLATFORM_I2C_SCL
const int PLATFORM_I2C_SCL = 3;
#endif

static bool Wire_IsInitialized = false;
static bool Wire1_IsInitialized = false;

/* Init I2C interface */
platform_err_code_t platform_i2c_init(hw_i2c_t i2c_hw, unsigned int speed, int sda_pin, int scl_pin)
{
    if ((i2c_hw != (hw_i2c_t)&Wire && i2c_hw != (hw_i2c_t)&Wire1) ||
        (sda_pin < 0 || sda_pin > 29) ||
        (scl_pin < 0 || scl_pin > 29))
    {
        return PLATFORM_ARGUMENT_ERR;
    }
    TwoWire* _I2C = (TwoWire*)i2c_hw;

    // Check initialized
    if ((_I2C == &Wire) && Wire_IsInitialized) {
        _I2C->setClock(speed);
        return PLATFORM_OK;
    }
    else {
        Wire_IsInitialized = true;
    }
    if ((_I2C == &Wire1) && Wire1_IsInitialized) {
        _I2C->setClock(speed);
        return PLATFORM_OK;
    }
    else {
        Wire1_IsInitialized = true;
    }
    
    // Init
    _I2C->setSDA(sda_pin);
    _I2C->setSCL(scl_pin);
    _I2C->setClock(speed);
    _I2C->begin();
    return PLATFORM_OK;
}
 
/* Attempt to read specified number of bytes from address over I2C */
platform_err_code_t platform_i2c_read(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* rxdata, size_t len)
{
    TwoWire* _I2C = (TwoWire*)i2c_hw;
    if (_I2C->requestFrom(addr, len, false) != len)
        return PLATFORM_I2C_COM_ERR;
    
    while (_I2C->available())
    {
        *rxdata = _I2C->read();
        rxdata++;
    }
    return PLATFORM_OK;
}
 
/* Attempt to write specified number of bytes to address over I2C */
platform_err_code_t platform_i2c_write(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* txdata, size_t len)
{
    TwoWire* _I2C = (TwoWire*)i2c_hw;
    _I2C->beginTransmission(addr);
    _I2C->write(txdata, len);
    if (_I2C->endTransmission() != 0)
        return PLATFORM_I2C_COM_ERR;
    return PLATFORM_OK;
}