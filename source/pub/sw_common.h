/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��sw_common.h
* FileIdentifier��None
* Abstract �����ļ�ΪǶ��ʽϵͳ����������ӿ���ع������塣
* Other Description��
* Current Version��V1.00
* Author��      
* Completed Date��2013��7��24��
*    
* Modified History1��
*        Modified Date��2013��7��24��
*        Version Number��V1.00
*        Modified Person��      
*        Modified part��Add new public definition.
******************************************************************************/

#include "type_def.h"

#ifndef _SW_COMMON_H_
#define _SW_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/************************* ͨ�ú궨�嶨�� *******************************/
#define   SW_DEVAPP_TYPE_RSV     (0x08)  /* ����   */


                /* �洢���Ͷ��� */
#define   SW_SVMWDIA_EEPROM      (0x01)  /* EEPROM */
#define   SW_SVMEDIA_FRAM        (0x02)  /* Fram   */
#define   SW_SVMEDIA_FLASH       (0x03)  /* Flash  */

                /* ͨѶ���Ͷ��� */
#define   SW_COMM_MEDIA_485      (0x01)  /* 485    */
#define   SW_COMM_MEDIA_CAN      (0x02)  /* CAN    */
#define   SW_COMM_MEDIA_232      (0x03)  /* 232    */
#define   SW_COMM_MEDIA_ETH      (0x04)  /* ��̫�� */
#define   SW_COMM_MEDIA_IR       (0x05)  /* ����   */
#define   SW_COMM_MEDIA_I2C      (0x06)  /* I2C    */
#define   SW_COMM_MEDIA_SPI      (0x07)  /* SPI    */
#define   SW_COMM_MEDIA_SOCKET   (0x08)  /* SOCKET */

               /* ������������Դ���� */
#define   SW_DATA_MEDIA_AD       (0x01)  /* ���ݴ�AD��ȡ       */
#define   SW_DATA_MEDIA_IC       (0x02)  /* ���ݴӼ���оƬ��ȡ */

               /* �������Ͷ��� */
#define   SW_CONTROL_RELAY       (0x01)  /* �̵������� */
#define   SW_CONTROL_WTCHDOG     (0x02)  /* ���Ź����� */
#define   SW_CONTROL_TIMER       (0x03)  /* ��ʱ��     */

               /* ��ʾ�豸���� */
#define   SW_DISP_MEDIA_SEGLED   (0x01)  /* ����� */
#define   SW_DISP_MEDIA_LCD      (0x02)  /* Һ��   */

/*********************** ����ģ��ID���� *****************************/
#define SW_COMM_DEV_BASE            (1)
#define SW_PERIPHERAL_UART          (SW_COMM_DEV_BASE)             /* UART       */
#define SW_PERIPHERAL_CAN           (SW_COMM_DEV_BASE + 1)         /* CAN        */
#define SW_PERIPHERAL_ETH           (SW_COMM_DEV_BASE + 2)         /* ETH        */
#define SW_PERIPHERAL_I2C           (SW_COMM_DEV_BASE + 3)         /* I2C        */
#define SW_PERIPHERAL_SPI           (SW_COMM_DEV_BASE + 4)         /* SPI        */
#define SW_PERIPHERAL_LORA          (SW_COMM_DEV_BASE + 5)         /* LORA       */
#define SW_PERIPHERAL_KNXCHIP       (SW_COMM_DEV_BASE + 6)         /* KNX Chip */
#define SW_COMM_DEV_RSV             (SW_COMM_DEV_BASE + 7)         /* reserve    */
/* for save media app. */
#define SW_MEDIA_DEV_BASE           (SW_COMM_DEV_RSV  + 1)
#define SW_PERIPHERAL_EEPROM        (SW_MEDIA_DEV_BASE)            /* EEPROM     */
#define SW_PERIPHERAL_FRAM          (SW_MEDIA_DEV_BASE + 1)        /* FRAM       */
#define SW_PERIPHERAL_FLASH         (SW_MEDIA_DEV_BASE + 2)        /* FLASH      */
#define SW_PERIPHERAL_RAM           (SW_MEDIA_DEV_BASE + 3)        /* RAM        */
#define SW_MEDIA_DEV_RSV            (SW_MEDIA_DEV_BASE + 4)        /* reserve    */
/* for control app. */
#define SW_PERIPHERAL_TIMER         (SW_MEDIA_DEV_RSV + 1)         /* TIMER      */
/* for display app. */
#define SW_PERIPHERAL_DISP          (SW_MEDIA_DEV_RSV + 2)         /* display    */
/* for DMA driver */
#define SW_PERIPHERAL_DMA           (SW_MEDIA_DEV_RSV + 3)         /* DMA        */
/* for math app. */
#define SW_MATH_DEV_BASE            (SW_MEDIA_DEV_RSV + 4)
#define SW_PERIPHERAL_CAL_IC        (SW_MATH_DEV_BASE)             /* ����оƬ   */
#define SW_PERIPHERAL_AD            (SW_MATH_DEV_BASE + 1)         /* AD         */

