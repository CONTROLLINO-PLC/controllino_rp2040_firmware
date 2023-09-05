#include <unity.h>
#include "controllino_wiring.h"

extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI0;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI1;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI2;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI3;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI4;
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI5;

extern const uint8_t _CY8C9520_EN_DO0;
extern const uint8_t _CY8C9520_EN_DO1;
extern const uint8_t _CY8C9520_EN_DO2;
extern const uint8_t _CY8C9520_EN_DO3;
extern const uint8_t _CY8C9520_EN_DO4;
extern const uint8_t _CY8C9520_EN_DO5;
extern const uint8_t _CY8C9520_EN_DO6;
extern const uint8_t _CY8C9520_EN_DO7;

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
}

void tearDown(void)
{}

void test_micro_getControllinoRp2040Pin()
{
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI0, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI0));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI1, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI1));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI2, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI2));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI3, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI3));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI4, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI4));
    TEST_ASSERT_EQUAL(_CONTROLLINO_MICRO_AI5, getControllinoRp2040Pin(CONTROLLINO_MICRO_AI5));
    // Wrong pin number
    TEST_ASSERT_EQUAL(nullptr, getControllinoRp2040Pin(0));
}

void test_micro_enableOutput()
{
    uint8_t dir;
    uint8_t drv_reg_en;
    
    // DO0
    enableOut(CONTROLLINO_MICRO_DO0);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO0 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO0 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);

    // DO1
    enableOut(CONTROLLINO_MICRO_DO1);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO1 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO1 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);

    // DO2
    enableOut(CONTROLLINO_MICRO_DO2);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO2 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO2 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);

    // DO3
    enableOut(CONTROLLINO_MICRO_DO3);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO3 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO3 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);

    // DO4
    enableOut(CONTROLLINO_MICRO_DO4);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO4 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO4 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);

    // DO5
    enableOut(CONTROLLINO_MICRO_DO5);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO5 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO5 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);

    // DO6
    enableOut(CONTROLLINO_MICRO_DO6);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO6 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO6 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);

    // DO7
    enableOut(CONTROLLINO_MICRO_DO7);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO7 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_UP, (_CY8C9520_EN_DO7 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
}

void test_micro_disableOutput()
{
    uint8_t dir;
    uint8_t drv_reg_en;

    // DO0
    disableOut(CONTROLLINO_MICRO_DO0);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO0 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO0 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO0);

    // DO1
    disableOut(CONTROLLINO_MICRO_DO1);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO1 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO1 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO1);

    // DO2
    disableOut(CONTROLLINO_MICRO_DO2);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO2 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO2 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO2);

    // DO3
    disableOut(CONTROLLINO_MICRO_DO3);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO3 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO3 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO3);

    // DO4
    disableOut(CONTROLLINO_MICRO_DO4);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO4 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO4 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO4);

    // DO5
    disableOut(CONTROLLINO_MICRO_DO5);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO5 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO5 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO5);

    // DO6
    disableOut(CONTROLLINO_MICRO_DO6);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO6 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO6 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO6);

    // DO7
    disableOut(CONTROLLINO_MICRO_DO7);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PORT_DIR, (_CY8C9520_EN_DO7 % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C9520_GPIO_IN, dir);
    cy8c9520_read_bit(dev_cy8c9520, CY8C9520_REG_PULL_DOWN, (_CY8C9520_EN_DO7 % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    enableOut(CONTROLLINO_MICRO_DO7);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_micro_getControllinoRp2040Pin);
    RUN_TEST(test_micro_enableOutput);
    RUN_TEST(test_micro_disableOutput);
    UNITY_END();
    return UNITY_END();
}
