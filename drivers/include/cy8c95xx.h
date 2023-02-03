/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef CY8C95XX_H
#define CY8C95XX_H
 
/**
 * \file cy8c95xx.h
 * \ingroup drivers
 * \defgroup cy8c95xx
 *
 * Driver librarry to handle cy8c95xx port expander.
 * Based on MikroE Expand 6 Click Driver (Copyright© 2020 MikroElektronika d.o.o.)
 */
 
#include <stdio.h>
#include "hw_platform.h" /* External harware interface library */
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup cy8c95xx
 */
typedef enum 
{
    CY8C95XX_OK =         PLATFORM_OK,
    CY8C95XX_ARG_ERR =  PLATFORM_ARGUMENT_ERR,
    CY8C95XX_INIT_ERR = PLATFORM_I2C_INIT_ERR,
    CY8C95XX_I2C_ERR =  PLATFORM_I2C_COM_ERR
} cy8c95xx_err_code_t;
 
/**
 * \brief Base addresses for comunications
 * \ingroup cy8c95xx
 */
#define CY8C95XX_M_PORT_BASE_ADDR            0x20
#define CY8C95XX_EEPROM_BASE_ADDR            0x50
#define CY8C95XX_DEV_ADDR_GND                0x00
#define CY8C95XX_DEV_ADDR_VCC                0x01
 
/**
 * \brief Register map
 * \ingroup cy8c95xx
 */
typedef enum
{
    CY8C95XX_REG_IN_PORT0 =                 0x00,
    CY8C95XX_REG_IN_PORT1 =                 0x01,
    CY8C95XX_REG_IN_PORT2 =                 0x02,
    CY8C95XX_REG_IN_PORT3 =                 0x03,
    CY8C95XX_REG_IN_PORT4 =                 0x04,
    CY8C95XX_REG_IN_PORT5 =                 0x05,
    CY8C95XX_REG_IN_PORT6 =                 0x06,
    CY8C95XX_REG_IN_PORT7 =                 0x07,
    CY8C95XX_REG_OUT_PORT0 =                0x08,
    CY8C95XX_REG_OUT_PORT1 =                0x09,
    CY8C95XX_REG_OUT_PORT2 =                0x0A,
    CY8C95XX_REG_OUT_PORT3 =                0x0B,
    CY8C95XX_REG_OUT_PORT4 =                0x0C,
    CY8C95XX_REG_OUT_PORT5 =                0x0D,
    CY8C95XX_REG_OUT_PORT6 =                0x0E,
    CY8C95XX_REG_OUT_PORT7 =                0x0F,
    CY8C95XX_REG_INT_STAT_PORT0 =           0x10,
    CY8C95XX_REG_INT_STAT_PORT1 =           0x11,
    CY8C95XX_REG_INT_STAT_PORT2 =           0x12,
    CY8C95XX_REG_INT_STAT_PORT3 =           0x13,
    CY8C95XX_REG_INT_STAT_PORT4 =           0x14,
    CY8C95XX_REG_INT_STAT_PORT5 =           0x15,
    CY8C95XX_REG_INT_STAT_PORT6 =           0x16,
    CY8C95XX_REG_INT_STAT_PORT7 =           0x17,
    CY8C95XX_REG_PORT_SEL =                 0x18,
    CY8C95XX_REG_INT_MASK =                 0x19,
    CY8C95XX_REG_SEL_PWM_OUT =              0x1A,
    CY8C95XX_REG_INV =                      0x1B,
    CY8C95XX_REG_PORT_DIR =                 0x1C,
    CY8C95XX_REG_PULL_UP =                  0x1D,
    CY8C95XX_REG_PULL_DOWN =                0x1E,
    CY8C95XX_REG_OPEN_DRAIN_HIGH =          0x1F,
    CY8C95XX_REG_OPEN_DRAIN_LOW =           0x20,
    CY8C95XX_REG_STRONG =                   0x21,
    CY8C95XX_REG_SLOW_STRONG =              0x22,
    CY8C95XX_REG_HIGH_Z =                   0x23,
    CY8C95XX_REG_RSRVD_1 =                  0x24,
    CY8C95XX_REG_RSRVD_2 =                  0x25,
    CY8C95XX_REG_RSRVD_3 =                  0x26,
    CY8C95XX_REG_RSRVD_4 =                  0x27,
    CY8C95XX_REG_PWM_SEL =                  0x28,
    CY8C95XX_REG_CFG_PWM =                  0x29,
    CY8C95XX_REG_PERIOD_PWM =               0x2A,
    CY8C95XX_REG_PULSE_WIDTH_PWM =          0x2B,
    CY8C95XX_REG_DIVIDER =                  0x2C,
    CY8C95XX_REG_EEPROM =                   0x2D,
    CY8C95XX_REG_DEV_ID =                   0x2E,
    CY8C95XX_REG_WDT =                      0x2F,
    CY8C95XX_REG_CMD =                      0x30
} cy8c95xx_reg_t;
 
