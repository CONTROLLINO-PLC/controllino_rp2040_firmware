#include "cy8C95xx.h"

// ------------------------------------------------------------------ VARIABLES
static uint8_t port_slave_addr;
static uint8_t eeprom_slave_addr;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void cy8C95xx_cfg_default_setup(cy8C95xx_cfg_t* cfg)
{
    // Hardware module
    cfg->i2c = i2c0;

    // Interface settings
    cfg->i2c_speed = 100000;
    cfg->i2c_addr = CY8C95XX_DEV_ADR_GND;

    // Communication gpio pins
    cfg->sda_pin = 4;
    cfg->scl_pin = 5;
    
    // Additional gpio pins
    cfg->rst_pin = -1;
    cfg->int_pin = 15;
}

uint cy8C95xx_init(cy8C95xx_t *ctx, cy8C95xx_cfg_t *cfg)
{
    // Check config
    if ((cfg->i2c != i2c0 && cfg->i2c != i2c1) || !cfg->scl_pin || !cfg->sda_pin)
        return CY8C95XX_INIT_ERROR;

    // Init interface pins
    gpio_set_function(cfg->sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(cfg->scl_pin, GPIO_FUNC_I2C);
    // gpio_pull_up(cfg->sda_pin);
    // gpio_pull_up(cfg->scl_pin);
    
    // Set values from cfg
    ctx->i2c = cfg->i2c;
    ctx->rst_pin = cfg->rst_pin;
    ctx->int_pin = cfg->int_pin;
    ctx->slave_addr = cfg->i2c_addr;

    // Init interface
    i2c_init(ctx->i2c, cfg->i2c_speed);

    // Init reset pin 
    if (ctx->rst_pin >= 0) {
        gpio_init(ctx->rst_pin);
        gpio_set_dir(ctx->rst_pin, GPIO_OUT);
    }

    // Init int pin
    if (ctx->int_pin >= 0) {
        gpio_init(cfg->int_pin);
        gpio_set_dir(cfg->int_pin, GPIO_IN);
    }

    // Base addresses
    port_slave_addr = CY8C95XX_M_PORT_BASE_ADR | ctx->slave_addr;
    eeprom_slave_addr = CY8C95XX_EEPROM_BASE_ADR | ctx->slave_addr;

    // Check coms
    uint8_t rxdata;
    if (i2c_read_blocking(ctx->i2c, port_slave_addr, &rxdata, 1, false) < 0)
        return CY8C95XX_INIT_ERROR;

    return CY8C95XX_OK;
}

void cy8C95xx_generic_write ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_write_blocking(ctx->i2c, ctx->slave_addr, tx_buf, len + 1, false);
}

void cy8C95xx_generic_read ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_write_blocking(ctx->i2c, ctx->slave_addr, &reg, 1, false);
    i2c_read_blocking(ctx->i2c, ctx->slave_addr, data_buf, len, false);
}

// Write the byte of data function
void cy8C95xx_write_byte ( cy8C95xx_t *ctx, uint8_t reg_adr, uint8_t wr_data )
{
    ctx->slave_addr = port_slave_addr;
    cy8C95xx_generic_write( ctx, reg_adr, &wr_data, 1 );
}

// Read the byte of data function
uint8_t cy8C95xx_read_byte ( cy8C95xx_t *ctx, uint8_t reg_adr )
{
    uint8_t result;

    ctx->slave_addr = port_slave_addr;
    cy8C95xx_generic_read( ctx, reg_adr, &result, 1 );

    return result;
}

void cy8C95xx_write_port_exp ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 255 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = buf[ cnt ];
    }

    ctx->slave_addr = port_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_addr, tx_buf, len + 1, false);
}

void cy8C95xx_read_port_exp ( cy8C95xx_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len )
{
    ctx->slave_addr = port_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_addr, &reg, 1, false);
    i2c_read_blocking(ctx->i2c, ctx->slave_addr, buf, len, false);
}

void cy8C95xx_send_eeprom_cmd ( cy8C95xx_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = CY8C95XX_REG_CMD_ADR;
    tx_buf[ 1 ] = cmd;

    ctx->slave_addr = port_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_addr, tx_buf, 2, false);
}

void cy8C95xx_write_eeprom ( cy8C95xx_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 255 ];
    uint8_t cnt;

    tx_buf[ 1 ] = (uint8_t)( mem_adr & 0x00FF );
    tx_buf[ 0 ] = (uint8_t)( ( mem_adr >> 8 ) & 0x00FF );

    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 2 ] = buf[ cnt ];
    }

    ctx->slave_addr = eeprom_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_addr, tx_buf, len + 2, false);
}

void cy8C95xx_read_eeprom ( cy8C95xx_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 1 ] = (uint8_t)( mem_adr & 0x00FF );
    tx_buf[0] = (uint8_t)((mem_adr >> 8) & 0x00FF);

    ctx->slave_addr = eeprom_slave_addr;
    i2c_write_blocking(ctx->i2c, ctx->slave_addr, tx_buf, 2, false);
    i2c_read_blocking(ctx->i2c, ctx->slave_addr, buf, len, false);
}

