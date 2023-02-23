/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "mcp356x.h"
#include "string.h"
#include "hw_platform.h" /* External harware interface library */
 
/*!
 * \brief Check channel identifier
 *
 * \param ch_id Channel identifier to check
 * \return PLATFORM_ARGUMENT_ERR : error
 *         PLATFORM_OK : successful
 */
static mcp356x_err_code_t mcp356x_check_ch_id(uint8_t ch_id)
{
    if (ch_id > MCP356X_CH_OFFSET)
        return PLATFORM_ARGUMENT_ERR;
    return PLATFORM_OK;
}
 
/* Initializes default configuration */
void mcp356x_set_default_cfg(mcp356x_cfg_t* cfg)
{
    cfg->mosi_pin = PLATFORM_SPI_MOSI;
    cfg->miso_pin = PLATFORM_SPI_MISO;
    cfg->sck_pin = PLATFORM_SPI_SCK;
    cfg->cs_pin = MCP356X_CS;
    cfg->spi_speed = PLATFORM_SPI_SPEED;
    cfg->spi_mode = PLATFORM_SPI_MODE_1;
    cfg->spi_bit_order = PLATFORM_SPI_MSBFIRST;
    cfg->spi = PLATFORM_SPI_HW;
    cfg->mclk_pin = MCP356X_MCLK;
    cfg->int_pin = MCP356X_INT;
    cfg->config_0_reg = MCP356X_INIT_CFG_0_REG;
    cfg->config_1_reg = MCP356X_INIT_CFG_1_REG;
    cfg->config_2_reg = MCP356X_INIT_CFG_2_REG;
    cfg->config_3_reg = MCP356X_INIT_CFG_3_REG;
    cfg->irq_reg = MCP356X_INIT_IRQ_REG;
    cfg->mux_reg = MCP356X_INIT_MUX_REG;
    cfg->scan_reg = MCP356X_INIT_SCAN_REG;
    cfg->timer_reg = MCP356X_INIT_TIMER_REG;
}
 
