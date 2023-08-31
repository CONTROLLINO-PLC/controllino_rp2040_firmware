/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef AD5664_H
#define AD5664_H
 
/**
 * \file ad5664.h
 * \ingroup drivers
 * \defgroup ad5664
 *
 * Driver librarry to handle ad5664 DAC.
 * Based on MikroE DAC 7 Click driver (Copyright© 2020 MikroElektronika d.o.o.)
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include <stdint.h>
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup ad5664
 */
typedef int ad5664_err_code_t;
 
/**
 * \brief Commands bits DB19-DB21
 * \ingroup ad5664
 */
typedef enum {
    AD5664_CMD_WRITE_INPUT_REGISTER =               0x00,
    AD5664_CMD_UPDATE_DAC_REGISTER =                0x01,
    AD5664_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL =    0x02,
    AD5664_CMD_WRITE_UPDATE_CH =                    0x03,
    AD5664_CMD_POWER_UPDOWN =                       0x04,
    AD5664_CMD_SW_RESET =                           0x05,
    AD5664_CMD_SET_LDAC =                           0x06
} ad5664_cmd_t;

/**
 * \brief Channel address bits DB16-DB18
 * \ingroup ad5664
 */
typedef enum {
    AD5664_CH_ADDR_A =                              0x00,
    AD5664_CH_ADDR_B =                              0x01,
    AD5664_CH_ADDR_C =                              0x02,
    AD5664_CH_ADDR_D =                              0x03,
    AD5664_CH_ADDR_ALL =                            0x07
} ad5664_ch_addr_t;
 
/**
 * \brief Software reset mode AD5664_CMD_SW_RESET DB0
 * \ingroup ad5664
 */
typedef enum {
    AD5664_SW_RST_PARTIAL =                         0x00,
    AD5664_SW_RST_FULL =                            0x01
} ad5664_sw_rst_t;
 
/**
 * \brief Channel select bits DB0-DB3
 * \ingroup ad5664
 */
typedef enum {
    AD5664_CH_SELECT_A =                            0x01,
    AD5664_CH_SELECT_B =                            0x02,
    AD5664_CH_SELECT_C =                            0x04,
    AD5664_CH_SELECT_D =                            0x08,
    AD5664_CH_SELECT_ALL =                          0x0F
} ad5664_ch_select_t;
 
/**
 * \brief Power modes AD5664_CMD_POWER_UPDOWN DB4-DB5
 * \ingroup ad5664
 */
typedef enum {
    AD5664_PWR_MODE_NORMAL =                        0x00,
    AD5664_PWR_MODE_POWERDOWN_1K =                  0x01,
    AD5664_PWR_MODE_POWERDOWN_100K =                0x02,
    AD5664_PWR_MODE_POWERDOWN_TRISTATE =            0x03
} ad5664_pwr_mode_t;
 
/**
 * \brief Other helpful definitions
 * \ingroup ad5664
 */
#define AD5664_CH_DONT_CARE                         AD5664_CH_ADDR_A
#define AD5664_DATA_DONT_CARE                       0x0000
 
/**
 * \brief Max digital resolution 
 * \ingroup ad5664
 */
#define AD5624_12_BITS                               0x0FFF
#define AD5664_16_BITS                               0xFFFF
#ifndef AD5664_RESOLUTION
#define AD5664_RESOLUTION                            AD5664_16_BITS 
#endif
 
/**
 * \brief External pins
 * \ingroup ad5664
 */
#ifndef AD5664_CS
#define AD5664_CS       -1
#endif
 
/**
 * \brief External hardware SPI interface
 */
typedef struct _hw_spi_t* hw_spi_t;
 
/**
 * \brief Initial config struct
 * \ingroup ad5664
 */
typedef struct
{
    int mosi_pin;
    int miso_pin;
    int sck_pin;
    int cs_pin;
    unsigned int spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t spi;
    uint16_t resolution;
} ad5664_cfg_t;
 
