#include "cy8c95xx.h"
#include "pico/binary_info.h"

static cy8c95xx_t cy8c95xx;

uint8_t pin_num;
uint8_t pin_state;

/* Task to test port expander functions */
void expander_task(void)
{
    // Out Test
    cy8c95xx_write_port(&cy8c95xx, CY8C95XX_PORT_1, 0xFF);
    // cy8c95xx_write_port(&cy8c95xx, CY8C95XX_PORT_2, 0xFF);

    printf("All pins set to HIGH logic level!\r\n");
    printf("---------------------------------\r\n");
    sleep_ms(2000);

    for (pin_num = 8; pin_num < 15; pin_num++)
    {
        cy8c95xx_write_pin(&cy8c95xx, pin_num, CY8C95XX_LOW);
        printf("Pin %u is set to LOW logic level!\r\n", pin_num);
        sleep_ms(300);
    }

    // // In test
    // pin_num = 0;
    // pin_state = cy8c95xx_read_pin(&cy8c95xx, pin_num, 0);
    // printf("Pin %u level is %u!\r\n", pin_num, pin_state);

    printf("---------------------------------\r\n");
    sleep_ms(1000);
}

/* Initialize port expander */
void expander_init(void)
{
    printf("---- Port expander Init ----\r\n");
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    if (cy8c95xx_init(&cy8c95xx, &cfg) == CY8C95XX_OK) {
        cy8c95xx_reset(&cy8c95xx);
        sleep_ms(1000);

        printf("-------------------------- \r\n");
        printf("  cy8c95xx PORT EXPANDER   \r\n");
        printf("-------------------------- \r\n");
        // Test task
        while (1) {
            expander_task();
        }
    }
    else {
        printf("---- Port expander Error ----\r\n");
    }
}

int main() {
    // Enable print status output
    stdio_init_all();
    
    // Init and test port expander
    expander_init();
    
    return 0;
}
