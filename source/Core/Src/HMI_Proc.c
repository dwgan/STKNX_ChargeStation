#include "HMI_Proc.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "sw_common.h"
#include "boardctrl.h"
#include "stm32g0xx_hal_uart.h"
#include "stm32g0xx_hal_gpio.h"
#include "SerialProc.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include <time.h>
#include "Knx_M0705.h"
#include "Knx_InternalData.h"
#include "stm32g0xx_hal_rcc.h"
#include "stm32g0xx.h"


/**************************************************************************
* valuable definition
**************************************************************************/
HMI_StateValue_t HMI_StateValue={0};


/**
 * @description: Initialize the corresponseding port of STM32, 
            this function should be called to initialize the STM32.
            Note that the corresponseding GPIO should be configurated in .h file
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_STM32GPIO_Init()
{
    HMI_CONNECTED_GPIO->PUPDR |= HMI_CONNECTED_GPIO_PUPDR;
    HMI_CONNECTED_GPIO->MODER &= ~HMI_CONNECTED_GPIO_MODER;
    
    NFC_TAG_GPIO->PUPDR |= NFC_TAG_GPIO_PUPDR;
    NFC_TAG_GPIO->MODER &= ~NFC_TAG_GPIO_MODER;
    
    RCC->IOPENR |= RCC_IOPENR_GPIOCEN;

    LED_S0_GPIO->MODER = GPIO_MODE_MASK_PA_EX;
    LED_S0_GPIO->PUPDR |= LED_S0_PUPDR;
    LED_S0_GPIO->MODER   |= LED_S0_MODER;
    LED_S1_GPIO->PUPDR |= LED_S1_PUPDR;
    LED_S1_GPIO->MODER   |= LED_S1_MODER;
    LED_S2_GPIO->PUPDR |= LED_S2_PUPDR;
    LED_S2_GPIO->MODER   |= LED_S2_MODER;
}

/**
 * @description: Initialize the display of HMI screen, 
            this function should be called to initialize the HMI¡£
            Note that this function should be called after UART initialization.
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_Init()
{
    HMI_STM32GPIO_Init();

    /*******************update the state to HMI*********************/
//    uint8_t UartDataBuff[RTXBUFFLEN];
//    unsigned char length;
//    // update current value to HMI
//    length = sprintf( ( char* )UartDataBuff, "%s.txt=\"%d.%dA\"\xff\xff\xff", "t1", \
//                      ( unsigned int )( ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) ) / 1000, \
//                      ( unsigned int )( ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) ) % 1000 );
//    serialData2Buff_Write( UartDataBuff, length );
    
    /*******************update the state to KNX Bus*********************/
    static volatile BYTE* PhyDataAddressPtr = (BYTE*)(VIR_ADDR_TABLE + VIR_TO_REAL_OFFSET+2);
    sprintf((char*)HMI_StateValue.chargerid,"ACC0%d",*PhyDataAddressPtr);
    HMI_StateValue.chargeridflag=1;
    HMI_StateValue.connectupdateflag=1;
}

void KNX_Bus_Init()
{
    HMI_StateValue.connectupdateflag=1;
    HMI_StateValue.runningupdateflag=1;
    HMI_StateValue.batteryupdateflag=1;
    HMI_StateValue.temperatureflag=1;
    HMI_StateValue.chargedtimeflag=1;
    HMI_StateValue.remaintimeflag=1;
}

