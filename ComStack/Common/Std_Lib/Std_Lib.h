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
**           File:  Std_Lib.h
**      Component:  -
**         Module:  -
**      Generator:  -
**
**    Description:  
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
**  01.00.00  2018-10-30     YG             Primary edition.
**  01.00.01  2018-11-28     YG             Increase  function macro interface Std_Lib_MemSet/Std_Lib_MemCpy.
**
**********************************************************************************************************************/

#ifndef COMMON_STD_LIB_STD_LIB_H_
#define COMMON_STD_LIB_STD_LIB_H_

/**********************************************************************************************************************
**  INCLUDES
**********************************************************************************************************************/

#include "Std_Types.h"

/**********************************************************************************************************************
**  CONFIGURATION SWITCHES
**********************************************************************************************************************/

/* PRQA S 3458 L1 */ /* MD_MSR_19.4 */
#define LIB_ENTER_EXCLUSIVE_AREA_0()
#if (0)
    \
    { \
        SuspendAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */ \
    }
#endif
/* PRQA L:L1 */

/* PRQA S 3458 L1 */ /* MD_MSR_19.4 */
#define LIB_EXIT_EXCLUSIVE_AREA_0()
#if (0)
    { \
        ResumeAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */ \
    }
#endif
/* PRQA L:L1 */

/**********************************************************************************************************************
**  PREPROCESSOR CONSTANTS DEFINES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

#define Std_Lib_MemSet(pDest, Pattern, Length)\
{\
  uint16 iCnt = (Length);\
  while(iCnt > (uint16)0x0000)\
  {\
    iCnt--;\
    (pDest)[iCnt] = (Pattern);\
  }\
}

#define Std_Lib_MemCpy(pDest, pSrc, Length)\
{\
  uint16 iCnt = (Length);\
  while(iCnt > (uint16)0x0000)\
  {\
    iCnt--;\
    (pDest)[iCnt] = (pSrc)[iCnt];\
  }\
}

/**********************************************************************************************************************
**  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

extern void   Std_Lib_SetMemory(uint8 *pStr, uint8 val, uint16 len);
extern void   Std_Lib_MemCopy(uint8 *pDes, uint8 *pSrc, uint16 len);
extern void   Std_Lib_BubbleSort(uint16 *pData, uint8 length);
extern uint16 Std_lib_CalcAverage(const uint16 *pData, uint8 length);


#endif /* COMMON_STD_LIB_STD_LIB_H_.*/

/*********************************************************************************************************************/

/* EOF: Std_Lib.h */
