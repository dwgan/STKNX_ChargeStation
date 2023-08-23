/******************************************************************************
* File       : rcc.h
* Function   : Reset and clock control
* description: Realise the system clock configuration.
*              *NOTE*: Extern crystal frequency should be defined in Boardctrl.h 
* Version    : V1.00
* Author     : Ian
* Date       : 30th Jul 2016
* History    :  No.  When           Who           What
*               1    30/Jul/2016    Ian           Create
******************************************************************************/


#ifndef _RCC_H_
#define _RCC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if the max AHB clock is defined or NOT */
#ifndef MAX_AHB_CLK_IN_MHZ
#if defined(__STM32F103)
#define MAX_AHB_CLK_IN_MHZ                   (72)                              /* 72MHz is the max AHB clock for STM32F103  */
#elif defined(__STM32101)
#define MAX_AHB_CLK_IN_MHZ                   (36)                              /* 36MHz is the max AHB clock for STM32F101  */
#else
#define MAX_AHB_CLK_IN_MHZ                   (36)                              /* 36MHz is the max AHB clock for the others */
#endif
#endif

#define RCC_BASE                             ((T_RCC_MEM_MAP)0x40021000U)      /* Address of RCC base register */

#define RCC_CR                               (RCC_BASE->CR)                    /* Address of clock control register   */
#define RCC_CFGR                             (RCC_BASE->CFGR)                  /* Address of clock configure register */
#define RCC_CIR                              (RCC_BASE->CIR)                   /* Address of clock interrupt register */
#define RCC_APB2RSTR                         (RCC_BASE->APB2RSTR)              /* Address of APB2 reset register      */
#define RCC_APB1RSTR                         (RCC_BASE->APB1RSTR)              /* Address of APB1 reset register      */
#define RCC_AHBENR                           (RCC_BASE->AHBENR)                /* Address of AHB enable register      */
#define RCC_APB2ENR                          (RCC_BASE->APB2ENR)               /* Address of APB2 enable register     */
#define RCC_APB1ENR                          (RCC_BASE->APB1ENR)               /* Address of APB1 enable register     */
#define RCC_BDCR                             (RCC_BASE->BDCR)                  /* Address of backup control register  */
#define RCC_CSR                              (RCC_BASE->CSR)                   /* Address of control/status register  */

#define RCC_CR_DEFAULT_VAL                   (0x00000083U)                     /* Default value of clock control register   */
#define RCC_CFGR_DEFAULT_VAL                 (0x00000000U)                     /* Default value of clock configure register */
#define RCC_CIR_DEFAULT_VAL                  (0x00000000U)                     /* Default value of clock interrupt register */
#define RCC_APB2RSTR_DEFAULT_VAL             (0x00000000U)                     /* Default value of APB2 reset register      */
#define RCC_APB1RSTR_DEFAULT_VAL             (0x00000000U)                     /* Default value of APB1 reset register      */
#define RCC_AHBENR_DEFAULT_VAL               (0x00000014U)                     /* Default value of AHB enable register      */
#define RCC_APB2ENR_DEFAULT_VAL              (0x00000000U)                     /* Default value of APB2 enable register     */
#define RCC_APB1ENR_DEFAULT_VAL              (0x00000000U)                     /* Default value of APB1 enable register     */
#define RCC_BDCR_DEFAULT_VAL                 (0x00000000U)                     /* Default value of backup control register  */
#define RCC_CSR_DEFAULT_VAL                  (0x0C000000U)                     /* Default value of control/status register  */

/* Bit definition for RCC_CR register */
#define RCC_CR_HSION_POS                     (0U)                              
#define RCC_CR_HSION_MASK                    (0x00000001)                      /* 0x00000001                       */
#define RCC_CR_HSION                         (RCC_CR_HSION_MASK)               /* Internal High Speed clock enable */
#define RCC_CR_HSIRDY_POS                    (1U)                              
#define RCC_CR_HSIRDY_MASK                   (0x00000002)                      /* 0x00000002                           */
#define RCC_CR_HSIRDY                        (RCC_CR_HSIRDY_MASK)              /* Internal High Speed clock ready flag */
#define RCC_CR_HSITRIM_POS                   (3U)                              
#define RCC_CR_HSITRIM_MASK                  (0x000000F8)                      /* 0x000000F8                         */
#define RCC_CR_HSITRIM                       (RCC_CR_HSITRIM_MASK)             /* Internal High Speed clock trimming */
#define RCC_CR_HSICAL_POS                    (8U)                              
#define RCC_CR_HSICAL_MASK                   (0x0000FF00)                      /* 0x0000FF00                            */
#define RCC_CR_HSICAL                        (RCC_CR_HSICAL_MASK)              /* Internal High Speed clock Calibration */
#define RCC_CR_HSEON_POS                     (16U)                             
#define RCC_CR_HSEON_MASK                    (0x00010000)                      /* 0x00010000                       */
#define RCC_CR_HSEON                         (RCC_CR_HSEON_MASK)               /* External High Speed clock enable */
#define RCC_CR_HSERDY_POS                    (17U)                             
#define RCC_CR_HSERDY_MASK                   (0x00020000)                      /* 0x00020000                           */
#define RCC_CR_HSERDY                        (RCC_CR_HSERDY_MASK)              /* External High Speed clock ready flag */
#define RCC_CR_HSEBYP_POS                    (18U)                             
#define RCC_CR_HSEBYP_MASK                   (0x00040000)                      /* 0x00040000                       */
#define RCC_CR_HSEBYP                        (RCC_CR_HSEBYP_MASK)              /* External High Speed clock Bypass */
#define RCC_CR_CSSON_POS                     (19U)                             
#define RCC_CR_CSSON_MASK                    (0x00080000)                      /* 0x00080000                   */
#define RCC_CR_CSSON                         (RCC_CR_CSSON_MASK)               /* Clock Security System enable */
#define RCC_CR_PLLON_POS                     (24U)                             
#define RCC_CR_PLLON_MASK                    (0x01000000)                      /* 0x01000000 */
#define RCC_CR_PLLON                         (RCC_CR_PLLON_MASK)               /* PLL enable */
#define RCC_CR_PLLRDY_POS                    (25U)                             
#define RCC_CR_PLLRDY_MASK                   (0x02000000)                      /* 0x02000000           */
#define RCC_CR_PLLRDY                        (RCC_CR_PLLRDY_MASK)              /* PLL clock ready flag */


/* Bit definition for RCC_CFGR register */
/* SW configuration */
#define RCC_CFGR_SW_POS                      (0U)                              
#define RCC_CFGR_SW_MASK                     (0x00000003)                      /* 0x00000003                         */
#define RCC_CFGR_SW                          (RCC_CFGR_SW_MASK)                /* SW[1:0] bits (System clock Switch) */
#define RCC_CFGR_SW_0                        (0x00000001)                      /* 0x00000001                         */
#define RCC_CFGR_SW_1                        (0x00000002)                      /* 0x00000002                         */

