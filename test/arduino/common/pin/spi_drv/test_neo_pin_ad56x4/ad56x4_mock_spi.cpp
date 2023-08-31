#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "ad5664.h"
 
extern uint16_t TEST_AD5664_DAC_DATA;
static uint16_t tx_dac_data = 0;
 
static bool ad5664_check_write_input_reg(uint8_t* txdata, uint8_t* rxdata)
{
    return
        *txdata == (uint8_t)((AD5664_CMD_WRITE_INPUT_REGISTER << 3) | AD5664_CH_ADDR_A) ||
        *txdata == (uint8_t)((AD5664_CMD_WRITE_INPUT_REGISTER << 3) | AD5664_CH_ADDR_B) ||
        *txdata == (uint8_t)((AD5664_CMD_WRITE_INPUT_REGISTER << 3) | AD5664_CH_ADDR_C) ||
        *txdata == (uint8_t)((AD5664_CMD_WRITE_INPUT_REGISTER << 3) | AD5664_CH_ADDR_D);
}
 
static bool ad5664_check_update_dac_reg(uint8_t* txdata, uint8_t* rxdata)
{
    return
        *txdata == (uint8_t)((AD5664_CMD_UPDATE_DAC_REGISTER << 3) | AD5664_CH_ADDR_A) ||
        *txdata == (uint8_t)((AD5664_CMD_UPDATE_DAC_REGISTER << 3) | AD5664_CH_ADDR_B) ||
        *txdata == (uint8_t)((AD5664_CMD_UPDATE_DAC_REGISTER << 3) | AD5664_CH_ADDR_C) ||
        *txdata == (uint8_t)((AD5664_CMD_UPDATE_DAC_REGISTER << 3) | AD5664_CH_ADDR_D);
}
 
platform_err_code_t mock_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (len == 3)
    {
        if (ad5664_check_write_input_reg(txdata, rxdata))
            tx_dac_data = (*(txdata + 1) << 8) | *(txdata + 2);
        else if (ad5664_check_update_dac_reg(txdata, rxdata))
            TEST_AD5664_DAC_DATA = tx_dac_data;
        return PLATFORM_OK;
    }
    return PLATFORM_SPI_COM_ERR;
}
 
#endif