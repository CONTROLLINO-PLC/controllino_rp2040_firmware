#ifdef NATIVE_ENV
 
#include "Arduino.h"
 
extern uint8_t TEST_BTS71220_CURRENT_SENSE_REF_ADC;
 
int analogRead(pin_size_t pin) { return TEST_BTS71220_CURRENT_SENSE_REF_ADC; }
 
#endif