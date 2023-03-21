#include <unity.h>
#include "Arduino.h"
 
uint8_t TEST_CY8C95XX_GPIO;
uint8_t TEST_CY8C95XX_ADDR = CY8C95XX_DEV_ADDR_GND;
 
void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
    pinMode(NEO_CORE_DI0, INPUT);
}
 
void tearDown(void)
{}
 
void test_native_pin_definitions_ok()
{
    TEST_ASSERT_EQUAL(6U, NEO_CORE_DI0->getPin());
    TEST_ASSERT_EQUAL(ControllinoNeoPin::NATIVE_PIN, NEO_CORE_DI0->getType());
}
 
void test_native_pin_input_hysteresis_disable_after_pinMode()
{
    TEST_ASSERT_FALSE(gpio_is_input_hysteresis_enabled(NEO_CORE_DI0->getPin()));
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_native_pin_definitions_ok);
    RUN_TEST(test_native_pin_input_hysteresis_disable_after_pinMode);
    UNITY_END();
    return UNITY_END();
}