/**
 * @description: Get the information from the Battery, this function
       should be called right after the connected battery is detected.
        Note that the battery percent and temperature is random initialized for display,
    the full capacity should be calculated according to the charge time duration.
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void Battery_Info_Get()
{
    srand((unsigned int)SysTick->VAL);
    HMI_StateValue.batterypercent = rand() % 20 + 10;
    HMI_StateValue.batteryupdateflag = 1;

    HMI_StateValue.temperature = rand() % 40 + 350;
    HMI_StateValue.temperatureflag = 1;

    uint16_t current = 12000;
    HMI_StateValue.currentvalue[1] = current & 0xff;
    HMI_StateValue.currentvalue[0] = ( current & 0xff00 ) >> 8;

    HMI_StateValue.fullcapacity = 880000;

    HMI_StateValue.currentcapacity = HMI_StateValue.batterypercent * HMI_StateValue.fullcapacity / 100;
}

/**
 * @description: Calculate the charging energy according to the current value,
        {HMI_LOOP_PERIOD} should be calculate to control the calculating period.
        in this example, the current capacity is updated per minute.
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void Battery_ChargeInfo_Calculate()
{
    // Current Time calculation
    static WORD16 timeVal;
    static uint8_t second;
    
    if ( ++timeVal > 1000 / HMI_LOOP_PERIOD ) // per second
    {
        timeVal = 0;
        if ( HMI_StateValue.runningstatus )
        {
            HMI_StateValue.currentcapacity += 220 * ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) / 60 / 60;
            HMI_StateValue.chargeenergy += 220 * ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) / 60 / 60;
            if ( ++second >= 60 ) // per minute
            {
                second = 0;
                HMI_StateValue.chargeenergyflag = 1;
                HMI_StateValue.chargedtime += 1;
            }
            if ( HMI_StateValue.currentcapacity >= HMI_StateValue.fullcapacity )
            {
                HMI_StateValue.currentcapacity = HMI_StateValue.fullcapacity;
                HMI_StateValue.currentvalue[0] = 0;
                HMI_StateValue.currentvalue[1] = 0;
                HMI_StateValue.runningstatus = 0;
                HMI_StateValue.runningupdateflag = 1;
                HMI_StateValue.chargedtime = 0;
            }
        }
    }
    
    if ( HMI_StateValue.currentvalue[0] == 0 && HMI_StateValue.currentvalue[1] == 0 )
    {
        HMI_StateValue.remainchargetime = 0;
    }
    else
    {
        HMI_StateValue.remainchargetime = 1 + ( HMI_StateValue.fullcapacity - HMI_StateValue.currentcapacity ) * 60 / ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) / 220;
    }
    
    static WORD16 currentValBak;
    if ( ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) != currentValBak )
    {
        HMI_StateValue.chargepower = 220 * ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 );
        HMI_StateValue.chargepowerflag=1;
    }
    currentValBak =( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 );
    
    HMI_StateValue.batterypercent = HMI_StateValue.currentcapacity  * 100 / HMI_StateValue.fullcapacity;
}

/**
 * @description: Calculate the system time and convert it to display format.
            Note that this function only support 24 hours calculating.
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_TimeData_Update()
{
    uint8_t UartDataBuff[RTXBUFFLEN];
    unsigned char length;
    uint8_t second, minute, hour;

    // Current Time calculation
    static WORD16 timeVal;
    if ( ++timeVal >= 1000 / HMI_LOOP_PERIOD ) // increse TimesMsInc per 1 s
    {
        timeVal = 0;
        HMI_StateValue.TimesMsInc++;
    }

    // Update display date and time to HMI
    length = sprintf( ( char* )UartDataBuff, "%s=\"%d-%.2d-%.2d\"\xff\xff\xff", "t2.txt", \
                      ( unsigned int )( ( HMI_StateValue.timedata[0] ) + 1900 ), \
                      ( unsigned int )( ( HMI_StateValue.timedata[1] & 0xf ) ), \
                      ( unsigned int )( ( HMI_StateValue.timedata[2] & 0x1f ) ) );
    serialData2Buff_Write( UartDataBuff, length );

    WORD32 time = ( HMI_StateValue.timedata[3] & 0x1f ) * 60 * 60
                  + ( HMI_StateValue.timedata[4] & 0x3f ) * 60
                  + ( HMI_StateValue.timedata[5] & 0x3f )
                  + HMI_StateValue.TimesMsInc;
    hour = time / 60 / 60 % 24;
    minute = ( time - hour * 60 * 60 ) / 60 % 60;
    second = ( time - hour * 60 * 60 - minute * 60 ) % 60;
    length = sprintf( ( char* )UartDataBuff, "%s=\"%.2d:%.2d:%.2d\"\xff\xff\xff", "t6.txt", \
                      ( unsigned int )( hour ), \
                      ( unsigned int )( minute ), \
                      ( unsigned int )( second ) );
    serialData2Buff_Write( UartDataBuff, length );
}

void LED_StatusUpdate(BYTE status);
/**
 * @description: Update the display of HMI screen periodically
            this function should be called periodically to update the HMI
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
static void HMI_DispInfoStateMachine_Update()
{
    uint8_t UartDataBuff[RTXBUFFLEN];
    unsigned char length;

    /*******************update the state to HMI*********************/
    if ( HMI_StateValue.connectionstatus == FALSE ) // the power cable is disconnected
    {
        HMI_StateValue.runningstatus = 0;
        // update connectionstatus to HMI
        length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "constatus", ( unsigned int )( ( HMI_StateValue.connectionstatus ) ) );
        serialData2Buff_Write( UartDataBuff, length );
        length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "runningstatus", ( unsigned int )( ( HMI_StateValue.runningstatus ) ) );
        serialData2Buff_Write( UartDataBuff, length );
        LED_StatusUpdate(0);
    }
    else // the power cable is connected
    {
        if ( HMI_StateValue.runningstatus == TRUE ) // the battery is charging
        {
            // update connectionstatus to HMI
            length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "constatus", ( unsigned int )( ( HMI_StateValue.connectionstatus ) ) );
            serialData2Buff_Write( UartDataBuff, length );
            // update runningstatus to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.val=%d\xff\xff\xff", "sw0", 1 );
            serialData2Buff_Write( UartDataBuff, length );
            length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "runningstatus", ( unsigned int )( ( HMI_StateValue.runningstatus ) ) );
            serialData2Buff_Write( UartDataBuff, length );
            // update current value to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"%d.%d A\"\xff\xff\xff", "t1", \
                              ( unsigned int )( ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) ) / 1000, \
                              ( unsigned int )( ( HMI_StateValue.currentvalue[1] | HMI_StateValue.currentvalue[0] << 8 ) ) % 1000 / 100 );
            serialData2Buff_Write( UartDataBuff, length );
            // update batterypercent to HMI
            length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "j0val", ( unsigned int )HMI_StateValue.batterypercent );
            serialData2Buff_Write( UartDataBuff, length );
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"%d%%\"\xff\xff\xff", "t4", ( unsigned int )HMI_StateValue.batterypercent );
            serialData2Buff_Write( UartDataBuff, length );
            // update chargedtime to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"%d min\"\xff\xff\xff", "t0", ( unsigned int )HMI_StateValue.chargedtime );
            serialData2Buff_Write( UartDataBuff, length );
            // update remainchargetime to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"ID: %s\"\xff\xff\xff", "t3", HMI_StateValue.chargerid);//, ( unsigned int )HMI_StateValue.remainchargetime );
            serialData2Buff_Write( UartDataBuff, length );
            // update temperature to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"%d.%d¡æ\"\xff\xff\xff", "t5", \
                              ( unsigned int )HMI_StateValue.temperature / 10, \
                              ( unsigned int )HMI_StateValue.temperature % 10 );
            serialData2Buff_Write( UartDataBuff, length );
            LED_StatusUpdate(2);
        }
        else // the battery is not charging
        {
            // update connectionstatus to HMI
            length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "constatus", ( unsigned int )( ( HMI_StateValue.connectionstatus ) ) );
            serialData2Buff_Write( UartDataBuff, length );
            // update runningstatus to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.val=%d\xff\xff\xff", "sw0", 0 );
            serialData2Buff_Write( UartDataBuff, length );
            length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "runningstatus", ( unsigned int )( ( HMI_StateValue.runningstatus ) ) );
            serialData2Buff_Write( UartDataBuff, length );
            // update current value to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"- - - A\"\xff\xff\xff", "t1" );
            serialData2Buff_Write( UartDataBuff, length );
            // update batterypercent to HMI
            length = sprintf( ( char* )UartDataBuff, "%s=%d\xff\xff\xff", "j0val", ( unsigned int )HMI_StateValue.batterypercent );
            serialData2Buff_Write( UartDataBuff, length );
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"%d%%\"\xff\xff\xff", "t4", ( unsigned int )HMI_StateValue.batterypercent );
            serialData2Buff_Write( UartDataBuff, length );
            // update chargedtime to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"- - min\"\xff\xff\xff", "t0" );
            serialData2Buff_Write( UartDataBuff, length );
            // update remainchargetime to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"ID: %s\"\xff\xff\xff", "t3", HMI_StateValue.chargerid);
            serialData2Buff_Write( UartDataBuff, length );
            // update temperature to HMI
            length = sprintf( ( char* )UartDataBuff, "%s.txt=\"%d.%d¡æ\"\xff\xff\xff", "t5", \
                              ( unsigned int )HMI_StateValue.temperature / 10, \
                              ( unsigned int )HMI_StateValue.temperature % 10 );
            serialData2Buff_Write( UartDataBuff, length );
            LED_StatusUpdate(1);
        }
    }
}

