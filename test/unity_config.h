/**
 * \file unity_config.h
 *
 * Define unity test harness interface
 * Provided by PlatformIO 
 */
#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H
 
#ifndef NULL
#ifndef __cplusplus
#define NULL (void*)0
#else
#define NULL 0
#endif
#endif
 
#ifdef __cplusplus
extern "C"
{
#endif
 
void unityOutputStart(unsigned long);
void unityOutputChar(unsigned int);
void unityOutputFlush();
void unityOutputComplete();
 
#define UNITY_OUTPUT_START()    unityOutputStart((unsigned long) 115200)
#define UNITY_OUTPUT_CHAR(c)    unityOutputChar(c)
#define UNITY_OUTPUT_FLUSH()    unityOutputFlush()
#define UNITY_OUTPUT_COMPLETE() unityOutputComplete()
 
/* Defines used in tests*/
#define TEST_GPIO                           25
#define TEST_I2C_ADDR                       0x20
#define TEST_BTS71220_DAISY_CHAIN_NUMBER    0
#define TEST_AD56X4_DAC_DATA                0x7FFF
 
/* Run unity tests return int UNITY_END() */
int runUnityTests(void);
 
#ifdef __cplusplus
}
#endif /* extern "C" */
 
#endif /* UNITY_CONFIG_H */

