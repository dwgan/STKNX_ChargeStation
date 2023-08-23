/*****************************************************************************************
* Copy right (C) for *********** company.(2016)
*
* File Name        : Stm32F10xx_uart.c
*
* File Description : driver for stm32f10xx cpu's uart.
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


#include "type_def.h"
#include "Sw_common.h"
#include "Pub.h"
#include "boardcfg.h"
#include "Hardware.h"
#include "Boardctrl.h"
#include "system_stm32f10x.h"
#include "Stm32F10xx_uart.h"
#include "comm_service.h"




/* Declaration of static functions */
static void Uartx_isr(BYTE ucDevNo);
WORD32 Uartx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara);


/* Base address of uart registers */
static const T_UART_MEM_MAP sg_aptUartAddr[5] = {UART1_BASE, UART2_BASE, UART3_BASE, UART4_BASE, UART5_BASE};

/* Baud rate table */
static const WORD16 sg_awBaudRate[8] = {6, 12, 24, 48, 96, 192, 384, 1152};

/* Uart operation functions */
static T_DEV_OPERATION sg_tUartOp;

/* Callback function for uart interrupt */
static void (*sg_pfAppCallBack[5])(T_SW_INT_EVENT *ptReason) = {NULL,NULL,NULL,NULL,NULL};     

/**************************************************************************
* Function: WORD32 Uartx_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Init operation of uartx
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara:
*           pIntCallBackHandler£º                             Interrupt callback
*           pExceptionIntCallBackHandler:                     Exception callback
*           ucPara[0]      BYTE      1-                       Device type ID
*           ucPara[1]      BYTE      0-4                      Channel number
*           ucPara[2]      BYTE      SW_COMM_TXINT_DISEN      Disable Tx interrupt
*                                    SW_COMM_RXINT_DISEN      Disable Rx interrupt
*                                    SW_COMM_TXINT_EN         Enable Tx inetrrupt
*                                    SW_COMM_RXINT_EN         Enable Rx interrupt
*                                    SW_COMM_DEV_CONFIG       Configure uart
*                                    SW_COMM_GET_RX_STAT      Get rx status
*                                    SW_COMM_GET_TX_STAT      Get tx status
*                                    SW_COMM_RX_DISEN         Disable Rx function
*                                    SW_COMM_TX_DISEN         Disable Tx function                                   
*           pucBuf         BYTE*                              Buffer for data from upper layer      
*           wBufLen        WORD16    0-65535                  Length of data in buffer
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/25       V1.0         Ian          Create 
**************************************************************************/
WORD32 Uartx_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    WORD32 dwRet;
    BYTE            ucDevNo;
    volatile WORD16 wData;
    T_UART_MEM_MAP  ptUartNo;

    /* Check if the input parameter is valid or NOT */
    if(NULL == ptPara)                                                          
    {   
        return SW_ERR;
    }
    
    /* Check if the command is valid or NOT */
    if (SW_COMM_DEV_CONFIG != ptPara->ucPara[UART_OPERATION_CMD])              
    {
        return SW_ERR;
    }

    /* Get uart number and register address */
    ucDevNo = ptPara->ucPara[UART_DEV_NO];

    /* Check if the uart number is valid or NOT */
    if(ucDevNo >= MAX_UART_DEVICE_NUM)
    {
        return SW_ERR;
    }
    
    ptUartNo = sg_aptUartAddr[ucDevNo];
    
    /* Enable uart clock and reset */
    if(UART_1 == ucDevNo) /* If it is uart1 */
    {
        RCC_APB2ENR  |=   RCC_APB2ENR_USART1EN;      /* Enable uart clock */
        RCC_APB2RSTR |=   RCC_APB2RSTR_USART1RST;    /* Reset uart device */
        RCC_APB2RSTR &= ~(RCC_APB2RSTR_USART1RST);   /* Stop reset uart   */     
    }    
    else /* If it is uart 2~5 */
    {
        RCC_APB1ENR  |=  (RCC_APB1ENR_USART2EN   << (ucDevNo - UART_2)); /* Enable uart clock */
        RCC_APB1RSTR |=  (RCC_APB1RSTR_USART2RST << (ucDevNo - UART_2)); /* Reset uart device */
        RCC_APB1RSTR &= ~(RCC_APB1RSTR_USART2RST << (ucDevNo - UART_2)); /* Reset uart device */
    }

    /* Disable Tx/Rx function, Tx/Rx interrupt and Error interrupt before uart init operation */
    UARTX_CR1(ptUartNo) &= ~(USART_CR1_RE\
                           | USART_CR1_TE\
                           | USART_CR1_UE\
                           | USART_CR1_RXNEIE\
                           | USART_CR1_TXEIE\
                           | USART_CR1_PEIE);
    UARTX_CR3(ptUartNo) &= ~(USART_CR3_EIE);

    
    /* Configure stop bit, bit mode, parity and Buad rate */
    dwRet = Uartx_Ctrl(ptPara);
    if (SW_ERR == dwRet)
    {
        return SW_ERR;
    }
    
    /* Clear error flags and data buffer */
    wData = UARTX_SR(ptUartNo);
    wData = UARTX_DR(ptUartNo);

    
    /* Enable Tx/Rx function, Rx interrupt and Error interrupt */
    UARTX_CR1(ptUartNo) |= (USART_CR1_RE\
                          | USART_CR1_TE\
                          | USART_CR1_UE\
                          | USART_CR1_RXNEIE\
                          | USART_CR1_PEIE);
    UARTX_CR3(ptUartNo) |=  USART_CR3_EIE;
        
    /*------------Register callback function---------------------*/                              
    sg_pfAppCallBack[ucDevNo] = ptPara->pIntCallBackHandler; 

    return SW_OK;  
}


