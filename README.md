# Controllino RP2040 firmware resources 

This repository in the form of a PlatformIO project contains the firmware resources for Controllino RP2040 boards, to support bare metal programming using RP2040 SDK and Arduino programing with Controllino RP2040 core based on Arduino-Pico core.

## Arduino IDE installation ❗

Add [https://github.com/CONTROLLINO-PLC/controllino_rp2040_firmware/releases/download/global/package_controllino_rp2040_index.json](https://github.com/CONTROLLINO-PLC/controllino_rp2040_firmware/releases/download/global/package_controllino_rp2040_index.json) to the Additional Boards Manager URLs in the Arduino IDE preferences.

## Internal hardware drivers

### Common

- Hardware abstraction layer for all drivers [lib/controllino_drivers/include/hw_platform.h](lib/controllino_drivers/include/hw_platform.h)
- hw_platform implementation for rp2040 SDK (used) [lib/controllino_hw_rp2040](lib/controllino_hw_rp2040)
- hw_platform implementation for Arduino (not functional not used) [lib/controllino_hw_arduino](lib/controllino_hw_arduino)

### I2C

- CY8C9520 Port Expander (I2C) [lib/controllino_drivers/include/cy8c9520.h](lib/controllino_drivers/include/cy8c9520.h)
- 2521020222501 WE Temperature Sensor (I2C) [lib/controllino_drivers/include/wsen_temp.h](lib/controllino_drivers/include/wsen_temp.h)
- ADG728 Analog Switch (I2C) [lib/controllino_drivers/include/adg728.h](lib/controllino_drivers/include/adg728.h)
- MCP4461 Digital Potentiometer (I2C) [lib/controllino_drivers/include/mcp4461.h](lib/controllino_drivers/include/mcp4461.h)

### SPI

- AD5664 16 bits DAC (SPI) [lib/controllino_drivers/include/ad5664.h](lib/controllino_drivers/include/ad5664.h)
- BTS71220 Output Driver (SPI) [lib/controllino_drivers/include/bts71220.h](lib/controllino_drivers/include/bts71220.h)
- MCP3564 24 bits ADC (SPI) [lib/controllino_drivers/include/mcp3564.h](lib/controllino_drivers/include/mcp3564.h)

## Controllino RP2040 core resources based on Arduino-Pico core

- ControllinoRp2040Pin Class and modifications to Arduino digital and analog wiring [lib/controllino_wiring](lib/controllino_wiring)
- Controllino Micro variant [lib/controllino_micro](lib/controllino_micro)
- Controllino Neo variant(not yet ready) [lib/controllino_neo](lib/controllino_neo)

## Modified Arduino libraries to support Controllino RP2040 core

- Wire modified version of Wire library from Arduino-Pico core [lib/arduino_wire](lib/ArduinoWire)
- CAN modified version of Arduino CAN library (MCP2515) [lib/arduino_can](lib/arduino_can)
- ArduinoModbus modified version of Arduino Modbus library [lib/arduino_modbus](lib/arduino_modbus)
- Other standard Arduino libraries are intended to be used without modifications like:
  - ArduinoECCX08 (ATECC608A Crypto Chip)
  - Ethernet (W5500)
  - ArduinoRS485 (RS485 coms)
  - SD (SD card access)

## Examples

- Usind RP2040 sdk [examples/pico_sdk](examples/pico_sdk)
- Using Arduino core:
  - Common to all variants [examples/arduino/common](examples/arduino/common)
  - Micro variant [examples/arduino/micro](examples/arduino/micro)
  - Neo variant [examples/arduino/neo](examples/arduino/neo)
  - Note: Some modifications of these examples are needed to run on PlatformIO. Within the Arduino Core released with this repo there are examples for every library that are ready to run in Arduino IDE.

## Unit tests

The unit tests are designed to run on the devices and also in a native enviroment using mocks to simulate the hardware see [platformio.ini](platformio.ini), [unity_config.h](test/unity_config.h) and [unity_config.cpp](test/unity_config.cpp). (For now run test only on MICRO device enviroment)

### Arduino core

"diag" refers to internal functinalities like power supply and temperature monitoring and "pin" refers to I/O management functionalities.

- Common [test/arduino/common](test/arduino/common)
- Micro variant [test/arduino/micro](test/arduino/micro)
- Neo variant [test/arduino/neo](test/arduino/neo)

### Drivers and Hardware abstraction layer

"hw" refers to hardware functionalities like I2C, SPI, GPIO and "drv" refers to the drivers for the specific functionalities.

#### gpio

- Common hardware abstraction functions [test/gpio/hw/common](test/gpio/hw/common)
- RP2040 especifics [test/gpio/hw/rp2040](test/gpio/hw/rp2040)

#### i2c

- ADG728 driver [test/i2c/drv/adg728](test/i2c/drv/adg728)
- CY8C9520 driver [test/i2c/drv/cy8c9520](test/i2c/drv/cy8c9520)
- MCP4461 driver [test/i2c/drv/mcp4461](test/i2c/drv/mcp4461)
- WSEN_TEMP driver [test/i2c/drv/wsen_temp](test/i2c/drv/wsen_temp)
- Common hardware abstraction functions [test/i2c/hw/common](test/i2c/hw/common)
- RP2040 especifics [test/i2c/hw/rp2040](test/i2c/hw/rp2040)

#### spi

- AD5664 driver [test/spi/drv/ad5664](test/spi/drv/ad5664)
- BTS71220 driver [test/spi/drv/bts71220](test/spi/drv/bts71220)
- MCP3564 driver [test/spi/drv/mcp3564](test/spi/drv/mcp3564)
- Common hardware abstraction functions [test/spi/hw/common](test/spi/hw/common)
- RP2040 especifics [test/spi/hw/rp2040](test/spi/hw/rp2040)

#### time

- Common hardware abstraction functions [test/time/hw/common](test/time/hw/common)

## References to external projects and libraries

- Arduino-Pico core [https://github.com/earlephilhower/arduino-pico](https://github.com/earlephilhower/arduino-pico)
- Pico SDK [https://github.com/raspberrypi/pico-sdk](https://github.com/raspberrypi/pico-sdk)
- MikroE Click libraries [https://github.com/MikroElektronika/mikrosdk_click_v2](https://github.com/MikroElektronika/mikrosdk_click_v2)
- WE Sensor libraries [https://github.com/WurthElektronik/SensorLibrariesArduino](https://github.com/WurthElektronik/SensorLibrariesArduino)
- Arduino CAN library [https://github.com/sandeepmistry/arduino-CAN](https://github.com/sandeepmistry/arduino-CAN)
- Arduino Modbus library [https://github.com/arduino-libraries/ArduinoModbus](https://github.com/arduino-libraries/ArduinoModbus)
