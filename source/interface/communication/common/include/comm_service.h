/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��comm_service.h
* FileIdentifier��None
* Abstract �����ļ�ΪͨѶ�ӿڲ㹫��ͷ�ļ����塣
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

#ifndef _COMM_SERVICE_H_
#define _COMM_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


/******************** UART��ز������� ***********************/
#define SW_UART_PARITY_NO        (0)         /* ��żУ��ر� */
#define SW_UART_PARITY_ODD       (1)         /* ��У�鷽ʽ   */
#define SW_UART_PARITY_EVEN      (2)         /* żУ�鷽ʽ   */

#define SW_UART_STOP_BIT_ONE     (1)         /* 1λֹͣλ    */
#define SW_UART_STOP_BIT_TWO     (2)         /* 2λֹͣλ    */

#define SW_UART_CHAR_NUM_8       (8)         /* 8λ�ַ�      */
#define SW_UART_CHAR_NUM_9       (9)         /* 9λ�ַ�      */
#define SW_UART_CHAR_NUM_10      (10)        /* 10λ�ַ�     */
  
#define SW_UART_BAUD_600         (0)         /* 600������    */
#define SW_UART_BAUD_1200        (1)         /* 1200������   */
#define SW_UART_BAUD_2400        (2)         /* 2400������   */
#define SW_UART_BAUD_4800        (3)         /* 4800������   */
#define SW_UART_BAUD_9600        (4)         /* 9600������   */
#define SW_UART_BAUD_19200       (5)         /* 19200������  */
#define SW_UART_BAUD_38400       (6)         /* 38400������  */
#define SW_UART_BAUD_115200      (7)         /* 115200������ */

#define SW_UART_FLOW_CTRL_OFF    (0)         /* ���عر�     */
#define SW_UART_FLOW_CTRL_ON     (1)         /* ���ش�     */

#define SW_UART_FIFO_OPEN        (1)         /* ����FIFO��ʽ */
#define SW_UART_FIFO_CLOSE       (0)         /* �ر�FIFO��ʽ */

/**********************SPI ��ز�������*****************************/
#define SW_SPI_BAUD_1M           (1)         /* 1M����                */
#define SW_SPI_BAUD_2M           (2)         /* 2M����                */
#define SW_SPI_BAUD_3M           (3)         /* 3M����                */
#define SW_SPI_BAUD_4M           (4)         /* 4M����                */
#define SW_SPI_BAUD_8M           (5)         /* 8M����                */
#define SW_SPI_BAUD_16M           (6)        /* 16M����               */

/* SPIʱ�Ӽ��� */
#define SW_SPI_CLK_ACTIVE_H      (1)         /* SPIʱ�Ӽ���Ϊ��(idle low) */
#define SW_SPI_CLK_ACTIVE_L      (0)         /* SPIʱ�Ӽ���Ϊ��(idle high)*/
/* SPIʱ����λ */
#define SW_SPI_CLK_PHASE_S       (0)         /* SPIʱ������������ʼ�� */
#define SW_SPI_CLK_PHASE_M       (1)         /* SPIʱ�����������жδ� */
/* SPI����ģʽ���� */
#define SW_SPI_MODE0             (0)         /* SPIʱ��Ϊ0(idel = 0)����λΪ0(ǰ�ز���) */
#define SW_SPI_MODE1             (1)         /* SPIʱ��Ϊ0(idel = 0)����λΪ1(���ز���) */
#define SW_SPI_MODE2             (2)         /* SPIʱ��Ϊ1(idel = 1)����λΪ0(ǰ�ز���) */
#define SW_SPI_MODE3             (3)         /* SPIʱ��Ϊ1(idel = 1)����λΪ1(���ز���) */

