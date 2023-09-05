/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef MCP3564_H
#define MCP3564_H
 
/**
 * \file mcp3564.h
 * \ingroup drivers
 * \defgroup mcp3564
 *
 * Driver librarry to handle MCP3564 ADC.
 * Based on MikroE ADC 9 Click driver (Copyright© 2020 MikroElektronika d.o.o.)
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include <stdint.h>
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup mcp3564
 */
typedef int mcp3564_err_code_t;
 
/**
 * \brief Device address
 * \ingroup mcp3564
 */
#define MCP3564_DEVICE_ADDR                  0x01
 
/**
 * \brief Fast commands CMD[5:2]
 * \ingroup mcp3564
 */
typedef enum {
    MCP3564_FAST_CMD_ADC_CONV_START =       0x0A,
    MCP3564_FAST_CMD_ADC_STANDBY_MODE =     0x0B,
    MCP3564_FAST_CMD_ADC_SHUTDOWN_MODE =    0x0C,
    MCP3564_FAST_CMD_FULL_SHUTDOWN_MODE =   0x0D,
    MCP3564_FAST_CMD_DEV_FULL_RESET =       0x0E
} mcp3564_fast_cmd_t;

/**
 * \brief Write/read commands CMD[1:0]
 * \ingroup mcp3564
 */
typedef enum {
    MCP3564_CMD_DONT_CARE =                 0x00,
    MCP3564_CMD_STAT_READ =                 0x01,
    MCP3564_CMD_INC_WRITE =                 0x02,
    MCP3564_CMD_INC_READ =                  0x03
} mcp3564_rw_cmd_t;
 
/**
 * \brief Internal register addresses CMD[5:2]
 * \ingroup mcp3564
 */
typedef enum {
    MCP3564_REG_ADC_DATA =                  0x00,
    MCP3564_REG_CFG_0 =                     0x01,
    MCP3564_REG_CFG_1 =                     0x02,
    MCP3564_REG_CFG_2 =                     0x03,
    MCP3564_REG_CFG_3 =                     0x04,
    MCP3564_REG_IRQ =                       0x05,
    MCP3564_REG_MUX =                       0x06,
    MCP3564_REG_SCAN =                      0x07,
    MCP3564_REG_TIMER =                     0x08,
    MCP3564_REG_OFFSET_CAL =                0x09,
    MCP3564_REG_GAIN_CAL =                  0x0A,
    MCP3564_REG_LOCK =                      0x0D,
    MCP3564_REG_CRC_CFG =                   0x0F,
} mcp3564_reg_t;
 
/**
 * \brief CONFIG0 Register
 * \ingroup mcp3564
 */
#define MCP3564_CFG_0_VREF_EXT               0x00
#define MCP3564_CFG_0_VREF_INT               0x80

#define MCP3564_CFG_0_CLK_EXT                0x00
#define MCP3564_CFG_0_CLK_EXT_               0x10
#define MCP3564_CFG_0_CLK_INT_NO_OUT         0x20
#define MCP3564_CFG_0_CLK_INT_OUT            0x30

#define MCP3564_CFG_0_CS_SEL_NONE            0x00
#define MCP3564_CFG_0_CS_SEL_0_9_UA          0x04
#define MCP3564_CFG_0_CS_SEL_3_7_UA          0x08
#define MCP3564_CFG_0_CS_SEL_15_UA           0x0C

#define MCP3564_CFG_0_MODE_SHD_DEF           0x00
#define MCP3564_CFG_0_MODE_SHD               0x01
#define MCP3564_CFG_0_MODE_STANDBY           0x02
#define MCP3564_CFG_0_MODE_CONV              0x03
 
/**
 * \brief CONFIG1 Register
 * \ingroup mcp3564
 */
#define MCP3564_CFG_1_PRE_1                  0x00
#define MCP3564_CFG_1_PRE_2                  0x40
#define MCP3564_CFG_1_PRE_4                  0x80
#define MCP3564_CFG_1_PRE_8                  0xC0

