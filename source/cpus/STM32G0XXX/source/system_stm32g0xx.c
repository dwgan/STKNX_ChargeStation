/**
  ******************************************************************************
  * @file    STM32F0518_Ex03_9T1L1R_SENSOR\src\system_stm32f0xx.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    04-April-2014
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Source File.
  *          This file contains the system clock configuration for STM32F0xx devices,
  *          and is generated by the clock configuration tool  
  *          STM32F0xx_Clock_Configuration_V1.0.0.xls
  *
  * 1.  This file provides two functions and one global variable to be called from 
  *     user application:
  *      - SystemInit(): Setups the system clock (System clock source, PLL Multiplier
  *                      and Divider factors, AHB/APBx prescalers and Flash settings),
  *                      depending on the configuration made in the clock xls tool.
  *                      This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32f0xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  * 2. After each device reset the HSI (8 MHz Range) is used as system clock source.
  *    Then SystemInit() function is called, in "startup_stm32f0xx.s" file, to
  *    configure the system clock before to branch to main program.
  *
  * 3. If the system clock source selected by user fails to startup, the SystemInit()
  *    function will do nothing and HSI still used as system clock source. User can 
  *    add some code to deal with this issue inside the SetSysClock() function.
  *
  * 4. The default value of HSE crystal is set to 8MHz, refer to "HSE_VALUE" define
  *    in "stm32f0xx.h" file. When HSE is used as system clock source, directly or
  *    through PLL, and you are using different crystal you have to adapt the HSE
  *    value to your own configuration.
  *
  * 5. This file configures the system clock as follows:
  *=============================================================================
  *                         System Clock Configuration
  *=============================================================================
  *        System Clock source          | PLL(HSE)
  *-----------------------------------------------------------------------------
  *        SYSCLK                       | 48000000 Hz
  *-----------------------------------------------------------------------------
  *        HCLK                         | 48000000 Hz
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler               | 1
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler               | 1
  *-----------------------------------------------------------------------------
  *        HSE Frequency                | 8000000 Hz
  *-----------------------------------------------------------------------------
  *        PLL MUL                      | 6
  *-----------------------------------------------------------------------------
  *        VDD                          | 3.3 V
  *-----------------------------------------------------------------------------
  *        Flash Latency                | 1 WS
  *-----------------------------------------------------------------------------
  *=============================================================================
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f0xx_system
  * @{
  */  
  
/** @addtogroup STM32F0xx_System_Private_Includes
  * @{
  */
#include "type_def.h"
#include "boardctrl.h"
#include "boardcfg.h"
#include "hardware.h"


#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
#pragma section = "CodeRelocate"
#pragma section = "CodeRelocateRam"

typedef unsigned char        uint8;  /*  8 bits */
typedef unsigned long int    uint32; /* 32 bits */


