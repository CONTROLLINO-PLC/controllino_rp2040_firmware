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
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI0;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI1;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI2;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI3;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI4;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI5;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI6;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AI7;

extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AO0;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AO1;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AO2;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_AO3;

extern ControllinoRp2040Pin* _CONTROLLINO_NEO_DO4;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_DO5;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_DO6;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_DO7;

extern ControllinoRp2040Pin* _CONTROLLINO_NEO_RE_PIN;
extern ControllinoRp2040Pin* _CONTROLLINO_NEO_DE_PIN;
 
#endif