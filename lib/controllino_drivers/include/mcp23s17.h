/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
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
  * Driver librarry to handle mcp23s17 port mcp23s17er.
  * Based on MikroE Expand Click Driver
  *
  * \author Pedro Marquez \pmmarquez , CONTROLLINO Firmware Team
  */

#include <stdint.h>
#include <stddef.h>
 
/**
 * \brief Error codes
 * \ingroup mcp23s17
 */
typedef int mcp23s17_err_code_t;
#define MCP23S17_OK           0x00
#define MCP23S17_INIT_ERROR   0xFF
 
/**
 * \brief Operation codes
 * \ingroup mcp23s17
 */
#define MCP23S17_SPI_DEVICE_OPCODE                                  0x40
#define MCP23S17_OPCODE_WRITE                                       0xFE
#define MCP23S17_OPCODE_READ                                        0x01
 
/**
 * \brief Module positions on the SPI bus
 * \ingroup mcp23s17
 */
#define MCP23S17_SPI_MODULE_POSITION_0                              0x00
#define MCP23S17_SPI_MODULE_POSITION_1                              0x02
#define MCP23S17_SPI_MODULE_POSITION_2                              0x04
#define MCP23S17_SPI_MODULE_POSITION_3                              0x06
#define MCP23S17_SPI_MODULE_POSITION_4                              0x08
#define MCP23S17_SPI_MODULE_POSITION_5                              0x0A
#define MCP23S17_SPI_MODULE_POSITION_6                              0x0C
#define MCP23S17_SPI_MODULE_POSITION_7                              0x0E
 
/**
 * \brief Port direction 
 * \ingroup mcp23s17
 */
#define MCP23S17_PORT_DIRECTION_OUTPUT                              0x00
#define MCP23S17_PORT_DIRECTION_INPUT                               0xFF
 
/**
 * \brief bank1_register_configuration BANK 1 register configuration
 * \ingroup mcp23s17
 */
#define MCP23S17_IODIRA_BANK1                                       0x00
#define MCP23S17_IPOLA_BANK1                                        0x01
#define MCP23S17_GPINTENA_BANK1                                     0x02
#define MCP23S17_DEFVALA_BANK1                                      0x03
#define MCP23S17_INTCONA_BANK1                                      0x04
#define MCP23S17_IOCON_BANK1                                        0x05
#define MCP23S17_GPPUA_BANK1                                        0x06
#define MCP23S17_INTFA_BANK1                                        0x07
#define MCP23S17_INTCAPA_BANK1                                      0x08
#define MCP23S17_GPIOA_BANK1                                        0x09
#define MCP23S17_OLATA_BANK1                                        0x0A
#define MCP23S17_IODIRB_BANK1                                       0x10
#define MCP23S17_IPOLB_BANK1                                        0x11
#define MCP23S17_GPINTENB_BANK1                                     0x12
#define MCP23S17_DEFVALB_BANK1                                      0x13
#define MCP23S17_INTCONB_BANK1                                      0x14
#define MCP23S17_IOCONO_BANK1                                       0x15
#define MCP23S17_GPPUB_BANK1                                        0x16
#define MCP23S17_INTFB_BANK1                                        0x17
#define MCP23S17_INTCAPB_BANK1                                      0x18
#define MCP23S17_GPIOB_BANK1                                        0x19
#define MCP23S17_OLATB_BANK1                                        0x1A
 
/**
 * \brief bank0_register_configuration BANK 0 register configuration
 * \ingroup mcp23s17
 */
#define MCP23S17_IODIRA_BANK0                                       0x00
#define MCP23S17_IODIRB_BANK0                                       0x01
#define MCP23S17_IPOLA_BANK0                                        0x02
#define MCP23S17_IPOLB_BANK0                                        0x03
#define MCP23S17_GPINTENA_BANK0                                     0x04
#define MCP23S17_GPINTENB_BANK0                                     0x05
#define MCP23S17_DEFVALA_BANK0                                      0x06
#define MCP23S17_DEFVALB_BANK0                                      0x07
#define MCP23S17_INTCONA_BANK0                                      0x08
#define MCP23S17_INTCONB_BANK0                                      0x09
#define MCP23S17_IOCON_BANK0                                        0x0A
#define MCP23S17_GPPUA_BANK0                                        0x0C
#define MCP23S17_GPPUB_BANK0                                        0x0D
#define MCP23S17_INTFA_BANK0                                        0x0E
#define MCP23S17_INTFB_BANK0                                        0x0F
#define MCP23S17_INTCAPA_BANK0                                      0x10
#define MCP23S17_INTCAPB_BANK0                                      0x11
#define MCP23S17_GPIOA_BANK0                                        0x12
#define MCP23S17_GPIOB_BANK0                                        0x13
#define MCP23S17_OLATA_BANK0                                        0x14
#define MCP23S17_OLATB_BANK0                                        0x15
 
