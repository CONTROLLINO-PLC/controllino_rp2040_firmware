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