
#include "Arduino.h"
#include "SPI.h"

void _cb(void) {
  Serial.println("DO1");
}

void _cb1(void) {
  Serial.printf("TEMP %f\n", readBoardTemperature());
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only
  delay(3000);

  Serial.println("Initializing..");
  pinMode(CONTROLLINO_MICRO_DI0, INPUT); // Digital only input 0-11V LOW > 11V HIGH
  pinMode(CONTROLLINO_MICRO_DI1, INPUT); // Digital only input 0-11V LOW > 11V HIGH
  pinMode(CONTROLLINO_MICRO_AI0, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  pinMode(CONTROLLINO_MICRO_AI1, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  setDigitalThreshold(CONTROLLINO_MICRO_AI0, 0x3FFFFF); // Digital therhold for analog input arround 12 V

  pinMode(CONTROLLINO_MICRO_DO0, OUTPUT); // DIgital outputs all with PWM
  pinMode(CONTROLLINO_MICRO_DO1, OUTPUT);
  pinMode(CONTROLLINO_MICRO_DO4, OUTPUT);
  pinMode(CONTROLLINO_MICRO_DO5, OUTPUT);

  enOutFaultInt(CONTROLLINO_MICRO_DO1, &_cb);
  enTempSensorInt(15.00F, 40.00F, &_cb1);
}

void loop(void) {
  Serial.print("CONTROLLINO_MICRO_DI0 state:");
  Serial.print(digitalRead(CONTROLLINO_MICRO_DI0) ? "HIGH" : "LOW");
  Serial.print("      CONTROLLINO_MICRO_DI1 ADC:");
  Serial.print(analogRead(CONTROLLINO_MICRO_DI1));
  Serial.print("      CONTROLLINO_MICRO_AI0 ADC:");
  Serial.print(analogRead(CONTROLLINO_MICRO_AI0));
  Serial.print(" DIGITAL:");
  Serial.print(digitalRead(CONTROLLINO_MICRO_AI0) ? "HIGH" : "LOW");

  digitalWrite(CONTROLLINO_MICRO_DO1, digitalRead(CONTROLLINO_MICRO_DI0));
  digitalWrite(CONTROLLINO_MICRO_DO5, digitalRead(CONTROLLINO_MICRO_AI0));

  uint8_t pwm = map(analogRead(CONTROLLINO_MICRO_AI0), 0, 0x7FFFFF, 0, 0xFF); // Analog 23 bits to 8 bit for PWM 
  Serial.print("      PWM:");
  Serial.print(pwm);
  
  Serial.print("      CONTROLLINO_MICRO_AI1 ADC:");
  Serial.print(analogRead(CONTROLLINO_MICRO_AI1));

  Serial.printf("     Current Temp: %f", readBoardTemperature());


  analogWrite(CONTROLLINO_MICRO_DO0, pwm);
  analogWrite(CONTROLLINO_MICRO_DO4, pwm);

  Serial.println();
  delay(500);
}
