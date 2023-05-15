#ifdef NATIVE_ENV
 
#include "Arduino.h"
 
extern "C" void delayMicroseconds(unsigned int us) {}
 
extern "C" void __pinMode(pin_size_t ulPin, PinMode ulMode) {}
extern "C" void __digitalWrite(pin_size_t ulPin, PinStatus ulVal) {}
extern "C" PinStatus __digitalRead(pin_size_t ulPin) { return LOW; }
 
extern "C" void analogWrite(pin_size_t pin, int val) {
    if (getControllinoNeoPin(pin) != nullptr)
        analogWrite(getControllinoNeoPin(pin), val);
}
 
extern uint8_t TEST_ANALOG_READ_ADC __attribute__((weak, alias("__TEST_ANALOG_READ_ADC")));
uint8_t __TEST_ANALOG_READ_ADC = 1;
extern "C" int analogRead(pin_size_t pin) {
    if (pin < 32)
        return TEST_ANALOG_READ_ADC;
    else if (getControllinoNeoPin(pin) != nullptr)
        return analogRead(getControllinoNeoPin(pin));
    return 0;
}
 
#endif