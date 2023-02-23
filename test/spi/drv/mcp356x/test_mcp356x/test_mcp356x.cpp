#include <unity.h>
#include "hw_platform.h"
#include "mcp356x.h"
 
static mcp356x_cfg_t cfg;
static mcp356x_t dev;
static mcp356x_err_code_t ret;
 
void setUp(void)
{
    mcp356x_set_default_cfg(&cfg);
    ret = mcp356x_init(&dev, &cfg);
}
 
void tearDown(void)
{
    mcp356x_write_fast_cmd(&dev, MCP356X_FAST_CMD_DEV_FULL_RESET);
}
 
void test_mcp356x_set_default_cfg()
{
    mcp356x_cfg_t def_cfg;
    mcp356x_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MOSI, def_cfg.mosi_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MISO, def_cfg.miso_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SCK, def_cfg.sck_pin);
    TEST_ASSERT_EQUAL(MCP356X_CS, def_cfg.cs_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SPEED, def_cfg.spi_speed);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MODE_1, def_cfg.spi_mode);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MSBFIRST, def_cfg.spi_bit_order);
    TEST_ASSERT_EQUAL(MCP356X_MCLK, def_cfg.mclk_pin);
    TEST_ASSERT_EQUAL(MCP356X_INT, def_cfg.int_pin);
    TEST_ASSERT_EQUAL(MCP356X_CFG_0_VREF_INT | MCP356X_CFG_0_CLK_INT_NO_OUT | MCP356X_CFG_0_CS_SEL_NONE | MCP356X_CFG_0_MODE_CONV, def_cfg.config_0_reg);
    TEST_ASSERT_EQUAL(MCP356X_CFG_1_PRE_1 | MCP356X_CFG_1_OSR_4096, def_cfg.config_1_reg);
    TEST_ASSERT_EQUAL(MCP356X_CFG_2_BOOST_X_1 | MCP356X_CFG_2_GAIN_X_2 | MCP356X_CFG_2_AZ_MUX_DIS | MCP356X_CFG_2_AZ_VREF_DIS, def_cfg.config_2_reg);
    TEST_ASSERT_EQUAL(MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_DEF | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS, def_cfg.config_3_reg);
    TEST_ASSERT_EQUAL(MCP356X_IRQ_MODE_IRQ | MCP356X_IRQ_MODE_LOGIC_HIGH | MCP356X_IRQ_FASTCMD_EN | MCP356X_IRQ_STP_EN, def_cfg.irq_reg);
    TEST_ASSERT_EQUAL(MCP356X_MUX_VIN_POS_CH0 | MCP356X_MUX_VIN_NEG_VREF_EXT_MINUS, def_cfg.mux_reg);
    TEST_ASSERT_EQUAL(MCP356X_SCAN_DLY_NO_DELAY, def_cfg.scan_reg);
    TEST_ASSERT_EQUAL(MCP356X_TIMER_DLY_NO_DELAY, def_cfg.timer_reg);
}
 
void test_mcp356x_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mcp356x_set_default_cfg);
    RUN_TEST(test_mcp356x_init_ok);
    return UNITY_END();
}
