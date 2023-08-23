/*****************************************************************************************
* Copy right (C) for *********** company.(2016)
*
* File Name        : Stm32F10xx_uart.h
*
* File Description : header file for the driver of stm32f10xx cpu's uart.
*
* Other Description: this file realizes the driver of Stm32F10xx uart.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2016.7.28
*
* Modification Rec.:
*   Modify Data    : 2016.7.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
*****************************************************************************************/


#ifndef _STM32F10XX_UART_H_
#define _STM32F10XX_UART_H_

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_UART_DEVICE_NUM                 (5)                                /* Max number of uart device   */

/* Interrupt reason data field position definition */
#define UART_INT_DATA_LEN_POS               (0)                                /* Field of data length        */
#define UART_INT_RX_DATA_POS                (1)                                /* Field of received data      */

/* Uart parameter data field position definition   */
#define UART_DEVICE_ID                      (0)                                /* Field of device type ID     */
#define UART_DEV_NO                         (1)                                /* Field of device No.         */
#define UART_OPERATION_CMD                  (2)                                /* Field of operation command  */
#define UART_BIT_MODE                       (3)                                /* Field of bit mode setting   */
#define UART_COMM_STAT                      (3)                                /* Field of Rx/Tx status       */
#define UART_STOP_BIT_MODE                  (4)                                /* Field of stop mode setting  */
#define UART_PARITY_MODE                    (5)                                /* Field of parity setting     */
#define UART_BAUD_MODE                      (6)                                /* Field of baud rate          */

/* Uart number */
#define UART_1                              (0)
#define UART_2                              (1)
#define UART_3                              (2)
#define UART_4                              (3)
#define UART_5                              (4)

/* Uart base addresses */
#define UART1_BASE                          ((T_UART_MEM_MAP)0x40013800u)      /* Address of base register for Uart1 */
#define UART2_BASE                          ((T_UART_MEM_MAP)0x40004400u)      /* Address of base register for Uart2 */
#define UART3_BASE                          ((T_UART_MEM_MAP)0x40004800u)      /* Address of base register for Uart3 */
#define UART4_BASE                          ((T_UART_MEM_MAP)0x40004C00u)      /* Address of base register for Uart4 */
#define UART5_BASE                          ((T_UART_MEM_MAP)0x40005000u)      /* Address of base register for Uart5 */

/* Uart Register accessors */
#define UARTX_SR(base)                      ((base)->SR)                       /* Address of Status Register    */
#define UARTX_DR(base)                      ((base)->DR)                       /* Address of Data Register      */
#define UARTX_BRR(base)                     ((base)->BRR)                      /* Address of Baud Rate Register */
#define UARTX_CR1(base)                     ((base)->CR1)                      /* Address of Control Register 1 */
#define UARTX_CR2(base)                     ((base)->CR2)                      /* Address of Control Register 1 */
#define UARTX_CR3(base)                     ((base)->CR3)                      /* Address of Control Register 1 */
#define UARTX_GTPR(base)                    ((base)->GTPR)                     /* Address of GTR Register       */

/* Uart Register accessors for each uart */
/* Uart1 */
#define UART1_SR                            UARTX_SR(UART1_BASE)
#define UART1_DR                            UARTX_DR(UART1_BASE)
#define UART1_BRR                           UARTX_BRR(UART1_BASE)
#define UART1_CR1                           UARTX_CR1(UART1_BASE)
#define UART1_CR2                           UARTX_CR2(UART1_BASE)
#define UART1_CR3                           UARTX_CR3(UART1_BASE)
#define UART1_GTPR                          UARTX_GTPR(UART1_BASE)

/* Uart2 */
#define UART2_SR                            UARTX_SR(UART2_BASE)
#define UART2_DR                            UARTX_DR(UART2_BASE)
#define UART2_BRR                           UARTX_BRR(UART2_BASE)
#define UART2_CR1                           UARTX_CR1(UART2_BASE)
#define UART2_CR2                           UARTX_CR2(UART2_BASE)
#define UART2_CR3                           UARTX_CR3(UART2_BASE)
#define UART2_GTPR                          UARTX_GTPR(UART2_BASE)

/* Uart3 */
#define UART3_SR                            UARTX_SR(UART3_BASE)
#define UART3_DR                            UARTX_DR(UART3_BASE)
#define UART3_BRR                           UARTX_BRR(UART3_BASE)
#define UART3_CR1                           UARTX_CR1(UART3_BASE)
#define UART3_CR2                           UARTX_CR2(UART3_BASE)
#define UART3_CR3                           UARTX_CR3(UART3_BASE)
#define UART3_GTPR                          UARTX_GTPR(UART3_BASE)

