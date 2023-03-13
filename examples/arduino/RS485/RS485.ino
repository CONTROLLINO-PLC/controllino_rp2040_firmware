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
    if (Serial.available()) {
        NeoRS485.noReceive();
        NeoRS485.beginTransmission();
        NeoRS485.write(Serial.read());
        NeoRS485.endTransmission();
        NeoRS485.receive();
    }

    if (NeoRS485.available()) {
        Serial.write(NeoRS485.read());
    }
}
