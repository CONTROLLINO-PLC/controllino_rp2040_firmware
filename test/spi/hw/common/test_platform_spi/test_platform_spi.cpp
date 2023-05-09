#include <unity.h>
#include "hw_platform.h"
 
static platform_err_code_t ret;
 
bool cs_select_called;
bool cs_deselect_called;
int cs_pin;

void cs_select(int pin) {
    cs_pin = pin;
    cs_select_called = true;
}

void cs_deselect(int pin) {
    cs_pin = pin;
    cs_deselect_called = true;
}
 
void setUp(void)
{
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MOSI, PLATFORM_SPI_MISO, PLATFORM_SPI_SCK);
    cs_select_called = false;
    cs_deselect_called = false;
    cs_pin = 0;
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
 
void test_platform_spi_write_ok(void)
{
    uint8_t dummy_txdata = 0x00;
    ret = platform_spi_write(PLATFORM_SPI_HW, &cs_select, &cs_deselect, -1 /*cs_pin*/,  &dummy_txdata, sizeof(dummy_txdata));
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_TRUE(cs_select_called);
    TEST_ASSERT_TRUE(cs_deselect_called);
    TEST_ASSERT_EQUAL(-1, cs_pin);
}
 
void test_platform_spi_write_read_ok(void)
{
    uint8_t dummy_txdata = 0x00;
    uint8_t dummy_rxdata = 0x00;
    ret = platform_spi_write_read(PLATFORM_SPI_HW, &cs_select, &cs_deselect, -1 /*cs_pin*/, &dummy_txdata, &dummy_rxdata, sizeof(dummy_rxdata));
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_TRUE(cs_select_called);
    TEST_ASSERT_TRUE(cs_deselect_called);
    TEST_ASSERT_EQUAL(-1, cs_pin);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_spi_init_ok);
    RUN_TEST(test_platform_spi_set_config_ok);
    RUN_TEST(test_platform_spi_write_ok);
    RUN_TEST(test_platform_spi_write_read_ok);
    return UNITY_END();
}