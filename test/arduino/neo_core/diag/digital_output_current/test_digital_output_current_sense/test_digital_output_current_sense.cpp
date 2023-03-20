#include <unity.h>
#include "Arduino.h"
 
uint8_t TEST_BTS71220_CURRENT_SENSE_REF_ADC = 181;
 
void setUp(void)
{
    initVariant();
}
 
void tearDown(void)
{
    disableCurrentSenseDO();
}
 
void test_enableCurrentSenseDO_sets_correct_bts71220_mux()
{
    bts71220_dcr_reg_t dcr_reg;
    // At init mux should be BTS71220_DCR_MUX_IS_SLEEP_Z
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(0);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH3, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(1);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH2, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(2);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH1, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(3);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH0, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(4);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH3, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(5);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH2, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(6);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH1, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(7);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_CH0, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
}
 
void test_disableCurrentSenseDO_sets_bts71220_mux_sleep_mode()
{
    bts71220_dcr_reg_t dcr_reg;
    //
    enableCurrentSenseDO(0);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(1);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(2);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(3);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(4);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(5);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(6);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    //
    enableCurrentSenseDO(7);
    disableCurrentSenseDO();
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
}
 
void test_readCurrentSenseDO_ok()
{
    enableCurrentSenseDO(0);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 1); // set verification mode to generate a fixed value in sense pin
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH0_OR_CH3, readCurrentSenseDO());
    //
    enableCurrentSenseDO(1);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 1);
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH1_OR_CH2, readCurrentSenseDO());
    //
    enableCurrentSenseDO(2);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 1);
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH1_OR_CH2, readCurrentSenseDO());
    //
    enableCurrentSenseDO(3);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 1);
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH0_OR_CH3, readCurrentSenseDO());
    //
    enableCurrentSenseDO(4);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 0);
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH0_OR_CH3, readCurrentSenseDO());
    //
    enableCurrentSenseDO(5);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 0);
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH1_OR_CH2, readCurrentSenseDO());
    //
    enableCurrentSenseDO(6);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 0);
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH1_OR_CH2, readCurrentSenseDO());
    //
    enableCurrentSenseDO(7);
    bts71220_set_sense_mux(neo_bts71220, BTS71220_DCR_MUX_IS_VERIF, 0);
    TEST_ASSERT_GREATER_OR_EQUAL(TEST_BTS71220_CURRENT_SENSE_REF_ADC * BTS71220_CURRENT_SENSE_CONVERSION_RATIO_CH0_OR_CH3, readCurrentSenseDO());
}
 
void test_enableCurrentSenseDO_DO_grater_than_8_does_nothing() {
    bts71220_dcr_reg_t dcr_reg;
    enableCurrentSenseDO(9);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 0);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
    bts71220_read_reg(neo_bts71220, BTS71220_REG_DCR, (uint8_t*)&dcr_reg, 1);
    TEST_ASSERT_EQUAL(BTS71220_DCR_MUX_IS_SLEEP_Z, dcr_reg.mux);
}
 
void test_readCurrentSenseDO_DO_grater_than_8_returns_0() {
    enableCurrentSenseDO(9);
    TEST_ASSERT_EQUAL(0, readCurrentSenseDO());
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_enableCurrentSenseDO_sets_correct_bts71220_mux);
    RUN_TEST(test_disableCurrentSenseDO_sets_bts71220_mux_sleep_mode);
    RUN_TEST(test_readCurrentSenseDO_ok);
    RUN_TEST(test_enableCurrentSenseDO_DO_grater_than_8_does_nothing);
    RUN_TEST(test_readCurrentSenseDO_DO_grater_than_8_returns_0);
    UNITY_END();
    return UNITY_END();
}
