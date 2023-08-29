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
 * Controllino Micro internal diagnosys API
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include "Arduino.h"
 
#include "cy8c95xx.h"
 
/**
 *\brief Measured power suply voltage in millivolts
 *
 */
extern int readVoltageSuply(void);
 
/**
 *\brief Measure current board temperature in °C using WSEN temperature sensor
 *
 */
extern float readBoardTemperature(void);

/**
 *\brief Measure output current in milliamps
 *
 */

/**
 * \brief Enable temperature sensor interrupt
 *
 * \param lowLim low temperature limit in °C
 * \param highLim high temperature limit in °C
 * \param cb callback function to be called on interrupt
 */
void enableTempSensorInt(float lowLim, float highLim, void(*cb)(void));
 
/**
 * \brief Disable temperature sensor interrupt
 *
 */
void disableTempSensorInt(void);
 
/**
 *\brief Enable digital output chip fault interrupt
 *
 * \param do digital output pin CONTROLLINO_MICRO_DO0 ... CONTROLLINO_MICRO_DO7
 * \param cb callback function to be called on interrupt
 */
void enableOutFaultInt(uint8_t doPin, void(*cb)(void));
 
/**
 *\brief Disable digital output chip fault interrupt
 *
 * \param do digital output pin CONTROLLINO_MICRO_DO0 ... CONTROLLINO_MICRO_DO7
 */
void disableOutOverloadInt(uint8_t doPin);
 
#endif  // CONTROLLINO_DIAG_H