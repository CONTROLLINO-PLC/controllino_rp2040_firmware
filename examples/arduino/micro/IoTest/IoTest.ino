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
  *
  * \note The resolution for analogAnalog read is set by default to 24 bits it can be changed with analogReadResolution(1..32)
  */

#include <Arduino.h>

bool do_en = true;
unsigned long enableDoTimer = 0;
unsigned long digitalAnalogTimer = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for native USB port only
  delay(3000);

  Serial.println("Initializing I/O ...");
  pinMode(CONTROLLINO_MICRO_DI0, INPUT); // Digital only input 0-11V LOW > 11V HIGH
  pinMode(CONTROLLINO_MICRO_DI1, INPUT); // Analog input
  pinMode(CONTROLLINO_MICRO_AI0, INPUT); // Analog input 23 bit resolution at default gain 0-24V

  // Digital therhold for analog input arround 12 V
  // Only for CONTROLLINO_MICRO_AI0...AI5
  setDigitalThreshold(CONTROLLINO_MICRO_AI0, 7360000U);

  pinMode(CONTROLLINO_MICRO_DO0, OUTPUT); // DIgital outputs all with PWM
  pinMode(CONTROLLINO_MICRO_DO1, OUTPUT);
  pinMode(CONTROLLINO_MICRO_DO2, OUTPUT);

  setOutCurrentLim(CONTROLLINO_MICRO_DO0, 1000); // Set current limit for DO0 to 1000 mA
}

void loop(void) {
  // I/O handling every 500 ms
  if ((millis() - digitalAnalogTimer) > 500)
  {
    digitalAnalogTimer = millis();

    // Digital and analog read AI0 and set value to DO0(digital) and DO1(analog as PWM)
    Serial.print("CONTROLLINO_MICRO_AI0 ADC:");
    Serial.print(analogRead(CONTROLLINO_MICRO_AI0));
    Serial.print(" DIGITAL:");
    Serial.print(digitalRead(CONTROLLINO_MICRO_AI0) ? "HIGH" : "LOW");
    digitalWrite(CONTROLLINO_MICRO_DO0, digitalRead(CONTROLLINO_MICRO_AI0));
    uint8_t pwm = map(analogRead(CONTROLLINO_MICRO_AI0), 0, 0xFFFFFFU, 0, 0xFFU); // Analog 24 bits to 8 bit for PWM
    Serial.print(" PWM:");
    Serial.print(pwm);
    analogWrite(CONTROLLINO_MICRO_DO1, pwm);

    // Digital read DI0 and set value to DO2
    Serial.print("      CONTROLLINO_MICRO_DI0 state:");
    Serial.print(digitalRead(CONTROLLINO_MICRO_DI0) ? "HIGH" : "LOW");
    digitalWrite(CONTROLLINO_MICRO_DO2, digitalRead(CONTROLLINO_MICRO_DI0));

    // Current measurement for DO2
    Serial.print(" CURRENT_DO2:");
    Serial.print(getOutCurrent(CONTROLLINO_MICRO_DO2));

    // Analog read DI1
    Serial.print("      CONTROLLINO_MICRO_DI1 ADC:");
    Serial.println(analogRead(CONTROLLINO_MICRO_DI1));
  }

  // Disable/Enable DO2 every 5 seconds
  if ((millis() - enableDoTimer) > 5000)
  {
    enableDoTimer = millis();
    if (do_en) {
      Serial.println("DO2 DISABLED");
      disableOut(CONTROLLINO_MICRO_DO2);
      do_en = false;
    }
    else {
      Serial.println(" DO2 ENABLED");
      enableOut(CONTROLLINO_MICRO_DO2);
      do_en = true;
    }
  }
}