#define MCP3564_CFG_1_OSR_98304              0x3C
#define MCP3564_CFG_1_OSR_81920              0x38
#define MCP3564_CFG_1_OSR_49152              0x34
#define MCP3564_CFG_1_OSR_40960              0x30
#define MCP3564_CFG_1_OSR_24576              0x2C
#define MCP3564_CFG_1_OSR_20480              0x28
#define MCP3564_CFG_1_OSR_16384              0x24
#define MCP3564_CFG_1_OSR_8192               0x20
#define MCP3564_CFG_1_OSR_4096               0x1C
#define MCP3564_CFG_1_OSR_2048               0x18
#define MCP3564_CFG_1_OSR_1024               0x14
#define MCP3564_CFG_1_OSR_512                0x10
#define MCP3564_CFG_1_OSR_256                0x0C
#define MCP3564_CFG_1_OSR_128                0x08
#define MCP3564_CFG_1_OSR_64                 0x04
#define MCP3564_CFG_1_OSR_32                 0x00
 
/**
 * \brief CONFIG2 Register
 * \ingroup mcp3564
 */
#define MCP3564_CFG_2_BOOST_X_2              0xC0
#define MCP3564_CFG_2_BOOST_X_1              0x80
#define MCP3564_CFG_2_BOOST_X_066            0x40
#define MCP3564_CFG_2_BOOST_X_05             0x00

#define MCP3564_CFG_2_GAIN_X_64              0x38
#define MCP3564_CFG_2_GAIN_X_32              0x30
#define MCP3564_CFG_2_GAIN_X_16              0x28
#define MCP3564_CFG_2_GAIN_X_8               0x20
#define MCP3564_CFG_2_GAIN_X_4               0x18
#define MCP3564_CFG_2_GAIN_X_2               0x10
#define MCP3564_CFG_2_GAIN_X_1               0x08
#define MCP3564_CFG_2_GAIN_X_033             0x00

typedef enum {
    MCP3564_GAIN_X_64 =     MCP3564_CFG_2_GAIN_X_64,
    MCP3564_GAIN_X_32 =     MCP3564_CFG_2_GAIN_X_32,
    MCP3564_GAIN_X_16 =     MCP3564_CFG_2_GAIN_X_16,
    MCP3564_GAIN_X_8 =      MCP3564_CFG_2_GAIN_X_8,
    MCP3564_GAIN_X_4 =      MCP3564_CFG_2_GAIN_X_4,
    MCP3564_GAIN_X_2 =      MCP3564_CFG_2_GAIN_X_2,
    MCP3564_GAIN_X_1 =      MCP3564_CFG_2_GAIN_X_1,
    MCP3564_GAIN_X_033 =    MCP3564_CFG_2_GAIN_X_033
} mcp3564_gain_t;

#define MCP3564_CFG_2_AZ_MUX_EN              0x04
#define MCP3564_CFG_2_AZ_MUX_DIS             0x00
#define MCP3564_CFG_2_AZ_VREF_EN             0x03
#define MCP3564_CFG_2_AZ_VREF_DIS            0x01
 
/**
 * \brief CONFIG3 Register
 * \ingroup mcp3564
 */
#define MCP3564_CFG_3_CONV_MODE_CONT         0xC0
#define MCP3564_CFG_3_CONV_MODE_STANDBY      0x80
#define MCP3564_CFG_3_CONV_MODE_SHD          0x40
#define MCP3564_CFG_3_CONV_MODE_SHD0         0x00

#define MCP3564_CFG_3_DATA_FORMAT_CH_ADC     0x30
#define MCP3564_CFG_3_DATA_FORMAT_EXT_ADC    0x20
#define MCP3564_CFG_3_DATA_FORMAT_LEFT_JUST  0x10
#define MCP3564_CFG_3_DATA_FORMAT_DEF        0x00

#define MCP3564_CFG_3_CRC_FORMAT_32          0x08
#define MCP3564_CFG_3_CRC_FORMAT_16          0x00

#define MCP3564_CFG_3_CRC_COM_EN             0x04
#define MCP3564_CFG_3_CRC_COM_DIS            0x00

#define MCP3564_CFG_3_CRC_OFF_CAL_EN         0x02
#define MCP3564_CFG_3_CRC_OFF_CAL_DIS        0x00
#define MCP3564_CFG_3_CRC_GAIN_CAL_EN        0x01
#define MCP3564_CFG_3_CRC_GAIN_CAL_DIS       0x00
 
/**
 * \brief IRQ Register
 * \ingroup mcp3564
 */
#define MCP3564_IRQ_MODE_MDAT                0x08
#define MCP3564_IRQ_MODE_IRQ                 0x00
#define MCP3564_IRQ_MODE_LOGIC_HIGH          0x04
#define MCP3564_IRQ_MODE_HIGH_Z              0x00
#define MCP3564_IRQ_FASTCMD_EN               0x02
#define MCP3564_IRQ_FASTCMD_DIS              0x00
#define MCP3564_IRQ_STP_EN                   0x01
#define MCP3564_IRQ_STP_DIS                  0x00
 
