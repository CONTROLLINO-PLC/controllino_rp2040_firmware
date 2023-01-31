/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "ad56x4.h"
 
/*!
 * \brief Check command bits
 *
 * \param cmd Comand to check
 * \return AD56X4_ARG_ERROR : error
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_check_cmd(uint8_t cmd)
{
    if (cmd > AD56X4_CMD_SET_LDAC)
        return AD56X4_ARG_ERROR;
    return AD56X4_OK;
}
 
/**
 *\brief Check address bits
 *
 * \param addr Channel address to check
 * \return AD56X4_ARG_ERROR : error
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_check_addr(uint8_t addr)
{
    if (addr != AD56X4_ADDR_CH_A &&
        addr != AD56X4_ADDR_CH_B &&
        addr != AD56X4_ADDR_CH_C &&
        addr != AD56X4_ADDR_CH_D &&
        addr != AD56X4_ADDR_CH_ALL)
    {
        return AD56X4_ARG_ERROR;
    }
    return AD56X4_OK;
}
 
/**
 *\brief Check power mode
 *
 * \param pwr_mode Power mode to check
 * \return AD56X4_ARG_ERROR : error
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_check_pwr_mode(uint8_t pwr_mode)
{
    if (pwr_mode > AD56X4_PWR_MODE_POWERDOWN_TRISTATE)
        return AD56X4_ARG_ERROR;
    return AD56X4_OK;
}
 
/**
 *\brief Check channel selection
 *
 * \param pwr_mode Channel selection to check
 * \return AD56X4_ARG_ERROR : error
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_check_ch_sel(uint8_t ch_sel)
{
    if (ch_sel != AD56X4_SELECT_CH_A &&
        ch_sel != AD56X4_SELECT_CH_B &&
        ch_sel != AD56X4_SELECT_CH_C &&
        ch_sel != AD56X4_SELECT_CH_D &&
        ch_sel != AD56X4_SELECT_CH_ALL)
    {
        return AD56X4_ARG_ERROR;
    }
    return AD56X4_OK;
}
 
/**
 *\brief Check reset mode
 *
 * \param rst_mode Reset mode to check
 * \return AD56X4_ARG_ERROR : error
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_check_rst_mode(uint8_t rst_mode)
{
    if (rst_mode > AD56X4_SW_RST_FULL)
        return AD56X4_ARG_ERROR;
    return AD56X4_OK;
}

/* Initializes default configuration */
void ad56x4_set_default_cfg(ad56x4_cfg_t* cfg)
{
    cfg->mosi_pin = PLATFORM_SPI_MOSI;
    cfg->miso_pin = PLATFORM_SPI_MISO;
    cfg->sck_pin = PLATFORM_SPI_SCK;
    cfg->cs_pin = AD56X4_CS;
    cfg->spi_speed = PLATFORM_SPI_SPEED;
    cfg->spi_mode = PLATFORM_SPI_MODE_1;
    cfg->spi_bit_order = PLATFORM_SPI_MSBFIRST;
    cfg->spi = PLATFORM_SPI_HW;
    cfg->resolution = AD56X4_RESOLUTION;
}
 
ad56x4_error_code_t ad56x4_init(ad56x4_t* dev, ad56x4_cfg_t* cfg)
{
    // Init hardware SPI interface
    if (platform_spi_init(cfg->spi, cfg->spi_speed, cfg->mosi_pin, cfg->miso_pin, cfg->sck_pin) != AD56X4_OK)
        return AD56X4_INIT_ERROR;
    // Init hardware cs pin
    platform_gpio_init(cfg->cs_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP);
    // Set values from cfg
    dev->cs_pin = cfg->cs_pin;
    dev->spi_speed = cfg->spi_speed;
    dev->spi_mode = cfg->spi_mode;
    dev->spi_bit_order = cfg->spi_bit_order;
    dev->spi = cfg->spi;
    dev->resolution = cfg->resolution;
    // Reset and set default internal settings
    if (ad56x4_sw_reset(dev, AD56X4_SW_RST_FULL) != AD56X4_OK)
        return AD56X4_INIT_ERROR;
    return AD56X4_OK;
}
 
