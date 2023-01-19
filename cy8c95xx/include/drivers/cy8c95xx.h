/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 * Copyright© 2020 MikroElektronika d.o.o.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef cy8c95xx_H
#define cy8c95xx_H
 
/**
 * \file drivers/cy8c95xx.h
 * \ingroup drivers
 * \defgroup cy8c95xx
 *
 * Driver librarry to handle cy8c95xx port expander.
 * Based on MikroE Expand 6 Click Driver (copyright notice included)
 */
 
#include <stdio.h>
#include "cy8c95xx_config.h" /* External harware interface configuration */

#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup cy8c95xx
 */
enum cy8c95xx_error_code {
    cy8c95xx_OK = 0x00,
    cy8c95xx_INIT_ERROR = 0x01,
    cy8c95xx_I2C_ERROR = 0x02
};
 
/**
 * \brief Base addresses for comunications
 * \ingroup cy8c95xx
 */
#define cy8c95xx_M_PORT_BASE_ADR            0x20
#define cy8c95xx_EEPROM_BASE_ADR            0x50
#define cy8c95xx_DEV_ADR_GND                0x00
#define cy8c95xx_DEV_ADR_VCC                0x01
 
/**
 * \brief Register map
 * \ingroup cy8c95xx
 */
#define cy8c95xx_REG_IN_PORT0_ADR           0x00
#define cy8c95xx_REG_IN_PORT1_ADR           0x01
#define cy8c95xx_REG_IN_PORT2_ADR           0x02
#define cy8c95xx_REG_IN_PORT3_ADR           0x03
#define cy8c95xx_REG_IN_PORT4_ADR           0x04
#define cy8c95xx_REG_IN_PORT5_ADR           0x05
#define cy8c95xx_REG_IN_PORT6_ADR           0x06
#define cy8c95xx_REG_IN_PORT7_ADR           0x07
#define cy8c95xx_REG_OUT_PORT0_ADR          0x08
#define cy8c95xx_REG_OUT_PORT1_ADR          0x09
#define cy8c95xx_REG_OUT_PORT2_ADR          0x0A
#define cy8c95xx_REG_OUT_PORT3_ADR          0x0B
#define cy8c95xx_REG_OUT_PORT4_ADR          0x0C
#define cy8c95xx_REG_OUT_PORT5_ADR          0x0D
#define cy8c95xx_REG_OUT_PORT6_ADR          0x0E
#define cy8c95xx_REG_OUT_PORT7_ADR          0x0F
#define cy8c95xx_REG_INT_STAT_PORT0_ADR     0x10
#define cy8c95xx_REG_INT_STAT_PORT1_ADR     0x11
#define cy8c95xx_REG_INT_STAT_PORT2_ADR     0x12
#define cy8c95xx_REG_INT_STAT_PORT3_ADR     0x13
#define cy8c95xx_REG_INT_STAT_PORT4_ADR     0x14
#define cy8c95xx_REG_INT_STAT_PORT5_ADR     0x15
#define cy8c95xx_REG_INT_STAT_PORT6_ADR     0x16
#define cy8c95xx_REG_INT_STAT_PORT7_ADR     0x17
#define cy8c95xx_REG_PORT_SEL_ADR           0x18
#define cy8c95xx_REG_INT_MASK_ADR           0x19
#define cy8c95xx_REG_SEL_PWM_OUT_ADR        0x1A
#define cy8c95xx_REG_INV_ADR                0x1B
#define cy8c95xx_REG_PORT_DIR_ADR           0x1C
#define cy8c95xx_REG_PULL_UP_ADR            0x1D
#define cy8c95xx_REG_PULL_DOWN_ADR          0x1E
#define cy8c95xx_REG_OPEN_DRAIN_HIGH_ADR    0x1F
#define cy8c95xx_REG_OPEN_DRAIN_LOW_ADR     0x20
#define cy8c95xx_REG_STRONG_ADR             0x21
#define cy8c95xx_REG_SLOW_STRONG_ADR        0x22
#define cy8c95xx_REG_HIGH_Z_ADR             0x23
#define cy8c95xx_REG_RSRVD_1_ADR            0x24
#define cy8c95xx_REG_RSRVD_2_ADR            0x25
#define cy8c95xx_REG_RSRVD_3_ADR            0x26
#define cy8c95xx_REG_RSRVD_4_ADR            0x27
#define cy8c95xx_REG_PWM_SEL_ADR            0x28
#define cy8c95xx_REG_CFG_PWM_ADR            0x29
#define cy8c95xx_REG_PERIOD_PWM_ADR         0x2A
#define cy8c95xx_REG_PULSE_WIDTH_PWM_ADR    0x2B
#define cy8c95xx_REG_DIVIDER_ADR            0x2C
#define cy8c95xx_REG_EEPROM_ADR             0x2D
#define cy8c95xx_REG_DEV_ID_ADR             0x2E
#define cy8c95xx_REG_WDT_ADR                0x2F
#define cy8c95xx_REG_CMD_ADR                0x30
 
