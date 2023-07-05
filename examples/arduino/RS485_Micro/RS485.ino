#include <SPI.h>
#include "ArduinoRS485.h"

RS485Class MicroRS485(RS485_SERIAL_PORT, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);

void setup() {
    Serial.begin(115200);

    Serial1.setTX(PIN_SERIAL1_TX);
    Serial1.setRX(PIN_SERIAL1_RX);

    while (!Serial); // Wait for serial port to connect. Needed for native USB port only
    delay(3000);
    Serial.println("RS485 tesing");

    MicroRS485.begin(115200);
    // enable reception, can be disabled with: MicroRS485.noReceive();
    MicroRS485.receive();
}

void loop() {
    if (Serial.available()) {
        MicroRS485.noReceive();
        MicroRS485.beginTransmission();
        MicroRS485.write(Serial.read());
        MicroRS485.endTransmission();
        MicroRS485.receive();
    }

    if (MicroRS485.available()) {
        Serial.write(MicroRS485.read());
    }
}
