#include "cy8c95xx.h"
#include "pico/binary_info.h"

static cy8c95xx_t cy8c95xx;

/* Test port expander outputs */
void expander_test_outputs(void)
{
    uint8_t pin_num;
    cy8c95xx_write_port(&cy8c95xx, CY8C95XX_PORT_1, 0xFF);
    printf("All pins set to HIGH logic level!\n");
    platform_sleep_ms(300);
    for (pin_num = 8; pin_num < 16; pin_num++)
    {
        cy8c95xx_write_pin(&cy8c95xx, pin_num, CY8C95XX_LOW);
        printf("Pin %u is set to LOW logic level!\n", pin_num);
        platform_sleep_ms(300);
    }
}

/* Test port expander inputs */
void expander_test_inputs(void)
{
    uint8_t pin_num = 0;
    uint8_t pin_state;
    cy8c95xx_read_pin(&cy8c95xx, pin_num, CY8C95XX_INT_NORMAL, &pin_state);
    printf("Pin %u level is %u!\r\n", pin_num, pin_state);
    platform_sleep_ms(1000);
}

/* Initialize port expander */
void expander_init(void)
{
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    cy8c95xx_init(&cy8c95xx, &cfg);
    cy8c95xx_reset(&cy8c95xx);
}

int main() {
    // Enable print status output
    stdio_init_all();
    // Init and test port expander
    expander_init();
    // Test tasks
    while (1) {
        expander_test_outputs();
        expander_test_inputs();
        platform_sleep_ms(1000);
    }
    return 0;
}
