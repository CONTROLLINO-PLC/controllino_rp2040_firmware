/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "wsen_temp.h"
#include "string.h"
 
/* Read the device id */
int wsen_temp_get_id(uint8_t* id)
{
    if (WE_FAIL == ReadReg((uint8_t)TIDS_DEVICE_ID_REG, 1, devID))
        return WE_FAIL;

    return WE_SUCCESS; /* expected value is TIDS_DEVICE_ID_VALUE */

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
* @brief  Set the block data update feature
* @param  state
* @retval Error code
*/
int wsen_temp_setBlockDataUpdate(TIDS_state_t bdu)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.blockDataUpdate = bdu;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}

/**
* @brief  Read the block data update state
* @param  pointer to auto Increment state
* @retval Error code
*/
int wsen_temp_getBlockDataUpdate(TIDS_state_t* bdu)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *bdu = (TIDS_state_t)ctrl_reg.blockDataUpdate;
    return WE_SUCCESS;
}

/**
* @brief  Set the output data rate of the sensor
* @param  output data rate
* @retval Error code
*/
int wsen_temp_setOutputDataRate(TIDS_output_data_rate_t odr)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.outputDataRate = odr;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}

/**
* @brief  Read the output data rate of the sensor
* @param  Pointer to Output Data Rate
* @retval Error code
*/
int wsen_temp_getOutputDataRate(TIDS_output_data_rate_t* odr)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *odr = (TIDS_output_data_rate_t)ctrl_reg.outputDataRate;
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
* @brief  Set the Auto increment feature
* @param  state
* @retval Error code
*/
int wsen_temp_setAutoIncrement(TIDS_state_t inc)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    ctrl_reg.autoAddIncr = inc;

    if (WE_FAIL == WriteReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    return WE_SUCCESS;
}

/**
* @brief  Read the auto increment state
* @param  pointer to auto Increment state
* @retval Error code
*/
int wsen_temp_getAutoIncrement(TIDS_state_t* inc)
{
    TIDS_ctrl_t ctrl_reg;

    if (WE_FAIL == ReadReg((uint8_t)TIDS_CTRL_REG, 1, (uint8_t*)&ctrl_reg))
        return WE_FAIL;

    *inc = (TIDS_state_t)ctrl_reg.autoAddIncr;
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

/**
* @brief  Set temperature high limit
* @param  High limit
* @retval Error code
*/
int wsen_temp_setTempHighLimit(uint8_t hLimit)
{
    if (WE_FAIL == WriteReg((uint8_t)TIDS_LIMIT_T_H_REG, 1, &hLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}
/**
* @brief  Get temperature high limit
* @param  pointer to temperature high limit
* @retval Error code
*/
int wsen_temp_getTempHighLimit(uint8_t* hLimit)
{
    if (WE_FAIL == ReadReg((uint8_t)TIDS_LIMIT_T_H_REG, 1, hLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}


/**
* @brief  Set temperature low limit
* @param  Low limit
* @retval Error code
*/
int wsen_temp_setTempLowLimit(uint8_t lLimit)
{
    if (WE_FAIL == WriteReg((uint8_t)TIDS_LIMIT_T_L_REG, 1, &lLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}


/**
* @brief  Get temperature low limit
* @param  pointer to temperature low limit
* @retval Error code
*/
int wsen_temp_getTempLowLimit(uint8_t* lLimit)
{
    if (WE_FAIL == ReadReg((uint8_t)TIDS_LIMIT_T_L_REG, 1, lLimit))
        return WE_FAIL;

    return WE_SUCCESS;
}

/**         EOF         */
