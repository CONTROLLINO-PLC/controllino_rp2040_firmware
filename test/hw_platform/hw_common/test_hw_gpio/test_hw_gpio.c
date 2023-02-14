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

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_platform_gpio_init() {
    int pin = 0;
    platform_gpio_dir_t dir = PLATFORM_GPIO_IN;
    platform_gpio_pull_mod_t pull = PLATFORM_GPIO_PULL_DOWN;
    platform_err_code_t ret = platform_gpio_init(pin, dir, pull);
    TEST_ASSERT_EQUAL_INT(PLATFORM_OK, ret);
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_platform_gpio_init);
    UNITY_END();
}