/**
 * @description: Update the control logil of HMI screen for reseting the status
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_DispInfoChange_Update()
{
    static HMI_StateValue_t HMI_StateValue_Backup;

    static WORD16 timeVal;
    if ( ++timeVal >= 1000 / HMI_LOOP_PERIOD ) // increse TimesMsInc per 1 s
    {
        timeVal = 0;
        
        if ( HMI_StateValue.connectionstatus )
        {
            if ( HMI_StateValue.batterypercent != HMI_StateValue_Backup.batterypercent )
            {
                HMI_StateValue.batteryupdateflag = 1;
            }
        }
        if ( HMI_StateValue.runningstatus )
        {
            if ( HMI_StateValue.chargedtime != HMI_StateValue_Backup.chargedtime )
            {
                HMI_StateValue.chargedtimeflag = 1;
            }
            if ( HMI_StateValue.remainchargetime != HMI_StateValue_Backup.remainchargetime )
            {
                HMI_StateValue.remaintimeflag = 1;
            }
            if ( HMI_StateValue.currentvalue != HMI_StateValue_Backup.currentvalue )
            {
                HMI_StateValue.currentcapacityupdateflag = 1;
            }
        }
        HMI_StateValue_Backup = HMI_StateValue;
    }
}

/**
 * @description: Start to charge
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_ResumeCharge()
{
    HMI_StateValue.runningstatus = TRUE;
    HMI_StateValue.runningupdateflag = 1;
    HMI_StateValue.connectupdateflag = 1;
    HMI_StateValue.chargepowerflag = 1;
}

/**
 * @description: Start to charge
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_PauseCharge()
{
    HMI_StateValue.runningstatus = FALSE;
    HMI_StateValue.runningupdateflag = 1;
    HMI_StateValue.connectupdateflag = 1;
    HMI_StateValue.chargepowerflag = 1;
}

/**
 * @description: HMI status update periodically
    repeat period can be set according to HMI_RERUN_PERIOD
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_StatusCycle()
{
    static BYTE connectionstatusBackup;
    static WORD32 time=0;

    if ( !connectionstatusBackup && HMI_StateValue.connectionstatus)
    {
        Battery_Info_Get();
    }
    connectionstatusBackup=HMI_StateValue.connectionstatus;
      
    // Start charging after few minutes if the cable is connected
    if (HMI_StateValue.connectionstatus && !HMI_StateValue.runningstatus)
    {
        if (time < HMI_RERUN_PERIOD/HMI_LOOP_PERIOD)
        {
            time++;
        }
        else
        {
            Battery_Info_Get();
            HMI_ResumeCharge();
            time =0;
        }
    }
}

/**
 * @description: Get the connetion status of the battery
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void HMI_ConnectStatus_Get()
{
    static uint32_t IO_Value_Backup;
    uint32_t IO_Value;
    IO_Value = HMI_CONNECTED_GPIO->IDR & HMI_CONNECTED_PIN;
    // get the connection status
    HMI_StateValue.connectionstatus = IO_Value ? 0 : 1;
    if ( IO_Value_Backup ^ IO_Value )
    {
        HMI_StateValue.connectupdateflag = 1;
        HMI_StateValue.runningupdateflag = 1;
        if ( !HMI_StateValue.connectionstatus )
        {
            HMI_StateValue.chargedtime = 0;
            HMI_StateValue.chargedtimeflag = 1;
            HMI_StateValue.remaintimeflag = 1;
            HMI_StateValue.remainchargetime = 0;
            HMI_StateValue.temperature = 0;
            HMI_StateValue.temperatureflag = 1;
            HMI_StateValue.batterypercent = 0;
            HMI_StateValue.batteryupdateflag = 1;
            HMI_StateValue.runningstatus = 0;
        }
    }
    IO_Value_Backup = IO_Value;
}

/**
 * @description: Get the connetion status of the NFC Tag
 * @param {none} 
 * @return: none
 * @date 2023/8/21
 */
