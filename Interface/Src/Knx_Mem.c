/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Mem.c
* FileIdentifier：None
* Abstract ：协议memory处理。
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
#include "Hardware.h"


#include "Knx_Mem.h"
#include "Knx_Prop.h"
#include "Application_Data.h"
#include "knx_chip.h"
#include "Knx_M0705.h"
#include "Knx_Configure.h"
#include "Boardctrl.h"
#include "mem_malloc.h"
#include "Knx_Auth.h"
#include "Rec_Table.h"
#include "Knx_InternalData.h"
#include "Common_media.h"
#include "Knx_LoadCtrl.h"
#include "Knx_InternalApp.h"
#include "KnxProp_0705.h"
#include "Knx_Nl.h"
#include "Knx_M0705_Ll.h"


static BYTE sg_ucDevNo=0;
const BYTE g_RecoverData[22] = {00,00,GET_HIBYTE(VALUE_FACTORY_ID),GET_LOWBYTE(VALUE_FACTORY_ID),00,00,00,00,00,00,00,00,01,01,01,01,00,00,00,00,00,00};

/* global communication object table reference. */
WORDPTR g_dwCoTableRef;
/* Link layer restart counter. */
BYTE g_ucLlRestartCount;
/* hop counter bit4-6. */
BYTE g_ucNlRoutingCount;
/* AL telegram limitation rate */
BYTE g_ucAlTelRateLimit;
/* RAM description variable */
T_RAM_DESC g_tRamDesc = {0x0000,0x0000,NULL};



/**************************************************************************
* FunctionName:BYTE KnxMem_GetVirtFlashStatus()
* FunctionDescription: Get the flash status.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:Flash status is saved in the record's data space in the record
            table.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BYTE KnxMem_GetVirtFlashStatus()
{
    BOOL ucCheck;
    BYTE ucStatus;
    WORD16 wRcdId;    /* Main-ID + Sub-ID. */
    
    /* creat the record ID. */
    wRcdId = BUILD_RECORD_ID(ID_REC_FLASH,0);
    /* get the flash status. */
    ucCheck = RecTable_GetByte(wRcdId,&ucStatus);
    if(TRUE==ucCheck)
    {
        return ucStatus;
    }
    
    return VIR_MEM_STATE_NEW;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_SetVirtMediaStatus(BYTE ucStatus)
* FunctionDescription: Set the flash status.
* InputParameterBYTE ucStatus:status.
* OutputParameterno.
* Return Value：no.
* Other Description:Flash status is saved in the record's data space in the record
            table.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_SetVirtMediaStatus(BYTE ucStatus)
{
    BOOL ucCheck;
    WORD16 wRcdId;    /* Main-ID + Sub-ID. */
    
    /* creat the record ID. */
    wRcdId = BUILD_RECORD_ID(ID_REC_FLASH,0);
    /* set the flash status. */
    ucCheck = RecTable_SetByte(wRcdId,ucStatus);
    
    return ucCheck;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteRam2Media(VOID)
* FunctionDescription: write the flash buffer data to the flash.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteRam2Media(VOID)
{
    WORD32 dwRes;

    dwRes = API_FlashMedia_DataFlush(sg_ucDevNo);    
    if(SW_OK != dwRes)
    {
        return FALSE;
    }
    
    return TRUE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteBufferFlush(VOID)
* FunctionDescription: write the flash buffer data to the flash and set the flash status.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteBufferFlush(VOID)
{
    BOOL ucResult;
    BYTE ucStatus;
    
    /* buffer has data to be written to media. */
    ucResult = KnxMem_WriteRam2Media();
    if(TRUE == ucResult)
    {
        ucStatus = KnxMem_GetVirtFlashStatus();
        if(VIR_MEM_STATE_OK != ucStatus)
        {
            /* at start,if flash is new,we set it OK. */
            ucResult = KnxMem_SetVirtMediaStatus(VIR_MEM_STATE_OK);
        }
    }

    return ucResult;
}

/**************************************************************************************************************
* FunctionName:VOID KnxMem_ReleaseVirRam(VOID)
* FunctionDescription: This function release the virtual RAM.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxMem_ReleaseVirRam(VOID)
{
    if(g_tRamDesc.pucData)
    {
        /* the physical RAM is made by malloc,so we should free it. */
        mem_free(g_tRamDesc.pucData);
        g_tRamDesc.pucData = NULL;
    }
    g_tRamDesc.wStart = 0x000;
    g_tRamDesc.wLength= 0x000;
    
    return;
}

/**************************************************************************************************************
* FunctionName:BOOL KnxMem_VirRamInit(VOID)
* FunctionDescription: This function initialize the virtual RAM.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxMem_VirRamInit(VOID)
{
    BOOL ucCheck = TRUE;
    
    /* free the virtual RAM's physical RAM. */
    KnxMem_ReleaseVirRam();
    /* we get the MCB's parameter of the virtual RAM. */
    Knx_GetRamAlloc(MEM_TYPE_HIRAM,&g_tRamDesc.wStart,&g_tRamDesc.wLength);
    if(g_tRamDesc.wLength)
    {
        /* we allocate a physicall RAM for the virtual RAM. */
        g_tRamDesc.pucData = mem_malloc(g_tRamDesc.wLength);
        if(g_tRamDesc.pucData)
        {
            /* clear the RAM. */
            mem_memset(g_tRamDesc.pucData,0,g_tRamDesc.wLength);
        }
        else
        {
            /* not enough RAM. */
            KnxMem_ReleaseVirRam();
            ucCheck = FALSE;
        }
    }
    
    return ucCheck;
}

/**************************************************************************************************************
* FunctionName:T_RAM_DESC *KnxMem_GetVirRamDesc(WORDPTR dwAddr)
* FunctionDescription: get RAM descriptor of a given virtual address.
* InputParameterWORDPTR dwAddr:virtual address.
* OutputParameterno.
* Return Value：NULL or pointer.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
T_RAM_DESC *KnxMem_GetVirRamDesc(WORDPTR dwAddr)
{
    T_RAM_DESC *ptRamDesc = NULL;
    
    if(g_tRamDesc.wLength != 0)
    {
        /* in RAM range. */
        if((dwAddr >= g_tRamDesc.wStart)&&\
           (dwAddr <= (g_tRamDesc.wStart + g_tRamDesc.wLength - 1)))
        {
            ptRamDesc = &g_tRamDesc;
        }
    }
    
    return ptRamDesc;
}