/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Defines
  * @{
  */
/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Variables
  * @{
  */
__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
__I uint8_t APBPrescTable[8UL] =  {0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL};


/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_FunctionPrototypes
  * @{
  */
uint32_t SystemCoreClock;
uint32_t SystemFrequency_SysClk;        /*!< System clock                        */
uint32_t SystemFrequency_AHBClk;        /*!< AHB System bus speed                */
uint32_t SystemFrequency_APB1Clk;       /*!< APB Peripheral bus 1 (low)  speed   */
uint32_t SystemFrequency_APB2Clk;       /*!< APB Peripheral bus 2 (high) speed   */
uint32_t SystemFreq_APB1MClk;
uint32_t SystemFreq_APB2MClk;
static void SetSysClock(void);

void system_base_clk(void)
{
    uint8 * data_ram, * data_rom, * data_rom_end;
    uint8 * bss_start, * bss_end;
    uint32 n;
    
    data_ram     = __section_begin(".data");
    data_rom     = __section_begin(".data_init");
    data_rom_end = __section_end(".data_init");
    n = data_rom_end - data_rom;
        
    while (n--)
        *data_ram++ = *data_rom++;
  
    bss_start = __section_begin(".bss");
    bss_end = __section_end(".bss");
    n = bss_end - bss_start;
    while(n--)
        *bss_start++ = 0;
    
    uint8* code_relocate_ram = __section_begin("CodeRelocateRam");
    uint8* code_relocate     = __section_begin("CodeRelocate");
    uint8* code_relocate_end = __section_end("CodeRelocate");

    /* Copy functions from ROM to RAM */
    n = code_relocate_end - code_relocate;
    while (n--)
        *code_relocate_ram++ = *code_relocate++;    
    
    SystemCoreClock         = SYS_CLK;        /*!< System Clock Frequency (Core Clock) */
    SystemFrequency_SysClk  = SYS_CLK;        /*!< System clock                        */
    SystemFrequency_AHBClk  = SYS_CLK;        /*!< AHB System bus speed                */
    SystemFrequency_APB1Clk = SYS_CLK;        /*!< APB Peripheral bus 1 (low)  speed   */
    SystemFrequency_APB2Clk = SYS_CLK;        /*!< APB Peripheral bus 2 (high) speed   */
    SystemFreq_APB1MClk     = SYS_MCLK;
    SystemFreq_APB2MClk     = SYS_MCLK;
}

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* Set HSION bit */
  RCC->CR |= RCC_CR_HSION;

  /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits */
  RCC->CFGR &= (uint32_t)0xf8ff80f8;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  RCC->PLLCFGR &= (uint32_t)0xeffe908c;
  RCC->PLLCFGR |= (uint32_t)0x20021072;

  /* Reset USARTSW[1:0], I2CSW, CECSW and ADCSW bits */
  RCC->CCIPR &= (uint32_t)0x3FFF0ff0;

  /* Disable all interrupts */
  RCC->CIER = 0x00000000;

  /* Configure the System clock frequency, AHB/APBx prescalers and Flash settings */
  SetSysClock();
}

/**
  * @brief  Configures the System clock frequency, AHB/APBx prescalers and Flash
  *         settings.
  * @note   This function should be called only once the RCC clock configuration
  *         is reset to the default reset state (done in SystemInit() function).
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer and set Flash Latency */
    FLASH->ACR |= (FLASH_ACR_PRFTEN | FLASH_ACR_ICEN);
    if((SYS_CLK > 24000000) && (SYS_CLK <= 48000000))
    {
        /* 1 cycle. */
        FLASH->ACR |= FLASH_ACR_LATENCY_0;
    }
    else if(SYS_CLK > 48000000)
    {
        /* 2 cycle. */
        FLASH->ACR |= FLASH_ACR_LATENCY_1;
    }
 
    /* HCLK = SYSCLK PCLK = HCLK */
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE);
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE_DIV1;

    /* input is 4M * 9 = 36M. */
    RCC->PLLCFGR &= (uint32_t)((uint32_t)~(RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLPEN | RCC_PLLCFGR_PLLREN | RCC_PLLCFGR_PLLR));
    if(HSE_Value == 8000000)
    {
        /* clock / 1 pll input 8M. */
        RCC->PLLCFGR |= (uint32_t)(RCC_PLLCFGR_PLLM_DIV_1 | RCC_PLLCFGR_PLLSRC);
    }
    else if(HSE_Value == 16000000)
    {
        /* clock / 2 pll input 8M. */
        RCC->PLLCFGR |= (uint32_t)(RCC_PLLCFGR_PLLM_DIV_2 | RCC_PLLCFGR_PLLSRC);
    }
#ifdef SYSCLK_FREQ_24MHz
    RCC->PLLCFGR |= (uint32_t)(RCC_PLLCFGR_PLLN_9  | RCC_PLLCFGR_PLLR_DIV_3 | RCC_PLLCFGR_PLLREN);
#elif defined SYSCLK_FREQ_32MHz
    RCC->PLLCFGR |= (uint32_t)(RCC_PLLCFGR_PLLN_12 | RCC_PLLCFGR_PLLR_DIV_3 | RCC_PLLCFGR_PLLREN);
#elif defined SYSCLK_FREQ_36MHz
    RCC->PLLCFGR |= (uint32_t)(RCC_PLLCFGR_PLLN_9  | RCC_PLLCFGR_PLLR_DIV_2 | RCC_PLLCFGR_PLLREN);
#elif defined SYSCLK_FREQ_48MHz
    RCC->PLLCFGR |= (uint32_t)(RCC_PLLCFGR_PLLN_12 | RCC_PLLCFGR_PLLR_DIV_2 | RCC_PLLCFGR_PLLREN);
#endif
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLLRCLK;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }  
}

/**************************************************************************
* function name   : void Hw_InterruptEn(SBYTE ucIrq)
* Description     : enable the interrupt.
* Input parameter : SBYTE ucIrq:interrupt number.
* Output parameter: no.
* Return          : no.
* Other description:
     the interrupt number can not be negative.
* Modify date     Ver.     Modifier      Action
* ------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
**************************************************************************/
void Hw_InterruptEn(SBYTE ucIrq)
{
    NVIC_EnableIRQ((IRQn_Type)ucIrq);
    
    return;
}

/**************************************************************************
* function name   : void Hw_InterruptDis(SBYTE ucIrq)
* Description     : disable the interrupt.
* Input parameter : SBYTE ucIrq:interrupt number.
* Output parameter: no.
* Return          : no.
* Other description:
     the interrupt number can not be negative.
* Modify date     Ver.     Modifier      Action
* ------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
**************************************************************************/
void Hw_InterruptDis(SBYTE ucIrq)
{
    NVIC_DisableIRQ((IRQn_Type)ucIrq);
    
    return;
}

/**************************************************************************
* function name   : void Hw_SetIntPriority(SBYTE ucIrq,BYTE ucPriority)
* Description     : set the interrupt priority.
* Input parameter : BYTE ucIrq     :interrupt number.
                    BYTE ucPriority:priority.
* Output parameter: no.
* Return          : no.
* Other description:
* Modify date     Ver.     Modifier      Action
* ------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
**************************************************************************/
void Hw_SetIntPriority(SBYTE ucIrq,BYTE ucPriority)
{
    NVIC_SetPriority((IRQn_Type)ucIrq,(WORD32)ucPriority);
    
    return;
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