/* Initializes hardware according to configuration */
mcp356x_err_code_t mcp356x_init(mcp356x_t* dev, mcp356x_cfg_t* cfg)
{
    // Init hardware SPI interface
    if (platform_spi_init(cfg->spi, cfg->spi_speed, cfg->mosi_pin, cfg->miso_pin, cfg->sck_pin) != PLATFORM_OK)
        return PLATFORM_SPI_INIT_ERR;
    // Init hardware cs, mclk and int pin
    if (platform_gpio_init(cfg->cs_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP) != PLATFORM_OK ||
        platform_gpio_init(cfg->mclk_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED) != PLATFORM_OK ||
        platform_gpio_init(cfg->int_pin, PLATFORM_GPIO_IN, PLATFORM_GPIO_PULL_DISABLED) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    // Set values from cfg
    dev->cs_pin = cfg->cs_pin;
    dev->spi_speed = cfg->spi_speed;
    dev->spi_mode = cfg->spi_mode;
    dev->spi_bit_order = cfg->spi_bit_order;
    dev->spi = cfg->spi;
    dev->mclk_pin = cfg->mclk_pin;
    dev->int_pin = cfg->int_pin;
    // Configure initial registers
    uint8_t txdata[12];
    memset(txdata, 0x00, sizeof(txdata));
    if (mcp356x_write_fast_cmd(dev, MCP356X_FAST_CMD_DEV_FULL_RESET) != PLATFORM_OK)
        return PLATFORM_SPI_INIT_ERR;
    txdata[0] = cfg->config_0_reg;
    txdata[1] = cfg->config_1_reg;
    txdata[2] = cfg->config_2_reg;
    txdata[3] = cfg->config_3_reg;
    txdata[4] = cfg->irq_reg;
    txdata[5] = cfg->mux_reg;
    if (cfg->scan_reg) {
        txdata[6] = (uint8_t)((cfg->scan_reg >> 16) & 0xff);
        txdata[7] = (uint8_t)((cfg->scan_reg >> 8) & 0xff);
        txdata[8] = (uint8_t)((cfg->scan_reg) & 0xff);
    }
    if (cfg->timer_reg) {
        txdata[9] = (uint8_t)((cfg->timer_reg >> 16) & 0xff);
        txdata[10] = (uint8_t)((cfg->timer_reg >> 8) & 0xff);
        txdata[11] = (uint8_t)((cfg->timer_reg) & 0xff);
    }
    return mcp356x_iwrite(dev, MCP356X_REG_CFG_0, txdata, sizeof(txdata));
}
 
/* Check interrupt by reading int_pin level */
uint8_t mcp356x_check_int(mcp356x_t* dev)
{
    bool int_val = false;
    platform_gpio_get(dev->int_pin, &int_val);
    return int_val ? 1 : 0;
}
 
/* Generic SPI data transfer */
mcp356x_err_code_t mcp356x_generic_transfer(mcp356x_t* dev, uint8_t fcmd_addr, mcp356x_rw_cmd_t rw_cmd, uint8_t* txdata, uint8_t* rxdata, uint8_t len)
{
    uint8_t tx_buf[len + 1];
    uint8_t rx_buf[len + 1];
    mcp356x_err_code_t ret;
    memset(tx_buf, 0x00, sizeof(tx_buf));
    // Set first command byte
    tx_buf[0] = (((uint8_t)MCP356X_DEVICE_ADDR << 6) | (fcmd_addr << 2)) | rw_cmd;
    // Copy data to transmit if necessary
    if (txdata != NULL)
        memcpy(&tx_buf[1], txdata, len);
    platform_spi_set_config(dev->spi, dev->spi_speed, dev->spi_mode, dev->spi_bit_order);
    mcp356x_cs_select(dev);
    platform_sleep_us(600);
    ret = platform_spi_write_read(dev->spi, tx_buf, rx_buf, sizeof(rx_buf));
    mcp356x_cs_deselect(dev);
    if (ret != PLATFORM_OK || !(rx_buf[0] & MCP356X_VALID_STATUS_MASK))
        return PLATFORM_SPI_COM_ERR;
    dev->status = rx_buf[0];
    // Copy received data if necessary
    if (rxdata != NULL)
        memcpy(rxdata, &rx_buf[1], len);
    return PLATFORM_OK;
}
 
/* Write fast commands */
mcp356x_err_code_t mcp356x_write_fast_cmd(mcp356x_t* dev, mcp356x_fast_cmd_t fast_cmd)
{
    return mcp356x_generic_transfer(dev, (uint8_t)fast_cmd, MCP356X_CMD_DONT_CARE, NULL, NULL, 0);
}
 
/* Write incremental data to registers */
mcp356x_err_code_t mcp356x_iwrite(mcp356x_t* dev, mcp356x_reg_t reg, uint8_t* txdata, uint8_t txlen)
{
    return mcp356x_generic_transfer(dev, (uint8_t)reg, MCP356X_CMD_INC_WRITE, txdata, NULL, txlen);
}
 
/* Read static register data */
mcp356x_err_code_t mcp356x_sread(mcp356x_t* dev, mcp356x_reg_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    return mcp356x_generic_transfer(dev, (uint8_t)reg, MCP356X_CMD_STAT_READ, NULL, rxdata, rxlen);
}
 
/* Read incremental from registers */
mcp356x_err_code_t mcp356x_iread(mcp356x_t* dev, mcp356x_reg_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    return mcp356x_generic_transfer(dev, (uint8_t)reg, MCP356X_CMD_INC_READ, NULL, rxdata, rxlen);
}
 
/* Read ADC data in default format */
mcp356x_err_code_t mcp356x_read_adc_def(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t rxdata[3];
    uint32_t temp;
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != PLATFORM_OK)
        return ret;
    temp = ((uint32_t)rxdata[0] << 16) | ((uint32_t)rxdata[1] << 8) | (uint32_t)rxdata[2];
    *adc_data = temp & 0x7FFFFF;
    *sgn = (uint8_t)((temp & 0x800000) >> 23) & 0x01;
    return PLATFORM_OK;
}
 
