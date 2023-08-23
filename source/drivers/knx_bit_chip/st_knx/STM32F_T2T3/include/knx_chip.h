/******************************************************************************************
* Right reserved (C 2019) Nanjing Shufan Information Technology Co.
*
* File Name        : knx_chip.h
*
* File Description : Header file for stm32f10xx & knx definition.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2019.4.1
*
* Modification Rec.:
*   Modify Data    : 2019.4.1
*   Operator       : Danny Cao.
*   Version        : 1.00
*   Action         : Creation.
*
******************************************************************(************************/


#ifndef _KNX_CHIP_H_
#define _KNX_CHIP_H_

#ifdef __cplusplus
extern "C" {
#endif



#define KNXCHIP_TO_MCU                 GET_GPIO_PORT_DATA(A,0)                     /* getting bit from knx chip. Attention: this pin is fixed to A0, or the driver has error.*/
#define MCU_TO_KNXCHIP                 GET_GPIO_PORT_DATA(A,7)                     /* getting bit from the output ping. */
#define RX_LINE_IS_ACTIVE              (KNXCHIP_TO_MCU != 0)
#define TX_LINE_IS_ACTIVE              (MCU_TO_KNXCHIP != 0)

#define SET_KNXCHIP_HIGH               SET_GPIO_PORT(A,0)
#define MCU_ENABLE_TX_2_KNX            SET_GPIO_PORT(A,6)                          /* enable MCU tx bit to KNX. */
#define MCU_DISABLE_TX_2_KNX           CLR_GPIO_PORT(A,6)                          /* disable MCU tx bit to KNX.*/


/* error mask for tx/rx. */
#define PH_RX_ERROR_MASK               0x0f
#define PH_TX_ERROR_MASK               0xf0
#define PH_ERR_FLAG_FRAME              0x01              /* Rx: frame error                                     */
#define PH_ERR_FLAG_PARITY             0x02              /* Rx: parity error                                    */
#define PH_ERR_FLAG_TX                 0x10              /* Tx: transmitter error                               */
#define PH_ERR_FLAG_TEMP               0x20              /* Tx: temperature warning                             */
#define PH_ERR_FLAG_TEMPSW             0x40              /* Tx: software signal that temp. warning was handled  */
#define PH_GET_RX_ERROR_FLG            (sg_ucPlErrorFlg & PH_RX_ERROR_MASK)
#define PH_SET_ERROR_FLG(error)        (sg_ucPlErrorFlg |= error)
#define PH_GET_TX_ERROR_FLG            (sg_ucPlErrorFlg & PH_TX_ERROR_MASK)

/* physical layer rx statemachine. it describes the state deuring one byte rx. */
#define PL_BIT_RX_IDLE                 0x00              /* physical layer rx is idle.  */
#define PL_BIT_RX_DATA                 0x01              /* physical layer rx is rxing. */
#define PL_BIT_RX_ERROR                0x02              /* physical layer rx is error. */

/* rx frame statemachin. */
#define PL_RX_FRAME_ONGOING            0x00              /* no incoming frames.       */
#define PL_RX_FRAME_END                0x01              /* start to receive a frame. */

#define PL_TX_FRAME_OFF                0x00
#define PL_TX_FRAME_ON                 0x01

/* define KNX ack byte. */
#define KNX_ACK_POS                    0xcc              /* KNX spec. positive ACK. */
#define KNX_ACK_NEG                    0x0c              /* KNX spec. negtive ACK.  */
#define KNX_ACK_BUSY                   0xc0              /* KNX spec. busy ACK.     */
#define KNX_ACK_NB                     0x00              /* KNX spec. neg&busy ACK. */


/* time define for rx/tx control. */
#define BIT_TIM                        416                   /* 104    104us bit time .             */
#define BIT_TIM_2                      832                   /* 208    2 bit time.                  */
#define BIT_TIM_3                      1248                  /* 312    3 bit time.                  */
#define BIT_TIM_4                      1664                  /* 416    4 bit time.                  */
#define BYTE_TIM                       4576                  /* 1144   1 byte's time = 11*104.      */
#define BYTE_TIM_2                     9152                  /* 2288   2 byte's time = 2*11*104.    */
#define BYTE_AND_SPACE_13TIM           5408                  /* 1352   1 byte + space time = 13*104 */
#define FRAME_AND_SPACE_15TIM          6240                  /* 1560   frame end space time = 15*104*/
#define BIT_35PULSE_TIM                140                   /* 35     normal time is 35.           */
#define BIT_IDLE_TIME                  276                   /* 69     idle time of a bit is 69us.  */
#define BIT_MIN_PULSE_TIM              52                    /* 13     min. time is 25us.           */
#define BIT_MAX_PULSE_TIM              296                   /* 70     max. time is 70us.  ->74us   */
#define BIT_MAX_OVERLAP_TIM            272                   /* 68us   for tx/rx overlap.           */
#define BIT_ACCEPTWIN_TIM              168                   /* 42     accept window is 40us. ->42  */
#define BIT_RX_OFFSET_TIM              32                    /* 8      accept window offset is 7us->8us.     */
#define BIT_STARTBIT_SPACE_TIME        165                   /* 32     window between 2 start bit is +-30us. */
#define RX_LINE_IDLE_TIME              20800                 /* 5200   wait 50*bit for idle.                 */
#define BIT_FILTER_TIME                48                    /* 13.5   filter time for the active pulse.     */
#define BIT_RISE_FILTER_TIME           41                    /* 10.25u for rising edge filter.      */
#define BIT_FALL_FILTER_TIME           99                    /* 24.75u for falling edge filter.     */
#define ACK_COMPENSATION_TIM           16                    /* 4us    for ack compensation time.   */
  
#define TX_BEGIN_50BITS                20800                 /* 5200   tx after 50 bits. 50*104. */
#define TX_BEGIN_53BITS                22048                 /* 5512   tx after 53 bits. 53*104. */
#define TX_RPT_BEGIN_24BITS            9984                  /* 2496   rpt tx without ACK after 24(50-15-11) bits. 50bits for idle. */
#define TX_RPT_BEGIN_27BITS            11232                 /* 2808   rpt tx without ACK after 27(53-15-11) bits. 53bits for idle. */
#define TX_ACK_BEGIN_FRMEND_TIM        6240                  /* 1560   tx ack time after the end of frame.                          */
#define TX_PROCESS_BEGIN_TIM           280                   /* 70     tx process at the next time slot.                            */
#define TX_TIMER_1MS_TIM               4000                  /* 1000   tx timer' 1ms time slot.                                     */

/* define for setting byte receiving control timer compare.. */
#define BYTE_RX_IS_ONGOING             ((TIM2->DIER & TIM_DIER_CC3IE) != 0)
#define BYTE_RXCTRL_TMINT_EN             TIM2->DIER |=  TIM_DIER_CC3IE
#define BYTE_RXCTRL_TMINT_DIS            TIM2->DIER &= ~TIM_DIER_CC3IE
#define BIT_RISE_EDGE_INT_PENDING      ((TIM2->SR   &  TIM_SR_CC1IF)  != 0)
#define BIT_FALL_EDGE_INT_PENDING      ((TIM2->SR   &  TIM_SR_CC2IF)  != 0)
#define BIT_RISE_INT_DISABBLE            TIM2->DIER &= ~TIM_DIER_CC1IE
#define BIT_FALL_INT_DISABBLE            TIM2->DIER &= ~TIM_DIER_CC2IE
#define BIT_RISE_INT_ENABLE              TIM2->DIER |= TIM_DIER_CC1IE
#define BIT_FALL_INT_ENABLE              TIM2->DIER |= TIM_DIER_CC2IE
#define BIT_RX_CAP_INT_CLR               TIM2->SR   &= ~(TIM_SR_CC1F | TIM_SR_CC2F)
#define BIT_RX_RISE_CAP_INT_CLR          TIM2->SR   &= ~TIM_SR_CC1F
#define BIT_RX_FALL_CAP_INT_CLR          TIM2->SR   &= ~TIM_SR_CC2F

#define BYTE_RXCTRL_TIMER_SET(wStartBitTime)   \
            {\
                TIM2->CCR3  = ((WORD16)(wStartBitTime + BYTE_TIM));\
                TIM2->SR   &= (~TIM_SR_CC3F);\
                TIM2->DIER |= TIM_DIER_CC3IE;\
            }
#define BYTE_RXCTRL_TIMER_STOP \
            {\
                TIM2->DIER &= (~TIM_DIER_CC3IE);\
                TIM2->SR   &= (~TIM_SR_CC3F);   \
            }

/* start rise edge capture. */
#define BIT_RISING_EDGE_CAP_START \
            {\
                TIM2->SR   &= ~(TIM_SR_CC1F | TIM_SR_CC2F);  \
                TIM2->CCER |= TIM_CCER_CC1E;                 \
                TIM2->DIER |= TIM_DIER_CC1IE;                \
            }
/* stop rise edge capture. */
#define BIT_RISING_EDGE_CAP_STOP \
            {\
                TIM2->CCER &= ~TIM_CCER_CC1E; \
                TIM2->DIER &= ~TIM_DIER_CC1IE;\
                TIM2->SR   &= ~TIM_SR_CC1F;   \
            }

/* start fall edge capture. */
#define BIT_FALLING_EDGE_CAP_START \
            {\
                TIM2->SR   &= ~(TIM_SR_CC1F | TIM_SR_CC2F);  \
                TIM2->CCER |= TIM_CCER_CC2E;                 \
                TIM2->DIER |= TIM_DIER_CC2IE;                \
            }
/* stop fall edge capture. */
#define BIT_FALLING_EDGE_CAP_STOP \
            {\
                TIM2->CCER &= ~TIM_CCER_CC2E; \
                TIM2->DIER &= ~TIM_DIER_CC2IE;\
                TIM2->SR   &= ~TIM_SR_CC2F;   \
            }

/* stop all capture. */
#define BIT_ALL_EDGE_CAP_STOP \
            {\
                TIM2->CCER &= ~(TIM_CCER_CC2E  | TIM_CCER_CC1E); \
                TIM2->DIER &= ~(TIM_DIER_CC2IE | TIM_DIER_CC1IE);\
                TIM2->SR   &= ~(TIM_SR_CC1F    | TIM_SR_CC2F);   \
            }

/* output set definition. */            
#define WANT_TO_OUTPUT_ACTIVE   \
            {\
                TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;  \
                TIM3->CCMR1 |=  TIM_CCMR1_OC2M_0;\
            }

#define WANT_TO_OUTPUT_IDLE     \
            {\
                TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;  \
                TIM3->CCMR1 |=  TIM_CCMR1_OC2M_1;\
            }

#define FORCE_OUTPUT_IDLE \
            {\
                TIM3->CCMR1 &= ~TIM_CCMR1_OC2M;  \
                TIM3->CCMR1 |=  TIM_CCMR1_OC2M_2;\
            }

#define ENABLE_OUTPUT_CAMP_INT     TIM3->DIER |=  TIM_DIER_CC2IE
#define DISABLE_OUTPUT_CAMP_INT    TIM3->DIER &= ~TIM_DIER_CC2IE; TIM3->SR = 0
#define IS_OUTPUT_CAMP_INT_EN      ((TIM3->DIER & TIM_DIER_CC2IE) != 0)
#define CLR_OUTPUT_CAMP_INT_FLG    TIM3->SR  = 0
#define SET_OUTPUT_CAMP_INT_FLG    TIM3->SR |= TIM_SR_CC2IF;
#define OUTPUT_CAMP_INT_PENDING    ((TIM3->SR  & TIM_SR_CC2IF) != 0)
#define SYNC_KNXPH_TIMER           sg_wTimCnt = TIM2->CNT; TIM3->CNT = sg_wTimCnt
#define IS_OUTPUT_WAITTO_ACTIVE    ((TIM3->CCMR1 & TIM_CCMR1_OC2M_0) != 0)

#define STOP_KNXPH_TIMER  \
            {\
                TIM2->CR1 &= ~TIM_CR1_CEN;  \
                TIM3->CR1 &= ~TIM_CR1_CEN;  \
            }
#define START_KNXPH_TIMER  \
            {\
                TIM2->CR1 |= TIM_CR1_CEN;  \
                TIM3->CR1 |= TIM_CR1_CEN;  \
            }

/* wait to output idle without interrupt. */
#define OUTPUT_IDLE_START_WITHOUT_INT(wWaitTime) \
            {\
                sg_wTimCnt = TIM3->CNT;                 \
                TIM3->CCR2 = sg_wTimCnt+ wWaitTime;     \
                DISABLE_OUTPUT_CAMP_INT;                \
                WANT_TO_OUTPUT_IDLE;                    \
            }
/* wait to output idle. */
#define OUTPUT_IDLE_START_WITH_INT(wWaitTime) \
            {\
                sg_wTimCnt = TIM3->CNT;                 \
                TIM3->CCR2 = sg_wTimCnt+ wWaitTime;     \
                CLR_OUTPUT_CAMP_INT_FLG;                \
                ENABLE_OUTPUT_CAMP_INT;                 \
                WANT_TO_OUTPUT_IDLE;                    \
            }
/* wait to output active. */
#define OUTPUT_ACTIVE_START_WITH_INT(wWaitTime) \
            {\
                sg_wTimCnt = TIM3->CNT;                 \
                TIM3->CCR2 = sg_wTimCnt+ wWaitTime;     \
                CLR_OUTPUT_CAMP_INT_FLG;                \
                ENABLE_OUTPUT_CAMP_INT;                 \
                WANT_TO_OUTPUT_ACTIVE;                  \
            }

#define QUIT_KNXPH_TX \
            {\
                FORCE_OUTPUT_IDLE;                   \
                DISABLE_OUTPUT_CAMP_INT;             \
            }

/***************************************************************************************************************
* Structure Name : T_KNXLL_ST_HANDLE
* Description    : this structure defines the entry of knx link layer operations.
* Parameters     : BYTE   ucBufferSize                          data buffer size for tx.
*                  BYTE   ucBufferNum                           data buffer number for tx.
*                  VOID  (*pfKnxLl_ConfirmHandle)(BYTE)         link layer confirm handler.
*                  VOID  (*KnxLl_ByteRxEntry)(BYTE,BYTE)        receive byte handler.
*                  VOID  (*KnxLl_FrameEndEntry)(VOID)           frame receive handler.
* Author         : Danny
* Modification   :
*   2017-8-27   Danny   Create.
****************************************************************************************************************/
typedef struct
{
    BYTE  ucBufferSize;
    BYTE  ucBufferNum;
    VOID (*pfKnxLl_ConfirmHandle)(BYTE);
    VOID (*KnxLl_ByteRxEntry)(BYTE,BYTE);
    VOID (*KnxLl_FrameEndEntry)(VOID);
}T_KNXLL_ST_HANDLE;

/***************************************************************************************************************
* Structure Name : T_KNX_CHIP_OP
* Description    : this structure defines the entry of knx physical layer operations.
* Parameters     : VOID   (*pfKnxPh_Process)(VOID)                                   knx chip process entry.
*                  VOID   (*pfKnxPh_Stop)(VOID)                                      knx ph stop.
*                  VOID   (*pfKnxPh_Reset)(VOID)                                     knx ph reset.
*                  VOID   (*pfKnxPh_Set_Ack)(BYTE ucAck)                             knx chip set ack entry.
*                  BOOL   (*pfKnxPh_IsTxBusy)(VOID)                                  physical layer is tx busy.                
*                  BOOL   (*pfKnxPh_IsTxing)(VOID)                                   physical layer is txing.                
*                  BOOL   (*pfKnxPh_IsRxing)(VOID)                                   physical layer is rxing.                
*                  BOOL   (*pfKnxPh_SetTxBuffer)(BYTE *pucBuffer)                    ph-layer sets sending buffer data entry.
*                  WORD32 (*pfPhKnx_Init)(BYTE ucDevNo,T_KNXLL_ST_HANDLE *pfHandler) ph-layer initialization entry.          
*                  BYTE   (*pfKnxPh_GetErrorFlg)(VOID)                               get error flags of ph.
* Author         : Danny
* Modification   :
*   2017-8-27   Danny   Create.
****************************************************************************************************************/
typedef struct
{
    VOID   (*pfKnxPh_Reset)(VOID);                                      /* knx ph reset.*/
    VOID   (*pfKnxPh_Stop)(VOID);                                       /* knx ph stop. */
    VOID   (*pfKnxPh_Process)(VOID);                                    /* knx chip process entry. */
    VOID   (*pfKnxPh_Set_Ack)(BYTE ucAck);                              /* knx chip set ack entry. */
    BOOL   (*pfKnxPh_IsTxBusy)(VOID);                                   /* physical layer is tx busy.              */
    BOOL   (*pfKnxPh_IsTxing)(VOID);                                    /* physical layer is txing.                */
    BOOL   (*pfKnxPh_IsRxing)(VOID);                                    /* physical layer is rxing.                */
    BOOL   (*pfKnxPh_SetTxBuffer)(BYTE *pucBuffer);                     /* ph-layer sets sending buffer data entry.*/
    WORD32 (*pfKnxPh_Init)(BYTE ucDevNo,T_KNXLL_ST_HANDLE *pfHandler);  /* ph-layer initialization entry.          */
    BYTE   (*pfKnxPh_GetErrorFlg)(VOID);                                /* get error flags of ph.                  */
}T_KNX_CHIP_OP;


/****************************************************************************************************************
* Function: VOID KnxPh_TxByteAndBit_Int(VOID)
* Descrip.: interrupt service of timer for tx. Timer works in continue mode with compare 2.
*           in Stm32f1xxx,07xxx, we use timer3's compare 2 associated with PA7.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxPh_TxByteAndBit_Int(VOID);

/****************************************************************************************************************
* Function: VOID KnxPh_RxByteAndBit_Int(VOID)
* Descrip.: interrupt service of timer for receiving. Timer works in continue mode with cap1,cap2,com3.
*           in Stm32f1xxx,07xxx, we use timer2's input channel 1 associated with PA0.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxPh_RxByteAndBit_Int(VOID);

/****************************************************************************************************************
* Function: VOID KnxPh_Register(VOID)
* Descrip.: handle the physical layer function.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxPh_Register(VOID);

/****************************************************************************************************************
* Function: BOOL KnxPl_SetTxBuffer(BYTE *pucBuffer)
* Descrip.: set data for tx. before call it we should check if physical layer is busy.
* Input   : BYTE *pucBuffer : tx data buffer pointer.
* Output  : none.
* Return  : TRUE : setting is successful.
*           FALSE: setting is failed.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
BOOL KnxPl_SetTxBuffer(BYTE *pucBuffer);

/****************************************************************************************************************
* Function: VOID KnxPh_Process(VOID)
* Descrip.: handle the physical layer function.
* Input   : none.
* Output  : none.
* Return  : none.
* Date             Version     Author        Content
* -------------------------------------------------------------------------------------------------------------
* 2019/04/01        V1.0      Danny.cao      creation
***************************************************************************************************************/
VOID KnxPh_Process(VOID);




#ifdef __cplusplus
}
#endif

#endif /* _STM32F10XX_KNX_CHIP_H_ */


