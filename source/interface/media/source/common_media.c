/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：common_media.c
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
#include "boardctrl.h"
#include "common_media.h"
#include "mem_malloc.h"


/* Common device. */
static BYTE               sg_ucMediaDevNum = 0;
static BYTE               sg_ucFlashWrtMode=SW_MEDIA_WORD;
static T_REGISTED_DEVICE *sg_ptMediaDev[SW_MEDIA_DEV_MAX_NUM] = {NULL,NULL};
static BYTE sg_aucPhy2LogNo[SW_MEDIA_DEV_RSV][SW_MEDIA_DEV_MAX_NUM];

#if(FLASH_PAGE_SIZE != 0)
    static BYTE    sg_aucFlashMem[FLASH_BUF_SIZE_ALIGNMENT(FLASH_PAGE_SIZE+MCU_SIZE)];
    static BYTE    *sg_aucFlashSectBuffer = NULL;
    static BYTE    *sg_pucSectBufferPtr   = NULL;
    static WORDPTR sg_dwFlashSectAddr     = 0;

/*****************************************************************************************************
* Function        : VOID API_Common_Media_Init(VOID)
* Description     : initialize common media.
* Input parameter : No.
* Output parameter: No.
* Return          : No.
* Other description:
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
VOID API_Common_Media_Init(VOID)
{
    sg_aucFlashSectBuffer = FLASH_BUF_ADDRESS_ALIGNMENT(sg_aucFlashMem);
    
    if(1 == FLASH_WRT_SIZE)
    {
        /* 1byte. */
        sg_ucFlashWrtMode = SW_MEDIA_BYTE;
    }
    else if(2 == FLASH_WRT_SIZE)
    {
        /* 2bytes. */
        sg_ucFlashWrtMode = SW_MEDIA_WORD;
    }
    else if(4 == FLASH_WRT_SIZE)
    {
        /* 4bytes. */
        sg_ucFlashWrtMode = SW_MEDIA_LWORD;
    }
    else if(8 == FLASH_WRT_SIZE)
    {
        /* 8bytes. */
        sg_ucFlashWrtMode = SW_MEDIA_LLWORD;
    }

    return;
}

#endif



/**************************************************************************
* FunctionName: WORD32 API_MediaDev_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription:  存储介质驱动层的设备注册入口。
* InputParameter T_REGISTED_DEVICE *ptRegDev:input device parameter.
                                    ->ucAppType:interface type
                                                   SW_SAVE_INTERFACE
                                    ->ucDevId  :device type 
                                                   SW_SVMWDIA_EEPROM
                                                   SW_SVMEDIA_FRAM
                                                   SW_SVMEDIA_FLASH
                                    ->ucLogDevNo:logical device No.
                                    ->ucDevNo   :physical device No.
                                    ->ptDevOp   :device operation handler.
                                    ->pfCallBack:device's call back handler.
* OutputParameter no.
* Return Value： SW_ERR:注册失败
             SW_OK :注册成功
  Other Description: 
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
WORD32 API_MediaDev_Reg(T_REGISTED_DEVICE *ptRegDev)
{
    BYTE   ucIndex;
    T_REGISTED_DEVICE *ptListDev = NULL;
    
    /* we check the validity of the input parameter. */
    if((ptRegDev) && (SW_MEDIA_DEV_MAX_NUM > sg_ucMediaDevNum))
    {
        if(SW_SAVE_INTERFACE != SW_SAVE_INTERFACE)
        {
            return SW_ERR;
        }
        ucIndex = ptRegDev->ucLogDevNo;
        /* arrange the device in ascending logical No. */
        if(sg_ptMediaDev[ucIndex] == NULL)
        {
            /* the device pointer is NULL.we can register the input device. */
            ptListDev = (T_REGISTED_DEVICE *)mem_malloc(sizeof(T_REGISTED_DEVICE));
            if(ptListDev)
            {
                /* copy the device parameter. */
                ptListDev->ucAppType  = ptRegDev->ucAppType;
                ptListDev->ucDevId    = ptRegDev->ucDevId;
                ptListDev->ucLogDevNo = ptRegDev->ucLogDevNo;
                ptListDev->ucDevNo    = ptRegDev->ucDevNo;
                ptListDev->ptDevOp    = ptRegDev->ptDevOp;
                ptListDev->pfCallBack = NULL;
                /* register the device into the device chain. */
                sg_ptMediaDev[ucIndex]= ptListDev;
                /* save the logical No. */
                sg_aucPhy2LogNo[ptRegDev->ucDevId][ptRegDev->ucDevNo] = ptRegDev->ucLogDevNo;
                /* the number of device adds 1. */
                sg_ucMediaDevNum++;
                
                return SW_OK;
            }
        }
    }
    
    return SW_ERR;
}

