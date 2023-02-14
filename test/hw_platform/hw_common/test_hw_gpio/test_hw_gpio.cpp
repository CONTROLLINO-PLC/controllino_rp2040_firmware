/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
/**
 * \file test_hw_common_gpio.c
 *
 * Main harware abstraction layer tests
 */
 
#include <unity.h>
#include "hw_platform.h"

int pin;
platform_gpio_dir_t dir;
platform_gpio_pull_mod_t pull;
platform_err_code_t ret;

void setUp(void)
{
    pin = 0;
    dir = PLATFORM_GPIO_IN;
    pull = PLATFORM_GPIO_PULL_DOWN;
    ret = PLATFORM_OK;
}

void tearDown(void)
{}

void test_platform_gpio_init_return_ok()
{
    ret = platform_gpio_init(pin, dir, pull);
    TEST_ASSERT_EQUAL_INT(PLATFORM_OK, ret);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_gpio_init_return_ok);
    UNITY_END();
    return UNITY_END();
}

#if defined(NATIVE_TEST_ENV)
int main(int argc, char** argv)
{
    return runUnityTests();
}
#endif

#if defined(ARDUINO_PICO_ENV)
#include "Arduino.h"
void setup()
{
    while (!Serial);
    runUnityTests();
}
void loop()
{}
#endif
