#include <unity.h>
#include "hw_platform.h"
#include "adg728.h"
 
static adg728_t dev;
static adg728_err_code_t ret;
 
void setUp(void)
{
    adg728_cfg_t cfg;
    adg728_set_default_cfg(&cfg);
    ret = adg728_init(&dev, &cfg);
}
 
void tearDown(void)
{}
 
void test_adg728_set_default_cfg()
{
    adg728_cfg_t def_cfg;
    adg728_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SDA, def_cfg.sda_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SCL, def_cfg.scl_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SPEED, def_cfg.i2c_speed);
    TEST_ASSERT_EQUAL(ADG728_DEV_ADDR_0, def_cfg.i2c_addr);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_HW, def_cfg.i2c);
}
 
void test_adg728_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_adg728_set_get_channel_ok()
{
    adg728_channel_t rx_channel = ADG728_CHANNEL_0;
    // ADG728_CHANNEL_OFF at the beginning
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_OFF, rx_channel);
    // ADG728_CHANNEL_0
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_0);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_0, rx_channel);
    // ADG728_CHANNEL_1
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_1);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_1, rx_channel);
    // ADG728_CHANNEL_2
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_2);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_2, rx_channel);
    // ADG728_CHANNEL_3
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_3);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_3, rx_channel);
    // ADG728_CHANNEL_4
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_4);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_4, rx_channel);
    // ADG728_CHANNEL_5
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_5);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_5, rx_channel);
    // ADG728_CHANNEL_6
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_6);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_6, rx_channel);
    // ADG728_CHANNEL_7
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_7);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_7, rx_channel);
    // ADG728_CHANNEL_OFF
    ret = adg728_set_channel(&dev, ADG728_CHANNEL_OFF);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = adg728_get_channel(&dev, &rx_channel);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_OFF, rx_channel);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_adg728_set_default_cfg);
    RUN_TEST(test_adg728_init_ok);
    RUN_TEST(test_adg728_set_get_channel_ok);
    return UNITY_END();
}