/**
 * \brief Select pwm output
 * \ingroup cy8c95xx
 */
#define CY8C95XX_SEL_PWM_0                  0x00
#define CY8C95XX_SEL_PWM_1                  0x01
#define CY8C95XX_SEL_PWM_2                  0x02
#define CY8C95XX_SEL_PWM_3                  0x03
 
/**
 * \brief Clock source for pwm
 * \ingroup cy8c95xx
 */
#define CY8C95XX_PWM_CLK_SRC_32_KHZ         0x00
#define CY8C95XX_PWM_CLK_SRC_24_MHZ         0x01
#define CY8C95XX_PWM_CLK_SRC_1_5_MHZ        0x02
#define CY8C95XX_PWM_CLK_SRC_93_75_KHZ      0x03
#define CY8C95XX_PWM_CLK_SRC_367_6_HZ       0x04
#define CY8C95XX_PWM_CLK_SRC_PREV           0x05
 
/**
 * \brief Available commands
 * \ingroup cy8c95xx
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
 * \ingroup cy8c95xx
 */
#define CY8C95XX_EEPROM_EN_WDE              0x01
#define CY8C95XX_EEPROM_EN_EEE              0x02
#define CY8C95XX_EEPROM_EN_EERO             0x04
 
/**
 * \brief Port select
 * \ingroup cy8c95xx
 */
#define CY8C95XX_PORT_0                     0x00
#define CY8C95XX_PORT_1                     0x01
#define CY8C95XX_PORT_2                     0x02
 
/**
 * \brief Pin states
 * \ingroup cy8c95xx
 */
#define CY8C95XX_LOW                        0x00
#define CY8C95XX_HIGH                       0x01

#define CY8C95XX_INT_NORMAL                 0x00
#define CY8C95XX_INT_INVERTED               0x01
 
/**
 * \brief Configuration offsets
 * \ingroup cy8c95xx
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
 * \brief Drive mode for pins
 * \ingroup cy8c95xx
 */
typedef enum
{
    CY8C95XX_DRV_PULL_UP =                  CY8C95XX_REG_PULL_UP,
    CY8C95XX_DRV_PULL_DOWN =                CY8C95XX_REG_PULL_DOWN,
    CY8C95XX_DRV_OPEN_DRAIN_HIGH =          CY8C95XX_REG_OPEN_DRAIN_HIGH,
    CY8C95XX_DRV_OPEN_DRAIN_LOW =           CY8C95XX_REG_OPEN_DRAIN_LOW,
    CY8C95XX_DRV_STRONG =                   CY8C95XX_REG_STRONG,
    CY8C95XX_DRV_SLOW_STRONG =              CY8C95XX_REG_SLOW_STRONG,
    CY8C95XX_DRV_HIGH_Z =                   CY8C95XX_REG_HIGH_Z
} cy8c95xx_drv_mode_t;
 
/**
 * \brief Direction input/output mode for pins
 * \ingroup cy8c95xx
 */
typedef enum 
{
    CY8C95XX_GPIO_IN =                      PLATFORM_GPIO_IN,
    CY8C95XX_GPIO_OUT =                     PLATFORM_GPIO_OUT
} cy8c95xx_dir_mode_t;
 
/**
 * \brief GPIO numbers only up to cy8c9520(20 GPIOs)
 * \ingroup cy8c95xx
 */
typedef enum
{
    CY8C95XX_GPIO_0 =                       0x00,
    CY8C95XX_GPIO_1 =                       0x01,
    CY8C95XX_GPIO_2 =                       0x02,
    CY8C95XX_GPIO_3 =                       0x03,
    CY8C95XX_GPIO_4 =                       0x04,
    CY8C95XX_GPIO_5 =                       0x05,
    CY8C95XX_GPIO_6 =                       0x06,
    CY8C95XX_GPIO_7 =                       0x07,
    CY8C95XX_GPIO_8 =                       0x08,
    CY8C95XX_GPIO_9 =                       0x09,
    CY8C95XX_GPIO_10 =                      0x0A,
    CY8C95XX_GPIO_11 =                      0x0B,
    CY8C95XX_GPIO_12 =                      0x0C,
    CY8C95XX_GPIO_13 =                      0x0D,
    CY8C95XX_GPIO_14 =                      0x0E,
    CY8C95XX_GPIO_15 =                      0x0F,
    CY8C95XX_GPIO_16 =                      0x10,
    CY8C95XX_GPIO_17 =                      0x11,
    CY8C95XX_GPIO_18 =                      0x12,
    CY8C95XX_GPIO_19 =                      0x13,
} cy8c95xx_gpio_t;
 