/**
 * \brief MUX_VIN+ Input Selection
 * \ingroup mcp3564
 */
typedef enum {
    MCP3564_MUX_VIN_POS_NO_IN =              0xF0,
    MCP3564_MUX_VIN_POS_VCM =                0xE0,
    MCP3564_MUX_VIN_POS_TEMP =               0xD0,
    MCP3564_MUX_VIN_POS_VREF_EXT_MINUS =     0xC0,
    MCP3564_MUX_VIN_POS_VREF_EXT_PLUS =      0xB0,
    MCP3564_MUX_VIN_POS_VREF_INT =           0xA0,
    MCP3564_MUX_VIN_POS_AVDD =               0x90,
    MCP3564_MUX_VIN_POS_VSS =                0x80,
    MCP3564_MUX_VIN_POS_CH7 =                0x70,
    MCP3564_MUX_VIN_POS_CH6 =                0x60,
    MCP3564_MUX_VIN_POS_CH5 =                0x50,
    MCP3564_MUX_VIN_POS_CH4 =                0x40,
    MCP3564_MUX_VIN_POS_CH3 =                0x30,
    MCP3564_MUX_VIN_POS_CH2 =                0x20,
    MCP3564_MUX_VIN_POS_CH1 =                0x10,
    MCP3564_MUX_VIN_POS_CH0 =                0x00
} mcp3564_mux_pos_t;

/**
 * \brief MUX_VIN- Input Selection
 * \ingroup mcp3564
 */
typedef enum {
    MCP3564_MUX_VIN_NEG_NO_IN =              0x0F,
    MCP3564_MUX_VIN_NEG_VCM =                0x0E,
    MCP3564_MUX_VIN_NEG_TEMP =               0x0D,
    MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS =     0x0C,
    MCP3564_MUX_VIN_NEG_VREF_EXT_PLUS =      0x0B,
    MCP3564_MUX_VIN_NEG_VREF_INT =           0x0A,
    MCP3564_MUX_VIN_NEG_AVDD =               0x09,
    MCP3564_MUX_VIN_NEG_VSS =                0x08,
    MCP3564_MUX_VIN_NEG_CH7 =                0x07,
    MCP3564_MUX_VIN_NEG_CH6 =                0x06,
    MCP3564_MUX_VIN_NEG_CH5 =                0x05,
    MCP3564_MUX_VIN_NEG_CH4 =                0x04,
    MCP3564_MUX_VIN_NEG_CH3 =                0x03,
    MCP3564_MUX_VIN_NEG_CH2 =                0x02,
    MCP3564_MUX_VIN_NEG_CH1 =                0x01,
    MCP3564_MUX_VIN_NEG_CH0 =                0x00
} mcp3564_mux_neg_t;

/**
 * \brief SCAN Register
 * \ingroup mcp3564
 */
#define MCP3564_SCAN_DLY_DM_CLK_X_512        0x00E00000
#define MCP3564_SCAN_DLY_DM_CLK_X_256        0x00C00000
#define MCP3564_SCAN_DLY_DM_CLK_X_128        0x00A00000
#define MCP3564_SCAN_DLY_DM_CLK_X_64         0x00800000
#define MCP3564_SCAN_DLY_DM_CLK_X_32         0x00600000
#define MCP3564_SCAN_DLY_DM_CLK_X_16         0x00400000
#define MCP3564_SCAN_DLY_DM_CLK_X_8          0x00200000
#define MCP3564_SCAN_DLY_NO_DELAY            0x00000000

#define MCP3564_SCAN_OFFSET                  0x00008000
#define MCP3564_SCAN_VREF                    0x00004000
#define MCP3564_SCAN_AVDD                    0x00002000
#define MCP3564_SCAN_TEMP                    0x00001000
#define MCP3564_SCAN_DIFF_D                  0x00000800
#define MCP3564_SCAN_DIFF_C                  0x00000400
#define MCP3564_SCAN_DIFF_B                  0x00000200
#define MCP3564_SCAN_DIFF_A                  0x00000100
#define MCP3564_SCAN_CH7                     0x00000080
#define MCP3564_SCAN_CH6                     0x00000040
#define MCP3564_SCAN_CH5                     0x00000020
#define MCP3564_SCAN_CH4                     0x00000010
#define MCP3564_SCAN_CH3                     0x00000008
#define MCP3564_SCAN_CH2                     0x00000004
#define MCP3564_SCAN_CH1                     0x00000002
#define MCP3564_SCAN_CH0                     0x00000001
 