/**************************************************************************
* FunctionName:VOID API_ComMedia_CallBack(T_SW_INT_EVENT *ptIntEvt)
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
extern VOID API_ComMedia_CallBack(T_SW_INT_EVENT *ptIntEvt)
{
    BYTE ucLogicalNo;
    T_REGISTED_DEVICE *ptOperDev;
    
    ucLogicalNo       = sg_aucPhy2LogNo[ptIntEvt->ucDevId][ptIntEvt->ucDevNo];
    ptOperDev         = sg_ptMediaDev[ucLogicalNo];
    ptIntEvt->ucDevNo = ptOperDev->ucLogDevNo;              /* set the logical No. according to the physical No. */
    if(ptOperDev->pfCallBack)
    {
        ptOperDev->pfCallBack(ptIntEvt);
    }
    
    return;
}

/*********************************************************************************************
* FunctionName: WORD32 API_MediaDev_Init(BYTE ucDevType,BYTE ucLogNo,CALLBACK_HANDLER pfCallBack)
* FunctionDescription:  this function is called to initialize the given media device.
* InputParameter BYTE ucLogNo : media device's logical No.
* OutputParameter No.
* Return Value： SW_OK :successfully.
             SW_ERR:failed.
 Other Description:  
* Modified Date        版本号     修改人          Modified part
* --------------------------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create
**********************************************************************************************/
WORD32 API_MediaDev_Init(BYTE ucDevType,BYTE ucLogNo,CALLBACK_HANDLER pfCallBack)
{
    WORD32 dwRet = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    T_SW_DEVICEDRIVER_PARA tInitPara;
    
    if(ucLogNo >= sg_ucMediaDevNum)
    {
        return SW_ERR;
    }
    ptOperDev = sg_ptMediaDev[ucLogNo];
    if(ptOperDev)
    {
#if(FLASH_PAGE_SIZE != 0)
        if(ptOperDev->ucDevId == SW_PERIPHERAL_FLASH)
        {
            /* flash page address is empty. */
            sg_pucSectBufferPtr = NULL;
        }
#endif
        /* save the call back handler. */
        ptOperDev->pfCallBack = pfCallBack;
        /* copy device type ID. */
        tInitPara.ucPara[0] = ptOperDev->ucDevId;
        /* copy device physical No. */
        tInitPara.ucPara[1] = ptOperDev->ucDevNo;
        /* set common callback handler. */
        if(pfCallBack)
        {
            tInitPara.pIntCallBackHandler = API_ComMedia_CallBack; /* call back handler.     */
        }
        else
        {
            tInitPara.pIntCallBackHandler = NULL;
        }
        if(ptOperDev->ptDevOp->pfDrvInit)
        {
            dwRet = ptOperDev->ptDevOp->pfDrvInit(&tInitPara);     /* initialize the device. */
        }
    }
    
    return dwRet;
}

/**************************************************************************
* FunctionName:WORD32 API_Media_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
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
WORD32 API_Media_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    ucIndex = ptCtlPara->ucPara[1];
    if(ucIndex < SW_MEDIA_DEV_MAX_NUM)
    {
        ptOperDev            = sg_ptMediaDev[ucIndex];
        ptCtlPara->ucPara[0] = ptOperDev->ucDevId;
        ptCtlPara->ucPara[1] = ptOperDev->ucDevNo;     /* set the physical No. */
        if(ptOperDev->ptDevOp->pfDrvCtrl)
        {
            /* call the control handler. */
            dwRes = ptOperDev->ptDevOp->pfDrvCtrl(ptCtlPara);
        }
        /* resume the device logical No. into the input parameter. */
        ptCtlPara->ucPara[1] = ucIndex;
    }
    
    return dwRes;
}

/**************************************************************************
* FunctionName:WORD32 API_Media_Write(T_DATA_OPERARTION *ptDataOp)
* 功能说明：media interface for writing data into media.
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :device's logical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_ERASE
                                             SW_MEDIA_BYTE
                                             SW_MEDIA_WORD
                                             SW_MEDIA_LWORD
                                             SW_MEDIA_LLWORD
                               ->pucBuffer  :buffer for writing the data.
                               ->wDataLength:length of data in byte.
                               ->dwDestAddr : the destination address.
* OutputParameterNone
* Return Value: SW_OK   ：成功
            SW_ERROR：失败
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_Media_Write(T_DATA_OPERARTION *ptDataOp)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    ucIndex = ptDataOp->ucDevNo;                      /* save the logical No. */
    if(ucIndex < SW_MEDIA_DEV_MAX_NUM)
    {
        ptOperDev = sg_ptMediaDev[ucIndex];
        if(ptOperDev)
        {
            ptDataOp->ucDevNo = ptOperDev->ucDevNo;   /* we should set the physical No. here. */
            if(ptOperDev->ptDevOp->pfDrvWrite)
            {
                dwRes = ptOperDev->ptDevOp->pfDrvWrite(ptDataOp);
            }
            /* resume the logical No. */
            ptDataOp->ucDevNo = ucIndex;
        }
    }
    
    return dwRes;
}

