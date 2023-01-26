/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "mcp356x.h"
 
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
}
 
/* Initializes hardware according to configuration */
int mcp356x_init(mcp356x_t* dev, mcp356x_cfg_t* cfg)
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

    if (spi_master_open(&dev->spi, &spi_cfg) == SPI_MASTER_ERROR)
    {
        return MCP356X_INIT_ERROR;
    }

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);
    spi_master_set_speed(&dev->spi, cfg->spi_speed);
    spi_master_set_mode(&dev->spi, cfg->spi_mode);
    spi_master_set_chip_select_polarity(cfg->cs_polarity);

    // Output pins 

    digital_out_init(&dev->mck, cfg->mck);

    // Input pins

    digital_in_init(&dev->int_pin, cfg->int_pin);

    spi_master_deselect_device(dev->chip_select);
    // Disable SPI by deselecting CS
    mcp356x_cs_deselect(dev);
    return MCP356X_OK;
}
 
/* Check interrupt by reading int_pin level */
uint8_t mcp356x_check_int(mcp356x_t* dev)
{
    return platform_gpio_get(dev->int_pin) ? 1 : 0;
}
 
/* Generic SPI data transfer */
int mcp356x_generic_transfer(mcp356x_t* dev, uint8_t* txdata, uint8_t txlen, uint8_t* rxdata, uint8_t rxlen)
{
    spi_master_select_device(dev->chip_select);

    spi_master_write_then_read(&dev->spi, wr_buf, wr_len, rd_buf, rd_len);
    spi_master_deselect_device(dev->chip_select);
}
 
/* Write fast commands */
int mcp356x_write_fast_cmd(mcp356x_t* dev, uint8_t fast_cmd)
{
    uint8_t tx_buf;
    uint8_t stat_byte = 0;

    tx_buf = (rw->dev_adr << 6) | rw->cmd;

    spi_master_set_default_write_data(&dev->spi, tx_buf);
    spi_master_select_device(dev->chip_select);
    spi_master_read(&dev->spi, &stat_byte, 1);
    spi_master_deselect_device(dev->chip_select);
    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    return stat_byte;
}
 
/* Write incremental data to registers */
int mcp356x_iwrite(mcp356x_t* dev, uint8_t reg, uint8_t* txdata, uint8_t txlen)
{
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];
    uint8_t stat_byte = 0;

    tx_buf[0] = (rw->dev_adr << 6) | ((rw->reg & 0x0F) << 2) | (MCP356X_CMD_INC_WRITE & 0x03);
    tx_buf[1] = wr_data;

    spi_master_set_default_write_data(&dev->spi, tx_buf[0]);
    spi_master_select_device(dev->chip_select);
    spi_master_read(&dev->spi, &stat_byte, 1);
    spi_master_write(&dev->spi, &tx_buf[1], 1);
    spi_master_deselect_device(dev->chip_select);
    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    return stat_byte;
}
 
/* Read static register data */
int mcp356x_sread(mcp356x_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];
    uint8_t stat_byte = 0;

    tx_buf[0] = (rw->dev_adr << 6) | ((rw->reg & 0x0F) << 2) | (rw->cmd & 0x03);
    tx_buf[1] = 0x00;

    spi_master_select_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, tx_buf[0]);
    spi_master_read(&dev->spi, &rx_buf[0], 1);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);
    spi_master_read(&dev->spi, &rx_buf[1], 1);

    spi_master_deselect_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    stat_byte = rx_buf[0];
    *rd_data = rx_buf[1];

    return stat_byte;
}
 
/* Read incremental from registers */
int mcp356x_iread(mcp356x_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    uint8_t tx_buf[3];
    uint8_t rx_buf[3];
    uint8_t stat_byte = 0;
    uint16_t tmp_data;

    tx_buf[0] = (rw->dev_adr << 6) | ((rw->reg & 0x0F) << 2) | (rw->cmd & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;

    spi_master_select_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, tx_buf[0]);
    spi_master_read(&dev->spi, &rx_buf[0], 1);


    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);
    spi_master_read(&dev->spi, &rx_buf[1], 2);

    spi_master_deselect_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    tmp_data = rx_buf[1];
    tmp_data <<= 8;
    tmp_data |= rx_buf[2];

    *rd_data = tmp_data;

    stat_byte = rx_buf[0];

    return rx_buf[0];
}
 
