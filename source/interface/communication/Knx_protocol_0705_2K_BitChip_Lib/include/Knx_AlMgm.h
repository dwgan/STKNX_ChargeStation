/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_AlMgm.h
* FileIdentifier：None
* Abstract ：knx ip application layer management header file.
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


#ifndef _KNX_ALMGM_H_
#define _KNX_ALMGM_H_

#ifdef __cplusplus
extern "C" {
#endif



/**************************************************************************************************************
* FunctionName:VOID Knx_AlMgmUp(BYTE **pucUpFrame)
* FunctionDescription: KNX application layer management up frames handle。
* InputParameterBYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:if we handle over the frames,we set the length of the buffer to clear it.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_AlMgmUp(BYTE **pucUpFrame);

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
VOID Knx_AlMgmInit(VOID);

/**************************************************************************************************************
* FunctionName:static BOOL KnxAl_ApduLengthCheck(BYTE *pucUpFrame,BYTE ucLength)
* FunctionDescription: check if the APDU length is right.
* InputParameterBYTE *pucUpFrame:up frame buffer's pointer.
            BYTE ucLength   :the right length to meassure the APDU length.
* OutputParameterno.
* Return Value：TRUE : the length is right.
            FALSE: the length is wrong.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAl_ApduLengthCheck(BYTE *pucUpFrame,BYTE ucLength);

/**************************************************************************************************************
* FunctionName:BYTE *KnxAl_GetMgmDownFrame(VOID)
* FunctionDescription: get the management down frame.
* InputParameterno.
* OutputParameterno.
* Return Value：BYTE *:down frame buffer pointer.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE *KnxAl_GetMgmDownFrame(VOID);

/**************************************************************************************************************
* FunctionName:VOID KnxAl_CompleteRespReq(BYTE *pucUpFrame,BYTE *pucDwFrame)
* FunctionDescription: complete the response frame.
* InputParameterBYTE *pucUpFrame : in frame's buffer.
            BYTE *pucDwFrame : down frame's buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxAl_CompleteRespReq(BYTE *pucUpFrame,BYTE *pucDwFrame);

/**************************************************************************************************************
* FunctionName:VOID KnxAl_SetDeviceControl(BYTE ucDevCtrl)
* FunctionDescription: set device control data.
* InputParameterBYTE ucDevCtrl.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID KnxAl_SetDeviceControl(BYTE ucDevCtrl);

/**************************************************************************************************************
* FunctionName:BYTE KnxAl_GetDeviceCtrl(VOID)
* FunctionDescription: get device control data.
* InputParameterno.
* OutputParameterno.
* Return Value：BYTE : sg_ucDevCtrl.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxAl_GetDeviceCtrl(VOID);







#ifdef __cplusplus
}
#endif

#endif /* _KNX_ALMGM_H_ */



/* end of file. */


