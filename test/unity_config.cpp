/**
 * \file unity_config.cpp
 *
 * Implement unity test harness interface for the different eviroments
 * Adapted from code provided by PlatformIO
 */
#include "unity_config.h"

#if !defined(UNITY_WEAK_ATTRIBUTE) && !defined(UNITY_WEAK_PRAGMA)
#   if defined(__GNUC__) || defined(__ghs__) /* __GNUC__ includes clang */
#       if !(defined(__WIN32__) && defined(__clang__)) && !defined(__TMS470__)
#           define UNITY_WEAK_ATTRIBUTE __attribute__((weak))
#       endif
#   endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef UNITY_WEAK_ATTRIBUTE
    UNITY_WEAK_ATTRIBUTE void setUp(void) { }
    UNITY_WEAK_ATTRIBUTE void tearDown(void) { }
    UNITY_WEAK_ATTRIBUTE void suiteSetUp(void) { }
    UNITY_WEAK_ATTRIBUTE int suiteTearDown(int num_failures) { return num_failures; }
#elif defined(UNITY_WEAK_PRAGMA)
#pragma weak setUp
    void setUp(void) { }
#pragma weak tearDown
    void tearDown(void) { }
#pragma weak suiteSetUp
    void suiteSetUp(void) { }
#pragma weak suiteTearDown
    int suiteTearDown(int num_failures) { return num_failures; }
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#ifdef NATIVE_ENV
#include <stdio.h>
void unityOutputStart(unsigned long baudrate) { }
void unityOutputChar(unsigned int c) { putchar(c); }
void unityOutputFlush(void) { fflush(stdout); }
void unityOutputComplete(void) { }
int main(int argc, char** argv) { runUnityTests(); return 0; }
#endif

#ifdef NEO_ENV
#include <Arduino.h>
void unityOutputStart(unsigned long baudrate)
{
#ifdef UNITY_OUTPUT_SERIAL1
    Serial1.begin(baudrate);
#else
    Serial.begin(baudrate);
#endif
}
 
void unityOutputChar(unsigned int c)
{
#ifdef UNITY_OUTPUT_SERIAL1
    Serial1.write(c);
#else
    Serial.write(c);
#endif
}
 
void unityOutputFlush(void)
{
#ifdef UNITY_OUTPUT_SERIAL1
    Serial1.flush();
#else
    Serial.flush();
#endif
}
 
void unityOutputComplete(void)
{
#ifdef UNITY_OUTPUT_SERIAL1
    Serial1.end();
#else
    Serial.end();
#endif
}
 
void setup()
{
#ifdef UNITY_OUTPUT_SERIAL1
    delay(3000);
#else
    while (!Serial)
#endif
    runUnityTests();
}
 
void loop() {}
#endif

    