/* Get high byte or low byte from a WORD. */
#define GET_HIBYTE(wWord)           ((BYTE)(((wWord)>>8)&0x00FF))
#define GET_LOWBYTE(wWord)          ((BYTE)((wWord) & 0x00FF))
#define WORD_2_HILOW(wWord)         GET_HIBYTE(wWord),GET_LOWBYTE(wWord)
#define HILOW_2_WORD(ucHi,ucLow)    ((WORD)(ucHi<<8)|ucLow)
#define GET_LONG_WORD(pucData)      (((WORD32)(*(pucData)) <<24) + \
                                     ((WORD32)(*(pucData+1))<<16) + \
                                     ((WORD32)(*(pucData+2))<<8 ) + \
                                     ((WORD32)(*(pucData+3))))
#define GET_WORD(pucData)           (((WORD16)(*(pucData))  <<8) + \
                                     ((WORD16)(*(pucData+1))))
#define GET_LONG_LOW0(dwWord)        ((dwWord) & 0x000000ff)
#define GET_LONG_LOW1(dwWord)        (((dwWord) & 0x0000ff00)>>8)
#define GET_LONG_HI0(dwWord)         (((dwWord) & 0x00ff0000)>>16)
#define GET_LONG_HI1(dwWord)         (((dwWord) & 0xff000000)>>24)

/****************** �ж��¼����� *******************************/
#define INTERRUPT_EVENT_RX            (1)          /* receive interrupt.      */
#define INTERRUPT_EVENT_TX            (2)          /* transmition interrupt.  */
#define INTERRUPT_TIMER_OVER          (3)          /* timeover interrupt.     */
#define INTERRUPT_EVENT_ERR           (4)          /* device wrong interrupt. */
#define INTERRUPT_EVENT_CMP           (5)          /* camparison interrupt.   */
#define INTERRUPT_EVENT_CAP           (6)          /* capture interrupt.      */

#define DEV_POWER_UP                  (1)          /* �豸�ϵ� ��־ */
#define DEV_POWER_DOWN                (0)          /* �豸�µ��־  */

/**********************ͨ���Զ���******************************************/
#define SW_DEV_START                  (1)          /* �豸����      */
#define SW_DEV_STOP                   (0)          /* �豸ֹͣ      */
#define SW_NONE_MEANING               (0xff)       /* None��������    */
#define SW_DMA_ENABLE                 (1)          /* DMA��������   */
#define SW_DMA_DISABLE                (0)          /* DMA���ܹر�   */
#define SW_MASTER_DEVICE              (1)          /* �豸����      */
#define SW_SLAVE_DEVICE               (0)          /* �豸�ӻ�      */
#define SW_SERIAL_MSB_FIRST           (1)          /* ���ݸ�λ��ǰ  */
#define SW_SERIAL_LSB_FIRST           (0)          /* ���ݵ�λ��ǰ  */
#define SW_DEV_BUSY                   (1)          /* �豸æ        */
#define SW_DEV_IDLE                   (0)          /* �豸����      */

/******************************* ͨ�����ݽṹ���� ***************************/

/****************************************************
*   �ṹ����T_SW_INT_EVENT
*   ������  �ýṹ���������жϲ������ݣ������ж��¼���
*           ��Ʒ���͵ȣ������ⲿӦ�ô��������жϡ�
*           
*           
*   ������  ���嶨������������������壻
*   ���ߣ�        
*   Modified History��
*   2013-7-24          �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucAppType;           /* Ӧ������     */
    BYTE    ucDevId;             /* �豸����     */
    BYTE    ucDevNo;             /* �豸��       */
    BYTE    ucEvent;             /* �ж��¼����� */
    BYTE    ucBuffer[8];         /* ����         */
}T_SW_INT_EVENT;

/****************************************************
*   �ṹ����T_SW_DEVICEDRIVER_PARA
*   ������  �ýṹ���������������ݣ�һ������������ʼ��
*           �����������ơ�����������壬�ο�����������
*           �嶨�塣ÿ��������ʹ�øýṹʱ����Ҫ����ͷ
*           �ļ��У��������ÿ�������ľ��嶨�塣
*   ������  ���嶨������������������壻
*   ���ߣ�        
*   Modified History��
*   2013-7-24          �����ṹ��
****************************************************/
typedef struct
{
    VOID    (*pIntCallBackHandler)(T_SW_INT_EVENT *ptReason);              /* һ��ص�����ָ��                      */
    VOID    (*pExceptionIntCallBackHandler)(T_SW_INT_EVENT *ptReason);     /*  �쳣�ص�����ָ��                     */
    WORDPTR pdwPara[4];                                                    /* ��Դ��������������������Դ����Mem��ַ  */
    BYTE    ucPara[10];                                                    /* 10������������Ʒ/����ʹ�ô��ڲ���      */
    BYTE    *pucBuf;                                                       /* ������ָ��                            */
    WORD16  wBufLen;                                                       /* ����������                            */
}T_SW_DEVICEDRIVER_PARA;

