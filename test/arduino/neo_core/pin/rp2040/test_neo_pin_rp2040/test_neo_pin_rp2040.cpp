#include <unity.h>
#include "Arduino.h"
#include "controllino_pins.h"

uint8_t TEST_CY8C9520_GPIO;
uint8_t TEST_CY8C9520_ADDR = CY8C9520_DEV_ADDR_GND;
 
void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
    pinMode(CONTROLLINO_NEO_DI0, INPUT);
}
 
void tearDown(void)
{}
 
// void test_native_pin_definitions_ok()
// {
//     TEST_ASSERT_EQUAL(6U, _CONTROLLINO_NEO_DI0->getPin());
//     TEST_ASSERT_EQUAL(ControllinoRp2040Pin::RP2040_PIN, _CONTROLLINO_NEO_DI0->getType());
// }
 
void test_native_pin_input_hysteresis_disable_after_pinMode()
{
    TEST_ASSERT_FALSE(gpio_is_input_hysteresis_enabled(CONTROLLINO_NEO_DI0));
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    // RUN_TEST(test_native_pin_definitions_ok);
    RUN_TEST(test_native_pin_input_hysteresis_disable_after_pinMode);
    UNITY_END();
    return UNITY_END();
}
