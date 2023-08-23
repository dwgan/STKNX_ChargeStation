/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：buffer.c
* FileIdentifier：None
* Abstract ：缓冲区管理源文件
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


#include "type_def.h"
#include "Pub.h"
#include "sw_common.h"
#include "Boardctrl.h"       /* it should be included before buffer.h for the TOTAL_BUFFER_SIZE definition. */
#include "buffer.h"
#include "mem_malloc.h"


static BYTE         sg_PoolInitFlg = 0;
static BYTE         sg_PoolIndex   = 0;
static BYTE         sg_BufferPool[DATA_BUF_SIZE_ALIGNMENT(TOTAL_BUFFER_SIZE)];
static BYTE         *sg_pucBufferPool = NULL,*sg_pucFreePool = NULL;
static T_BUFFER_MGM *sg_patBufferMgm[MAX_BUFFER_POOL_NUM] = {NULL,NULL,NULL,NULL};



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
VOID Buffer_Pool_Init(VOID)
{
    WORD16 wIndex;
    BYTE   *pucData;
    
    sg_pucBufferPool = DATA_BUF_ADDRESS_ALIGNMENT(sg_BufferPool);
    sg_pucFreePool   = sg_pucBufferPool;
    pucData          = sg_pucBufferPool;
    for(wIndex=0;wIndex<TOTAL_BUFFER_SIZE;wIndex++)
    {
        *(pucData+wIndex) = 0;
    }
    sg_PoolInitFlg = 1;
    
    return;
}

/**************************************************************************
* FunctionName:BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
* FunctionDescription: 从buffer总池中分配一段buffer子池，子池的大小为buffer长度和个数
            的乘积。
* InputParameterWORD16 wBufferSize : 一个buffer的大小
            WORD16 wBufferNum  : buffer的个数
* OutputParameterNone
* Return Value：POOL_ID_NULL  : buffer子池分配失败
                            其他为分配成功后的POOL ID,Pool ID < MAX_BUFFER_POOL_NUM
* Other Description:wBufferSize > sizeof(WORDPTR) + 1
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
{
    BYTE *pucPoint;
    WORD16 wMemSize,wIndex;
    T_BUFFER_MGM *ptMgm;
    
    if(0==sg_PoolInitFlg)
    {
        return POOL_ID_NULL;
    }
    
    wMemSize = wBufferSize * wBufferNum;
    if(((sg_pucFreePool + wMemSize) > (sg_pucBufferPool + TOTAL_BUFFER_SIZE))||\
       (sg_PoolIndex >= MAX_BUFFER_POOL_NUM)||(wBufferSize <= sizeof(T_BUFFER_HEADER)))
    {
        /* Not enough. */
        return POOL_ID_NULL;
    }
    ptMgm = mem_malloc(sizeof(T_BUFFER_MGM));
    if(NULL==ptMgm)
    {
        return POOL_ID_NULL;
    }
    sg_patBufferMgm[sg_PoolIndex] = ptMgm;
    ptMgm->ucUseFlg         = 0;
    ptMgm->pucPoolHeader    = sg_pucFreePool;
    ptMgm->pucBufferIn      = NULL;
    ptMgm->pucBufLastIn     = NULL;
    sg_PoolIndex++;
    pucPoint = sg_pucFreePool;
    for(wIndex=0;wIndex < wBufferNum;wIndex++)
    {
        if((wIndex + 1) == wBufferNum)
        {
            ptMgm->pucPoolEnd = pucPoint;
            ((T_BUFFER_HEADER *)pucPoint)->pucNext = NULL;                 /* the final one's next is set to NULL. */
        }
        else
        {
            ((T_BUFFER_HEADER *)pucPoint)->pucNext = pucPoint+wBufferSize; /* save the next buffer's address into the buffer's header. */
        }
        ((T_BUFFER_HEADER *)pucPoint)->ucPoolId = sg_PoolIndex;            /* save the pool ID. */
        pucPoint += wBufferSize;
    }
    sg_pucFreePool += wMemSize;                                    /* set the pool current free point. */
    
    return sg_PoolIndex;
}

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
BYTE* Buffer_Alloc(BYTE ucPoolId)
{
    BYTE *pucBuffer;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0 == ucPoolId))
    {
        return NULL;
    }
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(NULL == ptMgm->pucPoolHeader)
    {
        /* There is no buffer in pool. */
        return NULL;
    }

    if(ptMgm->ucUseFlg & SET_POOL_ACLLOC_FLAG)
    {
        /* Aclloc is conflicting. */
        return NULL;
    }
    ptMgm->ucUseFlg     |= SET_POOL_ACLLOC_FLAG;                         /* set using flag. */
    pucBuffer            = ptMgm->pucPoolHeader;
    ptMgm->pucPoolHeader = ((T_BUFFER_HEADER *)pucBuffer)->pucNext;
    ptMgm->ucUseFlg     &= CLR_POOL_ACLLOC_FLAG;                         /* clear using flag. */
    /* clear the buffer next chain link. */
    ((T_BUFFER_HEADER *)pucBuffer)->pucNext = NULL;
    
    return pucBuffer;
}

