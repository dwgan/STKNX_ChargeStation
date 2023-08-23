/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：app_common.h
* FileIdentifier：None
* Abstract ：本文件为应用相关的头文件定义。
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

#ifndef _APP_COMMON_
#define _APP_COMMON_

#ifdef __cplusplus
extern "C" {
#endif

/***************** 宏定义 *****************************************************/
#define KNX_APP_ON      1                    /* KNX application output ON.     */
#define KNX_APP_OFF     0                    /* KNX application output OFF.    */
#define KNX_APP_TOGGLE  2                    /* KNX application output toggle. */
#define KNX_APP_DIMMINGRSV 3                /*  KNX application output based on Dimming RSV*/
#define KNX_APP_DIMMINGASV 4                /*  KNX application output based on Dimming ASV*/
#define KNX_APP_CURTAINOPEN 5
#define KNX_APP_CURTAINCLOSE 6
#define KNX_APP_CURTAINSTOP  7



/* input channel No define,begin with 1, 0 is forbidden  */
#define INPUT_CHANNEL_1           1
#define INPUT_CHANNEL_2           2
#define INPUT_CHANNEL_3           3
#define INPUT_CHANNEL_4           4
#define INPUT_CHANNEL_5           5
#define INPUT_CHANNEL_6           6

/* output channel No define, begin with 1, 0 is forbidden */
#define OUTPUT_CHANNEL_1          1
#define OUTPUT_CHANNEL_2          2
#define OUTPUT_CHANNEL_3          3
#define OUTPUT_CHANNEL_4          4
#define OUTPUT_CHANNEL_5          5
#define OUTPUT_CHANNEL_6          6
#define OUTPUT_CHANNEL_7          7

/* 通道输入事件定义，不要修改事件定义码。 */
#define INPUT_EVENT_NONE          0x55              /* None事件发生                        */
#define INPUT_EVENT_0             0x00              /* 短按事件（长按使能）/短按按下事件 */
#define INPUT_EVENT_1             0x01              /* 短按释放事件/长按事件（长按使能） */
#define INPUT_EVENT_2             0x02              /* 长按释放事件（长按使能）          */

/* 通道输入事件定义，不要修改事件定义码。 */
#define OUTPUT_LED_OFF           KNX_APP_OFF        /* 管脚输出的OFF状态 */
#define OUTPUT_LED_ON            KNX_APP_ON         /* 管脚输出的ON状态  */

/* 输入功能的参数定义 */
#define INPUT_FILTER_MIN_TIME               20      /* 防抖最小时间20ms   */
#define INPUT_FILTER_MAX_TIME               1000    /* 防抖最大时间1000ms */
#define INPUT_HOLDING_PRESS_ENABLE          1       /* 使能长按功能       */
#define INPUT_HOLDING_PRESS_DISABLE         0       /* 关闭长按功能       */
#define INPUT_CONTACT_TYPE_OPEN             0       /* 输入触点为常开类型 */
#define INPUT_CONTACT_TYPE_CLOSE            1       /* 输入触点为常闭类型 */
#define INPUT_HOLDING_PRESS_MIN_TIME        200     /* 长按识别最短时间   */
#define INPUT_HOLDING_PRESS_MAX_TIME        65535   /* 长按识别最长时间   */

/* 按键检测结果定义，此处定义在设备编写按键功能是需要考虑按下和常闭/开触点的关系。 */
#define INPUT_CHANNEL_OPEN                  INPUT_CONTACT_TYPE_OPEN        /* CPU管脚检测到按键按下信号 */
#define INPUT_CHANNEL_CLOSE                 INPUT_CONTACT_TYPE_CLOSE       /* CPU管脚没有检测到按键信号 */
/* 上述输入信号定义和输入通断定义的对应需要在应用中根据实际情况做好对应 */

/************ 通用参数配置区 ********************/
#define INPUT_CHANNEL_ENABLE                1       /* 使能通道         */
#define INPUT_CHANNEL_DISABLE               0       /* 非能通道         */
#define INPUT_PWR_START_CHK_EN              1       /* 上电状态扫描使能 */
#define INPUT_PWR_START_CHK_DIS             0       /* 上电状态扫描非能 */
#define INPUT_PWR_START_BTN_EN              1       /* 上电按键使能     */
#define INPUT_PWR_START_BTN_DIS             0       /* 上电按键非能     */

#define INPUT_FUNC_NONE_CMD                 0       /* 输入通道None控制命令   */   
#define INPUT_FUNC_ONOFF_CMD                1       /* 输入通道开关控制命令 */    
#define INPUT_FUNC_DIM_CMD                  2       /* 输入通道调光控制命令 */    
#define INPUT_FUNC_SHUTTER_CMD              3       /* 输入通道窗帘控制命令 */    
#define INPUT_FUNC_FORCED_CMD               4       /* 输入通道强制控制命令 */    
#define INPUT_FUNC_SCENE_CMD                5       /* 输入通道场景控制命令 */    
#define INPUT_FUNC_VALUE_CMD                6       /* 输入通道数值控制命令 */        

/************ 开关功能参数定义 ******************/
#define SWITCH_CO_FUNC_EN                   INPUT_CHANNEL_ENABLE    /* 使能开关功能的通讯对象功能 */
#define SWITCH_CO_FUNC_DISABLE              INPUT_CHANNEL_DISABLE   /* 使能开关功能的通讯对象功能 */
#define SWITCH_FUNC_NOACTION                0                       /* 开关功能None动作             */
#define SWITCH_FUNC_ON                      1                       /* 开关On功能                 */
#define SWITCH_FUNC_OFF                     2                       /* 开关Off功能                */
#define SWITCH_FUNC_TOGGLE                  3                       /* 开关Toggle功能             */
#define SWITCH_PERIOD_FUNC_STOP             4                       /* 周期上发停止               */
#define SWITCH_FUNC_END                     5                       /* 通讯对象功能结束定义       */

#define SWITCH_PERIOD_FUNC_DISABLE          KNX_APP_OFF             /* 关闭周期上送功能           */
#define SWITCH_PERIOD_FUNC_ENABLE           KNX_APP_ON              /* 使能周期上送功能           */
#define SWITCH_PERIOD_FUNC_OFF_TRIGGER      1                       /* OFF启动周期上送功能        */
#define SWITCH_PERIOD_FUNC_ON_TRIGGER       2                       /* ON启动周期上送功能         */
#define SWITCH_PERIOD_FUNC_ALWAYS_TRIGGER   3                       /* On/Off启动周期上送功能     */

/************ 调光功能参数定义 ******************/
#define DIM_SWITCH_NO_ACTION                0                       /* Do nothing          */
#define DIM_SWITCH_ON                       1                       /* ON command          */
#define DIM_SWITCH_OFF                      2                       /* OFF command         */
#define DIM_SWITCH_TOGGLE                   3                       /* Toggle command      */
#define DIM_BRIGHT                          0                       /* dim bright          */
#define DIM_DARK                            1                       /* dim dark            */
#define DIM_ALTERNATING                     2                       /* Alternating dimmng  */
#define DIM_START_STOP_MODE                 0                       /* start/stop dim mode */
#define DIM_STEP_MODE                       1                       /* Step dim mode       */
#define DIM_STEP_1_56_PERCENT               1                       /* 1.56% step          */
#define DIM_STEP_3_13_PERCENT               2                       /* 3.13% step          */
#define DIM_STEP_6_25_PERCENT               3                       /* 6.25% step          */
#define DIM_STEP_12_5_PERCENT               4                       /* 12.5% step          */
#define DIM_STEP_25_0_PERCENT               5                       /* 25.0% step          */
#define DIM_STEP_50_0_PERCENT               6                       /* 50.0% step          */
#define DIM_STEP_100_0_PERCENT              7                       /* 100%  step          */

/************ 窗帘功能参数定义 ******************/
#define SHUTTER_1_BUTTON_MODE               0                       /* 1 button mode(Alternating) */
#define SHUTTER_2_BUTTON_UP_MODE            1                       /* 2 buttons up mode          */
#define SHUTTER_2_BUTTON_DOWN_MODE          2                       /* 2 buttons down mode        */
#define SHUTTER_RELEASE_STOP_DISABLE        0                       /* Disable "release stop"     */
#define SHUTTER_RELEASE_STOP_ENABLE         1                       /* Enable "release stop"      */

/************ 场景功能参数定义 ******************/
#define  SCENE_FUNC_DISABLE                 0                       /* Disable scene function     */
#define  SCENE_FUNC_ENABLE                  1                       /* Enable scene function      */
#define  SCENE_CALL_A_SCENE                 0                       /* Call a scene               */
#define  SCENE_STORE_A_SCENE                1                       /* Store a scene              */

/************ 数值功能参数定义 ******************/
#define VALUE_NO_VALUE_COMMAND              0                       /* Send no command            */
#define VALUE_1_BYTE_INT_VALUE              1                       /* Send 1 byte int value      */
#define VALUE_2_BYTE_INT_VALUE              2                       /* Send 2 byte int value      */
#define VALUE_2_BYTE_FLOAT_VALUE            3                       /* Send 2 byte float value    */

/************ 强制功能参数定义 ******************/
 #define FORCED_NO_COMMAND                  0                       /* Send no command                          */
 #define FORCED_DISABLE_FORCED_OPERATION    1                       /* Send disable forced operation command    */
 #define FORCED_ENABLE_FORCED_ON_OPERATION  2                       /* Send enable forced ON operation command  */
 #define FORCED_ENABLE_FORCED_OFF_OPERATION 3                       /* Send enable forced OFF operation command */

/************ 输出通道功能参数定义 ******************/
#define OUTPUT_CHANNEL_DISABLE              0                       /* Output channel is disabled */
#define OUTPUT_CHANNEL_ENABLE               1                       /* Output channel is enabled */
#define OUTPUT_ONOFF_MODE                   0                       /* Output mode is ON/OFF                */
#define OUTPUT_FLASH_MODE                   1                       /* Output mode is Flahs                 */
#define OUTPUT_INIT_OFF_STATE               0                       /* Init state is OFF                    */
#define OUTPUT_INIT_ON_STATE                1                       /* Init State is ON                     */
#define OUTPUT_ON_RCV1_AND_OFF_RCV0         0                       /* "1" for ON, "0" for OFF              */
#define OUTPUT_ON_RCV0_AND_OFF_RCV1         1                       /* "0" for ON, "1" for OFF              */
#define OUTPUT_ON_RCV1_0_NO_OFF_CMD         2                       /* "1" or "0" for ON,no OFF command     */
#define OUTPUT_INIT_STOP_FLASH              0                       /* Init state is stop flash             */
#define OUTPUT_INIT_START_FLASH             1                       /* Init state is start flash            */
#define OUTPUT_START_RCV1_AND_STOP_RCV0     0                       /* "1" for START, "0" for STOP          */
#define OUTPUT_START_RCV0_AND_STOP_RCV1     1                       /* "0" for START, "1" for STOP          */
#define OUTPUT_START_RCV1_0_AND_NO_STOP_CMD 2                       /* "1" or "0" for START,no STOP command */

/************ 通用通道功能参数定义 ******************/
#define GENERAL_NO_IN_OPERATION             0                       /* Disable in operation function       */
#define GENERAL_PERIODLY_SEND_0             1                       /* Enable in operation periodly send 0 */
#define GENERAL_PERIODLY_SEND_1             2                       /* Enable in operation periodly send 1 */
#define GENERAL_ALL_CONTROL_DISABLE         0                       /* Disable all control output          */
#define GENERAL_ALL_CONTROL_ENABLE          1                       /* Enable all control output           */
#define GENERAL_TELEGRAM_LIMIT_DISABLE      0                       /* Disable telegram limitation         */
#define GENERAL_TELEGRAM_LIMIT_ENABLE       1                       /* Enable telegaram limitation         */
#define GENERAL_LIMIT_TIME_50MS             0                       /* Limit period time is 50ms           */
#define GENERAL_LIMIT_TIME_200MS            1                       /* Limit period time is 200ms          */
#define GENERAL_LIMIT_TIME_500MS            2                       /* Limit period time is 500ms          */
#define GENERAL_LIMIT_TIME_1000MS           3                       /* Limit period time is 1s             */
#define GENERAL_LIMIT_TIME_5000MS           4                       /* Limit period time is 5s             */
#define GENERAL_LIMIT_TIME_10000MS          5                       /* Limit period time is 10s            */
#define GENERAL_LIMIT_TIME_30000MS          6                       /* Limit period time is 30s            */
#define GENERAL_LIMIT_TIME_60000MS          7                       /* Limit period time is 60s            */

/* force function control define. */
#define APP_FORCE_ENABLE         1                  /* enable the force function. */
#define APP_FORCE_DISABLE        0                  /* disable the force funtion. */
#define APP_FORCE_CTRL_MASK      0x02               /* bit1=0 means quit force. */
#define APP_FORCE_VALUE_MASK     0x01               /* bit0 is the force value. */

/* scene function control define. */
#define APP_SCENE_ENABLE          1                  /* enable the scene function. */
#define APP_SCENE_DISABLE         0                  /* disable the scene funtion. */
#define APP_SCENE_DATA_MASK       0x3f               /* valid data mask of scence data. */
#define APP_SCENE_RESV_DATA_MASK  0x40               /* reserve bit of scene data.      */
#define APP_SCENE_SAVE_MASK       0x80               /* save scene data mask.           */

#define OUTPUT_LED_OFF           KNX_APP_OFF
#define OUTPUT_LED_ON            KNX_APP_ON 
#define OUTPUT_ONOFF             KNX_APP_ON
#define OUTPUT_FLASH             KNX_APP_TOGGLE


/*************** 数据结构定义 **************************************************/
typedef BYTE (*INPUT_CHECK_FUNC)(BYTE ucChnNo);          /* 按键检测函数类型定义 */
typedef void (*OUTPUT_FUNC)(BYTE ucChnNo, BYTE ucOnOff);  /* 管脚输出函数类型定义 */
/****************************************************
* 结构名：T_BTN_EN_CO_FUNC_PARA;
* 描述：  开关量输入通道按键按键使能通讯对象参数。
* 参数：
    BYTE    ucCoNo;                               通讯对象号           
* 作者：      
* Modified History：
*  2014-7-8        新增结构；
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                            /* 通讯对象号           */
}T_BTN_EN_CO_FUNC_PARA;

