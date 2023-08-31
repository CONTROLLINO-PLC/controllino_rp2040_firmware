#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "wsen_temp.h"
#include "string.h"
 
static uint8_t reg_addr;
static uint8_t ctrl_reg_content = 0x00;
static uint8_t high_lim_reg_content = 0x00;
static uint8_t low_lim_reg_content = 0x00;
 
platform_err_code_t mock_i2c_read(uint8_t addr, uint8_t* rxdata, size_t len)
{
    memset(rxdata, 0x00, len);
    if (addr == WSEN_TEMP_ADDRESS_SAO_GND)
    {
        if (reg_addr == WSEN_TEMP_REG_DEVICE_ID)
            *rxdata = WSEN_TEMP_DEVICE_ID_VALUE;
        if (reg_addr == WSEN_TEMP_REG_CTRL)
            *rxdata = ctrl_reg_content;
        if (reg_addr == WSEN_TEMP_REG_HIGH_LIM)
            *rxdata = high_lim_reg_content;
        if (reg_addr == WSEN_TEMP_REG_LOW_LIM)
            *rxdata = low_lim_reg_content;
        if (reg_addr == WSEN_TEMP_REG_STATUS)
            *rxdata = 0x06; // over_lim = 1 and under_lim = 1
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
platform_err_code_t mock_i2c_write(uint8_t addr, uint8_t* txdata, size_t len)
{
    if (addr == WSEN_TEMP_ADDRESS_SAO_GND)
    {
        reg_addr = *txdata;
        if (len > 1)
        {
            if (reg_addr == WSEN_TEMP_REG_CTRL)
                ctrl_reg_content = *(txdata + 1);
            if (reg_addr == WSEN_TEMP_REG_HIGH_LIM)
                high_lim_reg_content = *(txdata + 1);
            if (reg_addr == WSEN_TEMP_REG_LOW_LIM)
                low_lim_reg_content = *(txdata + 1);
        }
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
#endif