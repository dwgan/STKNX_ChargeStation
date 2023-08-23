/********************************************************************
* Right reserved (C 2016) ,Nanjing Shufan Information Technology Co.,Ltd.
*
* File Name        : BoardIntVect_Set.c
*
* File Description : this file is used for the interrupt table define
*                    for a specific device.
*                    when developping a new device,the programer should
*                    fill the used interrupt vector into the vector table.
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

#include "type_def.h"
#include "Boardcfg.h"
#include "Hardware.h"


#include "sw_common.h"
#include "stm32f0xx_vector.h"
#include "Stm32F10xx_systick.h"
#include "knx_chip.h"
#include "Stm32G0xxx_adc.h"

#include "stm32g0xx_hal_uart.h"

#if DEBUG_MODE_OPEN
    SCB_LogType g_tCpuScbReg;
#endif 


extern unsigned long __BOOT_STACK_ADDRESS[];
extern void Reset_Handler(void );

/* UART handler declaration in boradctrl.c */
extern UART_HandleTypeDef UartHandle;

extern void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);


#pragma location = ".intvec"
const vector_entry  __vector_table[] =\
{
    (vector_entry)__BOOT_STACK_ADDRESS,
    Reset_Handler                  , // Reset Handler
    default_isr                    , // NMI Handler
    default_isr                    , // Hard Fault Handler
    0                              , // Reserved
    0                              , // Reserved
    0                              , // Reserved
    0                              , // Reserved
    0                              , // Reserved
    0                              , // Reserved
    0                              , // Reserved
    default_isr                    , // SVCall Handler
    0                              , // Reserved
    0                              , // Reserved
    default_isr                    , // PendSV Handler
    SysTick_Timer_isr              , // SysTick Handler

    // External Interrupts
    default_isr                    , // Window Watchdog
    default_isr                    , // PVD through EXTI Line detect
    default_isr                    , // RTC through EXTI Line
    default_isr                    , // FLASH
    default_isr                    , // RCC
    default_isr                    , // EXTI Line 0 and 1
    default_isr                    , // EXTI Line 2 and 3
    default_isr                    , // EXTI Line 4 to 15
    default_isr                    , // TS
    default_isr                    , // DMA1 Channel 1
    default_isr                    , // DMA1 Channel 2 and Channel 3
    default_isr                    , // DMA1 Channel 4 and Channel 5
    Adcx_isr                       , // ADC1, COMP1 and COMP2 
    default_isr                    , // TIM1 Break, Update, Trigger and Commutation
    KnxPh_RxByteAndBit_Int         , // TIM1 Capture Compare
    default_isr                    , // TIM2
    KnxPh_TxByteAndBit_Int         , // TIM3
    default_isr                    , // TIM6 and DAC
    default_isr                    , // TIM7
    default_isr                    , // TIM14
    default_isr                    , // TIM15
    default_isr                    , // TIM16
    default_isr                    , // TIM17
    default_isr                    , // I2C1
    default_isr                    , // I2C2
    default_isr                    , // SPI1
    default_isr                    , // SPI2
    default_isr                    , // USART1
    USART2_IRQHandler              , // USART2
    0                              , // Reserved
    default_isr                    , // CEC
    0                                // Reserved
};

void default_isr(void)
{
    RCC_IOPENR   |= RCC_IOPENR_GPIOAEN;
    GPIOA->MODER &= (~GPIO_MODER_MODER7);            /* out. */
    GPIOA->MODER |= GPIO_MODER_MODER7_0;
    CLR_GPIO_PORT(A,7);
    
    while(1);
}

/** @addtogroup EEPROM_Emulation
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */

void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
#if DEBUG_MODE_OPEN
        BYTE ucIndex;
          
        g_tCpuScbReg.CPUID = SCB->CPUID;                        /*!< CPU ID Base Register                                     */
        g_tCpuScbReg.ICSR  = SCB->ICSR;                         /*!< Interrupt Control State Register                         */
        g_tCpuScbReg.VTOR  = SCB->VTOR;                         /*!< Vector Table Offset Register                             */
        g_tCpuScbReg.AIRCR = SCB->AIRCR;                        /*!< Application Interrupt / Reset Control Register           */
        g_tCpuScbReg.SCR   = SCB->SCR;                          /*!< System Control Register                                  */
        g_tCpuScbReg.CCR   = SCB->CCR;                          /*!< Configuration Control Register                           */
        for(ucIndex = 0;ucIndex<12;ucIndex++)
        {
            g_tCpuScbReg.SHP[ucIndex] = SCB->SHP[ucIndex];      /*!< System Handlers Priority Registers (4-7, 8-11, 12-15)    */
        }
        g_tCpuScbReg.SHCSR = SCB->SHCSR;                        /*!< System Handler Control and State Register                */
        g_tCpuScbReg.CFSR  = SCB->CFSR;                         /*!< Configurable Fault Status Register                       */
        g_tCpuScbReg.HFSR  = SCB->HFSR;                         /*!< Hard Fault Status Register                               */
        g_tCpuScbReg.DFSR  = SCB->DFSR;                         /*!< Debug Fault Status Register                              */
        g_tCpuScbReg.MMFAR = SCB->MMFAR;                        /*!< Mem Manage Address Register                              */
        g_tCpuScbReg.BFAR  = SCB->BFAR;                         /*!< Bus Fault Address Register                               */
        g_tCpuScbReg.AFSR  = SCB->AFSR;                         /*!< Auxiliary Fault Status Register                          */
        g_tCpuScbReg.PFR[0]= SCB->PFR[0];                       /*!< Processor Feature Register                               */
        g_tCpuScbReg.PFR[1]= SCB->PFR[1];                       /*!< Processor Feature Register                               */
        g_tCpuScbReg.DFR   = SCB->DFR;                          /*!< Debug Feature Register                                   */
        g_tCpuScbReg.ADR   = SCB->ADR;                          /*!< Auxiliary Feature Register                               */
        for(ucIndex = 0;ucIndex<4;ucIndex++)
        {
            g_tCpuScbReg.MMFR[ucIndex] = SCB->MMFR[ucIndex];    /*!< Memory Model Feature Register                            */
            g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];    /*!< ISA Feature Register                                     */
        }
        g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];
#endif

    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
      /* Go to infinite loop when Memory Manage exception occurs */
#if DEBUG_MODE_OPEN
      BYTE ucIndex;
        
      g_tCpuScbReg.CPUID = SCB->CPUID;                        /*!< CPU ID Base Register                                     */
      g_tCpuScbReg.ICSR  = SCB->ICSR;                         /*!< Interrupt Control State Register                         */
      g_tCpuScbReg.VTOR  = SCB->VTOR;                         /*!< Vector Table Offset Register                             */
      g_tCpuScbReg.AIRCR = SCB->AIRCR;                        /*!< Application Interrupt / Reset Control Register           */
      g_tCpuScbReg.SCR   = SCB->SCR;                          /*!< System Control Register                                  */
      g_tCpuScbReg.CCR   = SCB->CCR;                          /*!< Configuration Control Register                           */
      for(ucIndex = 0;ucIndex<12;ucIndex++)
      {
          g_tCpuScbReg.SHP[ucIndex] = SCB->SHP[ucIndex];      /*!< System Handlers Priority Registers (4-7, 8-11, 12-15)    */
      }
      g_tCpuScbReg.SHCSR = SCB->SHCSR;                        /*!< System Handler Control and State Register                */
      g_tCpuScbReg.CFSR  = SCB->CFSR;                         /*!< Configurable Fault Status Register                       */
      g_tCpuScbReg.HFSR  = SCB->HFSR;                         /*!< Hard Fault Status Register                               */
      g_tCpuScbReg.DFSR  = SCB->DFSR;                         /*!< Debug Fault Status Register                              */
      g_tCpuScbReg.MMFAR = SCB->MMFAR;                        /*!< Mem Manage Address Register                              */
      g_tCpuScbReg.BFAR  = SCB->BFAR;                         /*!< Bus Fault Address Register                               */
      g_tCpuScbReg.AFSR  = SCB->AFSR;                         /*!< Auxiliary Fault Status Register                          */
      g_tCpuScbReg.PFR[0]= SCB->PFR[0];                       /*!< Processor Feature Register                               */
      g_tCpuScbReg.PFR[1]= SCB->PFR[1];                       /*!< Processor Feature Register                               */
      g_tCpuScbReg.DFR   = SCB->DFR;                          /*!< Debug Feature Register                                   */
      g_tCpuScbReg.ADR   = SCB->ADR;                          /*!< Auxiliary Feature Register                               */
      for(ucIndex = 0;ucIndex<4;ucIndex++)
      {
          g_tCpuScbReg.MMFR[ucIndex] = SCB->MMFR[ucIndex];    /*!< Memory Model Feature Register                            */
          g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];    /*!< ISA Feature Register                                     */
      }
      g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];
#endif    
     while (1)
     {
     }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