/**************************************************************************************************************
* FunctionName:BYTE *KnxMem_GetVirRamAddr(WORDPTR dwAddr)
* FunctionDescription: get physical RAM address of a given virtual address.
* InputParameterWORDPTR dwAddr:virtual address.
* OutputParameterno.
* Return Value：NULL or pointer.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE *KnxMem_GetVirRamAddr(WORDPTR dwAddr)
{
    BYTE *pucData = NULL;
    T_RAM_DESC *ptRamDesc;
    
    ptRamDesc = KnxMem_GetVirRamDesc(dwAddr);
    if(NULL!=ptRamDesc)
    {
        /* get the start address. */
        pucData  = ptRamDesc->pucData;
        /* + offset. */
        pucData += (dwAddr - ptRamDesc->wStart);
    }
    
    return pucData;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_ReadMediaByte(WORDPTR dwAddr, BYTE *pucData)
* FunctionDescription: get a byte data from the given virtual address of media.
* InputParameterWORDPTR dwAddr:source address.
            BYTE *pucData : destination address.
* OutputParameterBYTE *pucData : destination data.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_ReadMediaByte(WORDPTR dwAddr, BYTE *pucData)
{
    API_FlashMedia_Read_BYTE(sg_ucDevNo,GET_REAL_OF_VIR(dwAddr),pucData);
    
    return TRUE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_ReadRamByte(WORDPTR dwAddr, BYTE *pucData)
* FunctionDescription: get a byte data from the given virtual address of RAM.
* InputParameterWORDPTR dwAddr:source address.
            BYTE *pucData : destination address(virtual).
* OutputParameterBYTE *pucData : destination data.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_ReadRamByte(WORDPTR dwAddr,BYTE *pucData)
{
    BYTE *pucRamAddr;
    
    pucRamAddr = KnxMem_GetVirRamAddr(dwAddr);
    if(pucRamAddr)
    {
        *pucData = *pucRamAddr;
        return TRUE;
    }
    
    return FALSE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteRamByte(WORDPTR dwAddr, BYTE ucData)
* FunctionDescription: write a byte data to the given virtual address of RAM.
* InputParameterWORDPTR dwAddr:source address.
            BYTE ucData   : data.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteRamByte(WORDPTR dwAddr,BYTE ucData)
{
    BYTE *pucRamAddr;
    
    pucRamAddr = KnxMem_GetVirRamAddr(dwAddr);
    if(pucRamAddr)
    {
        *pucRamAddr = ucData;
        return TRUE;
    }
    
    return FALSE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData)
* FunctionDescription: get a byte data from the given virtual address.
* InputParameterWORDPTR dwAddr:source address.
            BYTE *pucData : destination address.
* OutputParameterBYTE *pucData : destination data.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData)
{
    BYTE ucType;
    
    ucType = KnxMask_GetMemTypeOfByte(dwAddr);
    switch(ucType)
    {
        case MEM_TYPE_EE_USER: /* user memory area. */
        case MEM_TYPE_EE_SYS:  /* system memory area. */
        {
            return KnxMem_ReadMediaByte(dwAddr,pucData);
        }
        case MEM_TYPE_HIRAM:   /* RAM area. */
        {
            return KnxMem_ReadRamByte(dwAddr,pucData);
        }
    }
    
    return FALSE;
}

/**************************************************************************
* FunctionName:BYTE KnxMem_GetByte(WORDPTR dwAddr)
* FunctionDescription: get a byte data from the given virtual address.
* InputParameterWORDPTR dwAddr:source address.
* OutputParameterno.
* Return Value：memory data.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BYTE KnxMem_GetByte(WORDPTR dwAddr)
{
    BOOL ucCheck;
    BYTE ucData;

    ucCheck = KnxMem_ReadByte(dwAddr,&ucData);
    if(TRUE==ucCheck)
    {
        return ucData;
    }

    return 0x00;
}

/**************************************************************************
* FunctionName:BYTE KnxMem_GetByte(WORDPTR dwAddr)
* FunctionDescription: This function reads one byte from virtual memory as well as from
            physical memory.
* InputParameterWORDPTR dwAddr:source address.
* OutputParameterno.
* Return Value：memory data.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BYTE KnxMem_GetByteEx(WORDPTR dwAddr)
{
    BYTE ucData,ucType;
    
    ucType = KnxMask_GetMemTypeOfByte(dwAddr);
    if(ucType != MEM_TYPE_ERROR)
    {
        /* get data from the virtual area. */
        KnxMem_ReadByte(dwAddr,&ucData);
    }
    else
    {
        /* the address is out of the system&user data area. */
        /* else,we get data directly from the given address. */
        ucData = *(BYTE*)dwAddr;
    }

    return ucData;
}

/**************************************************************************
* FunctionName:WORD16 KnxMem_GetWord(WORDPTR dwAddrHi)
* FunctionDescription: This function reads one word from virtual memory area.
* InputParameterWORDPTR dwAddr:source address.
* OutputParameterno.
* Return Value：memory data.
* Other Description:The requested word in virtual memory is assumed to have the 
            hibyte at address dwAddrHi and the lobyte at dwAddrHi+1
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
WORD16 KnxMem_GetWord(WORDPTR dwAddrHi)
{
    BOOL ucCheck;
    BYTE ucByte;
    WORD16 wWord;
    
    /* read hight byte. */
    ucCheck = KnxMem_ReadByte(dwAddrHi,&ucByte);
    if(FALSE==ucCheck)
    {
        return 0x0000;
    }
    else
    {
        wWord = (((WORD16)ucByte) << 8);
    }
    /* read low byte. */
    ucCheck = KnxMem_ReadByte(dwAddrHi+1,&ucByte);
    if(FALSE==ucCheck)
    {
        return 0x0000;
    }
    else
    {
        wWord += ucByte;
    }

    return wWord;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteMediaByte(WORDPTR dwAddr,BYTE ucData)
