/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifdef NATIVE_ENV
 
#include "hw_platform.h"
 
uint64_t mock_time_us = 1;
 
/* Get system time microseconds */
uint64_t platform_get_us(void)
{
    return mock_time_us;
}
 
/* Wait for specified milliseconds */
void platform_sleep_ms(uint32_t ms)
{
    mock_time_us += (ms * 1000);
}
 
/* Wait for specified microseconds */
void platform_sleep_us(uint64_t us)
{
    mock_time_us += us;
}
 
#endif