/**
 * \brief Timer Register
 * \ingroup mcp3564
 */
#define MCP3564_TIMER_DLY_DMCLK_X_16777215   0x00FFFFFF
#define MCP3564_TIMER_DLY_DMCLK_X_8388607    0x007FFFFF
#define MCP3564_TIMER_DLY_DMCLK_X_4194303    0x003FFFFF
#define MCP3564_TIMER_DLY_DMCLK_X_2097151    0x001FFFFF
#define MCP3564_TIMER_DLY_DMCLK_X_1048575    0x000FFFFF
#define MCP3564_TIMER_DLY_DMCLK_X_524287     0x0007FFFF
#define MCP3564_TIMER_DLY_DMCLK_X_262143     0x0003FFFF
#define MCP3564_TIMER_DLY_DMCLK_X_131071     0x0001FFFF
#define MCP3564_TIMER_DLY_DMCLK_X_65535      0x0000FFFF
#define MCP3564_TIMER_DLY_DMCLK_X_32767      0x00007FFF
#define MCP3564_TIMER_DLY_DMCLK_X_16383      0x00003FFF
#define MCP3564_TIMER_DLY_DMCLK_X_8191       0x00001FFF
#define MCP3564_TIMER_DLY_DMCLK_X_4095       0x00000FFF
#define MCP3564_TIMER_DLY_DMCLK_X_2047       0x000007FF
#define MCP3564_TIMER_DLY_DMCLK_X_1023       0x000003FF
#define MCP3564_TIMER_DLY_DMCLK_X_511        0x000001FF
#define MCP3564_TIMER_DLY_DMCLK_X_255        0x000000FF
#define MCP3564_TIMER_DLY_DMCLK_X_127        0x0000007F
#define MCP3564_TIMER_DLY_DMCLK_X_63         0x0000003F
#define MCP3564_TIMER_DLY_DMCLK_X_31         0x0000001F
#define MCP3564_TIMER_DLY_DMCLK_X_15         0x0000000F
#define MCP3564_TIMER_DLY_DMCLK_X_2          0x00000002
#define MCP3564_TIMER_DLY_DMCLK_X_1          0x00000001
#define MCP3564_TIMER_DLY_NO_DELAY           0x00000000
 
/**
 * \brief Channel identifiers
 * \ingroup mcp3564
 */
#define MCP3564_CH_OFFSET                    0x0F
#define MCP3564_CH_VREF                      0x0E
#define MCP3564_CH_AVDD                      0x0D
#define MCP3564_CH_TEMP                      0x0C
#define MCP3564_CH_DIFF_D                    0x0B
#define MCP3564_CH_DIFF_C                    0x0A
#define MCP3564_CH_DIFF_B                    0x09
#define MCP3564_CH_DIFF_A                    0x08
#define MCP3564_CH_CH7                       0x07
#define MCP3564_CH_CH6                       0x06
#define MCP3564_CH_CH5                       0x05
#define MCP3564_CH_CH4                       0x04
#define MCP3564_CH_CH3                       0x03
#define MCP3564_CH_CH2                       0x02
#define MCP3564_CH_CH1                       0x01
#define MCP3564_CH_CH0                       0x00
 
/**
 * \brief Bit masks
 * \ingroup mcp3564
 */
#define MCP3564_VALID_STATUS_MASK           (uint8_t)((MCP3564_DEVICE_ADDR << 4) | ((~MCP3564_DEVICE_ADDR & 0x1) << 3))
#define MCP3564_FCMD_ADDR_MASK              0x3C
#define MCP3564_RW_CMD_MASK                 0x03
#define MCP3564_CFG_2_GAIN_MASK             0x38
#define MCP3564_CFG_3_DATA_FORMAT_MASK      0x30
 
/**
 * \brief Calculation coefitient
 * \ingroup mcp3564
 */
#define MCP3564_CALC_COEF                    8388608
 
/**
 * \brief Posible resolutions
 * \ingroup mcp3564
 */
#define MCP3564_RES_23_BITS                 0x7FFFFF
#define MCP3564_RES_24_BITS                 0xFFFFFF
 
