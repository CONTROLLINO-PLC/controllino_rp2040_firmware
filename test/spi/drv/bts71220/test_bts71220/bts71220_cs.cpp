#include "cy8c95xx.h"
#include "bts71220.h"
#include "hw_platform.h"

static cy8c95xx_t cy8c95xx;
#define _BTS71220_CS CY8C95XX_GPIO_12
 

static void cs_init(void)
{
#ifdef NEO_ENV
    static uint8_t cs_initialized = 0;
    if (!cs_initialized) {
        cy8c95xx_cfg_t cfg;
        cy8c95xx_set_default_cfg(&cfg);
        cy8c95xx_init(&cy8c95xx, &cfg);
    }
    cs_initialized = 1;
#endif
}

 
void bts71220_cs_select(int cs_pin)
{
#ifdef NEO_ENV
    cs_init();
    cy8c95xx_write_pin(&cy8c95xx, _BTS71220_CS, CY8C95XX_LOW);
    platform_sleep_us(600);
#endif
}
 
void bts71220_cs_deselect(int cs_pin)
{
#ifdef NEO_ENV
    cs_init();
    cy8c95xx_write_pin(&cy8c95xx, _BTS71220_CS, CY8C95XX_HIGH);
#endif
}