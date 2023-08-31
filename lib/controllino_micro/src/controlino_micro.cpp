/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */

#include "controllino_wiring.h"
#include "controllino_diag.h"

/* Peripherals interfaces */
cy8c9520_t* dev_cy8c9520;
mcp3564_t* dev_mcp3564;
ad5664_t* dev_ad5664;
bts71220_t* dev_bts71220;
wsen_temp_t* dev_wsen_temp;
adg728_t* dev_adg728;

/* Other pins used on internal components */
#ifndef _CY8C9520_INT_PIN
#define _CY8C9520_INT_PIN           (4u)
#endif
#ifndef _MCP3564_INT_PIN
#define _MCP3564_INT_PIN            (13u)
#endif   
#ifndef _MCP3564_CS_PIN
#define _MCP3564_CS_PIN             (14u)
#endif
#ifndef _W5500_INT_PIN
#define _W5500_INT_PIN              (15u)
#endif

/**
 * Arduino-pico variant initialization
 * Note: This function will be called on every boot before setup()
 */  
void initVariant()
{
    // WSEN temperature sensor
    dev_wsen_temp = (wsen_temp_t*)malloc(sizeof(wsen_temp_t));
    wsen_temp_cfg_t wsen_temp_cfg;
    wsen_temp_set_default_cfg(&wsen_temp_cfg);
    wsen_temp_init(dev_wsen_temp, &wsen_temp_cfg);

    // Analog multiplexer
    dev_adg728 = (adg728_t*)malloc(sizeof(adg728_t));
    adg728_cfg_t adg728_cfg;
    adg728_set_default_cfg(&adg728_cfg);
    adg728_init(dev_adg728, &adg728_cfg);

    // Port expander 
    dev_cy8c9520 = (cy8c9520_t*)malloc(sizeof(cy8c9520_t));
    cy8c9520_cfg_t cy8c9520_cfg;
    cy8c9520_set_default_cfg(&cy8c9520_cfg);
    cy8c9520_init(dev_cy8c9520, &cy8c9520_cfg);

    // ADC analog inputs
    dev_mcp3564 = (mcp3564_t*)malloc(sizeof(mcp3564_t));
    pinMode(_MCP3564_CS_PIN, OUTPUT);
    mcp3564_cfg_t mcp3564_cfg;
    mcp3564_set_default_cfg(&mcp3564_cfg);
    mcp3564_init(dev_mcp3564, &mcp3564_cfg);

    // Set default resolution for RP2040 ADC to 12 bits
    analogReadResolution(12);
}
 
/* SPI chip select management */
void mcp3564_cs_select(int cs_pin) {
    digitalWrite(_MCP3564_CS_PIN, LOW);
}
void mcp3564_cs_deselect(int cs_pin) {
    digitalWrite(_MCP3564_CS_PIN, HIGH);
}
 
/* These are not used but need to be defined */
void ad5664_cs_select(int cs_pin) {}
void ad5664_cs_deselect(int cs_pin) {}
void bts71220_cs_select(int cs_pin) {}
void bts71220_cs_deselect(int cs_pin) {}

/* Pin definitions for ControllinoRp2040Pin API */
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI0 = new ControllinoRp2040Pin(MCP3564_CH_CH0, ControllinoRp2040Pin::MCP3564_PIN);
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI1 = new ControllinoRp2040Pin(MCP3564_CH_CH1, ControllinoRp2040Pin::MCP3564_PIN);
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI2 = new ControllinoRp2040Pin(MCP3564_CH_CH2, ControllinoRp2040Pin::MCP3564_PIN);
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI3 = new ControllinoRp2040Pin(MCP3564_CH_CH3, ControllinoRp2040Pin::MCP3564_PIN);
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI4 = new ControllinoRp2040Pin(MCP3564_CH_CH4, ControllinoRp2040Pin::MCP3564_PIN);
extern ControllinoRp2040Pin* _CONTROLLINO_MICRO_AI5 = new ControllinoRp2040Pin(MCP3564_CH_CH5, ControllinoRp2040Pin::MCP3564_PIN);
 
/* Returns ControllinoRp2040Pin API pin or nullptr */
ControllinoRp2040Pin* getControllinoRp2040Pin(int pin)
{
    switch (pin)
    {
    case CONTROLLINO_MICRO_AI0: return _CONTROLLINO_MICRO_AI0;
    case CONTROLLINO_MICRO_AI1: return _CONTROLLINO_MICRO_AI1;
    case CONTROLLINO_MICRO_AI2: return _CONTROLLINO_MICRO_AI2;
    case CONTROLLINO_MICRO_AI3: return _CONTROLLINO_MICRO_AI3;
    case CONTROLLINO_MICRO_AI4: return _CONTROLLINO_MICRO_AI4;
    case CONTROLLINO_MICRO_AI5: return _CONTROLLINO_MICRO_AI5;

    default: break;
    }
    return nullptr;
}
 
