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
 
#include <stdio.h>
#include "hw_platform.h" /* External harware interface library */
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief Error codes
 * \ingroup bts71220
 */
typedef enum 
{
    BTS71220_OK =       PLATFORM_OK,
    BTS71220_ARG_ERR =  PLATFORM_ARGUMENT_ERR,
    BTS71220_INIT_ERR = PLATFORM_SPI_INIT_ERR,
    BTS71220_SPI_ERR =  PLATFORM_SPI_COM_ERR
} bts71220_err_code_t;
 
/**
 * \brief Register addresses  RB + ADDR0 + ADDR1
 * \ingroup bts71220
 */
typedef enum {
    BTS71220_REG_OUT =  0b0000000,
    BTS71220_REG_RCS =  0b0001000,
    BTS71220_REG_SRC =  0b0001001,
    BTS71220_REG_OCR =  0b1000100,
    BTS71220_REG_RCD =  0b1001100,
    BTS71220_REG_KRC =  0b1010101,
    BTS71220_REG_PCS =  0b1011101,
    BTS71220_REG_HWCR = 0b1100110,
    BTS71220_REG_ICS =  0b1101110,
    BTS71220_REG_DCR =  0b1111111,
} bts71220_reg_t;
 
/**
 * \brief Bit masks
 * \ingroup bts71220
 */
#define BTS71220_BIT7_MASK  0b10000000
#define BTS71220_RB_MASK    0b01000000
#define BTS71220_ADRR0_MASK 0b00110000
#define BTS71220_ADRR1_MASK 0b00001111
#define BTS71220_CH0_MASK   0b00000001
#define BTS71220_CH1_MASK   0b00000010
#define BTS71220_CH2_MASK   0b00000100
#define BTS71220_CH3_MASK   0b00001000
 
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
#define BTS71220_CH_ERR_WARN        0b1 /* Warning:Overcurrent, Overtemperature or delta T detected, Error:Channel latched OFF*/
 
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

#define BTS71220_DCR_MUX_IS_CH0     0b000
#define BTS71220_DCR_MUX_IS_CH1     0b001
#define BTS71220_DCR_MUX_IS_CH2     0b010
#define BTS71220_DCR_MUX_IS_CH3     0b011
#define BTS71220_DCR_MUX_IS_VERIF   0b101
#define BTS71220_DCR_MUX_IS_Z       0b110
#define BTS71220_DCR_MUX_IS_SLEEP_Z 0b111

#define BTS71220_DCR_MUX_SWR_WR_ALL  0b0 /* Default */
#define BTS71220_DCR_MUX_SWR_WR_SOME 0b1 

#ifdef __cplusplus
}
#endif
 
#endif  // BTS71220_H
