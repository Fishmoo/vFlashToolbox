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
**         File:  Compiler.h
**    Component:  -
**       Module:  -
**    Reference:  AUTOSAR 4.2/Software-Architecture_Implementation-Integration/AUTOSAR_SWS_CompilerAbstraction.pdf
**
**  Description:  This file provides the AUTOSAR compiler abstraction for the Freescale/Metrowerks CodeWarrior compiler
**                Supported compiler:           Freescale/Metrowerks CodeWarrior PowerPC
**                Supported compiler version:   2.x
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

#ifndef COMPILER_H
#define COMPILER_H

/**********************************************************************************************************************
** INCLUDES
**********************************************************************************************************************/

#include "Compiler_Cfg.h"

/**********************************************************************************************************************
**  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/* Component Vendor ID and AUTOSAR Implementation Module ID.*/
#define COMPILER_VENDOR_ID                  (0x1999u)
#define COMPILER_MODULE_ID                  (198u)
 
/* AUTOSAR Software Specification Document Version Information.*/
/*           Part of AUTOSAR Release 4.2                       */
#define COMPILER_AR_MAJOR_VERSION           (0x04u)
#define COMPILER_AR_MINOR_VERSION           (0x02u)
#define COMPILER_AR_PATCH_VERSION           (0x02u)

/* Component Version Information.*/
#define COMPILER_SW_MAJOR_VERSION           (0x01u)
#define COMPILER_SW_MINOR_VERSION           (0x00u)
#define COMPILER_SW_PATCH_VERSION           (0x00u)

/**
 * The memory class AUTOMATIC shall be provided as empty definition,
 * used for the declaration of local pointers.
 */
#define AUTOMATIC

/**
 * The memory class TYPEDEF shall be provided as empty definition. This memory
 * class shall be used within type definitions, where no memory qualifier can be
 * specified. This can be necessary for defining pointer types, with e.g. P2VAR,
 * where the macros require two parameters.
 */
#define TYPEDEF

/* NULL_PTR define with a void pointer to zero definition.*/
#ifndef NULL_PTR
# define NULL_PTR           ((void*)0L)
#endif

/**********************************************************************************************************************
**  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


#endif  /* COMPILER_H */

/**********************************************************************************************************************
**  END OF FILE: Compiler.h
**********************************************************************************************************************/
