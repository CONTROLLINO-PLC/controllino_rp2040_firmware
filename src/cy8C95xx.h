/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 * Copyright© 2020 MikroElektronika d.o.o.
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * \file driver/cy8C95xx.h
 * \ingroup drivers
 * \defgroup cy8C95xx
 *
 * Driver librarry to handle cy8C95xx port expander.
 * Based on MikroE Expand 6 Click Driver (copyright notice included)
 */
 
#ifndef CY8C95XX_H
#define CY8C95XX_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup cy8C95xx
 */
enum cy8C95xx_error_code {
    CY8C95XX_OK = 0x00,
    CY8C95XX_INIT_ERROR = 0x01
}; 
 
/**
 * \brief Base addresses for comunications
 * \ingroup cy8C95xx
 */
#define CY8C95XX_M_PORT_BASE_ADR            0x20
#define CY8C95XX_EEPROM_BASE_ADR            0x50
#define CY8C95XX_DEV_ADR_GND                0x00
#define CY8C95XX_DEV_ADR_VCC                0x01
 
/**
 * \brief Register map
 * \ingroup cy8C95xx
 */
#define CY8C95XX_REG_IN_PORT0_ADR           0x00
#define CY8C95XX_REG_IN_PORT1_ADR           0x01
#define CY8C95XX_REG_IN_PORT2_ADR           0x02
#define CY8C95XX_REG_IN_PORT3_ADR           0x03
#define CY8C95XX_REG_IN_PORT4_ADR           0x04
#define CY8C95XX_REG_IN_PORT5_ADR           0x05
#define CY8C95XX_REG_IN_PORT6_ADR           0x06
#define CY8C95XX_REG_IN_PORT7_ADR           0x07
#define CY8C95XX_REG_OUT_PORT0_ADR          0x08
#define CY8C95XX_REG_OUT_PORT1_ADR          0x09
#define CY8C95XX_REG_OUT_PORT2_ADR          0x0A
#define CY8C95XX_REG_OUT_PORT3_ADR          0x0B
#define CY8C95XX_REG_OUT_PORT4_ADR          0x0C
#define CY8C95XX_REG_OUT_PORT5_ADR          0x0D
#define CY8C95XX_REG_OUT_PORT6_ADR          0x0E
#define CY8C95XX_REG_OUT_PORT7_ADR          0x0F
#define CY8C95XX_REG_INT_STAT_PORT0_ADR     0x10
#define CY8C95XX_REG_INT_STAT_PORT1_ADR     0x11
#define CY8C95XX_REG_INT_STAT_PORT2_ADR     0x12
#define CY8C95XX_REG_INT_STAT_PORT3_ADR     0x13
#define CY8C95XX_REG_INT_STAT_PORT4_ADR     0x14
#define CY8C95XX_REG_INT_STAT_PORT5_ADR     0x15
#define CY8C95XX_REG_INT_STAT_PORT6_ADR     0x16
#define CY8C95XX_REG_INT_STAT_PORT7_ADR     0x17
#define CY8C95XX_REG_PORT_SEL_ADR           0x18
#define CY8C95XX_REG_INT_MASK_ADR           0x19
#define CY8C95XX_REG_SEL_PWM_OUT_ADR        0x1A
#define CY8C95XX_REG_INV_ADR                0x1B
#define CY8C95XX_REG_PORT_DIR_ADR           0x1C
#define CY8C95XX_REG_PULL_UP_ADR            0x1D
#define CY8C95XX_REG_PULL_DOWN_ADR          0x1E
#define CY8C95XX_REG_OPEN_DRAIN_HIGH_ADR    0x1F
#define CY8C95XX_REG_OPEN_DRAIN_LOW_ADR     0x20
#define CY8C95XX_REG_STRONG_ADR             0x21
#define CY8C95XX_REG_SLOW_STRONG_ADR        0x22
#define CY8C95XX_REG_HIGH_Z_ADR             0x23
#define CY8C95XX_REG_RSRVD_1_ADR            0x24
#define CY8C95XX_REG_RSRVD_2_ADR            0x25
#define CY8C95XX_REG_RSRVD_3_ADR            0x26
#define CY8C95XX_REG_RSRVD_4_ADR            0x27
#define CY8C95XX_REG_PWM_SEL_ADR            0x28
#define CY8C95XX_REG_CFG_PWM_ADR            0x29
#define CY8C95XX_REG_PERIOD_PWM_ADR         0x2A
#define CY8C95XX_REG_PULSE_WIDTH_PWM_ADR    0x2B
#define CY8C95XX_REG_DIVIDER_ADR            0x2C
#define CY8C95XX_REG_EEPROM_ADR             0x2D
#define CY8C95XX_REG_DEV_ID_ADR             0x2E
#define CY8C95XX_REG_WDT_ADR                0x2F
#define CY8C95XX_REG_CMD_ADR                0x30
 
