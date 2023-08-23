/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：sw_common.h
* FileIdentifier：None
* Abstract ：本文件为嵌入式系统软件驱动、接口相关公共定义。
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

#include "type_def.h"

#ifndef _SW_COMMON_H_
#define _SW_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/************************* 通用宏定义定义 *******************************/
#define   SW_DEVAPP_TYPE_RSV     (0x08)  /* 保留   */


                /* 存储类型定义 */
#define   SW_SVMWDIA_EEPROM      (0x01)  /* EEPROM */
#define   SW_SVMEDIA_FRAM        (0x02)  /* Fram   */
#define   SW_SVMEDIA_FLASH       (0x03)  /* Flash  */

                /* 通讯类型定义 */
#define   SW_COMM_MEDIA_485      (0x01)  /* 485    */
#define   SW_COMM_MEDIA_CAN      (0x02)  /* CAN    */
#define   SW_COMM_MEDIA_232      (0x03)  /* 232    */
#define   SW_COMM_MEDIA_ETH      (0x04)  /* 以太网 */
#define   SW_COMM_MEDIA_IR       (0x05)  /* 红外   */
#define   SW_COMM_MEDIA_I2C      (0x06)  /* I2C    */
#define   SW_COMM_MEDIA_SPI      (0x07)  /* SPI    */
#define   SW_COMM_MEDIA_SOCKET   (0x08)  /* SOCKET */

               /* 计量等数据来源类型 */
#define   SW_DATA_MEDIA_AD       (0x01)  /* 数据从AD获取       */
#define   SW_DATA_MEDIA_IC       (0x02)  /* 数据从计量芯片获取 */

               /* 控制类型定义 */
#define   SW_CONTROL_RELAY       (0x01)  /* 继电器控制 */
#define   SW_CONTROL_WTCHDOG     (0x02)  /* 看门狗控制 */
#define   SW_CONTROL_TIMER       (0x03)  /* 定时器     */

               /* 显示设备类型 */
#define   SW_DISP_MEDIA_SEGLED   (0x01)  /* 数码管 */
#define   SW_DISP_MEDIA_LCD      (0x02)  /* 液晶   */

/*********************** 外设模块ID定义 *****************************/
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
#define SW_PERIPHERAL_CAL_IC        (SW_MATH_DEV_BASE)             /* 计量芯片   */
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

/****************** 中断事件定义 *******************************/
#define INTERRUPT_EVENT_RX            (1)          /* receive interrupt.      */
#define INTERRUPT_EVENT_TX            (2)          /* transmition interrupt.  */
#define INTERRUPT_TIMER_OVER          (3)          /* timeover interrupt.     */
#define INTERRUPT_EVENT_ERR           (4)          /* device wrong interrupt. */
#define INTERRUPT_EVENT_CMP           (5)          /* camparison interrupt.   */
#define INTERRUPT_EVENT_CAP           (6)          /* capture interrupt.      */

#define DEV_POWER_UP                  (1)          /* 设备上电 标志 */
#define DEV_POWER_DOWN                (0)          /* 设备下点标志  */

/**********************通用性定义******************************************/
#define SW_DEV_START                  (1)          /* 设备启动      */
#define SW_DEV_STOP                   (0)          /* 设备停止      */
#define SW_NONE_MEANING               (0xff)       /* None意义数据    */
#define SW_DMA_ENABLE                 (1)          /* DMA功能启用   */
#define SW_DMA_DISABLE                (0)          /* DMA功能关闭   */
#define SW_MASTER_DEVICE              (1)          /* 设备主机      */
#define SW_SLAVE_DEVICE               (0)          /* 设备从机      */
#define SW_SERIAL_MSB_FIRST           (1)          /* 数据高位先前  */
#define SW_SERIAL_LSB_FIRST           (0)          /* 数据低位在前  */
#define SW_DEV_BUSY                   (1)          /* 设备忙        */
#define SW_DEV_IDLE                   (0)          /* 设备空闲      */

/******************************* 通用数据结构定义 ***************************/

