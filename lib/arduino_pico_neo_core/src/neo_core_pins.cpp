/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "neo_core_pin.h"
 
cy8c95xx_t _neo_cy8c95xx;
mcp356x_t _neo_mcp356x;
ad56x4_t _neo_ad56x4;
bts71220_t _neo_bts71220;
 
cy8c95xx_t* neo_cy8c95xx;
mcp356x_t* neo_mcp356x;
ad56x4_t* neo_ad56x4;
bts71220_t* neo_bts71220;
 
/* Init internal peripherals */
void initVariant()
{
    neo_cy8c95xx = (cy8c95xx_t*)malloc(sizeof(cy8c95xx_t));
    neo_mcp356x = (mcp356x_t*)malloc(sizeof(mcp356x_t));
    neo_ad56x4 = (ad56x4_t*)malloc(sizeof(ad56x4_t));
    neo_bts71220 = (bts71220_t*)malloc(sizeof(bts71220_t));

    // Port expander 
    cy8c95xx_cfg_t cy8c95xx_cfg;
    cy8c95xx_set_default_cfg(&cy8c95xx_cfg);
    cy8c95xx_cfg.int_pin = 15; // RP2040 GPIO 15
    cy8c95xx_init(neo_cy8c95xx, &cy8c95xx_cfg);

    // ADC analog inputs
    mcp356x_cfg_t mcp356x_cfg;
    mcp356x_set_default_cfg(&mcp356x_cfg);
    mcp356x_init(neo_mcp356x, &mcp356x_cfg);

    // Digital outputs controller
    bts71220_cfg_t bts71220_cfg;
    bts71220_set_default_cfg(&bts71220_cfg);
    bts71220_init(neo_bts71220, &bts71220_cfg);
}
 
#define NEO_AI_CS      CY8C95XX_GPIO_14
void mcp356x_cs_select(mcp356x_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_AI_CS, 0); }
void mcp356x_cs_deselect(mcp356x_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_AI_CS, 1); }
 
#define NEO_AO_CS      CY8C95XX_GPIO_15
void ad56x4_cs_select(ad56x4_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_AO_CS, 0); }
void ad56x4_cs_deselect(ad56x4_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_AO_CS, 1); }
 
#define NEO_DO_CS      CY8C95XX_GPIO_12
void bts71220_cs_select(bts71220_t* dev) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_DO_CS, 0); }
void bts71220_cs_deselect(bts71220_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_DO_CS, 1); }
 
ControllinoNeoPin  NEO_CORE_AI0(MCP356X_CH_CH0, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_CORE_AI1(MCP356X_CH_CH1, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_CORE_AI2(MCP356X_CH_CH2, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_CORE_AI3(MCP356X_CH_CH3, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_CORE_AI4(MCP356X_CH_CH4, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_CORE_AI5(MCP356X_CH_CH5, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_CORE_AI6(MCP356X_CH_CH6, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_CORE_AI9(MCP356X_CH_CH7, ControllinoNeoPin::MCP356X_PIN);

ControllinoNeoPin  NEO_CORE_AO0(AD56X4_CH_ADDR_A, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  NEO_CORE_AO1(AD56X4_CH_ADDR_B, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  NEO_CORE_AO2(AD56X4_CH_ADDR_C, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  NEO_CORE_AO3(AD56X4_CH_ADDR_D, ControllinoNeoPin::AD56X4_PIN);

ControllinoNeoPin  NEO_CORE_DI0(6, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_CORE_DI1(7, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_CORE_DI2(12, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_CORE_DI3(13, ControllinoNeoPin::NATIVE_PIN);

ControllinoNeoPin  NEO_CORE_DO0(14, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_CORE_DO1(22, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_CORE_DO2(23, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_CORE_DO3(24, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_CORE_DO4(CY8C95XX_GPIO_6, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  NEO_CORE_DO5(CY8C95XX_GPIO_7, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  NEO_CORE_DO6(CY8C95XX_GPIO_8, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  NEO_CORE_DO7(CY8C95XX_GPIO_9, ControllinoNeoPin::CY8C95XX_PIN);