* FunctionDescription: This function writes one byte to virtual media area.
* InputParameterWORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteMediaByte(WORDPTR dwAddr,BYTE ucData)
{
    WORD32 dwRet;
    BOOL   ucCheck;
    BYTE   ucStatus;
    
    /* set flash's status to writing. */
    ucStatus = KnxMem_GetVirtFlashStatus();
    if(VIR_MEM_STATE_WRITING != ucStatus)
    {
        ucCheck = KnxMem_SetVirtMediaStatus(VIR_MEM_STATE_WRITING);
        if(FALSE == ucCheck)
        {
            return FALSE;
        }
    }
    
    /* write data. */
    dwRet = API_FlashMedia_Write_BYTE(sg_ucDevNo,GET_REAL_OF_VIR(dwAddr),ucData);
    if(SW_OK == dwRet)
    {
        ucCheck = TRUE;
    }
    else
    {
        ucCheck = FALSE;
    }
    
    return ucCheck;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData)
* FunctionDescription: This function writes one byte to virtual memory area.
* InputParameterWORDPTR dwAddr:source address.
            BYTE ucData   :source data.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData)
{
    BYTE ucType;
    
    /* get memory type. */
    ucType = KnxMask_GetMemTypeOfByte(dwAddr);
    switch(ucType)
    {
        case MEM_TYPE_EE_USER:
        case MEM_TYPE_EE_SYS:
        {
            /* virtual media area. */
            return KnxMem_WriteMediaByte(dwAddr,ucData);
        }
        case MEM_TYPE_HIRAM:
        {
            /* virtual RAM area. */
            return KnxMem_WriteRamByte(dwAddr,ucData);
        }
    }
    
    return FALSE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData)
* FunctionDescription: This function writes one word to virtual memory area.
* InputParameterWORDPTR dwAddrHi:destination high address.
            WORD16 wData    :source data.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData)
{
    BOOL ucCheck;
    
    /* we write the word. */
    ucCheck = KnxMem_WriteByte(dwAddrHi,GET_HIBYTE(wData));
    if(FALSE == ucCheck)
    {
        return FALSE;
    }
    ucCheck = KnxMem_WriteByte(dwAddrHi+1,GET_LOWBYTE(wData));
    if(FALSE == ucCheck)
    {
        return FALSE;
    }
    
    return TRUE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount)
* FunctionDescription: This function writes ucCount bytes to virtual memory area.
* InputParameterWORDPTR dwAddr:destination high address.
            BYTE *pucData :source data.
            BYTE ucCount  :byte count.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount)
{
    BYTE ucCheck,ucIndex;
    
    for(ucIndex = 0; ucIndex < ucCount; ucIndex++)
    {
        ucCheck = KnxMem_WriteByte(dwAddr + ucIndex,*(pucData+ucIndex));
        if(FALSE==ucCheck)
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_ReadAppHeader(BYTE ucPosition, BYTE *pucData)
* FunctionDescription: This function get the application header data.
* InputParameterBYTE ucPosition:index of application data.
                            POS_APP_KEY
                            POS_APP_CO_TAB_REF
                            POS_APP_STACK_TYPE
                            POS_APP_STACK_VERSION
            BYTE *pucData :source data.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_ReadAppHeader(BYTE ucPosition, BYTE *pucData)
{
    BYTE ucIndex,aucAppData[APP_MAIN_SIZE],ucType;
    WORDPTR dwAppRef;
    
    if(ucPosition >= APP_MAIN_SIZE)
    {
        /* over range. */
        return FALSE;
    }
    /* check whether the application was loaded. */
    ucType = Knx_GetLoadState(OBJECT_APPLICATION_ID);
    if(ucType != LOAD_STATE_LOADED)
    {
        return FALSE;
    }
    /* get the application header virtual address. */
    dwAppRef = KnxMem_GetWord(VIR_APP_MAIN);
    for(ucIndex = 0; ucIndex < APP_MAIN_SIZE; ucIndex++)
    {
        /* get application header data. */
        KnxMem_ReadByte(dwAppRef+ucIndex,aucAppData+ucIndex);
    }
    /* check KEY. */
    if((aucAppData[POS_APP_KEY]   != KNX_APP_KEY0)                      ||\
       (aucAppData[POS_APP_KEY+1] != KNX_APP_KEY1)                      ||\
       (aucAppData[POS_APP_STACK_TYPE]   != GET_HIBYTE(DEV_DESC_0705))  ||\
       (aucAppData[POS_APP_STACK_TYPE+1] != GET_LOWBYTE(DEV_DESC_0705)))
    {
        return FALSE;
    }
    /* get the destination data. */
    *pucData = aucAppData[ucPosition];
    
    return TRUE;
}

/**************************************************************************************************************
* FunctionName:VOID KnxMem_Init(VOID)
* FunctionDescription: This function does the initialisation of the internal variables.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxMem_Init(VOID)
{
    g_dwCoTableRef     = VIR_COMMOB_TABLE;
    g_ucLlRestartCount = (REPEAT_COUNTER_BUSY << 4)|REPEAT_COUNTER_NACK;
    g_ucNlRoutingCount = (AL_DEL_MESSAGE << 7)|(NL_ROUTING_COUNT << 4);
    g_ucAlTelRateLimit = AL_TEL_RATE_LIMIT;
    
    return;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_WriteFinished(VOID)
* FunctionDescription: This function is called to force writing data to the flash.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteFinished(VOID)
{
    BOOL ucResult;
    
    ucResult = KnxMem_WriteBufferFlush();   /* brush the RAM buffer data to FLASH. */
    KnxMem_Init();
    
    return ucResult;
}

/**************************************************************************
* FunctionName:WORD16 KnxMem_GetChecksum(WORD16 wStart,WORD16 wEnd)
* FunctionDescription: This function calculates the checksum for the given memory area.
* InputParameterWORD16 wStart:start address.
            WORD16 wEnd  :end address.
* OutputParameterno.
* Return Value：check sum.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
WORD16 KnxMem_GetChecksum(WORD16 wStart,WORD16 wEnd)
{
    WORD16 wAddr;
    WORD16 wChecksum;
    
    wChecksum = 0xFFFF;
    for(wAddr = wStart; wAddr < wEnd; wAddr++)
    {
        /* Build the CRC 16 CCITT checksum */
        /* Polynom (X^16 + X^12 + X^5 + 1) */
        wChecksum = (BYTE)(wChecksum >> 8) | (wChecksum << 8);
        wChecksum ^= KnxMem_GetByte(wAddr);
        wChecksum ^= (BYTE)(wChecksum & 0xFF) >> 4;
        wChecksum ^= (wChecksum << 8) << 4;
        wChecksum ^= ((wChecksum & 0xFF) << 4) << 1;
        /* If we are at start of new 1K block */
        if (((wAddr-wStart) & 0x03FF) == 0)
        {
            /* reset the watchdog. */
            Knx_Internal_ResetDog();
        }
    }

    return wChecksum;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_SetChecksum(BYTE ucObjIndex)
