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
    cfg->i2c =       PLATFORM_I2C_HW;
    cfg->i2c_speed = PLATFORM_I2C_SPEED;
    cfg->sda_pin =   PLATFORM_I2C_SDA;
    cfg->scl_pin =   PLATFORM_I2C_SCL;
    cfg->i2c_addr =  CY8C95XX_DEV_ADR_GND;
    cfg->rst_pin =   CY8C95XX_RST;
    cfg->int_pin =   CY8C95XX_INT;
}
 
/* Initializes hardware according to configuration */
int cy8c95xx_init(cy8c95xx_t* exp, cy8c95xx_cfg_t* cfg)
{
    // Init hardware i2c interface
    if (platform_i2c_init(cfg->i2c, cfg->i2c_speed, cfg->sda_pin, cfg->scl_pin) != PLATFORM_OK)
        return CY8C95XX_INIT_ERROR;
    // Init hardware reset and int pins 
    platform_gpio_init(cfg->rst_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED);
    platform_gpio_init(cfg->int_pin, PLATFORM_GPIO_IN, PLATFORM_GPIO_PULL_DISABLED);
    // Set values from cfg
    exp->i2c = cfg->i2c;
    exp->rst_pin = cfg->rst_pin;
    exp->int_pin = cfg->int_pin;
    exp->slave_addr = cfg->i2c_addr;
    // Base addresses
    port_slave_addr = CY8C95XX_M_PORT_BASE_ADR | exp->slave_addr;
    eeprom_slave_addr = CY8C95XX_EEPROM_BASE_ADR | exp->slave_addr;
    // Check coms
    uint8_t rxdata;
    return platform_i2c_read(exp->i2c, port_slave_addr, &rxdata, 1);
}
 
/* Reset port expander using rst_pin */
void cy8c95xx_reset(cy8c95xx_t* exp)
{
    platform_gpio_set(exp->rst_pin, true);
    platform_sleep_ms(1000);
    platform_gpio_set(exp->rst_pin, false);
    platform_sleep_ms(1000);
}
 
/* Check interrupt by reading int_pin level */
uint8_t cy8c95xx_check_int(cy8c95xx_t* exp)
{
    return platform_gpio_get(exp->int_pin) ? 1 : 0;
}
 
/* Writes data to register */
void cy8c95xx_generic_write(cy8c95xx_t* exp, uint8_t reg, uint8_t* data_buf, uint8_t len)
{
    uint8_t tx_buf[256];
    uint8_t cnt;
    tx_buf[0] = reg;
    for (cnt = 1; cnt <= len; cnt++) {
        tx_buf[cnt] = data_buf[cnt - 1]; 
    }
    
    platform_i2c_write(exp->i2c, exp->slave_addr, tx_buf, len + 1);
}
 
/* Reads data from register */
void cy8c95xx_generic_read(cy8c95xx_t* exp, uint8_t reg, uint8_t* data_buf, uint8_t len)
{
    platform_i2c_write(exp->i2c, exp->slave_addr, &reg, 1);
    platform_i2c_read(exp->i2c, exp->slave_addr, data_buf, len);
}
 
/* Write single byte of data to register */
void cy8c95xx_write_byte(cy8c95xx_t* exp, uint8_t reg_adr, uint8_t wr_data)
{
    exp->slave_addr = port_slave_addr;
    cy8c95xx_generic_write(exp, reg_adr, &wr_data, 1);
}
 
/* Write single byte of data to register */
uint8_t cy8c95xx_read_byte(cy8c95xx_t* exp, uint8_t reg_adr)
{
    uint8_t result;
    exp->slave_addr = port_slave_addr;
    cy8c95xx_generic_read(exp, reg_adr, &result, 1);
    return result;
}
 
