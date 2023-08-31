#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

void setup() {
  // Open serial communications and wait for port to open:
  Serial1.begin(115200);
  while (!Serial1); // Wait for serial port to connect. Needed for native USB port only
  
  Serial1.println("Initializing..");

  // Activate digital outputs for current measurement
  pinMode(CONTROLLINO_NEO_DO0, OUTPUT);
  pinMode(CONTROLLINO_NEO_DO1, OUTPUT);
  pinMode(CONTROLLINO_NEO_DO4, OUTPUT);
  pinMode(CONTROLLINO_NEO_DO5, OUTPUT);
  digitalWrite(CONTROLLINO_NEO_DO0, HIGH);
  digitalWrite(CONTROLLINO_NEO_DO1, HIGH);
  digitalWrite(CONTROLLINO_NEO_DO4, HIGH);
  digitalWrite(CONTROLLINO_NEO_DO5, HIGH);
}

void loop(void) {
  Serial1.print("Power: ");
  Serial1.print(readVoltageSuply()); // Board power suply
  Serial1.print(" mV");
  enableCurrentSenseDO(0); // Enable current measurement on digital output 0 (NEO_CORE_DO0)
  Serial1.print("\tDO0 I: ");
  Serial1.print(readCurrentSenseDO()); // Read current on digital output 0 (NEO_CORE_DO0)
  Serial1.print(" mA");
  enableCurrentSenseDO(1);
  Serial1.print("\tDO1 I: ");
  Serial1.print(readCurrentSenseDO());
  Serial1.print(" mA");
  enableCurrentSenseDO(4);
  Serial1.print("\tDO4 I: ");
  Serial1.print(readCurrentSenseDO());
  Serial1.print(" mA");
  enableCurrentSenseDO(5);
  Serial1.print("\tDO5 I: ");
  Serial1.print(readCurrentSenseDO());
  Serial1.print(" mA");
  Serial1.print("\tTemperature Board: ");
  Serial1.print(readBoardTemperature(), 2); // Board Temperature
  Serial1.print(" °C");
  Serial1.print(" RP2040: ");
  Serial1.print(analogReadTemp(3.3F), 2); // Main RP2040 internal temperature measurement
  Serial1.println(" °C");
  delay(500);
}
