#include "cy8c9520.h"
#include "ad5664.h"
#include "hw_platform.h"

static void cs_init(void)
{
#ifdef CONTROLLINO_NEO
    static uint8_t cs_initialized = 0;
    if (!cs_initialized) {
        platform_gpio_init(_AD5664_CS_PIN, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED);
    }
    cs_initialized = 1;
#endif
}


void mcp3564_cs_select(int cs_pin)
{
#ifdef CONTROLLINO_NEO
    cs_init();
    platform_gpio_set(_AD5664_CS_PIN, false);
#endif
}

void mcp3564_cs_deselect(int cs_pin)
{
#ifdef CONTROLLINO_NEO
    cs_init();
    platform_gpio_set(_AD5664_CS_PIN, true);
#endif
}