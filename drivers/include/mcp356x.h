/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef MCP356X_H
#define MCP356X_H
 
/**
 * \file mcp356x.h
 * \ingroup drivers
 * \defgroup mcp356x
 *
 * Driver librarry to handle MCP356X ADC.
 * Based on MikroE ADC 9 Click driver (Copyright© 2020 MikroElektronika d.o.o.)
 */
 
#include <stdio.h>
#include "hw_platform.h" /* External harware interface library */
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup mcp356x
 */
typedef enum {
    MCP356X_OK =         PLATFORM_OK,
    MCP356X_ARG_ERROR =  PLATFORM_ARGUMENT_ERROR,
    MCP356X_INIT_ERROR = PLATFORM_SPI_INIT_ERROR,
    MCP356X_SPI_ERROR =  PLATFORM_SPI_COM_ERROR
} mcp356x_error_code_t;
 
/**
 * \brief Device address
 * \ingroup mcp356x
 */
#define MCP356X_DEVICE_ADDR                  0x01
 
/**
 * \brief Fast commands CMD[5:2]
 * \ingroup mcp356x
 */
#define MCP356X_FAST_CMD_ADC_CONV_START      0x0A
#define MCP356X_FAST_CMD_ADC_STANDBY_MODE    0x0B
#define MCP356X_FAST_CMD_ADC_SHUTDOWN_MODE   0x0C
#define MCP356X_FAST_CMD_FULL_SHUTDOWN_MODE  0x0D
#define MCP356X_FAST_CMD_DEV_FULL_RESET      0x0E
 
/**
 * \brief Write/read commands CMD[1:0]
 * \ingroup mcp356x
 */
#define MCP356X_CMD_DONT_CARE                0x00
#define MCP356X_CMD_STAT_READ                0x01
#define MCP356X_CMD_INC_WRITE                0x02
#define MCP356X_CMD_INC_READ                 0x03
 
/**
 * \brief Internal register addresses CMD[5:2]
 * \ingroup mcp356x
 */
#define MCP356X_REG_ADC_DATA                 0x00
#define MCP356X_REG_CFG_0                    0x01
#define MCP356X_REG_CFG_1                    0x02
#define MCP356X_REG_CFG_2                    0x03
#define MCP356X_REG_CFG_3                    0x04
#define MCP356X_REG_IRQ                      0x05
#define MCP356X_REG_MUX                      0x06
#define MCP356X_REG_SCAN                     0x07
#define MCP356X_REG_TIMER                    0x08
#define MCP356X_REG_OFFSET_CAL               0x09
#define MCP356X_REG_GAIN_CAL                 0x0A
#define MCP356X_RSV_REG_W_A                  0x0B
#define MCP356X_REG_LOCK                     0x0D
#define MCP356X_RSV_REG                      0x0E
#define MCP356X_REG_CRC_CFG                  0x0F
 
/**
 * \brief CONFIG0 Register
 * \ingroup mcp356x
 */
#define MCP356X_CFG_0_VREF_EXT               0x00
#define MCP356X_CFG_0_VREF_INT               0x80

#define MCP356X_CFG_0_CLK_EXT                0x00
#define MCP356X_CFG_0_CLK_EXT_               0x10
#define MCP356X_CFG_0_CLK_INT_NO_OUT         0x20
#define MCP356X_CFG_0_CLK_INT_OUT            0x30

#define MCP356X_CFG_0_CS_SEL_NONE            0x00
#define MCP356X_CFG_0_CS_SEL_0_9_UA          0x04
#define MCP356X_CFG_0_CS_SEL_3_7_UA          0x08
#define MCP356X_CFG_0_CS_SEL_15_UA           0x0C

#define MCP356X_CFG_0_MODE_SHD_DEF           0x00
#define MCP356X_CFG_0_MODE_SHD               0x01
#define MCP356X_CFG_0_MODE_STANDBY           0x02
#define MCP356X_CFG_0_MODE_CONV              0x03
 
/**
 * \brief CONFIG1 Register
 * \ingroup mcp356x
 */
#define MCP356X_CFG_1_PRE_1                  0x00
#define MCP356X_CFG_1_PRE_2                  0x40
#define MCP356X_CFG_1_PRE_4                  0x80
#define MCP356X_CFG_1_PRE_8                  0xC0

