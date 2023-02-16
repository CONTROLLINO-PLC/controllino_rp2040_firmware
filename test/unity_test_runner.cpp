/**
 * \file unitity_test_runner.cpp
 *
 * Execute test runner in the diferent environments
 */
#include "unity_test_runner.h"
 
#if defined(NATIVE_TEST_ENV)
int main(int argc, char** argv)
{
    runUnityTests();
    return 0;
}
#endif
 
#if defined(ARDUINO_PICO_ENV)
#include "Arduino.h"
void setup()
{
    while (!Serial);
    runUnityTests();
}
void loop()
{}
#endif

