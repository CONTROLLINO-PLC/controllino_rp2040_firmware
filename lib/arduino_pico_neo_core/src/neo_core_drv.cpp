/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "neo_core_pin.h"
 
cy8c95xx_t* neo_cy8c95xx;
mcp356x_t* neo_mcp356x;
ad56x4_t* neo_ad56x4;
bts71220_t* neo_bts71220;
 
#define NEO_AI_CS      CY8C95XX_GPIO_14
void mcp356x_cs_select(mcp356x_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_AI_CS, 0); }
void mcp356x_cs_deselect(mcp356x_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_AI_CS, 1); }

#define NEO_AO_CS      CY8C95XX_GPIO_15
void ad56x4_cs_select(ad56x4_t* dac) {
    cy8c95xx_write_pin(neo_cy8c95xx, NEO_AO_CS, 0);
}
void ad56x4_cs_deselect(ad56x4_t* dac) {
    cy8c95xx_write_pin(neo_cy8c95xx, NEO_AO_CS, 1);
}

#define NEO_DO_CS      CY8C95XX_GPIO_12
void bts71220_cs_select(bts71220_t* dev) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_DO_CS, 0); }
void bts71220_cs_deselect(bts71220_t* dac) { cy8c95xx_write_pin(neo_cy8c95xx, NEO_DO_CS, 1); }
 
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

    // Digital output pins to low level at the beginning
    // cy8c95xx_send_cmd(neo_cy8c95xx, CY8C95XX_RESTORE_DEFAULTS);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_6, CY8C95XX_GPIO_IN, CY8C95XX_DRV_HIGH_Z);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_7, CY8C95XX_GPIO_IN, CY8C95XX_DRV_HIGH_Z);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_8, CY8C95XX_GPIO_IN, CY8C95XX_DRV_HIGH_Z);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_9, CY8C95XX_GPIO_IN, CY8C95XX_DRV_HIGH_Z);
    // cy8c95xx_send_cmd(neo_cy8c95xx, CY8C95XX_STORE_POR_CFG_TO_EEPROM);

    // ADC analog inputs
    mcp356x_cfg_t mcp356x_cfg;
    mcp356x_set_default_cfg(&mcp356x_cfg);
    mcp356x_init(neo_mcp356x, &mcp356x_cfg);

    // DAC analog output
    ad56x4_cfg_t ad56x4_cfg;
    ad56x4_set_default_cfg(&ad56x4_cfg);
    ad56x4_init(neo_ad56x4, &ad56x4_cfg);

    // Digital outputs controller
    bts71220_cfg_t bts71220_cfg;
    bts71220_set_default_cfg(&bts71220_cfg);
    bts71220_init(neo_bts71220, &bts71220_cfg);
}