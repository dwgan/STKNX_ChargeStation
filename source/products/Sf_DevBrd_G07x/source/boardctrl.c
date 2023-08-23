/********************************************************************
* Right reserved (C)2022,STMicroelectronics(ShenZhen)R&D Co.,Ltd..
*
* File Name        : boardctrl.c
*
* File Description : stm32G07x demo board control.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : Roger Li
*
* Data             : 2022.4.13
*
* Modification Rec.:
*   Modify Data    : 2022.4.13
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
********************************************************************/

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "Buffer.h"
#include "boardcfg.h"
#include "boardctrl.h"
#include "hardware.h"

#include "stm32f10xx_systick.h"
#include "Stm32G0XX_Flash.h"
#include "Stm32G0xxx_adc.h"
#include "stm32f10xx_iwdg.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "app_common.h"
#include "Common_media.h"
#include "Knx_Prop.h"
#include "Application.h"
#include "Math_service.h"
#include "Comm_service.h"
#include "Knx_InternalApp.h"
#include "Application.h"
#include "Application_Data.h"
#include "Knx_Timer.h"
#include "knx_chip.h"
#include "knx_M0705_Ll.h"


#include "stm32g0xx_hal_def.h"
#include "stm32g0xx_hal_uart.h"
#include "stm32g0xx_hal_uart_ex.h"
#include "stm32g0xx_hal_gpio.h"

static  BYTE   sg_ucKeySt = 0;
WORD32 sg_adwKeyPressTm[4] = {0, 0, 0, 0};

extern void UartDataStore( uint8_t *pData, uint16_t Size );



/********** peripheral devices table *******************/

const T_DEV_DISC sg_tDeviceTable[5] = \
{
    {
        /* ucAppType     */ SW_CONTROL_INTERFACE, \
        /* ucDevId       */ SW_PERIPHERAL_TIMER, \
        /* ucLogDevlNo   */ TIMER_LOGIC_NO,      \
        /* ucDevNo       */ TIMER_PHYSICAL_NO,   \
        /* pfDevRegister */ SysTick_Reg
    },
    {
        /* ucAppType     */ SW_SAVE_INTERFACE,  \
        /* ucDevId       */ SW_PERIPHERAL_FLASH, \
        /* ucLogDevlNo   */ FLASH_LOGIC_NO,     \
        /* ucDevNo       */ FLASH_PHYSICAL_NO,  \
        /* pfDevRegister */ Stm32G0xxx_Flash_Reg
    },
    {
        /* ucAppType     */ SW_MATH_INTERFACE, \
        /* ucDevId       */ SW_PERIPHERAL_AD, \
        /* ucLogDevNo    */ AD_LOGIC_NO,      \
        /* ucDevNo       */ AD_PHYSICAL_NO,   \
        /* pfDevRegister */ ADC_Reg
    },
    {
        /* ucAppType     */ 0, \
        /* ucDevId       */ 0, \
        /* ucLogDevNo    */ 0,
        /* ucDevNo       */ 0, \
        /* pfDevRegister */ NULL
    }
};

/********** Table for mapping AD channel *******************
 Note: Developers should change this table according to the
       real hardware design. 0 to 7 is kept for KNX stack,
       and others is kept for application. If a channel is
       idle, it's physical number should be set as 0xFF.
************************************************************/
BYTE sg_aucAdChnlMap[SW_MATH_MAX_CHNL_NUM] = \
{
    /* Logic Port Num*/     /* Physical AD Port */
    /* For KNX stack */
    /* 00 */               SW_NONE_MEANING,                         \
    /* 01 bus voltage  */  0,                                       \
    /* 02 */               SW_NONE_MEANING,                         \
    /* 03 */               SW_NONE_MEANING,                         \
    /* 04 */               SW_NONE_MEANING,                         \
    /* 05 */               SW_NONE_MEANING,                         \
    /* 06 */               SW_NONE_MEANING,                         \
    /* 07 */               SW_NONE_MEANING,                         \
    /* For application */
    /* 08 */               1,                         \
    /* 09 */               SW_NONE_MEANING,                         \
    /* 10 */               4,                         \
    /* 11 */               7,                         \
    /* 12 */               2,                         \
    /* 13 */               3,                         \
    /* 14 */               SW_NONE_MEANING,                         \
    /* 15 */               SW_NONE_MEANING,                         \
    /* 16 */               SW_NONE_MEANING,                         \
    /* 17 */               SW_NONE_MEANING,                         \
    /* 18 */               SW_NONE_MEANING,                         \
    /* 19 */               SW_NONE_MEANING,                         \
    /* 20 */               SW_NONE_MEANING,                         \
    /* 21 */               SW_NONE_MEANING,                         \
    /* 22 */               SW_NONE_MEANING,                         \
    /* 23 */               SW_NONE_MEANING,                         \
};


