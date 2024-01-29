/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：App_Api.c
* FileIdentifier：None
* Abstract ：Knx application API file.
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
#include "Sw_common.h"
#include "Buffer.h"
#include "Hardware.h"

#include "Knx_Mem.h"
#include "Knx_Prop.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "mem_malloc.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "Knx_InternalData.h"
#include "Knx_InternalApp.h"
#include "Knx_Timer.h"
#include "Knx_AlApp.h"
#include "Knx_AlMgm.h"
#include "Knx_Program.h"
#include "knx_chip.h"
#include "Knx_M0705_Ll.h"
#include "Knx_Auth.h"
#include "Knx_LoadCtrl.h"
#include "Knx_Run.h"
#include "Knx_Msg.h"
#include "Mem_malloc.h"


/* we should allocate an 512 bytes ROM area for below API. */

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
#pragma location = (KNX_API_START_VIR_ADDR + 0*MCU_SIZE)
__root VOID (*const API_Knx_UserAppHandler_Set)(VOID *pfHandler,BYTE ucHandlerType) = Knx_UserAppHandler_Set;

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
#pragma location = (KNX_API_START_VIR_ADDR + 1*MCU_SIZE)
__root VOID (*const API_KnxTm_TimerInit)(BYTE ucDevNo) = KnxTm_TimerInit;

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
#pragma location = (KNX_API_START_VIR_ADDR + 2*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetTimeMs)(VOID) = KnxTm_GetTimeMs;

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
#pragma location = (KNX_API_START_VIR_ADDR + 3*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetDelayMs)(WORD32 dwOldTime) = KnxTm_GetDelayMs;

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
#pragma location = (KNX_API_START_VIR_ADDR + 4*MCU_SIZE)
__root VOID (*const API_KnxTm_UpdateCycle)(VOID) = KnxTm_UpdateCycle;

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
#pragma location = (KNX_API_START_VIR_ADDR + 5*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetCycleTimeMs)(VOID) = KnxTm_GetCycleTimeMs;

