/**********************************************************************************************************************
**  COPYRIGHT
**  -------------------------------------------------------------------------------------------------------------------
**
**  Copyright (c) by ChongQing JiCheng Automotive Electronics CO.,LTD(CJAE).               All rights reserved.
**
**                This software is copyright protected and proprietary to CJAE.
**                CJAE grants to you only those rights as set out in the license conditions.
**                All other rights remain with CJAE.
**
**  -------------------------------------------------------------------------------------------------------------------
**  FILE DESCRIPTION
**  -------------------------------------------------------------------------------------------------------------------
**           File:  v_def.h
**      Component:  -.
**         Module:  -.
**      Reference:  -.
**
**    Description:  Declares types and definitions common.
**
**  -------------------------------------------------------------------------------------------------------------------
**  MISRA VIOLATIONS
**  -------------------------------------------------------------------------------------------------------------------
**  Number          MISRA Rule              Reason of violations
**  -------------------------------------------------------------------------------------------------------------------
**
**********************************************************************************************************************/

/**********************************************************************************************************************
**  AUTHOR IDENTITY
**  -------------------------------------------------------------------------------------------------------------------
**  Name                     Initials       Company
**  -------------------------------------------------------------------------------------------------------------------
**  YuGui                    YG             ChongQing JiCheng Automotive Electronics CO.,LTD
**  -------------------------------------------------------------------------------------------------------------------
**  REVISION HISTORY
**  -------------------------------------------------------------------------------------------------------------------
**  Version   Date           Author         Description
**  -------------------------------------------------------------------------------------------------------------------
**  01.00.00  2018-03-28     YG             - Primary edition.
**********************************************************************************************************************/

#ifndef V_DEF_H
#define V_DEF_H

/**********************************************************************************************************************
**  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  VERSION DEFINES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

#define COMMON_MAGIC_NUMBER         0x01280818u

/* NULL define.*/
#ifndef V_NULL
# define V_NULL ((void*)0)
#endif

#ifndef NULL
# define NULL   V_NULL
#endif

/* Helper macro to get number of array entries.*/
#define ARRAY_SIZE(arr)             (sizeof(arr) / sizeof((arr)[0]))

/* The bit index mapping order of BYTE.*/
#define BYTE_BIT0                   0x01u
#define BYTE_BIT1                   0x02u
#define BYTE_BIT2                   0x04u
#define BYTE_BIT3                   0x08u
#define BYTE_BIT4                   0x10u
#define BYTE_BIT5                   0x20u
#define BYTE_BIT6                   0x40u
#define BYTE_BIT7                   0x80u

/**********************************************************************************************************************
**  PREPROCESSOR CONSTANTS DEFINES
**********************************************************************************************************************/
/* -----------------------------------------------------------------------------
    &&&~ Specify the length of enumeration type.
 ----------------------------------------------------------------------------- */
#define ENUM_LEN_BYTE               (0u)
#define ENUM_LEN_WORD               (1u)
#define ENUMERATION_LENGTH          ENUM_LEN_WORD

/**********************************************************************************************************************
**  TYPEDEFS
**********************************************************************************************************************/

/* ============================================================================================= */
/* ------------------------------ Hardware independent settings  ------------------------------- */
/* ============================================================================================= */
typedef unsigned char   *TxDataPtr;              /* ptr to transmission data buffer */
typedef unsigned char   *RxDataPtr;              /* ptr to receiving data buffer    */

/* Structure for bit accessed memory.           */
/* The bit-order is hardware/compiler dependent */
#if (0)
#if defined( C_CPUTYPE_BITORDER_LSB2MSB )
struct _c_bits8
{
  vbittype  b0:1;  /* LSB-Bits (lower adr!) */
  vbittype  b1:1;
  vbittype  b2:1;
  vbittype  b3:1;
  vbittype  b4:1;
  vbittype  b5:1;
  vbittype  b6:1;
  vbittype  b7:1;  /* MSB-Bits (higher address) unused */
 };

struct _c_bits16
{
  vbittype  b0:1;  /* lower adr */
  vbittype  b1:1;
  vbittype  b2:1;
  vbittype  b3:1;
  vbittype  b4:1;
  vbittype  b5:1;
  vbittype  b6:1;
  vbittype  b7:1;

  vbittype  b10:1; /* higher adr */
  vbittype  b11:1;
  vbittype  b12:1;
  vbittype  b13:1;
  vbittype  b14:1;
  vbittype  b15:1;
  vbittype  b16:1;
  vbittype  b17:1;
};

#else
# if defined( C_CPUTYPE_BITORDER_MSB2LSB )
struct _c_bits8
{
  vbittype  b7:1;  /* MSB-Bits (Higher addr!) */
  vbittype  b6:1;
  vbittype  b5:1;
  vbittype  b4:1;
  vbittype  b3:1;
  vbittype  b2:1;
  vbittype  b1:1;
  vbittype  b0:1;  /* LSB-Bits (higher address) unused */
};

struct _c_bits16
{
  vbittype  b7:1;   /* lower adr */
  vbittype  b6:1;
  vbittype  b5:1;
  vbittype  b4:1;
  vbittype  b3:1;
  vbittype  b2:1;
  vbittype  b1:1;
  vbittype  b0:1;

  vbittype  b17:1;  /* higher adr */
  vbittype  b16:1;
  vbittype  b15:1;
  vbittype  b14:1;
  vbittype  b13:1;
  vbittype  b12:1;
  vbittype  b11:1;
  vbittype  b10:1;
};
# else
#  error "Bitorder unknown: C_CPUTYPE_BITORDER_MSB2LSB or C_CPUTYPE_BITORDER_LSB2MSB has to be defined"
# endif /* C_CPUTYPE_BITORDER_MSB2LSB */
#endif  /* C_CPUTYPE_BITORDER_LSB2MSB */
#endif



/**********************************************************************************************************************
**  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


#endif /* V_DEF_H.*/

/*********************************************************************************************************************/

/* EOF: v_def.h */
