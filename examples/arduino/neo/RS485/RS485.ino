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

#include <SPI.h>
#include <ArduinoRS485.h>

RS485Class NeoRS485(Serial1, 0, 3, 2);

void setup() {
    Serial.begin(115200);
    NeoRS485.begin(115200, 10, 10);

    // enable reception, can be disabled with: RS485.noReceive();
    NeoRS485.receive();
}

void loop() {
    if (Serial.available()) { // If anything comes in Serial (USB),
        NeoRS485.noReceive();
        NeoRS485.beginTransmission();
        NeoRS485.write(Serial.read()); // read it and send it out over RS485
        NeoRS485.endTransmission();
        NeoRS485.receive();
    }

    if (NeoRS485.available()) { // If anything comes in over RS485
        Serial.write(NeoRS485.read()); // read it and send it out over Serial (USB)
    }
}
