#include <unity.h>
#include "hw_platform.h"
#include "cy8c95xx.h"
 
uint8_t TEST_CY8C95XX_GPIO = 0;
uint8_t TEST_CY8C95XX_PORT = 2;
uint8_t TEST_CY8C95XX_ADDR = CY8C95XX_DEV_ADDR_GND;
#define TEST_CY8C95XX_BIT 0
static cy8c95xx_cfg_t cfg;
static cy8c95xx_t dev;
static cy8c95xx_err_code_t ret;
 
void setUp(void)
{
    cy8c95xx_set_default_cfg(&cfg);
    ret = cy8c95xx_init(&dev, &cfg);
}
 
void tearDown(void)
{
}
 
void test_cy8c95xx_set_default_cfg()
{
    cy8c95xx_cfg_t def_cfg;
    cy8c95xx_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SDA, def_cfg.sda_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SCL, def_cfg.scl_pin);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_SPEED, def_cfg.i2c_speed);
    TEST_ASSERT_EQUAL(CY8C95XX_DEV_ADDR_GND, def_cfg.i2c_addr);
    TEST_ASSERT_EQUAL(PLATFORM_I2C_HW, def_cfg.i2c);
    TEST_ASSERT_EQUAL(CY8C95XX_RST, def_cfg.rst_pin);
    TEST_ASSERT_EQUAL(CY8C95XX_INT, def_cfg.int_pin);
}
 
void test_cy8c95xx_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}
 
void test_cy8c95xx_read_byte_ok()
{
    uint8_t byte;
    ret = cy8c95xx_read_byte(&dev, CY8C95XX_REG_OUT_PORT0, &byte);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0xFF, byte);
}
 
void test_cy8c95xx_write_byte_ok()
{
    uint8_t byte = 0xFF;
    ret = cy8c95xx_write_byte(&dev, CY8C95XX_REG_OUT_PORT0, 0x00);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_OUT_PORT0, &byte);
    TEST_ASSERT_EQUAL(0x00, byte);
    ret = cy8c95xx_write_byte(&dev, CY8C95XX_REG_OUT_PORT0, 0xFF);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_OUT_PORT0, &byte);
    TEST_ASSERT_EQUAL(0xFF, byte);
}
 
void test_cy8c95xx_read_bit_ok()
{
    uint8_t bit;
    ret = cy8c95xx_read_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, &bit);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(1, bit);
}
 
void test_cy8c95xx_write_bit_ok()
{
    uint8_t byte = 0x00;
    uint8_t bit = 1;
    ret = cy8c95xx_write_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, 0);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, &bit);
    TEST_ASSERT_EQUAL(0, bit);
    //
    ret = cy8c95xx_write_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, 1);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, &bit);
    TEST_ASSERT_EQUAL(1, bit);
    //
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_OUT_PORT0, &byte);
    TEST_ASSERT_EQUAL(0xFF, byte);
}
 
void test_cy8c95xx_write_bit_val_grater_than_1_ok()
{
    uint8_t byte = 0x00;
    uint8_t bit = 1;
    ret = cy8c95xx_write_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, 0b10);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, &bit);
    TEST_ASSERT_EQUAL(0, bit); /* Only last bit used if val = 0b10 bit = 0*/
    //
    ret = cy8c95xx_write_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, 1);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_OUT_PORT0, TEST_CY8C95XX_BIT, &bit);
    TEST_ASSERT_EQUAL(1, bit);
    //
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_OUT_PORT0, &byte);
    TEST_ASSERT_EQUAL(0xFF, byte);
}
 
