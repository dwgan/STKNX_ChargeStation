/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Run.h
* FileIdentifier：None
* Abstract ：本文件为KNX协议栈状态处理头文件。
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



#ifndef _KNX_RUN_H_
#define _KNX_RUN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Run status machine define */
#define RUNSTATE_HALTED             0x00    /* The application is halted (e.g. no app loaded) */
#define RUNSTATE_RUNNING            0x01    /* The application is running                     */
#define RUNSTATE_READY              0x02    /* The application is ready to start (after reset)*/
#define RUNSTATE_TERMINATED         0x03    /* The application is stopped by external request */

/* Not extern (via property read) because only the low byte will be returned */
#define RUNSTATE_FLAG_SAVE_SUPPLY    0x40    /* A comming up power fail has been detected */
#define RUNSTATE_FLAG_SAVE_BUS       0x80    /* A comming up power fail has been detected */
#define RUNSTATE_MASK_EXT            0x0F    /* Mask to get the external run state  */
#define RUNSTATE_MASK_SAVE           0xF0    /* Mask to get the save flags in state */

/* Defines for run control commands (defined by KNX) */
#define RUNCONTROL_NO_OPERATION       0x00    /* No operation */
#define RUNCONTROL_RESTART            0x01    /* Request to start application */
#define RUNCONTROL_STOP               0x02    /* Request to stop application  */
/* Defines for run control commands (only used internally) */
#define RUNCONTROL_HALT               0xFF    /* Request to halt application */

/* Definitions for start delay */
#define START_DELAY_CONST            1700    /* Time constant in ms for application start   */
#define START_DELAY_MULT                5    /* Time mulitplier in ms for application start */
#define RUN_RESET_FLG                0x55
#define RUN_RESET_WAIT_TIM           40




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
BOOL Knx_StartRunApplication(VOID);

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
VOID Knx_SetRunState(BYTE ucControl);

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
BYTE Knx_GetRunStateEx(VOID);

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
BYTE Knx_GetRunState(VOID);

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
BOOL Knx_CallAppFunction(BYTE ucFunctionId,BYTE* pucBuffer,BYTE *pucDwBuf);

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
VOID Knx_RunProcess(VOID);

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
BOOL Knx_CheckRunConditions(VOID);

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
VOID Knx_RunOnBusPowerFail(VOID);

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
VOID Knx_RunOnSupplyPowerFail(VOID);

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
VOID KnxRun_SetResetCmd(VOID);






#ifdef __cplusplus
}
#endif

#endif /* _KNX_RUN_H_ */



/* end of file. */



