#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "ad56x4.h"
 
extern uint16_t TEST_AD56X4_DAC_DATA;
 
static bool ad56x4_check(uint8_t* txdata, uint8_t* rxdata, ad56x4_cmd_t cmd, ad56x4_ch_addr_t ch_addr, uint16_t data)
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
        if (ad56x4_check(txdata, rxdata, AD56X4_CMD_SW_RESET, AD56X4_CH_DONT_CARE, AD56X4_SW_RST_FULL) || /* test_ad56x4_init_dev_ok ad56x4_sw_reset */
            ad56x4_check(txdata, rxdata, AD56X4_CMD_WRITE_INPUT_REGISTER, AD56X4_CH_ADDR_D, TEST_AD56X4_DAC_DATA) || /* test_ad56x4_write_input_reg_ok */
            ad56x4_check(txdata, rxdata, AD56X4_CMD_UPDATE_DAC_REGISTER, AD56X4_CH_ADDR_D, AD56X4_DATA_DONT_CARE) || /* test_ad56x4_update_dac_reg_ok */
            ad56x4_check(txdata, rxdata, AD56X4_CMD_WRITE_INPUT_REGISTER_UPDATE_ALL, AD56X4_CH_ADDR_B, TEST_AD56X4_DAC_DATA) || /* test_ad56x4_write_input_reg_update_all_dac_ok */
            ad56x4_check(txdata, rxdata, AD56X4_CMD_WRITE_UPDATE_CH, AD56X4_CH_ADDR_ALL, TEST_AD56X4_DAC_DATA) || /* test_ad56x4_write_update_dac_reg_ok */
            ad56x4_check(txdata, rxdata, AD56X4_CMD_POWER_UPDOWN, AD56X4_CH_DONT_CARE, (AD56X4_PWR_MODE_POWERDOWN_100K << 4) | AD56X4_CH_SELECT_D) || /* test_ad56x4_set_pwr_ok */
            ad56x4_check(txdata, rxdata, AD56X4_CMD_SET_LDAC, AD56X4_CH_DONT_CARE, AD56X4_CH_SELECT_D)) /* test_ad56x4_set_ldev_ok test_ad56x4_set_ldev_greater_than_0xF_ignored */
        {
            return PLATFORM_OK;
        }
    }
    return PLATFORM_SPI_COM_ERR;
}
 
#endif