/**
 * \brief Select pwm output
 * \ingroup cy8c95xx
 */
#define cy8c95xx_SEL_PWM_0                  0x00
#define cy8c95xx_SEL_PWM_1                  0x01
#define cy8c95xx_SEL_PWM_2                  0x02
#define cy8c95xx_SEL_PWM_3                  0x03
 
/**
 * \brief Clock source for pwm
 * \ingroup cy8c95xx
 */
#define cy8c95xx_PWM_CLK_SRC_32_KHZ         0x00
#define cy8c95xx_PWM_CLK_SRC_24_MHZ         0x01
#define cy8c95xx_PWM_CLK_SRC_1_5_MHZ        0x02
#define cy8c95xx_PWM_CLK_SRC_93_75_KHZ      0x03
#define cy8c95xx_PWM_CLK_SRC_367_6_HZ       0x04
#define cy8c95xx_PWM_CLK_SRC_PREV           0x05
 
/**
 * \brief Available commands
 * \ingroup cy8c95xx
 */
#define cy8c95xx_STORE_POR_CFG_TO_EEPROM    0x01
#define cy8c95xx_RESTORE_DEFAULTS           0x02
#define cy8c95xx_WRITE_EEPROM_POR           0x03
#define cy8c95xx_READ_EEPROM_POR            0x04
#define cy8c95xx_WRITE_DEV_CFG              0x05
#define cy8c95xx_READ_DEV_CFG               0x06
#define cy8c95xx_RECFG_DEV_TO_POR           0x07
 
/**
 * \brief Enable registers
 * \ingroup cy8c95xx
 */
#define cy8c95xx_EEPROM_EN_WDE              0x01
#define cy8c95xx_EEPROM_EN_EEE              0x02
#define cy8c95xx_EEPROM_EN_EERO             0x04
 
/**
 * \brief Port select
 * \ingroup cy8c95xx
 */
#define cy8c95xx_PORT_0                     0x00
#define cy8c95xx_PORT_1                     0x01
#define cy8c95xx_PORT_2                     0x02
 
/**
 * \brief Pin states
 * \ingroup cy8c95xx
 */
#define cy8c95xx_LOW                        0x00
#define cy8c95xx_HIGH                       0x01
#define cy8c95xx_INT_NORMAL                 0x00
#define cy8c95xx_INT_INVERTED               0x01
 
/**
 * \brief Configuration offsets
 * \ingroup cy8c95xx
 */
#define cy8c95xx_PORT0_OUT_INX              0x00
#define cy8c95xx_PORT1_OUT_INX              0x01
#define cy8c95xx_PORT2_OUT_INX              0x02
#define cy8c95xx_PORT3_OUT_INX              0x03
#define cy8c95xx_PORT4_OUT_INX              0x04
#define cy8c95xx_PORT5_OUT_INX              0x05
#define cy8c95xx_PORT6_OUT_INX              0x06
#define cy8c95xx_PORT7_OUT_INX              0x07

