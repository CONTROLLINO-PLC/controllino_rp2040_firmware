/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "neo_pin.h"
 
ControllinoNeoPin  AI0(MCP356X_CH_CH0, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  AI1(MCP356X_CH_CH1, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  AI2(MCP356X_CH_CH2, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  AI3(MCP356X_CH_CH3, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  AI4(MCP356X_CH_CH4, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  AI5(MCP356X_CH_CH5, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  AI6(MCP356X_CH_CH6, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  AI9(MCP356X_CH_CH7, ControllinoNeoPin::MCP356X_PIN);

ControllinoNeoPin  AO0(AD56X4_CH_ADDR_A, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  AO1(AD56X4_CH_ADDR_B, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  AO2(AD56X4_CH_ADDR_C, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  AO3(AD56X4_CH_ADDR_D, ControllinoNeoPin::AD56X4_PIN);

ControllinoNeoPin  DI0(6, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  DI1(7, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  DI2(12, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  DI3(13, ControllinoNeoPin::NATIVE_PIN);

ControllinoNeoPin  DO0(14, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  DO1(22, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  DO2(23, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  DO3(24, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  DO4(CY8C95XX_GPIO_6, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  DO5(CY8C95XX_GPIO_7, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  DO6(CY8C95XX_GPIO_8, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  DO7(CY8C95XX_GPIO_9, ControllinoNeoPin::CY8C95XX_PIN);