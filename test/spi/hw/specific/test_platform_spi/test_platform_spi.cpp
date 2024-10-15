#include <unity.h>
#include "hw_platform.h"
 
static platform_err_code_t ret;
 
void setUp(void)
{}
 
void tearDown(void)
{}
 
void test_platform_spi_init_wrong_hw_err(void)
{
    uint8_t dummy_for_pointer;
    ret = platform_spi_init((hw_spi_t)&dummy_for_pointer, PLATFORM_SPI_SPEED, PLATFORM_SPI_MOSI, PLATFORM_SPI_MISO, PLATFORM_SPI_SCK);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_platform_spi_init_pin_less_than_0_err(void)
{
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, -1, PLATFORM_SPI_MISO, PLATFORM_SPI_SCK);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MOSI, -1, PLATFORM_SPI_SCK);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MOSI, PLATFORM_SPI_MISO, -1);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_platform_spi_init_pin_greater_than_29_err(void)
{
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, 30, PLATFORM_SPI_MISO, PLATFORM_SPI_SCK);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MOSI, 30, PLATFORM_SPI_SCK);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = platform_spi_init(PLATFORM_SPI_HW, PLATFORM_SPI_SPEED, PLATFORM_SPI_MOSI, PLATFORM_SPI_MISO, 30);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_spi_init_wrong_hw_err);
    RUN_TEST(test_platform_spi_init_pin_less_than_0_err);
    RUN_TEST(test_platform_spi_init_pin_greater_than_29_err);
    return UNITY_END();
}