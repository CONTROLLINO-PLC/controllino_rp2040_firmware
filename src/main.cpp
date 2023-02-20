#ifdef NATIVE_TEST_ENV
int main() {
    while (1);
    return 0;
}
#endif
 
#ifdef ARDUINO_NEO_ENV
#include "Arduino.h"
void setup() {
}
void loop() {
}
#endif