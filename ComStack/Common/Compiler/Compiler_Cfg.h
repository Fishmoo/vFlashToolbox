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
**         File:  Compiler_Cfg.h
**    Component:  -
**       Module:  -
**    Reference:  AUTOSAR 4.2/Software-Architecture_Implementation-Integration/AUTOSAR_SWS_CompilerAbstraction.pdf
**
**  Description:  -
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
**  01.00.00  2018.03.28    YG              - Initial creation.
**********************************************************************************************************************/

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/**********************************************************************************************************************
** INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**
 * Range: "empty"/__inline__/inline.
 *
 * The compiler abstraction shall provide the INLINE define for abstraction of
 * the keyword inline.
 */
#ifndef INLINE
# define INLINE
#endif

/**
 * Range: "empty"/static __inline__/static inline.
 *
 * The compiler abstraction shall provide the LOCAL_INLINE define for abstraction
 * of the keyword inline in functions with ¡°static¡± scope.
 */
#ifndef LOCAL_INLINE
# define LOCAL_INLINE
#endif

/* STATIC define for abstraction of compiler keyword static.*/
#define STATIC              static

/**
 * FUNC macro for the declaration and definition of functions that ensures correct syntax of
 * function declarations as required by a specific compiler.
 *
 * rettype  - return type of the function.
 * memclass - classification of the function itself.
 */
#define FUNC(rettype, memclass)                     (rettype)

/**
 * FUNC_P2CONST macro for the declaration and definition of functions returning a pointer to
 * a constant. This shall ensure the correct syntax of function declarations as required by
 * a specific compiler.
 *
 * rettype  - return type of the function.
 * ptrclass - defines the classification of the pointer¡¯s distance.
 * memclass - classification of the function itself.
 */
#define FUNC_P2CONST(rettype, ptrclass, memclass)   const (rettype)*

/**
 * FUNC_P2VAR macro for the declaration and definition of functions returning a pointer to
 * a variable. This shall ensure the correct syntax of function declarations as required by
 * a specific compiler.
 *
 * rettype  - return type of the function.
 * ptrclass - defines the classification of the pointer¡¯s distance.
 * memclass - classification of the function itself.
 */
#define FUNC_P2VAR(rettype, ptrclass, memclass)     (rettype)*

/**
 * P2VAR macro for the declaration and definition of pointers in RAM, pointing to variables.
 *
 * ptrtype  - type of the referenced variable memory class.
 * memclass - classification of the pointer variable itself.
 * ptrclass - defines the classification of the pointer's distance.
 */
#define P2VAR(ptrtype, memclass, ptrclass)          (ptrtype)*

/**
 * P2CONST macro for the declaration and definition of pointers in RAM pointing to constants.
 *
 * ptrtype  - type of the referenced data.
 * memclass - classification of the pointer variable itself.
 * ptrclass - defines the classification of the pointer distance.
 */
#define P2CONST(ptrtype, memclass, ptrclass)        const (ptrtype)*

/**
 * CONSTP2VAR macro for the declaration and definition of constant pointers accessing variables.
 *
 * ptrtype  - type of the referenced data.
 * memclass - classification of the pointer variable itself.
 * ptrclass - defines the classification of the pointer distance.
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass)     (ptrtype)* const

/**
 * CONSTP2CONST macro for the declaration and definition of constant pointers accessing constants.
 *
 * ptrtype  - type of the referenced data.
 * memclass - classification of the pointer variable itself.
 * ptrclass - defines the classification of the pointer distance.
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)   const (ptrtype)* const

/**
 * P2FUNC macro for the type definition of pointers to functions.
 *
 * rettype  -  return type of the function.
 * ptrclass - defines the classification of the pointer distance.
 * fctname  - function name respectively name of the defined type.
 */
#define P2FUNC(rettype, ptrclass, fctname)          (rettype) (*(fctname))

/**
 * CONSTP2FUNC macro for the type definition of pointers to functions.
 *
 * rettype  - return type of the function.
 * ptrclass - defines the classification of the pointer distance.
 * fctname  - function name respectively name of the defined type.
 *
 * Example :
 * (PowerPC): #define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)
 * (CodeWarrior, S12X): #define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const ptrclass fctname)
 */
#define CONSTP2FUNC(rettype, ptrclass, fctname)     (rettype) (* const (fctname))

/**
 * CONST macro for the declaration and definition of constants.
 *
 * type     - type of the constant.
 * memclass - classification of the constant itself.
 */
#define CONST(type, memclass)           const (type)

/**
 * VAR macro for the declaration and definition of variables.
 *
 * vartype  - type of the variable.
 * memclass - classification of the variable itself.
 */
#define VAR(vartype, memclass)          (vartype)


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


#endif  /* COMPILER_CFG_H */

/**********************************************************************************************************************
**  END OF FILE: Compiler_Cfg.h
**********************************************************************************************************************/