/****************************************************
* 结构名：T_INPUT_CH_DRIVER_PARA;
* 描述：  开关量输入通道按键驱动ETS配置参数。
* 参数：
    BYTE    ucButtonEn;            INPUT_CHANNEL_DISABLE        按键处于不使能状态
                                   INPUT_CHANNEL_ENABLE         按键处于使能状态  
    BYTE    ucPwrStartChk;         INPUT_PWR_START_CHK_EN       输入通道上电状态检查
                                   INPUT_PWR_START_CHK_DIS
    BYTE    ucLongPressEn;         INPUT_HOLDING_PRESS_DISABLE  不区分长短按
                                   INPUT_HOLDING_PRESS_ENABLE   区分长短按
    BYTE    ucContactType;         INPUT_CONTACT_TYPE_OPEN      常开触点类型
                                   INPUT_CONTACT_TYPE_CLOSE     常闭触点类型
    WORD16  wDebounceTime;         INPUT_FILTER_MIN_TIME        按键防抖时间最小20ms
                                   INPUT_FILTER_MAX_TIME        按键防抖时间最大1000ms
    WORD16  wTimeForLongPress;     INPUT_HOLDING_PRESS_MIN_TIME 长按区别时间
                                   INPUT_HOLDING_PRESS_MAX_TIME
    INPUT_CHECK_FUNC fpKeyCheckOp; 输入通道检测函数
* 作者：        
* Modified History：
*  2014-7-6          新增结构；
****************************************************/
typedef struct
{
    BYTE    ucButtonEn;                        /* 按键是否使能         */
    BYTE    ucPwrStartChk;                     /* 输入通道上电状态检查 */
    BYTE    ucLongPressEn;                     /* 长按是否使能         */
    BYTE    ucContactType;                     /* 面板接入触点类型     */
    WORD16  wTimeForLongPress;                 /* 长按区别时间         */
    WORD16  wDebounceTime;                     /* 按键防抖时间         */
    INPUT_CHECK_FUNC fpKeyCheckOp;             /* 输入通道检测函数     */
}T_INPUT_CH_DRIVER_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   开关                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* 结构名：T_SWITCH_CO_FUNC_PARA;
* 描述：  开关功能的开关通讯对象参数。
* 参数：
          BYTE    ucFuncEn          通讯对象的开关功能是否使能 
                                    取值：
                                    SWITCH_CO_FUNC_EN
                                    SWITCH_CO_FUNC_DISABLE
          BYTE    ucPressFunc       通讯对象的开关功能类型  
                                    取值：
                                    SWITCH_FUNC_NOACTION
                                    SWITCH_FUNC_ON
                                    SWITCH_FUNC_OFF
                                    SWITCH_FUNC_TOGGLE
                                    SWITCH_PERIOD_FUNC_STOP
          BYTE    ucReleaseFunc     通讯对象的开关功能类型  
                                    取值：
                                    SWITCH_FUNC_NOACTION
                                    SWITCH_FUNC_ON
                                    SWITCH_FUNC_OFF
                                    SWITCH_FUNC_TOGGLE
                                    SWITCH_PERIOD_FUNC_STOP
          WORD16  wEvt0DlyTm        事件0下通讯对象的开关命令延时处理时间MS
                                    0-65535Ms
          WORD16  wEvt1DlyTm        事件1下通讯对象的开关命令延时处理时间MS
                                    0-65535Ms
