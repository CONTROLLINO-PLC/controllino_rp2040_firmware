// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ARDUINO_ARCH_ESP32

#ifndef MCP2515_H
#define MCP2515_H

#include <SPI.h>

#include "CANController.h"

#ifndef MCP2515_DEFAULT_CLOCK_FREQUENCY
#define MCP2515_DEFAULT_CLOCK_FREQUENCY 16E6
#endif

#if defined(ARDUINO_ARCH_SAMD) && defined(PIN_SPI_MISO) && defined(PIN_SPI_MOSI) && defined(PIN_SPI_SCK) && (PIN_SPI_MISO == 10) && (PIN_SPI_MOSI == 8) && (PIN_SPI_SCK == 9)
// Arduino MKR board: MKR CAN shield CS is pin 3, INT is pin 7
#define MCP2515_DEFAULT_CS_PIN          3
#define MCP2515_DEFAULT_INT_PIN         7
#else
// Allow for external MCP2515 default CS and INT pin definitions
#ifndef MCP2515_DEFAULT_CS_PIN
#define MCP2515_DEFAULT_CS_PIN          13
#endif
#ifndef MCP2515_DEFAULT_INT_PIN
#define MCP2515_DEFAULT_INT_PIN         15
#endif
#endif
// Allow for external MCP2515 default SPI insterface definition
#ifndef MCP2515_DEFAULT_SPI
#define MCP2515_DEFAULT_SPI             SPI1
#endif

class MCP2515Class : public CANControllerClass {

public:
  MCP2515Class();
  virtual ~MCP2515Class();

  virtual int begin(long baudRate);
  virtual void end();

  virtual int endPacket();

  virtual int parsePacket();

  virtual void onReceive(void(*callback)(int));

  using CANControllerClass::filter;
  virtual int filter(int id, int mask);
  using CANControllerClass::filterExtended;
  virtual int filterExtended(long id, long mask);

  virtual int observe();
  virtual int loopback();
  virtual int sleep();
  virtual int wakeup();

  void setPins(int cs = MCP2515_DEFAULT_CS_PIN, int irq = MCP2515_DEFAULT_INT_PIN);
  void setSPIFrequency(uint32_t frequency);
  void setClockFrequency(long clockFrequency);

  void dumpRegisters(Stream& out);

private:
  void reset();

  void handleInterrupt();

  uint8_t readRegister(uint8_t address);
  void modifyRegister(uint8_t address, uint8_t mask, uint8_t value);
  void writeRegister(uint8_t address, uint8_t value);

  static void onInterrupt();

private:
  SPISettings _spiSettings;
  int _csPin;
  int _intPin;
  long _clockFrequency;
};

extern MCP2515Class CAN;

#endif

#endif
