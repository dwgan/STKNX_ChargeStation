/************************************************************************************************************
* Right reserved (C 2016) for Shufan information technology company.
*
* File Name        : Stm32G0xxx_adc.c
*
* File Description : deriver file for stm32g0xxx adc.
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
**********************************************************************************************************/



#include "type_def.h"
#include "Sw_common.h"
#include "Pub.h"
#include "boardcfg.h"
#include "Hardware.h"

#include "Boardctrl.h"
#include "math_service.h"
#include "system_stm32f10x.h"
#include "Stm32G0xxx_adc.h"


/* Operation of ADC */
static BYTE             sg_ucEocCunt,sg_ucCovChnlCunt;
static BYTE             sg_aucChl[ADC_MAX_CHL_NUM];
static T_DEV_OPERATION  sg_tAdcOp;
T_ADC_TMOPER            sg_tAdcTmOp;
static CALLBACK_HANDLER sg_pfAppCallBack = NULL;

WORD32 ADCx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara);

/**************************************************************************************************
* Function: WORD32 ADCx_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Init operation of adc
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara
*              ucPara[0]      BYTE      SW_PERIPHERAL_AD         device type.  
*              ucPara[1]      BYTE      0...                     Device logical number.
*              ucPara[2]      BYTE      0...                     Channel logical number.
*              ucPara[3]      BYTE      control command.         adc control command.
*                                          SW_ADC_CONFIGURE
*              ucPara[4]      BYTE      command parameter.
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* ------------------------------------------------------------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************************************/
WORD32 ADCx_Init(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    float  fTmp;
    WORD32 dwRet;
    WORD16 wTmp,wIndex;
    
    /* Check if adc No. is valid or NOT */
    if(0 != ptPara->ucPara[1])
    {
        return SW_ERR;
    }
    sg_ucEocCunt     = 0;
    sg_ucCovChnlCunt = 0;
    /* clock source is default sysclock(RCC_CCIPR), we only have one ADC. */
    RCC_APB2ENR |= RCC_APBENR2_ADCEN;
    RCC_APB2RSTR |= RCC_APBRSTR2_ADCRST;
    RCC_APB2RSTR &= (~RCC_APBRSTR2_ADCRST);

    /* initialize adc. */
    ADC_CR &= (~ADC_CR_ADEN_MSK);

    /* sample clock. default ADCCLK. */
    ADC_CCR &= (~ADC_CCR_PRESC_MSK);
    switch(SystemFrequency_SysClk)
    {
        case SYSCLK_FREQ_24M:
        {
            ADC_CCR |= ADC_CCR_PRESC_DIV12;
            break;
        }
        case SYSCLK_FREQ_32M:
        {
            ADC_CCR |= ADC_CCR_PRESC_DIV32;
            break;
        }
        case SYSCLK_FREQ_36M:
        case SYSCLK_FREQ_48M:
        {
            ADC_CCR |= ADC_CCR_PRESC_DIV12;
            break;
        }
        default:
        {
            ADC_CCR |= ADC_CCR_PRESC_DIV8;
        }
    }

    /* there are no any interrupts. */
    ADC_IER = 0;
    /* voltage regulator */
    fTmp    = SystemFrequency_SysClk / 1000000;
    wTmp    = (BYTE)(ADC_REGULAOR_TIME * fTmp);
    ADC_CR |= ADC_CR_ADVREGEN_MSK;
    for(wIndex=0;wIndex < wTmp;wIndex++);
    /* start to calibration. */
    ADC_ISR|= ADC_ISR_EOCAL_MSK;
    ADC_CR |= ADC_CR_ADCAL_MSK;
    while(0 == (ADC_ISR & ADC_ISR_EOCAL_MSK));
    
    /* configure ADC. */
    if(SW_ADC_CONFIGURE == ptPara->ucPara[ADC_PARA_CMD_INDEX])
    {
        dwRet = ADCx_Ctrl(ptPara);
    }
    else
    {
        /* enable AD. */
        ADC_ISR |= ADC_ISR_ADRDY_MSK;
        ADC_CR  |= ADC_CR_ADEN_MSK;
        while(0 == (ADC_ISR & ADC_ISR_ADRDY_MSK));
    }
    /* set callback handler. */
    sg_pfAppCallBack = ptPara->pIntCallBackHandler;
    
    return dwRet;
}

