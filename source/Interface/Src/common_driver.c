/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：common_driver.c
* FileIdentifier：None
* Abstract ：提供公共驱动应用入口的接口层文件，为需要统一管理的设备
            驱动提供统一管理的入口。
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
#include "common_driver.h"
#include "mem_malloc.h"

/* Common device. */
static BYTE               g_ucComDevNum = 0;
static T_REGISTED_DEVICE *gt_CommonDev[SW_COMMON_DEV_MAX_NUM] = {NULL,NULL,NULL,NULL};

/**************************************************************************
* FunctionName:WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* FunctionDescription:  通用设备控制。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value： SW_OK： 成功
             SW_ERR：失败
* Other Description: 
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create 
**************************************************************************/
WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    BYTE   ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptDev=NULL;
    
    /* 我们先不考虑对入参指针做检查。 */
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
* FunctionDescription:  通用驱动层的设备注册入口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value： SW_ERR:注册失败
             SW_OK :注册成功
  Other Description: 调用中间层的注册函数将SPI模块注册到中间层。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
WORD32 API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev)
{
    BYTE ucIndex;
    T_REGISTED_DEVICE *ptRegDevice = NULL;
    
    if((ptRegDev) && (g_ucComDevNum < SW_COMMON_DEV_MAX_NUM))
    {
        /* 应用设备以逻辑号排序。 */
        ucIndex = ptRegDev->ucLogDevNo;
        if(NULL==gt_CommonDev[ucIndex])
        {
            /* 该设备还没有被注册。 */
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
* FunctionDescription:  通用驱动层的初始化接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value： SW_OK :初始化成功
             SW_ERR:初始化失败
 Other Description:  设计思路上，要先注册资源、设备后，再调用该接口。
             该接口通过调用各个设备注册的接口再将各个驱动设
             备初始化。
* Modified Date        版本号     修改人          Modified part
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
                /* 初始化None入参，通过Control接口进行设置。 */
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

