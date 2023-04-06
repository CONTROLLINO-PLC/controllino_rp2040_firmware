/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
#include "hardware/gpio.h"
 
/* Init gpio pin */
platform_err_code_t platform_gpio_init(int pin, platform_gpio_dir_t dir, platform_gpio_pull_mod_t pull)
{
    if (pin > 29) {
        return PLATFORM_GPIO_INIT_ERR;
    }
    else if (pin > -1) {
        gpio_init(pin);
        gpio_set_dir(pin, dir == PLATFORM_GPIO_IN ? GPIO_IN : GPIO_OUT);
        if (pull != PLATFORM_GPIO_PULL_DISABLED) {
            gpio_set_pulls(pin, pull == PLATFORM_GPIO_PULL_UP ? true : false, pull == PLATFORM_GPIO_PULL_DOWN ? true : false);
        }
    } 
    return PLATFORM_OK;
}
 
/* Set out gpio value */
platform_err_code_t platform_gpio_set(int pin, bool value)
{
    if (pin > 29) {
        return PLATFORM_ARGUMENT_ERR;
    }
    if (pin > -1) {
        gpio_set_dir(pin, GPIO_OUT);
        gpio_put(pin, value ? 1 : 0);
    }
    return PLATFORM_OK;
}
 
/* Get in gpio value */
platform_err_code_t platform_gpio_get(int pin, bool* value)
{
    if (pin > 29) {
        return PLATFORM_ARGUMENT_ERR;
    }
    if (pin > -1) {
        *value = gpio_get(pin) ? true : false;
    }
    return PLATFORM_OK;
}