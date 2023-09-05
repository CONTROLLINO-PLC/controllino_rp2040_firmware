/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef NATIVE_ENV // Avoid the folowing part on native testing
#include "controllino_wiring.h"
 
#include <CoreMutex.h>
#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <hardware/clocks.h>
#include <hardware/pll.h>
#include <hardware/adc.h>

/* Controllino analog API */
int analogRead(ControllinoRp2040Pin* pin)
{
    int adcValue = 0;
    switch (pin->getType())
    {
    case ControllinoRp2040Pin::RP2040_PIN:
        adcValue = analogRead(pin->getPin());
        break;
    case ControllinoRp2040Pin::MCP3564_PIN: // mcp3564.h
        mcp3564_mux_pos_t chn;
        switch (pin->getPin())
        {
        case MCP3564_CH_CH1:
            chn = MCP3564_MUX_VIN_POS_CH1;
            break;
        case MCP3564_CH_CH2:
            chn = MCP3564_MUX_VIN_POS_CH2;
            break;
        case MCP3564_CH_CH3:
            chn = MCP3564_MUX_VIN_POS_CH3;
            break;
        case MCP3564_CH_CH4:
            chn = MCP3564_MUX_VIN_POS_CH4;
            break;
        case MCP3564_CH_CH5:
            chn = MCP3564_MUX_VIN_POS_CH5;
            break;
        case MCP3564_CH_CH6:
            chn = MCP3564_MUX_VIN_POS_CH6;
            break;
        case MCP3564_CH_CH7:
            chn = MCP3564_MUX_VIN_POS_CH7;
            break;
        default:
            chn = MCP3564_MUX_VIN_POS_CH0;
            break;
        }
        // 500 us delay for 256 over sample rate
        mcp3564_read_adc_mux(dev_mcp3564, (uint32_t*)&adcValue, chn, MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS, 500);
        break;
    default:
        // Other pin types are digital or analog output only
        break;
    }
    return adcValue;
}

void analogWrite(ControllinoRp2040Pin* pin, int value)
{
    switch (pin->getType())
    {
    case ControllinoRp2040Pin::RP2040_PIN:
        analogWrite(pin->getPin(), value);
        break;
    case ControllinoRp2040Pin::CY8C9520_PIN: // cy8c9520.h
        if (pin->getMode() == OUTPUT) {
            cy8c9520_pwm_cfg_t pwmCfg;
            float dummyFreq;
            float dummyDutyCyc;
            uint8_t pulseWid;
            pulseWid = (uint8_t)value & 0xFF; // 8 bit resolution
            if (pulseWid < 0xFF) {
                switch (pin->getPin()) // CY8C9520 datasheet
                {
                case CY8C9520_GPIO_0:
                case CY8C9520_GPIO_2:
                case CY8C9520_GPIO_4:
                case CY8C9520_GPIO_6:
                case CY8C9520_GPIO_19:
                    pwmCfg.pwm_sel = CY8C9520_SEL_PWM_3;
                    break;
                case CY8C9520_GPIO_1:
                case CY8C9520_GPIO_3:
                case CY8C9520_GPIO_5:
                case CY8C9520_GPIO_7:
                    pwmCfg.pwm_sel = CY8C9520_SEL_PWM_1;
                    break;
                case CY8C9520_GPIO_8:
                case CY8C9520_GPIO_10:
                case CY8C9520_GPIO_12:
                case CY8C9520_GPIO_14:
                case CY8C9520_GPIO_16:
                    pwmCfg.pwm_sel = CY8C9520_SEL_PWM_2;
                    break;
                case CY8C9520_GPIO_9:
                case CY8C9520_GPIO_11:
                case CY8C9520_GPIO_13:
                case CY8C9520_GPIO_15:
                case CY8C9520_GPIO_17:
                case CY8C9520_GPIO_18:
                    pwmCfg.pwm_sel = CY8C9520_SEL_PWM_0;
                    break;
                }
                pwmCfg.clk_src = CY8C9520_PWM_CLK_SRC_367_6_HZ;
                pwmCfg.devider = 0x01;
                pwmCfg.period = 0xFF;
                pwmCfg.pulse_wid = pulseWid;
                cy8c9520_set_pwm_cfg(dev_cy8c9520, &pwmCfg, &dummyDutyCyc, &dummyFreq); // Set duty cycle to selected PWM
                cy8c9520_en_pin_pwm(dev_cy8c9520, (int)pin->getPin()); // Enable pwm over output
            }
            else { // if pulseWid 0xFF just output HIGH
                cy8c9520_dis_pin_pwm(dev_cy8c9520, (int)pin->getPin()); // Disable pwm
            }
            cy8c9520_write_pin(dev_cy8c9520, (int)pin->getPin(), 1); // Enable output
        }
        break;
    case ControllinoRp2040Pin::AD5664_PIN: // ad5664.h
        ad5664_write_input_reg(dev_ad5664, (ad5664_ch_addr_t)pin->getPin(), ((uint16_t)value & 0xFFFF)); // 16 bits resolution
        ad5664_update_dac_reg(dev_ad5664, (ad5664_ch_addr_t)pin->getPin());
        break;
    default:
        // Other pin types are analog only
        break;
    }
}
 
/* Modifications of wiring_analog.cpp on arduino-pico  */
void __clearADCPin(pin_size_t p);

static uint32_t analogScale = 255;
static uint32_t analogFreq = 1000;
static uint32_t pwmInitted = 0;
static bool scaleInitted = false;
static bool adcInitted = false;
static uint16_t analogWritePseudoScale = 1;
static uint16_t analogWriteSlowScale = 1;

auto_init_mutex(_dacMutex);

