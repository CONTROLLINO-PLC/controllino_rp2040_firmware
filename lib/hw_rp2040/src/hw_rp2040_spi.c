/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
 
typedef struct spi_inst_t _hw_spi_t;
hw_spi_t PLATFORM_SPI_HW = (hw_spi_t)   spi0;
const unsigned int PLATFORM_SPI_SPEED = 1000000;
const int PLATFORM_SPI_MOSI =           19;
const int PLATFORM_SPI_MISO =           16;
const int PLATFORM_SPI_SCK = 18;
 
/* Init SPI interface */
platform_err_code_t platform_spi_init(hw_spi_t spi_hw, unsigned int speed, int mosi_pin, int miso_pin, int sck_pin)
{
    // Check arguments
    if ((spi_hw != (hw_spi_t)spi0 && spi_hw != (hw_spi_t)spi1) ||
        (mosi_pin < 0 || mosi_pin > 29) ||
        (miso_pin < 0 || miso_pin > 29) ||
        (sck_pin < 0 || sck_pin > 29) ||
        (speed < 1000 || speed > 2000000))
    {
        return PLATFORM_ARGUMENT_ERR;
    }
    // Init SPI gpios
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    gpio_set_function(miso_pin, GPIO_FUNC_SPI);
    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    // Init interface
    spi_deinit((spi_inst_t*)spi_hw);
    if (spi_init((spi_inst_t*)spi_hw, speed) != speed)
        return PLATFORM_SPI_INIT_ERR;
    return PLATFORM_OK;
}
 
/* Change SPI settings */
platform_err_code_t platform_spi_set_config(hw_spi_t spi_hw, unsigned int speed, uint8_t mode, uint8_t bit_order)
{
    spi_cpol_t cpol;
    spi_cpha_t cpha;
    spi_order_t order;
    // Check arguments
    if ((mode != PLATFORM_SPI_MODE_0 && mode != PLATFORM_SPI_MODE_1 && mode != PLATFORM_SPI_MODE_2 && mode != PLATFORM_SPI_MODE_3) ||
        (bit_order != PLATFORM_SPI_LSBFIRST && bit_order != PLATFORM_SPI_MSBFIRST) ||
        (speed < 1000 || speed > 2000000))
    {
        return PLATFORM_ARGUMENT_ERR;
    }
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
    spi_deinit((spi_inst_t*)spi_hw);
    if (spi_init((spi_inst_t*)spi_hw, speed) != speed)
        return PLATFORM_SPI_COM_ERR;
    spi_set_format((spi_inst_t*)spi_hw, 8, cpol, cpha, order);
    return PLATFORM_OK;
}
 
/* Write specified number of bytes to an SPI device */
platform_err_code_t platform_spi_write(hw_spi_t spi_hw, void(*cs_select)(int), void(*cs_deselect)(int), int cs_pin, uint8_t* txdata, size_t len)
{
    size_t ret;
    (*cs_select)(cs_pin);
    ret = spi_write_blocking((spi_inst_t*)spi_hw, txdata, len);
    (*cs_deselect)(cs_pin);
    if (ret != len)
        return PLATFORM_SPI_COM_ERR;
    return PLATFORM_OK;
}
 
/* Write and read specified number of bytes over SPI */
platform_err_code_t platform_spi_write_read(hw_spi_t spi_hw, void(*cs_select)(int), void(*cs_deselect)(int), int cs_pin, uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    size_t ret;
    (*cs_select)(cs_pin);
    ret = spi_write_read_blocking((spi_inst_t*)spi_hw, txdata, rxdata, len);
    (*cs_deselect)(cs_pin);
    if (ret != len)
        return PLATFORM_SPI_COM_ERR;
    return PLATFORM_OK;
}