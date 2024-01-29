/************************************************************************************************************
* Right reserved (C 2016) for Shufan information technology company.
*
* File Name        : math_service.h
*
* File Description : math interface layer head file.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2014.5.28
*
* Modification Rec.:
*   Modify Data    : 2014.5.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
* Modification Rec.:
*   Modify Data    : 2020.11.25
*   Operator       :
*   Version        : 1.10
*   Action         : change api for stm32g0xxx.
**********************************************************************************************************/

#ifndef _MATH_SERVICE_H_
#define _MATH_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


#define SW_MATH_MAX_NUM             2      /* max. number of math device. */
#define SW_MATH_MAX_CHNL_NUM        24     /* max. number of channel.     */

/********************** ADC¹¦ÄÜÅäÖÃ ***********************************************/

/* ADC configure byte define. */
     /* ADC speed define,it will be set according to the application signal. bit0-bit1. */
     #define SW_ADC_SPEED_MASK             (0x03)
     #define SW_ADC_LOWEST_SPEED           (0x00)                              /* lowest speed of sampling. */
     #define SW_ADC_MIDDLE_SPEED           (0x01)                              /* middle speed of sampling. */
     #define SW_ADC_HIGHEST_SPPED          (0x02)                              /* highest speed of sampling.*/
     
     /* control if ADC works in low-power mode. bit2. */
     #define SW_ADC_LOWPW_MASK             (0x04)
     #define SW_ADC_LOWPW_EN               (0x04)                              /* enable low power mode.  */
     #define SW_ADC_LOWPW_DISEN            (~SW_ADC_LOWPW_MASK)                /* disable low power mode. */
     
     /* control if ADC works in single step mode or continuous mode. bit3-bit4. */
     #define SW_ADC_STEP_MODE_MASK         (0x18)
     #define SW_ADC_SINGLE_CHL             (0x08)                              /* single channel conversion.         */
     #define SW_ADC_GROUP_CHL              (0x10)                              /* group channel conversion.          */
     #define SW_ADC_BURST_CHL              (0x18)                              /* continue group channel conversion. */
     
     /* ADC trigger source define. bit5. */
     #define SW_ADC_TRIGGER_SRC_MASK       (0x20)
     #define SW_ADC_TRIGGER_SOFT           (0x00)                              /* software trigger. */
     #define SW_ADC_TRIGGER_HARDWARE       (SW_ADC_TRIGGER_SRC_MASK)           /* hardware trigger. */
     
     /* ADC interrupt control.bit6. */
     #define SW_ADC_INTCTRL_MASK           (0x40)
     #define SW_ADC_INT_EN                 (0x40)                              /* enable ADC interrupt.  */
     #define SW_ADC_INT_DISEN              (~SW_ADC_INTCTRL_MASK)              /* disable ADC interrupt. */
     
     /* ADC DMA control. bit7. */
     #define SW_ADC_DMA_MASK               (0x80)
     #define SW_ADC_DMA_EN                 (0x80)                              /* enable ADC's DMA.  */
     #define SW_ADC_DMA_DISEN              (~SW_ADC_DMA_EN)                    /* disable ADC's DMA. */

/* ADC control byte define. */
#define SW_ADC_SOFT_STOP                   (0x00)                              /* software stop smampling.  */
#define SW_ADC_SOFT_START                  (0x01)                              /* software start smampling. */
#define SW_ADC_CONFIGURE                   (0x02)                              /* ADC configure command.    */



/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* Descrip.: register AD devices into math interface layer.
* Input   : T_REGISTED_DEVICE *ptRegDev : defined in sw_common.h
* Output  : no.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Reg(T_REGISTED_DEVICE *ptRegDev);

/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Read(BYTE ucLogNo,BYTE ucLogChnlNo,WORD16 *pwData)
* Descrip.: it is used to read data of a channel of an AD.
* Input   : BYTE   ucLogNo    : logical device No.
*           BYTE   ucLogChnlNo: logical channel No.
*           WORD16 *pwData    : pointer of return data(word length).
* Output  : WORD16 *pwData    : return data.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Read(BYTE ucLogNo,BYTE ucLogChnlNo,WORD16 *pwData);

/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* Descrip.: it is used to control AD, such as start, stop, configure AD.
* Input   : T_SW_DEVICEDRIVER_PARA *ptCtlPara
*              ucPara[0]      BYTE      SW_PERIPHERAL_AD         device type.  
*              ucPara[1]      BYTE      0...                     Device logical number.
*              ucPara[2]      BYTE      0...                     Channel logical number.
*              ucPara[3]      BYTE      control command.         adc control command.
*                                          SW_ADC_SOFT_STOP
*                                          SW_ADC_SOFT_START
*                                          SW_ADC_CONFIGURE
*              ucPara[4]      BYTE      command parameter.
* Output  : T_SW_DEVICEDRIVER_PARA *ptCtlPara.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/*****************************************************************************************************************
* Funciton: WORD32 API_MathDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
* Descrip.: it is used to initialize AD.
* Input   : T_SW_DEVICEDRIVER_PARA *ptCtlPara
*              ucPara[0]      BYTE      SW_PERIPHERAL_AD         device type.  
*              ucPara[1]      BYTE      0...                     Device logical number.
*              ucPara[2]      BYTE      0...                     Channel logical number.
*              ucPara[3]      BYTE      control command.         adc control command.
*                                          SW_ADC_CONFIGURE
*              ucPara[4]      BYTE      command parameter.
* Output  : T_SW_DEVICEDRIVER_PARA *ptCtlPara.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
extern WORD32 API_MathDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);

/*****************************************************************************************************************
* Funciton: VOID API_MathDrv_CallBack(T_SW_INT_EVENT *ptIntEvt)
* Descrip.: it is callback handler for device's interrupt. device interrupt will call this function, then this 
*           function will call the callback handler of the application.
* Input   : ptIntEvt->ucAppType : application type.
*                     ucDevId   : device type.
*                     ucDevNo   : physical No. of the device.
*                     ucEvent   : event type.
*                     ucBuffer  : parameter buffer(this pointer should be transmit to WORD16 pointer in application).
* Output  : T_SW_INT_EVENT *ptIntEvt.
*                     ucDevId   : device type.
*                     ucDevNo   : logical No. of the device.
*                     ucEvent   : event type.
*                     ucBuffer  : parameter buffer(this pointer should be transmit to WORD16 pointer in application).
*                                 for AD, ptIntEvt->ucBuffer[0] is device logical channel No.
* Return  : SW_OK  : successfully.
*           SW_ERR : failed.
* Note    : no.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
VOID API_MathDrv_CallBack(T_SW_INT_EVENT *ptIntEvt);

#ifdef __cplusplus
}
#endif

#endif /* _MATH_SERVICE_H_ */


