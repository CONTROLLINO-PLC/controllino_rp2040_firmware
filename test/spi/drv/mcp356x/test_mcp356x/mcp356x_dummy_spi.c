#ifdef NATIVE_TEST_ENV
 
#include "hw_platform.h"
#include "mcp356x.h"
 
static uint8_t cfg2_val = MCP356X_CFG_2_BOOST_X_1 | MCP356X_CFG_2_GAIN_X_2 | MCP356X_CFG_2_AZ_MUX_DIS | MCP356X_CFG_2_AZ_VREF_DIS;
static uint8_t cfg3_val = MCP356X_CFG_3_CONV_MODE_CONT | MCP356X_CFG_3_DATA_FORMAT_DEF | MCP356X_CFG_3_CRC_COM_DIS | MCP356X_CFG_3_CRC_GAIN_CAL_DIS;
 
platform_err_code_t dummy_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    uint8_t fcmd_addr = (*txdata & MCP356X_FCMD_ADDR_MASK) >> 2;
    uint8_t rw_cmd = *txdata & MCP356X_RW_CMD_MASK;
    if (fcmd_addr == MCP356X_REG_CFG_2) {
        if (rw_cmd == MCP356X_CMD_INC_WRITE)
        {
            cfg2_val = *(txdata + 1);
            if (len > 2) cfg3_val = *(txdata + 2);
        }
        else {
            *(rxdata + 1) = cfg2_val;
            if (len > 2) *(rxdata + 2) = cfg3_val;
        }
    }
    else if (fcmd_addr == MCP356X_REG_CFG_3) {
        if (rw_cmd == MCP356X_CMD_INC_WRITE)
            cfg3_val = *(txdata + 1);
        else
            *(rxdata + 1) = cfg3_val;
    }
    *rxdata = MCP356X_VALID_STATUS_MASK;
    return PLATFORM_OK;
}
 
#endif