* FunctionDescription: This function writes the checksum for the given memory block.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_SetChecksum(BYTE ucObjIndex)
{
    WORD16 wChecksum,wEnd;
    BYTE   ucIndex;
    BOOL   ucCheck = TRUE;
    T_KNXMEM_MCB tMcb;

    ucIndex = FIRST_MCB_INDEX;
    while(ucCheck)
    {
        ucCheck = Knx_GetNextMcb(&ucIndex, &tMcb);
        if(tMcb.ucOwner != ucObjIndex)
        {
            continue;
        }
        if(tMcb.ucEnCRC == FALSE)
        {
            continue;
        }
        /* get the MCB. */
        wEnd = tMcb.wStart + tMcb.wLength;
        /* calculate the checksum. */
        wChecksum = KnxMem_GetChecksum(tMcb.wStart,wEnd);
        /* write the checksum to the MCB. */
        Knx_WriteChecksum(ucIndex-1,wChecksum);
    }
    
    return TRUE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_CheckChecksum(VOID)
* FunctionDescription: This function checks the checksum(s) of the data in EEPROM area.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_CheckChecksum(VOID)
{
    BOOL ucCheck = TRUE;
    BYTE ucIndex;
    WORD16 wChecksum,wEnd;
    T_KNXMEM_MCB tMcb;
    
    /* set the start MCB. */
    ucIndex = FIRST_MCB_INDEX;
    while(ucCheck)
    {
        ucCheck = Knx_GetNextMcb(&ucIndex, &tMcb);
        if(tMcb.ucOwner > OWNER_MAX_VALID)
        {
            /* not the destination MCB,goto the next MCB. */
            continue;
        }
        if(tMcb.ucEnCRC == FALSE)
        {
            /* CRC is wrong.goto next. */
            continue;
        }
        wEnd      = tMcb.wStart + tMcb.wLength;
        wChecksum = KnxMem_GetChecksum(tMcb.wStart,wEnd);
        if(wChecksum != tMcb.wCrc)
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr)
* FunctionDescription: This function sets the physical address of the device.
* InputParameterWORD16 wPhysAddr : physical address.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr)
{
    BYTE ucSrvCtrl;

    ucSrvCtrl = GET_SRV_CTRL;
    if((ucSrvCtrl & SC_PHYS_ADDR_WRITE_EN) == 0x0000)
    {
        return FALSE;
    }
    /* write physical address. */
    KnxMem_WriteWord(VIR_PHY_ADDR,wPhysAddr);
    /* set the address table object checksum. */
    KnxMem_SetChecksum(OBJECT_ADDR_TABLE_ID);
    /* brush the buffer. */
    return KnxMem_WriteBufferFlush();
}

/**********************************************************************************
* FunctionName:BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr)
* FunctionDescription: This function returns the connection number of the given group address.
* InputParameterWORD16 wPhysAddr : physical address.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetConnNo(WORD16 wGrpAddr)
{
    BYTE ucLeft;
    BYTE ucRight;
    BYTE ucConnNo;
    WORD16 wTempAddr;

    /* First group address in array */
    ucLeft  = 1;
    /* Last group address in array */
    ucRight = GET_ADDR_TBL_LEN - 1;
    while(ucLeft <= ucRight)                       
    {
        /* find middle of interval */
        ucConnNo = (ucLeft + ucRight)>>1;
        /* Get address from table */
        wTempAddr = GET_GRP_ADDRESS(ucConnNo);//GET_WORD_DATA(VIR_PHY_ADDR+(ucConnNo<<1));
        /* If address matches ? */
        if(wGrpAddr == wTempAddr)
        {
            /* Return connection number */
            return ucConnNo;
        }
        /* If received address is left of middle */
        if(wGrpAddr < wTempAddr)
        {
            /* Check left half of interval */
            ucRight = ucConnNo - 1;
        }
        else /* Else it is right of middle */
        {
            /* Check right half of interval */
            ucLeft  = ucConnNo + 1;
        }
    }
    
    return 0;
}

/**********************************************************************************
* FunctionName:BYTE* KnxMem_GetCoRamFlags(VOID)
* FunctionDescription: This function returns the pointer to the communication objects RAM flags.
* InputParameterWORD16 wPhysAddr : physical address.
* OutputParameterno.
* Return Value：BYTE *:physical address of RAM.
* Other Description:The pointer returned by this function is valid in the physical address 
            space of the controller
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE* KnxMem_GetCoRamFlags(VOID)
{
    WORD16 wRamFlagsRef;

    if(g_dwCoTableRef == 0x00000000)
    {
        return 0x00;
    }
    /* get co. RAM flag reference from Co. table. */
    wRamFlagsRef = KnxMem_GetWord(g_dwCoTableRef + COTAB_POS_RAMFLAGS_REF);
    
    return KnxMem_GetVirRamAddr((WORDPTR)wRamFlagsRef);
}

