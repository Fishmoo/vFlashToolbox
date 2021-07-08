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
**           File:  MemMap.h
**      Component:  Memory Mapping
**         Module:  -
**      Reference:  AUTOSAR 4.2.2/Software-Architecture_Implementation-Integration/AUTOSAR_SWS_MemoryMapping.pdf
**
**    Description:  Memory Sections Mapping of functions, variables and constants.
**
**  -------------------------------------------------------------------------------------------------------------------
**  MISRA VIOLATIONS
**  -------------------------------------------------------------------------------------------------------------------
**  -------------------------------------------------------------------------------------------------------------------
**  Number          MISRA Rule              Reason of violations
**  -------------------------------------------------------------------------------------------------------------------
**  Msg(6:0883)     Dir-4.10                - Include file code is not protected against repeated inclusion.
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
**  01.00.00  2018.03.28     YG             - Primary edition.
**********************************************************************************************************************/
	
/**********************************************************************************************************************
**  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
**  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

#ifndef MEM_VERSION_INFORMATION
#define MEM_VERSION_INFORMATION
/** AUTOSAR Software Specification Version Information.*/
    #define MEM_AR_MAJOR_VERSION                  0x04u
    #define MEM_AR_MINOR_VERSION                  0x02u
    #define MEM_AR_PATCH_VERSION                  0x02u

/** Component Version Information.*/
    #define MEM_SW_MAJOR_VERSION                  0x01u
    #define MEM_SW_MINOR_VERSION                  0x00u
    #define MEM_SW_PATCH_VERSION                  0x00u
#endif

#define MEMMAP_ERROR

/**********************************************************************************************************************
**  CODE SECTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
**  VAR SECTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
**  CONST SECTIONS
**********************************************************************************************************************/

/* =========================================================================================== */
/* ----------------------------GLOBAL-START-SECTIONS------------------------------------------ */
/* =========================================================================================== */
/*
** ========================================================================
** \brief: Code section open.
** ======================================================================== 
*/
#ifdef START_SEC_CODE
    #define CODE_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma CODE_SEG MyBswCode
    ** 2) PowerPC - #pragma push
    **              #pragma section code_type ".MyBswCode"
    ** 3) MB966xx - #pragma segment FAR_CODE=MyBswCode,attr=CODE
    */
    /* #pragma */
    #undef START_SEC_CODE                          
    #undef MEMMAP_ERROR
#endif

#ifdef START_SEC_CODE_FAST                     
    #define CODE_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma CODE_SEG USER_CODE_FAST_SECTION
    ** 2) PowerPC - #pragma 
    ** 3) MB966xx - #pragma segment CODE=USER_CODE_SECTION,attr=CODE
    */
    /*  #pragma */
    #undef START_SEC_CODE_FAST                     
    #undef MEMMAP_ERROR
#endif


#ifdef START_SEC_CODE_SLOW
    #define CODE_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*  #pragma */
    #undef START_SEC_CODE_SLOW
    #undef MEMMAP_ERROR
#endif
/*
** ========================================================================
** \brief: DATA section open.
** ========================================================================
*/

/* Var Init section - for .data.*/
#ifdef START_SEC_VAR_INIT_8BIT                 
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma DATA_SEG MyBswDATA
    ** 2) PowerPC - #pragma push
    **              #pragma section sdata_type data_type ".MyBswDATA"
    ** 3) MB966xx - #pragma segment DATA=MyBswDATA,attr=DATA
    */
    #undef START_SEC_VAR_INIT_8BIT                 
    #undef MEMMAP_ERROR
#endif
    
#ifdef START_SEC_VAR_INIT_16BIT                
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_INIT_16BIT                
    #undef MEMMAP_ERROR
#endif
    
#ifdef START_SEC_VAR_INIT_32BIT                
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_INIT_32BIT                
    #undef MEMMAP_ERROR
#endif
    
#ifdef START_SEC_VAR_INIT_UNSPECIFIED          
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_INIT_UNSPECIFIED          
    #undef MEMMAP_ERROR
#endif


/* Var No Init section - for .bss.*/
#ifdef START_SEC_VAR_NOINIT_8BIT               
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma DATA_SEG MyBswBSS
    ** 2) PowerPC - #pragma push
    **              #pragma section sdata_type data_type ".MyBswBSS"
    ** 3) MB966xx - #pragma segment DATA=MyBswBSS,attr=DATA
    */
    #undef START_SEC_VAR_NOINIT_8BIT               
    #undef MEMMAP_ERROR
#endif
    
#ifdef START_SEC_VAR_NOINIT_16BIT              
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_NOINIT_16BIT              
    #undef MEMMAP_ERROR
#endif
    
#ifdef START_SEC_VAR_NOINIT_32BIT              
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_NOINIT_32BIT              
    #undef MEMMAP_ERROR
#endif
    
#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED        
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_NOINIT_UNSPECIFIED        
    #undef MEMMAP_ERROR
#endif
    
/*
** ------------------------------------------------------------------------
** \brief : VAR POWER_ON_CLEARD sections.
** \note  : Used for variables that are cleared to zero only after power 
**          on reset(KAM).
** ------------------------------------------------------------------------
*/
/* Customized, for example.*/
#ifdef START_SEC_VAR_POWER_ON_CLEARD_ALIGNMENT              
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_POWER_ON_CLEARD_ALIGNMENT               
    #undef MEMMAP_ERROR
