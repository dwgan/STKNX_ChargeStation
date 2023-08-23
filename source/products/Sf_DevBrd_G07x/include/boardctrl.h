/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：boardctrl.h
* FileIdentifier：None
* Abstract ：本文件为产品单板描述控制头文件。
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

#ifndef _BOARDCTRL_H_
#define _BOARDCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define STM32F10X
  
/* do not modify the name of the follow macro. */
#define CLK0_FREQ_HZ                          16000000

#ifndef MCU_SIZE
    #define MCU_SIZE 4   /* 4 bytes */
#endif

#ifndef FLASH_PAGE_SIZE
    #define FLASH_PAGE_SIZE                   2048
#endif

#ifdef FLASH_WRT_SIZE
    #undef  FLASH_WRT_SIZE
    #define FLASH_WRT_SIZE                    8
#else
    #define FLASH_WRT_SIZE                    8
#endif

/* redefine  the RxTx buffer pool size. */
#ifdef TOTAL_BUFFER_SIZE
    #undef  TOTAL_BUFFER_SIZE
#endif
#define TOTAL_BUFFER_SIZE               1288                                        /* 5 rx buffer,5 tx buffer.256 bytes for rx,128 bytes for tx. */
#define RX_BUFFER_NUMBER                5                                           /* rx buffer number. */
#define TX_BUFFER_NUMBER                5                                           /* tx buffer number. */
#define TX_PHY_BUFFER_SIZE              32                                          /* physical data buffer size. */

#define DEV_KEY_ON                      0
#define DEV_KEY_DEBOUNC_TIM             100
#define DEV_KEY_LONG_PRESS_TIM          300
  
/* Pin state define */
#define PIN_LOW_STATE                   0X00       /* Pin is Low voltage  */
#define PIN_HIGH_STATE                  0X01       /* Pin is High voltage */
#define PIN_LONGPRESS_STATE             0x80      /*  Pin is Long time hold*/


/* key press state machine. */
#define KEY_PRESS_NONE  0x00
#define KEY_PRESS_ST    0x01
#define KEY_PRESS_CONF  0x02
#define KEY_PRESS_REL   0x03

#define KEY1_ST_MASK    0xfc
#define KEY2_ST_MASK    0xf3
#define KEY3_ST_MASK    0xcf
#define KEY4_ST_MASK    0x3f

/* KNX power check. */
#define PIN_SAVE_SIGNAL                 (0 == GET_GPIO_PORT_DATA(A,5))              /* power down. */
/* KNX programming key */
#define KNX_KEY_PORT                    (0 == GET_GPIO_PORT_DATA(B,10))             /* knx programming key. */
/* KNX programming led */
#define SET_KNX_LED_OFF                 CLR_GPIO_PORT(B,12)                         /* Switch LED off */
#define SET_KNX_LED_ON                  SET_GPIO_PORT(B,12)                         /* Switch LED on  */  

#define SET_TST_LED_OFF                 CLR_GPIO_PORT(D,0)                         /* Switch test off */
#define SET_TST_LED_ON                  SET_GPIO_PORT(D,0)                         /* Switch test on  */  


#define SET_LED1                        1
#define SET_LED1_OFF                    CLR_GPIO_PORT(D,0)                         /* Switch Based board LED1 off */
#define SET_LED1_ON                     SET_GPIO_PORT(D,0)                         /* Switch Based boardLED1 on  */  
#define CHK_KEY1_PORT                   (0 == GET_GPIO_PORT_DATA(B,0))              /* key1. */


#define SET_LED2                        2
#define SET_LED2_OFF                    CLR_GPIO_PORT(D,1)                         /* Switch Based board LED2 off */
#define SET_LED2_ON                     SET_GPIO_PORT(D,1)                         /* Switch Based boardLED2 on  */  
#define CHK_KEY2_PORT                   (0 == GET_GPIO_PORT_DATA(B,1))              /* key2. */

#define SET_LED3                        3
#define SET_LED3_OFF                    CLR_GPIO_PORT(D,2)                         /* Switch Based board LED3 off */
#define SET_LED3_ON                     SET_GPIO_PORT(D,2)                         /* Switch Based board LED3 on  */  
#define CHK_KEY3_PORT                   (0 == GET_GPIO_PORT_DATA(B,2))              /* key3. */

#define SET_LED4                        4
#define SET_LED4_OFF                    CLR_GPIO_PORT(D,3)                         /* Switch Based board LED4 off */
#define SET_LED4_ON                     SET_GPIO_PORT(D,3)                         /* Switch Based board LED4 on  */
#define CHK_KEY4_PORT                   (0 == GET_GPIO_PORT_DATA(B,11))              /* key4. */

#define CHK_PIR_PORT                    (GET_GPIO_PORT_DATA(B,3) == 0)              /* PIR sensor output port */