/* Measure power suply voltage in millivolts */
#define POWER_SUPLY_CONVERSION_RATIO (float)(24000.0F / 7362700.0F) /* 24000 mV(24 V) for 7362700 on the ADC */
ControllinoRp2040Pin* POWER_SUPLY_AI_PIN = new ControllinoRp2040Pin(MCP3564_CH_CH6, ControllinoRp2040Pin::MCP3564_PIN); /* Power monitoring is connected to MCP3564_CH_CH6 */
int readVoltageSuply(void)
{
    float mV = ((float)analogRead(POWER_SUPLY_AI_PIN)) * POWER_SUPLY_CONVERSION_RATIO;
    return (int)mV;
}
 
/* Measure current board temperature in °C using WSEN temperature sensor */
float readBoardTemperature(void)
{
    float celsius = 0;
    wsen_temp_get_celsius(dev_wsen_temp, &celsius);
    return celsius;
}

/* Posible interrupt sources from port expander represented by their GPIO */
#define _CY8C9520_INT_TEMP_SENSOR   CY8C9520_GPIO_4
#define _CY8C9520_INT_NFAULT_DO0    CY8C9520_GPIO_8
#define _CY8C9520_INT_NFAULT_DO1    CY8C9520_GPIO_9
#define _CY8C9520_INT_NFAULT_DO2    CY8C9520_GPIO_10
#define _CY8C9520_INT_NFAULT_DO3    CY8C9520_GPIO_11
#define _CY8C9520_INT_NFAULT_DO4    CY8C9520_GPIO_12
#define _CY8C9520_INT_NFAULT_DO5    CY8C9520_GPIO_13
#define _CY8C9520_INT_NFAULT_DO6    CY8C9520_GPIO_14
#define _CY8C9520_INT_NFAULT_DO7    CY8C9520_GPIO_15

/* Callbacks definition */
void (*_CY8C9520_INT_TEMP_SENSOR_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO0_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO1_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO2_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO3_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO4_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO5_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO6_cb)(void) = nullptr;
void (*_CY8C9520_INT_NFAULT_DO7_cb)(void) = nullptr;

/* Interrupt handler to find source of interrupt and call user cb */
void _CY8C9520_INT_PIN_int_handler(void)
{
    // Disable interrupts to avoid reentrancy
    noInterrupts();

    // Read interrupt status from port expander to find source and clear interrupts
    uint8_t rxdata[2];
    cy8c9520_generic_read(dev_cy8c9520, CY8C9520_REG_INT_STAT_PORT0, &rxdata[0], 2);

    // Check if interrupt is from temperature sensor
    if (rxdata[0]) {
        if (((rxdata[0] >> (_CY8C9520_INT_TEMP_SENSOR % 8)) & 0x01) && _CY8C9520_INT_TEMP_SENSOR_cb) {
            // Read status to clear temperature sensor interrupt
            wsen_temp_status_t temp_status;
            wsen_temp_get_status(dev_wsen_temp, &temp_status);
            (*_CY8C9520_INT_TEMP_SENSOR_cb)();
        }
    }

    // Check if interrupt is from digital output overcurrent
    if (rxdata[1]) {
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO0 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO0_cb) {
            (*_CY8C9520_INT_NFAULT_DO0_cb)();
        }
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO1 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO1_cb) {
            (*_CY8C9520_INT_NFAULT_DO1_cb)();
        }
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO2 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO2_cb) {
            (*_CY8C9520_INT_NFAULT_DO2_cb)();
        }
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO3 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO3_cb) {
            (*_CY8C9520_INT_NFAULT_DO3_cb)();
        }
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO4 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO4_cb) {
            (*_CY8C9520_INT_NFAULT_DO4_cb)();
        }
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO5 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO5_cb) {
            (*_CY8C9520_INT_NFAULT_DO5_cb)();
        }
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO6 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO6_cb) {
            (*_CY8C9520_INT_NFAULT_DO6_cb)();
        }
        if (((rxdata[1] >> (_CY8C9520_INT_NFAULT_DO7 % 8)) & 0x01) && _CY8C9520_INT_NFAULT_DO7_cb) {
            (*_CY8C9520_INT_NFAULT_DO7_cb)();
        }
    }

    // Reenable interrupts
    interrupts();
}
 
/* Enable port expander interrupt on pin _CY8C9520_INT_PIN */
void _en_CY8C9520_INT_PIN_int(void)
{
    pinMode(_CY8C9520_INT_PIN, INPUT);
    attachInterrupt(_CY8C9520_INT_PIN, &_CY8C9520_INT_PIN_int_handler, RISING);
}
 