#define cy8c95xx_PORT0_INT_MASK_INX         0x08
#define cy8c95xx_PORT1_INT_MASK_INX         0x09
#define cy8c95xx_PORT2_INT_MASK_INX         0x0A
#define cy8c95xx_PORT3_INT_MASK_INX         0x0B
#define cy8c95xx_PORT4_INT_MASK_INX         0x0C
#define cy8c95xx_PORT5_INT_MASK_INX         0x0D
#define cy8c95xx_PORT6_INT_MASK_INX         0x0E
#define cy8c95xx_PORT7_INT_MASK_INX         0x0F

#define cy8c95xx_PORT0_SEL_PWM_INX          0x10
#define cy8c95xx_PORT1_SEL_PWM_INX          0x11
#define cy8c95xx_PORT2_SEL_PWM_INX          0x12
#define cy8c95xx_PORT3_SEL_PWM_INX          0x13
#define cy8c95xx_PORT4_SEL_PWM_INX          0x14
#define cy8c95xx_PORT5_SEL_PWM_INX          0x15
#define cy8c95xx_PORT6_SEL_PWM_INX          0x16
#define cy8c95xx_PORT7_SEL_PWM_INX          0x17

#define cy8c95xx_PORT0_INV_INX              0x18
#define cy8c95xx_PORT1_INV_INX              0x19
#define cy8c95xx_PORT2_INV_INX              0x1A
#define cy8c95xx_PORT3_INV_INX              0x1B
#define cy8c95xx_PORT4_INV_INX              0x1C
#define cy8c95xx_PORT5_INV_INX              0x1D
#define cy8c95xx_PORT6_INV_INX              0x1E
#define cy8c95xx_PORT7_INV_INX              0x1F

#define cy8c95xx_PORT0_DIR_INX              0x20
#define cy8c95xx_PORT1_DIR_INX              0x21
#define cy8c95xx_PORT2_DIR_INX              0x22
#define cy8c95xx_PORT3_DIR_INX              0x23
#define cy8c95xx_PORT4_DIR_INX              0x24
#define cy8c95xx_PORT5_DIR_INX              0x25
#define cy8c95xx_PORT6_DIR_INX              0x26
#define cy8c95xx_PORT7_DIR_INX              0x27