#define RCC_CFGR_SW_HSI                      (0x00000000)                      /* HSI selected as system clock */
#define RCC_CFGR_SW_HSE                      (0x00000001)                      /* HSE selected as system clock */
#define RCC_CFGR_SW_PLL                      (0x00000002)                      /* PLL selected as system clock */

/* SWS configuration */
#define RCC_CFGR_SWS_POS                     (2U)                              
#define RCC_CFGR_SWS_MASK                    (0x0000000C)                      /* 0x0000000C                                 */
#define RCC_CFGR_SWS                         (RCC_CFGR_SWS_MASK)               /* SWS[1:0] bits (System Clock Switch Status) */
#define RCC_CFGR_SWS_0                       (0x00000004)                      /* 0x00000004                                 */
#define RCC_CFGR_SWS_1                       (0x00000008)                      /* 0x00000008                                 */

#define RCC_CFGR_SWS_HSI                     (0x00000000)                      /* HSI oscillator used as system clock */
#define RCC_CFGR_SWS_HSE                     (0x00000004)                      /* HSE oscillator used as system clock */
#define RCC_CFGR_SWS_PLL                     (0x00000008)                      /* PLL used as system clock            */

/* HPRE configuration */
#define RCC_CFGR_HPRE_POS                    (4U)                              
#define RCC_CFGR_HPRE_MASK                   (0x000000F0)                      /* 0x000000F0                     */
#define RCC_CFGR_HPRE                        (RCC_CFGR_HPRE_MASK)              /* HPRE[3:0] bits (AHB prescaler) */
#define RCC_CFGR_HPRE_0                      (0x00000010)                      /* 0x00000010                     */
#define RCC_CFGR_HPRE_1                      (0x00000020)                      /* 0x00000020                     */
#define RCC_CFGR_HPRE_2                      (0x00000040)                      /* 0x00000040                     */
#define RCC_CFGR_HPRE_3                      (0x00000080)                      /* 0x00000080                     */
#define RCC_CFGR_HPRE_DIV_2                  (0x08U)

#define RCC_CFGR_HPRE_DIV1                   (0x00000000)                      /* SYSCLK not divided    */
#define RCC_CFGR_HPRE_DIV2                   (0x00000080)                      /* SYSCLK divided by 2   */
#define RCC_CFGR_HPRE_DIV4                   (0x00000090)                      /* SYSCLK divided by 4   */
#define RCC_CFGR_HPRE_DIV8                   (0x000000A0)                      /* SYSCLK divided by 8   */
#define RCC_CFGR_HPRE_DIV16                  (0x000000B0)                      /* SYSCLK divided by 16  */
#define RCC_CFGR_HPRE_DIV64                  (0x000000C0)                      /* SYSCLK divided by 64  */
#define RCC_CFGR_HPRE_DIV128                 (0x000000D0)                      /* SYSCLK divided by 128 */
#define RCC_CFGR_HPRE_DIV256                 (0x000000E0)                      /* SYSCLK divided by 256 */
#define RCC_CFGR_HPRE_DIV512                 (0x000000F0)                      /* SYSCLK divided by 512 */

/* PPRE1 configuration */
#define RCC_CFGR_PPRE1_POS                   (8U)                              
#define RCC_CFGR_PPRE1_MASK                  (0x00000700)                      /* 0x00000700                      */
#define RCC_CFGR_PPRE1                       (RCC_CFGR_PPRE1_MASK)             /* PRE1[2:0] bits (APB1 prescaler) */
#define RCC_CFGR_PPRE1_0                     (0x00000100)                      /* 0x00000100                      */
#define RCC_CFGR_PPRE1_1                     (0x00000200)                      /* 0x00000200                      */
#define RCC_CFGR_PPRE1_2                     (0x00000400)                      /* 0x00000400                      */
#define RCC_CFGR_PPRE1_DIV_2                 (0x04U)

#define RCC_CFGR_PPRE1_DIV1                  (0x00000000)                      /* HCLK not divided   */
#define RCC_CFGR_PPRE1_DIV2                  (0x00000400)                      /* HCLK divided by 2  */
#define RCC_CFGR_PPRE1_DIV4                  (0x00000500)                      /* HCLK divided by 4  */
#define RCC_CFGR_PPRE1_DIV8                  (0x00000600)                      /* HCLK divided by 8  */
#define RCC_CFGR_PPRE1_DIV16                 (0x00000700)                      /* HCLK divided by 16 */

/* PPRE2 configuration */
#define RCC_CFGR_PPRE2_POS                   (11U)                             
#define RCC_CFGR_PPRE2_MASK                  (0x00003800)                      /* 0x00003800                      */
#define RCC_CFGR_PPRE2                       (RCC_CFGR_PPRE2_MASK)             /* PRE2[2:0] bits (APB2 prescaler) */
#define RCC_CFGR_PPRE2_0                     (0x00000800)                      /* 0x00000800                      */
#define RCC_CFGR_PPRE2_1                     (0x00001000)                      /* 0x00001000                      */
#define RCC_CFGR_PPRE2_2                     (0x00002000)                      /* 0x00002000                      */
#define RCC_CFGR_PPRE2_DIV_2                 (0x04U)

#define RCC_CFGR_PPRE2_DIV1                  (0x00000000)                      /* HCLK not divided   */
#define RCC_CFGR_PPRE2_DIV2                  (0x00002000)                      /* HCLK divided by 2  */
#define RCC_CFGR_PPRE2_DIV4                  (0x00002800)                      /* HCLK divided by 4  */
#define RCC_CFGR_PPRE2_DIV8                  (0x00003000)                      /* HCLK divided by 8  */
#define RCC_CFGR_PPRE2_DIV16                 (0x00003800)                      /* HCLK divided by 16 */

/* ADCPPRE configuration */
#define RCC_CFGR_ADCPRE_POS                  (14U)                             
#define RCC_CFGR_ADCPRE_MASK                 (0x0000C000)                      /* 0x0000C000                       */
#define RCC_CFGR_ADCPRE                      (RCC_CFGR_ADCPRE_MASK)            /* ADCPRE[1:0] bits (ADC prescaler) */
#define RCC_CFGR_ADCPRE_0                    (0x00004000)                      /* 0x00004000                       */
#define RCC_CFGR_ADCPRE_1                    (0x00008000)                      /* 0x00008000                       */

#define RCC_CFGR_ADCPRE_DIV2                 (0x00000000)                      /* PCLK2 divided by 2 */
#define RCC_CFGR_ADCPRE_DIV4                 (0x00004000)                      /* PCLK2 divided by 4 */
#define RCC_CFGR_ADCPRE_DIV6                 (0x00008000)                      /* PCLK2 divided by 6 */
#define RCC_CFGR_ADCPRE_DIV8                 (0x0000C000)                      /* PCLK2 divided by 8 */

