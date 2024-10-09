/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "cy8c9520.h"
#include "string.h"
#include "hw_platform.h" /* External harware interface library */
 
/* Utility structures for addres management */
static uint8_t port_slave_addr;
static uint8_t eeprom_slave_addr;
static platform_err_code_t ret;
 
/* Initializes default configuration */
void cy8c9520_set_default_cfg(cy8c9520_cfg_t* cfg)
{
    cfg->sda_pin = PLATFORM_I2C_SDA;
    cfg->scl_pin = PLATFORM_I2C_SCL;
    cfg->i2c_speed = PLATFORM_I2C_SPEED;
    cfg->i2c_addr = CY8C9520_DEV_ADDR_GND;
    cfg->i2c = PLATFORM_I2C_HW;
    cfg->rst_pin = CY8C9520_RST;
    cfg->int_pin = CY8C9520_INT;
}
 
/* Initializes hardware according to configuration */
cy8c9520_err_code_t cy8c9520_init(cy8c9520_t* dev, cy8c9520_cfg_t* cfg)
{
    // Init hardware I2C interface
    if (platform_i2c_init(cfg->i2c, cfg->i2c_speed, cfg->sda_pin, cfg->scl_pin) != PLATFORM_OK)
        return PLATFORM_I2C_INIT_ERR;
    // Init hardware reset and cy8c9520_gpio_t pins 
    if (platform_gpio_init(cfg->rst_pin, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED) != PLATFORM_OK ||
        platform_gpio_init(cfg->int_pin, PLATFORM_GPIO_IN, PLATFORM_GPIO_PULL_DISABLED) != PLATFORM_OK)
        return PLATFORM_GPIO_INIT_ERR;
    // Base addresses
    port_slave_addr = CY8C9520_M_PORT_BASE_ADDR | cfg->i2c_addr;
    eeprom_slave_addr = CY8C9520_EEPROM_BASE_ADDR | cfg->i2c_addr;
    // Set values from cfg
    dev->i2c = cfg->i2c;
    dev->rst_pin = cfg->rst_pin;
    dev->int_pin = cfg->int_pin;
    // Check coms and reset registers
    return cy8c9520_send_cmd(dev, CY8C9520_RECFG_DEV_TO_POR);
}
 
/* Reset port expander using rst_pin */
void cy8c9520_reset(cy8c9520_t* dev)
{
    platform_gpio_set(dev->rst_pin, true);
    platform_sleep_ms(100);
    platform_gpio_set(dev->rst_pin, false);
    platform_sleep_ms(100);
}
 
/* Check interrupt by reading int_pin level */
uint8_t cy8c9520_check_int(cy8c9520_t* dev)
{
    bool int_val = false;
    platform_gpio_get(dev->int_pin, &int_val);
    return int_val ? 1 : 0;
}
 
/* Writes data to register */
cy8c9520_err_code_t cy8c9520_generic_write(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t* txdata, uint8_t txlen)
{
    uint8_t tx_buf[txlen + 1];
    tx_buf[0] = reg;
    memcpy(&tx_buf[1], txdata, txlen);
    return platform_i2c_write(dev->i2c, port_slave_addr, tx_buf, sizeof(tx_buf));
}
 
/* Reads data from register */
cy8c9520_err_code_t cy8c9520_generic_read(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t* rxdata, uint8_t rxlen)
{
    if (platform_i2c_write(dev->i2c, port_slave_addr, (uint8_t*)&reg, 1) != PLATFORM_OK)
        return PLATFORM_I2C_COM_ERR;
    return platform_i2c_read(dev->i2c, port_slave_addr, rxdata, rxlen);
}
 
/* Write single byte of data to register */
cy8c9520_err_code_t cy8c9520_write_byte(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t txdata)
{
    return cy8c9520_generic_write(dev, reg, &txdata, 1);
}
 
/* Write single byte of data to register */
cy8c9520_err_code_t cy8c9520_read_byte(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t* rxdata)
{
    return cy8c9520_generic_read(dev, reg, rxdata, 1);
}
 
/* Send command to CY8C9520_REG_CMD */
cy8c9520_err_code_t cy8c9520_send_cmd(cy8c9520_t* dev, cy8c9520_cmd_t cmd)
{
    return cy8c9520_write_byte(dev, CY8C9520_REG_CMD, cmd);
}
 
/* Read state of a single bit from register */
cy8c9520_err_code_t cy8c9520_read_bit(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t bit_num, uint8_t* state)
{
    uint8_t reg_byte;
    ret = cy8c9520_read_byte(dev, reg, &reg_byte);
    if (ret != PLATFORM_OK)
        return ret;
    *state = (reg_byte >> bit_num) & 0x01;
    return PLATFORM_OK;
}
 
