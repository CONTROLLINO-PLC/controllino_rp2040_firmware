/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "neo_pin.h"
 
ControllinoNeoPin  NEO_AI0(MCP356X_CH_CH0, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_AI1(MCP356X_CH_CH1, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_AI2(MCP356X_CH_CH2, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_AI3(MCP356X_CH_CH3, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_AI4(MCP356X_CH_CH4, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_AI5(MCP356X_CH_CH5, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_AI6(MCP356X_CH_CH6, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin  NEO_AI9(MCP356X_CH_CH7, ControllinoNeoPin::MCP356X_PIN);

ControllinoNeoPin  NEO_AO0(AD56X4_CH_ADDR_A, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  NEO_AO1(AD56X4_CH_ADDR_B, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  NEO_AO2(AD56X4_CH_ADDR_C, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin  NEO_AO3(AD56X4_CH_ADDR_D, ControllinoNeoPin::AD56X4_PIN);

ControllinoNeoPin  NEO_DI0(6, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_DI1(7, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_DI2(12, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_DI3(13, ControllinoNeoPin::NATIVE_PIN);

ControllinoNeoPin  NEO_DO0(14, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_DO1(22, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_DO2(23, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_DO3(24, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin  NEO_DO4(CY8C95XX_GPIO_6, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  NEO_DO5(CY8C95XX_GPIO_7, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  NEO_DO6(CY8C95XX_GPIO_8, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin  NEO_DO7(CY8C95XX_GPIO_9, ControllinoNeoPin::CY8C95XX_PIN);