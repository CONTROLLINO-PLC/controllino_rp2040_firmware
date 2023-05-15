/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "string.h"
#include "neo_core_pin.h"
 
/* Peripherals interfaces */
cy8c95xx_t* neo_cy8c95xx;
mcp356x_t* neo_mcp356x;
ad56x4_t* neo_ad56x4;
bts71220_t* neo_bts71220;
wsen_temp_t* neo_wsen_temp;
 
/*
Arduino-pico variant initialization
Note: This function will be called on every boot before setup()
*/
void initVariant()
{
    neo_cy8c95xx = (cy8c95xx_t*)malloc(sizeof(cy8c95xx_t));
    neo_mcp356x = (mcp356x_t*)malloc(sizeof(mcp356x_t));
    neo_ad56x4 = (ad56x4_t*)malloc(sizeof(ad56x4_t));
    neo_bts71220 = (bts71220_t*)malloc(sizeof(bts71220_t));
    neo_wsen_temp = (wsen_temp_t*)malloc(sizeof(wsen_temp_t));
    // WSEN temperature sensor
    wsen_temp_cfg_t wsen_temp_cfg;
    wsen_temp_set_default_cfg(&wsen_temp_cfg);
    wsen_temp_init(neo_wsen_temp, &wsen_temp_cfg);
    // Port expander 
    cy8c95xx_cfg_t cy8c95xx_cfg;
    cy8c95xx_set_default_cfg(&cy8c95xx_cfg);
    cy8c95xx_init(neo_cy8c95xx, &cy8c95xx_cfg);
    // Digital output pins to low level at the beginning
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_6, 0);
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_7, 0);
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_8, 0);
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_9, 0);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_6, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_7, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_8, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    cy8c95xx_pin_mode(neo_cy8c95xx, CY8C95XX_GPIO_9, CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
    // cy8c95xx_send_cmd(neo_cy8c95xx, CY8C95XX_STORE_POR_CFG_TO_EEPROM);
    // ADC analog inputs
    mcp356x_cfg_t mcp356x_cfg;
    mcp356x_set_default_cfg(&mcp356x_cfg);
    mcp356x_init(neo_mcp356x, &mcp356x_cfg);
    // DAC analog output
    ad56x4_cfg_t ad56x4_cfg;
    ad56x4_set_default_cfg(&ad56x4_cfg);
    ad56x4_init(neo_ad56x4, &ad56x4_cfg);
    // Digital outputs controller
    bts71220_cfg_t bts71220_cfg;
    bts71220_set_default_cfg(&bts71220_cfg);
    bts71220_init(neo_bts71220, &bts71220_cfg);
}
 
/* SPI chip select management */
void mcp356x_cs_select(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_14, 0);
    delayMicroseconds(600);
}
void mcp356x_cs_deselect(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_14, 1);
}

void ad56x4_cs_select(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_15, 0);
    delayMicroseconds(600);
}
void ad56x4_cs_deselect(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_15, 1);
}

void bts71220_cs_select(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_12, 0);
    delayMicroseconds(600);
}
void bts71220_cs_deselect(int cs_pin) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_12, 1);
}

void sd_card_cs_select(void) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_13, 0);
    delayMicroseconds(600);
}
void sd_card_cs_deselect(void) {
    cy8c95xx_write_pin(neo_cy8c95xx, CY8C95XX_GPIO_13, 1);
}
 
