#include <unity.h>
#include "Arduino.h"
#include "controllino_pins.h"

uint16_t TEST_AD56X4_WRITE_DAC_DATA = 0x7FFF;
uint16_t TEST_AD56X4_DAC_DATA = 0x0000;
 
void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
    pinMode(CONTROLLINO_NEO_AO0, OUTPUT);
}
 
void tearDown(void)
{}
 
void test_ad56x4_pin_definitions_ok()
{
    TEST_ASSERT_EQUAL(AD56X4_CH_ADDR_A, _CONTROLLINO_NEO_AO0->getPin());
    TEST_ASSERT_EQUAL(ControllinoRp2040Pin::AD56X4_PIN, _CONTROLLINO_NEO_AO0->getType());
}
 
void test_ad56x4_pin_pinMode_always_output()
{
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
    pinMode(CONTROLLINO_NEO_AO0, INPUT);
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
    pinMode(CONTROLLINO_NEO_AO0, INPUT_PULLUP);
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
    pinMode(CONTROLLINO_NEO_AO0, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
    pinMode(CONTROLLINO_NEO_AO0, OUTPUT_2MA);
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
    pinMode(CONTROLLINO_NEO_AO0, OUTPUT_4MA);
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
    pinMode(CONTROLLINO_NEO_AO0, OUTPUT_8MA);
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
    pinMode(CONTROLLINO_NEO_AO0, OUTPUT_12MA);
    TEST_ASSERT_EQUAL(OUTPUT, _CONTROLLINO_NEO_AO0->getMode());
}
 
void test_ad56x4_pin_analogWrite_ok()
{
    analogWrite(CONTROLLINO_NEO_AO0, TEST_AD56X4_WRITE_DAC_DATA);
#ifdef NATIVE_ENV /* Only posible to read back with native env mock */
    TEST_ASSERT_EQUAL(TEST_AD56X4_WRITE_DAC_DATA, TEST_AD56X4_DAC_DATA);
#endif
}
 
void test_ad56x4_pin_analogRead_does_nothing()
{
    int res = analogRead(CONTROLLINO_NEO_AO0);
    TEST_ASSERT_EQUAL(0, res);
}
 
void test_ad56x4_pin_digitalWrite_digitalRead_does_nothing()
{
    digitalWrite(CONTROLLINO_NEO_AO0, HIGH);
    int res = digitalRead(CONTROLLINO_NEO_AO0);
    TEST_ASSERT_EQUAL(0, res);
}
 
void test_ad56x4_pin_digitalThreshold_does_nothing()
{
    setDigitalThreshold(CONTROLLINO_NEO_AO0, 0);
    TEST_ASSERT_EQUAL(~0U, getDigitalThreshold(CONTROLLINO_NEO_AO0));
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ad56x4_pin_definitions_ok);
    RUN_TEST(test_ad56x4_pin_pinMode_always_output);
    RUN_TEST(test_ad56x4_pin_analogWrite_ok);
    RUN_TEST(test_ad56x4_pin_analogRead_does_nothing);
    RUN_TEST(test_ad56x4_pin_digitalWrite_digitalRead_does_nothing);
    RUN_TEST(test_ad56x4_pin_digitalThreshold_does_nothing);
    UNITY_END();
    return UNITY_END();
}