/* Enable temperature sensor interrupt */
void enableTempSensorInt(float lowLim, float highLim, void(*cb)(void))
{
    if ((lowLim < -39.68F) ||
        (highLim < -39.68F) ||
        (lowLim > 122.88F) ||
        (highLim > 122.88F) ||
        (lowLim > highLim)) return; // Invalid limits
    
    // Set callback and enable interrupt
    _CY8C9520_INT_TEMP_SENSOR_cb = cb;
    cy8c9520_en_pin_int(dev_cy8c9520, _CY8C9520_INT_TEMP_SENSOR);
    _en_CY8C9520_INT_PIN_int();

    // Set temperature limits
    wsen_temp_set_low_lim(dev_wsen_temp, lowLim);
    wsen_temp_set_high_lim(dev_wsen_temp, highLim);
}
 
/* Disable temperature sensor interrupt */
void disableTempSensorInt(void)
{
    _CY8C9520_INT_TEMP_SENSOR_cb = nullptr;
    cy8c9520_dis_pin_int(dev_cy8c9520, _CY8C9520_INT_TEMP_SENSOR);
}

/* Get CY8C9520_INT_NFAULT pin from do_pin returns -1 if pin is incorrect */
int _get_DO_CY8C9520_INT_NFAULT(uint8_t do_pin)
{
    switch (do_pin)
    {
        case CONTROLLINO_MICRO_DO0: return _CY8C9520_INT_NFAULT_DO0;
        case CONTROLLINO_MICRO_DO1: return _CY8C9520_INT_NFAULT_DO1;
        case CONTROLLINO_MICRO_DO2: return _CY8C9520_INT_NFAULT_DO2;
        case CONTROLLINO_MICRO_DO3: return _CY8C9520_INT_NFAULT_DO3;
        case CONTROLLINO_MICRO_DO4: return _CY8C9520_INT_NFAULT_DO4;
        case CONTROLLINO_MICRO_DO5: return _CY8C9520_INT_NFAULT_DO5;
        case CONTROLLINO_MICRO_DO6: return _CY8C9520_INT_NFAULT_DO6;
        case CONTROLLINO_MICRO_DO7: return _CY8C9520_INT_NFAULT_DO7;
        default: break;
    }
    return -1;
}

/* Set callback for CY8C9520_INT_NFAULT pin */
void _set_DO_CY8C9520_INT_NFAULT_cb(int cy8c9520_gpio, void(*cb)(void))
{
    switch (cy8c9520_gpio)
    {
        case _CY8C9520_INT_NFAULT_DO0: _CY8C9520_INT_NFAULT_DO0_cb = cb; break;
        case _CY8C9520_INT_NFAULT_DO1: _CY8C9520_INT_NFAULT_DO1_cb = cb; break;
        case _CY8C9520_INT_NFAULT_DO2: _CY8C9520_INT_NFAULT_DO2_cb = cb; break;
        case _CY8C9520_INT_NFAULT_DO3: _CY8C9520_INT_NFAULT_DO3_cb = cb; break;
        case _CY8C9520_INT_NFAULT_DO4: _CY8C9520_INT_NFAULT_DO4_cb = cb; break;
        case _CY8C9520_INT_NFAULT_DO5: _CY8C9520_INT_NFAULT_DO5_cb = cb; break;
        case _CY8C9520_INT_NFAULT_DO6: _CY8C9520_INT_NFAULT_DO6_cb = cb; break;
        case _CY8C9520_INT_NFAULT_DO7: _CY8C9520_INT_NFAULT_DO7_cb = cb; break;
        default: break;
    }
}

/* Enable or disable digital output overcurrent interrupt */
void enableOutFaultInt(uint8_t doPin, void(*cb)(void))
{
    int cy8c9520_gpio = _get_DO_CY8C9520_INT_NFAULT(doPin); // Just to have an initial value
    if (cy8c9520_gpio == -1) return; // Invalid pin

    // Set callback
    _set_DO_CY8C9520_INT_NFAULT_cb(cy8c9520_gpio, cb);

    // Enable interrupt
    cy8c9520_en_pin_int(dev_cy8c9520, cy8c9520_gpio);
    _en_CY8C9520_INT_PIN_int();
}

/* Disable digital output overcurrent interrupt */
void disableOutOverloadInt(uint8_t doPin)
{
    int cy8c9520_gpio = _get_DO_CY8C9520_INT_NFAULT(doPin); // Just to have an initial value
    if (cy8c9520_gpio == -1) return; // Invalid pin

    // Set callback to nullptr
    _set_DO_CY8C9520_INT_NFAULT_cb(cy8c9520_gpio, nullptr);

    // Disable interrupt
    cy8c9520_dis_pin_int(dev_cy8c9520, cy8c9520_gpio);
}