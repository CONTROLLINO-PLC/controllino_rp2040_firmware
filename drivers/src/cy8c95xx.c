/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "cy8c95xx.h"
#include "string.h"
 
/* Utility structures for addres management */
static uint8_t port_slave_addr;
static uint8_t eeprom_slave_addr;
 
/*!
 * \brief Check register address
 *
 * \param reg Register address to check
 * \return CY8C95XX_ARG_ERROR : error
 *         CY8C95XX_OK : successful
 */
cy8c95xx_error_code_t cy8c95xx_check_reg_addr(uint8_t reg)
{
    if (reg > CY8C95XX_REG_CMD)
        return CY8C95XX_ARG_ERROR;
    return CY8C95XX_OK;
}
/* Initializes default configuration */
void cy8c95xx_set_default_cfg(cy8c95xx_cfg_t* cfg)
{
    cfg->sda_pin = PLATFORM_I2C_SDA;
    cfg->scl_pin = PLATFORM_I2C_SCL;
    cfg->i2c_speed = PLATFORM_I2C_SPEED;
    cfg->i2c_addr = CY8C95XX_DEV_ADDR_GND;
    cfg->i2c = PLATFORM_I2C_HW;
    cfg->rst_pin = CY8C95XX_RST;
    cfg->int_pin = CY8C95XX_INT;
}
 
/* Initializes hardware according to configuration */
cy8c95xx_error_code_t cy8c95xx_init(cy8c95xx_t* dev, cy8c95xx_cfg_t* cfg)
{
    // Init hardware I2C interface
    if (platform_i2c_init(cfg->i2c, cfg->i2c_speed, cfg->sda_pin, cfg->scl_pin) != CY8C95XX_OK)
        return CY8C95XX_INIT_ERROR;
    // Init hardware reset and int pins 
    platform_gpio_init(cfg->rst_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED);
    platform_gpio_init(cfg->int_pin, PLATFORM_GPIO_IN, PLATFORM_GPIO_PULL_DISABLED);
    // Set values from cfg
    dev->slave_addr = cfg->i2c_addr;
    dev->i2c = cfg->i2c;
    dev->rst_pin = cfg->rst_pin;
    dev->int_pin = cfg->int_pin;
    // Base addresses
    port_slave_addr = CY8C95XX_M_PORT_BASE_ADDR | dev->slave_addr;
    eeprom_slave_addr = CY8C95XX_EEPROM_BASE_ADDR | dev->slave_addr;
    // Check coms
    uint8_t rxdata;
    return platform_i2c_read(dev->i2c, port_slave_addr, &rxdata, 1);
}
 
/* Reset port expander using rst_pin */
void cy8c95xx_reset(cy8c95xx_t* dev)
{
    platform_gpio_set(dev->rst_pin, true);
    platform_sleep_ms(1000);
    platform_gpio_set(dev->rst_pin, false);
    platform_sleep_ms(1000);
}
 
/* Check interrupt by reading int_pin level */
uint8_t cy8c95xx_check_int(cy8c95xx_t* dev)
{
    return platform_gpio_get(dev->int_pin) ? 1 : 0;
}
 
/* Writes data to register */
cy8c95xx_error_code_t cy8c95xx_generic_write(cy8c95xx_t* dev, uint8_t reg, uint8_t* txdata, uint8_t txlen)
{
    uint8_t tx_buf[txlen + 1];
    if (cy8c95xx_check_reg_addr(reg) != CY8C95XX_OK)
        return CY8C95XX_ARG_ERROR;
    tx_buf[0] = reg;
    memcpy(&tx_buf[1], txdata, txlen);
    return platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, sizeof(tx_buf));
}
 
/* Reads data from register */
cy8c95xx_error_code_t cy8c95xx_generic_read(cy8c95xx_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    if (cy8c95xx_check_reg_addr(reg) != CY8C95XX_OK)
        return CY8C95XX_ARG_ERROR;
    if (platform_i2c_write(dev->i2c, dev->slave_addr, &reg, 1) != CY8C95XX_OK)
        return CY8C95XX_I2C_ERROR;
    return platform_i2c_read(dev->i2c, dev->slave_addr, rxdata, rxlen);
}
 
/* Write single byte of data to register */
cy8c95xx_error_code_t cy8c95xx_write_byte(cy8c95xx_t* dev, uint8_t reg, uint8_t txdata)
{
    dev->slave_addr = port_slave_addr;
    return cy8c95xx_generic_write(dev, reg, &txdata, 1);
}
 
