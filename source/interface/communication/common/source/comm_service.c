/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：comm_service.c
* FileIdentifier：None
* Abstract ：通讯接口层源文件。
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
#include "comm_service.h"
#include "mem_malloc.h"


static BYTE               sg_ucMaxDevNum = 0;
static T_REGISTED_DEVICE  *sg_ptComDev[SW_COM_DEV_MAX_NUM] = {NULL,NULL,NULL,NULL};           /* 接口层设备表 */
static BYTE sg_aucPhy2LogNo[SW_COMM_DEV_RSV][SW_MAX_SUB_COM_DEV_NUM];                              /* 以设备物理号为索引，映射设备的逻辑号。 */


/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription: 向通讯层注册设备。
* InputParameterT_REGISTED_DEVICE *ptRegDev：见结构定义。
* OutputParameterNone。
* Return Value：SW_OK   ：注册成功；
            SW_ERROR：注册失败；
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
        /* 设备按照逻辑号排序 */
        if(sg_ptComDev[ucIndex] == NULL)
        {
            /* 该逻辑号设备还没注册 */
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
* 功能说明：通讯层接收数据接口。
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo  :逻辑设备号
                               ->pucBuffer:存放数据的缓冲区地址
* OutputParameterT_DATA_OPERARTION *ptDataOp
                               ->wDataLength:返回的读取到的数据长度，为0表示None数据。
* Return Value：SW_OK    ：成功
            SW_ERROR ：出错
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
    
    /* if(ptDataOp) */   /* 我们暂不考虑该保护 */
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
* 功能说明：通讯层发送数据接口。
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :逻辑设备号
                               ->pucBuffer  :存放数据的缓冲区地址
                               ->wDataLength:待发送字节个数
* OutputParameterNone
* Return Value: SW_OK   ：成功
            SW_ERROR：失败
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
    
    /* if(ptDataOp) */   /* 我们暂不考虑该保护 */
    {
        ucIndex = ptDataOp->ucDevNo;                      /* 保存逻辑设备号 */
        if(ucIndex < SW_COM_DEV_MAX_NUM)
        {
            ptOperDev = sg_ptComDev[ucIndex];
            if(ptOperDev)
            {
                ptDataOp->ucDevNo = ptOperDev->ucDevNo;   /* 逻辑设备号改成物理设备号 */
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
* 功能说明：通讯层设备控制接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value: SW_OK   ：成功
            SW_ERROR：失败
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
            ptCtlPara->ucPara[1] = ptOperDev->ucDevNo;                /* 设备号改成物理设备号 */
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
* 功能说明：设备的应用回调入口。
* InputParameterptIntEvt->ucAppType : application type.
                      ucDevId   : device type.
                      ucDevNo   : physical No. of the device.
                      ucEvent   : event type.
                      ucBuffer  : parameter buffer.
* OutputParameter
* Return Value: SW_OK   ：成功
            SW_ERROR：失败
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
* 功能说明：通讯层设备初始化接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->pIntCallBackHandler:callback function,if no,should set NULL.
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value: SW_OK   ：成功
            SW_ERROR：失败
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