#define cy8c95xx_PORT0_PULL_UP_INX          0x28
#define cy8c95xx_PORT0_PULL_DOWN_INX        0x29
#define cy8c95xx_PORT0_OPEN_DRAIN_HIGH_INX  0x2A
#define cy8c95xx_PORT0_OPEN_DRAIN_LOW_INX   0x2B
#define cy8c95xx_PORT0_STRONG_INX           0x2C
#define cy8c95xx_PORT0_SLOW_STRONG_INX      0x2D
#define cy8c95xx_PORT0_HIGH_Z_INX           0x2E
#define cy8c95xx_PORT1_PULL_UP_INX          0x2F
#define cy8c95xx_PORT1_PULL_DOWN_INX        0x30
#define cy8c95xx_PORT1_OPEN_DRAIN_HIGH_INX  0x31
#define cy8c95xx_PORT1_OPEN_DRAIN_LOW_INX   0x32
#define cy8c95xx_PORT1_STRONG_INX           0x33
#define cy8c95xx_PORT1_SLOW_STRONG_INX      0x34
#define cy8c95xx_PORT1_HIGH_Z_INX           0x35
#define cy8c95xx_PORT2_PULL_UP_INX          0x36
#define cy8c95xx_PORT2_PULL_DOWN_INX        0x37
#define cy8c95xx_PORT2_OPEN_DRAIN_HIGH_INX  0x38
#define cy8c95xx_PORT2_OPEN_DRAIN_LOW_INX   0x39
#define cy8c95xx_PORT2_STRONG_INX           0x3A
#define cy8c95xx_PORT2_SLOW_STRONG_INX      0x3B
#define cy8c95xx_PORT2_HIGH_Z_INX           0x3C
#define cy8c95xx_PORT3_PULL_UP_INX          0x3D
#define cy8c95xx_PORT3_PULL_DOWN_INX        0x3E
#define cy8c95xx_PORT3_OPEN_DRAIN_HIGH_INX  0x3F
#define cy8c95xx_PORT3_OPEN_DRAIN_LOW_INX   0x40
#define cy8c95xx_PORT3_STRONG_INX           0x41
#define cy8c95xx_PORT3_SLOW_STRONG_INX      0x42
#define cy8c95xx_PORT3_HIGH_Z_INX           0x43
#define cy8c95xx_PORT4_PULL_UP_INX          0x44
#define cy8c95xx_PORT4_PULL_DOWN_INX        0x45
#define cy8c95xx_PORT4_OPEN_DRAIN_HIGH_INX  0x46
#define cy8c95xx_PORT4_OPEN_DRAIN_LOW_INX   0x47
#define cy8c95xx_PORT4_STRONG_INX           0x48
#define cy8c95xx_PORT4_SLOW_STRONG_INX      0x49
#define cy8c95xx_PORT4_HIGH_Z_INX           0x4A
#define cy8c95xx_PORT5_PULL_UP_INX          0x4B
#define cy8c95xx_PORT5_PULL_DOWN_INX        0x4C
#define cy8c95xx_PORT5_OPEN_DRAIN_HIGH_INX  0x4D
#define cy8c95xx_PORT5_OPEN_DRAIN_LOW_INX   0x4E
#define cy8c95xx_PORT5_STRONG_INX           0x4F
#define cy8c95xx_PORT5_SLOW_STRONG_INX      0x50
#define cy8c95xx_PORT5_HIGH_Z_INX           0x51
#define cy8c95xx_PORT6_PULL_UP_INX          0x52
#define cy8c95xx_PORT6_PULL_DOWN_INX        0x53
#define cy8c95xx_PORT6_OPEN_DRAIN_HIGH_INX  0x54
#define cy8c95xx_PORT6_OPEN_DRAIN_LOW_INX   0x55
#define cy8c95xx_PORT6_STRONG_INX           0x56
#define cy8c95xx_PORT6_SLOW_STRONG_INX      0x57
#define cy8c95xx_PORT6_HIGH_Z_INX           0x58
#define cy8c95xx_PORT7_PULL_UP_INX          0x59
#define cy8c95xx_PORT7_PULL_DOWN_INX        0x5A
#define cy8c95xx_PORT7_OPEN_DRAIN_HIGH_INX  0x5B
#define cy8c95xx_PORT7_OPEN_DRAIN_LOW_INX   0x5C
#define cy8c95xx_PORT7_STRONG_INX           0x5D
#define cy8c95xx_PORT7_SLOW_STRONG_INX      0x5E
#define cy8c95xx_PORT7_HIGH_Z_INX           0x5F