/*****************************************************************************************************************************************
* Function: WORD32 ADCx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Control and configuration of ADC
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara
*              ucPara[0]      BYTE      SW_PERIPHERAL_AD         Device type.              ADC_PARA_DEVTYPE_INDEX
*              ucPara[1]      BYTE      0                        Device physical number.   ADC_PARA_DEV_NO_INDEX
*              ucPara[2]      BYTE      0                        Channel physical number.  ADC_PARA_CHNL_NO_INDEX
*              ucPara[3]      BYTE      control command.         adc control command.      ADC_PARA_CMD_INDEX
*                                          SW_ADC_SOFT_STOP
*                                          SW_ADC_SOFT_START
*                                          SW_ADC_CONFIGURE
*              ucPara[4]      BYTE      command parameter.                                 ADC_PARA_CMD_PARA_INDEX
*                                          if ucPara[3] == SW_ADC_CONFIGURE then
*                                             ucPara[4] =  configure data;
*
*                                             if SW_ADC_LOWEST_SPEED then
*                                                sampling is in the lowest speed.
*                                             elif SW_ADC_MIDDLE_SPEED then
*                                                sampling is in the middle speed.
*                                             elif SW_ADC_HIGHEST_SPPED then
*                                                sampling is in the highest speed.
*                                             endif
*
*                                             if SW_ADC_LOWPW_EN then
*                                                nothing.
*                                             endif
*
*                                             if SW_ADC_TRIGGER_HARDWARE then
*                                                ucPara[5].bit0-bit2 device's hardware trigger number.   ADC_PARA_TRIGGER_INDEX
*                                                        ADC_TIM1_TRGO2
*                                                        ADC_TIM1_CC4  
*                                                        ADC_RESERVE1  
*                                                        ADC_TIM3_TRGO 
*                                                        ADC_TIM15_TRGO
*                                                        ADC_TIM6_TRGO 
*                                                        ADC_RESERVE2  
*                                                        ADC_EXTI_LINE 
*                                                ucPara[5].bit3-bit4 trigger polarity setting in hardware trigger mode.
*                                                        ADC_TRG_POL_H
*                                                        ADC_TRG_POL_L
*                                                        ADC_TRG_POL_HL
*                                             elif SW_ADC_TRIGGER_SOFT then
*                                                 conversion is triggered by software.
*                                             endif
*
*                                             if SW_ADC_SINGLE_CHL then
*                                                 one trigger one time sampling on the next one channel.
*                                             elif SW_ADC_GROUP_CHL then
*                                                 nothing.
*                                             elif SW_ADC_BURST_CHL then
*                                                 nothing.
*                                             endif
*
*                                             if SW_ADC_INT_EN then
*                                                 use interrupt to handle ADC,else not.
*                                             endif
*
*                                             if SW_ADC_DMA_EN then
*                                                 use DMA to handle ADC,else not. in this mode, only BUST mode is used.
*                                                 we shold enable ADC's interrupt and disable ADC interrupt in NVIC.
*                                             endif
*                                             
*                                             ucPara[6] =  sample number;         ADC_PARA_SAMPLE_CNT_INDEX
*                                                 if 0== ucPara[6] then ADC does not need to oversample.
*                                                 else ADC oversamples. ucPara[6] =  ADC_OVERSMPLE_0
*                                                                                    ADC_OVERSMPLE_2  
*                                                                                    ADC_OVERSMPLE_4  
*                                                                                    ADC_OVERSMPLE_8  
*                                                                                    ADC_OVERSMPLE_16 
*                                                                                    ADC_OVERSMPLE_32 
*                                                                                    ADC_OVERSMPLE_64 
*                                                                                    ADC_OVERSMPLE_128
*                                                                                    ADC_OVERSMPLE_256
*                                             pdwPara[0] : channel shoose.
*                                               pdwPara[0].bit0~bit18 <--> phy. channel 0  ~ phy. channel 18
*                                                          bit x = 1   --> phy. channel x is used. 
*                                               it is NOT logical channel. it means a physical channel is used.
*                                          endif
*
*                                          if ucPara[3] == SW_ADC_SOFT_START / SW_ADC_SOFT_STOP then
*                                             ucPara[2] =  channel number. Attention : it's a physical channel number beginning from 0.
*                                          endif
* Output  : no.
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
*****************************************************************************************************************************************/
WORD32 ADCx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
{
    WORD32 dwTmp;
    BYTE   ucData,ucIndex;

    /* Check if adc No. is valid or NOT */
    if(0 != ptPara->ucPara[ADC_PARA_DEV_NO_INDEX])
    {
        return SW_ERR;
    }
    switch(ptPara->ucPara[ADC_PARA_CMD_INDEX])
    {
        case SW_ADC_SOFT_STOP:
        {
            if(0 == (ADC_CR & ADC_CR_ADSTART_MSK))
            {
                break;
            }
            else
            {
                ADC_CR  |= ADC_CR_ADSTP_MSK;
                ADC_ISR |= (ADC_ISR_EOC_MSK | ADC_ISR_EOS_MSK);
                while(0 != (ADC_CR & ADC_CR_ADSTP_MSK));
            }
            
            break;
        }
        case SW_ADC_SOFT_START:
        {
            /* we use one software start trigger one channel conversion. */
            if(ptPara->ucPara[ADC_PARA_CHNL_NO_INDEX] >= ADC_MAX_CHL_NUM)
            {
                return SW_ERR;
            }
            /* stop ad. */
            if(0 != (ADC_CR & ADC_CR_ADSTART_MSK))
            {
                /* we should stop AD. */
                ADC_CR  |= ADC_CR_ADSTP_MSK;
                ADC_ISR |= (ADC_ISR_EOC_MSK | ADC_ISR_EOS_MSK);
                while(0 != (ADC_CR & ADC_CR_ADSTP_MSK));
            }
            /* get physical channel No and set channel. */
            ADC_CHSELR = (0x00000001UL << ptPara->ucPara[ADC_PARA_CHNL_NO_INDEX]);
            while(0 == (ADC_ISR & ADC_ISR_CCRDY_MSK));
            /* start conversion. */
            ADC_CR  |= ADC_CR_ADSTART_MSK;
            while(0 != (ADC_CR & ADC_CR_ADSTART_MSK));
            
            break;
        }
        case SW_ADC_CONFIGURE:
        {
            /* operation check. */
            if(0 != (ADC_CR & ADC_CR_ADSTART_MSK))
            {
                /* we are in operation. */
                ADC_CR  |= ADC_CR_ADSTP_MSK;
                ADC_ISR |= (ADC_ISR_EOC_MSK | ADC_ISR_EOS_MSK);
                while(0 != (ADC_CR & ADC_CR_ADSTP_MSK));
            }
            /* we can configure it now. */
            ucData = ptPara->ucPara[ADC_PARA_CMD_PARA_INDEX];
            /* set sampling clk. */
            ADC_SMPR &= (~(ADC_SMPR_SMPSEL_MSK | ADC_SMPR_SMP1_MSK | ADC_SMPR_SMP2_MSK));
            switch(ucData & SW_ADC_SPEED_MASK)
            {
                case SW_ADC_LOWEST_SPEED:
                {
                    ADC_SMPR |= (ADC_SMPR_SMP1_2 | ADC_SMPR_SMP1_1 | ADC_SMPR_SMP2_2 | ADC_SMPR_SMP2_1);
                    break;
                }
                case SW_ADC_MIDDLE_SPEED:
                {
                    ADC_SMPR |= (ADC_SMPR_SMP1_0 | ADC_SMPR_SMP1_1 | ADC_SMPR_SMP2_0 | ADC_SMPR_SMP2_1);
                    break;
                }
                case SW_ADC_HIGHEST_SPPED:
                {
                    ADC_SMPR |= (ADC_SMPR_SMP1_0 | ADC_SMPR_SMP2_0);
                    break;
                }
                default:
                {
                    return SW_ERR;
                }
            }
            /* we work in single, discontinue mode. Start command can be set at the end of conversion. */
            ADC_CFGR1  &= (~ADC_CFGR1_CONT_MSK);
            ADC_CFGR1  |= (ADC_CFGR1_DISCEN_MSK | ADC_CFGR1_WAIT_MSK);
            /* we work in low frequence trig mode. */
            ADC_CFGR2  |= ADC_CFGR2_LFTRIG_MSK;
            
            /* interrupt control. */
            if(ucData & SW_ADC_INTCTRL_MASK)
            {
                /* interrupt enable. */
                ADC_IER |= (ADC_IER_EOSIE_MSK | ADC_IER_EOCIE_MSK);
            }
            else
            {
                /* interrupt disable. */
                ADC_IER &= (~(ADC_IER_EOSIE_MSK | ADC_IER_EOCIE_MSK));
            }
            
            /* trigger setting. */
            if(ucData & SW_ADC_TRIGGER_SRC_MASK)
            {
                /* hardware trigger. */
                ADC_CFGR1 &= (~(ADC_CFGR1_EXTEN_MSK | ADC_CFGR1_EXTSEL_MSK));
                ADC_CFGR1 |= ((WORD32)(ptPara->ucPara[ADC_PARA_TRIGGER_INDEX] & 0x18) << 7);
                ADC_CFGR1 |= ((WORD32)(ptPara->ucPara[ADC_PARA_TRIGGER_INDEX] & 0x07) << 6);
            }
            else
            {
                /* software trigger. */
                ADC_CFGR1 &= (~ADC_CFGR1_EXTEN_MSK);
            }
            
            /* DMA */
            if(ucData & SW_ADC_DMA_MASK)
            {
                /* DMA enable.one shot mode. */
                ADC_CFGR1 &= (~ADC_CFGR1_DMACFG_MSK);
                ADC_IER   |= ADC_IER_EOCIE_MSK;
                ADC_CFGR1 |= ADC_CFGR1_DMAEN_MSK;
            }

            /* channel setting. we only support one group. */
            ADC_ISR    |= ADC_ISR_CCRDY_MSK;
            ADC_CFGR1  &= (~ADC_CFGR1_CHSELRMOD_MSK);
            /* channel checking. */
            dwTmp       = 0x00000001;
            ADC_CHSELR &= (~ADC_CHSELR_CHSEL_MSK);
            while(0 == (ADC_ISR & ADC_ISR_CCRDY_MSK));
            /* setting channel. */
            ADC_CHSELR |= (ptPara->pdwPara[0] & ADC_CHSELR_CHSEL_MSK);
            while(0 == (ADC_ISR & ADC_ISR_CCRDY_MSK));
            for(ucIndex=0;ucIndex < ADC_MAX_CHL_NUM;ucIndex++)
            {
                if(0 != (ptPara->pdwPara[0] & dwTmp))
                {
                    sg_aucChl[sg_ucEocCunt] = ucIndex;                 /* sg_ucEocCunt : logical number, ucIndex : physical number. */
                    sg_ucEocCunt++;
                }
                dwTmp <<= 1;
            }
            
            /* sample count. */
            if(ADC_OVERSMPLE_0 == ptPara->ucPara[ADC_PARA_SAMPLE_CNT_INDEX])
            {
                ADC_CFGR2 &= (~ADC_CFGR2_OVSE_MSK);
            }
            else
            {
                if(ptPara->ucPara[ADC_PARA_SAMPLE_CNT_INDEX] > ADC_OVERSMPLE_256)
                {
                    return SW_ERR;
                }
                dwTmp      = ptPara->ucPara[ADC_PARA_SAMPLE_CNT_INDEX] - 1;
                dwTmp    <<= ADC_CFGR2_OVSR_SHIFT; 
                ADC_CFGR2 &= (~(ADC_CFGR2_OVSS_MSK | ADC_CFGR2_OVSR_MSK));
                ADC_CFGR2 |= dwTmp;
                dwTmp      = ptPara->ucPara[ADC_PARA_SAMPLE_CNT_INDEX];
                dwTmp    <<= ADC_CFGR2_OVSS_SHIFT;
                ADC_CFGR2 |= (dwTmp | ADC_CFGR2_OVSE_MSK);
            }
            /* enable AD. */
            ADC_ISR |= ADC_ISR_ADRDY_MSK;
            ADC_CR  |= ADC_CR_ADEN_MSK;
            while(0 == (ADC_ISR & ADC_ISR_ADRDY_MSK));
            
            break;
        }
    }    

    return SW_OK;                                
}

