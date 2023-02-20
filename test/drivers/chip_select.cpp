/**
 * \file chip_select.cpp
 *
 * Handle drivers chip select functions
 */
#include "chip_select.h"
#include "ad56x4.h"
#include "bts71220.h"
#include "cy8c95xx.h"
#include "mcp356x.h"

cy8c95xx_t cy8c95xx;

#ifdef AD56X4_CS 
#undef AD56X4_CS
#endif
#define AD56X4_CS           CY8C95XX_GPIO_15
 
#ifdef BTS71220_CS
#undef BTS71220_CS
#endif
#define BTS71220_CS          CY8C95XX_GPIO_12
 
void chip_select_init(void)
{
#ifdef ARDUINO_NEO_ENV
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    cy8c95xx_init(&cy8c95xx, &cfg);
    cy8c95xx_reset(&cy8c95xx);
    cy8c95xx_pin_mode(&cy8c95xx, AD56X4_CS, CY8C95XX_GPIO_OUT, CY8C95XX_DRV_PULL_UP);
    cy8c95xx_pin_mode(&cy8c95xx, BTS71220_CS, CY8C95XX_GPIO_OUT, CY8C95XX_DRV_PULL_UP);
#endif
}

void ad56x4_cs_select(ad56x4_t* dev)
{
#ifdef ARDUINO_NEO_ENV
    cy8c95xx_write_pin(&cy8c95xx, AD56X4_CS, CY8C95XX_LOW);
#endif
}

void ad56x4_cs_deselect(ad56x4_t* dev)
{
#ifdef ARDUINO_NEO_ENV
    cy8c95xx_write_pin(&cy8c95xx, AD56X4_CS, CY8C95XX_HIGH);
#endif
}

void bts71220_cs_select(bts71220_t * dev) {
#ifdef ARDUINO_NEO_ENV
    cy8c95xx_write_pin(&cy8c95xx, BTS71220_CS, CY8C95XX_LOW);
#endif
}

void bts71220_cs_deselect(bts71220_t * dev) {
#ifdef ARDUINO_NEO_ENV
    cy8c95xx_write_pin(&cy8c95xx, BTS71220_CS, CY8C95XX_HIGH);
#endif
}

