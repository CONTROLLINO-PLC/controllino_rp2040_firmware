/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "cy8c95xx.h"
 
/* Utility structures for addres management */
static uint8_t port_slave_addr;
static uint8_t eeprom_slave_addr;
 
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
int cy8c95xx_init(cy8c95xx_t* dev, cy8c95xx_cfg_t* cfg)
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
void cy8c95xx_generic_write(cy8c95xx_t* dev, uint8_t reg, uint8_t* data_buf, uint8_t len)
{
    uint8_t tx_buf[256];
    uint8_t cnt;
    tx_buf[0] = reg;
    for (cnt = 1; cnt <= len; cnt++) {
        tx_buf[cnt] = data_buf[cnt - 1]; 
    }
    
    platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, len + 1);
}
 
/* Reads data from register */
void cy8c95xx_generic_read(cy8c95xx_t* dev, uint8_t reg, uint8_t* data_buf, uint8_t len)
{
    platform_i2c_write(dev->i2c, dev->slave_addr, &reg, 1);
    platform_i2c_read(dev->i2c, dev->slave_addr, data_buf, len);
}
 
/* Write single byte of data to register */
void cy8c95xx_write_byte(cy8c95xx_t* dev, uint8_t reg_adr, uint8_t wr_data)
{
    dev->slave_addr = port_slave_addr;
    cy8c95xx_generic_write(dev, reg_adr, &wr_data, 1);
}
 
/* Write single byte of data to register */
uint8_t cy8c95xx_read_byte(cy8c95xx_t* dev, uint8_t reg_adr)
{
    uint8_t result;
    dev->slave_addr = port_slave_addr;
    cy8c95xx_generic_read(dev, reg_adr, &result, 1);
    return result;
}
 
/* Writes number of bytes into register */
void cy8c95xx_write_port_exp(cy8c95xx_t* dev, uint8_t reg, uint8_t* buf, uint8_t len)
{
    uint8_t tx_buf[255];
    uint8_t cnt;
    tx_buf[0] = reg;
    for (cnt = 0; cnt < len; cnt++) {
        tx_buf[cnt + 1] = buf[cnt];
    }
    dev->slave_addr = port_slave_addr;
    platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, len + 1);
}
 
/* Reads number of bytes from register */
void cy8c95xx_read_port_exp(cy8c95xx_t* dev, uint8_t reg, uint8_t* buf, uint8_t len)
{
    dev->slave_addr = port_slave_addr;
    platform_i2c_write(dev->i2c, dev->slave_addr, &reg, 1);
    platform_i2c_read(dev->i2c, dev->slave_addr, buf, len);
}
 
/* Send EEPROM comand */
void cy8c95xx_send_eeprom_cmd(cy8c95xx_t* dev, uint8_t cmd)
{
    uint8_t tx_buf[2];
    tx_buf[0] = CY8C95XX_REG_CMD_ADDR;
    tx_buf[1] = cmd;
    dev->slave_addr = port_slave_addr;
    platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, 2);
}
 
/* Writes number of bytes into EEPROM */
void cy8c95xx_write_eeprom(cy8c95xx_t* dev, uint16_t mem_adr, uint8_t* buf, uint8_t len)
{
    uint8_t tx_buf[255];
    uint8_t cnt;
    tx_buf[1] =(uint8_t)(mem_adr & 0x00FF);
    tx_buf[0] =(uint8_t)((mem_adr >> 8) & 0x00FF);
    for (cnt = 0; cnt < len; cnt++) {
        tx_buf[cnt + 2] = buf[cnt];
    }
    dev->slave_addr = eeprom_slave_addr;
    platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, len + 2);
}
 
/* Reads number of bytes from EEPROM */
void cy8c95xx_read_eeprom(cy8c95xx_t* dev, uint16_t mem_adr, uint8_t* buf, uint8_t len)
{
    uint8_t tx_buf[2];
    tx_buf[1] =(uint8_t)(mem_adr & 0x00FF);
    tx_buf[0] =(uint8_t)((mem_adr >> 8) & 0x00FF);
    dev->slave_addr = eeprom_slave_addr;
    platform_i2c_write(dev->i2c, dev->slave_addr, tx_buf, 2);
    platform_i2c_read(dev->i2c, dev->slave_addr, buf, len);
}
 
/* Read state of a single bit from register */
uint8_t cy8c95xx_read_bit(cy8c95xx_t* dev, uint8_t reg_adr, uint8_t bit_num)
{
    uint8_t bit_chk;
    uint8_t res;
    bit_chk = cy8c95xx_read_byte(dev, reg_adr);
    res = bit_chk & (1 << bit_num);
    return res;
}
 
/* Set or Clear specific bit in selected register */
void cy8c95xx_write_bit(cy8c95xx_t* dev, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val)
{
    uint8_t bit_chk;
    bit_chk = cy8c95xx_read_byte(dev, reg_adr);
    bit_chk =(pin_val != 0) ?(bit_chk |(1 << bit_num)) :(bit_chk & ~(1 << bit_num));
    cy8c95xx_write_byte(dev, reg_adr, bit_chk);
}
 
