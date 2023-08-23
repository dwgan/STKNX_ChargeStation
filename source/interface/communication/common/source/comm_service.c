/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��comm_service.c
* FileIdentifier��None
* Abstract ��ͨѶ�ӿڲ�Դ�ļ���
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
#include "comm_service.h"
#include "mem_malloc.h"


static BYTE               sg_ucMaxDevNum = 0;
static T_REGISTED_DEVICE  *sg_ptComDev[SW_COM_DEV_MAX_NUM] = {NULL,NULL,NULL,NULL};           /* �ӿڲ��豸�� */
static BYTE sg_aucPhy2LogNo[SW_COMM_DEV_RSV][SW_MAX_SUB_COM_DEV_NUM];                              /* ���豸�����Ϊ������ӳ���豸���߼��š� */


/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription: ��ͨѶ��ע���豸��
* InputParameterT_REGISTED_DEVICE *ptRegDev�����ṹ���塣
* OutputParameterNone��
* Return Value��SW_OK   ��ע��ɹ���
            SW_ERROR��ע��ʧ�ܣ�
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
{
    BYTE   ucIndex;
    T_REGISTED_DEVICE *ptListDev = NULL;
    
    /* we check the validity of the input parameter. */
    if((ptRegDev) && (SW_COM_DEV_MAX_NUM > sg_ucMaxDevNum))
    {
        ucIndex = ptRegDev->ucLogDevNo;
        /* �豸�����߼������� */
        if(sg_ptComDev[ucIndex] == NULL)
        {
            /* ���߼����豸��ûע�� */
            ptListDev = (T_REGISTED_DEVICE *)mem_malloc(sizeof(T_REGISTED_DEVICE));
            if(ptListDev)
            {
                ptListDev->ucAppType  = ptRegDev->ucAppType;
                ptListDev->ucDevId    = ptRegDev->ucDevId;
                ptListDev->ucLogDevNo = ptRegDev->ucLogDevNo;
                ptListDev->ucDevNo    = ptRegDev->ucDevNo;
                ptListDev->ptDevOp    = ptRegDev->ptDevOp;
                ptListDev->pfCallBack = NULL;
                sg_ptComDev[ucIndex]  = ptListDev;
                /* save the device. */
                sg_aucPhy2LogNo[ptRegDev->ucDevId][ptRegDev->ucDevNo] = ptRegDev->ucLogDevNo;
                sg_ucMaxDevNum++;
                
                return SW_OK;
            }
        }
    }
    
    return SW_ERR;
}

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Read(T_DATA_OPERARTION *ptDataOp)
* ����˵����ͨѶ��������ݽӿڡ�
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo  :�߼��豸��
                               ->pucBuffer:������ݵĻ�������ַ
* OutputParameterT_DATA_OPERARTION *ptDataOp
                               ->wDataLength:���صĶ�ȡ�������ݳ��ȣ�Ϊ0��ʾNone���ݡ�
* Return Value��SW_OK    ���ɹ�
            SW_ERROR ������
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Read(T_DATA_OPERARTION *ptDataOp)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    /* if(ptDataOp) */   /* �����ݲ����Ǹñ��� */
    {
        ucIndex = ptDataOp->ucDevNo;                      /* device's logic No. */
        if(ucIndex < SW_COM_DEV_MAX_NUM)
        {
            ptOperDev = sg_ptComDev[ucIndex];
            if(ptOperDev)
            {
                ptDataOp->ucDevNo = ptOperDev->ucDevNo;   /* we change device's logic No. to device's physical No. */
                if(ptOperDev->ptDevOp->pfDrvRead)
                {
                    dwRes = ptOperDev->ptDevOp->pfDrvRead(ptDataOp);
                }
                ptDataOp->ucDevNo = ucIndex;
            }
        }
    }
    
    return dwRes;
}

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Write(T_DATA_OPERARTION *ptDataOp)
* ����˵����ͨѶ�㷢�����ݽӿڡ�
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :�߼��豸��
                               ->pucBuffer  :������ݵĻ�������ַ
                               ->wDataLength:�������ֽڸ���
* OutputParameterNone
* Return Value: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Write(T_DATA_OPERARTION *ptDataOp)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    /* if(ptDataOp) */   /* �����ݲ����Ǹñ��� */
    {
        ucIndex = ptDataOp->ucDevNo;                      /* �����߼��豸�� */
        if(ucIndex < SW_COM_DEV_MAX_NUM)
        {
            ptOperDev = sg_ptComDev[ucIndex];
            if(ptOperDev)
            {
                ptDataOp->ucDevNo = ptOperDev->ucDevNo;   /* �߼��豸�Ÿĳ������豸�� */
                if(ptOperDev->ptDevOp->pfDrvWrite)
                {
                    dwRes = ptOperDev->ptDevOp->pfDrvWrite(ptDataOp);
                }
                ptDataOp->ucDevNo = ucIndex;
            }
        }
    }
    
    return dwRes;
}

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵����ͨѶ���豸���ƽӿڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* Return Value: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    /* if(ptCtlPara) */
    {
        ucIndex = ptCtlPara->ucPara[1];
        if(ucIndex < SW_COM_DEV_MAX_NUM)
        {
            ptOperDev            = sg_ptComDev[ucIndex];
            ptCtlPara->ucPara[0] = ptOperDev->ucDevId;
            ptCtlPara->ucPara[1] = ptOperDev->ucDevNo;                /* �豸�Ÿĳ������豸�� */
            if(ptOperDev->ptDevOp->pfDrvCtrl)
            {
                dwRes = ptOperDev->ptDevOp->pfDrvCtrl(ptCtlPara);
            }
            ptCtlPara->ucPara[1] = ucIndex;
        }
    }
    
    return dwRes;
}

/**************************************************************************
* FunctionName:VOID API_ComDrv_CallBack(T_SW_INT_EVENT *ptIntEvt)
* ����˵�����豸��Ӧ�ûص���ڡ�
* InputParameterptIntEvt->ucAppType : application type.
                      ucDevId   : device type.
                      ucDevNo   : physical No. of the device.
                      ucEvent   : event type.
                      ucBuffer  : parameter buffer.
* OutputParameter
* Return Value: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern VOID API_ComDrv_CallBack(T_SW_INT_EVENT *ptIntEvt)
{
    BYTE ucLogicalNo;
    T_REGISTED_DEVICE *ptOperDev;
    
    ucLogicalNo       = sg_aucPhy2LogNo[ptIntEvt->ucDevId][ptIntEvt->ucDevNo];
    ptOperDev         = sg_ptComDev[ucLogicalNo];
    ptIntEvt->ucDevNo = ptOperDev->ucLogDevNo;              /* set the logical No. according to the physical No. */
    if(ptOperDev->pfCallBack)
    {
        ptOperDev->pfCallBack(ptIntEvt);
    }
    
    return;
}

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Init(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵����ͨѶ���豸��ʼ���ӿڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->pIntCallBackHandler:callback function,if no,should set NULL.
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* Return Value: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    ucIndex = ptInitPara->ucPara[1];
    if(ucIndex < SW_COM_DEV_MAX_NUM)
    {
        /* get the registered device. */
        ptOperDev             = sg_ptComDev[ucIndex];
        /* hang the call back handler to the registered device. */
        ptOperDev->pfCallBack = ptInitPara->pIntCallBackHandler;
        /* change the input logical No to the device's physical No. */
        ptInitPara->ucPara[1] = ptOperDev->ucDevNo;
        if(ptInitPara->pIntCallBackHandler)
        {
            /* if there is a callback handler,we hang the common callback handler to the device driver. */
            ptInitPara->pIntCallBackHandler = API_ComDrv_CallBack;
        }
        /* call the device's initialize handler. */
        if(ptOperDev->ptDevOp->pfDrvInit)
        {
            dwRes = ptOperDev->ptDevOp->pfDrvInit(ptInitPara);
        }
        /* recover the logical No. and callback handler. */
        ptInitPara->ucPara[1] = ucIndex;
        ptInitPara->pIntCallBackHandler = ptOperDev->pfCallBack;
    }
    
    return dwRes;
}



/** End-of-file */
