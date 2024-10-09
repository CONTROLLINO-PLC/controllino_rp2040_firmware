/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "adg728.h"
#include "hw_platform.h" /* External harware interface library */
 
/* Initializes default configuration */
void adg728_set_default_cfg(adg728_cfg_t* cfg)
{
    cfg->sda_pin = PLATFORM_I2C_SDA;
    cfg->scl_pin = PLATFORM_I2C_SCL;
    cfg->i2c_speed = PLATFORM_I2C_SPEED;
    cfg->i2c_addr = ADG728_DEV_ADDR_0;
    cfg->i2c = PLATFORM_I2C_HW;
}
 
/* Initializes hardware according to configuration */
adg728_err_code_t adg728_init(adg728_t* dev, adg728_cfg_t* cfg)
{
    // Init hardware I2C interface
    if (platform_i2c_init(cfg->i2c, cfg->i2c_speed, cfg->sda_pin, cfg->scl_pin) != PLATFORM_OK)
        return PLATFORM_I2C_INIT_ERR;
    // Set values from cfg
    dev->i2c_addr = cfg->i2c_addr;
    dev->i2c = cfg->i2c;
    // Check coms and set channel selection off 
    return adg728_set_channel(dev, ADG728_CHANNEL_OFF);
}
 
/* Sets channel to be selected */
adg728_err_code_t adg728_set_channel(adg728_t* dev, adg728_channel_t ch)
{
    return platform_i2c_write(dev->i2c, dev->i2c_addr, (uint8_t*)&ch, 1);
}
 
/* Gets selected channel */
adg728_err_code_t adg728_get_channel(adg728_t* dev, adg728_channel_t* ch)
{
    return platform_i2c_read(dev->i2c, dev->i2c_addr, (uint8_t*)ch, 1);
}