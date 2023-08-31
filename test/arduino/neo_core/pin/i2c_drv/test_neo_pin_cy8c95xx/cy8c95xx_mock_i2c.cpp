#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "cy8c9520.h"
#include "string.h"
 
extern uint8_t TEST_CY8C9520_GPIO;
extern uint8_t TEST_CY8C9520_ADDR;
static uint8_t reg_addr;
static uint8_t port_dir_reg_content = 0x00;
static uint8_t drv_reg_content = 0x00;
static bool inverted_input = false;
static uint8_t in_port0_reg_content = 0xFF;
static uint8_t out_port0_reg_content = 0xFF;
static uint8_t sel_pwm_reg_content = 0x00;
static uint8_t cfg_pwm_reg_content = 0x00;
static uint8_t period_pwm_reg_content = 0x00;
static uint8_t pulse_witdth_pwm_reg_content = 0x00;
static uint8_t div_pwm_reg_content = 0x00;
 
platform_err_code_t mock_i2c_read(uint8_t addr, uint8_t* rxdata, size_t len)
{
    memset(rxdata, 0x00, len);
    if (addr == (CY8C9520_M_PORT_BASE_ADDR | TEST_CY8C9520_ADDR))
    {
        if (reg_addr == CY8C9520_REG_PORT_DIR)
            *rxdata = port_dir_reg_content;
        else if (reg_addr >= CY8C9520_REG_PULL_UP && reg_addr <= CY8C9520_REG_HIGH_Z)
            *rxdata = drv_reg_content;
        else if (reg_addr == CY8C9520_REG_IN_PORT0)
            *rxdata = inverted_input ? 0x00 : in_port0_reg_content;
        else if (reg_addr == CY8C9520_REG_OUT_PORT0)
            *rxdata = out_port0_reg_content;
        else if (reg_addr == CY8C9520_REG_SEL_PWM_OUT)
            *rxdata = sel_pwm_reg_content;
        else if (reg_addr == CY8C9520_REG_CFG_PWM)
            *rxdata = cfg_pwm_reg_content;
        else if (reg_addr == CY8C9520_REG_PERIOD_PWM)
            *rxdata = period_pwm_reg_content;
        else if (reg_addr == CY8C9520_REG_PULSE_WIDTH_PWM)
            *rxdata = pulse_witdth_pwm_reg_content;
        else if (reg_addr == CY8C9520_REG_DIV_PWM)
            *rxdata = div_pwm_reg_content;
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
platform_err_code_t mock_i2c_write(uint8_t addr, uint8_t* txdata, size_t len)
{
    if (addr == (CY8C9520_M_PORT_BASE_ADDR | TEST_CY8C9520_ADDR))
    {
        reg_addr = *txdata;
        if (len > 1)
        {
            if (reg_addr == CY8C9520_REG_PORT_DIR)
                port_dir_reg_content = *(txdata + 1);
            else if (reg_addr >= CY8C9520_REG_PULL_UP && reg_addr <= CY8C9520_REG_HIGH_Z) {
                drv_reg_content = *(txdata + 1);
                if (reg_addr == CY8C9520_REG_PULL_DOWN)
                    in_port0_reg_content = 0x3F;
                else
                    in_port0_reg_content = 0xFF;
            }
            else if (reg_addr == CY8C9520_REG_INV)
                inverted_input = (*(txdata + 1) & (1 << (TEST_CY8C9520_GPIO % 8))) ? true : false;
            else if (reg_addr == CY8C9520_REG_OUT_PORT0)
                out_port0_reg_content = *(txdata + 1);
            else if (reg_addr == CY8C9520_REG_SEL_PWM_OUT)
                sel_pwm_reg_content = *(txdata + 1);
            else if (reg_addr == CY8C9520_REG_CFG_PWM)
                cfg_pwm_reg_content = *(txdata + 1);
            else if (reg_addr == CY8C9520_REG_PERIOD_PWM)
                period_pwm_reg_content = *(txdata + 1);
            else if (reg_addr == CY8C9520_REG_PULSE_WIDTH_PWM)
                pulse_witdth_pwm_reg_content = *(txdata + 1);
            else if (reg_addr == CY8C9520_REG_DIV_PWM)
                div_pwm_reg_content = *(txdata + 1);
        }
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
#endif