/*****************************************************************************************************************
* Funciton: void Adcx_isr(void)
* Descrip.: interrupt process function of adc. used for sequence handling. it can not be used with software trigger
*           at the same time.
* Input   : no.
* Output  : no.
* Return  : no.
* Note    : This ISR will call the application callback function.the description of callback function's parameter
*           is as below:
*           T_SW_INT_EVENT  tReason
*             ucAppType        :   SW_MATH_INTERFACE.
*             ucDevId          :   SW_PERIPHERAL_AD
*             ucDevNo          :   device's physical No.
*             ucEvent          :   INTERRUPT_EVENT_RX
*                                        ucBuffer[0] is the physical channel No. begin with 0.
*                                        ucBuffer[1] is the low 8 bits of sampling data.
*                                        ucBuffer[2] is the up 4 bits of sampling data.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
void Adcx_isr(void)
{
    WORD32 dwData;
    T_SW_INT_EVENT tReason;
    
    tReason.ucAppType = SW_MATH_INTERFACE;
    tReason.ucDevId   = SW_PERIPHERAL_AD;
    tReason.ucEvent   = INTERRUPT_EVENT_RX;
    tReason.ucDevNo   = 0;
    if(0 != (ADC_ISR & ADC_ISR_EOC_MSK))
    {
        /* end of conversion. set the physical channel no. */
        tReason.ucBuffer[0] = sg_aucChl[sg_ucCovChnlCunt];
        /* get the AD data. */
        dwData              = ADC_DR;
        tReason.ucBuffer[1] = (BYTE)(dwData & 0xff);
        tReason.ucBuffer[2] = (BYTE)(dwData >> 8);
        if(sg_pfAppCallBack)
        {
            sg_pfAppCallBack(&tReason);
        }
        sg_ucCovChnlCunt = (sg_ucCovChnlCunt + 1) % sg_ucEocCunt;
    }
    if(0 != (ADC_ISR & ADC_ISR_EOS_MSK))
    {
        /* end of sequence. */
        sg_ucCovChnlCunt = 0;
        ADC_ISR         |= ADC_ISR_EOS_MSK;
        /* restart AD. */
        ADC_CR          |= ADC_CR_ADDIS_MSK;
        while(0 != (ADC_CR & ADC_CR_ADEN_MSK));
        ADC_CR          |= ADC_CR_ADEN_MSK;
        while(0 == (ADC_ISR & ADC_ISR_ADRDY_MSK));
    }
    
    return;
}