/**********************************************************************************
* FunctionName:BYTE KnxMem_GetCoCount(VOID)
* FunctionDescription: This function returns the number of communication objects.
* InputParameterWORD16 wPhysAddr : physical address.
* OutputParameterno.
* Return Value：BYTE :communication object number.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetCoCount(VOID)
{
    BYTE ucCoCount;
    
    if(g_dwCoTableRef == 0x00000000)
    {
        return 0x00;
    }
    /* get the Co. count from the Co. table. */
    ucCoCount = KnxMem_GetByte(g_dwCoTableRef + COTAB_POS_COUNT);
    /* valid range check. */
    if((g_dwCoTableRef + 2 + (4*ucCoCount)) > VIR_END_USER_EE)
    {
        return 0x00;
    }
    
    return ucCoCount;
}

/**********************************************************************************
* FunctionName:WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo)
* FunctionDescription: This function returns a pointer to a communication  object descriptor 
            defined in EEPROM area.
* InputParameterBYTE ucCoNo : number of communication object.
* OutputParameterno.
* Return Value：WORDPTR :communication object's descriptor reference(Virtual).
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
WORDPTR KnxMem_GetCoDescRef(BYTE ucCoNo)
{
    BYTE ucCoCunt;
    WORDPTR dwCoDescRef;
    
    if(g_dwCoTableRef == 0x00000000)
    {
        return 0x00000000;
    }
    /* get communication count. */
    ucCoCunt = *(BYTE*)(GET_REAL_OF_VIR(g_dwCoTableRef + COTAB_POS_COUNT));
    /* Is the Co. No. valide? */
    if(ucCoNo >= ucCoCunt)
    {
        return 0x00000000;
    }
    /* get the reference. */
    dwCoDescRef  = g_dwCoTableRef + COTAB_POS_FIRSTVAL_REF;
    dwCoDescRef += (ucCoNo * CO_DESC_SIZE);
    
    return dwCoDescRef;
}

/**********************************************************************************
* FunctionName:WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo)
* FunctionDescription: This function retrieves the virtual address of the buffer of the given 
            communication object.
* InputParameterBYTE ucCoNo : number of communication object.
* OutputParameterno.
* Return Value：WORDPTR :communication object's value reference(Virtual).
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo)
{
    WORDPTR dwCoDescRef,dwCoValRef;

    dwCoDescRef = KnxMem_GetCoDescRef(ucCoNo);
    if(dwCoDescRef == 0x00000000)
    {
        return 0x00000000;
    }
    /* get high byte. */
    dwCoValRef = *(BYTE*)(GET_REAL_OF_VIR(dwCoDescRef + CO_POS_VALUE_REF));
    dwCoValRef <<= 8;
    /* get low byte. */
    dwCoValRef += *(BYTE*)(GET_REAL_OF_VIR(dwCoDescRef + CO_POS_VALUE_REF + 1));

    return dwCoValRef;
}

/**********************************************************************************
* FunctionName:BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo)
* FunctionDescription: returns the configuration flags of the given communication object.
* InputParameterBYTE ucCoNo : number of communication object.
* OutputParameterno.
* Return Value：BYTE :communication object's configuration.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo)
{
    BYTE ucCfg;
    WORDPTR dwCoDescRef;

    dwCoDescRef = KnxMem_GetCoDescRef(ucCoNo);
    if(dwCoDescRef == 0x00000000)
    {
        return 0x00;
    }
    dwCoDescRef = dwCoDescRef + CO_POS_CONFIG;
    dwCoDescRef = GET_REAL_OF_VIR(dwCoDescRef);
    ucCfg = *(BYTE*)dwCoDescRef;//(GET_REAL_OF_VIR(dwCoDescRef + CO_POS_CONFIG));
    
    return ucCfg;
}

/**********************************************************************************
* FunctionName:BYTE KnxMem_GetCoValueType(BYTE nCoNo)
* FunctionDescription: This function returns the value type of the given communication object.
* InputParameterBYTE ucCoNo : number of communication object.
* OutputParameterno.
* Return Value：BYTE :communication object's value type.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetCoValueType(BYTE ucCoNo)
{
    BYTE ucType;
    WORDPTR dwCoDescRef;
    
    /* get communication descriptor. */
    dwCoDescRef = KnxMem_GetCoDescRef(ucCoNo);
    if(dwCoDescRef == 0x00000000)
    {
        return 0xFF;
    }
    /* get type. */
    ucType = *(BYTE*)(GET_REAL_OF_VIR(dwCoDescRef + CO_POS_TYPE));
    
    return ucType;
}

/**********************************************************************************
* FunctionName:BOOL KnxMem_AppHeaderCheck(VOID)
* FunctionDescription: This function check the application header validity.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BOOL KnxMem_AppHeaderCheck(VOID)
{
    BYTE ucByte;
    BOOL ucCheck;
    WORDPTR dwPointer;
    
    /* check communication object address. */
    ucCheck = KnxMem_ReadAppHeader(POS_APP_CO_TAB_REF,&ucByte);
    if(ucCheck==FALSE)
    {
        return ucCheck;
    }
    dwPointer = ucByte;
    KnxMem_ReadAppHeader(POS_APP_CO_TAB_REF+1,&ucByte);
    dwPointer = (dwPointer<<8)+ucByte;
    if(dwPointer != VIR_COMMOB_TABLE)
    {
        /* communication address is not right. */
        return FALSE;
    }
    /* check application stack version. */
    KnxMem_ReadAppHeader(POS_APP_STACK_VERSION, &ucByte);
    if(ucByte != APP_STACK_API_VERSION)
    {
        return FALSE;
    }

    return TRUE;
}

/**********************************************************************************
* FunctionName:BYTE KnxMem_GetAssocCount(VOID)
* FunctionDescription: This function returns the count of associations defined in virtual ROM 
            area.
* InputParameterno.
* OutputParameterno.
* Return Value：BYTE : associations count.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetAssocCount(VOID)
{
    BYTE ucCunt;
    
    ucCunt = GET_ASSOC_TBL_LEN;
    return ucCunt;
}

/**********************************************************************************
* FunctionName:BOOL KnxMem_GetAssoc(BYTE ucIndex, BYTE *pucConnNo, BYTE *pucCoNo)
* FunctionDescription: This function retrieves an association given by index.
* InputParameterBYTE ucIndex    : association index.
* OutputParameterBYTE *pucConnNo : connection number.
            BYTE *pucCoNo   : communication object No.
* Return Value：BYTE : associations count.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BOOL KnxMem_GetAssoc(BYTE ucIndex, BYTE *pucConnNo, BYTE *pucCoNo)
{
    /* get the connection no(Grp. address index). */
    *pucConnNo = GET_ASSOC_GRPINDEX(ucIndex);
    /* get the communication object no. */
    *pucCoNo   = GET_ASSOC_COMOBJNO(ucIndex);

    return TRUE;
}