#define RCC_CFGR_PLLSRC_POS                  (16U)                             
#define RCC_CFGR_PLLSRC_MASK                 (0x00010000)                      /* 0x00010000             */
#define RCC_CFGR_PLLSRC                      (RCC_CFGR_PLLSRC_MASK)            /* PLL entry clock source */

#define RCC_CFGR_PLLXTPRE_POS                (17U)                             
#define RCC_CFGR_PLLXTPRE_MASK               (0x00020000 )                     /* 0x00020000                */
#define RCC_CFGR_PLLXTPRE                    (RCC_CFGR_PLLXTPRE_MASK)          /* HSE divider for PLL entry */

/* PLLMUL configuration */
#define RCC_CFGR_PLLMULL_POS                 (18U)                             
#define RCC_CFGR_PLLMULL_MASK                (0x003C0000)                      /* 0x003C0000                                   */
#define RCC_CFGR_PLLMULL                     (RCC_CFGR_PLLMULL_MASK)           /* PLLMUL[3:0] bits (PLL multiplication factor) */
#define RCC_CFGR_PLLMULL_0                   (0x00040000)                      /* 0x00040000                                   */
#define RCC_CFGR_PLLMULL_1                   (0x00080000)                      /* 0x00080000                                   */
#define RCC_CFGR_PLLMULL_2                   (0x00100000)                      /* 0x00100000                                   */
#define RCC_CFGR_PLLMULL_3                   (0x00200000)                      /* 0x00200000                                   */

#define RCC_CFGR_PLLXTPRE_HSE                (0x00000000)                      /* HSE clock not divided for PLL entry  */
#define RCC_CFGR_PLLXTPRE_HSE_DIV2           (0x00020000)                      /* HSE clock divided by 2 for PLL entry */

#define RCC_CFGR_PLLMULL2                    (0x00000000)                      /* PLL input clock*2 */
#define RCC_CFGR_PLLMULL3_POS                (18U)                             
#define RCC_CFGR_PLLMULL3_MASK               (0x00040000)                      /* 0x00040000        */
#define RCC_CFGR_PLLMULL3                    (RCC_CFGR_PLLMULL3_MASK)          /* PLL input clock*3 */
#define RCC_CFGR_PLLMULL4_POS                (19U)                             
#define RCC_CFGR_PLLMULL4_MASK               (0x00080000)                      /* 0x00080000        */
#define RCC_CFGR_PLLMULL4                    (RCC_CFGR_PLLMULL4_MASK)          /* PLL input clock*4 */
#define RCC_CFGR_PLLMULL5_POS                (18U)                             
#define RCC_CFGR_PLLMULL5_MASK               (0x000C0000)                      /* 0x000C0000        */
#define RCC_CFGR_PLLMULL5                    (RCC_CFGR_PLLMULL5_MASK)          /* PLL input clock*5 */
#define RCC_CFGR_PLLMULL6_POS                (20U)                             
#define RCC_CFGR_PLLMULL6_MASK               (0x00100000)                      /* 0x00100000        */
#define RCC_CFGR_PLLMULL6                    (RCC_CFGR_PLLMULL6_MASK)          /* PLL input clock*6 */
#define RCC_CFGR_PLLMULL7_POS                (18U)                             
#define RCC_CFGR_PLLMULL7_MASK               (0x00140000)                      /* 0x00140000        */
#define RCC_CFGR_PLLMULL7                    (RCC_CFGR_PLLMULL7_MASK)          /* PLL input clock*7 */
#define RCC_CFGR_PLLMULL8_POS                (19U)                             
#define RCC_CFGR_PLLMULL8_MASK               (0x00180000)                      /* 0x00180000        */
#define RCC_CFGR_PLLMULL8                    (RCC_CFGR_PLLMULL8_MASK)          /* PLL input clock*8 */
#define RCC_CFGR_PLLMULL9_POS                (18U)                             
#define RCC_CFGR_PLLMULL9_MASK               (0x001C0000)                      /* 0x001C0000        */
#define RCC_CFGR_PLLMULL9                    (RCC_CFGR_PLLMULL9_MASK)          /* PLL input clock*9 */
#define RCC_CFGR_PLLMULL10_POS               (21U)                             
#define RCC_CFGR_PLLMULL10_MASK              (0x00200000)                      /* 0x00200000        */
#define RCC_CFGR_PLLMULL10                   (RCC_CFGR_PLLMULL10_MASK)         /* PLL input clock10 */
#define RCC_CFGR_PLLMULL11_POS               (18U)                             
#define RCC_CFGR_PLLMULL11_MASK              (0x00240000)                      /* 0x00240000         */
#define RCC_CFGR_PLLMULL11                   (RCC_CFGR_PLLMULL11_MASK)         /* PLL input clock*11 */
#define RCC_CFGR_PLLMULL12_POS               (19U)                             
#define RCC_CFGR_PLLMULL12_MASK              (0x00280000)                      /* 0x00280000         */
#define RCC_CFGR_PLLMULL12                   (RCC_CFGR_PLLMULL12_MASK)         /* PLL input clock*12 */
#define RCC_CFGR_PLLMULL13_POS               (18U)                             
#define RCC_CFGR_PLLMULL13_MASK              (0x002C0000)                      /* 0x002C0000         */
#define RCC_CFGR_PLLMULL13                   (RCC_CFGR_PLLMULL13_MASK)         /* PLL input clock*13 */
#define RCC_CFGR_PLLMULL14_POS               (20U)                             
#define RCC_CFGR_PLLMULL14_MASK              (0x00300000)                      /* 0x00300000         */
#define RCC_CFGR_PLLMULL14                   (RCC_CFGR_PLLMULL14_MASK)         /* PLL input clock*14 */
#define RCC_CFGR_PLLMULL15_POS               (18U)                             
#define RCC_CFGR_PLLMULL15_MASK              (0x00340000)                      /* 0x00340000         */
#define RCC_CFGR_PLLMULL15                   (RCC_CFGR_PLLMULL15_MASK)         /* PLL input clock*15 */
#define RCC_CFGR_PLLMULL16_POS               (19U)                             
#define RCC_CFGR_PLLMULL16_MASK              (0x00380000)                      /* 0x00380000         */
#define RCC_CFGR_PLLMULL16                   (RCC_CFGR_PLLMULL16_MASK)         /* PLL input clock*16 */
#define RCC_CFGR_USBPRE_POS                  (22U)                             
#define RCC_CFGR_USBPRE_MASK                 (0x00400000)                      /* 0x00400000           */
#define RCC_CFGR_USBPRE                      (RCC_CFGR_USBPRE_MASK)            /* USB Device prescaler */

