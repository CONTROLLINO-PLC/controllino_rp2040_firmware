/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "bts71220.h"
#include "string.h"
#include "hw_platform.h" /* External harware interface library */
 
static bts71220_err_code_t ret;
 
/*!
  * \brief Check daisy chain value
  *
  * \param dev Pointer to BTS71220 power controller struct
  * \param dchain_num Number to check
  * \return PLATFORM_ARGUMENT_ERR : error
  *         PLATFORM_OK : successful
  */
bts71220_err_code_t bts71220_check_dchain_num(bts71220_t* dev, uint8_t dchain_num)
{
    if (dchain_num >= dev->dchain_size)
        return PLATFORM_ARGUMENT_ERR;
    return PLATFORM_OK;
}
 
/* Initializes default configuration */
void bts71220_set_default_cfg(bts71220_cfg_t* cfg)
{
    cfg->mosi_pin = PLATFORM_SPI_MOSI;
    cfg->miso_pin = PLATFORM_SPI_MISO;
    cfg->sck_pin = PLATFORM_SPI_SCK;
    cfg->cs_pin = BTS71220_CS;
    cfg->spi_speed = PLATFORM_SPI_SPEED;
    cfg->spi_mode = PLATFORM_SPI_MODE_1;
    cfg->spi_bit_order = PLATFORM_SPI_MSBFIRST;
    cfg->spi = PLATFORM_SPI_HW;
    cfg->dchain_size = BTS71220_DAISY_CHAIN_SIZE;
}
 
/* Initializes hardware according to configuration */
bts71220_err_code_t bts71220_init(bts71220_t* dev, bts71220_cfg_t* cfg)
{
    // Check daisy chain size
    if (cfg->dchain_size < 1) return PLATFORM_SPI_INIT_ERR;
    // Init hardware SPI interface
    if (platform_spi_init(cfg->spi, cfg->spi_speed, cfg->mosi_pin, cfg->miso_pin, cfg->sck_pin) != PLATFORM_OK)
        return PLATFORM_SPI_INIT_ERR;
    // Init hardware cs pin
    if (platform_gpio_init(cfg->cs_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_UP) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    // Set values from cfg
    dev->cs_pin = cfg->cs_pin;
    dev->spi_speed = cfg->spi_speed;
    dev->spi_mode = cfg->spi_mode;
    dev->spi_bit_order = cfg->spi_bit_order;
    dev->spi = cfg->spi;
    dev->dchain_size = cfg->dchain_size;
    // Check coms
    uint8_t res;
    return bts71220_read_std_diag(dev, &res, 0);
}
 
/* Generic SPI data transfer */
bts71220_err_code_t bts71220_generic_transfer(bts71220_t* dev, uint8_t txdata, uint8_t* rxdata, uint8_t dchain_num)
{
    uint8_t tx_buf[dev->dchain_size];
    uint8_t rx_buf[dev->dchain_size];
    if (bts71220_check_dchain_num(dev, dchain_num) != PLATFORM_OK)
        return PLATFORM_ARGUMENT_ERR;
    memset(tx_buf, BTS71220_REG_STD_DIAG, sizeof(tx_buf));
    tx_buf[dchain_num] = txdata;
    platform_spi_set_config(dev->spi, dev->spi_speed, dev->spi_mode, dev->spi_bit_order);
    // First transfer only optains previos response
    bts71220_cs_select(dev);
    platform_sleep_us(600);
    ret = platform_spi_write_read(dev->spi, tx_buf, rx_buf, sizeof(rx_buf));
    bts71220_cs_deselect(dev);
    if (ret != PLATFORM_OK)
        return PLATFORM_SPI_COM_ERR;
    // Second transfer obtains first transfer response
    bts71220_cs_select(dev);
    platform_sleep_us(600);
    ret = platform_spi_write_read(dev->spi, tx_buf, rx_buf, sizeof(rx_buf));
    bts71220_cs_deselect(dev);
    if (ret != PLATFORM_OK)
        return PLATFORM_SPI_COM_ERR;
    *rxdata = rx_buf[dchain_num];
    return PLATFORM_OK;
}
 
/* Write to register */
bts71220_err_code_t bts71220_write_reg(bts71220_t* dev, bts71220_reg_t reg, uint8_t txdata, uint8_t dchain_num)
{
    if (reg == BTS71220_REG_WRN_DIAG ||
        reg == BTS71220_REG_STD_DIAG ||
        reg == BTS71220_REG_ERR_DIAG ||
        reg == BTS71220_REG_RCS ||
        reg == BTS71220_REG_SRC)
    {
        return PLATFORM_ARGUMENT_ERR;
    }
    uint8_t rxdata;
    txdata &= BTS71220_REG_CONT_MASK;
    reg &= (~BTS71220_REG_CONT_MASK & 0xFF);
    txdata |= (reg | BTS71220_WRITE_MASK);
    return bts71220_generic_transfer(dev, txdata, &rxdata, dchain_num);
    // Pending to check response for diagnosis errors
}
 
/* Read from register */
bts71220_err_code_t bts71220_read_reg(bts71220_t* dev, bts71220_reg_t reg, uint8_t* rxdata, uint8_t dchain_num)
{
    return bts71220_generic_transfer(dev, reg, rxdata, dchain_num);
}
 
/* Read standard diagnosis */
bts71220_err_code_t bts71220_read_std_diag(bts71220_t* dev, uint8_t* rxdata, uint8_t dchain_num)
{
    ret = bts71220_read_reg(dev, BTS71220_REG_STD_DIAG, rxdata, dchain_num);
    if (ret != PLATFORM_OK)
        return ret;
    if (*rxdata & BTS71220_DIAG_RES_MASK)
        return PLATFORM_SPI_COM_ERR;
    return PLATFORM_OK;
}
 
/* Read warnings diagnosis */
bts71220_err_code_t bts71220_read_wrn_diag(bts71220_t* dev, uint8_t* rxdata, uint8_t dchain_num)
{
    ret = bts71220_read_reg(dev, BTS71220_REG_WRN_DIAG, rxdata, dchain_num);
    if (ret != PLATFORM_OK)
        return ret;
    if (!(*rxdata & (BTS71220_ERR_WARN_MASK | BTS71220_REG_CONT_MASK)))
        return PLATFORM_SPI_COM_ERR;
    return PLATFORM_OK;
}
 
/* Read error diagnosis */
bts71220_err_code_t bts71220_read_err_diag(bts71220_t* dev, uint8_t* rxdata, uint8_t dchain_num)
{
    ret = bts71220_read_reg(dev, BTS71220_REG_ERR_DIAG, rxdata, dchain_num);
    if (ret != PLATFORM_OK)
        return ret;
    if (!(*rxdata & (BTS71220_ERR_WARN_MASK | BTS71220_REG_CONT_MASK)))
        return PLATFORM_SPI_COM_ERR;
    return PLATFORM_OK;
}
 
/* Set current sense multiplexer */
bts71220_err_code_t bts71220_set_sense_mux(bts71220_t* dev, bts71220_sense_mux_t mux, uint8_t dchain_num)
{
    bts71220_dcr_reg_t dcr_reg;
    uint8_t txdata;
    ret = bts71220_read_reg(dev, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, dchain_num);
    if (ret != PLATFORM_OK)
        return ret;
    dcr_reg.mux = mux;
    memcpy(&txdata, &dcr_reg, 1);
    return bts71220_write_reg(dev, BTS71220_REG_DCR, txdata, dchain_num);
}