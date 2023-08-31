#include <SPI.h>
#include "ArduinoRS485.h"

RS485Class MicroRS485(RS485_SERIAL_PORT, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);

void setup() {
    Serial2.setTX(PIN_SERIAL2_TX);
    Serial2.setRX(PIN_SERIAL2_RX);
    Serial.begin(115200);

    while (!Serial); // Wait for serial port to connect. Needed for native USB port only
    delay(3000);
    
    Serial.println("RS485 tesing");
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
