#include <stdio.h>
#include <pico/stdlib.h>
#include "cy8c9520.h"
#include "mcp3564.h"

cy8c9520_t cy8c9520;

mcp3564_t mcp3564;
#define MCP3564_CS          CY8C9520_GPIO_14
#define NEO_AO_MAX_10V      10000 

void exp_init(void)
{
    cy8c9520_cfg_t cfg;
    cy8c9520_set_default_cfg(&cfg);
    cy8c9520_init(&cy8c9520, &cfg);
    cy8c9520_pin_mode(&cy8c9520, MCP3564_CS, CY8C9520_GPIO_OUT, CY8C9520_REG_PULL_UP);
}

void mcp3564_cs_select(int cs_pin)
{
    cy8c9520_write_pin(&cy8c9520, MCP3564_CS, CY8C9520_LOW);
}

void mcp3564_cs_deselect(int cs_pin)
{
    cy8c9520_write_pin(&cy8c9520, MCP3564_CS, CY8C9520_HIGH);
}

void mcp3564_check_registers(void)
{
    uint8_t rxdata[12];
    mcp3564_iread(&mcp3564, MCP3564_REG_CFG_0, rxdata, sizeof(rxdata));
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

void mcp3564_print_channel_readings(void)
{
    uint8_t mux_reg;
    uint32_t vol_val;
    for (uint8_t i = 0x00; i < 0x08; i++)
    {
        mux_reg = (i << 4) | MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS;
        mcp3564_iwrite(&mcp3564, MCP3564_REG_MUX, &mux_reg, 1);
        mcp3564_read_voltage(&mcp3564, 0, 10938, &vol_val);
        printf("Channel%d mV %d\n", i, vol_val);
    }
}


void adc_init(void)
{
    mcp3564_cfg_t cfg;
    mcp3564_set_default_cfg(&cfg);
    mcp3564_init(&mcp3564, &cfg);
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();
    // Init CY8C9520
    exp_init();
    // Init MCP3564
    adc_init();
    // Check that registers where initialized
    mcp3564_check_registers();
    // Periodically print channel readings
    while (1)
    {
        printf("MCP3564 channel readings:\n");
        mcp3564_print_channel_readings();
        sleep_ms(500);
    }
    return 0;
}