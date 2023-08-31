#ifdef NATIVE_ENV
 
#include "hw_platform.h"
#include "bts71220.h"
 
static uint8_t out_reg_content[BTS71220_DAISY_CHAIN_SIZE];
static uint8_t dcr_reg_content[BTS71220_DAISY_CHAIN_SIZE];

platform_err_code_t mock_spi_transfer(uint8_t* txdata, uint8_t* rxdata, size_t len)
{
    if (len == BTS71220_DAISY_CHAIN_SIZE)
    {
        for (size_t i = 0; i < BTS71220_DAISY_CHAIN_SIZE; i++)
        {
            uint8_t req = *(txdata + i);
            if (req & BTS71220_WRITE_MASK) /* Write */
            {
                if (!(req & (~BTS71220_OUT_RES_MASK & 0xFF))) /* BTS71220_REG_OUT */
                    out_reg_content[i] = req & BTS71220_REG_CONT_MASK;
                if (req & (BTS71220_REG_DCR & BTS71220_ADRR0_MASK)) /* BTS71220_REG_DCR */
                    dcr_reg_content[i] = req & BTS71220_REG_CONT_MASK;
                *(rxdata + i) = BTS71220_DIAG_RES_MASK;
            }
            else /* Read */
            {
                uint8_t resp = 0x00;
                if (req == BTS71220_REG_OUT) /* BTS71220_REG_OUT */
                    resp |= out_reg_content[i];
                else if (req == BTS71220_REG_DCR) /* BTS71220_REG_DCR */
                    resp |= dcr_reg_content[i];
                if (req == BTS71220_REG_WRN_DIAG || req == BTS71220_REG_ERR_DIAG)
                    resp |= BTS71220_ERR_WARN_MASK;
                else if (req != BTS71220_REG_STD_DIAG)
                    resp |= BTS71220_WRITE_MASK;
                resp |= (req & BTS71220_ADRR0_MASK);
                *(rxdata + i) = resp;
            }
        }
        return PLATFORM_OK;
    }
    return PLATFORM_SPI_COM_ERR;
}
 
#endif