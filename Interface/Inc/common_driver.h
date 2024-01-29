/******************************************************************************
* VersionOwner (C)2017,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：dma.h
* FileIdentifier：None
* Abstract ：本文件为嵌入式系统软件公共定义。
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


#ifndef _COMMON_DRIVER_H_
#define _COMMON_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SW_COMMON_DEV_MAX_NUM      4

/**************************************************************************
* FunctionName:WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* FunctionDescription:  通用设备控制。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value： SW_OK： 成功
             SW_ERR：失败
* Other Description: 
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create 
**************************************************************************/
WORD32 API_CommDev_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara);

/**************************************************************************
* FunctionName: void API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev)
* FunctionDescription:  通用驱动层的设备注册入口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value： SW_ERR:注册失败
             SW_OK :注册成功
  Other Description: 调用中间层的注册函数将SPI模块注册到中间层。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create  
**************************************************************************/
WORD32 API_CommonCtrlDev_Reg(T_REGISTED_DEVICE *ptRegDev);

/**************************************************************************
* FunctionName: WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara)
* FunctionDescription:  通用驱动层的初始化接口。
* InputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* OutputParameterT_SW_DEVICEDRIVER_PARA *ptCtlPara;
                                    ->ucPara[0]:设备ID
                                    ->ucPara[1]:逻辑设备号
                                    其他参考各个驱动
* Return Value： SW_OK :初始化成功
             SW_ERR:初始化失败
 Other Description:  设计思路上，要先注册资源、设备后，再调用该接口。
             该接口通过调用各个设备注册的接口再将各个驱动设
             备初始化。
* Modified Date        版本号     修改人          Modified part
* ------------------------------------------------------------------------
* 2014/03/18       V1.0                        Create
**************************************************************************/
WORD32 API_CommonCtrlDev_Init(T_SW_DEVICEDRIVER_PARA *ptInitPara);



#endif /* _COMMON_DRIVER_H_ */

/* End of common_driver.h */