/* ͨѶ�ӿڿ������� */
#define SW_COMM_TXINT_DISEN      (0)         /* �رշ����ж� */
#define SW_COMM_RXINT_DISEN      (1)         /* �رս����ж� */ 
#define SW_COMM_TXINT_EN         (2)         /* �򿪷����ж� */
#define SW_COMM_RXINT_EN         (3)         /* �򿪽����ж� */
#define SW_COMM_DEV_CONFIG       (4)         /* �豸�������� */
#define SW_COMM_GET_RX_STAT      (5)         /* ��ȡ����״̬ */
#define SW_COMM_GET_TX_STAT      (6)         /* ��ȡ�Ƿ������ */
#define SW_COMM_EN_RX_DMA        (7)         /* ʹ�ܽ���DMA  */
#define SW_COMM_EN_TX_DMA        (8)         /* ʹ�ܷ���DMA  */
#define SW_COMM_DIS_RX_DMA       (9)         /* �رս���DMA  */
#define SW_COMM_DIS_TX_DMA       (10)        /* �رշ���DMA  */
#define SW_COMM_RX_DISEN         (11)        /* �رս��չ��� */
#define SW_COMM_TX_DISEN         (12)        /* �رշ��͹��� */
#define SW_COMM_RX_EN            (13)        /* �򿪽��չ��� */
#define SW_COMM_TX_EN            (14)        /* �򿪷��͹��� */



/* ͨѶ״̬���� */
#define SW_COMM_READY            (1)         /* �յ�����/�������/�豸׼����       */
#define SW_COMM_NOT_READY        (0)         /* ����δ���/����None����/�豸δ׼���� */

/********************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA�ṹ����UART��ʼ��/����ʱ�Ĳ������塣
* �����б�
           ������       ��������    ȡֵ��Χ                 ����   
  ------------------------------------------------------------------------------------------------------------------
  Input  ucPara[0]      BYTE      1-                       �豸ID��
  Input  ucPara[1]      BYTE      0-                       ����ͨ����
  Input  ucPara[2]      BYTE      0-4                      ��������
  Input                           SW_COMM_TXINT_DISEN
  Input                           SW_COMM_RXINT_DISEN
  Input                           SW_COMM_TXINT_EN
  Input                           SW_COMM_RXINT_EN
  Input                           SW_COMM_DEV_CONFIG
  Input                           SW_COMM_GET_RX_STAT
  Input                           SW_COMM_GET_TX_STAT
  Input                           SW_COMM_EN_RX_DMA
  Input                           SW_COMM_EN_TX_DMA
  Input                           SW_COMM_RX_DISEN
  Input                           SW_COMM_TX_DISEN
  Input                           SW_COMM_RX_EN
  Input                           SW_COMM_TX_EN
  Input  ucPara[3]      BYTE      ����Ϊ��������SW_COMM_DEV_CONFIGʱ��
  Input                           SW_UART_CHAR_NUM_8       8bits
  Input                           SW_UART_CHAR_NUM_9       9bits
  Input                           SW_UART_CHAR_NUM_10      10bits
  Input  ucPara[4]      BYTE      ����Ϊ��������SW_COMM_DEV_CONFIGʱ��
  Input                           SW_UART_STOP_BIT_ONE     1λֹͣλ
  Input                           SW_UART_STOP_BIT_TWO     2λֹͣλ
  Input  ucPara[5]      BYTE      ����Ϊ��������SW_COMM_DEV_CONFIGʱ��
  Input                           SW_UART_PARITY_NO        NoneУ��
  Input                           SW_UART_PARITY_ODD       ��У��
  Input                           SW_UART_PARITY_EVEN      żУ��
  Input  ucPara[6]      BYYTE     ����Ϊ��������SW_COMM_DEV_CONFIGʱ��
  Input                           SW_UART_BAUD_4800        ������:4800
  Input                           SW_UART_BAUD_9600        ������:9600
  Input                           SW_UART_BAUD_19200       ������:19200
  Input                           SW_UART_BAUD_38400       ������:38400
  Input                           SW_UART_BAUD_115200      ������:115200
  Input  pucBuf         BYTE*     ָ��                     �ϲ㴫����ջ�����ָ�룬��Ϊ�գ�ȡ�������
  Input  wBufLen        WORD16    0-                       �ϲ㴫�뻺�������ȣ���Ҫ�жϳ����Ƿ�����Ҫ��
 -------------------------------------------------------------------------------------------------
  Output ucPara[3]      BYTE      ����Ϊ��ȡ״̬SW_COMM_GET_RX_STAT/SW_COMM_GET_TX_STAT�ǣ�
                                  SW_COMM_READY            ���յ�����/�����������/�豸׼����
                                  SW_COMM_NOT_READY        ����δ���/����None����/�豸δ׼����
*******************************************************************************************************************/

