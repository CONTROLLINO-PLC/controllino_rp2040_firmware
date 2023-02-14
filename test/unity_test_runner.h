/**
 * \file unity_test_runner.h
 *
 * This file is used to define a test runner function
 * and avoid code duplication in tests
 */
#ifndef UNITY_TEST_RUNNER_H
#define UNITY_TEST_RUNNER_H
 
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