/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "hw_platform.h"
 
/* Init gpio pin */
int platform_gpio_init(int pin, uint dir, uint pull)
{
    if (pin > -1) {
        gpio_init(pin);
        gpio_set_dir(pin, dir == PLATFORM_GPIO_IN ? GPIO_IN : GPIO_OUT);
        if (pull != PLATFORM_GPIO_PULL_DISABLED) {
            gpio_set_pulls(pin, pull == PLATFORM_GPIO_PULL_UP ? true : false, pull == PLATFORM_GPIO_PULL_DOWN ? true : false);
        }
    }
    return PLATFORM_OK;
}
 
/* Set out gpio value */
void platform_gpio_set(int pin, bool value)
{
    if (pin > -1) {
        gpio_put(pin, value ? 1 : 0);
    }
}
 
/* Get in gpio value */
bool platform_gpio_get(int pin)
{
    if (pin > -1) {
        return gpio_get(pin) ? true : false;
    }
    return false;
}
 
/* Wait for specified milliseconds */
void platform_sleep_ms(uint32_t ms)
{
    sleep_ms(ms);
}
 
/* Init i2c interface */
int platform_i2c_init(hw_i2c_t* i2c_hw, uint speed, int sda_pin, int scl_pin)
{
    if ((i2c_hw != (hw_i2c_t*)i2c0 && i2c_hw != (hw_i2c_t*)i2c1) || !sda_pin || !scl_pin)
        return PLATFORM_I2C_INIT_ERROR;
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    i2c_init((i2c_inst_t*)i2c_hw, speed);
    return PLATFORM_OK;
}
 
/* Attempt to read specified number of bytes from address over i2c */
int platform_i2c_read(hw_i2c_t* i2c, uint8_t addr, uint8_t* rxdata, size_t len)
{
    if (i2c_read_blocking((i2c_inst_t*)i2c, addr, rxdata, len, false) != len)
        return PLATFORM_I2C_COM_ERROR;
    return PLATFORM_OK;
}
 
/* Attempt to write specified number of bytes to address over i2c */
int platform_i2c_write(hw_i2c_t* i2c, uint8_t addr, const uint8_t* txdata, size_t len)
{
    if (i2c_write_blocking((i2c_inst_t*)i2c, addr, txdata, len, false) != len)
        return PLATFORM_I2C_COM_ERROR;
    return PLATFORM_OK;
}