/**
 * \brief Pwm select
 * \ingroup cy8C95xx
 */
#define CY8C95XX_SEL_PWM_0                  0x00
#define CY8C95XX_SEL_PWM_1                  0x01
#define CY8C95XX_SEL_PWM_2                  0x02
#define CY8C95XX_SEL_PWM_3                  0x03
 
/**
 * \brief Pwm clock source
 * \ingroup cy8C95xx
 */
#define CY8C95XX_PWM_CLK_SRC_32_KHZ         0x00
#define CY8C95XX_PWM_CLK_SRC_24_MHZ         0x01
#define CY8C95XX_PWM_CLK_SRC_1_5_MHZ        0x02
#define CY8C95XX_PWM_CLK_SRC_93_75_KHZ      0x03
#define CY8C95XX_PWM_CLK_SRC_367_6_HZ       0x04
#define CY8C95XX_PWM_CLK_SRC_PREV           0x05
 
/**
 * \brief Pwm clock source
 * \ingroup cy8C95xx
 */
#define CY8C95XX_STORE_POR_CFG_TO_EEPROM    0x01
#define CY8C95XX_RESTORE_DEFAULTS           0x02
#define CY8C95XX_WRITE_EEPROM_POR           0x03
#define CY8C95XX_READ_EEPROM_POR            0x04
#define CY8C95XX_WRITE_DEV_CFG              0x05
#define CY8C95XX_READ_DEV_CFG               0x06
#define CY8C95XX_RECFG_DEV_TO_POR           0x07
 
/**
 * \brief Enable registers
 * \ingroup cy8C95xx
 */
#define CY8C95XX_EEPROM_EN_WDE              0x01
#define CY8C95XX_EEPROM_EN_EEE              0x02
#define CY8C95XX_EEPROM_EN_EERO             0x04
 
/**
 * \brief Port select
 * \ingroup cy8C95xx
 */
#define CY8C95XX_PORT_0                     0x00
#define CY8C95XX_PORT_1                     0x01
#define CY8C95XX_PORT_2                     0x02
 
/**
 * \brief Pin states
 * \ingroup cy8C95xx
 */
#define CY8C95XX_LOW                        0x00
#define CY8C95XX_HIGH                       0x01
#define CY8C95XX_INT_NORMAL                 0x00
#define CY8C95XX_INT_INVERTED               0x01
 
/**
 * \brief Configure data structure offsets
 * \ingroup cy8C95xx
 */
#define CY8C95XX_PORT0_OUT_INX              0x00
#define CY8C95XX_PORT1_OUT_INX              0x01
#define CY8C95XX_PORT2_OUT_INX              0x02
#define CY8C95XX_PORT3_OUT_INX              0x03
#define CY8C95XX_PORT4_OUT_INX              0x04
#define CY8C95XX_PORT5_OUT_INX              0x05
#define CY8C95XX_PORT6_OUT_INX              0x06
#define CY8C95XX_PORT7_OUT_INX              0x07

