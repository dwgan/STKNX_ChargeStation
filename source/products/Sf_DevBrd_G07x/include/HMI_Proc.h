#ifndef _HMI_PROC_H_
#define _HMI_PROC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "type_def.h"
  
#define HMI_CONNECTED_GPIO                      GPIOB
#define HMI_CONNECTED_PIN                       GPIO_PIN_8
#define HMI_CONNECTED_GPIO_PUPDR_PUPDR          GPIO_PUPDR_PUPDR8_0
#define HMI_CONNECTED_GPIO_MODER_MODER          GPIO_MODER_MODER8_0
  
#define NFC_TAG_GPIO                      GPIOB
#define NFC_TAG_PIN                       GPIO_PIN_13
#define NFC_TAG_GPIO_PUPDR_PUPDR          GPIO_PUPDR_PUPDR13_0
#define NFC_TAG_GPIO_MODER_MODER          GPIO_MODER_MODER13_0

#define KNX_PowerStateON  0xff
#define KNX_PowerStateOFF 0x00

#define HMI_LOOP_PERIOD  100 //HMI Loop Period, 100 ms
#define HMI_RERUN_PERIOD 1000*60*2 //HMI Restart to charge period, 2 minutes
  
#define CommandLen 8

typedef struct HMI_StateValue
{
    // external
    BYTE connectupdateflag;
    BYTE connectionstatus;
    BYTE runningupdateflag;
    BYTE runningstatus;
    BYTE batteryupdateflag;
    BYTE batterypercent;
    WORD32 fullcapacity;//per mWh
    BYTE fullcapacityupdateflag;
    WORD32 currentcapacity;//per mWh, used to calculate battery percent
    BYTE currentcapacityupdateflag;
    BYTE currentvalue[2];
    BYTE chargedtimeflag;
    WORD16 chargedtime;
//    BYTE remaintimeflag;
//    WORD16 remainchargetime;
    BYTE temperatureflag;
    WORD16 temperature;
    BYTE timedata[8];
    WORD32 chargeenergy;
    BYTE chargeenergyflag;
    WORD32 chargepower;
    BYTE chargepowerflag;
    BYTE chargerid[14];
    BYTE chargeridflag;
    
    // internal
    WORD32 TimesMsInc;
} HMI_StateValue_t;

extern HMI_StateValue_t HMI_StateValue;

void HMI_Display_Update();

extern uint8_t KNX_PowerState;
void HMI_STM32GPIO_Init();
void HMI_UpatePeriodical_Call();
void HMI_Init();

#ifdef __cplusplus
}
#endif

#endif /* _HMI_PROC_H_ */