extern "C" void analogWriteFreq(uint32_t freq) {
    if (freq == analogFreq) {
        return;
    }
    if (freq < 100) {
        DEBUGCORE("ERROR: analogWriteFreq too low (%lu)\n", freq);
        analogFreq = 100;
    }
    else if (freq > 10'000'000) {
        DEBUGCORE("ERROR: analogWriteFreq too high (%lu)\n", freq);
        analogFreq = 10'000'000;
    }
    else {
        analogFreq = freq;
    }
    pwmInitted = 0;
    scaleInitted = false;
}

extern "C" void analogWriteRange(uint32_t range) {
    if (range == analogScale) {
        return;
    }
    if ((range >= 3) && (range <= 65535)) {
        analogScale = range;
        pwmInitted = 0;
        scaleInitted = false;
    }
    else {
        DEBUGCORE("ERROR: analogWriteRange out of range (%lu)\n", range);
    }
}

extern "C" void analogWriteResolution(int res) {
    if ((res >= 2) && (res <= 16)) {
        analogWriteRange((1 << res) - 1);
    }
    else {
        DEBUGCORE("ERROR: analogWriteResolution out of range (%d)\n", res);
    }
}

extern "C" void analogWrite(pin_size_t pin, int val) {
    if (pin < 32) {
        CoreMutex m(&_dacMutex);

        if ((pin > 29) || !m) {
            DEBUGCORE("ERROR: Illegal analogWrite pin (%d)\n", pin);
            return;
        }
        __clearADCPin(pin);
        if (!scaleInitted) {
            // For low frequencies, we need to scale the output max value up to achieve lower periods
            analogWritePseudoScale = 1;
            while (((clock_get_hz(clk_sys) / ((float)analogScale * analogFreq)) > 255.0) && (analogScale < 32678)) {
                analogWritePseudoScale++;
                analogScale *= 2;
                DEBUGCORE("Adjusting analogWrite values PS=%d, scale=%lu\n", analogWritePseudoScale, analogScale);
            }
            // For high frequencies, we need to scale the output max value down to actually hit the frequency target
            analogWriteSlowScale = 1;
            while (((clock_get_hz(clk_sys) / ((float)analogScale * analogFreq)) < 1.0) && (analogScale >= 6)) {
                analogWriteSlowScale++;
                analogScale /= 2;
                DEBUGCORE("Adjusting analogWrite values SS=%d, scale=%lu\n", analogWriteSlowScale, analogScale);
            }
            scaleInitted = true;
        }
        if (!(pwmInitted & (1 << pwm_gpio_to_slice_num(pin)))) {
            pwm_config c = pwm_get_default_config();
            pwm_config_set_clkdiv(&c, clock_get_hz(clk_sys) / ((float)analogScale * analogFreq));
            pwm_config_set_wrap(&c, analogScale - 1);
            pwm_init(pwm_gpio_to_slice_num(pin), &c, true);
            pwmInitted |= 1 << pwm_gpio_to_slice_num(pin);
        }

        val <<= analogWritePseudoScale;
        val >>= analogWriteSlowScale;

        if (val < 0) {
            val = 0;
        }
        else if ((uint32_t)val > analogScale) {
            val = analogScale;
        }

        gpio_set_function(pin, GPIO_FUNC_PWM);
        pwm_set_gpio_level(pin, val);
    }
    else if (getControllinoRp2040Pin(pin) != nullptr) {
        analogWrite(getControllinoRp2040Pin(pin), val);
    }
}

auto_init_mutex(_adcMutex);
static uint8_t _readBits = 10;
static uint8_t _lastADCMux = 0;
static uint32_t _adcGPIOInit = 0;

void __clearADCPin(pin_size_t p) {
    _adcGPIOInit &= ~(1 << p);
}

extern "C" int analogRead(pin_size_t pin) {
    if (pin < 32) {
        CoreMutex m(&_adcMutex);

        pin_size_t maxPin = max(A0, A3);
        pin_size_t minPin = min(A0, A3);

        if ((pin < minPin) || (pin > maxPin) || !m) {
            DEBUGCORE("ERROR: Illegal analogRead pin (%d)\n", pin);
            return 0;
        }
        if (!adcInitted) {
            adc_init();
            adcInitted = true;
        }
        if (!(_adcGPIOInit & (1 << pin))) {
            adc_gpio_init(pin);
            _adcGPIOInit |= 1 << pin;
        }
        if (_lastADCMux != pin) {
            adc_select_input(pin - minPin);
            _lastADCMux = pin;
        }
        return (_readBits < 12) ? adc_read() >> (12 - _readBits) : adc_read() << (_readBits - 12);
    }
    else if (getControllinoRp2040Pin(pin) != nullptr) {
        return analogRead(getControllinoRp2040Pin(pin));
    }
    return 0;
}

extern "C" float analogReadTemp(float vref) {
    CoreMutex m(&_adcMutex);

    if (!m) {
        return 0.0f; // Deadlock
    }
    if (!adcInitted) {
        adc_init();
        adcInitted = true;
    }
    _lastADCMux = 0;
    adc_set_temp_sensor_enabled(true);
    delay(1); // Allow things to settle.  Without this, readings can be erratic
    adc_select_input(4); // Temperature sensor
    int v = adc_read();
    adc_set_temp_sensor_enabled(false);
    float t = 27.0f - ((v * vref / 4096.0f) - 0.706f) / 0.001721f; // From the datasheet
    return t;
}

extern "C" void analogReadResolution(int bits) {
    CoreMutex m(&_adcMutex);
    if (m && ((bits > 0) && (bits < 32))) {
        _readBits = bits;
    }
}

#endif // #ifndef NATIVE_ENV