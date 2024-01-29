/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Configure.h
* FileIdentifier：None
* Abstract ：lnx protocol configure data header file.
* Other Description：
* Current Version：V1.00
* Author：
* Completed Date：2014年5月5日
*    
* Modified History1：
*        Modified Date：2014年5月5日
*        Version Number：V1.00
*        Modified Person：
*        Modified part：Add new public definition.
******************************************************************************/

#ifndef _KNX_CONFIGURE_H_
#define _KNX_CONFIGURE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*  */
#define APP_PEI_TYPE        PEI_TYPE_0                                /* No adapter           */
#define PEI_SW_TYPE         {0x00, 0x00, 0x00, 0x00, 0x00}            /* No PEI program       */
#define API_VERSION         {0x00, 0x00, 0x01, VALUE_FIRMWARE_VER}    /* Version of firmware  */



/* retransmission counters define */
#define REPEAT_COUNTER_BUSY        3        /* repeat counts in busy. */
#define REPEAT_COUNTER_NACK        3        /* repeat counts in NAck. */

/* routing hop count define. */
#define NL_ROUTING_COUNT           6

/* frame rate control define. */
#define AL_DEL_MESSAGE             1
#define AL_TEL_RATE_LIMIT          0        /* Telegram limitation. Frames/17s,0=off. */

//#define STACK_LIMITATION

#ifdef __cplusplus
}
#endif

#endif /* _KNX_CONFIGURE_H_ */


