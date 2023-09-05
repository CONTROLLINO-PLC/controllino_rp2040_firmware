#include <unity.h>
#include "hw_platform.h"
#include "mcp3564.h"
 
static mcp3564_t dev;
static mcp3564_err_code_t ret;
 
#define MCP3564_TEST_VOL_REF_MIN 0 /* 0 V */
#define MCP3564_TEST_VOL_REF_MAX 10000 /* 10000 mV or 10 V */
 
void setUp(void)
{
    mcp3564_cfg_t cfg;
    mcp3564_set_default_cfg(&cfg);
    ret = mcp3564_init(&dev, &cfg);
}
 
void tearDown(void)
{
    mcp3564_write_fast_cmd(&dev, MCP3564_FAST_CMD_DEV_FULL_RESET);
}
 
void test_mcp3564_set_default_cfg()
{
    mcp3564_cfg_t def_cfg;
    mcp3564_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MOSI, def_cfg.mosi_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MISO, def_cfg.miso_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SCK, def_cfg.sck_pin);
    TEST_ASSERT_EQUAL(MCP3564_CS, def_cfg.cs_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SPEED, def_cfg.spi_speed);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MODE_1, def_cfg.spi_mode);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MSBFIRST, def_cfg.spi_bit_order);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_HW, def_cfg.spi);
    TEST_ASSERT_EQUAL(MCP3564_MCLK, def_cfg.mclk_pin);
    TEST_ASSERT_EQUAL(MCP3564_INT, def_cfg.int_pin);
    TEST_ASSERT_EQUAL(MCP3564_INIT_CFG_0_REG, def_cfg.config_0_reg);
    TEST_ASSERT_EQUAL(MCP3564_INIT_CFG_1_REG, def_cfg.config_1_reg);
    TEST_ASSERT_EQUAL(MCP3564_INIT_CFG_2_REG, def_cfg.config_2_reg);
    TEST_ASSERT_EQUAL(MCP3564_INIT_CFG_3_REG, def_cfg.config_3_reg);
    TEST_ASSERT_EQUAL(MCP3564_INIT_IRQ_REG, def_cfg.irq_reg);
    TEST_ASSERT_EQUAL(MCP3564_INIT_MUX_REG, def_cfg.mux_reg);
    TEST_ASSERT_EQUAL(MCP3564_INIT_SCAN_REG, def_cfg.scan_reg);
    TEST_ASSERT_EQUAL(MCP3564_INIT_TIMER_REG, def_cfg.timer_reg);
}
 
void test_mcp3564_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_mcp3564_fast_cmd_ok()
{
    ret = mcp3564_write_fast_cmd(&dev, MCP3564_FAST_CMD_ADC_CONV_START);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_mcp3564_sread_ok()
{
    uint8_t cfg2_val = 0x00;
    ret = mcp3564_sread(&dev, MCP3564_REG_CFG_2, &cfg2_val, 1); /* Read CFG_2 wrote in mcp3564_init() */
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP3564_INIT_CFG_2_REG, cfg2_val);
}
 
void test_mcp3564_iread_ok()
{
    uint8_t rxdata[2];
    ret = mcp3564_iread(&dev, MCP3564_REG_CFG_2, rxdata, 2);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP3564_INIT_CFG_2_REG, rxdata[0]);
    TEST_ASSERT_EQUAL(MCP3564_INIT_CFG_3_REG, rxdata[1]);
}
 
void test_mcp3564_iwrite_ok()
{
    uint8_t txdata[2]; /* CFG_2 and CFG_3 */
    uint8_t rxdata[2];
    txdata[0] = MCP3564_CFG_2_BOOST_X_1 | MCP3564_CFG_2_GAIN_X_1 | MCP3564_CFG_2_AZ_MUX_DIS | MCP3564_CFG_2_AZ_VREF_DIS;
    txdata[1] = MCP3564_CFG_3_CONV_MODE_CONT | MCP3564_CFG_3_DATA_FORMAT_CH_ADC | MCP3564_CFG_3_CRC_COM_DIS | MCP3564_CFG_3_CRC_GAIN_CAL_DIS;
    ret = mcp3564_iwrite(&dev, MCP3564_REG_CFG_2, txdata, 2);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    mcp3564_iread(&dev, MCP3564_REG_CFG_2, rxdata, 2);
    TEST_ASSERT_EQUAL(txdata[0], rxdata[0]);
    TEST_ASSERT_EQUAL(txdata[1], rxdata[1]);
}
 
