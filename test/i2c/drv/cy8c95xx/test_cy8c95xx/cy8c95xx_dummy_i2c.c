#ifdef NATIVE_TEST_ENV
 
#include "hw_platform.h"
#include "cy8c95xx.h"
 
extern uint8_t TEST_CY8C95XX_GPIO;
extern uint8_t TEST_CY8C95XX_ADDR;
static uint8_t port_dir_reg_content = 0x00;
static uint8_t pull_up_reg_content = 0x00;
static uint8_t in_reg_content = 0x00;
static uint8_t reg;
 
platform_err_code_t dummy_i2c_read(uint8_t addr, uint8_t* rxdata, size_t len)
{
    if (addr == (CY8C95XX_M_PORT_BASE_ADDR | TEST_CY8C95XX_ADDR))
    {
        if (reg == CY8C95XX_REG_PORT_DIR)
            *rxdata = port_dir_reg_content;
        else if (reg == CY8C95XX_REG_PULL_UP)
            *rxdata = pull_up_reg_content;
        else if (reg == (CY8C95XX_REG_IN_PORT0 + (TEST_CY8C95XX_GPIO / 8)))
        {
            in_reg_content |= (1 << (TEST_CY8C95XX_GPIO % 8)); /* Simulate one on pin */
            *rxdata = in_reg_content;
        }
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
platform_err_code_t dummy_i2c_write(uint8_t addr, uint8_t* txdata, size_t len)
{
    if (addr == (CY8C95XX_M_PORT_BASE_ADDR | TEST_CY8C95XX_ADDR))
    {
        reg = *txdata;
        if (len > 1)
        {
            if (reg == CY8C95XX_REG_PORT_DIR)
                port_dir_reg_content = *(txdata + 1);
            else if (reg == CY8C95XX_REG_PULL_UP)
                pull_up_reg_content = *(txdata + 1);
        }
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
#endif