#define MCP356X_CFG_1_OSR_98304              0x3C
#define MCP356X_CFG_1_OSR_81920              0x38
#define MCP356X_CFG_1_OSR_49152              0x34
#define MCP356X_CFG_1_OSR_40960              0x30
#define MCP356X_CFG_1_OSR_24576              0x2C
#define MCP356X_CFG_1_OSR_20480              0x28
#define MCP356X_CFG_1_OSR_16384              0x24
#define MCP356X_CFG_1_OSR_8192               0x20
#define MCP356X_CFG_1_OSR_4096               0x1C
#define MCP356X_CFG_1_OSR_2048               0x18
#define MCP356X_CFG_1_OSR_1024               0x14
#define MCP356X_CFG_1_OSR_512                0x10
#define MCP356X_CFG_1_OSR_256                0x0C
#define MCP356X_CFG_1_OSR_128                0x08
#define MCP356X_CFG_1_OSR_64                 0x04
#define MCP356X_CFG_1_OSR_32                 0x00
 
/**
 * \brief CONFIG2 Register
 * \ingroup mcp356x
 */
#define MCP356X_CFG_2_BOOST_X_2              0xC0
#define MCP356X_CFG_2_BOOST_X_1              0x80
#define MCP356X_CFG_2_BOOST_X_066            0x40
#define MCP356X_CFG_2_BOOST_X_05             0x00

#define MCP356X_CFG_2_GAIN_X_64              0x38
#define MCP356X_CFG_2_GAIN_X_32              0x30
#define MCP356X_CFG_2_GAIN_X_16              0x28
#define MCP356X_CFG_2_GAIN_X_8               0x20
#define MCP356X_CFG_2_GAIN_X_4               0x18
#define MCP356X_CFG_2_GAIN_X_2               0x10
#define MCP356X_CFG_2_GAIN_X_1               0x08
#define MCP356X_CFG_2_GAIN_X_033             0x00

#define MCP356X_CFG_2_AZ_MUX_EN              0x04
#define MCP356X_CFG_2_AZ_MUX_DIS             0x00
#define MCP356X_CFG_2_AZ_VREF_EN             0x02
#define MCP356X_CFG_2_AZ_VREF_DIS            0x00
 
/**
 * \brief CONFIG3 Register
 * \ingroup mcp356x
 */
#define MCP356X_CFG_3_CONV_MODE_CONT         0xC0
#define MCP356X_CFG_3_CONV_MODE_STANDBY      0x80
#define MCP356X_CFG_3_CONV_MODE_SHD          0x40
#define MCP356X_CFG_3_CONV_MODE_SHD0         0x00

#define MCP356X_CFG_3_DATA_FORMAT_CH_ADC     0x30
#define MCP356X_CFG_3_DATA_FORMAT_EXT_ADC    0x20
#define MCP356X_CFG_3_DATA_FORMAT_LEFT_JUST  0x10
#define MCP356X_CFG_3_DATA_FORMAT_DEF        0x00

#define MCP356X_CFG_3_CRC_FORMAT_32          0x08
#define MCP356X_CFG_3_CRC_FORMAT_16          0x00

#define MCP356X_CFG_3_CRC_COM_EN             0x04
#define MCP356X_CFG_3_CRC_COM_DIS            0x00

#define MCP356X_CFG_3_CRC_OFF_CAL_EN         0x02
#define MCP356X_CFG_3_CRC_OFF_CAL_DIS        0x00
#define MCP356X_CFG_3_CRC_GAIN_CAL_EN        0x01
#define MCP356X_CFG_3_CRC_GAIN_CAL_DIS       0x00
 
/**
 * \brief IRQ Register
 * \ingroup mcp356x
 */
#define MCP356X_IRQ_MODE_MDAT                0x08
#define MCP356X_IRQ_MODE_IRQ                 0x00
#define MCP356X_IRQ_MODE_LOGIC_HIGH          0x04
#define MCP356X_IRQ_MODE_HIGH_Z              0x00
#define MCP356X_IRQ_FASTCMD_EN               0x02
#define MCP356X_IRQ_FASTCMD_DIS              0x00
#define MCP356X_IRQ_STP_EN                   0x01
#define MCP356X_IRQ_STP_DIS                  0x00
 
/**
 * \brief MUX_VIN+ Input Selection
 * \ingroup mcp356x
 */
