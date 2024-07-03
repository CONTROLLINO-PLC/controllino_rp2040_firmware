#include <unity.h>
#include "hw_platform.h"
#include "mcp23s17.h"
 
static mcp23s17_t dev;
static mcp23s17_err_code_t ret;
 
void setUp(void)
{
    mcp23s17_cfg_t cfg;
    mcp23s17_set_default_cfg(&cfg);
    cfg.cs_pin = MCP23S17_CS;
    ret = mcp23s17_init(&dev, &cfg);
}
 
void tearDown(void)
{}
 
void test_mcp23s17_set_default_cfg()
{
    mcp23s17_cfg_t def_cfg;
    mcp23s17_set_default_cfg(&def_cfg);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MOSI, def_cfg.mosi_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MISO, def_cfg.miso_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SCK, def_cfg.sck_pin);
    TEST_ASSERT_EQUAL(MCP23S17_CS, def_cfg.cs_pin);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_SPEED, def_cfg.spi_speed);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MODE_1, def_cfg.spi_mode);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_MSBFIRST, def_cfg.spi_bit_order);
    TEST_ASSERT_EQUAL(PLATFORM_SPI_HW, def_cfg.spi);
    TEST_ASSERT_EQUAL(MCP23S17_RST, def_cfg.rst_pin);
    TEST_ASSERT_EQUAL(MCP23S17_INT, def_cfg.int_pin);
    TEST_ASSERT_EQUAL(MCP23S17_ADDRESS_0, def_cfg.addr);
}
 
void test_mcp23s17_init_ok()
{
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
}

void test_mcp23s17_generic_transfer_ok()
{
    uint8_t tx_data = 0x00;
    uint8_t rx_data = 0x00;
    // default value of IODIRA register is 0xFF
    ret = mcp23s17_generic_transfer(&dev, MCP23S17_IODIRA_BANK0, MCP23S17_CMD_READ, tx_data, &rx_data);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0xFF, rx_data);
    // default value of IPOLA register is 0x00
    ret = mcp23s17_generic_transfer(&dev, MCP23S17_IPOLA_BANK0, MCP23S17_CMD_READ, tx_data, &rx_data);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0x00, rx_data);
    // write MCP23S17_IOCON_BYTE_MODE | MCP23S17_IOCON_HAEN to IOCON register
    tx_data = MCP23S17_IOCON_BYTE_MODE | MCP23S17_IOCON_HAEN;
    ret = mcp23s17_generic_transfer(&dev, MCP23S17_IOCON_BANK0, MCP23S17_CMD_WRITE, tx_data, &rx_data);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    // read IOCON register
    ret = mcp23s17_generic_transfer(&dev, MCP23S17_IOCON_BANK0, MCP23S17_CMD_READ, tx_data, &rx_data);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(MCP23S17_IOCON_BYTE_MODE | MCP23S17_IOCON_HAEN, rx_data);
}

void test_mcp23s17_read_port_a_ok()
{
    uint8_t data = 0x00;
    ret = mcp23s17_read_port_a(&dev, &data);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0xFF, data);
}

void test_mcp23s17_read_port_b_ok()
{
    uint8_t data = 0x00;
    ret = mcp23s17_read_port_b(&dev, &data);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0xFF, data);
}

void test_mcp23s17_read_ports_ok()
{
    uint16_t data = 0x0000;
    ret = mcp23s17_read_ports(&dev, &data);
    TEST_ASSERT_EQUAL(PLATFORM_OK, ret);
    TEST_ASSERT_EQUAL(0xFFFF, data);
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mcp23s17_set_default_cfg);
    RUN_TEST(test_mcp23s17_init_ok);
    RUN_TEST(test_mcp23s17_generic_transfer_ok);
    RUN_TEST(test_mcp23s17_read_port_a_ok);
    RUN_TEST(test_mcp23s17_read_port_b_ok);
    RUN_TEST(test_mcp23s17_read_ports_ok);
    return UNITY_END();
}