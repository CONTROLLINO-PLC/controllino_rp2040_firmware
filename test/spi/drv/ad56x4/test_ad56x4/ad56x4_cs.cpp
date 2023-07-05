#include "cy8c95xx.h"
#include "ad56x4.h"
#include "hw_platform.h"

#define _AD56X4_CS (2u)

static void cs_init(void)
{
#ifdef NEO_ENV
    static uint8_t cs_initialized = 0;
    if (!cs_initialized) {
        platform_gpio_init(_AD56X4_CS, PLATFORM_GPIO_OUT, PLATFORM_GPIO_PULL_DISABLED);
    }
    cs_initialized = 1;
#endif
}


void mcp356x_cs_select(int cs_pin)
{
#ifdef NEO_ENV
    cs_init();
    platform_gpio_set(_AD56X4_CS, false);
#endif
}

void mcp356x_cs_deselect(int cs_pin)
{
#ifdef NEO_ENV
    cs_init();
    platform_gpio_set(_AD56X4_CS, true);
#endif
}