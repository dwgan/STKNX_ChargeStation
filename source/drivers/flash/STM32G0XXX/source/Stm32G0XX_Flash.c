/*****************************************************************************************
* (C) Copyright 2016 Nanjing shufan information technology company limited.
*
* File Name        : Stm32G0XX_Flash.c
*
* File Description : driver for stm32g0xx cpu's flash.
*
* Other Description: This driver only support erase page/write data into the normal
                     flash memory.do not support the operation in flash option area.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2016.7.28
*
* Modification Rec.:
*   Modify Data    : 2016.7.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
*****************************************************************************************/




#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "boardcfg.h"
#include "Hardware.h"


#include "Stm32G0XX_Flash.h"
#include "BoardCtrl.h"
#include "common_media.h"


/* function type. */
WORD32 Stm32G0xxx_Flash_Write(T_DATA_OPERARTION *ptPara);
static WORD32 Stm32G0xxx_Flash_Init(T_SW_DEVICEDRIVER_PARA *ptPara);

static T_FLASH_TMOPER sg_tFlashTmOp;
/* the global flash operation structure. */
static T_DEV_OPERATION sg_tStm32F10xxFlashOp;

/**************************************************************************
* function name   : static VOID Stm32G0xxx_Flash_Unlock(VOID)
* Description     : Unlock the flash.
* Input parameter : no.
* Output parameter: no.
* Return          : no.
* Other description:
     Before writing the flash,we should unlock the flash.the flash is locked
     after cpu resetting.
* Modify date     Ver.     Modifier      Action
* ------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
**************************************************************************/
#if(defined(IAR))
__ramfunc static VOID Stm32G0xxx_Flash_Unlock(VOID)
#elif(defined(KEIL))
__attribute__((section("KNX_RAMFUNC"))) static VOID Stm32G0xxx_Flash_Unlock(VOID)
#endif
{
    FTFA_KEY = FLASH_KEY1;
    FTFA_KEY = FLASH_KEY2;
    
    return;
}

/************************************************************************************
* function name   : static VOID Stm32G0xxx_Flash_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
* Description     : Initialize the flash.
* Input parameter : no.
* Output parameter: no.
* Return          : no.
* Other description:
     we should set the wait cycle of flash operation according to the sysclk.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
static WORD32 Stm32G0xxx_Flash_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    /* open hsi for flash writing and erasing. */
    RCC->CR |= RCC_CR_HSION;
    
    return SW_OK;
}

/************************************************************************************
* function name   : static BYTE Stm32G0xxx_Flash_WaitForOp(VOID)
* Description     : waiting for the end of flash operation.
* Input parameter : no.
* Output parameter: no.
* Return          : FLASH_ST_READY : ready for operation.
                    FLASH_ST_BUSY  : busy is overtime.
* Other description:
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
#if(defined(IAR))
__ramfunc static BYTE Stm32G0xxx_Flash_WaitForOp(VOID)
#elif(defined(KEIL))
__attribute__((section("KNX_RAMFUNC"))) static BYTE Stm32G0xxx_Flash_WaitForOp(VOID)
#endif
{
    BYTE ucRet = FLASH_ST_READY;
    WORD32 dwOldTime,dwTimeDif,dwError,dwEccErr;
    
    dwOldTime = sg_tFlashTmOp.pfGetMs();
    while(FTFA_ST & FLASH_SR_BSY)
    {
        /* busy,we wait for the end. */
        dwTimeDif = sg_tFlashTmOp.pfGetDlyMs(dwOldTime);
        if(dwTimeDif >= FTFA_CMD_ERASE_TIME)
        {
            /* time is over. */
            ucRet = FLASH_ST_BUSY;
            break;
        }
    }
    /* clear the flag. */
    dwError  = (FTFA_ST & FLASH_SR_ERR_MASK);
    FTFA_ST |= (FLASH_SR_ERR_MASK | FLASH_SR_EOP);
    
    /* check eccr. */
    dwEccErr = (FTFA_ECCR & FLASH_ECCR_ERR_MASK);
    if(0 != dwEccErr)
    {
        FTFA_ST |= dwEccErr;
        dwError |= dwEccErr;
    }
    if(0 != dwError)
    {
        ucRet = FLASH_ST_BUSY;
        return ucRet;
    }
    /* wait configure enable. */
    dwOldTime = sg_tFlashTmOp.pfGetMs();
    while(FTFA_ST & FLASH_SR_CFGBSY)
    {
        /* busy,we wait for the end. */
        dwTimeDif = sg_tFlashTmOp.pfGetDlyMs(dwOldTime);
        if(dwTimeDif >= FTFA_CMD_ERASE_TIME)
        {
            /* time is over. */
            ucRet = FLASH_ST_BUSY;
            break;
        }
    }
    
    return ucRet;
}

