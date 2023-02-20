/**
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef TEST_CONIFG_H
#define TEST_CONFIG_H
 
/**
 * \file unity_test_runner.h
 *
 * This file is used to define some especific configs and functions
 * used in the unit test suite
 */
 
#define TEST_GPIO                           25
#define TEST_I2C_ADDR                       0x20
#define TEST_BTS71220_DAISY_CHAIN_NUMBER    0
 
#ifdef __cplusplus
extern "C"
{
#endif
 
/**
 * \brief Run unity tests
 *
 * \return int UNITY_END()
 * \note Needs to be implemented in each test file
 */
int runUnityTests(void);
 
#ifdef __cplusplus
}
#endif /* extern "C" */
 
#endif /* UNITY_TEST_RUNNER_H */