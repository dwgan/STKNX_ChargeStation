/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��dma.h
* FileIdentifier��None
* Abstract �����ļ�ΪǶ��ʽϵͳ����������塣
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


#ifndef _COMMON_DRIVER_H_
#define _COMMON_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SW_COMMON_DEV_MAX_NUM      4

/**************************************************************************
* FunctionName:WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* FunctionDescription:  ͨ���豸���ơ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* Return Value�� SW_OK�� �ɹ�
             SW_ERR��ʧ��
* Other Description: 
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create 
**************************************************************************/
WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara);

/**************************************************************************
* FunctionName: void API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription:  ͨ����������豸ע����ڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* Return Value�� SW_ERR:ע��ʧ��
             SW_OK :ע��ɹ�
  Other Description: �����м���ע�ắ����SPIģ��ע�ᵽ�м�㡣
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
WORD32 API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* FunctionName: WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
* FunctionDescription:  ͨ��������ĳ�ʼ���ӿڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* Return Value�� SW_OK :��ʼ���ɹ�
             SW_ERR:��ʼ��ʧ��
 Other Description:  ���˼·�ϣ�Ҫ��ע����Դ���豸���ٵ��øýӿڡ�
             �ýӿ�ͨ�����ø����豸ע��Ľӿ��ٽ�����������
             ����ʼ����
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create
**************************************************************************/
WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);



#endif /* _COMMON_DRIVER_H_ */

/* End of common_driver.h */

