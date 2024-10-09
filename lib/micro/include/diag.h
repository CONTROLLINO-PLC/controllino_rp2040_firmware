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
 
#include "adg728.h"
#include "mcp4461.h"
#include "wsen_temp.h"
 
/**
 *\brief Other peripherals used for diagnosys
 *
 */
extern adg728_t* dev_adg728;
extern wsen_temp_t* dev_wsen_temp;
extern mcp4461_t* dev_mcp4461_0;
extern mcp4461_t* dev_mcp4461_1;
 
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
void disableOutFaultInt(uint8_t doPin);
 
/**
 *\brief Set output current limit in milliamps
 *
 * \param do digital output pin CONTROLLINO_MICRO_DO0 ... CONTROLLINO_MICRO_DO7
 * \param currentLim output current limit in milliamps
 */
void setOutCurrentLim(uint8_t doPin, uint16_t currentLim);
 
/**
 *\brief Get output current limit in milliamps
 *
 * \param do digital output pin CONTROLLINO_MICRO_DO0 ... CONTROLLINO_MICRO_DO7
 * \return output current limit in milliamps or 0 if invalid pin
 */
uint16_t getOutCurrentLim(uint8_t doPin);
 
/**
 *\brief Measure output current in milliamps
 *
 * \param do digital output pin CONTROLLINO_MICRO_DO0 ... CONTROLLINO_MICRO_DO7
 * \return output current in milliamps or 0 if invalid pin
 */
uint16_t getOutCurrent(uint8_t doPin);
 
#endif  // CONTROLLINO_DIAG_H