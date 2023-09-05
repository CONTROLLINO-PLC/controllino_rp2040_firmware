#include <math.h>
#include <unity.h>
#include "controllino_diag.h"

extern uint16_t _CONTROLLINO_MICRO_DO0_R;
extern uint16_t _CONTROLLINO_MICRO_DO1_R;
extern uint16_t _CONTROLLINO_MICRO_DO2_R;
extern uint16_t _CONTROLLINO_MICRO_DO3_R;
extern uint16_t _CONTROLLINO_MICRO_DO4_R;
extern uint16_t _CONTROLLINO_MICRO_DO5_R;
extern uint16_t _CONTROLLINO_MICRO_DO6_R;
extern uint16_t _CONTROLLINO_MICRO_DO7_R;

void setUp(void)
{
#ifdef NATIVE_ENV
    initVariant();
#endif
}

void tearDown(void)
{}

void test_micro_setOutCurrentLim()
{
    uint16_t wiper = 0;
    // DO0
    // Lower limit is 500
    setOutCurrentLim(CONTROLLINO_MICRO_DO0, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO0_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_0, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO0, 499);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO0_R); // Not changed
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_0, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    // Upper limit is 30000
    setOutCurrentLim(CONTROLLINO_MICRO_DO0, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO0_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_0, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO0, 3001);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO0_R); // Not changed
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_0, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);
    
    // DO1
    setOutCurrentLim(CONTROLLINO_MICRO_DO1, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO1_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_1, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO1, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO1_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_1, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);

    // DO2
    setOutCurrentLim(CONTROLLINO_MICRO_DO2, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO2_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_2, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO2, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO2_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_2, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);

    // DO3
    setOutCurrentLim(CONTROLLINO_MICRO_DO3, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO3_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_3, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO3, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO3_R);
    mcp4461_read_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_3, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);

    // DO4
    setOutCurrentLim(CONTROLLINO_MICRO_DO4, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO4_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_0, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO4, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO4_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_0, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);

    // DO5
    setOutCurrentLim(CONTROLLINO_MICRO_DO5, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO5_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_1, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO5, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO5_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_1, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);

    // DO6
    setOutCurrentLim(CONTROLLINO_MICRO_DO6, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO6_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_2, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO6, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO6_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_2, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);

    // DO7
    setOutCurrentLim(CONTROLLINO_MICRO_DO7, 500);
    TEST_ASSERT_EQUAL(30000, _CONTROLLINO_MICRO_DO7_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_3, &wiper);
    TEST_ASSERT_EQUAL(256, wiper);
    setOutCurrentLim(CONTROLLINO_MICRO_DO7, 3000);
    TEST_ASSERT_EQUAL(5000, _CONTROLLINO_MICRO_DO7_R);
    mcp4461_read_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_3, &wiper);
    TEST_ASSERT_EQUAL(0, wiper);
}

void test_micro_getOutCurrentLim()
{
    // DO0
    setOutCurrentLim(CONTROLLINO_MICRO_DO0, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO0));
    setOutCurrentLim(CONTROLLINO_MICRO_DO0, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO0));
    
    // DO1
    setOutCurrentLim(CONTROLLINO_MICRO_DO1, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO1));
    setOutCurrentLim(CONTROLLINO_MICRO_DO1, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO1));

    // DO2
    setOutCurrentLim(CONTROLLINO_MICRO_DO2, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO2));
    setOutCurrentLim(CONTROLLINO_MICRO_DO2, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO2));

    // DO3
    setOutCurrentLim(CONTROLLINO_MICRO_DO3, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO3));
    setOutCurrentLim(CONTROLLINO_MICRO_DO3, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO3));

    // DO4
    setOutCurrentLim(CONTROLLINO_MICRO_DO4, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO4));
    setOutCurrentLim(CONTROLLINO_MICRO_DO4, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO4));

    // DO5
    setOutCurrentLim(CONTROLLINO_MICRO_DO5, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO5));
    setOutCurrentLim(CONTROLLINO_MICRO_DO5, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO5));

    // DO6
    setOutCurrentLim(CONTROLLINO_MICRO_DO6, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO6));
    setOutCurrentLim(CONTROLLINO_MICRO_DO6, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO6));

    // DO7
    setOutCurrentLim(CONTROLLINO_MICRO_DO7, 500);
    TEST_ASSERT_EQUAL(500, getOutCurrentLim(CONTROLLINO_MICRO_DO7));
    setOutCurrentLim(CONTROLLINO_MICRO_DO7, 3000);
    TEST_ASSERT_EQUAL(3000, getOutCurrentLim(CONTROLLINO_MICRO_DO7));
}

void test_micro_getOutCurrent()
{
    adg728_channel_t ch;
    uint8_t mux;
    
    // DO0
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO0));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_0, ch);

    // DO1
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO1));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_1, ch);

    // DO2
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO2));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_2, ch);

    // DO3
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO3));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_3, ch);

    // DO4
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO4));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_4, ch);

    // DO5
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO5));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_5, ch);

    // DO6
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO6));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_6, ch);

    // DO7
    TEST_ASSERT_GREATER_THAN(0, getOutCurrent(CONTROLLINO_MICRO_DO7));
    mcp3564_iread(dev_mcp3564, MCP3564_REG_MUX, &mux, 1);
    TEST_ASSERT_EQUAL(MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS | MCP3564_MUX_VIN_POS_CH7, mux);
    adg728_get_channel(dev_adg728, &ch);
    TEST_ASSERT_EQUAL(ADG728_CHANNEL_7, ch);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_micro_setOutCurrentLim);
    RUN_TEST(test_micro_getOutCurrentLim);
    RUN_TEST(test_micro_getOutCurrent);
    UNITY_END();
    return UNITY_END();
}
