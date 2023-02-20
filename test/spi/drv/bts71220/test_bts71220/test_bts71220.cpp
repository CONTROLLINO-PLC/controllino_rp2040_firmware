#include <unity.h>
#include "hw_platform.h"
#include "bts71220.h"
 
static bts71220_cfg_t cfg;
static bts71220_t dev;
static bts71220_err_code_t ret;
 
void setUp(void)
{
    bts71220_set_default_cfg(&cfg);
    ret = bts71220_init_hw(&dev, &cfg);
}
 
void tearDown(void)
{}
 
void test_bts71220_set_default_cfg()
{
    bts71220_cfg_t def_cfg;
    bts71220_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MOSI, def_cfg.mosi_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MISO, def_cfg.miso_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SCK, def_cfg.sck_pin);
    TEST_ASSERT_EQUAL(BTS71220_CS, def_cfg.cs_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SPEED, def_cfg.spi_speed);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MODE_1, def_cfg.spi_mode);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MSBFIRST, def_cfg.spi_bit_order);
    TEST_ASSERT_EQUAL(BTS71220_DAISY_CHAIN_SIZE, def_cfg.dchain_size);
}
 
void test_bts71220_bts71220_init_hw_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_bts71220_generic_transfer_ok()
{
    uint8_t rxdata;
    ret = bts71220_generic_transfer(&dev, BTS71220_REG_STD_DIAG, &rxdata, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_TRUE(rxdata & BTS71220_DIAG_RES_MASK);
}
 
void test_bts71220_read_wrn_diag_ok()
{
    uint8_t rxdata;
    ret = bts71220_read_wrn_diag(&dev, &rxdata, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_TRUE(rxdata & BTS71220_DIAG_RES_MASK);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_bts71220_set_default_cfg);
    RUN_TEST(test_bts71220_bts71220_init_hw_ok);
    RUN_TEST(test_bts71220_generic_transfer_ok);
    RUN_TEST(test_bts71220_read_wrn_diag_ok);
    return UNITY_END();
}