#define CY8C95XX_PORT0_INT_MASK_INX         0x08
#define CY8C95XX_PORT1_INT_MASK_INX         0x09
#define CY8C95XX_PORT2_INT_MASK_INX         0x0A
#define CY8C95XX_PORT3_INT_MASK_INX         0x0B
#define CY8C95XX_PORT4_INT_MASK_INX         0x0C
#define CY8C95XX_PORT5_INT_MASK_INX         0x0D
#define CY8C95XX_PORT6_INT_MASK_INX         0x0E
#define CY8C95XX_PORT7_INT_MASK_INX         0x0F

#define CY8C95XX_PORT0_SEL_PWM_INX          0x10
#define CY8C95XX_PORT1_SEL_PWM_INX          0x11
#define CY8C95XX_PORT2_SEL_PWM_INX          0x12
#define CY8C95XX_PORT3_SEL_PWM_INX          0x13
#define CY8C95XX_PORT4_SEL_PWM_INX          0x14
#define CY8C95XX_PORT5_SEL_PWM_INX          0x15
#define CY8C95XX_PORT6_SEL_PWM_INX          0x16
#define CY8C95XX_PORT7_SEL_PWM_INX          0x17

#define CY8C95XX_PORT0_INV_INX              0x18
#define CY8C95XX_PORT1_INV_INX              0x19
#define CY8C95XX_PORT2_INV_INX              0x1A
#define CY8C95XX_PORT3_INV_INX              0x1B
#define CY8C95XX_PORT4_INV_INX              0x1C
#define CY8C95XX_PORT5_INV_INX              0x1D
#define CY8C95XX_PORT6_INV_INX              0x1E
#define CY8C95XX_PORT7_INV_INX              0x1F

#define CY8C95XX_PORT0_DIR_INX              0x20
#define CY8C95XX_PORT1_DIR_INX              0x21
#define CY8C95XX_PORT2_DIR_INX              0x22
#define CY8C95XX_PORT3_DIR_INX              0x23
#define CY8C95XX_PORT4_DIR_INX              0x24
#define CY8C95XX_PORT5_DIR_INX              0x25
#define CY8C95XX_PORT6_DIR_INX              0x26
#define CY8C95XX_PORT7_DIR_INX              0x27

#define CY8C95XX_PORT0_PULL_UP_INX          0x28
#define CY8C95XX_PORT0_PULL_DOWN_INX        0x29
#define CY8C95XX_PORT0_OPEN_DRAIN_HIGH_INX  0x2A
#define CY8C95XX_PORT0_OPEN_DRAIN_LOW_INX   0x2B
#define CY8C95XX_PORT0_STRONG_INX           0x2C
#define CY8C95XX_PORT0_SLOW_STRONG_INX      0x2D
#define CY8C95XX_PORT0_HIGH_Z_INX           0x2E

#define CY8C95XX_PORT1_PULL_UP_INX          0x2F
#define CY8C95XX_PORT1_PULL_DOWN_INX        0x30
#define CY8C95XX_PORT1_OPEN_DRAIN_HIGH_INX  0x31
#define CY8C95XX_PORT1_OPEN_DRAIN_LOW_INX   0x32
#define CY8C95XX_PORT1_STRONG_INX           0x33
#define CY8C95XX_PORT1_SLOW_STRONG_INX      0x34
#define CY8C95XX_PORT1_HIGH_Z_INX           0x35

#define CY8C95XX_PORT2_PULL_UP_INX          0x36
#define CY8C95XX_PORT2_PULL_DOWN_INX        0x37
#define CY8C95XX_PORT2_OPEN_DRAIN_HIGH_INX  0x38
#define CY8C95XX_PORT2_OPEN_DRAIN_LOW_INX   0x39
#define CY8C95XX_PORT2_STRONG_INX           0x3A
#define CY8C95XX_PORT2_SLOW_STRONG_INX      0x3B
#define CY8C95XX_PORT2_HIGH_Z_INX           0x3C

#define CY8C95XX_PORT3_PULL_UP_INX          0x3D
#define CY8C95XX_PORT3_PULL_DOWN_INX        0x3E
#define CY8C95XX_PORT3_OPEN_DRAIN_HIGH_INX  0x3F
#define CY8C95XX_PORT3_OPEN_DRAIN_LOW_INX   0x40
#define CY8C95XX_PORT3_STRONG_INX           0x41
#define CY8C95XX_PORT3_SLOW_STRONG_INX      0x42
#define CY8C95XX_PORT3_HIGH_Z_INX           0x43