#endif

/*
** ------------------------------------------------------------------------
** \brief : VAR CLEARD sections(ZERO INIT).
** \note  : Used for variables that are cleared to zero after every reset.
** ------------------------------------------------------------------------
*/
/* Customized, for example.*/
#ifdef START_SEC_VAR_ZERO_INIT_ALIGNMENT           
    #define VAR_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_VAR_ZERO_INIT_ALIGNMENT           
    #undef MEMMAP_ERROR
#endif


/*
** ========================================================================
** \brief: CONST section open.
** ========================================================================
*/
#ifdef START_SEC_CONST_8BIT                    
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_CONST_8BIT                    
    #undef MEMMAP_ERROR
#endif
    
#ifdef START_SEC_CONST_16BIT                   
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_CONST_16BIT                   
    #undef MEMMAP_ERROR
#endif

#ifdef START_SEC_CONST_32BIT                   
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_CONST_32BIT                   
    #undef MEMMAP_ERROR
#endif

#ifdef START_SEC_CONST_UNSPECIFIED             
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_CONST_UNSPECIFIED             
    #undef MEMMAP_ERROR
#endif
    
/*
** ------------------------------------------------------------------------
** \brief : CONST FAST sections.
** \note  : To be used for constants accessed frequently(16-bit MCU,near 
**          mirror).
** ------------------------------------------------------------------------
*/
/* Customized, for example.*/
#ifdef START_SEC_CONST_FAST_ALIGNMENT              
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section */
    /*    #pragma */
    #undef START_SEC_CONST_FAST_ALIGNMENT               
    #undef MEMMAP_ERROR
#endif
/*
** ------------------------------------------------------------------------
** \brief : CALPRM sections.
** \note  : To be used for calibration constants.
** ------------------------------------------------------------------------
*/
/* Customized, for example.*/
#ifdef START_SEC_CALIB_ALIGNMENT              
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma CONST_SEG MyCAL_Section
    ** 2) PowerPC - #pragma push
    **              #pragma section const_type sconst_type ".MyCAL_Section"
    ** 3) MB966xx - #pragma segment CONST=MyCAL_Section,attr=CONST
    */
    #undef START_SEC_CONST_CALIB_ALIGNMENT               
    #undef MEMMAP_ERROR
#endif
/*
** ------------------------------------------------------------------------
** \brief : CONFIG DATA sections.
** \note  : Constants with attributes that show that they reside in one 
**          segment for module configuration.
** ------------------------------------------------------------------------ 
*/
/* Customized, for example.*/
#ifdef START_SEC_CONFIG_DATA_ALIGNMENT              
    #define CONST_SEC_OPEN
    /* Enter here a #pragma command for opening the specified section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma CONST_SEG MyConfigData_Section
    ** 2) PowerPC - #pragma push
    **              #pragma section const_type sconst_type ".MyConfigData_Section"
    ** 3) MB966xx - #pragma segment CONST=MyConfigData_Section,attr=CONST
    */
    #undef START_SEC_CONFIG_DATA_ALIGNMENT               
    #undef MEMMAP_ERROR
#endif


/* =========================================================================================== */
/* ---------------------------------GLOBAL-STOP-SECTIONS-------------------------------------- */
/* =========================================================================================== */
/*
** ========================================================================
** \brief: Code section close.
** ========================================================================
*/
#ifdef STOP_SEC_CODE
    #undef CODE_SEC_OPEN
    /* Enter here a #pragma command for closing the specified section!
    ** This should switch back to the default section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma CODE_SEG DEFAULT
    ** 2) PowerPC - #pragma pop
    ** 3) MB966xx - #pragma segment FAR_CODE=CODE,attr=CODE
    */
    #undef STOP_SEC_CODE
    #undef MEMMAP_ERROR
#endif

/*
** ========================================================================
** \brief: DATA section close.
** ========================================================================
*/
#ifdef STOP_SEC_VAR
    #undef VAR_SEC_OPEN
    /* Enter here a #pragma command for closing the specified section!
    ** This should switch back to the default section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma DATA_SEG DEFAULT
    ** 2) PowerPC - #pragma pop
    ** 3) MB966xx - #pragma segment DATA=DATA,attr=DATA
    */
    #undef STOP_SEC_VAR
    #undef MEMMAP_ERROR
#endif

/*
** ========================================================================
** \brief: Const section close.
** ========================================================================
*/
#ifdef STOP_SEC_CONST
    #undef CONST_SEC_OPEN
    /* Enter here a #pragma command for closing the specified section!
    ** This should switch back to the default section!
    **
    ** For example:
    ** 1) S12(x/z)- #pragma CONST_SEG DEFAULT
    ** 2) PowerPC - #pragma pop
    ** 3) MB966xx - #pragma segment CONST=CONST,attr=CONST
    */
    #undef STOP_SEC_CONST
    #undef MEMMAP_ERROR
#endif

/*********************************************************************************************************************/

/* EOF: MemMap.h */
