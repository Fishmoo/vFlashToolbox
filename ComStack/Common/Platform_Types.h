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
**         File:  Platform_Types.h
**    Component:  -
**       Module:  -
**    Reference:  AUTOSAR 4.2/Software-Architecture_Implementation-Integration/AUTOSAR_SWS_PlatformTypes.pdf
**
**  Description:  Provision of Platform Types for SPC5xxx
**
**  -------------------------------------------------------------------------------------------------------------------
**  MISRA VIOLATIONS
**  -------------------------------------------------------------------------------------------------------------------
**
**********************************************************************************************************************/

/**********************************************************************************************************************
**  AUTHOR IDENTITY
**  -------------------------------------------------------------------------------------------------------------------
**  Name                    Initials        Company
**  -------------------------------------------------------------------------------------------------------------------
**  YuGui                   YG              CJAE
**  -------------------------------------------------------------------------------------------------------------------
**  REVISION HISTORY
**  -------------------------------------------------------------------------------------------------------------------
**  Version   Date          Author          Description
**  -------------------------------------------------------------------------------------------------------------------
**  01.00.00  2017-12-19    YG              Initial creation.
**********************************************************************************************************************/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/**********************************************************************************************************************
** INCLUDES
**********************************************************************************************************************/

#include "v_def.h"

/**********************************************************************************************************************
**  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/* Component Vendor ID and AUTOSAR Implementation Module ID.*/
#define PLATFORM_VENDOR_ID                      (0x1999u)
#define PLATFORM_MODULE_ID                      (199u)

/* AUTOSAR Software Specification Document Version Information.*/
/* AUTOSAR Document version 2.2.1 part of release 4.2.2 */
#define PLATFORM_AR_MAJOR_VERSION               (0x04u)
#define PLATFORM_AR_MINOR_VERSION               (0x02u)
#define PLATFORM_AR_PATCH_VERSION               (0x02u)

/* Component Version Information */
#define PLATFORM_SW_MAJOR_VERSION               (0x01u)
#define PLATFORM_SW_MINOR_VERSION               (0x00u)
#define PLATFORM_SW_PATCH_VERSION               (0x00u)

/**
 * CPU types.
 *
 * For each platform the register width of the CPU used shall be
 * indicated by defining CPU_TYPE.
 */
#define CPU_TYPE_8          8u     /* Indicating a 8 bit processor. */
#define CPU_TYPE_16         16u    /* Indicating a 16 bit processor.*/
#define CPU_TYPE_32         32u    /* Indicating a 32 bit processor.*/

/**
 *  Bit Ordering (Register).
 *
 *  For each platform the appropriate bit order on register level
 *  shall be indicated in the platform types header file using the symbol
 *  CPU_BIT_ORDER.
 */
#define MSB_FIRST           0u    /* big endian bit ordering.*/
#define LSB_FIRST           1u    /* little endian bit ordering.*/

/**
 * Byte Ordering (Memory).
 *
 * For each platform the appropriate byte order on memory
 * level shall be indicated in the platform types header file using the symbol
 * CPU_BYTE_ORDER.
 */
#define HIGH_BYTE_FIRST     0u    /* big endian byte ordering.*/
#define LOW_BYTE_FIRST      1u    /* little endian byte ordering.*/

/* Boolean data type.*/
#ifndef TRUE
 #define TRUE               1u
#endif

#ifndef FALSE
 #define FALSE              0u
#endif

/* ================================================================ */
/* -------------------- !! USER SPECIFY !! ------------------------ */
/* ================================================================ */
#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       MSB_FIRST
#define CPU_BYTE_ORDER      HIGH_BYTE_FIRST
                      
/**********************************************************************************************************************
**  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

typedef unsigned char       boolean;        /*         TRUE .. FALSE        */

typedef signed char         sint8;          /*         -128 .. +127         */
typedef unsigned char       uint8;          /*            0 .. 255          */
typedef signed short        sint16;         /*       -32768 .. +32767       */
typedef unsigned short      uint16;         /*            0 .. 65535        */
typedef signed long         sint32;         /*  -2147483648 .. +2147483647  */
typedef unsigned long       uint32;         /*            0 .. 4294967295   */

 
/* The optimized AUTOSAR integer data types.*/
typedef signed int          sint8_least;    /* At least 7 bit + 1 bit sign  */
typedef unsigned int        uint8_least;    /* At least 8 bit               */
typedef signed int          sint16_least;   /* At least 15 bit + 1 bit sign */
typedef unsigned int        uint16_least;   /* At least 16 bit              */
typedef signed long         sint32_least;   /* At least 31 bit + 1 bit sign */
typedef unsigned long       uint32_least;   /* At least 32 bit              */

#if (0)
/**
 * Fill in the following 64 bit integer data types only if the platform + compiler support them.
 * Otherwise please remove the data types (including the define "PLATFORM_SUPPORT_SINT64_UINT64").
 * In case of the compiler specific keyword(s) required for definition of the 64 bit integer data types depends on
 * - used compiler at all
 * - on specific compiler option(s)
 * then please encapsulate the definition of these types (including the define "PLATFORM_SUPPORT_SINT64_UINT64")
 * by the corresponding compiler specific define!
 */
#define PLATFORM_SUPPORT_SINT64_UINT64
typedef signed   long long  sint64;         /* -9223372036854775808 .. 9223372036854775807  */
typedef unsigned long long  uint64;         /*                    0 .. 18446744073709551615 */
#endif
                                        
typedef float               float32;
typedef double              float64;

/* qualifier for bitfield definition.*/
typedef unsigned int        vbittype;

/**********************************************************************************************************************
**  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
 
/**********************************************************************************************************************
**  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

 
#endif  /* PLATFORM_TYPES_H */

/**********************************************************************************************************************
**  END OF FILE: Platform_Types.h
**********************************************************************************************************************/