/*************************************************************************
* FunctionName:VOID Prdt_PortsInit(VOID)
* 功能说明：产品相关端口初始化。
* InputParameterNone
* OutputParameterNone
* Return Value：None
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
void Prdt_PortsInit( void )
{
    /* Lvkong demo-kit 103
      Chip 2 Mcu                 PA9   I
      Mcu  2 Chip Ctrl           PA7   O  1 enable
      VBUS                       PA5   I  KNX ok

      UART_2_TX                  PA2
      UART_2_RX 				 PA3

      Base board LED1           PD0 // PA0
      Base board LED2           PD1 // PA1
      Base board LED3           PD2 // PB8
      Base board LED4           PD3 // PB9

      KEY1                      PB0
      KEY2                      PB1
      KEY3                      PB2
      KEY4                      PB11

      prg-Key                    PB10  I  0 pressed
      prg-LED                    PB12  O  1 light

    */
    RCC_IOPENR  |= ( RCC_IOPENR_GPIOAEN     | RCC_IOPENR_GPIOBEN | RCC_IOPENR_GPIODEN );
    RCC_IOPRSTR |= ( RCC_IOPRSTR_GPIOARST   | RCC_IOPRSTR_GPIOBRST | RCC_IOPRSTR_GPIODRST );
    RCC_IOPRSTR &= ( ~( RCC_IOPRSTR_GPIOARST | RCC_IOPRSTR_GPIOBRST | RCC_IOPRSTR_GPIODRST ) );

    /* Port A set. */
    GPIOA->MODER   &= GPIO_MODE_MASK_PA;
    GPIOA->MODER   |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER7_1   | GPIO_MODER_MODER3_1 | GPIO_MODER_MODER2_1 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER0_0;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7 | GPIO_OSPEEDR_OSPEEDR5_0 | GPIO_OSPEEDR_OSPEEDR1_0 | GPIO_OSPEEDR_OSPEEDR0_0;;
    GPIOA->PUPDR   |= GPIO_PUPDR_PUPDR2_0   | GPIO_PUPDR_PUPDR5_0   | GPIO_PUPDR_PUPDR9_0;
    GPIOA->AFR[0]  |= 0x10001100;                     /* PA7:AF1 PA2,PA3:AF1 */
    GPIOA->AFR[1]  |= 0x00000020;                     /* PA9:AF2 */

    /* Port B set. */
    GPIOB->MODER   &= GPIO_MODE_MASK_PA_EX;
    GPIOB->MODER   |= GPIO_MODER_MODER7_0   | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER12_0;
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR7_0 | GPIO_OSPEEDR_OSPEEDR8_0 | GPIO_OSPEEDR_OSPEEDR9_0 | GPIO_OSPEEDR_OSPEEDR12_0;

    SET_KNX_LED_OFF;


    /* Port D set. */
    GPIOD->MODER   &= GPIO_MODE_MASK_PA_EX;
    GPIOD->MODER   |= GPIO_MODER_MODER0_0   | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;
    GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR0_0 | GPIO_OSPEEDR_OSPEEDR1_0 | GPIO_OSPEEDR_OSPEEDR2_0 | GPIO_OSPEEDR_OSPEEDR3_0;



    SET_RESETPIN_LOW;

    SET_LED1_ON;
    SET_LED2_ON;
    SET_LED3_ON;
    SET_LED4_ON;


    SET_LED1_OFF;
    SET_LED2_OFF;
    SET_LED3_OFF;
    SET_LED4_OFF;



    return;
}

