/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#include "wiring.h"
#include "diag.h"
 
/* Peripherals interfaces */
cy8c9520_t*     dev_cy8c9520 =  nullptr;
mcp3564_t*      dev_mcp3564 =   nullptr;
ad5664_t*       dev_ad5664 =    nullptr;
wsen_temp_t*    dev_wsen_temp = nullptr;
adg728_t*       dev_adg728 =    nullptr;
mcp4461_t*      dev_mcp4461_0 = nullptr;
mcp4461_t*      dev_mcp4461_1 = nullptr;
 
/* Other pins used on internal components */
extern const uint8_t _CY8C9520_INT_PIN =    (4u);
extern const uint8_t _MCP3564_INT_PIN =     (5u);
extern const uint8_t _MCP3564_CS_PIN =      (6u);
extern const uint8_t _W5500_INT_PIN =       (7u);
 
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

    // Digital potentiometers
    dev_mcp4461_0 = (mcp4461_t*)malloc(sizeof(mcp4461_t));
    dev_mcp4461_1 = (mcp4461_t*)malloc(sizeof(mcp4461_t));
    mcp4461_cfg_t mcp4461_cfg;
    mcp4461_set_default_cfg(&mcp4461_cfg);
    mcp4461_cfg.i2c_addr = MCP4461_DEV_ADDR_1;
    mcp4461_init(dev_mcp4461_0, &mcp4461_cfg);
    mcp4461_cfg.i2c_addr = MCP4461_DEV_ADDR_3;
    mcp4461_init(dev_mcp4461_1, &mcp4461_cfg);

    // Current limit 3A for all digital outputs
    setOutCurrentLim(CONTROLLINO_MICRO_DO0, 3000);
    setOutCurrentLim(CONTROLLINO_MICRO_DO1, 3000);
    setOutCurrentLim(CONTROLLINO_MICRO_DO2, 3000);
    setOutCurrentLim(CONTROLLINO_MICRO_DO3, 3000);
    setOutCurrentLim(CONTROLLINO_MICRO_DO4, 3000);
    setOutCurrentLim(CONTROLLINO_MICRO_DO5, 3000);
    setOutCurrentLim(CONTROLLINO_MICRO_DO6, 3000);
    setOutCurrentLim(CONTROLLINO_MICRO_DO7, 3000);

    // Port expander 
    dev_cy8c9520 = (cy8c9520_t*)malloc(sizeof(cy8c9520_t));
    cy8c9520_cfg_t cy8c9520_cfg;
    cy8c9520_set_default_cfg(&cy8c9520_cfg);
    cy8c9520_init(dev_cy8c9520, &cy8c9520_cfg);

    // ADC analog inputs
    dev_mcp3564 = (mcp3564_t*)malloc(sizeof(mcp3564_t));
    mcp3564_cfg_t mcp3564_cfg;
    mcp3564_set_default_cfg(&mcp3564_cfg);
    mcp3564_cfg.cs_pin = _MCP3564_CS_PIN;
    mcp3564_init(dev_mcp3564, &mcp3564_cfg);

    // Set default resolution for RP2040 ADC to 12 bits
    analogReadResolution(12);
}
 