* 作者：        
* Modified History：
*  2014-7-6          新增结构；
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                             /* 通讯对象的通讯对象号码       */
    BYTE    ucFuncEn;                           /* 通讯对象的开关功能是否使能   */
    BYTE    ucPressFunc;                        /* 按下时通讯对象的开关功能类型 */
    BYTE    ucReleaseFunc;                      /* 释放时通讯对象的开关功能类型 */
    WORD16  wEvt0DlyTm;                         /* EVENT0延时发送时间           */
    WORD16  wEvt1DlyTm;                         /* EVENT1延时发送时间           */
}T_SWITCH_CO_FUNC_PARA;

/****************************************************
* 结构名：T_SWITCH_CHANNEL_PARA;
* 描述：  开关功能的开关通讯对象参数。
* 参数：
    BYTE   ucChnlNo;                                开关通道号,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    注：一个产品中的输入通道号要连续。
    BYTE                   ucPeriodFuncPara         周期上送功能参数，取值如下：
                                                    SWITCH_PERIOD_FUNC_DISABLE
                                                    SWITCH_PERIOD_FUNC_ON_TRIGGER
                                                    SWITCH_PERIOD_FUNC_OFF_TRIGGER
                                                    SWITCH_PERIOD_FUNC_ALWAYS_TRIGGER
    WORD16                 wPeriodFuncTime;         周期上送功能时间1-65535S 
    T_BTN_EN_CO_FUNC_PARA  tBtnEnCoPara;            按键使能通讯对象参数     
    T_INPUT_CH_DRIVER_PARA tChannelPara;            通道参数                 
    T_SWITCH_CO_FUNC_PARA  tSwitchCo1Para;          开关通讯对象1的参数   
    T_SWITCH_CO_FUNC_PARA  tSwitchCo2Para;          开关通讯对象1的参数   
    T_SWITCH_CO_FUNC_PARA  tSwitchCo3Para;          开关通讯对象1的参数   
* 作者：      
* Modified History：
*  2014-4-30        新增结构；
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* 输入通道号,从1开始       */
    BYTE                    ucPeriodFuncPara;    /* 周期上送功能参数         */
    WORD16                  wPeriodFuncTime;     /* 周期上送功能时间1-65535S */
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;        /* 按键使能通讯对象参数     */
    T_INPUT_CH_DRIVER_PARA  tChannelPara;        /* 通道参数                 */
    T_SWITCH_CO_FUNC_PARA   tSwitchCo1Para;      /* 开关通讯对象1的参数      */
    T_SWITCH_CO_FUNC_PARA   tSwitchCo2Para;      /* 开关通讯对象2的参数      */
    T_SWITCH_CO_FUNC_PARA   tSwitchCo3Para;      /* 开关通讯对象3的参数      */
}T_SWITCH_CHANNEL_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   调光                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************                        
* 结构名：T_DIM_SWITCH_CO_FUNC_PARA;
* 描述：  调光功能的开关通讯对象参数。
* 参数：
    BYTE   ucCoNo;                                  通讯对象的通讯对象号码
    BYTE   ucDimSwichFunc;                          开关选项，取值如下:
                                                    DIM_SWITCH_NO_ACTION   None开关功能
                                                    DIM_SWITCH_ON          打开
                                                    DIM_SWTICH_OFF         关闭
                                                    DIM_SWITCH_TOGGLE      交替开关
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码 */
    BYTE   ucDimSwichFunc;                         /* 开关选项               */
}T_DIM_SWITCH_CO_FUNC_PARA;