/*************************************************************************
* FunctionName:BOOL BoardCtrl_AdRead(BYTE ucLogDevNo,BYTE ucLogChnlNo,BYTE ucCunt,WORD16 *pwData)
* 功能说明：get AD data.
* InputParameterBYTE ucLogDevNo : logical device No.
            BYTE ucLogChnlNo: logical channel No.
            BYTE ucCunt     : sample count.
            WORD16 *pwData  : pointer of retuen data.
* OutputParameterWORD16 *pwData  : return AD data.
* Return Value：TRUE : get successfully.
            FALSE: get failed.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL BoardCtrl_AdRead( BYTE ucLogDevNo, BYTE ucLogChnlNo, BYTE ucCunt, WORD16 *pwData )
{
    T_SW_DEVICEDRIVER_PARA tDevPara;

    /* start conversion. */
    tDevPara.ucPara[0]  = SW_PERIPHERAL_AD;
    tDevPara.ucPara[1]  = ucLogDevNo;
    tDevPara.ucPara[2]  = ucLogChnlNo;
    tDevPara.ucPara[3]  = SW_ADC_SOFT_START;
    API_MathDrv_Ctrl( &tDevPara );
    /* get AD data. */
    API_MathDrv_Read( ucLogDevNo, 1, pwData );

    if( PIN_SAVE_SIGNAL )
    {
        /* power down. */
        *pwData = 0;
    }
    else
    {
        *pwData = 0x0644;  /* 30 v */
    }

    return TRUE;
}

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
#pragma location = "APP_INTERNAL_SEG"
VOID BoardCtrl_Init( VOID )
{
    T_DEV_DISC             *ptDev = ( T_DEV_DISC* )sg_tDeviceTable;
    T_SW_DEVICEDRIVER_PARA tDevPara;

    /* Ports init. */
    Prdt_PortsInit();

    /* initialize the rxtx pool. */
    Buffer_Pool_Init();
#if(DEBUG_ONOFF)
    Application_Para_Debug();
#endif
    while( SW_NA_INTERFACE != ptDev->ucAppType )
    {
        if( ( SW_PERIPHERAL_FLASH == ptDev->ucDevId ) && ( SW_SAVE_INTERFACE == ptDev->ucAppType ) )
        {
            /* flash device. */
            T_FLASH_TMOPER tFlashTmOp;

            tFlashTmOp.pfAppCheck = KnxLl_HaveToWaitCheck;
            tFlashTmOp.pfGetDlyMs = KnxTm_GetDelayMs;  /* must be ram function. */
            tFlashTmOp.pfGetMs    = KnxTm_GetTimeMs;   /* must be ram function. */
            ptDev->pfDevRegister( ptDev->ucLogDevNo, ptDev->ucDevNo, ( VOID * )( &tFlashTmOp ) );
        }
        else
        {
            ptDev->pfDevRegister( ptDev->ucLogDevNo, ptDev->ucDevNo, NULL ); /* register device. */
        }
        ptDev++;
    }
    /* flash initialize. */
    API_Common_Media_Init();
    API_MediaDev_Init( SW_SAVE_INTERFACE, FLASH_LOGIC_NO, NULL );
    /* AD initialization. */
    tDevPara.ucPara[0]  = SW_PERIPHERAL_AD;
    tDevPara.ucPara[1]  = 0;
    tDevPara.ucPara[2]  = 0;
    tDevPara.ucPara[3]  = SW_ADC_CONFIGURE;
    tDevPara.ucPara[4]  = ( SW_ADC_LOWEST_SPEED | SW_ADC_TRIGGER_SOFT | SW_ADC_SINGLE_CHL );
    tDevPara.ucPara[5]  = 0;
    tDevPara.ucPara[6]  = ADC_OVERSMPLE_64;
    tDevPara.pdwPara[0] = 0x0000001;                             /* physical channel 0. */
    tDevPara.pucBuf     = sg_aucAdChnlMap;
    tDevPara.pIntCallBackHandler = NULL;
    API_MathDrv_Init( &tDevPara );

    /* KNX chip register. */
    KnxPh_Register();

    return;
}

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
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_PrgmLed_Off( VOID )
{
    SET_KNX_LED_OFF;
    return TRUE;
}

