/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
#include "pico/time.h"
 
/* Get system time microseconds */
uint64_t platform_get_us(void)
{
    return time_us_64();
}
 
/* Wait for specified milliseconds */
void platform_sleep_ms(uint32_t ms)
{
    sleep_ms(ms);
}
 
/* Wait for specified microseconds */
void platform_sleep_us(uint64_t us)
{
    sleep_us(us);
}