/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��common_driver.c
* FileIdentifier��None
* Abstract ���ṩ��������Ӧ����ڵĽӿڲ��ļ���Ϊ��Ҫͳһ������豸
            �����ṩͳһ�������ڡ�
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





#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "common_driver.h"
#include "mem_malloc.h"

/* Common device. */
static BYTE               g_ucComDevNum = 0;
static T_REGISTED_DEVICE *gt_CommonDev[SW_COMMON_DEV_MAX_NUM] = {NULL,NULL,NULL,NULL};

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
WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    BYTE   ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptDev=NULL;
    
    /* �����Ȳ����Ƕ����ָ������顣 */
    {
        ucIndex = ptPara->ucPara[1];
        if(ucIndex < SW_COMMON_DEV_MAX_NUM)
        {
            ptDev             = gt_CommonDev[ucIndex];
            ptPara->ucPara[1] = ptDev->ucDevNo;
            /* if(ptDev->ptDevOp->pfDrvCtrl) */
            {
                dwRes = ptDev->ptDevOp->pfDrvCtrl(ptPara);
            }
            ptPara->ucPara[1] = ucIndex;
        }
    }
    
    return dwRes;
}

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
WORD32 API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev)
{
    BYTE ucIndex;
    T_REGISTED_DEVICE *ptRegDevice = NULL;
    
    if((ptRegDev) && (g_ucComDevNum < SW_COMMON_DEV_MAX_NUM))
    {
        /* Ӧ���豸���߼������� */
        ucIndex = ptRegDev->ucLogDevNo;
        if(NULL==gt_CommonDev[ucIndex])
        {
            /* ���豸��û�б�ע�ᡣ */
            ptRegDevice = (T_REGISTED_DEVICE *)mem_malloc(sizeof(T_REGISTED_DEVICE));
            if(ptRegDevice)
            {
                ptRegDevice->ucAppType  = ptRegDev->ucAppType;
                ptRegDevice->ucDevId    = ptRegDev->ucDevId;
                ptRegDevice->ucLogDevNo = ptRegDev->ucLogDevNo;
                ptRegDevice->ucDevNo    = ptRegDev->ucDevNo;
                ptRegDevice->ptDevOp    = ptRegDev->ptDevOp;
                gt_CommonDev[ucIndex]   = ptRegDevice;
                g_ucComDevNum++;
                
                return SW_OK;
            }
        }
    }
    
    return SW_ERR;
}

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
WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
{
    WORD32 dwRes;
    BYTE ucIndex;
    T_REGISTED_DEVICE *ptRegDevice = NULL;
    
    /* if(ptInitPara) */
    {
        ucIndex = ptInitPara->ucPara[1];
        if(ucIndex < SW_COMMON_DEV_MAX_NUM)
        {
            ptRegDevice = gt_CommonDev[ucIndex];
            if(ptRegDevice)
            {
                /* ��ʼ��None��Σ�ͨ��Control�ӿڽ������á� */
                dwRes = ptRegDevice->ptDevOp->pfDrvInit(NULL);
                if(SW_ERR==dwRes)
                {
                    return dwRes;
                }
            }
        }
    }
    
    return dwRes;
}



/* End of common_driver.c */

