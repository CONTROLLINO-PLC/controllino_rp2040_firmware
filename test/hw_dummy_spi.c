/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifdef NATIVE_TEST_ENV
 
#include "string.h"
#include "hw_platform.h"
#include "test_config.h"
#include "ad56x4.h"
#include "bts71220.h"
 
typedef struct
{} spi_inst_t;
static uint8_t dummy_for_pointer;
hw_spi_t PLATFORM_SPI_HW = (hw_spi_t)&dummy_for_pointer;
const unsigned int PLATFORM_SPI_SPEED;
const int PLATFORM_SPI_MOSI;
const int PLATFORM_SPI_MISO;
const int PLATFORM_SPI_SCK;

/* Check and simulate basic spi write */
static platform_err_code_t check_dummy_write(uint8_t* txdata, size_t len)
{
    if (len == 1 && *txdata == 0x00)
        return PLATFORM_OK;
    return PLATFORM_SPI_COM_ERR;
}

/* Check and simulate ad56x4 spi write */
static platform_err_code_t check_ad56x4_write(uint8_t* txdata, size_t len)
{
    if (len == 3 &&
        *txdata == (uint8_t)((AD56X4_CMD_SW_RESET << 3) | AD56X4_CH_DONT_CARE) &&
        *(txdata + 1) == (uint8_t)((AD56X4_SW_RST_FULL >> 8) & 0xFF) &&
        *(txdata + 2) == (uint8_t)(AD56X4_SW_RST_FULL & 0xFF))
    {
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
    if (check_ad56x4_write(txdata, len) == PLATFORM_OK)
        return PLATFORM_OK;
    if (check_dummy_write(txdata, len) == PLATFORM_OK)
        return PLATFORM_OK;
    return PLATFORM_SPI_COM_ERR;
}

/* Write and read specified number of bytes over SPI */
platform_err_code_t platform_spi_write_read(hw_spi_t spi_hw, uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    // test_bts71220_generic_transfer_ok
    if (len == BTS71220_DAISY_CHAIN_SIZE)
    {
        if (*(txdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) == BTS71220_REG_STD_DIAG)
        {
            memset(rxdata, BTS71220_DIAG_RES_MASK, len);
            return PLATFORM_OK;
        }
        else if (*(txdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) == BTS71220_REG_WRN_DIAG ||
            *(txdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) == BTS71220_REG_WRN_DIAG)
        {
            memset(rxdata, BTS71220_RB_MASK, len);
            return PLATFORM_OK;
        }
    }
    else if (len == 1)
    {
        if (*txdata == 0x00)
            return PLATFORM_OK;
    }
    return PLATFORM_SPI_COM_ERR;
}
 
#endif