/*****************************************************************************************************************
* Funciton: WORD32 ADCx_Read(T_DATA_OPERARTION  *ptData)
* Descrip.: Get data from ADC data register
* Input   : None.
* Output  : T_DATA_OPERARTION  *ptData: 
*              ucDevNo       0              Device No.
*              pucBuffer     0~255          Low 8-bit of ADC data
*              pucBuffer+1   0~255          High 8-bit of ADC data
*              wDataLength   0~65535        The length of ADC data
* Return  : SW_OK    Successful
            SW_ERR   Failed
* Note    : None
* Date             Version     Author        Content
* ----------------------------------------------------------------------------------------------------------------
* 2016/07/31       V1.0       Danny.cao      Create 
******************************************************************************************************************/
WORD32 ADCx_Read(T_DATA_OPERARTION  *ptData)
{
    WORD16 wData;
    BYTE   ucDevNo = ptData->ucDevNo;

    /* Check if adc No. is valid or NOT */
    if(0 != ucDevNo)
    {
        return SW_ERR;
    }
    while(0 == (ADC_ISR & ADC_ISR_EOC_MSK));
    /* Get the adc data */
    wData                  = (WORD16)ADC_DR;
    /* Fill the data structure and return back to uppoer layer */
    *(ptData->pucBuffer)   = (wData & 0xFF);
    *(ptData->pucBuffer+1) = ((wData & 0xFF00)>>8);
    ptData->wDataLength    = 2;
    /* next channel. */
    sg_ucCovChnlCunt = (sg_ucCovChnlCunt + 1) % sg_ucEocCunt;
    /* check flag. */
    if(0 != (ADC_ISR & ADC_ISR_EOS_MSK))
    {
        /* end of sequence. */
        sg_ucCovChnlCunt = 0;
        ADC_ISR         |= ADC_ISR_EOS_MSK;
        /* restart AD. */
        ADC_CR          |= ADC_CR_ADDIS_MSK;
        while(0 != (ADC_CR & ADC_CR_ADEN_MSK));
        ADC_CR          |= ADC_CR_ADEN_MSK;
        while(0 == (ADC_ISR & ADC_ISR_ADRDY_MSK));
    }

    return SW_OK;                             
}

/*****************************************************************************************************************
* Funciton: void ADC_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
* Descrip.: Register ADC
* Input   : BYTE ucLogNo      Device logic No.
*           BYTE ucDevNo      Device physical No.
*           VOID *ptPara      None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* ----------------------------------------------------------------------------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
******************************************************************************************************************/
void ADC_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
{   
    T_REGISTED_DEVICE tAdcDev;    
    
    /* Check if the device No. is valid or NOT */
    if(ucDevNo != 0)
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
    /* if there are timer handle functions. */
    if(ptPara)
    {
        sg_tAdcTmOp.pfGetDlyMs = ((T_ADC_TMOPER *)ptPara)->pfGetDlyMs;
        sg_tAdcTmOp.pfGetMs    = ((T_ADC_TMOPER *)ptPara)->pfGetMs;
    }
    
    return;
}


/* End of adc.c */