/**
 * \brief Init values to set in configuration registers
 * \ingroup mcp3564
 */
#define MCP3564_INIT_CFG_0_REG              (MCP3564_CFG_0_VREF_INT | MCP3564_CFG_0_CLK_INT_NO_OUT | MCP3564_CFG_0_CS_SEL_NONE | MCP3564_CFG_0_MODE_CONV)
#define MCP3564_INIT_CFG_1_REG              (MCP3564_CFG_1_PRE_1 | MCP3564_CFG_1_OSR_256)
#define MCP3564_INIT_CFG_2_REG              (MCP3564_CFG_2_BOOST_X_1 | MCP3564_CFG_2_GAIN_X_2 | MCP3564_CFG_2_AZ_MUX_DIS | MCP3564_CFG_2_AZ_VREF_EN)
#define MCP3564_INIT_CFG_3_REG              (MCP3564_CFG_3_CONV_MODE_CONT | MCP3564_CFG_3_DATA_FORMAT_DEF | MCP3564_CFG_3_CRC_COM_DIS | MCP3564_CFG_3_CRC_GAIN_CAL_DIS)
#define MCP3564_INIT_IRQ_REG                (MCP3564_IRQ_MODE_IRQ | MCP3564_IRQ_MODE_LOGIC_HIGH | MCP3564_IRQ_FASTCMD_EN | MCP3564_IRQ_STP_EN)
#define MCP3564_INIT_MUX_REG                (MCP3564_MUX_VIN_POS_CH0 | MCP3564_MUX_VIN_NEG_VREF_EXT_MINUS) 
#define MCP3564_INIT_SCAN_REG               MCP3564_SCAN_DLY_NO_DELAY
#define MCP3564_INIT_TIMER_REG              MCP3564_TIMER_DLY_NO_DELAY 
 
/**
 * \brief External pins
 * \ingroup mcp3564
 */
#ifndef MCP3564_MCLK
#define MCP3564_MCLK    -1
#endif
#ifndef MCP3564_INT
#define MCP3564_INT     -1
#endif
#ifndef MCP3564_CS
#define MCP3564_CS      -1
#endif
 
/**
 * \brief External hardware SPI interface
 */
typedef struct _hw_spi_t* hw_spi_t;
 
/**
 * \brief Initial config struct
 * \ingroup mcp3564
 */
typedef struct
{
    int mosi_pin;
    int miso_pin;
    int sck_pin;
    int cs_pin;
    unsigned int spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t spi;
    int mclk_pin;
    int int_pin;
    uint8_t config_0_reg;
    uint8_t config_1_reg;
    uint8_t config_2_reg;
    uint8_t config_3_reg;
    uint8_t irq_reg;
    uint8_t mux_reg;
    uint32_t scan_reg;
    uint32_t timer_reg;
} mcp3564_cfg_t;
 
/**
 * \brief MCP3564 ADC struct
 * \ingroup mcp3564
 */
typedef struct
{
    int cs_pin;
    unsigned int spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t spi;
    int mclk_pin;
    int int_pin;
    uint8_t status;
} mcp3564_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup mcp3564
 *
 * \param cfg Initial config struct
 */
