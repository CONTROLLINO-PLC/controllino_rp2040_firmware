/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifdef NATIVE_ENV
 
#include "hw_platform.h"
 
static uint8_t dummy_for_pointer;
hw_i2c_t PLATFORM_I2C_HW = (hw_i2c_t)&dummy_for_pointer;
const unsigned int PLATFORM_I2C_SPEED = 0;
const int PLATFORM_I2C_SDA = 0;
const int PLATFORM_I2C_SCL = 0;
 
/* Test doubles to simulate and check i2c transfers */
extern platform_err_code_t mock_i2c_read(uint8_t addr, uint8_t* rxdata, size_t len);
extern platform_err_code_t mock_i2c_write(uint8_t addr, uint8_t* txdata, size_t len);
 
/* Init I2C interface */
platform_err_code_t platform_i2c_init(hw_i2c_t i2c_hw, unsigned int speed, int sda_pin, int scl_pin)
{
    return PLATFORM_OK;
}
 
/* Attempt to read specified number of bytes from address over I2C */
platform_err_code_t platform_i2c_read(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* rxdata, size_t len)
{
    return mock_i2c_read(addr, rxdata, len);
}
 
/* Attempt to write specified number of bytes to address over I2C */
platform_err_code_t platform_i2c_write(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* txdata, size_t len)
{
    return mock_i2c_write(addr, txdata, len);
}
 
#endif