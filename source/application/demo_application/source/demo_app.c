/******************************************************************************
* VersionOwner C)2022,STMicroelectronics(ShenZhen)R&D Co.,Ltd.
*
* FileName：demo_app.c
* FileIdentifier：None
* Abstract ：demo application for education.
* Other Description：The code only for prestudy,No forwarding without permission
* Current Version：V1.00
* Author：
* Completed Date：2022年4月12日
*
* Modified History1：
*        Modified Date：2022年4月12日
*        Version Number：V1.00
*        Modified Person：
*        Modified part：Add new public definition.
******************************************************************************/

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "app_common.h"
#include "Hardware.h"

#include "Knx_Prop.h"
#include "Rec_Table.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "Application.h"
#include "Knx_AlApp.h"
#include "demo_app.h"
#include "App_Api.h"
#include "boardctrl.h"
#include "stm32g0xx_hal_uart.h"
#include "SerialProc.h"
#include "HMI_Proc.h"
#include "string.h"

#define DIMMERVALUEMASK      0X07
#define RSCUPDOWNMASK        0X08


extern uint8_t mPlTxData[50 + 2];
extern uint8_t mPlTxDataSize;
/* UART handler declaration */
extern UART_HandleTypeDef UartHandle;

uint8_t  UartSendingData[20];


typedef struct
{
    uint8_t nCount;
    uint8_t nStartIndex;
    uint8_t nEndIndex;
    uint8_t nData[100];
} tag_TXStoreDataStruct;

tag_TXStoreDataStruct TXDataStoreBuff;



BYTE RGBmaptable[3] = {0xff, 0x00, 0x00};


/* input channel structure define. */
T_INPUT_STATUS g_aucInputSt[MAX_INPUT_CH_NUM];


/* output channel structure define. */
const T_OUTPUT_CHANNEL g_atOutput[MAX_OUTPUT_CH_NUM];

/* variable for output status recording. */
T_OUTPUT_STATUS g_atOutStatus[MAX_OUTPUT_CH_NUM];

/**************************************************************************
* FunctionName: App_Data_Init(void)
* FunctionDescription:  Initialize the demo application data.
* InputParameter no.
* OutputParameter no.
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2022-04-14   V1.00                   modified.
**************************************************************************/
void Demo_App_Init( void )
{
    BYTE ucIndex, ucData;

    ucData = 0;

    for( ucIndex = 0; ucIndex < MAX_OUTPUT_CH_NUM; ucIndex++ )
    {
        API_KnxAl_SetCoValue( g_atOutput[ucIndex].ucOutCoNo, &ucData ); /* clear the Co. Obj's data. */
        g_atOutStatus[ucIndex].ucOldSt     = 0;
        g_atOutStatus[ucIndex].dwStartTime = 0;
        g_atOutStatus[ucIndex].ucFlashCtl  = OUTPUT_FLASH_STOP;
    }

    //TXDataStoreBuff.nCount = 0;
    //TXDataStoreBuff.nStartIndex = 0;
    // TXDataStoreBuff.nEndIndex = 0;

    return;
}

/**************************************************************************
* FunctionName: VOID Demo_App_Forced_Run(BYTE ucInputNo)
* FunctionDescription:  handle the force function happening on the input channel.
* InputParameter BYTE ucInputNo : the NO. of the input channel.
* OutputParameter no.
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Forced_Run( BYTE ucInputNo )
{
#ifdef UNLIMTVERSION
    BYTE ucCoData;
    API_KnxAl_GetCoValue( g_atInput[ucInputNo].ucForceCoNo, &ucCoData );
    if( APP_FORCE_CTRL_MASK & ucCoData )
    {
        /* in force status. */
        g_atInput[ucInputNo].pdwChnlParaRef->ucForced = TRUE;
        /* here we force the input channel's switch co-obj send the force data. */
        ucCoData &= APP_FORCE_VALUE_MASK;
        API_KnxAl_SetCoValue( g_atInput[ucInputNo].ucSwtCoNo, &ucCoData );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( g_atInput[ucInputNo].ucSwtCoNo );
    }
    else
    {
        g_atInput[ucInputNo].pdwChnlParaRef->ucForced = FALSE;
    }
#endif

}