/*************************************************************************
* FunctionName:BOOL Board_PrgmKey_Handle(VOID)
* 功能说明：编程按钮状态判断
* InputParameterNone
* OutputParameterNone
* Return Value：TRUE:编程按钮按下
            FALSE:编程按钮未按下
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_PrgmKey_Handle( VOID )
{
    return KNX_KEY_PORT;
}

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
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_PrgmLed_On( VOID )
{
    SET_KNX_LED_ON;
    return  TRUE;
}

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
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_SavePin_Check( VOID )
{
    return PIN_SAVE_SIGNAL;
}

/***************************************************************************************
* FunctionName:BOOL Board_CheckMasterReset(VOID)
* 功能说明：检查是否需要进行上电恢复默认设置。
* InputParameterNone
* OutputParameterNone
* Return Value：TRUE:要恢复
            FALSE:不要恢复
* Other Description:if Programming key is pressed over MASTER_RESET_TIME seconds at the start,
            we will reset the device to the default status.
* Modified Date VersionNumber Author ModifiedContent
* --------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
****************************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
BOOL Board_CheckMasterReset( VOID )
{
    WORD32 dwPressTime;

    /* Check programming key status. */
    if( KNX_KEY_PORT )
    {
        dwPressTime = API_KnxTm_GetTimeMs();
        while( 1 )
        {
            if( dwPressTime < 50 )
            {
                /* de-bounce 50ms. */
                continue;
            }
            if( ( dwPressTime >= MASTER_RESET_TIME ) && ( KNX_KEY_PORT ) )
            {
                return TRUE;
            }
            else if( !KNX_KEY_PORT )
            {
                break;
            }
        }
    }

    return FALSE;
}

