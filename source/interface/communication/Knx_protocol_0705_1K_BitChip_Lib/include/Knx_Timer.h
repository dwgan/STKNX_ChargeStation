/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��Knx_timer.h
* FileIdentifier��None
* Abstract ��KNX timer handle header file.
* Other Description��
* Current Version��V1.00
* Author��      
* Completed Date��2013��7��24��
*    
* Modified History1��
*        Modified Date��2013��7��24��
*        Version Number��V1.00
*        Modified Person��      
*        Modified part��Add new public definition.
******************************************************************************/

#ifndef _KNX_TIMER_H_
#define _KNX_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif



#define KNX_TIMER_SACLE             1           /* timing scale:1Ms. */



/**************************************************************************
* FunctionName:VOID KnxTm_TimerInit(BYTE ucDevNo)
* FunctionDescription: KNX��ʱ����ʼ���ӿڣ���ʱ��1ms��
* InputParameterBYTE ucDevNo:device logical number.
* OutputParameterno.
* Return Value��no.
* Other Description:ͨ��api�ṩ���ⲿʹ�á���ʱ������ͨ��ע�᷽ʽע�ᵽKNX��ʱ������
            ���й�����
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      Create 
**************************************************************************/
VOID KnxTm_TimerInit(BYTE ucDevNo);

/**************************************************************************
* FunctionName:WORD32 KnxTm_GetTimeMs(VOID)
* FunctionDescription: ��ȡ��ǰ��ʱ��������
* InputParameter None��
* OutputParameter None��
* Return Value�� ��ǰ��������0-0xFFFFFFFF��
* Other Description: None
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      Create 
**************************************************************************/
WORD32 KnxTm_GetTimeMs(VOID);

/**************************************************************************
* FunctionName:WORD32 KnxTm_GetDelayMs(WORD32 dwOldTime)
* FunctionDescription: ��ȡ����ʱ�����ǰʱ���ʱ����룩��
* InputParameter WORD16 wOldTime��������ʱ�䡣
* OutputParameter None��
* Return Value�� ʱ����룺0-0xFFFF��
* Other Description: None
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create 
**************************************************************************/
WORD32 KnxTm_GetDelayMs(WORD32 dwOldTime);

/**************************************************************************
* FunctionName:VOID KnxTm_UpdateCycle(VOID)
* FunctionDescription:  ��������ʱ��ͼ�����
* InputParameter None��
* OutputParameter None��
* Return Value�� None��
* Other Description: None��
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create
**************************************************************************/
VOID KnxTm_UpdateCycle(VOID);

/**************************************************************************
* FunctionName:WORD16 KnxTm_GetCycleTimeMs(VOID)
* FunctionDescription:  ��ȡѭ������ʱ�䣨���룩��
* InputParameter None��
* OutputParameter None��
* Return Value�� ʱ��ֵ�����룬0~0xFFFF��
* Other Description: ��Ҫ��ѭ���е���KnxTm_UpdateCycle��������ʱ�䡣
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create
**************************************************************************/
WORD32 KnxTm_GetCycleTimeMs(VOID);

/**************************************************************************
* FunctionName:WORD32 KnxTm_GetCycleCount(VOID)
* FunctionDescription:  ��ȡѭ�����ڴ�����
* InputParameter None��
* OutputParameter None��
* Return Value�� ѭ��������0~0xFFFF��
* Other Description: ��Ҫ��ѭ���е���KnxTm_UpdateCycle�������¼�����
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create
**************************************************************************/
WORD32 KnxTm_GetCycleCount(VOID);

/**************************************************************************
* FunctionName:VOID KnxTm_CallBack(T_SW_INT_EVENT *ptReason)
* FunctionDescription: ��ʱ���ص�������
* InputParameterNone��
* OutputParameterNone��
* Return Value��None��
* Other Description:
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                       Create 
**************************************************************************/
VOID KnxTm_CallBack(T_SW_INT_EVENT *ptReason);


#ifdef __cplusplus
}
#endif

#endif /* _KNX_TIMER_H_ */


/* end of file. */

