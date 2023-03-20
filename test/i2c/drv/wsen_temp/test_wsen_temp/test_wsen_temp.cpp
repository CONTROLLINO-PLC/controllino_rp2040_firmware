#include <unity.h>
#include "hw_platform.h"
#include "wsen_temp.h"
 
static wsen_temp_t dev;
static wsen_temp_err_code_t ret;
 
#define WSEN_TEMP_TEST_SET_GET_HIGHT_LIMIT 40.5F
#define WSEN_TEMP_TEST_SET_GET_LOW_LIMIT   1.5F
#define WSEN_TEMP_TEST_SET_GET_LIMIT_ERROR 0.2F
 
void setUp(void)
{
    wsen_temp_cfg_t cfg;
    wsen_temp_set_default_cfg(&cfg);
    ret = wsen_temp_init(&dev, &cfg);
}
 
void tearDown(void)
{
    wsen_temp_sw_rst(&dev);
}
 
void test_wsen_temp_set_default_cfg()
{
    wsen_temp_cfg_t def_cfg;
    wsen_temp_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SDA, def_cfg.sda_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SCL, def_cfg.scl_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SPEED, def_cfg.i2c_speed);
    TEST_ASSERT_EQUAL(WSEN_TEMP_ADDRESS_SAO_GND, def_cfg.i2c_addr);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_HW, def_cfg.i2c);
    TEST_ASSERT_EQUAL(WSEN_TEMP_INT, def_cfg.int_pin);
    TEST_ASSERT_EQUAL(WSEN_TEMP_CTRL_FREE_RUN_EN, def_cfg.ctrl_reg.free_run);
    TEST_ASSERT_EQUAL(WSEN_TEMP_CTRL_BLOCK_DATA_UPD_EN, def_cfg.ctrl_reg.block_data_upd);
    TEST_ASSERT_EQUAL(WSEN_TEMP_CTRL_ODR_50HZ, def_cfg.ctrl_reg.out_rate);
}
 
void test_wsen_temp_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_wsen_temp_get_ctrl_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    wsen_temp_ctrl_t ctrl_reg;
    ret = wsen_temp_get_ctrl(&dev, &ctrl_reg);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(WSEN_TEMP_CTRL_FREE_RUN_EN, ctrl_reg.free_run);
    TEST_ASSERT_EQUAL(WSEN_TEMP_CTRL_BLOCK_DATA_UPD_EN, ctrl_reg.block_data_upd);
    TEST_ASSERT_EQUAL(WSEN_TEMP_CTRL_ODR_50HZ, ctrl_reg.out_rate);
}
 
void test_wsen_temp_set_get_high_lim_ok()
{
    float celsius = 0;
    ret = wsen_temp_set_high_lim(&dev, WSEN_TEMP_TEST_SET_GET_HIGHT_LIMIT);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = wsen_temp_get_high_lim(&dev, &celsius);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_LESS_OR_EQUAL(
        WSEN_TEMP_TEST_SET_GET_LIMIT_ERROR, celsius - WSEN_TEMP_TEST_SET_GET_HIGHT_LIMIT
    );
}
 
void test_wsen_temp_set_get_low_lim_ok()
{
    float celsius = 0;
    ret = wsen_temp_set_low_lim(&dev, WSEN_TEMP_TEST_SET_GET_LOW_LIMIT);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = wsen_temp_get_low_lim(&dev, &celsius);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_LESS_OR_EQUAL(
        WSEN_TEMP_TEST_SET_GET_LIMIT_ERROR, celsius - WSEN_TEMP_TEST_SET_GET_LOW_LIMIT
    );
}
 
void test_wsen_temp_set_lim_less_than_minus_39_68_err()
{
    ret = wsen_temp_set_high_lim(&dev, -40.0F);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = wsen_temp_set_low_lim(&dev, -40.0F);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_wsen_temp_set_lim_greater_than_122_88_err()
{
    ret = wsen_temp_set_high_lim(&dev, 123.0F);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = wsen_temp_set_low_lim(&dev, 123.0F);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_wsen_temp_get_status()
{
    wsen_temp_status_t status;
    wsen_temp_set_low_lim(&dev, 50.0F);
    wsen_temp_set_high_lim(&dev, 0.0F);
    platform_sleep_ms(100);
    ret = wsen_temp_get_status(&dev, &status);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_TRUE(status.over_lim);
    TEST_ASSERT_TRUE(status.under_lim);
    TEST_ASSERT_FALSE(status.busy);
}
 
void test_wsen_temp_read_temp_ok()
{
    float celsius;
    uint16_t raw_temp;
    ret = wsen_temp_get_celsius(&dev, &celsius);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = wsen_temp_get_raw(&dev, &raw_temp);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_GREATER_THAN(-40, celsius);
    TEST_ASSERT_LESS_THAN(125, celsius);
    TEST_ASSERT_EQUAL(celsius, (float)raw_temp * 0.01F);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_wsen_temp_set_default_cfg);
    RUN_TEST(test_wsen_temp_init_ok);
    RUN_TEST(test_wsen_temp_get_ctrl_ok);
    RUN_TEST(test_wsen_temp_set_get_high_lim_ok);
    RUN_TEST(test_wsen_temp_set_get_low_lim_ok);
    RUN_TEST(test_wsen_temp_set_lim_less_than_minus_39_68_err);
    RUN_TEST(test_wsen_temp_set_lim_greater_than_122_88_err);
    RUN_TEST(test_wsen_temp_get_status);
    RUN_TEST(test_wsen_temp_read_temp_ok);
    return UNITY_END();
}