/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "neo_core_diag.h"

/* Selected DO for current sennsing */
static uint8_t _DO = 9;

/* Current sense enabled for the selected digital output */
void enableCurrentSenseDO(uint8_t DO)
{
    _DO = DO;
    disableCurrentSenseDO();
    switch (DO)
    {
    case 0:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH3, 1);
        break;
    case 1:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH2, 1);
        break;
    case 2:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH1, 1);
        break;
    case 3:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH0, 1);
        break;
    case 4:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH3, 0);
        break;
    case 5:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH2, 0);
        break;
    case 6:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH1, 0);
        break;
    case 7:
        bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_CH0, 0);
        break;
    default:
        break;
    }
}
 
/* Disable current sense for digital output */
void disableCurrentSenseDO(void)
{
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_SLEEP_Z, 0);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_SLEEP_Z, 1);
}
/* Measure current in previously selected digital output */
int readCurrentSenseDO()
{
    int current = 0;
    if (_DO < 9)
    {
        switch (_DO)
        {
        case 0:
        case 3:
            current = analogRead(NEO_CURRENT_SENSE_DO0_DO3_AI_PIN) * BTS71220_CURRENT_SENSE_CONVERSION_CH0_OR_CH3;
            break;
        case 1:
        case 2:
            current = analogRead(NEO_CURRENT_SENSE_DO0_DO3_AI_PIN) * BTS71220_CURRENT_SENSE_CONVERSION_CH1_OR_CH2;
            break;
        case 4:
        case 7:
            current = analogRead(NEO_CURRENT_SENSE_DO4_DO7_AI_PIN) * BTS71220_CURRENT_SENSE_CONVERSION_CH0_OR_CH3;
            break;
        case 5:
        case 6:
            current = analogRead(NEO_CURRENT_SENSE_DO4_DO7_AI_PIN) * BTS71220_CURRENT_SENSE_CONVERSION_CH1_OR_CH2;
            break;
        default:
            break;
        }
    }
    return current;
}