/* Uart4 */
#define UART4_SR                            UARTX_SR(UART4_BASE)
#define UART4_DR                            UARTX_DR(UART4_BASE)
#define UART4_BRR                           UARTX_BRR(UART4_BASE)
#define UART4_CR1                           UARTX_CR1(UART4_BASE)
#define UART4_CR2                           UARTX_CR2(UART4_BASE)
#define UART4_CR3                           UARTX_CR3(UART4_BASE)
#define UART4_GTPR                          UARTX_GTPR(UART4_BASE)

/* Uart5 */
#define UART5_SR                            UARTX_SR(UART5_BASE)
#define UART5_DR                            UARTX_DR(UART5_BASE)
#define UART5_BRR                           UARTX_BRR(UART5_BASE)
#define UART5_CR1                           UARTX_CR1(UART5_BASE)
#define UART5_CR2                           UARTX_CR2(UART5_BASE)
#define UART5_CR3                           UARTX_CR3(UART5_BASE)
#define UART5_GTPR                          UARTX_GTPR(UART5_BASE)

/* Bit definition for USART_SR register */
#define USART_SR_PE_POS                     (0U)                               
#define USART_SR_PE_MASK                    (0x00000001u)                      /* 0x00000001   */
#define USART_SR_PE                         USART_SR_PE_MASK                   /* Parity Error */
#define USART_SR_FE_POS                     (1U)                               
#define USART_SR_FE_MASK                    (0x00000002u)                      /* 0x00000002    */
#define USART_SR_FE                         USART_SR_FE_MASK                   /* Framing Error */
#define USART_SR_NE_POS                     (2U)                               
#define USART_SR_NE_MASK                    (0x00000004u)                      /* 0x00000004       */
#define USART_SR_NE                         USART_SR_NE_MASK                   /* Noise Error Flag */
#define USART_SR_ORE_POS                    (3U)                               
#define USART_SR_ORE_MASK                   (0x00000008u)                      /* 0x00000008    */
#define USART_SR_ORE                        USART_SR_ORE_MASK                  /* OverRun Error */
#define USART_SR_IDLE_POS                   (4U)                               
#define USART_SR_IDLE_MASK                  (0x00000010u)                      /* 0x00000010         */
#define USART_SR_IDLE                       USART_SR_IDLE_MASK                 /* IDLE line detected */
#define USART_SR_RXNE_POS                   (5U)                               
#define USART_SR_RXNE_MASK                  (0x00000020u)                      /* 0x00000020                   */
#define USART_SR_RXNE                       USART_SR_RXNE_MASK                 /* Read Data Register Not Empty */
#define USART_SR_TC_POS                     (6U)                               
#define USART_SR_TC_MASK                    (0x00000040u)                      /* 0x00000040            */
#define USART_SR_TC                         USART_SR_TC_MASK                   /* Transmission Complete */
#define USART_SR_TXE_POS                    (7U)                               
#define USART_SR_TXE_MASK                   (0x00000080u)                      /* 0x00000080                   */
#define USART_SR_TXE                        USART_SR_TXE_MASK                  /* Transmit Data Register Empty */
#define USART_SR_LBD_POS                    (8U)                               
#define USART_SR_LBD_MASK                   (0x00000100u)                      /* 0x00000100               */
#define USART_SR_LBD                        USART_SR_LBD_MASK                  /* LIN Break Detection Flag */
#define USART_SR_CTS_POS                    (9U)                               
#define USART_SR_CTS_MASK                   (0x00000200u)                      /* 0x00000200 */
#define USART_SR_CTS                        USART_SR_CTS_MASK                  /* CTS Flag   */

#define USART_SR_ERR_MASK                   (0x0000000F)                       /* All kinds of error */


/* Bit definition for USART_DR register */
#define USART_DR_DR_POS                     (0U)                               
#define USART_DR_DR_MASK                    (0x000001FFu)                      /* 0x000001FF */
#define USART_DR_DR                         USART_DR_DR_MASK                   /* Data value */

/* Bit definition for USART_BRR register */
#define USART_BRR_DIV_FRACTION_POS          (0U)                               
#define USART_BRR_DIV_FRACTION_MASK         (0x0000000Fu)                       /* 0x0000000F           */
#define USART_BRR_DIV_FRACTION              (USART_BRR_DIV_FRACTION_MASK)      /* Fraction of USARTDIV */
#define USART_BRR_DIV_MAMTISSA_POS          (4U)                               
#define USART_BRR_DIV_MAMTISSA_MASK         (0x0000FFF0u)                       /* 0x0000FFF0           */
#define USART_BRR_DIV_MAMTISSA              (USART_BRR_DIV_MAMTISSA_MASK)      /* Mantissa of USARTDIV */

