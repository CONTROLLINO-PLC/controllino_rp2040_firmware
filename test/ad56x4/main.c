#include "expand6.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

#define AD5624R_ADDR_DAC0			0x00
#define AD5624R_ADDR_DAC1			0x01
#define AD5624R_ADDR_DAC2			0x02
#define AD5624R_ADDR_DAC3			0x03
#define AD5624R_ADDR_ALL_DAC			0x07

#define AD5624R_CMD_WRITE_INPUT_N		0x00
#define AD5624R_CMD_UPDATE_DAC_N		0x01
#define AD5624R_CMD_WRITE_INPUT_N_UPDATE_ALL	0x02
#define AD5624R_CMD_WRITE_INPUT_N_UPDATE_N	0x03
#define AD5624R_CMD_POWERDOWN_DAC		0x04
#define AD5624R_CMD_RESET			0x05
#define AD5624R_CMD_LDAC_SETUP			0x06
#define AD5624R_CMD_INTERNAL_REFER_SETUP	0x07

#define AD5624R_LDAC_PWRDN_NONE			0x00
#define AD5624R_LDAC_PWRDN_1K			0x01
#define AD5624R_LDAC_PWRDN_100K			0x02
#define AD5624R_LDAC_PWRDN_3STATE		0x03

#define EXP_CS_AO 15
static expand6_t expand6;

uint8_t command;
uint8_t address;
uint16_t data;

void cs_select(int pin) {
    if (pin >= 0) {
        expand6_write_pin(&expand6, pin, EXPAND6_LOW);
    }
    sleep_ms(1);
}

void cs_deselect(int pin) {
    sleep_ms(1);
    if (pin >= 0) {
        expand6_write_pin(&expand6, pin, EXPAND6_HIGH);
    }
}

void ad56X4r_spi_write(spi_inst_t* spi, uint8_t command, uint8_t address, uint16_t data) {
    uint8_t src[3];
    src[0] = (uint8_t)((command << 3) | address);
    src[1] = (uint8_t)((data >> 8) & 0xFF);
    src[2] = (uint8_t)(data & 0xFF);
    printf("%02x %04x\r\n", src[0], (((uint16_t)src[1] << 8) | (uint16_t)src[2]));

    cs_select(EXP_CS_AO);
    spi_write_blocking(spi, src, sizeof(src));
    cs_deselect(EXP_CS_AO);
    // sleep_ms(10);
}

void expander_init(void)
{
    expand6_cfg_t cfg;
    expand6_cfg_default_setup(&cfg);
    expand6_init(&expand6, &cfg);
    expand6_reset(&expand6);
}

int main() {
    // Enable UART so we can print status output
    stdio_init_all();

    // SPI configuration
    spi_init(spi_default, 1000000);
    spi_set_format(spi_default, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST); // SPI mode 1
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);

    // Port expander init
    printf("---- Port expander Init ----\r\n");
    expander_init();
    sleep_ms(100);

    // Init AO
    // cs_select(EXP_CS_AO);
    // sleep_ms(100);
    cs_deselect(EXP_CS_AO);
    sleep_ms(100);
    ad56X4r_spi_write(spi_default, AD5624R_CMD_RESET, 0x00, 0x0001); // Reset
    ad56X4r_spi_write(spi_default, AD5624R_CMD_WRITE_INPUT_N, AD5624R_ADDR_DAC0, 0x7028);
    // ad56X4r_spi_write(spi_default, AD5624R_CMD_WRITE_INPUT_N, AD5624R_ADDR_DAC1, 0x2000);
    // ad56X4r_spi_write(spi_default, AD5624R_CMD_WRITE_INPUT_N, AD5624R_ADDR_DAC2, 0x2000);
    // ad56X4r_spi_write(spi_default, AD5624R_CMD_WRITE_INPUT_N, AD5624R_ADDR_DAC3, 0x2000);
    ad56X4r_spi_write(spi_default, AD5624R_CMD_UPDATE_DAC_N, AD5624R_ADDR_DAC0, 0x0000);
    // ad56X4r_spi_write(spi_default, AD5624R_CMD_POWERDOWN_DAC, 0x00, (AD5624R_LDAC_PWRDN_NONE << 4) | AD5624R_ADDR_ALL_DAC); // Power up
    // ad56X4r_spi_write(spi_default, AD5624R_CMD_WRITE_INPUT_N_UPDATE_N, AD5624R_ADDR_DAC0, 0xFFFF); // Write Channel 0
    while (1)
    {
        asm volatile("nop");
    }

    return 0;
}