/**
 * \brief PWM selection for each GPIO up to cy8c9520(20 GPIOs)
 * \ingroup cy8c95xx
 */
#define CY8C95XX_GPIO_0_PWM                 CY8C95XX_SEL_PWM_3
#define CY8C95XX_GPIO_1_PWM                 CY8C95XX_SEL_PWM_1
#define CY8C95XX_GPIO_2_PWM                 CY8C95XX_SEL_PWM_3
#define CY8C95XX_GPIO_3_PWM                 CY8C95XX_SEL_PWM_1
#define CY8C95XX_GPIO_4_PWM                 CY8C95XX_SEL_PWM_3
#define CY8C95XX_GPIO_5_PWM                 CY8C95XX_SEL_PWM_1
#define CY8C95XX_GPIO_6_PWM                 CY8C95XX_SEL_PWM_3
#define CY8C95XX_GPIO_7_PWM                 CY8C95XX_SEL_PWM_1
#define CY8C95XX_GPIO_8_PWM                 CY8C95XX_SEL_PWM_2
#define CY8C95XX_GPIO_9_PWM                 CY8C95XX_SEL_PWM_0
#define CY8C95XX_GPIO_10_PWM                CY8C95XX_SEL_PWM_2
#define CY8C95XX_GPIO_11_PWM                CY8C95XX_SEL_PWM_0
#define CY8C95XX_GPIO_12_PWM                CY8C95XX_SEL_PWM_2
#define CY8C95XX_GPIO_13_PWM                CY8C95XX_SEL_PWM_0
#define CY8C95XX_GPIO_14_PWM                CY8C95XX_SEL_PWM_2
#define CY8C95XX_GPIO_15_PWM                CY8C95XX_SEL_PWM_0
#define CY8C95XX_GPIO_16_PWM                CY8C95XX_SEL_PWM_2
#define CY8C95XX_GPIO_17_PWM                CY8C95XX_SEL_PWM_0
#define CY8C95XX_GPIO_18_PWM                CY8C95XX_SEL_PWM_0
#define CY8C95XX_GPIO_19_PWM                CY8C95XX_SEL_PWM_3
 
/**
 * \brief External pins
 * \ingroup cy8c95xx
 */
#ifndef CY8C95XX_RST
#define CY8C95XX_RST        -1
#endif
#ifndef CY8C95XX_INT
#define CY8C95XX_INT        -1
#endif
 
/**
 * \brief Initial config struct
 * \ingroup cy8c95xx
 */
typedef struct
{
    int sda_pin;
    int scl_pin;
    uint i2c_speed;
    uint8_t i2c_addr;
    hw_i2c_t* i2c;
    int rst_pin;
    int int_pin;
} cy8c95xx_cfg_t;
 
/**
 * \brief CY8C95XX expander struct
 * \ingroup cy8c95xx
 */
typedef struct 
{
    hw_i2c_t* i2c;
    int rst_pin;
    int int_pin;
} cy8c95xx_t;
 
/**
 * \brief Struct to store pwm config
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
 * \brief Initializes default configuration
 * \ingroup cy8c95xx
 *
 * \param cfg Initial config struct
 */