/**************************************************************************
* FunctionName:WORD32 API_Media_Read(T_DATA_OPERARTION *ptDataOp)
* 功能说明：interface for reading media.
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :device's logical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_ERASE
                                             SW_MEDIA_BYTE
                                             SW_MEDIA_WORD
                                             SW_MEDIA_LWORD
                                             SW_MEDIA_LLWORD
                               ->pucBuffer  :buffer for writing the data.
                               ->dwDestAddr : the destination address.
* OutputParameterT_DATA_OPERARTION *ptDataOp
                               ->wDataLength:length of read data in byte..
* Return Value：SW_OK    ：成功
            SW_ERROR ：出错
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_Media_Read(T_DATA_OPERARTION *ptDataOp)
{
    BYTE ucIndex;
    WORD32 dwRes = SW_ERR;
    T_REGISTED_DEVICE *ptOperDev = NULL;
    
    ucIndex = ptDataOp->ucDevNo;                      /* device's logic No. */
    if(ucIndex < SW_MEDIA_DEV_MAX_NUM)
    {
        ptOperDev = sg_ptMediaDev[ucIndex];
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
    
    return dwRes;
}

#if(FLASH_PAGE_SIZE != 0)

/************************************************************************************
* function name   : WORD32 API_FlashMedia_Erase_Sector(BYTE ucDevNo,WORDPTR dwAddr)
* Description     : erase a sector of flash media.
* Input parameter : dwAddr : real address of the sector.
                    ucDevNo: logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for FLASH media.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 API_FlashMedia_Erase_Sector(BYTE ucDevNo,WORDPTR dwAddr)
{
    WORD32 dwRet;
    T_DATA_OPERARTION tReadData;

    tReadData.ucDevNo     = ucDevNo;
    tReadData.pucBuffer   = NULL;
    tReadData.dwDestAddr  = (dwAddr & (~(FLASH_PAGE_SIZE-1)));
    tReadData.ucOperMode  = SW_MEDIA_ERASE;
    tReadData.wDataLength = FLASH_PAGE_SIZE;
    dwRet = API_Media_Write(&tReadData);

    return dwRet;
}

/************************************************************************************
* function name   : WORD32 API_FlashMedia_Write_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE ucData)
* Description     : write a byte data to Flash buffer(not the practical media).
* Input parameter : dwAddr : real address of the destination.
                    ucData : written data.
                    ucDevNo: logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 API_FlashMedia_Write_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE ucData)
{
    WORD32 dwOffset,dwRet;
    T_DATA_OPERARTION tReadData;
    
    if(sg_pucSectBufferPtr == NULL)
    {
        /* buffer is in idle. */
        sg_dwFlashSectAddr  = dwAddr & (~(FLASH_PAGE_SIZE-1));
        sg_pucSectBufferPtr = sg_aucFlashSectBuffer;
        /* get the page data of flash. */
        tReadData.ucDevNo     = ucDevNo;
        tReadData.pucBuffer   = sg_pucSectBufferPtr;
        tReadData.dwDestAddr  = sg_dwFlashSectAddr;
        tReadData.ucOperMode  = SW_MEDIA_READ;
        tReadData.wDataLength = FLASH_PAGE_SIZE;
        API_Media_Read(&tReadData);
        /* write data to the buffer. */
        dwOffset = dwAddr - sg_dwFlashSectAddr;
        *(BYTE*)(sg_pucSectBufferPtr + dwOffset) = ucData;
    }
    else
    {
        /*buffer is in using.we should write the data into the flash first,then write the new data. */
        if(sg_dwFlashSectAddr != (dwAddr & (~(FLASH_PAGE_SIZE-1))))
        {
            /* first. we erase the page of flash which sg_dwFlashSectAddr pointing to. */
            tReadData.ucDevNo     = ucDevNo;
            tReadData.pucBuffer   = NULL;
            tReadData.dwDestAddr  = sg_dwFlashSectAddr;
            tReadData.ucOperMode  = SW_MEDIA_ERASE;
            tReadData.wDataLength = FLASH_PAGE_SIZE;
            dwRet = API_Media_Write(&tReadData);
            if(SW_ERR == dwRet)
            {
                return dwRet;
            }
            /* second. we write the buffer's data into flash page pointed by sg_dwFlashSectAddr. */
            tReadData.pucBuffer   = sg_pucSectBufferPtr;
            tReadData.dwDestAddr  = sg_dwFlashSectAddr;
            tReadData.ucOperMode  = sg_ucFlashWrtMode;
            tReadData.wDataLength = FLASH_PAGE_SIZE;
            dwRet =API_Media_Write(&tReadData);
            if(SW_ERR == dwRet)
            {
                return dwRet;
            }
            /* third. we renew the login of flash page address. */
            sg_dwFlashSectAddr = dwAddr & (~(FLASH_PAGE_SIZE-1));
            /* fouth. we read the destination page data into flash buffer. */
            tReadData.dwDestAddr  = sg_dwFlashSectAddr;
            tReadData.ucOperMode  = SW_MEDIA_READ;
            tReadData.wDataLength = FLASH_PAGE_SIZE;
            API_Media_Read(&tReadData);
            /* write data to the buffer. */
            dwOffset = dwAddr - sg_dwFlashSectAddr;
            *(BYTE*)(sg_pucSectBufferPtr + dwOffset) = ucData;
        }
        else
        {
            /* we write the data directly into the buffer. */
            dwOffset = dwAddr - sg_dwFlashSectAddr;
            *(BYTE*)(sg_pucSectBufferPtr + dwOffset) = ucData;
        }
    }

    return SW_OK;
}