#define CY8C95XX_PORT4_PULL_UP_INX          0x44
#define CY8C95XX_PORT4_PULL_DOWN_INX        0x45
#define CY8C95XX_PORT4_OPEN_DRAIN_HIGH_INX  0x46
#define CY8C95XX_PORT4_OPEN_DRAIN_LOW_INX   0x47
#define CY8C95XX_PORT4_STRONG_INX           0x48
#define CY8C95XX_PORT4_SLOW_STRONG_INX      0x49
#define CY8C95XX_PORT4_HIGH_Z_INX           0x4A

#define CY8C95XX_PORT5_PULL_UP_INX          0x4B
#define CY8C95XX_PORT5_PULL_DOWN_INX        0x4C
#define CY8C95XX_PORT5_OPEN_DRAIN_HIGH_INX  0x4D
#define CY8C95XX_PORT5_OPEN_DRAIN_LOW_INX   0x4E
#define CY8C95XX_PORT5_STRONG_INX           0x4F
#define CY8C95XX_PORT5_SLOW_STRONG_INX      0x50
#define CY8C95XX_PORT5_HIGH_Z_INX           0x51

#define CY8C95XX_PORT6_PULL_UP_INX          0x52
#define CY8C95XX_PORT6_PULL_DOWN_INX        0x53
#define CY8C95XX_PORT6_OPEN_DRAIN_HIGH_INX  0x54
#define CY8C95XX_PORT6_OPEN_DRAIN_LOW_INX   0x55
#define CY8C95XX_PORT6_STRONG_INX           0x56
#define CY8C95XX_PORT6_SLOW_STRONG_INX      0x57
#define CY8C95XX_PORT6_HIGH_Z_INX           0x58

#define CY8C95XX_PORT7_PULL_UP_INX          0x59
#define CY8C95XX_PORT7_PULL_DOWN_INX        0x5A
#define CY8C95XX_PORT7_OPEN_DRAIN_HIGH_INX  0x5B
#define CY8C95XX_PORT7_OPEN_DRAIN_LOW_INX   0x5C
#define CY8C95XX_PORT7_STRONG_INX           0x5D
#define CY8C95XX_PORT7_SLOW_STRONG_INX      0x5E
#define CY8C95XX_PORT7_HIGH_Z_INX           0x5F

#define CY8C95XX_PWM0_CFG_INX               0x60
#define CY8C95XX_PWM0_PERIOD_INX            0x61
#define CY8C95XX_PWM0_PULSE_WIDTH_INX       0x62

#define CY8C95XX_PWM1_CFG_INX               0x63
#define CY8C95XX_PWM1_PERIOD_INX            0x64
#define CY8C95XX_PWM1_PULSE_WIDTH_INX       0x65

#define CY8C95XX_PWM2_CFG_INX               0x66
#define CY8C95XX_PWM2_PERIOD_INX            0x67
#define CY8C95XX_PWM2_PULSE_WIDTH_INX       0x68

#define CY8C95XX_PWM3_CFG_INX               0x69
#define CY8C95XX_PWM3_PERIOD_INX            0x6A
#define CY8C95XX_PWM3_PULSE_WIDTH_INX       0x6B

#define CY8C95XX_PWM4_CFG_INX               0x6C
#define CY8C95XX_PWM4_PERIOD_INX            0x6D
#define CY8C95XX_PWM4_PULSE_WIDTH_INX       0x6E

#define CY8C95XX_PWM5_CFG_INX               0x6F
#define CY8C95XX_PWM5_PERIOD_INX            0x70
#define CY8C95XX_PWM5_PULSE_WIDTH_INX       0x71

#define CY8C95XX_PWM6_CFG_INX               0x72
#define CY8C95XX_PWM6_PERIOD_INX            0x73
#define CY8C95XX_PWM6_PULSE_WIDTH_INX       0x74