/****************************************************
*   �ṹ����T_DATA_OPERARTION
*   ������  �ýṹ�������ݷ���ʱ�Ĳ������ݣ�����������
*           д�롢��ȡ�ȡ�
*           
*   ������  ���嶨������������������壻
*   ���ߣ�        
*   Modified History��
*   2013-7-24          �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucDevNo;             /* �豸��,0...     */
    BYTE    ucOperMode;          /* ����ģʽ        */
    BYTE    *pucBuffer;          /* ���ݻ�������ַ  */
    WORD16  wDataLength;         /* ���ݳ���        */
    WORDPTR dwDestAddr;          /* Ŀ���ַ        */
}T_DATA_OPERARTION;

/*********************************************************************
*  Structure  ��T_MSG_DEV
*  Description��RxTx message device parameter.
*               it is same to T_KNX_DEV.
*  Parameters ��  
                BYTE ucDevNo           device's hy/log No.
                BYTE ucPoolId          device's pool id.
                BYTE *puInBuffer       device's input buffer.
                BYTE *puOutBuffer      device's output buffer.
*   Author    ��Danny Cao.
*   Modify log��
*   2013-7-24         Creation��
**********************************************************************/
typedef struct
{
    BYTE ucDevNo;         /* device's phy/log No.    */
    BYTE ucPoolId;        /* device's rx pool id.    */
    BYTE *pucInBuffer;    /* device's input buffer.  */
    BYTE *pucOutBuffer;   /* device's output buffer. */
}T_MSG_DEV;

/*********************************************************************
*  Structure  ��T_MSG_SRC
*  Description��Message source description structure.
*               it is same to T_KNX_MSG_SRC.
*  Parameters ��  
                BYTE      ucTxPoolId  : sending buffer's pool ID.
                T_MSG_DEV *ptMsgDev   : relative KNX device.     
*   Author    ��Danny Cao.
*   Modify log��
*   2013-7-24         Creation��
**********************************************************************/
typedef struct
{
    BYTE      ucTxPoolId;     /* sending buffer's pool ID. */
    T_MSG_DEV *ptMsgDev;      /* relative KNX device.      */
}T_MSG_SRC;

/********************************************************************
*   �ṹ����T_DATA_BUFFER_HEADER
*   ������  data buffer header,it is same to T_BUFFER_HEADER
*   ������  
            BYTE *pucNext : next buffer's address.
            BYTE ucPoolId : buffer's pool ID.
*   Modified History��
*   2013-7-24         �����ṹ��
********************************************************************/
#pragma pack(1)
typedef struct
{
    BYTE *pucNext;     /* next buffer's address */
    BYTE ucPoolId;     /* buffer's pool ID.     */
}T_DATA_BUFFER_HEADER;
#pragma pack()

/*********************************************************************
*  Structure  ��T_MSG_BUFFER_HEADER
*  Description��Message buffer header description.
*               it is same to T_KNX_BUFFER_HEADER.
*  Parameters ��
*               T_DATA_BUFFER_HEADER tBfHeader :    buffer header.
*               BYTE *pucPayload               :    payload address.
*               BYTE ucLength;                 :    payload length.
*               BYTE ucMessInfo                :    message information.
*               BYTE ucDevNo                   :    device's No.
*               BYTE aucAddData[6]             :    additional data.
*   Author    ��Danny Cao.
*   Modify log��
*   2013-7-24         Creation��
**********************************************************************/
#pragma pack(1)
typedef struct
{
    T_DATA_BUFFER_HEADER tBfHeader;    /* buffer header.       */
    WORD16 wLength;                    /* payload length.      */
    BYTE   *pucPayload;                /* payload address.     */
    BYTE   ucMessInfo;                 /* message information. */
    BYTE   ucDevNo;                    /* device's No.         */
    BYTE   aucAddData[6];              /* additional data.     */
}T_MSG_BUFFER_HEADER;
#pragma pack()

#define SW_MSG_HEADER_LEN                      48    /* it's equal to TOTAL_KNX_BUFFER_HEADER_LEN. */

