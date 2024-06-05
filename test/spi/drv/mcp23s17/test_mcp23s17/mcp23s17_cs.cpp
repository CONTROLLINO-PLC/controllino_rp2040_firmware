#include "mcp23s17.h"
#include "hw_platform.h"
 

static void cs_init(void)
{
    static uint8_t cs_initialized = 0;
    if (!cs_initialized) {
        platform_gpio_init(MCP23S17_CS, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED);
    }
    cs_initialized = 1;
}

 
void mcp23s17_cs_select(int cs_pin)
{
    cs_init();
    platform_gpio_set(cs_pin, 0);
}
 
void mcp23s17_cs_deselect(int cs_pin)
{
    cs_init();
    platform_gpio_set(cs_pin, 1);
}