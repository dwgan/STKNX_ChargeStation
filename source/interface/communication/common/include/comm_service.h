/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：comm_service.h
* FileIdentifier：None
* Abstract ：本文件为通讯接口层公共头文件定义。
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

#ifndef _COMM_SERVICE_H_
#define _COMM_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


/******************** UART相关参数定义 ***********************/
#define SW_UART_PARITY_NO        (0)         /* 奇偶校验关闭 */
#define SW_UART_PARITY_ODD       (1)         /* 奇校验方式   */
#define SW_UART_PARITY_EVEN      (2)         /* 偶校验方式   */

#define SW_UART_STOP_BIT_ONE     (1)         /* 1位停止位    */
#define SW_UART_STOP_BIT_TWO     (2)         /* 2位停止位    */

#define SW_UART_CHAR_NUM_8       (8)         /* 8位字符      */
#define SW_UART_CHAR_NUM_9       (9)         /* 9位字符      */
#define SW_UART_CHAR_NUM_10      (10)        /* 10位字符     */
  
#define SW_UART_BAUD_600         (0)         /* 600波特率    */
#define SW_UART_BAUD_1200        (1)         /* 1200波特率   */
#define SW_UART_BAUD_2400        (2)         /* 2400波特率   */
#define SW_UART_BAUD_4800        (3)         /* 4800波特率   */
#define SW_UART_BAUD_9600        (4)         /* 9600波特率   */
#define SW_UART_BAUD_19200       (5)         /* 19200波特率  */
#define SW_UART_BAUD_38400       (6)         /* 38400波特率  */
#define SW_UART_BAUD_115200      (7)         /* 115200波特率 */

#define SW_UART_FLOW_CTRL_OFF    (0)         /* 流控关闭     */
#define SW_UART_FLOW_CTRL_ON     (1)         /* 流控打开     */

#define SW_UART_FIFO_OPEN        (1)         /* 启用FIFO方式 */
#define SW_UART_FIFO_CLOSE       (0)         /* 关闭FIFO方式 */

/**********************SPI 相关参数定义*****************************/
#define SW_SPI_BAUD_1M           (1)         /* 1M速率                */
#define SW_SPI_BAUD_2M           (2)         /* 2M速率                */
#define SW_SPI_BAUD_3M           (3)         /* 3M速率                */
#define SW_SPI_BAUD_4M           (4)         /* 4M速率                */
#define SW_SPI_BAUD_8M           (5)         /* 8M速率                */
#define SW_SPI_BAUD_16M           (6)        /* 16M速率               */

/* SPI时钟极性 */
#define SW_SPI_CLK_ACTIVE_H      (1)         /* SPI时钟极性为高(idle low) */
#define SW_SPI_CLK_ACTIVE_L      (0)         /* SPI时钟极性为低(idle high)*/
/* SPI时钟相位 */
#define SW_SPI_CLK_PHASE_S       (0)         /* SPI时钟沿在数据起始处 */
#define SW_SPI_CLK_PHASE_M       (1)         /* SPI时钟沿在数据中段处 */
/* SPI工作模式定义 */
#define SW_SPI_MODE0             (0)         /* SPI时钟为0(idel = 0)，相位为0(前沿采样) */
#define SW_SPI_MODE1             (1)         /* SPI时钟为0(idel = 0)，相位为1(后沿采样) */
#define SW_SPI_MODE2             (2)         /* SPI时钟为1(idel = 1)，相位为0(前沿采样) */
#define SW_SPI_MODE3             (3)         /* SPI时钟为1(idel = 1)，相位为1(后沿采样) */

/* 通讯接口控制命令 */
#define SW_COMM_TXINT_DISEN      (0)         /* 关闭发送中断 */
#define SW_COMM_RXINT_DISEN      (1)         /* 关闭接收中断 */ 
#define SW_COMM_TXINT_EN         (2)         /* 打开发送中断 */
#define SW_COMM_RXINT_EN         (3)         /* 打开接收中断 */
#define SW_COMM_DEV_CONFIG       (4)         /* 设备配置命令 */
#define SW_COMM_GET_RX_STAT      (5)         /* 获取接收状态 */
#define SW_COMM_GET_TX_STAT      (6)         /* 获取是否发送完成 */
#define SW_COMM_EN_RX_DMA        (7)         /* 使能接收DMA  */
#define SW_COMM_EN_TX_DMA        (8)         /* 使能发送DMA  */
#define SW_COMM_DIS_RX_DMA       (9)         /* 关闭接收DMA  */
#define SW_COMM_DIS_TX_DMA       (10)        /* 关闭发送DMA  */
#define SW_COMM_RX_DISEN         (11)        /* 关闭接收功能 */
#define SW_COMM_TX_DISEN         (12)        /* 关闭发送功能 */
#define SW_COMM_RX_EN            (13)        /* 打开接收功能 */
#define SW_COMM_TX_EN            (14)        /* 打开发送功能 */



