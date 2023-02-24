#include <unity.h>
#include "hw_platform.h"
#include "cy8c95xx.h"
 
uint8_t TEST_CY8C95XX_GPIO = 4; /* Most be a non used GPIO */
uint8_t TEST_CY8C95XX_ADDR = CY8C95XX_DEV_ADDR_GND;
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
 
void test_cy8c95xx_pin_mode_ok()
{
    uint8_t dir;
    uint8_t pull_up_en;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_UP);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = cy8c95xx_write_byte(&dev, CY8C95XX_REG_PORT_SEL, (0x00 + (TEST_CY8C95XX_GPIO / 8)));
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = cy8c95xx_read_bit(&dev, CY8C95XX_REG_PORT_DIR, (TEST_CY8C95XX_GPIO % 8), &dir);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(CY8C95XX_GPIO_IN, dir);
    ret = cy8c95xx_read_bit(&dev, CY8C95XX_REG_PULL_UP, (TEST_CY8C95XX_GPIO % 8), &pull_up_en);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(1, pull_up_en);
}
 
void test_cy8c95xx_read_pin_ok()
{
    uint8_t state;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_UP);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = cy8c95xx_read_pin(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(1, state);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_cy8c95xx_set_default_cfg);
    RUN_TEST(test_cy8c95xx_init_ok);
    RUN_TEST(test_cy8c95xx_pin_mode_ok);
    RUN_TEST(test_cy8c95xx_read_pin_ok);
    return UNITY_END();
}