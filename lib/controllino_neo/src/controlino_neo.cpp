/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "controllino_wiring.h"

/* Peripherals interfaces */
cy8c9520_t* neo_cy8c9520;
mcp3564_t* neo_mcp3564;
ad5664_t* neo_ad5664;
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

    // Port expander 
    neo_cy8c9520 = (cy8c9520_t*)malloc(sizeof(cy8c9520_t));
    cy8c9520_cfg_t cy8c9520_cfg;
    cy8c9520_set_default_cfg(&cy8c9520_cfg);
    cy8c9520_init(neo_cy8c9520, &cy8c9520_cfg);

    // Digital output pins to low level at the beginning
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_6, 0);
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_7, 0);
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_8, 0);
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_9, 0);
    cy8c9520_pin_mode(neo_cy8c9520, CY8C9520_GPIO_6, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);
    cy8c9520_pin_mode(neo_cy8c9520, CY8C9520_GPIO_7, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);
    cy8c9520_pin_mode(neo_cy8c9520, CY8C9520_GPIO_8, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);
    cy8c9520_pin_mode(neo_cy8c9520, CY8C9520_GPIO_9, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);

    // RS485 RE and DE pins initialization
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_14, 1); // RE
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_15, 0); // DE
    cy8c9520_pin_mode(neo_cy8c9520, CY8C9520_GPIO_14, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_UP);
    cy8c9520_pin_mode(neo_cy8c9520, CY8C9520_GPIO_15, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);

    // cy8c9520_send_cmd(neo_cy8c9520, CY8C9520_STORE_POR_CFG_TO_EEPROM);

    // ADC analog inputs
    neo_mcp3564 = (mcp3564_t*)malloc(sizeof(mcp3564_t));
    pinMode(_MCP3564_CS_PIN, OUTPUT);
    mcp3564_cfg_t mcp3564_cfg;
    mcp3564_set_default_cfg(&mcp3564_cfg);
    mcp3564_init(neo_mcp3564, &mcp3564_cfg);

    // DAC analog output
    neo_ad5664 = (ad5664_t*)malloc(sizeof(ad5664_t));
    pinMode(_AD5664_CS_PIN, OUTPUT);
    ad5664_cfg_t ad5664_cfg;
    ad5664_set_default_cfg(&ad5664_cfg);
    ad5664_init(neo_ad5664, &ad5664_cfg);

    // Digital outputs controller
    neo_bts71220 = (bts71220_t*)malloc(sizeof(bts71220_t));
    bts71220_cfg_t bts71220_cfg;
    bts71220_set_default_cfg(&bts71220_cfg);
    bts71220_init(neo_bts71220, &bts71220_cfg);
}
 
/* SPI chip select management */
void mcp3564_cs_select(int cs_pin) {
    digitalWrite(_MCP3564_CS_PIN, LOW);
}
void mcp3564_cs_deselect(int cs_pin) {
    digitalWrite(_MCP3564_CS_PIN, HIGH);
}
 
void ad5664_cs_select(int cs_pin) {
    digitalWrite(_AD5664_CS_PIN, LOW);
}
void ad5664_cs_deselect(int cs_pin) {
    digitalWrite(_AD5664_CS_PIN, HIGH);
}
 
void bts71220_cs_select(int cs_pin) {
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_12, 0);
    delayMicroseconds(600);
}
void bts71220_cs_deselect(int cs_pin) {
    cy8c9520_write_pin(neo_cy8c9520, CY8C9520_GPIO_12, 1);
}
 
