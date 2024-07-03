#include <unity.h>
#include "Arduino.h"
#include "controllino_wiring.h"

uint8_t TEST_CY8C9520_GPIO;
uint8_t TEST_CY8C9520_ADDR = CY8C9520_DEV_ADDR_GND;

#ifdef CONTROLLINO_MICRO
ControllinoPin* _PIN = new ControllinoPin(CY8C9520_GPIO_17, ControllinoPin::CY8C9520_PIN);
#define TEST_CY8C9520_ARDUINO_PIN _PIN
#define _TEST_CY8C9520_ARDUINO_PIN _PIN
#define TEST_CY8C9520_GPIO CY8C9520_GPIO_17
#endif
#ifdef CONTROLLINO_NEO
extern ControllinoPin* _CONTROLLINO_NEO_DO4;
#define TEST_CY8C9520_ARDUINO_PIN CONTROLLINO_NEO_DO4
#define _TEST_CY8C9520_ARDUINO_PIN _CONTROLLINO_NEO_DO4
#define TEST_CY8C9520_GPIO CY8C9520_GPIO_9
#endif

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
    pinMode(TEST_CY8C9520_ARDUINO_PIN, INPUT);
}
 
void tearDown(void)
{
    pinMode(TEST_CY8C9520_ARDUINO_PIN, INPUT_PULLUP);
}
 
void test_cy8c9520_pin_definitions_ok()
{
    TEST_ASSERT_EQUAL(TEST_CY8C9520_GPIO, _TEST_CY8C9520_ARDUINO_PIN->getPin());
    TEST_ASSERT_EQUAL(ControllinoPin::CY8C9520_PIN, _TEST_CY8C9520_ARDUINO_PIN->getType());
}
 
void test_cy8c9520_pin_pinMode_is_input_pull_up_down_or_output()
{
    TEST_ASSERT_EQUAL(INPUT_PULLUP, _TEST_CY8C9520_ARDUINO_PIN->getMode());
    pinMode(TEST_CY8C9520_ARDUINO_PIN, INPUT_PULLUP);
    TEST_ASSERT_EQUAL(INPUT_PULLUP, _TEST_CY8C9520_ARDUINO_PIN->getMode());
    pinMode(TEST_CY8C9520_ARDUINO_PIN, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(INPUT_PULLDOWN, _TEST_CY8C9520_ARDUINO_PIN->getMode());
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_CY8C9520_ARDUINO_PIN->getMode());
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT_2MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_CY8C9520_ARDUINO_PIN->getMode());
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT_4MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_CY8C9520_ARDUINO_PIN->getMode());
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT_8MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_CY8C9520_ARDUINO_PIN->getMode());
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT_12MA);
    TEST_ASSERT_EQUAL(OUTPUT, _TEST_CY8C9520_ARDUINO_PIN->getMode());
}
 
void test_cy8c9520_pin_digitalRead()
{
    TEST_ASSERT_EQUAL(HIGH, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
    pinMode(TEST_CY8C9520_ARDUINO_PIN, INPUT_PULLDOWN);
    TEST_ASSERT_EQUAL(LOW, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
}
 
void test_cy8c9520_pin_digitalWrite()
{
    digitalWrite(TEST_CY8C9520_ARDUINO_PIN, LOW);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(TEST_CY8C9520_ARDUINO_PIN)); // Still high because mode is input pull up
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT);
    digitalWrite(TEST_CY8C9520_ARDUINO_PIN, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
    digitalWrite(TEST_CY8C9520_ARDUINO_PIN, HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
}
 
void test_cy8c9520_pin_analogRead_does_nothing()
{
    TEST_ASSERT_EQUAL(0, analogRead(TEST_CY8C9520_ARDUINO_PIN));
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT);
    TEST_ASSERT_EQUAL(0, analogRead(TEST_CY8C9520_ARDUINO_PIN));
}
 
void test_cy8c9520_pin_analogWrite()
{
    uint8_t res_pwm_en = 0x1;
    uint8_t res_pulse_wid = 0x00;
    //
    pinMode(TEST_CY8C9520_ARDUINO_PIN, OUTPUT);
    digitalWrite(TEST_CY8C9520_ARDUINO_PIN, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
    analogWrite(TEST_CY8C9520_ARDUINO_PIN, 0x7F);
    cy8c9520_read_byte(dev_cy8c9520, CY8C9520_REG_PULSE_WIDTH_PWM, &res_pulse_wid);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_SEL_PWM_OUT, (_TEST_CY8C9520_ARDUINO_PIN->getPin() % 8), &res_pwm_en);
    TEST_ASSERT_EQUAL(0x7F, res_pulse_wid);
    TEST_ASSERT_EQUAL(0x1, res_pwm_en);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
    //
    digitalWrite(TEST_CY8C9520_ARDUINO_PIN, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
    analogWrite(TEST_CY8C9520_ARDUINO_PIN, 0xFF); // 0xFF will be the same as digitalWrite() HIGH and pwm get disable
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_SEL_PWM_OUT, (_TEST_CY8C9520_ARDUINO_PIN->getPin() % 8), &res_pwm_en);
    TEST_ASSERT_EQUAL(0x7F, res_pulse_wid); 
    TEST_ASSERT_EQUAL(0x0, res_pwm_en); 
    TEST_ASSERT_EQUAL(HIGH, digitalRead(TEST_CY8C9520_ARDUINO_PIN));
}
 
void test_cy8c9520_pin_digitalThreshold_does_nothing()
{
    setDigitalThreshold(TEST_CY8C9520_ARDUINO_PIN, 0);
    TEST_ASSERT_EQUAL(~0U, getDigitalThreshold(TEST_CY8C9520_ARDUINO_PIN));
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_cy8c9520_pin_definitions_ok);
    RUN_TEST(test_cy8c9520_pin_pinMode_is_input_pull_up_down_or_output);
    RUN_TEST(test_cy8c9520_pin_digitalRead);
    RUN_TEST(test_cy8c9520_pin_digitalWrite);
    RUN_TEST(test_cy8c9520_pin_analogRead_does_nothing);
    RUN_TEST(test_cy8c9520_pin_analogWrite);
    RUN_TEST(test_cy8c9520_pin_digitalThreshold_does_nothing);
    UNITY_END();
    return UNITY_END();
}
