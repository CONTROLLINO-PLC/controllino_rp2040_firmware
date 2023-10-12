/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
 
typedef struct i2c_inst_t _hw_i2c_t;
hw_i2c_t PLATFORM_I2C_HW = (hw_i2c_t)   i2c1;
const unsigned int PLATFORM_I2C_SPEED = 100000;
const int PLATFORM_I2C_SDA =            2;
const int PLATFORM_I2C_SCL =            3;
 
/* Init I2C interface */
platform_err_code_t platform_i2c_init(hw_i2c_t i2c_hw, unsigned int speed, int sda_pin, int scl_pin)
{
    if ((i2c_hw != (hw_i2c_t)i2c0 && i2c_hw != (hw_i2c_t)i2c1) ||
        (sda_pin < 0 || sda_pin > 29) ||
        (scl_pin < 0 || scl_pin > 29) ||
        (speed < 1000 || speed > 1000000))
    {
        return PLATFORM_ARGUMENT_ERR;
    }
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
    i2c_deinit((i2c_inst_t*)i2c_hw);
    if (i2c_init((i2c_inst_t*)i2c_hw, speed) != speed)
        return PLATFORM_I2C_INIT_ERR;
    i2c_set_slave_mode((i2c_inst_t*)i2c_hw, false, 0);
    return PLATFORM_OK;
}
 
/* Attempt to read specified number of bytes from address over I2C */
platform_err_code_t platform_i2c_read(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* rxdata, size_t len)
{
    if (i2c_read_blocking((i2c_inst_t*)i2c_hw, addr, rxdata, len, false) != len)
        return PLATFORM_I2C_COM_ERR;
    return PLATFORM_OK;
}
 
/* Attempt to write specified number of bytes to address over I2C */
platform_err_code_t platform_i2c_write(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* txdata, size_t len)
{
    if (i2c_write_blocking((i2c_inst_t*)i2c_hw, addr, txdata, len, false) != len)
        return PLATFORM_I2C_COM_ERR;
    return PLATFORM_OK;
}