/************************************************************************************************
* function name   : static VOID Stm32G0xxx_Flash_WriteDblWord(WORDPTR dwAddr, WORD64 ddwData)
* Description     : write a 16-bit data to flash with the desired address.
* Input parameter : WORDPTR dwAddr : desired address.
                    WORD16 wData   : writed data.
* Output parameter: no.
* Return          : SW_ERR : writing failed.
                    SW_OK  : writing successfully.
* Other description:
     this function will run in ram.
* Modify date     Ver.     Modifier      Action
* ---------------------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
***********************************************************************************************/
#if(defined(IAR))
__ramfunc WORD32 Stm32G0xxx_Flash_WriteDblWord(WORDPTR dwAddr, WORD64 ddwData)
#elif(defined(KEIL))
__attribute__((section("KNX_RAMFUNC"))) WORD32 Stm32G0xxx_Flash_WriteDblWord(WORDPTR dwAddr, WORD64 ddwData)
#endif
{
    BYTE ucStatus;
    WORD32 dwRet;
    
    if(dwAddr & 0x00000007)
    {
        /* the address should align to 16 bits. */
        return SW_ERR;
    }
    /* unlock the flash. */
    Stm32G0xxx_Flash_Unlock();
    /* check the status of flash. */
    ucStatus = Stm32G0xxx_Flash_WaitForOp();
    if(FLASH_ST_BUSY == ucStatus)
    {
        return SW_ERR;
    }
    if(sg_tFlashTmOp.pfAppCheck)
    {
        while(sg_tFlashTmOp.pfAppCheck());
    }
    /* we start the programming. */
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
	__asm
	{
      	CPSID i
	}
#endif
    FTFA_CTRL |= FLASH_CR_PG;
    *(WORD32*)dwAddr = (WORD32)ddwData;                                  /* write data to the address. */
    /* Barrier to ensure programming is performed in 2 steps, in right order
       (independently of compiler optimization behavior)*/
    __ISB(); 
    *(WORD32*)(dwAddr + 4U) = (WORD32)(ddwData >> 32U);
    /* wait the end operation. */
    ucStatus = Stm32G0xxx_Flash_WaitForOp();
    if(FLASH_ST_BUSY == ucStatus)
    {
        dwRet = SW_ERR;
    }
    else
    {
        dwRet = SW_OK;
    }
    /* Open all interrupt. */
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
	__asm
	{
      	CPSIE i
    }
#endif
    FTFA_CTRL &= (~FLASH_CR_PG);
    FTFA_CTRL |= FLASH_CR_LOCK;                   /* we lock the flash. */

    return dwRet;        
}