// Read bit
uint8_t cy8C95xx_read_bit ( cy8C95xx_t *ctx, uint8_t reg_adr, uint8_t bit_num )
{
    uint8_t bit_chk;
    uint8_t res;

    bit_chk = cy8C95xx_read_byte( ctx, reg_adr );
    res = bit_chk & ( 1 << bit_num );

    return res;
}

void cy8C95xx_write_bit ( cy8C95xx_t *ctx, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val )
{
    uint8_t bit_chk;

    bit_chk = cy8C95xx_read_byte( ctx, reg_adr );
    bit_chk = ( pin_val != 0 ) ? ( bit_chk | ( 1 << bit_num ) ) : ( bit_chk & ~( 1 << bit_num ) );

    cy8C95xx_write_byte( ctx, reg_adr, bit_chk );
}

// Get a single INPUT pin's logic level
uint8_t cy8C95xx_read_pin ( cy8C95xx_t *ctx, uint16_t pin, uint8_t inv )
{
    uint8_t buf;
    
    if ( inv == 0x01 )
    {
        cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
        cy8C95xx_write_byte( ctx, CY8C95XX_REG_INV_ADR, ( pin % 8 ) );
    }
    
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_DIR_ADR, 0xFF );
    
    buf = cy8C95xx_read_bit( ctx, ( CY8C95XX_REG_IN_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}

// Get all pin logic levels from one port
uint8_t cy8C95xx_read_port ( cy8C95xx_t *ctx, uint8_t port, uint8_t inv )
{
    uint8_t buf;
    
    if ( inv == 0x01 )
    {
        cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, port );
        cy8C95xx_write_byte( ctx, CY8C95XX_REG_INV_ADR, 0xFF );
    }
    
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, port );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_DIR_ADR, 0xFF );

    buf = cy8C95xx_read_byte( ctx, CY8C95XX_REG_IN_PORT0_ADR + port );

    return buf;
}

// Get a single OUTPUT pin's setting
uint8_t cy8C95xx_get_pin_out_lvl ( cy8C95xx_t *ctx, uint16_t pin )
{
    uint8_t buf;
    
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_DIR_ADR, 0xFF );

    buf = cy8C95xx_read_bit( ctx, ( CY8C95XX_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}

// Get all pin output settings from one port
uint8_t cy8C95xx_get_port_out_lvl ( cy8C95xx_t *ctx, uint8_t port )
{
    uint8_t buf;
    
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, port );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_DIR_ADR, 0xFF );

    buf = cy8C95xx_read_byte ( ctx, CY8C95XX_REG_OUT_PORT0_ADR + port );

    return buf;
}

// Set a single OUTPUT pin's logic level
void cy8C95xx_write_pin ( cy8C95xx_t *ctx, uint16_t pin, uint8_t pin_val )
{
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_DIR_ADR, 0x00 );

    cy8C95xx_write_bit( ctx, ( CY8C95XX_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ), pin_val );
}

// Set all OUTPUT pins' logic levels in one port
void cy8C95xx_write_port ( cy8C95xx_t *ctx, uint8_t port, uint8_t value )
{
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, port );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_DIR_ADR, 0x00 );

    cy8C95xx_write_byte( ctx, ( CY8C95XX_REG_OUT_PORT0_ADR + port ), value );
}

// Select a PWM pin output pin
void cy8C95xx_sel_pwm_pin ( cy8C95xx_t *ctx, uint16_t pin, uint8_t pwm_en )
{
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_DIR_ADR, 0x00 );

    cy8C95xx_write_bit( ctx, ( CY8C95XX_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ), pwm_en );

    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_SEL_PWM_OUT_ADR, ( pwm_en << ( pin % 8 ) ) );
}

// PWM Configuration
void cy8C95xx_pwm_cfg ( cy8C95xx_t *ctx, cy8C95xx_pwm_cfg_t pwm_cfg, float *duty_cyc, float *freq )
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

    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PWM_SEL_ADR, buf[ 0 ] );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_CFG_PWM_ADR, buf[ 1 ] );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PERIOD_PWM_ADR, buf[ 2 ] );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_PULSE_WIDTH_PWM_ADR, buf[ 3 ] );
    cy8C95xx_write_byte( ctx, CY8C95XX_REG_DIVIDER_ADR, buf[ 4 ] );
    
    *duty_cyc = (float)buf[ 3 ] / (float)buf[ 2 ];
    *freq = 93750.0 / (float)buf[ 4 ];
}

// Enable Register Configuration
void cy8C95xx_eeprom_enable ( cy8C95xx_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = 0x43;
    tx_buf[ 1 ] = 0x4D;
    tx_buf[ 2 ] = 0x53;
    tx_buf[ 3 ] = cmd;

    cy8C95xx_write_port_exp( ctx, CY8C95XX_REG_EEPROM_ADR, tx_buf, 4 );
}

// Reset
void cy8C95xx_reset ( cy8C95xx_t *ctx )
{
    if (ctx->rst_pin >= 0) {
        gpio_put(ctx->rst_pin, 1);
        sleep_ms(1000);
        gpio_put(ctx->rst_pin, 0);
        sleep_ms(1000);
    }
}

// Check interrupt
uint8_t cy8C95xx_check_int(cy8C95xx_t* ctx)
{
    if (ctx->int_pin >= 0) {
        return gpio_get(ctx->int_pin);
    }
    
    return 0;
}

// ------------------------------------------------------------------------- END

