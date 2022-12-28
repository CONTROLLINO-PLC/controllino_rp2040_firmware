/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "expand6.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t port_slave_addr;
static uint8_t eeprom_slave_addr;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void expand6_cfg_default_setup (expand6_cfg_t* cfg)
{
    // Hardware module
    cfg->i2c = i2c0;

    // Interface settings
    cfg->i2c_speed = 100000;
    cfg->i2c_address = EXPAND6_DEV_ADR_GND;

    // Communication gpio pins
    cfg->sda = 4;
    cfg->scl = 5;
    
    // Additional gpio pins
    cfg->rst = -1;
    cfg->int_pin = 15;
}

EXPAND6_RETVAL expand6_init ( expand6_t *ctx, expand6_cfg_t *cfg )
{
    // Check config
    if ((cfg->i2c != i2c0 && cfg->i2c != i2c1) || !cfg->scl || !cfg->sda)
        return EXPAND6_INIT_ERROR;

    // Init interface pins
    gpio_set_function(cfg->sda, GPIO_FUNC_I2C);
    gpio_set_function(cfg->scl, GPIO_FUNC_I2C);
    // gpio_pull_up(cfg->sda);
    // gpio_pull_up(cfg->scl);
    
    // Set values from cfg
    ctx->i2c = cfg->i2c;
    ctx->rst = cfg->rst;
    ctx->int_pin = cfg->int_pin;
    ctx->slave_address = cfg->i2c_address;

    // Init interface
    i2c_init(ctx->i2c, cfg->i2c_speed);

    // Init reset pin 
    if (ctx->rst >= 0) {
        gpio_init(ctx->rst);
        gpio_set_dir(ctx->rst, GPIO_OUT);
    }

    // Init int pin
    if (ctx->int_pin >= 0) {
        gpio_init(cfg->int_pin);
        gpio_set_dir(cfg->int_pin, GPIO_IN);
    }

    // Base addresses
    port_slave_addr = EXPAND6_M_PORT_BASE_ADR | ctx->slave_address;
    eeprom_slave_addr = EXPAND6_EEPROM_BASE_ADR | ctx->slave_address;

    // Check coms
    uint8_t rxdata;
    if (i2c_read_blocking(ctx->i2c, port_slave_addr, &rxdata, 1, false) < 0)
        return EXPAND6_INIT_ERROR;

    return EXPAND6_OK;
}

void expand6_generic_write ( expand6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_write_blocking(ctx->i2c, ctx->slave_address, tx_buf, len + 1, false);
}

void expand6_generic_read ( expand6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_write_blocking(ctx->i2c, ctx->slave_address, &reg, 1, false);
    i2c_read_blocking(ctx->i2c, ctx->slave_address, data_buf, len, false);
}

// Write the byte of data function
void expand6_write_byte ( expand6_t *ctx, uint8_t reg_adr, uint8_t wr_data )
{
    ctx->slave_address = port_slave_addr;
    expand6_generic_write( ctx, reg_adr, &wr_data, 1 );
}

// Read the byte of data function
uint8_t expand6_read_byte ( expand6_t *ctx, uint8_t reg_adr )
{
    uint8_t result;

    ctx->slave_address = port_slave_addr;
    expand6_generic_read( ctx, reg_adr, &result, 1 );

    return result;
}

void expand6_write_port_exp ( expand6_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 255 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = buf[ cnt ];
    }

    ctx->slave_address = port_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_address, tx_buf, len + 1, false);
}

void expand6_read_port_exp ( expand6_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len )
{
    ctx->slave_address = port_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_address, &reg, 1, false);
    i2c_read_blocking(ctx->i2c, ctx->slave_address, buf, len, false);
}

void expand6_send_eeprom_cmd ( expand6_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = EXPAND6_REG_CMD_ADR;
    tx_buf[ 1 ] = cmd;

    ctx->slave_address = port_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_address, tx_buf, 2, false);
}

void expand6_write_eeprom ( expand6_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 255 ];
    uint8_t cnt;

    tx_buf[ 1 ] = (uint8_t)( mem_adr & 0x00FF );
    tx_buf[ 0 ] = (uint8_t)( ( mem_adr >> 8 ) & 0x00FF );

    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 2 ] = buf[ cnt ];
    }

    ctx->slave_address = eeprom_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_address, tx_buf, len + 2, false);
}

void expand6_read_eeprom ( expand6_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 1 ] = (uint8_t)( mem_adr & 0x00FF );
    tx_buf[0] = (uint8_t)((mem_adr >> 8) & 0x00FF);

    ctx->slave_address = eeprom_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_address, tx_buf, 2, false);
    i2c_read_blocking(ctx->i2c, ctx->slave_address, buf, len, false);
}

// Read bit
uint8_t expand6_read_bit ( expand6_t *ctx, uint8_t reg_adr, uint8_t bit_num )
{
    uint8_t bit_chk;
    uint8_t res;

    bit_chk = expand6_read_byte( ctx, reg_adr );
    res = bit_chk & ( 1 << bit_num );

    return res;
}

void expand6_write_bit ( expand6_t *ctx, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val )
{
    uint8_t bit_chk;

    bit_chk = expand6_read_byte( ctx, reg_adr );
    bit_chk = ( pin_val != 0 ) ? ( bit_chk | ( 1 << bit_num ) ) : ( bit_chk & ~( 1 << bit_num ) );

    expand6_write_byte( ctx, reg_adr, bit_chk );
}

