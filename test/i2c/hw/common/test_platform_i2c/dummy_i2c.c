#ifdef NATIVE_TEST_ENV
 
#include "hw_platform.h"
 
platform_err_code_t dummy_i2c_read(uint8_t addr, uint8_t* rxdata, size_t len)
{
    return PLATFORM_OK;
}
 
platform_err_code_t dummy_i2c_write(uint8_t addr, uint8_t* txdata, size_t len)
{
    return PLATFORM_OK;
}
 
#endif