void NFC_TAG_Status_Get()
{
    static uint32_t IO_Value_Backup;
    uint32_t IO_Value;
    IO_Value = NFC_TAG_GPIO->IDR & NFC_TAG_PIN;
    // get the NFC TAG status
    if ( !IO_Value_Backup && IO_Value )
    {
        if ( HMI_StateValue.connectionstatus )
        {
            if (HMI_StateValue.runningstatus)
            {
                HMI_PauseCharge();
            }
            else
            {
                if ( HMI_StateValue.batterypercent >= 100 )
                {
                    Battery_Info_Get();
                }
                HMI_ResumeCharge();
            }
        }
    }
    IO_Value_Backup = IO_Value;
}

/**
 * @description: LED_StatusUpdate
 * @param {type} receive byte
 * @return: none
 */
void LED_StatusUpdate(BYTE status)
{
    switch (status)
    {
    case 0:
      LED_S0_SET;
      LED_S1_RESET;
      LED_S2_RESET;
      break;
    case 1:
      LED_S0_RESET;
      LED_S1_SET;
      LED_S2_RESET;
      break;
    case 2:
      LED_S0_RESET;
      LED_S1_RESET;
      LED_S2_SET;
      break;
    default:
      break;
    }
}


/**
 * @description: HMI_CommandDecoder on serial receive byte interrup
 * @param {type} receive byte
 * @return: none
 */
