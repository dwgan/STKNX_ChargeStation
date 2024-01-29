/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Auth.h
* FileIdentifier：None
* Abstract ：本文件为KNX协议栈授权处理头文件。
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



#ifndef _KNX_AUTH_H_
#define _KNX_AUTH_H_

#ifdef __cplusplus
extern "C" {
#endif


/* define access level */
#define ACC_SYS          0x02    /* Access to application program.           */
#define ACC_TABLE        0x02    /* Access to address and association table. */
#define ACC_PARAM        0x03    /* Access to application parameters.        */
#define ACC_FREE         0x0F    /* Free access.    */
#define ACC_ERROR        0xFF    /* Error detected. */



/**************************************************************************************************************
* FunctionName:BYTE KnxAuth_SetLevel(BYTE* pucKey)
* FunctionDescription: Setting the actual access level according to the given key.
* InputParameterBYTE *pucKey:key data pointer.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxAuth_SetLevel(BYTE* pucKey);

/**************************************************************************************************************
* FunctionName:BYTE KnxAuth_GetLevel(VOID)
* FunctionDescription: Getting the actual access level.
* InputParameterno.
* OutputParameterno.
* Return Value：access level.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxAuth_GetLevel(VOID);

/**************************************************************************************************************
* FunctionName:BOOL KnxAuth_GetKey(BYTE ucLevel, BYTE *pucKey)
* FunctionDescription: Getting a key by the level.
* InputParameterBYTE ucLevel : input level.
            BYTE *pucKey : the output buffer's pointer.
* OutputParameterBYTE *pucKey : the output key data.
* Return Value：TRUE / FALSE
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAuth_GetKey(BYTE ucLevel, BYTE *pucKey);

/**************************************************************************************************************
* FunctionName:BOOL KnxAuth_SetKey(BYTE ucLevel, BYTE *pucKey)
* FunctionDescription: Setting a key by the level.
* InputParameterBYTE ucLevel : input level.
            BYTE *pucKey : the input buffer's pointer.
* OutputParameterno.
* Return Value：TRUE / FALSE
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL KnxAuth_SetKey(BYTE ucLevel, BYTE *pucKey);












#ifdef __cplusplus
}
#endif

#endif /* _KNX_AUTH_H_ */

/* End of _KNX_AUTH_H_ */

