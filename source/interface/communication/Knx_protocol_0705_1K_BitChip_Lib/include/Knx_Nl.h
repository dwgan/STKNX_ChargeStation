/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Nl.h
* FileIdentifier：None
* Abstract ：knx ip network layer header file.
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


#ifndef _KNX_NL_H_
#define _KNX_NL_H_

#ifdef __cplusplus
extern "C" {
#endif


#define NPDU_CLR_HOP_COUNT        0x8F           /* clear the hop count.        */
#define NPDU_MAX_HOP_COUNT        0x60           /* Max. hop count.             */
#define NPDU_ESC_HOP_COUNT        0x70           /* No blocking hop count.      */
#define NPDU_HOP_COUNT_MASK       0x70           /* Mask for getting hop count. */


/**************************************************************************************************************
* FunctionName:VOID Knx_NlUp(BYTE **pucUpFrame)
* FunctionDescription: KNX network up frame handle。
* InputParameterBYTE **pucUpFrame:up frame buffer's pointer,*pucUpFrame points to the header of buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:if there is a wrong in the buffer,we set the length to 0.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_NlUp(BYTE **pucUpFrame);

/**************************************************************************************************************
* FunctionName:VOID Knx_NlDown(BYTE **pucDownFrame)
* FunctionDescription: KNX network down frame handle。
* InputParameterBYTE **pucDownFrame:down frame buffer's pointer,*pucDownFrame points to the header of buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:if there is a wrong in the buffer,we set the length to 0.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_NlDown(BYTE **pucDownFrame);











#ifdef __cplusplus
}
#endif

#endif /* _KNX_NL_H_ */



/* end of file. */


