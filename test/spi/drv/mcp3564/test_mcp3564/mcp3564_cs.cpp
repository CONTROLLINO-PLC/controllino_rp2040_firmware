#include "cy8c9520.h"
#include "mcp3564.h"
#include "hw_platform.h"
 
static void cs_init(void)
{
#if defined(CONTROLLINO_NEO) || defined(CONTROLLINO_MICRO)
    static uint8_t cs_initialized = 0;
    if (!cs_initialized) {
        platform_gpio_init(_MCP3564_CS_PIN, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED);
    }
    cs_initialized = 1;
#endif
}
 
void mcp3564_cs_select(int cs_pin)
{
#if defined(CONTROLLINO_NEO) || defined(CONTROLLINO_MICRO)
    cs_init();
    platform_gpio_set(_MCP3564_CS_PIN, false);
#endif
}
 
void mcp3564_cs_deselect(int cs_pin)
{
#if defined(CONTROLLINO_NEO) || defined(CONTROLLINO_MICRO)
    cs_init();
    platform_gpio_set(_MCP3564_CS_PIN, true);
#endif
}