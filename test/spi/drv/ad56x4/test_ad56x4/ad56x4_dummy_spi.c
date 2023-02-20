#include <unity.h>
#include "hw_platform.h"
#include "ad56x4.h"
 
platform_err_code_t dummy_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (len == 3)
    {
        if (*txdata == (uint8_t)((AD56X4_CMD_WRITE_INPUT_REGISTER << 3) | AD56X4_CH_ADDR_D) &&
            *(txdata + 1) == (uint8_t)((TEST_AD56X4_DAC_DATA >> 8) & 0xFF) &&
            *(txdata + 2) == (uint8_t)(TEST_AD56X4_DAC_DATA & 0xFF))
        {
            return PLATFORM_OK;
        }
    }
    return PLATFORM_SPI_COM_ERR;
}