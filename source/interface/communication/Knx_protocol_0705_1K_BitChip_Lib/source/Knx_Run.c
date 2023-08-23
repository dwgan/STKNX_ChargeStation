/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Run.c
* FileIdentifier：None
* Abstract ：KNX run status management source file.
* Other Description：
* Current Version：V1.00
* Author：      
* Completed Date：2013年7月24日
*    
* Modified History1：
*        Modified Date：2013年7月24日
*        Version Number：V1.00
*        Modified Person：      
*        Modified part：Add new public definition.
******************************************************************************/

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "BUffer.h"
#include "Knx_Run.h"
#include "Knx_Prop.h"
#include "Application_Data.h"
#include "knx_chip.h"
#include "Knx_M0705.h"
#include "Knx_M0705_Ll.h"
#include "Knx_Mem.h"
#include "Knx_AlApp.h"
#include "Knx_InternalApp.h"
#include "Knx_Msg.h"
#include "Knx_Timer.h"
#include "Knx_InternalData.h"
#include "Knx_TlState.h"
#include "Knx_LoadCtrl.h"
#include "Knx_Mem.h"


BYTE   sg_ucRunState = RUNSTATE_READY;  /* run status for application.  */
WORD16 sg_wStartTime = 0x0000;          /* Start time of bus voltage.  */
BYTE   sg_ucResetFgl;
WORD32 sg_dwResetPointTim;

/****************************************************************************************************************
* Function: VOID KnxRun_SetResetCmd(VOID)
* Descrip.: reset device.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxRun_SetResetCmd(VOID)
{
    sg_ucResetFgl      = RUN_RESET_FLG;
    sg_dwResetPointTim = KnxTm_GetTimeMs();
    
    return;
}

/**************************************************************************************************************
* FunctionName:BOOL Knx_StartRunApplication(VOID)
* FunctionDescription: This function initializes the application.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_StartRunApplication(VOID)
{
    BOOL ucCheck;
    WORD16 wAppId;
    
    /* Already started? */
    if(Knx_GetRunState() == RUNSTATE_RUNNING)
    {
        return FALSE;
    }
    /* halted. */
    sg_ucRunState = RUNSTATE_HALTED;
    
    KnxMem_Init();
    ucCheck = Knx_CheckRunConditions();
    if(ucCheck == FALSE)
    {
        /* run conditions are fulfilled? */
        return FALSE;
    }

    /* check application ID. */
    wAppId = KnxMem_GetWord(VIR_APP_ID);
    if(wAppId != APP_ID)
    {
        return FALSE;
    }
    
    /* AL initiation. */
    ucCheck = KnxAl_Init();
    if(FALSE == ucCheck)
    {
        return FALSE;
    }
    /* Application initiation. */
    ucCheck = Knx_InternalApp_Entry(APP_MAIN_INIT_FUNC);
    if(FALSE == ucCheck)
    {
        /* failed. */
        KnxAl_Close();
        return FALSE;
    }
    /* set run state:running. */
    sg_ucRunState = RUNSTATE_RUNNING;
    sg_ucResetFgl = 0;

    return TRUE;
}

/**************************************************************************************************************
* FunctionName:VOID Knx_SetRunState(BYTE ucControl)
* FunctionDescription: This function set the run state.
* InputParameterBYTE ucControl:run control byte.
                 RUNCONTROL_NO_OPERATION
                 RUNCONTROL_RESTART
                 RUNCONTROL_STOP
                 RUNCONTROL_HALT
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_SetRunState(BYTE ucControl)
{
    BYTE ucRes;
    
    switch(ucControl)
    {
        case RUNCONTROL_NO_OPERATION:
        {
            /* do nothing. */
            break;
        }
        case RUNCONTROL_RESTART:
        {
            /* restart application. */
            ucRes = Knx_GetRunState();
            if(ucRes == RUNSTATE_TERMINATED)
            {
                Knx_StartRunApplication();
            }
            break;
        }
        case RUNCONTROL_STOP:
        case RUNCONTROL_HALT:
        {
            ucRes = Knx_GetRunState();
            if(ucRes == RUNSTATE_RUNNING)
            {
                Knx_InternalApp_Entry(APP_SAVE_FUNC);
                /* close app. */
                KnxAl_Close();   
            }
            /* change run state. */
            if(ucControl == RUNCONTROL_STOP)
            {
                sg_ucRunState = RUNSTATE_TERMINATED;
            }
            else
            {
                sg_ucRunState = RUNSTATE_HALTED;
            }
            break;
        }
    }
    
    return;
}

