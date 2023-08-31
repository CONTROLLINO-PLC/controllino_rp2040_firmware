#include <stdio.h>
#include <pico/stdlib.h>
#include "cy8c9520.h"
#include "ad5664.h"

cy8c9520_t cy8c9520;

ad5664_t ad5664;
#define AD5664_CS           CY8C9520_GPIO_15
#define NEO_AO_MAX_10V      10000 

void exp_init(void)
{
    cy8c9520_cfg_t cfg;
    cy8c9520_set_default_cfg(&cfg);
    cy8c9520_init(&cy8c9520, &cfg);
    cy8c9520_pin_mode(&cy8c9520, AD5664_CS, CY8C9520_GPIO_OUT, CY8C9520_REG_PULL_UP);
}

void ad5664_cs_select(ad5664_t* dac) {
    cy8c9520_write_pin(&cy8c9520, AD5664_CS, CY8C9520_LOW);
}

void ad5664_cs_deselect(ad5664_t* dac) {
    cy8c9520_write_pin(&cy8c9520, AD5664_CS, CY8C9520_HIGH);
}

void dac_init(void) {
    ad5664_cfg_t cfg;
    ad5664_set_default_cfg(&cfg);
    ad5664_init(&ad5664, &cfg);
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
    // Init CY8C9520
    exp_init();
    // Init AD5664
    dac_init();
    // Set test voltage to output
    // uint8_t channel = AD5664_CH_ADDR_A;
    // uint8_t channel = AD5664_CH_ADDR_B;
    // uint8_t channel = AD5664_CH_ADDR_C;
    // uint8_t channel = AD5664_CH_ADDR_D;
    uint8_t channel = AD5664_CH_ADDR_ALL;
    while (1)
    {
        ad5664_set_ch_voltage(&ad5664, channel, 2000, NEO_AO_MAX_10V);
        sleep_ms(1000);
        ad5664_set_ch_voltage(&ad5664, channel, 5555, NEO_AO_MAX_10V);
        sleep_ms(1000);
        ad5664_set_ch_voltage(&ad5664, channel, 8000, NEO_AO_MAX_10V);
        sleep_ms(1000);
        ad5664_set_ch_voltage(&ad5664, channel, 10000, NEO_AO_MAX_10V);
        sleep_ms(1000);
        ad5664_set_ch_voltage(&ad5664, channel, 0, NEO_AO_MAX_10V);
        sleep_ms(1000);
    }
    return 0;
}