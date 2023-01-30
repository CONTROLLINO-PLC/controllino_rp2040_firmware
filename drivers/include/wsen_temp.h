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
 * Driver librarry to handle WE sensors 2521020222501 temperature sensor.
 * Based on WE Sensor libraries (https://github.com/WurthElektronik/SensorLibrariesArduino )
 */
 
#include <stdio.h>
#include "hw_platform.h" /* External harware interface library */
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup wsen_temp
 */
typedef enum {
    WSEN_TEMP_OK =          PLATFORM_OK,
    WSEN_TEMP_ARG_ERROR =   PLATFORM_ARGUMENT_ERROR,
    WSEN_TEMP_INIT_ERROR =  PLATFORM_I2C_INIT_ERROR,
    WSEN_TEMP_I2C_ERROR =   PLATFORM_I2C_COM_ERROR
} wsen_error_code_t;
 
/**
 * \brief Posible I2C Slave addresses
 * \ingroup wsen_temp
 */ 
#define WSEN_TEMP_ADDRESS_SAO_0		0x3F /* when SAO of TIDS is connected to logic LOW level */
#define WSEN_TEMP_ADDRESS_SAO_1		0x38 /* when SAO of TIDS is connected to logic HIGH level */
 
/**
 * \brief Device id
 * \ingroup wsen_temp
 */
#define WSEN_TEMP_DEVICE_ID_VALUE   0xA0 /* Device ID of TIDS 2521020222501 Sensor */
 
/**
 * \brief Register map
 * \ingroup wsen_temp
 */
typedef enum {
    WSEN_TEMP_DEVICE_ID_REG =       0x01 /* Device ID register */
    WSEN_TEMP_LIMIT_T_H_REG =       0x02 /* Temperature high limit register */
    WSEN_TEMP_LIMIT_T_L_REG =       0x03 /* Temperature low limit register */
    WSEN_TEMP_CTRL_REG =            0x04 /* Control Register*/
    WSEN_TEMP_STATUS_REG =          0x05 /* Status Register */
    WSEN_TEMP_DATA_T_L_REG =        0x06 /* Temperature Output LSB value Register */
    WSEN_TEMP_DATA_T_H_REG =        0x07 /* Temperature Output MSB value Register */
    WSEN_TEMP_SOFT_RESET_REG =      0x0C /* Software reset register */
} wsen_temp_reg_t;
 
/**
 * \brief Control register
 * \ingroup wsen_temp
 *
 * Address 0x04
 * Type  R/W
 * Default value: 0x00
 *      AVG1  | AVG0  | Temperature output data-rate(Hz)
 *   ---------------- ----------------------------------------------------
 *       0    |  0    |      25
 *       0    |  1    |      50
 *       1    |  0    |      100
 *       1    |  1    |      200
 */
typedef struct {
    uint8_t one_shot        : 1; /* Trigger a single measurement by setting this bit to 1; Bit automatically reset to 0*/
    uint8_t reserved01      : 1; /* Must be set to 0 */
    uint8_t free_run        : 1; /* FREERUN : 1:Enable continuous mode 0:Disable continuous mode */
    uint8_t auto_add_incr   : 1; /* IF_ADD_INC : Register address automatically incremented during a multiple byte access with I2C interface. Default value 1.( 0: disable; 1: enable) */
    uint8_t out_data_rate   : 2; /* AVG[1:0]: Output data rate in continuous mode.Default '00' */
    uint8_t block_data_upd  : 1; /* BDU : Block data update. 0 - Continuous update; 1 - Output registers not update till both MSB and LSB are read */
    uint8_t reserved02      : 1; /* Must be set to 0 */
} wsen_temp_ctrl_t;
 
/**
 * \brief Status register
 * \ingroup wsen_temp
 *
 * Address 0x05
 * Type R only
 * Default value: 0x00
 */
typedef struct {
    uint8_t busy            : 1; /* BUSY : Temperature conversion status.(0: data conversion complete; 1: data conversion in progress) */
    uint8_t over_lim        : 1; /* OVER_THL :Temperature higher limit status. (0: temperature is below limit or disabled; 1: temperature exceeded high limit*/
    uint8_t under_lim       : 2; /* UNDER_TLL :Temperature lower limit status. (0: temperature is below limit or disabled; 1: temperature exceeded low limit*/
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
typedef struct {
    uint8_t reserved01      : 1; /* Must be set to 0 */
    uint8_t reset           : 1; /* SOFT_RESET : Reset the digital block by setting this bit to 1 */
    uint8_t reserved06      : 6; /* Must be set to 0 */
} wsen_temp_reset_t;
 
/**
 * \brief Enable disable state
 * \ingroup wsen_temp
 */
typedef enum {
    WSEN_TEMP_DISABLE =     0,
    WSEN_TEMP_ENABLE =      1
} wsen_temp_state_t;
 
/**
 * \brief Output data rate
 * \ingroup wsen_temp
 */
typedef enum {
    WSEN_TEMP_ODR_25HZ =    0, /* 25 Hz */
    WSEN_TEMP_ODR_50HZ =    1, /* 50 Hz */
    WSEN_TEMP_ODR_100HZ =   2, /* 100 Hz */
    WSEN_TEMP_ODR_200HZ =   3, /* 200 Hz */
} wsen_temp_out_rate_t;
 
/**
 * \brief Initial config struct
 * \ingroup wsen_temp
 */
typedef struct {
    int sda_pin;
    int scl_pin;
    uint i2c_speed;
    uint8_t i2c_addr;
    hw_i2c_t* i2c;
    int int_pin;
} wsen_temp_cfg_t;
 
/**
 * \brief WE sensors 2521020222501 temperature sensor struct
 * \ingroup wsen_temp
 */
typedef struct
{
    uint8_t slave_addr;
    hw_i2c_t* i2c;
    int int_pin;
} wsen_temp_t;
 
/*!
 * \brief Read the device id
 * \ingroup wsen_temp
 *
 * \param id Pointer to receive the device id
 * \return WSEN_TEMP_I2C_ERROR : error in coms
 *         WSEN_TEMP_ARG_ERROR : error in arguments
 *         WSEN_TEMP_OK : successful
 */
int wsen_temp_get_id(uint8_t* id);

    /* Temperature limits */
    int wsen_temp_setTempHighLimit(uint8_t hLimit);
    int wsen_temp_setTempLowLimit(uint8_t lLimit);

    int wsen_temp_getTempHighLimit(uint8_t* hLimit);
    int wsen_temp_getTempLowLimit(uint8_t* lLimit);

    /* Block data update */
    int wsen_temp_setBlockDataUpdate(TIDS_state_t bdu);
    int wsen_temp_getBlockDataUpdate(TIDS_state_t* bdu);

    /* Output data rate */
    int wsen_temp_setOutputDataRate(TIDS_output_data_rate_t odr);
    int wsen_temp_getOutputDataRate(TIDS_output_data_rate_t* odr);

    /* Address auto increment */
    int wsen_temp_setAutoIncrement(TIDS_state_t inc);
    int wsen_temp_getAutoIncrement(TIDS_state_t* inc);

    /* Free run mode */
    int wsen_temp_setContinuousMode(TIDS_state_t mode);
    int wsen_temp_getContinuousMode(TIDS_state_t* mode);

    /* One shot mode */
    int wsen_temp_setSingleConvMode(TIDS_state_t mode);
    int wsen_temp_getSingleConvMode(TIDS_state_t* mode);

    /* Status */
    int wsen_temp_getOverHighLimStatus(TIDS_state_t* state);
    int wsen_temp_getUnderLowLimStatus(TIDS_state_t* state);
    int wsen_temp_getBusyStatus(TIDS_state_t* state);

    /* Software reset */
    int wsen_temp_setSwReset(TIDS_state_t mode);
    int wsen_temp_getSwReset(TIDS_state_t* mode);

    /* standard Data Out */
    int wsen_temp_getRAWTemperature(uint16_t* rawTemp);
    int wsen_temp_getTemperature(float* tempdegC);  // Temperature Value in °C

#ifdef __cplusplus
}
#endif

#endif /* _WSEN_TIDS_H */
/**         EOF         */
