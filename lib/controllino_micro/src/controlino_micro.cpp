/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "controllino_wiring.h"

/* Peripherals interfaces */
cy8c95xx_t* neo_cy8c95xx;
mcp356x_t* neo_mcp356x;
ad56x4_t* neo_ad56x4;
bts71220_t* neo_bts71220;
wsen_temp_t* neo_wsen_temp;
adg728_t* neo_adg728;

/**
 * Arduino-pico variant initialization
 * Note: This function will be called on every boot before setup()
 */  
void initVariant()
{
    // WSEN temperature sensor
    neo_wsen_temp = (wsen_temp_t*)malloc(sizeof(wsen_temp_t));
    wsen_temp_cfg_t wsen_temp_cfg;
    wsen_temp_set_default_cfg(&wsen_temp_cfg);
    wsen_temp_init(neo_wsen_temp, &wsen_temp_cfg);

    // // Analog multiplexer
    // neo_adg728 = (adg728_t*)malloc(sizeof(adg728_t));
    // adg728_cfg_t adg728_cfg;
    // adg728_set_default_cfg(&adg728_cfg);
    // adg728_init(neo_adg728, &adg728_cfg);

    // Port expander 
    // neo_cy8c95xx = (cy8c95xx_t*)malloc(sizeof(cy8c95xx_t));
    // cy8c95xx_cfg_t cy8c95xx_cfg;
    // cy8c95xx_set_default_cfg(&cy8c95xx_cfg);
    // cy8c95xx_init(neo_cy8c95xx, &cy8c95xx_cfg);
    // cy8c95xx_send_cmd(neo_cy8c95xx, CY8C95XX_STORE_POR_CFG_TO_EEPROM);

    // ADC analog inputs
    neo_mcp356x = (mcp356x_t*)malloc(sizeof(mcp356x_t));
    pinMode(_MCP356X_CS_PIN, OUTPUT);
    mcp356x_cfg_t mcp356x_cfg;
    mcp356x_set_default_cfg(&mcp356x_cfg);
    mcp356x_init(neo_mcp356x, &mcp356x_cfg);
}
 
/* SPI chip select management */
void mcp356x_cs_select(int cs_pin) {
    digitalWrite(_MCP356X_CS_PIN, LOW);
}
void mcp356x_cs_deselect(int cs_pin) {
    digitalWrite(_MCP356X_CS_PIN, HIGH);
}

/* These are not used but need to be defined */
void ad56x4_cs_select(int cs_pin) {}
void ad56x4_cs_deselect(int cs_pin) {}
void bts71220_cs_select(int cs_pin) {}
void bts71220_cs_deselect(int cs_pin) {}

/* Pin definitions for ControllinoRp2040Pin API */
ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI0 = new ControllinoRp2040Pin(MCP356X_CH_CH0, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI1 = new ControllinoRp2040Pin(MCP356X_CH_CH1, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI2 = new ControllinoRp2040Pin(MCP356X_CH_CH2, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI3 = new ControllinoRp2040Pin(MCP356X_CH_CH3, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI4 = new ControllinoRp2040Pin(MCP356X_CH_CH4, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI5 = new ControllinoRp2040Pin(MCP356X_CH_CH5, ControllinoRp2040Pin::MCP356X_PIN);
 
/* Returns ControllinoRp2040Pin API pin or nullptr */
ControllinoRp2040Pin* getControllinoRp2040Pin(int pin)
{
    switch (pin)
    {
    case CONTROLLINO_MICRO_AI0: return _CONTROLLINO_MICRO_AI0;
    case CONTROLLINO_MICRO_AI1: return _CONTROLLINO_MICRO_AI1;
    case CONTROLLINO_MICRO_AI2: return _CONTROLLINO_MICRO_AI2;
    case CONTROLLINO_MICRO_AI3: return _CONTROLLINO_MICRO_AI3;
    case CONTROLLINO_MICRO_AI4: return _CONTROLLINO_MICRO_AI4;
    case CONTROLLINO_MICRO_AI5: return _CONTROLLINO_MICRO_AI5;

    default: break;
    }
    return nullptr;
}