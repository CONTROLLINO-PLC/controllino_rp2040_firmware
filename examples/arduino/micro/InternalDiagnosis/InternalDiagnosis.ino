#include "Arduino.h"
#include "SPI.h"

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only
  delay(2000);
  Serial.println("Initializing..");
}

void loop(void) {
  Serial.print("Power: ");
  Serial.print(readVoltageSuply()); // Board power suply
  Serial.print(" mV");
  Serial.print("\tTemperature Board: ");
  Serial.print(readBoardTemperature(), 2); // Board Temperature
  Serial.print(" °C");
  Serial.print(" RP2040: ");
  Serial.print(analogReadTemp(3.3F), 2); // Main RP2040 internal temperature measurement
  Serial.println(" °C");
  delay(500);
}
