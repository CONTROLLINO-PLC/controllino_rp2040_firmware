/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef BTS71220_H
#define BTS71220_H
 
/**
 * \file bts71220.h
 * \ingroup drivers
 * \defgroup bts71220
 *
 * Driver librarry to handle BTS71220-4ESA power controller
 */
 
#include <stdint.h>
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup bts71220
 */
typedef int bts71220_err_code_t;
 
/**
 * \brief Register addresses  RB + ADDR0 + ADDR1
 * \ingroup bts71220
 */
typedef enum {
    BTS71220_REG_OUT =          0b00000000,
    BTS71220_REG_WRN_DIAG =     0b00000001,
    BTS71220_REG_STD_DIAG =     0b00000010,
    BTS71220_REG_ERR_DIAG =     0b00000011,
    BTS71220_REG_RCS =          0b00001000,
    BTS71220_REG_SRC =          0b00001001,
    BTS71220_REG_OCR =          0b01000100,
    BTS71220_REG_RCD =          0b01001100,
    BTS71220_REG_KRC =          0b01010101,
    BTS71220_REG_PCS =          0b01011101,
    BTS71220_REG_HWCR =         0b01100110,
    BTS71220_REG_ICS =          0b01101110,
    BTS71220_REG_DCR =          0b01111111,
} bts71220_reg_t;
 
/**
 * \brief Bit masks
 * \ingroup bts71220
 */
#define BTS71220_CH0_MASK       0b00000001
#define BTS71220_CH1_MASK       0b00000010
#define BTS71220_CH2_MASK       0b00000100
#define BTS71220_CH3_MASK       0b00001000
#define BTS71220_REG_CONT_MASK  0b00001111
#define BTS71220_ADRR1_MASK     0b00001111
#define BTS71220_ADRR0_MASK     0b00110000
#define BTS71220_ERR_WARN_MASK  0b01000000
#define BTS71220_RB_MASK        0b01000000
#define BTS71220_WRITE_MASK     0b10000000
#define BTS71220_DIAG_RES_MASK  0b11000000
#define BTS71220_OUT_RES_MASK   0b10011111
 
/**
 * \brief Standard diagnosis respose
 * \ingroup bts71220
 */
typedef struct
{
    uint8_t vsmon   : 1; /* VS monitor              0 (default) */
    uint8_t sbm     : 1; /* Switch bypass monitor               */
    uint8_t slp     : 1; /* Sleep mode monitor      1 (default) */
    uint8_t lhi     : 1; /* Limp home monitor       0 (default) */
    uint8_t csv     : 1; /* Checksum verification   0 (default) */
    uint8_t ter     : 1; /* Transmition error       1 (default) */
    uint8_t bit6_7  : 2; /* Don't care                          */
} bts71220_std_diag_t;
 
/**
 * \brief Typical strtucture uses for channel configuration in multiple registers	
 * \ingroup bts71220
 */
typedef struct
{
    uint8_t ch0     : 1; /* Channel 0 */
    uint8_t ch1     : 1; /* Channel 1 */
    uint8_t ch2     : 1; /* Channel 2 */
    uint8_t ch3     : 1; /* Channel 3 */
    uint8_t bit4_7  : 4; /* Don't care */
} bts71220_ch_reg_t;
 
/**
 * \brief Warning and error channel diagnosis respose
 * \ingroup bts71220
 *
 * \note 0 No failure
 *       1 Overcurrent, Overtemperature or delta T detected
 */
typedef bts71220_ch_reg_t bts71220_wrn_diag_t;
typedef bts71220_ch_reg_t bts71220_err_diag_t;

#define BTS71220_CH_NO_FAILURE      0b0
#define BTS71220_CH_ERR_WARN        0b1 /* Warning:Overcurrent, Overtemperature or delta T detected, Error:Channel latched OFF */  
 
/**
 * \brief Channel output register
 * \ingroup bts71220
 */
typedef bts71220_ch_reg_t bts71220_out_reg_t;

#define BTS71220_CH_OFF             0b0 /* Default */
#define BTS71220_CH_ON              0b1
 
/**
 * \brief Restart counter status (read only)
 * \ingroup bts71220
 */
typedef struct
{
    uint8_t rcsn    : 3; /* Restart counter value of channel selected via MUX */
    uint8_t bit3_7  : 5; /* Don't care */
} bts71220_rcs_reg_t;
 