/**************************************************************************
* FunctionName: VOID Demo_App_Scene_Run(BYTE ucInputNo)
* FunctionDescription:  handle the scene function happening on the input channel.
* InputParameter BYTE ucInputNo : the NO. of the input channel.
* OutputParameter no.
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Scene_Run( BYTE ucInputNo )
{
#ifdef UNLIMTVERSION
    BYTE ucCoData, ucOutCoData;


    API_KnxAl_GetCoValue( g_atInput[ucInputNo].ucSceneCoNo, &ucCoData );
    if( ( ucCoData & APP_SCENE_RESV_DATA_MASK ) || \
            ( ( ucCoData & APP_SCENE_DATA_MASK ) > 7 ) )
    {
        /* data is wrong.quit directly. */
        return;
    }
    if( ucCoData & APP_SCENE_SAVE_MASK )
    {
        /* we need to save the scene data. */
        API_KnxAl_GetCoValue( g_atOutput[ucInputNo].ucOutStCoNo, &ucOutCoData );
        /* we link the output one to the input one. */
        API_KnxMem_WriteByte( g_atInput[ucInputNo].pdwSceneDataRef + ( ucCoData & APP_SCENE_DATA_MASK ), ( ucOutCoData & 0x01 ) );
        API_KnxMem_WriteFinished();
    }
    else
    {
        /* handle the scene function. */
        if( TRUE == g_atInput[ucInputNo].pdwChnlParaRef->ucForced )
        {
            /* if forced,we do nothing. */
            return;
        }
        API_KnxMem_ReadByte( g_atInput[ucInputNo].pdwSceneDataRef + ( ucCoData & APP_SCENE_DATA_MASK ), &ucOutCoData );
        ucOutCoData &= 0x01;
        API_KnxAl_SetCoValue( g_atInput[ucInputNo].ucSwtCoNo, &ucOutCoData );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( g_atInput[ucInputNo].ucSwtCoNo );
    }
#endif
    return;
}

/**************************************************************************
* FunctionName: VOID Demo_App_Switch_Run(BYTE ucInputNo)
* FunctionDescription:  handle key input function.
* InputParameter BYTE ucInputNo : the NO. of the input channel.
* OutputParameter no.
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
VOID Demo_App_Switch_Run( BYTE ucInputNo )
{
    BYTE ucPinSt, ucData, ucData2;
    static unsigned char remotecontrolmessage[10];
    static unsigned char remoterkey_usecounter = 0;
    WORD16 dataconvert;
    static unsigned char pirstate = 0;
    static unsigned char prepirstate = 0;
    static WORD32 pirdelaycount = 0;
    BYTE pinstate;

    ucPinSt = Get_Input( ucInputNo );

    if( ( GetRemoteKeyStatus( &remotecontrolmessage[0] ) ) != 0 )
    {
        remoterkey_usecounter = 4;
    }

    /*the following was used to process the data which come from UART port*/
    if( remoterkey_usecounter > 0 )
    {
        ;

    }

    if( PIN_HIGH_STATE == ucPinSt )
    {
        ;
    }

    return;
}

