/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "controllino_driver.h"

/* Peripherals interfaces */
cy8c95xx_t* neo_cy8c95xx;
mcp356x_t* neo_mcp356x;
ad56x4_t* neo_ad56x4;
bts71220_t* neo_bts71220;
wsen_temp_t* neo_wsen_temp;
 
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
    neo_cy8c95xx = (cy8c95xx_t*)malloc(sizeof(cy8c95xx_t));
    cy8c95xx_cfg_t cy8c95xx_cfg;
    cy8c95xx_set_default_cfg(&cy8c95xx_cfg);
    cy8c95xx_init(neo_cy8c95xx, &cy8c95xx_cfg);

    // Digital output pins to low level at the beginning
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_6, 0);
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_7, 0);
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_8, 0);
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_9, 0);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_6, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_7, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_8, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_9, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);

    // RS485 RE and DE pins initialization
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_14, 1); // RE
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_15, 0); // DE
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_14, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_UP);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_15, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);

    // cy8c95xx_send_cmd(neo_cy8c95xx, CY8C95XX_STORE_POR_CFG_TO_EEPROM);

    // ADC analog inputs
    neo_mcp356x = (mcp356x_t*)malloc(sizeof(mcp356x_t));
    pinMode(_MCP356X_CS_PIN, OUTPUT);
    mcp356x_cfg_t mcp356x_cfg;
    mcp356x_set_default_cfg(&mcp356x_cfg);
    mcp356x_init(neo_mcp356x, &mcp356x_cfg);

    // DAC analog output
    neo_ad56x4 = (ad56x4_t*)malloc(sizeof(ad56x4_t));
    pinMode(_AD56X4_CS_PIN, OUTPUT);
    ad56x4_cfg_t ad56x4_cfg;
    ad56x4_set_default_cfg(&ad56x4_cfg);
    ad56x4_init(neo_ad56x4, &ad56x4_cfg);

    // Digital outputs controller
    neo_bts71220 = (bts71220_t*)malloc(sizeof(bts71220_t));
    bts71220_cfg_t bts71220_cfg;
    bts71220_set_default_cfg(&bts71220_cfg);
    bts71220_init(neo_bts71220, &bts71220_cfg);
}
 
/* SPI chip select management */
void mcp356x_cs_select(int cs_pin) {
    digitalWrite(_MCP356X_CS_PIN, LOW);
}
void mcp356x_cs_deselect(int cs_pin) {
    digitalWrite(_MCP356X_CS_PIN, HIGH);
}
 
void ad56x4_cs_select(int cs_pin) {
    digitalWrite(_AD56X4_CS_PIN, LOW);
}
void ad56x4_cs_deselect(int cs_pin) {
    digitalWrite(_AD56X4_CS_PIN, HIGH);
}
 
void bts71220_cs_select(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_12, 0);
    delayMicroseconds(600);
}
void bts71220_cs_deselect(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_12, 1);
}
 
/* Pin definitions for ControllinoRp2040Pin API */
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI0 = new ControllinoRp2040Pin(MCP356X_CH_CH0, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI1 = new ControllinoRp2040Pin(MCP356X_CH_CH1, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI2 = new ControllinoRp2040Pin(MCP356X_CH_CH2, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI3 = new ControllinoRp2040Pin(MCP356X_CH_CH3, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI4 = new ControllinoRp2040Pin(MCP356X_CH_CH4, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI5 = new ControllinoRp2040Pin(MCP356X_CH_CH5, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI6 = new ControllinoRp2040Pin(MCP356X_CH_CH6, ControllinoRp2040Pin::MCP356X_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AI7 = new ControllinoRp2040Pin(MCP356X_CH_CH7, ControllinoRp2040Pin::MCP356X_PIN);

ControllinoRp2040Pin* _CONTROLLINO_NEO_AO0 = new ControllinoRp2040Pin(AD56X4_CH_ADDR_A, ControllinoRp2040Pin::AD56X4_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AO1 = new ControllinoRp2040Pin(AD56X4_CH_ADDR_B, ControllinoRp2040Pin::AD56X4_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AO2 = new ControllinoRp2040Pin(AD56X4_CH_ADDR_C, ControllinoRp2040Pin::AD56X4_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_AO3 = new ControllinoRp2040Pin(AD56X4_CH_ADDR_D, ControllinoRp2040Pin::AD56X4_PIN);

ControllinoRp2040Pin* _CONTROLLINO_NEO_DO4 = new ControllinoRp2040Pin(CY8C95XX_GPIO_9, ControllinoRp2040Pin::CY8C95XX_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DO5 = new ControllinoRp2040Pin(CY8C95XX_GPIO_8, ControllinoRp2040Pin::CY8C95XX_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DO6 = new ControllinoRp2040Pin(CY8C95XX_GPIO_7, ControllinoRp2040Pin::CY8C95XX_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DO7 = new ControllinoRp2040Pin(CY8C95XX_GPIO_6, ControllinoRp2040Pin::CY8C95XX_PIN);

ControllinoRp2040Pin* _CONTROLLINO_NEO_RE_PIN = new ControllinoRp2040Pin(CY8C95XX_GPIO_14, ControllinoRp2040Pin::CY8C95XX_PIN);
ControllinoRp2040Pin* _CONTROLLINO_NEO_DE_PIN = new ControllinoRp2040Pin(CY8C95XX_GPIO_15, ControllinoRp2040Pin::CY8C95XX_PIN);
 
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