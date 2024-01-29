/************************************************************************************************************
* Right reserved (C 2016) for Shufan information technology company.
*
* File Name        : math_service.c
*
* File Description : math interface layer source file.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2014.5.28
*
* Modification Rec.:
*   Modify Data    : 2014.5.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
* Modification Rec.:
*   Modify Data    : 2020.11.25
*   Operator       :
*   Version        : 1.10
*   Action         : change api for stm32g0xxx.
**********************************************************************************************************/




#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "math_service.h"
#include "mem_malloc.h"






/* AD/DC control define */
static BYTE              sg_ucMathDevNum                  = 0;
static T_REGISTED_DEVICE *sg_ptMathDev[SW_MATH_MAX_NUM]   = {NULL,NULL};     /* device table.  */
static BYTE              sg_aucPhy2LogNo[SW_MATH_MAX_NUM] = {0,0};           /* logical device No. indexed by the physical device No. */
static BYTE              *sg_pAdChnlMap[SW_MATH_MAX_NUM]  = {NULL,NULL};     /* relation map from locial channel No. to the physical channel No. locial channel No. is the index. */



/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* Descrip.: register AD devices into math interface layer.
* Input   : T_REGISTED_DEVICE *ptRegDev : defined in sw_common.h
* Output  : no.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
{
    BYTE   ucIndex;
    T_REGISTED_DEVICE *ptListDev = NULL;
    
    /* we check the validity of the input parameter. */
    if((ptRegDev) && (SW_MATH_MAX_NUM > sg_ucMathDevNum))
    {
        ucIndex = ptRegDev->ucLogDevNo;
        /* index is device logical number. */
        if(sg_ptMathDev[ucIndex] == NULL)
        {
            /* it is empty, we can register it. */
            ptListDev = (T_REGISTED_DEVICE *)mem_malloc(sizeof(T_REGISTED_DEVICE));
            if(ptListDev)
            {
                ptListDev->ucAppType  = ptRegDev->ucAppType;
                ptListDev->ucDevId    = ptRegDev->ucDevId;
                ptListDev->ucLogDevNo = ptRegDev->ucLogDevNo;
                ptListDev->ucDevNo    = ptRegDev->ucDevNo;
                ptListDev->ptDevOp    = ptRegDev->ptDevOp;
                ptListDev->pfCallBack = NULL;
                sg_ptMathDev[ucIndex] = ptListDev;
                /* save the device. */
                sg_aucPhy2LogNo[ptRegDev->ucDevNo] = ptRegDev->ucLogDevNo;
                sg_ucMathDevNum++;
                
                return SW_OK;
            }
        }
    }
    
    return SW_ERR;
}

/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Read(BYTE ucLogNo,BYTE ucLogChnlNo,WORD16 *pwData)
* Descrip.: it is used to read data of a channel of an AD.
* Input   : BYTE   ucLogNo    : logical device No.
*           BYTE   ucLogChnlNo: logical channel No.
*           WORD16 *pwData    : pointer of return data(word length).
* Output  : WORD16 *pwData    : return data.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Read(BYTE ucLogNo,BYTE ucLogChnlNo,WORD16 *pwData)
{
    WORD32            dwRes;
    BYTE              ucPhyChnlNo,aucData[2]                                        /* [0]:low byte,[1]:high byte. */;
    T_DATA_OPERARTION tDataOp;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    dwRes = SW_ERR;
    if(ucLogNo < SW_MATH_MAX_NUM)
    {
        /* transmit logical channel No. */
        if(sg_pAdChnlMap[ucLogNo] != NULL)
        {
            ucPhyChnlNo = sg_pAdChnlMap[ucLogNo][ucLogChnlNo];
        }
        else
        {
            /* default. */
            ucPhyChnlNo = ucLogChnlNo;
        }
        ptOperDev = sg_ptMathDev[ucLogNo];
        if(ptOperDev)
        {
            tDataOp.ucDevNo     = ptOperDev->ucDevNo;   /* device's physical No. */
            tDataOp.ucOperMode  = ucPhyChnlNo;          /* physical channel No.  */
            tDataOp.pucBuffer   = aucData;              /* return data pointer.  */
            if(ptOperDev->ptDevOp->pfDrvRead)
            {
                dwRes = ptOperDev->ptDevOp->pfDrvRead(&tDataOp);
            }
            if(SW_OK == dwRes)
            {
                /* [0]:data low byte,[1]:data high byte. */
                *pwData = ((WORD16)aucData[1]<<8) + aucData[0];
            }
            else
            {
                *pwData = 0;
            }
        }
    }
    
    return dwRes;
}