/**************************************************************************
* function name   : BOOL BoardCtrl_Reset(VOID)
* Description     : reset the device.
* Input parameter : no.
* Output parameter: no.
* Return          : TRUE :successfully.
                    FALSE:failed.
* Other description:
* Modify date     Ver.     Modifier      Action
* ------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
**************************************************************************/
BOOL BoardCtrl_Reset( VOID )
{
    WORD32 dwAircr, dwResCnt = 0xffffffffu;

    dwAircr  = SCB->AIRCR;
    dwAircr &= 0x0000ffffu;
    dwAircr |= 0x05FA0004u;
    /* reset the cpu. */
    SCB->AIRCR = dwAircr;
    while( dwResCnt )
    {
        dwResCnt--;
    }

    return TRUE;
}

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
#pragma location = "APP_INTERNAL_SEG"
VOID BoardCtrl_Set( VOID )
{
    BOOL ucCheck;

    /* set the Application handler.every productor has to set the handlers. */
    API_Knx_UserAppHandler_Set( ( VOID* )Application_Process, APP_HANDLER_MAIN );
    /* set the handler for application initiation. */
    API_Knx_UserAppHandler_Set( ( VOID* )Application_Init, APP_HANDLER_INIT );
    /* set application save handler in running halt/stop. before running stop/halt stack will call
    this handler to save the user's data. */
    API_Knx_UserAppHandler_Set( ( VOID* )Application_Save, APP_HANDLER_SAVE );
    /* set application bus voltage down saving handler. when bus voltage down stack will call
    this handler to save the user's data. */
    API_Knx_UserAppHandler_Set( ( VOID* )Application_BusSave, APP_HANDLER_BUS_SAVE );
    /* set application power down saving handler. when power down stack will call
    this handler to save the user's data. */
    API_Knx_UserAppHandler_Set( ( VOID* )Application_PowerSave, APP_HANDLER_POWER_SAVE );
    /* set watchdog reset handler. */
    API_Knx_UserAppHandler_Set( ( VOID* )Stm32F10xx_Iwdg_Reset, APP_HANDLER_WDG_RESET );
    /* set CPU reset handler */
    API_Knx_UserAppHandler_Set( ( VOID* )BoardCtrl_Reset, APP_HANDLER_RESET_CPU );
    /* set program led off handler */
    API_Knx_UserAppHandler_Set( ( VOID* )Board_PrgmLed_Off, APP_HANDLER_PRGM_LED_OFF );
    /* set program led oN handler */
    API_Knx_UserAppHandler_Set( ( VOID* )Board_PrgmLed_On, APP_HANDLER_PRGM_LED_ON );
    /* set program key press handler */
    API_Knx_UserAppHandler_Set( ( VOID* )Board_PrgmKey_Handle, APP_HANDLER_PRGM_KEY );
    /* set bus power down check handler */
    API_Knx_UserAppHandler_Set( ( VOID* )Board_SavePin_Check, APP_HANDLER_BUS_POWER_CHECK );
    /* set AD operation handler. */
    API_Knx_UserAppHandler_Set( ( VOID* )BoardCtrl_AdRead, APP_HANDLER_ADC_OP );
    /**********************************************************************/
    /* start the knx timer. */
    Hw_SetIntPriority( SysTick_IRQn, 2 );
    /* Timer initialization will be done. */
    API_KnxTm_TimerInit( TIMER_LOGIC_NO );
    API_Common_Media_Init();
    API_RecTable_OpInit( FLASH_LOGIC_NO, FLASH_WRT_SIZE );
    /* check master reset.
          Attention: You should modify Board_CheckMasterRest function in BoardCtrl.c according to your application. */
    ucCheck = Board_CheckMasterReset();
    if( TRUE == ucCheck )
    {
        /* proframming key has been pressed over MASTER_RESET_TIME. */
        API_KnxMem_MediaRecoveDefault();
    }
    /* Init the media.check it's status. */
    API_KnxMem_InitMedia( FLASH_LOGIC_NO );
    /* record table clean up. */
    API_RecTable_CleanUpTable();
    /* KNX application layer management initialization. */
    API_Knx_AlMgmInit();
    /* KNX  virtual RAM memory management initialization. */
    API_KnxMem_VirRamInit();
    /* KNX virtual memory management initialization. */
    API_KnxMem_Init();

    /* KNX message process initialization. */
    API_Knx_MsgInit();

    /* register the uart device to knx link layer. */
    API_KnxLl_DevReg( KNX_CHIP_LOGIC_NO, KNX_CHIP_PH_NO, RX_BUFFER_NUMBER, TX_BUFFER_NUMBER );

    /* Knx link layer initalization. */
    API_KnxLl_Init( TX_BUFFER_NUMBER, TX_PHY_BUFFER_SIZE );

    /* priority set. */
    Hw_SetIntPriority( TIM3_IRQn, 0 );
    Hw_SetIntPriority( TIM1_CC_IRQn, 1 );
    /* Open interrupt. */
    Hw_InterruptEn( TIM1_CC_IRQn );
    Hw_InterruptEn( TIM3_IRQn );

    /* initializing the wathchdog,500ms period. */
//roger 2021.06.10 temporary removed for debuging    Stm32F10xx_Iwdg_Init(2000);

    return;
}