/**************************************************************************
* FunctionName: void Demo_App_Out_Run(BYTE ucOutputNo)
* FunctionDescription:  handle output function.
* InputParameter BYTE ucOutputNo : the NO. of the output channel.
* OutputParameter no.
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2022年4月12日    1.00              Create
**************************************************************************/
void Demo_App_Out_Run( BYTE ucOutputNo )
{
    BYTE ucData, dimmervalue, updownflag;
    // WORD32 dwTimeDif;
    static BYTE outputdataToUart[5];
    u8_t i;
    WORD16 temp;

    API_KnxMem_ReadByte( g_atOutput[ucOutputNo].pdwOutTypeRef, &ucData );
    if( ucData == KNX_APP_TOGGLE )
    {
        /* get scene co-obj's flag data. */
        ucData = API_KnxAl_GetRamFlags( g_atOutput[ucOutputNo].ucOutCoNo );
        /* check whether this co-obj's data was renewed. */
        if( ucData & CO_EXTERNAL_UPDATE )
        {
            /* switch led on or off. */
            API_KnxAl_GetCoValue( g_atOutput[ucOutputNo].ucOutCoNo, &ucData );
            if( ucData & 0x01 )
            {
                /* light LED. */
                Set_Output( ucOutputNo + 1, OUTPUT_LED_ON );
            }
            else
            {
                /* light LED. */
                Set_Output( ucOutputNo + 1, OUTPUT_LED_OFF );
            }
            /* set status co-obj. */
            //     API_KnxAl_SetCoValue(g_atOutput[ucOutputNo].ucOutStCoNo,&ucData);

//            outputdataToUart[0] = ITEMTYPE_INPUTSTATUS;
            outputdataToUart[1] = ucOutputNo + 1;
            outputdataToUart[2] = ( ucData & 0x01 );


            serialProc_TxData( &outputdataToUart[0], 3 );

            if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
            {
                UartSendingData[0] = mPlTxDataSize;
                for( i = 0; i < mPlTxDataSize; i++ )
                {
                    UartSendingData[i + 1] = mPlTxData[i];
                }
                UartSendData( &UartSendingData[1], UartSendingData[0] );
                mPlTxDataSize = 0;
            }
            else
            {
                UartDataStore( &mPlTxData[0], mPlTxDataSize );
                mPlTxDataSize = 0;
            }
        }
    }
    else if( ucData == KNX_APP_DIMMINGRSV )
    {
        /* get dimming output value co-obj's flag data. */
        //   ucData = API_KnxAl_GetRamFlags(OUT_COM_OBJ_NO_RelativeDimming);
        /* check whether this co-obj's data was renewed. */
        if( ucData & CO_EXTERNAL_UPDATE )
        {
            /* Adjust the dimmer output based on the relative dimmer output value */
            //    API_KnxAl_GetCoValue(OUT_COM_OBJ_NO_RelativeDimming,&ucData);
            updownflag = ucData & RSCUPDOWNMASK;
            dimmervalue = ucData & DIMMERVALUEMASK;

            if( dimmervalue >= 1 )
            {
                ucData = 1;
                dimmervalue--;
                for( ; dimmervalue > 0; dimmervalue-- )
                {
                    ucData = ucData * 2;
                }
                dimmervalue = 100 / ucData;
            }

            ucData = g_atOutStatus[ucOutputNo].ucOldSt;
            if( dimmervalue == 0 ) // step code equal 0,then break;
            {
                ucData = 0;
            }
            else if( updownflag == 0 ) //It's decrease the dimmer value
            {
                if( ucData >= dimmervalue )
                {
                    ucData = ucData - dimmervalue;
                }
                else
                {
                    ucData = 0;
                }
            }
            else               //it's increase the dimmer value
            {
                ucData = ucData + dimmervalue;
                if( ucData > 100 )
                {
                    ucData = 100;
                }
            }
            g_atOutStatus[ucOutputNo].ucOldSt = ucData;

            /*update output on PWM output*/
            //PwmDutyCycleUpdate(ucData,ucOutputNo); need to initial related HW

//			 outputdataToUart[0] = ITEMTYPE_DIMMINGSTATUS;
            outputdataToUart[1] = 1;
            outputdataToUart[2] = ucData;

            serialProc_TxData( &outputdataToUart[0], 3 );

            if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
            {
                UartSendingData[0] = mPlTxDataSize;
                for( i = 0; i < mPlTxDataSize; i++ )
                {
                    UartSendingData[i + 1] = mPlTxData[i];
                }
                UartSendData( &UartSendingData[1], UartSendingData[0] );
                mPlTxDataSize = 0;
            }
            else
            {
                UartDataStore( &mPlTxData[0], mPlTxDataSize );
                mPlTxDataSize = 0;
            }

        }

    }
    else if( ucData == KNX_APP_DIMMINGASV )
    {
        /* get dimming output value co-obj's flag data. */
        ucData = API_KnxAl_GetRamFlags( OUT_COM_OBJ_NO_AbsoluteDimming );
        /* check whether this co-obj's data was renewed. */
        if( ucData & CO_EXTERNAL_UPDATE )
        {
            /* dimming output value. */
            API_KnxAl_GetCoValue( OUT_COM_OBJ_NO_AbsoluteDimming, &ucData );
            temp = ucData;
            temp = ( ( temp * 100 ) + 125 ) / 255;
            if( temp >= 35 )
            {
                temp = ( temp - 35 ) * 100 / 65;
            }
            else
            {
                temp = 0;
            }

            //		  outputdataToUart[0] = ITEMTYPE_DIMMINGSTATUS;
            outputdataToUart[1] = 1;
            outputdataToUart[2] = temp;

            serialProc_TxData( &outputdataToUart[0], 3 );

            if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
            {
                UartSendingData[0] = mPlTxDataSize;
                for( i = 0; i < mPlTxDataSize; i++ )
                {
                    UartSendingData[i + 1] = mPlTxData[i];
                }
                UartSendData( &UartSendingData[1], UartSendingData[0] );
                mPlTxDataSize = 0;
            }
            else
            {
                UartDataStore( &mPlTxData[0], mPlTxDataSize );
                mPlTxDataSize = 0;
            }
        }
    }
}

