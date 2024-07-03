/*
 * Copyright (c) 2024 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "string.h"
#include "mcp23s17.h"
#include "hw_platform.h"
 
#define NULL_TX 0x00
#define NULL_RX NULL
static mcp23s17_err_code_t ret;
 
/* Initializes default configuration */
void mcp23s17_set_default_cfg(mcp23s17_cfg_t* cfg)
{
    cfg->mosi_pin =         PLATFORM_SPI_MOSI;
    cfg->miso_pin =         PLATFORM_SPI_MISO;
    cfg->sck_pin =          PLATFORM_SPI_SCK;
    cfg->cs_pin =           MCP23S17_CS;
    cfg->spi_speed =        PLATFORM_SPI_SPEED;
    cfg->spi_mode =         PLATFORM_SPI_MODE_1;
    cfg->spi_bit_order =    PLATFORM_SPI_MSBFIRST;
    cfg->spi =              PLATFORM_SPI_HW;
    cfg->rst_pin =          MCP23S17_RST;
    cfg->int_pin = MCP23S17_INT;
    cfg->addr = MCP23S17_ADDRESS_0;
}
 
/* Initializes hardware according to configuration */
mcp23s17_err_code_t mcp23s17_init(mcp23s17_t* dev, mcp23s17_cfg_t* cfg)
{
    // Init hardware SPI interface
    if (platform_spi_init(cfg->spi, cfg->spi_speed, cfg->mosi_pin, cfg->miso_pin, cfg->sck_pin) != PLATFORM_OK)
        return PLATFORM_SPI_INIT_ERR;
    // Init hardware pins
    if (platform_gpio_init(cfg->cs_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    if (platform_gpio_init(cfg->rst_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    if (platform_gpio_init(cfg->int_pin, PLATFORM_GPIO_IN, PLATFORM_GPIO_PULL_UP) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    // Set values from cfg
    dev->rst_pin = cfg->rst_pin;
    dev->cs_pin = cfg->cs_pin;
    dev->spi_speed = cfg->spi_speed;
    dev->spi_mode = cfg->spi_mode;
    dev->spi_bit_order = cfg->spi_bit_order;
    dev->spi = cfg->spi;
    dev->addr = cfg->addr;
    mcp23s17_cs_deselect(dev->cs_pin);
    // Reset device
    mcp23s17_reset(dev);
    // Set default internal configuration and test connection
    ret = mcp23s17_generic_transfer(
        dev,
        MCP23S17_IOCON_BANK0,
        MCP23S17_CMD_WRITE,
        MCP23S17_IOCON_BYTE_MODE | MCP23S17_IOCON_HAEN,
        NULL);
    if (ret != PLATFORM_OK)
        return ret;
    return PLATFORM_OK;
}
 
/* Read or write a byte of data from or to register */
mcp23s17_err_code_t mcp23s17_generic_transfer(
    mcp23s17_t* dev,
    mcp23s17_regs_t reg,
    mcp23s17_rw_cmd_t rw_cmd,
    uint8_t tx_data,
    uint8_t* rx_data)
{
    uint8_t tx_buf[3];
    uint8_t rx_buf[3];
    // Set address, register, read/write command and data
    memset(tx_buf, 0x00, sizeof(tx_buf));
    tx_buf[0] = dev->addr | rw_cmd;
    tx_buf[1] = reg;
    if (rw_cmd == MCP23S17_CMD_WRITE)
        tx_buf[2] = tx_data;
    // Write and read data
    platform_spi_set_config(dev->spi, dev->spi_speed, dev->spi_mode, dev->spi_bit_order);
    ret = platform_spi_write_read(dev->spi, &mcp23s17_cs_select, &mcp23s17_cs_deselect, dev->cs_pin, tx_buf, rx_buf, sizeof(rx_buf));
    if (ret != PLATFORM_OK)
        return PLATFORM_SPI_COM_ERR;
    // Copy readed data if needed
    if (rw_cmd == MCP23S17_CMD_READ)
        *rx_data = rx_buf[2];
    return PLATFORM_OK;
}
 
/* Set register bits */
mcp23s17_err_code_t mcp23s17_set_bits(mcp23s17_t* dev, mcp23s17_regs_t reg, uint8_t bit_mask) // missing test
{
    uint8_t temp;
    ret = mcp23s17_generic_transfer(dev, reg, MCP23S17_CMD_READ, NULL_TX, &temp);
    if (ret != PLATFORM_OK)
        return ret;
    temp |= bit_mask;
    ret = mcp23s17_generic_transfer(dev, reg, MCP23S17_CMD_WRITE, temp, NULL_RX);
    if (ret != PLATFORM_OK)
        return ret;
    return PLATFORM_OK;
}

/* Clear register bits */
mcp23s17_err_code_t mcp23s17_clear_bits(mcp23s17_t* dev, mcp23s17_regs_t reg, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Toggle register bits */
mcp23s17_err_code_t mcp23s17_toggle_bits(mcp23s17_t* dev, mcp23s17_regs_t reg, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Read data from PORTA */
mcp23s17_err_code_t mcp23s17_read_port_a(mcp23s17_t* dev, uint8_t* data)
{
    ret = mcp23s17_generic_transfer(dev, MCP23S17_GPIOA_BANK0, MCP23S17_CMD_READ, NULL_TX, data);
    if (ret != PLATFORM_OK)
        return ret;
    return PLATFORM_OK;
}

/* Read data from PORTB */
mcp23s17_err_code_t mcp23s17_read_port_b(mcp23s17_t* dev, uint8_t* data)
{
    ret = mcp23s17_generic_transfer(dev, MCP23S17_GPIOB_BANK0, MCP23S17_CMD_READ, NULL_TX, data);
    if (ret != PLATFORM_OK)
        return ret;
    return PLATFORM_OK;
}

/* Read data from PORTA-PORTB and merge into one 16bit value PORTA is the MSB and PORTB is the LSB */
mcp23s17_err_code_t mcp23s17_read_ports(mcp23s17_t* dev, uint16_t* data)
{
    uint8_t porta;
    uint8_t portb;
    ret = mcp23s17_read_port_a(dev, &porta);
    if (ret != PLATFORM_OK)
        return ret;
    ret = mcp23s17_read_port_b(dev, &portb);
    if (ret != PLATFORM_OK)
        return ret;
    *data = (portb << 8) | porta;
    return PLATFORM_OK;
}

/* Write one byte of data to PORTA */
mcp23s17_err_code_t mcp23s17_write_port_a(mcp23s17_t* dev, uint8_t write_data)
{
    return PLATFORM_OK;
}

/* Clear bit from PORTA */
mcp23s17_err_code_t mcp23s17_clear_bit_port_a(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Set bit from PORTA */
mcp23s17_err_code_t mcp23s17_set_bit_port_a(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Toggle bit from PORTA */
mcp23s17_err_code_t mcp23s17_toggle_bit_port_a(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Write one byte of data to PORTB */
mcp23s17_err_code_t mcp23s17_write_port_b(mcp23s17_t* dev, uint8_t write_data)
{
    return PLATFORM_OK;
}

/* Clear bit from PORTB */
mcp23s17_err_code_t mcp23s17_clear_bit_port_b(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Set bit from PORTB */
mcp23s17_err_code_t mcp23s17_set_bit_port_b(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Toggle bit from PORTB */
mcp23s17_err_code_t mcp23s17_toggle_bit_port_b(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Set PORTA direction */
mcp23s17_err_code_t mcp23s17_set_direction_port_a(mcp23s17_t* dev, uint8_t write_data)
{
    return PLATFORM_OK;
}

/* Set pins from PORTA as input */
mcp23s17_err_code_t mcp23s17_set_input_dir_port_a(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Set pins from PORTA as output */
mcp23s17_err_code_t mcp23s17_set_output_dir_port_a(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Set PORTB direction */
mcp23s17_err_code_t mcp23s17_set_direction_port_b(mcp23s17_t* dev, uint8_t write_data)
{
    return PLATFORM_OK;
}

/* Set pins from PORTB as input */
mcp23s17_err_code_t mcp23s17_set_input_dir_port_b(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Set pins from PORTB as output */
mcp23s17_err_code_t mcp23s17_set_output_dir_port_b(mcp23s17_t* dev, uint8_t bit_mask)
{
    return PLATFORM_OK;
}

/* Set pull-ups of PORTA pins */
mcp23s17_err_code_t mcp23s17_set_pull_ups_port_a(mcp23s17_t* dev, uint8_t write_data)
{
    return PLATFORM_OK;
}

/* Set pull-ups of PORTB pins */
mcp23s17_err_code_t mcp23s17_set_pull_ups_port_b(mcp23s17_t* dev, uint8_t write_data)
{
    return PLATFORM_OK;
}

/* Active pin by position on PORTA, from PA0 to PA7 */
mcp23s17_err_code_t mcp23s17_set_potr_a(mcp23s17_t* dev, uint8_t position)
{
    return PLATFORM_OK;
}

/* Active pin by position on PORTB, from PB0 to PB7 */
mcp23s17_err_code_t mcp23s17_set_potr_b(mcp23s17_t* dev, uint8_t position)
{
    return PLATFORM_OK;
}

/* Reset */
void mcp23s17_reset(mcp23s17_t* dev)
{}

/* Get state of interrupt pin */
void mcp23s17_get_interrupt(mcp23s17_t* dev, uint8_t* state)
{}

/* Enable CS for start SPI coms */
void __attribute__((weak)) mcp23s17_cs_select(int cs_pin) { platform_gpio_set(cs_pin, false); };

/* Disable CS after SPI coms*/
void __attribute__((weak)) mcp23s17_cs_deselect(int cs_pin) { platform_gpio_set(cs_pin, true); };