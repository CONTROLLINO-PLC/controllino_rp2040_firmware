#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "ad5664.h"
 
extern uint16_t TEST_AD5664_DAC_DATA;
 
static bool ad5664_check(uint8_t* txdata, uint8_t* rxdata, ad5664_cmd_t cmd, ad5664_ch_addr_t ch_addr, uint16_t data)
{
    return
        *txdata == (uint8_t)((cmd << 3) | ch_addr) &&
        *(txdata + 1) == (uint8_t)((data >> 8) & 0xFF) &&
        *(txdata + 2) == (uint8_t)(data & 0xFF);
}
 
platform_err_code_t mock_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (len == 3)
    {
        if (ad5664_check(txdata, rxdata, AD5664_CMD_SW_RESET, AD5664_CH_DONT_CARE, AD5664_SW_RST_FULL) || /* test_ad5664_init_dev_ok ad5664_sw_reset */
            ad5664_check(txdata, rxdata, AD5664_CMD_WRITE_INPUT_REGISTER, AD5664_CH_ADDR_D, TEST_AD5664_DAC_DATA) || /* test_ad5664_write_input_reg_ok */
            ad5664_check(txdata, rxdata, AD5664_CMD_UPDATE_DAC_REGISTER, AD5664_CH_ADDR_D, AD5664_DATA_DONT_CARE) || /* test_ad5664_update_dac_reg_ok */
            ad5664_check(txdata, rxdata, AD5664_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL, AD5664_CH_ADDR_B, TEST_AD5664_DAC_DATA) || /* test_ad5664_write_input_reg_update_all_dac_ok */
            ad5664_check(txdata, rxdata, AD5664_CMD_WRITE_UPDATE_CH, AD5664_CH_ADDR_ALL, TEST_AD5664_DAC_DATA) || /* test_ad5664_write_update_dac_reg_ok */
            ad5664_check(txdata, rxdata, AD5664_CMD_POWER_UPDOWN, AD5664_CH_DONT_CARE, (AD5664_PWR_MODE_POWERDOWN_100K << 4) | AD5664_CH_SELECT_D) || /* test_ad5664_set_pwr_ok */
            ad5664_check(txdata, rxdata, AD5664_CMD_SET_LDAC, AD5664_CH_DONT_CARE, AD5664_CH_SELECT_D)) /* test_ad5664_set_ldev_ok test_ad5664_set_ldev_greater_than_0xF_ignored */
        {
            return PLATFORM_OK;
        }
    }
    return PLATFORM_SPI_COM_ERR;
}
 
#endif