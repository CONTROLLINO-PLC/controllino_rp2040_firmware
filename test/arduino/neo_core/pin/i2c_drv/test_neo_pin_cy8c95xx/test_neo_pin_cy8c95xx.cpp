#include <unity.h>
#include "Arduino.h"
 
uint8_t TEST_CY8C95XX_GPIO;
uint8_t TEST_CY8C95XX_ADDR = CY8C95XX_DEV_ADDR_GND;
 
void setUp(void)
{}
 
void tearDown(void)
{}
 
int runUnityTests(void)
{
    UNITY_BEGIN();
    UNITY_END();
    return UNITY_END();
}
