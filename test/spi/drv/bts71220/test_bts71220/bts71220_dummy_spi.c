#include <unity.h>
#include "hw_platform.h"
#include "bts71220.h"

platform_err_code_t dummy_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (len == BTS71220_DAISY_CHAIN_SIZE)
    {
        if (*(txdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) == BTS71220_REG_STD_DIAG)
        {
            *(rxdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) = BTS71220_DIAG_RES_MASK;
            return PLATFORM_OK;
        }
        else if (*(txdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) == BTS71220_REG_WRN_DIAG ||
            *(txdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) == BTS71220_REG_WRN_DIAG)
        {
            *(rxdata + TEST_BTS71220_DAISY_CHAIN_NUMBER) = BTS71220_RB_MASK;
            return PLATFORM_OK;
        }
    }
    return PLATFORM_SPI_COM_ERR;
}