#include <unity.h>
#include "Arduino.h"
#include "diag.h"

float _readBoardTemperature(void)
{
    float celsius;
    wsen_temp_get_celsius(dev_wsen_temp, &celsius);
    return celsius;
}

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
}

void tearDown(void)
{}
 
void test_readBoardTemperature_ok() {
    // Difference between the two readings should be less than 1 degree
    TEST_ASSERT_GREATER_THAN(-1, readBoardTemperature() - _readBoardTemperature());
    TEST_ASSERT_LESS_THAN(1, readBoardTemperature() - _readBoardTemperature());
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_readBoardTemperature_ok);
    UNITY_END();
    return UNITY_END();
}