void test_cy8c95xx_pin_mode_ok()
{
    uint8_t dir = 0;
    uint8_t drv_reg_en = 0;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_UP);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_PORT_DIR, (TEST_CY8C95XX_GPIO % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C95XX_GPIO_IN, dir);
    //
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_OUT, CY8C95XX_DRV_PULL_UP);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_PORT_DIR, (TEST_CY8C95XX_GPIO % 8), &dir);
    TEST_ASSERT_EQUAL(CY8C95XX_GPIO_OUT, dir);
    //
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_PULL_UP, (TEST_CY8C95XX_GPIO % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    //
    drv_reg_en = 0;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_PULL_DOWN, (TEST_CY8C95XX_GPIO % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    //
    drv_reg_en = 0;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_OPEN_DRAIN_HIGH);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_OPEN_DRAIN_HIGH, (TEST_CY8C95XX_GPIO % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    //
    drv_reg_en = 0;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_OPEN_DRAIN_LOW);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_OPEN_DRAIN_LOW, (TEST_CY8C95XX_GPIO % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    //
    drv_reg_en = 0;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_STRONG);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_STRONG, (TEST_CY8C95XX_GPIO % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    //
    drv_reg_en = 0;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_SLOW_STRONG);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_SLOW_STRONG, (TEST_CY8C95XX_GPIO % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
    //
    drv_reg_en = 0;
    ret = cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_IN, CY8C95XX_DRV_HIGH_Z);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_HIGH_Z, (TEST_CY8C95XX_GPIO % 8), &drv_reg_en);
    TEST_ASSERT_EQUAL(1, drv_reg_en);
}
 
void test_cy8c95xx_read_pin_in_ok()
{
    uint8_t state = 0;
    ret = cy8c95xx_read_pin(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(1, state);
}
 
void test_cy8c95xx_en_dis_pin_inv_in_ok()
{
    uint8_t state = 0;
    ret = cy8c95xx_pin_en_inv_in(&dev, TEST_CY8C95XX_GPIO);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_pin(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(0, state);
    //
    ret = cy8c95xx_pin_dis_inv_in(&dev, TEST_CY8C95XX_GPIO);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_pin(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(1, state);
}
 
void test_cy8c95xx_read_port_in_ok()
{
    uint8_t state = 0x00;
    ret = cy8c95xx_read_port(&dev, TEST_CY8C95XX_PORT, &state);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0xFF, state);
}
 
void test_cy8c95xx_read_pin_out_lvl_ok()
{
    uint8_t state = 0;
    ret = cy8c95xx_read_pin_out_lvl(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(1, state);
}
 
void test_cy8c95xx_read_port_out_lvl_ok()
{
    uint8_t state = 0x00;
    ret = cy8c95xx_read_port_out_lvl(&dev, TEST_CY8C95XX_PORT, &state);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0xFF, state);
}
 
void test_cy8c95xx_write_pin_ok()
{
    uint8_t state = 0;
    cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_OUT, CY8C95XX_DRV_STRONG);
    ret = cy8c95xx_write_pin(&dev, TEST_CY8C95XX_GPIO, 1);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_pin_out_lvl(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(1, state);
    //
    ret = cy8c95xx_write_pin(&dev, TEST_CY8C95XX_GPIO, 0);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_pin_out_lvl(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(0, state);
    //
    cy8c95xx_pin_mode(&dev, TEST_CY8C95XX_GPIO, CY8C95XX_GPIO_OUT, CY8C95XX_DRV_STRONG);
    ret = cy8c95xx_write_pin(&dev, TEST_CY8C95XX_GPIO, 1);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_pin_out_lvl(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(1, state);
}
 
void test_cy8c95xx_send_cmd_ok()
{
    uint8_t state = 0;
    ret = cy8c95xx_send_cmd(&dev, CY8C95XX_RESTORE_DEFAULTS);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_pin(&dev, TEST_CY8C95XX_GPIO, &state);
    TEST_ASSERT_EQUAL(1, state);
}
 
void test_cy8c95xx_en_dis_pin_pwm_ok()
{
    uint8_t en = 0;
    //
    ret = cy8c95xx_en_pin_pwm(&dev, TEST_CY8C95XX_GPIO);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_SEL_PWM_OUT, (TEST_CY8C95XX_GPIO % 8), &en);
    TEST_ASSERT_EQUAL(1, en);
    //
    ret = cy8c95xx_dis_pin_pwm(&dev, TEST_CY8C95XX_GPIO);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_bit(&dev, CY8C95XX_REG_SEL_PWM_OUT, (TEST_CY8C95XX_GPIO % 8), &en);
    TEST_ASSERT_EQUAL(0, en);
}
 
void test_cy8c95xx_set_pwm_cfg_ok()
{
    uint8_t res_pwm_config = 0x00;
    float res_duty_cyc = 0.0F;
    float res_freq = 0.0F;
    cy8c95xx_pwm_cfg_t pwm_cfg;
    pwm_cfg.pwm_sel = CY8C95XX_SEL_PWM_0;
    pwm_cfg.clk_src = CY8C95XX_PWM_CLK_SRC_93_75_KHZ;
    pwm_cfg.period = 0xFF;
    pwm_cfg.pulse_wid = 0x00;
    pwm_cfg.devider = 0x01;
    ret = cy8c95xx_set_pwm_cfg(&dev, &pwm_cfg, &res_duty_cyc, &res_freq);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_CFG_PWM, &res_pwm_config);
    TEST_ASSERT_EQUAL(pwm_cfg.clk_src, res_pwm_config);
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_PERIOD_PWM, &res_pwm_config);
    TEST_ASSERT_EQUAL(pwm_cfg.period, res_pwm_config);
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_PULSE_WIDTH_PWM, &res_pwm_config);
    TEST_ASSERT_EQUAL(pwm_cfg.pulse_wid, res_pwm_config);
    cy8c95xx_read_byte(&dev, CY8C95XX_REG_DIV_PWM, &res_pwm_config);
    TEST_ASSERT_EQUAL(pwm_cfg.devider, res_pwm_config);
}
 
