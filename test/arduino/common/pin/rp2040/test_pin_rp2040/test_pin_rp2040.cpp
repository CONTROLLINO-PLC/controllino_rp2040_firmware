#include <unity.h>
#include "Arduino.h"
#include "wiring.h"

#define TEST_RP2040_GPIO (pin_size_t)0

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
    pinMode(TEST_RP2040_GPIO, INPUT);
}
 
void tearDown(void)
{}
 
void test_native_pin_input_hysteresis_disable_after_pinMode()
{
    TEST_ASSERT_FALSE(gpio_is_input_hysteresis_enabled(TEST_RP2040_GPIO));
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    // RUN_TEST(test_native_pin_definitions_ok);
    RUN_TEST(test_native_pin_input_hysteresis_disable_after_pinMode);
    UNITY_END();
    return UNITY_END();
}
