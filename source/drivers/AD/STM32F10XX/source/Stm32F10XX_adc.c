/********************************************************************
* Right reserved (C 2016) for *********** company.
*
* File Name        : Stm32F10XX_adc.c
*
* File Description : deriver file for stm32f10xx adc.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2016.7.28
*
* Modification Rec.:
*   Modify Data    : 2016.7.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
********************************************************************/



#include "type_def.h"
#include "Sw_common.h"
#include "Pub.h"
#include "boardcfg.h"
#include "Hardware.h"


#include "Boardctrl.h"
#include "math_service.h"
#include "system_stm32f10x.h"
#include "Stm32F10XX_adc.h"


/* Operation of ADC */
static T_DEV_OPERATION   sg_tAdcOp;

/**************************************************************************
* Function: WORD32 ADCx_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Init operation of adc
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara:
*               ucPara[1]      BYTE          1,2    ADC device No.
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
WORD32 ADCx_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    WORD32 dwAdcCr1, dwAdcCr2;
    BYTE   ucDevNo = ptPara->ucPara[ADC_DEV_NO_POS];
    
    /* Check if adc No. is valid or NOT */
    if((ucDevNo - 1) > (MAX_ADC_DEVICE_NUM - 1))
    {
        return SW_ERR;
    }

    ucDevNo = ptPara->ucPara[ADC_DEV_NO_POS];     /* Get device No.   */
    if(ucDevNo == ADC_1)
    {
        RCC_APB2ENR  |=   RCC_APB2ENR_ADC1EN;         /* Enable ADC clock */
        RCC_APB2RSTR |=   RCC_APB2RSTR_ADC1RST;       /* Reset ADC        */
        RCC_APB2RSTR &= ~(RCC_APB2RSTR_ADC1RST);      /* Stop reset ADC   */
    }
    else
    {
        RCC_APB2ENR  |=   RCC_APB2ENR_ADC2EN;         /* Enable ADC clock */
        RCC_APB2RSTR |=   RCC_APB2RSTR_ADC2RST;       /* Reset ADC        */
        RCC_APB2RSTR &= ~(RCC_APB2RSTR_ADC2RST);      /* Stop reset ADC   */
    }

    RCC_CFGR &= ~(RCC_CFGR_ADCPRE_MASK);
    if(SystemFrequency_APB2Clk <= SYSCLK_FREQ_24M)
    {
        RCC_CFGR |= RCC_CFGR_ADCPRE_DIV2;       /* PCLK2/2 as clock */
    }
    else if(SystemFrequency_APB2Clk < SYSCLK_FREQ_56M)
    {
        RCC_CFGR |= RCC_CFGR_ADCPRE_DIV4;       /* PCLK2/4 as clock */
    }
    else
    {
        RCC_CFGR |= RCC_CFGR_ADCPRE_DIV6;       /* PCLK2/6 as clock */
    }
    
    dwAdcCr1  =   ADCX_CR1(ucDevNo);
    dwAdcCr1 &= ~(ADC_CR1_DUALMOD);               /* Independent mode  */
    dwAdcCr1 &= ~(ADC_CR1_SCAN);                  /* Scan mode disable */
    ADCX_CR1(ucDevNo) = dwAdcCr1;

    dwAdcCr2  =   ADCX_CR2(ucDevNo);
    dwAdcCr2 &= ~(ADC_CR2_CONT);                  /* Single conversion mode */
    dwAdcCr2 &= ~(ADC_CR2_EXTSEL);
    dwAdcCr2 |=   ADC_CR2_EXTSEL_SWSTART;         /* Software start convert */
    dwAdcCr2 |=   ADC_CR2_EXTTRIG;                /* External trigger       */
    dwAdcCr2 &= ~(ADC_CR2_ALIGN);                 /* Right alignment        */
    ADCX_CR2(ucDevNo) = dwAdcCr2;

    ADCX_SQR1(ucDevNo) &= ~(ADC_SQR1_L_MASK);         /* Only 1 sequence        */

    ADCX_SMPR1(ucDevNo) = ( ADC_SMPR1_SMP10_SEL(7)\
                          | ADC_SMPR1_SMP11_SEL(7)\
                          | ADC_SMPR1_SMP12_SEL(7)\
                          | ADC_SMPR1_SMP13_SEL(7)\
                          | ADC_SMPR1_SMP14_SEL(7)\
                          | ADC_SMPR1_SMP15_SEL(7)\
                          | ADC_SMPR1_SMP16_SEL(7)\
                          | ADC_SMPR1_SMP17_SEL(7));  /* 239.5 period sample time */

    ADCX_SMPR2(ucDevNo) = ( ADC_SMPR2_SMP0_SEL(7)\
                          | ADC_SMPR2_SMP1_SEL(7)\
                          | ADC_SMPR2_SMP2_SEL(7)\
                          | ADC_SMPR2_SMP3_SEL(7)\
                          | ADC_SMPR2_SMP4_SEL(7)\
                          | ADC_SMPR2_SMP5_SEL(7)\
                          | ADC_SMPR2_SMP6_SEL(7)\
                          | ADC_SMPR2_SMP7_SEL(7)\
                          | ADC_SMPR2_SMP8_SEL(7)\
                          | ADC_SMPR2_SMP9_SEL(7));  /* 239.5 period sample time */

    ADCX_CR2(ucDevNo) |= ADC_CR2_ADON;               /* Power on ADC             */

    ADCX_CR2(ucDevNo) |= ADC_CR2_RSTCAL;             /* Init calibration             */
    while(ADCX_CR2(ucDevNo) & ADC_CR2_RSTCAL);       /* Wait for init operation done */

    ADCX_CR2(ucDevNo) |= ADC_CR2_CAL;                /* Start calibration            */
    while(ADCX_CR2(ucDevNo) & ADC_CR2_CAL);          /* Wait for calibraion done     */
    
    return SW_OK;
}