#if DEBUG_MODE_OPEN
        BYTE ucIndex;
          
        g_tCpuScbReg.CPUID = SCB->CPUID;                        /*!< CPU ID Base Register                                     */
        g_tCpuScbReg.ICSR  = SCB->ICSR;                         /*!< Interrupt Control State Register                         */
        g_tCpuScbReg.VTOR  = SCB->VTOR;                         /*!< Vector Table Offset Register                             */
        g_tCpuScbReg.AIRCR = SCB->AIRCR;                        /*!< Application Interrupt / Reset Control Register           */
        g_tCpuScbReg.SCR   = SCB->SCR;                          /*!< System Control Register                                  */
        g_tCpuScbReg.CCR   = SCB->CCR;                          /*!< Configuration Control Register                           */
        for(ucIndex = 0;ucIndex<12;ucIndex++)
        {
            g_tCpuScbReg.SHP[ucIndex] = SCB->SHP[ucIndex];      /*!< System Handlers Priority Registers (4-7, 8-11, 12-15)    */
        }
        g_tCpuScbReg.SHCSR = SCB->SHCSR;                        /*!< System Handler Control and State Register                */
        g_tCpuScbReg.CFSR  = SCB->CFSR;                         /*!< Configurable Fault Status Register                       */
        g_tCpuScbReg.HFSR  = SCB->HFSR;                         /*!< Hard Fault Status Register                               */
        g_tCpuScbReg.DFSR  = SCB->DFSR;                         /*!< Debug Fault Status Register                              */
        g_tCpuScbReg.MMFAR = SCB->MMFAR;                        /*!< Mem Manage Address Register                              */
        g_tCpuScbReg.BFAR  = SCB->BFAR;                         /*!< Bus Fault Address Register                               */
        g_tCpuScbReg.AFSR  = SCB->AFSR;                         /*!< Auxiliary Fault Status Register                          */
        g_tCpuScbReg.PFR[0]= SCB->PFR[0];                       /*!< Processor Feature Register                               */
        g_tCpuScbReg.PFR[1]= SCB->PFR[1];                       /*!< Processor Feature Register                               */
        g_tCpuScbReg.DFR   = SCB->DFR;                          /*!< Debug Feature Register                                   */
        g_tCpuScbReg.ADR   = SCB->ADR;                          /*!< Auxiliary Feature Register                               */
        for(ucIndex = 0;ucIndex<4;ucIndex++)
        {
            g_tCpuScbReg.MMFR[ucIndex] = SCB->MMFR[ucIndex];    /*!< Memory Model Feature Register                            */
            g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];    /*!< ISA Feature Register                                     */
        }
        g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];
#endif    
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
#if DEBUG_MODE_OPEN
        BYTE ucIndex;
          
        g_tCpuScbReg.CPUID = SCB->CPUID;                        /*!< CPU ID Base Register                                     */
        g_tCpuScbReg.ICSR  = SCB->ICSR;                         /*!< Interrupt Control State Register                         */
        g_tCpuScbReg.VTOR  = SCB->VTOR;                         /*!< Vector Table Offset Register                             */
        g_tCpuScbReg.AIRCR = SCB->AIRCR;                        /*!< Application Interrupt / Reset Control Register           */
        g_tCpuScbReg.SCR   = SCB->SCR;                          /*!< System Control Register                                  */
        g_tCpuScbReg.CCR   = SCB->CCR;                          /*!< Configuration Control Register                           */
        for(ucIndex = 0;ucIndex<12;ucIndex++)
        {
            g_tCpuScbReg.SHP[ucIndex] = SCB->SHP[ucIndex];      /*!< System Handlers Priority Registers (4-7, 8-11, 12-15)    */
        }
        g_tCpuScbReg.SHCSR = SCB->SHCSR;                        /*!< System Handler Control and State Register                */
        g_tCpuScbReg.CFSR  = SCB->CFSR;                         /*!< Configurable Fault Status Register                       */
        g_tCpuScbReg.HFSR  = SCB->HFSR;                         /*!< Hard Fault Status Register                               */
        g_tCpuScbReg.DFSR  = SCB->DFSR;                         /*!< Debug Fault Status Register                              */
        g_tCpuScbReg.MMFAR = SCB->MMFAR;                        /*!< Mem Manage Address Register                              */
        g_tCpuScbReg.BFAR  = SCB->BFAR;                         /*!< Bus Fault Address Register                               */
        g_tCpuScbReg.AFSR  = SCB->AFSR;                         /*!< Auxiliary Fault Status Register                          */
        g_tCpuScbReg.PFR[0]= SCB->PFR[0];                       /*!< Processor Feature Register                               */
        g_tCpuScbReg.PFR[1]= SCB->PFR[1];                       /*!< Processor Feature Register                               */
        g_tCpuScbReg.DFR   = SCB->DFR;                          /*!< Debug Feature Register                                   */
        g_tCpuScbReg.ADR   = SCB->ADR;                          /*!< Auxiliary Feature Register                               */
        for(ucIndex = 0;ucIndex<4;ucIndex++)
        {
            g_tCpuScbReg.MMFR[ucIndex] = SCB->MMFR[ucIndex];    /*!< Memory Model Feature Register                            */
            g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];    /*!< ISA Feature Register                                     */
        }
        g_tCpuScbReg.ISAR[ucIndex] = SCB->ISAR[ucIndex];
#endif    
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}



void USART2_IRQHandler(void)
{
   HAL_UART_IRQHandler(&UartHandle);
}







/* end of file. */
