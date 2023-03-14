#include <unity.h>
#include "Arduino.h"
 
#define TEST_MCP356X_ADC_READING_ERROR 100
uint32_t TEST_MCP356X_ADC_DATA = 0x7FFFFF;
 
void setUp(void)
{
    initVariant();
    pinMode(NEO_CORE_AI0, INPUT);
}
 
void tearDown(void)
{}
 
void test_mcp356x_pin_definitions_ok()
{
    TEST_ASSERT_EQUAL(MCP356X_CH_CH0, NEO_CORE_AI0->getPin());
    TEST_ASSERT_EQUAL(ControllinoNeoPin::MCP356X_PIN, NEO_CORE_AI0->getType());
}
 
void test_mcp356x_pinMode_always_input()
{
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
    pinMode(NEO_CORE_AI0, OUTPUT);
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
    pinMode(NEO_CORE_AI0, INPUT_PULLUP);
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
    pinMode(NEO_CORE_AI0, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
    pinMode(NEO_CORE_AI0, OUTPUT_2MA);
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
    pinMode(NEO_CORE_AI0, OUTPUT_4MA);
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
    pinMode(NEO_CORE_AI0, OUTPUT_8MA);
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
    pinMode(NEO_CORE_AI0, OUTPUT_12MA);
    TEST_ASSERT_EQUAL(INPUT, NEO_CORE_AI0->getMode());
}
 
void test_mcp356x_analogRead_ok()
{
    int adcArduino = analogRead(NEO_CORE_AI0);
    int adc_mcp356x;
    uint8_t dummySgn;
    uint32_t dummyRes;
    mcp356x_read_raw_adc(neo_mcp356x, (uint32_t*)&adc_mcp356x, &dummySgn, &dummyRes);
    TEST_ASSERT_LESS_OR_EQUAL(TEST_MCP356X_ADC_READING_ERROR, abs(adcArduino - adc_mcp356x));
#ifdef NATIVE_ENV /* Only posible to read back with native env mock */
    TEST_ASSERT_EQUAL(TEST_MCP356X_ADC_DATA, adcArduino);
#endif
}
 
void test_analogWrite_does_nothing()
{
    /* Just test if compiles */
    analogWrite(NEO_CORE_AI0, 0);
}
 
void test_digitalWrite_digitalRead_does_nothing()
{
    digitalWrite(NEO_CORE_AI0, HIGH);
    int res = digitalRead(NEO_CORE_AI0);
    TEST_ASSERT_EQUAL(0, res);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mcp356x_pin_definitions_ok);
    RUN_TEST(test_mcp356x_pinMode_always_input);
    RUN_TEST(test_mcp356x_analogRead_ok);
    RUN_TEST(test_analogWrite_does_nothing);
    RUN_TEST(test_digitalWrite_digitalRead_does_nothing);
    UNITY_END();
    return UNITY_END();
}
