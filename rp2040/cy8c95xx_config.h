/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef cy8c95xx_CONFIG_H
#define cy8c95xx_CONFIG_H

/**
 * \file cy8c95xx_config.h
 * \ingroup cy8c95xx
 * \defgroup cy8c95xx_config
 *
 * External hardware interface for cy8c95xx port expander driver library
 */

#ifdef PLATFORM_RP2040
#include "pico/stdlib.h"
#include "hardware/i2c.h"
typedef struct i2c_inst_t hw_i2c_t;
#endif

#endif /* cy8c95xx_CONFIG_H */