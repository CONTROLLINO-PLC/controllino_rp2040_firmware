#include <unity.h>
#include "Arduino.h"
#include "controllino_wiring.h"

extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI0;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI1;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI2;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI3;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI4;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI5;

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
}

void tearDown(void)
{}

void test_micro_getControllinoRp2040Pin()
{
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI0, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI0));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI1, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI1));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI2, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI2));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI3, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI3));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI4, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI4));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI5, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI5));
    // Wrong pin number
    TEST_ASSERT_EQUAL(nullptr, getControllinoRp2040Pin(0));
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_micro_getControllinoRp2040Pin);
    UNITY_END();
    return UNITY_END();
}