#define cy8c95xx_PWM0_CFG_INX               0x60
#define cy8c95xx_PWM0_PERIOD_INX            0x61
#define cy8c95xx_PWM0_PULSE_WIDTH_INX       0x62
#define cy8c95xx_PWM1_CFG_INX               0x63
#define cy8c95xx_PWM1_PERIOD_INX            0x64
#define cy8c95xx_PWM1_PULSE_WIDTH_INX       0x65
#define cy8c95xx_PWM2_CFG_INX               0x66
#define cy8c95xx_PWM2_PERIOD_INX            0x67
#define cy8c95xx_PWM2_PULSE_WIDTH_INX       0x68
#define cy8c95xx_PWM3_CFG_INX               0x69
#define cy8c95xx_PWM3_PERIOD_INX            0x6A
#define cy8c95xx_PWM3_PULSE_WIDTH_INX       0x6B
#define cy8c95xx_PWM4_CFG_INX               0x6C
#define cy8c95xx_PWM4_PERIOD_INX            0x6D
#define cy8c95xx_PWM4_PULSE_WIDTH_INX       0x6E
#define cy8c95xx_PWM5_CFG_INX               0x6F
#define cy8c95xx_PWM5_PERIOD_INX            0x70
#define cy8c95xx_PWM5_PULSE_WIDTH_INX       0x71
#define cy8c95xx_PWM6_CFG_INX               0x72
#define cy8c95xx_PWM6_PERIOD_INX            0x73
#define cy8c95xx_PWM6_PULSE_WIDTH_INX       0x74
#define cy8c95xx_PWM7_CFG_INX               0x75
#define cy8c95xx_PWM7_PERIOD_INX            0x76
#define cy8c95xx_PWM7_PULSE_WIDTH_INX       0x77
#define cy8c95xx_PWM8_CFG_INX               0x78
#define cy8c95xx_PWM8_PERIOD_INX            0x79
#define cy8c95xx_PWM8_PULSE_WIDTH_INX       0x7A
#define cy8c95xx_PWM9_CFG_INX               0x7B
#define cy8c95xx_PWM9_PERIOD_INX            0x7C
#define cy8c95xx_PWM9_PULSE_WIDTH_INX       0x7D
#define cy8c95xx_PWM10_CFG_INX              0x7E
#define cy8c95xx_PWM10_PERIOD_INX           0x7F
#define cy8c95xx_PWM10_PULSE_WIDTH_INX      0x80
#define cy8c95xx_PWM11_CFG_INX              0x81
#define cy8c95xx_PWM11_PERIOD_INX           0x82
#define cy8c95xx_PWM11_PULSE_WIDTH_INX      0x83
#define cy8c95xx_PWM12_CFG_INX              0x84
#define cy8c95xx_PWM12_PERIOD_INX           0x85
#define cy8c95xx_PWM12_PULSE_WIDTH_INX      0x86
#define cy8c95xx_PWM13_CFG_INX              0x87
#define cy8c95xx_PWM13_PERIOD_INX           0x88
#define cy8c95xx_PWM13_PULSE_WIDTH_INX      0x89
#define cy8c95xx_PWM14_CFG_INX              0x8A
#define cy8c95xx_PWM14_PERIOD_INX           0x8B
#define cy8c95xx_PWM14_PULSE_WIDTH_INX      0x8C
#define cy8c95xx_PWM15_CFG_INX              0x8D
#define cy8c95xx_PWM15_PERIOD_INX           0x8E
#define cy8c95xx_PWM15_PULSE_WIDTH_INX      0x8F

#define cy8c95xx_DIVIDER_INX                0x90
#define cy8c95xx_EEPROM_ENABLE_INX          0x91
#define cy8c95xx_CRC_INX                    0x92

/**
 * \brief Object to store port expander initial config
 * \ingroup cy8c95xx
 */
typedef struct {
    int scl_pin;
    int sda_pin;
    int rst_pin;
    int int_pin;
    hw_i2c_t* i2c;
    uint i2c_speed;
    uint8_t i2c_addr;
} cy8c95xx_cfg_t;
 
/**
 * \brief Port expander instance
 * \ingroup cy8c95xx
 */
typedef struct
{
    int rst_pin;
    int int_pin;
    hw_i2c_t* i2c;
    uint8_t slave_addr;
} cy8c95xx_t;
 
/**
 * \brief Object to store pwm config
 * \ingroup cy8c95xx
 */
typedef struct
{
    uint8_t pwm_sel;
    uint8_t clk_src;
    uint8_t period;
    uint8_t pulse_wid;
    uint8_t devider;
} cy8c95xx_pwm_cfg_t;
 
/*!
 * \brief Initializes all necessary pins and peripherals used by expander object
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param cfg Click configuration structure
 * \return cy8c95xx_INIT_ERROR : error
 *         cy8c95xx_OK : successful
 */
int cy8c95xx_init(cy8c95xx_t *exp, cy8c95xx_cfg_t *cfg);
 
/*!
 * \brief Writes data to register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg Register address
 * \param data_buf Data buf to be written
 * \param len Number of the bytes in data buf
 */
void cy8c95xx_generic_write(cy8c95xx_t *exp, uint8_t reg, uint8_t *data_buf, uint8_t len);
 
/*!
 * \brief Reads data from register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg Register address
 * \param data_buf Output data buf
 * \param len Number of the bytes to be read
 */