/* BLE Reset Contrl port */
#define SET_RESETPIN_HIGH               SET_GPIO_PORT(B,7)                         /* Switch BLE Device to normal */
#define SET_RESETPIN_LOW                CLR_GPIO_PORT(B,7) 


/* Switch test on  */  
#define MASTER_RESET_TIME        3000                                        /* do master reset time.default 3s. */
/* device no define. */
#define AD_LOGIC_NO              0                                                  /* AD's logical No. */
#define AD_PHYSICAL_NO           0                                                  /* AD's physical No. */
#define TIMER_LOGIC_NO           0                                                  /* Timer logical No.  */
#define TIMER_PHYSICAL_NO        0                                                  /* Timer physical No. */
#define FLASH_LOGIC_NO           0                                                  /* Flash logical No.  */
#define FLASH_PHYSICAL_NO        0                                                  /* Flash physical No. */
#define KNX_CHIP_LOGIC_NO        0
#define KNX_CHIP_PH_NO           0


/*************************************************************************
* FunctionName:VOID BoardCtrl_Init(VOID) 
* 功能说明：设备描述初始化。
* InputParameterNone
* OutputParameterNone
* Return Value：None
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
VOID BoardCtrl_Init(VOID);

/*************************************************************************
* FunctionName:BOOL Board_PrgmLed_On(VOID)
* 功能说明：编程指示灯亮
* InputParameterNone
* OutputParameterNone
* Return Value：None
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL Board_PrgmLed_On(VOID);

/*************************************************************************
* FunctionName:BOOL Board_PrgmLed_Off(VOID)
* 功能说明：编程指示灯灭
* InputParameterNone
* OutputParameterNone
* Return Value：None
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL Board_PrgmLed_Off(VOID);

/*************************************************************************
* FunctionName:BOOL Board_PrgmKey_Handle(VOID)
* 功能说明：编程按钮状态判断
* InputParameterNone
* OutputParameterNone
* Return Value：None
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL Board_PrgmKey_Handle(VOID);

/*************************************************************************
* FunctionName:BOOL Board_SavePin_Check(VOID)
* 功能说明：判断总线掉电管脚是否有掉电。
* InputParameterNone
* OutputParameterNone
* Return Value：TRUE:出现总线掉电
                          FALSE:没有总线掉电
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL Board_SavePin_Check(VOID);

/*************************************************************************
* FunctionName:BOOL Board_CheckMasterReset(VOID)
* 功能说明：检查是否需要进行上电恢复默认设置。
* InputParameterNone
* OutputParameterNone
* Return Value：TRUE:要恢复
                          FALSE:不要恢复
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
BOOL Board_CheckMasterReset(VOID);

/*****************************************************************************************************
* Function        : VOID BrdCtrl_KeyCheck(VOID)
* Description     : check the key input.
* Input parameter : No.
* Output parameter: No.
* Return          : No.
* Other description:
*             K1	PIO0_0     0 is pressed. 1 is released.
*             K2	PIO0_1
*             K15	PIO0_15
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
VOID BrdCtrl_KeyCheck(VOID);

/**************************************************************************
* FunctionName: Set_Output(BYTE ucChnlNo, BYTE ucOnOff)
* FunctionDescription:  设置输出的管脚状态。
* InputParameter BYTE ucChnlNo           输出通道号，从1开始
                                     OUTPUT_CHANNLE_1
                                     OUTPUT_CHANNLE_2
                                     OUTPUT_CHANNLE_3
             BYTE ucOnOff            开关指令
                                     OUTPUT_LED_OFF  LED灯灭
                                     OUTPUT_LED_ON   LED灯亮
* OutputParameter None      
* Return Value： None
* Other Description: LED亮灭状态根据硬件设计进行修改
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
void Set_Output(BYTE ucChnlNo, BYTE ucOnOff);

/***************************************************************************************
* FunctionName:BOOL VOID BoardCtrl_Set(VOID)
* 功能说明：set device working parameters.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* --------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
****************************************************************************************/
VOID BoardCtrl_Set(VOID);

/*****************************************************************************************************
* Function        : BYTE Get_Input(BYTE ucChnlNo)
* Description     : return key status.
* Input parameter : BYTE ucChnlNo : channel No.
* Output parameter: No.
* Return          : key status.
* Other description:
* Date        version     author      action
* --------------------------------------------------------------------------------------------------
* 2018/06/06   V1.0	     Danny.cao   creation
****************************************************************************************************/
BYTE Get_Input(BYTE ucChnlNo);


void UARTCtrl_init(void);
void UartSendData(BYTE *pData, WORD16 Size);



#ifdef __cplusplus
}
#endif

#endif /* _BOARDCTRL_H_ */




