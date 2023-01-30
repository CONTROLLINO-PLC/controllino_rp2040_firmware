#include "cy8c95xx.h"
#include "mcp356x.h"
#include "pico/binary_info.h"

cy8c95xx_t cy8c9520;

/* Init cy8c95xx port expander */
void exp_init(void)
{
    cy8c95xx_cfg_t cfg;
    cy8c95xx_set_default_cfg(&cfg);
    cy8c95xx_init(&cy8c9520, &cfg);
    cy8c95xx_reset(&cy8c9520);
}

mcp356x_t mcp3564;
#define CY8C9520_GPIO_14    14
#define MCP3564_CS          CY8C9520_GPIO_14
#define NEO_AO_MAX_10V      10000 

void mcp356x_cs_select(mcp356x_t* dac)
{
    cy8c95xx_write_pin(&cy8c9520, MCP3564_CS, CY8C95XX_LOW);
}

void mcp356x_cs_deselect(mcp356x_t* dac)
{
    cy8c95xx_write_pin(&cy8c9520, MCP3564_CS, CY8C95XX_HIGH);
}

void mcp356x_check_registers(void)
{
    uint8_t rxdata[12];
    mcp356x_iread(&mcp3564, MCP356X_REG_CFG_0, rxdata, sizeof(rxdata));
    printf("\nMCP3564 config registers:\n");
    printf("CONFIG0 %X\n", rxdata[0]);
    printf("CONFIG1 %X\n", rxdata[1]);
    printf("CONFIG2 %X\n", rxdata[2]);
    printf("CONFIG3 %X\n", rxdata[3]);
    printf("IRQ %X\n", rxdata[4]);
    printf("MUX %X\n", rxdata[5]);
    printf("SCAN %X\n", (((uint32_t)rxdata[6] << 16) | ((uint32_t)rxdata[7] << 8)) | (uint32_t)rxdata[8]);
    printf("TIMER %X\n", (((uint32_t)rxdata[9] << 16) | ((uint32_t)rxdata[10] << 8)) | (uint32_t)rxdata[11]);
}

void mcp356x_print_channel_readings(void)
{
    uint8_t mux_reg;
    uint32_t vol_val;
    for (uint8_t i = 0x00; i < 0x08; i++)
    {
        mux_reg = (i << 4)  | MCP356X_MUX_VIN_NEG_VREF_EXT_MINUS;
        mcp356x_iwrite(&mcp3564, MCP356X_REG_MUX, &mux_reg, 1);
        mcp356x_read_voltage(&mcp3564, 0, 10938, &vol_val);
        printf("Channel%d mV %d\n", i, vol_val);
    }
}


void adc_init(void)
{
    mcp356x_cfg_t cfg;
    mcp356x_set_default_cfg(&cfg);
    mcp356x_init(&mcp3564, &cfg);
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
    // Init CY8C9520
    exp_init();
    // Init MCP356X
    adc_init();
    // Check that registers where initialized
    mcp356x_check_registers();
    // Periodically print channel readings
    while (1)
    {
        printf("MCP3564 channel readings:\n");
        mcp356x_print_channel_readings();
        platform_sleep_ms(500);
    }
    return 0;
}