/* Writes number of bytes into register */
void cy8c95xx_write_port_exp(cy8c95xx_t* exp, uint8_t reg, uint8_t* buf, uint8_t len)
{
    uint8_t tx_buf[255];
    uint8_t cnt;
    tx_buf[0] = reg;
    for (cnt = 0; cnt < len; cnt++) {
        tx_buf[cnt + 1] = buf[cnt];
    }
    exp->slave_addr = port_slave_addr;
    platform_i2c_write(exp->i2c, exp->slave_addr, tx_buf, len + 1);
}
 
/* Reads number of bytes from register */
void cy8c95xx_read_port_exp(cy8c95xx_t* exp, uint8_t reg, uint8_t* buf, uint8_t len)
{
    exp->slave_addr = port_slave_addr;
    platform_i2c_write(exp->i2c, exp->slave_addr, &reg, 1);
    platform_i2c_read(exp->i2c, exp->slave_addr, buf, len);
}
 
/* Send EEPROM comand */
void cy8c95xx_send_eeprom_cmd(cy8c95xx_t* exp, uint8_t cmd)
{
    uint8_t tx_buf[2];
    tx_buf[0] = CY8C95XX_REG_CMD_ADR;
    tx_buf[1] = cmd;
    exp->slave_addr = port_slave_addr;
    platform_i2c_write(exp->i2c, exp->slave_addr, tx_buf, 2);
}
 
/* Writes number of bytes into EEPROM */
void cy8c95xx_write_eeprom(cy8c95xx_t* exp, uint16_t mem_adr, uint8_t* buf, uint8_t len)
{
    uint8_t tx_buf[255];
    uint8_t cnt;
    tx_buf[1] =(uint8_t)(mem_adr & 0x00FF);
    tx_buf[0] =(uint8_t)((mem_adr >> 8) & 0x00FF);
    for (cnt = 0; cnt < len; cnt++) {
        tx_buf[cnt + 2] = buf[cnt];
    }
    exp->slave_addr = eeprom_slave_addr;
    platform_i2c_write(exp->i2c, exp->slave_addr, tx_buf, len + 2);
}
 
/* Reads number of bytes from EEPROM */
void cy8c95xx_read_eeprom(cy8c95xx_t* exp, uint16_t mem_adr, uint8_t* buf, uint8_t len)
{
    uint8_t tx_buf[2];
    tx_buf[1] =(uint8_t)(mem_adr & 0x00FF);
    tx_buf[0] =(uint8_t)((mem_adr >> 8) & 0x00FF);
    exp->slave_addr = eeprom_slave_addr;
    platform_i2c_write(exp->i2c, exp->slave_addr, tx_buf, 2);
    platform_i2c_read(exp->i2c, exp->slave_addr, buf, len);
}
 
/* Read state of a single bit from register */
uint8_t cy8c95xx_read_bit(cy8c95xx_t* exp, uint8_t reg_adr, uint8_t bit_num)
{
    uint8_t bit_chk;
    uint8_t res;
    bit_chk = cy8c95xx_read_byte(exp, reg_adr);
    res = bit_chk & (1 << bit_num);
    return res;
}
 
/* Set or Clear specific bit in selected register */
void cy8c95xx_write_bit(cy8c95xx_t* exp, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val)
{
    uint8_t bit_chk;
    bit_chk = cy8c95xx_read_byte(exp, reg_adr);
    bit_chk =(pin_val != 0) ?(bit_chk |(1 << bit_num)) :(bit_chk & ~(1 << bit_num));
    cy8c95xx_write_byte(exp, reg_adr, bit_chk);
}
 
/* Get a single INPUT pin logic level */
uint8_t cy8c95xx_read_pin(cy8c95xx_t* exp, uint16_t pin, uint8_t inv)
{
    uint8_t buf;
    if (inv == 0x01) {
        cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR, (0x00 + (pin / 8)));
        cy8c95xx_write_byte(exp, CY8C95XX_REG_INV_ADR, (pin % 8));
    }
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR, (0x00 + (pin / 8)));
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_DIR_ADR, 0xFF);
    buf = cy8c95xx_read_bit(exp,(CY8C95XX_REG_IN_PORT0_ADR +(pin / 8)),(pin % 8));
    return buf;
}
 