/* Pin definitions for ControllinoPin API */
ControllinoPin* _CONTROLLINO_MICRO_AI0 = new ControllinoPin(MCP3564_CH_CH0, ControllinoPin::MCP3564_PIN);
ControllinoPin* _CONTROLLINO_MICRO_AI1 = new ControllinoPin(MCP3564_CH_CH1, ControllinoPin::MCP3564_PIN);
ControllinoPin* _CONTROLLINO_MICRO_AI2 = new ControllinoPin(MCP3564_CH_CH2, ControllinoPin::MCP3564_PIN);
ControllinoPin* _CONTROLLINO_MICRO_AI3 = new ControllinoPin(MCP3564_CH_CH3, ControllinoPin::MCP3564_PIN);
ControllinoPin* _CONTROLLINO_MICRO_AI4 = new ControllinoPin(MCP3564_CH_CH4, ControllinoPin::MCP3564_PIN);
ControllinoPin* _CONTROLLINO_MICRO_AI5 = new ControllinoPin(MCP3564_CH_CH5, ControllinoPin::MCP3564_PIN);
// ControllinoPin* _CONTROLLINO_MICRO_DI0 = new ControllinoPin(26u, ControllinoPin::RP2040_PIN);
// ControllinoPin* _CONTROLLINO_MICRO_DI1 = new ControllinoPin(27u, ControllinoPin::RP2040_PIN);
// ControllinoPin* _CONTROLLINO_MICRO_DI2 = new ControllinoPin(28u, ControllinoPin::RP2040_PIN);
// ControllinoPin* _CONTROLLINO_MICRO_DI3 = new ControllinoPin(29u, ControllinoPin::RP2040_PIN);
 

/* Returns ControllinoPin API pin or nullptr */
ControllinoPin* getControllinoPin(int pin)
{
    switch (pin)
    {
    case CONTROLLINO_MICRO_AI0: return _CONTROLLINO_MICRO_AI0;
    case CONTROLLINO_MICRO_AI1: return _CONTROLLINO_MICRO_AI1;
    case CONTROLLINO_MICRO_AI2: return _CONTROLLINO_MICRO_AI2;
    case CONTROLLINO_MICRO_AI3: return _CONTROLLINO_MICRO_AI3;
    case CONTROLLINO_MICRO_AI4: return _CONTROLLINO_MICRO_AI4;
    case CONTROLLINO_MICRO_AI5: return _CONTROLLINO_MICRO_AI5;
    // case CONTROLLINO_MICRO_DI0: return _CONTROLLINO_MICRO_DI0;
    // case CONTROLLINO_MICRO_DI1: return _CONTROLLINO_MICRO_DI1;
    // case CONTROLLINO_MICRO_DI2: return _CONTROLLINO_MICRO_DI2;
    // case CONTROLLINO_MICRO_DI3: return _CONTROLLINO_MICRO_DI3;
    default: break;
    }
    return nullptr;
}
 
/* Measure power suply voltage in millivolts */
#define POWER_SUPLY_CONVERSION_RATIO (24000.0F / 7362700.0F) /* 24000 mV(24 V) for 7362700 on the ADC */
int readVoltageSuply(void)
{
    // Power suply monitoring is connected to ADC channel 6
    // 500 us delay for 256 over sample rate
    uint32_t adcValue;
    mcp3564_read_adc_mux(dev_mcp3564, &adcValue, MCP3564_MUX_VIN_POS_CH6, MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS, 500);
    return (float)adcValue * POWER_SUPLY_CONVERSION_RATIO; // Convert to mV
}
 
/* Measure current board temperature in °C using WSEN temperature sensor */
float readBoardTemperature(void)
{
    float celsius = 0;
    wsen_temp_get_celsius(dev_wsen_temp, &celsius);
    return celsius;
}
 
/* Posible interrupt sources from port expander represented by their GPIO */
extern const uint8_t _CY8C9520_INT_NFAULT_DO0 = CY8C9520_GPIO_8;
extern const uint8_t _CY8C9520_INT_NFAULT_DO1 = CY8C9520_GPIO_9;
extern const uint8_t _CY8C9520_INT_NFAULT_DO2 = CY8C9520_GPIO_10;
extern const uint8_t _CY8C9520_INT_NFAULT_DO3 = CY8C9520_GPIO_11;
extern const uint8_t _CY8C9520_INT_NFAULT_DO4 = CY8C9520_GPIO_12;
extern const uint8_t _CY8C9520_INT_NFAULT_DO5 = CY8C9520_GPIO_13;
extern const uint8_t _CY8C9520_INT_NFAULT_DO6 = CY8C9520_GPIO_14;
extern const uint8_t _CY8C9520_INT_NFAULT_DO7 = CY8C9520_GPIO_15;
extern const uint8_t _CY8C9520_INT_TEMP_SENSOR = CY8C9520_GPIO_16;

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
void _cy8c9520_int_pin_handler(void)
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
void _en_cy8c9520_int_pin(void)
{
    pinMode(_CY8C9520_INT_PIN, INPUT);
    attachInterrupt(_CY8C9520_INT_PIN, &_cy8c9520_int_pin_handler, RISING);
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
    _en_cy8c9520_int_pin();

    // Set temperature limits
    wsen_temp_set_low_lim(dev_wsen_temp, lowLim);
    wsen_temp_set_high_lim(dev_wsen_temp, highLim);
}
 
