/******************************************************************************
* VersionOwner (C)2013，南京******************** 有限公司。
*
* FileName：demo_app.h
* FileIdentifier：None
* Abstract ：demo app header file.
* Other Description：
* Current Version：V1.00
* Author：    
* Completed Date：2014年7月8日
*    
* Modified History1：
*        Modified Date：2014年7月8日
*        Version Number：V1.00
*        Modified Person：    
*        Modified part：Add new public definition.
******************************************************************************/

#ifndef _DEMO_APP_H_
#define _DEMO_APP_H_

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stddef.h>

#define OUTPUT_FLASH_TIME          500 /* 500 ms. */
#define INPUT_CHECK_TIME           50  /* 50ms    */
#define OUTPUT_FLASH_START         1
#define OUTPUT_FLASH_STOP          0

#define NONE_TYPE_CONTROL         0XFF
#define DIMASV_TYPE_CONTROL       0X10
#define ONOFF_TYPE_CONTROL        0X11
#define COLOR_TYPE_CONTROL        0x12
#define DIMRSV_TYPE_CONTROL       0X13


#define UARTDATA_HEADER1         0XAA
#define UARTDATA_HEADER2         0x55

#define DATATYPE_TEMPERATURE     0X10
#define DATATYPE_HUMIDITY        0X11


#define ITEMTYPE_CONNECTSTATUS   0x01
#define ITEMTYPE_RUNNINGSTATUS   0x02
#define ITEMTYPE_BATTERYSTATUS   0x03
#define ITEMTYPE_CHARGECURRENT   0x04
#define ITEMTYPE_CHARGEPOWER     0x05
#define ITEMTYPE_CHARGEDTIME     0x06
#define ITEMTYPE_REMAININGTIME   0x07
#define ITEMTYPE_TEMPERATURE     0x08

#define ITEMTYPE_CHARGEDENERGY   0x09
#define ITEMTYPE_DATETIME        0X0A
#define ITEMTYPE_CHARGERID       0X0B





typedef struct
{
    BOOL   ucForced;               /* channel is in forced status. */
    BYTE   ucOldCoData;            /* previous data of co-obj.       */
    WORD32 dwStartTime;            /* input start time.            */
}T_INPUT_STATUS;

typedef struct
{
    BYTE    ucSwtCoNo;                   /* switch function com. NO. */
    T_INPUT_STATUS *pdwChnlParaRef;      /* channel ram data variable's address. */
    WORDPTR pdwSwtTypeRef;               /* switch type set address.   */
}T_INPUT_CHANNEL;

typedef struct
{
    BYTE    ucOutCoNo;           /* output function com. NO. */
    WORDPTR pdwOutTypeRef;       /* output type set address com. NO. */
}T_OUTPUT_CHANNEL;

typedef struct
{
    BYTE   ucOldSt;               /* the old status of output. */
    BYTE   ucFlashCtl;            /* control flash stop or  start. */
    WORD32 dwStartTime;           /* the action start time(ms). */
}T_OUTPUT_STATUS;



/**************************************************************************
* FunctionName: App_Data_Init(void)
* FunctionDescription:  Initialize the demo application data.
* InputParameter no.
* OutputParameter no.      
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Init(void);

/**************************************************************************
* FunctionName: App_Data_Init(void)
* FunctionDescription:  Initialize the demo application data.
* InputParameter no.
* OutputParameter no.      
* Return Value： no.
* Other Description: no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2016-07-08   V1.00                   creat.
**************************************************************************/
void Demo_App_Run(void);

void Demo_App_SensorValue_Update(void);
void Demo_App_ChargeStationValue_Update(void);

void SendUartStoreData(void);

void DataConvert_IntToFloat(BYTE *pData);
void DataConvert_FloatToInt(BYTE *pData);
void UartDataStore(uint8_t *pData, uint16_t Size);
void swapEndian(void* data, size_t size);


#ifdef __cplusplus
}
#endif

#endif /* _DEMO_APP_H_ */






/* end of file. */
