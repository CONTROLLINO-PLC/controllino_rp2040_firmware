#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "mcp4461.h"
#include "string.h"

static uint8_t reg_addr;
static uint16_t reg_tcon_0_value = 0x01FF;
static uint16_t reg_v_wiper_0_value = 0x0000;
 
platform_err_code_t mock_i2c_read(uint8_t addr, uint8_t* rxdata, size_t len)
{
    memset(rxdata, 0x00, len);
    if (addr == MCP4461_DEV_ADDR_1)
    {
        if (reg_addr == MCP4461_REG_TCON_0) {
            *rxdata = reg_tcon_0_value >> 8 & MCP4461_DATA_MASK;
            *(rxdata + 1) = reg_tcon_0_value & 0xFF;
        }
        if (reg_addr == MCP4461_REG_V_WIPER_0) {
            *rxdata = reg_v_wiper_0_value >> 8 & MCP4461_DATA_MASK;
            *(rxdata + 1) = reg_v_wiper_0_value & 0xFF;
        }
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
platform_err_code_t mock_i2c_write(uint8_t addr, uint8_t* txdata, size_t len)
{
    if (addr == MCP4461_DEV_ADDR_1)
    {
        reg_addr = *txdata >> 4 & 0b00001111;
        if (len > 1) {
            if (reg_addr == MCP4461_REG_V_WIPER_0) {
                reg_v_wiper_0_value = (*txdata & MCP4461_DATA_MASK) << 8 | *(txdata + 1);
            }
        }
        return PLATFORM_OK;
    }
    return PLATFORM_I2C_COM_ERR;
}
 
#endif