/********************************************************************
* Right reserved (C 2019) Shufan information technology company.
*
* File Name        : Knx_M0705_Ll.h
*
* File Description : link layer head file for M0705.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : Danny Cao
*
* Data             : 2019.4.1
*
* Modification Rec.:
*   Modify Data    : 2019.4.1
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
********************************************************************/


#ifndef _KNX_M0705_LL_H_
#define _KNX_M0705_LL_H_

#ifdef __cplusplus
extern "C" {
#endif


#define KNX_LL_GET_IN_PAYLOAD      ((T_KNX_BUFFER_HEADER *)sg_KnxLlDev.pucInBuffer)->pucPayload
#define KNX_LL_GET_IN_LENGTH       ((T_KNX_BUFFER_HEADER *)sg_KnxLlDev.pucInBuffer)->wLength
#define KNX_LL_GET_IN_DEVNO        ((T_KNX_BUFFER_HEADER *)sg_KnxLlDev.pucInBuffer)->ucDevNo
#define KNX_LL_GET_IN_MSGINFO      ((T_KNX_BUFFER_HEADER *)sg_KnxLlDev.pucInBuffer)->ucMessInfo



/******************* state machine define **********************/
#define KNXLL_NEW_FRM_IDLE            (0)
#define KNXLL_NEW_FRM_ST              (1)

/****** rx state machine ************/
#define KNXLL_RX_STOPPED              (0)      /* Receive process is stopped                                      */
#define KNXLL_RX_IDLE                 (1)      /* Receive process is idle,receive control byte.                   */
#define KNXLL_RX_EXCTRL               (2)      /* Receive process is waiting for ex-control byte.                 */
#define KNXLL_RX_SRCADDR_HI           (3)      /* Receive process is waiting for high byte of source address      */
#define KNXLL_RX_SRCADDR_LO           (4)      /* Receive process is waiting for low byte of source address       */
#define KNXLL_RX_DESTADDR_HI          (5)      /* Receive process is waiting for high byte of destination address */
#define KNXLL_RX_DESTADDR_LO          (6)      /* Receive process is waiting for low byte of destination address  */
#define KNXLL_RX_ATYPE_BYTE           (7)      /* Receive process is waiting for ATYPE byte                       */
#define KNXLL_RX_DATA                 (8)      /* Receive process is waiting for remain data                      */
#define KNXLL_RX_CHECKSUM             (9)      /* Receive process is waiting for check sum                        */
#define KNXLL_RX_IGNORE_DATA          (10)     /* Receive process ignore the data                                 */

#define KNXLL_RCV_OVER_TIMER           (5)     /* at the end of the last data(not checksum), there will be max. 4.16ms(15bits + 13bits + 11bits)free space. */
#define KNXLL_REC_ACK_OVER_TIMER       (4)     /* time for waiting ACK. the end of a tx frame will be followed with a ACK with late 2.7ms(15bits + 11bits(ack)).*/
#define KNXLL_TX_OVER_SEG_TIMER        (192)   /* max. 23*13*5 + (15+11+53)*4 + 15 + 11 bits.              */
#define KNXLL_TX_REPEAT_TIMER          (113)   /* time of repeat 3 times. 53 + 23*13*3 + (15+11+53)*2 bits.*/

/****  Position of clearing Rx Busy in LL *************/
#define LL_CLR_RXBUSY_POS_RXEND        0x00    /* position of clearing rx busy status is in rx end. */
#define LL_CLR_RXBUSY_POS_ACK          0x01    /* position of clearing rx busy status is in ACK.    */
#define LL_CLR_RXBUSY_POS_NACK         0x02    /* position of clearing rx busy status is in NACK.   */
#define LL_CLR_RXBUSY_POS_INGNORE      0x03    /* position of clearing rx busy status is in ingnore.*/

/********** ll related ***************/
#define MAX_FRAME_LENGTH             24
#define MIN_FRAME_LENGTH             7
#define MAX_FRAME_DATA_LEN           16        /* valid data + checksum. */
/* Frame ex/std type mask */
#define LL_FRAME_TYPE_MASK          0xD3    /* 1101 1100 */
#define LL_FRAME_STANDARD_MASK       0x90    /* standard frame mask.    */
#define LL_FRAME_EXTENDED_MASK       0x10    /* extended frame mask.    */
#define LL_HIGHER_PRIORITY_MASK      0x04    /* higher priority mask.   */
/* Assemble frame type */
#define LL_FRAME_TYPE_FLAG_MASK      0x30                                                /* mask for frame detail. */
#define LL_FRAME_STANDARD_FLG        0x10
#define LL_FRAME_EXTENDED_FLG        0x20
#define LL_STANDARD_P2P_FRAME        (KNX_STANDARD_FRAME_P2P | LL_FRAME_STANDARD_FLG)    /* 0x10:P2P standard frame.  Bit7:0-Phy,Bit5Bit4:01-Standard. */
#define LL_STANDARD_GRP_FRAME        (KNX_STANDARD_FRAME_GRP | LL_FRAME_STANDARD_FLG)    /* 0x90:Group standard frame.Bit7:1-Grp,Bit5Bit4:01-Standard. */
#define LL_EXTENDED_P2P_FRAME        (KNX_EXTENDED_FRAME_P2P | LL_FRAME_EXTENDED_FLG)    /* 0x20:P2P extended frame.  Bit7:0-Phy,Bit5Bit4:10-Extended. */
#define LL_EXTENDED_GRP_FRAME        (KNX_EXTENDED_FRAME_GRP | LL_FRAME_EXTENDED_FLG)    /* 0xA0:Group extended frame.Bit7:1-Grp,Bit5Bit4:10-Extended. */
#define LL_EXTENDED_LTE_FRAME        (KNX_EXTENDED_FRAME_LTE | LL_FRAME_EXTENDED_FLG)    /* 0xA4:LTE extended frame.             */
#define LL_FRAME_ADDR_TYPE_MASK      0x80                                                /* Bit7:0-Phy,1-Grp                     */
#define LL_UNKNOWN_FRAME             (0xFF)                                              /* Unknown frame.                       */
#define LL_REASSEMBLE_DESTADDR_TYPE  (0x00020000)


#define KNX_LL_BUFFER_SIZE          KNX_MSG_BUFFER_SIZE

/*link layer's destination address state define. */
#define KNXLL_DEST_ADDR_GRP_H       (KNX_ADDR_PASS + 1)         /* Group address high byte is match. */
#define KNXLL_DEST_ADDR_GRP_B       (KNX_ADDR_PASS + 2)         /* Group address is match.           */


/********************** function type ******************************/
typedef VOID (*KnxLl_ConfirmEntry)(BYTE);
typedef VOID (*KnxLl_ByteRxEntry)(BYTE,BYTE);
typedef VOID (*KnxLl_FrameEndEntry)(VOID);



/****************************************************************************************************************
* Function: WORD32 KnxLl_Init(BYTE ucBufferNum,BYTE ucBufferSize)
* Descrip.: link layer initialization entry.
* Input   : BYTE ucBufferNum : buffer number.
*           BYTE uxBufferSize: buffer size.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
WORD32 KnxLl_Init(BYTE ucBufferNum,BYTE ucBufferSize);

/****************************************************************************************************************
* Function: BOOL KnxLl_SetTxBuffer(BYTE *pucBuffer)
* Descrip.: link layer sets a tx frame to PH.
* Input   : BYTE *pucBuffer : buffer waiting for setting.
* Output  : none.
* Return  : TRUE : can be txed.
*           FALSE: can not be txed.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
BOOL KnxLl_SetTxBuffer(BYTE *pucBuffer);

/****************************************************************************************************************
* Function: WORD32 KnxLl_DevReg(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum)
* Descrip.: Message device regiter into link layer by this function.
* Input   : BYTE ucLogNo:device's logical No.
            BYTE ucPhyNo:device's physical No.
            WORD16 wRxBufNum:buffer count for receiving.it should be bigger than 0.
            WORD16 wTxBufNum:buffer count for transmitting.it should be bigger than 0.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
WORD32 KnxLl_DevReg(BYTE ucLogNo,BYTE ucPhyNo,WORD16 wRxBufNum,WORD16 wTxBufNum);

/****************************************************************************************************************
* Function: VOID KnxLl_PhDevReg(T_KNX_CHIP_OP *ptPhDev)
* Descrip.: entry for physical chip device regitering to the link layer.
* Input   : T_KNX_CHIP_OP *ptPhDev : physical layer device's operation entry.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxLl_PhDevReg(T_KNX_CHIP_OP *ptPhDev);

/****************************************************************************************************************
* Function: VOID KnxLl_Process(VOID)
* Descrip.: link layer process entry.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxLl_Process(VOID);

/****************************************************************************************************************
* Function: BOOL KnxLl_HaveToWaitCheck(VOID)
* Descrip.: link layer have to complete status when running.
* Input   : none.
* Output  : none.
* Return  : TRUE : should be wait.
*           FALSE: may go on.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
BOOL KnxLl_HaveToWaitCheck(VOID);

/****************************************************************************************************************
* Function: VOID KnxLl_DisDev_Rx(VOID)
* Descrip.: Disable link layer rx.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxLl_DisDev_Rx(VOID);


#ifdef __cplusplus
}
#endif

#endif /* _KNX_M0705_LL_H_ */