/**
 * \brief Channel slew rate control (read only)
 * \ingroup bts71220
 */
typedef bts71220_ch_reg_t bts71220_src_reg_t;

#define BTS71220_CH_SRC_NORMAL      0b0 /* Default */
#define BTS71220_CH_SRC_ADJUSTED    0b1
 
/**
 * \brief Channel overcurrent threshold
 * \ingroup bts71220
 */
typedef bts71220_ch_reg_t bts71220_ocr_reg_t;

#define BTS71220_CH_OCR_HIGH_LEVEL  0b0 /* Default */
#define BTS71220_CH_OCR_LOW_LEVEL   0b1  
 
/**
 * \brief Channel restart strategy
 * \ingroup bts71220
 */
typedef bts71220_ch_reg_t bts71220_rcd_reg_t;

#define BTS71220_CH_RCD_AUTOMATIC   0b0 /* Default */
#define BTS71220_CH_RCD_LATCH       0b1  
 
/**
 * \brief Channel current sense ratio range
 * \ingroup bts71220
 */
typedef bts71220_ch_reg_t bts71220_krc_reg_t;

#define BTS71220_CH_KRC_HIGH_RANGE  0b0 /* Default */
#define BTS71220_CH_KRC_LOW_RANGE   0b1  
 
/**
 * \brief Parallel channel and slew rate control
 * \ingroup bts71220
 */
typedef struct
{
    uint8_t src     : 1; /* Set slew rate control channel selected by MUX*/
    uint8_t clc     : 1; /* Clear restart counters and latches channel selected by MUX*/
    uint8_t pcc     : 2; /* Parallel Channel Configuration */
    uint8_t bit4_7  : 4; /* Don't care */
} bts71220_pcc_reg_t;

#define BTS71220_PCC_IND            0b00 /* Default */
#define BTS71220_PCC_03             0b01
#define BTS71220_PCC_12             0b10
#define BTS71220_PCC_03_12          0b11
 
/**
 * \brief Hardware configuration
 * \ingroup bts71220
 */
typedef struct
{
    uint8_t clc     : 1; /* Clear restart counters and latches */
    uint8_t rst_slp : 1; /* Reset command(write) Sleep mode(read) */
    uint8_t col     : 1; /* Input combinatorial logic with OUT register */
    uint8_t bit3_7  : 5; /* Don't care */
} bts71220_hwcr_reg_t;

#define BTS71220_HWCR_CLC_COUNT     0b0 /* Default */
#define BTS71220_HWCR_CLC_ALL       0b1

#define BTS71220_HWCR_RST_NORMAL    0b0 /* Default */
#define BTS71220_HWCR_RST_EXEC_CMD  0b1

#define BTS71220_HWCR_SLP_AWAKE     0b0  
#define BTS71220_HWCR_SLP_MUX_111   0b1 /* Default */

#define BTS71220_HWCR_COL_IO_OR     0b0 /* Default */
#define BTS71220_HWCR_COL_IO_AND    0b1
 
/**
 * \brief Input status & checksum input
 * \ingroup bts71220
 */
typedef bts71220_ch_reg_t bts71220_ics_reg_t; /* 4 bit Checksum (write) Channel input status monitor(read)*/

#define BTS71220_ICS_CH_IN_LOW      0b0
#define BTS71220_ICS_CH_IN_HIGH     0b1
 
/**
 * \brief Diagnostic configuration & swap bit
 * \ingroup bts71220
 */
typedef struct
{
    uint8_t mux : 3; /* Current sense multiplexer */
    uint8_t swr : 1; /* Switch register */
    uint8_t bit4_7 : 4; /* Don't care */
} bts71220_dcr_reg_t;

typedef enum {
    BTS71220_DCR_MUX_IS_CH0 =       0b000,
    BTS71220_DCR_MUX_IS_CH1 =       0b001,
    BTS71220_DCR_MUX_IS_CH2 =       0b010,
    BTS71220_DCR_MUX_IS_CH3 =       0b011,
    BTS71220_DCR_MUX_IS_VERIF =     0b101,
    BTS71220_DCR_MUX_IS_Z =         0b110,
    BTS71220_DCR_MUX_IS_SLEEP_Z =   0b111
} bts71220_sense_mux_t;

#define BTS71220_DCR_MUX_SWR_WR_ALL  0b0 /* Default */
#define BTS71220_DCR_MUX_SWR_WR_SOME 0b1 
 
