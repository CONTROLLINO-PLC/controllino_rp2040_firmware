/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
#ifdef NATIVE_ENV
 
#include "hw_platform.h"
 
typedef struct {
    int num;
    bool state;
    platform_gpio_dir_t dir;
    platform_gpio_pull_mod_t pull;
} mock_pin_t;

mock_pin_t mock_pin;

/* Init gpio pin */
platform_err_code_t platform_gpio_init(int pin, platform_gpio_dir_t dir, platform_gpio_pull_mod_t pull)
{
    mock_pin.num = pin;
    mock_pin.dir = dir;
    mock_pin.pull = pull;
    switch (pull)
    {
    case PLATFORM_GPIO_PULL_DOWN:
    case PLATFORM_GPIO_PULL_DISABLED:
        mock_pin.state = 0;
        break;
    case PLATFORM_GPIO_PULL_UP:
        mock_pin.state = 1;
        break;
    }
    return PLATFORM_OK;
}
 
/* Set out gpio value */
platform_err_code_t platform_gpio_set(int pin, bool value)
{
    if (pin > -1 && mock_pin.dir == PLATFORM_GPIO_OUT) {
        mock_pin.state = value;
    }
    return PLATFORM_OK;
}
 
/* Get in gpio value */
platform_err_code_t platform_gpio_get(int pin, bool *value)
{
    if (pin > -1) {
        *value = mock_pin.state;
    }
    return PLATFORM_OK;
}
 
#endif