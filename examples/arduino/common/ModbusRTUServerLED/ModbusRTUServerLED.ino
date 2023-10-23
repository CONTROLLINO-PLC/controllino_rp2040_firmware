/*
  Modbus RTU Server LED

  This sketch creates a Modbus RTU Server with a simulated coil.
  The value of the simulated coil is set on the LED

  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the Modbus RTU server
     - Y connected to A/Y of the Modbus RTU client
     - Z connected to B/Z of the Modbus RTU client
     - Jumper positions
       - FULL set to OFF
       - Z \/\/ Y set to OFF

  created 16 July 2018
  by Sandeep Mistry
*/

// Modified version for this project

#include <SPI.h>

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

RS485Class MicroRS485(RS485_SERIAL_PORT, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);

const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only
  delay(3000);
  Serial.println("Modbus RTU Server LED");

  // start the Modbus RTU server, with (slave) id 1
  Serial2.setTX(PIN_SERIAL2_TX);
  Serial2.setRX(PIN_SERIAL2_RX);
  if (!ModbusRTUServer.begin(MicroRS485, 1, 9600)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  // configure the LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // configure a single coil at address 0x00
  ModbusRTUServer.configureCoils(0x00, 1);
}

void loop() {
  // poll for Modbus RTU requests
  int packetReceived = ModbusRTUServer.poll();

  if(packetReceived) {
    // read the current value of the coil
    int coilValue = ModbusRTUServer.coilRead(0x00);
  
    if (coilValue) {
      // coil value set, turn LED on
      digitalWrite(ledPin, HIGH);
    } else {
      // coil value clear, turn LED off
      digitalWrite(ledPin, LOW);
    }
  }
}
