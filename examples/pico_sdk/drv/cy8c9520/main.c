#include <stdio.h>
#include <pico/stdlib.h>
#include "cy8c9520.h"

static cy8c9520_t cy8c9520;
#define OUTPIN 15
#define INPIN 0

/* Test port expander output */
void expander_test_output(void)
{
    uint8_t pin_state;
    cy8c9520_write_pin(&cy8c9520, OUTPIN, CY8C9520_LOW);
    cy8c9520_read_pin_out_lvl(&cy8c9520, OUTPIN, &pin_state);
    printf("Pin %u out level is %u!\r\n", OUTPIN, pin_state);
    sleep_ms(1000);
    cy8c9520_write_pin(&cy8c9520, OUTPIN, CY8C9520_HIGH);
    cy8c9520_read_pin_out_lvl(&cy8c9520, OUTPIN, &pin_state);
    printf("Pin %u out level is %u!\r\n", OUTPIN, pin_state);

}

/* Test port expander input */
void expander_test_input(void)
{
    uint8_t pin_state;
    cy8c9520_read_pin(&cy8c9520, INPIN, &pin_state);
    printf("Pin %u level is %u!\r\n", INPIN, pin_state);
}

/* Initialize port expander */
void expander_init(void)
{
    cy8c9520_cfg_t cfg;
    cy8c9520_set_default_cfg(&cfg);
    cy8c9520_init(&cy8c9520, &cfg);
    // Set pin modes
    cy8c9520_pin_mode(&cy8c9520, INPIN, CY8C9520_GPIO_IN, CY8C9520_REG_PULL_UP);
    cy8c9520_pin_mode(&cy8c9520, OUTPIN, CY8C9520_GPIO_OUT, CY8C9520_REG_PULL_UP);
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
        sleep_ms(1000);
    }
    return 0;
}
