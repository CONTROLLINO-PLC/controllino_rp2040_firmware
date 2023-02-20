#include <unity.h>
#include "hw_platform.h"
 
static platform_err_code_t ret;
 
void setUp(void)
{
    ret = platform_i2c_init(PLATFORM_I2C_HW, PLATFORM_I2C_SPEED, PLATFORM_I2C_SDA, PLATFORM_I2C_SCL);
}
 
void tearDown(void)
{}
 
void test_platform_i2c_init_ok(void)
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_platform_i2c_write_test_addr_ok(void)
{
    uint8_t dummy_txdata;
    ret = platform_i2c_write(PLATFORM_I2C_HW, TEST_I2C_ADDR, &dummy_txdata, sizeof(dummy_txdata));
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_platform_i2c_read_test_addr_ok(void)
{
    uint8_t dummy_rxdata;
    ret = platform_i2c_read(PLATFORM_I2C_HW, TEST_I2C_ADDR, &dummy_rxdata, sizeof(dummy_rxdata));
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_i2c_init_ok);
    RUN_TEST(test_platform_i2c_write_test_addr_ok);
    RUN_TEST(test_platform_i2c_read_test_addr_ok);
    return UNITY_END();
}