BYTE   g_ucFlag = 0;
WORD32 g_dwTimeSt = 0;
/* check key state. */
BYTE Get_Input( BYTE ucChNum )
{
    BYTE ucKeySt, ucRes = PIN_LOW_STATE;
    WORD32 dwTimDly;
    BYTE ucChnlNo = ucChNum + 1;
    static unsigned char keyprocessedflag[4];

    switch ( ucChnlNo )
    {
    case INPUT_CHANNEL_1:
    {
        ucKeySt = ( ( sg_ucKeySt & ( ~KEY1_ST_MASK ) ) >> 0 );
        switch( ucKeySt )
        {
        case KEY_PRESS_NONE:
        {
            if( CHK_KEY1_PORT )
            {
                sg_adwKeyPressTm[0] = API_KnxTm_GetTimeMs();
                sg_ucKeySt         &= KEY1_ST_MASK;
                sg_ucKeySt         |= ( KEY_PRESS_ST << 0 );
                keyprocessedflag[0]  = 0;
            }

            break;
        }
        case KEY_PRESS_ST:
        {
            if( CHK_KEY1_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[0] );
                if( dwTimDly > DEV_KEY_DEBOUNC_TIM )
                {
                    sg_ucKeySt &= KEY1_ST_MASK;
                    sg_ucKeySt |= ( KEY_PRESS_CONF << 0 );
                }
            }
            else
            {
                sg_ucKeySt &= KEY1_ST_MASK;
            }

            break;
        }
        case KEY_PRESS_CONF:
        {
            if( CHK_KEY1_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[0] );
                if( ( dwTimDly > DEV_KEY_LONG_PRESS_TIM ) && ( keyprocessedflag[0]  == 0 ) )
                {
                    ucRes = PIN_HIGH_STATE | PIN_LONGPRESS_STATE;
                    keyprocessedflag[0]  = 1;
                }
                break;
            }
            else
            {
                sg_ucKeySt &= KEY1_ST_MASK;
                sg_ucKeySt |= ( KEY_PRESS_REL << 0 );
            }

            break;
        }
        case KEY_PRESS_REL:
        {
            sg_ucKeySt &= KEY1_ST_MASK;
            ucRes       = PIN_HIGH_STATE;
            dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[0] );
            if( dwTimDly > DEV_KEY_LONG_PRESS_TIM )
            {
                ucRes |= PIN_LONGPRESS_STATE;
                if( keyprocessedflag[0]  == 1 )
                    ucRes = PIN_LOW_STATE;
            }
            break;
        }
        }

        break;
    }
    case INPUT_CHANNEL_2:
    {
        ucKeySt = ( ( sg_ucKeySt & ( ~KEY2_ST_MASK ) ) >> 2 );
        switch( ucKeySt )
        {
        case KEY_PRESS_NONE:
        {
            if( CHK_KEY2_PORT )
            {
                sg_adwKeyPressTm[1] = API_KnxTm_GetTimeMs();
                sg_ucKeySt         &= KEY2_ST_MASK;
                sg_ucKeySt         |= ( KEY_PRESS_ST << 2 );
                keyprocessedflag[1]  = 0;
            }

            break;
        }
        case KEY_PRESS_ST:
        {
            if( CHK_KEY2_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[1] );
                if( dwTimDly > DEV_KEY_DEBOUNC_TIM )
                {
                    sg_ucKeySt &= KEY2_ST_MASK;
                    sg_ucKeySt |= ( KEY_PRESS_CONF << 2 );
                }
            }
            else
            {
                sg_ucKeySt &= KEY2_ST_MASK;
            }

            break;
        }
        case KEY_PRESS_CONF:
        {
            if( CHK_KEY2_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[1] );
                if( ( dwTimDly > DEV_KEY_LONG_PRESS_TIM ) && ( keyprocessedflag[1]  == 0 ) )
                {
                    ucRes = PIN_HIGH_STATE | PIN_LONGPRESS_STATE;
                    keyprocessedflag[1]  = 1;
                }
                break;
            }
            else
            {
                sg_ucKeySt &= KEY2_ST_MASK;
                sg_ucKeySt |= ( KEY_PRESS_REL << 2 );
            }

            break;
        }
        case KEY_PRESS_REL:
        {
            sg_ucKeySt &= KEY2_ST_MASK;
            ucRes       = PIN_HIGH_STATE;
            dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[1] );
            if( dwTimDly > DEV_KEY_LONG_PRESS_TIM )
            {
                ucRes |= PIN_LONGPRESS_STATE;
                if( keyprocessedflag[1]  == 1 )
                    ucRes = PIN_LOW_STATE;
            }

            break;
        }
        }

        break;
    }
    case INPUT_CHANNEL_3:
    {
        ucKeySt = ( ( sg_ucKeySt & ( ~KEY3_ST_MASK ) ) >> 4 );
        switch( ucKeySt )
        {
        case KEY_PRESS_NONE:
        {
            if( CHK_KEY3_PORT )
            {
                sg_adwKeyPressTm[2] = API_KnxTm_GetTimeMs();
                sg_ucKeySt         &= KEY3_ST_MASK;
                sg_ucKeySt         |= ( KEY_PRESS_ST << 4 );
                keyprocessedflag[2]  = 0;
            }

            break;
        }
        case KEY_PRESS_ST:
        {
            if( CHK_KEY3_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[2] );
                if( dwTimDly > DEV_KEY_DEBOUNC_TIM )
                {
                    sg_ucKeySt &= KEY3_ST_MASK;
                    sg_ucKeySt |= ( KEY_PRESS_CONF << 4 );
                }
            }
            else
            {
                sg_ucKeySt &= KEY3_ST_MASK;
            }

            break;
        }
        case KEY_PRESS_CONF:
        {
            if( CHK_KEY3_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[2] );
                if( ( dwTimDly > DEV_KEY_LONG_PRESS_TIM ) && ( keyprocessedflag[2]  == 0 ) )
                {
                    ucRes = PIN_HIGH_STATE | PIN_LONGPRESS_STATE;
                    keyprocessedflag[2]  = 1;
                }
                break;
            }
            else
            {
                sg_ucKeySt &= KEY3_ST_MASK;
                sg_ucKeySt |= ( KEY_PRESS_REL << 4 );
            }

            break;
        }
        case KEY_PRESS_REL:
        {
            sg_ucKeySt &= KEY3_ST_MASK;
            ucRes       = PIN_HIGH_STATE;
            dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[2] );
            if( dwTimDly > DEV_KEY_LONG_PRESS_TIM )
            {
                ucRes |= PIN_LONGPRESS_STATE;
                if( keyprocessedflag[2]  == 1 )
                    ucRes = PIN_LOW_STATE;

            }

            break;
        }
        }

        break;
    }
    case INPUT_CHANNEL_4:
    {
        ucKeySt = ( ( sg_ucKeySt & ( ~KEY4_ST_MASK ) ) >> 6 );
        switch( ucKeySt )
        {
        case KEY_PRESS_NONE:
        {
            if( CHK_KEY4_PORT )
            {
                sg_adwKeyPressTm[3] = API_KnxTm_GetTimeMs();
                sg_ucKeySt         &= KEY4_ST_MASK;
                sg_ucKeySt         |= ( KEY_PRESS_ST << 6 );
                keyprocessedflag[3]  = 0;
            }

            break;
        }
        case KEY_PRESS_ST:
        {
            if( CHK_KEY4_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[3] );
                if( dwTimDly > DEV_KEY_DEBOUNC_TIM )
                {
                    sg_ucKeySt &= KEY4_ST_MASK;
                    sg_ucKeySt |= ( KEY_PRESS_CONF << 6 );
                }
            }
            else
            {
                sg_ucKeySt &= KEY4_ST_MASK;
            }

            break;
        }
        case KEY_PRESS_CONF:
        {
            if( CHK_KEY4_PORT )
            {
                dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[3] );
                if( ( dwTimDly > DEV_KEY_LONG_PRESS_TIM ) && ( keyprocessedflag[3]  == 0 ) )
                {
                    ucRes = PIN_HIGH_STATE | PIN_LONGPRESS_STATE;
                    keyprocessedflag[3]  = 1;
                }
                break;
            }
            else
            {
                sg_ucKeySt &= KEY4_ST_MASK;
                sg_ucKeySt |= ( KEY_PRESS_REL << 6 );
            }

            break;
        }
        case KEY_PRESS_REL:
        {
            sg_ucKeySt &= KEY4_ST_MASK;
            ucRes       = PIN_HIGH_STATE;
            dwTimDly = API_KnxTm_GetDelayMs( sg_adwKeyPressTm[3] );
            if( dwTimDly > DEV_KEY_LONG_PRESS_TIM )
            {
                ucRes |= PIN_LONGPRESS_STATE;
                if( keyprocessedflag[0]  == 1 )
                    ucRes = PIN_LOW_STATE;

            }

            break;
        }
        }

        break;
    }
    }

    return ucRes;
}


