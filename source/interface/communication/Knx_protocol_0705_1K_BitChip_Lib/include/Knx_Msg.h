/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：KnxIp_core.h
* FileIdentifier：None
* Abstract ：knx ip core header file.
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


#ifndef _KNX_MSG_H_
#define _KNX_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif


#define KNX_SDEV_MAX_CUNT              1          /* KNX second device's Max. count. */
#define KNX_MDEV_MAX_CUNT              6          /* KNX main side device's number.  */


/* device information of buffer. Bit0-3:the source device flag&No.Bit4-7:the destination device flag&No. */
#define KNX_SRC_SIDE_MASK              0x08       /* the mask of the source device in the buffer header. */
#define KNX_SRC_SLAV_DEV               0x00       /* Source:second side device. */
#define KNX_SRC_MAIN_DEV               0x08       /* Source:main side device. */
#define KNX_DEST_SIDE_MASK             0x80       /* the mask of the destination device in the buffer header. */
#define KNX_DEST_SLAV_DEV              0x00       /* Destination:seconde side device. */
#define KNX_DEST_MAIN_DEV              0x80       /* Destination:main side device. */
#define KNX_SRC_DEV_NO_MASK            0x07       /* the mask for getting the source device's No. */
#define KNX_DEST_DEV_NO_MASK           0x70       /* the mask for getting the destination device's No. */
#define KNX_SRC_DEVNO_CLR              0xF8       /* clear the source device No. */
#define KNX_DEST_DEVNO_CLR             0x8F       /* clear the destination device No. */

/* message information definition. */
#define KNX_MSG_LAYER_MASK             0xC0       /* Mask for msg layer type.bit6-7:layer type.*/
#define KNX_MSG_PHY_LAYER              0x00       /* message for physical layer.  */
#define KNX_MSG_LINK_LAYER             0x40       /* message for link layer.      */
#define KNX_MSG_NET_LAYER              0x80       /* message for network layer.   */
#define KNX_MSG_MGM_LAYER              0xC0       /* message for Mgm layer.       */
#define KNX_MSG_CNT_ID_MASK            0x3F       /* bit4-5:PortNo,bit0-3:connect channel No. */

#define GET_BUFFER_PAYLOAD(pucBuffer)             ((T_KNX_BUFFER_HEADER*)pucBuffer)->pucPayload
#define GET_BUFFER_LENGTH(pucBuffer)              ((T_KNX_BUFFER_HEADER*)pucBuffer)->wLength
#define GET_BUFFER_MSG_INFO(pucBuffer)            ((T_KNX_BUFFER_HEADER*)pucBuffer)->ucMessInfo
#define GET_BUFFER_DEV_NO(pucBuffer)              ((T_KNX_BUFFER_HEADER*)pucBuffer)->ucDevNo
#define GET_BUFFER_ADD_DATA_POINT(pucBuffer)      ((T_KNX_BUFFER_HEADER*)pucBuffer)->aucAddData
#define GET_BUFFER_POOL_ID(pucBuffer)             ((T_BUFFER_HEADER*)pucBuffer)->ucPoolId
#define GET_BUFFER_NEXT(pucBuffer)                ((T_BUFFER_HEADER*)pucBuffer)->pucNext


#define KNX_MSG_BUFFER_SIZE            128        /* KNX message's buffer size.                   */
#define NETIP_BUFFER_SIZE              1600       /* buffer size for net ip.                      */

/* define socket attribute. */
#define KNXIP_SOCKET_DATA              0          /* socket for data point.    */
#define KNXIP_SOCKET_CTRL              1          /* socket for control point. */

/* socket NO. define. */
#define DHCP_SCK_NO                            0  /* socket for DHCP.       */
#define DATA_POINT_SCK_NO                      1  /* socket for data point. */
#define CTRL_POINT_SCK0_NO                     2  /* socket for port0's control point. */
#define CTRL_POINT_SCK1_NO                     3  /* socket for port1's control point. */
#define CTRL_POINT_SCK2_NO                     4  /* socket for port2's control point. */
#define CTRL_POINT_SCK3_NO                     5  /* socket for port3's control point. */
#define ERROR_SCK_NO                           0xff /* wrong socket No. */

#define TOTAL_KNX_BUFFER_HEADER_LEN  32         /* the lenght from the buffer header to the Knx subnet Msg header.from the next address to Mesage code. */

#define KNX_BUFFER_FOR_KNX           0   /* buffer used for KNX frame dealing. */
#define KNX_BUFFER_FOR_IP            1   /* buffer used for KNX IP frame dealing. */

/****************************************************
*   结构名：T_KNX_DEV
*   描述：  KNX message device parameter。
*   参数：  
            BYTE ucDevNo           device's physical No.    
            BYTE ucPoolId          device's pool id.        
            BYTE *puInBuffer       device's input buffer.   
            BYTE *puOutBuffer      device's output buffer.  
*   作者：  Jackson
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE ucDevNo;         /* device's physical No.   */
    BYTE ucPoolId;        /* device's pool id.       */
    BYTE *pucInBuffer;    /* device's input buffer.  */
    BYTE *pucOutBuffer;   /* device's output buffer. */
}T_KNX_DEV;

