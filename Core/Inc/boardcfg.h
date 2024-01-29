/*****************************************************************************************
* (C) Copyright 2016 Nanjing Shufan Information Technology Co.,Ltd.
*
* File Name        : boardcfg.h
*
* File Description : Header file for device configure.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2016.7.28
*
* Modification Rec.:
*   Modify Data    : 2016.7.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
********************************************************************/

#ifndef _BOARDCFG_H_
#define _BOARDCFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IAR

#define DEBUG_MODE_OPEN       0        /* open debug mode for debug.  */
#define DEBUG_TEST_OPEN       0        /* open test mode for testing. */

/** the programer should define the cpu type by the follow macro define. **/
//#define STM32F10X_HD                    /* High-density devices,256 and 512 K    */
/* #define STM32F10X_XL      */         /* XL-density devices,768 Kbytes and 1 M */
/* #define STM32F10X_CL      */         /* Connectivity line devices             */
/* #define STM32F10X_LD_VL   */         /* Low-density devices,16 and 32 K       */
//#define STM32F10X_MD_VL                 /* Medium-density devices,64 and 128 K   */
#define STM32F10X_MD

/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application 
   
   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */           
#if !defined  HSE_Value
 #ifdef STM32F10X_CL   
  /*!< Value of the External oscillator in Hz */
  #define HSE_Value    (25000000)
 #else 
  /*!< Value of the External oscillator in Hz */
  #define HSE_Value    (CLK0_FREQ_HZ)
 #endif /* STM32F10X_CL */
#endif /* HSE_Value */

#if defined (STM32F10X_LD_VL) || (defined STM32F10X_MD_VL) 
    /* #define SYSCLK_FREQ_HSE    HSE_Value */
     #define SYSCLK_FREQ_24MHz  24000000
     #define SYS_CLK            SYSCLK_FREQ_24MHz
#else
    //#define SYSCLK_FREQ_HSE    HSE_Value
    //#define SYSCLK_FREQ_32MHz  32000000
    //#define SYSCLK_FREQ_36MHz  36000000
    #define SYSCLK_FREQ_48MHz  48000000                   /* Max. freq. is 48M. */
    #define SYS_CLK             SYSCLK_FREQ_48MHz            /* it should be equal to SYSCLK_FREQ_XXMHz defined before.*/
    #if defined (SYSCLK_FREQ_48MHz)
        #define SYS_MCLK           48
    #elif defined (SYSCLK_FREQ_36MHz)
        #define SYS_MCLK           36
    #elif defined (SYSCLK_FREQ_32MHz)
        #define SYS_MCLK           32
    #endif
#endif



#ifdef __cplusplus
}
#endif

#endif /* _BOARDCFG_H_ */