/* Pin definitions for ControllinoNeoPin API */
ControllinoNeoPin* _NEO_CORE_AI0 = new ControllinoNeoPin(MCP356X_CH_CH0, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* _NEO_CORE_AI1 = new ControllinoNeoPin(MCP356X_CH_CH1, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* _NEO_CORE_AI2 = new ControllinoNeoPin(MCP356X_CH_CH2, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* _NEO_CORE_AI3 = new ControllinoNeoPin(MCP356X_CH_CH3, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* _NEO_CORE_AI4 = new ControllinoNeoPin(MCP356X_CH_CH4, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* _NEO_CORE_AI5 = new ControllinoNeoPin(MCP356X_CH_CH5, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* _NEO_CORE_AI6 = new ControllinoNeoPin(MCP356X_CH_CH6, ControllinoNeoPin::MCP356X_PIN);
ControllinoNeoPin* _NEO_CORE_AI7 = new ControllinoNeoPin(MCP356X_CH_CH7, ControllinoNeoPin::MCP356X_PIN);

ControllinoNeoPin* _NEO_CORE_AO0 = new ControllinoNeoPin(AD56X4_CH_ADDR_A, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin* _NEO_CORE_AO1 = new ControllinoNeoPin(AD56X4_CH_ADDR_B, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin* _NEO_CORE_AO2 = new ControllinoNeoPin(AD56X4_CH_ADDR_C, ControllinoNeoPin::AD56X4_PIN);
ControllinoNeoPin* _NEO_CORE_AO3 = new ControllinoNeoPin(AD56X4_CH_ADDR_D, ControllinoNeoPin::AD56X4_PIN);

ControllinoNeoPin* _NEO_CORE_DO4 = new ControllinoNeoPin(CY8C95XX_GPIO_9, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin* _NEO_CORE_DO5 = new ControllinoNeoPin(CY8C95XX_GPIO_8, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin* _NEO_CORE_DO6 = new ControllinoNeoPin(CY8C95XX_GPIO_7, ControllinoNeoPin::CY8C95XX_PIN);
ControllinoNeoPin* _NEO_CORE_DO7 = new ControllinoNeoPin(CY8C95XX_GPIO_6, ControllinoNeoPin::CY8C95XX_PIN);

ControllinoNeoPin* _NEO_CORE_DI0 = new ControllinoNeoPin(_NEO_CORE_DI0_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);
ControllinoNeoPin* _NEO_CORE_DI1 = new ControllinoNeoPin(_NEO_CORE_DI1_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);
ControllinoNeoPin* _NEO_CORE_DI2 = new ControllinoNeoPin(_NEO_CORE_DI2_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);
ControllinoNeoPin* _NEO_CORE_DI3 = new ControllinoNeoPin(_NEO_CORE_DI3_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);

ControllinoNeoPin* _NEO_CORE_DO0 = new ControllinoNeoPin(_NEO_CORE_DO0_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);
ControllinoNeoPin* _NEO_CORE_DO1 = new ControllinoNeoPin(_NEO_CORE_DO1_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);
ControllinoNeoPin* _NEO_CORE_DO2 = new ControllinoNeoPin(_NEO_CORE_DO2_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);
ControllinoNeoPin* _NEO_CORE_DO3 = new ControllinoNeoPin(_NEO_CORE_DO3_RP2040_GPIO, ControllinoNeoPin::RP2040_PIN);
 
/* Returns ControllinoNeoPin API pin or nullptr */
ControllinoNeoPin* getControllinoNeoPin(int pin)
{
    switch (pin)
    {
    case NEO_CORE_AI0: return _NEO_CORE_AI0;
    case NEO_CORE_AI1: return _NEO_CORE_AI1;
    case NEO_CORE_AI2: return _NEO_CORE_AI2;
    case NEO_CORE_AI3: return _NEO_CORE_AI3;
    case NEO_CORE_AI4: return _NEO_CORE_AI4;
    case NEO_CORE_AI5: return _NEO_CORE_AI5;
    case NEO_CORE_AI6: return _NEO_CORE_AI6;
    case NEO_CORE_AI7: return _NEO_CORE_AI7;

    case NEO_CORE_AO0: return _NEO_CORE_AO0;
    case NEO_CORE_AO1: return _NEO_CORE_AO1;
    case NEO_CORE_AO2: return _NEO_CORE_AO2;
    case NEO_CORE_AO3: return _NEO_CORE_AO3;

    case NEO_CORE_DO4: return _NEO_CORE_DO4;
    case NEO_CORE_DO5: return _NEO_CORE_DO5;
    case NEO_CORE_DO6: return _NEO_CORE_DO6;
    case NEO_CORE_DO7: return _NEO_CORE_DO7;

    case NEO_CORE_DI0: return _NEO_CORE_DI0;
    case NEO_CORE_DI1: return _NEO_CORE_DI1;
    case NEO_CORE_DI2: return _NEO_CORE_DI2;
    case NEO_CORE_DI3: return _NEO_CORE_DI3;

    case NEO_CORE_DO0: return _NEO_CORE_DO0;
    case NEO_CORE_DO1: return _NEO_CORE_DO1;
    case NEO_CORE_DO2: return _NEO_CORE_DO2;
    case NEO_CORE_DO3: return _NEO_CORE_DO3;
    default: break;
    }
    return nullptr;
}
 
/* ControllinoNeoPin API */
void setDigitalThreshold(pin_size_t pin, uint32_t threshold) {
    if (getControllinoNeoPin(pin) != nullptr)
        setDigitalThreshold(getControllinoNeoPin(pin), threshold);
}
 
uint32_t getDigitalThreshold(pin_size_t pin) {
    if (getControllinoNeoPin(pin) != nullptr)
        return getDigitalThreshold(getControllinoNeoPin(pin));
    return 0;
}
 
void pinMode(ControllinoNeoPin* pin, PinMode mode)
{
    switch (pin->getType())
    {
    case ControllinoNeoPin::RP2040_PIN:
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
        cy8c95xx_dis_pin_pwm(neo_cy8c95xx, (int)pin->getPin()); // Disable PWM
        cy8c95xx_pin_mode(neo_cy8c95xx, (int)pin->getPin(), dir, drv);
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
    case ControllinoNeoPin::RP2040_PIN:
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
    case ControllinoNeoPin::RP2040_PIN:
        digitalWrite(pin->getPin(), value);
        break;
    case ControllinoNeoPin::CY8C95XX_PIN: // cy8c95xx.h
        if (pin->getMode() == OUTPUT) {
            if (value == HIGH)
                cy8c95xx_pin_mode(neo_cy8c95xx, (int)pin->getPin(), CY8C95XX_GPIO_OUT, CY8C95XX_DRV_STRONG);
            else
                cy8c95xx_pin_mode(neo_cy8c95xx, (int)pin->getPin(), CY8C95XX_GPIO_IN, CY8C95XX_DRV_PULL_DOWN);
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
    case ControllinoNeoPin::RP2040_PIN:
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
    case ControllinoNeoPin::RP2040_PIN:
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
 
/* Trick arduino API to handle NEO pins */ 
extern "C" void __pinMode(pin_size_t pin, PinMode mode);
extern "C" void __digitalWrite(pin_size_t pin, PinStatus val);
extern "C" PinStatus __digitalRead(pin_size_t pin);
 
void pinMode(pin_size_t pin, PinMode mode) {
    if (pin < 32) { // Call Arduino API because is an RP2040 pin
        gpio_set_input_hysteresis_enabled(pin, false); // Disable input histerisys
        __pinMode(pin, mode);
    }
    else if (getControllinoNeoPin(pin) != nullptr) {
        pinMode(getControllinoNeoPin(pin), mode);
    }
    else {
        asm volatile("nop");
    }
}
 
void digitalWrite(pin_size_t pin, PinStatus val) {
    if (pin < 32) {
        __digitalWrite(pin, val);
    }
    else if (pin == SDCARD_SS_PIN) {
        if (val) sd_card_cs_deselect();
        else sd_card_cs_select();
    }
    else if (getControllinoNeoPin(pin) != nullptr) {
        digitalWrite(getControllinoNeoPin(pin), val);
    }
}
 
PinStatus digitalRead(pin_size_t pin) {
    if (pin < 32) {
        return __digitalRead(pin);
    }
    else if (getControllinoNeoPin(pin) != nullptr) {
        return digitalRead(getControllinoNeoPin(pin));
    }
    return LOW;
}
 
#ifndef NATIVE_ENV // Avoid the folowing part on native testing
 
/* Modifications of wiring_analog.cpp on arduino-pico  */
#include <CoreMutex.h>
#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <hardware/clocks.h>
#include <hardware/pll.h>
#include <hardware/adc.h>

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
    else if (getControllinoNeoPin(pin) != nullptr) {
        analogWrite(getControllinoNeoPin(pin), val);
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
    else if (getControllinoNeoPin(pin) != nullptr) {
        return analogRead(getControllinoNeoPin(pin));
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