// Get a single INPUT pin's logic level
uint8_t expand6_read_pin ( expand6_t *ctx, uint16_t pin, uint8_t inv )
{
    uint8_t buf;
    
    if ( inv == 0x01 )
    {
        expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
        expand6_write_byte( ctx, EXPAND6_REG_INV_ADR, ( pin % 8 ) );
    }
    
    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand6_write_byte( ctx, EXPAND6_REG_PORT_DIR_ADR, 0xFF );
    
    buf = expand6_read_bit( ctx, ( EXPAND6_REG_IN_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}

// Get all pin logic levels from one port
uint8_t expand6_read_port ( expand6_t *ctx, uint8_t port, uint8_t inv )
{
    uint8_t buf;
    
    if ( inv == 0x01 )
    {
        expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, port );
        expand6_write_byte( ctx, EXPAND6_REG_INV_ADR, 0xFF );
    }
    
    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, port );
    expand6_write_byte( ctx, EXPAND6_REG_PORT_DIR_ADR, 0xFF );

    buf = expand6_read_byte( ctx, EXPAND6_REG_IN_PORT0_ADR + port );

    return buf;
}

// Get a single OUTPUT pin's setting
uint8_t expand6_get_pin_out_lvl ( expand6_t *ctx, uint16_t pin )
{
    uint8_t buf;
    
    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand6_write_byte( ctx, EXPAND6_REG_PORT_DIR_ADR, 0xFF );

    buf = expand6_read_bit( ctx, ( EXPAND6_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}

// Get all pin output settings from one port
uint8_t expand6_get_port_out_lvl ( expand6_t *ctx, uint8_t port )
{
    uint8_t buf;
    
    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, port );
    expand6_write_byte( ctx, EXPAND6_REG_PORT_DIR_ADR, 0xFF );

    buf = expand6_read_byte ( ctx, EXPAND6_REG_OUT_PORT0_ADR + port );

    return buf;
}

// Set a single OUTPUT pin's logic level
void expand6_write_pin ( expand6_t *ctx, uint16_t pin, uint8_t pin_val )
{
    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand6_write_byte( ctx, EXPAND6_REG_PORT_DIR_ADR, 0x00 );

    expand6_write_bit( ctx, ( EXPAND6_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ), pin_val );
}

// Set all OUTPUT pins' logic levels in one port
void expand6_write_port ( expand6_t *ctx, uint8_t port, uint8_t value )
{
    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, port );
    expand6_write_byte( ctx, EXPAND6_REG_PORT_DIR_ADR, 0xFF );

    expand6_write_byte( ctx, ( EXPAND6_REG_OUT_PORT0_ADR + port ), value );
}

// Select a PWM pin output pin
void expand6_sel_pwm_pin ( expand6_t *ctx, uint16_t pin, uint8_t pwm_en )
{
    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand6_write_byte( ctx, EXPAND6_REG_PORT_DIR_ADR, 0x00 );

    expand6_write_bit( ctx, ( EXPAND6_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ), pwm_en );

    expand6_write_byte( ctx, EXPAND6_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand6_write_byte( ctx, EXPAND6_REG_SEL_PWM_OUT_ADR, ( pwm_en << ( pin % 8 ) ) );
}

// PWM Configuration
void expand6_pwm_cfg ( expand6_t *ctx, expand6_pwm_cfg_t pwm_cfg, float *duty_cyc, float *freq )
{
    uint8_t buf[ 5 ];
    
    buf[ 0 ] = pwm_cfg.pwm_sel;
    buf[ 1 ] = pwm_cfg.clk_src;
    buf[ 2 ] = pwm_cfg.period;
    buf[ 3 ] = pwm_cfg.pulse_wid;
    buf[ 4 ] = pwm_cfg.devider;
    
    if( buf[ 3 ] >= buf[ 2 ] )
    {
        buf[ 3 ] = ( buf[ 2 ] - 1 );
    }

    expand6_write_byte( ctx, EXPAND6_REG_PWM_SEL_ADR, buf[ 0 ] );
    expand6_write_byte( ctx, EXPAND6_REG_CFG_PWM_ADR, buf[ 1 ] );
    expand6_write_byte( ctx, EXPAND6_REG_PERIOD_PWM_ADR, buf[ 2 ] );
    expand6_write_byte( ctx, EXPAND6_REG_PULSE_WIDTH_PWM_ADR, buf[ 3 ] );
    expand6_write_byte( ctx, EXPAND6_REG_DIVIDER_ADR, buf[ 4 ] );
    
    *duty_cyc = (float)buf[ 3 ] / (float)buf[ 2 ];
    *freq = 93750.0 / (float)buf[ 4 ];
}

// Enable Register Configuration
void expand6_eeprom_enable ( expand6_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = 0x43;
    tx_buf[ 1 ] = 0x4D;
    tx_buf[ 2 ] = 0x53;
    tx_buf[ 3 ] = cmd;

    expand6_write_port_exp( ctx, EXPAND6_REG_EEPROM_ADR, tx_buf, 4 );
}

// Reset
void expand6_reset ( expand6_t *ctx )
{
    if (ctx->rst >= 0) {
        gpio_put(ctx->rst, 1);
        sleep_ms(1000);
        gpio_put(ctx->rst, 0);
        sleep_ms(1000);
    }
}

// Check interrupt
uint8_t expand6_check_int(expand6_t* ctx)
{
    if (ctx->int_pin >= 0) {
        return gpio_get(ctx->int_pin);
    }
    
    return 0;
}

// ------------------------------------------------------------------------- END

