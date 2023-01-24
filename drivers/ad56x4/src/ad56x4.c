/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "ad56x4.h"
 
/* Initializes default configuration */
void ad56x4_set_default_cfg(ad56x4_cfg_t* cfg)
{
    cfg->sck_pin =          PLATFORM_SPI_SCK;
    cfg->miso_pin =         PLATFORM_SPI_MISO;
    cfg->mosi_pin =         PLATFORM_SPI_MOSI;
    cfg->cs_pin   =         HAL_PIN_NC;
    cfg->spi_speed =    PLATFORM_SPI_SPEED;
    cfg->spi_mode =     SPI_MASTER_MODE_0;
}

int ad56x4_init(ad56x4_t* dac, ad56x4_cfg_t* cfg)
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg);
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_data = AD56X4_DUMMY;

    digital_out_init( &dac->cs_pin, cfg->cs_pin);
    dac->cs_pin = cfg->cs_pin;

    if ( spi_master_open( &dac->spi, &spi_cfg) == SPI_MASTER_ERROR)
    {
        return AD56X4_INIT_ERROR;
    }

    spi_master_set_default_data( &dac->spi, AD56X4_DUMMY);
    spi_master_set_speed( &dac->spi, cfg->spi_speed);
    spi_master_set_mode( &dac->spi, cfg->spi_mode);
    spi_master_set_cs_pin_polarity( cfg->cs_pin_polarity);

    return AD56X4_OK;
}

/* Check command bits */
int ad56x4_check_cmd(ad56x4_t* dac, uint8_t cmd)
{
    if (cmd != AD56X4_COMMAND_WRITE_INPUT_REGISTER &&
        cmd != AD56X4_COMMAND_UPDATE_DAC_REGISTER &&
        cmd != AD56X4_COMMAND_WRITE_INPUT_REGISTER_UPDATE_ALL &&
        cmd != AD56X4_COMMAND_WRITE_UPDATE_CHANNEL &&
        cmd != AD56X4_COMMAND_POWER_UPDOWN &&
        cmd != AD56X4_COMMAND_SW_RESET &&
        cmd != AD56X4_COMMAND_SET_LDAC)
    {
        return AD56X4_ARG_ERROR;
    }
    return AD56X4_OK;
}

/* Check address bits */
int ad56x4_check_addr(ad56x4_t* dac, uint8_t addr)
{
    if (addr != AD56X4_ADDRESS_CHANNEL_A &&
        addr != AD56X4_ADDRESS_CHANNEL_B &&
        addr != AD56X4_ADDRESS_CHANNEL_C &&
        addr != AD56X4_ADDRESS_CHANNEL_D &&
        addr != AD56X4_ADDRESS_CHANNEL_ALL)
    {
        return AD56X4_ARG_ERROR;
    }
    return AD56X4_OK;
}

int ad56x4_generic_write(ad56x4_t* dac, uint8_t cmd, uint8_t ch_addr, uint16_t data)
{
    uint8_t tx_buf[3];
    uint8_t rx_buf;

    cmd <<= 3;
    cmd &= AD56X4_MASK_BIT_COMMAND;
    ch_addr &= AD56X4_MASK_BIT_ADDRESS;

    tx_buf[0]  =(uint8_t)cmd;
    tx_buf[0] |= (uint8_t)ch_addr;
    
    data  &= AD56X4_MASK_BIT_12_BITS;
    data <<= 4;
    
    tx_buf[1] =(uint8_t)(( data >> 8) & AD56X4_MASK_BIT_LBS);
    tx_buf[2] =(uint8_t) data;
    
    spi_master_select_device( dac->cs_pin);
    spi_master_write( &dac->spi, tx_buf, 3);
    spi_master_deselect_device( dac->cs_pin);  
}

int ad56x4_update_channel(ad56x4_t* dac, uint8_t addr_ch, uint16_t ch_data)
{
    if (ad56x4_check_addr(dac, addr_ch))
    {
        ad56x4_generic_write( dac, AD56X4_COMMAND_WRITE_UPDATE_CHANNEL, addr_ch, ch_data);
        
        return AD56X4_SUCCESS;
    }
    else
    {
        return AD56X4_ERROR;
    }
}

int ad56x4_set_pwr(ad56x4_t* dac, uint8_t pwr_mode, uint8_t ch_sel)
{
    uint8_t tx_buf[3];
    uint8_t rx_buf;
    
    if (ch_sel > AD56X4_MASK_BIT_SEL_CHANNEL)
    {
        return AD56X4_ERROR;
    }
    else
    {
        tx_buf[0]  = AD56X4_COMMAND_POWER_UPDOWN;
        tx_buf[1]  = AD56X4_DONT_CARE_COMMAND;
        tx_buf[2] = (pwr_mode & AD56X4_MASK_BIT_POWERMODE);
        tx_buf[2] |=(ch_sel & AD56X4_MASK_BIT_SEL_CHANNEL);
        
        spi_master_select_device( dac->cs_pin);
        spi_master_write( &dac->spi, tx_buf, 3);
        spi_master_deselect_device( dac->cs_pin);  
        
        return AD56X4_SUCCESS;
    }
}

int ad56x4_sw_reset(ad56x4_t* dac)
{
    uint8_t tx_buf[3];
    uint8_t rx_buf;

    tx_buf[0] = AD56X4_COMMAND_RESET;
    tx_buf[1] = AD56X4_DONT_CARE_COMMAND;
    tx_buf[2] = AD56X4_SW_RST_COMMAND;
    
    spi_master_select_device( dac->cs_pin);
    spi_master_write( &dac->spi, tx_buf, 3);
    spi_master_deselect_device( dac->cs_pin);  
    
    return AD56X4_SUCCESS;
}

int ad56x4_set_ldac(ad56x4_t* dac, uint8_t ldac_mode, uint8_t ch_sel)
{
    uint8_t tx_buf[3];
    uint8_t rx_buf[3];

    if (ch_sel > AD56X4_MASK_BIT_SEL_CHANNEL)
    {
        return AD56X4_ERROR;
    }
    else
    {
        tx_buf[0] = AD56X4_COMMAND_SET_LDAC;
        tx_buf[1] = AD56X4_DONT_CARE_COMMAND;
        tx_buf[2] = ch_sel & AD56X4_MASK_BIT_SEL_CHANNEL;
    
        spi_master_select_device( dac->cs_pin);
        spi_master_write( &dac->spi, tx_buf, 3);
        spi_master_deselect_device( dac->cs_pin);  

        return AD56X4_SUCCESS;
    }
}

int ad56x4_set_ch_voltage(ad56x4_t* dac, uint8_t addr_ch, uint16_t vol_val, uint16_t v_ref_mv)
{
    uint16_t tmp;

    if ((v_ref_mv == AD56X4_VREF_4096mV) || (v_ref_mv == AD56X4_VREF_5000mV))
    {
        if ((vol_val >= 0) || (vol_val < v_ref_mv))
        {
            tmp = (uint16_t)(((uint32_t)vol_val * 4095) / v_ref_mv);

            if (ad56x4_check_addr(dac, addr_ch))
            {
                ad56x4_set_channel(dac, AD56X4_COMMAND_WRITE_UPDATE_CHANNEL, addr_ch, tmp);

                return AD56X4_SUCCESS;
            }
            else
            {
                return AD56X4_ERROR;
            }
        }
        else
        {
            return AD56X4_ERROR;
        }
    }
    else
    {
        return AD56X4_ERROR;
    }
}
