# Controllino NEO core firmware resources

## Hardware drivers [lib/drivers/include/](lib/drivers/include/)

- AD56X4 dac
- BTS71220-4ESA power out
- CY8C95XX i2c i/o expander
- MCP356X adc
- 2521020222501 WE temp. sensor

## Arduino-pico port

- Arduino pins API for NEO boards [lib/arduino_pico_neo_pin](lib/arduino_pico_neo_pin)
- NEO core pin definitions [lib/arduino_pico_neo_core_pins](lib/arduino_pico_neo_core_pins)

## Examples

- Usind pico_sdk [examples/pico_sdk](examples/pico_sdk)

## Unit tests

- Unity configuration for PlatformIO [test/unity_config.h](test/unity_config.h)
- Driver tests [test/i2c/drv/](test/i2c/drv/), [test/spi/drv/](test/spi/drv/)
