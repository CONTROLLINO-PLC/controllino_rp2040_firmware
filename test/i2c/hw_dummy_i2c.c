/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifdef NATIVE_TEST_ENV
 
#include "hw_platform.h"
 
typedef struct
{} i2c_inst_t;
static uint8_t dummy_for_pointer;
typedef struct i2c_inst_t _hw_i2c_t;
hw_i2c_t PLATFORM_I2C_HW = (hw_i2c_t)&dummy_for_pointer;
const unsigned int PLATFORM_I2C_SPEED;
const int PLATFORM_I2C_SDA;
const int PLATFORM_I2C_SCL;
 
/* Init I2C interface */
platform_err_code_t platform_i2c_init(hw_i2c_t i2c_hw, unsigned int speed, int sda_pin, int scl_pin)
{
    return PLATFORM_OK;
}
 
/* Attempt to read specified number of bytes from address over I2C */
platform_err_code_t platform_i2c_read(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* rxdata, size_t len)
{
    return PLATFORM_OK;
}
 
/* Attempt to write specified number of bytes to address over I2C */
platform_err_code_t platform_i2c_write(hw_i2c_t i2c_hw, uint8_t addr, const uint8_t* txdata, size_t len)
{
    return PLATFORM_OK;
}
 
#endif