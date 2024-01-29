/**
  ******************************************************************************
  * @file    system_stm32g0xx.h
  * @author  MCD Application Team
  * @version V1.3.1
  * @date    17-January-2014
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Header File.
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
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32G0XX_H
#define __SYSTEM_STM32G0XX_H

#ifdef __cplusplus
 extern "C" {
#endif 
   
 #include "type_def.h"   

/** @addtogroup STM32F0xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup STM32F0xx_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
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

/** @addtogroup STM32F0xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F0xx_System_Exported_Functions
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

#endif /*__SYSTEM_STM32G0XX_H */

/**
  * @}
  */
  
/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
