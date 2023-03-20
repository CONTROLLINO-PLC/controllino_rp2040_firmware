#include <unity.h>
#include "hw_platform.h"
#include "mcp356x.h"
 
static mcp356x_t dev;
static mcp356x_err_code_t ret;
 
#define MCP356X_TEST_VOL_REF_MIN 0 /* 0 V */
#define MCP356X_TEST_VOL_REF_MAX 10000 /* 10000 mV or 10 V */
 
void setUp(void)
{
    mcp356x_cfg_t cfg;
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
    TEST_ASSERT_EQUAL(PLATFORM_SPI_HW, def_cfg.spi);
    TEST_ASSERT_EQUAL(MCP356X_MCLK, def_cfg.mclk_pin);
    TEST_ASSERT_EQUAL(MCP356X_INT, def_cfg.int_pin);
    TEST_ASSERT_EQUAL(MCP356X_INIT_CFG_0_REG, def_cfg.config_0_reg);
    TEST_ASSERT_EQUAL(MCP356X_INIT_CFG_1_REG, def_cfg.config_1_reg);
    TEST_ASSERT_EQUAL(MCP356X_INIT_CFG_2_REG, def_cfg.config_2_reg);
    TEST_ASSERT_EQUAL(MCP356X_INIT_CFG_3_REG, def_cfg.config_3_reg);
    TEST_ASSERT_EQUAL(MCP356X_INIT_IRQ_REG, def_cfg.irq_reg);
    TEST_ASSERT_EQUAL(MCP356X_INIT_MUX_REG, def_cfg.mux_reg);
    TEST_ASSERT_EQUAL(MCP356X_INIT_SCAN_REG, def_cfg.scan_reg);
    TEST_ASSERT_EQUAL(MCP356X_INIT_TIMER_REG, def_cfg.timer_reg);
}
 
void test_mcp356x_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_mcp356x_fast_cmd_ok()
{
    ret = mcp356x_write_fast_cmd(&dev, MCP356X_FAST_CMD_ADC_CONV_START);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_mcp356x_sread_ok()
{
    uint8_t cfg2_val = 0x00;
    ret = mcp356x_sread(&dev, MCP356X_REG_CFG_2, &cfg2_val, 1); /* Read CFG_2 wrote in mcp356x_init() */
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP356X_INIT_CFG_2_REG, cfg2_val);
}

void test_mcp356x_iread_ok()
{
    uint8_t rxdata[2];
    ret = mcp356x_iread(&dev, MCP356X_REG_CFG_2, rxdata, 2);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP356X_INIT_CFG_2_REG, rxdata[0]);
    TEST_ASSERT_EQUAL(MCP356X_INIT_CFG_3_REG, rxdata[1]);
}

void test_mcp356x_iwrite_ok()
{
    uint8_t txdata[2]; /* CFG_2 and CFG_3 */
    uint8_t rxdata[2];
    txdata[0] = MCP356X_CFG_2_BOOST_X_1 | MCP356X_CFG_2_GAIN_X_1 | MCP356X_CFG_2_AZ_MUX_DIS | MCP356X_CFG_2_AZ_VREF_DIS;
    txdata[1] = MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_CH_ADC | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS;
    ret = mcp356x_iwrite(&dev, MCP356X_REG_CFG_2, txdata, 2);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    mcp356x_iread(&dev, MCP356X_REG_CFG_2, rxdata, 2);
    TEST_ASSERT_EQUAL(txdata[0], rxdata[0]);
    TEST_ASSERT_EQUAL(txdata[1], rxdata[1]);
}
 
void test_mcp356x_read_adc_format_ok()
{
    uint32_t adc_data;
    uint32_t max_resolution;
    uint8_t sgn;
    uint8_t cfg3_val;
    cfg3_val = MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_DEF | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS;
    mcp356x_iwrite(&dev, MCP356X_REG_CFG_3, &cfg3_val, 1);
    ret = mcp356x_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP356X_RES_23_BITS, max_resolution);
    //
    cfg3_val = MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_LEFT_JUST | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS;
    mcp356x_iwrite(&dev, MCP356X_REG_CFG_3, &cfg3_val, 1);
    ret = mcp356x_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP356X_RES_23_BITS, max_resolution);
    //
    cfg3_val = MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_EXT_ADC | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS;
    mcp356x_iwrite(&dev, MCP356X_REG_CFG_3, &cfg3_val, 1);
    ret = mcp356x_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP356X_RES_24_BITS, max_resolution);
    //
    cfg3_val = MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_CH_ADC | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS;
    mcp356x_iwrite(&dev, MCP356X_REG_CFG_3, &cfg3_val, 1);
    ret = mcp356x_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP356X_RES_24_BITS, max_resolution);
}
 
void test_mcp356x_read_voltage_ok()
{
    uint32_t vol_val;
    ret = mcp356x_read_voltage(&dev, MCP356X_TEST_VOL_REF_MIN, MCP356X_TEST_VOL_REF_MAX, &vol_val);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_GREATER_OR_EQUAL(0, vol_val);
}
 
void test_mcp356x_read_voltage_ref_min_greater_than_ref_max_err()
{
    uint32_t vol_val;
    ret = mcp356x_read_voltage(&dev, MCP356X_TEST_VOL_REF_MAX, MCP356X_TEST_VOL_REF_MIN, &vol_val);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mcp356x_set_default_cfg);
    RUN_TEST(test_mcp356x_init_ok);
    RUN_TEST(test_mcp356x_fast_cmd_ok);
    RUN_TEST(test_mcp356x_sread_ok);
    RUN_TEST(test_mcp356x_iread_ok);
    RUN_TEST(test_mcp356x_iwrite_ok);
    RUN_TEST(test_mcp356x_read_adc_format_ok);
    RUN_TEST(test_mcp356x_read_voltage_ok);
    RUN_TEST(test_mcp356x_read_voltage_ref_min_greater_than_ref_max_err);
    return UNITY_END();
}