/* Write single byte of data to register */
cy8c95xx_error_code_t cy8c95xx_read_byte(cy8c95xx_t* dev, uint8_t reg, uint8_t* rxdata)
{
    dev->slave_addr = port_slave_addr;
    return cy8c95xx_generic_read(dev, reg, rxdata, 1);
}
 
/* Writes number of bytes into register */
cy8c95xx_error_code_t cy8c95xx_write_port_exp(cy8c95xx_t* dev, uint8_t reg, uint8_t* txdata, uint8_t txlen)
{
    dev->slave_addr = port_slave_addr;
    return cy8c95xx_generic_write(dev, reg, txdata, txlen);
}
 
/* Reads number of bytes from register */
cy8c95xx_error_code_t cy8c95xx_read_port_exp(cy8c95xx_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    dev->slave_addr = port_slave_addr;
    return cy8c95xx_generic_read(dev, reg, rxdata, rxlen);
}
 
/* Send EEPROM comand */
cy8c95xx_error_code_t cy8c95xx_send_eeprom_cmd(cy8c95xx_t* dev, uint8_t cmd)
{
    dev->slave_addr = port_slave_addr;
    return cy8c95xx_generic_write(dev, CY8C95XX_REG_CMD, &cmd, 1);
}
 
/* Writes number of bytes into EEPROM */
cy8c95xx_error_code_t cy8c95xx_write_eeprom(cy8c95xx_t* dev, uint16_t mem, uint8_t* txdata, uint8_t txlen)
{
    uint8_t tx_buf[txlen + 2];
    dev->slave_addr = eeprom_slave_addr;
    tx_buf[1] = (uint8_t)(mem & 0x00FF);
    tx_buf[0] =(uint8_t)((mem >> 8) & 0x00FF);
    memcpy(&tx_buf[2], txdata, txlen);
    return platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, sizeof(tx_buf));
}
 
/* Reads number of bytes from EEPROM */
cy8c95xx_error_code_t cy8c95xx_read_eeprom(cy8c95xx_t* dev, uint16_t mem, uint8_t* rxdata, uint8_t rxlen)
{
    uint8_t tx_buf[2];
    dev->slave_addr = eeprom_slave_addr;
    tx_buf[1] = (uint8_t)(mem & 0x00FF);
    tx_buf[0] =(uint8_t)((mem >> 8) & 0x00FF);
    if (platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, 2) != CY8C95XX_OK)
        return CY8C95XX_I2C_ERROR;
    return platform_i2c_read(dev->i2c, dev->slave_addr, rxdata, rxlen);
}
 
/* Read state of a single bit from register */
cy8c95xx_error_code_t cy8c95xx_read_bit(cy8c95xx_t* dev, uint8_t reg, uint8_t bit_num, uint8_t* state)
{
    uint8_t reg_byte;
    uint8_t ret;
    ret = cy8c95xx_read_byte(dev, reg, &reg_byte);
    if (ret != CY8C95XX_OK)
        return ret;
    *state = reg_byte & (1 << bit_num);
    return CY8C95XX_OK;
}
 
/* Set or clear specific bit in register */
cy8c95xx_error_code_t cy8c95xx_write_bit(cy8c95xx_t* dev, uint8_t reg, uint8_t bit_num, uint8_t val)
{
    uint8_t reg_byte;
    uint8_t ret;
    ret = cy8c95xx_read_byte(dev, reg, &reg_byte);
    if (ret != CY8C95XX_OK)
        return ret;
    reg_byte = val ? (reg_byte | (1 << bit_num)) : (reg_byte & ~(1 << bit_num));
    return cy8c95xx_write_byte(dev, reg, reg_byte);
}
 
/* Get a single input pin logic level */
cy8c95xx_error_code_t cy8c95xx_read_pin(cy8c95xx_t* dev, uint8_t pin, uint8_t inv, uint8_t* state)
{
    uint8_t ret;
    if (inv == 0x01) {
        ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, (0x00 + (pin / 8)));
        if (ret != CY8C95XX_OK)
            return ret;
        ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_INV, (pin % 8));
        if (ret != CY8C95XX_OK)
            return ret;
    }
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, (0x00 + (pin / 8)));
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR, 0xFF);
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_read_bit(dev, (CY8C95XX_REG_IN_PORT0 + (pin / 8)), (pin % 8), state);
}
 
