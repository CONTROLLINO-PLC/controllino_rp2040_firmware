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
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
 
/**
 * \brief Platform I2C settings
 * \ingroup platform
 */
typedef struct _hw_i2c_t* hw_i2c_t;
extern hw_i2c_t PLATFORM_I2C_HW;
extern const unsigned int PLATFORM_I2C_SPEED;
extern const int PLATFORM_I2C_SDA;
extern const int PLATFORM_I2C_SCL;
 
/**
 * \brief Platform SPI settings
 * \ingroup platform
 */
typedef struct _hw_spi_t* hw_spi_t;
extern hw_spi_t PLATFORM_SPI_HW;
extern const unsigned int PLATFORM_SPI_SPEED;
extern const int PLATFORM_SPI_MOSI;
extern const int PLATFORM_SPI_MISO;
extern const int PLATFORM_SPI_SCK;
 
/**
 * \brief Error codes
 * \ingroup platform
 */
enum {
    PLATFORM_OK =                   0x00,
    PLATFORM_ARGUMENT_ERR =         0x01,
    PLATFORM_GPIO_INIT_ERR =        0x02,
    PLATFORM_I2C_INIT_ERR =         0x03,
    PLATFORM_I2C_COM_ERR =          0x04,
    PLATFORM_SPI_INIT_ERR =         0x05,
    PLATFORM_SPI_COM_ERR =          0x06,
};
typedef int platform_err_code_t;
/**
 * \brief GPIO direction
 * \ingroup platform
 */
typedef enum
{
    PLATFORM_GPIO_IN =              0x0,
    PLATFORM_GPIO_OUT
} platform_gpio_dir_t;
 
/**
 * \brief GPIO internal pull resistor
 * \ingroup platform
 */
typedef enum
{
    PLATFORM_GPIO_PULL_DISABLED =   0x0,
    PLATFORM_GPIO_PULL_UP =     	0x1,
    PLATFORM_GPIO_PULL_DOWN =       0x2,
} platform_gpio_pull_mod_t;
 
/**
 * \brief SPI modes
 * \ingroup platform
 */
typedef enum
{
    PLATFORM_SPI_MODE_0 =           0x0,
    PLATFORM_SPI_MODE_1 =           0x1,
    PLATFORM_SPI_MODE_2 =           0x2,
    PLATFORM_SPI_MODE_3 =           0x3
} platform_spi_mode_t;
 
/**
 * \brief SPI bit order
 * \ingroup platform
 */
typedef enum
{
    PLATFORM_SPI_LSBFIRST =         0x0,
    PLATFORM_SPI_MSBFIRST =         0x1
} platform_spi_bit_order_t;
 
#ifdef __cplusplus
extern "C" {
#endif
 
/*!
 * \brief Initialize and config gpio pin
 * \ingroup platform
 *
 * \param pin pin number -1 for unused pins
 * \param dir in/out configuration
 * \param pull internal pull resistor configuration
 * \return PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_gpio_init(int pin, platform_gpio_dir_t dir, platform_gpio_pull_mod_t pull);
 
/*!
 * \brief Set out gpio value
 * \ingroup platform
 *
 * \param pin pin number -1 for unused pins
 * \param value boolean true for HIGH level, false for LOW level
 */
platform_err_code_t platform_gpio_set(int pin, bool value);
 
/*!
 * \brief Get in gpio value
 * \ingroup platform
 *
 * \param pin pin number -1 for unused pins
 * \return true HIGH level
 *         false LOW level default if pin is -1
 */
platform_err_code_t platform_gpio_get(int pin, bool* value);
 
/*!
 * \brief Get system time microseconds
 * \ingroup platform
 *
 * \return microseconds since system boot
 */
uint64_t platform_get_us(void);
 
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
void platform_sleep_us(uint64_t us);
 
/*!
 * \brief Init I2C interface
 * \ingroup platform
 *
 * \param i2c_hw Pointer to I2C interface
 * \param speed Baudrate
 * \param sda_pin SDA pin number
 * \param scl_pin SCL pin number
 * \return PLATFORM_I2C_INIT_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_i2c_init(hw_i2c_t i2c_hw, unsigned int speed, int sda_pin, int scl_pin);
 
/*!
 * \brief Attempt to read specified number of bytes from address over I2C
 * \ingroup platform
 *
 * \param i2c_hw Pointer to I2C interface
 * \param addr 7-bit address of device to read from
 * \param rxdata Pointer to data to receive
 * \param len Length of data in bytes to receive
 * \return PLATFORM_I2C_COM_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_i2c_read(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* rxdata, size_t len);
 
/*!
 * \brief Attempt to write specified number of bytes to address over I2C
 * \ingroup platform
 *
 * \param i2c_hw Pointer to I2C interface
 * \param addr 7-bit address of device to write to
 * \param txdata Pointer to data to send
 * \param len Length of data in bytes to send
 * \return PLATFORM_I2C_COM_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_i2c_write(hw_i2c_t i2c_hw, uint8_t addr, uint8_t* txdata, size_t len);
 
/*!
 * \brief Init SPI interface
 * 
 * \param spi_hw Pointer to SPI interface
 * \param speed Baudrate
 * \param mosi_pin MOSI pin number
 * \param miso_pin MISO pin number
 * \param sck_pin SCK pin number
 * \return PLATFORM_SPI_INIT_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_spi_init(hw_spi_t spi_hw, unsigned int speed, int mosi_pin, int miso_pin, int sck_pin);
 
/**
 * \brief Change SPI settings
 * 
 * \param spi_hw Pointer to SPI interface
 * \param speed Baudrate
 * \param mode SPI mode (0, 1, 2, 3)
 * \param bit_order SPI bit order
 * \return PLATFORM_ARGUMENT_ERR : error
 *         PLATFORM_SPI_COM_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_spi_set_config(hw_spi_t spi_hw, unsigned int speed, platform_spi_mode_t mode, platform_spi_bit_order_t bit_order);
 
/**
 * \brief Write specified number of bytes to an SPI device
 * 
 * \param spi_hw Pointer to SPI interface
 * \param cs_select Pointer to chip select pin handler to select the chip
 * \param cs_deselect Pointer to chip select pin handler to deselect the chip
 * \param cs_pin Chip select pin
 * \param txdata Pointer to data to send
 * \param len Length of data in bytes to send
 * \return PLATFORM_SPI_COM_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_spi_write(hw_spi_t spi_hw, void(*cs_select)(int), void(*cs_deselect)(int), int cs_pin,  uint8_t* txdata, size_t len);
 
/**
 * \brief Write and read specified number of bytes over SPI
 *
 * \param spi_hw Pointer to SPI interface
 * \param cs_select Pointer to chip select pin handler to select the chip
 * \param cs_deselect Pointer to chip select pin handler to deselect the chip
 * \param cs_pin Chip select pin
 * \param txdata Pointer to data to send
 * \param rxdata Pointer to data to receive
 * \param len Length of data in bytes to send
 * \return PLATFORM_SPI_COM_ERR : error
 *         PLATFORM_OK : successful
 */
platform_err_code_t platform_spi_write_read(hw_spi_t spi_hw, void(*cs_select)(int), void(*cs_deselect)(int), int cs_pin, uint8_t* txdata, uint8_t* rxdata, size_t len);
 
#ifdef __cplusplus
}
#endif
 
#endif /* HW_PLATFORM_H */