void test_mcp3564_set_gain_ok()
{
    uint8_t config_2_reg;
    mcp3564_iread(&dev, MCP3564_REG_CFG_2, &config_2_reg, 1);
    TEST_ASSERT_EQUAL(MCP3564_CFG_2_GAIN_X_2, config_2_reg & MCP3564_CFG_2_GAIN_MASK);
    ret = mcp3564_set_gain(&dev, MCP3564_GAIN_X_1);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    mcp3564_iread(&dev, MCP3564_REG_CFG_2, &config_2_reg, 1);
    TEST_ASSERT_EQUAL(MCP3564_CFG_2_GAIN_X_1, config_2_reg & MCP3564_CFG_2_GAIN_MASK);
    ret = mcp3564_set_gain(&dev, MCP3564_GAIN_X_2);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    mcp3564_iread(&dev, MCP3564_REG_CFG_2, &config_2_reg, 1);
    TEST_ASSERT_EQUAL(MCP3564_CFG_2_GAIN_X_2, config_2_reg & MCP3564_CFG_2_GAIN_MASK);
}
 
void test_mcp3564_read_adc_format_ok()
{
    uint32_t adc_data;
    uint32_t max_resolution;
    uint8_t sgn;
    uint8_t cfg3_val;
    cfg3_val = MCP3564_CFG_3_CONV_MODE_CONT | MCP3564_CFG_3_DATA_FORMAT_DEF | MCP3564_CFG_3_CRC_COM_DIS | MCP3564_CFG_3_CRC_GAIN_CAL_DIS;
    mcp3564_iwrite(&dev, MCP3564_REG_CFG_3, &cfg3_val, 1);
    ret = mcp3564_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP3564_RES_23_BITS, max_resolution);
    //
    cfg3_val = MCP3564_CFG_3_CONV_MODE_CONT | MCP3564_CFG_3_DATA_FORMAT_LEFT_JUST | MCP3564_CFG_3_CRC_COM_DIS | MCP3564_CFG_3_CRC_GAIN_CAL_DIS;
    mcp3564_iwrite(&dev, MCP3564_REG_CFG_3, &cfg3_val, 1);
    ret = mcp3564_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP3564_RES_23_BITS, max_resolution);
    //
    cfg3_val = MCP3564_CFG_3_CONV_MODE_CONT | MCP3564_CFG_3_DATA_FORMAT_EXT_ADC | MCP3564_CFG_3_CRC_COM_DIS | MCP3564_CFG_3_CRC_GAIN_CAL_DIS;
    mcp3564_iwrite(&dev, MCP3564_REG_CFG_3, &cfg3_val, 1);
    ret = mcp3564_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP3564_RES_24_BITS, max_resolution);
    //
    cfg3_val = MCP3564_CFG_3_CONV_MODE_CONT | MCP3564_CFG_3_DATA_FORMAT_CH_ADC | MCP3564_CFG_3_CRC_COM_DIS | MCP3564_CFG_3_CRC_GAIN_CAL_DIS;
    mcp3564_iwrite(&dev, MCP3564_REG_CFG_3, &cfg3_val, 1);
    ret = mcp3564_read_raw_adc(&dev, &adc_data, &sgn, &max_resolution);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP3564_RES_24_BITS, max_resolution);
}
 
void test_mcp3564_read_adc_mux_ok()
{
    uint32_t adc_data;
    uint8_t mux;
    uint16_t delay = 500;
    ret = mcp3564_read_adc_mux(&dev, &adc_data, MCP3564_MUX_VIN_POS_CH0, MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS, delay);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_GREATER_OR_EQUAL(0, adc_data);
    // Check if MUX is set correctly
    mcp3564_iread(&dev, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_POS_CH0 | MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS, mux);
}
 
void test_mcp3564_read_voltage_ok()
{
    uint32_t vol_val;
    ret = mcp3564_read_voltage(&dev, MCP3564_TEST_VOL_REF_MIN, MCP3564_TEST_VOL_REF_MAX, &vol_val);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_GREATER_OR_EQUAL(0, vol_val);
}
 
void test_mcp3564_read_voltage_ref_min_greater_than_ref_max_err()
{
    uint32_t vol_val;
    ret = mcp3564_read_voltage(&dev, MCP3564_TEST_VOL_REF_MAX, MCP3564_TEST_VOL_REF_MIN, &vol_val);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mcp3564_set_default_cfg);
    RUN_TEST(test_mcp3564_init_ok);
    RUN_TEST(test_mcp3564_fast_cmd_ok);
    RUN_TEST(test_mcp3564_sread_ok);
    RUN_TEST(test_mcp3564_iread_ok);
    RUN_TEST(test_mcp3564_iwrite_ok);
    RUN_TEST(test_mcp3564_set_gain_ok);
    RUN_TEST(test_mcp3564_read_adc_format_ok);
    RUN_TEST(test_mcp3564_read_adc_mux_ok);
    RUN_TEST(test_mcp3564_read_voltage_ok);
    RUN_TEST(test_mcp3564_read_voltage_ref_min_greater_than_ref_max_err);
    return UNITY_END();
}
