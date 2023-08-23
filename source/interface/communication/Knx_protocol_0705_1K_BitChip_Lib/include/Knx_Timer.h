/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_timer.h
* FileIdentifier：None
* Abstract ：KNX timer handle header file.
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

#ifndef _KNX_TIMER_H_
#define _KNX_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif



#define KNX_TIMER_SACLE             1           /* timing scale:1Ms. */



/**************************************************************************
* FunctionName:VOID KnxTm_TimerInit(BYTE ucDevNo)
* FunctionDescription: KNX定时器初始化接口，定时器1ms。
* InputParameterBYTE ucDevNo:device logical number.
* OutputParameterno.
* Return Value：no.
* Other Description:通过api提供给外部使用。定时器驱动通过注册方式注册到KNX定时器处理
            进行工作。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      Create 
**************************************************************************/
VOID KnxTm_TimerInit(BYTE ucDevNo);

/**************************************************************************
* FunctionName:WORD32 KnxTm_GetTimeMs(VOID)
* FunctionDescription: 获取当前计时毫秒数。
* InputParameter None。
* OutputParameter None。
* Return Value： 当前毫秒数：0-0xFFFFFFFF。
* Other Description: None
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      Create 
**************************************************************************/
WORD32 KnxTm_GetTimeMs(VOID);

/**************************************************************************
* FunctionName:WORD32 KnxTm_GetDelayMs(WORD32 dwOldTime)
* FunctionDescription: 获取给定时间跟当前时间的时差（毫秒）。
* InputParameter WORD16 wOldTime：给定老时间。
* OutputParameter None。
* Return Value： 时差，毫秒：0-0xFFFF。
* Other Description: None
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create 
**************************************************************************/
WORD32 KnxTm_GetDelayMs(WORD32 dwOldTime);

/**************************************************************************
* FunctionName:VOID KnxTm_UpdateCycle(VOID)
* FunctionDescription:  更新周期时间和计数。
* InputParameter None。
* OutputParameter None。
* Return Value： None。
* Other Description: None。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create
**************************************************************************/
VOID KnxTm_UpdateCycle(VOID);

/**************************************************************************
* FunctionName:WORD16 KnxTm_GetCycleTimeMs(VOID)
* FunctionDescription:  获取循环周期时间（毫秒）。
* InputParameter None。
* OutputParameter None。
* Return Value： 时间值（毫秒，0~0xFFFF）
* Other Description: 需要在循环中调用KnxTm_UpdateCycle函数更新时间。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create
**************************************************************************/
WORD32 KnxTm_GetCycleTimeMs(VOID);

/**************************************************************************
* FunctionName:WORD32 KnxTm_GetCycleCount(VOID)
* FunctionDescription:  获取循环周期次数。
* InputParameter None。
* OutputParameter None。
* Return Value： 循环次数（0~0xFFFF）
* Other Description: 需要在循环中调用KnxTm_UpdateCycle函数更新计数。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create
**************************************************************************/
WORD32 KnxTm_GetCycleCount(VOID);

/**************************************************************************
* FunctionName:VOID KnxTm_CallBack(T_SW_INT_EVENT *ptReason)
* FunctionDescription: 定时器回调函数。
* InputParameterNone。
* OutputParameterNone。
* Return Value：None。
* Other Description:
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                       Create 
**************************************************************************/
VOID KnxTm_CallBack(T_SW_INT_EVENT *ptReason);


#ifdef __cplusplus
}
#endif

#endif /* _KNX_TIMER_H_ */


/* end of file. */

