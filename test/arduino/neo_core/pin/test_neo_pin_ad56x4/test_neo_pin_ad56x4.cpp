#include <unity.h>
#include "Arduino.h"
#include "pins_arduino.h"
 
uint16_t TEST_AD56X4_WRITE_DAC_DATA = 0x7FFF;
uint16_t TEST_AD56X4_DAC_DATA = 0;
 
void setUp(void)
{
    pinMode(NEO_CORE_AO0, OUTPUT);
}
 
void tearDown(void)
{}
 
void test_ad56x4_pin_definitions_ok()
{
    TEST_ASSERT_EQUAL(AD56X4_CH_ADDR_A, NEO_CORE_AO0->getPin());
    TEST_ASSERT_EQUAL(AD56X4_CH_ADDR_B, NEO_CORE_AO1->getPin());
    TEST_ASSERT_EQUAL(AD56X4_CH_ADDR_C, NEO_CORE_AO2->getPin());
    TEST_ASSERT_EQUAL(AD56X4_CH_ADDR_D, NEO_CORE_AO3->getPin());
    TEST_ASSERT_EQUAL(ControllinoNeoPin::AD56X4_PIN, NEO_CORE_AO0->getType());
    TEST_ASSERT_EQUAL(ControllinoNeoPin::AD56X4_PIN, NEO_CORE_AO1->getType());
    TEST_ASSERT_EQUAL(ControllinoNeoPin::AD56X4_PIN, NEO_CORE_AO2->getType());
    TEST_ASSERT_EQUAL(ControllinoNeoPin::AD56X4_PIN, NEO_CORE_AO3->getType());
}

void test_ad56x4_pinMode_always_output_ok()
{
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
    pinMode(NEO_CORE_AO0, INPUT);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
    pinMode(NEO_CORE_AO0, INPUT_PULLUP);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
    pinMode(NEO_CORE_AO0, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
    pinMode(NEO_CORE_AO0, OUTPUT_2MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
    pinMode(NEO_CORE_AO0, OUTPUT_4MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
    pinMode(NEO_CORE_AO0, OUTPUT_8MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
    pinMode(NEO_CORE_AO0, OUTPUT_12MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_AO0->getMode());
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ad56x4_pin_definitions_ok);
    RUN_TEST(test_ad56x4_pinMode_always_output_ok);
    UNITY_END();
    return UNITY_END();
}