/**************************************************************************************************************
* FunctionName:BYTE Knx_GetRunStateEx(VOID)
* FunctionDescription: This function get the run state(with save flags).
* InputParameterno.
* OutputParameterno.
* Return Value：run state with save flags.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE Knx_GetRunStateEx(VOID)
{
    return sg_ucRunState;
}

/**************************************************************************************************************
* FunctionName:BYTE Knx_GetRunState(VOID)
* FunctionDescription: This function get the run state(without save flags).
* InputParameterno.
* OutputParameterno.
* Return Value：run state without save flags.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE Knx_GetRunState(VOID)
{
    return (sg_ucRunState & RUNSTATE_MASK_EXT);
}

/**************************************************************************************************************
* FunctionName:BOOL Knx_CallAppFunction(BYTE ucFunctionId,BYTE* pucBuffer,BYTE *pucDwBuf);
* FunctionDescription: calling a function in application.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_CallAppFunction(BYTE ucFunctionId, BYTE* pucBuffer,BYTE *pucDwBuf)
{
    return FALSE;
}

/**************************************************************************************************************
* FunctionName:VOID Knx_RunProcess(VOID)
* FunctionDescription: managing the application precess.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:It will be called periodically.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_RunProcess(VOID)
{
    BOOL ucCheck;
    WORD32 dwTimDif;
    
    /* do we need to restart? */
    if(RUN_RESET_FLG == sg_ucResetFgl)
    {
        dwTimDif = KnxTm_GetDelayMs(sg_dwResetPointTim);
        if(dwTimDif > RUN_RESET_WAIT_TIM)
        {
            KnxLl_DisDev_Rx();
            /* write the memory data into the media really.Some data maybe in writing buffer ram. */
            KnxMem_WriteFinished();
            /* we should stop the application. */
            Knx_SetRunState(RUNCONTROL_STOP);
            /* restart the CPU,the real handler will be register into the KNX protocol by application. */
            Knx_Internal_ResetDev();
        }
    }
    
    /* Having power failure? */
    if(sg_ucRunState & RUNSTATE_MASK_SAVE)
    {
        /* switch off prg led to reduce power consume. */
        Knx_Internal_PrgmLedOff();
        /* No real failure? */
        ucCheck = Knx_Internal_BusPowerCheck();
        if(FALSE==ucCheck)
        {
            /* we should change this function to call save. */
            sg_ucRunState &= ~RUNSTATE_MASK_SAVE;
            return;
        }
        ucCheck = Knx_InternalApp_Entry(APP_SAVE_FUNC);
        if(FALSE==ucCheck)
        {
            sg_ucRunState &= ~RUNSTATE_MASK_SAVE;                       
            return;
        }
        /* Here we have a real failure */
        KnxLl_DisDev_Rx();         /* disable link layer receiving. */
        Knx_Internal_ResetDev();   /* reset CPU and wait. */
    }

    switch(sg_ucRunState & RUNSTATE_MASK_EXT)
    {
        case RUNSTATE_RUNNING:
        {
            /* application run the main function. */
            ucCheck = Knx_InternalApp_Entry(APP_MAIN_FUNC);
            if(FALSE==ucCheck)
            {
                /* failed? set to halted. */
                sg_ucRunState = RUNSTATE_HALTED;
            }
            break;
        }
        case RUNSTATE_READY:
        {
            WORD32 wStartDelay,wDelyTime;
            
            /* deleter user message. */
            Knx_MsgDelUserMsg();
            /* bus voltage not present? */
            ucCheck = Knx_Internal_BusPowerCheck();
            if(TRUE == ucCheck)
            {
                /* bus voltage is not present,we renew the start time. */
                sg_wStartTime = KnxTm_GetTimeMs();
                break;
            }
            /* calculate the delay time. */
            wStartDelay  = (BYTE)~GET_PHY_ADDR_LOW;    /* get the low physical address and invert it. */
            wStartDelay *= START_DELAY_MULT;
            wStartDelay += START_DELAY_CONST;
            wDelyTime = KnxTm_GetDelayMs(sg_wStartTime);
            if(wDelyTime > wStartDelay)
            {
                /* time is enough. */
                Knx_StartRunApplication();
            }
            break;
        }
        case RUNSTATE_HALTED:
        case RUNSTATE_TERMINATED:
        {
            /* halted or stopped,we delete the user message and call the app substitute. */
            BYTE ucSt;
            WORD32 dwTime;
            
            Knx_MsgDelUserMsg();
            ucSt = KnxTl_GetTlState();
            if(KNX_TL_CNECT_CLOSED==ucSt)
            {
                dwTime = KnxTm_GetTimeMs();
                if((dwTime>>8)&0x0001)
                {
                    Knx_Internal_PrgmLedOff();
                }
                else
                {
                    Knx_Internal_PrgmLedOn();
                }
            }
            break;
        }
    }
    
    return;
}

/**************************************************************************************************************
* FunctionName:BOOL Knx_CheckRunConditions(VOID)
* FunctionDescription: Checking whether the system is ready to start the application program.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_CheckRunConditions(VOID)
{
    BOOL ucCheck;
    
    ucCheck = Knx_CheckLoadStates();
    if(FALSE == ucCheck)
    {
        /* Load is not OK. */
        return FALSE;
    }
    ucCheck = KnxMem_CheckChecksum();
    if(FALSE == ucCheck)
    {
        /* memory is not OK. */
        return FALSE;
    }
    
    return TRUE;
}

/**************************************************************************************************************
* FunctionName:VOID Knx_RunOnBusPowerFail(VOID)
* FunctionDescription: if bus power failed this function will be called.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_RunOnBusPowerFail(VOID)
{
    sg_ucRunState |= RUNSTATE_FLAG_SAVE_BUS;
}

/**************************************************************************************************************
* FunctionName:VOID Knx_RunOnSupplyPowerFail(VOID)
* FunctionDescription: supply power failed should call this function.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_RunOnSupplyPowerFail(VOID)
{
    sg_ucRunState |= RUNSTATE_FLAG_SAVE_SUPPLY;
}


/* end of file. */

