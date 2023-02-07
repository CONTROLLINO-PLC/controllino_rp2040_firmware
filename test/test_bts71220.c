#include "cy8c95xx.h"
#include "bts71220.h"

cy8c95xx_t cy8c9520;

void exp_init(void)
{
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    cy8c95xx_init(&cy8c9520, &cfg);
    cy8c95xx_reset(&cy8c9520);
    // cy8c95xx_pin_mode(&cy8c9520, CY8C9520_GPIO_15, CY8C95XX_GPIO_OUT, CY8C95XX_REG_PULL_UP);
}

// void dac_init(void) {
//     ad56x4_cfg_t cfg;
//     ad56x4_set_default_cfg(&cfg);
//     ad56x4_init(&ad5664, &cfg);
// }

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
    // Init CY8C9520
    exp_init();
    while (1)
    {
        
    }
    return 0;
}