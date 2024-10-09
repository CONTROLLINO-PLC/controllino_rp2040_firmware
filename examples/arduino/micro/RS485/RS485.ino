/*
  RS-485 Passthrough

  This sketch relays data sent and received between the Serial port and the RS-485 interface

  Circuit:
   - MKR board
   - MKR 485 Shield
     - ISO GND connected to GND of the RS-485 device
     - Y connected to A of the RS-485 device
     - Z connected to B of the RS-485 device
     - A connected to Y of the RS-485 device
     - B connected to Z of the RS-485 device
     - Jumper positions
       - FULL set to ON
       - Z \/\/ Y set to ON, if the RS-485 device doesn't provide termination
       - B \/\/ A set to ON, if the RS-485 device doesn't provide termination

  created 4 July 2018
  by Sandeep Mistry
*/

// Modified version for this project

#include "ArduinoRS485.h"

RS485Class MicroRS485(RS485_SERIAL_PORT, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial port to connect. Needed for native USB port only
    delay(3000);
    Serial.println("RS485 tesing");

    // Initialize RS485
    Serial2.setTX(PIN_SERIAL2_TX);
    Serial2.setRX(PIN_SERIAL2_RX);
    MicroRS485.begin(115200);
    MicroRS485.receive();
}

void loop() {
    if (Serial.available()) { // If anything comes in Serial (USB), 
        MicroRS485.noReceive(); 
        MicroRS485.beginTransmission();
        MicroRS485.write(Serial.read()); // read it and send it out over RS485
        MicroRS485.endTransmission();
        MicroRS485.receive();
    }

    if (MicroRS485.available()) { // If anything comes in over RS485
        Serial.write(MicroRS485.read()); // read it and send it out over Serial (USB)
    }
}
