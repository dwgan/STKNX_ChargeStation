#ifndef _SERIAL_PROC_H_
#define _SERIAL_PROC_H_

#include "stdint.h"

#define RTXBUFFDEEP     20
#define RTXBUFFLEN      50

uint8_t serialProc_TxData(uint8_t *pBuffer,uint8_t pSize);
uint8_t serialProc_Routine(uint8_t *charbuff);
void serialProc_ByteRecv(uint8_t nByte);
uint8_t serialData2Buff_Write( uint8_t *pData, uint16_t Size );
uint8_t serialBuffData_Send();

#endif