#define GET_MSG_PAYLOAD(pucBuffer)             ((T_MSG_BUFFER_HEADER*)pucBuffer)->pucPayload
#define GET_MSG_LENGTH(pucBuffer)              ((T_MSG_BUFFER_HEADER*)pucBuffer)->wLength
#define GET_MSG_MSG_INFO(pucBuffer)            ((T_MSG_BUFFER_HEADER*)pucBuffer)->ucMessInfo
#define GET_MSG_DEV_NO(pucBuffer)              ((T_MSG_BUFFER_HEADER*)pucBuffer)->ucDevNo
#define GET_MSG_ADD_DATA_POINT(pucBuffer)      ((T_MSG_BUFFER_HEADER*)pucBuffer)->aucAddData
#define GET_MSG_POOL_ID(pucBuffer)             ((T_BUFFER_HEADER*)pucBuffer)->ucPoolId
#define GET_MSG_NEXT(pucBuffer)                ((T_BUFFER_HEADER*)pucBuffer)->pucNext


/* �����ӿں���(DRV_FUNC)���� */
typedef WORD32 (*DRV_FUNC)            (T_SW_DEVICEDRIVER_PARA *ptPara);
typedef WORD32 (*SW_DATA_ACCESS_FUNC) (T_DATA_OPERARTION *ptPara);
typedef VOID   (*DEV_REG)             (BYTE ucLogicDevNo,BYTE ucDevNo,VOID *ptPara);
typedef BOOL   (*APP_HANDLER)         (VOID);
typedef VOID   (*CALLBACK_HANDLER)    (T_SW_INT_EVENT *ptReason);
/* ADC operation handler. ucChnl:oper. channel,ucCunt:sample count,*wData:returning data. */
typedef BOOL   (*APP_ADC_HANDLER)(BYTE ucDevNo,BYTE ucChnl,BYTE ucCunt,WORD16 *wData);


/****************************************************
*   �ṹ����T_DEV_OPERATION
*   ������  �ýṹ������������ע�ᣬ����������صĲ���
*           �ӿڡ�
*           
*   ������  pfDrvRead�� �������ݶ�ȡ�ӿ�
            pfDrvWrite����������д��ӿ�
            pfDrvInit�� ������ʼ���ӿ�
            pfDrvCtrl�� �������ƺ����ýӿ�
*   ���ߣ�        
*   Modified History��
*   2013-7-24          �����ṹ��
****************************************************/
typedef struct 
{
    DRV_FUNC               pfDrvInit;    /** init    */
    DRV_FUNC               pfDrvCtrl;    /** ctrl    */
    SW_DATA_ACCESS_FUNC    pfDrvRead;    /** read    */
    SW_DATA_ACCESS_FUNC    pfDrvWrite;   /** write   */
}T_DEV_OPERATION;

/****************************************************
*   �ṹ����T_REGISTED_DEVICE
*   ������  �ýṹ��������ע�ᣬ����������صĲ���
*           �ӿڡ�
*           
*   ������  ucAppType ���豸���ڵ�Ӧ�����ͣ�����ͨѶ
            ucDevId   ���豸����ID
            ucLogDevNo���߼��豸��
            ucDevNo   ���豸�����
            ptDevOp   ���豸���������ӿ�
*   ���ߣ�        
*   Modified History��
*   2013-7-24          �����ṹ��
****************************************************/
typedef struct
{
    BYTE             ucAppType;          /* Ӧ������          */
    BYTE             ucDevId;            /* �豸����          */
    BYTE             ucLogDevNo;         /* �߼��豸��,0....  */
    BYTE             ucDevNo;            /* �����豸��,0....  */
    T_DEV_OPERATION *ptDevOp;            /* �豸�����ӿ�      */
    CALLBACK_HANDLER pfCallBack;         /* �豸�ҽӻص����. */
}T_REGISTED_DEVICE;

/****************************************************
*   �ṹ����T_DEV_DISC
*   ������  �豸�����ṹ��
*           
*   ������  ucAppType ���豸���ڵ�Ӧ�����ͣ�����ͨѶ
            ucDevId   ���豸����ID
            ucLogDevNo���߼��豸��,��0��ʼ
            ucDevNo   ���豸�����,��0��ʼ
            ptDevOp   ���豸ע��ӿ�
*   ���ߣ�        
*   Modified History��
*   2013-7-24          �����ṹ��
****************************************************/
typedef struct
{
    BYTE     ucAppType;          /* Ӧ������          */
    BYTE     ucDevId;            /* �豸����          */
    BYTE     ucLogDevNo;         /* �߼��豸��,0....  */
    BYTE     ucDevNo;            /* �����豸��,0....  */
    DEV_REG  pfDevRegister;      /* �豸ע��ӿڽӿ�  */
}T_DEV_DISC; 




/******************************** ����ԭ�Ͷ��� *****************************/




#ifdef __cplusplus
}
#endif

#endif /* _SW_COMMON_H_ */

/* End-of-file */