#define MCP356X_MUX_VIN_POS_NO_IN            0xF0
#define MCP356X_MUX_VIN_POS_VCM              0xE0
#define MCP356X_MUX_VIN_POS_TEMP             0xD0
#define MCP356X_MUX_VIN_POS_VREF_EXT_MINUS   0xC0
#define MCP356X_MUX_VIN_POS_VREF_EXT_PLUS    0xB0
#define MCP356X_MUX_VIN_POS_VREF_INT         0xA0
#define MCP356X_MUX_VIN_POS_AVDD             0x90
#define MCP356X_MUX_VIN_POS_VSS              0x80
#define MCP356X_MUX_VIN_POS_CH7              0x70
#define MCP356X_MUX_VIN_POS_CH6              0x60
#define MCP356X_MUX_VIN_POS_CH5              0x50
#define MCP356X_MUX_VIN_POS_CH4              0x40
#define MCP356X_MUX_VIN_POS_CH3              0x30
#define MCP356X_MUX_VIN_POS_CH2              0x20
#define MCP356X_MUX_VIN_POS_CH1              0x10
#define MCP356X_MUX_VIN_POS_CH0              0x00
 
/**
 * \brief MUX_VIN- Input Selection
 * \ingroup mcp356x
 */
#define MCP356X_MUX_VIN_NEG_NO_IN            0x0F
#define MCP356X_MUX_VIN_NEG_VCM              0x0E
#define MCP356X_MUX_VIN_NEG_TEMP             0x0D
#define MCP356X_MUX_VIN_NEG_VREF_EXT_MINUS   0x0C
#define MCP356X_MUX_VIN_NEG_VREF_EXT_PLUS    0x0B
#define MCP356X_MUX_VIN_NEG_VREF_INT         0x0A
#define MCP356X_MUX_VIN_NEG_AVDD             0x09
#define MCP356X_MUX_VIN_NEG_VSS              0x08
#define MCP356X_MUX_VIN_NEG_CH7              0x07
#define MCP356X_MUX_VIN_NEG_CH6              0x06
#define MCP356X_MUX_VIN_NEG_CH5              0x05
#define MCP356X_MUX_VIN_NEG_CH4              0x04
#define MCP356X_MUX_VIN_NEG_CH3              0x03
#define MCP356X_MUX_VIN_NEG_CH2              0x02
#define MCP356X_MUX_VIN_NEG_CH1              0x01
#define MCP356X_MUX_VIN_NEG_CH0              0x00
 
/**
 * \brief SCAN Register
 * \ingroup mcp356x
 */
#define MCP356X_SCAN_DLY_DM_CLK_X_512        0x00E00000
#define MCP356X_SCAN_DLY_DM_CLK_X_256        0x00C00000
#define MCP356X_SCAN_DLY_DM_CLK_X_128        0x00A00000
#define MCP356X_SCAN_DLY_DM_CLK_X_64         0x00800000
#define MCP356X_SCAN_DLY_DM_CLK_X_32         0x00600000
#define MCP356X_SCAN_DLY_DM_CLK_X_16         0x00400000
#define MCP356X_SCAN_DLY_DM_CLK_X_8          0x00200000
#define MCP356X_SCAN_DLY_NO_DELAY            0x00000000

#define MCP356X_SCAN_OFFSET                  0x00008000
#define MCP356X_SCAN_VREF                    0x00004000
#define MCP356X_SCAN_AVDD                    0x00002000
#define MCP356X_SCAN_TEMP                    0x00001000
#define MCP356X_SCAN_DIFF_D                  0x00000800
#define MCP356X_SCAN_DIFF_C                  0x00000400
#define MCP356X_SCAN_DIFF_B                  0x00000200
#define MCP356X_SCAN_DIFF_A                  0x00000100
#define MCP356X_SCAN_CH7                     0x00000080
#define MCP356X_SCAN_CH6                     0x00000040
#define MCP356X_SCAN_CH5                     0x00000020
#define MCP356X_SCAN_CH4                     0x00000010
#define MCP356X_SCAN_CH3                     0x00000008
#define MCP356X_SCAN_CH2                     0x00000004
#define MCP356X_SCAN_CH1                     0x00000002
#define MCP356X_SCAN_CH0                     0x00000001
 