/**************************************************************************
* FunctionName: App_Data_Init(void)
* FunctionDescription:  Initialize the demo application data.
* InputParameter no.
* OutputParameter no.
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2022年4月12日    1.00              Create
**************************************************************************/
void Demo_App_Run( void )
{
    BYTE ucIndex;

    // ucPara = 0;

    //for( ucIndex = 0; ucIndex < MAX_INPUT_CH_NUM; ucIndex++ )
    //{
    //
    //    Demo_App_Switch_Run( ucIndex );
    //}
    for( ucIndex = 0; ucIndex < MAX_OUTPUT_CH_NUM; ucIndex++ )
    {
        Demo_App_Out_Run( ucIndex );
    }

    Demo_App_ChargeStationValue_Update();

//	Demo_App_SensorValue_Update();

    SendUartStoreData();
    
    HMI_UpatePeriodical_Call();
    

    serialBuffData_Send();
    
    SET_LED2_ON;
}

WORD32 g_dwTXTimeSt = 0;

void SendUartStoreData( void )
{
    u8_t i;
    WORD32 dwTXDif;

    if( TXDataStoreBuff.nCount >= 1 )
    {
        dwTXDif = API_KnxTm_GetDelayMs( g_dwTXTimeSt );
        if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
        {
            if( dwTXDif >= 100 )
            {
                for( i = 0; i <= TXDataStoreBuff.nData[0]; i++ )
                {
                    UartSendingData[i] = TXDataStoreBuff.nData[i];
                }
                TXDataStoreBuff.nCount = TXDataStoreBuff.nCount - 1;
                if( TXDataStoreBuff.nCount >= 1 )
                {
                    for( i = 0; i < ( TXDataStoreBuff.nEndIndex - UartSendingData[0] ); i++ )
                    {
                        TXDataStoreBuff.nData[i] = TXDataStoreBuff.nData[i + 1 + UartSendingData[0]];
                    }
                    TXDataStoreBuff.nEndIndex = TXDataStoreBuff.nEndIndex - UartSendingData[0] - 1;
                }
                else
                {
                    TXDataStoreBuff.nEndIndex = 0;

                }
                for( i = TXDataStoreBuff.nEndIndex ; i < 100; i++ )
                {
                    TXDataStoreBuff.nData[i] = 0;
                }

                UartSendData( &UartSendingData[1], UartSendingData[0] );
            }
        }
        else
        {
            g_dwTXTimeSt = API_KnxTm_GetTimeMs();
        }

    }




}

