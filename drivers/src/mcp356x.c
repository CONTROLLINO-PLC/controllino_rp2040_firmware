/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "mcp356x.h"
#include "string.h"
 
/*!
  * \brief Check fast command
  *
  * \param fast_cmd Fast command to check
  * \return MCP356X_ARG_ERROR : error
  *         MCP356X_OK : successful
  */
mcp356x_error_code_t mcp356x_check_fast_cmd(uint8_t fast_cmd)
{
    if ((fast_cmd < MCP356X_FAST_CMD_ADC_CONV_START) || (fast_cmd > MCP356X_FAST_CMD_DEV_FULL_RESET))
        return MCP356X_ARG_ERROR;
    return MCP356X_OK;
}
 
/*!
 * \brief Check register address
 *
 * \param reg Register address to check
 * \return MCP356X_ARG_ERROR : error
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_check_reg_addr(uint8_t reg)
{
    if (reg > MCP356X_REG_CRC_CFG)
        return MCP356X_ARG_ERROR;
    return MCP356X_OK;
}
 
/*!
 * \brief Check channel identifier
 *
 * \param ch_id Channel identifier to check
 * \return MCP356X_ARG_ERROR : error
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_check_ch_id(uint8_t ch_id)
{
    if (ch_id > MCP356X_CH_OFFSET)
        return MCP356X_ARG_ERROR;
    return MCP356X_OK;
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
    cfg->config_0_reg = MCP356X_CFG_0_VREF_INT | MCP356X_CFG_0_CLK_INT_NO_OUT | MCP356X_CFG_0_CS_SEL_NONE | MCP356X_CFG_0_MODE_CONV;
    cfg->config_1_reg = MCP356X_CFG_1_PRE_1 | MCP356X_CFG_1_OSR_4096;
    cfg->config_2_reg = MCP356X_CFG_2_BOOST_X_1 | MCP356X_CFG_2_GAIN_X_2 | MCP356X_CFG_2_AZ_MUX_DIS | MCP356X_CFG_2_AZ_VREF_DIS;
    cfg->config_3_reg = MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_DEF | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS;
    cfg->irq_reg = MCP356X_IRQ_MODE_IRQ | MCP356X_IRQ_MODE_LOGIC_HIGH | MCP356X_IRQ_FASTCMD_EN | MCP356X_IRQ_STP_EN;
    cfg->mux_reg = MCP356X_MUX_VIN_POS_CH0 | MCP356X_MUX_VIN_NEG_VREF_EXT_MINUS;
    cfg->scan_reg = MCP356X_SCAN_DLY_NO_DELAY;
    cfg->timer_reg = MCP356X_TIMER_DLY_NO_DELAY;
}
 
/* Initializes hardware according to configuration */
mcp356x_error_code_t mcp356x_init(mcp356x_t* dev, mcp356x_cfg_t* cfg)
{
    // Init hardware SPI interface
    if (platform_spi_init(cfg->spi, cfg->spi_speed, cfg->mosi_pin, cfg->miso_pin, cfg->sck_pin) != MCP356X_OK)
        return MCP356X_INIT_ERROR;
    // Init hardware cs, mclk and int pin
    platform_gpio_init(cfg->cs_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP);
    platform_gpio_init(cfg->mclk_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED);
    platform_gpio_init(cfg->int_pin, PLATFORM_GPIO_IN, PLATFORM_GPIO_PULL_DISABLED);
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
    if (mcp356x_write_fast_cmd(dev, MCP356X_FAST_CMD_DEV_FULL_RESET) != MCP356X_OK)
        return MCP356X_INIT_ERROR;
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
    if (mcp356x_iwrite(dev, MCP356X_REG_CFG_0, txdata, sizeof(txdata)) != MCP356X_OK)
        return MCP356X_INIT_ERROR;
    return MCP356X_OK;
}
 
/* Check interrupt by reading int_pin level */
uint8_t mcp356x_check_int(mcp356x_t* dev)
{
    return platform_gpio_get(dev->int_pin) ? 1 : 0;
}
 
/* Generic SPI data transfer */
mcp356x_error_code_t mcp356x_generic_transfer(mcp356x_t* dev, uint8_t fcmd_addr, uint8_t r_w_cmd, uint8_t* txdata, uint8_t* rxdata, uint8_t len)
{
    uint8_t tx_buf[len + 1];
    uint8_t rx_buf[len + 1];
    memset(tx_buf, 0x00, sizeof(tx_buf));
    // Check arguments
    if (((mcp356x_check_reg_addr(fcmd_addr) != MCP356X_OK) &&
        (mcp356x_check_fast_cmd(fcmd_addr) != MCP356X_OK)) ||
        (r_w_cmd > MCP356X_CMD_INC_READ))
        return MCP356X_ARG_ERROR;
    // Set first command byte
    tx_buf[0] = (((uint8_t)MCP356X_DEVICE_ADDR << 6) | (fcmd_addr << 2)) | r_w_cmd;
    // Copy data to transmit if necessary
    if (txdata != NULL)
        memcpy(&tx_buf[1], txdata, len);
    platform_spi_set_config(dev->spi, dev->spi_speed, dev->spi_mode, dev->spi_bit_order);
    mcp356x_cs_select(dev);
    platform_sleep_us(600);
    if (platform_spi_write_read(dev->spi, tx_buf, rx_buf, sizeof(rx_buf)) != MCP356X_OK)
        return MCP356X_SPI_ERROR;
    mcp356x_cs_deselect(dev);
    // Get status from first byte of received data
    // Pending analyce status byte
    dev->status = rx_buf[0];
    // Copy received data if necessary
    if (rxdata != NULL)
        memcpy(rxdata, &rx_buf[1], len);
    return MCP356X_OK;
}
 
