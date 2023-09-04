/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef WSEN_TEMP_H
#define WSEN_TEMP_H

/**
 * \file wsen_temp.h
 * \ingroup drivers
 * \defgroup wsen_temp
 *
 * Driver librarry to handle 2521020222501 temperature sensor.
 * Based on WE Sensor libraries (https://github.com/WurthElektronik/SensorLibrariesArduino )
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
 * \ingroup wsen_temp
 */
typedef int wsen_temp_err_code_t;
 
/**
 * \brief Posible I2C Slave addresses
 * \ingroup wsen_temp
 */ 
#define WSEN_TEMP_ADDRESS_SAO_GND	0x3F /* when SAO of TIDS is connected to logic LOW level */
#define WSEN_TEMP_ADDRESS_SAO_VCC	0x38 /* when SAO of TIDS is connected to logic HIGH level */
 
/**
 * \brief Device id
 * \ingroup wsen_temp
 */
#define WSEN_TEMP_DEVICE_ID_VALUE   0xA0 /* Device ID of TIDS 2521020222501 Sensor */
 
/**
 * \brief Register map
 * \ingroup wsen_temp
 */
typedef enum
{
    WSEN_TEMP_REG_DEVICE_ID =  0x01, /* Device ID register */
    WSEN_TEMP_REG_HIGH_LIM =   0x02, /* Temperature high limit register */
    WSEN_TEMP_REG_LOW_LIM =    0x03, /* Temperature low limit register */
    WSEN_TEMP_REG_CTRL =       0x04, /* Control Register*/
    WSEN_TEMP_REG_STATUS =     0x05, /* Status Register */
    WSEN_TEMP_REG_DATA_T_L =   0x06, /* Temperature Output LSB value Register */
    WSEN_TEMP_REG_DATA_T_H =   0x07, /* Temperature Output MSB value Register */
    WSEN_TEMP_REG_SOFT_RESET = 0x0C /* Software reset register */
} wsen_temp_reg_t;
 
/**
 * \brief Control register
 * \ingroup wsen_temp
 *
 * Address 0x04
 * Type  R/W
 * Default value: 0x00
 */
typedef struct
{
    uint8_t one_shot        : 1; /* Trigger a single measurement by setting this bit to 1; Bit automatically reset to 0*/
    uint8_t reserved01      : 1; /* Must be set to 0 */
    uint8_t free_run        : 1; /* FREERUN : 1:Enable continuous mode 0:Disable continuous mode */
    uint8_t add_inc         : 1; /* IF_ADD_INC : Register address automatically incremented during a multiple byte access with I2C interface. Default value 1.( 0: disable; 1: enable) */
    uint8_t out_rate        : 2; /* AVG[1:0]: Output data rate in continuous mode.Default '00' */
    uint8_t block_data_upd  : 1; /* BDU : Block data update. 0 - Continuous update; 1 - Output registers not update till both MSB and LSB are read */
    uint8_t reserved02      : 1; /* Must be set to 0 */
} wsen_temp_ctrl_t;
 
/**
 * \brief Control register posible settings
 * \ingroup wsen_temp
 */
#define WSEN_TEMP_CTRL_ONE_SHOT_EN          0x01
#define WSEN_TEMP_CTRL_ONE_SHOT_DIS         0x00

#define WSEN_TEMP_CTRL_FREE_RUN_EN          0x01
#define WSEN_TEMP_CTRL_FREE_RUN_DIS         0x00

#define WSEN_TEMP_CTRL_ADD_INC_EN           0x01
#define WSEN_TEMP_CTRL_ADD_INC_DIS          0x00

#define WSEN_TEMP_CTRL_ODR_25HZ             0x00 /* 25 Hz */
#define WSEN_TEMP_CTRL_ODR_50HZ             0x01 /* 50 Hz */
#define WSEN_TEMP_CTRL_ODR_100HZ            0x02 /* 100 Hz */
#define WSEN_TEMP_CTRL_ODR_200HZ            0x03 /* 200 Hz */

#define WSEN_TEMP_CTRL_BLOCK_DATA_UPD_EN    0x01
#define WSEN_TEMP_CTRL_BLOCK_DATA_UPD_DIS   0x00
 
/**
 * \brief Status register
 * \ingroup wsen_temp
 *
 * Address 0x05
 * Type R only
 * Default value: 0x00
 */
typedef struct
{
    uint8_t busy            : 1; /* BUSY : Temperature conversion status.(0: data conversion complete; 1: data conversion in progress) */
    uint8_t over_lim        : 1; /* OVER_THL :Temperature higher limit status. (0: temperature is below limit or disabled; 1: temperature exceeded high limit*/
    uint8_t under_lim       : 1; /* UNDER_TLL :Temperature lower limit status. (0: temperature is below limit or disabled; 1: temperature exceeded low limit*/
    uint8_t reserved05      : 5; /* Must be set to 0 */
} wsen_temp_status_t;
 
