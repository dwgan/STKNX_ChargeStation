/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Tl.h
* FileIdentifier：None
* Abstract ：knx ip transport layer header file.
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


#ifndef _KNX_TL_H_
#define _KNX_TL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* define TPDU type. */
#define KNX_TPDU_TYPE_MASK        0xC0   /* TPDU type mask.                     */
#define KNX_TPDU_TYPE_DATA        0x00   /* TPDU data type,P2P-cntless/Brd/Grp. */
#define KNX_TPDU_TYPE_CDATA       0x40   /* T_Connect_Data.                     */
#define KNX_TPDU_TYPE_CMD         0x80   /* Cnt/DisCnt command.                 */
#define KNX_TPDU_TYPE_ACK         0xC0   /* connection ACK.                     */
#define KNX_TPDU_TYPE_SEQU_NO     0xFC

/* define connection command. */
#define KNX_TPDU_CNECT_CMD        0x80   /* establish a connection command. */
#define KNX_TPDU_DISCNT_CMD       0x81   /* release a connection command.   */

/* define connection ACK. */
#define KNX_TPDU_ACK              0xC2   /* Positive connection ACK. */
#define KNX_TPDU_NACK             0xC3   /* Negative connection ACK. */

/* connection sequence mask. */
#define KNX_TPDU_SEQ_MASK         0x3C   /* connection sequence mask. */


/**************************************************************************************************************
* FunctionName:VOID Knx_TlUp(BYTE **pucUpFrame)
* FunctionDescription: KNX transport up frame handle。
* InputParameterBYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:if there is a wrong in the buffer,we set the length to 0.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_TlUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* FunctionName:VOID Knx_TlDown(BYTE **pucDownFrame)
* FunctionDescription: KNX transport down frame handle。
* InputParameterBYTE **pucDownFrame:down frame buffer's pointer,*pucDownFrame points to the header of buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:if there is a wrong in the buffer,we set the length to 0.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_TlDown(BYTE **pucDownFrame);











#ifdef __cplusplus
}
#endif

#endif /* _KNX_TL_H_ */



/* end of file. */


