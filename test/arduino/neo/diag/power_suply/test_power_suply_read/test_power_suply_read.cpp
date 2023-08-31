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
 
void test_readVoltageSuply_ok() {
    TEST_ASSERT_GREATER_THAN(0, readVoltageSuply());
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_readVoltageSuply_ok);
    UNITY_END();
    return UNITY_END();
}
