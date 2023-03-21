#include <unity.h>
#include "Arduino.h"
 
void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
}
 
void tearDown(void)
{}
 
void test_readBoardTemperature_ok() {
    float celsius;
    wsen_temp_get_celsius(neo_wsen_temp, &celsius);
    TEST_ASSERT_EQUAL_FLOAT(celsius, readBoardTemperature());
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_readBoardTemperature_ok);
    UNITY_END();
    return UNITY_END();
}