/* MCO configuration */
#define RCC_CFGR_MCO_POS                     (24U)                             
#define RCC_CFGR_MCO_MASK                    (0x07000000)                      /* 0x07000000                                   */
#define RCC_CFGR_MCO                         (RCC_CFGR_MCO_MASK)               /* MCO[2:0] bits (Microcontroller Clock Output) */
#define RCC_CFGR_MCO_0                       (0x01000000)                      /* 0x01000000                                   */
#define RCC_CFGR_MCO_1                       (0x02000000)                      /* 0x02000000                                   */
#define RCC_CFGR_MCO_2                       (0x04000000)                      /* 0x04000000                                   */

#define RCC_CFGR_MCO_NOCLOCK                 (0x00000000)                      /* No clock                                      */
#define RCC_CFGR_MCO_SYSCLK                  (0x04000000)                      /* System clock selected as MCO source           */
#define RCC_CFGR_MCO_HSI                     (0x05000000)                      /* HSI clock selected as MCO source              */
#define RCC_CFGR_MCO_HSE                     (0x06000000)                      /* HSE clock selected as MCO source              */
#define RCC_CFGR_MCO_PLLCLK_DIV2             (0x07000000)                      /* PLL clock divided by 2 selected as MCO source */

 /* Reference defines */
 #define RCC_CFGR_MCOSEL                     (RCC_CFGR_MCO)
 #define RCC_CFGR_MCOSEL_0                   (RCC_CFGR_MCO_0)
 #define RCC_CFGR_MCOSEL_1                   (RCC_CFGR_MCO_1)
 #define RCC_CFGR_MCOSEL_2                   (RCC_CFGR_MCO_2)
 #define RCC_CFGR_MCOSEL_NOCLOCK             (RCC_CFGR_MCO_NOCLOCK)
 #define RCC_CFGR_MCOSEL_SYSCLK              (RCC_CFGR_MCO_SYSCLK)
 #define RCC_CFGR_MCOSEL_HSI                 (RCC_CFGR_MCO_HSI)
 #define RCC_CFGR_MCOSEL_HSE                 (RCC_CFGR_MCO_HSE)
 #define RCC_CFGR_MCOSEL_PLL_DIV2            (RCC_CFGR_MCO_PLLCLK_DIV2)

/* Bit definition for RCC_CIR register */
#define RCC_CIR_LSIRDYF_POS                  (0U)                              
#define RCC_CIR_LSIRDYF_MASK                 (0x00000001)                      /* 0x00000001               */
#define RCC_CIR_LSIRDYF                      (RCC_CIR_LSIRDYF_MASK)            /* LSI Ready Interrupt flag */
#define RCC_CIR_LSERDYF_POS                  (1U)                              
#define RCC_CIR_LSERDYF_MASK                 (0x00000002)                      /* 0x00000002               */
#define RCC_CIR_LSERDYF                      (RCC_CIR_LSERDYF_MASK)            /* LSE Ready Interrupt flag */
#define RCC_CIR_HSIRDYF_POS                  (2U)                              
#define RCC_CIR_HSIRDYF_MASK                 (0x00000004)                      /* 0x00000004               */
#define RCC_CIR_HSIRDYF                      (RCC_CIR_HSIRDYF_MASK)            /* HSI Ready Interrupt flag */
#define RCC_CIR_HSERDYF_POS                  (3U)                              
#define RCC_CIR_HSERDYF_MASK                 (0x00000008)                      /* 0x00000008               */
#define RCC_CIR_HSERDYF                      (RCC_CIR_HSERDYF_MASK)            /* HSE Ready Interrupt flag */
#define RCC_CIR_PLLRDYF_POS                  (4U)                              
#define RCC_CIR_PLLRDYF_MASK                 (0x00000010)                      /* 0x00000010               */
#define RCC_CIR_PLLRDYF                      (RCC_CIR_PLLRDYF_MASK)            /* PLL Ready Interrupt flag */
#define RCC_CIR_CSSF_POS                     (7U)                              
#define RCC_CIR_CSSF_MASK                    (0x00000080)                      /* 0x00000080                           */
#define RCC_CIR_CSSF                         (RCC_CIR_CSSF_MASK)               /* Clock Security System Interrupt flag */
#define RCC_CIR_LSIRDYIE_POS                 (8U)                              
#define RCC_CIR_LSIRDYIE_MASK                (0x00000100)                      /* 0x00000100                 */
#define RCC_CIR_LSIRDYIE                     (RCC_CIR_LSIRDYIE_MASK)           /* LSI Ready Interrupt Enable */
#define RCC_CIR_LSERDYIE_POS                 (9U)                              
#define RCC_CIR_LSERDYIE_MASK                (0x00000200)                      /* 0x00000200                 */
#define RCC_CIR_LSERDYIE                     (RCC_CIR_LSERDYIE_MASK)           /* LSE Ready Interrupt Enable */
#define RCC_CIR_HSIRDYIE_POS                 (10U)                             
#define RCC_CIR_HSIRDYIE_MASK                (0x00000400)                      /* 0x00000400                 */
#define RCC_CIR_HSIRDYIE                     (RCC_CIR_HSIRDYIE_MASK)           /* HSI Ready Interrupt Enable */
#define RCC_CIR_HSERDYIE_POS                 (11U)                             
#define RCC_CIR_HSERDYIE_MASK                (0x00000800)                      /* 0x00000800                 */
#define RCC_CIR_HSERDYIE                     (RCC_CIR_HSERDYIE_MASK)           /* HSE Ready Interrupt Enable */
#define RCC_CIR_PLLRDYIE_POS                 (12U)                             
#define RCC_CIR_PLLRDYIE_MASK                (0x00001000)                      /* 0x00001000                 */
#define RCC_CIR_PLLRDYIE                     (RCC_CIR_PLLRDYIE_MASK)           /* PLL Ready Interrupt Enable */
#define RCC_CIR_LSIRDYC_POS                  (16U)                             
#define RCC_CIR_LSIRDYC_MASK                 (0x00010000)                      /* 0x00010000                */
#define RCC_CIR_LSIRDYC                      (RCC_CIR_LSIRDYC_MASK)            /* LSI Ready Interrupt Clear */
#define RCC_CIR_LSERDYC_POS                  (17U)                             
#define RCC_CIR_LSERDYC_MASK                 (0x00020000)                      /* 0x00020000                */
#define RCC_CIR_LSERDYC                      (RCC_CIR_LSERDYC_MASK)            /* LSE Ready Interrupt Clear */
#define RCC_CIR_HSIRDYC_POS                  (18U)                             
#define RCC_CIR_HSIRDYC_MASK                 (0x00040000)                      /* 0x00040000                */
#define RCC_CIR_HSIRDYC                      (RCC_CIR_HSIRDYC_MASK)            /* HSI Ready Interrupt Clear */
#define RCC_CIR_HSERDYC_POS                  (19U)                             
#define RCC_CIR_HSERDYC_MASK                 (0x00080000)                      /* 0x00080000                */
#define RCC_CIR_HSERDYC                      (RCC_CIR_HSERDYC_MASK)            /* HSE Ready Interrupt Clear */
#define RCC_CIR_PLLRDYC_POS                  (20U)                             
#define RCC_CIR_PLLRDYC_MASK                 (0x00100000)                      /* 0x00100000                */
#define RCC_CIR_PLLRDYC                      (RCC_CIR_PLLRDYC_MASK)            /* PLL Ready Interrupt Clear */
#define RCC_CIR_CSSC_POS                     (23U)                             
#define RCC_CIR_CSSC_MASK                    (0x00800000)                      /* 0x00800000                            */
#define RCC_CIR_CSSC                         (RCC_CIR_CSSC_MASK)               /* Clock Security System Interrupt Clear */


