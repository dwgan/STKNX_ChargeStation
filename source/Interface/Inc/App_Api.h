/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：App_Api.h
* FileIdentifier：None
* Abstract ：Knx application API header file.
* Other Description：
* Current Version：V1.00
* Author：Jackson
* Completed Date：2014年3月18日
*    
* Modified History1：
*        Modified Date：2014年3月18日
*        Version Number：V1.00
*        Modified Person：Jackson
*        Modified part：Create文件
******************************************************************************/


#ifndef _APP_API_H_
#define _APP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#define KNX_API_START_VIR_ADDR         0x0800FE80


/*****************************************************************************************************************
* FunctionName:VOID API_Knx_UserAppHandler_Set(VOID *pfHandler,BYTE ucHandlerType)
* FunctionDescription: application set handler relate to the device design.
* InputParameterAPP_HANDLER pfHandler:application handler.
            BYTE ucHandlerType   :handler type.
                 APP_HANDLER_MAIN            0x01           application entry
                 APP_HANDLER_INIT            0x02           application initialize entry.
                 APP_HANDLER_SAVE            0x03           application save handling entry.
                 APP_HANDLER_BUS_SAVE        0x04           application save handling when bus voltage down.
                 APP_HANDLER_POWER_SAVE      0x05           application save handling when power supply down.
                 APP_HANDLER_WDG_RESET       0x06           application reset watchdog entry.
                 APP_HANDLER_RESET_CPU       0x07           CPU reset entry.
                 APP_HANDLER_PRGM_LED_OFF    0x08           OFF program LED entry.
                 APP_HANDLER_PRGM_LED_ON     0x09           light program LED entry.
                 APP_HANDLER_PRGM_KEY        0x0a           program key check entry.
                 APP_HANDLER_BUS_POWER_CHECK 0x0b           bus power check entry.
                 APP_HANDLER_ADC_OP          0x0c           adc operation entry. 
* OutputParameterno.
* Return Value：no.
* Other Description:application realize the design in self source files.these handler will be used by KNX protocol
            stack internally.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                  Create
********************************************************************************************************************/
extern VOID (*const API_Knx_UserAppHandler_Set)(VOID *pfHandler,BYTE ucHandlerType);

/****************************************/
/**************** Knx time op. ************/
/****************************************/

/**************************************************************************
* FunctionName:VOID API_KnxTm_TimerInit(BYTE ucDevNo)
* FunctionDescription: KNX定时器初始化接口，定时器1ms。
* InputParameterBYTE ucDevNo:device logical number.
* OutputParameterno.
* Return Value：no.
* Other Description:通过api提供给外部使用。定时器驱动通过注册方式注册到KNX定时器处理
            进行工作。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      Create 
**************************************************************************/
extern VOID (*const API_KnxTm_TimerInit)(BYTE ucDevNo);

/**************************************************************************
* FunctionName:WORD32 API_KnxTm_GetTimeMs(VOID)
* FunctionDescription: 获取当前计时毫秒数。
* InputParameter None。
* OutputParameter None。
* Return Value： 当前毫秒数：0-0xFFFFFFFF。
* Other Description: None
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                      Create 
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetTimeMs)(VOID);

/**************************************************************************
* FunctionName:WORD32 API_KnxTm_GetDelayMs(WORD32 dwOldTime)
* FunctionDescription: 获取给定时间跟当前时间的时差（毫秒）。
* InputParameter WORD16 wOldTime：给定老时间。
* OutputParameter None。
* Return Value： 时差，毫秒：0-0xFFFF。
* Other Description: None
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    Create 
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetDelayMs)(WORD32 dwOldTime);

/**************************************************************************
* FunctionName:VOID API_KnxTm_UpdateCycle(VOID)
* FunctionDescription:  更新周期时间和计数。
* InputParameter None。
* OutputParameter None。
* Return Value： None。
* Other Description: None。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    Create
**************************************************************************/
extern VOID (*const API_KnxTm_UpdateCycle)(VOID);

/**************************************************************************
* FunctionName:WORD16 API_KnxTm_GetCycleTimeMs(VOID)
* FunctionDescription:  获取循环周期时间（毫秒）。
* InputParameter None。
* OutputParameter None。
* Return Value： 时间值（毫秒，0~0xFFFF）
* Other Description: 需要在循环中调用KnxTm_UpdateCycle函数更新时间。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                        Create
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetCycleTimeMs)(VOID);

/**************************************************************************
* FunctionName:WORD32 API_KnxTm_GetCycleCount(VOID)
* FunctionDescription:  获取循环周期次数。
* InputParameter None。
* OutputParameter None。
* Return Value： 循环次数（0~0xFFFF）
* Other Description: 需要在循环中调用KnxTm_UpdateCycle函数更新计数。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    Create
**************************************************************************/
extern WORD32 (*const API_KnxTm_GetCycleCount)(VOID);