/* control led. */
void Set_Output( BYTE ucChnlNo, BYTE ucOnOff )
{
    switch( ucChnlNo )
    {
    case SET_LED1 :
        if( ucOnOff == 0 )
        {
            SET_LED1_OFF;
        }
        else
        {
            SET_LED1_ON;
        }
        break;

    case SET_LED2:
        if( ucOnOff == 0 )
        {
            SET_LED2_OFF;
        }
        else
        {
            SET_LED2_ON;
        }
        break;

    case SET_LED3:
        if( ucOnOff == 0 )
        {
            SET_LED3_OFF;

        }
        else
        {
            SET_LED3_ON;
        }

        break;

    case SET_LED4 :
        if( ucOnOff == 0 )
        {
            SET_LED4_OFF;
        }
        else
        {
            SET_LED4_ON;
        }
        break;

    default:
        break;


    }
    return;
}

/*##-1- Configure the UART peripheral ######################################*/
/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
/* UART configured as follows:
    - Word Length = 8 Bits
    - Stop Bit = One Stop bit
    - Parity = None
    - BaudRate = 9600 baud
    - Hardware flow control disabled (RTS and CTS signals) */

/* UART handler declaration */
UART_HandleTypeDef UartHandle;
/* Buffer used for reception */
unsigned char aRxBuffer[100];
extern unsigned char HMI_uartRxBuff[];

