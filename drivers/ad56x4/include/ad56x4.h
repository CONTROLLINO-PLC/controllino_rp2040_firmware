/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef AD56X4_H
#define AD56X4_H

/**
 * \file ad56x4.h
 * \ingroup drivers
 * \defgroup ad56x4
 *
 * Driver librarry to handle ad56x4 DAC.
 * Based on MikroE DAC 7 Click driver (Copyright© 2020 MikroElektronika d.o.o.)
 */
 
#include <stdio.h>
#include "hw_platform.h" /* External harware interface library */
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup ad56x4
 */
enum ad56x4_error_code {
    AD56X4_OK =         0x00,
    AD56X4_INIT_ERROR = 0x01,
    AD56X4_SPI_ERROR =  0x02,
    AD56X4_ARG_ERROR =  0x03
};
 
/**
 * \brief Commands bits DB19-DB21
 * \ingroup ad56x4
 */
#define AD56X4_COMMAND_WRITE_INPUT_REGISTER              0x00
#define AD56X4_COMMAND_UPDATE_DAC_REGISTER               0x01
#define AD56X4_COMMAND_WRITE_INPUT_REGISTER_UPDATE_ALL   0x02
#define AD56X4_COMMAND_WRITE_UPDATE_CHANNEL              0x03
#define AD56X4_COMMAND_POWER_UPDOWN                      0x04
#define AD56X4_COMMAND_SW_RESET                          0x05
#define AD56X4_COMMAND_SET_LDAC                          0x06          
 
/**
 * \brief Channel address bits DB16-DB18
 * \ingroup ad56x4
 */
#define AD56X4_ADDRESS_CHANNEL_A                         0x00
#define AD56X4_ADDRESS_CHANNEL_B                         0x01
#define AD56X4_ADDRESS_CHANNEL_C                         0x02
#define AD56X4_ADDRESS_CHANNEL_D                         0x03
#define AD56X4_ADDRESS_CHANNEL_ALL                       0x07
 
/**
 * \brief Software reset mode AD56X4_COMMAND_SW_RESET DB0
 * \ingroup ad56x4
 */
#define AD56X4_SW_RST_PARTIAL                            0x00
#define AD56X4_SW_RST_FULL                               0x01
 
/**
 * \brief Channel select bits DB0-DB3
 * \ingroup ad56x4
 */
#define AD56X4_SELECT_CHANNEL_A                          0x01
#define AD56X4_SELECT_CHANNEL_B                          0x02
#define AD56X4_SELECT_CHANNEL_C                          0x04
#define AD56X4_SELECT_CHANNEL_D                          0x08
#define AD56X4_SELECT_CHANNEL_ALL                        0x0F
 
/**
 * \brief Power modes AD56X4_COMMAND_POWER_UPDOWN DB4-DB5
 * \ingroup ad56x4
 */
#define AD56X4_PWR_MODE_NORMAL                           0x00
#define AD56X4_PWR_MODE_POWERDOWN_1K                     0x10
#define AD56X4_PWR_MODE_POWERDOWN_100K                   0x20
#define AD56X4_PWR_MODE_POWERDOWN_TRISTATE               0x30
 
/**
 * \brief LDAC mode AD56X4_COMMAND_SET_LDAC mask for DB0-DB3
 * \ingroup ad56x4
 */
#define AD56X4_LDAC_NORMAL                               0x00
#define AD56X4_LDAC_TRANSP                               0x01
 
/**
 * \brief Max digital resolution 
 * \ingroup ad56x4
 */
#define AD56X4_12_BITS                                   0x0FFF
#define AD56X4_16_BITS                                   0xFFFF
 
/**
 * \brief Object to store initial config
 * \ingroup ad56x4
 */
typedef struct
{
    int miso_pin;
    int mosi_pin;
    int sck_pin;
    int cs_pin;
    uint spi_speed;
    uint8_t spi_mode;
    hw_spi_t* spi;
} ad56x4_cfg_t;
 
/**
 * \brief AD56X4 dac instance
 * \ingroup ad56x4
 */
typedef struct
{
    int cs_pin;
    hw_spi_t* spi;
} ad56x4_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup ad56x4
 *
 * \param cfg Driver initial configuration
 */
void ad56x4_set_default_cfg(ad56x4_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param cfg Driver initial configuration
 * \return AD56X4_INIT_ERROR : error
 *         AD56X4_OK : successful
 */
int ad56x4_init(ad56x4_t* dac, ad56x4_cfg_t* cfg);
 
/*!
 * \brief Check command bits
 *
 * \param dac Driver instance
 * \param cmd Comand to check
 * \return AD56X4_ARG_ERROR : error
 *         AD56X4_OK : successful
 */
int ad56x4_check_cmd(ad56x4_t* dac, uint8_t cmd);
 
/**
 *\brief Check address bits
 *
 * \param dac Driver instance
 * \param addr Channel address to check
 * \return AD56X4_ARG_ERROR : error
 *         AD56X4_OK : successful
 */
int ad56x4_check_addr(ad56x4_t* dac, uint8_t addr);
 
/*!
 * \brief Generic write data function.
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param cmd Comand
 * \param ch_addr Channel address
 * \param data Data to write
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_generic_write(ad56x4_t* dac, uint8_t cmd, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Write to input register n AD56X4_COMMAND_WRITE_INPUT_REGISTER
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param ch_addr Channel address
 * \param data Data to write
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_write_input_reg(ad56x4_t* dac, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Update DAC register n AD56X4_COMMAND_UPDATE_DAC_REGISTER
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param ch_addr Channel address
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_update_dac_reg(ad56x4_t* dac, uint8_t ch_addr);
 
/*!
 * \brief Write to input register n, update all (software LDAC) AD56X4_COMMAND_WRITE_INPUT_REGISTER_UPDATE_ALL
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param ch_addr Channel address
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successfull
 */
int ad56x4_write_input_reg_update_all_dac(ad56x4_t* dac, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Write to and update DAC channel n AD56X4_COMMAND_WRITE_UPDATE_CHANNEL
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param ch_addr Channel address
 * \param data Data to write
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_write_update_dac_reg(ad56x4_t* dac, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Set power mode
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param pwr_mode Power up or power down mode
 * \param ch_sel Channel selection
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_set_pwr(ad56x4_t* dac, uint8_t pwr_mode, uint8_t ch_sel);
 
/*!
 * \brief Software reset
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_sw_reset(ad56x4_t *dac);
 
/*!
 * \brief Set channel LDAC mode
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param ldac_mode Normal or transparent operation
 * \param ch_sel Channel selection
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_set_ldac(ad56x4_t* dac, uint8_t ldac_mode, uint8_t ch_sel);
 
/*!
 * \brief Set the voltage values of the specified channel function.
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \param addr_ch       3-bit address command.
 * \param vol_val       Voltage values [ from 0 mV to 4096 mV or 5000 mV ].
 * \param v_ref_mv      Voltage reference value.
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
int ad56x4_set_ch_voltage(ad56x4_t* dac, uint8_t addr_ch, uint16_t vol_val, uint16_t v_ref_mv);
 
/*!
 * \brief Enable CS for start SPI coms
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \note Should be implemented externally
 */
void ad56x4_cs_select(ad56x4_t* dac);
 
/*!
 * \brief Disable CS after SPI coms
 * \ingroup ad56x4
 *
 * \param dac Driver instance
 * \note Should be implemented externally
 */
void ad56x4_cs_deselect(ad56x4_t* dac);
 
#ifdef __cplusplus
}
#endif
 
#endif  // AD56X4_H