/****************************************/
/**************** Knx co. op. ************/
/****************************************/

/**************************************************************************************************************
* FunctionName:BYTE API_KnxAl_GetCoBufferLength(BYTE ucCoNo)
* FunctionDescription: This function retrieves the buffer length used by the given communication object.
* InputParameterBYTE ucCoNo :communication object No.
* OutputParameterno.
* Return Value：buffer length.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BYTE (*const API_KnxAl_GetCoBufferLength)(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BOOL API_KnxAl_GetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* FunctionDescription: This function is used by application to retrieve the value of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :data buffer pointer.
* OutputParameterBYTE *pucBuffer :communication object data.
* Return Value：TRUE / FALSE.
* Other Description:This function will be a API function used by the application.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_GetCoValue)(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* FunctionName:BOOL API_KnxAl_SetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* FunctionDescription: This function is used by application to set the value of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :data buffer pointer.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:(1)This function will be a API function used by the application.
            (2)To initiate a transmission of the new value KnxAl_RequestValueWrite(para) has to be called in addition.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_SetCoValue)(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* FunctionName:BOOL API_KnxAl_GetUpdatedCo(BYTE *pucCoNo)
* FunctionDescription: This function is used by the application to retrieve the number of the next communication object
            updated by external event.
* InputParameterBYTE *pucCoNo:Co.objet No pointer.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_GetUpdatedCo)(BYTE *pucCoNo);

/**************************************************************************************************************
* FunctionName:BYTE API_KnxAl_GetRamFlags(BYTE ucCoNo)
* FunctionDescription: This function is used by application to retrieve the status of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
* OutputParameterno.
* Return Value：BYTE : the status of the communication object.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BYTE (*const API_KnxAl_GetRamFlags)(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BOOL API_KnxAl_SetRamFlags(BYTE ucCoNo, BYTE ucFlags)
* FunctionDescription: This function is used by application to set the status of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_SetRamFlags)(BYTE ucCoNo, BYTE ucFlags);

/**************************************************************************************************************
* FunctionName:BOOL API_KnxAl_RequestValueWrite(BYTE ucCoNo)
* FunctionDescription: This function initiates a value write request on the given communication object.
* InputParameterBYTE ucCoNo:Co.objet No.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:The system will transmitts the current value of the given communication object.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_RequestValueWrite)(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BOOL API_KnxAl_RequestValueRead(BYTE ucCoNo)
* FunctionDescription: This function initiates a value read request on the given communication object.
* InputParameterBYTE ucCoNo:Co.objet No.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:Attention: The response by remote device can only be received if the "Update on response" flag is set
            for this communication object.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BOOL (*const API_KnxAl_RequestValueRead)(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:VOID Knx_AlMgmInit(VOID)
* FunctionDescription: KNX application layer management initialize。
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_AlMgmInit)(VOID);

/****************************************/
/*********** Knx memory data op. **********/
/****************************************/

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
extern VOID (*const API_KnxMem_Init)(VOID);

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
extern BYTE (*const API_KnxMem_GetByte)(WORDPTR dwAddr);

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
extern WORD16 (*const API_KnxMem_GetWord)(WORDPTR dwAddrHi);

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
extern BOOL (*const API_KnxMem_ReadByte)(WORDPTR dwAddr, BYTE *pucData);

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
extern BOOL (*const API_KnxMem_WriteByte)(WORDPTR dwAddr,BYTE ucData);

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
extern BOOL (*const API_KnxMem_WriteWord)(WORDPTR dwAddrHi, WORD16 wData);

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
extern BOOL (*const API_KnxMem_WriteData)(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount);

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
extern BOOL (*const API_KnxMem_WriteFinished)(VOID);

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
extern BYTE (*const API_KnxMem_GetCoCount)(VOID);

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
extern BOOL (*const API_KnxMem_SetChecksum)(BYTE ucObjIndex);

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
extern BOOL (*const API_KnxMem_SetParam)(BYTE ucItem, BYTE ucValue);