/* Bit definition for RCC_APB2RSTR register */
#define RCC_APB2RSTR_AFIORST_POS             (0U)                              
#define RCC_APB2RSTR_AFIORST_MASK            (0x00000001)                      /* 0x00000001                  */
#define RCC_APB2RSTR_AFIORST                 (RCC_APB2RSTR_AFIORST_MASK)       /* Alternate Function I/O reset */
#define RCC_APB2RSTR_IOPARST_POS             (2U)                              
#define RCC_APB2RSTR_IOPARST_MASK            (0x00000004)                      /* 0x00000004      */
#define RCC_APB2RSTR_IOPARST                 (RCC_APB2RSTR_IOPARST_MASK)       /* I/O port A reset */
#define RCC_APB2RSTR_IOPBRST_POS             (3U)                              
#define RCC_APB2RSTR_IOPBRST_MASK            (0x00000008)                      /* 0x00000008      */
#define RCC_APB2RSTR_IOPBRST                 (RCC_APB2RSTR_IOPBRST_MASK)       /* I/O port B reset */
#define RCC_APB2RSTR_IOPCRST_POS             (4U)                              
#define RCC_APB2RSTR_IOPCRST_MASK            (0x00000010)                      /* 0x00000010      */
#define RCC_APB2RSTR_IOPCRST                 (RCC_APB2RSTR_IOPCRST_MASK)       /* I/O port C reset */
#define RCC_APB2RSTR_IOPDRST_POS             (5U)                              
#define RCC_APB2RSTR_IOPDRST_MASK            (0x00000020)                      /* 0x00000020      */
#define RCC_APB2RSTR_IOPDRST                 (RCC_APB2RSTR_IOPDRST_MASK)       /* I/O port D reset */
#define RCC_APB2RSTR_ADC1RST_POS             (9U)                              
#define RCC_APB2RSTR_ADC1RST_MASK            (0x00000200)                      /* 0x00000200           */
#define RCC_APB2RSTR_ADC1RST                 (RCC_APB2RSTR_ADC1RST_MASK)       /* ADC 1 interface reset */

#define RCC_APB2RSTR_ADC2RST_POS             (10U)                             
#define RCC_APB2RSTR_ADC2RST_MASK            (0x00000400)                      /* 0x00000400           */
#define RCC_APB2RSTR_ADC2RST                 (RCC_APB2RSTR_ADC2RST_MASK)       /* ADC 2 interface reset */

#define RCC_APB2RSTR_TIM1RST_POS             (11U)                             
#define RCC_APB2RSTR_TIM1RST_MASK            (0x00000800)                      /* 0x00000800      */
#define RCC_APB2RSTR_TIM1RST                 (RCC_APB2RSTR_TIM1RST_MASK)       /* TIM1 Timer reset */
#define RCC_APB2RSTR_SPI1RST_POS             (12U)                             
#define RCC_APB2RSTR_SPI1RST_MASK            (0x00001000)                      /* 0x00001000 */
#define RCC_APB2RSTR_SPI1RST                 (RCC_APB2RSTR_SPI1RST_MASK)       /* SPI 1 reset */
#define RCC_APB2RSTR_USART1RST_POS           (14U)                             
#define RCC_APB2RSTR_USART1RST_MASK          (0x00004000)                      /* 0x00004000 */
#define RCC_APB2RSTR_USART1RST               (RCC_APB2RSTR_USART1RST_MASK)     /* USART1 reset  */

#define RCC_APB2RSTR_IOPERST_POS             (6U)                              
#define RCC_APB2RSTR_IOPERST_MASK            (0x00000040)                      /* 0x00000040      */
#define RCC_APB2RSTR_IOPERST                 (RCC_APB2RSTR_IOPERST_MASK)       /* I/O port E reset */


/* Bit definition for RCC_APB1RSTR register */
#define RCC_APB1RSTR_TIM2RST_POS             (0U)                              
#define RCC_APB1RSTR_TIM2RST_MASK            (0x00000001)                      /* 0x00000001   */
#define RCC_APB1RSTR_TIM2RST                 (RCC_APB1RSTR_TIM2RST_MASK)       /* Timer 2 reset */
#define RCC_APB1RSTR_TIM3RST_POS             (1U)                              
#define RCC_APB1RSTR_TIM3RST_MASK            (0x00000002)                      /* 0x00000002   */
#define RCC_APB1RSTR_TIM3RST                 (RCC_APB1RSTR_TIM3RST_MASK)       /* Timer 3 reset */
#define RCC_APB1RSTR_WWDGRST_POS             (11U)                             
#define RCC_APB1RSTR_WWDGRST_MASK            (0x00000800)                      /* 0x00000800           */
#define RCC_APB1RSTR_WWDGRST                 (RCC_APB1RSTR_WWDGRST_MASK)       /* Window Watchdog reset */
#define RCC_APB1RSTR_USART2RST_POS           (17U)                             
#define RCC_APB1RSTR_USART2RST_MASK          (0x00020000)                      /* 0x00020000 */
#define RCC_APB1RSTR_USART2RST               (RCC_APB1RSTR_USART2RST_MASK)     /* USART 2 reset */
#define RCC_APB1RSTR_I2C1RST_POS             (21U)                             
#define RCC_APB1RSTR_I2C1RST_MASK            (0x00200000)                      /* 0x00200000 */
#define RCC_APB1RSTR_I2C1RST                 (RCC_APB1RSTR_I2C1RST_MASK)       /* I2C 1 reset */

#define RCC_APB1RSTR_CAN1RST_POS             (25U)                             
#define RCC_APB1RSTR_CAN1RST_MASK            (0x02000000)                      /* 0x02000000 */
#define RCC_APB1RSTR_CAN1RST                 (RCC_APB1RSTR_CAN1RST_MASK)       /* CAN1 reset  */