/****************************************************                        
* 结构名：T_DIM_CO_FUNC_PARA;
* 描述：  调光功能的调光通讯对象参数。
* 参数：
    BYTE   ucCoNo;                                  通讯对象的通讯对象号码
    BYTE   ucDimFunc;                               调光选项，取值如下:
                                                    DIM_BRIGHT             调亮
                                                    DIM_DARK               调暗
                                                    DIM_ALTERNATING        交替调光
    BYTE   ucDimMode;                               调光模式,取值如下:
                                                    DIM_START_STOP_MODE    启停调光模式
                                                    DIM_STEP_MODE          步长调光模式
    BYTE   ucDimStep;                               调光步长
                                                    DIM_STEP_1_56_PERCENT  1.56%步长 
                                                    DIM_STEP_3_13_PERCENT  3.13%步长   
                                                    DIM_STEP_6_25_PERCENT  6.25%步长   
                                                    DIM_STEP_12_5_PERCENT  12.5%步长   
                                                    DIM_STEP_25_0_PERCENT  25.0%步长   
                                                    DIM_STEP_50_0_PERCENT  50.0%步长   
                                                    DIM_STEP_100_0_PERCENT 100.0%步长  
    WORD16 wDimStepPd;                              步长调光周期，取值范围0~65535ms                                                   
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码 */
    BYTE   ucDimFunc;                              /* 调光选项               */
    BYTE   ucDimMode;                              /* 调光模式               */
    BYTE   ucDimStep;                              /* 调光步长               */
    WORD16 wDimStepPd;                             /* 步长调光周期           */
}T_DIM_CO_FUNC_PARA;