/**************************************************************************
* FunctionName:VOID KnxMem_MediaRecoveDefault(VOID)
* FunctionDescription: This function sets the parameter area in flash to the default.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:this function will be called at the start.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern VOID (*const API_KnxMem_MediaRecoveDefault)(VOID);

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
extern WORDPTR (*const API_KnxMem_GetCoValueRef)(BYTE ucCoNo);

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
extern BYTE (*const API_KnxMem_GetCoValueType)(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BYTE API_KnxAl_GetCoBufferLength(BYTE ucCoNo)
* FunctionDescription: This function retrieves the buffer length used by the given communication object.
* InputParameterBYTE ucCoNo :communication object No.
* OutputParameterno.
* Return Value：buffer length.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BYTE (*const API_KnxAl_GetCoBufLength)(BYTE ucCoNo);

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
extern BYTE (*const API_KnxMem_GetCoConfigByte)(BYTE ucCoNo);

/**************************************************************************
* FunctionName:BOOL KnxMem_InitMedia(VOID)
* FunctionDescription: This function is called by main at the begin.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_KnxMem_InitMedia)(BYTE ucDevNo);

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
extern BOOL (*const API_KnxMem_VirRamInit)(VOID);


/****************************************/
/*********** Knx program led&key op. **********/
/****************************************/