/**
 * \brief External pins
 * \ingroup bts71220
 */
#ifndef BTS71220_CS
#define BTS71220_CS       -1
#endif
 
/**
 * \brief Number of BTS71220 devices in daisy chain
 * \ingroup bts71220
 */
#ifndef BTS71220_DAISY_CHAIN_SIZE
#define BTS71220_DAISY_CHAIN_SIZE   2
#endif
 
/**
 * \brief External hardware SPI interface
 */
typedef struct _hw_spi_t* hw_spi_t;
 
/**
 * \brief Initial config struct
 * \ingroup bts71220
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
    uint8_t dchain_size;
} bts71220_cfg_t;
 
/**
 * \brief BTS71220 power controller instance
 * \ingroup bts71220
 */
typedef struct
{
    int cs_pin;
    unsigned int spi_speed;
    uint8_t spi_mode;
    uint8_t spi_bit_order;
    hw_spi_t spi;
    uint8_t dchain_size;
} bts71220_t;
 
/*!
 * \brief Initializes default configuration
 * \ingroup bts71220
 *
 * \param cfg Initial config struct
 */
void bts71220_set_default_cfg(bts71220_cfg_t* cfg);
 
/*!
 * \brief Initializes hardware according to configuration
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param cfg Initial config struct
 * \return PLATFORM_SPI_INIT_ERR : error
 *         PLATFORM_GPIO_INIT_ERR : error
 *         PLATFORM_SPI_COM_ERR : error
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_init(bts71220_t* dev, bts71220_cfg_t* cfg);
 
/*!
 * \brief Generic SPI data transfer
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param txdata Byte to send to device
 * \param rxdata Pointer to receive response byte
 * \param dchain_num Number of device in daisy chain starting from 0
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_generic_transfer(bts71220_t* dev, uint8_t txdata, uint8_t* rxdata, uint8_t dchain_num);
 
/*!
 * \brief Write to register
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param reg Register to write
 * \param txdata Byte with contents of register
 * \param dchain_num Number of device in daisy chain starting from 0
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_write_reg(bts71220_t* dev, bts71220_reg_t reg, uint8_t txdata, uint8_t dchain_num);
 
/*!
 * \brief Read from register
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param reg Register to read from
 * \param rxdata Pointer to receive response byte with contents of register
 * \param dchain_num Number of device in daisy chain starting from 0
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_read_reg(bts71220_t* dev, bts71220_reg_t reg, uint8_t* rxdata, uint8_t dchain_num);
 
/*!
 * \brief Read standard diagnosis
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param rxdata Pointer to receive response byte with contents of register
 * \param dchain_num Number of device in daisy chain starting from 0
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_read_std_diag(bts71220_t* dev, uint8_t* rxdata, uint8_t dchain_num);
 
/*!
 * \brief Read warnings diagnosis
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param rxdata Pointer to receive response byte with contents of register
 * \param dchain_num Number of device in daisy chain starting from 0
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_read_wrn_diag(bts71220_t* dev, uint8_t* rxdata, uint8_t dchain_num);
 
/*!
 * \brief Read error diagnosis
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param rxdata Pointer to receive response byte with contents of register
 * \param dchain_num Number of device in daisy chain starting from 0
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_read_err_diag(bts71220_t* dev, uint8_t* rxdata, uint8_t dchain_num);
 
/*!
 * \brief Set current sense multiplexer
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \param mux Current sense multiplexer configuration to set
 * \param dchain_num Number of device in daisy chain starting from 0
 * \return PLATFORM_SPI_COM_ERR : error in coms
 *         PLATFORM_ARGUMENT_ERR : error in arguments
 *         PLATFORM_OK : successful
 */
bts71220_err_code_t bts71220_set_sense_mux(bts71220_t* dev, bts71220_sense_mux_t mux, uint8_t dchain_num);
 
/*!
 * \brief Enable CS for start SPI coms
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \note Should be implemented externally
 */
void bts71220_cs_select(bts71220_t* dev);
 
/*!
 * \brief Disable CS after SPI coms
 * \ingroup bts71220
 *
 * \param dev Pointer to BTS71220 power controller struct
 * \note Should be implemented externally
 */
void bts71220_cs_deselect(bts71220_t* dev);
 
#ifdef __cplusplus
}
#endif
 
#endif  // BTS71220_H