/**************************************************************************
* Function: WORD32 Uartx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Control and configuration of uart
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara:
*           pIntCallBackHandler£º                             Interrupt callback
*           pExceptionIntCallBackHandler:                     Exception callback
*           ucPara[0]      BYTE      1-                       Device type ID
*           ucPara[1]      BYTE      0-4                      Channel number
*           ucPara[2]      BYTE      SW_COMM_TXINT_DISEN      Disable Tx interrupt
*                                    SW_COMM_RXINT_DISEN      Disable Rx interrupt
*                                    SW_COMM_TXINT_EN         Enable Tx inetrrupt
*                                    SW_COMM_RXINT_EN         Enable Rx interrupt
*                                    SW_COMM_DEV_CONFIG       Configure uart
*                                    SW_COMM_GET_RX_STAT      Get rx status
*                                    SW_COMM_GET_TX_STAT      Get tx status
*                                    SW_COMM_RX_DISEN         Disable Rx function
*                                    SW_COMM_TX_DISEN         Disable Tx function
*                                     
*           When command is SW_COMM_DEV_CONFIG:
*           ucPara[3]      BYTE      SW_UART_CHAR_NUM_8       8 bits
*                                    SW_UART_CHAR_NUM_9       9 bits
*                                    SW_UART_CHAR_NUM_10      10 bits
*           ucPara[4]      BYTE      SW_UART_STOP_BIT_ONE     1-bit stop 
*                                    SW_UART_STOP_BIT_TWO     2-bit stop
*           ucPara[5]      BYTE      SW_UART_PARITY_NO        None Parity
*                                    SW_UART_PARITY_ODD       Odd Parity
*                                    SW_UART_PARITY_EVEN      Even Parity
*           ucPara[6]      BYTE      SW_UART_BAUD_4800        Baud rate: 4800
*                                    SW_UART_BAUD_9600        Baud rate: 9600
*                                    SW_UART_BAUD_19200       Baud rate: 19200
*                                    SW_UART_BAUD_38400       Baud rate: 38400
*                                    SW_UART_BAUD_115200      Baud rate: 115200
*           pucBuf         BYTE*                              Buffer for data from upper layer      
*           wBufLen        WORD16    0-65535                  Length of data in buffer
* Output  : ucPara[3]      BYTE      When command is SW_COMM_GET_RX_STAT or SW_COMM_GET_TX_STAT£º
*                                    SW_COMM_READY            Get received data/Data sending is done
*                                    SW_COMM_NOT_READY        No received data/Data sending is NOT finished
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/25       V1.0         Ian          Create 
**************************************************************************/
WORD32 Uartx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    BYTE   ucDevNo;
    WORD32 dwMantissa, dwFraction, dwPCLK, dwBaudRate;
    T_UART_MEM_MAP ptUartNo;
    
    /* Check if input parameter is valid or NOT */
    if(NULL == ptPara)
    {
        return SW_ERR;
    }

    /* Get uart number and register address */
    ucDevNo = ptPara->ucPara[UART_DEV_NO];

    /* Check if the uart number is valid or NOT */
    if(ucDevNo > (MAX_UART_DEVICE_NUM - 1))
    {
        return SW_ERR;
    }
    
    ptUartNo = sg_aptUartAddr[ucDevNo];

    /* Check command */
    switch (ptPara->ucPara[UART_OPERATION_CMD])                                
    {
        case SW_COMM_TXINT_DISEN :                        /* Command to disable Tx interrupt */
        {
            UARTX_CR1(ptUartNo) &= ~(USART_CR1_TXEIE);    /* Disable Tx interrupt            */
            break;
        }

        case SW_COMM_RXINT_DISEN :                        /* Command to disable Rx interrupt */
        {
            UARTX_CR1(ptUartNo) &= ~(USART_CR1_RXNEIE);   /* Disable Rx interrupt            */
            break;
        }

        case SW_COMM_TXINT_EN :                           /* Command to enable Tx interrupt  */              
        {
            UARTX_CR1(ptUartNo) |= USART_CR1_TXEIE;       /* Enable Tx interrupt             */                          
            break;
        }

        case SW_COMM_RXINT_EN :                           /* Command to enable Rx interrupt  */               
        {
            UARTX_CR1(ptUartNo) |= USART_CR1_RXNEIE;      /* Enable Rx interrupt             */                            
            break;
        }
        
        case SW_COMM_RX_DISEN :                           /* Command to disable Rx function  */
        {
            UARTX_CR1(ptUartNo) &= ~(USART_CR1_RE);       /* Disable Rx function             */
            break;
        }
        
        case SW_COMM_TX_DISEN :                           /* Command to disable Tx function  */
        {
            UARTX_CR1(ptUartNo) &= ~(USART_CR1_TE);       /* Disable Tx function             */
            break;
        }

        case SW_COMM_RX_EN:
        {
            UARTX_CR1(ptUartNo) |= USART_CR1_RE;
            break;
        }

        case SW_COMM_TX_EN:
        {
            UARTX_CR1(ptUartNo) |= USART_CR1_TE;
            break;
        }

        case SW_COMM_DEV_CONFIG :                         /* Command to configure uart       */
        {
            float fTemp;
            /* Disable TX/RX first before UART init */
            UARTX_CR1(ptUartNo)  &= ~(USART_CR1_TE | USART_CR1_RE);
 
            /* Configure the bit mode */
            switch (ptPara->ucPara[UART_BIT_MODE])        /* Check the bit mode              */
            {
                case SW_UART_CHAR_NUM_8:                  /* If it is 8 bit mode             */
                {
                    UARTX_CR1(ptUartNo) &= ~(USART_CR1_M);/* Set 8-bit mode                  */
                    break;
                }
                
                case SW_UART_CHAR_NUM_9:                  /* If it is 9 bit mode             */
                {
                    UARTX_CR1(ptUartNo) |= USART_CR1_M;   /* Set 9-bit mode                  */
                    break;
                }
                                
                default:                                  /* Invalid parameter               */
                {
                    return SW_ERR;
                }
            }

            /* Configure the STOP BIT */
            UARTX_CR2(ptUartNo) &= ~(USART_CR2_STOP);     /* Clear Stop bits first           */
            switch (ptPara->ucPara[UART_STOP_BIT_MODE])   /* Check stop bit mode             */
            {
                case SW_UART_STOP_BIT_ONE:                /* If it is 1-bit stop mode        */
                {
                    break;                                /* Already done                    */
                }
                case SW_UART_STOP_BIT_TWO:                /* If it is 2-bit stop mode        */
                {
                    UARTX_CR2(ptUartNo) |= USART_CR2_STOP_TWO_BIT; /* Set 2-bit stop mode    */
                    break;
                }
                default:                                  /* Invalide parameter              */
                {
                    return SW_ERR;
                }
            }

            /* Configure the parity mode */
            switch (ptPara->ucPara[UART_PARITY_MODE])     /* Check parity mode               */
            {
                case SW_UART_PARITY_NO:                   /* If no parity                    */
                {
                    UARTX_CR1(ptUartNo) &= ~(USART_CR1_PCE);/* Disable parity                */
                    break;
                }
                case SW_UART_PARITY_ODD:                  /* If odd parity                   */
                {
                    UARTX_CR1(ptUartNo) |= USART_CR1_PCE; /* Enable parity                   */
                    UARTX_CR1(ptUartNo) |= USART_CR1_PS;  /* Select odd parity               */
                    break;
                }
                case SW_UART_PARITY_EVEN:                 /* If even parity                  */
                {
                    UARTX_CR1(ptUartNo) |= USART_CR1_PCE; /* Enable parity                   */
                    UARTX_CR1(ptUartNo) &= ~(USART_CR1_PS);/* Select even parity             */
                    break;
                }
                default:                                  /* Invalid parameter               */
                {
                    return SW_ERR;
                }
            }
            
            /* Configure the Baud rate */
            /* Get baud rate */
            if(ptPara->ucPara[UART_BAUD_MODE] > SW_UART_BAUD_115200)
            {
                return SW_ERR;
            }
            dwBaudRate = sg_awBaudRate[ptPara->ucPara[UART_BAUD_MODE]];
           
            /* Get PCLK */
            if(UART_1 == ucDevNo) /* If it is uart1 which uses APB2 */
            {
                dwPCLK = SystemFrequency_APB2Clk;
            }
            else/* Else use APB1 */
            {
                dwPCLK = SystemFrequency_APB1Clk;
            }

            /* Calculate BRR value -- BRR = (PCLK/(BAUDRATE*16))*/

            /* Calculate BRR value -- BRR = (PCLK/(BAUDRATE*16))*/
            fTemp  = (float)(dwPCLK/100)/(dwBaudRate << 4);
            dwMantissa = (WORD32)fTemp;
            dwFraction = (WORD32)((fTemp - dwMantissa) * 16);
            dwMantissa <<= 4;
            dwMantissa += dwFraction;
            UARTX_BRR(ptUartNo) = dwMantissa;  /* Ser UART_BRR value */

            break;
        }

        case SW_COMM_GET_RX_STAT :                        /* Command to get Rx status        */
        {
            /* If Rx function is enabled AND get a received data */
            if ((UARTX_SR(ptUartNo)  & USART_SR_RXNE)\
              &&(UARTX_CR1(ptUartNo) & USART_CR1_RE))         
            {
                ptPara->ucPara[UART_COMM_STAT] = SW_COMM_READY;     /* Output ready          */
            }
            else
            {
                ptPara->ucPara[UART_COMM_STAT] = SW_COMM_NOT_READY; /* Output NOT ready      */
            }
            break;
        }

        case SW_COMM_GET_TX_STAT :                        /* Command to get Rx status        */
        {
            /* If Rx function is enabled AND get a received data */
            if ((UARTX_SR(ptUartNo)  & USART_SR_TXE)\
              &&(UARTX_CR1(ptUartNo) & USART_CR1_TE))         
            {
                ptPara->ucPara[UART_COMM_STAT] = SW_COMM_READY;     /* Output ready          */
            }
            else
            {
                ptPara->ucPara[UART_COMM_STAT] = SW_COMM_NOT_READY; /* Output NOT ready      */
            }
            break;
        }
        
        default :                                         /* Invalid command                 */
        {
            return SW_ERR;
        }
    }
    return SW_OK;
}


