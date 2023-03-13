#include <SPI.h>

void setup() {
  Serial1.begin(115200);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.println("Initializing..");
  pinMode(NEO_CORE_DI0, INPUT);
  pinMode(NEO_CORE_AI0, INPUT);
  pinMode(NEO_CORE_DO0, OUTPUT);
  pinMode(NEO_CORE_DO4, OUTPUT);
  pinMode(NEO_CORE_AO0, OUTPUT);
  analogWrite(NEO_CORE_AO0, 0);
  digitalWrite(NEO_CORE_DO0, HIGH);
  digitalWrite(NEO_CORE_DO4, HIGH);

}

void loop(void) {
  Serial1.print("NEO_CORE_AI0 state:");
  Serial1.println(analogRead(NEO_CORE_AI0));
  delay(1000);
}