void cy8c95xx_set_default_cfg(cy8c95xx_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param cfg Initial config struct
 * \return CY8C95XX_INIT_ERR : error
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_init(cy8c95xx_t *dev, cy8c95xx_cfg_t *cfg);
 
/*!
 * \brief Reset port expander using rst_pin
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \note Functon holds two 100 ms reset delays
 */
void cy8c95xx_reset(cy8c95xx_t* dev);
 
/*!
 * \brief Check interrupt by reading int_pin level
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \return 0 : Interrupt has not occured
 *         1 : Interrupt has occured
 */
uint8_t cy8c95xx_check_int(cy8c95xx_t* dev);
 
/*!
 * \brief Writes data to register
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param reg Register address
 * \param txdata Pointer to data to send
 * \param txlen Number of the bytes in data buf
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_generic_write(cy8c95xx_t* dev, cy8c95xx_reg_t reg, uint8_t* txdata, uint8_t txlen);
 
/*!
 * \brief Reads data from register
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param reg Register address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of the bytes to be read
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_generic_read(cy8c95xx_t *dev, cy8c95xx_reg_t reg, uint8_t *rxdata, uint8_t rxlen);
 
/*!
 * \brief Write single byte of data to register
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param reg Register address
 * \param txdata Byte to be written
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_write_byte(cy8c95xx_t* dev, cy8c95xx_reg_t reg, uint8_t txdata);
 
/*!
 * \brief Read single byte of data fromregister
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param reg Register address
 * \param rxdata Pointer to readed byte
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_read_byte(cy8c95xx_t* dev, cy8c95xx_reg_t reg, uint8_t* rxdata);
 
/*!
 * \brief Read state of a single bit from register
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param reg Register address
 * \param bit_num Specific bit to read
 * \param state Pointer to receive bit state
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_read_bit(cy8c95xx_t* dev, cy8c95xx_reg_t reg, uint8_t bit_num, uint8_t* state);
 
/*!
 * \brief Set or clear specific bit in register
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param reg_adr Register address
 * \param bit_num Specific bit to write
 * \param val Value to apply on bit
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_write_bit(cy8c95xx_t* dev, cy8c95xx_reg_t reg, uint8_t bit_num, uint8_t val);
 
/*!
 * \brief Send EEPROM comand
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param cmd Command to send
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_send_eeprom_cmd(cy8c95xx_t *dev, uint8_t cmd);
 
/*!
 * \brief Writes number of bytes into EEPROM
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param mem Memory address
 * \param txdata Pointer to data to send
 * \param txlen Number of the bytes in data buf
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_write_eeprom(cy8c95xx_t* dev, uint16_t mem, uint8_t* txdata, uint8_t txlen);
 
/*!
 * \brief Reads number of bytes from EEPROM
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param mem Memory address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of the bytes to be read
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_read_eeprom(cy8c95xx_t *dev, uint16_t mem, uint8_t *rxdata, uint8_t rxlen);
 
/*!
 * \brief Set pin especific configuration
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param pin Specific pin to configure
 * \param dir Pin input/output direction
 * \param drv Pin drver configuration
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_pin_mode(cy8c95xx_t* dev, int pin, cy8c95xx_dir_mode_t dir, cy8c95xx_drv_mode_t drv);
 
/*!
 * \brief Set pin input inverted mode
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param pin Specific pin to configure
 * \param dir Pin input/output direction
 * \param drv Pin drver configuration
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_pin_inv_in(cy8c95xx_t* dev, int pin);
 
/*!
 * \brief Get a single input pin logic level
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param pin Specific pin to read
 * \param state Pointer to receive pin state
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_read_pin(cy8c95xx_t* dev, int pin, uint8_t* state);
 
/*!
 * \brief Get all input pin logic levels from port
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param port Port to read
 * \param port_state Pointer to receive port state
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_read_port(cy8c95xx_t* dev, uint8_t port, uint8_t* port_state);
 
/*!
 * \brief Get a single output pin logic level
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param pin Specific pin to read
 * \param state Pointer to receive pin state
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_read_pin_out_lvl(cy8c95xx_t* dev, int pin, uint8_t* state);
 
/*!
 * \brief Get all output pin logic levels from port
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param port Port to read
 * \param port_state Pointer to receive port state
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_read_port_out_lvl(cy8c95xx_t* dev, uint8_t port, uint8_t* port_state);
 
/*!
 * \brief Set a single output pin logic level
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param pin Specific pin to write
 * \param val Value to apply on bit
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_write_pin(cy8c95xx_t* dev, int pin, uint8_t val);
 
/*!
 * \brief Set all output pins logic levels in a port
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param port Port to write
 * \param port_val Port pins logic level to write
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_write_port(cy8c95xx_t* dev, uint8_t port, uint8_t port_val);
 
/*!
 * \brief Enable or disable pwm output on pin
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param pin Specific pin to configure pwm
 * \param pwm_en Enables or disables pwm
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_sel_pwm_pin(cy8c95xx_t* dev, int pin, uint8_t pwm_en);
 
/*!
 * \brief Configure pwm output
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param pwm_cfg Pointer to pwm Configuration structure
 * \param duty_cyc Pointer  to resoulting pwm duty cycle
 * \param freq Pointer to resoulting frequency
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 */
cy8c95xx_err_code_t cy8c95xx_set_pwm_cfg(cy8c95xx_t *dev, cy8c95xx_pwm_cfg_t* pwm_cfg, float *duty_cyc, float *freq);
 
/*!
 * \brief Configures EEPROM enable register
 * \ingroup cy8c95xx
 *
 * \param dev Pointer to CY8C95XX expander struct
 * \param cmd Enable EEPROM commad
 * \return CY8C95XX_I2C_ERR : error in coms
 *         CY8C95XX_ARG_ERR : error in arguments
 *         CY8C95XX_OK : successful
 * \note Writes to dev register differ from other registers, see datasheet
 */
cy8c95xx_err_code_t cy8c95xx_eeprom_enable(cy8c95xx_t *dev, uint8_t cmd);
 
#ifdef __cplusplus
}
#endif
 
#endif  // CY8C95XX_H