/**************************************************************************
* Funciton: WORD32 Uartx_Read(T_DATA_OPERARTION *ptData)
* Descrip.: Get data from Rx buffer 
* Input   : T_DATA_OPERARTION *ptData->ucDevNo      1~5    Number of Uart
* Output  : T_DATA_OPERARTION *ptData->wDataLength  1      Length of Rx data
*           T_DATA_OPERARTION *ptData->pucBuffer           Rx data
* Return  : SW_OK    Successful
            SW_ERR   Failed
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/25       V1.0         Ian          Create 
**************************************************************************/
WORD32 Uartx_Read(T_DATA_OPERARTION *ptData)
{
    BYTE            ucDevNo = ptData->ucDevNo;
    T_UART_MEM_MAP  ptUartNo;
    volatile WORD16 wData;

    /* Check if input parameters are valid or NOT */
    if((ucDevNo > (MAX_UART_DEVICE_NUM - 1)) || (NULL == ptData))                                                    
    {
        return SW_ERR;
    }    

    /* Get uart register address */
    ptUartNo = sg_aptUartAddr[ucDevNo];

    /* Return error if:           */
    /* Rx function is NOT enabled */
    /* Or error happens           */
    /* Or no data in Rx buffer    */
    if((!(UARTX_CR1(ptUartNo) & USART_CR1_RE))\
     ||  (UARTX_SR(ptUartNo)  & USART_SR_ERR_MASK)\
     ||(!(UARTX_SR(ptUartNo)  & USART_SR_RXNE)))
    {
        wData = UARTX_SR(ptUartNo);   /* Clear error status */    
        wData = UARTX_DR(ptUartNo);   /* Clear Rx buffer    */
        return SW_ERR;
    }
    /* Else, it is a valid data and return the data back    */
    
    ptData->wDataLength = 1;
    *ptData->pucBuffer  = UARTX_DR(ptUartNo);          
    return SW_OK;                                                   
}


