/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef CONTROLLINO_DIAG_H
#define CONTROLLINO_DIAG_H
 
/**
 * \file controllino_diag.h
 *
 * Controllino Neo internal diagnosys API
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include "Arduino.h"
 
/**
 *\brief Digital output current sense
 * 
 */
#define BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH0_OR_CH3  (float)(1330.0F / 104.0F) /* 1340 mA for 104 on the RP2040 ADC */
#define BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH1_OR_CH2  (float)(1340.0F / 252.0F)
#define NEO_CURRENT_SENSE_DO0_DO3_AI_PIN                    (26U)
#define NEO_CURRENT_SENSE_DO4_DO7_AI_PIN                    (27U)
 
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
 
/**
 *\brief Power supply monitor
 *
 */
#define NEO_POWER_SUPLY_CONVERSION_RATIO                    (float)(24000.0F / 505.0F) /* 24000 mV(24 V) for 505 on the RP2040 ADC */
#define NEO_POWER_SUPLY_AI_PIN                              (29U)
 
/**
 *\brief Measure current power suply voltage
 * 
 * \return Measured power suply voltage in millivolts
 */
int readVoltageSuply(void);

/**
 *\brief Measure current board temperature using WSEN temperature sensor
 *
 * \return Measured temperature in °C
 */
float readBoardTemperature(void);

#endif  // NEO_CORE_DIAG_H