/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "drivers/cy8C95xx.h"

/*
 * Initializes default configuration
 *
 * i2c:hw_i2c_t sda:4 scl:5  i2c_speed:100000 i2c_address:CY8C95XX_DEV_ADR_GND rst:-1 int_pin:15
 */
void cy8C95xx_set_default_cfg(cy8C95xx_cfg_t* cfg)
{
    cfg->i2c = (hw_i2c_t*)i2c0;
    cfg->i2c_speed = 100000;
    cfg->i2c_addr = CY8C95XX_DEV_ADR_GND;
    cfg->sda_pin = 4;
    cfg->scl_pin = 5;
    cfg->rst_pin = -1;
    cfg->int_pin = 15;
}

/* Init hardware according to configuration */
int cy8C95xx_hw_init(cy8C95xx_cfg_t* cfg)
{
    // Check config
    if ((cfg->i2c != (hw_i2c_t*)i2c0 && cfg->i2c != (hw_i2c_t*)i2c1) || !cfg->scl_pin || !cfg->sda_pin)
        return CY8C95XX_INIT_ERROR;

    // Init i2c pins
    gpio_set_function(cfg->sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(cfg->scl_pin, GPIO_FUNC_I2C);
    // gpio_pull_up(cfg->sda_pin);
    // gpio_pull_up(cfg->scl_pin);

    // Init i2c
    i2c_init((i2c_inst_t*)cfg->i2c, cfg->i2c_speed);

    // Init reset pin 
    if (cfg->rst_pin >= 0) {
        gpio_init(cfg->rst_pin);
        gpio_set_dir(cfg->rst_pin, GPIO_OUT);
    }

    // Init int pin
    if (cfg->int_pin >= 0) {
        gpio_init(cfg->int_pin);
        gpio_set_dir(cfg->int_pin, GPIO_IN);
    }

    return CY8C95XX_OK;
}

/* Reset port expander using rst_pin */
void cy8C95xx_reset(cy8C95xx_t* exp)
{
    if (exp->rst_pin >= 0) {
        gpio_put(exp->rst_pin, 1);
        sleep_ms(1000);
        gpio_put(exp->rst_pin, 0);
        sleep_ms(1000);
    }
}

/* Check interrupt by reading int_pin level */
uint8_t cy8C95xx_check_int(cy8C95xx_t* exp)
{
    if (exp->int_pin >= 0) {
        return gpio_get(exp->int_pin);
    }
    return 0;
}

/* Attempt to read specified number of bytes from address over i2c */
int cy8C95xx_i2c_read(hw_i2c_t* i2c, uint8_t addr, uint8_t* rxdata, size_t len)
{
    if (i2c_read_blocking((i2c_inst_t*)i2c, addr, rxdata, len, false) != len)
        return CY8C95XX_I2C_ERROR;
    
    return CY8C95XX_OK;
}

/* Attempt to write specified number of bytes to address over i2c */
int cy8C95xx_i2c_write(hw_i2c_t* i2c, uint8_t addr, const uint8_t* txdata, size_t len)
{
    if (i2c_write_blocking((i2c_inst_t*)i2c, addr, txdata, len, false) != len)
        return CY8C95XX_I2C_ERROR;

    return CY8C95XX_OK;
}