/* Write fast commands */
mcp356x_error_code_t mcp356x_write_fast_cmd(mcp356x_t* dev, uint8_t fast_cmd)
{
    return mcp356x_generic_transfer(dev, fast_cmd, MCP356X_CMD_DONT_CARE, NULL, NULL, 0);
}
 
/* Write incremental data to registers */
mcp356x_error_code_t mcp356x_iwrite(mcp356x_t* dev, uint8_t reg, uint8_t* txdata, uint8_t txlen)
{
    return mcp356x_generic_transfer(dev, reg, MCP356X_CMD_INC_WRITE, txdata, NULL, txlen);
}
 
/* Read static register data */
mcp356x_error_code_t mcp356x_sread(mcp356x_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    return mcp356x_generic_transfer(dev, reg, MCP356X_CMD_STAT_READ, NULL, rxdata, rxlen);
}
 
/* Read incremental from registers */
mcp356x_error_code_t mcp356x_iread(mcp356x_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    return mcp356x_generic_transfer(dev, reg, MCP356X_CMD_INC_READ, NULL, rxdata, rxlen);
}
 
/* Read ADC data in default format */
mcp356x_error_code_t mcp356x_read_adc_def(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t rxdata[3];
    uint32_t temp;
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != MCP356X_OK)
        return ret;
    temp = ((uint32_t)rxdata[0] << 16) | ((uint32_t)rxdata[1] << 8) | (uint32_t)rxdata[2];
    *adc_data = temp & 0x7FFFFF;
    *sgn = (uint8_t)((temp & 0x800000) >> 23) & 0x01;
    return MCP356X_OK;
}
 
/* Read ADC data in left justified format */
mcp356x_error_code_t mcp356x_read_adc_left_just(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t rxdata[4];
    uint32_t temp;
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != MCP356X_OK)
        return ret;
    temp = ((uint32_t)rxdata[0] << 16) | ((uint32_t)rxdata[1] << 8) | (uint32_t)rxdata[2];
    *adc_data = temp & 0x7FFFFF;
    *sgn = (uint8_t)((temp & 0x800000) >> 23) & 0x01;
    return MCP356X_OK;
}
 
/* Read ADC data in extended format */
mcp356x_error_code_t mcp356x_read_adc_ext(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t rxdata[4];
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != MCP356X_OK)
        return ret;
    *adc_data = ((uint32_t)rxdata[1] << 16) | ((uint32_t)rxdata[2] << 8) | (uint32_t)rxdata[3];
    *sgn = rxdata[0] & 0x01;
    return MCP356X_OK;
}
 
/* Read ADC data in extended format including ch_id */
mcp356x_error_code_t mcp356x_read_adc_ch_ext(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn, uint8_t* ch_id)
{
    uint8_t rxdata[4];
    uint8_t ret = mcp356x_iread(dev, MCP356X_REG_ADC_DATA, rxdata, sizeof(rxdata));
    if (ret != MCP356X_OK)
        return ret;
    *adc_data = ((uint32_t)rxdata[1] << 16) | ((uint32_t)rxdata[2] << 8) | (uint32_t)rxdata[3];
    *sgn = rxdata[0] & 0x0F;
    *ch_id = (rxdata[0] >> 4) & 0x0F;
    if (mcp356x_check_ch_id(*ch_id) != MCP356X_OK)
        return MCP356X_SPI_ERROR;
    return MCP356X_OK;
}

/* Read channel voltage in millivolts using vol_ref_min to vol_ref_max as reference */
mcp356x_error_code_t mcp356x_read_voltage(mcp356x_t* dev, uint32_t vol_ref_min, uint32_t vol_ref_max, uint32_t* vol_val)
{
    uint8_t ret;
    uint8_t config_3_reg;
    uint8_t adc_data_format;
    uint32_t max_resolution;
    uint32_t adc_data;
    uint8_t sgn;
    uint8_t ch_id;
    // Check arguments
    if (vol_ref_min > vol_ref_max)
        return MCP356X_ARG_ERROR;
    // Read ADC data format
    ret = mcp356x_iread(dev, MCP356X_REG_CFG_3, &config_3_reg, 1);
    if (ret != MCP356X_OK)
        return ret;
    adc_data_format = config_3_reg & 0x30;
    switch (adc_data_format)
    {
    case MCP356X_CFG_3_DATA_FORMAT_CH_ADC:
        mcp356x_read_adc_ch_ext(dev, &adc_data, &sgn, &ch_id);
        max_resolution = 0xFFFFFF;
        break;
    case MCP356X_CFG_3_DATA_FORMAT_EXT_ADC:
        mcp356x_read_adc_ext(dev, &adc_data, &sgn);
        max_resolution = 0xFFFFFF;
        break;
    case MCP356X_CFG_3_DATA_FORMAT_LEFT_JUST:
        mcp356x_read_adc_left_just(dev, &adc_data, &sgn);
        max_resolution = 0x7FFFFF;
        break;
    case MCP356X_CFG_3_DATA_FORMAT_DEF:
        mcp356x_read_adc_def(dev, &adc_data, &sgn);
        max_resolution = 0x7FFFFF;
        break;
    }
    // Calulate voltage
    *vol_val = (int)(((float)(vol_ref_max - vol_ref_min) * (float)adc_data) / (float)max_resolution);
    return MCP356X_OK;
}