/* 通讯状态定义 */
#define SW_COMM_READY            (1)         /* 收到数据/发送完成/设备准备好       */
#define SW_COMM_NOT_READY        (0)         /* 发送未完成/接收None数据/设备未准备好 */

/********************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA结构用于UART初始化/配置时的参数定义。
* 参数列表：
           参数名       数据类型    取值范围                 含义   
  ------------------------------------------------------------------------------------------------------------------
  Input  ucPara[0]      BYTE      1-                       设备ID。
  Input  ucPara[1]      BYTE      0-                       物理通道号
  Input  ucPara[2]      BYTE      0-4                      操作命令
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
  Input  ucPara[3]      BYTE      命令为配置命令SW_COMM_DEV_CONFIG时：
  Input                           SW_UART_CHAR_NUM_8       8bits
  Input                           SW_UART_CHAR_NUM_9       9bits
  Input                           SW_UART_CHAR_NUM_10      10bits
  Input  ucPara[4]      BYTE      命令为配置命令SW_COMM_DEV_CONFIG时：
  Input                           SW_UART_STOP_BIT_ONE     1位停止位
  Input                           SW_UART_STOP_BIT_TWO     2位停止位
  Input  ucPara[5]      BYTE      命令为配置命令SW_COMM_DEV_CONFIG时：
  Input                           SW_UART_PARITY_NO        None校验
  Input                           SW_UART_PARITY_ODD       奇校验
  Input                           SW_UART_PARITY_EVEN      偶校验
  Input  ucPara[6]      BYYTE     命令为配置命令SW_COMM_DEV_CONFIG时：
  Input                           SW_UART_BAUD_4800        波特率:4800
  Input                           SW_UART_BAUD_9600        波特率:9600
  Input                           SW_UART_BAUD_19200       波特率:19200
  Input                           SW_UART_BAUD_38400       波特率:38400
  Input                           SW_UART_BAUD_115200      波特率:115200
  Input  pucBuf         BYTE*     指针                     上层传入接收缓冲区指针，可为空，取决于设计
  Input  wBufLen        WORD16    0-                       上层传入缓冲区长度，需要判断长度是否满足要求
 -------------------------------------------------------------------------------------------------
  Output ucPara[3]      BYTE      命令为获取状态SW_COMM_GET_RX_STAT/SW_COMM_GET_TX_STAT是：
                                  SW_COMM_READY            接收到数据/发送完成数据/设备准备好
                                  SW_COMM_NOT_READY        发送未完成/接收None数据/设备未准备好
*******************************************************************************************************************/

/******************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA结构用于SPI初始化/配置时的参数定义。
* 参数列表：
           参数名       数据类型    取值范围                 含义   
  -----------------------------------------------------------------------------------------------------------------
  Input      ucPara[0]      BYTE      SW_PERIPHERAL_SPI        设备ID。
  Input      ucPara[1]      BYTE      0-1                      物理通道号
  Input      ucPara[2]      BYTE      工作方式配置：
  Input                               SW_WORK_POLLING          轮询方式（初始化用）
  Input                               SW_WORK_INTERRUPT        中断方式（初始化用）
                                      配置操作命令:
  Input                               SW_COMM_TXINT_DISEN      关闭发送中断（配置用）
  Input                               SW_COMM_RXINT_DISEN      关闭接收中断（配置用）
  Input                               SW_COMM_TXINT_EN         打开发送中断（配置用）
  Input                               SW_COMM_RXINT_EN         打开接收中断（配置用）
  Input                               SW_COMM_GET_RX_STAT      接收状态获取（配置用）
  Input                               SW_COMM_GET_TX_STAT      发送状态获取（配置用）
  Input                               SW_COMM_EN_RX_DMA        使能接收DMA（配置用）
  Input                               SW_COMM_EN_TX_DMA        使能发送DMA（配置用）
  Input                               SW_COMM_DIS_RX_DMA       关闭接收DMA（配置用）
  Input                               SW_COMM_DIS_TX_EMA       关闭发送DMA（配置用）
  Input      ucPara[3]      BYTE      速率定义：
  Input                               SW_SPI_BAUD_1M           1M速率
  Input                               SW_SPI_BAUD_2M           2M速率
  Input                               SW_SPI_BAUD_3M           3M速率
  Input                               SW_SPI_BAUD_4M           4M速率(Attention:MAX,Depending on the actual OSHz)
  Input      ucPara[4]      BYTE      SPI工作模式定义:
  Input                               SW_SPI_MODE0             SPI时钟为0(idel = 0)，相位为0(前沿采样)
  Input                               SW_SPI_MODE1             SPI时钟为0(idel = 0)，相位为1(后沿采样)
  Input                               SW_SPI_MODE2             SPI时钟为1(idel = 1)，相位为0(前沿采样)
  Input                               SW_SPI_MODE3             SPI时钟为1(idel = 1)，相位为1(后沿采样)
  Input      ucPara[5]      BYTE      字节序定义：
  Input                               SW_SERIAL_MSB_FIRST      数据高位先前
  Input                               SW_SERIAL_LSB_FIRST      数据低位在前
  Input      ucPara[6]      BYTE      主从机定义：
  Input                               SW_MASTER_DEVICE         主机
  Input                               SW_SLAVE_DEVICE          从机
  Input      pucBuf         BYTE*     指针                     上层传入接收缓冲区指针，可为空，取决于设计
  Input      wBufLen        WORD16    0-                       上层传入缓冲区长度，需要判断长度是否满足要求
  ----------------------------------------------------------------------------------------------------------
  Output     命令为SW_COMM_GET_RX_STAT/SW_COMM_GET_TX_STAT时：
             ucPara[3]      BYTE      SW_COMM_READY            设备接收/发送完成            
                                      SW_COMM_NOT_READY        设备接收/发送未完成
************************************************************************************************************/