/************************************************************************************
* function name   : static BOOL Stm32G0xxx_ErasePage(WORDPTR dwStart)
* Description     : Erase a page of flash according to the pointed address.
* Input parameter : WORDPTR dwAddr : desired address.
* Output parameter: no.
* Return          : FALSE : erase failed.
                    TRUE  : erase successfully.
* Other description:
     this function will run in ram.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
#if(defined(IAR))
__ramfunc static BOOL Stm32G0xxx_ErasePage(WORDPTR dwStart)
#elif(defined(KEIL))
__attribute__((section("KNX_RAMFUNC"))) static BOOL Stm32G0xxx_ErasePage(WORDPTR dwStart)
#endif
{
    BOOL   ucRet;
    BYTE   ucStatus,ucPageNum;
    WORD32 dwOldTime,dwTimeDif;
    
    /* unlock the flash. */
    Stm32G0xxx_Flash_Unlock();
    /* check the status of flash. */
    ucStatus = Stm32G0xxx_Flash_WaitForOp();
    if(FLASH_ST_BUSY == ucStatus)
    {
        return FALSE;
    }
    /* wait application is ok. */
    if(sg_tFlashTmOp.pfAppCheck)
    {
        dwOldTime = sg_tFlashTmOp.pfGetMs();
        while(sg_tFlashTmOp.pfAppCheck())
        {
            /* busy,we wait for the end. */
            dwTimeDif = sg_tFlashTmOp.pfGetDlyMs(dwOldTime);
            if(dwTimeDif >= FTFA_CMD_ERASE_TIME)
            {
                break;
            }
        }
    }
    /* get the page address. */
    ucPageNum  = ((dwStart & 0x07ffffff) / FLASH_PAGE_SIZE);
    FTFA_CTRL &= (~(FLASH_CR_MER | FLASH_CR_PAGE_NUM));
    FTFA_CTRL |= (FLASH_CR_PER | (ucPageNum << 3));
    /* close all interrupt. */
#ifdef IAR
    asm("CPSID i");
#endif
#ifdef KEIL
	__asm
	{
      	CPSID i
	}
#endif
    /* start erasing. */
    FTFA_CTRL |= FLASH_CR_STRT;
    /* wait for operation end. */
    ucStatus   = Stm32G0xxx_Flash_WaitForOp();
    if(FLASH_ST_BUSY == ucStatus)
    {
        ucRet = FALSE;
    }
    else
    {
        ucRet = TRUE;
    }
    /* Open interrupt. */
#ifdef IAR
    asm("CPSIE i");
#endif
#ifdef KEIL
	__asm
	{
      	CPSIE i
    }
#endif
    FTFA_CTRL &= (~FLASH_CR_PER);
    FTFA_CTRL |= FLASH_CR_LOCK;                   /* we lock the flash. */

    return ucRet;
}

/************************************************************************************
* function name   : WORD32 Stm32G0xxx_Flash_Write(T_DATA_OPERARTION *ptPara)
* Description     : writing data into flash by the pointed address.
* Input parameter : T_DATA_OPERARTION *ptPara
                               ->ucDevNo    :device's physical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_ERASE  : erase the flash data.
                                             SW_MEDIA_BYTE   : do not support byte writing.
                                             SW_MEDIA_WORD   : write words into flash.
                                             SW_MEDIA_LWORD  : write long words into flash.
                               ->pucBuffer  :buffer for writing the data.
                               ->wDataLength:length of data in byte.
                               ->dwDestAddr :the destination address.
* Output parameter: no.
* Return          : SW_OK :successfully
                    SW_ERR:failed.
* Other description:
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 Stm32G0xxx_Flash_Write(T_DATA_OPERARTION *ptPara)
{
    BOOL ucCheck;
    WORD32 dwRes = SW_ERR;
    
    switch(ptPara->ucOperMode)
    {
        case SW_MEDIA_ERASE:
        {
            /* erase a block. */
            ucCheck = Stm32G0xxx_ErasePage(ptPara->dwDestAddr);
            if(TRUE == ucCheck)
            {
                dwRes = SW_OK;
            }
            break;
        }
        case SW_MEDIA_BYTE:
        case SW_MEDIA_WORD:
        case SW_MEDIA_LWORD:
        {
            /* do not support byte writing. */
            dwRes = SW_ERR;
            break;
        }
        case SW_MEDIA_LLWORD:
        {
            BYTE    *pucData,ucIndex;
            WORDPTR dwAddr;
            WORD16  wLength;
            WORD64  ddwData;
            
            /* get data buffer and the destination address. */
            dwAddr  = ptPara->dwDestAddr;
            pucData = ptPara->pucBuffer;
            wLength = ptPara->wDataLength;
            if(((dwAddr & 0x00000007) != 0) || ((wLength % 8)!=0))
            {
                /* not aligned by long word. */
                return SW_ERR;
            }
            else
            {
                while(wLength > 0)
                {
                    ddwData = 0;
                    for(ucIndex=7;ucIndex > 0;ucIndex--)
                    {
                        /* make a word64 data. */
                        ddwData |= (((WORD64)(*(BYTE*)(pucData + ucIndex))) << (ucIndex * 8));
                    }
                    ddwData += *(BYTE*)pucData;
                    /* write the long word data. */
                    Stm32G0xxx_Flash_WriteDblWord(dwAddr,ddwData);
                    wLength -= 8;
                    pucData += 8;
                    dwAddr  += 8;
                }
                dwRes = SW_OK;
            }
            break;
        }
    }
    
    return dwRes;
}

