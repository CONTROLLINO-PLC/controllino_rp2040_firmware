/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MCP4461_H
#define MCP4461_H

/**
 * \file mcp4461.h
 * \ingroup drivers
 * \defgroup mcp4461
 *
 * Driver librarry to handle MCP4461 digital potentiometer.
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include <stdint.h>
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup mcp4461
 */
typedef int mcp4461_err_code_t;
 
/**
 * \brief Posible I2C Slave addresses based on A0 and A1 pins
 * \ingroup mcp4461
 */ 
#define MCP4461_DEV_ADDR_0      0x2C // A1 = 0, A0 = 0
#define MCP4461_DEV_ADDR_1      0x2D // A1 = 0, A0 = 1
#define MCP4461_DEV_ADDR_2      0x2E // A1 = 1, A0 = 0
#define MCP4461_DEV_ADDR_3      0x2F // A1 = 1, A0 = 1
 /**
 * \brief Register map
 * \ingroup mcp4461
 */
typedef enum
{
    MCP4461_REG_V_WIPER_0 =     0x00,
    MCP4461_REG_V_WIPER_1 =     0x01,
    MCP4461_REG_NV_WIPER_0 =    0x02,
    MCP4461_REG_NV_WIPER_1 =    0x03,
    MCP4461_REG_TCON_0 =        0x04,
    MCP4461_REG_STATUS =        0x05,
    MCP4461_REG_V_WIPER_2 =     0x06,
    MCP4461_REG_V_WIPER_3 =     0x07,
    MCP4461_REG_NV_WIPER_2 =    0x08,
    MCP4461_REG_NV_WIPER_3 =    0x09,
    MCP4461_REG_TCON_1 =        0x0A,
    MCP4461_REG_DATA_EEPROM_0 = 0x0B,
    MCP4461_REG_DATA_EEPROM_1 = 0x0C,
    MCP4461_REG_DATA_EEPROM_2 = 0x0D,
    MCP4461_REG_DATA_EEPROM_3 = 0x0E,
    MCP4461_REG_DATA_EEPROM_4 = 0x0F,
} mcp4461_reg_t;
 
/**
 * \brief Commands
 * \ingroup mcp4461
 */
typedef enum
{
    MCP4461_CMD_WRITE =         0b00,
    MCP4461_CMD_INCREMENT =     0b01,
    MCP4461_CMD_DECREMENT =     0b10,
    MCP4461_CMD_READ =          0b11,
} mcp4461_cmd_t;
 
/**
 * \brief Utility masks
 * \ingroup mcp4461
 */
#define MCP4461_MEM_ADDR_MASK   0b11110000
#define MCP4461_CMD_MASK        0b00001100
#define MCP4461_DATA_MASK       0b00000011

 /**
 * \brief Max value for wiper 8 bit potentiometer
 * \ingroup mcp4461
 */
#define MCP4461_MAX_VALUE       0x100
 
/**
 * \brief External hardware I2C interface
 */
typedef struct _hw_i2c_t* hw_i2c_t;
 
/**
 * \brief Initial config struct
 * \ingroup mcp4461
 */
typedef struct
{
    int sda_pin;
    int scl_pin;
    unsigned int i2c_speed;
    uint8_t i2c_addr;
    hw_i2c_t i2c;
} mcp4461_cfg_t;
 
/**
 * \brief MCP4461 device struct
 * \ingroup mcp4461
 */
typedef struct
{
    uint8_t i2c_addr;
    hw_i2c_t i2c;
} mcp4461_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup mcp4461
 *
 * \param cfg Initial config struct
 */
void mcp4461_set_default_cfg(mcp4461_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup mcp4461
 *
 * \param dev Pointer to mcp4461 device struct
 * \param cfg Initial config struct
 * \return PLATFORM_I2C_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_I2C_COM_ERR : error
 *         PLATFORM_OK : successful
 */
mcp4461_err_code_t mcp4461_init(mcp4461_t* dev, mcp4461_cfg_t* cfg);

/*
 *  Read and write operations on mcp4461 can be continuos
 *  but like they are more complex to implement and most of the time
 *  they are single operations, we will only implement single operations
 */

/*!
 * \brief Writes data to memory register
 * \ingroup mcp4461
 *
 * \param dev Pointer to mcp4461 device struct
 * \param reg Register address
 * \param txdata Data to send
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp4461_err_code_t mcp4461_write_reg(mcp4461_t* dev, mcp4461_reg_t reg, uint16_t txdata);
 
/*!
 * \brief Reads data from memory register
 * \ingroup mcp4461
 *
 * \param dev Pointer to mcp4461 device struct
 * \param reg Register address
 * \param rxdata Pointer to receive data
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp4461_err_code_t mcp4461_read_reg(mcp4461_t* dev, mcp4461_reg_t reg, uint16_t* rxdata);
 
#ifdef __cplusplus
}
#endif
 
#endif /* MCP4461_H */
