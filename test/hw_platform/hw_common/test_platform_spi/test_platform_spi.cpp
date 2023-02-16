#include <unity.h>
#include "unity_test_runner.h"
#include "hw_platform.h"
 
#define PLATFORM_SPI_MODE_WRONG (PLATFORM_SPI_MODE_3 + 1)
#define PLATFORM_SPI_BIT_ORDER_WRONG (PLATFORM_SPI_MSBFIRST + 1)
static platform_err_code_t ret;
 
void setUp(void)
{
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MOSI, PLATFORM_SPI_MISO, PLATFORM_SPI_SCK);
}
 
void tearDown(void)
{}

void test_platform_spi_init_ok(void)
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_platform_spi_set_config_ok(void)
{
    ret = platform_spi_set_config(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MODE_0, PLATFORM_SPI_MSBFIRST);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_platform_spi_set_config_wrong_mode_err(void)
{
    ret = platform_spi_set_config(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MODE_WRONG, PLATFORM_SPI_MSBFIRST);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_platform_spi_set_config_wrong_bit_order_err(void)
{
    ret = platform_spi_set_config(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MODE_0, PLATFORM_SPI_BIT_ORDER_WRONG);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_platform_spi_write_ok(void)
{
    uint8_t dummy_txdata;
    ret = platform_spi_write(PLATFORM_SPI_HW, &dummy_txdata, sizeof(dummy_txdata));
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_platform_spi_write_read_ok(void)
{
    uint8_t dummy_txdata;
    uint8_t dummy_rxdata;
    ret = platform_spi_write_read(PLATFORM_SPI_HW, &dummy_txdata, &dummy_rxdata, sizeof(dummy_rxdata));
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_spi_init_ok);
    RUN_TEST(test_platform_spi_set_config_ok);
    RUN_TEST(test_platform_spi_set_config_wrong_mode_err);
    RUN_TEST(test_platform_spi_set_config_wrong_bit_order_err);
    RUN_TEST(test_platform_spi_write_ok);
    RUN_TEST(test_platform_spi_write_read_ok);
    return UNITY_END();
}