/****************************************************
* 结构名：T_DIM_CHANNEL_PARA;
* 描述：  调光命令通道的参数
* 参数：
    BYTE                      ucChnlNo;               开关通道号,1-6 
                                                      INPUT_CHANNEL_1
                                                      INPUT_CHANNEL_2
                                                      INPUT_CHANNEL_3
                                                      INPUT_CHANNEL_4
                                                      INPUT_CHANNEL_5
                                                      INPUT_CHANNEL_6
                                                      注：一个产品中的输入通道号要连续。
    T_BTN_EN_CO_FUNC_PARA     tBtnEnCoPara;           按键使能通讯对象参数  
    T_INPUT_CH_DRIVER_PARA    tChannelPara;           通道按键参数                 
    T_DIM_SWITCH_CO_FUNC_PARA tSwitchCoPara;          开关通讯对象的参数    
    T_DIM_CO_FUNC_PARA        tDimCoPara;             调光通讯对象的参数       
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE                      ucChnNo;             /* 输入通道号,从1开始       */
    T_BTN_EN_CO_FUNC_PARA     tBtnEnCoPara;        /* 按键使能通讯对象参数     */
    T_INPUT_CH_DRIVER_PARA    tChannelPara;        /* 通道按键参数             */
    T_DIM_SWITCH_CO_FUNC_PARA tSwitchCoPara;       /* 开关通讯对象的参数       */
    T_DIM_CO_FUNC_PARA        tDimCoPara;          /* 调光通讯对象的参数       */
}T_DIM_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   窗帘                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* 结构名：T_SHUTTER_CO_FUNC_PARA;
* 描述：  窗帘控制命令的窗帘通讯对象(移动、停止)参数。
* 参数：
    BYTE    ucCoNo;                             通讯对象的通讯对象号码
    BYTE    ucShutterMode;                      窗帘控制模式
                                                SHUTTER_1_BUTTON             单键模式:向上-> 停/向下调角度 -> 向下 ->停/向上调角度
                                                SHUTTER_2_BUTTON_UP          双键模式:短按=停/向上调整角度；长按=向上移动
                                                SHUTTER_2_BUTTON_DOWN        双键模式:短按=停/向下调整角度；长按=向下移动
    BYTE    ucShutterReleaseStop;               按键释放是否停止 
                                                SHUTTER_RELEASE_STOP_DISABLE 按键释放不停止
                                                SHUTTER_RELEASE_STOP_ENABLE  按键释放停止                                               
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码 */
    BYTE   ucShutterMode;                          /* 窗帘控制模式           */
    BYTE   ucShutterReleaseStop;                   /* 按键释放是否停止       */
}T_SHUTTER_CO_FUNC_PARA;

/****************************************************
* 结构名：T_POSITION_LIMIT_CO_FUNC_PARA;
* 描述：  窗帘控制命令上下限位通讯对象参数
* 参数：
    BYTE    ucCoNo;                             通讯对象的通讯对象号码                                             
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码 */
}T_POSITION_LIMIT_CO_FUNC_PARA;

/****************************************************
* 结构名：T_SHUTTER_CHANNEL_PARA;
* 描述：  窗帘控制命令通道的参数
* 参数：
    BYTE   ucChnlNo;                                      开关通道号,1-6 
                                                          INPUT_CHANNEL_1
                                                          INPUT_CHANNEL_2
                                                          INPUT_CHANNEL_3
                                                          INPUT_CHANNEL_4
                                                          INPUT_CHANNEL_5
                                                          INPUT_CHANNEL_6
                                                          注：一个产品中的输入通道号要连续。
    T_BTN_EN_CO_FUNC_PARA         tBtnEnCoPara;           按键使能通讯对象参数  
    T_INPUT_CH_DRIVER_PARA        tChannelPara;           通道按键参数                 
    T_SHUTTER_CO_FUNC_PARA        tUpDownCoPara;          上下移动通讯对象的参数      
    T_SHUTTER_CO_FUNC_PARA        tStopAdjCoPara;         停止/角度调整通讯对象的参数 
    T_POSITION_LIMIT_CO_FUNC_PARA tUpLimitCoPara;         上限位通讯对象的参数        
    T_POSITION_LIMIT_CO_FUNC_PARA tLowLimitCoPara;        下限位通讯对象的参数            
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE                          ucChnNo;             /* 输入通道号,从1开始          */
    T_BTN_EN_CO_FUNC_PARA         tBtnEnCoPara;        /* 按键使能通讯对象参数        */
    T_INPUT_CH_DRIVER_PARA        tChannelPara;        /* 通道按键参数                */
    T_SHUTTER_CO_FUNC_PARA        tUpDownCoPara;       /* 上下移动通讯对象的参数      */
    T_SHUTTER_CO_FUNC_PARA        tStopAdjCoPara;      /* 停止/角度调整通讯对象的参数 */
    T_POSITION_LIMIT_CO_FUNC_PARA tUpLimitCoPara;      /* 上限位通讯对象的参数        */
    T_POSITION_LIMIT_CO_FUNC_PARA tLowLimitCoPara;     /* 下限位通讯对象的参数        */
}T_SHUTTER_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   场景                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* 结构名：T_SCENE_CO_FUNC_PARA;
* 描述：  场景控制命令场景通讯对象参数
* 参数：
    BYTE    ucCoNo;                             通讯对象的通讯对象号码   
    BYTE    ucSceneEn0;                         是否启用EVENT 0下场景功能
                                                SCENE_FUNC_DISABLE         不启用EVENT 0下场景功能
                                                SCENE_FUNC_ENABLE          启用EVENT 0下场景功能   
    BYTE    ucSceneEn1;                         是否启用EVENT 1下场景功能
                                                SCENE_FUNC_DISABLE         不启用EVENT 1下场景功能
                                                SCENE_FUNC_ENABLE          启用EVENT 1下场景功能
    BYTE    ucSceneCallStore0;                  EVNET0配置为调用/储存场景
                                                SCENE_CALL_A_SCENE         EVNET0配置为调用场景
                                                SCENE_STORE_A_SCENE        EVNET0配置为储存场景
    BYTE    ucSceneCallStore1;                  EVNET1配置为调用/储存场景
                                                SCENE_CALL_A_SCENE         EVNET1配置为调用场景
                                                SCENE_STORE_A_SCENE        EVNET1配置为储存场景
    BYTE    ucSceneNum0;                        场景号 for EVENT 0，取值范围 0~63
    BYTE    ucSceneNum1;                        场景号 for EVENT 1，取值范围 0~63    
    WORD16 wEvt0DlyTm;                          EVENT0延时发送时间，取值范围 0~65535s  
    WORD16 wEvt1DlyTm;                          EVENT1延时发送时间，取值范围 0~65535s                                    
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码    */
    BYTE   ucSceneEn0;                             /* 是否启用EVENT 0下场景功能 */
    BYTE   ucSceneEn1;                             /* 是否启用EVENT 1下场景功能 */
    BYTE   ucSceneCallStore0;                      /* EVNET0配置为调用/储存场景 */
    BYTE   ucSceneCallStore1;                      /* EVNET1配置为调用/储存场景 */
    BYTE   ucSceneNum0;                            /* EVENT0场景号              */
    BYTE   ucSceneNum1;                            /* EVENT1场景号              */
    WORD16 wEvt0DlyTm;                             /* EVENT0延时发送时间        */
    WORD16 wEvt1DlyTm;                             /* EVENT1延时发送时间        */
}T_SCENE_CO_FUNC_PARA;

