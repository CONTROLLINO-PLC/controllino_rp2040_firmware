/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "mcp356x.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADC9_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mcp356x_set_default_cfg(mcp356x_cfg_t* cfg)
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mck = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

int mcp356x_init(mcp356x_t *adc, mcp356x_cfg_t *cfg)
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default(&spi_cfg);
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC9_DUMMY;

    digital_out_init(&adc->cs, cfg->cs);
    adc->chip_select = cfg->cs;

    if(spi_master_open(&adc->spi, &spi_cfg) == SPI_MASTER_ERROR)
    {
        return ADC9_INIT_ERROR;
    }

    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_set_speed(&adc->spi, cfg->spi_speed);
    spi_master_set_mode(&adc->spi, cfg->spi_mode);
    spi_master_set_chip_select_polarity(cfg->cs_polarity);

    // Output pins 
    
    digital_out_init(&adc->mck, cfg->mck);

    // Input pins

    digital_in_init(&adc->int_pin, cfg->int_pin);
    
    spi_master_deselect_device(adc->chip_select);  

    return ADC9_OK;
}

// Check IRQ pin state function
uint8_t mcp356x_check_int(mcp356x_t* adc)
{
    return digital_in_read(&adc->int_pin);
}

void mcp356x_generic_transfer 
(
    mcp356x_t *adc, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device(adc->chip_select);
    spi_master_write_then_read(&adc->spi, wr_buf, wr_len, rd_buf, rd_len);
    spi_master_deselect_device(adc->chip_select);   
}

uint8_t mcp356x_write_fast_cmd(mcp356x_t* adc, uint8_t fast_cmd)
{
    uint8_t tx_buf;
    uint8_t stat_byte = 0;

    tx_buf =(rw->dev_adr << 6) | rw->cmd;

    spi_master_set_default_write_data(&adc->spi, tx_buf);
    spi_master_select_device(adc->chip_select);
    spi_master_read(&adc->spi, &stat_byte, 1);
    spi_master_deselect_device(adc->chip_select); 
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    return stat_byte;
}

// Write byte function
uint8_t mcp356x_write_u8(mcp356x_t* adc, uint8_t reg, uint8_t txdata)
{
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((rw->reg & 0x0F) << 2) |(ADC9_CMD_INC_WRITE & 0x03);
    tx_buf[1] = wr_data;

    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_select_device(adc->chip_select);
    spi_master_read(&adc->spi, &stat_byte, 1);
    spi_master_write(&adc->spi, &tx_buf[1], 1);
    spi_master_deselect_device(adc->chip_select); 
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    return stat_byte;
}

// Read byte function
uint8_t mcp356x_read_u8(mcp356x_t* adc, uint8_t reg, uint8_t* rxdata)
{
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((rw->reg & 0x0F) << 2) |(rw->cmd & 0x03);
    tx_buf[1] = 0x00;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_read(&adc->spi, &rx_buf[1], 1);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    stat_byte = rx_buf[0];
    *rd_data = rx_buf[1];

    return stat_byte;
}

// Write word function
uint8_t mcp356x_write_u16(mcp356x_t* adc, uint8_t reg, uint16_t txdata)
{
    uint8_t tx_buf [3];
    uint8_t rx_buf [3];
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((rw->reg & 0x0F) << 2) |(ADC9_CMD_INC_WRITE & 0x03);
    tx_buf[1] =(wr_data >> 8) & 0xFF;
    tx_buf[2] = wr_data & 0xFF;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    spi_master_write(&adc->spi, &tx_buf[1], 2);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    stat_byte = rx_buf [0];

    return stat_byte;
}

