#ifdef NATIVE_TEST_ENV
 
#include "hw_platform.h"
 
platform_err_code_t mock_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (len == 1)
    {
        if (*txdata == 0x00)
            return PLATFORM_OK;
    }
    return PLATFORM_SPI_COM_ERR;
}
 
#endif