/******************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA�ṹ����SPI��ʼ��/����ʱ�Ĳ������塣
* �����б�
           ������       ��������    ȡֵ��Χ                 ����   
  -----------------------------------------------------------------------------------------------------------------
  Input      ucPara[0]      BYTE      SW_PERIPHERAL_SPI        �豸ID��
  Input      ucPara[1]      BYTE      0-1                      ����ͨ����
  Input      ucPara[2]      BYTE      ������ʽ���ã�
  Input                               SW_WORK_POLLING          ��ѯ��ʽ����ʼ���ã�
  Input                               SW_WORK_INTERRUPT        �жϷ�ʽ����ʼ���ã�
                                      ���ò�������:
  Input                               SW_COMM_TXINT_DISEN      �رշ����жϣ������ã�
  Input                               SW_COMM_RXINT_DISEN      �رս����жϣ������ã�
  Input                               SW_COMM_TXINT_EN         �򿪷����жϣ������ã�
  Input                               SW_COMM_RXINT_EN         �򿪽����жϣ������ã�
  Input                               SW_COMM_GET_RX_STAT      ����״̬��ȡ�������ã�
  Input                               SW_COMM_GET_TX_STAT      ����״̬��ȡ�������ã�
  Input                               SW_COMM_EN_RX_DMA        ʹ�ܽ���DMA�������ã�
  Input                               SW_COMM_EN_TX_DMA        ʹ�ܷ���DMA�������ã�
  Input                               SW_COMM_DIS_RX_DMA       �رս���DMA�������ã�
  Input                               SW_COMM_DIS_TX_EMA       �رշ���DMA�������ã�
  Input      ucPara[3]      BYTE      ���ʶ��壺
  Input                               SW_SPI_BAUD_1M           1M����
  Input                               SW_SPI_BAUD_2M           2M����
  Input                               SW_SPI_BAUD_3M           3M����
  Input                               SW_SPI_BAUD_4M           4M����(Attention:MAX,Depending on the actual OSHz)
  Input      ucPara[4]      BYTE      SPI����ģʽ����:
  Input                               SW_SPI_MODE0             SPIʱ��Ϊ0(idel = 0)����λΪ0(ǰ�ز���)
  Input                               SW_SPI_MODE1             SPIʱ��Ϊ0(idel = 0)����λΪ1(���ز���)
  Input                               SW_SPI_MODE2             SPIʱ��Ϊ1(idel = 1)����λΪ0(ǰ�ز���)
  Input                               SW_SPI_MODE3             SPIʱ��Ϊ1(idel = 1)����λΪ1(���ز���)
  Input      ucPara[5]      BYTE      �ֽ����壺
  Input                               SW_SERIAL_MSB_FIRST      ���ݸ�λ��ǰ
  Input                               SW_SERIAL_LSB_FIRST      ���ݵ�λ��ǰ
  Input      ucPara[6]      BYTE      ���ӻ����壺
  Input                               SW_MASTER_DEVICE         ����
  Input                               SW_SLAVE_DEVICE          �ӻ�
  Input      pucBuf         BYTE*     ָ��                     �ϲ㴫����ջ�����ָ�룬��Ϊ�գ�ȡ�������
  Input      wBufLen        WORD16    0-                       �ϲ㴫�뻺�������ȣ���Ҫ�жϳ����Ƿ�����Ҫ��
  ----------------------------------------------------------------------------------------------------------
  Output     ����ΪSW_COMM_GET_RX_STAT/SW_COMM_GET_TX_STATʱ��
             ucPara[3]      BYTE      SW_COMM_READY            �豸����/�������            
                                      SW_COMM_NOT_READY        �豸����/����δ���
************************************************************************************************************/