#define RCC_APB1RSTR_BKPRST_POS              (27U)                             
#define RCC_APB1RSTR_BKPRST_MASK             (0x08000000)                      /* 0x08000000             */
#define RCC_APB1RSTR_BKPRST                  (RCC_APB1RSTR_BKPRST_MASK)        /* Backup interface reset */
#define RCC_APB1RSTR_PWRRST_POS              (28U)                             
#define RCC_APB1RSTR_PWRRST_MASK             (0x10000000)                      /* 0x10000000            */
#define RCC_APB1RSTR_PWRRST                  (RCC_APB1RSTR_PWRRST_MASK)        /* Power interface reset */

#define RCC_APB1RSTR_TIM4RST_POS             (2U)                              
#define RCC_APB1RSTR_TIM4RST_MASK            (0x00000004)                      /* 0x00000004   */
#define RCC_APB1RSTR_TIM4RST                 (RCC_APB1RSTR_TIM4RST_MASK)       /* Timer 4 reset */
#define RCC_APB1RSTR_SPI2RST_POS             (14U)                             
#define RCC_APB1RSTR_SPI2RST_MASK            (0x00004000)                      /* 0x00004000 */
#define RCC_APB1RSTR_SPI2RST                 (RCC_APB1RSTR_SPI2RST_MASK)       /* SPI 2 reset */
#define RCC_APB1RSTR_USART3RST_POS           (18U)                             
#define RCC_APB1RSTR_USART3RST_MASK          (0x00040000)                      /* 0x00040000 */
#define RCC_APB1RSTR_USART3RST               (RCC_APB1RSTR_USART3RST_MASK)     /* USART 3 reset */
#define RCC_APB1RSTR_I2C2RST_POS             (22U)                             
#define RCC_APB1RSTR_I2C2RST_MASK            (0x00400000)                      /* 0x00400000 */
#define RCC_APB1RSTR_I2C2RST                 (RCC_APB1RSTR_I2C2RST_MASK)       /* I2C 2 reset */

#define RCC_APB1RSTR_USBRST_POS              (23U)                             
#define RCC_APB1RSTR_USBRST_MASK             (0x00800000)                      /* 0x00800000       */
#define RCC_APB1RSTR_USBRST                  (RCC_APB1RSTR_USBRST_MASK)        /* USB Device reset */


/* Bit definition for RCC_AHBENR register */
#define RCC_AHBENR_DMA1EN_POS                (0U)                              
#define RCC_AHBENR_DMA1EN_MASK               (0x00000001)                      /* 0x00000001        */
#define RCC_AHBENR_DMA1EN                    (RCC_AHBENR_DMA1EN_MASK)          /* DMA1 clock enable */
#define RCC_AHBENR_SRAMEN_POS                (2U)                              
#define RCC_AHBENR_SRAMEN_MASK               (0x00000004)                      /* 0x00000004                  */
#define RCC_AHBENR_SRAMEN                    (RCC_AHBENR_SRAMEN_MASK)          /* SRAM interface clock enable */
#define RCC_AHBENR_FLITFEN_POS               (4U)                              
#define RCC_AHBENR_FLITFEN_MASK              (0x00000010)                      /* 0x00000010         */
#define RCC_AHBENR_FLITFEN                   (RCC_AHBENR_FLITFEN_MASK)         /* FLITF clock enable */
#define RCC_AHBENR_CRCEN_POS                 (6U)                              
#define RCC_AHBENR_CRCEN_MASK                (0x00000040)                      /* 0x00000040       */
#define RCC_AHBENR_CRCEN                     (RCC_AHBENR_CRCEN_MASK)           /* CRC clock enable */


/* Bit definition for RCC_APB2ENR register */
#define RCC_APB2ENR_AFIOEN_POS               (0U)                              
#define RCC_APB2ENR_AFIOEN_MASK              (0x00000001)                      /* 0x00000001                          */
#define RCC_APB2ENR_AFIOEN                   (RCC_APB2ENR_AFIOEN_MASK)         /* Alternate Function I/O clock enable */
#define RCC_APB2ENR_IOPAEN_POS               (2U)                              
#define RCC_APB2ENR_IOPAEN_MASK              (0x00000004)                      /* 0x00000004              */
#define RCC_APB2ENR_IOPAEN                   (RCC_APB2ENR_IOPAEN_MASK)         /* I/O port A clock enable */
#define RCC_APB2ENR_IOPBEN_POS               (3U)                              
#define RCC_APB2ENR_IOPBEN_MASK              (0x00000008)                      /* 0x00000008              */
#define RCC_APB2ENR_IOPBEN                   (RCC_APB2ENR_IOPBEN_MASK)         /* I/O port B clock enable */
#define RCC_APB2ENR_IOPCEN_POS               (4U)                              
#define RCC_APB2ENR_IOPCEN_MASK              (0x00000010)                      /* 0x00000010              */
#define RCC_APB2ENR_IOPCEN                   (RCC_APB2ENR_IOPCEN_MASK)         /* I/O port C clock enable */
#define RCC_APB2ENR_IOPDEN_POS               (5U)                              
#define RCC_APB2ENR_IOPDEN_MASK              (0x00000020)                      /* 0x00000020              */
#define RCC_APB2ENR_IOPDEN                   (RCC_APB2ENR_IOPDEN_MASK)         /* I/O port D clock enable */
#define RCC_APB2ENR_ADC1EN_POS               (9U)                              
#define RCC_APB2ENR_ADC1EN_MASK              (0x00000200)                      /* 0x00000200                   */
#define RCC_APB2ENR_ADC1EN                   (RCC_APB2ENR_ADC1EN_MASK)         /* ADC 1 interface clock enable */

#define RCC_APB2ENR_ADC2EN_POS               (10U)                             
#define RCC_APB2ENR_ADC2EN_MASK              (0x00000400)                      /* 0x00000400                   */
#define RCC_APB2ENR_ADC2EN                   (RCC_APB2ENR_ADC2EN_MASK)         /* ADC 2 interface clock enable */

#define RCC_APB2ENR_TIM1EN_POS               (11U)                             
#define RCC_APB2ENR_TIM1EN_MASK              (0x00000800)                      /* 0x00000800              */
#define RCC_APB2ENR_TIM1EN                   (RCC_APB2ENR_TIM1EN_MASK)         /* TIM1 Timer clock enable */
#define RCC_APB2ENR_SPI1EN_POS               (12U)                             
#define RCC_APB2ENR_SPI1EN_MASK              (0x00001000)                      /* 0x00001000          */
#define RCC_APB2ENR_SPI1EN                   (RCC_APB2ENR_SPI1EN_MASK)         /* SPI 1 clock enable  */
#define RCC_APB2ENR_USART1EN_POS             (14U)                             
#define RCC_APB2ENR_USART1EN_MASK            (0x00004000)                      /* 0x00004000         */
#define RCC_APB2ENR_USART1EN                 (RCC_APB2ENR_USART1EN_MASK)       /* USART1 clock enable */


