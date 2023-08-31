/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef CY8C9520_H
#define CY8C9520_H
 
/**
 * \file cy8c9520.h
 * \ingroup drivers
 * \defgroup cy8c9520
 *
 * Driver librarry to handle cy8c9520 port expander.
 * Based on MikroE Expand 6 Click Driver (Copyright© 2020 MikroElektronika d.o.o.)
 *
 * \author Pedro Marquez @pmmarquez , CONTROLLINO Firmware Team
 */
 
#include <stdint.h>
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup cy8c9520
 */
typedef int cy8c9520_err_code_t;
 
/**
 * \brief Base addresses for comunications depending on A0 pin
 * \ingroup cy8c9520
 */
#define CY8C9520_M_PORT_BASE_ADDR            0x20
#define CY8C9520_EEPROM_BASE_ADDR            0x50
#define CY8C9520_DEV_ADDR_GND                0x00
#define CY8C9520_DEV_ADDR_VCC                0x01
 
/**
 * \brief Register map
 * \ingroup cy8c9520
 */
typedef enum
{
    CY8C9520_REG_IN_PORT0 =                 0x00,
    CY8C9520_REG_IN_PORT1 =                 0x01,
    CY8C9520_REG_IN_PORT2 =                 0x02,
    CY8C9520_REG_IN_PORT3 =                 0x03,
    CY8C9520_REG_IN_PORT4 =                 0x04,
    CY8C9520_REG_IN_PORT5 =                 0x05,
    CY8C9520_REG_IN_PORT6 =                 0x06,
    CY8C9520_REG_IN_PORT7 =                 0x07,
    CY8C9520_REG_OUT_PORT0 =                0x08,
    CY8C9520_REG_OUT_PORT1 =                0x09,
    CY8C9520_REG_OUT_PORT2 =                0x0A,
    CY8C9520_REG_OUT_PORT3 =                0x0B,
    CY8C9520_REG_OUT_PORT4 =                0x0C,
    CY8C9520_REG_OUT_PORT5 =                0x0D,
    CY8C9520_REG_OUT_PORT6 =                0x0E,
    CY8C9520_REG_OUT_PORT7 =                0x0F,
    CY8C9520_REG_INT_STAT_PORT0 =           0x10,
    CY8C9520_REG_INT_STAT_PORT1 =           0x11,
    CY8C9520_REG_INT_STAT_PORT2 =           0x12,
    CY8C9520_REG_INT_STAT_PORT3 =           0x13,
    CY8C9520_REG_INT_STAT_PORT4 =           0x14,
    CY8C9520_REG_INT_STAT_PORT5 =           0x15,
    CY8C9520_REG_INT_STAT_PORT6 =           0x16,
    CY8C9520_REG_INT_STAT_PORT7 =           0x17,
    CY8C9520_REG_PORT_SEL =                 0x18,
    CY8C9520_REG_INT_MASK =                 0x19,
    CY8C9520_REG_SEL_PWM_OUT =              0x1A,
    CY8C9520_REG_INV =                      0x1B,
    CY8C9520_REG_PORT_DIR =                 0x1C,
    CY8C9520_REG_PULL_UP =                  0x1D,
    CY8C9520_REG_PULL_DOWN =                0x1E,
    CY8C9520_REG_OPEN_DRAIN_HIGH =          0x1F,
    CY8C9520_REG_OPEN_DRAIN_LOW =           0x20,
    CY8C9520_REG_STRONG =                   0x21,
    CY8C9520_REG_SLOW_STRONG =              0x22,
    CY8C9520_REG_HIGH_Z =                   0x23,
    CY8C9520_REG_RSRVD_1 =                  0x24,
    CY8C9520_REG_RSRVD_2 =                  0x25,
    CY8C9520_REG_RSRVD_3 =                  0x26,
    CY8C9520_REG_RSRVD_4 =                  0x27,
    CY8C9520_REG_PWM_SEL =                  0x28,
    CY8C9520_REG_CFG_PWM =                  0x29,
    CY8C9520_REG_PERIOD_PWM =               0x2A,
    CY8C9520_REG_PULSE_WIDTH_PWM =          0x2B,
    CY8C9520_REG_DIV_PWM =                  0x2C,
    CY8C9520_REG_EEPROM =                   0x2D,
    CY8C9520_REG_DEV_ID =                   0x2E,
    CY8C9520_REG_WDT =                      0x2F,
    CY8C9520_REG_CMD =                      0x30
} cy8c9520_reg_t;
 
/**
 * \brief Select pwm output
 * \ingroup cy8c9520
 */
typedef enum {
    CY8C9520_SEL_PWM_0 =                    0x00,
    CY8C9520_SEL_PWM_1 =                    0x01,
    CY8C9520_SEL_PWM_2 =                    0x02,
    CY8C9520_SEL_PWM_3 =                    0x03
} cy8c9520_sel_pwm_t;