/* Bit definition for USART_CR1 register */
#define USART_CR1_SBK_POS                   (0U)                               
#define USART_CR1_SBK_MASK                  (0x00000001u)                      /* 0x00000001 */
#define USART_CR1_SBK                       USART_CR1_SBK_MASK                 /* Send Break */
#define USART_CR1_RWU_POS                   (1U)                               
#define USART_CR1_RWU_MASK                  (0x00000002u)                       /* 0x00000002      */
#define USART_CR1_RWU                       USART_CR1_RWU_MASK                 /* Receiver wakeup */
#define USART_CR1_RE_POS                    (2U)                               
#define USART_CR1_RE_MASK                   (0x00000004u)                      /* 0x00000004      */
#define USART_CR1_RE                        USART_CR1_RE_MASK                  /* Receiver Enable */
#define USART_CR1_TE_POS                    (3U)                               
#define USART_CR1_TE_MASK                   (0x00000008u)                      /* 0x00000008         */
#define USART_CR1_TE                        USART_CR1_TE_MASK                  /* Transmitter Enable */
#define USART_CR1_IDLEIE_POS                (4U)                               
#define USART_CR1_IDLEIE_MASK               (0x00000010u)                      /* 0x00000010            */
#define USART_CR1_IDLEIE                    USART_CR1_IDLEIE_MASK              /* IDLE Interrupt Enable */
#define USART_CR1_RXNEIE_POS                (5U)                               
#define USART_CR1_RXNEIE_MASK               (0x00000020u)                      /* 0x00000020            */
#define USART_CR1_RXNEIE                    USART_CR1_RXNEIE_MASK              /* RXNE Interrupt Enable */
#define USART_CR1_TCIE_POS                  (6U)                               
#define USART_CR1_TCIE_MASK                 (0x00000040u)                      /* 0x00000040                             */
#define USART_CR1_TCIE                      USART_CR1_TCIE_MASK                /* Transmission Complete Interrupt Enable */
#define USART_CR1_TXEIE_POS                 (7U)                               
#define USART_CR1_TXEIE_MASK                (0x00000080u)                      /* 0x00000080          */
#define USART_CR1_TXEIE                     USART_CR1_TXEIE_MASK               /* PE Interrupt Enable */
#define USART_CR1_PEIE_POS                  (8U)                               
#define USART_CR1_PEIE_MASK                 (0x00000100u)                      /* 0x00000100          */
#define USART_CR1_PEIE                      USART_CR1_PEIE_MASK                /* PE Interrupt Enable */
#define USART_CR1_PS_POS                    (9U)                               
#define USART_CR1_PS_MASK                   (0x00000200u)                      /* 0x00000200       */
#define USART_CR1_PS                        USART_CR1_PS_MASK                  /* Parity Selection */
#define USART_CR1_PCE_POS                   (10U)                              
#define USART_CR1_PCE_MASK                  (0x00000400u)                      /* 0x00000400            */
#define USART_CR1_PCE                       USART_CR1_PCE_MASK                 /* Parity Control Enable */
#define USART_CR1_WAKE_POS                  (11U)                              
#define USART_CR1_WAKE_MASK                 (0x00000800u)                      /* 0x00000800    */
#define USART_CR1_WAKE                      USART_CR1_WAKE_MASK                /* Wakeup method */
#define USART_CR1_M_POS                     (12U)                              
#define USART_CR1_M_MASK                    (0x00001000u)                      /* 0x00001000  */
#define USART_CR1_M                         USART_CR1_M_MASK                   /* Word length */
#define USART_CR1_UE_POS                    (13U)                              
#define USART_CR1_UE_MASK                   (0x00002000u)                      /* 0x00002000   */
#define USART_CR1_UE                        USART_CR1_UE_MASK                  /* USART Enable */

