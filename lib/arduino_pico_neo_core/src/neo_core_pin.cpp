/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "string.h"
#include "neo_core_pin.h"

/* Neo Core pins definitions */
ControllinoNeoPin* NEO_CORE_AI0 = new ControllinoNeoPin(MCP356X_CH_CH0, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* NEO_CORE_AI1 = new ControllinoNeoPin(MCP356X_CH_CH1, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* NEO_CORE_AI2 = new ControllinoNeoPin(MCP356X_CH_CH2, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* NEO_CORE_AI3 = new ControllinoNeoPin(MCP356X_CH_CH3, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* NEO_CORE_AI4 = new ControllinoNeoPin(MCP356X_CH_CH4, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* NEO_CORE_AI5 = new ControllinoNeoPin(MCP356X_CH_CH5, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* NEO_CORE_AI6 = new ControllinoNeoPin(MCP356X_CH_CH6, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* NEO_CORE_AI9 = new ControllinoNeoPin(MCP356X_CH_CH7, ControllinoNeoPin::MCP356X_PIN);

ControllinoNeoPin* NEO_CORE_AO0 = new ControllinoNeoPin(AD56X4_CH_ADDR_A, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin* NEO_CORE_AO1 = new ControllinoNeoPin(AD56X4_CH_ADDR_B, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin* NEO_CORE_AO2 = new ControllinoNeoPin(AD56X4_CH_ADDR_C, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin* NEO_CORE_AO3 = new ControllinoNeoPin(AD56X4_CH_ADDR_D, ControllinoNeoPin::AD56X4_PIN);

ControllinoNeoPin* NEO_CORE_DI0 = new ControllinoNeoPin(6U, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin* NEO_CORE_DI1 = new ControllinoNeoPin(7U, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin* NEO_CORE_DI2 = new ControllinoNeoPin(12U, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin* NEO_CORE_DI3 = new ControllinoNeoPin(13U, ControllinoNeoPin::NATIVE_PIN);

ControllinoNeoPin* NEO_CORE_DO0 = new ControllinoNeoPin(24U, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin* NEO_CORE_DO1 = new ControllinoNeoPin(23U, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin* NEO_CORE_DO2 = new ControllinoNeoPin(22U, ControllinoNeoPin::NATIVE_PIN);
ControllinoNeoPin* NEO_CORE_DO3 = new ControllinoNeoPin(14U, ControllinoNeoPin::NATIVE_PIN);

ControllinoNeoPin* NEO_CORE_DO4 = new ControllinoNeoPin(CY8C95XX_GPIO_9, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin* NEO_CORE_DO5 = new ControllinoNeoPin(CY8C95XX_GPIO_8, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin* NEO_CORE_DO6 = new ControllinoNeoPin(CY8C95XX_GPIO_7, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin* NEO_CORE_DO7 = new ControllinoNeoPin(CY8C95XX_GPIO_6, ControllinoNeoPin::CY8C95XX_PIN);
 
void pinMode(ControllinoNeoPin* pin, PinMode mode)
{
    switch (pin->getType())
    {
    case ControllinoNeoPin::NATIVE_PIN:
        gpio_set_input_hysteresis_enabled(pin->getPin(), false);
        pinMode(pin->getPin(), mode);
        break;
    case ControllinoNeoPin::CY8C95XX_PIN: // cy8c95xx.h
        cy8c95xx_dir_mode_t dir;
        cy8c95xx_drv_mode_t drv;
        switch (mode)
        {
        case OUTPUT:
        case OUTPUT_2MA:
        case OUTPUT_4MA:
        case OUTPUT_8MA:
        case OUTPUT_12MA:
            mode = OUTPUT;
        case INPUT_PULLDOWN:
            dir = CY8C95XX_GPIO_IN;
            drv = CY8C95XX_DRV_PULL_DOWN;
            break;
        default:
            mode = INPUT_PULLUP;
            dir = CY8C95XX_GPIO_IN;
            drv = CY8C95XX_DRV_PULL_UP;
            break;
        }
        cy8c95xx_write_pin(neo_cy8c95xx, (int)pin->getPin(), 0); // Set output to LOW
        cy8c95xx_pin_mode(neo_cy8c95xx, (int)pin->getPin(), dir, drv);
        cy8c95xx_dis_pin_pwm(neo_cy8c95xx, (int)pin->getPin()); // Disable PWM
        break;
        // Other pin types has fixed modes 
    case ControllinoNeoPin::MCP356X_PIN:
        mode = INPUT;
        break;
    case ControllinoNeoPin::AD56X4_PIN:
        mode = OUTPUT;
        break;
    }
    pin->setMode(mode);
}
 
PinStatus digitalRead(ControllinoNeoPin* pin)
{
    PinStatus pinStatus = LOW;
    switch (pin->getType())
    {
    case ControllinoNeoPin::NATIVE_PIN:
        pinStatus = digitalRead(pin->getPin());
        break;
    case ControllinoNeoPin::CY8C95XX_PIN: // cy8c95xx.h
        uint8_t pinState;
        switch (pin->getMode())
        {
        case OUTPUT:
        case OUTPUT_4MA:
        case OUTPUT_2MA:
        case OUTPUT_8MA:
        case OUTPUT_12MA:
            cy8c95xx_read_pin_out_lvl(neo_cy8c95xx, (int)pin->getPin(), &pinState);
            break;
        default:
            cy8c95xx_read_pin(neo_cy8c95xx, (int)pin->getPin(), &pinState);
            break;
        }
        pinStatus = pinState ? HIGH : LOW;
        break;
    case ControllinoNeoPin::MCP356X_PIN:
        pinStatus = (analogRead(pin) >= pin->_getDigitalThreshold()) ? HIGH : LOW;
        break;
    default:
        // In other pins digitalRead does not make sense
        break;
    }
    return pinStatus;
}
 
void digitalWrite(ControllinoNeoPin* pin, PinStatus value)
{
    switch (pin->getType())
    {
    case ControllinoNeoPin::NATIVE_PIN:
        digitalWrite(pin->getPin(), value);
        break;
    case ControllinoNeoPin::CY8C95XX_PIN: // cy8c95xx.h
        if (pin->getMode() == OUTPUT) {
            cy8c95xx_dir_mode_t dir;
            cy8c95xx_drv_mode_t drv;
            if (value == HIGH)
            {
                dir = CY8C95XX_GPIO_OUT;
                drv = CY8C95XX_DRV_STRONG;
            }
            else
            {
                dir = CY8C95XX_GPIO_IN;
                drv = CY8C95XX_DRV_PULL_DOWN;
            }
            cy8c95xx_pin_mode(neo_cy8c95xx, (int)pin->getPin(), dir, drv);
            cy8c95xx_write_pin(neo_cy8c95xx, (int)pin->getPin(), (uint8_t)value);
            cy8c95xx_dis_pin_pwm(neo_cy8c95xx, (int)pin->getPin()); // Disable PWM
        }
        break;
    default:
        // Other pin types are analog only
        break;
    }
}
 
int analogRead(ControllinoNeoPin* pin)
{
    int adcValue = 0;
    switch (pin->getType())
    {
    case ControllinoNeoPin::NATIVE_PIN:
        adcValue = analogRead(pin->getPin());
        break;
    case ControllinoNeoPin::MCP356X_PIN: // mcp356x.h
        uint8_t txdata[7];
        memset(txdata, 0x00, sizeof(txdata));
        txdata[0] = MCP356X_MUX_VIN_NEG_VREF_EXT_MINUS;
        switch (pin->getPin())
        {
        case MCP356X_CH_CH1:
            txdata[0] |= MCP356X_MUX_VIN_POS_CH1;
            break;
        case MCP356X_CH_CH2:
            txdata[0] |= MCP356X_MUX_VIN_POS_CH2;
            break;
        case MCP356X_CH_CH3:
            txdata[0] |= MCP356X_MUX_VIN_POS_CH4;
            break;
        case MCP356X_CH_CH5:
            txdata[0] |= MCP356X_MUX_VIN_POS_CH5;
            break;
        case MCP356X_CH_CH6:
            txdata[0] |= MCP356X_MUX_VIN_POS_CH6;
            break;
        case MCP356X_CH_CH7:
            txdata[0] |= MCP356X_MUX_VIN_POS_CH7;
            break;
        default:
            txdata[0] |= MCP356X_MUX_VIN_POS_CH0;
            break;
        }
        mcp356x_iwrite(neo_mcp356x, MCP356X_REG_MUX, txdata, sizeof(txdata));
        uint8_t dummySgn;
        uint32_t dummyRes;
        mcp356x_read_raw_adc(neo_mcp356x, (uint32_t*)&adcValue, &dummySgn, &dummyRes);
        break;
    default:
        // Other pin types are digital or analog output only
        break;
    }
    return adcValue;
}
 
void analogWrite(ControllinoNeoPin* pin, int value)
{
    switch (pin->getType())
    {
    case ControllinoNeoPin::NATIVE_PIN:
        analogWrite(pin->getPin(), value);
        break;
    case ControllinoNeoPin::CY8C95XX_PIN: // cy8c95xx.h
        if (pin->getMode() == OUTPUT) {
            cy8c95xx_pwm_cfg_t pwmCfg;
            float dummyFreq;
            float dummyDutyCyc;
            uint8_t pulseWid;
            pulseWid = (uint8_t)value & 0xFF; // 8 bit resolution
            if (pulseWid < 0xFF) {
                switch (pin->getPin()) // CY8C95XX datasheet
                {
                case CY8C95XX_GPIO_0:
                case CY8C95XX_GPIO_2:
                case CY8C95XX_GPIO_4:
                case CY8C95XX_GPIO_6:
                case CY8C95XX_GPIO_19:
                    pwmCfg.pwm_sel = CY8C95XX_SEL_PWM_3;
                    break;
                case CY8C95XX_GPIO_1:
                case CY8C95XX_GPIO_3:
                case CY8C95XX_GPIO_5:
                case CY8C95XX_GPIO_7:
                    pwmCfg.pwm_sel = CY8C95XX_SEL_PWM_1;
                    break;
                case CY8C95XX_GPIO_8:
                case CY8C95XX_GPIO_10:
                case CY8C95XX_GPIO_12:
                case CY8C95XX_GPIO_14:
                case CY8C95XX_GPIO_16:
                    pwmCfg.pwm_sel = CY8C95XX_SEL_PWM_2;
                    break;
                case CY8C95XX_GPIO_9:
                case CY8C95XX_GPIO_11:
                case CY8C95XX_GPIO_13:
                case CY8C95XX_GPIO_15:
                case CY8C95XX_GPIO_17:
                case CY8C95XX_GPIO_18:
                    pwmCfg.pwm_sel = CY8C95XX_SEL_PWM_0;
                    break;
                }
                pwmCfg.clk_src = CY8C95XX_PWM_CLK_SRC_367_6_HZ;
                pwmCfg.devider = 0x01;
                pwmCfg.period = 0xFF;
                pwmCfg.pulse_wid = pulseWid;
                cy8c95xx_set_pwm_cfg(neo_cy8c95xx, &pwmCfg, &dummyDutyCyc, &dummyFreq); // Set duty cycle to selected PWM
                cy8c95xx_en_pin_pwm(neo_cy8c95xx, (int)pin->getPin()); // Enable pwm over output
            }
            else { // if pulseWid 0xFF just output HIGH
                cy8c95xx_dis_pin_pwm(neo_cy8c95xx, (int)pin->getPin()); // Disable pwm
            }
            cy8c95xx_write_pin(neo_cy8c95xx, (int)pin->getPin(), 1); // Enable output
        }
        break;
    case ControllinoNeoPin::AD56X4_PIN: // ad56x4.h
        ad56x4_write_input_reg(neo_ad56x4, (ad56x4_ch_addr_t)pin->getPin(), ((uint16_t)value & 0xFFFF)); // 16 bits resolution
        ad56x4_update_dac_reg(neo_ad56x4, (ad56x4_ch_addr_t)pin->getPin());
        break;
    default:
        // Other pin types are analog only
        break;
    }
}
 
/* Set the digital threshold to implement a digital input with an analog input only pin */
void setDigitalThreshold(ControllinoNeoPin* pin, uint32_t threshold)
{
    switch (pin->getType())
    {
    case ControllinoNeoPin::MCP356X_PIN:
        pin->_setDigitalThreshold(threshold);
        break;
    default:
        // Other pin types are not analog inputs
        break;
    }
}
 
/* Get current digital threshold */
uint32_t getDigitalThreshold(ControllinoNeoPin* pin)
{
    return pin->_getDigitalThreshold();
}