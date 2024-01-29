/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_AlApp.h
* FileIdentifier：None
* Abstract ：knx ip application layer application header file.
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


#ifndef _KNX_ALAPP_H_
#define _KNX_ALAPP_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Value types of communication objects */
#define TYPE_UINT1                   0    /*  1 Bit value  */
#define TYPE_UINT2                   1    /*  2 Bit value  */
#define TYPE_UINT3                   2    /*  3 Bit value  */
#define TYPE_UINT4                   3    /*  4 Bit value  */
#define TYPE_UINT5                   4    /*  5 Bit value  */
#define TYPE_UINT6                   5    /*  6 Bit value  */
#define TYPE_UINT7                   6    /*  7 Bit value  */
#define TYPE_UINT8                   7    /*  1 Byte value */
#define TYPE_UINT16                  8    /*  2 Byte value */
#define TYPE_TIME_DATE               9    /*  3 Byte value */
#define TYPE_FLOAT                  10    /*  4 Byte value */
#define TYPE_DATA6                  11    /*  6 Byte value */
#define TYPE_DOUBLE                 12    /*  8 Byte value */
#define TYPE_DATA10                 13    /* 10 Byte value */
#define TYPE_MAXDATA                14    /* 14 Byte value */

/* Defines for config flags */
#define CO_PRIORITY                0x03    /* Priority class for the object              */
#define CO_COMM_ENABLE             0x04    /* Object in enabled for communication        */
#define CO_READ_ENABLE             0x08    /* Object value can be read via bus           */
#define CO_WRITE_ENABLE            0x10    /* Object value can be written via bus        */
#define CO_COMM_SEG1               0x20    /* Memory offset (only DM0012 & DM0021)       */
#define CO_TRANS_ENABLE            0x40    /* Object is enabled to send                  */
#define CO_UPDATE_ENABLE           0x80    /* Object accepts values from response frames */

/* Abreviations */
#define COM_EN                     0x04    /* Object is enabled for communication        */
#define COM_R                      0x08    /* Object value can be read via bus           */
#define COM_W                      0x10    /* Object value can be written via bus        */
#define COM_T                      0x40    /* Object is enabled to send                  */
#define COM_U                      0x80    /* Object accepts values from response frames */

/* Combinations for config flags */
#define COM_ALL                    COM_EN | COM_R | COM_W | COM_T | COM_U
#define COM_STD                    COM_EN | COM_W | COM_T
#define COM_SND                    COM_EN | COM_T
#define COM_RCV                    COM_EN | COM_W

/* Com. Obj. priority. */
#define PRIO_LOW					0x03	/* Priority low    */
#define PRIO_HIGH					0x01	/* Priority high   */
#define PRIO_ALRM					0x02	/* Priority alarm  */
#define PRIO_SYS					0x00	/* Priority system */


/* Defines for RAM-Flags */
#define CO_FLAGS                   0x0F    /* Mask for all used flags */
#define CO_STATUS                  0x03    /* Mask for status flags                       */
#define CO_STATUS_OK               0x00    /* Flag pattern for status ok                  */
#define CO_STATUS_ERROR            0x01    /* Flag pattern for status error               */
#define CO_STATUS_PROGRESS         0x02    /* Flag pattern for status transm. in progress */
#define CO_STATUS_TRANSREQ         0x03    /* Flag pattern for status transm. requested   */

#define CO_READ_REQ                0x04    /* Object has to send a read request    */
#define CO_EXTERNAL_UPDATE         0x08    /* Object has been updated via telegram */
#define CO_FLAG_ERROR              0x0F    /* Used for return value                */


/* Define for telegram rate limitation */
#define TEL_LIMIT_BASE_TIME       17000    /* Base time in ms for telegram limitation */


/**************************************************************************************************************
* FunctionName:VOID Knx_AlAppUp(BYTE **pucUpFrame)
* FunctionDescription: KNX application layer up frames handle。
* InputParameterBYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:if we handle over the frames,we set the length of the buffer to clear it.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxAl_AppUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* FunctionName:BYTE KnxAl_GetCoInfoLength(BYTE ucCoNo)
* FunctionDescription: This function retrieves the buffer length used by the given communication object.
* InputParameterBYTE ucCoNo :communication object No.
* OutputParameterno.
* Return Value：buffer length.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxAl_GetCoBufferLength(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_GetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* FunctionDescription: This function is used by application to retrieve the value of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :frame's payload pointer.
* OutputParameterBYTE *pucBuffer :communication object data.
* Return Value：TRUE / FALSE.
* Other Description:This function will be a API function used by the application.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAl_GetCoValue(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_SetCoValue(BYTE ucCoNo,BYTE *pucBuffer)
* FunctionDescription: This function is used by application to set the value of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
            BYTE *pucBuffer :frame's payload pointer.
* OutputParameterBYTE *pucBuffer :communication object data.
* Return Value：TRUE / FALSE.
* Other Description:(1)This function will be a API function used by the application.
            (2)To initiate a transmission of the new value KnxAl_RequestValueWrite(para) has to be called in addition.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAl_SetCoValue(BYTE ucCoNo,BYTE *pucBuffer);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_GetUpdatedCo(BYTE *pucCoNo)
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
BOOL KnxAl_GetUpdatedCo(BYTE *pucCoNo);

/**************************************************************************************************************
* FunctionName:BYTE KnxAl_GetRamFlags(BYTE ucCoNo)
* FunctionDescription: This function is used by application to retrieve the status of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
* OutputParameterno.
* Return Value：BYTE : the status of the communication object.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxAl_GetRamFlags(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_SetRamFlags(BYTE ucCoNo, BYTE ucFlags)
* FunctionDescription: This function is used by application to set the status of the given communication object.
* InputParameterBYTE ucCoNo     :communication object No.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAl_SetRamFlags(BYTE ucCoNo, BYTE ucFlags);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_RequestValueWrite(BYTE ucCoNo)
* FunctionDescription: This function initiates a value write request on the given communication object.
* InputParameterBYTE ucCoNo:Co.objet No.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:The system will transmitts the current value of the given communication object.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAl_RequestValueWrite(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_RequestValueRead(BYTE ucCoNo)
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
BOOL KnxAl_RequestValueRead(BYTE ucCoNo);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_Init(VOID)
* FunctionDescription: KNX application layer management initialize。
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAl_Init(VOID);

/**************************************************************************************************************
* FunctionName:VOID KnxAl_IncTelRateCredits(VOID)
* FunctionDescription: This function updates the telegram limitation credits.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:(1)The telegram limitation is enabled if the limit rate is not equal 0x00.
            (2)each ms of runtime is a "send credit".in order to send a telegram,we should have enough send credits.
               when we send a telegram,we will subtract Telegram-limitation-base-time/limitation.We can not have more 
               credits than the base time.
            (3)to decrement credit when ucEnSub = TURE.
            (4)to increment the credit KnxAl_UpdateTelRateCredit() must be called during each cycle.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxAl_UpdateTelRateCredit(VOID);

/**************************************************************************************************************
* FunctionName:BYTE *KnxAl_GetDownFrame(VOID)
* FunctionDescription: This function is called to build a new request to be sent to the bus.
* InputParameterno.
* OutputParameterno.
* Return Value：BYTE *:down buffer.
* Other Description:if we handle over the frames,we set the length of the buffer to clear it.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE *KnxAl_GetDownFrame(VOID);

/**************************************************************************************************************
* FunctionName:BOOL KnxAl_Close(void)
* FunctionDescription: close the application.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAl_Close(void);







#ifdef __cplusplus
}
#endif

#endif /* _KNX_ALAPP_H_ */



/* end of file. */


