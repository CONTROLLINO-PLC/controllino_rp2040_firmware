/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef HW_PLATFORM_H
#define HW_PLATFORM_H
 
/**
 * \file hw_platform.h
 * \defgroup platform
 *
 * External hardware interface library
 */
 
#ifdef __cplusplus
extern "C" {
#endif
 
#ifdef PLATFORM_RP2040
#include "pico/stdlib.h"
#include "hardware/i2c.h"
typedef struct i2c_inst_t hw_i2c_t;

#define PLATFORM_I2C_HW    (hw_i2c_t*)i2c0
#define PLATFORM_I2C_SPEED 100000
#define PLATFORM_I2C_SDA   4
#define PLATFORM_I2C_SCL   5

#endif /* PLATFORM_RP2040 */
 
/**
 * \brief Error codes
 * \ingroup platform
 */
enum PLATFORM_ERROR_CODE
{
    PLATFORM_OK = 0x00,
    PLATFORM_GPIO_INIT_ERROR = 0x01,
    PLATFORM_I2C_INIT_ERROR = 0x02,
    PLATFORM_I2C_COM_ERROR = 0x02,
};
 
/**
 * \brief GPIO direction
 * \ingroup platform
 */
enum PLATFORM_GPIO_DIR
{
    PLATFORM_GPIO_IN,
    PLATFORM_GPIO_OUT
};
 
/**
 * \brief GPIO internal pull resistor
 * \ingroup platform
 */
enum PLATFORM_GPIO_PULL_MODE
{
    PLATFORM_GPIO_PULL_DISABLED,
    PLATFORM_GPIO_PULL_UP,
    PLATFORM_GPIO_PULL_DOWN
};
 
// /**
//  * \brief GPIO configuration object
//  * \ingroup platform
//  */
// typedef struct {
//     uint8_t gpio_dir;
//     uint8_t gpio_pull_mode;
// } platform_gpio_cfg_t;
 
// /**
//  * \brief GPIO instance
//  * \ingroup platform
//  */
// typedef struct {
//     platform_gpio_cfg_t cfg;
//     int pin_num;
// } platform_gpio_t;
 
/*!
 * \brief Initialize and config gpio pin
 * \ingroup platform
 *
 * \param pin pin number -1 for unused pins
 * \param dir in/out configuration
 * \param pull internal pull resistor configuration
 * \return PLATFORM_GPIO_INIT_ERROR : error
 *         PLATFORM_OK : successful
 */
int platform_gpio_init(int pin, uint dir, uint pull);
 
/*!
 * \brief Set out gpio value
 * \ingroup platform
 *
 * \param pin pin number -1 for unused pins
 * \param value boolean true for HIGH level, false for LOW level
 */
void platform_gpio_set(int pin, bool value);
 
/*!
 * \brief Get in gpio value
 * \ingroup platform
 *
 * \param pin pin number -1 for unused pins
 * \return true HIGH level
 *         false LOW level default if pin is -1
 */
bool platform_gpio_get(int pin);
 
/*!
 * \brief Wait for specified milliseconds
 * \ingroup platform
 *
 * \param ms milliseconds to wait for
 */
void platform_sleep_ms(uint32_t ms);
 
/*!
 * \brief Wait for specified microseconds
 * \ingroup platform
 *
 * \param us microseconds to wait for
 */
void platform_sleep_us(uint32_t us);
 
/*!
 * \brief Init i2c interface
 * \ingroup platform
 *
 * \param i2c_hw hw_i2c_t pointer to hardware i2c interface
 * \param speed baudrate
 * \param sda_pin sda pin number
 * \param scl_pin scl pin number
 * \return PLATFORM_I2C_INIT_ERROR : error
 *         PLATFORM_OK : successful
 */
int platform_i2c_init(hw_i2c_t* i2c_hw, uint speed, int sda_pin, int scl_pin);
 
/*!
 * \brief Attempt to read specified number of bytes from address over i2c
 * \ingroup platform
 *
 * \param i2c hw_i2c_t i2c interfase
 * \param addr 7-bit address of device to read from
 * \param rxdata Pointer to buffer to receive data
 * \param len Length of data in bytes to receive
 * \return PLATFORM_I2C_COM_ERROR : error
 *         PLATFORM_OK : successful
 */
int platform_i2c_read(hw_i2c_t* i2c, uint8_t addr, uint8_t* rxdata, size_t len);
 
/*!
 * \brief Attempt to write specified number of bytes to address over i2c
 * \ingroup platform
 *
 * \param i2c hw_i2c_t i2c interfase
 * \param addr 7-bit address of device to write to
 * \param txdata Pointer to data to send
 * \param len Length of data in bytes to send
 * \return PLATFORM_I2C_COM_ERROR : error
 *         PLATFORM_OK : successful
 */
int platform_i2c_write(hw_i2c_t* i2c, uint8_t addr, const uint8_t* txdata, size_t len);
 
#ifdef __cplusplus
}
#endif
 
#endif /* HW_PLATFORM_H */