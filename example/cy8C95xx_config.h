/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef CY8C95XX_CONFIG_H
#define CY8C95XX_CONFIG_H

/**
 * \file cy8C95xx_config.h
 * \ingroup cy8C95xx
 * \defgroup cy8C95xx_config
 *
 * External hardware interface for cy8C95xx port expander driver library
 */

#ifdef PLATFORM_RP2040
#include "pico/stdlib.h"
#include "hardware/i2c.h"
typedef struct i2c_inst_t hw_i2c_t;
#endif

#endif /* CY8C95XX_CONFIG_H */