#define CY8C95XX_PWM7_CFG_INX               0x75
#define CY8C95XX_PWM7_PERIOD_INX            0x76
#define CY8C95XX_PWM7_PULSE_WIDTH_INX       0x77

#define CY8C95XX_PWM8_CFG_INX               0x78
#define CY8C95XX_PWM8_PERIOD_INX            0x79
#define CY8C95XX_PWM8_PULSE_WIDTH_INX       0x7A

#define CY8C95XX_PWM9_CFG_INX               0x7B
#define CY8C95XX_PWM9_PERIOD_INX            0x7C
#define CY8C95XX_PWM9_PULSE_WIDTH_INX       0x7D

#define CY8C95XX_PWM10_CFG_INX              0x7E
#define CY8C95XX_PWM10_PERIOD_INX           0x7F
#define CY8C95XX_PWM10_PULSE_WIDTH_INX      0x80

#define CY8C95XX_PWM11_CFG_INX              0x81
#define CY8C95XX_PWM11_PERIOD_INX           0x82
#define CY8C95XX_PWM11_PULSE_WIDTH_INX      0x83

#define CY8C95XX_PWM12_CFG_INX              0x84
#define CY8C95XX_PWM12_PERIOD_INX           0x85
#define CY8C95XX_PWM12_PULSE_WIDTH_INX      0x86

#define CY8C95XX_PWM13_CFG_INX              0x87
#define CY8C95XX_PWM13_PERIOD_INX           0x88
#define CY8C95XX_PWM13_PULSE_WIDTH_INX      0x89

#define CY8C95XX_PWM14_CFG_INX              0x8A
#define CY8C95XX_PWM14_PERIOD_INX           0x8B
#define CY8C95XX_PWM14_PULSE_WIDTH_INX      0x8C

#define CY8C95XX_PWM15_CFG_INX              0x8D
#define CY8C95XX_PWM15_PERIOD_INX           0x8E
#define CY8C95XX_PWM15_PULSE_WIDTH_INX      0x8F

#define CY8C95XX_DIVIDER_INX                0x90
#define CY8C95XX_EEPROM_ENABLE_INX          0x91
#define CY8C95XX_CRC_INX                    0x92
 
/**
 * \brief PWM configuration
 * \ingroup cy8C95xx
 */
typedef struct
{
    uint8_t pwm_sel;
    uint8_t clk_src;
    uint8_t period;
    uint8_t pulse_wid;
    uint8_t devider;
} cy8C95xx_pwm_cfg_t;
 
/**
 * \brief Click ctx object definition.
 * \ingroup cy8C95xx
 */
typedef struct
{ 
    int rst_pin;
    int int_pin;
    i2c_inst_t* i2c;
    uint8_t slave_addr;
} cy8C95xx_t;
 
/**
 * \brief Click configuration structure definition.
 * \ingroup cy8C95xx
 */
typedef struct
{
    int scl_pin;
    int sda_pin;
    int rst_pin;
    int int_pin;
    i2c_inst_t* i2c;
    uint i2c_speed;
    uint8_t i2c_addr;
} cy8C95xx_cfg_t;
 
/*!
 * \brief Config Object Initialization function.
 * \ingroup cy8C95xx
 *
 * Initializes default configuration:
 * i2c: i2c0, sda:4, scl:5, i2c_speed: 100000, i2c_address: CY8C95XX_DEV_ADR_GND
 * rst: -1, int_pin: 15
 *
 * \param cfg  Click configuration structure.
 * \note The gpio will not be initialized, that happens in cy8C95xx_init().
 */
void cy8C95xx_cfg_default_setup(cy8C95xx_cfg_t *cfg);

/**
 * \brief Initialization function.
 * \ingroup cy8C95xx
 *
 * Initializes all necessary pins and peripherals used for this click.
 *
 * \param cy8C95xx Click object.
 * \param cfg Click configuration structure.
 */
uint cy8C95xx_init(cy8C95xx_t *ctx, cy8C95xx_cfg_t *cfg);