/**************************************************************************
* Funciton: WORD32 Uartx_Write(T_DATA_OPERARTION *ptData)
* Descrip.: Send data of tx buffer. 
* Input   : T_DATA_OPERARTION *ptData->ucDevNo      1~5    Number of Uart
* Output  : T_DATA_OPERARTION *ptData->wDataLength  1      Length of Rx data
*           T_DATA_OPERARTION *ptData->pucBuffer           Rx data
* Return  : SW_OK    Successful
            SW_ERR   Failed
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/25       V1.0         Ian          Create 
**************************************************************************/
WORD32 Uartx_Write(T_DATA_OPERARTION *ptData)
{
    BYTE ucDevNo = ptData->ucDevNo;
    T_UART_MEM_MAP ptUartNo;

    /* Check if input parameters are valid or NOT */
    if((ucDevNo > (MAX_UART_DEVICE_NUM - 1)) || (NULL == ptData) || (1 != ptData->wDataLength))                                                    
    {
        return SW_ERR;
    }    
    
    /* Get uart register address */
    ptUartNo = sg_aptUartAddr[ucDevNo];

    /* Return error if:           */
    /* Tx function is NOT enabled */
    /* Or data stay in Tx buffer  */
    if((!(UARTX_CR1(ptUartNo) & USART_CR1_TE)) || (!(UARTX_SR(ptUartNo) & USART_SR_TXE)))
    {
        return SW_ERR;
    }
    /* Else, it is a valid data and send data into Tx buffer */
    UARTX_DR(ptUartNo) = *(ptData->pucBuffer);                                            

    return SW_OK;
}




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
void Uart_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
{
    T_REGISTED_DEVICE tUartDev;

    /* Check if the device No. is valid or NOT */
    if(ucDevNo > (MAX_UART_DEVICE_NUM - 1))
    {
        return;
    }

    /* set operation. */
    sg_tUartOp.pfDrvInit  = Uartx_Init;
    sg_tUartOp.pfDrvCtrl  = Uartx_Ctrl;
    sg_tUartOp.pfDrvRead  = Uartx_Read;
    sg_tUartOp.pfDrvWrite = Uartx_Write;
    /* register this device. */    
    tUartDev.ucAppType  = SW_COMM_INTERFACE;
    tUartDev.ucDevId    = SW_PERIPHERAL_UART;
    tUartDev.ucLogDevNo = ucLogNo;
    tUartDev.ucDevNo    = ucDevNo;
    tUartDev.ptDevOp    = &sg_tUartOp;
    tUartDev.pfCallBack = NULL;
    /* call register interface. */
    API_ComDrv_Reg(&tUartDev);
    
    return;
}

