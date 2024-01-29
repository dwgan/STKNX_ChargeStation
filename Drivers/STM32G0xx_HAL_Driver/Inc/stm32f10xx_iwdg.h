/********************************************************************
* Right reserved (C 2016) for *********** company.
*
* File Name        : Stm32F10XX_iwdg.h
*
* File Description : Header file for stm32f10xx iwdg definition.
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


#ifndef _STM32F10XX_IWDG_H_
#define _STM32F10XX_IWDG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* key for iwdg operation. */
#define IWDG_START_KEY         0xCCCC
#define IWDG_RELOAD_KEY        0xAAAA
#define IWDG_UNLOCK_KEY        0x5555
#define IWDG_MAX_CUNTER        0xFFF

/************************************************************************************
* function name   : VOID Stm32F10xx_Iwdg_Init(WORD16 wWdgTime)
* Description     : Initialize the iwdg.
* Input parameter : WORD16 wWdgTime:watchdog overtime in ms.
* Output parameter: no.
* Return          : no.
* Other description:
        The maxmum time is 26000ms.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
VOID Stm32F10xx_Iwdg_Init(WORD16 wWdgTime);

/************************************************************************************
* function name   : VOID Stm32F10xx_Iwdg_Reset(VOID)
* Description     : reset the iwdg.
* Input parameter : no.
* Output parameter: no.
* Return          : no.
* Other description:
        The maxmum time is 26000ms.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
VOID Stm32F10xx_Iwdg_Reset(VOID);

#ifdef __cplusplus
}
#endif

#endif



/* end of file _STM32F10XX_IWDG_H_ */