/**
 * \brief AD5664 DAC instance
 * \ingroup ad5664
 */
typedef struct
{
    int cs_pin;
    unsigned int spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t spi;
    uint16_t resolution;
} ad5664_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup ad5664
 *
 * \param cfg Initial config struct
 */
void ad5664_set_default_cfg(ad5664_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param cfg Initial config struct
 * \return PLATFORM_SPI_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_SPI_COM_ERR : error
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_init(ad5664_t* dev, ad5664_cfg_t* cfg);
 
/*!
 * \brief Generic write data function.
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param cmd Comand
 * \param ch_addr Channel address
 * \param data Data to write
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_generic_write(ad5664_t* dev, ad5664_cmd_t cmd, ad5664_ch_addr_t ch_addr, uint16_t data);
 
/*!
 * \brief Write to input register n AD5664_CMD_WRITE_INPUT_REGISTER
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param ch_addr Channel address
 * \param data Data to write
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_write_input_reg(ad5664_t* dev, ad5664_ch_addr_t ch_addr, uint16_t data);
 
/*!
 * \brief Update DAC register n AD5664_CMD_UPDATE_DAC_REGISTER
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param ch_addr Channel address
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_update_dac_reg(ad5664_t* dev, ad5664_ch_addr_t ch_addr);
 
/*!
 * \brief Write to input register n, update all (software LDAC) AD5664_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param ch_addr Channel address
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successfull
 */
ad5664_err_code_t ad5664_write_input_reg_update_all_dac(ad5664_t* dev, ad5664_ch_addr_t ch_addr, uint16_t data);
 
/*!
 * \brief Write to and update DAC channel n AD5664_CMD_WRITE_UPDATE_CH
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param ch_addr Channel address
 * \param data Data to write
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_write_update_dac_reg(ad5664_t* dev, ad5664_ch_addr_t ch_addr, uint16_t data);
 
/*!
 * \brief Set power mode AD5664_CMD_POWER_UPDOWN
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param pwr_mode Power up or power down mode
 * \param ch_sel Channel selection
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_set_pwr(ad5664_t* dev, ad5664_pwr_mode_t pwr_mode, ad5664_ch_select_t ch_sel);
 
/*!
 * \brief Software reset AD5664_CMD_SW_RESET
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param rst_mode Reset mode
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_sw_reset(ad5664_t* dev, ad5664_sw_rst_t rst_mode);
 
/*!
 * \brief Set channel LDAC mode AD5664_CMD_SET_LDAC
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param ch_ldev_mode DB0-DB3 channel LDAC config
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 * \note Value 1 in channel bit means LDAC transparent, 0 means LDAC normal
 */
ad5664_err_code_t ad5664_set_ldev(ad5664_t* dev, uint8_t ch_ldev_mode);
 
/*!
 * \brief Set the voltage values of the specified channel
 * \ingroup ad5664
 *
 * \param dev Pointer to AD5664 DAC struct
 * \param ch_addr Channel address
 * \param vol_val Desired voltage value in millivolts
 * \param vol_ref_max Maximun reference voltage in millivolts equivalent to max resolution
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
ad5664_err_code_t ad5664_set_ch_voltage(ad5664_t* dev, ad5664_ch_addr_t ch_addr, uint16_t vol_val, uint16_t vol_ref_max);
 
/*!
 * \brief Enable CS for start SPI coms
 * \ingroup ad5664
 *
 * \param cs_pin Chip select pin
 * \note Should be implemented externally
 */
void ad5664_cs_select(int cs_pin);
 
/*!
 * \brief Disable CS after SPI coms
 * \ingroup ad5664
 *
 * \param dev cs_pin Chip select pin
 * \note Should be implemented externally
 */
void ad5664_cs_deselect(int cs_pin);
 
#ifdef __cplusplus
}
#endif
 
#endif  // AD5664_H