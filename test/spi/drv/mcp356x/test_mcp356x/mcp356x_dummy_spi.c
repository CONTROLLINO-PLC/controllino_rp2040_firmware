#include <unity.h>
#include "hw_platform.h"
#include "mcp356x.h"

platform_err_code_t dummy_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    return PLATFORM_OK;
}