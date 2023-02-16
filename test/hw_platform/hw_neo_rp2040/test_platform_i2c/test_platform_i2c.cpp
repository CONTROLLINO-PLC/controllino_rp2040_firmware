#include <unity.h>
#include "unity_test_runner.h"
#include "hw_platform.h"
 
static platform_err_code_t ret;
 
void setUp(void)
{}
 
void tearDown(void)
{}
 
void test_platform_i2c_init_wrong_hw_err(void)
{
    uint8_t dummy_for_pointer;
    ret = platform_i2c_init((hw_i2c_t)&dummy_for_pointer, PLATFORM_I2C_SPEED, PLATFORM_I2C_SDA, PLATFORM_I2C_SCL);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_platform_i2c_init_pin_less_than_0_err(void)
{
    ret = platform_i2c_init(PLATFORM_I2C_HW, PLATFORM_I2C_SPEED, -1, PLATFORM_I2C_SCL);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = platform_i2c_init(PLATFORM_I2C_HW, PLATFORM_I2C_SPEED, PLATFORM_I2C_SDA, -1);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_platform_i2c_init_pin_greater_than_29_err(void)
{
    ret = platform_i2c_init(PLATFORM_I2C_HW, PLATFORM_I2C_SPEED, 30, PLATFORM_I2C_SCL);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = platform_i2c_init(PLATFORM_I2C_HW, PLATFORM_I2C_SPEED, PLATFORM_I2C_SDA, 30);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}

void test_platform_i2c_init_speed_greater_than_1Mbps_err(void)
{
    ret = platform_i2c_init(PLATFORM_I2C_HW, 1000001/* 1.000001 Mbps*/, PLATFORM_I2C_SDA, PLATFORM_I2C_SCL);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}

void test_platform_i2c_init_speed_less_than_1kbps_err(void)
{
    ret = platform_i2c_init(PLATFORM_I2C_HW, 999 /* 1 Kbps */, PLATFORM_I2C_SDA, PLATFORM_I2C_SCL);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_i2c_init_wrong_hw_err);
    RUN_TEST(test_platform_i2c_init_pin_less_than_0_err);
    RUN_TEST(test_platform_i2c_init_pin_greater_than_29_err);
    RUN_TEST(test_platform_i2c_init_speed_greater_than_1Mbps_err);
    RUN_TEST(test_platform_i2c_init_speed_less_than_1kbps_err);
    return UNITY_END();
}