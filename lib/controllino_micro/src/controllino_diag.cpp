/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "controllino_diag.h"

 /* Power monitoring is connected to MCP356X_CH_CH6 */
ControllinoRp2040Pin* POWER_SUPLY_AI_PIN = new ControllinoRp2040Pin(MCP356X_CH_CH6, ControllinoRp2040Pin::MCP356X_PIN);

/* Measure current power suply voltage in millivolts */
int readVoltageSuply(void)
{
    float mV = ((float)analogRead(POWER_SUPLY_AI_PIN)) * POWER_SUPLY_CONVERSION_RATIO;
    return (int)mV;
}
 
/* Measure current board temperature using WSEN temperature sensor */
float readBoardTemperature(void)
{
    float celsius = 0;
    wsen_temp_get_celsius(neo_wsen_temp, &celsius);
    return celsius;
}