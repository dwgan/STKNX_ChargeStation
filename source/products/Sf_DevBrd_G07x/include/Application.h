/******************************************************************************
* VersionOwner (C)2022,STMicroelectronics(ShenZhen)R&D Co.,Ltd.
*
* FileName：Application.h
* FileIdentifier：None
* Abstract ：KNXapplication header file。
* Other Description：The code only for prestudy,No forwarding without permission
* Current Version：V1.00
* Author：    
* Completed Date：2022年4月12日
*    
* Modified History1：
*        Modified Date：2022年4月12日
*        Version Number：V1.00
*        Modified Person：    
*        Modified part：Add new public definition.
******************************************************************************/

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------Define for application------------------------------*/

#define MAX_INPUT_CH_NUM         4           /* 输入通道最大数量 */
#define MAX_OUTPUT_CH_NUM        4           /* 输出通道最大数量 */


/* communication object No. define. */

/* input channel Co. define. */
#define CHARGE_CONNECT_STATUS_CO                0   /* charge point connection status 1bit  */
#define CHARGE_RUNNING_STATUS_CO                1   /* charge point running status 1bit */
#define CHARGE_BATTERY_PERCENT_CO               2   /* charge battery status 1 byte */
#define CHARGE_CURRENT_VALUE_CO                 3   /* charge current status 2 bytes */
#define CHARGE_POWER_VALUE_CO                   4   /* charge power value 4 bytes */
#define CHARGED_TIME_CO                         5   /* has been charged time */
#define REMAINING_CHARGE_TIME_CO                6   /* still reqeust charged time */
#define CHARGE_TEMPERATURE_CO                   7   /* charge temperature */
#define CHARGE_ENERGY_CO                        8   /* charged energy**/
#define DATETIME_CO                             9   /* system date time*/
#define CHARGE_ID_CO                            10  /* charging point ID */

#define OUT_COM_OBJ_NO_AbsoluteDimming       11   /* Absolute dimming *//* 1byte */

#define TEMPERATURE_ABSOLUTE_OBJ_NO          12  /*Temperature Co No*//* 2bytes */
#define HUMIDITY_OBJ_NO                      13  /*Humidity Co No*//* 2byteds */
#define COLOR_SETVALUE_OBJ_NO                14  /*Color setvalue Co No*//* 3bytes */



/*-------------------------Declaration of functions---------------------------*/
/**************************************************************************
* FunctionName: BOOL Application_Init(void)
* FunctionDescription:  Total entry for application initialization。
* InputParameter None
* OutputParameter None
* Return Value： None
* Other Description: 
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
BOOL Application_Init(void);

/**************************************************************************
* FunctionName: BOOL Application_Process(void)
* FunctionDescription:  General application entrance。
* InputParameter None
* OutputParameter None
* Return Value： None
* Other Description: 
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
BOOL Application_Process(void);

/**************************************************************************
* FunctionName: App_Data_Init(void)
* FunctionDescription:  读取输入参数功能，分配数据结构地址并读取ETS参数，通讯对象编号
             和IO读取/输出操作函数。
* InputParameter None
* OutputParameter None      
* Return Value： None
* Other Description: None
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
void App_Data_Init(void);

/**************************************************************************
* FunctionName:BOOL Application_Save(VOID)
* FunctionDescription: application save entry used for saving user data in running halt.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
BOOL Application_Save(VOID);

/**************************************************************************
* FunctionName:BOOL Application_BusSave(VOID)
* FunctionDescription: application save entry used for saving user data when bus voltage
            is abnormal.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
BOOL Application_BusSave(VOID);

/**************************************************************************
* FunctionName:BOOL Application_PowerSave(VOID)
* FunctionDescription: application save entry used for saving user data in power down.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
BOOL Application_PowerSave(VOID);






#ifdef __cplusplus
}
#endif

#endif /* _APPLICATION_H_ */