/**********************************************************************************
* FunctionName:BYTE KnxMem_GetSendConnNo(BYTE ucCoNo)
* FunctionDescription: This function is used by sending communication object to retrieve the 
            sending connection number.
* InputParameterBYTE ucCoNo : communication object N.
* OutputParameterno.
* Return Value：BYTE : connection number(Grp. index).
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetSendConnNo(BYTE ucCoNo)
{
    BYTE ucAssocCount;
    BYTE ucIndex;

    ucAssocCount = GET_ASSOC_TBL_LEN;
    /* go through the association table. */
    for(ucIndex = 0; ucIndex < ucAssocCount; ucIndex++)
    {
        /* check CO number. */
        if(ucCoNo == GET_ASSOC_COMOBJNO(ucIndex))
        {
            /* get Connection number. */
            return GET_ASSOC_GRPINDEX(ucIndex);
        }
    }

    return 0x00;
}

/**********************************************************************************
* FunctionName:BOOL KnxMem_SetParam(BYTE ucItem, BYTE ucValue)
* FunctionDescription: This function may be called by application to set some system parameters.
* InputParameterBYTE ucItem : system parameter id.
                          PARID_RESTART_COUNT
                          PARID_ROUTING_COUNT
                          PARID_DEL_USER_MSG
                          PARID_TELRATE_LIMIT
            BYTE ucValue: 
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BOOL KnxMem_SetParam(BYTE ucItem, BYTE ucValue)
{
    switch(ucItem)
    {
        case PARID_RESTART_COUNT:
        {
            /* renew restart count. */
            g_ucLlRestartCount = ucValue;
            /* set restart count to the interface. */
            break;
        }
        case PARID_ROUTING_COUNT:
        {
            if(ucValue > 7)
            {
                return FALSE;
            }
            ucValue <<= 4;
            /* set hop count. */
            g_ucNlRoutingCount &= ~NPDU_HOP_COUNT_MASK;
            g_ucNlRoutingCount |= ucValue;
            break;
        }
        case PARID_DEL_USER_MSG:
        {
            if(ucValue)
            {
                g_ucNlRoutingCount |= DELETE_USER_MSG;
            }
            else
            {
                g_ucNlRoutingCount &= ~DELETE_USER_MSG;
            }
            break;
        }
        case PARID_TELRATE_LIMIT:
        {
            g_ucAlTelRateLimit = ucValue;
            break;
        }
        default:
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