BYTE dataToUart[10], dataTobus[14];
void Demo_App_ChargeStationValue_Update( void )
{
    BYTE ucData;
	BYTE timedata[8];
	SWORD32 energyvalue;
    WORD16 dataconvert;
    u8_t i;

    /* The following part was used to get command from KNX BUS*/


    /* get CHARGE_RUNNING_STATUS_CO flag data. */
    ucData = API_KnxAl_GetRamFlags( CHARGE_ID_CO );
    /* check whether this co-obj's data was renewed. */
    if( ucData & CO_EXTERNAL_UPDATE )
    {
        /*Get CHARGE_RUNNING_STATUS_CO value */
        API_KnxAl_GetCoValue( CHARGE_ID_CO, &HMI_StateValue.chargerid[0] );


        /*send position data to UART PORT  */
        dataToUart[0] = ITEMTYPE_CHARGERID;
        dataToUart[1] = 1;
        for( i = 0; i < 14; i++ )
        {
            dataToUart[i + 2] = HMI_StateValue.chargerid[i];
        }

        serialProc_TxData( &dataToUart[0], 16 );

        if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
        {
            UartSendingData[0] = mPlTxDataSize;
            for( i = 0; i < mPlTxDataSize; i++ )
            {
                UartSendingData[i + 1] = mPlTxData[i];
            }
            UartSendData( &UartSendingData[1], UartSendingData[0] );
            mPlTxDataSize = 0;
        }
        else
        {
            UartDataStore( &mPlTxData[0], mPlTxDataSize );
            mPlTxDataSize = 0;
        }
    }



    /* get CHARGE_RUNNING_STATUS_CO flag data. */
    ucData = API_KnxAl_GetRamFlags( CHARGE_RUNNING_STATUS_CO );
    /* check whether this co-obj's data was renewed. */
    if( ucData & CO_EXTERNAL_UPDATE )
    {
        /*Get CHARGE_RUNNING_STATUS_CO value */
        //BYTE runningstatus;
        API_KnxAl_GetCoValue( CHARGE_RUNNING_STATUS_CO, &HMI_StateValue.runningstatus );
        //HMI_StateValue.runningstatus=HMI_StateValue.batterypercent<100?runningstatus:0;
        
        if (HMI_StateValue.runningstatus)
        {
            if ( HMI_StateValue.batterypercent >= 100 )
            {
                Battery_Info_Get();
            }
            HMI_ResumeCharge();
        }
        
        /*send position data to UART PORT  */
        dataToUart[0] = ITEMTYPE_RUNNINGSTATUS;
        dataToUart[1] = 1;
        dataToUart[2] = HMI_StateValue.runningstatus;

        serialProc_TxData( &dataToUart[0], 3 );

        if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
        {
            UartSendingData[0] = mPlTxDataSize;
            for( i = 0; i < mPlTxDataSize; i++ )
            {
                UartSendingData[i + 1] = mPlTxData[i];
            }
            UartSendData( &UartSendingData[1], UartSendingData[0] );
            mPlTxDataSize = 0;
        }
        else
        {
            UartDataStore( &mPlTxData[0], mPlTxDataSize );
            mPlTxDataSize = 0;
        }
    }


    /* get CHARGE_CURRENT_VALUE_CO flag data. */
    ucData = API_KnxAl_GetRamFlags( CHARGE_CURRENT_VALUE_CO );
    /* check whether this co-obj's data was renewed. */
    if( ucData & CO_EXTERNAL_UPDATE )
    {
        /*Get CHARGE_CURRENT_VALUE_CO value */
        API_KnxAl_GetCoValue( CHARGE_CURRENT_VALUE_CO, &HMI_StateValue.currentvalue[0] );


        /*send position data to UART PORT  */
        dataToUart[0] = ITEMTYPE_CHARGECURRENT;
        dataToUart[1] = 1;
        dataToUart[2] = HMI_StateValue.currentvalue[0];  //
        dataToUart[3] = HMI_StateValue.currentvalue[1];  //need update??

        serialProc_TxData( &dataToUart[0], 4 );

        if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
        {
            UartSendingData[0] = mPlTxDataSize;
            for( i = 0; i < mPlTxDataSize; i++ )
            {
                UartSendingData[i + 1] = mPlTxData[i];
            }
            UartSendData( &UartSendingData[1], UartSendingData[0] );
            mPlTxDataSize = 0;
        }
        else
        {
            UartDataStore( &mPlTxData[0], mPlTxDataSize );
            mPlTxDataSize = 0;
        }
    }

    /* get datetime value from KNX bus. */
    ucData = API_KnxAl_GetRamFlags( DATETIME_CO );
    /* check whether this co-obj's data was renewed. */
    if( ucData & CO_EXTERNAL_UPDATE )
    {
        /*Get CHARGE_CURRENT_VALUE_CO value */
        //API_KnxAl_GetCoValue( DATETIME_CO, &timedata[0] );
        API_KnxAl_GetCoValue( DATETIME_CO, &HMI_StateValue.timedata[0] );
        HMI_StateValue.TimesMsInc=0;


        ///*send position data to UART PORT  */
        //dataToUart[0] = ITEMTYPE_DATETIME;
        //dataToUart[1] = 1;
        //dataToUart[2] = timedata[0];  //
        //dataToUart[3] = timedata[1];  //
        //dataToUart[4] = timedata[2];  //
        //dataToUart[5] = timedata[3];  //
        //dataToUart[6] = timedata[4];  //
        //dataToUart[7] = timedata[5];  //
        //dataToUart[8] = timedata[6];  //
        //dataToUart[9] = timedata[7];  //
        //
        //serialProc_TxData( &dataToUart[0], 10 );
        //
        //if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
        //{
        //    UartSendingData[0] = mPlTxDataSize;
        //    for( i = 0; i < mPlTxDataSize; i++ )
        //    {
        //        UartSendingData[i + 1] = mPlTxData[i];
        //    }
        //    UartSendData( &UartSendingData[1], UartSendingData[0] );
        //    mPlTxDataSize = 0;
        //}
        //else
        //{
        //    UartDataStore( &mPlTxData[0], mPlTxDataSize );
        //    mPlTxDataSize = 0;
        //}
    }
    
    /*the following was used send OUT charge stations status to KNX BUS*/

    /* update the charge connection status to system**/
    if( HMI_StateValue.connectupdateflag == 1 )
    {
        dataTobus[0] = HMI_StateValue.connectionstatus ;

        API_KnxAl_SetCoValue( CHARGE_CONNECT_STATUS_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGE_CONNECT_STATUS_CO );

        HMI_StateValue.connectupdateflag = 0;

    }
    /* update the charge connection status to system**/
    else if( HMI_StateValue.runningupdateflag == 1 )
    {
        dataTobus[0] = HMI_StateValue.runningstatus ;

        API_KnxAl_SetCoValue( CHARGE_RUNNING_STATUS_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGE_RUNNING_STATUS_CO );

        HMI_StateValue.runningupdateflag = 0;

    }
    /*update the battery status*/
    else if( HMI_StateValue.batteryupdateflag == 1 )
    {
        dataconvert = HMI_StateValue.batterypercent;
        dataconvert = ( ( dataconvert * 255 ) + 50 ) / 100; //convert the data range from 0--100 to 0--255
        dataTobus[0] = ( BYTE )dataconvert;

        API_KnxAl_SetCoValue( CHARGE_BATTERY_PERCENT_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGE_BATTERY_PERCENT_CO );

        HMI_StateValue.batteryupdateflag = 0;
    }
    /*update the charged time status*/
    else if( HMI_StateValue.chargedtimeflag == 1 )
    {
        dataTobus[1] = HMI_StateValue.chargedtime & 0xff;
        dataTobus[0] = ( HMI_StateValue.chargedtime >> 8 ) & 0xff;

        API_KnxAl_SetCoValue( CHARGED_TIME_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGED_TIME_CO );

        HMI_StateValue.chargedtimeflag = 0;
    }
    /*update the remaining charge time status*/
    else if( HMI_StateValue.remaintimeflag == 1 )
    {
        dataTobus[1] = HMI_StateValue.remainchargetime & 0xff;
        dataTobus[0] = ( HMI_StateValue.remainchargetime >> 8 ) & 0xff;
        API_KnxAl_SetCoValue( REMAINING_CHARGE_TIME_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( REMAINING_CHARGE_TIME_CO );

        HMI_StateValue.remaintimeflag = 0;
    }
    /*update the temperature status*/
    else if( HMI_StateValue.temperatureflag == 1 )
    {
        dataTobus[0] = ( BYTE )( ( ( HMI_StateValue.temperature * 10 ) >> 8 ) & 0xff );
        dataTobus[1] = ( BYTE )( ( HMI_StateValue.temperature * 10 ) & 0xff );
        DataConvert_IntToFloat( &dataTobus[0] );

        API_KnxAl_SetCoValue( CHARGE_TEMPERATURE_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGE_TEMPERATURE_CO );

        HMI_StateValue.temperatureflag = 0;
    }
    /*update the charge energy status*/
    else if( HMI_StateValue.chargeenergyflag == 1 )
    {
        dataTobus[3] = ( BYTE )( ( HMI_StateValue.chargeenergy/1000 ) & 0xff );
        dataTobus[2] = ( BYTE )( ( HMI_StateValue.chargeenergy/1000>>8 ) & 0xff );
        dataTobus[1] = ( BYTE )( ( HMI_StateValue.chargeenergy/1000>>16 ) & 0xff );
        dataTobus[0] = ( BYTE )( ( HMI_StateValue.chargeenergy/1000>>24 ) & 0xff );
        DataConvert_IntToFloat( &dataTobus[0] );

        API_KnxAl_SetCoValue( CHARGE_ENERGY_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGE_ENERGY_CO );

        HMI_StateValue.chargeenergyflag = 0;
    }
    /*update the charge power*/
    else if( HMI_StateValue.chargepowerflag== 1 )
    {
        *(float*)&dataTobus[0]=(float)HMI_StateValue.chargepower/1000;
        swapEndian(dataTobus,4);
        
        API_KnxAl_SetCoValue( CHARGE_POWER_VALUE_CO, &dataTobus[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGE_POWER_VALUE_CO );

        HMI_StateValue.chargepowerflag = 0;
    }
    /*update the charging device ID*/
    else if( HMI_StateValue.chargeridflag == 1 )
    {
        API_KnxMem_ReadByte( DEVICE_ID_REF, &ucData );

        API_KnxAl_SetCoValue( CHARGE_ID_CO, &HMI_StateValue.chargerid[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( CHARGE_ID_CO );

        HMI_StateValue.chargeridflag = 0;
    }
}

WORD32 g_dwTimeStSensor = 0;

void Demo_App_SensorValue_Update( void )
{
    BYTE ucData;
    BYTE sensorvalue[2];
    static BYTE dataToUart[5];
    static BYTE powerupflag = 0;
    WORD32 dwDifsensor;
    u8_t i;

    /* get temperature co-obj's flag data. */
    ucData = API_KnxAl_GetRamFlags( TEMPERATURE_ABSOLUTE_OBJ_NO );
    /* check whether this co-obj's data was renewed. */
    if( ( ucData & CO_EXTERNAL_UPDATE ) || ( powerupflag == 1 ) )
    {
        /*Get temperature sensor value */
        API_KnxAl_GetCoValue( TEMPERATURE_ABSOLUTE_OBJ_NO, &sensorvalue[0] );

        // API_KnxAl_SetCoValue(TEMPERATURE_ABSOLUTE_OBJ_NO,&sensorvalue[0]);
        /* send the switch co-obj's data. */
        // API_KnxAl_RequestValueWrite(TEMPERATURE_ABSOLUTE_OBJ_NO);

        /*send databack to BLE device, only for testing now   */
        DataConvert_FloatToInt( &sensorvalue[0] );
        dataToUart[0] = ITEMTYPE_TEMPERATURE;
        dataToUart[1] = 1;
        dataToUart[2] = sensorvalue[0];
        dataToUart[3] = sensorvalue[1];

        serialProc_TxData( &dataToUart[0], 4 );

        if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
        {
            UartSendingData[0] = mPlTxDataSize;
            for( i = 0; i < mPlTxDataSize; i++ )
            {
                UartSendingData[i + 1] = mPlTxData[i];
            }
            UartSendData( &UartSendingData[1], UartSendingData[0] );
            mPlTxDataSize = 0;
        }
        else
        {
            UartDataStore( &mPlTxData[0], mPlTxDataSize );
            mPlTxDataSize = 0;
        }

    }

    /* get humidity co-obj's flag data. */
    ucData = API_KnxAl_GetRamFlags( HUMIDITY_OBJ_NO );
    /* check whether this co-obj's data was renewed. */
    if( ( ucData & CO_EXTERNAL_UPDATE ) || ( powerupflag == 1 ) )
    {
        /*Get temperature sensor value */
        API_KnxAl_GetCoValue( HUMIDITY_OBJ_NO, &sensorvalue[0] );

        //	API_KnxAl_SetCoValue(HUMIDITY_OBJ_NO,&sensorvalue[0]);
        /* send the switch co-obj's data. */
        //   API_KnxAl_RequestValueWrite(HUMIDITY_OBJ_NO);

        /*send databack to BLE device, only for testing now   */
        DataConvert_FloatToInt( &sensorvalue[0] );
        //	dataToUart[0] = ITEMTYPE_HUMIDITY;
        dataToUart[1] = 1;
        dataToUart[2] = sensorvalue[0];
        dataToUart[3] = sensorvalue[1];

        serialProc_TxData( &dataToUart[0], 4 );

        if( UartHandle.gState != HAL_UART_STATE_BUSY_TX )
        {
            UartSendingData[0] = mPlTxDataSize;
            for( i = 0; i < mPlTxDataSize; i++ )
            {
                UartSendingData[i + 1] = mPlTxData[i];
            }
            UartSendData( &UartSendingData[1], UartSendingData[0] );
            mPlTxDataSize = 0;
        }
        else
        {
            UartDataStore( &mPlTxData[0], mPlTxDataSize );
            mPlTxDataSize = 0;
        }

        powerupflag = 0xff;

    }

#if 0
    if( powerupflag == 0 )
    {
        sensorvalue[0] = 0x0d;  //26.0c
        sensorvalue[1] = 0x14;

        API_KnxAl_SetCoValue( TEMPERATURE_ABSOLUTE_OBJ_NO, &sensorvalue[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( TEMPERATURE_ABSOLUTE_OBJ_NO );

        sensorvalue[0] = 0x15;
        sensorvalue[1] = 0xdc;

        API_KnxAl_SetCoValue( HUMIDITY_OBJ_NO, &sensorvalue[0] );
        /* send the switch co-obj's data. */
        API_KnxAl_RequestValueWrite( HUMIDITY_OBJ_NO );

        powerupflag = 1;
    }

    dwDifsensor = API_KnxTm_GetDelayMs( g_dwTimeStSensor );
    if( dwDifsensor >= 30000 )
    {
        g_dwTimeStSensor = API_KnxTm_GetTimeMs();
        powerupflag = 0;
    }
#endif

}

/******************************************************************
The following function was used to convert 2 bytes float data to short
 currently only processed postive date

*******************************************************************/
void DataConvert_FloatToInt( BYTE *pData )
{
    WORD16 converrvalue;
    BYTE indexnumer;

    indexnumer = ( ( pData[0] & 0x78 ) >> 3 );
    converrvalue = ( ( pData[0] & 0x07 ) << 8 ) + pData[1] ;

    for( ; indexnumer >= 1; indexnumer-- )
    {
        converrvalue = converrvalue * 2;
    }
    pData[1] = ( BYTE )( converrvalue & 0xff );
    pData[0] = ( BYTE )( ( converrvalue >> 8 ) & 0xff );
}


/******************************************************************
The following function was used to convert short to 2 bytes float data
 currently only processed postive date

*******************************************************************/
void DataConvert_IntToFloat( BYTE *pData )
{
    WORD16 converrvalue;
    BYTE indexnumer;

    converrvalue = ( pData[0] << 8 ) + pData[1] ;
    indexnumer = 0;


    for( ; converrvalue > 0x7ff; )
    {
        converrvalue = converrvalue / 2;
        indexnumer++;
    }
    pData[1] = ( BYTE )( converrvalue & 0xff );
    pData[0] = ( BYTE )( ( ( converrvalue >> 8 ) & 0xff ) | ( indexnumer << 3 ) );
}


/******************************************************************
The following function was used to temperialy store UART data txbuff

as the UART was sending date

*******************************************************************/

void UartDataStore( uint8_t *pData, uint16_t Size )
{
    uint16_t i;
    if( ( TXDataStoreBuff.nEndIndex + Size + 1 ) < 100 )
    {
        TXDataStoreBuff.nCount = TXDataStoreBuff.nCount + 1;
        TXDataStoreBuff.nData[TXDataStoreBuff.nEndIndex++] = Size;
        for( i = 0; i < Size ; i++ )
        {
            TXDataStoreBuff.nData[TXDataStoreBuff.nEndIndex++] = *( pData + i );
        }
    }
}

/**
 * @description: swap big-endian or little-endian to another type
 * @param {none} 
 * @return: none
 * @date 2023/9/2
 * example: swapEndian(&value16, sizeof(value16));
 */
void swapEndian(void* data, size_t size)
{
    uint8_t* byteData = (uint8_t*)data;
    uint8_t temp;
    
    for (size_t i = 0; i < size / 2; ++i)
    {
        temp = byteData[i];
        byteData[i] = byteData[size - 1 - i];
        byteData[size - 1 - i] = temp;
    }
}
/* end of file. */