/**
 * \brief Generic write function.
 * \ingroup cy8C95xx
 *
 * Writes data to the desired register.
 *
 * \param ctx          Click object.
 * \param reg          Register address.
 * \param data_buf     Data buf to be written.
 * \param len          Number of the bytes in data buf.
 */
void cy8C95xx_generic_write ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * \brief Generic read function.
 * \ingroup cy8C95xx
 *
 * Reads data from the desired register.
 *
 * \param ctx          Click object.
 * \param reg          Register address.
 * \param data_buf     Output data buf
 * \param len          Number of the bytes to be read
 */
void cy8C95xx_generic_read ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * \brief Write byte function
 *
 * \param ctx          Click object.
 * \param reg_adr  8-bit value that defines the register
 * \param wr_data  8-bit value that defines the input data
 *
 * Function is used to write single byte of data into user defined register.
**/
void cy8C95xx_write_byte ( cy8C95xx_t *ctx, uint8_t reg_adr, uint8_t wr_data );

/**
 * \brief Read byte function
 *
 * \param ctx          Click object.
 * \param reg_adr  8-bit value that defines the register
 *
 * \returns rx_buf 8-bit value that defines the output data
 *
 * Function is used to read single byte of data from user defined register.
**/
uint8_t cy8C95xx_read_byte ( cy8C95xx_t *ctx, uint8_t reg_adr );

/**
 * \brief Port Expander Write function
 *
 * \param ctx          Click object.
 * \param reg  8-bit register address
 * \param buf  8-bit write data
 * \param len  8-bit number of bytes
 *
 * Writes user defined number of bytes into registers defined by 8-bit register
 * address
**/
void cy8C95xx_write_port_exp ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len );

/**
 * \brief Port Expander Read function
 *
 * \param ctx          Click object.
 * \param reg  8-bit register address
 * \param buf  8-bit read data
 * \param len  8-bit number of bytes
 *
 * Reads user defined number of bytes from registers defined by 8-bit register
 * address
**/
void cy8C95xx_read_port_exp ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len );

/**
 * \brief Send Command function
 *
 * \param ctx          Click object.
 * \param cmd  8-bit value that defines the command
 *
 * Function is used to send the command to Command Register.
**/
void cy8C95xx_send_eeprom_cmd ( cy8C95xx_t *ctx, uint8_t cmd );

/**
 * \brief EEPROM Write function
 *
 * \param ctx          Click object.
 * \param reg  8-bit register address
 * \param wr_data  8-bit write data
 * \param len  8-bit number of bytes
 *
 * Writes user defined number of bytes into EEPROM defined by 8-bit address
**/
void cy8C95xx_write_eeprom ( cy8C95xx_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len );

/**
 * \brief EEPROM Read function
 *
 * \param ctx          Click object.
 * \param reg  8-bit register address
 * \param buf  8-bit read data
 * \param len  8-bit number of bytes
 *
 * Reads user defined number of bytes from EEPROM defined by 8-bit address
**/
void cy8C95xx_read_eeprom ( cy8C95xx_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len );

/**
 * \brief Read bit function
 *
 * \param ctx          Click object.
 * \param reg_adr  8-bit value that defines the register
 * \param bit_num  8-bit value that defines the specific bit
 *
 * \returns 8-bit value that represents the specific bit's value
 *
 * Function is used to read state of a single bit of data from user defined register.
**/
uint8_t cy8C95xx_read_bit ( cy8C95xx_t *ctx, uint8_t reg_adr, uint8_t bit_num );

/**
 * \brief Write bit function
 *
 * \param ctx          Click object.
 * \param reg_adr  8-bit value that defines the register
 * \param bit_num  8-bit value that defines the specific bit
 * \param pin_val  8-bit value that defines the specific bit's value
 *
 * Function is used to set or clear the specific bit.
**/
void cy8C95xx_write_bit ( cy8C95xx_t *ctx, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val );

/**
 * \brief Get a single INPUT pin's logic level function
 *
 * \param ctx          Click object.
 * \param pin  16-bit value that defines the specific pin
 *
 * \returns 8-bit value that represents the specific pin's state
 *
 * Function is used to read the state of a defined pin.
**/
uint8_t cy8C95xx_read_pin ( cy8C95xx_t *ctx, uint16_t pin, uint8_t inv );