void cy8c95xx_generic_read(cy8c95xx_t *exp, uint8_t reg, uint8_t *data_buf, uint8_t len);
 
/*!
 * \brief Write single byte of data to register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg_adr 8-bit value that defines the register
 * \param wr_data 8-bit value that defines the input data
 */
void cy8c95xx_write_byte(cy8c95xx_t *exp, uint8_t reg_adr, uint8_t wr_data);
 
/*!
 * \brief Read single byte of data fromregister
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg_adr 8-bit value that defines the register
 * \return rx_buf 8-bit value that defines the output data
 */
uint8_t cy8c95xx_read_byte(cy8c95xx_t *exp, uint8_t reg_adr);
 
/*!
 * \brief Writes number of bytes into register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg 8-bit register address
 * \param buf 8-bit write data
 * \param len 8-bit number of bytes
 */
void cy8c95xx_write_port_exp(cy8c95xx_t *exp, uint8_t reg, uint8_t *buf, uint8_t len);
 
/*!
 * \brief Reads number of bytes from register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg 8-bit register address
 * \param buf 8-bit read data
 * \param len 8-bit number of bytes
 */
void cy8c95xx_read_port_exp(cy8c95xx_t *exp, uint8_t reg, uint8_t *buf, uint8_t len);
 
/*!
 * \brief Send EEPROM comand
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param cmd 8-bit value that defines the command
 */
void cy8c95xx_send_eeprom_cmd(cy8c95xx_t *exp, uint8_t cmd);
 
/*!
 * \brief Writes number of bytes into EEPROM
 *
 * \param exp Port expander instance
 * \param reg 8-bit register address
 * \param wr_data 8-bit write data
 * \param len 8-bit number of bytes
 */
void cy8c95xx_write_eeprom(cy8c95xx_t *exp, uint16_t mem_adr, uint8_t *buf, uint8_t len);
 
/*!
 * \brief Reads number of bytes from EEPROM
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg 8-bit register address
 * \param buf 8-bit read data
 * \param len 8-bit number of bytes
 */
void cy8c95xx_read_eeprom(cy8c95xx_t *exp, uint16_t mem_adr, uint8_t *buf, uint8_t len);
 
/*!
 * \brief Read state of a single bit from register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg_adr 8-bit value that defines the register
 * \param bit_num 8-bit value that defines the specific bit
 * \return 8-bit value that represents the specific bit value
 */
uint8_t cy8c95xx_read_bit(cy8c95xx_t *exp, uint8_t reg_adr, uint8_t bit_num);
 
/*!
 * \brief Set or Clear specific bit in selected register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param reg_adr 8-bit value that defines the register
 * \param bit_num 8-bit value that defines the specific bit
 * \param bit_val 8-bit value that defines the specific bit value
 */
void cy8c95xx_write_bit(cy8c95xx_t* exp, uint8_t reg_adr, uint8_t bit_num, uint8_t bit_val);
 
/*!
 * \brief Get a single INPUT pin logic level
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param pin 16-bit value that defines the specific pin
 * \return 8-bit value that represents the specific pin state
 */
uint8_t cy8c95xx_read_pin(cy8c95xx_t *exp, uint16_t pin, uint8_t inv);
 
/*!
 * \brief Get all pin logic levels from port
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param port 8-bit value that defines the port
 * \return 8-bit value that represents the states of pins in selected port
 */
uint8_t cy8c95xx_read_port(cy8c95xx_t *exp, uint8_t port, uint8_t inv);
 
/*!
 * \brief Get a single OUTPUT pin setting
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param pin 16-bit value that defines the specific pin
 * \return Pin output setting (0 or 1)
 */
uint8_t cy8c95xx_get_pin_out_lvl(cy8c95xx_t *exp, uint16_t pin);
 
/*!
 * \brief Get all pin output settings from port
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param port 8-bit value that defines the port
 * \return Pin output setting (0 or 1)
 */
uint8_t cy8c95xx_get_port_out_lvl(cy8c95xx_t *exp, uint8_t port);
 
