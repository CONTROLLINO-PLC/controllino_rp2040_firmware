#include "cy8c95xx.h"
#include "ad56x4.h"
#include "pico/binary_info.h"

cy8c95xx_t cy8c9520;

/* Init cy8c95xx port expander */
void exp_init(void)
{
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    cy8c95xx_init(&cy8c9520, &cfg);
    cy8c95xx_reset(&cy8c9520);
}

ad56x4_t ad5664;
#define CY8C9520_GPIO_15    15
#define AD5664_CS           CY8C9520_GPIO_15
#define NEO_AO_MAX_10V      10000 

void ad56x4_cs_select(ad56x4_t* dac) {
    cy8c95xx_write_pin(&cy8c9520, AD5664_CS, CY8C95XX_LOW);
}

void ad56x4_cs_deselect(ad56x4_t* dac) {
    cy8c95xx_write_pin(&cy8c9520, AD5664_CS, CY8C95XX_HIGH);
}

void dac_init(void) {
    ad56x4_cfg_t cfg;
    ad56x4_set_default_cfg(&cfg);
    ad56x4_init(&ad5664, &cfg);
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
    // Init CY8C9520
    exp_init();
    // Init AD5664
    dac_init();
    // Set test voltage to output
    // uint8_t channel = AD56X4_ADDR_CH_A;
    // uint8_t channel = AD56X4_ADDR_CH_B;
    // uint8_t channel = AD56X4_ADDR_CH_C;
    // uint8_t channel = AD56X4_ADDR_CH_D;
    uint8_t channel = AD56X4_ADDR_CH_ALL;
    ad56x4_set_ch_voltage(&ad5664, channel, 2000,  NEO_AO_MAX_10V);
    ad56x4_set_ch_voltage(&ad5664, channel, 5555,  NEO_AO_MAX_10V);
    ad56x4_set_ch_voltage(&ad5664, channel, 8000,  NEO_AO_MAX_10V);
    ad56x4_set_ch_voltage(&ad5664, channel, 10000, NEO_AO_MAX_10V);
    ad56x4_set_ch_voltage(&ad5664, channel, 0,     NEO_AO_MAX_10V);
    while (1)
    {
        asm volatile("nop");
    }

    return 0;
}