/* Get all pin logic levels from port */
uint8_t cy8c95xx_read_port(cy8c95xx_t* exp, uint8_t port, uint8_t inv)
{
    uint8_t buf;
    if (inv == 0x01) {
        cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR, port);
        cy8c95xx_write_byte(exp, CY8C95XX_REG_INV_ADR, 0xFF);
    }
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR, port);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_DIR_ADR, 0xFF);
    buf = cy8c95xx_read_byte(exp, CY8C95XX_REG_IN_PORT0_ADR + port);
    return buf;
}
 
/* Get a single OUTPUT pin setting */
uint8_t cy8c95xx_get_pin_out_lvl(cy8c95xx_t* exp, uint16_t pin)
{
    uint8_t buf;
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_DIR_ADR, 0xFF);
    buf = cy8c95xx_read_bit(exp,(CY8C95XX_REG_OUT_PORT0_ADR +(pin / 8)),(pin % 8));
    return buf;
}
 
/* Get all pin output settings from port */
uint8_t cy8c95xx_get_port_out_lvl(cy8c95xx_t* exp, uint8_t port)
{
    uint8_t buf;
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR, port);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_DIR_ADR, 0xFF);
    buf = cy8c95xx_read_byte(exp, CY8C95XX_REG_OUT_PORT0_ADR + port);
    return buf;
}
 
/* Set a single OUTPUT pin logic level */
void cy8c95xx_write_pin(cy8c95xx_t* exp, uint16_t pin, uint8_t pin_val)
{
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_DIR_ADR, 0x00);
    cy8c95xx_write_bit(exp,(CY8C95XX_REG_OUT_PORT0_ADR +(pin / 8)),(pin % 8), pin_val);
}
 
/* Set all OUTPUT pins logic levels in one port */
void cy8c95xx_write_port(cy8c95xx_t* exp, uint8_t port, uint8_t value)
{
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR, port);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_DIR_ADR, 0x00);
    cy8c95xx_write_byte(exp,(CY8C95XX_REG_OUT_PORT0_ADR + port), value);
}
 
void cy8c95xx_sel_pwm_pin(cy8c95xx_t *exp, uint16_t pin, uint8_t pwm_en)
{
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_DIR_ADR, 0x00);
    cy8c95xx_write_bit(exp,(CY8C95XX_REG_OUT_PORT0_ADR +(pin / 8)),(pin % 8), pwm_en);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PORT_SEL_ADR,(0x00 +(pin / 8)));
    cy8c95xx_write_byte(exp, CY8C95XX_REG_SEL_PWM_OUT_ADR,(pwm_en <<(pin % 8)));
}
 
/* Configure pwm output */
void cy8c95xx_pwm_cfg(cy8c95xx_t* exp, cy8c95xx_pwm_cfg_t pwm_cfg, float* duty_cyc, float* freq)
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
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PWM_SEL_ADR, buf[0]);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_CFG_PWM_ADR, buf[1]);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PERIOD_PWM_ADR, buf[2]);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_PULSE_WIDTH_PWM_ADR, buf[3]);
    cy8c95xx_write_byte(exp, CY8C95XX_REG_DIVIDER_ADR, buf[4]);
    *duty_cyc =(float)buf[3] /(float)buf[2];
    *freq = 93750.0 /(float)buf[4];
}
 
/* Configures EEPROM enable register */
void cy8c95xx_eeprom_enable(cy8c95xx_t* exp, uint8_t cmd)
{
    uint8_t tx_buf[4];
    tx_buf[0] = 0x43;
    tx_buf[1] = 0x4D;
    tx_buf[2] = 0x53;
    tx_buf[3] = cmd;
    cy8c95xx_write_port_exp(exp, CY8C95XX_REG_EEPROM_ADR, tx_buf, 4);
}

