# Controllino RP2 firmware resources

This repository in the form of a PlatformIO project contains the firmware resources for Controllino RP2 boards, to support bare metal programming using Pico SDK and Arduino programing with Controllino RP2 core based on Arduino-Pico core.

## Arduino IDE installation ❗

Add <https://github.com/CONTROLLINO-PLC/controllino_rp2/releases/download/global/package_controllino_rp2_index.json> to the Additional Boards Manager URLs in the Arduino IDE preferences.

## Internal hardware drivers

### Common

- Drivers hardware abstraction layer for [lib/drivers/include/hw_platform.h](lib/drivers/include/hw_platform.h)
- hw_platform implementation for Pico SDK (not used) [lib/hw_rp2](lib/hw_rp2)
- hw_platform implementation for Arduino (used) [lib/hw](lib/hw)

### I2C

- CY8C9520 Port Expander [lib/drivers/include/cy8c9520.h](lib/drivers/include/cy8c9520.h)
- 2521020222501 WE Temperature Sensor [lib/drivers/include/wsen_temp.h](lib/drivers/include/wsen_temp.h)
- ADG728 Analog Switch [lib/drivers/include/adg728.h](lib/drivers/include/adg728.h)
- MCP4461 Digital Potentiometer [lib/drivers/include/mcp4461.h](lib/drivers/include/mcp4461.h)

### SPI

- AD5664 16 bits DAC [lib/drivers/include/ad5664.h](lib/drivers/include/ad5664.h)
- BTS71220 Output Driver [lib/drivers/include/bts71220.h](lib/drivers/include/bts71220.h)
- MCP3564 24 bits ADC [lib/drivers/include/mcp3564.h](lib/drivers/include/mcp3564.h)
- MCP23S17 Port Expander [lib/drivers/include/mcp23s17.h](lib/drivers/include/mcp23s17.h)

## Controllino RP2 resources based on Arduino-Pico core

- ControllinoPin Class and modifications to Arduino digital and analog wiring [lib/wiring](lib/wiring)
- Controllino Micro [lib/micro](lib/micro)

## Arduino libraries to support Controllino RP2 core

- CAN modified version of Arduino CAN library (MCP2515) [lib/CAN](lib/CAN)
- Other standard Arduino libraries are intended to be used without modifications like:
  - ArduinoECCX08 (ATECC608A Crypto Chip)
  - Ethernet (W5500)
  - SD (SD card access)
  - ArduinoRS485 (RS485 coms)
  - ArduinoModbus (Modbus coms)

## Examples

- Usind Pico SDK [examples/pico_sdk](examples/pico_sdk)
- Using Arduino core:
  - Common to all Controllino RP2 boards [examples/arduino/common](examples/arduino/common)
  - Micro [examples/arduino/micro](examples/arduino/micro)

## Unit tests

The unit tests are designed to run on the devices and also in a native enviroment using mocks to simulate the hardware see [platformio.ini](platformio.ini), [unity_config.h](test/unity_config.h) and [unity_config.cpp](test/unity_config.cpp). (For now run test only on Micro device enviroment)

### Arduino core

"diag" refers to internal functinalities like power supply and temperature monitoring and "pin" refers to I/O management functionalities.

- Common [test/arduino/common](test/arduino/common)
- Micro [test/arduino/micro](test/arduino/micro)

### Drivers and Hardware abstraction layer

"hw" refers to hardware functionalities like I2C, SPI, GPIO and "drv" refers to the drivers for the specific functionalities.

#### gpio

- Common hardware abstraction functions [test/gpio/hw/common](test/gpio/hw/common)
- Hardware specifics [test/gpio/hw/specific](test/gpio/hw/specific)

#### i2c

- ADG728 driver [test/i2c/drv/adg728](test/i2c/drv/adg728)
- CY8C9520 driver [test/i2c/drv/cy8c9520](test/i2c/drv/cy8c9520)
- MCP4461 driver [test/i2c/drv/mcp4461](test/i2c/drv/mcp4461)
- WSEN_TEMP driver [test/i2c/drv/wsen_temp](test/i2c/drv/wsen_temp)
- Common hardware abstraction functions [test/i2c/hw/common](test/i2c/hw/common)
- Hardware specifics [test/i2c/hw/specific](test/i2c/hw/specific)

#### spi

- AD5664 driver [test/spi/drv/ad5664](test/spi/drv/ad5664)
- BTS71220 driver [test/spi/drv/bts71220](test/spi/drv/bts71220)
- MCP3564 driver [test/spi/drv/mcp3564](test/spi/drv/mcp3564)
- MCP23S17 driver [test/spi/drv/mcp23s17](test/spi/drv/mcp23s17)
- Common hardware abstraction functions [test/spi/hw/common](test/spi/hw/common)
- Hardware specifics [test/spi/hw/specific](test/spi/hw/specific)

#### timing

- Common hardware abstraction functions [test/timing/hw/common](test/timing/hw/common)

## References to external projects and libraries

- Arduino-Pico core <https://github.com/earlephilhower/arduino-pico>
- Pico SDK <https://github.com/raspberrypi/pico-sdk>
- MikroE Click libraries <https://github.com/MikroElektronika/mikrosdk_click_v2>
- WE Sensor libraries <https://github.com/WurthElektronik/SensorLibrariesArduino>
- Arduino CAN library <https://github.com/sandeepmistry/arduino-CAN>
- Arduino Modbus library <https://github.com/arduino-libraries/ArduinoModbus>
- Arduino RS485 library <https://github.com/arduino-libraries/ArduinoRS485>
- ArduinoOTA library <https://github.com/JAndrassy/ArduinoOTA>