#define RCC_APB2ENR_IOPEEN_POS               (6U)                              
#define RCC_APB2ENR_IOPEEN_MASK              (0x00000040)                      /* 0x00000040              */
#define RCC_APB2ENR_IOPEEN                   (RCC_APB2ENR_IOPEEN_MASK)         /* I/O port E clock enable */


/* Bit definition for RCC_APB1ENR register */
#define RCC_APB1ENR_TIM2EN_POS               (0U)                              
#define RCC_APB1ENR_TIM2EN_MASK              (0x00000001)                      /* 0x00000001            */
#define RCC_APB1ENR_TIM2EN                   (RCC_APB1ENR_TIM2EN_MASK)         /* Timer 2 clock enabled */
#define RCC_APB1ENR_TIM3EN_POS               (1U)                              
#define RCC_APB1ENR_TIM3EN_MASK              (0x00000002)                      /* 0x00000002            */
#define RCC_APB1ENR_TIM3EN                   (RCC_APB1ENR_TIM3EN_MASK)         /* Timer 3 clock enable  */
#define RCC_APB1ENR_WWDGEN_POS               (11U)                             
#define RCC_APB1ENR_WWDGEN_MASK              (0x00000800)                      /* 0x00000800                   */
#define RCC_APB1ENR_WWDGEN                   (RCC_APB1ENR_WWDGEN_MASK)         /* Window Watchdog clock enable */
#define RCC_APB1ENR_USART2EN_POS             (17U)                             
#define RCC_APB1ENR_USART2EN_MASK            (0x00020000)                      /* 0x00020000          */
#define RCC_APB1ENR_USART2EN                 (RCC_APB1ENR_USART2EN_MASK)       /* USART 2 clock enable */
#define RCC_APB1ENR_I2C1EN_POS               (21U)                             
#define RCC_APB1ENR_I2C1EN_MASK              (0x00200000)                      /* 0x00200000         */
#define RCC_APB1ENR_I2C1EN                   (RCC_APB1ENR_I2C1EN_MASK)         /* I2C 1 clock enable */

#define RCC_APB1ENR_CAN1EN_POS               (25U)                             
#define RCC_APB1ENR_CAN1EN_MASK              (0x02000000)                      /* 0x02000000        */
#define RCC_APB1ENR_CAN1EN                   (RCC_APB1ENR_CAN1EN_MASK)         /* CAN1 clock enable */

#define RCC_APB1ENR_BKPEN_POS                (27U)                             
#define RCC_APB1ENR_BKPEN_MASK               (0x08000000)                      /* 0x08000000                    */
#define RCC_APB1ENR_BKPEN                    (RCC_APB1ENR_BKPEN_MASK)          /* Backup interface clock enable */
#define RCC_APB1ENR_PWREN_POS                (28U)                             
#define RCC_APB1ENR_PWREN_MASK               (0x10000000)                      /* 0x10000000                   */
#define RCC_APB1ENR_PWREN                    (RCC_APB1ENR_PWREN_MASK)          /* Power interface clock enable */

#define RCC_APB1ENR_TIM4EN_POS               (2U)                              
#define RCC_APB1ENR_TIM4EN_MASK              (0x00000004)                      /* 0x00000004           */
#define RCC_APB1ENR_TIM4EN                   (RCC_APB1ENR_TIM4EN_MASK)         /* Timer 4 clock enable */
#define RCC_APB1ENR_SPI2EN_POS               (14U)                             
#define RCC_APB1ENR_SPI2EN_MASK              (0x00004000)                      /* 0x00004000           */
#define RCC_APB1ENR_SPI2EN                   (RCC_APB1ENR_SPI2EN_MASK)         /* SPI 2 clock enable   */
#define RCC_APB1ENR_USART3EN_POS             (18U)                             
#define RCC_APB1ENR_USART3EN_MASK            (0x00040000)                      /* 0x00040000          */
#define RCC_APB1ENR_USART3EN                 (RCC_APB1ENR_USART3EN_MASK)       /* USART 3 clock enable */
#define RCC_APB1ENR_I2C2EN_POS               (22U)                             
#define RCC_APB1ENR_I2C2EN_MASK              (0x00400000)                      /* 0x00400000           */
#define RCC_APB1ENR_I2C2EN                   (RCC_APB1ENR_I2C2EN_MASK)         /* I2C 2 clock enable   */

#define RCC_APB1ENR_USBEN_POS                (23U)                             
#define RCC_APB1ENR_USBEN_MASK               (0x00800000)                      /* 0x00800000              */
#define RCC_APB1ENR_USBEN                    (RCC_APB1ENR_USBEN_MASK)          /* USB Device clock enable */


/* Bit definition for RCC_BDCR register */
#define RCC_BDCR_LSEON_POS                   (0U)                              
#define RCC_BDCR_LSEON_MASK                  (0x00000001)                      /* 0x00000001                           */
#define RCC_BDCR_LSEON                       (RCC_BDCR_LSEON_MASK)             /* External Low Speed oscillator enable */
#define RCC_BDCR_LSERDY_POS                  (1U)                              
#define RCC_BDCR_LSERDY_MASK                 (0x00000002)                      /* 0x00000002                           */
#define RCC_BDCR_LSERDY                      (RCC_BDCR_LSERDY_MASK)            /* External Low Speed oscillator Ready  */
#define RCC_BDCR_LSEBYP_POS                  (2U)                              
#define RCC_BDCR_LSEBYP_MASK                 (0x00000004)                      /* 0x00000004                           */
#define RCC_BDCR_LSEBYP                      (RCC_BDCR_LSEBYP_MASK)            /* External Low Speed oscillator Bypass */

#define RCC_BDCR_RTCSEL_POS                  (8U)                              
#define RCC_BDCR_RTCSEL_MASK                 (0x00000300)                      /* 0x00000300                                    */
#define RCC_BDCR_RTCSEL                      (RCC_BDCR_RTCSEL_MASK)            /* RTCSEL[1:0] bits (RTC clock source selection) */
#define RCC_BDCR_RTCSEL_0                    (0x00000100)                      /* 0x00000100                                    */
#define RCC_BDCR_RTCSEL_1                    (0x00000200)                      /* 0x00000200                                    */

/* RTC congiguration */
#define RCC_BDCR_RTCSEL_NOCLOCK              (0x00000000)                      /* No clock                               */
#define RCC_BDCR_RTCSEL_LSE                  (0x00000100)                      /* LSE oscillator clock used as RTC clock */
#define RCC_BDCR_RTCSEL_LSI                  (0x00000200)                      /* LSI oscillator clock used as RTC clock */
#define RCC_BDCR_RTCSEL_HSE                  (0x00000300)                      /* HSE oscillator clock divided by 128 used as RTC clock */