/**************************************************************************
* FunctionName:WORD32 API_KnxTm_GetCycleCount(VOID)
* FunctionDescription:  获取循环周期次数。
* InputParameter None。
* OutputParameter None。
* Return Value： 循环次数（0~0xFFFFFFFF）
* Other Description: 需要在循环中调用KnxTm_UpdateCycle函数更新计数。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/25       V1.0                    Create
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 6*MCU_SIZE)
__root WORD32 (*const API_KnxTm_GetCycleCount)(VOID) = KnxTm_GetCycleCount;


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
#pragma location = (KNX_API_START_VIR_ADDR + 7*MCU_SIZE)
__root BYTE (*const API_KnxAl_GetCoBufLength)(BYTE ucCoNo) = KnxAl_GetCoBufferLength;

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
#pragma location = (KNX_API_START_VIR_ADDR + 8*MCU_SIZE)
__root BOOL (*const API_KnxAl_GetCoValue)(BYTE ucCoNo,BYTE *pucBuffer) = KnxAl_GetCoValue;

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
#pragma location = (KNX_API_START_VIR_ADDR + 9*MCU_SIZE)
__root BOOL (*const API_KnxAl_SetCoValue)(BYTE ucCoNo,BYTE *pucBuffer) = KnxAl_SetCoValue;

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
#pragma location = (KNX_API_START_VIR_ADDR + 10*MCU_SIZE)
__root BOOL (*const API_KnxAl_GetUpdatedCo)(BYTE *pucCoNo) = KnxAl_GetUpdatedCo;

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
#pragma location = (KNX_API_START_VIR_ADDR + 11*MCU_SIZE)
__root BYTE (*const API_KnxAl_GetRamFlags)(BYTE ucCoNo) = KnxAl_GetRamFlags;

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
#pragma location = (KNX_API_START_VIR_ADDR + 12*MCU_SIZE)
__root BOOL (*const API_KnxAl_SetRamFlags)(BYTE ucCoNo, BYTE ucFlags) = KnxAl_SetRamFlags;

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
#pragma location = (KNX_API_START_VIR_ADDR + 13*MCU_SIZE)
__root BOOL (*const API_KnxAl_RequestValueWrite)(BYTE ucCoNo) = KnxAl_RequestValueWrite;

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
#pragma location = (KNX_API_START_VIR_ADDR + 14*MCU_SIZE)
__root BOOL (*const API_KnxAl_RequestValueRead)(BYTE ucCoNo) = KnxAl_RequestValueRead;

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
#pragma location = (KNX_API_START_VIR_ADDR + 15*MCU_SIZE)
__root VOID (*const API_Knx_AlMgmInit)(VOID) = Knx_AlMgmInit;

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
#pragma location = (KNX_API_START_VIR_ADDR + 16*MCU_SIZE)
__root VOID (*const API_KnxMem_Init)(VOID) = KnxMem_Init;

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
#pragma location = (KNX_API_START_VIR_ADDR + 17*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetByte)(WORDPTR dwAddr) = KnxMem_GetByte;

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
#pragma location = (KNX_API_START_VIR_ADDR + 18*MCU_SIZE)
__root WORD16 (*const API_KnxMem_GetWord)(WORDPTR dwAddrHi) = KnxMem_GetWord;

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
#pragma location = (KNX_API_START_VIR_ADDR + 19*MCU_SIZE)
__root BOOL (*const API_KnxMem_ReadByte)(WORDPTR dwAddr, BYTE *pucData) = KnxMem_ReadByte;

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
#pragma location = (KNX_API_START_VIR_ADDR + 20*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteByte)(WORDPTR dwAddr,BYTE ucData) = KnxMem_WriteByte;

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
#pragma location = (KNX_API_START_VIR_ADDR + 21*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteWord)(WORDPTR dwAddrHi, WORD16 wData) = KnxMem_WriteWord;

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
#pragma location = (KNX_API_START_VIR_ADDR + 22*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteData)(WORDPTR dwAddr, BYTE *pucData, BYTE ucCount) = KnxMem_WriteData;

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
#pragma location = (KNX_API_START_VIR_ADDR + 23*MCU_SIZE)
__root BOOL (*const API_KnxMem_WriteFinished)(VOID) = KnxMem_WriteFinished;

/**********************************************************************************
* FunctionName:BYTE API_KnxMem_GetCoCount(VOID)
* FunctionDescription: This function returns the number of communication objects.
* InputParameterno.
* OutputParameterno.
* Return Value：BYTE :communication object number.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ---------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***********************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 24*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetCoCount)(VOID) = KnxMem_GetCoCount;

/**************************************************************************
* FunctionName:BOOL API_KnxMem_SetChecksum(BYTE ucObjIndex)
* FunctionDescription: This function writes the checksum for the given memory block.
* InputParameterucObjIndex:interface object
                          OBJECT_ADDR_TABLE_ID
                          OBJECT_ASSOC_TABLE_ID
                          OBJECT_APPLICATION_ID
* OutputParameterno.
* Return Value：TREU/FLASE
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 25*MCU_SIZE)
__root BOOL (*const API_KnxMem_SetChecksum)(BYTE ucObjIndex) = KnxMem_SetChecksum;

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
#pragma location = (KNX_API_START_VIR_ADDR + 26*MCU_SIZE)
__root BOOL (*const API_KnxMem_SetParam)(BYTE ucItem, BYTE ucValue) = KnxMem_SetParam;

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
#pragma location = (KNX_API_START_VIR_ADDR + 27*MCU_SIZE)
__root VOID (*const API_KnxMem_MediaRecoveDefault)(VOID) = KnxMem_MediaRecoveDefault;

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
#pragma location = (KNX_API_START_VIR_ADDR + 28*MCU_SIZE)
__root WORDPTR (*const API_KnxMem_GetCoValueRef)(BYTE ucCoNo) = KnxMem_GetCoValueRef;

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
#pragma location = (KNX_API_START_VIR_ADDR + 29*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetCoValueType)(BYTE ucCoNo) = KnxMem_GetCoValueType;

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
#pragma location = (KNX_API_START_VIR_ADDR + 30*MCU_SIZE)
__root BYTE (*const API_KnxMem_GetCoConfigByte)(BYTE ucCoNo) = KnxMem_GetCoConfigByte;

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
#pragma location = (KNX_API_START_VIR_ADDR + 31*MCU_SIZE)
__root BOOL (*const API_KnxMem_InitMedia)(BYTE ucDevNo) = KnxMem_InitMedia;

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
#pragma location = (KNX_API_START_VIR_ADDR + 32*MCU_SIZE)
__root BOOL (*const API_KnxMem_VirRamInit)(VOID) = KnxMem_VirRamInit;


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
#pragma location = (KNX_API_START_VIR_ADDR + 33*MCU_SIZE)
__root VOID (*const API_Knx_GetProgKey)(VOID) = Knx_GetProgKey;

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
#pragma location = (KNX_API_START_VIR_ADDR + 34*MCU_SIZE)
__root BYTE (*const API_Knx_GetPrgLedState)(VOID) = Knx_GetPrgLedState;

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
#pragma location = (KNX_API_START_VIR_ADDR + 35*MCU_SIZE)
__root VOID (*const API_Knx_SetPrgLed)(VOID) = Knx_SetPrgLed;


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
#pragma location = (KNX_API_START_VIR_ADDR + 36*MCU_SIZE)
__root VOID (*const API_Knx_SetPrgLedState)(BYTE ucState) = Knx_SetPrgLedState;

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
#pragma location = (KNX_API_START_VIR_ADDR + 39*MCU_SIZE)
__root VOID *(*const API_RecTable_GetRecord)(WORD16 wRecordId) = RecTable_GetRecord;

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
#pragma location = (KNX_API_START_VIR_ADDR + 40*MCU_SIZE)
__root BOOL (*const API_RecTable_SetRecord)(VOID *ptRec2Write) = RecTable_SetRecord;

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
#pragma location = (KNX_API_START_VIR_ADDR + 41*MCU_SIZE)
__root BOOL (*const API_RecTable_DeleteRecord)(WORD16 wRecordId) = RecTable_DeleteRecord;

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
#pragma location = (KNX_API_START_VIR_ADDR + 42*MCU_SIZE)
__root BOOL (*const API_RecTable_DeleteAppRecords)(void) = RecTable_DeleteAppRecords;

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
#pragma location = (KNX_API_START_VIR_ADDR + 43*MCU_SIZE)
__root VOID (*const API_RecTable_OpInit)(BYTE ucDevNo,BYTE ucWrtSize) = RecTable_OpInit;

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
#pragma location = (KNX_API_START_VIR_ADDR + 44*MCU_SIZE)
__root BOOL (*const API_RecTable_GetByte)(WORD16 wRecordID, BYTE *pucData) = RecTable_GetByte;

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
#pragma location = (KNX_API_START_VIR_ADDR + 45*MCU_SIZE)
__root BOOL (*const API_RecTable_SetByte)(WORD16 wRecordID, BYTE ucData) = RecTable_SetByte;

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
#pragma location = (KNX_API_START_VIR_ADDR + 46*MCU_SIZE)
__root BOOL (*const API_RecTable_CleanUpRecord)(T_RECORD *ptRecord) = RecTable_CleanUpRecord;

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
#pragma location = (KNX_API_START_VIR_ADDR + 47*MCU_SIZE)
__root BOOL (*const API_RecTable_CleanUpTable)(VOID) = RecTable_CleanUpTable;

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
#pragma location = (KNX_API_START_VIR_ADDR + 48*MCU_SIZE)
__root BOOL (*const API_RecTable_ClearTable)(void) = RecTable_ClearTable;

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
#pragma location = (KNX_API_START_VIR_ADDR + 49*MCU_SIZE)
__root VOID (*const API_Knx_SetRunState)(BYTE ucControl) = Knx_SetRunState;

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
#pragma location = (KNX_API_START_VIR_ADDR + 50*MCU_SIZE)
__root BYTE (*const API_Knx_GetRunStateEx)(VOID) = Knx_GetRunStateEx;

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
#pragma location = (KNX_API_START_VIR_ADDR + 51*MCU_SIZE)
__root VOID (*const API_Knx_RunProcess)(VOID) = Knx_RunProcess;

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
#pragma location = (KNX_API_START_VIR_ADDR + 52*MCU_SIZE)
__root WORD32 (*const API_KnxLl_DevReg)(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum) = KnxLl_DevReg;

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
#pragma location = (KNX_API_START_VIR_ADDR + 53*MCU_SIZE)
__root VOID (*const API_Knx_MsgInit)(VOID) = Knx_MsgInit;

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
#pragma location = (KNX_API_START_VIR_ADDR + 54*MCU_SIZE)
__root VOID (*const API_Knx_MsgProcess)(VOID) = Knx_MsgProcess;

/**************************************************************************************************************
* FunctionName: WORD32 KnxLl_Init(WORD16 *pwKnxBitTimArry,BYTE ucBufferNum,BYTE ucBufferSize)
* FunctionDescription:  initialize the link device.
* InputParameter 
* OutputParameter 
* Return Value： SW_OK ：操作成功
             SW_ERR：操作失败
* Other Description: 
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************************************************/
#pragma location = (KNX_API_START_VIR_ADDR + 55*MCU_SIZE)
__root WORD32 (*const API_KnxLl_Init)(BYTE ucBufferNum,BYTE ucBufferSize) = KnxLl_Init;


/****************************************/
/*********** system memory op. **********/
/****************************************/

#pragma location = (KNX_API_START_VIR_ADDR + 64*MCU_SIZE)
__root VOID *(*const API_malloc)(unsigned short wLen) = mem_malloc;

#pragma location = (KNX_API_START_VIR_ADDR + 65*MCU_SIZE)
__root VOID (*const API_free)(void *p) = mem_free;

#pragma location = (KNX_API_START_VIR_ADDR + 66*MCU_SIZE)
__root VOID *(*const API_realloc)(void *p,unsigned short wLen) = mem_realloc;

#pragma location = (KNX_API_START_VIR_ADDR + 67*MCU_SIZE)
__root VOID (*const API_memset)(void *p,unsigned char byte,unsigned short wLen) = mem_memset;


/* end of file. */