/**********************************************************************************
* FunctionName:BYTE KnxMem_GetNlRoutingCount(VOID)
* FunctionDescription: This function retrieves the current routing count.
* InputParameterno. 
* OutputParameterno.
* Return Value：hop count.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetNlRoutingCount(VOID)
{
    return (g_ucNlRoutingCount & NPDU_HOP_COUNT_MASK);
}

/**********************************************************************************
* FunctionName:BOOL KnxMem_GetDelUserMsg(void)
* FunctionDescription: This function retrieves whether automated deleting of user messages is enabled.
* InputParameterno. 
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BOOL KnxMem_GetDelUserMsg(void)
{
    if(g_ucNlRoutingCount & DELETE_USER_MSG)
    {
        return TRUE;
    }
    
    return FALSE;
}

/**********************************************************************************
* FunctionName:BYTE KnxMem_GetAlTelRateLimit(void)
* FunctionDescription: This function retrieves the current telegram rate limitation rate.
* InputParameterno. 
* OutputParameterno.
* Return Value：hop count.
* Other Description:Value definition: Telegram rate whithin 17s, 0x00,if limitation is off
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetAlTelRateLimit(void)
{
    return g_ucAlTelRateLimit;
}

/**************************************************************************
* FunctionName:VOID KnxMem_MediaRecoveDefault(VOID)
* FunctionDescription: This function clears the parameter area in flash.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:this function will be called at the start.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
VOID KnxMem_MediaRecoveDefault(VOID)
{
    WORD16 wIndex;
    WORD32 dwRes;
    WORDPTR dwStart;
    T_KNXMEM_MCB tMcb;
    T_DATA_OPERARTION tWriteOper;
    BYTE *sg_aucFlashPageRam = NULL;

    /* light the programming LED. */
    Knx_Internal_PrgmLedOn();
    /* alloc memory for data operation. */
    sg_aucFlashPageRam = mem_malloc(2*sizeof(T_0705_DEVOBJ_PARAM));
    if(NULL == sg_aucFlashPageRam)
    {
        Knx_Internal_ResetDev();
    }
    /* We indicate that a master reset has been started;*/
    KnxMem_SetVirtMediaStatus(VIR_MEM_STATE_WRITING);

    /* we clear the user data area and system data area. */
    for(dwStart = VIR_BEG_USER_EE;dwStart < VIR_END_USER_EE;dwStart+=FLASH_PAGE_SIZE)
    {
        tWriteOper.ucDevNo    = 0;
        tWriteOper.ucOperMode = SW_MEDIA_ERASE;                     /* erase the flash. */
        tWriteOper.wDataLength= 0;
        tWriteOper.pucBuffer  = NULL;
        tWriteOper.dwDestAddr = GET_REAL_OF_VIR(dwStart);
        dwRes = API_Media_Write(&tWriteOper);
        if(SW_ERR==dwRes)
        {
            /* if flash has error,we dead. the programming LED is lighting. */
            while(1);
        }
        /* here,we do not clear the record table area. */
    }
    tWriteOper.ucDevNo    = 0;
    tWriteOper.ucOperMode = SW_MEDIA_ERASE;                     /* erase the flash. */
    tWriteOper.wDataLength= 0;
    tWriteOper.pucBuffer  = NULL;
    tWriteOper.dwDestAddr = GET_REAL_OF_VIR(VIR_BEG_SYS_EE);
    dwRes = API_Media_Write(&tWriteOper);
    if(SW_ERR==dwRes)
    {
        /* if flash has error,we dead. the programming LED is lighting. */
        while(1);
    }
    /* now we set the default data. */
    KnxMem_WriteByte(VIR_ADDR_TABLE_LENGTH, 0x01);    /* stop the address table. */
    /* set device object property data. */
    for(wIndex=0;wIndex<sizeof(T_0705_DEVOBJ_PARAM);wIndex++)
    {
        /* get backup data of device object property. */
        sg_aucFlashPageRam[wIndex] = *(BYTE*)((BYTE*)(&tDevObj_Prop_Dflt)+wIndex);
    }
    /* write data to the parameter area. */
    KnxMem_WriteData(DEV_OBJ_PROP_LOCATION,sg_aucFlashPageRam,sizeof(T_0705_DEVOBJ_PARAM));
    
    /* set address table object property data. */
    for(wIndex=0;wIndex<sizeof(T_0705_ADDROBJ_PARAM);wIndex++)
    {
        /* get backup data of device object property. */
        sg_aucFlashPageRam[wIndex] = *(BYTE*)((BYTE*)(&tAddrObj_Prop_Dflt)+wIndex);
    }
    /* write data to the parameter area. */
    KnxMem_WriteData(ADDR_OBJ_PROP_LOCATION,sg_aucFlashPageRam,sizeof(T_0705_ADDROBJ_PARAM));
    
    /* set association table object property data. */
    for(wIndex=0;wIndex<sizeof(T_0705_ASSOCOBJ_PARAM);wIndex++)
    {
        /* get backup data of device object property. */
        sg_aucFlashPageRam[wIndex] = *(BYTE*)((BYTE*)(&tAssocObj_Prop_Dflt)+wIndex);
    }
    /* write data to the parameter area. */
    KnxMem_WriteData(ASSOC_OBJ_PROP_LOCATION,sg_aucFlashPageRam,sizeof(T_0705_ASSOCOBJ_PARAM));
    
    /* set application object property data. */
    for(wIndex=0;wIndex<sizeof(T_0705_APPOBJ_PARAM);wIndex++)
    {
        /* get backup data of device object property. */
        sg_aucFlashPageRam[wIndex] = *(BYTE*)((BYTE*)(&tAppObj_Prop_Dflt)+wIndex);
    }
    /* write data to the parameter area. */
    KnxMem_WriteData(APP_OBJ_PROP_LOCATION,sg_aucFlashPageRam,sizeof(T_0705_APPOBJ_PARAM));
    
    /* set PEI object property data. */
    for(wIndex=0;wIndex<sizeof(T_0705_PEIOBJ_PARAM);wIndex++)
    {
        /* get backup data of device object property. */
        sg_aucFlashPageRam[wIndex] = *(BYTE*)((BYTE*)(&tPeiObj_Prop_Dflt)+wIndex);
    }
    /* write data to the parameter area. */
    KnxMem_WriteData(PEI_OBJ_PROP_LOCATION,sg_aucFlashPageRam,sizeof(T_0705_PEIOBJ_PARAM));

    /* Re-write MCB for system memory 1 */
    tMcb.wStart    = VIR_BEG_SYS1_EE;      /* Set start of block */
    tMcb.wLength   = VIR_SYS1_SIZE;        /* Set size of block  */
    tMcb.ucAccess  = ACC_APP;              /* Set access level   */
    tMcb.ucEnCRC   = FALSE;                /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_SYS;      /* Set memory type   */
    tMcb.ucOwner   = OWNER_SYS;            /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                 /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_00,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for system memory 4 */
    tMcb.wStart    = VIR_BEG_SYS4_EE;      /* Set start of block */
    tMcb.wLength   = VIR_SYS4_SIZE;        /* Set size of block  */
    tMcb.ucAccess  = ACC_APP;              /* Set access level   */
    tMcb.ucEnCRC   = FALSE;                /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_SYS;      /* Set memory type   */
    tMcb.ucOwner   = OWNER_SYS;            /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                 /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_01,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for system memory 5 */
    tMcb.wStart    = VIR_BEG_SYS5_EE;      /* Set start of block */
    tMcb.wLength   = VIR_SYS5_SIZE;        /* Set size of block  */
    tMcb.ucAccess  = ACC_APP;              /* Set access level   */
    tMcb.ucEnCRC   = FALSE;                /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_SYS;      /* Set memory type   */
    tMcb.ucOwner   = OWNER_SYS;            /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                 /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_02,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for system memory 7 */
    tMcb.wStart    = VIR_BEG_SYS7_EE;      /* Set start of block */
    tMcb.wLength   = VIR_SYS7_SIZE;        /* Set size of block  */
    tMcb.ucAccess  = ACC_APP;              /* Set access level   */
    tMcb.ucEnCRC   = FALSE;                /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_SYS;      /* Set memory type   */
    tMcb.ucOwner   = OWNER_SYS;            /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                 /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_03,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for system memory address table. */
    tMcb.wStart    = APP_ADDR_TABLE_REF;      /* Set start of block */
    tMcb.wLength   = ADDR_TABLE_SIZE;         /* Set size of block  */
    tMcb.ucAccess  = ACC_ADDR;                /* Set access level   */
    tMcb.ucEnCRC   = TRUE;                    /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_USER;        /* Set memory type   */
    tMcb.ucOwner   = OWNER_ADDR;              /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                    /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_04,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for system memory association table. */
    tMcb.wStart    = APP_ASSOC_TABLE_REF;      /* Set start of block */
    tMcb.wLength   = ASSOC_TABLE_SIZE;         /* Set size of block  */
    tMcb.ucAccess  = ACC_ASSOC;                /* Set access level   */
    tMcb.ucEnCRC   = TRUE;                     /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_USER;         /* Set memory type   */
    tMcb.ucOwner   = OWNER_ASSOC;              /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                     /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_05,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for system RAM. */
    tMcb.wStart    = APP_RAM_BEGIN;            /* Set start of block */
    tMcb.wLength   = APP_RAM_SIZE;             /* Set size of block  */
    tMcb.ucAccess  = ACC_APP;                  /* Set access level   */
    tMcb.ucEnCRC   = FALSE;                    /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_HIRAM;           /* Set memory type   */
    tMcb.ucOwner   = OWNER_APP;                /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                     /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_06,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));
    
    /* Re-write MCB for Memory1. */
    tMcb.wStart    = APP_MEM1_REF;            /* Set start of block */
    tMcb.wLength   = APP_MEM1_SIZE;           /* Set size of block  */
    tMcb.ucAccess  = ACC_APP;                 /* Set access level   */
    tMcb.ucEnCRC   = TRUE;                    /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_USER;        /* Set memory type   */
    tMcb.ucOwner   = OWNER_APP;               /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                    /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_07,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for Memory2. */
    tMcb.wStart    = APP_MEM2_REF;            /* Set start of block */
    tMcb.wLength   = APP_MEM2_SIZE;           /* Set size of block  */
    tMcb.ucAccess  = ACC_PAR;                 /* Set access level   */
    tMcb.ucEnCRC   = FALSE;                   /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_USER;        /* Set memory type   */
    tMcb.ucOwner   = OWNER_APP;               /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                    /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_08,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for Memory3. */
    tMcb.wStart    = 0x0000FFFF;              /* Set start of block */
    tMcb.wLength   = 0xFFFF;                  /* Set size of block  */
    tMcb.ucAccess  = 0xFF;                    /* Set access level   */
    tMcb.ucEnCRC   = TRUE;                    /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_USER;        /* Set memory type   */
    tMcb.ucOwner   = OWNER_FREE;              /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                    /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_09,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for Memory4. */
    tMcb.wStart    = 0x0000FFFF;              /* Set start of block */
    tMcb.wLength   = 0xFFFF;                  /* Set size of block  */
    tMcb.ucAccess  = 0xFF;                    /* Set access level   */
    tMcb.ucEnCRC   = TRUE;                    /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_USER;        /* Set memory type   */
    tMcb.ucOwner   = OWNER_FREE;              /* Set owner of block */
    tMcb.wCrc      = 0xFF;                    /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_10,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* Re-write MCB for Memory5. */
    tMcb.wStart    = 0x0000FFFF;              /* Set start of block */
    tMcb.wLength   = 0xFFFF;                  /* Set size of block  */
    tMcb.ucAccess  = 0xFF;                    /* Set access level   */
    tMcb.ucEnCRC   = TRUE;                    /* Disable CRC check */
    tMcb.ucMemType = MEM_TYPE_EE_USER;        /* Set memory type   */
    tMcb.ucOwner   = OWNER_FREE;              /* Set owner of block */
    tMcb.wCrc      = 0xFFFF;                    /* Set checksum (unused) */
    KnxMem_WriteData(VIR_MCB_11,(BYTE*)(&tMcb),sizeof(T_KNXMEM_MCB));

    /* clear all load controls. */
    for(wIndex = VIR_BEG_SYS7_EE; wIndex <= VIR_END_SYS7_EE; wIndex++)
    {
        KnxMem_WriteByte(wIndex, 0x00);
    }
    /* write additional data. */
    KnxMem_WriteByte(VIR_APP_MAIN,HI_BYTE(APP_HEADER_MAIN_REF));
    KnxMem_WriteByte(VIR_APP_MAIN+1,LOW_BYTE(APP_HEADER_MAIN_REF));
    KnxMem_WriteByte(VIR_INTOB_TAB_REF,HI_BYTE(USER_INTOBJ_TABLE_REF));
    KnxMem_WriteByte(VIR_INTOB_TAB_REF+1,LOW_BYTE(USER_INTOBJ_TABLE_REF));
    KnxMem_WriteByte(VIR_INTOB_COUNT,HI_BYTE(USER_OBJECT_COUNT));
    for(wIndex=0;wIndex<22;wIndex++)
    {
        KnxMem_WriteByte(VIR_KNX_PROT+wIndex,g_RecoverData[wIndex]);
    }
    /* complete the data write. */
    KnxMem_WriteBufferFlush();
    /* clear record table. */
    RecTable_ClearTable();
    /* set media status. */
    KnxMem_SetVirtMediaStatus(VIR_MEM_STATE_NEW);
    /* reset and wait for reset. */
    Knx_Internal_ResetDev();

    return;
}

