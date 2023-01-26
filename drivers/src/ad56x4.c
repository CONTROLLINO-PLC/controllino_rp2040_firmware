/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "ad56x4.h"
 
/* Initializes default configuration */
void ad56x4_set_default_cfg(ad56x4_cfg_t* cfg)
{
    cfg->mosi_pin =         PLATFORM_SPI_MOSI;
    cfg->miso_pin =         PLATFORM_SPI_MISO;
    cfg->sck_pin =          PLATFORM_SPI_SCK;
    cfg->cs_pin =           AD56X4_CS;
    cfg->spi_speed =        PLATFORM_SPI_SPEED;
    cfg->spi_mode =         PLATFORM_SPI_MODE_1;
    cfg->spi_bit_order =    PLATFORM_SPI_MSBFIRST;
    cfg->spi =              PLATFORM_SPI_HW;
    cfg->resolution =       AD56X4_RESOLUTION;
}
 
int ad56x4_init(ad56x4_t* dac, ad56x4_cfg_t* cfg)
{
    // Init hardware SPI interface
    if (platform_spi_init(cfg->spi, cfg->spi_speed, cfg->mosi_pin, cfg->miso_pin, cfg->sck_pin) != PLATFORM_OK)
        return AD56X4_INIT_ERROR;
    // Init hardware cs pin
    platform_gpio_init(cfg->cs_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP);
    // Set values from cfg
    dac->cs_pin =           cfg->cs_pin;
    dac->spi_speed =        cfg->spi_speed;
    dac->spi_mode =         cfg->spi_mode;
    dac->spi_bit_order =    cfg->spi_bit_order;
    dac->spi =              cfg->spi;
    dac->resolution =       cfg->resolution;
    return AD56X4_OK;
}
 
/* Check command bits */
int ad56x4_check_cmd(uint8_t cmd)
{
    if (cmd != AD56X4_CMD_WRITE_INPUT_REGISTER &&
        cmd != AD56X4_CMD_UPDATE_DAC_REGISTER &&
        cmd != AD56X4_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL &&
        cmd != AD56X4_CMD_WRITE_UPDATE_CH &&
        cmd != AD56X4_CMD_POWER_UPDOWN &&
        cmd != AD56X4_CMD_SW_RESET &&
        cmd != AD56X4_CMD_SET_LDAC)
    {
        return AD56X4_ARG_ERROR;
    }
    return AD56X4_OK;
}
 
/* Check address bits */
int ad56x4_check_addr(uint8_t addr)
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
 
int ad56x4_generic_write(ad56x4_t* dac, uint8_t cmd, uint8_t ch_addr, uint16_t data)
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
    platform_spi_set_config(dac->spi, dac->spi_speed, dac->spi_mode, dac->spi_bit_order);
    ad56x4_cs_select(dac);
    platform_sleep_us(600); // Necesary delay
    if (platform_spi_write(dac->spi, tx_buf, sizeof(tx_buf)) != PLATFORM_OK)
        return AD56X4_SPI_ERROR;
    ad56x4_cs_deselect(dac);
    return AD56X4_OK;
}
 
/* Write to input register n */
int ad56x4_write_input_reg(ad56x4_t* dac, uint8_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dac, AD56X4_CMD_WRITE_INPUT_REGISTER, ch_addr, data);
}
 
/* Update DAC register n */
int ad56x4_update_dac_reg(ad56x4_t* dac, uint8_t ch_addr)
{
    return ad56x4_generic_write(dac, AD56X4_CMD_UPDATE_DAC_REGISTER, ch_addr, 0x0000 /* don't care */);
}
 
/* Write to input register n, update all */
int ad56x4_write_input_reg_update_all_dac(ad56x4_t* dac, uint8_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dac, AD56X4_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL, ch_addr, data);
}
 
/* Write to and update DAC channel n */
int ad56x4_write_update_dac_reg(ad56x4_t* dac, uint8_t ch_addr, uint16_t data)
{
    return ad56x4_generic_write(dac, AD56X4_CMD_WRITE_UPDATE_CH, ch_addr, data);
}
 
/* Set power mode */
int ad56x4_set_pwr(ad56x4_t* dac, uint8_t pwr_mode, uint8_t ch_sel)
{
    uint16_t data;
    // Check arguments
    if (pwr_mode != AD56X4_PWR_MODE_NORMAL &&
        pwr_mode != AD56X4_PWR_MODE_POWERDOWN_1K &&
        pwr_mode != AD56X4_PWR_MODE_POWERDOWN_100K &&
        pwr_mode != AD56X4_PWR_MODE_POWERDOWN_TRISTATE)
    {
        return AD56X4_ARG_ERROR;
    }
    if (ch_sel != AD56X4_SELECT_CH_A &&
        ch_sel != AD56X4_SELECT_CH_B &&
        ch_sel != AD56X4_SELECT_CH_C &&
        ch_sel != AD56X4_SELECT_CH_D &&
        ch_sel != AD56X4_SELECT_CH_ALL)
    {
        return AD56X4_ARG_ERROR;
    }
    // Prepare txdata
    data = ((uint16_t)pwr_mode << 4) | (uint16_t)ch_sel;
    return ad56x4_generic_write(dac, AD56X4_CMD_POWER_UPDOWN, 0x00 /* don't care */, data);
}
 
/* Software reset */
int ad56x4_sw_reset(ad56x4_t* dac, uint8_t rst_mode)
{
    // Check arguments
    if (rst_mode != AD56X4_SW_RST_PARTIAL &&
        rst_mode != AD56X4_SW_RST_FULL)
    {
        return AD56X4_ARG_ERROR;
    }
    return ad56x4_generic_write(dac, AD56X4_CMD_SW_RESET, 0x00 /* don't care */, (uint16_t)rst_mode);
}
 
/* Set channel LDAC mode */
int ad56x4_set_ldac(ad56x4_t* dac, uint8_t ch_ldac_mode)
{
    // Pending ch_ldac_mode arg check 
    return ad56x4_generic_write(dac, AD56X4_CMD_SET_LDAC, 0x00 /* don't care */, (uint16_t)ch_ldac_mode);
}
 
/* Set the voltage values of the specified channel */
int ad56x4_set_ch_voltage(ad56x4_t* dac, uint8_t ch_addr, uint16_t vol_val, uint16_t vol_ref_max)
{
    int ret;
    float float_dac = ((float)vol_val / (float)vol_ref_max) * (float)dac->resolution;
    int data = (int)float_dac;
    ret = ad56x4_write_input_reg(dac, ch_addr, (uint16_t)data);
    if (ret != AD56X4_OK) return ret;
    ret = ad56x4_update_dac_reg(dac, ch_addr);
    return ret;
}
