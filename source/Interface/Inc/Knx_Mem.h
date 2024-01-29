/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Mem.h
* FileIdentifier：None
* Abstract ：协议memory处理头文件。
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


#ifndef _KNX_MEM_H_
#define _KNX_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Flash state define.we use these defines to check if the system start the first time. */
#define VIR_MEM_STATE_CLEAR          0xFF    /* State after erasing                 */
#define VIR_MEM_STATE_NEW            0xFE    /* State after loading EEPROM via JTAG */
#define VIR_MEM_STATE_OK             0xFC    /* State after KnxMem_InitEeprom()     */
#define VIR_MEM_STATE_WRITING        0xF0    /* Data writing is in progress         */
#define VIR_MEM_STATE_ERROR          0x00    /* Used for return value               */

#define NOT_PROGRAMMING              0x00    /* No programming in progress          */
#define ADDR_IN_PROG_AREA            0x01    /* Programming in progress but address in prog. area */
#define ADDR_OUT_OF_PROG_AREA        0x02    /* Programming in progress and address out of prog. area.*/
#define ADDR_OUT_OF_EEPROM           0x03    /* Error: Address is not valid eeprom space              */

#define GET_FLASH_PAGE(dwAddr)       (GET_REAL_OF_VIR(dwAddr)&(~(FLASH_PAGE_SIZE-1)))


/* Defines for communication object descriptor tabe.*/
#define COTAB_POS_COUNT              0    /* The count of communication objects */
#define COTAB_POS_RAMFLAGS_REF       1    /* The pointer to RAM flags (2 bytes) */
#define COTAB_POS_FIRSTVAL_REF       3    /* Start of the first object desc.    */

/* Defines for a single communication object descriptor */
#define CO_POS_VALUE_REF             0    /* The value pointer of the co (2 bytes)    */
#define CO_POS_CONFIG                2    /* The config byte of the co                */
#define CO_POS_TYPE                  3    /* The type byte of the co                  */
#define CO_DESC_SIZE                 4    /* The count of bytes for one co descriptor */

/* define for set parameter by user. */
#define PARID_RESTART_COUNT            0         /* Parameter ID for restart count (BIM112) */
#define PARID_ROUTING_COUNT            1         /* Parameter ID for routing count (BIM112) */
#define PARID_DEL_USER_MSG             11        /* Parameter ID for delete user messages   */
#define PARID_TELRATE_LIMIT            12        /* Parameter ID for tel. limitation rate   */

/****************************************************
*   结构名：T_RAM_DESC
*   描述：  KNX virtual RAM discription structure.
*   参数：  
            WORD16  wStart         Start of the block in virtual address space
            WORD16  wLength        Length of the block in bytes
            BYTE    *pucData       Pointer to block in physical address space
*   作者：  Jackson
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    WORDPTR wStart;         /* Start of the block in virtual address space */
    WORD16  wLength;        /* Length of the block in bytes */
    BYTE    *pucData;       /* Pointer to block in physical address space */
}T_RAM_DESC;


/**************************************************************************
* FunctionName:BYTE API_KnxMem_GetByte(WORDPTR dwAddr)
* FunctionDescription: get a byte data from the given virtual address.
* InputParameterWORDPTR dwAddr:source address.
* OutputParameterno.
* Return Value：memory data.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BYTE KnxMem_GetByte(WORDPTR dwAddr);

/**************************************************************************
* FunctionName:WORD16 API_KnxMem_GetWord(WORDPTR dwAddrHi)
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
WORD16 KnxMem_GetWord(WORDPTR dwAddrHi);

/**************************************************************************
* FunctionName:BOOL API_KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData)
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
BOOL KnxMem_ReadByte(WORDPTR dwAddr, BYTE *pucData);

/**************************************************************************
* FunctionName:BOOL API_KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData)
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
BOOL KnxMem_WriteByte(WORDPTR dwAddr,BYTE ucData);

/**************************************************************************
* FunctionName:BOOL API_KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData)
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
BOOL KnxMem_WriteWord(WORDPTR dwAddrHi, WORD16 wData);

/**************************************************************************
* FunctionName:BOOL API_KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount)
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
BOOL KnxMem_WriteData(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount);

/**************************************************************************
* FunctionName:BOOL API_KnxMem_WriteFinished(VOID)
* FunctionDescription: This function is called to force writing data to the flash.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_WriteFinished(VOID);

/**********************************************************************************
* FunctionName:BYTE API_KnxMem_GetCoCount(VOID)
* FunctionDescription: This function returns the number of communication objects.
* InputParameterWORD16 wPhysAddr : physical address.
* OutputParameterno.
* Return Value：BYTE :communication object number.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BYTE KnxMem_GetCoCount(VOID);

/**************************************************************************
* FunctionName:BOOL API_KnxMem_SetChecksum(BYTE ucObjIndex)
* FunctionDescription: This function writes the checksum for the given memory block.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL KnxMem_SetChecksum(BYTE ucObjIndex);

/**********************************************************************************
* FunctionName:BOOL API_KnxMem_SetParam(BYTE ucItem, BYTE ucValue)
* FunctionDescription: This function may be called by application to set some system parameters.
* InputParameterBYTE ucItem : communication object N.
            BYTE ucValue: 
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
BOOL KnxMem_SetParam(BYTE ucItem, BYTE ucValue);

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
VOID KnxMem_MediaRecoveDefault(VOID);

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
WORDPTR KnxMem_GetCoValueRef(BYTE ucCoNo);

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
BYTE KnxMem_GetCoValueType(BYTE ucCoNo);

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
BYTE KnxMem_GetCoConfigByte(BYTE ucCoNo);

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
BOOL KnxMem_InitMedia(BYTE ucDevNo);

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
BOOL KnxMem_VirRamInit(VOID);

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
VOID KnxMem_Init(VOID);

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
BYTE KnxMem_GetByteEx(WORDPTR dwAddr);

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
BYTE* KnxMem_GetCoRamFlags(VOID);

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
BYTE KnxMem_GetSendConnNo(BYTE ucCoNo);

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
BYTE KnxMem_GetAssocCount(VOID);

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
BOOL KnxMem_GetAssoc(BYTE ucIndex, BYTE *pucConnNo, BYTE *pucCoNo);

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
BYTE KnxMem_GetAlTelRateLimit(void);

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
BOOL KnxMem_SetPhysAddr(WORD16 wPhysAddr);

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
BOOL KnxMem_WriteMediaByte(WORDPTR dwAddr,BYTE ucData);

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
BOOL KnxMem_GetDelUserMsg(void);

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
BYTE KnxMem_GetNlRoutingCount(VOID);

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
BOOL KnxMem_CheckChecksum(VOID);

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
BYTE KnxMem_GetConnNo(WORD16 wGrpAddr);









#ifdef __cplusplus
}
#endif

#endif /* _KNX_MEM_H_ */


/* end of file. */