/**
 * \brief Clock source for pwm
 * \ingroup cy8c9520
 */
typedef enum {
    CY8C9520_PWM_CLK_SRC_32_KHZ =           0x00,
    CY8C9520_PWM_CLK_SRC_24_MHZ =           0x01,
    CY8C9520_PWM_CLK_SRC_1_5_MHZ =          0x02,
    CY8C9520_PWM_CLK_SRC_93_75_KHZ =        0x03,
    CY8C9520_PWM_CLK_SRC_367_6_HZ =         0x04,
    CY8C9520_PWM_CLK_SRC_PREV =             0x05
} cy8c9520_clk_src_t;
 
/**
 * \brief Available commands
 * \ingroup cy8c9520
 */
typedef enum {
    CY8C9520_STORE_POR_CFG_TO_EEPROM =      0x01,
    CY8C9520_RESTORE_DEFAULTS =             0x02,
    CY8C9520_WRITE_EEPROM_POR =             0x03,
    CY8C9520_READ_EEPROM_POR =              0x04,
    CY8C9520_WRITE_DEV_CFG =                0x05,
    CY8C9520_READ_DEV_CFG =                 0x06,
    CY8C9520_RECFG_DEV_TO_POR =             0x07
} cy8c9520_cmd_t;
 
/**
 * \brief Enable registers
 * \ingroup cy8c9520
 */
#define CY8C9520_EEPROM_EN_WDE              0x01
#define CY8C9520_EEPROM_EN_EEE              0x02
#define CY8C9520_EEPROM_EN_EERO             0x04
 
/**
 * \brief Port select
 * \ingroup cy8c9520
 */
#define CY8C9520_PORT_0                     0x00
#define CY8C9520_PORT_1                     0x01
#define CY8C9520_PORT_2                     0x02
 
/**
 * \brief Pin states
 * \ingroup cy8c9520
 */
#define CY8C9520_LOW                        0x00
#define CY8C9520_HIGH                       0x01

#define CY8C9520_INT_NORMAL                 0x00
#define CY8C9520_INT_INVERTED               0x01
 
/**
 * \brief Drive mode for pins
 * \ingroup cy8c9520
 */
typedef enum
{
    CY8C9520_DRV_PULL_UP =                  CY8C9520_REG_PULL_UP,
    CY8C9520_DRV_PULL_DOWN =                CY8C9520_REG_PULL_DOWN,
    CY8C9520_DRV_OPEN_DRAIN_HIGH =          CY8C9520_REG_OPEN_DRAIN_HIGH,
    CY8C9520_DRV_OPEN_DRAIN_LOW =           CY8C9520_REG_OPEN_DRAIN_LOW,
    CY8C9520_DRV_STRONG =                   CY8C9520_REG_STRONG,
    CY8C9520_DRV_SLOW_STRONG =              CY8C9520_REG_SLOW_STRONG,
    CY8C9520_DRV_HIGH_Z =                   CY8C9520_REG_HIGH_Z
} cy8c9520_drv_mode_t;
 
/**
 * \brief Direction input/output mode for pins
 * \ingroup cy8c9520
 */
typedef enum 
{
    CY8C9520_GPIO_OUT =                     0x0,
    CY8C9520_GPIO_IN =                      0x1
} cy8c9520_dir_mode_t;
 
/**
 * \brief GPIO numbers only up to cy8c9520(20 GPIOs)
 * \ingroup cy8c9520
 */
typedef enum
{
    CY8C9520_GPIO_0 =                       0x00,
    CY8C9520_GPIO_1 =                       0x01,
    CY8C9520_GPIO_2 =                       0x02,
    CY8C9520_GPIO_3 =                       0x03,
    CY8C9520_GPIO_4 =                       0x04,
    CY8C9520_GPIO_5 =                       0x05,
    CY8C9520_GPIO_6 =                       0x06,
    CY8C9520_GPIO_7 =                       0x07,
    CY8C9520_GPIO_8 =                       0x08,
    CY8C9520_GPIO_9 =                       0x09,
    CY8C9520_GPIO_10 =                      0x0A,
    CY8C9520_GPIO_11 =                      0x0B,
    CY8C9520_GPIO_12 =                      0x0C,
    CY8C9520_GPIO_13 =                      0x0D,
    CY8C9520_GPIO_14 =                      0x0E,
    CY8C9520_GPIO_15 =                      0x0F,
    CY8C9520_GPIO_16 =                      0x10,
    CY8C9520_GPIO_17 =                      0x11,
    CY8C9520_GPIO_18 =                      0x12,
    CY8C9520_GPIO_19 =                      0x13,
} cy8c9520_gpio_t;
 