/****************************************************
*   结构名：T_SW_INT_EVENT
*   描述：  该结构用于驱动中断参数传递，传递中断事件、
*           产品类型等，用于外部应用处理驱动中断。
*           
*           
*   参数：  具体定义见各个具体驱动定义；
*   作者：        
*   Modified History：
*   2013-7-24          新增结构；
****************************************************/
typedef struct
{
    BYTE    ucAppType;           /* 应用类型     */
    BYTE    ucDevId;             /* 设备类型     */
    BYTE    ucDevNo;             /* 设备号       */
    BYTE    ucEvent;             /* 中断事件类型 */
    BYTE    ucBuffer[8];         /* 参数         */
}T_SW_INT_EVENT;

/****************************************************
*   结构名：T_SW_DEVICEDRIVER_PARA
*   描述：  该结构用于驱动参数传递，一般用于驱动初始化
*           或者驱动控制。具体参数定义，参考各个驱动具
*           体定义。每个驱动在使用该结构时，需要在其头
*           文件中，描述清楚每个参数的具体定义。
*   参数：  具体定义见各个具体驱动定义；
*   作者：        
*   Modified History：
*   2013-7-24          新增结构；
****************************************************/
typedef struct
{
    VOID    (*pIntCallBackHandler)(T_SW_INT_EVENT *ptReason);              /* 一般回调函数指针                      */
    VOID    (*pExceptionIntCallBackHandler)(T_SW_INT_EVENT *ptReason);     /*  异常回调函数指针                     */
    WORDPTR pdwPara[4];                                                    /* 资源参数，用于描述外设资源，如Mem地址  */
    BYTE    ucPara[10];                                                    /* 10个参数，各产品/驱动使用存在差异      */
    BYTE    *pucBuf;                                                       /* 缓冲区指针                            */
    WORD16  wBufLen;                                                       /* 缓冲区长度                            */
}T_SW_DEVICEDRIVER_PARA;

/****************************************************
*   结构名：T_DATA_OPERARTION
*   描述：  该结构用于数据访问时的参数传递，可用于数据
*           写入、读取等。
*           
*   参数：  具体定义见各个具体驱动定义；
*   作者：        
*   Modified History：
*   2013-7-24          新增结构；
****************************************************/
typedef struct
{
    BYTE    ucDevNo;             /* 设备号,0...     */
    BYTE    ucOperMode;          /* 操作模式        */
    BYTE    *pucBuffer;          /* 数据缓冲区地址  */
    WORD16  wDataLength;         /* 数据长度        */
    WORDPTR dwDestAddr;          /* 目标地址        */
}T_DATA_OPERARTION;

/*********************************************************************
*  Structure  ：T_MSG_DEV
*  Description：RxTx message device parameter.
*               it is same to T_KNX_DEV.
*  Parameters ：  
                BYTE ucDevNo           device's hy/log No.
                BYTE ucPoolId          device's pool id.
                BYTE *puInBuffer       device's input buffer.
                BYTE *puOutBuffer      device's output buffer.
*   Author    ：Danny Cao.
*   Modify log：
*   2013-7-24         Creation；
**********************************************************************/
typedef struct
{
    BYTE ucDevNo;         /* device's phy/log No.    */
    BYTE ucPoolId;        /* device's rx pool id.    */
    BYTE *pucInBuffer;    /* device's input buffer.  */
    BYTE *pucOutBuffer;   /* device's output buffer. */
}T_MSG_DEV;

/*********************************************************************
*  Structure  ：T_MSG_SRC
*  Description：Message source description structure.
*               it is same to T_KNX_MSG_SRC.
*  Parameters ：  
                BYTE      ucTxPoolId  : sending buffer's pool ID.
                T_MSG_DEV *ptMsgDev   : relative KNX device.     
*   Author    ：Danny Cao.
*   Modify log：
*   2013-7-24         Creation；
**********************************************************************/
typedef struct
{
    BYTE      ucTxPoolId;     /* sending buffer's pool ID. */
    T_MSG_DEV *ptMsgDev;      /* relative KNX device.      */
}T_MSG_SRC;

/********************************************************************
*   结构名：T_DATA_BUFFER_HEADER
*   描述：  data buffer header,it is same to T_BUFFER_HEADER
*   参数：  
            BYTE *pucNext : next buffer's address.
            BYTE ucPoolId : buffer's pool ID.
*   Modified History：
*   2013-7-24         新增结构；
********************************************************************/
#pragma pack(1)
typedef struct
{
    BYTE *pucNext;     /* next buffer's address */
    BYTE ucPoolId;     /* buffer's pool ID.     */
}T_DATA_BUFFER_HEADER;
#pragma pack()

