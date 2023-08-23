/*****************************************************************************************
* Copy right (C) for *********** company.(2016)
*
* File Name        : Stm32F10XX_iwdg.c
*
* File Description : driver for stm32f10xx cpu's independent watchdog.
*
* Other Description: no.
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
*****************************************************************************************/




#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "boardcfg.h"
#include "Hardware.h"

#include "stm32f10xx_iwdg.h"

/* prescaler of iwdg. */
static const WORD16 sg_IwdgPrescaler[7] = {4,8,16,32,64,128,256};

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
VOID Stm32F10xx_Iwdg_Init(WORD16 wWdgTime)
{
    BYTE ucIndex;
    WORD16 wValue = 0;
    WORD32 dwCsr = RCC->CSR;
    
    /* Initialize the iwdg. */
    RCC->CSR |= RCC_CSR_LSION;   /* enable the clock of iwdg. */
    while(0==(dwCsr & RCC_CSR_LSIRDY))
    {
        /* waiting for the iwdg ready. */
        dwCsr = RCC->CSR;
    }
    /* we calculate the prescaler and the load value.the iwdg's clock is 40KHz. */
    for(ucIndex=0;ucIndex<7;ucIndex++)
    {
        wValue = (wWdgTime * 40)/sg_IwdgPrescaler[ucIndex];
        if(wValue <= IWDG_MAX_CUNTER)
        {
            /* we find the right prescaler index. */
            break;
        }
    }
    /* we write the right index and value to the iwdg register. */
    IWDG->KR  = IWDG_UNLOCK_KEY;
    IWDG->PR  = ucIndex;
    IWDG->RLR = wValue;
    IWDG->KR  = IWDG_START_KEY;
    
    return;
}

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
VOID Stm32F10xx_Iwdg_Reset(VOID)
{
    IWDG->KR = IWDG_RELOAD_KEY;
}

/* end of file */