/**
 * \brief Get all pin logic levels from one port function
 *
 * \param ctx          Click object.
 * \param port 8-bit value that defines the port
 *
 * \returns 8-bit value that represents the states of pins in selected port.
 *
 * Function is used to read the states of pins in selected port.
**/
uint8_t cy8C95xx_read_port ( cy8C95xx_t *ctx, uint8_t port, uint8_t inv );

/**
 * \brief Get a single OUTPUT pin's setting function
 *
 * \param ctx          Click object.
 * \param pin  16-bit value that defines the specific pin
 *
 * \returns Pin output setting (0 or 1)
 *
 * Function is used to get a single OUTPUT pin's setting.
**/
uint8_t cy8C95xx_get_pin_out_lvl ( cy8C95xx_t *ctx, uint16_t pin );

/**
 * \brief Get all pin output settings from one port function
 *
 * \param ctx          Click object.
 * \param port 8-bit value that defines the port
 *
 * \returns Pin output setting (0 or 1)
 *
 * Function is used to get all pin output settings from one port.
**/
uint8_t cy8C95xx_get_port_out_lvl ( cy8C95xx_t *ctx, uint8_t port );

/**
 * \brief Set a single OUTPUT pin's logic level function
 *
 * \param ctx          Click object.
 * \param pin 8-bit value that defines the specific pin
 * \param pin_val 8-bit value that defines the specific pin's value
 *
 * Function is used to set a single output pin's logic level.
**/
void cy8C95xx_write_pin ( cy8C95xx_t *ctx, uint16_t pin, uint8_t pin_val );

/**
 * \brief Set all OUTPUT pins' logic levels in one port function
 *
 * \param ctx          Click object.
 * \param port  8-bit value that defines which port to write to.
 * \param value  8-bit value that defines pins' output logic level (0 or 1 for each pin).
 *
 * Function is used to set logic levels in one port.
**/
void cy8C95xx_write_port ( cy8C95xx_t *ctx, uint8_t port, uint8_t value );

/**
 * \brief Select a PWM output pin function
 *
 * \param ctx          Click object.
 * \param port  8-bit value that defines PWM output pin.
 * \param value  8-bit value that enables or disables PWM output (0 or 1 for each pin).
 *
 * Function is used to enable or disable PWM output on a specific pin.
**/
void cy8C95xx_sel_pwm_pin ( cy8C95xx_t *ctx, uint16_t pin, uint8_t pwm_en );

/**
 * \brief PWM Configuration function
 *
 * \param ctx          Click object.
 * \param cy8C95xx_pwm_cfg_t  structure where PWM Configuration data are stored.
 * \param duty_cyc  float value representing PWM duty cycle
 * \param freq  float value representing output frequency
 *
 * Function is used to configure PWM output.
**/
void cy8C95xx_pwm_cfg ( cy8C95xx_t *ctx, cy8C95xx_pwm_cfg_t pwm_cfg, float *duty_cyc, float *freq );

/**
 * \brief Enable Register Configuration function
 *
 * \param ctx          Click object.
 * \param cmd value that represents input data to Enable Register
 *
 * Function is used to write to Enable Register.
 * \note Writes to this register differ from other registers, 
 * consult datasheet for further information.
**/
void cy8C95xx_eeprom_enable ( cy8C95xx_t *ctx, uint8_t cmd );

/**
 * \brief Reset function
 *
 * \param ctx          Click object.
 * 
 * Function is used to reset the device.
 * \note Functon holds two 100 ms reset delays.
**/
void cy8C95xx_reset ( cy8C95xx_t *ctx );

/**
 * \brief Get Interrupt state function
 *
 * \param ctx          Click object.
 * 
 * \return
 * - 0 : Interrupt has not occured
 * - 1 : Interrupt has occured
 *
 * Function is used to check if an interrupt has occured.
**/
uint8_t cy8C95xx_check_int ( cy8C95xx_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CY8C95XX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! \} */
// ------------------------------------------------------------------------- END
