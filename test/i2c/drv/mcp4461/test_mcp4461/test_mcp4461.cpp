#include <unity.h>
#include "hw_platform.h"
#include "mcp4461.h"
 
static mcp4461_t dev;
static mcp4461_err_code_t ret;

#define TEST_INITIAL_MCP4461_REG_TCON_0_VALUE 0x01FF

void setUp(void)
{
    mcp4461_cfg_t cfg;
    mcp4461_set_default_cfg(&cfg);
    cfg.i2c_addr = MCP4461_DEV_ADDR_1;
    ret = mcp4461_init(&dev, &cfg);
}
 
void tearDown(void)
{}
 
void test_mcp4461_set_default_cfg()
{
    mcp4461_cfg_t def_cfg;
    mcp4461_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SDA, def_cfg.sda_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SCL, def_cfg.scl_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SPEED, def_cfg.i2c_speed);
    TEST_ASSERT_EQUAL(MCP4461_DEV_ADDR_0, def_cfg.i2c_addr);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_HW, def_cfg.i2c);
}
 
void test_mcp4461_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_mcp4461_read_reg_ok()
{
    uint16_t reg_value = 0x0000;
    ret = mcp4461_read_reg(&dev, MCP4461_REG_TCON_0, &reg_value);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(TEST_INITIAL_MCP4461_REG_TCON_0_VALUE, reg_value);
}

void test_mcp4461_write_reg_ok()
{
    uint16_t reg_initial_value;
    uint16_t reg_value;
    mcp4461_read_reg(&dev, MCP4461_REG_V_WIPER_0, &reg_initial_value);
    //
    ret = mcp4461_write_reg(&dev, MCP4461_REG_V_WIPER_0, 0x100);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    mcp4461_read_reg(&dev, MCP4461_REG_V_WIPER_0, &reg_value);
    TEST_ASSERT_EQUAL(reg_value, 0x100);
    //
    ret = mcp4461_write_reg(&dev, MCP4461_REG_V_WIPER_0, reg_initial_value);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    mcp4461_read_reg(&dev, MCP4461_REG_V_WIPER_0, &reg_value);
    TEST_ASSERT_EQUAL(reg_value, reg_initial_value);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mcp4461_set_default_cfg);
    RUN_TEST(test_mcp4461_init_ok);
    RUN_TEST(test_mcp4461_read_reg_ok);
    RUN_TEST(test_mcp4461_write_reg_ok);
    return UNITY_END();
}