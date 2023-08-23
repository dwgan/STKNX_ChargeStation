/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Rec_Table.h
* FileIdentifier：None
* Abstract ：record table header file.
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


#ifndef _REC_TABLE_H_
#define _REC_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif


/* record's status define. */
#define ID_RECORD_FREE                0xffff    /* Record is free and ready to be used      */
#define ID_RECORD_VALID               0x5555    /* The data that record contains is valid   */
#define ID_RECORD_INVALID             0xaaaa    /* The data that record contains is invalid */
#define ID_RCD_FREE_DATA              0xff
#define ID_RCD_INVALID_DATA           0xaa
#define ID_RCD_VALID_DATA             0x55

#define RCD_INVALID_INDEX             0
#define RCD_INVALID_ST_OFFSET         16

#define RCD_VALID_INDEX               8
#define RCD_VALID_ST_OFFSET           24

#define RCD_DATA_INDEX                0
#define RCD_DATA_OFFSET               8
#define RCD_ST_LENG                   16

/* system relating record type define. */
#define ID_REC_SYS                    0x01    /* One byte record used by system */
#define ID_REC_FLASH                  0x02    /* one byte used for flash status. */
/* application relatint record define. */
#define ID_REC_APP                    0x06    /* One byte Record used by application */

/* record table virtual space.1K bytes,8 bytes per record. */
#define RECORD_TABLE_BEG             VIR_BEG_REC_EE
#define RECTBL_FIRST_RECORD          RECORD_TABLE_BEG

#define RECORD_TABLE_END                   VIR_END_REC_EE
#define RECTBL_RECORD_LEN                  8
#define RECTBL_LAST_RECORD                 (RECORD_TABLE_END - RECTBL_RECORD_LEN + 1)
#define RECTBL_RECORD_CUNT                 ((RECORD_TABLE_END - RECORD_TABLE_BEG + 1)/RECTBL_RECORD_LEN)
#define BUILD_RECORD_ID(ucMainId,ucSubId)  (((ucMainId & 0x0F)<<8) | ucSubId)

#define GET_RECORD_MAIN_ID(ptRecord)   (((T_RECORD*)ptRecord)->ucMainId)
#define GET_RECORD_SUB_ID(ptRecord)    (((T_RECORD*)ptRecord)->ucSubId)
#define GET_RECORD_ID(ptRecord)        ((((T_RECORD*)ptRecord)->ucMainId << 8) + ((T_RECORD*)ptRecord)->ucSubId)

/****************************************************
*   结构名：T_RECORD
*   描述：  record structure define of record table.
            every record has 6 data.
*   参数：  
            BYTE ucMainId:4;           The main ID of record   
            BYTE ucReserved_0:4;       Only used by word record
            BYTE ucSubId;              The sub ID of record    
            BYTE aucResv[6];           reserve space.
            BYTE aucData[8];           Data bytes
            BYTE aucStatus[16];        The status of record,0-1 invalid,2-3 valid
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE ucMainId:4;                     /* The main ID of record    */
    BYTE ucReserved_0:4;                 /* Only used by word record */
    BYTE ucSubId;                        /* The sub ID of record     */
    BYTE aucResv[6];                     /* reserve space.           */
    BYTE aucData[8];                     /* Data bytes               */
    BYTE aucStatus[RCD_ST_LENG];         /* The status of record     */
}T_RECORD;
#pragma pack()

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
VOID *RecTable_GetRecord(WORD16 wRecordId);

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
BOOL RecTable_SetRecord(VOID *ptRec2Write);

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
BOOL RecTable_DeleteRecord(WORD16 wRecordId);

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
BOOL RecTable_DeleteAppRecords(void);

/**************************************************************************
* FunctionName:BYTE RecTable_GetByteIndex(BYTE ucBytePlace)
* 功能说明：This function retrieves the byte index in a byte record for a 
            given ucBytePlace bit pattern.
* InputParameterBYTE ucBytePlace : data saving pattern.
* OutputParameterno.
* Return Value: saving data index.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BYTE RecTable_GetByteIndex(BYTE ucBytePlace);

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
BOOL RecTable_GetByte(WORD16 wRecordID, BYTE *pucData);

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
BOOL RecTable_SetByte(WORD16 wRecordID, BYTE ucData);

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
BOOL RecTable_CleanUpRecord(T_RECORD *ptRecord);

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
BOOL RecTable_CleanUpTable(VOID);

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
BOOL RecTable_ClearTable(void);

/**************************************************************************
* FunctionName:VOID RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize)
* 功能说明：init recorder table operation.
* InputParameterBYTE ucBytePlace : data saving pattern.
*           BYTE ucWrtSize   : flash programing size of byte.  1.2.4.8
* OutputParameterno.
* Return Value: no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
VOID RecTable_OpInit(BYTE ucDevNo,BYTE ucWrtSize);






#ifdef __cplusplus
}
#endif

#endif /* _REC_TABLE_H_ */

/* end of file. */