/************************************************************************************
* function name   : WORD32 Stm32G0xxx_Flash_Read(T_DATA_OPERARTION *ptPara)
* Description     : read data into buffer by the pointed address.
* Input parameter : T_DATA_OPERARTION *ptPara
                               ->ucDevNo    :device's physical No.
                               ->ucOperMode :operation mode
                                             SW_MEDIA_READ  : read from flash.
                               ->pucBuffer  :buffer for reading data.
                               ->wDataLength:length of data in byte.
                               ->dwDestAddr :the destination address.
* Output parameter: ->pucBuffer : read data.
* Return          : SW_OK :successfully
                    SW_ERR:failed.
* Other description:
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
WORD32 Stm32G0xxx_Flash_Read(T_DATA_OPERARTION *ptPara)
{
    WORD16 wIndex;

    if((ptPara->ucOperMode != SW_MEDIA_READ)||(ptPara->pucBuffer == NULL))
    {
        return SW_ERR;
    }
    for(wIndex = 0;wIndex < ptPara->wDataLength;wIndex++)
    {
        *(ptPara->pucBuffer + wIndex) = *(BYTE*)(ptPara->dwDestAddr + wIndex);
    }

    return SW_OK;
}

/************************************************************************************
* function name   : VOID Stm32G0xxx_Flash_Reg(BYTE ucLogNo,BYTE ucDevNo,VOID *ptPara)
* Description     : register flash dreiver to the user layer.
* Input parameter : BYTE ucLogNo : device's logical no.
                    BYTE ucDevNo : device's physical no.
                    VOID *ptPara : hander of Ms timer operation.
* Output parameter: no.
* Return          : no.
* Other description:
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
VOID Stm32G0xxx_Flash_Reg(BYTE ucLogNo,BYTE ucDevNo,VOID *ptPara)
{
    T_REGISTED_DEVICE tRegFlash;
    
    sg_tStm32F10xxFlashOp.pfDrvInit  = Stm32G0xxx_Flash_Init;
    sg_tStm32F10xxFlashOp.pfDrvCtrl  = NULL;
    sg_tStm32F10xxFlashOp.pfDrvRead  = Stm32G0xxx_Flash_Read;
    sg_tStm32F10xxFlashOp.pfDrvWrite = Stm32G0xxx_Flash_Write;
    
    tRegFlash.ucAppType  = SW_SAVE_INTERFACE;              /* application type         */
    tRegFlash.ucDevId    = SW_PERIPHERAL_FLASH;            /* device type              */
    tRegFlash.ucLogDevNo = ucLogNo;                        /* logical no.,0....        */
    tRegFlash.ucDevNo    = ucDevNo;                        /* physical no,0....        */
    tRegFlash.ptDevOp    = &sg_tStm32F10xxFlashOp;         /* interface of device op.  */
    /* registration. */
    API_MediaDev_Reg(&tRegFlash);
    /* hang the handler of ms-timer. */
    if(ptPara)
    {
        sg_tFlashTmOp.pfAppCheck = ((T_FLASH_TMOPER *)ptPara)->pfAppCheck;
        sg_tFlashTmOp.pfGetDlyMs = ((T_FLASH_TMOPER *)ptPara)->pfGetDlyMs;
        sg_tFlashTmOp.pfGetMs    = ((T_FLASH_TMOPER *)ptPara)->pfGetMs;
    }
    
    return;
}





/* End of Flash.c */

