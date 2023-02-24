#include <unity.h>
#include "hw_platform.h"
#include "cy8c95xx.h"
 
#define TEST_CY8C95XX_GPIO 0 
static cy8c95xx_cfg_t cfg;
static cy8c95xx_t dev;
static cy8c95xx_err_code_t ret;
 
void setUp(void)
{
    cy8c95xx_set_default_cfg(&cfg);
    ret = cy8c95xx_init(&dev, &cfg);
}
 
void tearDown(void)
{
}
 
void test_cy8c95xx_set_default_cfg()
{
    cy8c95xx_cfg_t def_cfg;
    cy8c95xx_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SDA, def_cfg.sda_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SCL, def_cfg.scl_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SPEED, def_cfg.i2c_speed);
    TEST_ASSERT_EQUAL(CY8C95XX_DEV_ADDR_GND, def_cfg.i2c_addr);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_HW, def_cfg.i2c);
    TEST_ASSERT_EQUAL(CY8C95XX_RST, def_cfg.rst_pin);
    TEST_ASSERT_EQUAL(CY8C95XX_INT, def_cfg.int_pin);
}
 
void test_cy8c95xx_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_cy8c95xx_set_default_cfg);
    RUN_TEST(test_cy8c95xx_init_ok);
    return UNITY_END();
}