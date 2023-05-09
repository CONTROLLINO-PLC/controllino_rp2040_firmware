#include <SPI.h>
#include <Wire.h>

void setup() {
  Serial1.begin(115200);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.println("Initializing..");
  pinMode(NEO_CORE_DI0, INPUT);
  pinMode(NEO_CORE_AI0, INPUT);
  setDigitalThreshold(NEO_CORE_AI0, 0x3FFFFF);

  pinMode(NEO_CORE_DO0, OUTPUT);
  pinMode(NEO_CORE_DO1, OUTPUT);
  pinMode(NEO_CORE_DO4, OUTPUT);
  pinMode(NEO_CORE_DO5, OUTPUT);
  
  pinMode(NEO_CORE_AO0, OUTPUT);
  analogWrite(NEO_CORE_AO0, 0x7FFF); /* 5V */
}

void loop(void) {
  Serial1.print("NEO_CORE_DI0 state:");
  Serial1.print(digitalRead(NEO_CORE_DI0) ? "HIGH" : "LOW");
  Serial1.print("      NEO_CORE_AI0 ADC:");
  Serial1.print(analogRead(NEO_CORE_AI0));
  Serial1.print(" DIGITAL:");
  Serial1.print(digitalRead(NEO_CORE_AI0) ? "HIGH" : "LOW");

  digitalWrite(NEO_CORE_DO1, digitalRead(NEO_CORE_DI0));
  digitalWrite(NEO_CORE_DO5, digitalRead(NEO_CORE_AI0));
  
  uint8_t pwm = map(analogRead(NEO_CORE_AI0), 0, 0x7FFFFF, 0, 0xFF);
  Serial1.print("      PWM:");
  Serial1.println(pwm);
  analogWrite(NEO_CORE_DO0, pwm);
  analogWrite(NEO_CORE_DO4, pwm);

  delay(500);
}