/* Disable temperature sensor interrupt */
void disableTempSensorInt(void)
{
    // Set callback to nullptr and disable port expander interrupt
    _CY8C9520_INT_TEMP_SENSOR_cb = nullptr;
    cy8c9520_dis_pin_int(dev_cy8c9520, _CY8C9520_INT_TEMP_SENSOR);

    // Disable temp sensor interrupt
    wsen_temp_dis_int(dev_wsen_temp);
}
 
/* Get CY8C9520_INT_NFAULT pin from do_pin returns -1 if pin is incorrect */
int _get_do_cy8c9520_int_nfault(uint8_t doPin)
{
    switch (doPin)
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
void _set_do_cy8c9520_int_nfault_cb(int cy8c9520_gpio, void(*cb)(void))
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
 
/* Enable digital output fault interrupt */
void enableOutFaultInt(uint8_t doPin, void(*cb)(void))
{
    int cy8c9520_gpio = _get_do_cy8c9520_int_nfault(doPin);
    if (cy8c9520_gpio == -1) return; // Invalid pin

    // Set callback
    _set_do_cy8c9520_int_nfault_cb(cy8c9520_gpio, cb);

    // Enable interrupt
    cy8c9520_en_pin_int(dev_cy8c9520, cy8c9520_gpio);
    _en_cy8c9520_int_pin();
}
 
/* Disable digital output fault interrupt */
void disableOutFaultInt(uint8_t doPin)
{
    int cy8c9520_gpio = _get_do_cy8c9520_int_nfault(doPin);
    if (cy8c9520_gpio == -1) return; // Invalid pin

    // Set callback to nullptr
    _set_do_cy8c9520_int_nfault_cb(cy8c9520_gpio, nullptr);

    // Disable interrupt
    cy8c9520_dis_pin_int(dev_cy8c9520, cy8c9520_gpio);
}
 
/* Current limit and measurement */
 
/* Resistors that set the current limit */
uint16_t _CONTROLLINO_MICRO_DO0_R = 0;
uint16_t _CONTROLLINO_MICRO_DO1_R = 0;
uint16_t _CONTROLLINO_MICRO_DO2_R = 0;
uint16_t _CONTROLLINO_MICRO_DO3_R = 0;
uint16_t _CONTROLLINO_MICRO_DO4_R = 0;
uint16_t _CONTROLLINO_MICRO_DO5_R = 0;
uint16_t _CONTROLLINO_MICRO_DO6_R = 0;
uint16_t _CONTROLLINO_MICRO_DO7_R = 0;
 
/*  Set output current limit in milliamps */
void setOutCurrentLim(uint8_t doPin, uint16_t currentLim)
{
    // Invalid limit should be between 500 and 3000 mA
    if (currentLim > 3000 || currentLim < 500) return;

    // There are two resistors in parallel, one is 50k and the other is variable plus 5k in series
    // The variable resistor is a potentiometer with 256 steps
    // See MP6610GS datasheet limit is 1.5V current is 100uA/A
    float current = float(currentLim) / 1000.0F;
    float parallel = (1.5F / (current / 10000.0F)) - 5000.0F;
    float r = parallel * 50000.0F / (50000.0F - parallel);

    uint16_t res_val = (uint16_t)parallel + 5000;
    uint16_t pot_val = map((uint16_t)r, 0, 50000, 0, 256);

    // Set resistor value and potentiometer value
    switch (doPin)
    {
    case CONTROLLINO_MICRO_DO0:
        _CONTROLLINO_MICRO_DO0_R = res_val;
        mcp4461_write_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_0, pot_val);
        break;
    case CONTROLLINO_MICRO_DO1:
        _CONTROLLINO_MICRO_DO1_R = res_val;
        mcp4461_write_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_1, pot_val);
        break;
    case CONTROLLINO_MICRO_DO2:
        _CONTROLLINO_MICRO_DO2_R = res_val;
        mcp4461_write_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_2, pot_val);
        break;
    case CONTROLLINO_MICRO_DO3:
        _CONTROLLINO_MICRO_DO3_R = res_val;
        mcp4461_write_reg(dev_mcp4461_0, MCP4461_REG_V_WIPER_3, pot_val);
        break;
    case CONTROLLINO_MICRO_DO4:
        _CONTROLLINO_MICRO_DO4_R = res_val;
        mcp4461_write_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_0, pot_val);
        break;
    case CONTROLLINO_MICRO_DO5:
        _CONTROLLINO_MICRO_DO5_R = res_val;
        mcp4461_write_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_1, pot_val);
        break;
    case CONTROLLINO_MICRO_DO6:
        _CONTROLLINO_MICRO_DO6_R = res_val;
        mcp4461_write_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_2, pot_val);
        break;
    case CONTROLLINO_MICRO_DO7:
        _CONTROLLINO_MICRO_DO7_R = res_val;
        mcp4461_write_reg(dev_mcp4461_1, MCP4461_REG_V_WIPER_3, pot_val);
        break;
    default:
        // Invalid pin
        break;
    }
}
 