/**
 * \brief PWM selection for each GPIO up to cy8c9520(20 GPIOs)
 * \ingroup cy8c9520
 */
#define CY8C9520_GPIO_0_PWM                 CY8C9520_SEL_PWM_3
#define CY8C9520_GPIO_1_PWM                 CY8C9520_SEL_PWM_1
#define CY8C9520_GPIO_2_PWM                 CY8C9520_SEL_PWM_3
#define CY8C9520_GPIO_3_PWM                 CY8C9520_SEL_PWM_1
#define CY8C9520_GPIO_4_PWM                 CY8C9520_SEL_PWM_3
#define CY8C9520_GPIO_5_PWM                 CY8C9520_SEL_PWM_1
#define CY8C9520_GPIO_6_PWM                 CY8C9520_SEL_PWM_3
#define CY8C9520_GPIO_7_PWM                 CY8C9520_SEL_PWM_1
#define CY8C9520_GPIO_8_PWM                 CY8C9520_SEL_PWM_2
#define CY8C9520_GPIO_9_PWM                 CY8C9520_SEL_PWM_0
#define CY8C9520_GPIO_10_PWM                CY8C9520_SEL_PWM_2
#define CY8C9520_GPIO_11_PWM                CY8C9520_SEL_PWM_0
#define CY8C9520_GPIO_12_PWM                CY8C9520_SEL_PWM_2
#define CY8C9520_GPIO_13_PWM                CY8C9520_SEL_PWM_0
#define CY8C9520_GPIO_14_PWM                CY8C9520_SEL_PWM_2
#define CY8C9520_GPIO_15_PWM                CY8C9520_SEL_PWM_0
#define CY8C9520_GPIO_16_PWM                CY8C9520_SEL_PWM_2
#define CY8C9520_GPIO_17_PWM                CY8C9520_SEL_PWM_0
#define CY8C9520_GPIO_18_PWM                CY8C9520_SEL_PWM_0
#define CY8C9520_GPIO_19_PWM                CY8C9520_SEL_PWM_3
 
/**
 * \brief External pins
 * \ingroup cy8c9520
 */
#ifndef CY8C9520_RST
#define CY8C9520_RST        -1
#endif
#ifndef CY8C9520_INT
#define CY8C9520_INT        -1
#endif
 
/**
 * \brief External hardware I2C interface
 */
typedef struct _hw_i2c_t* hw_i2c_t;
 
/**
 * \brief Initial config struct
 * \ingroup cy8c9520
 */
typedef struct
{
    int sda_pin;
    int scl_pin;
    unsigned int i2c_speed;
    uint8_t i2c_addr;
    hw_i2c_t i2c;
    int rst_pin;
    int int_pin;
} cy8c9520_cfg_t;
 
/**
 * \brief CY8C9520 expander struct
 * \ingroup cy8c9520
 */
typedef struct 
{
    hw_i2c_t i2c;
    int rst_pin;
    int int_pin;
} cy8c9520_t;
 
/**
 * \brief Struct to store pwm config
 * \ingroup cy8c9520
 */
typedef struct
{
    cy8c9520_sel_pwm_t pwm_sel;
    cy8c9520_clk_src_t clk_src;
    uint8_t period;
    uint8_t pulse_wid;
    uint8_t devider;
} cy8c9520_pwm_cfg_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup cy8c9520
 *
 * \param cfg Initial config struct
 */