/**************************************************************************
* Funciton: static void Uartx_isr(BYTE ucNo)
* Descrip.: interrupt process function of uartx
* Input   : BYTE ucNo      1-5     Number of uart
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
static void Uartx_isr(BYTE ucDevNo)
{
    volatile WORD32 dwData;
    T_SW_INT_EVENT tReason;
    T_UART_MEM_MAP ptUartNo = sg_aptUartAddr[ucDevNo];
   
    /* Fill information of reason */
    tReason.ucAppType   = SW_COMM_INTERFACE;                      
    tReason.ucDevId     = SW_PERIPHERAL_UART;
    tReason.ucDevNo     = ucDevNo;
    tReason.ucBuffer[UART_INT_DATA_LEN_POS] = 0;

    /* If it is an interrupt due to error flags */
    if(UARTX_SR(ptUartNo) & USART_SR_ERR_MASK)
    {
        /* Clear error flag and data, and provide error event */
        dwData = UARTX_SR(ptUartNo);     
        dwData = UARTX_DR(ptUartNo);  
        tReason.ucEvent = INTERRUPT_EVENT_ERR;
    }

    /* If it is Rx interrupt */
    else if(UARTX_SR(ptUartNo) & USART_SR_RXNE)
    {
        /* receive Data */
        tReason.ucBuffer[UART_INT_RX_DATA_POS]  = UARTX_DR(ptUartNo);
        tReason.ucBuffer[UART_INT_DATA_LEN_POS] = 1;
        tReason.ucEvent = INTERRUPT_EVENT_RX;
    }

    /* If it is Tx interrupt */
    else if(UARTX_CR1(ptUartNo) & USART_CR1_TXEIE)
    {
        /* Disable Tx interrupt */
        UARTX_CR1(ptUartNo) &= ~(USART_CR1_TXEIE);
        tReason.ucEvent = INTERRUPT_EVENT_TX;                           
    }

    /* Call callback functon with reason */
    if(sg_pfAppCallBack[ucDevNo])
    {
        (sg_pfAppCallBack[ucDevNo])(&tReason);
    }
    
    return;
}

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
void Uart1_isr(void)
{
    Uartx_isr(UART_1);  /* Call uart 1 interrupt process function */

    return;
}

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
void Uart2_isr(void)
{
    Uartx_isr(UART_2);  /* Call uart 2 interrupt process function */

    return;
}

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
void Uart3_isr(void)
{
    Uartx_isr(UART_3);  /* Call uart 3 interrupt process function */

    return;
}


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
void Uart4_isr(void)
{
    Uartx_isr(UART_4);  /* Call uart 4 interrupt process function */

    return;
}


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
void Uart5_isr(void)
{
    Uartx_isr(UART_5);  /* Call uart 5 interrupt process function */

    return;
}


// End of Uart0.c



