#include "cy8c95xx.h"
#include "mcp356x.h"
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

mcp356x_t mcp3564;
#define CY8C9520_GPIO_14    14
#define MCP3564_CS           CY8C9520_GPIO_14
#define NEO_AO_MAX_10V      10000 

void mcp356x_cs_select(mcp356x_t* dac) {
    cy8c95xx_write_pin(&cy8c9520, MCP3564_CS, CY8C95XX_LOW);
}

void mcp356x_cs_deselect(mcp356x_t* dac) {
    cy8c95xx_write_pin(&cy8c9520, MCP3564_CS, CY8C95XX_HIGH);
}

void mcp356x_print_registers(void) {
    
}

void adc_init(void) {
    mcp356x_cfg_t cfg;
    mcp356x_set_default_cfg(&cfg);
    mcp356x_init(&mcp3564, &cfg);
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
    // Init CY8C9520
    exp_init();
    // Init MCP356X
    adc_init();
    
    while (1)
    {
        asm volatile("nop");
    }

    return 0;
}