#include "cy8c9520.h"
#include "bts71220.h"
#include "hw_platform.h"

static cy8c9520_t cy8c9520;
#define _BTS71220_CS CY8C9520_GPIO_12
 

static void cs_init(void)
{
#ifdef CONTROLLINO_NEO
    static uint8_t cs_initialized = 0;
    if (!cs_initialized) {
        cy8c9520_cfg_t cfg;
        cy8c9520_set_default_cfg(&cfg);
        cy8c9520_init(&cy8c9520, &cfg);
    }
    cs_initialized = 1;
#endif
}

 
void bts71220_cs_select(int cs_pin)
{
#ifdef CONTROLLINO_NEO
    cs_init();
    cy8c9520_write_pin(&cy8c9520, _BTS71220_CS, CY8C9520_LOW);
    platform_sleep_us(600);
#endif
}
 
void bts71220_cs_deselect(int cs_pin)
{
#ifdef CONTROLLINO_NEO
    cs_init();
    cy8c9520_write_pin(&cy8c9520, _BTS71220_CS, CY8C9520_HIGH);
#endif
}