/******************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA for ethernet device's control and configuration.
* Para List��
          Name of Parameter Type      Value scope                    explanation  
  -----------------------------------------------------------------------------------------------------------------
  Input      ucPara[0]      BYTE      SW_PERIPHERAL_ETH            device ID��
  Input      ucPara[1]      BYTE      0-3                          ethernet device's physical NO.
  Input      ucPara[2]      BYTE      Control command,it's value and parameter is as below��
  Input                     BYTE        SW_SET_IP_PARA             set network working parameter.
  Input                                    pucBuf[0]~pucBuf[5]         SMAC0~SMAC5(ex.00-SM0.08-SM1.DC-SM2.01-SM3.02-SM4.03-SM5):mac address
  Input                                    pucBuf[6]~pucBuf[9]         GAR0~GAR3(ex.192-GAR0.168-GAR1.0-GAR2.1-GAR3)            :gateway address
  Input                                    pucBuf[10]~pucBuf[13]       SUBR0~SUBR3(ex.255-SUBR0.255-SUBR1.255-SUBR2.0-SUBR3)    :subnet work address mask
  Input                                    pucBuf[14]~pucBuf[17]       SIP0~SIP3(ex.192-SIP0.168-SIP1.0-SIP2.2-SIP3)            :ip address
  Input                                 SW_GATEWAY_ADDRESS         set gateway address,Parameter as below:
  Input                     BYTE           ucPara[3]~ucPara[6]          GAR0~GAR3(ex.192-GAR0.168-GAR1.0-GAR2.1-GAR3)
  Input                                 SW_SUBNET_MASK_ADDRESS     set subnet mask address,Parameter as below:
  Input                     BYTE           ucPara[3]~ucPara[6]          SUBR0~SUBR3(ex.255-SUBR0.255-SUBR1.255-SUBR2.0-SUBR3)
  Input                                 SW_SOURCE_MAC_ADDRESS      set source MAC address,Parameter as below:
  Input                     BYTE           pucBuf[0]~pucBuf[5]          SMAC0~SMAC5(ex.00-SM0.08-SM1.DC-SM2.01-SM3.02-SM4.03-SM5)
  Input                                 SW_SOURCE_IP_ADDRESS       set source IP address,Parameter as below:
  Input                     BYTE           ucPara[3]~ucPara[6]          SIP0~SIP3(ex.192-SIP0.168-SIP1.0-SIP2.2-SIP3)
                                        SW_GET_ETH_STATUS          get the link/SPEED/DPX status.
                                        SW_SOCKET_CREATE           create a socket.
                                        SW_SOCKET_CONTROL          control a socket.
                            BYTE           ucPara[3]                    socket No.1-8
                            BYTE           ucPara[4]                    socket command.SW_SOCKET_OPEN~SW_SOCKET_SEND_KEEP
                                        SW_SOCKET_DSIP_PORT        set socket destination IP & port.
                                           ucPara[3]               the socket No.1-8
                                           pucBuf[0~3]             destination IP,from high to low.
                                           pucBuf[4~5]             destination port,from high to low.
                                        SW_SOCKET_GET_INT_STATUS   get socket's interrupt status.
                                           ucPara[3]               the socket No.1-8
  Input      pucBuf         BYTE*     point                        used by up layer,decided by application.
  Input      wBufLen        WORD16    0-                           data length.
  ----------------------------------------------------------------------------------------------------------
             For SW_GET_ETH_STATUS command��
  Output     ucPara[3]      BYTE      Bit0:link status
                                        SW_COMM_LINK_UP               physical link is established.
                                        SW_COMM_LINK_DOWN             physical link is not established.s
                                      Bit1:ETH Speed
                                        SW_ETH_SPEED_10M              10M speed
                                        SW_ETH_SPEED_100M             100M speed
                                        SW_ETH_SPEED_1G               1G speed
                                      Bit2:DPX status  
                                        SW_ETH_FULL_DPX               full DPX
                                        SW_ETH_HALF_DPX               half DPX
             For SW_SOCKET_CREATE command:
             ucPara[3]      BYTE      1-8                           successfully created socket No.
             For SW_SOCKET_GET_INT_STATUS commmand:
             ucPara[4]      BYTE      BIT0:1-Establis link,     0-Not establish link.
                                      BIT1:1-receive disconnect,0-Not receive disconnect.
                                      BIT2:1-receive data,      0-Not receive data.
                                      BIT3:1-timeout,           0-Not timeout.
                                      BIT4:1-send ok,           0-Not send ok.
************************************************************************************************************/
#define SW_GATEWAY_ADDRESS                   (0)       /* set gateway address             */
#define SW_SUBNET_MASK_ADDRESS               (1)       /* set subnet mask address         */
#define SW_SOURCE_MAC_ADDRESS                (2)       /* set source MAC address          */
#define SW_SOURCE_IP_ADDRESS                 (3)       /* set source IP address           */
#define SW_GET_ETH_STATUS                    (4)       /* get the link/speed/DPX status   */
#define SW_SOCKET_CREATE                     (5)       /* create a scoket                 */
#define SW_SOCKET_CONTROL                    (6)       /* control a socket                */
#define SW_SOCKET_DSIP_PORT                  (7)       /* set socket's destination IP & PORT */
#define SW_SOCKET_DMAC_ADDRESS               (8)       /* set socket's destination MAC */
#define SW_SOCKET_GET_INT_STATUS             (9)       /* get socket's interrupt status.  */
#define SW_SET_IP_PARA                       (10)       /* set multi Ip parameter.         */