/*!
 * \brief Set a single OUTPUT pin logic level
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param pin 8-bit value that defines the specific pin
 * \param pin_val 8-bit value that defines the specific pin value 
 */
void cy8c95xx_write_pin(cy8c95xx_t *exp, uint16_t pin, uint8_t pin_val);
 
/*!
 * \brief Set all OUTPUT pins logic levels in one port
 *
 * \param exp Port expander instance
 * \param port 8-bit value that defines which port to write to
 * \param value 8-bit value that defines pins' output logic level (0 or 1)
 */
void cy8c95xx_write_port(cy8c95xx_t *exp, uint8_t port, uint8_t value);
 
/*!
 * \brief Enable or disable PWM output on pin
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param port 8-bit value that defines PWM output pin
 * \param value 8-bit value that enables or disables PWM output (0 or 1)
 */
void cy8c95xx_sel_pwm_pin(cy8c95xx_t *exp, uint16_t pin, uint8_t pwm_en);
 
/*!
 * \brief Configure pwm output
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param pwm_cfg cy8c95xx_pwm_cfg_t pwm Configuration structure
 * \param duty_cyc float value representing pwm duty cycle
 * \param freq float value representing output frequency
 */
void cy8c95xx_pwm_cfg(cy8c95xx_t *exp, cy8c95xx_pwm_cfg_t pwm_cfg, float *duty_cyc, float *freq);
 
/*!
 * \brief Configures EEPROM enable register
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \param cmd value that represents input data to Enable Register
 * \note Writes to this register differ from other registers, see datasheet
 */
void cy8c95xx_eeprom_enable(cy8c95xx_t *exp, uint8_t cmd);
 
/************************************************************************************
* External hardware interfase API
************************************************************************************/
/*!
 * \brief Initializes default configuration
 * \ingroup cy8c95xx
 *
 * \param cfg Port expander initail configuration
 */
void cy8c95xx_set_default_cfg(cy8c95xx_cfg_t* cfg);
 
/*!
 * \brief Init hardware according to configuration
 * \ingroup cy8c95xx
 *
 * \param cfg Port expander initail configuration
 * \return cy8c95xx_INIT_ERROR : error
 *         cy8c95xx_OK : successful
 */
int cy8c95xx_hw_init(cy8c95xx_cfg_t* cfg);
 
/*!
 * \brief Reset port expander using rst_pin
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \note Functon holds two 100 ms reset delays
 */
void cy8c95xx_reset(cy8c95xx_t* exp);
 
/*!
 * \brief Check interrupt by reading int_pin level
 * \ingroup cy8c95xx
 *
 * \param exp Port expander instance
 * \return 0 : Interrupt has not occured
 *         1 : Interrupt has occured
 */
uint8_t cy8c95xx_check_int(cy8c95xx_t* exp);

/*!
 * \brief Attempt to read specified number of bytes from address over i2c
 * \ingroup cy8c95xx
 *
 * \param i2c hw_i2c_t i2c interfase
 * \param addr 7-bit address of device to read from
 * \param rxdata Pointer to buffer to receive data
 * \param len Length of data in bytes to receive
 * \return cy8c95xx_I2C_ERROR : error
 *         cy8c95xx_OK : successful
 */
int cy8c95xx_i2c_read(hw_i2c_t* i2c, uint8_t addr, uint8_t* rxdata, size_t len);

/*!
 * \brief Attempt to write specified number of bytes to address over i2c
 * \ingroup cy8c95xx
 *
 * \param i2c hw_i2c_t i2c interfase
 * \param addr 7-bit address of device to write to
 * \param txdata Pointer to data to send
 * \param len Length of data in bytes to send
 * \return cy8c95xx_I2C_ERROR : error
 *         cy8c95xx_OK : successful
 */
int cy8c95xx_i2c_write(hw_i2c_t* i2c, uint8_t addr, const uint8_t* txdata, size_t len);

#ifdef __cplusplus
}
#endif
#endif  // _cy8c95xx_H_
