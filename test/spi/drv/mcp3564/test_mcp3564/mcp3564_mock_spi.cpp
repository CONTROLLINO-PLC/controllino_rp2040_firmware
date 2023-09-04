#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "mcp3564.h"
 
static uint8_t cfg2_val = MCP3564_CFG_2_BOOST_X_1 | MCP3564_CFG_2_GAIN_X_2 | MCP3564_CFG_2_AZ_MUX_DIS | MCP3564_CFG_2_AZ_VREF_DIS;
static uint8_t cfg3_val = MCP3564_CFG_3_CONV_MODE_CONT | MCP3564_CFG_3_DATA_FORMAT_DEF | MCP3564_CFG_3_CRC_COM_DIS | MCP3564_CFG_3_CRC_GAIN_CAL_DIS;
 
platform_err_code_t mock_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    uint8_t fcmd_addr = (*txdata & MCP3564_FCMD_ADDR_MASK) >> 2;
    uint8_t rw_cmd = *txdata & MCP3564_RW_CMD_MASK;
    if (fcmd_addr == MCP3564_REG_CFG_2) {
        if (rw_cmd == MCP3564_CMD_INC_WRITE)
        {
            cfg2_val = *(txdata + 1);
            if (len > 2) cfg3_val = *(txdata + 2);
        }
        else {
            *(rxdata + 1) = cfg2_val;
            if (len > 2) *(rxdata + 2) = cfg3_val;
        }
    }
    else if (fcmd_addr == MCP3564_REG_CFG_3) {
        if (rw_cmd == MCP3564_CMD_INC_WRITE)
            cfg3_val = *(txdata + 1);
        else
            *(rxdata + 1) = cfg3_val;
    }
    *rxdata = MCP3564_VALID_STATUS_MASK;
    return PLATFORM_OK;
}
 
void mcp3564_cs_select(int cs_pin) {}
void mcp3564_cs_deselect(int cs_pin) {}
 
#endif