#define SW_ETH_LINKUP                        (1)       /* eth establish a link. */
#define SW_ETHPHY_RESETOK                    (8)       /* eth phy reset is ok.  */
#define SW_ETH_RESETOK                       (0)       /* eth reset is ok.        */
#define SW_ETH_RESETOK_MASK                  (8)       /* eth reset mask.       */

#define SW_SOCKET_TYPE_UDP                   (0)       /* socket use UDP protocol.    */
#define SW_SOCKET_TYPE_TCP                   (1)       /* socket use TCP protocol.    */
#define SW_SOCKET_TYPE_RAW                   (2)       /* socket working in RAW mode. */

#define SW_SOCKET_BUFFER_1K                  (0)       /* socket buffer size 1 k. */
#define SW_SOCKET_BUFFER_2K                  (1)       /* socket buffer size 2 k. */
#define SW_SOCKET_BUFFER_4K                  (2)       /* socket buffer size 4 k. */
#define SW_SOCKET_BUFFER_8K                  (3)       /* socket buffer size 8 k. */

#define SW_SOCKET_MULTI_DISEN                (0)       /* disable multicast in UDP.   */
#define SW_SOCKET_MULTI_EN                   (1)       /* enable multicast in UDP.    */
#define SW_SOCKET_MAC_FILTER_DISEN           (0)       /* disable MAC filter in RAW.  */
#define SW_SOCKET_MAC_FILTER_EN              (1)       /* enable MAC filter in RAW.   */
#define SW_SOCKET_BROADCAST_BLOCK_DISEN      (0)       /* disable broadcast block.    */
#define SW_SOCKET_BROADCAST_BLOCK_EN         (1)       /* enable broadcast block.     */
#define SW_SOCKET_NO_DELAY_ACK_DISEN         (0)       /* disable delay ACK in TCP.   */
#define SW_SOCKET_NO_DELAY_ACK_EN            (1)       /* enable delay ACK in TCP.    */
#define SW_SOCKET_IGMP_VER1                  (1)       /* IGMP use version 1.         */
#define SW_SOCKET_IGMP_VER2                  (0)       /* IGMP use version 2.         */
#define SW_SOCKET_UNICAST_BLOCK_DISEN        (0)       /* disable unicast block.      */
#define SW_SOCKET_UNICAST_BLOCK_EN           (1)       /* enable unicast block.       */
#define SW_SOCKET_IPV6_BLOCK_DISEN           (0)       /* disable IPV6 block.         */
#define SW_SOCKET_IPV6_BLOCK_EN              (1)       /* enable IPV6 block.          */

