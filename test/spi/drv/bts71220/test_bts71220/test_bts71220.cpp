#include <unity.h>
#include "hw_platform.h"
#include "bts71220.h"
 
static bts71220_t dev;
static bts71220_err_code_t ret;
 
void setUp(void)
{
    bts71220_cfg_t cfg;
    bts71220_set_default_cfg(&cfg);
    ret = bts71220_init(&dev, &cfg);
}
 
void tearDown(void)
{
    for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++)
        bts71220_write_reg(&dev, BTS71220_REG_OUT, 0x00, i);
}
 
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
    TEST_ASSERT_EQUAL(PLATFORM_SPI_HW, def_cfg.spi);
    TEST_ASSERT_EQUAL(BTS71220_DAISY_CHAIN_SIZE, def_cfg.dchain_size);
}
 
void test_bts71220_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_bts71220_read_reg_ok()
{
    for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++) {
        uint8_t rxdata = 0xFF;
        ret = bts71220_read_reg(&dev, BTS71220_REG_OUT, &rxdata, i);
        TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
        TEST_ASSERT_EQUAL(0x00, (rxdata & (~BTS71220_WRITE_MASK & 0xFF)));
    }
}
 
void test_bts71220_write_reg_ok()
{
    for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++) {
        uint8_t txdata = 0x03;
        uint8_t rxdata = 0x00;
        ret = bts71220_write_reg(&dev, BTS71220_REG_OUT, txdata, i);
        TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
        bts71220_read_reg(&dev, BTS71220_REG_OUT, &rxdata, i);
        TEST_ASSERT_EQUAL(txdata, (rxdata & (~BTS71220_WRITE_MASK & 0xFF)));
    }
}
 
void test_bts71220_try_write_read_only_reg_err()
{
    ret = bts71220_write_reg(&dev, BTS71220_REG_WRN_DIAG, 0x00, 0);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_STD_DIAG, 0x00, 0);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_ERR_DIAG, 0x00, 0);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_RCS, 0x00, 0);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = bts71220_write_reg(&dev, BTS71220_REG_SRC, 0x00, 0);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_bts71220_read_wrn_diag_ok()
{
    for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++) {
        uint8_t rxdata;
        ret = bts71220_read_wrn_diag(&dev, &rxdata, i);
        TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
        TEST_ASSERT_TRUE(rxdata & (BTS71220_ERR_WARN_MASK | BTS71220_REG_CONT_MASK));
    }
}
 
void test_bts71220_read_err_diag_ok()
{
    for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++) {
        uint8_t rxdata;
        ret = bts71220_read_err_diag(&dev, &rxdata, i);
        TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
        TEST_ASSERT_TRUE(rxdata & (BTS71220_ERR_WARN_MASK | BTS71220_REG_CONT_MASK));
    }
}
 
void test_bts71220_set_sense_mux_ok()
{
    for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++) {
        bts71220_dcr_reg_t dcr_reg;
        ret = bts71220_set_sense_mux(&dev, BTS71220_DCR_MUX_IS_Z, i);
        TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
        bts71220_read_reg(&dev, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, i);
        TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_Z, dcr_reg.mux);
    }
}
 
void test_bts71220_mux_sleep_mode_after_init()
{
    for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++) {
        bts71220_dcr_reg_t dcr_reg;
        bts71220_read_reg(&dev, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, i);
        TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    }
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_bts71220_set_default_cfg);
    RUN_TEST(test_bts71220_init_ok);
    RUN_TEST(test_bts71220_read_reg_ok);
    RUN_TEST(test_bts71220_write_reg_ok);
    RUN_TEST(test_bts71220_try_write_read_only_reg_err);
    RUN_TEST(test_bts71220_read_wrn_diag_ok);
    RUN_TEST(test_bts71220_read_err_diag_ok);
    RUN_TEST(test_bts71220_set_sense_mux_ok);
    RUN_TEST(test_bts71220_mux_sleep_mode_after_init);
    return UNITY_END();
}
