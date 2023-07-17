/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef CONTROLLINO_PINS_H
#define CONTROLLINO_PINS_H
 
/**
 * \file controlino_pins.h
 *
 * User available definitions for internal pins configuration
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include "controllino_driver.h"
 
/**
 * \brief User can access the pin definitions for Controllino RP2040 pins API
 */
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI0;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI1;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI2;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI3;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI4;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI5;
 
#endif