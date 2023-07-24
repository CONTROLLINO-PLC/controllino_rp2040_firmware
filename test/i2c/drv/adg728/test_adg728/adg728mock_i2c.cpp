#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "adg728.h"
#include "string.h"
 
static uint8_t channel_selected = 0x00;
 
platform_err_code_t mock_i2c_read(uint8_t addr, uint8_t* rxdata, size_t len)
{
    memset(rxdata, 0x00, len);
    if (addr == ADG728_DEV_ADDR_0)
    {
        *rxdata = channel_selected;
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
platform_err_code_t mock_i2c_write(uint8_t addr, uint8_t* txdata, size_t len)
{
    if (addr == ADG728_DEV_ADDR_0)
    {
        channel_selected = *txdata;
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
#endif