/* Bit definition for USART_CR2 register */
#define USART_CR2_ADD_POS                   (0U)                               
#define USART_CR2_ADD_MASK                  (0x0000000Fu)                      /* 0x0000000F                */
#define USART_CR2_ADD                       USART_CR2_ADD_MASK                 /* Address of the USART node */
#define USART_CR2_LBDL_POS                  (5U)                               
#define USART_CR2_LBDL_MASK                 (0x00000020u)                      /* 0x00000020                 */
#define USART_CR2_LBDL                      USART_CR2_LBDL_MASK                /* LIN Break Detection Length */
#define USART_CR2_LBDIE_POS                 (6U)                               
#define USART_CR2_LBDIE_MASK                (0x00000040u)                      /* 0x00000040                           */
#define USART_CR2_LBDIE                     USART_CR2_LBDIE_MASK               /* LIN Break Detection Interrupt Enable */
#define USART_CR2_LBCL_POS                  (8U)                               
#define USART_CR2_LBCL_MASK                 (0x00000100u)                      /* 0x00000100           */
#define USART_CR2_LBCL                      USART_CR2_LBCL_MASK                /* Last Bit Clock pulse */
#define USART_CR2_CPHA_POS                  (9U)                               
#define USART_CR2_CPHA_MASK                 (0x00000200u)                      /* 0x00000200  */
#define USART_CR2_CPHA                      USART_CR2_CPHA_MASK                /* Clock Phase */
#define USART_CR2_CPOL_POS                  (10U)                              
#define USART_CR2_CPOL_MASK                 (0x00000400u)                      /* 0x00000400     */
#define USART_CR2_CPOL                      USART_CR2_CPOL_MASK                /* Clock Polarity */
#define USART_CR2_CLKEN_POS                 (11U)                              
#define USART_CR2_CLKEN_MASK                (0x00000800u)                      /* 0x00000800   */
#define USART_CR2_CLKEN                     USART_CR2_CLKEN_MASK               /* Clock Enable */

#define USART_CR2_STOP_POS                  (12U)                              
#define USART_CR2_STOP_MASK                 (0x00003000u)                       /* 0x00003000                 */
#define USART_CR2_STOP                      (USART_CR2_STOP_MASK)              /* STOP[1:0] bits (STOP bits) */
#define USART_CR2_STOP_0                    (0x00001000u)                       /* 0x00001000                 */
#define USART_CR2_STOP_1                    (0x00002000u)                       /* 0x00002000                 */

#define USART_CR2_STOP_ONE_BIT              (0x00000000u)                       /* 0x00000000 */
#define USART_CR2_STOP_HALF_BIT             (0x00001000u)                       /* 0x00001000 */
#define USART_CR2_STOP_TWO_BIT              (0x00002000u)                       /* 0x00002000 */
#define USART_CR2_STOP_ONE_HALF_BIT         (0x00003000u)                       /* 0x00003000 */

#define USART_CR2_LINEN_POS                 (14U)                              
#define USART_CR2_LINEN_MASK                (0x00004000u)                      /* 0x00004000      */
#define USART_CR2_LINEN                     USART_CR2_LINEN_MASK               /* LIN mode enable */

/* Bit definition for USART_CR3 register */
#define USART_CR3_EIE_POS                   (0U)                               
#define USART_CR3_EIE_MASK                  (0x00000001u)                      /* 0x00000001             */
#define USART_CR3_EIE                       USART_CR3_EIE_MASK                 /* Error Interrupt Enable */
#define USART_CR3_IREN_POS                  (1U)                               
#define USART_CR3_IREN_MASK                 (0x00000002u)                      /* 0x00000002       */
#define USART_CR3_IREN                      USART_CR3_IREN_MASK                /* IrDA mode Enable */
#define USART_CR3_IRLP_POS                  (2U)                               
#define USART_CR3_IRLP_MASK                 (0x00000004u)                      /* 0x00000004     */
#define USART_CR3_IRLP                      USART_CR3_IRLP_MASK                /* IrDA Low-Power */
#define USART_CR3_HDSEL_POS                 (3U)                               
#define USART_CR3_HDSEL_MASK                (0x00000008u)                      /* 0x00000008            */
#define USART_CR3_HDSEL                     USART_CR3_HDSEL_MASK               /* Half-Duplex Selection */
#define USART_CR3_NACK_POS                  (4U)                               
#define USART_CR3_NACK_MASK                 (0x00000010u)                      /* 0x00000010            */
#define USART_CR3_NACK                      USART_CR3_NACK_MASK                /* Smartcard NACK enable */
#define USART_CR3_SCEN_POS                  (5U)                               
#define USART_CR3_SCEN_MASK                 (0x00000020u)                      /* 0x00000020            */
#define USART_CR3_SCEN                      USART_CR3_SCEN_MASK                /* Smartcard mode enable */
#define USART_CR3_DMAR_POS                  (6U)                               
#define USART_CR3_DMAR_MASK                 (0x00000040u)                      /* 0x00000040            */
#define USART_CR3_DMAR                      USART_CR3_DMAR_MASK                /* DMA Enable Receiver   */
#define USART_CR3_DMAT_POS                  (7U)                               
#define USART_CR3_DMAT_MASK                 (0x00000080u)                      /* 0x00000080             */
#define USART_CR3_DMAT                      USART_CR3_DMAT_MASK                /* DMA Enable Transmitter */
#define USART_CR3_RTSE_POS                  (8U)                               
#define USART_CR3_RTSE_MASK                 (0x00000100u)                      /* 0x00000100 */
#define USART_CR3_RTSE                      USART_CR3_RTSE_MASK                /* RTS Enable */
#define USART_CR3_CTSE_POS                  (9U)                               
#define USART_CR3_CTSE_MASK                 (0x00000200u)                      /* 0x00000200 */
#define USART_CR3_CTSE                      USART_CR3_CTSE_MASK                /* CTS Enable */
#define USART_CR3_CTSIE_POS                 (10U)                              
#define USART_CR3_CTSIE_MASK                (0x00000400u)                      /* 0x00000400           */
#define USART_CR3_CTSIE                     USART_CR3_CTSIE_MASK               /* CTS Interrupt Enable */