/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****HELLOW**** ";

void UARTCtrl_init( void )
{
    UartHandle.Instance 	   = USART2;
    UartHandle.Init.BaudRate	= 115200;
    UartHandle.Init.WordLength =   UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits	= UART_STOPBITS_1;
    UartHandle.Init.Parity 	= UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl	= UART_HWCONTROL_NONE;
    UartHandle.Init.Mode		= UART_MODE_TX_RX;
    UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if( HAL_UART_DeInit( &UartHandle ) != HAL_OK )
    {
        SET_LED1_ON;
    }
    if( HAL_UART_Init( &UartHandle ) != HAL_OK )
    {
        SET_LED1_ON;
    }

    /*##-2- Start the transmission process #####################################*/
    /* While the UART in reception process, user can transmit data through
       "aTxBuffer" buffer */
    if( HAL_UART_Transmit_IT( &UartHandle, ( uint8_t* )aTxBuffer, 20 ) != HAL_OK )
    {
        SET_LED1_ON;;  // Error_Handler();
    }


    /*##-2- Put UART peripheral in reception process ###########################*/
    if( HAL_UART_Receive_IT( &UartHandle, ( unsigned char * )HMI_uartRxBuff, 1 ) != HAL_OK )
    {
        SET_LED1_ON;;  //Error_Handler();
    }

    /* priority set. */
    Hw_SetIntPriority( USART2_IRQn, 2 );
    /* Open interrupt. */
    Hw_InterruptEn( USART2_IRQn );

}

void UartSendData( uint8_t *pData, uint16_t Size )
{
    HAL_UART_Transmit_IT( &UartHandle, pData, Size );
}

/**
  * @brief  Toggle the specified GPIO pin.
  * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32G0xx family
  * @param  GPIO_Pin specifies the pin to be toggled.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void HAL_GPIO_TogglePin( GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin )
{
    /* Check the parameters */
    //assert_param(IS_GPIO_PIN(GPIO_Pin));

    if ( ( GPIOx->ODR & GPIO_Pin ) != 0x00u )
    {
        GPIOx->BRR = ( uint32_t )GPIO_Pin;
    }
    else
    {
        GPIOx->BSRR = ( uint32_t )GPIO_Pin;
    }
}


/* End of file */

