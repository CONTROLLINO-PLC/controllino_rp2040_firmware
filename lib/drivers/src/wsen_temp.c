/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "wsen_temp.h"
#include "string.h"
#include "hw_platform.h" /* External harware interface library */
 
/* Initializes default configuration */
void wsen_temp_set_default_cfg(wsen_temp_cfg_t* cfg)
{
    cfg->sda_pin = PLATFORM_I2C_SDA;
    cfg->scl_pin = PLATFORM_I2C_SCL;
    cfg->i2c_speed = PLATFORM_I2C_SPEED;
    cfg->i2c_addr = WSEN_TEMP_ADDRESS_SAO_GND;
    cfg->i2c = PLATFORM_I2C_HW;
    cfg->int_pin = WSEN_TEMP_INT;
    cfg->ctrl_reg.free_run = WSEN_TEMP_CTRL_FREE_RUN_EN;
    cfg->ctrl_reg.block_data_upd = WSEN_TEMP_CTRL_BLOCK_DATA_UPD_EN;
    cfg->ctrl_reg.out_rate = WSEN_TEMP_CTRL_ODR_50HZ;
}
 
/* Initializes hardware according to configuration */
wsen_temp_err_code_t wsen_temp_init(wsen_temp_t* dev, wsen_temp_cfg_t* cfg)
{
    // Init hardware I2C interface
    if (platform_i2c_init(cfg->i2c, cfg->i2c_speed, cfg->sda_pin, cfg->scl_pin) != PLATFORM_OK)
        return PLATFORM_I2C_INIT_ERR;
    // Init hardware reset and wsen_temp_err_code_t pins 
    if (platform_gpio_init(cfg->int_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    // Set values from cfg
    dev->i2c_addr = cfg->i2c_addr;
    dev->i2c = cfg->i2c;
    dev->int_pin = cfg->int_pin;
    // Check coms
    uint8_t id;
    wsen_temp_err_code_t ret = wsen_temp_get_id(dev, &id);
    if ((ret != PLATFORM_OK) || id != WSEN_TEMP_DEVICE_ID_VALUE)
        return PLATFORM_I2C_INIT_ERR;
    // Inital settings
    ret = wsen_temp_sw_rst(dev);
    if (ret != PLATFORM_OK)
        return ret;
    wsen_temp_ctrl_t ctrl_reg;
    ret = wsen_temp_get_ctrl(dev, &ctrl_reg);
    if (ret != PLATFORM_OK)
        return ret;
    ctrl_reg.free_run = cfg->ctrl_reg.free_run;
    ctrl_reg.block_data_upd = cfg->ctrl_reg.block_data_upd;
    ctrl_reg.out_rate = cfg->ctrl_reg.out_rate;
    return wsen_temp_set_ctrl(dev, &ctrl_reg);
}
 
/* Writes data to register */
wsen_temp_err_code_t wsen_temp_generic_write(wsen_temp_t* dev, wsen_temp_reg_t reg, uint8_t* txdata, uint8_t txlen)
{
    uint8_t tx_buf[txlen + 1];
    tx_buf[0] = reg;
    memcpy(&tx_buf[1], txdata, txlen);
    return platform_i2c_write(dev->i2c, dev->i2c_addr, tx_buf, sizeof(tx_buf));
}
 
/* Reads data from register */
wsen_temp_err_code_t wsen_temp_generic_read(wsen_temp_t* dev, wsen_temp_reg_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    if (platform_i2c_write(dev->i2c, dev->i2c_addr, (uint8_t*)&reg, 1) != PLATFORM_OK)
        return PLATFORM_I2C_COM_ERR;
    return platform_i2c_read(dev->i2c, dev->i2c_addr, rxdata, rxlen);
}
 
/* Read the device id */
wsen_temp_err_code_t wsen_temp_get_id(wsen_temp_t* dev, uint8_t* id)
{
    return wsen_temp_generic_read(dev, WSEN_TEMP_REG_DEVICE_ID, id, 1);
}
 
/* Software reset */
wsen_temp_err_code_t wsen_temp_sw_rst(wsen_temp_t* dev) {
    wsen_temp_reset_t rst_reg;
    wsen_temp_err_code_t ret;
    // Set 1
    ret = wsen_temp_generic_read(dev, WSEN_TEMP_REG_SOFT_RESET, (uint8_t*)&rst_reg, 1);
    if (ret != PLATFORM_OK)
        return ret;
    rst_reg.reset = 1;
    ret = wsen_temp_generic_write(dev, WSEN_TEMP_REG_SOFT_RESET, (uint8_t*)&rst_reg, 1);
    if (ret != PLATFORM_OK)
        return ret;
    // Set 0
    ret = wsen_temp_generic_read(dev, WSEN_TEMP_REG_SOFT_RESET, (uint8_t*)&rst_reg, 1);
    if (ret != PLATFORM_OK)
        return ret;
    rst_reg.reset = 0;
    return wsen_temp_generic_write(dev, WSEN_TEMP_REG_SOFT_RESET, (uint8_t*)&rst_reg, 1);
}
 
/* Set CONTROL register settings */
wsen_temp_err_code_t wsen_temp_set_ctrl(wsen_temp_t* dev, wsen_temp_ctrl_t* ctrl)
{
    return wsen_temp_generic_write(dev, WSEN_TEMP_REG_CTRL, (uint8_t*)ctrl, 1);
}
 
/* Get CONTROL register current state */
wsen_temp_err_code_t wsen_temp_get_ctrl(wsen_temp_t* dev, wsen_temp_ctrl_t* ctrl)
{
    return wsen_temp_generic_read(dev, WSEN_TEMP_REG_CTRL, (uint8_t*)ctrl, 1);
}
 
/* Get STATUS register current state */
wsen_temp_err_code_t wsen_temp_get_status(wsen_temp_t* dev, wsen_temp_status_t* status)
{
    return wsen_temp_generic_read(dev, WSEN_TEMP_REG_STATUS, (uint8_t*)status, 1);
}
 
/* Set temperature high limit for interrupt */
wsen_temp_err_code_t wsen_temp_set_high_lim(wsen_temp_t* dev, float celsius)
{
    if (celsius < -39.68F || celsius > 122.88F)
        return PLATFORM_ARGUMENT_ERR;
    uint8_t limit = (uint8_t)(celsius / 0.64F + 63);
    return wsen_temp_generic_write(dev, WSEN_TEMP_REG_HIGH_LIM, &limit, 1);
}
 
/* Get temperature high limit for interrupt */
wsen_temp_err_code_t wsen_temp_get_high_lim(wsen_temp_t* dev, float* celsius)
{
    uint8_t limit;
    wsen_temp_err_code_t ret = wsen_temp_generic_read(dev, WSEN_TEMP_REG_HIGH_LIM, &limit, 1);
    if (ret != PLATFORM_OK)
        return ret;
    *celsius = (limit - 63) * 0.64F;
    return PLATFORM_OK;
}
 
/* Set temperature low limit for interrupt */
wsen_temp_err_code_t wsen_temp_set_low_lim(wsen_temp_t* dev, float celsius)
{
    if (celsius < -39.68F || celsius > 122.88F)
        return PLATFORM_ARGUMENT_ERR;
    uint8_t limit = (uint8_t)(celsius / 0.64F + 63);
    return wsen_temp_generic_write(dev, WSEN_TEMP_REG_LOW_LIM, &limit, 1);
}
 
/* Get temperature low limit for interrupt */
wsen_temp_err_code_t wsen_temp_get_low_lim(wsen_temp_t* dev, float* celsius)
{
    uint8_t limit;
    wsen_temp_err_code_t ret = wsen_temp_generic_read(dev, WSEN_TEMP_REG_LOW_LIM, &limit, 1);
    if (ret != PLATFORM_OK)
        return ret;
    *celsius = ((float)limit - 63.0F) * 0.64F;
    return PLATFORM_OK;
}

/* Disable interrupt generation */
wsen_temp_err_code_t wsen_temp_dis_int(wsen_temp_t* dev)
{
    // Write 0 to both high and low limit registers to disable interrupt
    wsen_temp_err_code_t ret;
    uint8_t limit = 0; 
    ret = wsen_temp_generic_write(dev, WSEN_TEMP_REG_HIGH_LIM, &limit, 1);
    if (ret != PLATFORM_OK)
        return ret;
    return wsen_temp_generic_write(dev, WSEN_TEMP_REG_LOW_LIM, &limit, 1);
}

/* Get raw temperature digital value */
wsen_temp_err_code_t wsen_temp_get_raw(wsen_temp_t* dev, uint16_t* temp)
{
    uint8_t tmp[2];
    wsen_temp_err_code_t ret;
    ret = wsen_temp_generic_read(dev, WSEN_TEMP_REG_DATA_T_L, &tmp[0], 1);
    if (ret != PLATFORM_OK)
        return ret;
    ret = wsen_temp_generic_read(dev, WSEN_TEMP_REG_DATA_T_H, &tmp[1], 1);
    if (ret != PLATFORM_OK)
        return ret;
    *temp = (uint16_t)(tmp[1] << 8) | (uint16_t)tmp[0];
    return PLATFORM_OK;
}
 
/* Get temperature value in °C */
wsen_temp_err_code_t wsen_temp_get_celsius(wsen_temp_t* dev, float* temp)
{
    uint16_t raw_temp;
    wsen_temp_err_code_t ret = wsen_temp_get_raw(dev, &raw_temp);
    if (ret != PLATFORM_OK)
        return ret;
    *temp = (float)raw_temp * 0.01F;
    return PLATFORM_OK;
}