#define RCC_BDCR_RTCEN_POS                   (15U)                             
#define RCC_BDCR_RTCEN_MASK                  (0x00008000)                      /* 0x00008000       */
#define RCC_BDCR_RTCEN                       (RCC_BDCR_RTCEN_MASK)             /* RTC clock enable */
#define RCC_BDCR_BDRST_POS                   (16U)                             
#define RCC_BDCR_BDRST_MASK                  (0x00010000)                      /* 0x00010000                   */
#define RCC_BDCR_BDRST                       (RCC_BDCR_BDRST_MASK)             /* Backup domain software reset */

/* Bit definition for RCC_CSR register */  
#define RCC_CSR_LSION_POS                    (0U)                              
#define RCC_CSR_LSION_MASK                   (0x00000001)                      /* 0x00000001                           */
#define RCC_CSR_LSION                        (RCC_CSR_LSION_MASK)              /* Internal Low Speed oscillator enable */
#define RCC_CSR_LSIRDY_POS                   (1U)                              
#define RCC_CSR_LSIRDY_MASK                  (0x00000002)                      /* 0x00000002                           */
#define RCC_CSR_LSIRDY                       (RCC_CSR_LSIRDY_MASK)             /* Internal Low Speed oscillator Ready  */
#define RCC_CSR_RMVF_POS                     (24U)                             
#define RCC_CSR_RMVF_MASK                    (0x01000000)                      /* 0x01000000        */
#define RCC_CSR_RMVF                         (RCC_CSR_RMVF_MASK)               /* Remove reset flag */
#define RCC_CSR_PINRSTF_POS                  (26U)                             
#define RCC_CSR_PINRSTF_MASK                 (0x04000000)                      /* 0x04000000     */
#define RCC_CSR_PINRSTF                      (RCC_CSR_PINRSTF_MASK)            /* PIN reset flag */
#define RCC_CSR_PORRSTF_POS                  (27U)                             
#define RCC_CSR_PORRSTF_MASK                 (0x08000000)                      /* 0x08000000         */
#define RCC_CSR_PORRSTF                      (RCC_CSR_PORRSTF_MASK)            /* POR/PDR reset flag */
#define RCC_CSR_SFTRSTF_POS                  (28U)                             
#define RCC_CSR_SFTRSTF_MASK                 (0x10000000)                      /* 0x10000000          */
#define RCC_CSR_SFTRSTF                      (RCC_CSR_SFTRSTF_MASK)            /* Software Reset flag */
#define RCC_CSR_IWDGRSTF_POS                 (29U)                             
#define RCC_CSR_IWDGRSTF_MASK                (0x20000000)                      /* 0x20000000                      */
#define RCC_CSR_IWDGRSTF                     (RCC_CSR_IWDGRSTF_MASK)           /* Independent Watchdog reset flag */
#define RCC_CSR_WWDGRSTF_POS                 (30U)                             
#define RCC_CSR_WWDGRSTF_MASK                (0x40000000)                      /* 0x40000000                 */
#define RCC_CSR_WWDGRSTF                     (RCC_CSR_WWDGRSTF_MASK)           /* Window watchdog reset flag */
#define RCC_CSR_LPWRRSTF_POS                 (31U)                             
#define RCC_CSR_LPWRRSTF_MASK                (0x80000000)                      /* 0x80000000           */
#define RCC_CSR_LPWRRSTF                     (RCC_CSR_LPWRRSTF_MASK)           /* Low-Power reset flag */

/* Data structure definition */
/* RCC register */
/****************************************************
*   Structure��  T_RCC_MEM_MAP
*   Description��Memory map of RCC registers.
*   Parameter:   WORD32 CR          RCC clock control register   
*                WORD32 CFGR        RCC clock configure register 
*                WORD32 CIR         RCC clock interrupt register 
*                WORD32 APB2RSTR    RCC APB2 reset register      
*                WORD32 APB1RSTR    RCC APB1 reset register      
*                WORD32 AHBENR      RCC AHB enable register      
*                WORD32 APB2ENR     RCC APB2 enable register     
*                WORD32 APB1ENR     RCC APB1 enable register     
*                WORD32 BDCR        RCC backup control register  
*                WORD32 CSR         RCC control/status register 
*   Authour��    Ian
*   Modify record:
*   Date:  2016-7-25 creat.
****************************************************/
typedef struct _T_RCC_MEM_MAP
{
    WORD32 CR;          /* RCC clock control register   */
    WORD32 CFGR;        /* RCC clock configure register */
    WORD32 CIR;         /* RCC clock interrupt register */
    WORD32 APB2RSTR;    /* RCC APB2 reset register      */
    WORD32 APB1RSTR;    /* RCC APB1 reset register      */
    WORD32 AHBENR;      /* RCC AHB enable register      */
    WORD32 APB2ENR;     /* RCC APB2 enable register     */
    WORD32 APB1ENR;     /* RCC APB1 enable register     */
    WORD32 BDCR;        /* RCC backup control register  */
    WORD32 CSR;         /* RCC control/status register  */
}volatile *T_RCC_MEM_MAP;



/* Declaration of functions */
/**************************************************************************
* Function: WORD32 Rcc_SysClk_Config(BYTE ucSetClk)
* Descrip.: Configure system clock
* Input   : BYTE ucSetClk       Desired clock in MHz
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    ��None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_SysClk_Config(BYTE ucSetClk);

/**************************************************************************
* Function: WORD32 Rcc_Get_SYSCLK(void)
* Descrip.: Get SYSCLK in Hz
* Input   : None
* Output  : None
* Return  : WORD32 SYSCLK in Hz
* Note    ��None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_SYSCLK(void);

/**************************************************************************
* Function: WORD32 Rcc_Get_HCLK(void)
* Descrip.: Get HCLK in Hz
* Input   : None
* Output  : None
* Return  : WORD32 HCLK in Hz
* Note    ��None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_HCLK(void);

/**************************************************************************
* Function: WORD32 Rcc_Get_PCLK1(void)
* Descrip.: Get PCLK1 in Hz
* Input   : None
* Output  : None
* Return  : WORD32 PCLK1 in Hz
* Note    ��None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_PCLK1(void);

/**************************************************************************
* Function: WORD32 Rcc_Get_PCLK2(void)
* Descrip.: Get PCLK2 in Hz
* Input   : None
* Output  : None
* Return  : WORD32 PCLK2 in Hz
* Note    ��None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_PCLK2(void);


#ifdef __cplusplus
}
#endif

#endif /* _RCC_H_ */



