#include <SPI.h>
#include "neo_core_diag.h"

bts71220_dcr_reg_t dcr_reg;

void setup() {
  Serial1.begin(115200);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.println("Initializing..");
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
  delay(500);
  Serial1.print("Power: ");
  Serial1.print(analogRead(29U));
  enableCurrentSenseDO(0);
  Serial1.print("\tDO0 I: ");
  Serial1.print(readCurrentSenseDO());
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
  Serial1.println(" mA");
}
