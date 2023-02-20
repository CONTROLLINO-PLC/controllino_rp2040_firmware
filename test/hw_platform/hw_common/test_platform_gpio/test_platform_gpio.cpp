#include <unity.h>
#include "test_config.h"
#include "hw_platform.h"
 
static int pin;
static platform_gpio_dir_t dir;
static platform_gpio_pull_mod_t pull;
static platform_err_code_t ret;
 
void setUp(void)
{
    pin = TEST_GPIO;
    dir = PLATFORM_GPIO_IN;
    pull = PLATFORM_GPIO_PULL_DOWN;
    ret = PLATFORM_OK;
    ret = platform_gpio_init(pin, dir, pull);
}
 
void tearDown(void)
{}
 
void test_platform_gpio_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_platform_gpio_set_ok()
{
    dir = PLATFORM_GPIO_OUT;
    platform_gpio_init(pin, dir, pull);
    ret = platform_gpio_set(pin, true);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);    
}
 
void test_platform_gpio_get_ok()
{
    bool val;
    ret = platform_gpio_get(pin, &val);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_platform_gpio_pull_up_default_true()
{
    bool val;
    pull = PLATFORM_GPIO_PULL_UP;
    platform_gpio_init(pin, dir, pull);
    platform_gpio_get(pin, &val);
    TEST_ASSERT_TRUE(val);
}
 
void test_platform_gpio_pull_down_default_false()
{
    bool val;
    pull = PLATFORM_GPIO_PULL_DOWN;
    platform_gpio_init(pin, dir, pull);
    platform_gpio_get(pin, &val);
    TEST_ASSERT_FALSE(val);
}
 
void test_platform_gpio_pull_disabled_default_false()
{
    bool val;
    pull = PLATFORM_GPIO_PULL_DISABLED;
    platform_gpio_init(pin, dir, pull);
    platform_gpio_get(pin, &val);
    TEST_ASSERT_FALSE(val);
}
 
void test_platform_gpio_out_set_get()
{
    bool val = false;
    dir = PLATFORM_GPIO_OUT;
    platform_gpio_init(pin, dir, pull);
    platform_gpio_set(pin, true);
    platform_gpio_get(pin, &val);
    TEST_ASSERT_TRUE(val);
    platform_gpio_set(pin, false);
    platform_gpio_get(pin, &val);
    TEST_ASSERT_FALSE(val);
}
 
void test_platform_gpio_in_ignore_set()
{
    bool val;
    platform_gpio_set(pin, true);
    platform_gpio_get(pin, &val);
    TEST_ASSERT_FALSE(val);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_gpio_init_ok);
    RUN_TEST(test_platform_gpio_set_ok);
    RUN_TEST(test_platform_gpio_get_ok);
    RUN_TEST(test_platform_gpio_pull_up_default_true);
    RUN_TEST(test_platform_gpio_pull_down_default_false);
    RUN_TEST(test_platform_gpio_pull_disabled_default_false);
    RUN_TEST(test_platform_gpio_out_set_get);
    RUN_TEST(test_platform_gpio_in_ignore_set);
    return UNITY_END();
}