/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ADG728_H
#define ADG728_H

/**
 * \file adg728.h
 * \ingroup drivers
 * \defgroup adg728
 *
 * Driver librarry to handle ADG728 analog matrix switch.
 * Based on MikroE AnalogMux 2 Click Driver (Copyright© 2020 MikroElektronika d.o.o.)
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include <stdint.h>
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup adg728
 */
typedef int adg728_err_code_t;
 
/**
 * \brief Posible I2C Slave addresses based on A0 and A1 pins
 * \ingroup adg728
 */ 
#define ADG728_DEV_ADDR_0           0x4C
#define ADG728_DEV_ADDR_1           0x4D
#define ADG728_DEV_ADDR_2           0x4E
#define ADG728_DEV_ADDR_3           0x4F
 
/**
 * \brief Channel selection values
 * \ingroup adg728
 */
typedef enum
{
    ADG728_CHANNEL_OFF =            0x00,
    ADG728_CHANNEL_0 =              0x01,
    ADG728_CHANNEL_1 =              0x02,
    ADG728_CHANNEL_2 =              0x04,
    ADG728_CHANNEL_3 =              0x08,
    ADG728_CHANNEL_4 =              0x10,
    ADG728_CHANNEL_5 =              0x20,
    ADG728_CHANNEL_6 =              0x40,
    ADG728_CHANNEL_7 =              0x80,
} adg728_channel_t;
 
/**
 * \brief External hardware I2C interface
 */
typedef struct _hw_i2c_t* hw_i2c_t;
 
/**
 * \brief Initial config struct
 * \ingroup adg728
 */
typedef struct
{
    int sda_pin;
    int scl_pin;
    unsigned int i2c_speed;
    uint8_t i2c_addr;
    hw_i2c_t i2c;
} adg728_cfg_t;
 
/**
 * \brief ADG728 device struct
 * \ingroup adg728
 */
typedef struct
{
    uint8_t i2c_addr;
    hw_i2c_t i2c;
} adg728_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup adg728
 *
 * \param cfg Initial config struct
 */
void adg728_set_default_cfg(adg728_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup adg728
 *
 * \param dev Pointer to temp sensor struct
 * \param cfg Initial config struct
 * \return PLATFORM_I2C_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_I2C_COM_ERR : error
 *         PLATFORM_OK : successful
 */
adg728_err_code_t adg728_init(adg728_t* dev, adg728_cfg_t* cfg);

/**
 * ADG728 has basically two simple functions write and read channel selection
 * so there is no point on implement basic functions for write and read
 */

/*!
 * \brief Sets channel to be selected
 * \ingroup adg728
 *
 * \param dev Pointer to temp sensor struct
 * \param ch Channel to be selected
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
adg728_err_code_t adg728_set_channel(adg728_t* dev, adg728_channel_t ch);
 
/*!
 * \brief Gets selected channel
 * \ingroup adg728
 *
 * \param dev Pointer to temp sensor struct
 * \param ch Pointer to receive selected channel
 * \return PLATFORM_I2C_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
adg728_err_code_t adg728_get_channel(adg728_t* dev, adg728_channel_t *ch);
 
#ifdef __cplusplus
}
#endif
 
#endif /* ADG728_H */