void mcp3564_set_default_cfg(mcp3564_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup mcp3564
 *
 * \param dac Pointer MCP3564 ADC struct
 * \param cfg Initial config struct
 * \return PLATFORM_SPI_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_init(mcp3564_t* dev, mcp3564_cfg_t* cfg);
 
/*!
 * \brief Check interrupt by reading int_pin level
 * \ingroup mcp3564
 *
 * \param exp Pointer to CY8C9520 expander struct
 * \return 0 : Interrupt has not occured
 *         1 : Interrupt has occured
 */
uint8_t mcp3564_check_int(mcp3564_t* dev);
 
/*!
 * \brief Generic SPI data transfer
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param fcmd_addr Fast command or register address CMD[5:2]
 * \param r_w_cmd Static read or incremental write or read CMD[1:0] set to MCP3564_CMD_DONT_CARE if fast command
 * \param txdata Pointer to write data set to NULL for only read
 * \param rxdata Pointer to receive data set to NULL for only write
 * \param len Number of bytes to exchange
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_generic_transfer(
    mcp3564_t* dev,
    uint8_t fcmd_addr,
    mcp3564_rw_cmd_t rw_cmd,
    uint8_t* txdata,
    uint8_t* rxdata,
    uint8_t len);
 
/*!
 * \brief Write fast commands
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param fast_cmd Fast command to send
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_write_fast_cmd(mcp3564_t* dev, mcp3564_fast_cmd_t fast_cmd);
 
/*!
 * \brief Write incremental data to registers
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param reg Start register address
 * \param txdata Pointer to transmit data
 * \param txlen Number of bytes to write should fit registers data size
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_iwrite(mcp3564_t* dev, mcp3564_reg_t reg, uint8_t* txdata, uint8_t txlen);
 
/*!
 * \brief Read static register data
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param reg Register address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of bytes to read should fit register data size
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_sread(mcp3564_t* dev, mcp3564_reg_t reg, uint8_t* rxdata, uint8_t rxlen);
 
/*!
 * \brief Read incremental from registers
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param reg Start register address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of bytes to read should fit registers data size
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_iread(mcp3564_t* dev, mcp3564_reg_t reg, uint8_t* rxdata, uint8_t rxlen);
 
/*!
 * \brief Set GAIN configuration
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param gain Gain value to set
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_set_gain(mcp3564_t* dev, mcp3564_gain_t gain);
 
/*!
 * \brief Read ADC data in default format MCP3564_CFG_3_DATA_FORMAT_DEF
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param adc_data Pointer to receive 23bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_read_adc_def(mcp3564_t* dev, uint32_t* adc_data, uint8_t* sgn);
 
/*!
 * \brief Read ADC data in left justified format MCP3564_CFG_3_DATA_FORMAT_LEFT_JUST
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param adc_data Pointer to receive 23bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_read_adc_left_just(mcp3564_t* dev, uint32_t* adc_data, uint8_t* sgn);
 
/*!
 * \brief Read ADC data in extended format MCP3564_CFG_3_DATA_FORMAT_EXT_ADC
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param adc_data Pointer to receive 24bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_read_adc_ext(mcp3564_t* dev, uint32_t* adc_data, uint8_t* sgn);
 
/*!
 * \brief Read ADC data in extended format including ch_id MCP3564_CFG_3_DATA_FORMAT_CH_ADC
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param adc_data Pointer to receive 24bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \param ch_id Pointer to receive channel identifier
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_read_adc_ch_ext(mcp3564_t* dev, uint32_t* adc_data, uint8_t* sgn, uint8_t* ch_id);
 
/*!
 * \brief Read current adc raw conversion data
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param adc_data Pointer to receive ADC raw data
 * \param sgn Pointer to receive sign bit
 * \param max_resolution Pointer to receive max resulution of ADC conversion
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_read_raw_adc(mcp3564_t* dev, uint32_t* adc_data, uint8_t* sgn, uint32_t* max_resolution);
 
/*!
 * \brief Set MUX and read current adc raw conversion data
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct
 * \param adc_data Pointer to receive ADC raw data
 * \param pos Positive input MUX selection
 * \param neg Negative input MUX selection
 * \param delay_us Delay in microseconds to wait for conversion
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 * \note delay_us deppends on oversampling rate and its the necessary delay to have a valid conversion after MUX change
 */
mcp3564_err_code_t mcp3564_read_adc_mux(mcp3564_t* dev, uint32_t* adc_data, mcp3564_mux_pos_t pos, mcp3564_mux_neg_t neg, uint16_t delay_us);
 
/*!
 * \brief Read current adc voltage conversion in millivolts using \p vol_ref_min to \p vol_ref_max as reference
 * \ingroup mcp3564
 *
 * \param dev Pointer MCP3564 ADC struct 
 * \param vol_ref_min Min reference voltage in millivolts equivalent to 0 in ADC
 * \param vol_ref_max Maximun reference voltage in millivolts equivalent to max resolution
 * \param vol_val Pointer to receive voltage value in millivolts
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
mcp3564_err_code_t mcp3564_read_voltage(mcp3564_t* dev, uint32_t vol_ref_min, uint32_t vol_ref_max, uint32_t* vol_val);
 
/*!
 * \brief Enable CS for start SPI coms
 * \ingroup mcp3564
 *
 * \param cs_pin Chip select pin
 * \note Should be implemented externally
 */
void mcp3564_cs_select(int cs_pin);

/*!
 * \brief Disable CS after SPI coms
 * \ingroup mcp3564
 *
 * \param cs_pin Chip select pin
 * \note Should be implemented externally
 */
void mcp3564_cs_deselect(int cs_pin);

#ifdef __cplusplus
}
#endif
 
#endif  // AD5664_H
