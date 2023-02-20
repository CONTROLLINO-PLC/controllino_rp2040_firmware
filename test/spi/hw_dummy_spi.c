/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifdef NATIVE_TEST_ENV
 
#include <unity.h>
#include "hw_platform.h"
 
typedef struct
{} spi_inst_t;
static uint8_t dummy_for_pointer;
hw_spi_t PLATFORM_SPI_HW = (hw_spi_t)&dummy_for_pointer;
const unsigned int PLATFORM_SPI_SPEED;
const int PLATFORM_SPI_MOSI;
const int PLATFORM_SPI_MISO;
const int PLATFORM_SPI_SCK;

/* Simulate and check spi transfer */
extern platform_err_code_t dummy_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len);

/* Init SPI interface */
platform_err_code_t platform_spi_init(hw_spi_t spi_hw, unsigned int speed, int mosi_pin, int miso_pin, int sck_pin)
{
    return PLATFORM_OK;
}
 
/* Change SPI settings */
platform_err_code_t platform_spi_set_config(hw_spi_t spi_hw, unsigned int speed, uint8_t mode, uint8_t bit_order)
{
    if ((mode != PLATFORM_SPI_MODE_0 && mode != PLATFORM_SPI_MODE_1 && mode != PLATFORM_SPI_MODE_2 && mode != PLATFORM_SPI_MODE_3) ||
        (bit_order != PLATFORM_SPI_LSBFIRST && bit_order != PLATFORM_SPI_MSBFIRST))
    {
        return PLATFORM_ARGUMENT_ERR;
    }
    return PLATFORM_OK;
}
 
/* Write specified number of bytes to an SPI device */
platform_err_code_t platform_spi_write(hw_spi_t spi_hw, uint8_t* txdata, size_t len)
{
    uint8_t dummy_rxdata[len];
    return platform_spi_write_read(spi_hw, txdata, dummy_rxdata, len);
}

/* Write and read specified number of bytes over SPI */
platform_err_code_t platform_spi_write_read(hw_spi_t spi_hw, uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    return dummy_spi_transfer(txdata, rxdata, len);
}
 
#endif