/**
 * \brief Software reset register
 * \ingroup wsen_temp
 *
 * Address 0x0C
 * Type  R/W
 * Default value: 0x00
 */
typedef struct
{
    uint8_t reserved01      : 1; /* Must be set to 0 */
    uint8_t reset           : 1; /* SOFT_RESET : Reset the digital block by setting this bit to 1 */
    uint8_t reserved06      : 6; /* Must be set to 0 */
} wsen_temp_reset_t;
 
/**
 * \brief External pins
 * \ingroup wsen_temp
 */
#ifndef WSEN_TEMP_INT
#define WSEN_TEMP_INT        -1
#endif
 
/**
 * \brief External hardware I2C interface
 */
typedef struct _hw_i2c_t* hw_i2c_t;
 
/**
 * \brief Initial config struct
 * \ingroup wsen_temp
 */
typedef struct
{
    int sda_pin;
    int scl_pin;
    unsigned int i2c_speed;
    uint8_t i2c_addr;
    hw_i2c_t i2c;
    int int_pin;
    wsen_temp_ctrl_t ctrl_reg;
} wsen_temp_cfg_t;
 
/**
 * \brief WE sensors 2521020222501 temperature sensor struct
 * \ingroup wsen_temp
 */
typedef struct
{
    uint8_t i2c_addr;
    hw_i2c_t i2c;
    int int_pin;
} wsen_temp_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup wsen_temp
 *
 * \param cfg Initial config struct
 */
void wsen_temp_set_default_cfg(wsen_temp_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param cfg Initial config struct
 * \return PLATFORM_I2C_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_I2C_COM_ERR : error
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_init(wsen_temp_t* dev, wsen_temp_cfg_t* cfg);
 
/*!
 * \brief Writes data to registers
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param reg Register address
 * \param txdata Pointer to data to send
 * \param txlen Number of the bytes in data buf
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_generic_write(wsen_temp_t* dev, wsen_temp_reg_t reg, uint8_t* txdata, uint8_t txlen);
 
/*!
 * \brief Reads data from registers
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param reg Register address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of the bytes to be read
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_generic_read(wsen_temp_t* dev, wsen_temp_reg_t reg, uint8_t* rxdata, uint8_t rxlen);
 
/*!
 * \brief Read the device id
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param id Pointer to receive the device id
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_get_id(wsen_temp_t* dev, uint8_t* id);
 
/*!
 * \brief Software reset
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_sw_rst(wsen_temp_t* dev);
 
/*!
 * \brief Set CONTROL register settings
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param ctrl Pointer to control register settings
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_set_ctrl(wsen_temp_t* dev, wsen_temp_ctrl_t* ctrl);
 
/*!
 * \brief Get CONTROL register current state
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param ctrl Pointer to receive current control register state
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_get_ctrl(wsen_temp_t* dev, wsen_temp_ctrl_t* ctrl);
 
/*!
 * \brief Get STATUS register current state
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param status Pointer to receive current status register state
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_get_status(wsen_temp_t* dev, wsen_temp_status_t* status);
 
/*!
 * \brief Set temperature high limit for interrupt
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param celsius Limit to set in celsius degrees
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_set_high_lim(wsen_temp_t* dev, float celsius);
 
/*!
 * \brief Get temperature high limit for interrupt
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param celsius Pointer to receive current limit value in celsius degrees
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_get_high_lim(wsen_temp_t* dev, float* celsius);
 
/*!
 * \brief Set temperature low limit for interrupt
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param celsius Limit to set in celsius degrees
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_set_low_lim(wsen_temp_t* dev, float celsius);
 
/*!
 * \brief Get temperature low limit for interrupt
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param celsius Pointer to receive current limit value in celsius degrees
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_get_low_lim(wsen_temp_t* dev, float* celsius);
 
/*!
 * \brief Disable interrupt generation
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_dis_int(wsen_temp_t* dev);
 
/*!
 * \brief Get raw temperature digital value
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param temp Pointer to receive temperature
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_get_raw(wsen_temp_t* dev, uint16_t* temp);
 
/*!
 * \brief Get temperature value in °C
 * \ingroup wsen_temp
 *
 * \param dev Pointer to temp sensor struct
 * \param temp Pointer to receive temperature
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
wsen_temp_err_code_t wsen_temp_get_celsius(wsen_temp_t* dev, float* temp);
 
#ifdef __cplusplus
}
#endif
 
#endif /* WSEN_TEMP_H */