/**************************************************************************************************************
* FunctionName:VOID Knx_GetProgKey(VOID)
* FunctionDescription: checks the KNX key state and stores it.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:it should be called periodically.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_GetProgKey)(VOID);

/**************************************************************************************************************
* FunctionName:BYTE API_Knx_GetPrgLedState(VOID)
* FunctionDescription: retrieves the current state of the programming LED.
* InputParameterno.
* OutputParameterBYTE ucState.
* Return Value：KNX_PRGLED_OFF / KNX_PRGLED_ON
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BYTE (*const API_Knx_GetPrgLedState)(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_SetPrgLed(VOID)
* FunctionDescription: sets the state of the KNX programing LED according to the state in g_ucProgramState.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:it should be called periodically.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_SetPrgLed)(VOID);


/**************************************************************************************************************
* FunctionName:VOID API_Knx_SetPrgLedState(BYTE ucState)
* FunctionDescription: set the program LED state to g_ucProgramState.
* InputParameterBYTE ucState.
                                     KNX_PRGLED_OFF
                                     KNX_PRGLED_ON
                                     KNX_PRGLED_BLINK_SLOW
                                     KNX_PRGLED_BLINK_FAST
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_SetPrgLedState)(BYTE ucState);

/**************************************************************************
* FunctionName:VOID *RecTable_GetRecord(WORD16 wRecordId)
* 功能说明：This function searches the requested control record in the 
            record table.
* InputParameterWORD16 wRecordId : record id.
* OutputParameterno.
* Return Value: record pointer.
* Other Description:Attention:the return pointer is physicall address.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern VOID *(*const API_RecTable_GetRecord)(WORD16 wRecordId);

/**************************************************************************
* FunctionName:BOOL RecTable_SetRecord(VOID *ptRec2Write)
* 功能说明：This function searches the record with the given ID 
            in the record table.If possible (only 1->0 to write)
            overwrite this record.else mark found record as invalid
            and use the next free record.
* InputParameterVOID *ptRec2Write : record.
* OutputParameterno.
* Return Value: TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_SetRecord)(VOID *ptRec2Write);

/**************************************************************************
* FunctionName:BOOL RecTable_DeleteRecord(WORD16 wRecordId)
* 功能说明：This function searches the requested control record in the 
            record table and mark it as invalid.
* InputParameterWORD16 wRecordId : record id.
* OutputParameterno.
* Return Value: TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_DeleteRecord)(WORD16 wRecordId);

/**************************************************************************
* FunctionName:BOOL RecTable_DeleteAppRecords(void)
* 功能说明：This function searches all control records used by the application
            process in the record table and mark them as invalid.
* InputParameterno.
* OutputParameterno.
* Return Value: TRUE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_DeleteAppRecords)(void);

/**************************************************************************
* FunctionName:BYTE RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize)
* 功能说明：This function initializes rectalbe.
* InputParameterBYTE ucBytePlace : data saving pattern.
*           BYTE ucWrtSize   : flash programing size of byte.  1.2.4.8
* OutputParameterno.
* Return Value: saving data index.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern VOID (*const API_RecTable_OpInit)(BYTE ucDevNo,BYTE ucWrtSize);

/**************************************************************************
* FunctionName:BOOL RecTable_GetByte(WORD16 wRecordID, BYTE *pucData)
* 功能说明：reading one data byte to pucData from a record's data area.
* InputParameterWORD16 wRecordID : record ID.
            BYTE *pucData    : return data's pointer.
* OutputParameterBYTE *pucData    : return data.
* Return Value: TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_GetByte)(WORD16 wRecordID, BYTE *pucData);

/**************************************************************************
* FunctionName:BOOL RecTable_SetByte(WORD16 wRecordID, BYTE ucData)
* 功能说明：This function writes one data byte ucData to OneByteRecord with 
            wRecordID. modify it, else it creates new record.
* InputParameterWORD16 wRecordID : record ID.
            BYTE ucData      : input data byte.
* OutputParameterno.
* Return Value: TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_SetByte)(WORD16 wRecordID, BYTE ucData);

/**************************************************************************
* FunctionName:BOOL RecTable_CleanUpRecord(T_RECORD *ptRecord)
* 功能说明：This function is used by cleanup to free dirty memory in one 
            byte and one word records.
* InputParameterT_RECORD *ptRecord : record.
* OutputParameterno.
* Return Value: TRUE / FALSE.
* Other Description:we only use byte mode to save the data.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_CleanUpRecord)(T_RECORD *ptRecord);

/**************************************************************************
* FunctionName:BOOL RecTable_CleanUpTable(VOID)
* 功能说明：This function copys all valid records to RAM, erases Record table 
            write back the valid records.
* InputParameterno.
* OutputParameterno.
* Return Value: TRUE / FALSE.
* Other Description:This function can not be called during running.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_CleanUpTable)(VOID);

/**************************************************************************
* FunctionName:BOOL RecTable_ClearTable(void)
* 功能说明：This function erases the complete record table.
* InputParameterno.
* OutputParameterno.
* Return Value: TRUE / FALSE.
* Other Description:This function can not be called during running.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern BOOL (*const API_RecTable_ClearTable)(void);

/**************************************************************************************************************
* FunctionName:VOID Knx_SetRunState(BYTE ucControl)
* FunctionDescription: This function set the run state.
* InputParameterBYTE ucControl:run control byte.
                 RUNCONTROL_NO_OPERATION
                 RUNCONTROL_RESTART
                 RUNCONTROL_STOP
                 RUNCONTROL_HALT
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_SetRunState)(BYTE ucControl);

/**************************************************************************************************************
* FunctionName:BYTE Knx_GetRunStateEx(VOID)
* FunctionDescription: This function get the run state(with save flags).
* InputParameterno.
* OutputParameterno.
* Return Value：run state with save flags.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern BYTE (*const API_Knx_GetRunStateEx)(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_RunProcess(VOID)
* FunctionDescription: managing the application precess.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:It will be called periodically.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_RunProcess)(VOID);

/*******************************************************************************************
* FunctionName:WORD32 KnxLl_DevReg(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum)
* FunctionDescription: 向链路层注册设备，设备逻辑号从0开始，按序进行注册。
* InputParameterBYTE ucLogNo:device's logical No.
            BYTE ucPhyNo:device's physical No.
            WORD16 wRxBufNum:buffer count for receiving.it should be bigger than 0.
            WORD16 wTxBufNum:buffer count for transmitting.it should be bigger than 0.
* OutputParameter
* Return Value：SW_OK ：注册成功；
            SW_ERR：注册失败；
* Other Description:(1)the device logical No. should begin with 0.
            (2)the device should be registered in sequence.
            (3)wBufferNum should set according to the resource of CPU.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
*********************************************************************************************/
extern WORD32 (*const API_KnxLl_DevReg)(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum);

/**************************************************************************************************************
* FunctionName:VOID Knx_MsgInit(VOID)
* FunctionDescription: KNX message handler initialization.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_MsgInit)(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_MsgProcess(VOID)
* FunctionDescription: KNX消息处理总入口。
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
extern VOID (*const API_Knx_MsgProcess)(VOID);

/**************************************************************************
* FunctionName: WORD32 KnxLl_Init(BYTE ucBufferNum,BYTE ucBufferSize)
* FunctionDescription:  initialize the link device.
* InputParameter 
* OutputParameter 
* Return Value： SW_OK ：操作成功
             SW_ERR：操作失败
* Other Description: 
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 (*const API_KnxLl_Init)(BYTE ucBufferNum,BYTE ucBufferSize);


/****************************************/
/*********** system memory op. **********/
/****************************************/

extern VOID *(*const API_malloc)(unsigned short wLen);

extern VOID (*const API_free)(void *p);

extern VOID *(*const API_realloc)(void *p,unsigned short wLen);

extern VOID (*const API_memset)(void *p,unsigned char byte,unsigned short wLen);






#ifdef __cplusplus
}
#endif

#endif /* _APP_API_H_ */

/* end of file. */

