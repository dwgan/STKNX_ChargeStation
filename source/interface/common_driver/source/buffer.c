/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��buffer.c
* FileIdentifier��None
* Abstract ������������Դ�ļ�
* Other Description��
* Current Version��V1.00
* Author��     
* Completed Date��2014��3��18��
*    
* Modified History1��
*        Modified Date��2014��3��18��
*        Version Number��V1.00
*        Modified Person��     
*        Modified part��Create�ļ�
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
* FunctionDescription: ��ʼ��buffer�ء�
* InputParameterNone
* OutputParameterNone
* Return Value��None
* Other Description:
* Modified Date        �汾��     �޸���          Modified part
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
* FunctionDescription: ��buffer�ܳ��з���һ��buffer�ӳأ��ӳصĴ�СΪbuffer���Ⱥ͸���
            �ĳ˻���
* InputParameterWORD16 wBufferSize : һ��buffer�Ĵ�С
            WORD16 wBufferNum  : buffer�ĸ���
* OutputParameterNone
* Return Value��POOL_ID_NULL  : buffer�ӳط���ʧ��
                            ����Ϊ����ɹ����POOL ID,Pool ID < MAX_BUFFER_POOL_NUM
* Other Description:wBufferSize > sizeof(WORDPTR) + 1
* Modified Date        �汾��     �޸���          Modified part
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
* FunctionDescription: ��buffer�ӳ��з���һ��buffer��
* InputParameterBYTE ucPoolId : pool Id.
* OutputParameterNone
* Return Value��NULL  : buffer�ӳط���ʧ��
                    �������ɹ���bufferָ��
* Other Description:
* Modified Date        �汾��     �޸���          Modified part
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
* FunctionDescription: �ͷ�һ��buffer��pool�С�
* InputParameterBYTE ucPoolId : pool Id.
            BYTE *pucBuffer:���ͷ�buffer.
* OutputParameterNone
* Return Value��NULL  : buffer�ӳ��ͷ�ʧ��
                    �ͷųɹ��������ӳ���buffer
* Other Description:���ں������������£�����ֵ������Ϊbuffer�ص��׵�ַ���м��㡣
* Modified Date        �汾��     �޸���          Modified part
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
* FunctionDescription: ��buffer���в���һ��buffer��
* InputParameterBYTE ucPoolId : pool Id.
            BYTE *pucBuffer:insert buffer.
* OutputParameterNone
* Return Value��NULL  : ����bufferʧ��
                    ����ɹ������ص�ǰbuffer����buffer��
* Other Description:���ں������������£�����ֵ������Ϊbuffer�����׵�ַ���м��㡣
* Modified Date        �汾��     �޸���          Modified part
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
* FunctionDescription: ��buffer���е�һ��buffer��
* InputParameterBYTE ucPoolId : pool Id.
* OutputParameterNone
* Return Value��NULL  : ��ȡbufferʧ��
                    ��ȡ�ɹ������ص�ǰbuffer��
* Other Description:
* Modified Date        �汾��     �޸���          Modified part
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