/* Read ADC data in default format */
int mcp356x_read_dev_def(mcp356x_t* dev, uint32_t* dev_data, uint8_t* sgn)
{
    uint8_t tx_buf[5];
    uint8_t rx_buf[5];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] = (rw->dev_adr << 6) | ((MCP356X_REG_ADC_DATA & 0x0F) << 2) | (MCP356X_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    spi_master_select_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, tx_buf[0]);
    spi_master_read(&dev->spi, &rx_buf[0], 1);


    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);
    spi_master_read(&dev->spi, &rx_buf[1], 3);

    spi_master_deselect_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    tmp_data = rx_buf[1];
    tmp_data <<= 8;
    tmp_data |= rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;
    tmp_data |= rx_buf[4];

    *rd_data = ((int32_t)tmp_data) / 256;
    stat_byte = rx_buf[0];

    return stat_byte;
}
 
/* Read ADC data in left justified format */
int mcp356x_read_dev_left_just(mcp356x_t* dev, uint32_t* dev_data, uint8_t* sgn)
{
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] = (rw->dev_adr << 6) | ((MCP356X_REG_ADC_DATA & 0x0F) << 2) | (MCP356X_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;

    spi_master_select_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, tx_buf[0]);
    spi_master_read(&dev->spi, &rx_buf[0], 1);


    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);
    spi_master_read(&dev->spi, &rx_buf[1], 3);

    spi_master_deselect_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    tmp_data = rx_buf[1];
    tmp_data <<= 8;
    tmp_data |= rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;

    *rd_data = ((int32_t)tmp_data) / 256;
    stat_byte = rx_buf[0];

    return stat_byte;
}
 
/* Read ADC data in extended format */
int mcp356x_read_dev_ext(mcp356x_t* dev, uint32_t* dev_data, uint8_t* sgn)
{
    uint8_t tx_buf[5];
    uint8_t rx_buf[5];
    uint8_t sign;
    int32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] = (rw->dev_adr << 6) | ((MCP356X_REG_ADC_DATA & 0x0F) << 2) | (MCP356X_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    spi_master_select_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, tx_buf[0]);
    spi_master_read(&dev->spi, &rx_buf[0], 1);


    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);
    spi_master_read(&dev->spi, &rx_buf[1], 3);

    spi_master_deselect_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    tmp_data = rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;
    tmp_data |= rx_buf[4];

    sign = rx_buf[1] & 0x01;

    if (sign != 0)
    {
        tmp_data -= 16777215;
    }

    *dev_val = tmp_data;

    stat_byte = rx_buf[0];

    return stat_byte;
}
 
/* Read ADC data in extended format including ch_id */
int mcp356x_read_dev_ch_ext(mcp356x_t* dev, uint32_t* dev_data, uint8_t* sgn, uint8_t* ch_id)
{
    uint8_t tx_buf[5];
    uint8_t rx_buf[5];
    uint8_t sign;
    uint8_t temp;
    int32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] = (rw->dev_adr << 6) | ((MCP356X_REG_ADC_DATA & 0x0F) << 2) | (MCP356X_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    spi_master_select_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, tx_buf[0]);
    spi_master_read(&dev->spi, &rx_buf[0], 1);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);
    spi_master_read(&dev->spi, &rx_buf[1], 4);

    spi_master_deselect_device(dev->chip_select);

    spi_master_set_default_write_data(&dev->spi, MCP356X_DUMMY);

    tmp_data = rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;
    tmp_data |= rx_buf[4];

    temp = rx_buf[1];

    *chan = (temp >> 4) & 0x0F;
    sign = temp & 0x01;

    if (sign != 0)
    {
        tmp_data -= 16777215;
    }

    *dev_val = tmp_data;

    stat_byte = rx_buf[0];

    return stat_byte;
}

/* Read channel voltage in millivolts using 0 to \p vol_ref_max as reference */
int mcp356x_read_ch_voltage(mcp356x_t* dev, uint8_t ch_id, uint8_t gain, uint16_t vol_ref_max, uint16_t* vol_val)
{
    float volt;
    uint32_t coef = MCP356X_CALC_COEF;

    volt = (float)(dev_val / (float)(coef * gain)) * (float)v_ref;

    return volt;
}

// ------------------------------------------------------------------------- END