/* Pin definitions for ControllinoRp2040Pin API */
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI0 = new ControllinoRp2040Pin(MCP3564_CH_CH0, ControllinoRp2040Pin::MCP3564_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI1 = new ControllinoRp2040Pin(MCP3564_CH_CH1, ControllinoRp2040Pin::MCP3564_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI2 = new ControllinoRp2040Pin(MCP3564_CH_CH2, ControllinoRp2040Pin::MCP3564_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI3 = new ControllinoRp2040Pin(MCP3564_CH_CH3, ControllinoRp2040Pin::MCP3564_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI4 = new ControllinoRp2040Pin(MCP3564_CH_CH4, ControllinoRp2040Pin::MCP3564_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI5 = new ControllinoRp2040Pin(MCP3564_CH_CH5, ControllinoRp2040Pin::MCP3564_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI6 = new ControllinoRp2040Pin(MCP3564_CH_CH6, ControllinoRp2040Pin::MCP3564_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI7 = new ControllinoRp2040Pin(MCP3564_CH_CH7, ControllinoRp2040Pin::MCP3564_PIN);

ControllinoRp2040Pin* _CONTROLLINO_NEO_AO0 = new ControllinoRp2040Pin(AD5664_CH_ADDR_A, ControllinoRp2040Pin::AD5664_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AO1 = new ControllinoRp2040Pin(AD5664_CH_ADDR_B, ControllinoRp2040Pin::AD5664_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AO2 = new ControllinoRp2040Pin(AD5664_CH_ADDR_C, ControllinoRp2040Pin::AD5664_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AO3 = new ControllinoRp2040Pin(AD5664_CH_ADDR_D, ControllinoRp2040Pin::AD5664_PIN);

ControllinoRp2040Pin* _CONTROLLINO_NEO_DO4 = new ControllinoRp2040Pin(CY8C9520_GPIO_9, ControllinoRp2040Pin::CY8C9520_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DO5 = new ControllinoRp2040Pin(CY8C9520_GPIO_8, ControllinoRp2040Pin::CY8C9520_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DO6 = new ControllinoRp2040Pin(CY8C9520_GPIO_7, ControllinoRp2040Pin::CY8C9520_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DO7 = new ControllinoRp2040Pin(CY8C9520_GPIO_6, ControllinoRp2040Pin::CY8C9520_PIN);

ControllinoRp2040Pin* _CONTROLLINO_NEO_RE_PIN = new ControllinoRp2040Pin(CY8C9520_GPIO_14, ControllinoRp2040Pin::CY8C9520_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DE_PIN = new ControllinoRp2040Pin(CY8C9520_GPIO_15, ControllinoRp2040Pin::CY8C9520_PIN);
 
/* Returns ControllinoRp2040Pin API pin or nullptr */
ControllinoRp2040Pin* getControllinoRp2040Pin(int pin)
{
    switch (pin)
    {
    case CONTROLLINO_NEO_AI0: return _CONTROLLINO_NEO_AI0;
    case CONTROLLINO_NEO_AI1: return _CONTROLLINO_NEO_AI1;
    case CONTROLLINO_NEO_AI2: return _CONTROLLINO_NEO_AI2;
    case CONTROLLINO_NEO_AI3: return _CONTROLLINO_NEO_AI3;
    case CONTROLLINO_NEO_AI4: return _CONTROLLINO_NEO_AI4;
    case CONTROLLINO_NEO_AI5: return _CONTROLLINO_NEO_AI5;
    case CONTROLLINO_NEO_AI6: return _CONTROLLINO_NEO_AI6;
    case CONTROLLINO_NEO_AI7: return _CONTROLLINO_NEO_AI7;

    case CONTROLLINO_NEO_AO0: return _CONTROLLINO_NEO_AO0;
    case CONTROLLINO_NEO_AO1: return _CONTROLLINO_NEO_AO1;
    case CONTROLLINO_NEO_AO2: return _CONTROLLINO_NEO_AO2;
    case CONTROLLINO_NEO_AO3: return _CONTROLLINO_NEO_AO3;

    case CONTROLLINO_NEO_DO4: return _CONTROLLINO_NEO_DO4;
    case CONTROLLINO_NEO_DO5: return _CONTROLLINO_NEO_DO5;
    case CONTROLLINO_NEO_DO6: return _CONTROLLINO_NEO_DO6;
    case CONTROLLINO_NEO_DO7: return _CONTROLLINO_NEO_DO7;

    case RS485_DEFAULT_RE_PIN: return _CONTROLLINO_NEO_RE_PIN;
    case RS485_DEFAULT_DE_PIN: return _CONTROLLINO_NEO_DE_PIN;

    default: break;
    }
    return nullptr;
}