/****************************************************
* 结构名：T_SCENE_CHANNEL_PARA;
* 描述：  场景控制命令通道的参数
* 参数：
    BYTE   ucChnlNo;                                开关通道号,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    注：一个产品中的输入通道号要连续。
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;           按键使能通讯对象参数  
    T_INPUT_CH_DRIVER_PARA  tChannelPara;           通道按键参数                 
    T_SCENE_CO_FUNC_PARA    tSceneCoPara;           场景通讯对象的参数      
         
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* 输入通道号,从1开始          */
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;        /* 按键使能通讯对象参数        */
    T_INPUT_CH_DRIVER_PARA  tChannelPara;        /* 通道按键参数                */
    T_SCENE_CO_FUNC_PARA    tSceneCoPara;        /* 场景通讯对象的参数          */
}T_SCENE_CHANNEL_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   数值                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* 结构名：T_1_BYTE_VALUE_CO_FUNC_PARA;
* 描述：  数值控制命令1byte数值通讯对象参数
* 参数：
    BYTE   ucCoNo;                              通讯对象的通讯对象号码   
    BYTE   ucValue0;                            EVENT0下数值，取值范围 0~255              
    BYTE   ucValue1;                            EVENT1下数值，取值范围 0~255                 
    WORD16 wEvt0DlyTm;                          EVENT0延时发送时间，取值范围 0~65535s
    WORD16 wEvt1DlyTm;                          EVENT1延时发送时间，取值范围 0~65535s                                  
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码    */
    BYTE   ucValue0;                               /* EVENT0下数值              */
    BYTE   ucValue1;                               /* EVENT1下数值              */
    WORD16 wEvt0DlyTm;                             /* EVENT0延时发送时间        */
    WORD16 wEvt1DlyTm;                             /* EVENT1延时发送时间        */
}T_1_BYTE_VALUE_CO_FUNC_PARA;

/****************************************************
* 结构名：T_2_BYTE_VALUE_CO_FUNC_PARA;
* 描述：  数值控制命令2byte数值通讯对象参数
* 参数：
    BYTE    ucCoNo;                             通讯对象的通讯对象号码   
    WORD16  wValue0;                            EVENT0下整形数值，取值范围 0~65535              
    WORD16  wValue1;                            EVENT1下整形数值，取值范围 0~65535 
    WORD16  wValueBase0;                        EVENT0下浮点型底数数值，取值范围 0~4095    
    WORD16  wValueBase1;                        EVENT1下浮点型底数数值，取值范围 0~4095   
    BYTE    ucValueExp0;                        EVENT0下浮点型指数数值，取值范围 0~15     
    BYTE    ucValueExp1;                        EVENT1下浮点型指数数值，取值范围 0~15                  
    WORD16  wEvt0DlyTm;                         EVENT0延时发送时间，取值范围 0~65535s
    WORD16  wEvt1DlyTm;                         EVENT1延时发送时间，取值范围 0~65535s                                  
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码    */
    WORD16 wValue0;                                /* EVENT0下整形数值          */
    WORD16 wValue1;                                /* EVENT1下整形数值          */
    WORD16 wValueBase0;                            /* EVENT0下浮点型底数数值    */ 
    WORD16 wValueBase1;                            /* EVENT1下浮点型底数数值    */ 
    BYTE   ucValueExp0;                            /* EVENT0下浮点型指数数值    */ 
    BYTE   ucValueExp1;                            /* EVENT1下浮点型指数数值    */ 
    WORD16 wEvt0DlyTm;                             /* EVENT0延时发送时间        */
    WORD16 wEvt1DlyTm;                             /* EVENT1延时发送时间        */
}T_2_BYTE_VALUE_CO_FUNC_PARA;

