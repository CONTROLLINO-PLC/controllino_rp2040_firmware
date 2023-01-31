/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "wsen_temp.h"
#include "string.h"
 
/* Initializes default configuration */
void wsen_temp_set_default_cfg(wsen_temp_cfg_t* cfg)
{
    cfg->sda_pin = PLATFORM_I2C_SDA;
    cfg->scl_pin = PLATFORM_I2C_SCL;
    cfg->i2c_speed = PLATFORM_I2C_SPEED;
    cfg->i2c_addr = WSEN_TEMP_ADDRESS_SAO_GND;
    cfg->i2c = PLATFORM_I2C_HW;
    cfg->int_pin = WSEN_TEMP_INT;
}
 
/* Read the device id */
int wsen_temp_get_id(uint8_t* id)
{
    if (WE_FAIL == ReadReg((uint8_t)TIDS_DEVICE_ID_REG, 1, devID))
        return WE_FAIL;

    return WE_SUCCESS; /* expected value is TIDS_DEVICE_ID_VALUE */

}
 
/* Set address auto incrment feature */
int wsen_temp_set_add_incr(wsen_temp_state_t state)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.autoAddIncr = inc;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}
 
/* Read the address auto incrment state */
int wsen_temp_get_add_incr(wsen_temp_state_t* state)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *inc = (TIDS_state_t)ctrl_reg.autoAddIncr;
    return WE_SUCCESS;
}
 
/* Set the block data update feature */
int wsen_temp_set_block_data_upd(wsen_temp_state_t state)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.blockDataUpdate = bdu;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}
 
/* Read the block data update state */
int wsen_temp_get_block_data_upd(wsen_temp_state_t* state)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *bdu = (TIDS_state_t)ctrl_reg.blockDataUpdate;
    return WE_SUCCESS;
}
 
/* Set the output data rate in continuous mode */
int wsen_temp_set_out_rate(wsen_temp_out_rate_t odr)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.outputDataRate = odr;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}
 
/* Read the output data rate */
int wsen_temp_get_out_rate(wsen_temp_out_rate_t* odr)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *odr = (TIDS_output_data_rate_t)ctrl_reg.outputDataRate;
    return WE_SUCCESS;
}
 
/* Set temperature high limit for interrupt */
int wsen_temp_set_int_high_lim(uint8_t limit)
{
    if (WE_FAIL == WriteReg((uint8_t)TIDS_LIMIT_T_H_REG, 1, &hLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}
 
/* Get temperature high limit for interrupt */
int wsen_temp_get_int_high_lim(uint8_t* limit)
{
    if (WE_FAIL == ReadReg((uint8_t)TIDS_LIMIT_T_H_REG, 1, hLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}
 
/* Set temperature low limit for interrupt  */
int wsen_temp_set_int_low_lim(uint8_t limit)
{
    if (WE_FAIL == WriteReg((uint8_t)TIDS_LIMIT_T_L_REG, 1, &lLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}
 
/* Get temperature low limit for interrupt  */
int wsen_temp_get_int_low_lim(uint8_t* limit)
{
    if (WE_FAIL == ReadReg((uint8_t)TIDS_LIMIT_T_L_REG, 1, lLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}
/**
* @brief  Set software reset [enabled,disabled]
* @param  state
* @retval Error code
*/
int wsen_temp_setSwReset(TIDS_state_t mode)
{
    TIDS_soft_reset_t swRstReg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_SOFT_RESET_REG, 1, (uint8_t*)&swRstReg))
        return WE_FAIL;

    swRstReg.reset = mode;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_SOFT_RESET_REG, 1, (uint8_t*)&swRstReg))
        return WE_FAIL;

    return WE_SUCCESS;
}

/**
* @brief  Read the software reset state [enabled,disabled]
* @param  Pointer to software reset state
* @retval Error code
*/
int wsen_temp_getSwReset(TIDS_state_t* mode)
{
    TIDS_soft_reset_t swRstReg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_SOFT_RESET_REG, 1, (uint8_t*)&swRstReg))
        return WE_FAIL;

    *mode = (TIDS_state_t)swRstReg.reset;
    return WE_SUCCESS;
}

/**
* @brief  Set the free run mode[enabled,disabled]
* @param  mode
* @retval Error code
*/
int wsen_temp_setContinuousMode(TIDS_state_t mode)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.freeRunBit = mode;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}
/**
* @brief  Read the Single Conversion Mode state [enabled,disabled]
* @param  Pointer to Single Conversion Mode state
* @retval Error code
*/
int wsen_temp_getContinuousMode(TIDS_state_t* mode)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *mode = (TIDS_state_t)ctrl_reg.freeRunBit;
    return WE_SUCCESS;
}

/**
* @brief  Set the single conversion mode[enabled,disabled]
* @param  mode
* @retval Error code
*/
int wsen_temp_setSingleConvMode(TIDS_state_t mode)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.oneShotbit = mode;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}

/**
* @brief  Read the Single Conversion Mode state [enabled,disabled]
* @param  Pointer to Single Conversion Mode state
* @retval Error code
*/
int wsen_temp_getSingleConvMode(TIDS_state_t* mode)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *mode = (TIDS_state_t)ctrl_reg.oneShotbit;
    return WE_SUCCESS;
}

/**
* @brief  Check if the sensor is busy
* @param  pointer to busy State
* @retval error code
*/
int wsen_temp_getBusyStatus(TIDS_state_t* state)
{
    TIDS_status_t status_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_STATUS_REG, 1, (uint8_t*)&status_reg))
        return WE_FAIL;

    *state = (TIDS_state_t)status_reg.busy;
    return WE_SUCCESS;
}

/**
* @brief  Check if high limit is reached
* @param  pointer to State
* @retval error code
*/
int wsen_temp_getOverHighLimStatus(TIDS_state_t* state)
{
    TIDS_status_t status_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_STATUS_REG, 1, (uint8_t*)&status_reg))
        return WE_FAIL;

    *state = (TIDS_state_t)status_reg.overLimit;
    return WE_SUCCESS;
}

/**
* @brief  Check if low limit is reached
* @param  pointer to State
* @retval error code
*/
int wsen_temp_getUnderLowLimStatus(TIDS_state_t* state)
{
    TIDS_status_t status_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_STATUS_REG, 1, (uint8_t*)&status_reg))
        return WE_FAIL;

    *state = (TIDS_state_t)status_reg.underlimit;
    return WE_SUCCESS;
}

/**
* @brief  Read the raw measured temperature value
* @param  pointer to Temperature Measurement
* @retval Error code
*/
int wsen_temp_getRAWTemperature(uint16_t* rawTemp)
{
    uint8_t tmp[2] = { 0 };

    if (WE_FAIL == ReadReg((uint8_t)TIDS_DATA_T_L_REG, 1, &tmp[0]))
        return WE_FAIL;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_DATA_T_H_REG, 1, &tmp[1]))
        return WE_FAIL;

    *rawTemp = (uint16_t)(tmp[1] << 8);
    *rawTemp |= (uint16_t)tmp[0];
    return WE_SUCCESS;
}

/**
* @brief  Read the measured temperature value in Â°C
* @param  Pointer to Temperature Measurement
* @retval Error code
*/
int wsen_temp_getTemperature(float* tempdegC)
{
    uint16_t rawTemp = 0;
    if (WE_FAIL == TIDS_getRAWTemperature(&rawTemp))
        return WE_FAIL;

    *tempdegC = (float)rawTemp;
    *tempdegC = *tempdegC / 100;
    return WE_SUCCESS;
}