/**
 * \brief Timer Register
 * \ingroup mcp356x
 */
#define MCP356X_TIMER_DLY_DMCLK_X_16777215   0x00FFFFFF
#define MCP356X_TIMER_DLY_DMCLK_X_8388607    0x007FFFFF
#define MCP356X_TIMER_DLY_DMCLK_X_4194303    0x003FFFFF
#define MCP356X_TIMER_DLY_DMCLK_X_2097151    0x001FFFFF
#define MCP356X_TIMER_DLY_DMCLK_X_1048575    0x000FFFFF
#define MCP356X_TIMER_DLY_DMCLK_X_524287     0x0007FFFF
#define MCP356X_TIMER_DLY_DMCLK_X_262143     0x0003FFFF
#define MCP356X_TIMER_DLY_DMCLK_X_131071     0x0001FFFF
#define MCP356X_TIMER_DLY_DMCLK_X_65535      0x0000FFFF
#define MCP356X_TIMER_DLY_DMCLK_X_32767      0x00007FFF
#define MCP356X_TIMER_DLY_DMCLK_X_16383      0x00003FFF
#define MCP356X_TIMER_DLY_DMCLK_X_8191       0x00001FFF
#define MCP356X_TIMER_DLY_DMCLK_X_4095       0x00000FFF
#define MCP356X_TIMER_DLY_DMCLK_X_2047       0x000007FF
#define MCP356X_TIMER_DLY_DMCLK_X_1023       0x000003FF
#define MCP356X_TIMER_DLY_DMCLK_X_511        0x000001FF
#define MCP356X_TIMER_DLY_DMCLK_X_255        0x000000FF
#define MCP356X_TIMER_DLY_DMCLK_X_127        0x0000007F
#define MCP356X_TIMER_DLY_DMCLK_X_63         0x0000003F
#define MCP356X_TIMER_DLY_DMCLK_X_31         0x0000001F
#define MCP356X_TIMER_DLY_DMCLK_X_15         0x0000000F
#define MCP356X_TIMER_DLY_DMCLK_X_2          0x00000002
#define MCP356X_TIMER_DLY_DMCLK_X_1          0x00000001
#define MCP356X_TIMER_DLY_NO_DELAY           0x00000000
 
/**
 * \brief Channel identifiers
 * \ingroup mcp356x
 */
#define MCP356X_CH_OFFSET                    0x0F
#define MCP356X_CH_VREF                      0x0E
#define MCP356X_CH_AVDD                      0x0D
#define MCP356X_CH_TEMP                      0x0C
#define MCP356X_CH_DIFF_D                    0x0B
#define MCP356X_CH_DIFF_C                    0x0A
#define MCP356X_CH_DIFF_B                    0x09
#define MCP356X_CH_DIFF_A                    0x08
#define MCP356X_CH_CH7                       0x07
#define MCP356X_CH_CH6                       0x06
#define MCP356X_CH_CH5                       0x05
#define MCP356X_CH_CH4                       0x04
#define MCP356X_CH_CH3                       0x03
#define MCP356X_CH_CH2                       0x02
#define MCP356X_CH_CH1                       0x01
#define MCP356X_CH_CH0                       0x00
 
/**
 * \brief Calculation coefitient
 * \ingroup mcp356x
 */
#define MCP356X_CALC_COEF                    8388608
 
/**
 * \brief External pins
 * \ingroup mcp356x
 */
#ifndef MCP356X_MCLK
#define MCP356X_MCLK    -1
#endif
#ifndef MCP356X_INT
#define MCP356X_INT     -1
#endif
#ifndef MCP356X_CS
#define MCP356X_CS      -1
#endif
 
/**
 * \brief Initial config struct
 * \ingroup mcp356x
 */
typedef struct
{
    int mosi_pin;
    int miso_pin;
    int sck_pin;
    int cs_pin;
    uint spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t* spi;
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
} mcp356x_cfg_t;
 
/**
 * \brief MCP356X ADC struct
 * \ingroup mcp356x
 */
typedef struct
{
    int cs_pin;
    uint spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t* spi;
    int mclk_pin;
    int int_pin;
    uint8_t status;
} mcp356x_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup mcp356x
 *
 * \param cfg Initial config struct
 */
