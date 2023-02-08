#include "cy8c95xx.h"
#include "bts71220.h"

cy8c95xx_t cy8c9520;

bts71220_t bts71220;

#ifdef BTS71220_CS
#undef BTS71220_CS
#endif
#define BTS71220_CS          CY8C95XX_GPIO_12

#ifdef BTS71220_DAISY_CHAIN_SIZE
#undef BTS71220_DAISY_CHAIN_SIZE
#endif
#define BTS71220_DAISY_CHAIN_SIZE     2

void exp_init(void)
{
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    cy8c95xx_init(&cy8c9520, &cfg);
    cy8c95xx_reset(&cy8c9520);
    cy8c95xx_pin_mode(&cy8c9520, BTS71220_CS, CY8C95XX_GPIO_OUT, CY8C95XX_REG_PULL_UP);
}

void bts71220_cs_select(bts71220_t* dac)
{
    cy8c95xx_write_pin(&cy8c9520, BTS71220_CS, CY8C95XX_LOW);
}

void bts71220_cs_deselect(bts71220_t* dac)
{
    cy8c95xx_write_pin(&cy8c9520, BTS71220_CS, CY8C95XX_HIGH);
}

void power_out_init(void) {
    bts71220_cfg_t cfg;
    cfg.dchain_size = BTS71220_DAISY_CHAIN_SIZE;
    bts71220_set_default_cfg(&cfg);
    bts71220_init(&bts71220, &cfg);
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
    // Init CY8C9520
    exp_init();
    // Init BTS71220
    power_out_init();
    while (1)
    {
        asm volatile("nop");
    }
    return 0;
}