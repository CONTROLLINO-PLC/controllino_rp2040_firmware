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
typedef enum {
    AD56X4_OK =         PLATFORM_OK,
    AD56X4_ARG_ERROR =  PLATFORM_ARGUMENT_ERROR,
    AD56X4_INIT_ERROR = PLATFORM_SPI_INIT_ERROR,
    AD56X4_SPI_ERROR =  PLATFORM_SPI_COM_ERROR
} ad56x4_error_code_t;
 
/**
 * \brief Commands bits DB19-DB21
 * \ingroup ad56x4
 */
#define AD56X4_CMD_WRITE_INPUT_REGISTER             0x00
#define AD56X4_CMD_UPDATE_DAC_REGISTER              0x01
#define AD56X4_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL  0x02
#define AD56X4_CMD_WRITE_UPDATE_CH                  0x03
#define AD56X4_CMD_POWER_UPDOWN                     0x04
#define AD56X4_CMD_SW_RESET                         0x05
#define AD56X4_CMD_SET_LDAC                         0x06          
 
/**
 * \brief Channel address bits DB16-DB18
 * \ingroup ad56x4
 */
#define AD56X4_ADDR_CH_A                            0x00
#define AD56X4_ADDR_CH_B                            0x01
#define AD56X4_ADDR_CH_C                            0x02
#define AD56X4_ADDR_CH_D                            0x03
#define AD56X4_ADDR_CH_ALL                          0x07
 
/**
 * \brief Software reset mode AD56X4_CMD_SW_RESET DB0
 * \ingroup ad56x4
 */
#define AD56X4_SW_RST_PARTIAL                       0x00
#define AD56X4_SW_RST_FULL                          0x01
 
/**
 * \brief Channel select bits DB0-DB3
 * \ingroup ad56x4
 */
#define AD56X4_SELECT_CH_A                          0x01
#define AD56X4_SELECT_CH_B                          0x02
#define AD56X4_SELECT_CH_C                          0x04
#define AD56X4_SELECT_CH_D                          0x08
#define AD56X4_SELECT_CH_ALL                        0x0F
 
/**
 * \brief Power modes AD56X4_CMD_POWER_UPDOWN DB4-DB5
 * \ingroup ad56x4
 */
#define AD56X4_PWR_MODE_NORMAL                       0x00
#define AD56X4_PWR_MODE_POWERDOWN_1K                 0x01
#define AD56X4_PWR_MODE_POWERDOWN_100K               0x02
#define AD56X4_PWR_MODE_POWERDOWN_TRISTATE           0x03
 
/**
 * \brief Max digital resolution 
 * \ingroup ad56x4
 */
#define AD5624_12_BITS                               0x0FFF
#define AD5664_16_BITS                               0xFFFF
#ifndef AD56X4_RESOLUTION
#define AD56X4_RESOLUTION                            AD5664_16_BITS 
#endif
 
/**
 * \brief External pins
 * \ingroup ad56x4
 */
#ifndef AD56X4_CS
#define AD56X4_CS       -1
#endif
 
/**
 * \brief Initial config struct
 * \ingroup ad56x4
 */
typedef struct
{
    int mosi_pin;
    int miso_pin;
    int sck_pin;
    int cs_pin;
    uint spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t* spi;
    uint16_t resolution;
} ad56x4_cfg_t;
 
/**
 * \brief AD56X4 DAC instance
 * \ingroup ad56x4
 */
typedef struct
{
    int cs_pin;
    uint spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t* spi;
    uint16_t resolution;
} ad56x4_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup ad56x4
 *
 * \param cfg Initial config struct
 */
void ad56x4_set_default_cfg(ad56x4_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param cfg Initial config struct
 * \return AD56X4_INIT_ERROR : error
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_init(ad56x4_t* dev, ad56x4_cfg_t* cfg);
 
/*!
 * \brief Generic write data function.
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param cmd Comand
 * \param ch_addr Channel address
 * \param data Data to write
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_generic_write(ad56x4_t* dev, uint8_t cmd, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Write to input register n AD56X4_CMD_WRITE_INPUT_REGISTER
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param ch_addr Channel address
 * \param data Data to write
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_write_input_reg(ad56x4_t* dev, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Update DAC register n AD56X4_CMD_UPDATE_DAC_REGISTER
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param ch_addr Channel address
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_update_dev_reg(ad56x4_t* dev, uint8_t ch_addr);
 
/*!
 * \brief Write to input register n, update all (software LDAC) AD56X4_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param ch_addr Channel address
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successfull
 */
ad56x4_error_code_t ad56x4_write_input_reg_update_all_dev(ad56x4_t* dev, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Write to and update DAC channel n AD56X4_CMD_WRITE_UPDATE_CH
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param ch_addr Channel address
 * \param data Data to write
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_write_update_dev_reg(ad56x4_t* dev, uint8_t ch_addr, uint16_t data);
 
/*!
 * \brief Set power mode AD56X4_CMD_POWER_UPDOWN
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param pwr_mode Power up or power down mode
 * \param ch_sel Channel selection
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_set_pwr(ad56x4_t* dev, uint8_t pwr_mode, uint8_t ch_sel);
 
/*!
 * \brief Software reset AD56X4_CMD_SW_RESET
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param rst_mode Reset mode
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_sw_reset(ad56x4_t* dev, uint8_t rst_mode);
 
/*!
 * \brief Set channel LDAC mode AD56X4_CMD_SET_LDAC
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param ch_ldev_mode DB0-DB3 channel LDAC config
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 * \note Value 1 in channel bit means LDAC transparent, 0 means LDAC normal
 */
ad56x4_error_code_t ad56x4_set_ldev(ad56x4_t* dev, uint8_t ch_ldev_mode);
 
/*!
 * \brief Set the voltage values of the specified channel
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \param ch_addr Channel address
 * \param vol_val Desired voltage value in millivolts
 * \param vol_ref_max Maximun reference voltage in millivolts equivalent to max resolution
 * \return AD56X4_SPI_ERROR : error in coms
 *         AD56X4_ARG_ERROR : error in arguments
 *         AD56X4_OK : successful
 */
ad56x4_error_code_t ad56x4_set_ch_voltage(ad56x4_t* dev, uint8_t ch_addr, uint16_t vol_val, uint16_t vol_ref_max);
 
/*!
 * \brief Enable CS for start SPI coms
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \note Should be implemented externally
 */
void ad56x4_cs_select(ad56x4_t* dev);
 
/*!
 * \brief Disable CS after SPI coms
 * \ingroup ad56x4
 *
 * \param dev Pointer to AD56X4 DAC struct
 * \note Should be implemented externally
 */
void ad56x4_cs_deselect(ad56x4_t* dev);
 
#ifdef __cplusplus
}
#endif
 
#endif  // AD56X4_H