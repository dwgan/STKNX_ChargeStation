/*
 * @Author:
 * @Date: 2021-06-10 22:52:57
 * @Description: add rx and tx function
 * @FilePath:
 */

#include "type_def.h"
#include "SerialProc.h"
#include "stdint.h"
#include "string.h"
#include "boardctrl.h"

#include "stm32g0xx_hal_uart.h"

#define FS_CHAR         0x7E
#define TSC_CHAR        0x7D
#define TE_CHAR         0x7F


/*
import declear in serial phys c
*/
uint8_t mPlTxData[RTXBUFFLEN + 2];
uint8_t mPlTxDataSize;

typedef struct
{
    uint8_t nSize;
    uint8_t nData[RTXBUFFLEN];
} tag_RTXStruct;


typedef struct
{
    int PosIn;
    int PosOut;
    tag_RTXStruct Buff[RTXBUFFDEEP];
} tag_RTXStructBuff;

static tag_RTXStruct mRxBuffer[2];
static tag_RTXStruct *mRxPointer;

static tag_RTXStructBuff TxBuffMtx = {0, 0, {0}};

extern UART_HandleTypeDef UartHandle;
//static uint8_t mTxBusy;

//static uint16_t mRxStamp;
//static uint8_t mRxSize;
static uint8_t mRxBusy;
/**
 * @description: update receive pointer
 * @param {type}
 * @return:
  true:have free rx buffer
  false:no free rx buffer
 */
uint8_t serialProc_UpdateRxPointer( void )
{
    if( mRxBuffer[0].nSize == 0 )
    {
        mRxPointer = &mRxBuffer[0];
    }
    else if( mRxBuffer[1].nSize == 0 )
    {
        mRxPointer = &mRxBuffer[1];
    }
    else
        return FALSE;
    return TRUE;
}




/**
 * @description: on serial receive byte interrup
 * @param {type} receive byte
 * @return: none
 */
void serialProc_ByteRecv( uint8_t nByte )
{
    static uint16_t nRxSize;
    static uint8_t nTcByte;
    switch( nByte )
    {
    case   FS_CHAR:
        if( serialProc_UpdateRxPointer() )
        {
            mRxBusy = TRUE;
            nRxSize = 0;
        }
        break;
    case   TSC_CHAR:
        nTcByte = 0x20;
        break;
    case   TE_CHAR:
        if( !mRxBusy ) return;
        mRxPointer->nSize = nRxSize;
        mRxBusy = FALSE;
        break;
    default:
        if( !mRxBusy ) return;
        mRxPointer->nData[nRxSize] = nByte + nTcByte;
        nRxSize++;
        nTcByte = 0;
        break;
    }
}

/**
 * @description: app to call to send serial data
 * @param {type}
  pBuffer:pointer to send;
  pSize:size to send
 * @return:
  true:tx buffer is free,accept to send
  false:tx buffer is busy
 */
uint8_t serialProc_TxData( uint8_t *pBuffer, uint8_t pSize )
{
    if( mPlTxDataSize )    return FALSE;

    mPlTxDataSize = 0;
    mPlTxData[mPlTxDataSize++] = FS_CHAR;
    for( uint8_t i = 0; i < pSize; i++ )
    {
        if( pBuffer[i] >= TSC_CHAR && pBuffer[i] <= TE_CHAR )
        {
            mPlTxData[mPlTxDataSize++] = TSC_CHAR;
            mPlTxData[mPlTxDataSize++] = pBuffer[i] - 0x20;
        }
        else
            mPlTxData[mPlTxDataSize++] = pBuffer[i];
    }
    mPlTxData[mPlTxDataSize++] = TE_CHAR;

    /*serial request to tx,maybe interrupt or DMA send*/
//    serial_RequestTx();

    return FALSE;
}


/*
put into routine
*/
/**
 * @description: process rx buffer in routine
 * @param {type} stamp of this mcu
 * @return: none
 */
uint8_t serialProc_Routine( uint8_t *charbuff )
{
    uint8_t datasize;
    if( mRxBuffer[0].nSize )
    {
        memcpy( charbuff, mRxBuffer[0].nData, mRxBuffer[0].nSize );
        datasize =  mRxBuffer[0].nSize;
        // if(userapp_serial_process(mRxBuffer[0].nData,mRxBuffer[0].nSize))
        mRxBuffer[0].nSize = 0;
    }
    else if( ( mRxBuffer[1].nSize ) )
    {
        memcpy( charbuff, mRxBuffer[1].nData, mRxBuffer[1].nSize );
        datasize =  mRxBuffer[1].nSize;
//    if(userapp_serial_process(mRxBuffer[1].nData,mRxBuffer[1].nSize))
        mRxBuffer[1].nSize = 0;
    }
    else
    {
        datasize = 0;
    }
    return datasize;
}

/**
 * @description: app to call to send serial data in buffer mode
 * @param {type}
  pBuffer:pointer to send;
  pSize:size to send
 * @return:
  true:tx buffer is free,accept to send
  false:tx buffer is busy
 */
uint8_t serialBuffData_Send()
{
    // check wether the buff matrix is empty
    if( TxBuffMtx.PosIn == TxBuffMtx.PosOut || UartHandle.gState == HAL_UART_STATE_BUSY_TX )
    {
        return FALSE;
    }

    static uint8_t Buff[RTXBUFFLEN] = {0};
    memcpy( Buff, TxBuffMtx.Buff[TxBuffMtx.PosOut].nData, TxBuffMtx.Buff[TxBuffMtx.PosOut].nSize );
    UartSendData( Buff, TxBuffMtx.Buff[TxBuffMtx.PosOut].nSize );
    memset( TxBuffMtx.Buff[TxBuffMtx.PosOut].nData, 0, RTXBUFFLEN );
    TxBuffMtx.PosOut = TxBuffMtx.PosOut + 1 < RTXBUFFDEEP ? TxBuffMtx.PosOut + 1 : 0;

    return TRUE;
}

/**
 * @description: app to call to send serial data in buffer mode
 * @param {type}
  pBuffer:pointer to send;
  pSize:size to send
 * @return:
  true:tx buffer is free,accept to send
  false:tx buffer is busy
 */
uint8_t serialData2Buff_Write( uint8_t *pData, uint16_t Size )
{
    // check wether the buff matrix is fulled
    if ( ( TxBuffMtx.PosOut == TxBuffMtx.PosIn + 1 ) || ( TxBuffMtx.PosOut == 0 && TxBuffMtx.PosIn == RTXBUFFDEEP - 1 ) )    return FALSE;

    memcpy( TxBuffMtx.Buff[TxBuffMtx.PosIn].nData, pData, Size );
    TxBuffMtx.Buff[TxBuffMtx.PosIn].nSize = Size;
    TxBuffMtx.PosIn = TxBuffMtx.PosIn + 1 < RTXBUFFDEEP ? TxBuffMtx.PosIn + 1 : 0;

    return TRUE;
}