/* Get a single INPUT pin logic level */
uint8_t cy8c95xx_read_pin(cy8c95xx_t* dev, uint16_t pin, uint8_t inv)
{
    uint8_t buf;
    if (inv == 0x01) {
        cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR, (0x00 + (pin / 8)));
        cy8c95xx_write_byte(dev, CY8C95XX_REG_INV_ADDR, (pin % 8));
    }
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR, (0x00 + (pin / 8)));
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR_ADDR, 0xFF);
    buf = cy8c95xx_read_bit(dev,(CY8C95XX_REG_IN_PORT0_ADDR +(pin / 8)),(pin % 8));
    return buf;
}
 
/* Get all pin logic levels from port */
uint8_t cy8c95xx_read_port(cy8c95xx_t* dev, uint8_t port, uint8_t inv)
{
    uint8_t buf;
    if (inv == 0x01) {
        cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR, port);
        cy8c95xx_write_byte(dev, CY8C95XX_REG_INV_ADDR, 0xFF);
    }
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR, port);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR_ADDR, 0xFF);
    buf = cy8c95xx_read_byte(dev, CY8C95XX_REG_IN_PORT0_ADDR + port);
    return buf;
}
 
/* Get a single OUTPUT pin setting */
uint8_t cy8c95xx_get_pin_out_lvl(cy8c95xx_t* dev, uint16_t pin)
{
    uint8_t buf;
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR_ADDR, 0xFF);
    buf = cy8c95xx_read_bit(dev,(CY8C95XX_REG_OUT_PORT0_ADDR +(pin / 8)),(pin % 8));
    return buf;
}
 
/* Get all pin output settings from port */
uint8_t cy8c95xx_get_port_out_lvl(cy8c95xx_t* dev, uint8_t port)
{
    uint8_t buf;
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR, port);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR_ADDR, 0xFF);
    buf = cy8c95xx_read_byte(dev, CY8C95XX_REG_OUT_PORT0_ADDR + port);
    return buf;
}
 
/* Set a single OUTPUT pin logic level */
void cy8c95xx_write_pin(cy8c95xx_t* dev, uint16_t pin, uint8_t pin_val)
{
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR_ADDR, 0x00);
    cy8c95xx_write_bit(dev,(CY8C95XX_REG_OUT_PORT0_ADDR +(pin / 8)),(pin % 8), pin_val);
}
 
/* Set all OUTPUT pins logic levels in one port */
void cy8c95xx_write_port(cy8c95xx_t* dev, uint8_t port, uint8_t value)
{
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR, port);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR_ADDR, 0x00);
    cy8c95xx_write_byte(dev,(CY8C95XX_REG_OUT_PORT0_ADDR + port), value);
}
 
void cy8c95xx_sel_pwm_pin(cy8c95xx_t *dev, uint16_t pin, uint8_t pwm_en)
{
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_DIR_ADDR, 0x00);
    cy8c95xx_write_bit(dev,(CY8C95XX_REG_OUT_PORT0_ADDR +(pin / 8)),(pin % 8), pwm_en);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PORT_SEL_ADDR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(dev, CY8C95XX_REG_SEL_PWM_OUT_ADDR,(pwm_en <<(pin % 8)));
}
 
/* Configure pwm output */
void cy8c95xx_pwm_cfg(cy8c95xx_t* dev, cy8c95xx_pwm_cfg_t pwm_cfg, float* duty_cyc, float* freq)
{
    uint8_t buf[5];
    buf[0] = pwm_cfg.pwm_sel;
    buf[1] = pwm_cfg.clk_src;
    buf[2] = pwm_cfg.period;
    buf[3] = pwm_cfg.pulse_wid;
    buf[4] = pwm_cfg.devider;
    if (buf[3] >= buf[2]) {
        buf[3] =(buf[2] - 1);
    }
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PWM_SEL_ADDR, buf[0]);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_CFG_PWM_ADDR, buf[1]);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PERIOD_PWM_ADDR, buf[2]);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_PULSE_WIDTH_PWM_ADDR, buf[3]);
    cy8c95xx_write_byte(dev, CY8C95XX_REG_DIVIDER_ADDR, buf[4]);
    *duty_cyc =(float)buf[3] /(float)buf[2];
    *freq = 93750.0 /(float)buf[4];
}
 
/* Configures EEPROM enable register */
void cy8c95xx_eeprom_enable(cy8c95xx_t* dev, uint8_t cmd)
{
    uint8_t tx_buf[4];
    tx_buf[0] = 0x43;
    tx_buf[1] = 0x4D;
    tx_buf[2] = 0x53;
    tx_buf[3] = cmd;
    cy8c95xx_write_port_exp(dev, CY8C95XX_REG_EEPROM_ADDR, tx_buf, 4);
}

