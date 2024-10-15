/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "mcp4461.h"
#include "hw_platform.h" /* External harware interface library */
 
/* Initializes default configuration */
void mcp4461_set_default_cfg(mcp4461_cfg_t* cfg)
{
    cfg->sda_pin = PLATFORM_I2C_SDA;
    cfg->scl_pin = PLATFORM_I2C_SCL;
    cfg->i2c_speed = PLATFORM_I2C_SPEED;
    cfg->i2c_addr = MCP4461_DEV_ADDR_0;
    cfg->i2c = PLATFORM_I2C_HW;
}
 
/* Initializes hardware according to configuration */
mcp4461_err_code_t mcp4461_init(mcp4461_t* dev, mcp4461_cfg_t* cfg)
{
    // Init hardware I2C interface
    if (platform_i2c_init(cfg->i2c, cfg->i2c_speed, cfg->sda_pin, cfg->scl_pin) != PLATFORM_OK)
        return PLATFORM_I2C_INIT_ERR;
    // Set values from cfg
    dev->i2c_addr = cfg->i2c_addr;
    dev->i2c = cfg->i2c;
    // Check coms and set channel selection off 
    return PLATFORM_OK;
}

/* Writes data to memory register */
mcp4461_err_code_t mcp4461_write_reg(mcp4461_t* dev, mcp4461_reg_t reg, uint16_t txdata)
{
    if ((reg == MCP4461_REG_V_WIPER_0 ||
        reg == MCP4461_REG_V_WIPER_1 ||
        reg == MCP4461_REG_NV_WIPER_0 ||
        reg == MCP4461_REG_NV_WIPER_1 ||
        reg == MCP4461_REG_V_WIPER_2 ||
        reg == MCP4461_REG_V_WIPER_3 ||
        reg == MCP4461_REG_NV_WIPER_2 ||
        reg == MCP4461_REG_NV_WIPER_3) &&
        txdata > MCP4461_MAX_VALUE)
    {
        return PLATFORM_ARGUMENT_ERR; // Value out of range
    }
    uint8_t tx_buf[2];
    txdata = txdata & 0x1FF; // Mask value to 9 bits
    tx_buf[0] = ((reg << 4) & MCP4461_MEM_ADDR_MASK) | ((MCP4461_CMD_WRITE << 2) & MCP4461_CMD_MASK) | ((txdata >> 8) & MCP4461_DATA_MASK);
    tx_buf[1] = txdata & 0xFF;
    return platform_i2c_write(dev->i2c, dev->i2c_addr, tx_buf, 2);
}

/* Reads data from memory register */
mcp4461_err_code_t mcp4461_read_reg(mcp4461_t* dev, mcp4461_reg_t reg, uint16_t* rxdata)
{
    uint8_t tx_data = ((reg << 4) & MCP4461_MEM_ADDR_MASK) | ((MCP4461_CMD_READ << 2) & MCP4461_CMD_MASK);
    uint8_t rx_buf[2];
    if (platform_i2c_write(dev->i2c, dev->i2c_addr, &tx_data, 1) != PLATFORM_OK)
        return PLATFORM_I2C_COM_ERR;
    if (platform_i2c_read(dev->i2c, dev->i2c_addr, rx_buf, 2) != PLATFORM_OK)
        return PLATFORM_I2C_COM_ERR;
    *rxdata = ((uint16_t)rx_buf[0] << 8) | rx_buf[1];
    return PLATFORM_OK;
}