/**
 * \brief IOCON modes
 * \ingroup mcp23s17
 */
#define MCP23S17_IOCON_BYTE_MODE                                    0x20
#define MCP23S17_IOCON_HAEN                                         0x08

#define MCP23S17_CN4_PA0                                            0x01
#define MCP23S17_CN4_PA1                                            0x02
#define MCP23S17_CN4_PA2                                            0x04
#define MCP23S17_CN4_PA3                                            0x08
#define MCP23S17_CN4_PA4                                            0x10
#define MCP23S17_CN4_PA5                                            0x20
#define MCP23S17_CN4_PA6                                            0x40
#define MCP23S17_CN4_PA7                                            0x80

#define MCP23S17_CN5_PB0                                            0x01
#define MCP23S17_CN5_PB1                                            0x02
#define MCP23S17_CN5_PB2                                            0x04
#define MCP23S17_CN5_PB3                                            0x08
#define MCP23S17_CN5_PB4                                            0x10
#define MCP23S17_CN5_PB5                                            0x20
#define MCP23S17_CN5_PB6                                            0x40
#define MCP23S17_CN5_PB7                                            0x80

#define MCP23S17_CN_START_POSITION                                  0x01

#define MCP23S17_INT_ERR                                            0xFF

/**
 * \brief External hardware SPI interface
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
    int rst_pin;
    int int_pin;
    unsigned int spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
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
    unsigned int spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
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
 * \brief Read byte of data from register
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_amd Module command.
 * \param reg_addr Register address.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_read_byte(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t reg_addr);
 
/**
 * \brief Write byte of data to register
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param reg_addr Register address.
 * \param write_data Data to write to register.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_write_byte(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t reg_addr, uint8_t write_data);
 
/**
 * \brief Set default internal configuration to registers
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_default_internal_cfg(mcp23s17_t* dev, uint8_t mod_cmd);
 
/**
 * \brief Set register bits
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param reg_addr Register address.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_bits(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask);
 
/**
 * \brief Clear register bits
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param reg_addr Register address.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_clear_bits(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask);
 
/**
 * \brief Toggle register bits
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param reg_addr Register address.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_toggle_bits(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t reg_addr, uint8_t bit_mask);
 
/**
 * \brief Read one byte of data from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param read_data Pointer to receive data byte.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_read_byte_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t* read_data);
 
/**
 * \brief Read one byte of data from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param read_data Pointer to receive data byte.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_read_byte_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t* read_data);
 
/**
 * \brief Read the two byte of data from PORTA & PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param read_data Pointer to receive data.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_read_ports(mcp23s17_t* dev, uint8_t mod_cmd, uint16_t* read_data);
 
/**
 * \brief Write one byte of data to PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_write_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t write_data);
 
/**
 * \brief Clear bit from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_clear_bit_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Set bit from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_bit_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Toggle bit from PORTA
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_toggle_bit_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Write one byte of data to PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_write_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t write_data);
 
/**
 * \brief Clear bit from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_clear_bit_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Set bit from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_bit_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Toggle bit from PORTB
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bits mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_toggle_bit_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Set PORTA direction
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_direction_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t write_data);
 
/**
 * \brief Set pins from PORTA as input
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bit mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_input_dir_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
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
mcp23s17_err_code_t mcp23s17_set_output_dir_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Set PORTB direction
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param write_data Data to write.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_direction_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t write_data);

/**
 * \brief Set pins from PORTB as input
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bit mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_input_dir_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);

/**
 * \brief Set pins from PORTB as output
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param bit_mask Bit mask.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_output_dir_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t bit_mask);
 
/**
 * \brief Set pull-ups of PORTA pins
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param write_data Pull up value.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_pull_ups_port_a(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t write_data);
 
/**
 * \brief Set pull-ups of PORTB pins
 * \ingroup mcp23s17
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param mod_cmd Module command.
 * \param write_data Pull up value.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp23s17_err_code_t mcp23s17_set_pull_ups_port_b(mcp23s17_t* dev, uint8_t mod_cmd, uint8_t write_data);
 
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
 * \param mod_cmd Module command.
 * \param write_data Pull up value.
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 * \note delay is 11ms
 */
mcp23s17_err_code_t mcp23s17_reset(mcp23s17_t* dev);
 
/**
 * \brief Get state of interrupt pin
 *
 * \param dev Pointer to MCP23S17 driver struct
 * \param state Pointer to receive state of interrupt pin 
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
uint8_t mcp23s17_get_interrupt(mcp23s17_t *dev, uint8_t *state);
 
#ifdef __cplusplus
}
#endif

#endif  // MCP23S17_H