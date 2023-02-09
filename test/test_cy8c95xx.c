#include "cy8c95xx.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

static cy8c95xx_t cy8c9520;
#define OUTPIN 15
#define INPIN 0

/* Test port expander output */
void expander_test_output(void)
{
    uint8_t pin_state;
    cy8c95xx_write_pin(&cy8c9520, OUTPIN, CY8C95XX_LOW);
    cy8c95xx_read_pin_out_lvl(&cy8c9520, OUTPIN, &pin_state);
    printf("Pin %u out level is %u!\r\n", OUTPIN, pin_state);
    platform_sleep_ms(1000);
    cy8c95xx_write_pin(&cy8c9520, OUTPIN, CY8C95XX_HIGH);
    cy8c95xx_read_pin_out_lvl(&cy8c9520, OUTPIN, &pin_state);
    printf("Pin %u out level is %u!\r\n", OUTPIN, pin_state);
    
}

/* Test port expander input */
void expander_test_input(void)
{
    uint8_t pin_state;
    cy8c95xx_read_pin(&cy8c9520, INPIN, &pin_state);
    printf("Pin %u level is %u!\r\n", INPIN, pin_state);
}

/* Initialize port expander */
void expander_init(void)
{
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    cy8c95xx_init(&cy8c9520, &cfg);
    // Set pin modes
    cy8c95xx_pin_mode(&cy8c9520, INPIN, CY8C95XX_GPIO_IN, CY8C95XX_REG_PULL_UP);
    cy8c95xx_pin_mode(&cy8c9520, OUTPIN, CY8C95XX_GPIO_OUT, CY8C95XX_REG_PULL_UP);
}

int main() {
    // Enable print status output
    stdio_init_all();
    // Init and test port expander
    expander_init();
    // Test tasks
    while (1) {
        expander_test_output();
        expander_test_input();
        platform_sleep_ms(1000);
    }
    return 0;
}