void cy8c9520_set_default_cfg(cy8c9520_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param cfg Initial config struct
 * \return PLATFORM_I2C_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_I2C_COM_ERR : error
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_init(cy8c9520_t *dev, cy8c9520_cfg_t *cfg);
 
/*!
 * \brief Reset port expander using rst_pin
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \note Functon holds two 100 ms reset delays
 */
void cy8c9520_reset(cy8c9520_t* dev);
 
/*!
 * \brief Check interrupt by reading int_pin level
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \return 0 : Interrupt has not occured
 *         1 : Interrupt has occured
 */
uint8_t cy8c9520_check_int(cy8c9520_t* dev);
 
/*!
 * \brief Writes data to register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param reg Register address
 * \param txdata Pointer to data to send
 * \param txlen Number of the bytes in data buf
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_generic_write(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t* txdata, uint8_t txlen);
 
/*!
 * \brief Reads data from register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param reg Register address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of the bytes to be read
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_generic_read(cy8c9520_t *dev, cy8c9520_reg_t reg, uint8_t *rxdata, uint8_t rxlen);
 
/*!
 * \brief Write single byte of data to register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param reg Register address
 * \param txdata Byte to be written
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_write_byte(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t txdata);
 
/*!
 * \brief Read single byte of data fromregister
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param reg Register address
 * \param rxdata Pointer to readed byte
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_read_byte(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t* rxdata);
 
/*!
 * \brief Read state of a single bit from register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param reg Register address
 * \param bit_num Specific bit to read
 * \param state Pointer to receive bit state
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_read_bit(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t bit_num, uint8_t* state);
 
/*!
 * \brief Set or clear specific bit in register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param reg_adr Register address
 * \param bit_num Specific bit to write
 * \param val Value to apply on bit
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_write_bit(cy8c9520_t* dev, cy8c9520_reg_t reg, uint8_t bit_num, uint8_t val);
 
/*!
 * \brief Separated select port function to optimize coms
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param port_num port to select
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_select_port(cy8c9520_t* dev, uint8_t port_num);
 
/*!
 * \brief Send command to CY8C9520_REG_CMD
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param cmd Command to send
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_send_cmd(cy8c9520_t* dev, cy8c9520_cmd_t cmd);
 
/*!
 * \brief Writes number of bytes into EEPROM
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param mem Memory address
 * \param txdata Pointer to data to send
 * \param txlen Number of the bytes in data buf
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_write_eeprom(cy8c9520_t* dev, uint16_t mem, uint8_t* txdata, uint8_t txlen);
 
/*!
 * \brief Reads number of bytes from EEPROM
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param mem Memory address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of the bytes to be read
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_read_eeprom(cy8c9520_t *dev, uint16_t mem, uint8_t *rxdata, uint8_t rxlen);
 
/*!
 * \brief Set pin mode settings
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to configure
 * \param dir Pin input/output direction
 * \param drv Pin drver configuration
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_pin_mode(cy8c9520_t* dev, int pin, cy8c9520_dir_mode_t dir, cy8c9520_drv_mode_t drv);
 
/*!
 * \brief Enable pin input inverted mode
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to configure
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_pin_en_inv_in(cy8c9520_t* dev, int pin);
 
/*!
 * \brief Disable pin input inverted mode
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to configure
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_pin_dis_inv_in(cy8c9520_t* dev, int pin);
 
/*!
 * \brief Get a single input pin logic level
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to read
 * \param state Pointer to receive pin state
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_read_pin(cy8c9520_t* dev, int pin, uint8_t* state);
 
/*!
 * \brief Get all input pin logic levels from port
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param port Port to read
 * \param port_state Pointer to receive port state
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_read_port(cy8c9520_t* dev, uint8_t port, uint8_t* port_state);
 
/*!
 * \brief Get a single output pin logic level
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to read
 * \param state Pointer to receive pin state
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_read_pin_out_lvl(cy8c9520_t* dev, int pin, uint8_t* state);
 
/*!
 * \brief Get all output pin logic levels from port
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param port Port to read
 * \param port_state Pointer to receive port state
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_read_port_out_lvl(cy8c9520_t* dev, uint8_t port, uint8_t* port_state);
 
/*!
 * \brief Set a single output pin logic level
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to write
 * \param val Value to apply on bit
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_write_pin(cy8c9520_t* dev, int pin, uint8_t val);
 
/*!
 * \brief Set all output pins logic levels in a port
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param port Port to write
 * \param port_val Port pins logic level to write
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_write_port(cy8c9520_t* dev, uint8_t port, uint8_t port_val);
 
/*!
 * \brief Enable interrupt on pin with Interrupt Mask Port Register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to enable interrupt
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_en_pin_int(cy8c9520_t* dev, int pin);
 
/*!
 * \brief Disable interrupt on pin with Interrupt Mask Port Register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to disable interrupt
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_dis_pin_int(cy8c9520_t* dev, int pin);
 
/*!
 * \brief Enable pwm output on pin
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to enable pwm
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments   
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_en_pin_pwm(cy8c9520_t* dev, int pin);
 
/*!
 * \brief Disable pwm output on pin
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pin Specific pin to disable pwm
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_dis_pin_pwm(cy8c9520_t* dev, int pin);
 
/*!
 * \brief Configure pwm output
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param pwm_cfg Pointer to pwm Configuration structure
 * \param duty_cyc Pointer  to resoulting pwm duty cycle
 * \param freq Pointer to resoulting frequency
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
cy8c9520_err_code_t cy8c9520_set_pwm_cfg(cy8c9520_t *dev, cy8c9520_pwm_cfg_t* pwm_cfg, float *duty_cyc, float *freq);
 
/*!
 * \brief Configures EEPROM enable register
 * \ingroup cy8c9520
 *
 * \param dev Pointer to CY8C9520 expander struct
 * \param cmd Enable EEPROM commad
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 * \note Writes to dev register differ from other registers, see datasheet
 */
cy8c9520_err_code_t cy8c9520_eeprom_enable(cy8c9520_t *dev, uint8_t cmd);
 
#ifdef __cplusplus
}
#endif
 
#endif  // CY8C9520_H