const uint8_t CommandList[CommandLen] = {0x71, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff};
uint8_t KNX_PowerState = KNX_PowerStateOFF;
static void HMI_CommandDecoder( uint8_t nByte )
{
    static uint8_t pos = 0;
    static uint8_t Buff[CommandLen] = {0};
    if ( !pos )
    {
        if ( nByte == CommandList[0] )
            Buff[pos++] = nByte;
    }
    else if ( pos < CommandLen - 3 )
    {
        Buff[pos++] = nByte;
    }
    else
    {
        if ( nByte == CommandList[pos] && pos == CommandLen - 1 )
        {
            Buff[pos] = nByte;
            if ( *( Buff + 1 ) == 0x21 && *( Buff + 2 ) == 0x43 && *( Buff + 3 ) == 0x65 && *( Buff + 4 ) == 0x87 )
            {
                if ( HMI_StateValue.batterypercent < 100 )
                {
                    HMI_ResumeCharge();
                }
            }
            else if ( *( Buff + 1 ) == 0x78 && *( Buff + 2 ) == 0x56 && *( Buff + 3 ) == 0x34 && *( Buff + 4 ) == 0x12 )
            {
                HMI_PauseCharge();
            }
            pos = 0;
            memset( Buff, 0, CommandLen );
        }
        else if ( nByte == CommandList[pos] && pos < CommandLen - 1 )
        {
            Buff[pos++] = nByte;
        }
        else
        {
            pos = 0;
            memset( Buff, 0, CommandLen );
        }
    }
}

unsigned char HMI_uartRxBuff[10];
extern UART_HandleTypeDef UartHandle;
void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart )
{
    HMI_CommandDecoder( HMI_uartRxBuff[0] );
    huart->pRxBuffPtr = ( unsigned char * )HMI_uartRxBuff;
    huart->RxXferCount = 1;
}

/**
 * @description: Run HMI tasks
 * @param {none} 
 * @return: none
 * @date 2023/8/30
 */
void HMI_TaskRun()
{
    HMI_TimeData_Update();
    Battery_ChargeInfo_Calculate();
    HMI_DispInfoStateMachine_Update();
    HMI_DispInfoChange_Update();
    HMI_StatusCycle();
}

/**
 * @description: HMI event process
 * @param {none} 
 * @return: none
 * @date 2023/8/30
 */
void HMI_EventProcess()
{
    HMI_ConnectStatus_Get();
    NFC_TAG_Status_Get();
}

/**
 * @description: Main loop of the HMI system and logic control, this function 
    should be called per ms.
 * @param {type} receive byte
 * @return: none
 */
void HMI_UpatePeriodical_Call()
{
    static WORD32 TimesMsRef;
    static BYTE InitFlag=FALSE;
    
    if (!InitFlag)
    {
        HMI_Init();
        KNX_Bus_Init();
        InitFlag=TRUE;
    }
    
    if ( API_KnxTm_GetDelayMs( TimesMsRef ) >= HMI_LOOP_PERIOD )
    {
        TimesMsRef = API_KnxTm_GetTimeMs();
        
        HMI_TaskRun();
        HMI_EventProcess();
    }
}
