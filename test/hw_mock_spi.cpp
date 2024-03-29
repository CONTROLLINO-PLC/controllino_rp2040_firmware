/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifdef NATIVE_ENV
 
#include "hw_platform.h"
 
static uint8_t dummy_for_pointer;
hw_spi_t PLATFORM_SPI_HW = (hw_spi_t)&dummy_for_pointer;
const unsigned int PLATFORM_SPI_SPEED = 0;
const int PLATFORM_SPI_MOSI = 0;
const int PLATFORM_SPI_MISO = 0;
const int PLATFORM_SPI_SCK = 0;
 
/* Test double to simulate and check spi transfer */
extern platform_err_code_t mock_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len) __attribute__((weak));
platform_err_code_t mock_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (len == 1)
    {
        if (*txdata == 0x00)
            return PLATFORM_OK;
    }
    return PLATFORM_SPI_COM_ERR;
}

/* Init SPI interface */
platform_err_code_t platform_spi_init(hw_spi_t spi_hw, unsigned int speed, int mosi_pin, int miso_pin, int sck_pin)
{
    return PLATFORM_OK;
}
 
/* Change SPI settings */
platform_err_code_t platform_spi_set_config(hw_spi_t spi_hw, unsigned int speed, platform_spi_mode_t mode, platform_spi_bit_order_t bit_order)
{
    if ((mode != PLATFORM_SPI_MODE_0 && mode != PLATFORM_SPI_MODE_1 && mode != PLATFORM_SPI_MODE_2 && mode != PLATFORM_SPI_MODE_3) ||
        (bit_order != PLATFORM_SPI_LSBFIRST && bit_order != PLATFORM_SPI_MSBFIRST))
    {
        return PLATFORM_ARGUMENT_ERR;
    }
    return PLATFORM_OK;
}
 
/* Write specified number of bytes to an SPI device */
platform_err_code_t platform_spi_write(hw_spi_t spi_hw, void(*cs_select)(int), void(*cs_deselect)(int), int cs_pin, uint8_t* txdata, size_t len)
{
    uint8_t dummy_rxdata[len];
    return platform_spi_write_read(spi_hw, cs_select, cs_deselect, cs_pin, txdata, dummy_rxdata, len);
}
 
/* Write and read specified number of bytes over SPI */
platform_err_code_t platform_spi_write_read(hw_spi_t spi_hw, void(*cs_select)(int), void(*cs_deselect)(int), int cs_pin, uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    platform_err_code_t res;
    (*cs_select)(cs_pin);
    res = mock_spi_transfer(txdata, rxdata, len);
    (*cs_deselect)(cs_pin);
    return res;
}
 
#endif