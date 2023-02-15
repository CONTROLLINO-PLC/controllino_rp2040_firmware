/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "hw_platform.h"
 
uint64_t dummy_time_us = 1;
 
/* Get system time microseconds */
uint64_t platform_get_us(void)
{
    return dummy_time_us;
}
 
/* Wait for specified milliseconds */
void platform_sleep_ms(uint32_t ms)
{
    dummy_time_us += (ms * 1000);
}
 
/* Wait for specified microseconds */
void platform_sleep_us(uint64_t us)
{
    dummy_time_us += us;
}