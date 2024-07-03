#include <unity.h>
#include "Arduino.h"
#include "controllino_wiring.h"

uint16_t TEST_AD5664_WRITE_DAC_DATA = 0x7FFF;
uint16_t TEST_AD5664_DAC_DATA = 0x0000;

#ifdef CONTROLLINO_MICRO
ControllinoPin* _PIN = new ControllinoPin(AD5664_CH_ADDR_A, ControllinoPin::AD5664_PIN);
#define TEST_AD5664_ARDUINO_PIN _PIN
#define _TEST_AD5664_ARDUINO_PIN _PIN
#endif
#ifdef CONTROLLINO_NEO
extern ControllinoPin* _CONTROLLINO_NEO_AO0;
#define TEST_AD5664_ARDUINO_PIN CONTROLLINO_NEO_AO0
#define _TEST_AD5664_ARDUINO_PIN _CONTROLLINO_NEO_AO0
#endif

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
    pinMode(TEST_AD5664_ARDUINO_PIN, OUTPUT);
}
 
void tearDown(void)
{}
 
void test_ad5664_pin_definitions_ok()
{
    TEST_ASSERT_EQUAL(AD5664_CH_ADDR_A, _TEST_AD5664_ARDUINO_PIN->getPin());
    TEST_ASSERT_EQUAL(ControllinoPin::AD5664_PIN, _TEST_AD5664_ARDUINO_PIN->getType());
}
 
void test_ad5664_pin_pinMode_always_output()
{
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
    pinMode(TEST_AD5664_ARDUINO_PIN, INPUT);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
    pinMode(TEST_AD5664_ARDUINO_PIN, INPUT_PULLUP);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
    pinMode(TEST_AD5664_ARDUINO_PIN, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
    pinMode(TEST_AD5664_ARDUINO_PIN, OUTPUT_2MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
    pinMode(TEST_AD5664_ARDUINO_PIN, OUTPUT_4MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
    pinMode(TEST_AD5664_ARDUINO_PIN, OUTPUT_8MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
    pinMode(TEST_AD5664_ARDUINO_PIN, OUTPUT_12MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_AD5664_ARDUINO_PIN->getMode());
}
 
void test_ad5664_pin_analogWrite_ok()
{
    analogWrite(TEST_AD5664_ARDUINO_PIN, TEST_AD5664_WRITE_DAC_DATA);
#ifdef NATIVE_ENV /* Only posible to read back with native env mock */
    TEST_ASSERT_EQUAL(TEST_AD5664_WRITE_DAC_DATA, TEST_AD5664_DAC_DATA);
#endif
}
 
void test_ad5664_pin_analogRead_does_nothing()
{
    int res = analogRead(TEST_AD5664_ARDUINO_PIN);
    TEST_ASSERT_EQUAL(0, res);
}
 
void test_ad5664_pin_digitalWrite_digitalRead_does_nothing()
{
    digitalWrite(TEST_AD5664_ARDUINO_PIN, HIGH);
    int res = digitalRead(TEST_AD5664_ARDUINO_PIN);
    TEST_ASSERT_EQUAL(0, res);
}
 
void test_ad5664_pin_digitalThreshold_does_nothing()
{
    setDigitalThreshold(TEST_AD5664_ARDUINO_PIN, 0);
    TEST_ASSERT_EQUAL(~0U, getDigitalThreshold(TEST_AD5664_ARDUINO_PIN));
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
#ifndef CONTROLLINO_MICRO // Micro does not have AD5664
    RUN_TEST(test_ad5664_pin_definitions_ok);
    RUN_TEST(test_ad5664_pin_pinMode_always_output);
    RUN_TEST(test_ad5664_pin_analogWrite_ok);
    RUN_TEST(test_ad5664_pin_analogRead_does_nothing);
    RUN_TEST(test_ad5664_pin_digitalWrite_digitalRead_does_nothing);
    RUN_TEST(test_ad5664_pin_digitalThreshold_does_nothing);
#endif
    UNITY_END();
    return UNITY_END();
}