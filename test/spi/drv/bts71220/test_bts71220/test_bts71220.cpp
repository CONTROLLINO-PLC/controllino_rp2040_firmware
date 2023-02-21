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
 
void test_bts71220_init_dev_ok()
{
    ret = bts71220_init_dev(&dev); /* Implies testing bts71220_read_std_diag */
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_bts71220_write_read_out_reg_ok()
{
    uint8_t txdata = 0x03;
    uint8_t rxdata = 0x00;
    ret = bts71220_write_reg(&dev, BTS71220_REG_OUT, txdata, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = bts71220_read_reg(&dev, BTS71220_REG_OUT, &rxdata, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(txdata, (rxdata & (~BTS71220_WRITE_MASK & 0xFF)));
}
 
void test_bts71220_write_read_only_reg_err()
{
    ret = bts71220_write_reg(&dev, BTS71220_REG_WRN_DIAG, 0x00, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_STD_DIAG, 0x00, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_ERR_DIAG, 0x00, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_RCS, 0x00, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_SRC, 0x00, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_bts71220_read_wrn_diag_ok()
{
    uint8_t rxdata;
    ret = bts71220_read_wrn_diag(&dev, &rxdata, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_TRUE(rxdata & (BTS71220_ERR_WARN_MASK | BTS71220_REG_CONT_MASK));
}
 
void test_bts71220_read_err_diag_ok()
{
    uint8_t rxdata;
    ret = bts71220_read_err_diag(&dev, &rxdata, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_TRUE(rxdata & (BTS71220_ERR_WARN_MASK | BTS71220_REG_CONT_MASK));
}
 
void test_bts71220_set_sense_mux_ok()
{
    bts71220_dcr_reg_t dcr_reg;
    ret = bts71220_set_sense_mux(&dev, BTS71220_DCR_MUX_IS_Z, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    ret = bts71220_read_reg(&dev, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, TEST_BTS71220_DAISY_CHAIN_NUMBER);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_Z, dcr_reg.mux);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_bts71220_set_default_cfg);
    RUN_TEST(test_bts71220_bts71220_init_hw_ok);
    RUN_TEST(test_bts71220_init_dev_ok);
    RUN_TEST(test_bts71220_write_read_out_reg_ok);
    RUN_TEST(test_bts71220_write_read_only_reg_err);
    RUN_TEST(test_bts71220_read_wrn_diag_ok);
    RUN_TEST(test_bts71220_read_err_diag_ok);
    RUN_TEST(test_bts71220_set_sense_mux_ok);
    return UNITY_END();
}
