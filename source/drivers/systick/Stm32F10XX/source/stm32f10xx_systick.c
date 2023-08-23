/******************************************************************************
* File       : systick.c
* Function   : Systick driver for stm32f10x
* description: This driver realise the basic function of systick initialization.
* Version    : V1.00
* Author     : Ian
* Date       : 31sr Jul 2016
* History    :  No.  When           Who           What
*               1    31/Jul/2016    Ian           Create
******************************************************************************/


#include "type_def.h"
#include "hardware.h"

#include "sw_common.h"
#include "pub.h"
#include "boardcfg.h"
#include "system_stm32f10x.h"
#include "stm32f10xx_systick.h"
#include "ctrl_service.h"





/* Timer operation functions */
static T_DEV_OPERATION sg_tTimerOp;

/* Callback function for timer interrupt */
static void (*sg_pfAppCallBack)(T_SW_INT_EVENT *ptReason) = NULL;     

/**************************************************************************
* Function: WORD32 SysTick_Timer_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Timer initialization of systick timer, set prescaler/callback and enable
*           interrupt
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara:
               ucPara[0] = SW_PERIPHERAL_TIMER : timer ID
               ucPara[1] = ucDevNo             : device logical no.
               ucPara[2] = SW_TIMER_TM_MODE    : working mode. 
               ucPara[3] = KNX_TIMER_SACLE     : time scale,0 < ucPara[3] < 64ms;
                                                 or        10 < ucPara[3] < 256 us;
               ucPara[4] = SW_TIMER_MS/SW_TIMER_US
               pIntCallBackHandler             : call back handler.
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
WORD32 SysTick_Timer_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    WORD16 wTime;
    WORD32 dwFreq,dwScale;

    /* Check if input parameter is valid or NOT */
    if(NULL == ptPara)                                                          
    {
        return SW_ERR;
    }

    wTime = ptPara->ucPara[SYSTICK_INT_PERIOD_POS];       /* Get the period time */  
    /* If the period time is 0 */
    if (0 == wTime)                                             
    {
        return SW_ERR;
    }

    /* Get HCLK */
    dwFreq = SystemFrequency_AHBClk;
    if(SW_TIMER_MS == ptPara->ucPara[SYSTICK_INT_PERIOD_SCALE])
    {
        dwScale = 1000;
    }
    else
    {
        dwScale = 1000000;
    }

    SYSTICK_CTRL &= ~SYSTICK_CTRL_ENABLE_MASK;     /* Disable systick first */
    SYSTICK_CTRL |=  SYSTICK_CTRL_CLKSOURCE_MASK;  /* Select AHB clock      */
    SYSTICK_CTRL |=  SYSTICK_CTRL_TICKINT_MASK;    /* Enable interrupt      */

    SYSTICK_LOAD  =  dwFreq / dwScale * wTime;     /* Set the period in ms  */
    SYSTICK_VAL   =  0;                            /* Clear timer counter   */

    SYSTICK_CTRL |=  SYSTICK_CTRL_ENABLE_MASK;     /* Enable systick        */

    /* Get the callback function */
    sg_pfAppCallBack = ptPara->pIntCallBackHandler; 
    
    return SW_OK;        

}


/**************************************************************************
* Funciton: void SysTick_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
* Descrip.: Register system ticker.
* Input   : BYTE ucLogNo      Device logic No.
*           BYTE ucDevNo      Device physical No.
*           VOID *ptPara      None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
void SysTick_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
{    
    T_REGISTED_DEVICE tTimer;  
 
    sg_tTimerOp.pfDrvInit  = SysTick_Timer_Init;
    sg_tTimerOp.pfDrvCtrl  = NULL;
    sg_tTimerOp.pfDrvRead  = NULL;
    sg_tTimerOp.pfDrvWrite = NULL;
    /* set device parameter. */
    tTimer.ucAppType = SW_CONTROL_INTERFACE;
    tTimer.ucDevId   = SW_PERIPHERAL_TIMER;
    tTimer.ucLogDevNo= ucLogNo;
    tTimer.ucDevNo   = ucDevNo;
    tTimer.ptDevOp   = &sg_tTimerOp;
    tTimer.pfCallBack= NULL;
    /* register to the interface. */
    API_TimerDrv_Reg(&tTimer);
    
    return;
}



/**************************************************************************
* Funciton: void SysTick_Timer_isr(void)
* Descrip.: interrupt process function of SysTick
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
void SysTick_Timer_isr(void)
{
    volatile WORD32 dwTemp;
    T_SW_INT_EVENT tReason;

    /* Clear interrupt flag */
    dwTemp = SYSTICK_CTRL & SYSTICK_CTRL_COUNTFLAG_MASK;   

    /* Fill interrupt information */
    tReason.ucAppType = SW_CONTROL_INTERFACE;                
    tReason.ucDevId   = SW_PERIPHERAL_TIMER;               
    tReason.ucDevNo   = 0; 
    tReason.ucEvent   = INTERRUPT_TIMER_OVER;                                 

    /* If we have callback to do */
    if(sg_pfAppCallBack)
    {   /* Call callback function for upper layer */
        (sg_pfAppCallBack)(&tReason);                                          
    }
    return;
}



/* End of systick.c */