#define SW_SOCKET_OPEN                       (0)       /* open socket                 */
#define SW_SOCKET_LISTEN                     (1)       /* socket listen               */
#define SW_SOCKET_CONNECT                    (2)       /* socket connect              */
#define SW_SOCKET_DISCON                     (3)       /* socket disconnect           */
#define SW_SOCKET_CLOSE                      (4)       /* close socket                */
#define SW_SOCKET_SEND_KEEP                  (5)       /* socket send keep            */

/* socket interrupt mask */
#define SW_SOCKET_CONNECT_MASK               (0x01)    /* socket establish connect.   */
#define SW_SOCKET_DISCONNECT_MASK            (0x02)    /* socket receive disconnect.  */
#define SW_SOCKET_RECEIVE_MASK               (0x04)    /* socket recevie data.        */
#define SW_SOCKET_TIMEOUT_MASK               (0x08)    /* socket time out.            */
#define SW_SOCKET_SEND_MASK                  (0x10)    /* socket send ok.             */

/******************** CAN��ز������� ************************/
#define SW_CAN_BAUD_50K          (0)         /* 50K������    */
#define SW_CAN_BAUD_100K         (1)         /* 100K������   */
#define SW_CAN_BAUD_125K         (2)         /* 125K������   */
#define SW_CAN_BAUD_250K         (3)         /* 250K������   */
#define SW_CAN_BAUD_500K         (4)         /* 500K������   */


/******************** I2C��ز������� ************************/
#define SW_DEV_MASTER            (0)         /* ���豸       */
#define SW_DEV_SLAVE             (1)         /* ���豸       */


/******************* ͨ�ö��� *********************************/
#define SW_COM_DEV_MAX_NUM       (4)          /* ���ӿ��豸����    */
#define SW_WORK_POLLING          (0)          /* ��������ѯ��ʽ      */
#define SW_WORK_INTERRUPT        (1)          /* ��������ѯ��ʽ      */
#define SW_MAX_SUB_COM_DEV_NUM   (4)          /* ÿ���豸������    */



/**********************����ԭ�Ͷ���******************************/

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription: ��ͨѶ��ע���豸��
* InputParameterT_REGISTED_DEVICE *ptRegDev�����ṹ���塣
* OutputParameterNone��
* Return Value��SW_OK   ��ע��ɹ���
            SW_ERROR��ע��ʧ�ܣ�
* Other Description:
**************************************************************************/
extern WORD32 API_ComDrv_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Read(BYTE ucDevID,T_DATA_OPERARTION *ptDataOp)
* ����˵����ͨѶ��������ݽӿڡ�
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo  :�߼��豸��
                               ->pucBuffer:������ݵĻ�������ַ
* OutputParameterT_DATA_OPERARTION *ptDataOp
                               ->wDataLength:���صĶ�ȡ�������ݳ��ȣ�Ϊ0��ʾNone���ݡ�
* Return Value��SW_OK    ���ɹ�
            SW_ERROR ������
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Read(T_DATA_OPERARTION *ptDataOp);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Write(T_DATA_OPERARTION *ptDataOp)
* ����˵����ͨѶ�㷢�����ݽӿڡ�
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :�߼��豸��
                               ->pucBuffer  :������ݵĻ�������ַ
                               ->wDataLength:�������ֽڸ���
* OutputParameterNone
* Return Value��TRUE ���ɹ�
            FALSE��ʧ��
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Write(T_DATA_OPERARTION *ptDataOp);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵����ͨѶ���豸���ƽӿڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* Return Value��TRUE ���ɹ�
            FALSE��ʧ��
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Init(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* ����˵����ͨѶ���豸��ʼ���ӿڡ�
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:�豸ID
                                    ->ucPara[1]:�߼��豸��
                                    �����ο���������
* Return Value: SW_OK   ���ɹ�
            SW_ERROR��ʧ��
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);

#ifdef __cplusplus
}
#endif

#endif /* _COMM_SERVICE_H_ */




