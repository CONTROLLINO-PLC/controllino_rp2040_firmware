/*
  ECCX08 Random Number

  This sketch uses the ECC508 or ECC608 to generate a random number 
  every second and print it to the Serial1 monitor

  Circuit:
   - MKR board with ECC508 or ECC608 on board

  created 19 July 2018
  by Sandeep Mistry
*/
#include "SPI.h"
#include <ArduinoECCX08.h>


void setup() {
  Serial1.begin(115200);
  while (!Serial1);

  if (!ECCX08.begin()) {
    Serial1.println("Failed to communicate with ECC508/ECC608!");
    while (1);
  }

  if (!ECCX08.locked()) {
    Serial1.println("The ECC508/ECC608 is not locked!");
    while (1);
  }
}

void loop() {
  Serial1.print("Random number = ");
  Serial1.println(ECCX08.random(65535));

  delay(1000);
}