void test_cy8c95xx_pin_arg_less_than_0_err()
{
    uint8_t dummy;
    ret = cy8c95xx_pin_mode(&dev, -1, CY8C95XX_GPIO_IN, CY8C95XX_DRV_OPEN_DRAIN_LOW);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_read_pin(&dev, -1, &dummy);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_pin_en_inv_in(&dev, -1);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_pin_dis_inv_in(&dev, -1);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_read_pin_out_lvl(&dev, -1, &dummy);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_write_pin(&dev, -1, dummy);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_en_pin_pwm(&dev, -1);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_dis_pin_pwm(&dev, -1);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
void test_cy8c95xx_pin_arg_greater_than_59_err()
{
    uint8_t dummy;
    ret = cy8c95xx_pin_mode(&dev, 60, CY8C95XX_GPIO_IN, CY8C95XX_DRV_OPEN_DRAIN_LOW);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_read_pin(&dev, 60, &dummy);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_pin_en_inv_in(&dev, 60);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_pin_dis_inv_in(&dev, 60);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_read_pin_out_lvl(&dev, 60, &dummy);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_write_pin(&dev, 60, dummy);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_en_pin_pwm(&dev, 60);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
    ret = cy8c95xx_dis_pin_pwm(&dev, 60);
    TEST_ASSERT_EQUAL(PLATFORM_ARGUMENT_ERR, ret);
}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_cy8c95xx_set_default_cfg);
    RUN_TEST(test_cy8c95xx_init_ok);
    RUN_TEST(test_cy8c95xx_read_byte_ok);
    RUN_TEST(test_cy8c95xx_write_byte_ok);
    RUN_TEST(test_cy8c95xx_read_bit_ok);
    RUN_TEST(test_cy8c95xx_write_bit_ok);
    RUN_TEST(test_cy8c95xx_write_bit_val_grater_than_1_ok);
    RUN_TEST(test_cy8c95xx_pin_mode_ok);
    RUN_TEST(test_cy8c95xx_read_pin_in_ok);
    RUN_TEST(test_cy8c95xx_en_dis_pin_inv_in_ok);
    // RUN_TEST(test_cy8c95xx_read_port_in_ok);
    RUN_TEST(test_cy8c95xx_read_pin_out_lvl_ok);
    // RUN_TEST(test_cy8c95xx_read_port_out_lvl_ok);
    RUN_TEST(test_cy8c95xx_write_pin_ok);
    // RUN_TEST(test_cy8c95xx_send_cmd_ok);
    RUN_TEST(test_cy8c95xx_en_dis_pin_pwm_ok);
    RUN_TEST(test_cy8c95xx_set_pwm_cfg_ok);
    RUN_TEST(test_cy8c95xx_pin_arg_less_than_0_err);
    RUN_TEST(test_cy8c95xx_pin_arg_greater_than_59_err);
    return UNITY_END();
}