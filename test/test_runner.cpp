/**
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 *
 * \file unitity_test_runner.cpp
 *
 * Execute unit test in the diferent environments
 * this avoid code duplication in the test files
 */
#include "test_config.h"
 
#ifdef NATIVE_TEST_ENV
int main(int argc, char** argv)
{
    runUnityTests();
    return 0;
}
#endif
 
#ifdef ARDUINO_NEO_ENV
#include "Arduino.h"
void setup()
{
    while (!Serial);
    runUnityTests();
}
void loop()
{}
#endif

