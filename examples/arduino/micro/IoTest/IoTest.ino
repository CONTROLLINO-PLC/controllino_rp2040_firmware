/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * \file IoTest.ino
 *
 * \brief Example of CONTROLLINO MICRO I/O usage
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */

#include "Arduino.h"
#include "SPI.h"

bool do_en = true;

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

  setOutCurrentLim(CONTROLLINO_MICRO_DO0, 1000); // Set current limit for DO0 to 1000 mA
}

unsigned long lastMillis = 0;

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

  analogWrite(CONTROLLINO_MICRO_DO0, pwm);
  analogWrite(CONTROLLINO_MICRO_DO4, pwm);

  Serial.print("      CURRENT_DO0:");
  Serial.print(getOutCurrent(CONTROLLINO_MICRO_DO0));

  if ((millis() - lastMillis) > 5000)
  {
    if (do_en) {
      Serial.println(" DO1 DISABLED");
      disableOut(CONTROLLINO_MICRO_DO0);
      do_en = false;
    }
    else {
      Serial.println(" DO1 ENABLED");
      enableOut(CONTROLLINO_MICRO_DO0);
      do_en = true;
    }
    lastMillis = millis();
  }

  Serial.println();
  delay(500);
}