/* Set or clear specific bit in register */
cy8c9520_err_code_t cy8c9520_write_bit(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t bit_num, uint8_t val)
{
    uint8_t reg_byte;
    ret = cy8c9520_read_byte(dev, reg, &reg_byte);
    if (ret != PLATFORM_OK)
        return ret;
    reg_byte = (val & 0x1) ? (reg_byte | (uint8_t)(1 << bit_num)) : (reg_byte & (uint8_t)~(1 << bit_num));
    return cy8c9520_write_byte(dev, reg, reg_byte);
}
 
/* Separated select port function to optimize coms */
// cy8c9520_err_code_t cy8c9520_select_port(cy8c9520_t* dev, uint8_t port_num) {
//     static uint8_t prev_port_num = 0x07; // Save last port number to optimize coms
//     if (port_num > 0x06) return PLATFORM_ARGUMENT_ERR;
//     // Select port only if it is different from previous
//     ret = PLATFORM_OK;
//     if (prev_port_num != port_num) {
//         ret = cy8c9520_write_byte(dev, CY8C9520_REG_PORT_SEL, port_num);
//         if (ret != PLATFORM_OK)
//             return ret;
//         prev_port_num = port_num;
//     }
//     return ret;
// }
 
/* Port select without optimization */
cy8c9520_err_code_t cy8c9520_select_port(cy8c9520_t* dev, uint8_t port_num) {
    if (port_num > 0x06) return PLATFORM_ARGUMENT_ERR;
    return cy8c9520_write_byte(dev, CY8C9520_REG_PORT_SEL, port_num);
}
 
/* Writes number of bytes into EEPROM */
cy8c9520_err_code_t cy8c9520_write_eeprom(cy8c9520_t* dev, uint16_t mem, uint8_t* txdata, uint8_t txlen)
{
    uint8_t tx_buf[txlen + 2];
    tx_buf[1] = (uint8_t)(mem & 0x00FF);
    tx_buf[0] =(uint8_t)((mem >> 8) & 0x00FF);
    memcpy(&tx_buf[2], txdata, txlen);
    return platform_i2c_write(dev->i2c, eeprom_slave_addr, tx_buf, sizeof(tx_buf));
}
 
/* Reads number of bytes from EEPROM */
cy8c9520_err_code_t cy8c9520_read_eeprom(cy8c9520_t* dev, uint16_t mem, uint8_t* rxdata, uint8_t rxlen)
{
    uint8_t tx_buf[2];
    tx_buf[1] = (uint8_t)(mem & 0x00FF);
    tx_buf[0] =(uint8_t)((mem >> 8) & 0x00FF);
    if (platform_i2c_write(dev->i2c, eeprom_slave_addr, tx_buf, 2) != PLATFORM_OK)
        return PLATFORM_I2C_COM_ERR;
    return platform_i2c_read(dev->i2c, eeprom_slave_addr, rxdata, rxlen);
}
 
/* Set pin mode settings */
cy8c9520_err_code_t cy8c9520_pin_mode(cy8c9520_t* dev, int pin, cy8c9520_dir_mode_t dir, cy8c9520_drv_mode_t drv)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    ret = cy8c9520_select_port(dev, (0x00 + (pin / 8)));
    if (ret != PLATFORM_OK)
        return ret;
    ret = cy8c9520_write_bit(dev, CY8C9520_REG_PORT_DIR, (pin % 8), dir);
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_bit(dev, (uint8_t)drv, (pin % 8), 1);
}
 
/* Enable pin input inverted mode */
cy8c9520_err_code_t cy8c9520_pin_en_inv_in(cy8c9520_t* dev, int pin)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    ret = cy8c9520_select_port(dev, (0x00 + (pin / 8)));
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_bit(dev, CY8C9520_REG_INV, (pin % 8), 1);
}
 
/* Disable pin input inverted mode */
cy8c9520_err_code_t cy8c9520_pin_dis_inv_in(cy8c9520_t* dev, int pin)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    ret = cy8c9520_select_port(dev, (0x00 + (pin / 8)));
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_bit(dev, CY8C9520_REG_INV, (pin % 8), 0);
}
 
/* Get a single input pin logic level */
cy8c9520_err_code_t cy8c9520_read_pin(cy8c9520_t* dev, int pin, uint8_t* state)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    return cy8c9520_read_bit(dev, (CY8C9520_REG_IN_PORT0 + (pin / 8)), (pin % 8), state);
}
 
/* Get all pin logic levels from port */
cy8c9520_err_code_t cy8c9520_read_port(cy8c9520_t* dev, uint8_t port, uint8_t* port_state)
{
    return cy8c9520_read_byte(dev, CY8C9520_REG_IN_PORT0 + port, port_state);
}
 
