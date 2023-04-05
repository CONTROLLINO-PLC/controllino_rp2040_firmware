/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
#include <Arduino.h>
 
/* Get system time microseconds */
uint64_t platform_get_us(void)
{
    return micros();
}
 
/* Wait for specified milliseconds */
void platform_sleep_ms(uint32_t ms)
{
    delay(ms);
}
 
/* Wait for specified microseconds */
void platform_sleep_us(uint64_t us)
{
    delayMicroseconds(us);
}