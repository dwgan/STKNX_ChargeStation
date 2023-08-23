/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��buffer.h
* FileIdentifier��None
* Abstract ������������ͷ�ļ�
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
*   �ṹ����T_BUFFER_MGM
*   ������  buffer����ṹ
*   ������  
    BYTE    ucUseFlg;              Bit0:alloc Pool's flag
                                   Bit1:free pool's flag
                                   Bit2:In buffer's flag
    BYTE    *pucPoolHeader;        the current free buffer point
    BYTE    *pucPoolEnd;           the current free buffer end  
    BYTE    *pucBufferIn;          the buffer for input         
    BYTE    *pucBufLastIn;         the last in buffer           
*   ���ߣ�       
*   ˵��:
       (1) buffer frame format is as below:
              |sizeof(WORDPTR)|1 byte for pool ID| data ....|
       (2) buffer size shold be >= (Max. data size + sizeof(WORDPTR) + 1)
       (3) the byte for pool ID in frame is defined as below:
              bit0~bit3:the source pool's ID;
              bit4~bit7:the destination pool's ID;
*   Modified History��
*   2013-7-24         �����ṹ��
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
*   �ṹ����T_BUFFER_HEADER
*   ������  bufferͷ��
*   ������  
            BYTE *pucNext : next buffer's address.
            BYTE ucPoolId : buffer's pool ID.
*   Modified History��
*   2013-7-24         �����ṹ��
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
* FunctionDescription: ��ʼ��buffer�ء�
* InputParameterNone
* OutputParameterNone
* Return Value��None
* Other Description:
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
VOID Buffer_Pool_Init(VOID);

/**************************************************************************
* FunctionName:BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum)
* FunctionDescription: ��buffer�ܳ��з���һ��buffer�ӳأ��ӳصĴ�СΪbuffer���Ⱥ͸���
            �ĳ˻���
* InputParameterWORD16 wBufferSize : һ��buffer�Ĵ�С
            WORD16 wBufferNum  : buffer�ĸ���
* OutputParameterNone
* Return Value��POOL_ID_NULL  : buffer�ӳط���ʧ��
                            ����Ϊ����ɹ����POOL ID
* Other Description:wBufferSize > sizeof(WORDPTR) + 1
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE Buffer_Pool_Alloc(WORD16 wBufferSize,WORD16 wBufferNum);

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
BYTE* Buffer_Alloc(BYTE ucPoolId);

/**************************************************************************
* FunctionName:BYTE* Buffer_Free(BYTE ucPoolId)
* FunctionDescription: �ͷ�һ��buffer��pool�С�
* InputParameterBYTE ucPoolId : pool Id.
* OutputParameterNone
* Return Value��NULL  : buffer�ӳ��ͷ�ʧ��
                    �ͷųɹ��������ӳ���buffer
* Other Description:���ں������������£�����ֵ������Ϊbuffer�ص��׵�ַ���м��㡣
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer);

/**************************************************************************
* FunctionName:BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer)
* FunctionDescription: ��buffer���в���һ��buffer��
* InputParameterBYTE ucPoolId : pool Id.
            BYTE *pucBuffer:buffer.
* OutputParameterNone
* Return Value��NULL  : ����bufferʧ��
                    ����ɹ������ص�ǰbuffer����buffer��
* Other Description:���ں������������£�����ֵ������Ϊbuffer�����׵�ַ���м��㡣
* Modified Date        �汾��     �޸���          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
BYTE* Buffer_Insert(BYTE ucPoolId,BYTE *pucBuffer);

/**************************************************************************
* FunctionName:BYTE* Buffer_GetHeader(BYTE ucPoolId)
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
BYTE* Buffer_Get(BYTE ucPoolId);



#ifdef __cplusplus
}
#endif

#endif /* _BUFFER_H_ */



/* end of file. */

