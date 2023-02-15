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
#include "unity_test_runner.h"
#include "hw_platform.h"

int pin;
platform_gpio_dir_t dir;
platform_gpio_pull_mod_t pull;
platform_err_code_t ret;

void setUp(void)
{
    pin = 25;
    dir = PLATFORM_GPIO_IN;
    pull = PLATFORM_GPIO_PULL_DOWN;
    ret = PLATFORM_OK;
    platform_gpio_init(pin, dir, pull);
}

void tearDown(void)
{}

void test_platform_gpio_init_pin_less_than_30()
{
    pin = 30;
    ret = platform_gpio_init(pin, dir, pull);
    TEST_ASSERT_EQUAL_INT(PLATFORM_GPIO_INIT_ERR, ret);
}

void test_platform_gpio_set_pin_less_than_30()
{
    pin = 30;
    dir = PLATFORM_GPIO_OUT;
    platform_gpio_init(pin, dir, pull);
    ret = platform_gpio_set(pin, true);
    TEST_ASSERT_EQUAL_INT(PLATFORM_ARGUMENT_ERR, ret);
}

void test_platform_gpio_get_pin_less_than_30()
{
    pin = 30;
    bool val;
    platform_gpio_init(pin, dir, pull);
    ret = platform_gpio_get(pin, &val);
    TEST_ASSERT_EQUAL_INT(PLATFORM_ARGUMENT_ERR, ret);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_gpio_init_pin_less_than_30);
    RUN_TEST(test_platform_gpio_set_pin_less_than_30);
    RUN_TEST(test_platform_gpio_get_pin_less_than_30);
    UNITY_END();
    return UNITY_END();
}
