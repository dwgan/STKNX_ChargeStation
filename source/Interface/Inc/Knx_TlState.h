/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_TlState.h
* FileIdentifier：None
* Abstract ：knx transport layer state machine header file.
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


#ifndef _KNX_TLSTATE_H_
#define _KNX_TLSTATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* define the tl style.1/2/3 */
#define KNX_TL_STYLE               3
#define TL_STYLE1                  1
#define TL_STYLE2                  2
#define TL_STYLE3                  3

/* TL state machine definition. */
#define KNX_TL_CNECT_CLOSED        0    /* there is no connection.                 */
#define KNX_TL_CNECT_IDLE          1    /* there is a connection open and idle.    */
#define KNX_TL_CNECT_WAIT          2    /* Waiting for a T_ACK after sending data. */
#define KNX_TL_CNECT_CNECTING      3    /* Only for client.                        */

#define KNX_TL_REPT_MAX_CUNT       3    /* max. count for TL repititions. */

#define KNX_TL_SEQ_ADD_1           0x04   /* sequence No. + 1.    */
#define KNX_TL_SEQ_MASK            0x3C   /* sequence No.'s Mask. */

#define KNX_TL_REP_FLAG            0x8000 /* repeat send flag.                  */
#define KNX_TL_ACK_OVERTIME        3000   /* 3000ms-3s for ack overtime.        */
#define KNX_TL_CNECT_OVERTIME      6000   /* 6000ms-3s for connection overtime. */

/****************************************************
*   结构名：T_KNXTL_ATTR
*   描述：  transport parameter connection parameter.
*   参数：  see below.
*   作者：  Jackson
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE   ucDevInfo;                                /* Bit0-3:the source device flag&No.Bit4-7:the destination device flag&No. */
    BYTE   ucMsgInfo;                                /* bit6-7:layer type.bit4-5:PortNo,bit0-3:connect channel No.              */
    BYTE   ucPoolId;                                 /* buffer pool used for connection frames. */
    BYTE   ucState;                                  /* connection's state.Closed/IDEL/Wait.    */
    BYTE   ucRxSeq;                                  /* receive sequence No.                    */
    BYTE   ucTxSeq;                                  /* transmit sequence No.                   */
    BYTE   ucRepCunt;                                /* the counter of repetition.              */
    WORD16 wParterAddr;                              /* remote device's address.                */
    WORD32 wTimeCnect;                               /* connection time for over time.          */
    WORD32 wTimeAck;                                 /* start time for waiting ACK.             */
    BYTE   *pucTlCtlUp;                              /* buffer for Tl control up frames.        */
    BYTE   *pucTlCtlDwn;                             /* buffer for Tl control down frames.      */
    BYTE   *pucTlData;                               /* buffer for down frames.                 */
}T_KNXTL_CNECT_ATTR;


/**************************************************************************************************************
* FunctionName:BOOL Knx_TlStatInit(BYTE ucPoolId)
* FunctionDescription: KNX transport layer state initiation.
* InputParameterBYTE ucPoolId:pool for TL.
* OutputParameterno.
* Return Value：TRUE or FLASE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_TlStatInit(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_TlCnect_Data(**pucUpFrame)
* FunctionDescription: Connection data frames handling.
* InputParameterBYTE **pucUpFrame:frame buffer's pointer's pointer.
* OutputParameterno.
* Return Value：no.
* Other Description:we will clear the buffer length if the buffer is not need to be handled anymore.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_TlCnect_Data(BYTE **pucUpFrame);

/**************************************************************************************************************
* FunctionName:VOID Knx_TlCnect_Ctrl(**pucUpFrame)
* FunctionDescription: Connection command handling.
* InputParameterBYTE **pucUpFrame:frame buffer's pointer's pointer.
* OutputParameterno.
* Return Value：no.
* Other Description:we will clear the buffer length if the buffer is not need to be handled anymore.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_TlCnect_Ctrl(BYTE **pucUpFrame);

/**************************************************************************************************************
* FunctionName:VOID KnxTlCnect_Ack(**pucUpFrame)
* FunctionDescription: Connection ACK handling.
* InputParameterBYTE **pucUpFrame:frame buffer's pointer's pointer.
* OutputParameterno.
* Return Value：no.
* Other Description:we will clear the buffer length if the buffer is not need to be handled anymore.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxTlCnect_Ack(BYTE **pucUpFrame);

/**************************************************************************************************************
* FunctionName:BYTE *KnxTl_GetStUpFrame(VOID)
* FunctionDescription: Getting the KNX TL state management up frames.
* InputParameterno.
* OutputParameterno.
* Return Value：NULL    :no return buffer;
            Not Null:up frames buffer pointer.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE *KnxTl_GetStUpFrame(VOID);

/**************************************************************************************************************
* FunctionName:VOID KnxTl_GetStDwnFrame(VOID)
* FunctionDescription: Getting the KNX TL state management up frames.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxTl_GetStDwnFrame(VOID);

/**************************************************************************************************************
* FunctionName:BYTE KnxTl_GetTlState(VOID)
* FunctionDescription: Getting the KNX TL state.
* InputParameterno.
* OutputParameterno.
* Return Value：   KNX_TL_CNECT_CLOSED
                             KNX_TL_CNECT_IDLE
                             KNX_TL_CNECT_WAIT
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxTl_GetTlState(VOID);

/**************************************************************************************************************
* FunctionName:BOOL KnxTl_IsWaiting(VOID)
* FunctionDescription: KNX TL is in waiting.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE:TL is in waiting;
            FALSE:TL is not in waiting.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxTl_IsWaiting(VOID);

/**************************************************************************************************************
* FunctionName:BOOL KnxTl_Evt15Action(BYTE *pucBuffer)
* FunctionDescription: Action of Knx Tl Event15.
* InputParameterBYTE *pucBuffer:frame buffer's pointer.
* OutputParameterno.
* Return Value：TRUE or FLASE.
* Other Description:case ucstate == CLOSED,we do action0;
            case ucstate == IDLE,we do action7,ucstate = WAIT;
            case ucstate == WAIT,we do action11(do nothing).
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxTl_Evt15Action(BYTE *pucBuffer);









#ifdef __cplusplus
}
#endif

#endif /* _KNX_TLSTATE_H_ */



/* end of file. */


