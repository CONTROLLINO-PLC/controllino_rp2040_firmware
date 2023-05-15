#include "Arduino.h"

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only
  
  Serial.println("Initializing..");

  // Activate digital outputs for current measurement
  pinMode(NEO_CORE_DO0, OUTPUT); 
  pinMode(NEO_CORE_DO1, OUTPUT);
  pinMode(NEO_CORE_DO4, OUTPUT);
  pinMode(NEO_CORE_DO5, OUTPUT);
  digitalWrite(NEO_CORE_DO0, HIGH);
  digitalWrite(NEO_CORE_DO1, HIGH);
  digitalWrite(NEO_CORE_DO4, HIGH);
  digitalWrite(NEO_CORE_DO5, HIGH);
}

void loop(void) {
  Serial.print("Power: ");
  Serial.print(readVoltageSuply()); // Board power suply
  Serial.print(" mV");
  enableCurrentSenseDO(0); // Enable current measurement on digital output 0 (NEO_CORE_DO0)
  Serial.print("\tDO0 I: ");
  Serial.print(readCurrentSenseDO()); // Read current on digital output 0 (NEO_CORE_DO0)
  Serial.print(" mA");
  enableCurrentSenseDO(1);
  Serial.print("\tDO1 I: ");
  Serial.print(readCurrentSenseDO());
  Serial.print(" mA");
  enableCurrentSenseDO(4);
  Serial.print("\tDO4 I: ");
  Serial.print(readCurrentSenseDO());
  Serial.print(" mA");
  enableCurrentSenseDO(5);
  Serial.print("\tDO5 I: ");
  Serial.print(readCurrentSenseDO());
  Serial.print(" mA");
  Serial.print("\tTemperature Board: ");
  Serial.print(readBoardTemperature(), 2); // Board Temperature
  Serial.print(" °C");
  Serial.print(" RP2040: ");
  Serial.print(analogReadTemp(3.3F), 2); // Main RP2040 internal temperature measurement
  Serial.println(" °C");
  delay(500);
}
