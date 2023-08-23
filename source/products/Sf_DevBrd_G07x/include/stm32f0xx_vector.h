/********************************************************************
* Right reserved (C 2016) Nanjing Shufan Information Technology Co.,Ltd.
*
* File Name        : stm32f10x_vector.h
*
* File Description : Header file for board interrupt set definition.
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

#ifndef _STM32F10X_VECTOR_H_
#define _STM32F10X_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  uint32_t CPUID;                        /*!< CPU ID Base Register                                     */
  uint32_t ICSR;                         /*!< Interrupt Control State Register                         */
  uint32_t VTOR;                         /*!< Vector Table Offset Register                             */
  uint32_t AIRCR;                        /*!< Application Interrupt / Reset Control Register           */
  uint32_t SCR;                          /*!< System Control Register                                  */
  uint32_t CCR;                          /*!< Configuration Control Register                           */
  uint8_t  SHP[12];                      /*!< System Handlers Priority Registers (4-7, 8-11, 12-15)    */
  uint32_t SHCSR;                        /*!< System Handler Control and State Register                */
  uint32_t CFSR;                         /*!< Configurable Fault Status Register                       */
  uint32_t HFSR;                         /*!< Hard Fault Status Register                               */
  uint32_t DFSR;                         /*!< Debug Fault Status Register                              */
  uint32_t MMFAR;                        /*!< Mem Manage Address Register                              */
  uint32_t BFAR;                         /*!< Bus Fault Address Register                               */
  uint32_t AFSR;                         /*!< Auxiliary Fault Status Register                          */
  uint32_t PFR[2];                       /*!< Processor Feature Register                               */
  uint32_t DFR;                          /*!< Debug Feature Register                                   */
  uint32_t ADR;                          /*!< Auxiliary Feature Register                               */
  uint32_t MMFR[4];                      /*!< Memory Model Feature Register                            */
  uint32_t ISAR[5];                      /*!< ISA Feature Register                                     */
} SCB_LogType;

#define WWDG_IRQHandler                 default_isr /* Window Watchdog                                  */
#define PVD_IRQHandler                  default_isr /* PVD through EXTI Line detect                     */
#define RTC_IRQHandler                  default_isr /* RTC through EXTI Line                            */
#define FLASH_IRQHandler                default_isr /* FLASH                                            */
#define RCC_IRQHandler                  default_isr /* RCC                                              */
#define EXTI0_1_IRQHandler              default_isr /* EXTI Line 0 and 1                                */
#define EXTI2_3_IRQHandler              default_isr /* EXTI Line 2 and 3                                */
#define EXTI4_15_IRQHandler             default_isr /* EXTI Line 4 to 15                                */
#define TS_IRQHandler                   default_isr /* TS                                               */
#define DMA1_Channel1_IRQHandler        default_isr /* DMA1 Channel 1                                   */
#define DMA1_Channel2_3_IRQHandler      default_isr /* DMA1 Channel 2 and Channel 3                     */
#define DMA1_Channel4_5_IRQHandler      default_isr /* DMA1 Channel 4 and Channel 5                     */
#define ADC1_COMP_IRQHandler            default_isr /* ADC1, COMP1 and COMP2                            */
#define TIM1_BRK_UP_TRG_COM_IRQHandler  default_isr /* TIM1 Break, Update, Trigger and Commutation      */
#define TIM1_CC_IRQHandler              default_isr /* TIM1 Capture Compare                             */
#define TIM2_IRQHandler                 default_isr /* TIM2                                             */
#define TIM3_IRQHandler                 default_isr /* TIM3                                             */
#define TIM6_DAC_IRQHandler             default_isr /* TIM6 and DAC                                     */
#define TIM14_IRQHandler                default_isr /* TIM14                                            */
#define TIM15_IRQHandler                default_isr /* TIM15                                            */
#define TIM16_IRQHandler                default_isr /* TIM16                                            */
#define TIM17_IRQHandler                default_isr /* TIM17                                            */
#define I2C1_IRQHandler                 default_isr /* I2C1                                             */
#define I2C2_IRQHandler                 default_isr /* I2C2                                             */
#define SPI1_IRQHandler                 default_isr /* SPI1                                             */
#define SPI2_IRQHandler                 default_isr /* SPI2                                             */
#define USART1_IRQHandler               default_isr /* USART1                                           */
//#define USART2_IRQHandler               default_isr /* USART2                                           */
#define CEC_IRQHandler                  default_isr /* CEC                                              */

/* function defined for interrupt vector table. */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void Default_Isr(void);
void default_isr(void);

void USART2_IRQHandler(void);



#ifdef __cplusplus
}
#endif

#endif /* _BOARDINT_SET_H_ */



/* end of file */