ad56x4_error_code_t ad56x4_generic_write(ad56x4_t* dev, uint8_t cmd, uint8_t ch_addr, uint16_t data)
{
    uint8_t tx_buf[3];
    // Check arguments
    if (ad56x4_check_cmd(cmd) != AD56X4_OK)
        return AD56X4_ARG_ERROR;
    if (ad56x4_check_addr(ch_addr) != AD56X4_OK)
        return AD56X4_ARG_ERROR;
    // Prepare txdata
    tx_buf[0] = (cmd << 3) | ch_addr;
    tx_buf[1] = (uint8_t)((data >> 8) & 0xFF);
    tx_buf[2] = (uint8_t)(data & 0xFF);
    // Set ad56x4 SPI settings and attempt to transmit data
    platform_spi_set_config(dev->spi, dev->spi_speed, dev->spi_mode, dev->spi_bit_order);
    ad56x4_cs_select(dev);
    platform_sleep_us(600);
    if (platform_spi_write(dev->spi, tx_buf, sizeof(tx_buf)) != AD56X4_OK)
        return AD56X4_SPI_ERROR;
    ad56x4_cs_deselect(dev);
    return AD56X4_OK;
}
 
/* Write to input register n */
ad56x4_error_code_t ad56x4_write_input_reg(ad56x4_t* dev, uint8_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_WRITE_INPUT_REGISTER, ch_addr, data);
}
 
/* Update DAC register n */
ad56x4_error_code_t ad56x4_update_dev_reg(ad56x4_t* dev, uint8_t ch_addr)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_UPDATE_DAC_REGISTER, ch_addr, 0x0000 /* don't care */);
}
 
/* Write to input register n, update all */
ad56x4_error_code_t ad56x4_write_input_reg_update_all_dev(ad56x4_t* dev, uint8_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL, ch_addr, data);
}
 
/* Write to and update DAC channel n */
ad56x4_error_code_t ad56x4_write_update_dev_reg(ad56x4_t* dev, uint8_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_WRITE_UPDATE_CH, ch_addr, data);
}
 
/* Set power mode */
ad56x4_error_code_t ad56x4_set_pwr(ad56x4_t* dev, uint8_t pwr_mode, uint8_t ch_sel)
{
    uint16_t data;
    // Check arguments
    if (ad56x4_check_pwr_mode(pwr_mode) != AD56X4_OK)
        return AD56X4_ARG_ERROR;
    if (ad56x4_check_ch_sel(ch_sel) != AD56X4_OK)
        return AD56X4_ARG_ERROR;
    // Prepare txdata
    data = ((uint16_t)pwr_mode << 4) | (uint16_t)ch_sel;
    return ad56x4_generic_write(dev, AD56X4_CMD_POWER_UPDOWN, 0x00 /* don't care */, data);
}
 
/* Software reset */
ad56x4_error_code_t ad56x4_sw_reset(ad56x4_t* dev, uint8_t rst_mode)
{
    // Check arguments
    if (ad56x4_check_rst_mode(rst_mode) != AD56X4_OK)
        return AD56X4_ARG_ERROR;
    return ad56x4_generic_write(dev, AD56X4_CMD_SW_RESET, 0x00 /* don't care */, (uint16_t)rst_mode);
}
 
/* Set channel LDAC mode */
ad56x4_error_code_t ad56x4_set_ldev(ad56x4_t* dev, uint8_t ch_ldev_mode)
{
    // Pending ch_ldev_mode arg check 
    return ad56x4_generic_write(dev, AD56X4_CMD_SET_LDAC, 0x00 /* don't care */, (uint16_t)ch_ldev_mode);
}
 
/* Set the voltage values of the specified channel */
ad56x4_error_code_t ad56x4_set_ch_voltage(ad56x4_t* dev, uint8_t ch_addr, uint16_t vol_val, uint16_t vol_ref_max)
{
    int ret;
    float float_dev = ((float)vol_val / (float)vol_ref_max) * (float)dev->resolution;
    int data = (int)float_dev;
    ret = ad56x4_write_input_reg(dev, ch_addr, (uint16_t)data);
    if (ret != AD56X4_OK) return ret;
    ret = ad56x4_update_dev_reg(dev, ch_addr);
    return ret;
}
