/******************************************************************************
* VersionOwner (C)2013，Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Application.c
* FileIdentifier：None
* Abstract ：KNXapplication source file。
* Other Description：KNX具体应用相关的功能在此实现。在下面各个函数中增加相关功能。
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

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "Hardware.h"
#include "Knx_Prop.h"
#include "boardctrl.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "App_Common.h"
#include "Application.h"
#include "Application_Data.h"
#include "Knx_AlApp.h"
#include "demo_app.h"



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
#pragma location = "APP_APPLICATION_SEG"
void App_Data_Init(void)
{
    return;
}


/**************************************************************************
* FunctionName: BOOL Application_Init(void)
* FunctionDescription:  Total entry for application initialization。
* InputParameter None
* OutputParameter None
* Return Value： None
* Other Description: None
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
#pragma location = "APP_APPLICATION_SEG"
BOOL Application_Init(void)
{
    /* add application initicalize data here. */
    App_Data_Init();
    Demo_App_Init();
    
    return TRUE;
}


/**************************************************************************
* FunctionName: BOOL Application_Process(void)
* FunctionDescription:  General application entrance。
* InputParameter None
* OutputParameter None
* Return Value： None
* Other Description: None
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------
* 2014-07-08   V1.00                   Create
**************************************************************************/
#pragma location = "APP_APPLICATION_SEG"
BOOL Application_Process(void)
{
    /* application handler entrance. */
    Demo_App_Run();

    return TRUE;
}

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
#pragma location = "APP_APPLICATION_SEG"
BOOL Application_Save(VOID)
{
    return TRUE;
}

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
#pragma location = "APP_APPLICATION_SEG"
BOOL Application_BusSave(VOID)
{
    return TRUE;
}

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
#pragma location = "APP_APPLICATION_SEG"
BOOL Application_PowerSave(VOID)
{
    return TRUE;
}




/* End of file */