// Read word function
uint8_t mcp356x_read_u16(mcp356x_t* adc, uint8_t reg, uint16_t* rxdata)
{
    uint8_t tx_buf[3];
    uint8_t rx_buf[3];
    uint8_t stat_byte = 0;
    uint16_t tmp_data;

    tx_buf[0] =(rw->dev_adr << 6) |((rw->reg & 0x0F) << 2) |(rw->cmd & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_read(&adc->spi, &rx_buf[1], 2);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    tmp_data = rx_buf[1];
    tmp_data <<= 8;
    tmp_data |= rx_buf[2];

    *rd_data = tmp_data;

    stat_byte = rx_buf [0];

    return rx_buf [0];
}

// Write 24-bit function
uint8_t mcp356x_write_u24(mcp356x_t* adc, uint8_t reg, uint32_t txdata)
{
    uint8_t tx_buf [4];
    uint8_t rx_buf [4];
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((rw->reg & 0x0F) << 2) |(ADC9_CMD_INC_WRITE & 0x03);
    tx_buf[1] =(wr_data >> 16) & 0xFF;
    tx_buf[2] =(wr_data >> 8) & 0xFF;
    tx_buf[3] = wr_data & 0xFF;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    spi_master_write(&adc->spi, &tx_buf[1], 3);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    stat_byte = rx_buf [0];

    return stat_byte;
}

// Read 24-bit function
uint8_t mcp356x_read_u24(mcp356x_t* adc, uint8_t reg, uint32_t* rxdata)
{
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((rw->reg & 0x0F) << 2) |(rw->cmd & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_read(&adc->spi, &rx_buf[1], 3);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    tmp_data = rx_buf[1];
    tmp_data <<= 8;
    tmp_data |= rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];

    tmp_data &= 0x00FFFFFF;
    *rd_data = tmp_data;

    stat_byte = rx_buf [0];

    return stat_byte;
}

int mcp356x_read_u32(mcp356x_t* adc, uint8_t reg, uint32_t* rxdata) {
    
}

// Read default adc value
uint8_t mcp356x_read_adc_def(mcp356x_t* adc, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t tx_buf[5];
    uint8_t rx_buf[5];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((ADC9_REG_ADC_DATA & 0x0F) << 2) |(ADC9_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_read(&adc->spi, &rx_buf[1], 3);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    tmp_data = rx_buf[1];
    tmp_data <<= 8;
    tmp_data |= rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;
    tmp_data |= rx_buf[4];

    *rd_data =((int32_t) tmp_data) / 256;
    stat_byte = rx_buf [0];

    return stat_byte;
}

// Read 24-bits left justified adc value
uint8_t mcp356x_read_adc_left_just(mcp356x_t* adc, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];
    uint32_t tmp_data;
    uint8_t stat_byte = 0;
    
    tx_buf[0] =(rw->dev_adr << 6) |((ADC9_REG_ADC_DATA & 0x0F) << 2) |(ADC9_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_read(&adc->spi, &rx_buf[1], 3);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    tmp_data = rx_buf[1];
    tmp_data <<= 8;
    tmp_data |= rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;
    
    *rd_data =((int32_t) tmp_data) / 256;
    stat_byte = rx_buf [0];
    
    return stat_byte;
}

// Read Sign and ADC value function
uint8_t mcp356x_read_adc_ext(mcp356x_t* adc, uint32_t* adc_data, uint8_t* sgn)
{
    uint8_t tx_buf[5];
    uint8_t rx_buf[5];
    uint8_t sign;
    int32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((ADC9_REG_ADC_DATA & 0x0F) << 2) |(ADC9_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_read(&adc->spi, &rx_buf[1], 3);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    
    tmp_data = rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;
    tmp_data |= rx_buf[4];
    
    sign =  rx_buf[1] & 0x01;

    if(sign != 0)
    {
        tmp_data -= 16777215;
    }

    *adc_val = tmp_data;

    stat_byte = rx_buf [0];

    return stat_byte;
}

// Read Channel and ADC value function
uint8_t mcp356x_read_adc_ch_ext(mcp356x_t* adc, uint32_t* adc_data, uint8_t* sgn, uint8_t* ch_id)
{
    uint8_t tx_buf[5];
    uint8_t rx_buf[5];
    uint8_t sign;
    uint8_t temp;
    int32_t tmp_data;
    uint8_t stat_byte = 0;

    tx_buf[0] =(rw->dev_adr << 6) |((ADC9_REG_ADC_DATA & 0x0F) << 2) |(ADC9_CMD_INC_READ & 0x03);
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    spi_master_select_device(adc->chip_select);
    
    spi_master_set_default_write_data(&adc->spi, tx_buf[0]);
    spi_master_read(&adc->spi, &rx_buf[0], 1);
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);
    spi_master_read(&adc->spi, &rx_buf[1], 4);
    
    spi_master_deselect_device(adc->chip_select); 
    
    spi_master_set_default_write_data(&adc->spi, ADC9_DUMMY);

    tmp_data = rx_buf[2];
    tmp_data <<= 8;
    tmp_data |= rx_buf[3];
    tmp_data <<= 8;
    tmp_data |= rx_buf[4];

    temp = rx_buf[1];

    *chan =(temp >> 4) & 0x0F;
    sign =  temp & 0x01;

    if(sign != 0)
    {
        tmp_data -= 16777215;
    }

    *adc_val = tmp_data;

    stat_byte = rx_buf [0];

    return stat_byte;
}

// Calculate Voltage function
int mcp356x_volt_calc(mcp356x_t* adc, uint8_t ch_id, uint8_t gain, uint16_t vol_ref_max, uint16_t* vol_val)
{
    float volt;
    uint32_t coef = ADC9_CALC_COEF;
    
    volt =(float)(adc_val /(float)(coef * gain)) *(float) v_ref;

    return volt;
}

// ------------------------------------------------------------------------- END