/****************************************************
* 结构名：T_VALUE_CHANNEL_PARA;
* 描述：  数值控制命令通道的参数
* 参数：
    BYTE   ucChnlNo;                                开关通道号,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    注：一个产品中的输入通道号要连续。
    BYTE   ucValueOpt0;                             EVENT0数值参数选项 
                                                    VALUE_NO_VALUE_COMMAND    事件0下不发送数值命令
                                                    VALUE_1_BYTE_INT_VALUE    事件0下发送1BYTE整形数值命令
                                                    VALUE_2_BYTE_INT_VALUE    事件0下发送2BYTE整形数值命令
                                                    VALUE_2_BYTE_FLOAT_VALUE  事件0下发送2BYTE浮点型数值命令    
    BYTE   ucValueOpt1;                             EVENT1数值参数选项 
                                                    VALUE_NO_VALUE_COMMAND    事件1下不发送数值命令
                                                    VALUE_1_BYTE_INT_VALUE    事件1下发送1BYTE整形数值命令
                                                    VALUE_2_BYTE_INT_VALUE    事件1下发送2BYTE整形数值命令
                                                    VALUE_2_BYTE_FLOAT_VALUE  事件1下发送2BYTE浮点型数值命令 
    T_BTN_EN_CO_FUNC_PARA       tBtnEnCoPara;       按键使能通讯对象参数  
    T_INPUT_CH_DRIVER_PARA      tChannelPara;       通道按键参数                      
    T_2_BYTE_VALUE_CO_FUNC_PARA t1ByteValueCoPara;  1BYTE数值通讯对象的参数     
    T_2_BYTE_VALUE_CO_FUNC_PARA t2ByteValueCoPara;  2BYTE数值通讯对象的参数              
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE                        ucChnNo;             /* 输入通道号,从1开始          */
    BYTE                        ucValueOpt0;         /* EVENT0数值参数选项          */
    BYTE                        ucValueOpt1;         /* EVENT1数值参数选项          */
    T_BTN_EN_CO_FUNC_PARA       tBtnEnCoPara;        /* 按键使能通讯对象参数        */
    T_INPUT_CH_DRIVER_PARA      tChannelPara;        /* 通道按键参数                */
    T_1_BYTE_VALUE_CO_FUNC_PARA t1ByteValueCoPara;   /* 1BYTE数值通讯对象的参数     */
    T_2_BYTE_VALUE_CO_FUNC_PARA t2ByteValueCoPara;   /* 2BYTE数值通讯对象的参数     */
}T_VALUE_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   强制                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* 结构名：T_FORCED_CO_FUNC_PARA;
* 描述：  强制控制命令强制通讯对象参数
* 参数：
    BYTE    ucCoNo;                                 通讯对象的通讯对象号码   
    BYTE    ucForcedOp0;                            EVENT0下强制功能选项
                                                    FORCED_NO_COMMAND                   事件0下None强制功能命令
                                                    FORCED_DISABLE_FORCED_OPERATION     事件0下发送退出强制功能命令
                                                    FORCED_ENABLE_FORCED_ON_OPERATION   事件0下发送强制ON命令
                                                    FORCED_ENABLE_FORCED_OFF_OPERATION  事件0下发送强制OFF命令
    BYTE    ucForcedOp1;                            EVENT1下强制功能选项
                                                    FORCED_NO_COMMAND                   事件1下None强制功能命令
                                                    FORCED_DISABLE_FORCED_OPERATION     事件1下发送退出强制功能命令
                                                    FORCED_ENABLE_FORCED_ON_OPERATION   事件1下发送强制ON命令
                                                    FORCED_ENABLE_FORCED_OFF_OPERATION  事件1下发送强制OFF命令 
    WORD16 wEvt0DlyTm;                              EVENT0延时发送时间，取值范围 0~65535s
    WORD16 wEvt1DlyTm;                              EVENT1延时发送时间，取值范围 0~65535s                                  
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* 通讯对象的通讯对象号码    */
    BYTE   ucForcedOp0;                            /* EVENT0下强制功能选项      */
    BYTE   ucForcedOp1;                            /* EVENT1下强制功能选项      */
    WORD16 wEvt0DlyTm;                             /* EVENT0延时发送时间        */
    WORD16 wEvt1DlyTm;                             /* EVENT1延时发送时间        */
}T_FORCED_CO_FUNC_PARA;

/****************************************************
* 结构名：T_FORCED_CHANNEL_PARA;
* 描述：  强制控制命令通道的参数
* 参数：
    BYTE   ucChnlNo;                                开关通道号,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    注：一个产品中的输入通道号要连续。
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;           按键使能通讯对象参数 
    T_INPUT_CH_DRIVER_PARA  tChannelPara;           通道按键参数                 
    T_FORCED_CO_FUNC_PARA   tForcedCoPara;          强制通讯对象的参数            
         
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* 输入通道号,从1开始          */
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;        /* 按键使能通讯对象参数        */
    T_INPUT_CH_DRIVER_PARA  tChannelPara;        /* 通道按键参数                */
    T_FORCED_CO_FUNC_PARA   tForcedCoPara;       /* 强制通讯对象的参数          */
}T_FORCED_CHANNEL_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                 通用通道                                   */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* 结构名：T_INOPERATION_CO_FUNC_PARA;
* 描述：  设备通用通道工作指示通讯对象参数
* 参数：
    BYTE    ucCoNo;                             通讯对象的通讯对象号码   
    BYTE    ucInOpOption;                       工作指示报文选项
                                                GENERAL_NO_IN_OPERATION  不开启工作指示报文
                                                GENERAL_PERIODLY_SEND_0  循环发"0"
                                                GENERAL_PERIODLY_SEND_1  循环发"1"
    WORD16  wInOpPd;                            工作指示周期上发时间，取值范围 1~65535                                
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                                 /* 通讯对象的通讯对象号码    */
    BYTE    ucInOpOption;                           /* 工作指示报文选项          */
    WORD16  wInOpPd;                                /* 工作指示周期上发时间      */
}T_INOPERATION_CO_FUNC_PARA;

/****************************************************
* 结构名：T_ALLCONTROL_CO_FUNC_PARA;
* 描述：  设备通用通道全控使能通讯对象参数
* 参数：
    BYTE    ucCoNo;                             通讯对象的通讯对象号码   
    BYTE    ucAllCtrlOption;                    输出全控是否使能
                                                GENERAL_ALL_CONTROL_DISABLE   不使能输出全控功能
                                                GENERAL_ALL_CONTROL_ENABLE    使能输出全控功能                                        
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                                 /* 通讯对象的通讯对象号码    */
    BYTE    ucAllCtrlOption;                        /* 输出全控是否使能          */
}T_ALLCONTROL_CO_FUNC_PARA;