/**********************************************************************************************************
* function name   : WORD32 API_FlashMedia_WriteData(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucData,WORD16 wCunt)
* Description     : write wCunt bytes to Flash buffer(not the practical media).
* Input parameter : dwAddr   : real address of the destination.
                    *pucData : written data.
                    ucDevNo  : logical device no.
                    wCunt    : byte's counts.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************************/
WORD32 API_FlashMedia_WriteData(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucData,WORD16 wCunt)
{
    WORD16 wIndex;
    WORD32 dwRet;

    for(wIndex=0;wIndex<wCunt;wIndex++)
    {
        dwRet = API_FlashMedia_Write_BYTE(ucDevNo,dwAddr+wIndex,*(BYTE*)(pucData+wIndex));
        if(SW_ERR==dwRet)
        {
            return SW_ERR;
        }
    }

    return SW_OK;
}

/***********************************************************************************************
* function name   : WORD32 API_FlashMedia_Read_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucBuffer)
* Description     : read a byte data from Flash.
* Input parameter : dwAddr    : real address of the destination.
                    pucBuffer : data buffer pointer for saving.
                    ucDevNo   : logical device no.
* Output parameter: *pucBuffer: output data.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for reading byte data of FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************/
WORD32 API_FlashMedia_Read_BYTE(BYTE ucDevNo,WORDPTR dwAddr,BYTE *pucBuffer)
{
    WORD32 dwOffset;
    
    if(sg_pucSectBufferPtr)
    {
        /* we should return the data of the flash buffer. */
        if(sg_dwFlashSectAddr == (dwAddr & (~(FLASH_PAGE_SIZE-1))))
        {
            /* return the data of the buffer. */
            dwOffset   = dwAddr - sg_dwFlashSectAddr;
            *pucBuffer = *(BYTE*)(sg_pucSectBufferPtr + dwOffset);
            
            return SW_OK;
        }
    }
    /* return  the data directly. */
    *pucBuffer = *(BYTE*)dwAddr;

    return SW_OK;
}

/***********************************************************************************************
* function name   : WORD32 API_FlashMedia_DataFlush(BYTE ucDevNo)
* Description     : flush the data in buffer to the flash media.
* Input parameter : ucDevNo   : logical device no.
* Output parameter: no.
* Return          : SW_OK/SW_ERR.
* Other description:
    This function used for writing buffered byte data to FLASH media.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************/
WORD32 API_FlashMedia_DataFlush(BYTE ucDevNo)
{
    WORD32 dwRet;
    T_DATA_OPERARTION tReadData;
    
    if(sg_pucSectBufferPtr)
    {
        /* first. we erase the page of flash which sg_dwFlashSectAddr pointing to. */
        tReadData.ucDevNo     = ucDevNo;
        tReadData.pucBuffer   = NULL;
        tReadData.dwDestAddr  = sg_dwFlashSectAddr;
        tReadData.ucOperMode  = SW_MEDIA_ERASE;
        tReadData.wDataLength = FLASH_PAGE_SIZE;
        dwRet = API_Media_Write(&tReadData);
        if(SW_ERR == dwRet)
        {
            return dwRet;
        }
        /* second. we write the buffer's data into flash page pointed by sg_dwFlashSectAddr. */
        tReadData.pucBuffer   = sg_pucSectBufferPtr;
        tReadData.dwDestAddr  = sg_dwFlashSectAddr;
        tReadData.ucOperMode  = sg_ucFlashWrtMode;
        tReadData.wDataLength = FLASH_PAGE_SIZE;
        dwRet =API_Media_Write(&tReadData);
        if(SW_ERR == dwRet)
        {
            return dwRet;
        }
        /* clear the recorder of flash sector page address. */
        sg_pucSectBufferPtr = NULL;
    }

    return SW_OK;
}
#endif

/* End of common_driver.c */

