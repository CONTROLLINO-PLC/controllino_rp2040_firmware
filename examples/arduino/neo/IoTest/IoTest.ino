
/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * \file IoTest.ino
 *
 * \brief Example of CONTROLLINO NEO I/O usage
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */

#include "Arduino.h"
#include "SPI.h"

void setup() {
  // Open serial communications and wait for port to open:
  Serial1.begin(115200);
  while (!Serial1); // Wait for serial port to connect. Needed for native USB port only

  Serial1.println("Initializing..");
  pinMode(CONTROLLINO_NEO_DI0, INPUT); // Digital only input 0-10V LOW > 10V HIGH 
  pinMode(CONTROLLINO_NEO_AI0, INPUT); // Analog input 23 bit resolution at default gain 0-24V
  pinMode(CONTROLLINO_NEO_AI1, INPUT);
  setDigitalThreshold(CONTROLLINO_NEO_AI0, 0x3FFFFF); // Digital therhold for analog input arround 12 V

  pinMode(CONTROLLINO_NEO_DO0, OUTPUT); // DIgital outputs all with PWM
  pinMode(CONTROLLINO_NEO_DO1, OUTPUT);
  pinMode(CONTROLLINO_NEO_DO2, OUTPUT);
  pinMode(CONTROLLINO_NEO_DO4, OUTPUT);
  pinMode(CONTROLLINO_NEO_DO5, OUTPUT);

  digitalWrite(CONTROLLINO_NEO_DO2, HIGH);

  pinMode(CONTROLLINO_NEO_AO0, OUTPUT); // Analog output
  analogWrite(CONTROLLINO_NEO_AO0, 0x7FFF); // (0-10V)16 bit resolution, 0x7FFF means 5V
}

void loop(void) {
  Serial1.print("CONTROLLINO_NEO_DI0 state:");
  Serial1.print(digitalRead(CONTROLLINO_NEO_DI0) ? "HIGH" : "LOW");
  Serial1.print("      CONTROLLINO_NEO_AI0 ADC:");
  Serial1.print(analogRead(CONTROLLINO_NEO_AI0));
  Serial1.print("      CONTROLLINO_NEO_AI0 ADC:");
  Serial1.print(analogRead(CONTROLLINO_NEO_AI0));
  Serial1.print(" DIGITAL:");
  Serial1.print(digitalRead(CONTROLLINO_NEO_AI0) ? "HIGH" : "LOW");

  digitalWrite(CONTROLLINO_NEO_DO1, digitalRead(CONTROLLINO_NEO_DI0));
  digitalWrite(CONTROLLINO_NEO_DO5, digitalRead(CONTROLLINO_NEO_AI0));
  
  uint8_t pwm = map(analogRead(CONTROLLINO_NEO_AI0), 0, 0x7FFFFF, 0, 0xFF); // Analog 23 bits to 8 bit for PWM 
  Serial1.print("      PWM:");
  Serial1.print(pwm);
  analogWrite(CONTROLLINO_NEO_DO0, pwm);
  analogWrite(CONTROLLINO_NEO_DO4, pwm);

  Serial1.print("      CONTROLLINO_NEO_AI1 ADC:");
  Serial1.print(analogRead(CONTROLLINO_NEO_AI1));
  Serial1.println();
  delay(500);
}