/****************************************************
*   结构名：T_KNX_MSG_SRC
*   描述：  the message source struct。
*   参数：  
            BYTE ucTxPoolId     : sending buffer's pool ID.
            BYTE *pucTxBuffer   : sending buffer's chain.  
            T_KNX_DEV *ptKnxDev : relative KNX device.     
*   作者：  Jackson
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
typedef struct
{
    BYTE ucTxPoolId;     /* sending buffer's pool ID. */
    T_KNX_DEV *ptKnxDev; /* relative KNX device.      */
}T_KNX_MSG_SRC;

/****************************************************
*   结构名：T_KNX_BUFFER_HEADER
*   描述：  KNX buffer的头部定义。
*   参数：  
*           T_BUFFER_HEADER tBfHeader : buffer header.
*           BYTE *pucPayload          :    payload address.
*           BYTE ucLength;            :    payload length.
*           BYTE ucMessInfo           :    message information.
*           BYTE ucDevNo              :    device's No.
*           BYTE aucAddData[6]        :    additional data.
*   作者：  Jackson
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    T_BUFFER_HEADER tBfHeader;    /* buffer header.       */
    WORD16 wLength;               /* payload length.      */
    BYTE   *pucPayload;           /* payload address.     */
    BYTE   ucMessInfo;            /* message information. */
    BYTE   ucDevNo;               /* device's No.         */
    BYTE   aucAddData[6];         /* additional data.     */
}T_KNX_BUFFER_HEADER;
#pragma pack()

/**************************************************************************************************************
* FunctionName:BYTE KnxMsg_GetDevTxPool(BYTE ucDevNo)
* FunctionDescription: get the device's tx pool id.
* InputParameterBYTE ucDevNo : Bit3   - side flag;
                           Bit0~2 - device No.
* Return Value：BYTE : Tx pool Id.
* Other Description:this function can be used to get the tx pool Id by the device No.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxMsg_GetDevTxPool(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_MsgProcess(VOID)
* FunctionDescription: KNX消息处理总入口。
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_MsgProcess(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_MsgInit(VOID)
* FunctionDescription: KNX message handler initialization.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_MsgInit(VOID);

/**************************************************************************
* FunctionName:BYTE* Knx_Buffer_Alloc(BYTE ucPoolId,BYTE ucUseFlg)
* FunctionDescription: 从buffer子池中分配一个buffer用于Knx消息处理。
* InputParameterBYTE ucPoolId : pool Id.
            BYTE ucUseFlg : KNX_BUFFER_FOR_KNX
                            KNX_BUFFER_FOR_IP
* OutputParameterNone
* Return Value：NULL  : buffer子池分配失败
                    其他，成功的buffer指针
* Other Description:(1)KnxIP frame format is as below:
            |sizeof(WORDPTR) for next frame address|1byte for Pool Id|1byte KNX payload length|1byte Knx payload offset|socket No.|Ip&port|data...|
            (2)the return point pints to the buffer header saving the next buffer's address. 
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0         Caoxw          Create  
**************************************************************************/
BYTE* Knx_Buffer_Alloc(BYTE ucPoolId,BYTE ucUseFlg);

/**************************************************************************
* FunctionName:VOID KnxIp_Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer)
* FunctionDescription: 从buffer子池中分配一个buffer用于Knx Ip消息处理。
* InputParameterBYTE ucPoolId : pool Id.
* OutputParameterNone
* Return Value：NULL  : buffer子池分配失败
                    其他，成功的buffer指针
* Other Description:
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0         Caoxw          Create  
**************************************************************************/
VOID Knx_Buffer_Free(BYTE ucPoolId,BYTE *pucBuffer);

/**************************************************************************************************************
* FunctionName:VOID Knx_MsgDelUserMsg(VOID)
* FunctionDescription: delete an input frame.
* InputParameterBYTE *pucUpFrame:up frame buffer,point to the header of buffer.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_MsgDelUserMsg(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_MsgDev_Reg(BYTE ucSideFlg,BYTE ucLogNo,T_KNX_DEV *ptKnxDev,WORD16 wTxBufNum)
* FunctionDescription: KNX消息源设备注册接口。
* InputParameterBYTE ucSideFlg      : register device's flag：
                                  KNX_SRC_MAIN_DEV   : the device is in the main side.
                                  KNX_SRC_SLAV_DEV   : the device is in the second side.
            BYTE ucLogNo        : register device's logical No.begin with 0.
            T_KNX_DEV *ptKnxDev : discription structure of the register device.
            WORD16 wTxBufNum    : count of buffers for transmitting.
* OutputParameterno.
* Return Value：no.
* Other Description:(1)the logical device No. begins with 0.
            (2)the device should be registered in sequence.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_MsgDev_Reg(BYTE ucSideFlg,BYTE ucLogNo,T_KNX_DEV *ptKnxDev,WORD16 wTxBufNum);

/****************************************************************************************************************
* Function: VOID Knx_MsgSet_InFrameTime(WORD32 dwDly)
* Descrip.: Set the input frmaes' time.
* Input   : WORD32 dwDly : delay time for tx.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID Knx_MsgSet_InFrameTime(WORD32 dwDly);



#ifdef __cplusplus
}
#endif

#endif /* _KNX_MSG_H_ */



/* end of file. */


