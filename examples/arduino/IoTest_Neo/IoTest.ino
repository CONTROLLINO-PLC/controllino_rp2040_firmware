
#include "Arduino.h"
#include "SPI.h"

void setup() {
  // Open serial communications and wait for port to open:
  Serial1.begin(115200);
  while (!Serial1); // Wait for serial port to connect. Needed for native USB port only

  Serial1.println("Initializing..");
  pinMode(NEO_CORE_DI0, INPUT); // Digital only input 0-10V LOW > 10V HIGH 
  pinMode(NEO_CORE_AI0, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  pinMode(NEO_CORE_AI1, INPUT);
  setDigitalThreshold(NEO_CORE_AI0, 0x3FFFFF); // Digital therhold for analog input arround 12 V

  pinMode(NEO_CORE_DO0, OUTPUT); // DIgital outputs all with PWM
  pinMode(NEO_CORE_DO1, OUTPUT);
  pinMode(NEO_CORE_DO4, OUTPUT);
  pinMode(NEO_CORE_DO5, OUTPUT);
  
  pinMode(NEO_CORE_AO0, OUTPUT); // Analog output
  analogWrite(NEO_CORE_AO0, 0x7FFF); // (0-10V)16 bit resolution, 0x7FFF means 5V
}

void loop(void) {
  Serial1.print("NEO_CORE_DI0 state:");
  Serial1.print(digitalRead(NEO_CORE_DI0) ? "HIGH" : "LOW");
  Serial1.print("      NEO_CORE_AI0 ADC:");
  Serial1.print(analogRead(NEO_CORE_AI0));
  Serial1.print("      NEO_CORE_AI0 ADC:");
  Serial1.print(analogRead(NEO_CORE_AI0));
  Serial1.print(" DIGITAL:");
  Serial1.print(digitalRead(NEO_CORE_AI0) ? "HIGH" : "LOW");

  digitalWrite(NEO_CORE_DO1, digitalRead(NEO_CORE_DI0));
  digitalWrite(NEO_CORE_DO5, digitalRead(NEO_CORE_AI0));
  
  uint8_t pwm = map(analogRead(NEO_CORE_AI0), 0, 0x7FFFFF, 0, 0xFF); // Analog 23 bits to 8 bit for PWM 
  Serial1.print("      PWM:");
  Serial1.print(pwm);
  analogWrite(NEO_CORE_DO0, pwm);
  analogWrite(NEO_CORE_DO4, pwm);

  Serial1.print("      NEO_CORE_AI1 ADC:");
  Serial1.print(analogRead(NEO_CORE_AI1));
  Serial1.println();
  delay(500);
}