/**************************************************************************
* Function: WORD32 ADCx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Control and configuration of ADC
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara:
*              ucPara[1]  BYTE          1,2                  ADC device No.
*              ucPara[2]  BYTE                               Port/Channel No.
*              ucPara[3]  BYTE          SW_DEV_STOP          Stop ADC
*                                       SW_DEV_START         start ADC
*              ucPara[4]  BYTE          1,4,8,16,32          Sampling count
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
WORD32 ADCx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    BYTE ucDevNo = ptPara->ucPara[ADC_DEV_NO_POS];
    BYTE ucAdcCh = ptPara->ucPara[ADC_PORT_CH_POS];

    /* Check if adc No. is valid or NOT */
    if((ucDevNo - 1) > (MAX_ADC_DEVICE_NUM - 1))
    {
        return SW_ERR;
    }
    
    if (SW_DEV_STOP == ptPara->ucPara[ADC_START_POS])       
    {   
        return SW_OK;   /* Do nothing and return */
    }
    
    ADCX_SQR3(ucDevNo) &= ~(ADC_SQR3_SQ1_MASK);
    ADCX_SQR3(ucDevNo) |=   ucAdcCh;           /* Set channel          */

    ADCX_CR2(ucDevNo)  |=   ADC_CR2_SWSTART;   /* Start adc conversion */

    return SW_OK;                                
}

/**************************************************************************
* Funciton: WORD32 ADCx_Read(T_DATA_OPERARTION  *ptData)
* Descrip.: Get data from ADC data register
* Input   : None.
* Output  : T_DATA_OPERARTION  *ptData: 
*              ucDevNo       1,2            Device No.
*              pucBuffer     0~255          Low 8-bit of ADC data
*              pucBuffer+1   0~255          High 8-bit of ADC data
*              wDataLength   0~65535        The length of ADC data
* Return  : SW_OK    Successful
            SW_ERR   Failed
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
WORD32 ADCx_Read(T_DATA_OPERARTION  *ptData)
{
    WORD16 wData;
    BYTE ucDevNo = ptData->ucDevNo;

    /* Check if adc No. is valid or NOT */
    if((ucDevNo - 1) > (MAX_ADC_DEVICE_NUM - 1))
    {
        return SW_ERR;
    }
   
    while(!(ADCX_SR(ucDevNo) & ADC_SR_EOC));   /* Wait for conversion done */
      
    wData = ((WORD16)ADCX_DR(ucDevNo));        /* Get the adc data */

    /* Fill the data structure and return back to uppoer layer */
    *(ptData->pucBuffer)   = (wData & 0xFF);
    *(ptData->pucBuffer+1) = ((wData & 0xFF00)>>8);
    ptData->wDataLength    = 2;
    
    return SW_OK;                             
}




/**************************************************************************
* Funciton: void ADC_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
* Descrip.: Register ADC
* Input   : BYTE ucLogNo      Device logic No.
*           BYTE ucDevNo      Device physical No.
*           VOID *ptPara      None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
void ADC_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
{   
    T_REGISTED_DEVICE tAdcDev;    
    
    /* Check if the device No. is valid or NOT */
    if((ucDevNo - 1) > (MAX_ADC_DEVICE_NUM - 1))
    {
        return;
    }

    /* set operation. */
    sg_tAdcOp.pfDrvInit  = ADCx_Init;
    sg_tAdcOp.pfDrvCtrl  = ADCx_Ctrl;
    sg_tAdcOp.pfDrvRead  = ADCx_Read;
    sg_tAdcOp.pfDrvWrite = NULL;
    /* register this device. */
    tAdcDev.ucAppType  = SW_MATH_INTERFACE;
    tAdcDev.ucDevId    = SW_PERIPHERAL_AD;
    tAdcDev.ucLogDevNo = ucLogNo;
    tAdcDev.ucDevNo    = ucDevNo;
    tAdcDev.ptDevOp    = &sg_tAdcOp;
    tAdcDev.pfCallBack = NULL;
    /* call register interface. */
    API_MathDrv_Reg(&tAdcDev);
    
    return;
}


/* End of adc.c */


