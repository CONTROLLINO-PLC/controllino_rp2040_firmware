# Controllino NEO core firmware resources

## Hardware drivers

- AD5664 dac [lib/drivers/include/ad5664.h](lib/drivers/include/ad5664.h)
- BTS71220-4ESA power out [lib/drivers/include/bts71220.h](lib/drivers/include/bts71220.h)
- CY8C9520 i2c i/o expander [lib/drivers/include/cy8c9520.h](lib/drivers/include/cy8c9520.h)
- MCP3564 adc [lib/drivers/include/mcp3564.h](lib/drivers/include/mcp3564.h)
- 2521020222501 WE temp. sensor [lib/drivers/include/wsen_temp.h](lib/drivers/include/wsen_temp.h)

## Arduino-pico port

- Arduino pins API for NEO boards [lib/arduino_pico_neo_pin](lib/arduino_pico_neo_pin)
- NEO core pin definitions [lib/arduino_pico_neo_core_pins](lib/arduino_pico_neo_core_pins)

## Examples

- Usind pico_sdk [examples/pico_sdk](examples/pico_sdk)

## Unit tests

- Unity configuration for PlatformIO [test/unity_config.h](test/unity_config.h)
- Driver tests [test/i2c/drv/](test/i2c/drv/), [test/spi/drv/](test/spi/drv/)