/**************************************************************************
* FunctionName:VOID KnxMem_InitChecksum(VOID)
* FunctionDescription: initialize the checksum.
* InputParameterno.
* OutputParameterno.
* Return Value：VOID.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
VOID KnxMem_InitChecksum(VOID)
{
    KnxMem_SetChecksum(OBJECT_ADDR_TABLE_ID);       /* Set checksum of addr. table object  */
    KnxMem_SetChecksum(OBJECT_ASSOC_TABLE_ID);      /* Set checksum of assoc. table object */
    KnxMem_SetChecksum(OBJECT_APPLICATION_ID);      /* Set checksum of application object  */
    /* Force writing to flash. */
    KnxMem_WriteBufferFlush();
    
    return;
}

/**************************************************************************
* FunctionName:BOOL KnxMem_InitMedia(BYTE ucDevNo)
* FunctionDescription: This function is called by main at the begin.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_InitMedia(BYTE ucDevNo)
{
    BYTE ucMemState;

    sg_ucDevNo = ucDevNo;

    ucMemState = KnxMem_GetVirtFlashStatus();
    /* check the state. */
    switch(ucMemState)
    {
        case VIR_MEM_STATE_NEW:
        {
            /* new,we calculate the checksum. */
            KnxMem_InitChecksum();
            return TRUE;
        }
        case VIR_MEM_STATE_OK:
        {
            return TRUE;
        }
        case VIR_MEM_STATE_CLEAR:
        default:
        {
            KnxMem_MediaRecoveDefault();
        }
    }
    
    return FALSE;
}



/* end of file. */