/* Get a single output pin logic level*/
cy8c9520_err_code_t cy8c9520_read_pin_out_lvl(cy8c9520_t* dev, int pin, uint8_t* state)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    return cy8c9520_read_bit(dev, (CY8C9520_REG_OUT_PORT0 + (pin / 8)), (pin % 8), state);
}
 
/* Get all output pin logic levels from port */
cy8c9520_err_code_t cy8c9520_read_port_out_lvl(cy8c9520_t* dev, uint8_t port, uint8_t* port_state)
{
    return cy8c9520_read_byte(dev, CY8C9520_REG_OUT_PORT0 + port, port_state);
}
 
/* Set a single output pin logic level */
cy8c9520_err_code_t cy8c9520_write_pin(cy8c9520_t* dev, int pin, uint8_t val)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    return cy8c9520_write_bit(dev, (CY8C9520_REG_OUT_PORT0 + (pin / 8)), (pin % 8), val);
}
 
/* Set all output pins logic levels in a port */
cy8c9520_err_code_t cy8c9520_write_port(cy8c9520_t* dev, uint8_t port, uint8_t port_val)
{
    return cy8c9520_write_byte(dev, (CY8C9520_REG_OUT_PORT0 + port), port_val);
}
 
/* Enable interrupt on pin with Interrupt Mask Port Register */
cy8c9520_err_code_t cy8c9520_en_pin_int(cy8c9520_t* dev, int pin)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    ret = cy8c9520_select_port(dev, (0x00 + (pin / 8)));
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_bit(dev, CY8C9520_REG_INT_MASK, (pin % 8), 0);
}
 
/* Disable interrupt on pin with Interrupt Mask Port Register */
cy8c9520_err_code_t cy8c9520_dis_pin_int(cy8c9520_t* dev, int pin)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    ret = cy8c9520_select_port(dev, (0x00 + (pin / 8)));
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_bit(dev, CY8C9520_REG_INT_MASK, (pin % 8), 1);
}
 
/* Enable pwm output on pin */
cy8c9520_err_code_t cy8c9520_en_pin_pwm(cy8c9520_t* dev, int pin)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    ret = cy8c9520_select_port(dev, (0x00 + (pin / 8)));
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_bit(dev, CY8C9520_REG_SEL_PWM_OUT, (pin % 8), 1);
}
 
/* Disable pwm output on pin */
cy8c9520_err_code_t cy8c9520_dis_pin_pwm(cy8c9520_t* dev, int pin)
{
    if (pin < 0 || pin > 59) return PLATFORM_ARGUMENT_ERR;
    ret = cy8c9520_select_port(dev, (0x00 + (pin / 8)));
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_bit(dev, CY8C9520_REG_SEL_PWM_OUT, (pin % 8), 0);
}
 
/* Configure pwm output */
cy8c9520_err_code_t cy8c9520_set_pwm_cfg(cy8c9520_t* dev, cy8c9520_pwm_cfg_t* pwm_cfg, float* duty_cyc, float* freq)
{
    uint8_t tx_buf[5];
    tx_buf[0] = pwm_cfg->pwm_sel;
    tx_buf[1] = pwm_cfg->clk_src;
    tx_buf[2] = pwm_cfg->period;
    tx_buf[3] = pwm_cfg->pulse_wid;
    tx_buf[4] = pwm_cfg->devider;
    if (tx_buf[3] >= tx_buf[2]) {
        tx_buf[3] =(tx_buf[2] - 1);
    }
    ret = cy8c9520_write_byte(dev, CY8C9520_REG_PWM_SEL, tx_buf[0]);
    if (ret != PLATFORM_OK)
        return ret;
    ret = cy8c9520_write_byte(dev, CY8C9520_REG_CFG_PWM, tx_buf[1]);
    if (ret != PLATFORM_OK)
        return ret;
    ret = cy8c9520_write_byte(dev, CY8C9520_REG_PERIOD_PWM, tx_buf[2]);
    *duty_cyc = (float)tx_buf[3] / (float)tx_buf[2];
    *freq = 93750.0 / (float)tx_buf[4];
    ret = cy8c9520_write_byte(dev, CY8C9520_REG_PULSE_WIDTH_PWM, tx_buf[3]);
    if (ret != PLATFORM_OK)
        return ret;
    return cy8c9520_write_byte(dev, CY8C9520_REG_DIV_PWM, tx_buf[4]);
}
 
/* Configures EEPROM enable register */
cy8c9520_err_code_t cy8c9520_eeprom_enable(cy8c9520_t* dev, uint8_t cmd)
{
    uint8_t tx_buf[4];
    tx_buf[0] = 0x43;
    tx_buf[1] = 0x4D;
    tx_buf[2] = 0x53;
    tx_buf[3] = cmd;
    return cy8c9520_generic_write(dev, CY8C9520_REG_EEPROM, tx_buf, 4);
}

