/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef NEO_CORE_DIAG_H
#define NEO_CORE_DIAG_H
 
/**
 * \file neo_core_diag.h
 *
 * API access to some internal diagnosys functionalities
 */
 
#include "Arduino.h"
 
/**
 *\brief Digital output current sense
 * 
 */
#define BTS71220_CURRENT_SENSE_CONVERSION_CH0_OR_CH3    (float)(1330.0F / 104.0F) /* 1340 mA for 104 on the RP2040 AI */
#define BTS71220_CURRENT_SENSE_CONVERSION_CH1_OR_CH2    (float)(1340.0F / 252.0F)
#define NEO_CURRENT_SENSE_DO0_DO3_AI_PIN                (26U)
#define NEO_CURRENT_SENSE_DO4_DO7_AI_PIN                (27U)

/**
 *\brief Enable current sense for the selected digital output
 * 
 * \param DO Digital output to select for current sense (0-7)
 */
void enableCurrentSenseDO(uint8_t DO);
 
/**
 *\brief Disable current sense for digital output
 *
 */
void disableCurrentSenseDO(void);
 
/**
 *\brief Measure current in previously selected digital output
 * 
 * \return Measured current in milliamps
 */
int readCurrentSenseDO(void);
 
#endif  // NEO_CORE_DIAG_H