#include <unity.h>
#include "unity_test_runner.h"
#include "hw_platform.h"
 
static uint64_t initial_time_us;
static uint64_t final_time_us;
 
void setUp(void)
{}
 
void tearDown(void)
{}
 
void test_platform_get_time_us(void)
{
    TEST_ASSERT_GREATER_THAN(0, platform_get_us());
}
 
void test_platform_get_sleep_ms(void)
{
    initial_time_us = platform_get_us();
    platform_sleep_ms(1);
    final_time_us = platform_get_us();
    // 200 us error allowed
    TEST_ASSERT_GREATER_OR_EQUAL(1000 /* 1 ms */, final_time_us - initial_time_us);
    TEST_ASSERT_LESS_THAN(200 /* 200 us */, (final_time_us - initial_time_us) - 1000);
}
 
void test_platform_get_sleep_us(void)
{
    initial_time_us = platform_get_us();
    platform_sleep_us(500);
    final_time_us = platform_get_us();
    // 200 us error allowed
    TEST_ASSERT_GREATER_OR_EQUAL(500 /* 500 us */, final_time_us - initial_time_us);
    TEST_ASSERT_LESS_OR_EQUAL(200 /* 200 us */, (final_time_us - initial_time_us) - 500);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_platform_get_time_us);
    RUN_TEST(test_platform_get_sleep_ms);
    RUN_TEST(test_platform_get_sleep_us);
    UNITY_END();
    return UNITY_END();
}