/* Get output current limit in milliamps */
uint16_t getOutCurrentLim(uint8_t doPin)
{
    switch (doPin)
    {
    case CONTROLLINO_MICRO_DO0: return (35000 - _CONTROLLINO_MICRO_DO0_R) / 10;
    case CONTROLLINO_MICRO_DO1: return (35000 - _CONTROLLINO_MICRO_DO1_R) / 10;
    case CONTROLLINO_MICRO_DO2: return (35000 - _CONTROLLINO_MICRO_DO2_R) / 10;
    case CONTROLLINO_MICRO_DO3: return (35000 - _CONTROLLINO_MICRO_DO3_R) / 10;
    case CONTROLLINO_MICRO_DO4: return (35000 - _CONTROLLINO_MICRO_DO4_R) / 10;
    case CONTROLLINO_MICRO_DO5: return (35000 - _CONTROLLINO_MICRO_DO5_R) / 10;
    case CONTROLLINO_MICRO_DO6: return (35000 - _CONTROLLINO_MICRO_DO6_R) / 10;
    case CONTROLLINO_MICRO_DO7: return (35000 - _CONTROLLINO_MICRO_DO7_R) / 10;
    default: break; // Invalid pin
    }
    return 0;
}
 
/* Measure output current in milliamps */
uint16_t getOutCurrent(uint8_t doPin)
{
    float mA;
    float mV;
    uint16_t r = 0;

    // Set channel on analog multiplexer and get resistor for calculation
    switch (doPin)
    {
    case CONTROLLINO_MICRO_DO0:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_0);
        r = _CONTROLLINO_MICRO_DO0_R;
        break;
    case CONTROLLINO_MICRO_DO1:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_1);
        r = _CONTROLLINO_MICRO_DO1_R;
        break;
    case CONTROLLINO_MICRO_DO2:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_2);
        r = _CONTROLLINO_MICRO_DO2_R;
        break;
    case CONTROLLINO_MICRO_DO3:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_3);
        r = _CONTROLLINO_MICRO_DO3_R;
        break;
    case CONTROLLINO_MICRO_DO4:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_4);
        r = _CONTROLLINO_MICRO_DO4_R;
        break;
    case CONTROLLINO_MICRO_DO5:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_5);
        r = _CONTROLLINO_MICRO_DO5_R;
        break;
    case CONTROLLINO_MICRO_DO6:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_6);
        r = _CONTROLLINO_MICRO_DO6_R;
        break;
    case CONTROLLINO_MICRO_DO7:
        adg728_set_channel(dev_adg728, ADG728_CHANNEL_7);
        r = _CONTROLLINO_MICRO_DO7_R;
        break;
    default: break; // Invalid pin
    }

    // Read ADC value and calculate
    if (r != 0)
    {
        uint32_t adcValue;
        // Default gain is x2 needs to be changed to x1
        mcp3564_set_gain(dev_mcp3564, MCP3564_GAIN_X_1);
        // 500 us delay for 256 over sample rate
        mcp3564_read_adc_mux(dev_mcp3564, &adcValue, MCP3564_MUX_VIN_POS_CH7, MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS, 500);
        // Set gain back to x2
        mcp3564_set_gain(dev_mcp3564, MCP3564_GAIN_X_2);

        /* 2.4V for 23 bits on the ADC */
        mV = (float)adcValue * 2.4F / (float)MCP3564_RES_23_BITS * 1000.0F;

        // Current need to be converted from uA to mA
        mA = mV * 10000.0F / (float)r;
        return (uint16_t)mA;
    }

    // Invalid pin
    return 0;
}
 