/* Bit definition for USART_GTPR register */
#define USART_GTPR_PSC_POS                  (0U)                               
#define USART_GTPR_PSC_MASK                 (0x000000FFu)                       /* 0x000000FF                      */
#define USART_GTPR_PSC                      (USART_GTPR_PSC_MASK)              /* PSC[7:0] bits (Prescaler value) */
#define USART_GTPR_PSC_0                    (0x00000001u)                       /* 0x00000001 */
#define USART_GTPR_PSC_1                    (0x00000002u)                       /* 0x00000002 */
#define USART_GTPR_PSC_2                    (0x00000004u)                       /* 0x00000004 */
#define USART_GTPR_PSC_3                    (0x00000008u)                       /* 0x00000008 */
#define USART_GTPR_PSC_4                    (0x00000010u)                       /* 0x00000010 */
#define USART_GTPR_PSC_5                    (0x00000020u)                       /* 0x00000020 */
#define USART_GTPR_PSC_6                    (0x00000040u)                       /* 0x00000040 */
#define USART_GTPR_PSC_7                    (0x00000080u)                       /* 0x00000080 */

#define USART_GTPR_GT_POS                   (8U)                                
#define USART_GTPR_GT_MASK                  (0x0000FF00)                       /* 0x0000FF00       */
#define USART_GTPR_GT                       (USART_GTPR_GT_MASK)               /* Guard time value */




/* Data structure definition */
/****************************************************
*   Structure£º  T_UART_MEM_MAP
*   Description£ºMemory map of uart registers.
*   Parameter:   WORD32 SR          Uart status register                  
*                WORD32 DR          Uart data register                    
*                WORD32 BRR         Uart baud rate register               
*                WORD32 CR1         Uart control register 1               
*                WORD32 CR2         Uart control register 2               
*                WORD32 CR3         Uart control register 3               
*                WORD32 GTPR        Uart guard time and prescaler register
*   Authour£º    Ian
*   Modify record:
*   Date:  2016-7-25 creat.
****************************************************/
typedef struct _T_UART_MEM_MAP
{
    WORD32 SR;         /* Uart status register                   */
    WORD32 DR;         /* Uart data register                     */
    WORD32 BRR;        /* Uart baud rate register                */
    WORD32 CR1;        /* Uart control register 1                */
    WORD32 CR2;        /* Uart control register 2                */
    WORD32 CR3;        /* Uart control register 3                */
    WORD32 GTPR;       /* Uart guard time and prescaler register */
}volatile *T_UART_MEM_MAP;




/* Declaration of functions */
/**************************************************************************
* Funciton: void Uart_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
* Descrip.: Register Uart
* Input   : BYTE ucLogNo      Device logic No.
*           BYTE ucDevNo      Device physical No.
*           VOID *ptPara      None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
void Uart_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara);


/**************************************************************************
* Funciton: void Uart1_isr(void)
* Descrip.: interrupt process function of uart1
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart1_isr(void);

/**************************************************************************
* Funciton: void Uart2_isr(void)
* Descrip.: interrupt process function of uart2
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart2_isr(void);

/**************************************************************************
* Funciton: void Uart3_isr(void)
* Descrip.: interrupt process function of uart3
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart3_isr(void);


/**************************************************************************
* Funciton: void Uart4_isr(void)
* Descrip.: interrupt process function of uart4
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart4_isr(void);

/**************************************************************************
* Funciton: void Uart5_isr(void)
* Descrip.: interrupt process function of uart5
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
void Uart5_isr(void);


#ifdef __cplusplus
}
#endif

#endif /* _STM32F10XX_UART_H_ */