/**************************************************************************
* FunctionName:BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
* FunctionDescription: 释放一个buffer回pool中。
* InputParameterBYTE ucPoolId : pool Id.
            BYTE *pucBuffer:待释放buffer.
* OutputParameterNone
* Return Value：NULL  : buffer子池释放失败
                    释放成功，返回子池首buffer
* Other Description:存在函数重入的情况下，返回值不能作为buffer池的首地址进行计算。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
{
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId)||(NULL==pucBuffer))
    {
        return NULL;
    }
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(ptMgm->ucUseFlg & SET_POOL_FREE_FLAG)
    {
        return NULL;
    }
    ptMgm->ucUseFlg |= SET_POOL_FREE_FLAG;                         /* set using flag. */
    ((T_BUFFER_HEADER *)pucBuffer)->pucNext = NULL;
    if(NULL == ptMgm->pucPoolHeader)
    {
        ptMgm->pucPoolHeader = pucBuffer;
    }
    else
    {
        ((T_BUFFER_HEADER *)ptMgm->pucPoolEnd)->pucNext = pucBuffer;
    }
    ptMgm->pucPoolEnd = pucBuffer;
    ptMgm->ucUseFlg &= CLR_POOL_FREE_FLAG;                         /* clear using flag. */

    return ptMgm->pucPoolHeader;
}

/**************************************************************************
* FunctionName:BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
* FunctionDescription: 向buffer链中插入一个buffer。
* InputParameterBYTE ucPoolId : pool Id.
            BYTE *pucBuffer:insert buffer.
* OutputParameterNone
* Return Value：NULL  : 插入buffer失败
                    插入成功，返回当前buffer池首buffer。
* Other Description:存在函数重入的情况下，返回值不能作为buffer链的首地址进行计算。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
{
    BYTE *pucBufEnd;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId)||(NULL==pucBuffer))
    {
        return NULL;
    }
    
    /* we get the input buffer chain's end. */
    pucBufEnd = pucBuffer;
    while(((T_BUFFER_HEADER *)pucBufEnd)->pucNext != NULL)
    {
        /* it is a buffer chain. */
        pucBufEnd = ((T_BUFFER_HEADER *)pucBufEnd)->pucNext;
    }
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(NULL == ptMgm->pucBufferIn)
    {
        ptMgm->pucBufferIn  = pucBuffer;
        ptMgm->pucBufLastIn = pucBufEnd;
    }
    /* we use first in first out mode. */
    else
    {
        ((T_BUFFER_HEADER *)(ptMgm->pucBufLastIn))->pucNext = pucBuffer;
        ptMgm->pucBufLastIn   = pucBufEnd;
    }

    return ptMgm->pucBufferIn;
}

/**************************************************************************
* FunctionName:BYTE* Buffer_Get(BYTE ucPoolId)
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
BYTE* Buffer_Get(BYTE ucPoolId)
{
    BYTE *pucResult = NULL;
    T_BUFFER_MGM *ptMgm;
    
    if((ucPoolId > MAX_BUFFER_POOL_NUM)||(0==ucPoolId))
    {
        return NULL;
    }
    
    /* get the buffer management data. */
    ptMgm = sg_patBufferMgm[ucPoolId-1];
    if(NULL != ptMgm->pucBufferIn)
    {
        pucResult = ptMgm->pucBufferIn;
        ptMgm->pucBufferIn = ((T_BUFFER_HEADER *)(ptMgm->pucBufferIn))->pucNext;
        ((T_BUFFER_HEADER *)pucResult)->pucNext = NULL;
    }

    return pucResult;
}



/* end of file. */