void mcp356x_set_default_cfg(mcp356x_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup mcp356x
 *
 * \param dac Pointer MCP356X ADC struct
 * \param cfg Initial config struct
 * \return MCP356X_INIT_ERROR : error
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_init(mcp356x_t* dev, mcp356x_cfg_t* cfg);
 
/*!
 * \brief Check interrupt by reading int_pin level
 * \ingroup mcp356x
 *
 * \param exp Pointer to CY8C95XX expander struct
 * \return 0 : Interrupt has not occured
 *         1 : Interrupt has occured
 */
uint8_t mcp356x_check_int(mcp356x_t* dev);
 
/*!
 * \brief Generic SPI data transfer
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param fcmd_addr Fast command or register address CMD[5:2]
 * \param r_w_cmd Static read or incremental write or read CMD[1:0] set to MCP356X_CMD_DONT_CARE if fast command
 * \param txdata Pointer to write data set to NULL for only read
 * \param rxdata Pointer to receive data set to NULL for only write
 * \param len Number of bytes to exchange
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_generic_transfer(mcp356x_t* dev, uint8_t fcmd_addr, uint8_t r_w_cmd, uint8_t* txdata, uint8_t* rxdata, uint8_t len);
 
/*!
 * \brief Write fast commands
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param fast_cmd Fast command to send
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_write_fast_cmd(mcp356x_t* dev, uint8_t fast_cmd);
 
/*!
 * \brief Write incremental data to registers
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param reg Start register address
 * \param txdata Pointer to transmit data
 * \param txlen Number of bytes to write should fit registers data size
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_iwrite(mcp356x_t* dev, uint8_t reg, uint8_t* txdata, uint8_t txlen);
 
/*!
 * \brief Read static register data
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param reg Register address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of bytes to read should fit register data size
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_sread(mcp356x_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen);
 
/*!
 * \brief Read incremental from registers
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param reg Start register address
 * \param rxdata Pointer to receive data
 * \param rxlen Number of bytes to read should fit registers data size
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_iread(mcp356x_t* dev, uint8_t reg, uint8_t* rxdata, uint8_t rxlen);
 
/*!
 * \brief Read ADC data in default format MCP356X_CFG_3_DATA_FORMAT_DEF
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param adc_data Pointer to receive 23bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_read_adc_def(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn);
 
/*!
 * \brief Read ADC data in left justified format MCP356X_CFG_3_DATA_FORMAT_LEFT_JUST
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param adc_data Pointer to receive 23bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_read_adc_left_just(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn);
 
/*!
 * \brief Read ADC data in extended format MCP356X_CFG_3_DATA_FORMAT_EXT_ADC
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param adc_data Pointer to receive 24bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_read_adc_ext(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn);
 
/*!
 * \brief Read ADC data in extended format including ch_id MCP356X_CFG_3_DATA_FORMAT_CH_ADC
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \param adc_data Pointer to receive 24bit(uint32_t*) ADC data
 * \param sgn Pointer to receive sign bit
 * \param ch_id Pointer to receive channel identifier
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_read_adc_ch_ext(mcp356x_t* dev, uint32_t* adc_data, uint8_t* sgn, uint8_t* ch_id);
 
/*!
 * \brief Read channel voltage in millivolts using \p vol_ref_min to \p vol_ref_max as reference
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct 
 * \param vol_ref_min Min reference voltage in millivolts equivalent to 0 in ADC
 * \param vol_ref_max Maximun reference voltage in millivolts equivalent to max resolution
 * \param vol_val Pointer to receive voltage value in millivolts
 * \return MCP356X_SPI_ERROR : error in coms
 *         MCP356X_ARG_ERROR : error in arguments
 *         MCP356X_OK : successful
 */
mcp356x_error_code_t mcp356x_read_voltage(mcp356x_t* dev, uint32_t vol_ref_min, uint32_t vol_ref_max, uint32_t* vol_val);
 
/*!
 * \brief Enable CS for start SPI coms
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \note Should be implemented externally
 */
void mcp356x_cs_select(mcp356x_t* dev);

/*!
 * \brief Disable CS after SPI coms
 * \ingroup mcp356x
 *
 * \param dev Pointer MCP356X ADC struct
 * \note Should be implemented externally
 */
void mcp356x_cs_deselect(mcp356x_t* dev);

#ifdef __cplusplus
}
#endif
 
#endif  // AD56X4_H
