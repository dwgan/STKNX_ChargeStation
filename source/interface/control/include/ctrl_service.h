/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：ctrl_service.h
* FileIdentifier：None
* Abstract ：本文件为控制接口层公共头文件定义。
* Other Description：
* Current Version：V1.00
* Author：      
* Completed Date：2013年7月24日
*    
* Modified History1：
*        Modified Date：2013年7月24日
*        Version Number：V1.00
*        Modified Person：      
*        Modified part：Add new public definition.
******************************************************************************/

#ifndef _CTRL_SERVICE_H_
#define _CTRL_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


/***************TIMER define***********************/
#define SW_TIMER_MAX_NUM                    20       /* max. number of timer. */
/* working mode define. */
#define SW_TIMER_TM_MODE                    0        /* timer working mode.   */
#define SW_TIMER_COUNT_MODE                 1        /* counter working mode. */
#define SW_TIMER_PWM_MODE                   2        /* PWM working mode.     */
/* control the timer. */
#define SW_TIMER_STOP                       0        /* stop the timer.  */
#define SW_TIMER_START                      1        /* start the timer. */
#define SW_DISABLE_TIMER_INT                2        /* disable the interrupt of timer. */
#define SW_ENABLE_TIMER_INT                 3        /* enable the interrupt of timer.  */
/* time scale. */
#define SW_TIMER_MS                         0        /* timer is running in ms scale. */
#define SW_TIMER_US                         1        /* timer is running is us scale. */

/********************************************************************************************************************
* T_SW_DEVICEDRIVER_PARA结构用于Timer初始化/配置时的参数定义。
* 参数列表：
           参数名       数据类型    取值范围                 含义   
  ------------------------------------------------------------------------------------------------------------------
  Input  pIntCallBackHandler                               回调函数。
  Input  ucPara[0]      BYTE      1-                       设备ID。
  Input  ucPara[1]      BYTE      0-                       物理设备号
  Input  ucPara[2]      BYTE      0-4                      工作模式
  Input                           SW_TIMER_TM_MODE
  Input                           SW_TIMER_COUNT_MODE
  Input                           SW_TIMER_PWM_MODE
  Input  ucPara[3]      BYTE      1-                       定时器时间长度(ms/us)
  Input  ucPara[4]      BYTE      SW_TIMER_MS/SW_TIMER_US
 -------------------------------------------------------------------------------------------------
  Output no.
*******************************************************************************************************************/





/**********************函数原型定义******************************/

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription: 定时器设备注册。
* InputParameterT_REGISTED_DEVICE *ptRegDev：见结构定义。
* OutputParameterNone。
* Return Value：SW_OK   ：注册成功；
            SW_ERROR：注册失败；
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData)
* 功能说明：定时器计数器读取接口。
* InputParameterucLogNo:device logical no.
            WORD32 *pdwData:pointer of return data.
* OutputParameterWORD32 *pdwData:timer data.
* Return Value：SW_OK    ：successfully.
            SW_ERROR ：failed.
* Other Description:获取物理定时器的计数器数据。
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Read(BYTE ucLogNo,WORD32 *pdwData);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData)
* 功能说明：定时器数据写接口。
* InputParameterucLogNo:device logical no.
            WORD32 dwData:pointer of return data.
* OutputParameterNone
* Return Value: SW_OK   ：成功
            SW_ERROR：失败
* Other Description:写定时器的计数器值。
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Write(BYTE ucLogNo,WORD32 dwData);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* 功能说明：定时器设备控制接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara.
*              ucPara[0]      BYTE      SW_PERIPHERAL_TIMER      Timer type.  
*              ucPara[1]      BYTE      1                        timer logical number.
*              ucPara[2]      BYTE      control command.         timer control command.  
* OutputParameterdevice dependent.
* Return Value: SW_OK   ：successfully.
            SW_ERROR：failed.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Ctrl(T_SW_DEVICEDRIVER_PARA *ptCtlPara);

/**************************************************************************
* FunctionName:WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptCtlPara)
* 功能说明：通讯层设备初始化接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->pIntCallBackHandler:callback function,if no,should set NULL.
                                    ->ucPara[0]:device ID
                                    ->ucPara[1]:logical device No.
                                    ->ucPara[2]:working mode.
                                                SW_TIMER_TM_MODE
                                                SW_TIMER_COUNT_MODE
                                                SW_TIMER_PWM_MODE
* OutputParameterno.
* Return Value: SW_OK   ：successfully.
            SW_ERROR：failed.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
**************************************************************************/
extern WORD32 API_TimerDrv_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);

/********************** DMA功能配置 *************************************************/
#define SW_DMA_CHANNEL_RELEASE        (0)          /* 释放DMA通道               */
#define SW_DMA_CHANNEL_ALLOC          (1)          /* 分配DMA通道               */
#define SW_DMA_FUNC_START             (2)          /* DMA配置和启动             */
#define SW_DMA_PARA_SET               (3)          /* DMA通道参数设置           */
    /* parameter bit0-bit1 define. */
    #define SW_DMA_TRANS_MEM2MEM      (0x01)       /* DMA数据在内存间传输       */
    #define SW_DMA_TRANS_MEM2PRE      (0x02)       /* DMA数据由内存到外设间传输 */
    #define SW_DMA_TRANS_PRE2MEM      (0x03)       /* DMA数据由外设传到内存     */
    /* parameter bit2-bit3 define. */
    #define SW_DMA_SINGLE             (0x04)       /* DMA单次传送 */
    #define SW_DMA_PINPON             (0x08)       /* DMA乒乓触发 */
    #define SW_DMA_CHAINED            (0x0c)       /* DMA连续触发 */
    /* parameter bit4 define. */
    #define SW_DMA_INTERRUPT_EN       (0x10)       /* DMA中断使能               */
    #define SW_DMA_INTERRUPT_DIS      (0x00)       /* DMA中断关闭               */



#ifdef __cplusplus
}
#endif

#endif /* _CTRL_SERVICE_H_ */




