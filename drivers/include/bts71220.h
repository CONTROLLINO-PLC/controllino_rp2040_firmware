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
 * \brief Standard diagnosis respose structure
 * \ingroup bts71220
 */
typedef struct
{
    uint8_t vsmon : 1; /* VS monitor */
    uint8_t sbm : 1; /* Switch bypass monitor */
    uint8_t slp : 1; /* Sleep mode monitor */
    uint8_t lhi : 1; /* Limp home monitor */
    uint8_t csv : 1; /* Checksum verification */
    uint8_t ter : 1; /* Transmition error */
    uint8_t bit6_7 : 2; /* Don't care */
} bts71220_std_diag_t;
 
/**
 * \brief Warning channel diagnosis respose structure
 * \ingroup bts71220
 *
 * \note 0 No failure
 *       1 Overcurrent, Overtemperature or delta T detected
 */
typedef struct
{
    uint8_t ch0 : 1; /* Warning in channel 0 */
    uint8_t ch1 : 1; /* Warning in channel 1 */
    uint8_t ch2 : 1; /* Warning in channel 2 */
    uint8_t ch3 : 1; /* Warning in channel 3 */
    uint8_t bit4_7 : 4; /* Don't care */
} bts71220_wrn_diag_t;
 
/**
 * \brief Error channel diagnosis respose structure
 * \ingroup bts71220
 *
 * \note 0 No failure
 *       1 Channel latched OFF
 */
typedef struct
{
    uint8_t ch0 : 1; /* Error in channel 0 */
    uint8_t ch1 : 1; /* Error in channel 1 */
    uint8_t ch2 : 1; /* Error in channel 2 */
    uint8_t ch3 : 1; /* Error in channel 3 */
    uint8_t bit4_7 : 4; /* Don't care */
} bts71220_err_diag_t;
#ifdef __cplusplus
}
#endif
 
#endif  // BTS71220_H
