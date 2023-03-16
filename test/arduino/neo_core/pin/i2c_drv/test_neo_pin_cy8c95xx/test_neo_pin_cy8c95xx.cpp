#include <unity.h>
#include "Arduino.h"
 
uint8_t TEST_CY8C95XX_GPIO;
uint8_t TEST_CY8C95XX_ADDR = CY8C95XX_DEV_ADDR_GND;
 
void setUp(void)
{
    initVariant();
    pinMode(NEO_CORE_DO7, INPUT);
}
 
void tearDown(void)
{
    pinMode(NEO_CORE_DO7, INPUT_PULLDOWN);
}
 
void test_cy8c95xx_pin_definitions_ok()
{
    TEST_ASSERT_EQUAL(CY8C95XX_GPIO_6, NEO_CORE_DO7->getPin());
    TEST_ASSERT_EQUAL(ControllinoNeoPin::CY8C95XX_PIN, NEO_CORE_DO7->getType());
}
 
void test_cy8c95xx_pin_pinMode_is_input_pull_up_down_or_output()
{
    TEST_ASSERT_EQUAL(INPUT_PULLUP, NEO_CORE_DO7->getMode());
    pinMode(NEO_CORE_DO7, INPUT_PULLUP);
    TEST_ASSERT_EQUAL(INPUT_PULLUP, NEO_CORE_DO7->getMode());
    pinMode(NEO_CORE_DO7, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(INPUT_PULLDOWN, NEO_CORE_DO7->getMode());
    pinMode(NEO_CORE_DO7, OUTPUT);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_DO7->getMode());
    pinMode(NEO_CORE_DO7, OUTPUT_2MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_DO7->getMode());
    pinMode(NEO_CORE_DO7, OUTPUT_4MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_DO7->getMode());
    pinMode(NEO_CORE_DO7, OUTPUT_8MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_DO7->getMode());
    pinMode(NEO_CORE_DO7, OUTPUT_12MA);
    TEST_ASSERT_EQUAL(OUTPUT, NEO_CORE_DO7->getMode());
}
 
void test_cy8c95xx_pin_digitalRead()
{
    TEST_ASSERT_EQUAL(HIGH, digitalRead(NEO_CORE_DO7));
    pinMode(NEO_CORE_DO7, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(LOW, digitalRead(NEO_CORE_DO7));
}
 
void test_cy8c95xx_pin_digitalWrite()
{
    digitalWrite(NEO_CORE_DO7, LOW);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(NEO_CORE_DO7)); // Still high because mode is input pull up
    pinMode(NEO_CORE_DO7, OUTPUT);
    digitalWrite(NEO_CORE_DO7, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(NEO_CORE_DO7));
    digitalWrite(NEO_CORE_DO7, HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(NEO_CORE_DO7));
}
 
void test_cy8c95xx_pin_analogRead_does_nothing()
{
    TEST_ASSERT_EQUAL(0, analogRead(NEO_CORE_DO7));
    pinMode(NEO_CORE_DO7, OUTPUT);
    TEST_ASSERT_EQUAL(0, analogRead(NEO_CORE_DO7));
}
 
void test_cy8c95xx_pin_analogWrite()
{
    uint8_t res_pwm_en = 0x1;
    uint8_t res_pulse_wid = 0x00;
    //
    pinMode(NEO_CORE_DO7, OUTPUT);
    digitalWrite(NEO_CORE_DO7, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(NEO_CORE_DO7));
    analogWrite(NEO_CORE_DO7, 0x7F);
    cy8c95xx_read_byte(neo_cy8c95xx, CY8C95XX_REG_PULSE_WIDTH_PWM, &res_pulse_wid);
    cy8c95xx_read_bit(neo_cy8c95xx, CY8C95XX_REG_SEL_PWM_OUT, (NEO_CORE_DO7->getPin() % 8), &res_pwm_en);
    TEST_ASSERT_EQUAL(0x7F, res_pulse_wid);
    TEST_ASSERT_EQUAL(0x1, res_pwm_en);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(NEO_CORE_DO7));
    //
    digitalWrite(NEO_CORE_DO7, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(NEO_CORE_DO7));
    analogWrite(NEO_CORE_DO7, 0xFF); // 0xFF will be the same as digitalWrite() HIGH and pwm get disable
    cy8c95xx_read_bit(neo_cy8c95xx, CY8C95XX_REG_SEL_PWM_OUT, (NEO_CORE_DO7->getPin() % 8), &res_pwm_en);
    TEST_ASSERT_EQUAL(0x7F, res_pulse_wid); 
    TEST_ASSERT_EQUAL(0x0, res_pwm_en); 
    TEST_ASSERT_EQUAL(HIGH, digitalRead(NEO_CORE_DO7));
}
 
void test_cy8c95xx_pin_digitalThreshold_does_nothing()
{
    setDigitalThreshold(NEO_CORE_DO7, 0);
    TEST_ASSERT_EQUAL(~0U, getDigitalThreshold(NEO_CORE_DO7));
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_cy8c95xx_pin_definitions_ok);
    RUN_TEST(test_cy8c95xx_pin_pinMode_is_input_pull_up_down_or_output);
    RUN_TEST(test_cy8c95xx_pin_digitalRead);
    RUN_TEST(test_cy8c95xx_pin_digitalWrite);
    RUN_TEST(test_cy8c95xx_pin_analogRead_does_nothing);
    RUN_TEST(test_cy8c95xx_pin_analogWrite);
    RUN_TEST(test_cy8c95xx_pin_digitalThreshold_does_nothing);
    UNITY_END();
    return UNITY_END();
}
