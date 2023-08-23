/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��ctrl_service.h
* FileIdentifier��None
* Abstract �����ļ�Ϊ���ƽӿڲ㹫��ͷ�ļ����塣
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

#ifndef _CTRL_SERVICE_H_
#define _CTRL_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


/***************TIMER define***********************/
#define SW_TIMER_MAX_NUM                    20       /* max. number of timer. */
/* working mode define. */
#define SW_TIMER_TM_MODE                    0        /* timer working mode.   */
#define SW_TIMER_COUNT_MODE                 1        /* counter working mode. */
#define SW_TIMER_PWM_MODE                   2        /* PWM working mode.     */
/* control the timer. */
#define SW_TIMER_STOP                       0        /* stop the timer.  */
#define SW_TIMER_START                      1        /* start the timer. */
#define SW_DISABLE_TIMER_INT                2        /* disable the interrupt of timer. */
#define SW_ENABLE_TIMER_INT                 3        /* enable the interrupt of timer.  */
/* time scale. */
#define SW_TIMER_MS                         0        /* timer is running in ms scale. */
#define SW_TIMER_US                         1        /* timer is running is us scale. */

/********************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA�ṹ����Timer��ʼ��/����ʱ�Ĳ������塣
* �����б�
           ������       ��������    ȡֵ��Χ                 ����   
  ------------------------------------------------------------------------------------------------------------------
  Input  pIntCallBackHandler                               �ص�������
  Input  ucPara[0]      BYTE      1-                       �豸ID��
  Input  ucPara[1]      BYTE      0-                       �����豸��
  Input  ucPara[2]      BYTE      0-4                      ����ģʽ
  Input                           SW_TIMER_TM_MODE
  Input                           SW_TIMER_COUNT_MODE
  Input                           SW_TIMER_PWM_MODE
  Input  ucPara[3]      BYTE      1-                       ��ʱ��ʱ�䳤��(ms/us)
  Input  ucPara[4]      BYTE      SW_TIMER_MS/SW_TIMER_US
 -------------------------------------------------------------------------------------------------
  Output no.
*******************************************************************************************************************/





/**********************����ԭ�Ͷ���******************************/

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription: ��ʱ���豸ע�ᡣ
* InputParameterT_REGISTED_DEVICE *ptRegDev�����ṹ���塣
* OutputParameterNone��
* Return Value��SW_OK   ��ע��ɹ���
            SW_ERROR��ע��ʧ�ܣ�
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData)
* ����˵������ʱ����������ȡ�ӿڡ�
* InputParameterucLogNo:device logical no.
            WORD32 *pdwData:pointer of return data.
* OutputParameterWORD32 *pdwData:timer data.
* Return Value��SW_OK    ��successfully.
            SW_ERROR ��failed.
* Other Description:��ȡ����ʱ���ļ��������ݡ�
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData)
* ����˵������ʱ������д�ӿڡ�
* InputParameterucLogNo:device logical no.
            WORD32 dwData:pointer of return data.
* OutputParameterNone
* Return Value: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* Other Description:д��ʱ���ļ�����ֵ��
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵������ʱ���豸���ƽӿڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara.
*              ucPara[0]      BYTE      SW_PERIPHERAL_TIMER      Timer type.  
*              ucPara[1]      BYTE      1                        timer logical number.
*              ucPara[2]      BYTE      control command.         timer control command.  
* OutputParameterdevice dependent.
* Return Value: SW_OK   ��successfully.
            SW_ERROR��failed.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵����ͨѶ���豸��ʼ���ӿڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->pIntCallBackHandler:callback function,if no,should set NULL.
                                    ->ucPara[0]:device ID
                                    ->ucPara[1]:logical device No.
                                    ->ucPara[2]:working mode.
                                                SW_TIMER_TM_MODE
                                                SW_TIMER_COUNT_MODE
                                                SW_TIMER_PWM_MODE
* OutputParameterno.
* Return Value: SW_OK   ��successfully.
            SW_ERROR��failed.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);

/********************** DMA�������� *************************************************/
#define SW_DMA_CHANNEL_RELEASE        (0)          /* �ͷ�DMAͨ��               */
#define SW_DMA_CHANNEL_ALLOC          (1)          /* ����DMAͨ��               */
#define SW_DMA_FUNC_START             (2)          /* DMA���ú�����             */
#define SW_DMA_PARA_SET               (3)          /* DMAͨ����������           */
    /* parameter bit0-bit1 define. */
    #define SW_DMA_TRANS_MEM2MEM      (0x01)       /* DMA�������ڴ�䴫��       */
    #define SW_DMA_TRANS_MEM2PRE      (0x02)       /* DMA�������ڴ浽����䴫�� */
    #define SW_DMA_TRANS_PRE2MEM      (0x03)       /* DMA���������贫���ڴ�     */
    /* parameter bit2-bit3 define. */
    #define SW_DMA_SINGLE             (0x04)       /* DMA���δ��� */
    #define SW_DMA_PINPON             (0x08)       /* DMAƹ�Ҵ��� */
    #define SW_DMA_CHAINED            (0x0c)       /* DMA�������� */
    /* parameter bit4 define. */
    #define SW_DMA_INTERRUPT_EN       (0x10)       /* DMA�ж�ʹ��               */
    #define SW_DMA_INTERRUPT_DIS      (0x00)       /* DMA�жϹر�               */



#ifdef __cplusplus
}
#endif

#endif /* _CTRL_SERVICE_H_ */




