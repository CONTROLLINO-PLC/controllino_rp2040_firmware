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
 
/* Wait for specified microseconds */
void platform_sleep_us(uint64_t us)
{
    sleep_us(us);
}
 
/* Init I2C interface */
int platform_i2c_init(hw_i2c_t* i2c_hw, uint speed, int sda_pin, int scl_pin)
{
    if ((i2c_hw != (hw_i2c_t*)i2c0 && i2c_hw != (hw_i2c_t*)i2c1) || (sda_pin < 0 && sda_pin > 31) || (scl_pin < 0 && scl_pin > 31))
        return PLATFORM_I2C_INIT_ERROR;
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    i2c_init((i2c_inst_t*)i2c_hw, speed);
    return PLATFORM_OK;
}
 
/* Attempt to read specified number of bytes from address over I2C */
int platform_i2c_read(hw_i2c_t* i2c_hw, uint8_t addr, uint8_t* rxdata, size_t len)
{
    if (i2c_read_blocking((i2c_inst_t*)i2c_hw, addr, rxdata, len, false) != len)
        return PLATFORM_I2C_COM_ERROR;
    return PLATFORM_OK;
}
 
/* Attempt to write specified number of bytes to address over I2C */
int platform_i2c_write(hw_i2c_t* i2c_hw, uint8_t addr, const uint8_t* txdata, size_t len)
{
    if (i2c_write_blocking((i2c_inst_t*)i2c_hw, addr, txdata, len, false) != len)
        return PLATFORM_I2C_COM_ERROR;
    return PLATFORM_OK;
}
 
/* Init SPI interface */
int platform_spi_init(hw_spi_t* spi_hw, uint speed, int mosi_pin, int miso_pin, int sck_pin)
{
    // Check arguments
    if ((spi_hw != (hw_spi_t*)spi0 && spi_hw != (hw_spi_t*)spi1))
        return PLATFORM_I2C_INIT_ERROR;
    if ((mosi_pin < 0 && mosi_pin > 31) || (miso_pin < 0 && miso_pin > 31) || (sck_pin < 0 && sck_pin > 31))
        return PLATFORM_I2C_INIT_ERROR;
    // Init SPI gpios
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    gpio_set_function(miso_pin, GPIO_FUNC_SPI);
    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    // Init interface
    spi_init((spi_inst_t*)spi_hw, speed);
    return PLATFORM_OK;
}
 
/* Change SPI settings */
int platform_spi_set_config(hw_spi_t* spi_hw, uint speed, uint8_t mode, uint8_t bit_order)
{
    spi_cpol_t cpol;
    spi_cpha_t cpha;
    spi_order_t order;
    // Check arguments
    if ((mode != PLATFORM_SPI_MODE_0) && (mode != PLATFORM_SPI_MODE_1) && (mode != PLATFORM_SPI_MODE_2) && (mode != PLATFORM_SPI_MODE_3))
        return PLATFORM_SPI_INIT_ERROR;
    if ((bit_order != PLATFORM_SPI_LSBFIRST) && (bit_order != PLATFORM_SPI_MSBFIRST))
        return PLATFORM_SPI_INIT_ERROR;
    // Set SPI settings
    switch (mode)
    {
    case PLATFORM_SPI_MODE_1:
        cpol = SPI_CPOL_0;
        cpha = SPI_CPHA_1;
        break;
    case PLATFORM_SPI_MODE_2:
        cpol = SPI_CPOL_1;
        cpha = SPI_CPHA_0;
        break;
    case PLATFORM_SPI_MODE_3:
        cpol = SPI_CPOL_1;
        cpha = SPI_CPHA_1;
        break;
    default: // PLATFORM_SPI_MODE_0
        cpol = SPI_CPOL_0;
        cpha = SPI_CPHA_0;
        break;
    }
    if (bit_order == PLATFORM_SPI_LSBFIRST)
        order = SPI_LSB_FIRST;
    else
        order = SPI_MSB_FIRST;

    spi_set_baudrate((spi_inst_t*)spi_hw, speed);
    spi_set_format((spi_inst_t*)spi_hw, 8, cpol, cpha, order);
    return PLATFORM_OK;
}
 
/* Write specified number of bytes to an SPI device */
int platform_spi_write(hw_spi_t* spi_hw, uint8_t* txdata, size_t len)
{
    size_t ret;
    ret = spi_write_blocking((spi_inst_t*)spi_hw, txdata, len);
    if (ret != len)
        return PLATFORM_SPI_COM_ERROR;
    return PLATFORM_OK;
}

/* Write and read specified number of bytes over SPI */
int platform_spi_write_read(hw_spi_t* spi_hw, uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (spi_write_read_blocking((spi_inst_t*)spi_hw, txdata, rxdata, len) != len)
        return PLATFORM_SPI_COM_ERROR;
    return PLATFORM_OK;
}