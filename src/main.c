#include "expand6.h"
#include "pico/binary_info.h"

static expand6_t expand6;

uint8_t pin_num;
uint8_t pin_state;

// ------------------------------------------------------ APPLICATION FUNCTIONS
void expander_task(void)
{
    // Out Test
    expand6_write_port(&expand6, EXPAND6_PORT_1, 0xFF);
    // expand6_write_port(&expand6, EXPAND6_PORT_2, 0xFF);

    printf("All pins set to HIGH logic level!\r\n");
    printf("---------------------------------\r\n");
    sleep_ms(2000);

    for (pin_num = 8; pin_num < 15; pin_num++)
    {
        expand6_write_pin(&expand6, pin_num, EXPAND6_LOW);
        printf("Pin %u is set to LOW logic level!\r\n", pin_num);
        sleep_ms(300);
    }

    // // In test
    // pin_num = 0;
    // pin_state = expand6_read_pin(&expand6, pin_num, 0);
    // printf("Pin %u level is %u!\r\n", pin_num, pin_state);

    printf("---------------------------------\r\n");
    sleep_ms(1000);
}

void expander_init(void)
{
    expand6_cfg_t cfg;
    printf("---- Port expander Init ----\r\n");

    //  Click initialization.
    expand6_cfg_default_setup(&cfg);
    if (expand6_init(&expand6, &cfg) == EXPAND6_OK) {
        expand6_reset(&expand6);
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