/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* Descrip.: it is used to control AD, such as start, stop, configure AD.
* Input   : T_SW_DEVICEDRIVER_PARA *ptCtlPara
*              ucPara[0]      BYTE      SW_PERIPHERAL_AD         device type.  
*              ucPara[1]      BYTE      0...                     Device logical number.
*              ucPara[2]      BYTE      0...                     Channel logical number.
*              ucPara[3]      BYTE      control command.         adc control command.
*                                          SW_ADC_SOFT_STOP
*                                          SW_ADC_SOFT_START
*                                          SW_ADC_CONFIGURE
*              ucPara[4]      BYTE      command parameter.
* Output  : T_SW_DEVICEDRIVER_PARA *ptCtlPara.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
{
    BYTE              ucPhyChnlNo,ucLogNo,ucLogChnlNo;
    WORD32            dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    /* if(ptCtlPara) */
    {
        ucLogNo     = ptCtlPara->ucPara[1];
        ucLogChnlNo = ptCtlPara->ucPara[2];
        if(ucLogNo < SW_MATH_MAX_NUM)
        {
            /* transmit logical channel No. */
            if(sg_pAdChnlMap[ucLogNo] != NULL)
            {
                ucPhyChnlNo = sg_pAdChnlMap[ucLogNo][ucLogChnlNo];
            }
            else
            {
                /* default. */
                ucPhyChnlNo = ucLogChnlNo;
            }
            /* set operation parameter. */
            ptOperDev            = sg_ptMathDev[ucLogNo];
            ptCtlPara->ucPara[1] = ptOperDev->ucDevNo;        /* change to physical device number.  */
            ptCtlPara->ucPara[2] = ucPhyChnlNo;               /* change to physical channel number. */
            if(ptOperDev->ptDevOp->pfDrvCtrl)
            {
                dwRes = ptOperDev->ptDevOp->pfDrvCtrl(ptCtlPara);
            }
            /* restore the initial parameters. */
            ptCtlPara->ucPara[1] = ucLogNo;
            ptCtlPara->ucPara[2] = ucLogChnlNo;
        }
    }
    
    return dwRes;
}

/*****************************************************************************************************************
* Funciton: VOID API_MathDrv_CallBack(T_SW_INT_EVENT *ptIntEvt)
* Descrip.: it is callback handler for device's interrupt.
* Input   : ptIntEvt->ucAppType : application type.
*                     ucDevId   : device type.
*                     ucDevNo   : physical No. of the device.
*                     ucEvent   : event type.
*                     ucBuffer  : parameter buffer(this pointer should be transmit to WORD16 pointer in application).
* Output  : T_SW_INT_EVENT *ptIntEvt.
*                     ucDevId   : device type.
*                     ucDevNo   : logical No. of the device.
*                     ucEvent   : event type.
*                     ucBuffer  : parameter buffer(this pointer should be transmit to WORD16 pointer in application).
*                                 for AD, ptIntEvt->ucBuffer[0] is device logical channel No.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
VOID API_MathDrv_CallBack(T_SW_INT_EVENT *ptIntEvt)
{
    BYTE              ucLogicalNo,ucIndex;
    T_REGISTED_DEVICE *ptOperDev;
    
    ucLogicalNo       = sg_aucPhy2LogNo[ptIntEvt->ucDevNo];
    ptOperDev         = sg_ptMathDev[ucLogicalNo];
    ptIntEvt->ucDevNo = ptOperDev->ucLogDevNo;              /* set the logical No. according to the physical No. */
    for(ucIndex=0;ucIndex < SW_MATH_MAX_CHNL_NUM;ucIndex++)
    {
        if(sg_pAdChnlMap[ucLogicalNo])
        {
            if(sg_pAdChnlMap[ucLogicalNo][ucIndex] == ptIntEvt->ucBuffer[0])
            {
                /* change it to logical channel No. */
                ptIntEvt->ucBuffer[0] = ucIndex;
                break;
            }
        }
    }
    if(ptOperDev->pfCallBack)
    {
        ptOperDev->pfCallBack(ptIntEvt);
    }
    
    return;
}

/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
* Descrip.: it is used to initialize AD.
* Input   : T_SW_DEVICEDRIVER_PARA *ptCtlPara
*              ucPara[0]      BYTE      SW_PERIPHERAL_AD         device type.  
*              ucPara[1]      BYTE      0...                     Device logical number.
*              ucPara[2]      BYTE      0...                     Channel logical number.
*              ucPara[3]      BYTE      control command.         adc control command.
*                                          SW_ADC_CONFIGURE
*              ucPara[4]      BYTE      command parameter.
* Output  : T_SW_DEVICEDRIVER_PARA *ptCtlPara.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;

    if(ptInitPara->ucPara[1] >= SW_MATH_MAX_NUM)
    {
        return dwRes;
    }
    /* get logical device No. */
    ucIndex = ptInitPara->ucPara[1];
    /* save channel map table. */
    sg_pAdChnlMap[ucIndex] = ptInitPara->pucBuf;
    if(ucIndex < SW_MATH_MAX_NUM)
    {
        /* get the registered device. */
        ptOperDev             = sg_ptMathDev[ucIndex];
        /* hang the call back handler to the registered device. */
        ptOperDev->pfCallBack = ptInitPara->pIntCallBackHandler;
        /* change the input logical No to the device's physical No. */
        ptInitPara->ucPara[1] = ptOperDev->ucDevNo;
        if(ptInitPara->pIntCallBackHandler)
        {
            /* if there is a callback handler,we hang the common callback handler to the device driver. */
            ptInitPara->pIntCallBackHandler = API_MathDrv_CallBack;
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


/* End-of-file */