/* Get all pin logic levels from port */
cy8c95xx_error_code_t cy8c95xx_read_port(cy8c95xx_t* dev, uint8_t port, uint8_t inv, uint8_t* port_state)
{
    uint8_t ret;
    if (inv == 0x01) {
        ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, port);
        if (ret != CY8C95XX_OK)
            return ret;
        ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_INV, 0xFF);
        if (ret != CY8C95XX_OK)
            return ret;
    }
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, port);
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR, 0xFF);
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_read_byte(dev, CY8C95XX_REG_IN_PORT0 + port, port_state);
}
 
/* Get a single output pin logic level*/
cy8c95xx_error_code_t cy8c95xx_get_pin_out_lvl(cy8c95xx_t* dev, uint8_t pin, uint8_t* state)
{
    uint8_t ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, (0x00 + (pin / 8)));
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR, 0xFF);
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_read_bit(dev, (CY8C95XX_REG_OUT_PORT0 + (pin / 8)), (pin % 8), state);
}
 
/* Get all output pin logic levels from port */
cy8c95xx_error_code_t cy8c95xx_get_port_out_lvl(cy8c95xx_t* dev, uint8_t port, uint8_t* port_state)
{
    uint8_t ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, port);
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR, 0xFF);
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_read_byte(dev, CY8C95XX_REG_OUT_PORT0 + port, port_state);
}
 
/* Set a single output pin logic level */
cy8c95xx_error_code_t cy8c95xx_write_pin(cy8c95xx_t* dev, uint8_t pin, uint8_t val)
{
    uint8_t ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, (0x00 + (pin / 8)));
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR, 0x00);
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_write_bit(dev, (CY8C95XX_REG_OUT_PORT0 + (pin / 8)), (pin % 8), val);
}
 
/* Set all output pins logic levels in a port */
cy8c95xx_error_code_t cy8c95xx_write_port(cy8c95xx_t* dev, uint8_t port, uint8_t port_val)
{
    uint8_t ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, port);
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR, 0x00);
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_write_byte(dev, (CY8C95XX_REG_OUT_PORT0 + port), port_val);
}
 
/* Enable or disable pwm output on pin */
cy8c95xx_error_code_t cy8c95xx_sel_pwm_pin(cy8c95xx_t* dev, uint8_t pin, uint8_t pwm_en)
{
    uint8_t ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, (0x00 + (pin / 8)));
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR, 0x00);
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_bit(dev, (CY8C95XX_REG_OUT_PORT0 + (pin / 8)), (pin % 8), pwm_en);
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL, (0x00 + (pin / 8)));
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_write_byte(dev, CY8C95XX_REG_SEL_PWM_OUT, (pwm_en << (pin % 8)));
}
 
/* Configure pwm output */
cy8c95xx_error_code_t cy8c95xx_set_pwm_cfg(cy8c95xx_t* dev, cy8c95xx_pwm_cfg_t* pwm_cfg, float* duty_cyc, float* freq)
{
    uint8_t tx_buf[5];
    uint8_t ret;
    tx_buf[0] = pwm_cfg->pwm_sel;
    tx_buf[1] = pwm_cfg->clk_src;
    tx_buf[2] = pwm_cfg->period;
    tx_buf[3] = pwm_cfg->pulse_wid;
    tx_buf[4] = pwm_cfg->devider;
    if (tx_buf[3] >= tx_buf[2]) {
        tx_buf[3] =(tx_buf[2] - 1);
    }
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PWM_SEL, tx_buf[0]);
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_CFG_PWM, tx_buf[1]);
    if (ret != CY8C95XX_OK)
        return ret;
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PERIOD_PWM, tx_buf[2]);
    *duty_cyc = (float)tx_buf[3] / (float)tx_buf[2];
    *freq = 93750.0 / (float)tx_buf[4];
    ret = cy8c95xx_write_byte(dev, CY8C95XX_REG_PULSE_WIDTH_PWM, tx_buf[3]);
    if (ret != CY8C95XX_OK)
        return ret;
    return cy8c95xx_write_byte(dev, CY8C95XX_REG_DIVIDER, tx_buf[4]);
}
 
/* Configures EEPROM enable register */
cy8c95xx_error_code_t cy8c95xx_eeprom_enable(cy8c95xx_t* dev, uint8_t cmd)
{
    uint8_t tx_buf[4];
    tx_buf[0] = 0x43;
    tx_buf[1] = 0x4D;
    tx_buf[2] = 0x53;
    tx_buf[3] = cmd;
    return cy8c95xx_write_port_exp(dev, CY8C95XX_REG_EEPROM, tx_buf, 4);
}

