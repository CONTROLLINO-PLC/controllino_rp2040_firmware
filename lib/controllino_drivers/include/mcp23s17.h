/*
 * Copyright (c) 2024 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef MCP23S17_H
#define MCP23S17_H

 /**
  * \file mcp23s17.h
  * \ingroup drivers
  * \defgroup mcp23s17
  *
  * Driver library to handle mcp23s17 port expander.
  * Based on MikroE Expand Click Driver
  *
  * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
  */

#include <stdint.h>
#include <stddef.h>
 
/**
 * \brief Error codes
 * \ingroup mcp23s17
 */
typedef int mcp23s17_err_code_t;
 
/**
 * \brief MCP23S17 addresses
 * \ingroup mcp23s17
 */
typedef enum {
    MCP23S17_ADDRESS_0 =                0x40,
    MCP23S17_ADDRESS_1 =                0x42,
    MCP23S17_ADDRESS_2 =                0x44,
    MCP23S17_ADDRESS_3 =                0x46,
    MCP23S17_ADDRESS_4 =                0x48,
    MCP23S17_ADDRESS_5 =                0x4A,
    MCP23S17_ADDRESS_6 =                0x4C,
    MCP23S17_ADDRESS_7 =                0x4E
} mcp23s17_addr_t;

/**
 * \brief Operation codes
 * \ingroup mcp23s17
 */
typedef enum {
    MCP23S17_CMD_WRITE =                0x00,
    MCP23S17_CMD_READ =                 0x01
} mcp23s17_rw_cmd_t;
 
/**
 * \brief Port direction 
 * \ingroup mcp23s17
 */
#define MCP23S17_PORT_DIRECTION_OUTPUT  0x00
#define MCP23S17_PORT_DIRECTION_INPUT   0xFF
 
/**
 * \brief Register addresses
 * \ingroup mcp23s17
 */
typedef enum {
    MCP23S17_IODIRA_BANK0 =             0x00,
    MCP23S17_IODIRB_BANK0 =             0x01,
    MCP23S17_IPOLA_BANK0 =              0x02,
    MCP23S17_IPOLB_BANK0 =              0x03,
    MCP23S17_GPINTENA_BANK0 =           0x04,
    MCP23S17_GPINTENB_BANK0 =           0x05,
    MCP23S17_DEFVALA_BANK0 =            0x06,
    MCP23S17_DEFVALB_BANK0 =            0x07,
    MCP23S17_INTCONA_BANK0 =            0x08,
    MCP23S17_INTCONB_BANK0 =            0x09,
    MCP23S17_IOCON_BANK0 =              0x0A,
    MCP23S17_GPPUA_BANK0 =              0x0C,
    MCP23S17_GPPUB_BANK0 =              0x0D,
    MCP23S17_INTFA_BANK0 =              0x0E,
    MCP23S17_INTFB_BANK0 =              0x0F,
    MCP23S17_INTCAPA_BANK0 =            0x10,
    MCP23S17_INTCAPB_BANK0 =            0x11,
    MCP23S17_GPIOA_BANK0 =              0x12,
    MCP23S17_GPIOB_BANK0 =              0x13,
    MCP23S17_OLATA_BANK0 =              0x14,
    MCP23S17_OLATB_BANK0 =              0x15,
} mcp23s17_regs_t;

/**
 * \brief IOCON modes
 * \ingroup mcp23s17
 */
#define MCP23S17_IOCON_BYTE_MODE        0x20
#define MCP23S17_IOCON_HAEN             0x08

#define MCP23S17_CN4_PA0                0x01
#define MCP23S17_CN4_PA1                0x02
#define MCP23S17_CN4_PA2                0x04
#define MCP23S17_CN4_PA3                0x08
#define MCP23S17_CN4_PA4                0x10
#define MCP23S17_CN4_PA5                0x20
#define MCP23S17_CN4_PA6                0x40
#define MCP23S17_CN4_PA7                0x80

#define MCP23S17_CN5_PB0                0x01
#define MCP23S17_CN5_PB1                0x02
#define MCP23S17_CN5_PB2                0x04
#define MCP23S17_CN5_PB3                0x08
#define MCP23S17_CN5_PB4                0x10
#define MCP23S17_CN5_PB5                0x20
#define MCP23S17_CN5_PB6                0x40
#define MCP23S17_CN5_PB7                0x80

#define MCP23S17_CN_START_POSITION      0x01
#define MCP23S17_INT_ERR                0xFF

/**
 * \brief External pins
 * \ingroup mcp23s17
 */
#ifndef MCP23S17_RST
#define MCP23S17_RST                    -1
#endif
#ifndef MCP23S17_INT
#define MCP23S17_INT                    -1
#endif
#ifndef MCP23S17_CS
#define MCP23S17_CS                     -1
#endif
 
/**
 * \brief External hardware SPI interface
 * \ingroup mcp23s17
 */
typedef struct _hw_spi_t* hw_spi_t;
 
/**
 * \brief Initial config struct
 * \ingroup mcp23s17
 */
typedef struct
{
    int mosi_pin;
    int miso_pin;
    int sck_pin;
    int cs_pin; 
    int rst_pin;            // reset pin
    int int_pin;            // interrupt pin
    mcp23s17_addr_t addr;   // device address
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    unsigned int spi_speed;
    hw_spi_t spi;
} mcp23s17_cfg_t;
 