/******************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA for ethernet device's control and configuration.
* Para List：
          Name of Parameter Type      Value scope                    explanation  
  -----------------------------------------------------------------------------------------------------------------
  Input      ucPara[0]      BYTE      SW_PERIPHERAL_ETH            device ID。
  Input      ucPara[1]      BYTE      0-3                          ethernet device's physical NO.
  Input      ucPara[2]      BYTE      Control command,it's value and parameter is as below：
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
             For SW_GET_ETH_STATUS command：
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

/******************** CAN相关参数定义 ************************/
#define SW_CAN_BAUD_50K          (0)         /* 50K波特率    */
#define SW_CAN_BAUD_100K         (1)         /* 100K波特率   */
#define SW_CAN_BAUD_125K         (2)         /* 125K波特率   */
#define SW_CAN_BAUD_250K         (3)         /* 250K波特率   */
#define SW_CAN_BAUD_500K         (4)         /* 500K波特率   */


/******************** I2C相关参数定义 ************************/
#define SW_DEV_MASTER            (0)         /* 主设备       */
#define SW_DEV_SLAVE             (1)         /* 从设备       */


/******************* 通用定义 *********************************/
#define SW_COM_DEV_MAX_NUM       (4)          /* 最多接口设备个数    */
#define SW_WORK_POLLING          (0)          /* 工作于轮询方式      */
#define SW_WORK_INTERRUPT        (1)          /* 工作于轮询方式      */
#define SW_MAX_SUB_COM_DEV_NUM   (4)          /* 每类设备最大个数    */



/**********************函数原型定义******************************/

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription: 向通讯层注册设备。
* InputParameterT_REGISTED_DEVICE *ptRegDev：见结构定义。
* OutputParameterNone。
* Return Value：SW_OK   ：注册成功；
            SW_ERROR：注册失败；
* Other Description:
**************************************************************************/
extern WORD32 API_ComDrv_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Read(BYTE ucDevID,T_DATA_OPERARTION *ptDataOp)
* 功能说明：通讯层接收数据接口。
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo  :逻辑设备号
                               ->pucBuffer:存放数据的缓冲区地址
* OutputParameterT_DATA_OPERARTION *ptDataOp
                               ->wDataLength:返回的读取到的数据长度，为0表示None数据。
* Return Value：SW_OK    ：成功
            SW_ERROR ：出错
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Read(T_DATA_OPERARTION *ptDataOp);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Write(T_DATA_OPERARTION *ptDataOp)
* 功能说明：通讯层发送数据接口。
* InputParameterT_DATA_OPERARTION *ptDataOp
                               ->ucDevNo    :逻辑设备号
                               ->pucBuffer  :存放数据的缓冲区地址
                               ->wDataLength:待发送字节个数
* OutputParameterNone
* Return Value：TRUE ：成功
            FALSE：失败
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Write(T_DATA_OPERARTION *ptDataOp);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* 功能说明：通讯层设备控制接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value：TRUE ：成功
            FALSE：失败
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_ComDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* FunctionName:WORD32 API_ComDrv_Init(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* 功能说明：通讯层设备初始化接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value: SW_OK   ：成功
            SW_ERROR：失败
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




