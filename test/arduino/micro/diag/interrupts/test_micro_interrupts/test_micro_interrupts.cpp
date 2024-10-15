#include <math.h>
#include <unity.h>
#include "diag.h"

extern const uint8_t _CY8C9520_INT_PIN;

extern const uint8_t _CY8C9520_INT_TEMP_SENSOR;
extern const uint8_t _CY8C9520_INT_NFAULT_DO0;
extern const uint8_t _CY8C9520_INT_NFAULT_DO1;
extern const uint8_t _CY8C9520_INT_NFAULT_DO2;
extern const uint8_t _CY8C9520_INT_NFAULT_DO3;
extern const uint8_t _CY8C9520_INT_NFAULT_DO4;
extern const uint8_t _CY8C9520_INT_NFAULT_DO5;
extern const uint8_t _CY8C9520_INT_NFAULT_DO6;
extern const uint8_t _CY8C9520_INT_NFAULT_DO7;

extern void (*_CY8C9520_INT_TEMP_SENSOR_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO0_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO1_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO2_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO3_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO4_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO5_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO6_cb)(void);
extern void (*_CY8C9520_INT_NFAULT_DO7_cb)(void);

void test_cb(void) {}

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
}

void tearDown(void)
{}

/* Check CY8C9520 pin interrupt enable */
void check_cy8c9520_pin_int_en(uint8_t pin)
{
    uint8_t state;
    cy8c9520_select_port(dev_cy8c9520, (0x00 + (pin  / 8)));
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_INT_MASK, (pin  % 8), &state);
    TEST_ASSERT_EQUAL(0, state);
}

/* Check CY8C9520 pin interrupt disable */
void check_cy8c9520_pin_int_dis(uint8_t pin)
{
    uint8_t state;
    cy8c9520_select_port(dev_cy8c9520, (0x00 + (pin  / 8)));
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_INT_MASK, (pin  % 8), &state);
    TEST_ASSERT_EQUAL(1, state);
}

void test_micro_enableTempSensorInt()
{
    float lowLim = -30.00F;
    float highLim = 100.00F;

    // Enable
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_TEMP_SENSOR_cb);
    enableTempSensorInt(lowLim, highLim, &test_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_TEMP_SENSOR_cb);
    
    // CY8C9520 pin interrupt enable
    check_cy8c9520_pin_int_en(_CY8C9520_INT_TEMP_SENSOR);

    // RP2040 pin interrupt enable
    // Event 8 -> RISING
    // TEST_ASSERT_EQUAL(8, gpio_get_irq_event_mask(_CY8C9520_INT_PIN));

    // Temp limits
    float _lowLim;
    float _highLim;
    wsen_temp_get_low_lim(dev_wsen_temp, &_lowLim);
    wsen_temp_get_high_lim(dev_wsen_temp, &_highLim);
    TEST_ASSERT_EQUAL(round(lowLim), round(_lowLim));
    TEST_ASSERT_EQUAL(round(highLim), round(_highLim));
}

void test_micro_disableTempSensorInt()
{
    // Disable
    disableTempSensorInt();
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_TEMP_SENSOR_cb);

    // CY8C9520 pin interrupt disable
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_TEMP_SENSOR);

    // RP2040 pin interrupt disable
    // TEST_ASSERT_EQUAL(0, gpio_get_irq_event_mask(_CY8C9520_INT_PIN));

    // Temp limits
    uint8_t limit;
    wsen_temp_generic_read(dev_wsen_temp, WSEN_TEMP_REG_HIGH_LIM, &limit, 1);
    TEST_ASSERT_EQUAL(0x00, limit);
    wsen_temp_generic_read(dev_wsen_temp, WSEN_TEMP_REG_LOW_LIM, &limit, 1);
    TEST_ASSERT_EQUAL(0x00, limit);
}

void test_micro_enableOutFaultInt()
{
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO0_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO1_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO2_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO3_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO4_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO5_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO6_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO7_cb);

    // Enable
    enableOutFaultInt(CONTROLLINO_MICRO_DO0, &test_cb);
    enableOutFaultInt(CONTROLLINO_MICRO_DO1, &test_cb);
    enableOutFaultInt(CONTROLLINO_MICRO_DO2, &test_cb);
    enableOutFaultInt(CONTROLLINO_MICRO_DO3, &test_cb);
    enableOutFaultInt(CONTROLLINO_MICRO_DO4, &test_cb);
    enableOutFaultInt(CONTROLLINO_MICRO_DO5, &test_cb);
    enableOutFaultInt(CONTROLLINO_MICRO_DO6, &test_cb);
    enableOutFaultInt(CONTROLLINO_MICRO_DO7, &test_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO0_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO1_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO2_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO3_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO4_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO5_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO6_cb);
    TEST_ASSERT_EQUAL(&test_cb, _CY8C9520_INT_NFAULT_DO7_cb);

    // CY8C9520 pin interrupt enable
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO0);
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO1);
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO2);
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO3);
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO4);
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO5);
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO6);
    check_cy8c9520_pin_int_en(_CY8C9520_INT_NFAULT_DO7);

    // RP2040 pin interrupt enable
    // Event 8 -> RISING
    // TEST_ASSERT_EQUAL(8, gpio_get_irq_event_mask(_CY8C9520_INT_PIN));
}

void test_micro_disableOutFaultInt()
{
    // Disable
    disableOutFaultInt(CONTROLLINO_MICRO_DO0);
    disableOutFaultInt(CONTROLLINO_MICRO_DO1);
    disableOutFaultInt(CONTROLLINO_MICRO_DO2);
    disableOutFaultInt(CONTROLLINO_MICRO_DO3);
    disableOutFaultInt(CONTROLLINO_MICRO_DO4);
    disableOutFaultInt(CONTROLLINO_MICRO_DO5);
    disableOutFaultInt(CONTROLLINO_MICRO_DO6);
    disableOutFaultInt(CONTROLLINO_MICRO_DO7);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO0_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO1_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO2_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO3_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO4_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO5_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO6_cb);
    TEST_ASSERT_EQUAL(nullptr, _CY8C9520_INT_NFAULT_DO7_cb);

    // CY8C9520 pin interrupt disable
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO0);
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO1);
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO2);
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO3);
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO4);
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO5);
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO6);
    check_cy8c9520_pin_int_dis(_CY8C9520_INT_NFAULT_DO7);

    // RP2040 pin interrupt disable
    // TEST_ASSERT_EQUAL(0, gpio_get_irq_event_mask(_CY8C9520_INT_PIN));
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_micro_enableTempSensorInt);
    RUN_TEST(test_micro_disableTempSensorInt);
    RUN_TEST(test_micro_enableOutFaultInt);
    RUN_TEST(test_micro_disableOutFaultInt);
    UNITY_END();
    return UNITY_END();
}
