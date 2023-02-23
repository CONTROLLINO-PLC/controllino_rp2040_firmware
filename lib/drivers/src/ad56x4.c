/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "ad56x4.h"
#include "hw_platform.h" /* External harware interface library */
 
static ad56x4_err_code_t ret;
 
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
 
/* Initializes hardware according to configuration */
ad56x4_err_code_t ad56x4_init(ad56x4_t* dev, ad56x4_cfg_t* cfg)
{
    // Init hardware SPI interface
    if (platform_spi_init(cfg->spi, cfg->spi_speed, cfg->mosi_pin, cfg->miso_pin, cfg->sck_pin) != PLATFORM_OK)
        return PLATFORM_SPI_INIT_ERR;
    // Init hardware cs pin
    if (platform_gpio_init(cfg->cs_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    // Set values from cfg
    dev->cs_pin = cfg->cs_pin;
    dev->spi_speed = cfg->spi_speed;
    dev->spi_mode = cfg->spi_mode;
    dev->spi_bit_order = cfg->spi_bit_order;
    dev->spi = cfg->spi;
    dev->resolution = cfg->resolution;
    // Reset and set default internal settings
    return ad56x4_sw_reset(dev, AD56X4_SW_RST_FULL);
}
 
ad56x4_err_code_t ad56x4_generic_write(ad56x4_t* dev, ad56x4_cmd_t cmd, ad56x4_ch_addr_t ch_addr, uint16_t data)
{
    uint8_t tx_buf[3];
    // Prepare txdata
    tx_buf[0] = (uint8_t)(cmd << 3) | ch_addr;
    tx_buf[1] = (uint8_t)((data >> 8) & 0xFF);
    tx_buf[2] = (uint8_t)(data & 0xFF);
    // Set ad56x4 SPI settings and attempt to transmit data
    platform_spi_set_config(dev->spi, dev->spi_speed, dev->spi_mode, dev->spi_bit_order);
    ad56x4_cs_select(dev);
    platform_sleep_us(600);
    ret = platform_spi_write(dev->spi, tx_buf, sizeof(tx_buf));
    ad56x4_cs_deselect(dev);
    if (ret != PLATFORM_OK)
        return PLATFORM_SPI_COM_ERR;
    return PLATFORM_OK;
}
 
/* Write to input register n */
ad56x4_err_code_t ad56x4_write_input_reg(ad56x4_t* dev, ad56x4_ch_addr_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_WRITE_INPUT_REGISTER, ch_addr, data);
}
 
/* Update DAC register n */
ad56x4_err_code_t ad56x4_update_dac_reg(ad56x4_t* dev, ad56x4_ch_addr_t ch_addr)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_UPDATE_DAC_REGISTER, ch_addr, AD56X4_DATA_DONT_CARE);
}
 
/* Write to input register n, update all */
ad56x4_err_code_t ad56x4_write_input_reg_update_all_dac(ad56x4_t* dev, ad56x4_ch_addr_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL, ch_addr, data);
}
 
/* Write to and update DAC channel n */
ad56x4_err_code_t ad56x4_write_update_dac_reg(ad56x4_t* dev, ad56x4_ch_addr_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_WRITE_UPDATE_CH, ch_addr, data);
}
 
/* Set power mode */
ad56x4_err_code_t ad56x4_set_pwr(ad56x4_t* dev, ad56x4_pwr_mode_t pwr_mode, ad56x4_ch_select_t ch_sel)
{
    uint16_t data = ((uint16_t)pwr_mode << 4) | (uint16_t)ch_sel;
    return ad56x4_generic_write(dev, AD56X4_CMD_POWER_UPDOWN, AD56X4_CH_DONT_CARE, data);
}
 
/* Software reset */
ad56x4_err_code_t ad56x4_sw_reset(ad56x4_t* dev, ad56x4_sw_rst_t rst_mode)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_SW_RESET, AD56X4_CH_DONT_CARE, (uint16_t)rst_mode);
}
 
/* Set channel LDAC mode */
ad56x4_err_code_t ad56x4_set_ldev(ad56x4_t* dev, uint8_t ch_ldev_mode)
{
    return ad56x4_generic_write(dev, AD56X4_CMD_SET_LDAC, AD56X4_CH_DONT_CARE, (uint16_t)(ch_ldev_mode & 0x000F));
}
 
/* Set the voltage values of the specified channel */
ad56x4_err_code_t ad56x4_set_ch_voltage(ad56x4_t* dev, ad56x4_ch_addr_t ch_addr, uint16_t vol_val, uint16_t vol_ref_max)
{
    if (vol_val > vol_ref_max)
        return PLATFORM_ARGUMENT_ERR;
    float float_dac = ((float)vol_val / (float)vol_ref_max) * (float)dev->resolution;
    int txdata = (int)float_dac;
    ret = ad56x4_write_input_reg(dev, ch_addr, (uint16_t)txdata);
    if (ret != PLATFORM_OK) return ret;
    ret = ad56x4_update_dac_reg(dev, ch_addr);
    return ret;
}
