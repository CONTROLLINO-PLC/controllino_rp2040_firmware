#include <unity.h>
#include "hw_platform.h"
#include "ad5664.h"
#include "math.h"
 
#define AD5664_TEST_VOL_REF_MAX 10000 /* 10000 mV or 10 V*/
uint16_t TEST_AD5664_DAC_DATA = 0x7FFF;
static ad5664_t dev;
static ad5664_err_code_t ret;
 
void setUp(void)
{
    ad5664_cfg_t cfg;
    ad5664_set_default_cfg(&cfg);
    ret = ad5664_init(&dev, &cfg);
}
 
void tearDown(void)
{
    ad5664_sw_reset(&dev, AD5664_SW_RST_FULL);
}
 
void test_ad5664_set_default_cfg()
{
    ad5664_cfg_t def_cfg;
    ad5664_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MOSI, def_cfg.mosi_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MISO, def_cfg.miso_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SCK, def_cfg.sck_pin);
    TEST_ASSERT_EQUAL(AD5664_CS, def_cfg.cs_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SPEED, def_cfg.spi_speed);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MODE_1, def_cfg.spi_mode);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MSBFIRST, def_cfg.spi_bit_order);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_HW, def_cfg.spi);
    TEST_ASSERT_EQUAL(AD5664_RESOLUTION, def_cfg.resolution);
}
 
void test_ad5664_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_write_input_reg_ok()
{
    ret = ad5664_write_input_reg(&dev, AD5664_CH_ADDR_D, TEST_AD5664_DAC_DATA);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_update_dac_reg_ok()
{
    ret = ad5664_update_dac_reg(&dev, AD5664_CH_ADDR_D);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_write_input_reg_update_all_dac_ok()
{
    ret = ad5664_write_input_reg_update_all_dac(&dev, AD5664_CH_ADDR_B, TEST_AD5664_DAC_DATA);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_write_update_dac_reg_ok()
{
    ret = ad5664_write_update_dac_reg(&dev, AD5664_CH_ADDR_ALL, TEST_AD5664_DAC_DATA);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_set_pwr_ok()
{
    ret = ad5664_set_pwr(&dev, AD5664_PWR_MODE_POWERDOWN_100K, AD5664_CH_SELECT_D);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_set_ldev_ok()
{
    ret = ad5664_set_ldev(&dev, AD5664_CH_SELECT_D);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_set_ldev_greater_than_0xF_ignored()
{
    ret = ad5664_set_ldev(&dev, AD5664_CH_SELECT_D & 0xFFFF);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_set_ch_voltage()
{
    /* Should have same efect as test_ad5664_write_input_reg_ok and then test_ad5664_update_dac_reg_ok*/
    uint16_t vol_val = round((float)TEST_AD5664_DAC_DATA / (float)AD5664_RESOLUTION * (float)AD5664_TEST_VOL_REF_MAX);
    ret = ad5664_set_ch_voltage(&dev, AD5664_CH_ADDR_D, vol_val, AD5664_TEST_VOL_REF_MAX);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_ad5664_set_ch_voltage_vol_val_greater_than_vol_ref_max_err()
{
    ret = ad5664_set_ch_voltage(&dev, AD5664_CH_ADDR_A, AD5664_TEST_VOL_REF_MAX, AD5664_TEST_VOL_REF_MAX / 2);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ad5664_set_default_cfg);
    RUN_TEST(test_ad5664_init_ok);
    RUN_TEST(test_ad5664_write_input_reg_ok);
    RUN_TEST(test_ad5664_update_dac_reg_ok);
    RUN_TEST(test_ad5664_write_input_reg_update_all_dac_ok);
    RUN_TEST(test_ad5664_write_update_dac_reg_ok);
    RUN_TEST(test_ad5664_set_pwr_ok);
    RUN_TEST(test_ad5664_set_ldev_ok);
    RUN_TEST(test_ad5664_set_ldev_greater_than_0xF_ignored);
    RUN_TEST(test_ad5664_set_ch_voltage);
    RUN_TEST(test_ad5664_set_ch_voltage_vol_val_greater_than_vol_ref_max_err);
    return UNITY_END();
}