/**
 * \brief Port mcp23s17er struct
 * \ingroup mcp23s17
 */
typedef struct
{
    int cs_pin;
    int rst_pin;
    int int_pin;
    mcp23s17_addr_t addr;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    unsigned int spi_speed;
    hw_spi_t spi;
} mcp23s17_t;
 
#ifdef __cplusplus
extern "C" {
#endif
 
/*!
 * \brief Initializes default configuration
 * \ingroup mcp23s17
 *
 * \param cfg Initial config struct
 */
void mcp23s17_set_default_cfg(mcp23s17_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param cfg Initial config struct
 * \return PLATFORM_SPI_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_SPI_COM_ERR : error
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_init(mcp23s17_t* dev, mcp23s17_cfg_t* cfg);
 
/**
 * \brief Read or write a byte of data from or to register
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param reg Register address.
 * \param rw_cmd Read or write command.
 * \param tx_data Pointer to transmit data byte.
 * \param rx_data Pointer to receive data byte.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_generic_transfer(
    mcp23s17_t* dev,
    mcp23s17_regs_t reg,
    mcp23s17_rw_cmd_t rw_cmd,
    uint8_t tx_data,
    uint8_t* rx_data
);
 
/**
 * \brief Set register bits
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param reg Register address.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_bits(mcp23s17_t* dev, mcp23s17_regs_t reg, uint8_t bit_mask);
 
/**
 * \brief Clear register bits
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param reg Register address.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_clear_bits(mcp23s17_t* dev, mcp23s17_regs_t reg, uint8_t bit_mask);
 
/**
 * \brief Toggle register bits
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param reg Register address.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_toggle_bits(mcp23s17_t* dev, mcp23s17_regs_t reg, uint8_t bit_mask);
 
/**
 * \brief Read data from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param data Pointer to receive data byte.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_read_port_a(mcp23s17_t* dev, uint8_t* data);
 
/**
 * \brief Read data from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param data Pointer to receive data byte.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_read_port_b(mcp23s17_t* dev, uint8_t* data);
 
/**
 * \brief Read data from PORTA-PORTB and merge into one 16bit value
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param data Pointer to receive data.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 * \note PORTB is the MSB and PORTA is the LSB
 */
mcp23s17_err_code_t mcp23s17_read_ports(mcp23s17_t* dev, uint16_t* data);
 
/**
 * \brief Write one byte of data to PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_write_port_a(mcp23s17_t* dev, uint8_t write_data);
 
/**
 * \brief Clear bit from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_clear_bit_port_a(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Set bit from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_bit_port_a(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Toggle bit from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_toggle_bit_port_a(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Write one byte of data to PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_write_port_b(mcp23s17_t* dev, uint8_t write_data);
 
/**
 * \brief Clear bit from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_clear_bit_port_b(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Set bit from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_bit_port_b(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Toggle bit from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_toggle_bit_port_b(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Set PORTA direction
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_direction_port_a(mcp23s17_t* dev, uint8_t write_data);
 
/**
 * \brief Set pins from PORTA as input
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bit mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_input_dir_port_a(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Set pins from PORTA as output
 * \ingroup mcp23s17
 *
 * \param dev          Pointer to MCP23S17 driver struct
 * \param mod_cmd      Module command.
 * \param bit_mask     Bit mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_output_dir_port_a(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Set PORTB direction
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_direction_port_b(mcp23s17_t* dev, uint8_t write_data);

/**
 * \brief Set pins from PORTB as input
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bit mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_input_dir_port_b(mcp23s17_t* dev, uint8_t bit_mask);

/**
 * \brief Set pins from PORTB as output
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param bit_mask Bit mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_output_dir_port_b(mcp23s17_t* dev, uint8_t bit_mask);
 
/**
 * \brief Set pull-ups of PORTA pins
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param write_data Pull up value.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_pull_ups_port_a(mcp23s17_t* dev, uint8_t write_data);
 
/**
 * \brief Set pull-ups of PORTB pins
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param write_data Pull up value.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_pull_ups_port_b(mcp23s17_t* dev, uint8_t write_data);
 
/**
 * \brief Active pin by position on PORTA, from PA0 to PA7
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param position Pin position.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_potr_a(mcp23s17_t* dev, uint8_t position);
 
/**
 * \brief Active pin by position on PORTB, from PB0 to PB7
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param position Pin position.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_potr_b(mcp23s17_t* dev, uint8_t position);
 
/**
 * \brief Reset
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \note delay is 11ms
 */
void mcp23s17_reset(mcp23s17_t* dev);
 
/**
 * \brief Get state of interrupt pin
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param state Pointer to receive state of interrupt pin 
 */
void mcp23s17_get_interrupt(mcp23s17_t* dev, uint8_t* state);
 
/*!
 * \brief Enable CS for start SPI coms
 * \ingroup mcp23s17
 *
 * \param cs_pin Chip select pin
 * \note Should be implemented externally
 */
void mcp23s17_cs_select(int cs_pin);
 
/*!
 * \brief Disable CS after SPI coms
 * \ingroup mcp23s17
 *
 * \param cs_pin Chip select pin
 * \note Should be implemented externally
 */
void mcp23s17_cs_deselect(int cs_pin);
 
#ifdef __cplusplus
}
#endif

#endif  // MCP23S17_H