/****************************************************
* 结构名：T_GENERAL_CHANNEL_PARA;
* 描述：  通用通道的参数
* 参数：
    WORD16                     wPwrUpDelay;             上电延时工作时间,取值范围 2~65535s    
    BYTE                       ucTeleLmtEn;             是否使能报文限制
                                                        GENERAL_TELEGRAM_LIMIT_DISABLE  不使能报文限制
                                                        GENERAL_TELEGRAM_LIMIT_ENABLE   使能报文限制
    BYTE                       ucTeleLmtNum;            报文限制数量，取值范围 0~255
    BYTE                       ucTeleLmtPd;             报文限制周期
                                                        GENERAL_LIMIT_TIME_50MS    报文限制周期为50ms                                                       
                                                        GENERAL_LIMIT_TIME_200MS   报文限制周期为200ms
                                                        GENERAL_LIMIT_TIME_500MS   报文限制周期为500ms
                                                        GENERAL_LIMIT_TIME_1000MS  报文限制周期为1s
                                                        GENERAL_LIMIT_TIME_5000MS  报文限制周期为5s
                                                        GENERAL_LIMIT_TIME_10000MS 报文限制周期为10s
                                                        GENERAL_LIMIT_TIME_30000MS 报文限制周期为30s
                                                        GENERAL_LIMIT_TIME_60000MS 报文限制周期为1min
    T_INOPERATION_CO_FUNC_PARA tInOpCoPara;             工作指示通讯对象的参数         
         
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    WORD16                     wPwrUpDelay;        /* 上电延时工作时间       */
    BYTE                       ucTeleLmtEn;        /* 是否使能报文限制       */
    BYTE                       ucTeleLmtNum;       /* 报文限制数量           */
    BYTE                       ucTeleLmtPd;        /* 报文限制周期           */
    T_INOPERATION_CO_FUNC_PARA tInOpCoPara;        /* 工作指示通讯对象的参数 */
    T_ALLCONTROL_CO_FUNC_PARA  tAllCtrlPara;       /* 输出全控通讯对象的参数 */
}T_GENERAL_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                 输出通道                                   */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************     
* 结构名：T_OUTPUT_CO_FUNC_PARA;
* 描述：  输出通讯对象参数
* 参数：
    BYTE    ucCoNo;                             通讯对象的通讯对象号码   
    BYTE    ucOutputMode;                       输出模式
                                                OUTPUT_ONOFF_MODE              ON/OFF输出
                                                OUTPUT_FLASH_MODE              闪烁输出
    BYTE    ucOnOffPwrUp;                       上电后ON/OFF状态
                                                OUTPUT_INIT_OFF_STATE          上电后输出OFF
                                                OUTPUT_INIT_ON_STATE           上电后输出ON
    BYTE    ucOnOffMode;                        ON/OFF与通讯对象值关系
                                                OUTPUT_ON_RCV1_AND_OFF_RCV0   收到"1" 时输出ON, 收到"0" 时输出OFF
                                                OUTPUT_ON_RCV0_AND_OFF_RCV1   收到"0" 时输出ON, 收到"1" 时输出OFF
                                                OUTPUT_ON_RCV1_0_NO_OFF_CMD   收到"0"或"1"时输出ON，不输出OFF
    WORD16  wDelayOff;                          延时关闭输出时间，取值范围 0~65535s，0为不延时关闭
    BYTE    ucFlashPwrUp;                       上电后闪烁状态
                                                OUTPUT_INIT_STOP_FLASH         上电后不输出闪烁
                                                OUTPUT_INIT_START_FLASH        上电后输出闪烁
    BYTE    ucFlashMode;                        闪烁启停与通讯对象值关系
                                                OUTPUT_START_RCV1_AND_STOP_RCV0      收到"1" 时输出闪烁, 收到"0" 时停止闪烁
                                                OUTPUT_START_RCV0_AND_STOP_RCV1      收到"0" 时输出闪烁, 收到"1" 时停止闪烁
                                                OUTPUT_START_RCV1_0_AND_NO_STOP_CMD  收到"0"或"1"时输出闪烁，不停止闪烁
    WORD16  wFlashPeriod;                       输出闪烁周期，取值范围 0~65535ms
    WORD16  wFlashCount;                        输出闪烁次数，取值范围 0~65535，0为持续闪烁                                
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                             /* 通讯对象的通讯对象号码         */
    BYTE    ucOutputMode;                       /* 开关输出/闪烁输出              */
    BYTE    ucOnOffPwrUp;                       /* 上电后开关输出状态             */
    BYTE    ucOnOffMode;                        /* ON/OFF与通讯对象值关系         */
    WORD16  wDelayOff;                          /* 延时关闭输出时间               */
    BYTE    ucFlashPwrUp;                       /* 上电后闪烁输出状态             */
    BYTE    ucFlashMode;                        /* 闪烁启停与通讯对象值关系       */
    WORD16  wFlashPeriod;                       /* 输出闪烁周期                   */
    WORD16  wFlashCount;                        /* 输出闪烁次数                   */
}T_OUTPUT_CO_FUNC_PARA;

/****************************************************
* 结构名：T_OUTPUT_CHANNEL_PARA;
* 描述：  输出通道的参数
* 参数：
    BYTE   ucChnlNo;                                开关通道号,1-6 
                                                    OUTPUT_CHANNEL_1
                                                    OUTPUT_CHANNEL_2
                                                    OUTPUT_CHANNEL_3
                                                    OUTPUT_CHANNEL_4
                                                    OUTPUT_CHANNEL_5
                                                    OUTPUT_CHANNEL_6
                                                    OUTPUT_CHANNEL_7
                                                    注：一个产品中的输入通道号要连续。          
    OUTPUT_FUNC             fpOutputOp;             输出操作函数指针                
    T_OUTPUT_CO_FUNC_PARA   tOutputCoPara;          输出通讯对象的参数              
* 作者：      
* Modified History：
*  2014-7-6        新增结构；
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* 输入通道号,从1开始          */
    OUTPUT_FUNC             fpOutputOp;          /* 输出操作函数指针            */       
    T_OUTPUT_CO_FUNC_PARA   tOutputCoPara;       /* 输出通讯对象的参数          */
}T_OUTPUT_CHANNEL_PARA;



#ifdef __cplusplus
}
#endif

#endif /* _APP_COMMON_ */