/*********************************************************************
*  Structure  ：T_MSG_BUFFER_HEADER
*  Description：Message buffer header description.
*               it is same to T_KNX_BUFFER_HEADER.
*  Parameters ：
*               T_DATA_BUFFER_HEADER tBfHeader :    buffer header.
*               BYTE *pucPayload               :    payload address.
*               BYTE ucLength;                 :    payload length.
*               BYTE ucMessInfo                :    message information.
*               BYTE ucDevNo                   :    device's No.
*               BYTE aucAddData[6]             :    additional data.
*   Author    ：Danny Cao.
*   Modify log：
*   2013-7-24         Creation；
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


/* 驱动接口函数(DRV_FUNC)定义 */
typedef WORD32 (*DRV_FUNC)            (T_SW_DEVICEDRIVER_PARA *ptPara);
typedef WORD32 (*SW_DATA_ACCESS_FUNC) (T_DATA_OPERARTION *ptPara);
typedef VOID   (*DEV_REG)             (BYTE ucLogicDevNo,BYTE ucDevNo,VOID *ptPara);
typedef BOOL   (*APP_HANDLER)         (VOID);
typedef VOID   (*CALLBACK_HANDLER)    (T_SW_INT_EVENT *ptReason);
/* ADC operation handler. ucChnl:oper. channel,ucCunt:sample count,*wData:returning data. */
typedef BOOL   (*APP_ADC_HANDLER)(BYTE ucDevNo,BYTE ucChnl,BYTE ucCunt,WORD16 *wData);


/****************************************************
*   结构名：T_DEV_OPERATION
*   描述：  该结构用于用于驱动注册，描述驱动相关的操作
*           接口。
*           
*   参数：  pfDrvRead： 驱动数据读取接口
            pfDrvWrite：驱动数据写入接口
            pfDrvInit： 驱动初始化接口
            pfDrvCtrl： 驱动控制和配置接口
*   作者：        
*   Modified History：
*   2013-7-24          新增结构；
****************************************************/
typedef struct 
{
    DRV_FUNC               pfDrvInit;    /** init    */
    DRV_FUNC               pfDrvCtrl;    /** ctrl    */
    SW_DATA_ACCESS_FUNC    pfDrvRead;    /** read    */
    SW_DATA_ACCESS_FUNC    pfDrvWrite;   /** write   */
}T_DEV_OPERATION;

/****************************************************
*   结构名：T_REGISTED_DEVICE
*   描述：  该结构用于驱动注册，描述驱动相关的操作
*           接口。
*           
*   参数：  ucAppType ：设备属于的应用类型，比如通讯
            ucDevId   ：设备驱动ID
            ucLogDevNo：逻辑设备号
            ucDevNo   ：设备物理号
            ptDevOp   ：设备驱动操作接口
*   作者：        
*   Modified History：
*   2013-7-24          新增结构；
****************************************************/
typedef struct
{
    BYTE             ucAppType;          /* 应用类型          */
    BYTE             ucDevId;            /* 设备类型          */
    BYTE             ucLogDevNo;         /* 逻辑设备号,0....  */
    BYTE             ucDevNo;            /* 物理设备号,0....  */
    T_DEV_OPERATION *ptDevOp;            /* 设备操作接口      */
    CALLBACK_HANDLER pfCallBack;         /* 设备挂接回调入口. */
}T_REGISTED_DEVICE;

/****************************************************
*   结构名：T_DEV_DISC
*   描述：  设备描述结构。
*           
*   参数：  ucAppType ：设备属于的应用类型，比如通讯
            ucDevId   ：设备驱动ID
            ucLogDevNo：逻辑设备号,从0开始
            ucDevNo   ：设备物理号,从0开始
            ptDevOp   ：设备注册接口
*   作者：        
*   Modified History：
*   2013-7-24          新增结构；
****************************************************/
typedef struct
{
    BYTE     ucAppType;          /* 应用类型          */
    BYTE     ucDevId;            /* 设备类型          */
    BYTE     ucLogDevNo;         /* 逻辑设备号,0....  */
    BYTE     ucDevNo;            /* 物理设备号,0....  */
    DEV_REG  pfDevRegister;      /* 设备注册接口接口  */
}T_DEV_DISC; 




/******************************** 函数原型定义 *****************************/




#ifdef __cplusplus
}
#endif

#endif /* _SW_COMMON_H_ */

/* End-of-file */


