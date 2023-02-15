
#if defined(NATIVE_TEST_ENV)
int main() {
    while (1);
    return 0;
}
#endif
 
#if defined(ARDUINO_PICO_ENV)
#include "Arduino.h"
void setup() {
}
void loop() {
}
#endif