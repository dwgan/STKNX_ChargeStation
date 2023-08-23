/**
  ******************************************************************************
  * @file    system_stm32f10x.h
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Header File.
  ******************************************************************************  
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f10x_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32F10X_H
#define __SYSTEM_STM32F10X_H

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup STM32F10x_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup STM32F10x_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;               /*!< System Clock Frequency (Core Clock) */
extern uint32_t SystemFrequency_SysClk;        /*!< System clock                        */
extern uint32_t SystemFrequency_AHBClk;        /*!< AHB System bus speed                */
extern uint32_t SystemFrequency_APB1Clk;       /*!< APB Peripheral bus 1 (low)  speed   */
extern uint32_t SystemFrequency_APB2Clk;       /*!< APB Peripheral bus 2 (high) speed   */
extern uint32_t SystemFreq_APB1MClk;
extern uint32_t SystemFreq_APB2MClk;

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
void Hw_InterruptEn(SBYTE ucIrq);

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
void Hw_InterruptDis(SBYTE ucIrq);

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
void Hw_SetIntPriority(SBYTE ucIrq,BYTE ucPriority);

void system_base_clk(void);



/**
  * @}
  */

/** @addtogroup STM32F10x_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F10x_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F10x_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32F10X_H */

/**
  * @}
  */
  
/**
  * @}
  */  
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