/* Read ADC data in left justified format */
mcp356x_err_code_t mcp356x_read_adc_left_just(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t rxdata[4];
    uint32_t temp;
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != PLATFORM_OK)
        return ret;
    temp = ((uint32_t)rxdata[0] << 16) | ((uint32_t)rxdata[1] << 8) | (uint32_t)rxdata[2];
    *adc_data = temp & 0x7FFFFF;
    *sgn = (uint8_t)((temp & 0x800000) >> 23) & 0x01;
    return PLATFORM_OK;
}
 
/* Read ADC data in extended format */
mcp356x_err_code_t mcp356x_read_adc_ext(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t rxdata[4];
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != PLATFORM_OK)
        return ret;
    *adc_data = ((uint32_t)rxdata[1] << 16) | ((uint32_t)rxdata[2] << 8) | (uint32_t)rxdata[3];
    *sgn = rxdata[0] & 0x01;
    return PLATFORM_OK;
}
 
/* Read ADC data in extended format including ch_id */
mcp356x_err_code_t mcp356x_read_adc_ch_ext(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn, uint8_t* ch_id)
{
    uint8_t rxdata[4];
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != PLATFORM_OK)
        return ret;
    *adc_data = ((uint32_t)rxdata[1] << 16) | ((uint32_t)rxdata[2] << 8) | (uint32_t)rxdata[3];
    *sgn = rxdata[0] & 0x0F;
    *ch_id = (rxdata[0] >> 4) & 0x0F;
    if (mcp356x_check_ch_id(*ch_id) != PLATFORM_OK)
        return PLATFORM_SPI_COM_ERR;
    return PLATFORM_OK;
}
 
/* Read current adc raw conversion data */
mcp356x_err_code_t mcp356x_read_raw_adc(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn, uint32_t* max_resolution)
{
    uint8_t ret;
    uint8_t config_3_reg;
    uint8_t adc_data_format;
    uint8_t ch_id;
    ret = mcp356x_iread(dev, MCP356X_REG_CFG_3, &config_3_reg, 1);
    if (ret != PLATFORM_OK)
        return ret;
    adc_data_format = config_3_reg & MCP356X_CFG_3_DATA_FORMAT_MASK;
    switch (adc_data_format)
    {
    case MCP356X_CFG_3_DATA_FORMAT_CH_ADC:
        ret = mcp356x_read_adc_ch_ext(dev, adc_data, sgn, &ch_id);
        *max_resolution = MCP356X_RES_24_BITS;
        break;
    case MCP356X_CFG_3_DATA_FORMAT_EXT_ADC:
        ret = mcp356x_read_adc_ext(dev, adc_data, sgn);
        *max_resolution = MCP356X_RES_24_BITS;
        break;
    case MCP356X_CFG_3_DATA_FORMAT_LEFT_JUST:
        ret = mcp356x_read_adc_left_just(dev, adc_data, sgn);
        *max_resolution = MCP356X_RES_23_BITS;
        break;
    case MCP356X_CFG_3_DATA_FORMAT_DEF:
        ret = mcp356x_read_adc_def(dev, adc_data, sgn);
        *max_resolution = MCP356X_RES_23_BITS;
        break;
    }
    return ret;
}

/* Read current adc voltage conversion in millivolts */
mcp356x_err_code_t mcp356x_read_voltage(mcp356x_t* dev, uint32_t vol_ref_min, uint32_t vol_ref_max, uint32_t* vol_val)
{
    uint8_t ret;
    uint32_t adc_data;
    uint8_t sgn;
    uint32_t max_resolution;
    // Check arguments
    if (vol_ref_min > vol_ref_max)
        return PLATFORM_ARGUMENT_ERR;
    // Read ADC data format
    ret = mcp356x_read_raw_adc(dev, &adc_data, &sgn, &max_resolution);
    if (ret != PLATFORM_OK)
        return ret;
    // Calulate voltage
    *vol_val = (int)(((float)(vol_ref_max - vol_ref_min) * (float)adc_data) / (float)max_resolution);
    return PLATFORM_OK;
}

