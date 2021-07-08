/**********************************************************************************************************************
**  COPYRIGHT
**  -------------------------------------------------------------------------------------------------------------------
**
**  Copyright (c) 2007 by ChongQing JiCheng Automotive Electronics CO.,LTD(CJAE).               All rights reserved.
**
**                This software is copyright protected and proprietary to CJAE.
**                CJAE to you only those rights as set out in the license conditions.
**                All other rights remain with CJAE.
**
**  -------------------------------------------------------------------------------------------------------------------
**  FILE DESCRIPTION
**  -------------------------------------------------------------------------------------------------------------------
**         File:  Std_Types.h
**    Component:  -
**       Module:  -
**    Reference:  AUTOSAR 4.2.2/AUTOSAR_SWS_StandardTypes.pdf
**
**  Description:  Provision of Standard Types
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
**  01.00.00  2017-12-19    YG              - Initial creation.
**  01.01.01  2018.03.28    YG              - Add PREPROCESSOR CONSTANTS DEFINES of Platform_Types.
**********************************************************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/**********************************************************************************************************************
** INCLUDES
**********************************************************************************************************************/

#include "Compiler.h"
#include "Platform_Types.h"

/**********************************************************************************************************************
**  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/* Component Vendor ID and AUTOSAR Implementation Module ID.*/
#define STD_TYPES_VENDOR_ID                 (0x1999u)
#define STD_TYPES_MODULE_ID                 (197u)


/* AUTOSAR Software Specification Version Information.*/
#define STD_TYPES_AR_MAJOR_VERSION          (0x04u)
#define STD_TYPES_AR_MINOR_VERSION          (0x02u)
#define STD_TYPES_AR_PATCH_VERSION          (0x02u)

/* Component Version Information */
#define STD_TYPES_SW_MAJOR_VERSION          (0x01u)
#define STD_TYPES_SW_MINOR_VERSION          (0x00u)
#define STD_TYPES_SW_PATCH_VERSION          (0x00u)

/* Standard Logic electrical level state.*/
#define STD_HIGH                            (0x01u) /* Physical state 5V or 3.3V.*/
#define STD_LOW                             (0x00u) /* Physical state 0V.*/

/* Standard Logic state.*/
#define STD_ACTIVE                          (0x01u) /* Logical state active.*/
#define STD_IDLE                            (0x00u) /* Logical state idle.*/

#define STD_ON                              (0x01u)
#define STD_OFF                             (0x00u)

/* Non-ASR define.*/
#if !defined (FALSE)
#define FALSE                               (0U)
#endif

#if !defined (TRUE)
#define TRUE                                (1U)
#endif

/**********************************************************************************************************************
**  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/* ============================================================ */
/* ---------------- STANDARD ERROR CODE DEFINE ---------------- */
/* ============================================================ */
/* 0x00~0x01 - AutoSAR specified.*/
#ifndef STATUSTYPEDEFINED
# define STATUSTYPEDEFINED
#  ifndef E_OK
#  define E_OK          0x00u
#  endif
typedef unsigned char StatusType; /* OSEK compliance */
#endif

#ifndef E_NOT_OK
#define E_NOT_OK        0x01u
#endif
/* 0x02~0x3F - Available to user specific errors.*/
#ifndef E_PENDING
#define E_PENDING       0x02u
#endif

/* 0x40~0xFF - Reserved by RTE.*/
typedef uint8 Std_ReturnType;

/* ============================================================ */
/* --------------- STANDARD VERSION INFO DEFINE --------------- */
/* ============================================================ */
typedef struct {
    uint16  vendorID;
    uint16  moduleID;
    uint8   instanceID;
    uint8   sw_major_version;
    uint8   sw_minor_version;
    uint8   sw_patch_version;
} Std_VersionInfoType;

/**********************************************************************************************************************
**  PREPROCESSOR CONSTANTS DEFINES
**********************************************************************************************************************/


/**********************************************************************************************************************
**  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

#endif  /* STD_TYPES_H */

/**********************************************************************************************************************
**  END OF FILE: Std_Types.h
**********************************************************************************************************************/
