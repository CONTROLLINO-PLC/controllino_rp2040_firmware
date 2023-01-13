#include "cy8C95xx.h"
#include "pico/binary_info.h"

static cy8C95xx_t cy8C95xx;

uint8_t pin_num;
uint8_t pin_state;

// ------------------------------------------------------ APPLICATION FUNCTIONS
void expander_task(void)
{
    // Out Test
    cy8C95xx_write_port(&cy8C95xx, CY8C95XX_PORT_1, 0xFF);
    // cy8C95xx_write_port(&cy8C95xx, CY8C95XX_PORT_2, 0xFF);

    printf("All pins set to HIGH logic level!\r\n");
    printf("---------------------------------\r\n");
    sleep_ms(2000);

    for (pin_num = 8; pin_num < 15; pin_num++)
    {
        cy8C95xx_write_pin(&cy8C95xx, pin_num, CY8C95XX_LOW);
        printf("Pin %u is set to LOW logic level!\r\n", pin_num);
        sleep_ms(300);
    }

    // // In test
    // pin_num = 0;
    // pin_state = cy8C95xx_read_pin(&cy8C95xx, pin_num, 0);
    // printf("Pin %u level is %u!\r\n", pin_num, pin_state);

    printf("---------------------------------\r\n");
    sleep_ms(1000);
}

void expander_init(void)
{
    cy8C95xx_cfg_t cfg;
    printf("---- Port expander Init ----\r\n");

    //  Click initialization.
    cy8C95xx_cfg_default_setup(&cfg);
    if (cy8C95xx_init(&cy8C95xx, &cfg) == CY8C95XX_OK) {
        cy8C95xx_reset(&cy8C95xx);
        sleep_ms(1000);

        printf("------------------- \r\n");
        printf("   EXPAND 6 click   \r\n");
        printf("------------------- \r\n");

        // Main task
        while (1) {
            expander_task();
        }
    }
    else {
        printf("---- Port expander Error ----\r\n");
    }
}

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / bus_scan example requires a board with I2C pins
        puts("Default I2C pins were not defined");
#else
    expander_init();
    return 0;
#endif
}
