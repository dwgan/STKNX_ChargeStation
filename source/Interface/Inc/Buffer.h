/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：buffer.h
* FileIdentifier：None
* Abstract ：缓冲区管理头文件
* Other Description：
* Current Version：V1.00
* Author：     
* Completed Date：2014年3月18日
*    
* Modified History1：
*        Modified Date：2014年3月18日
*        Version Number：V1.00
*        Modified Person：     
*        Modified part：Create文件
******************************************************************************/


#ifndef _BUFFER_H_
#define _BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Attention:The follow definition should be redefined in BoardCtrl.h according to the realistic scenario. */
#ifndef TOTAL_BUFFER_SIZE
    #define TOTAL_BUFFER_SIZE (2048)   /* the total size of buffer pool. */
#endif

/* MCU_SIZE should be defined in hardware.h */
#define DATA_BUF_ADDRESS_ALIGNMENT(x)  ((BYTE*)((((WORDPTR)(x))+MCU_SIZE-1) & (~(MCU_SIZE-1))))  /* align the address of the buffer. */
#define DATA_BUF_SIZE_ALIGNMENT(x)     (((x)+MCU_SIZE-1) & (~(MCU_SIZE-1)))                      /* align the size of the buffer.    */

/* The Max. number of pools. */
#define MAX_BUFFER_POOL_NUM         (16)

/* Pool ID definition. */
#define POOL_ID_NULL              (0)
#define POOL_ID_ERROR             (0xff)
#define SET_POOL_ACLLOC_FLAG      (0x01)    /* set alloc flag.      */
#define CLR_POOL_ACLLOC_FLAG      (0xFE)    /* release aclloc flag. */
#define SET_POOL_FREE_FLAG        (0x02)    /* set free flag.       */
#define CLR_POOL_FREE_FLAG        (0xFD)    /* release free flag.   */
#define SET_POOL_IN_FLAG          (0x04)    /* set input flag.      */
#define CLR_POOL_IN_FLAG          (0xFB)    /* release input flag.  */

/****************************************************
*   结构名：T_BUFFER_MGM
*   描述：  buffer管理结构
*   参数：  
    BYTE    ucUseFlg;              Bit0:alloc Pool's flag
                                   Bit1:free pool's flag
                                   Bit2:In buffer's flag
    BYTE    *pucPoolHeader;        the current free buffer point
    BYTE    *pucPoolEnd;           the current free buffer end  
    BYTE    *pucBufferIn;          the buffer for input         
    BYTE    *pucBufLastIn;         the last in buffer           
*   作者：       
*   说明:
       (1) buffer frame format is as below:
              |sizeof(WORDPTR)|1 byte for pool ID| data ....|
       (2) buffer size shold be >= (Max. data size + sizeof(WORDPTR) + 1)
       (3) the byte for pool ID in frame is defined as below:
              bit0~bit3:the source pool's ID;
              bit4~bit7:the destination pool's ID;
*   Modified History：
*   2013-7-24         新增结构；
****************************************************/
typedef struct
{
    BYTE    ucUseFlg;              /* Bit0:alloc Pool's flag,
                                      Bit1:free pool's flag,
                                      Bit2:In buffer's flag;         */
    BYTE    *pucPoolHeader;        /* the current free buffer point. */
    BYTE    *pucPoolEnd;           /* the current free buffer end.   */
    BYTE    *pucBufferIn;          /* the buffer for input.          */
    BYTE    *pucBufLastIn;         /* the last in buffer.            */
}T_BUFFER_MGM;

/****************************************************
*   结构名：T_BUFFER_HEADER
*   描述：  buffer头部
*   参数：  
            BYTE *pucNext : next buffer's address.
            BYTE ucPoolId : buffer's pool ID.
*   Modified History：
*   2013-7-24         新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE *pucNext;     /* next buffer's address */
    BYTE ucPoolId;     /* buffer's pool ID.     */
}T_BUFFER_HEADER;
#pragma pack()

/**************************************************************************
* FunctionName:VOID Buffer_Pool_Init(VOID)
* FunctionDescription: 初始化buffer池。
* InputParameterNone
* OutputParameterNone
* Return Value：None
* Other Description:
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
VOID Buffer_Pool_Init(VOID);

/**************************************************************************
* FunctionName:BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
* FunctionDescription: 从buffer总池中分配一段buffer子池，子池的大小为buffer长度和个数
            的乘积。
* InputParameterWORD16 wBufferSize : 一个buffer的大小
            WORD16 wBufferNum  : buffer的个数
* OutputParameterNone
* Return Value：POOL_ID_NULL  : buffer子池分配失败
                            其他为分配成功后的POOL ID
* Other Description:wBufferSize > sizeof(WORDPTR) + 1
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum);

/**************************************************************************
* FunctionName:BYTE* Buffer_Alloc(BYTE ucPoolId)
* FunctionDescription: 从buffer子池中分配一个buffer。
* InputParameterBYTE ucPoolId : pool Id.
* OutputParameterNone
* Return Value：NULL  : buffer子池分配失败
                    其他，成功的buffer指针
* Other Description:
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Alloc(BYTE ucPoolId);

/**************************************************************************
* FunctionName:BYTE* Buffer_Free(BYTE ucPoolId)
* FunctionDescription: 释放一个buffer回pool中。
* InputParameterBYTE ucPoolId : pool Id.
* OutputParameterNone
* Return Value：NULL  : buffer子池释放失败
                    释放成功，返回子池首buffer
* Other Description:存在函数重入的情况下，返回值不能作为buffer池的首地址进行计算。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer);

/**************************************************************************
* FunctionName:BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
* FunctionDescription: 向buffer链中插入一个buffer。
* InputParameterBYTE ucPoolId : pool Id.
            BYTE *pucBuffer:buffer.
* OutputParameterNone
* Return Value：NULL  : 插入buffer失败
                    插入成功，返回当前buffer池首buffer。
* Other Description:存在函数重入的情况下，返回值不能作为buffer链的首地址进行计算。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer);

/**************************************************************************
* FunctionName:BYTE* Buffer_GetHeader(BYTE ucPoolId)
* FunctionDescription: 从buffer链中第一个buffer。
* InputParameterBYTE ucPoolId : pool Id.
* OutputParameterNone
* Return Value：NULL  : 获取buffer失败
                    获取成功，返回当前buffer。
* Other Description:
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Get(BYTE ucPoolId);



#ifdef __cplusplus
}
#endif

#endif /* _BUFFER_H_ */



/* end of file. */