/* Enable outputs pins connected to port expander GPIOs */
extern const uint8_t _CY8C9520_EN_DO0 = CY8C9520_GPIO_0;
extern const uint8_t _CY8C9520_EN_DO1 = CY8C9520_GPIO_1;
extern const uint8_t _CY8C9520_EN_DO2 = CY8C9520_GPIO_2;
extern const uint8_t _CY8C9520_EN_DO3 = CY8C9520_GPIO_3;
extern const uint8_t _CY8C9520_EN_DO4 = CY8C9520_GPIO_4;
extern const uint8_t _CY8C9520_EN_DO5 = CY8C9520_GPIO_5;
extern const uint8_t _CY8C9520_EN_DO6 = CY8C9520_GPIO_6;
extern const uint8_t _CY8C9520_EN_DO7 = CY8C9520_GPIO_7;
 
/* Get CY8C9520_EN_DO pin from do_pin returns -1 if pin is incorrect */
int _get_cy8c9520_en_do(uint8_t doPin)
{
    switch (doPin)
    {
    case CONTROLLINO_MICRO_DO0: return _CY8C9520_EN_DO0;
    case CONTROLLINO_MICRO_DO1: return _CY8C9520_EN_DO1;
    case CONTROLLINO_MICRO_DO2: return _CY8C9520_EN_DO2;
    case CONTROLLINO_MICRO_DO3: return _CY8C9520_EN_DO3;
    case CONTROLLINO_MICRO_DO4: return _CY8C9520_EN_DO4;
    case CONTROLLINO_MICRO_DO5: return _CY8C9520_EN_DO5;
    case CONTROLLINO_MICRO_DO6: return _CY8C9520_EN_DO6;
    case CONTROLLINO_MICRO_DO7: return _CY8C9520_EN_DO7;
    default: break;
    }
    return -1;
}

/* Enable digital output doPin -> CONTROLLINO_MICRO_DO0...D07 */
void enableOut(uint8_t doPin)
{
    int cy8c9520_gpio = _get_cy8c9520_en_do(doPin);
    if (cy8c9520_gpio == -1) return; // Invalid pin
    // Pull up on port expander 
    cy8c9520_pin_mode(dev_cy8c9520, cy8c9520_gpio, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_UP);
}

/* Disable digital output doPin -> CONTROLLINO_MICRO_DO0...D07 */
void disableOut(uint8_t doPin)
{
    int cy8c9520_gpio = _get_cy8c9520_en_do(doPin);
    if (cy8c9520_gpio == -1) return; // Invalid pin
    // Pull down on port expander 
    cy8c9520_pin_mode(dev_cy8c9520, cy8c9520_gpio, CY8C9520_GPIO_IN, CY8C9520_DRV_PULL_DOWN);
}
