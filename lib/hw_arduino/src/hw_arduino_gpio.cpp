/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
#include <Arduino.h>
 
/* Init gpio pin */
platform_err_code_t platform_gpio_init(int pin, platform_gpio_dir_t dir, platform_gpio_pull_mod_t pull)
{
    if (pin > 29) {
        return PLATFORM_GPIO_INIT_ERR;
    }
    else if (pin > -1) {
        PinMode mode;
        switch (dir)
        {
        case PLATFORM_GPIO_IN:
            switch (pull)
            {
            case PLATFORM_GPIO_PULL_UP:
                mode = INPUT_PULLUP;
                break;
            case PLATFORM_GPIO_PULL_DOWN:
                mode = INPUT_PULLDOWN;
                break;
            default:
                mode = INPUT;
                break;
            }
            break;
        case PLATFORM_GPIO_OUT:
            mode = OUTPUT;
            break;
        }
        pinMode(pin, mode);
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
        digitalWrite(pin, value ? HIGH : LOW);
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
        *value = digitalRead(pin) == HIGH ? true : false;
    }
    return PLATFORM_OK;
}