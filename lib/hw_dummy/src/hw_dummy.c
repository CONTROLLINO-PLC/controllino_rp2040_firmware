/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"

typedef struct {
    int num;
    bool state;
    platform_gpio_dir_t dir;
    platform_gpio_pull_mod_t pull;
} dummy_pin_t;

dummy_pin_t dummy_pin;

/* Init gpio pin */
platform_err_code_t platform_gpio_init(int pin, platform_gpio_dir_t dir, platform_gpio_pull_mod_t pull)
{
    dummy_pin.num = pin;
    dummy_pin.dir = dir;
    dummy_pin.pull = pull;
    switch (pull)
    {
    case PLATFORM_GPIO_PULL_DOWN:
    case PLATFORM_GPIO_PULL_DISABLED:
        dummy_pin.state = 0;
        break;
    case PLATFORM_GPIO_PULL_UP:
        dummy_pin.state = 1;
        break;
    }
    return PLATFORM_OK;
}
 
/* Set out gpio value */
platform_err_code_t platform_gpio_set(int pin, bool value)
{
    if (pin > -1 && dummy_pin.dir == PLATFORM_GPIO_OUT) {
        dummy_pin.state = value;
    }
    return PLATFORM_OK;
}
 
/* Get in gpio value */
platform_err_code_t platform_gpio_get(int pin, bool *value)
{
    if (pin > -1) {
        *value = dummy_pin.state;
    }
    return PLATFORM_OK;
}
 
/* Wait for specified milliseconds */
void platform_sleep_ms(uint32_t ms)
{
    
}
 
/* Wait for specified microseconds */
void platform_sleep_us(uint64_t us)
{
    
}
 
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
 
/* Init SPI interface */
platform_err_code_t platform_spi_init(hw_spi_t spi_hw, unsigned int speed, int mosi_pin, int miso_pin, int sck_pin)
{
    return PLATFORM_OK;
}
 
/* Change SPI settings */
platform_err_code_t platform_spi_set_config(hw_spi_t spi_hw, unsigned int speed, uint8_t mode, uint8_t bit_order)
{
    return PLATFORM_OK;
}
 
/* Write specified number of bytes to an SPI device */
platform_err_code_t platform_spi_write(hw_spi_t spi_hw, uint8_t* txdata, size_t len)
{
    return PLATFORM_OK;
}

/* Write and read specified number of bytes over SPI */
platform_err_code_t platform_spi_write_read(hw_spi_t spi_hw, uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    return PLATFORM_OK;
}