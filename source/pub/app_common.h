/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��app_common.h
* FileIdentifier��None
* Abstract �����ļ�ΪӦ����ص�ͷ�ļ����塣
* Other Description��
* Current Version��V1.00
* Author��      
* Completed Date��2013��7��24��
*    
* Modified History1��
*        Modified Date��2013��7��24��
*        Version Number��V1.00
*        Modified Person��      
*        Modified part��Add new public definition.
******************************************************************************/

#ifndef _APP_COMMON_
#define _APP_COMMON_

#ifdef __cplusplus
extern "C" {
#endif

/***************** �궨�� *****************************************************/
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

/* ͨ�������¼����壬��Ҫ�޸��¼������롣 */
#define INPUT_EVENT_NONE          0x55              /* None�¼�����                        */
#define INPUT_EVENT_0             0x00              /* �̰��¼�������ʹ�ܣ�/�̰������¼� */
#define INPUT_EVENT_1             0x01              /* �̰��ͷ��¼�/�����¼�������ʹ�ܣ� */
#define INPUT_EVENT_2             0x02              /* �����ͷ��¼�������ʹ�ܣ�          */

/* ͨ�������¼����壬��Ҫ�޸��¼������롣 */
#define OUTPUT_LED_OFF           KNX_APP_OFF        /* �ܽ������OFF״̬ */
#define OUTPUT_LED_ON            KNX_APP_ON         /* �ܽ������ON״̬  */

/* ���빦�ܵĲ������� */
#define INPUT_FILTER_MIN_TIME               20      /* ������Сʱ��20ms   */
#define INPUT_FILTER_MAX_TIME               1000    /* �������ʱ��1000ms */
#define INPUT_HOLDING_PRESS_ENABLE          1       /* ʹ�ܳ�������       */
#define INPUT_HOLDING_PRESS_DISABLE         0       /* �رճ�������       */
#define INPUT_CONTACT_TYPE_OPEN             0       /* ���봥��Ϊ�������� */
#define INPUT_CONTACT_TYPE_CLOSE            1       /* ���봥��Ϊ�������� */
#define INPUT_HOLDING_PRESS_MIN_TIME        200     /* ����ʶ�����ʱ��   */
#define INPUT_HOLDING_PRESS_MAX_TIME        65535   /* ����ʶ���ʱ��   */

/* ������������壬�˴��������豸��д������������Ҫ���ǰ��ºͳ���/������Ĺ�ϵ�� */
#define INPUT_CHANNEL_OPEN                  INPUT_CONTACT_TYPE_OPEN        /* CPU�ܽż�⵽���������ź� */
#define INPUT_CHANNEL_CLOSE                 INPUT_CONTACT_TYPE_CLOSE       /* CPU�ܽ�û�м�⵽�����ź� */
/* ���������źŶ��������ͨ�϶���Ķ�Ӧ��Ҫ��Ӧ���и���ʵ��������ö�Ӧ */

/************ ͨ�ò��������� ********************/
#define INPUT_CHANNEL_ENABLE                1       /* ʹ��ͨ��         */
#define INPUT_CHANNEL_DISABLE               0       /* ����ͨ��         */
#define INPUT_PWR_START_CHK_EN              1       /* �ϵ�״̬ɨ��ʹ�� */
#define INPUT_PWR_START_CHK_DIS             0       /* �ϵ�״̬ɨ����� */
#define INPUT_PWR_START_BTN_EN              1       /* �ϵ簴��ʹ��     */
#define INPUT_PWR_START_BTN_DIS             0       /* �ϵ簴������     */

#define INPUT_FUNC_NONE_CMD                 0       /* ����ͨ��None��������   */   
#define INPUT_FUNC_ONOFF_CMD                1       /* ����ͨ�����ؿ������� */    
#define INPUT_FUNC_DIM_CMD                  2       /* ����ͨ������������� */    
#define INPUT_FUNC_SHUTTER_CMD              3       /* ����ͨ�������������� */    
#define INPUT_FUNC_FORCED_CMD               4       /* ����ͨ��ǿ�ƿ������� */    
#define INPUT_FUNC_SCENE_CMD                5       /* ����ͨ�������������� */    
#define INPUT_FUNC_VALUE_CMD                6       /* ����ͨ����ֵ�������� */        

/************ ���ع��ܲ������� ******************/
#define SWITCH_CO_FUNC_EN                   INPUT_CHANNEL_ENABLE    /* ʹ�ܿ��ع��ܵ�ͨѶ������ */
#define SWITCH_CO_FUNC_DISABLE              INPUT_CHANNEL_DISABLE   /* ʹ�ܿ��ع��ܵ�ͨѶ������ */
#define SWITCH_FUNC_NOACTION                0                       /* ���ع���None����             */
#define SWITCH_FUNC_ON                      1                       /* ����On����                 */
#define SWITCH_FUNC_OFF                     2                       /* ����Off����                */
#define SWITCH_FUNC_TOGGLE                  3                       /* ����Toggle����             */
#define SWITCH_PERIOD_FUNC_STOP             4                       /* �����Ϸ�ֹͣ               */
#define SWITCH_FUNC_END                     5                       /* ͨѶ�����ܽ�������       */

#define SWITCH_PERIOD_FUNC_DISABLE          KNX_APP_OFF             /* �ر��������͹���           */
#define SWITCH_PERIOD_FUNC_ENABLE           KNX_APP_ON              /* ʹ���������͹���           */
#define SWITCH_PERIOD_FUNC_OFF_TRIGGER      1                       /* OFF�����������͹���        */
#define SWITCH_PERIOD_FUNC_ON_TRIGGER       2                       /* ON�����������͹���         */
#define SWITCH_PERIOD_FUNC_ALWAYS_TRIGGER   3                       /* On/Off�����������͹���     */

/************ ���⹦�ܲ������� ******************/
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

/************ �������ܲ������� ******************/
#define SHUTTER_1_BUTTON_MODE               0                       /* 1 button mode(Alternating) */
#define SHUTTER_2_BUTTON_UP_MODE            1                       /* 2 buttons up mode          */
#define SHUTTER_2_BUTTON_DOWN_MODE          2                       /* 2 buttons down mode        */
#define SHUTTER_RELEASE_STOP_DISABLE        0                       /* Disable "release stop"     */
#define SHUTTER_RELEASE_STOP_ENABLE         1                       /* Enable "release stop"      */

/************ �������ܲ������� ******************/
#define  SCENE_FUNC_DISABLE                 0                       /* Disable scene function     */
#define  SCENE_FUNC_ENABLE                  1                       /* Enable scene function      */
#define  SCENE_CALL_A_SCENE                 0                       /* Call a scene               */
#define  SCENE_STORE_A_SCENE                1                       /* Store a scene              */

/************ ��ֵ���ܲ������� ******************/
#define VALUE_NO_VALUE_COMMAND              0                       /* Send no command            */
#define VALUE_1_BYTE_INT_VALUE              1                       /* Send 1 byte int value      */
#define VALUE_2_BYTE_INT_VALUE              2                       /* Send 2 byte int value      */
#define VALUE_2_BYTE_FLOAT_VALUE            3                       /* Send 2 byte float value    */

/************ ǿ�ƹ��ܲ������� ******************/
 #define FORCED_NO_COMMAND                  0                       /* Send no command                          */
 #define FORCED_DISABLE_FORCED_OPERATION    1                       /* Send disable forced operation command    */
 #define FORCED_ENABLE_FORCED_ON_OPERATION  2                       /* Send enable forced ON operation command  */
 #define FORCED_ENABLE_FORCED_OFF_OPERATION 3                       /* Send enable forced OFF operation command */

/************ ���ͨ�����ܲ������� ******************/
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

/************ ͨ��ͨ�����ܲ������� ******************/
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


/*************** ���ݽṹ���� **************************************************/
typedef BYTE (*INPUT_CHECK_FUNC)(BYTE ucChnNo);          /* ������⺯�����Ͷ��� */
typedef void (*OUTPUT_FUNC)(BYTE ucChnNo, BYTE ucOnOff);  /* �ܽ�����������Ͷ��� */
/****************************************************
* �ṹ����T_BTN_EN_CO_FUNC_PARA;
* ������  ����������ͨ����������ʹ��ͨѶ���������
* ������
    BYTE    ucCoNo;                               ͨѶ�����           
* ���ߣ�      
* Modified History��
*  2014-7-8        �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                            /* ͨѶ�����           */
}T_BTN_EN_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_INPUT_CH_DRIVER_PARA;
* ������  ����������ͨ����������ETS���ò�����
* ������
    BYTE    ucButtonEn;            INPUT_CHANNEL_DISABLE        �������ڲ�ʹ��״̬
                                   INPUT_CHANNEL_ENABLE         ��������ʹ��״̬  
    BYTE    ucPwrStartChk;         INPUT_PWR_START_CHK_EN       ����ͨ���ϵ�״̬���
                                   INPUT_PWR_START_CHK_DIS
    BYTE    ucLongPressEn;         INPUT_HOLDING_PRESS_DISABLE  �����ֳ��̰�
                                   INPUT_HOLDING_PRESS_ENABLE   ���ֳ��̰�
    BYTE    ucContactType;         INPUT_CONTACT_TYPE_OPEN      ������������
                                   INPUT_CONTACT_TYPE_CLOSE     ���մ�������
    WORD16  wDebounceTime;         INPUT_FILTER_MIN_TIME        ��������ʱ����С20ms
                                   INPUT_FILTER_MAX_TIME        ��������ʱ�����1000ms
    WORD16  wTimeForLongPress;     INPUT_HOLDING_PRESS_MIN_TIME ��������ʱ��
                                   INPUT_HOLDING_PRESS_MAX_TIME
    INPUT_CHECK_FUNC fpKeyCheckOp; ����ͨ����⺯��
* ���ߣ�        
* Modified History��
*  2014-7-6          �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucButtonEn;                        /* �����Ƿ�ʹ��         */
    BYTE    ucPwrStartChk;                     /* ����ͨ���ϵ�״̬��� */
    BYTE    ucLongPressEn;                     /* �����Ƿ�ʹ��         */
    BYTE    ucContactType;                     /* �����봥������     */
    WORD16  wTimeForLongPress;                 /* ��������ʱ��         */
    WORD16  wDebounceTime;                     /* ��������ʱ��         */
    INPUT_CHECK_FUNC fpKeyCheckOp;             /* ����ͨ����⺯��     */
}T_INPUT_CH_DRIVER_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   ����                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* �ṹ����T_SWITCH_CO_FUNC_PARA;
* ������  ���ع��ܵĿ���ͨѶ���������
* ������
          BYTE    ucFuncEn          ͨѶ����Ŀ��ع����Ƿ�ʹ�� 
                                    ȡֵ��
                                    SWITCH_CO_FUNC_EN
                                    SWITCH_CO_FUNC_DISABLE
          BYTE    ucPressFunc       ͨѶ����Ŀ��ع�������  
                                    ȡֵ��
                                    SWITCH_FUNC_NOACTION
                                    SWITCH_FUNC_ON
                                    SWITCH_FUNC_OFF
                                    SWITCH_FUNC_TOGGLE
                                    SWITCH_PERIOD_FUNC_STOP
          BYTE    ucReleaseFunc     ͨѶ����Ŀ��ع�������  
                                    ȡֵ��
                                    SWITCH_FUNC_NOACTION
                                    SWITCH_FUNC_ON
                                    SWITCH_FUNC_OFF
                                    SWITCH_FUNC_TOGGLE
                                    SWITCH_PERIOD_FUNC_STOP
          WORD16  wEvt0DlyTm        �¼�0��ͨѶ����Ŀ���������ʱ����ʱ��MS
                                    0-65535Ms
          WORD16  wEvt1DlyTm        �¼�1��ͨѶ����Ŀ���������ʱ����ʱ��MS
                                    0-65535Ms
* ���ߣ�        
* Modified History��
*  2014-7-6          �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                             /* ͨѶ�����ͨѶ�������       */
    BYTE    ucFuncEn;                           /* ͨѶ����Ŀ��ع����Ƿ�ʹ��   */
    BYTE    ucPressFunc;                        /* ����ʱͨѶ����Ŀ��ع������� */
    BYTE    ucReleaseFunc;                      /* �ͷ�ʱͨѶ����Ŀ��ع������� */
    WORD16  wEvt0DlyTm;                         /* EVENT0��ʱ����ʱ��           */
    WORD16  wEvt1DlyTm;                         /* EVENT1��ʱ����ʱ��           */
}T_SWITCH_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_SWITCH_CHANNEL_PARA;
* ������  ���ع��ܵĿ���ͨѶ���������
* ������
    BYTE   ucChnlNo;                                ����ͨ����,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    ע��һ����Ʒ�е�����ͨ����Ҫ������
    BYTE                   ucPeriodFuncPara         �������͹��ܲ�����ȡֵ���£�
                                                    SWITCH_PERIOD_FUNC_DISABLE
                                                    SWITCH_PERIOD_FUNC_ON_TRIGGER
                                                    SWITCH_PERIOD_FUNC_OFF_TRIGGER
                                                    SWITCH_PERIOD_FUNC_ALWAYS_TRIGGER
    WORD16                 wPeriodFuncTime;         �������͹���ʱ��1-65535S 
    T_BTN_EN_CO_FUNC_PARA  tBtnEnCoPara;            ����ʹ��ͨѶ�������     
    T_INPUT_CH_DRIVER_PARA tChannelPara;            ͨ������                 
    T_SWITCH_CO_FUNC_PARA  tSwitchCo1Para;          ����ͨѶ����1�Ĳ���   
    T_SWITCH_CO_FUNC_PARA  tSwitchCo2Para;          ����ͨѶ����1�Ĳ���   
    T_SWITCH_CO_FUNC_PARA  tSwitchCo3Para;          ����ͨѶ����1�Ĳ���   
* ���ߣ�      
* Modified History��
*  2014-4-30        �����ṹ��
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* ����ͨ����,��1��ʼ       */
    BYTE                    ucPeriodFuncPara;    /* �������͹��ܲ���         */
    WORD16                  wPeriodFuncTime;     /* �������͹���ʱ��1-65535S */
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;        /* ����ʹ��ͨѶ�������     */
    T_INPUT_CH_DRIVER_PARA  tChannelPara;        /* ͨ������                 */
    T_SWITCH_CO_FUNC_PARA   tSwitchCo1Para;      /* ����ͨѶ����1�Ĳ���      */
    T_SWITCH_CO_FUNC_PARA   tSwitchCo2Para;      /* ����ͨѶ����2�Ĳ���      */
    T_SWITCH_CO_FUNC_PARA   tSwitchCo3Para;      /* ����ͨѶ����3�Ĳ���      */
}T_SWITCH_CHANNEL_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   ����                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************                        
* �ṹ����T_DIM_SWITCH_CO_FUNC_PARA;
* ������  ���⹦�ܵĿ���ͨѶ���������
* ������
    BYTE   ucCoNo;                                  ͨѶ�����ͨѶ�������
    BYTE   ucDimSwichFunc;                          ����ѡ�ȡֵ����:
                                                    DIM_SWITCH_NO_ACTION   None���ع���
                                                    DIM_SWITCH_ON          ��
                                                    DIM_SWTICH_OFF         �ر�
                                                    DIM_SWITCH_TOGGLE      ���濪��
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ������� */
    BYTE   ucDimSwichFunc;                         /* ����ѡ��               */
}T_DIM_SWITCH_CO_FUNC_PARA;

/****************************************************                        
* �ṹ����T_DIM_CO_FUNC_PARA;
* ������  ���⹦�ܵĵ���ͨѶ���������
* ������
    BYTE   ucCoNo;                                  ͨѶ�����ͨѶ�������
    BYTE   ucDimFunc;                               ����ѡ�ȡֵ����:
                                                    DIM_BRIGHT             ����
                                                    DIM_DARK               ����
                                                    DIM_ALTERNATING        �������
    BYTE   ucDimMode;                               ����ģʽ,ȡֵ����:
                                                    DIM_START_STOP_MODE    ��ͣ����ģʽ
                                                    DIM_STEP_MODE          ��������ģʽ
    BYTE   ucDimStep;                               ���ⲽ��
                                                    DIM_STEP_1_56_PERCENT  1.56%���� 
                                                    DIM_STEP_3_13_PERCENT  3.13%����   
                                                    DIM_STEP_6_25_PERCENT  6.25%����   
                                                    DIM_STEP_12_5_PERCENT  12.5%����   
                                                    DIM_STEP_25_0_PERCENT  25.0%����   
                                                    DIM_STEP_50_0_PERCENT  50.0%����   
                                                    DIM_STEP_100_0_PERCENT 100.0%����  
    WORD16 wDimStepPd;                              �����������ڣ�ȡֵ��Χ0~65535ms                                                   
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ������� */
    BYTE   ucDimFunc;                              /* ����ѡ��               */
    BYTE   ucDimMode;                              /* ����ģʽ               */
    BYTE   ucDimStep;                              /* ���ⲽ��               */
    WORD16 wDimStepPd;                             /* ������������           */
}T_DIM_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_DIM_CHANNEL_PARA;
* ������  ��������ͨ���Ĳ���
* ������
    BYTE                      ucChnlNo;               ����ͨ����,1-6 
                                                      INPUT_CHANNEL_1
                                                      INPUT_CHANNEL_2
                                                      INPUT_CHANNEL_3
                                                      INPUT_CHANNEL_4
                                                      INPUT_CHANNEL_5
                                                      INPUT_CHANNEL_6
                                                      ע��һ����Ʒ�е�����ͨ����Ҫ������
    T_BTN_EN_CO_FUNC_PARA     tBtnEnCoPara;           ����ʹ��ͨѶ�������  
    T_INPUT_CH_DRIVER_PARA    tChannelPara;           ͨ����������                 
    T_DIM_SWITCH_CO_FUNC_PARA tSwitchCoPara;          ����ͨѶ����Ĳ���    
    T_DIM_CO_FUNC_PARA        tDimCoPara;             ����ͨѶ����Ĳ���       
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE                      ucChnNo;             /* ����ͨ����,��1��ʼ       */
    T_BTN_EN_CO_FUNC_PARA     tBtnEnCoPara;        /* ����ʹ��ͨѶ�������     */
    T_INPUT_CH_DRIVER_PARA    tChannelPara;        /* ͨ����������             */
    T_DIM_SWITCH_CO_FUNC_PARA tSwitchCoPara;       /* ����ͨѶ����Ĳ���       */
    T_DIM_CO_FUNC_PARA        tDimCoPara;          /* ����ͨѶ����Ĳ���       */
}T_DIM_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   ����                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* �ṹ����T_SHUTTER_CO_FUNC_PARA;
* ������  ������������Ĵ���ͨѶ����(�ƶ���ֹͣ)������
* ������
    BYTE    ucCoNo;                             ͨѶ�����ͨѶ�������
    BYTE    ucShutterMode;                      ��������ģʽ
                                                SHUTTER_1_BUTTON             ����ģʽ:����-> ͣ/���µ��Ƕ� -> ���� ->ͣ/���ϵ��Ƕ�
                                                SHUTTER_2_BUTTON_UP          ˫��ģʽ:�̰�=ͣ/���ϵ����Ƕȣ�����=�����ƶ�
                                                SHUTTER_2_BUTTON_DOWN        ˫��ģʽ:�̰�=ͣ/���µ����Ƕȣ�����=�����ƶ�
    BYTE    ucShutterReleaseStop;               �����ͷ��Ƿ�ֹͣ 
                                                SHUTTER_RELEASE_STOP_DISABLE �����ͷŲ�ֹͣ
                                                SHUTTER_RELEASE_STOP_ENABLE  �����ͷ�ֹͣ                                               
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ������� */
    BYTE   ucShutterMode;                          /* ��������ģʽ           */
    BYTE   ucShutterReleaseStop;                   /* �����ͷ��Ƿ�ֹͣ       */
}T_SHUTTER_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_POSITION_LIMIT_CO_FUNC_PARA;
* ������  ������������������λͨѶ�������
* ������
    BYTE    ucCoNo;                             ͨѶ�����ͨѶ�������                                             
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ������� */
}T_POSITION_LIMIT_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_SHUTTER_CHANNEL_PARA;
* ������  ������������ͨ���Ĳ���
* ������
    BYTE   ucChnlNo;                                      ����ͨ����,1-6 
                                                          INPUT_CHANNEL_1
                                                          INPUT_CHANNEL_2
                                                          INPUT_CHANNEL_3
                                                          INPUT_CHANNEL_4
                                                          INPUT_CHANNEL_5
                                                          INPUT_CHANNEL_6
                                                          ע��һ����Ʒ�е�����ͨ����Ҫ������
    T_BTN_EN_CO_FUNC_PARA         tBtnEnCoPara;           ����ʹ��ͨѶ�������  
    T_INPUT_CH_DRIVER_PARA        tChannelPara;           ͨ����������                 
    T_SHUTTER_CO_FUNC_PARA        tUpDownCoPara;          �����ƶ�ͨѶ����Ĳ���      
    T_SHUTTER_CO_FUNC_PARA        tStopAdjCoPara;         ֹͣ/�Ƕȵ���ͨѶ����Ĳ��� 
    T_POSITION_LIMIT_CO_FUNC_PARA tUpLimitCoPara;         ����λͨѶ����Ĳ���        
    T_POSITION_LIMIT_CO_FUNC_PARA tLowLimitCoPara;        ����λͨѶ����Ĳ���            
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE                          ucChnNo;             /* ����ͨ����,��1��ʼ          */
    T_BTN_EN_CO_FUNC_PARA         tBtnEnCoPara;        /* ����ʹ��ͨѶ�������        */
    T_INPUT_CH_DRIVER_PARA        tChannelPara;        /* ͨ����������                */
    T_SHUTTER_CO_FUNC_PARA        tUpDownCoPara;       /* �����ƶ�ͨѶ����Ĳ���      */
    T_SHUTTER_CO_FUNC_PARA        tStopAdjCoPara;      /* ֹͣ/�Ƕȵ���ͨѶ����Ĳ��� */
    T_POSITION_LIMIT_CO_FUNC_PARA tUpLimitCoPara;      /* ����λͨѶ����Ĳ���        */
    T_POSITION_LIMIT_CO_FUNC_PARA tLowLimitCoPara;     /* ����λͨѶ����Ĳ���        */
}T_SHUTTER_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   ����                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* �ṹ����T_SCENE_CO_FUNC_PARA;
* ������  �������������ͨѶ�������
* ������
    BYTE    ucCoNo;                             ͨѶ�����ͨѶ�������   
    BYTE    ucSceneEn0;                         �Ƿ�����EVENT 0�³�������
                                                SCENE_FUNC_DISABLE         ������EVENT 0�³�������
                                                SCENE_FUNC_ENABLE          ����EVENT 0�³�������   
    BYTE    ucSceneEn1;                         �Ƿ�����EVENT 1�³�������
                                                SCENE_FUNC_DISABLE         ������EVENT 1�³�������
                                                SCENE_FUNC_ENABLE          ����EVENT 1�³�������
    BYTE    ucSceneCallStore0;                  EVNET0����Ϊ����/���泡��
                                                SCENE_CALL_A_SCENE         EVNET0����Ϊ���ó���
                                                SCENE_STORE_A_SCENE        EVNET0����Ϊ���泡��
    BYTE    ucSceneCallStore1;                  EVNET1����Ϊ����/���泡��
                                                SCENE_CALL_A_SCENE         EVNET1����Ϊ���ó���
                                                SCENE_STORE_A_SCENE        EVNET1����Ϊ���泡��
    BYTE    ucSceneNum0;                        ������ for EVENT 0��ȡֵ��Χ 0~63
    BYTE    ucSceneNum1;                        ������ for EVENT 1��ȡֵ��Χ 0~63    
    WORD16 wEvt0DlyTm;                          EVENT0��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s  
    WORD16 wEvt1DlyTm;                          EVENT1��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s                                    
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ�������    */
    BYTE   ucSceneEn0;                             /* �Ƿ�����EVENT 0�³������� */
    BYTE   ucSceneEn1;                             /* �Ƿ�����EVENT 1�³������� */
    BYTE   ucSceneCallStore0;                      /* EVNET0����Ϊ����/���泡�� */
    BYTE   ucSceneCallStore1;                      /* EVNET1����Ϊ����/���泡�� */
    BYTE   ucSceneNum0;                            /* EVENT0������              */
    BYTE   ucSceneNum1;                            /* EVENT1������              */
    WORD16 wEvt0DlyTm;                             /* EVENT0��ʱ����ʱ��        */
    WORD16 wEvt1DlyTm;                             /* EVENT1��ʱ����ʱ��        */
}T_SCENE_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_SCENE_CHANNEL_PARA;
* ������  ������������ͨ���Ĳ���
* ������
    BYTE   ucChnlNo;                                ����ͨ����,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    ע��һ����Ʒ�е�����ͨ����Ҫ������
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;           ����ʹ��ͨѶ�������  
    T_INPUT_CH_DRIVER_PARA  tChannelPara;           ͨ����������                 
    T_SCENE_CO_FUNC_PARA    tSceneCoPara;           ����ͨѶ����Ĳ���      
         
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* ����ͨ����,��1��ʼ          */
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;        /* ����ʹ��ͨѶ�������        */
    T_INPUT_CH_DRIVER_PARA  tChannelPara;        /* ͨ����������                */
    T_SCENE_CO_FUNC_PARA    tSceneCoPara;        /* ����ͨѶ����Ĳ���          */
}T_SCENE_CHANNEL_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   ��ֵ                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* �ṹ����T_1_BYTE_VALUE_CO_FUNC_PARA;
* ������  ��ֵ��������1byte��ֵͨѶ�������
* ������
    BYTE   ucCoNo;                              ͨѶ�����ͨѶ�������   
    BYTE   ucValue0;                            EVENT0����ֵ��ȡֵ��Χ 0~255              
    BYTE   ucValue1;                            EVENT1����ֵ��ȡֵ��Χ 0~255                 
    WORD16 wEvt0DlyTm;                          EVENT0��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s
    WORD16 wEvt1DlyTm;                          EVENT1��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s                                  
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ�������    */
    BYTE   ucValue0;                               /* EVENT0����ֵ              */
    BYTE   ucValue1;                               /* EVENT1����ֵ              */
    WORD16 wEvt0DlyTm;                             /* EVENT0��ʱ����ʱ��        */
    WORD16 wEvt1DlyTm;                             /* EVENT1��ʱ����ʱ��        */
}T_1_BYTE_VALUE_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_2_BYTE_VALUE_CO_FUNC_PARA;
* ������  ��ֵ��������2byte��ֵͨѶ�������
* ������
    BYTE    ucCoNo;                             ͨѶ�����ͨѶ�������   
    WORD16  wValue0;                            EVENT0��������ֵ��ȡֵ��Χ 0~65535              
    WORD16  wValue1;                            EVENT1��������ֵ��ȡֵ��Χ 0~65535 
    WORD16  wValueBase0;                        EVENT0�¸����͵�����ֵ��ȡֵ��Χ 0~4095    
    WORD16  wValueBase1;                        EVENT1�¸����͵�����ֵ��ȡֵ��Χ 0~4095   
    BYTE    ucValueExp0;                        EVENT0�¸�����ָ����ֵ��ȡֵ��Χ 0~15     
    BYTE    ucValueExp1;                        EVENT1�¸�����ָ����ֵ��ȡֵ��Χ 0~15                  
    WORD16  wEvt0DlyTm;                         EVENT0��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s
    WORD16  wEvt1DlyTm;                         EVENT1��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s                                  
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ�������    */
    WORD16 wValue0;                                /* EVENT0��������ֵ          */
    WORD16 wValue1;                                /* EVENT1��������ֵ          */
    WORD16 wValueBase0;                            /* EVENT0�¸����͵�����ֵ    */ 
    WORD16 wValueBase1;                            /* EVENT1�¸����͵�����ֵ    */ 
    BYTE   ucValueExp0;                            /* EVENT0�¸�����ָ����ֵ    */ 
    BYTE   ucValueExp1;                            /* EVENT1�¸�����ָ����ֵ    */ 
    WORD16 wEvt0DlyTm;                             /* EVENT0��ʱ����ʱ��        */
    WORD16 wEvt1DlyTm;                             /* EVENT1��ʱ����ʱ��        */
}T_2_BYTE_VALUE_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_VALUE_CHANNEL_PARA;
* ������  ��ֵ��������ͨ���Ĳ���
* ������
    BYTE   ucChnlNo;                                ����ͨ����,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    ע��һ����Ʒ�е�����ͨ����Ҫ������
    BYTE   ucValueOpt0;                             EVENT0��ֵ����ѡ�� 
                                                    VALUE_NO_VALUE_COMMAND    �¼�0�²�������ֵ����
                                                    VALUE_1_BYTE_INT_VALUE    �¼�0�·���1BYTE������ֵ����
                                                    VALUE_2_BYTE_INT_VALUE    �¼�0�·���2BYTE������ֵ����
                                                    VALUE_2_BYTE_FLOAT_VALUE  �¼�0�·���2BYTE��������ֵ����    
    BYTE   ucValueOpt1;                             EVENT1��ֵ����ѡ�� 
                                                    VALUE_NO_VALUE_COMMAND    �¼�1�²�������ֵ����
                                                    VALUE_1_BYTE_INT_VALUE    �¼�1�·���1BYTE������ֵ����
                                                    VALUE_2_BYTE_INT_VALUE    �¼�1�·���2BYTE������ֵ����
                                                    VALUE_2_BYTE_FLOAT_VALUE  �¼�1�·���2BYTE��������ֵ���� 
    T_BTN_EN_CO_FUNC_PARA       tBtnEnCoPara;       ����ʹ��ͨѶ�������  
    T_INPUT_CH_DRIVER_PARA      tChannelPara;       ͨ����������                      
    T_2_BYTE_VALUE_CO_FUNC_PARA t1ByteValueCoPara;  1BYTE��ֵͨѶ����Ĳ���     
    T_2_BYTE_VALUE_CO_FUNC_PARA t2ByteValueCoPara;  2BYTE��ֵͨѶ����Ĳ���              
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE                        ucChnNo;             /* ����ͨ����,��1��ʼ          */
    BYTE                        ucValueOpt0;         /* EVENT0��ֵ����ѡ��          */
    BYTE                        ucValueOpt1;         /* EVENT1��ֵ����ѡ��          */
    T_BTN_EN_CO_FUNC_PARA       tBtnEnCoPara;        /* ����ʹ��ͨѶ�������        */
    T_INPUT_CH_DRIVER_PARA      tChannelPara;        /* ͨ����������                */
    T_1_BYTE_VALUE_CO_FUNC_PARA t1ByteValueCoPara;   /* 1BYTE��ֵͨѶ����Ĳ���     */
    T_2_BYTE_VALUE_CO_FUNC_PARA t2ByteValueCoPara;   /* 2BYTE��ֵͨѶ����Ĳ���     */
}T_VALUE_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                   ǿ��                                     */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* �ṹ����T_FORCED_CO_FUNC_PARA;
* ������  ǿ�ƿ�������ǿ��ͨѶ�������
* ������
    BYTE    ucCoNo;                                 ͨѶ�����ͨѶ�������   
    BYTE    ucForcedOp0;                            EVENT0��ǿ�ƹ���ѡ��
                                                    FORCED_NO_COMMAND                   �¼�0��Noneǿ�ƹ�������
                                                    FORCED_DISABLE_FORCED_OPERATION     �¼�0�·����˳�ǿ�ƹ�������
                                                    FORCED_ENABLE_FORCED_ON_OPERATION   �¼�0�·���ǿ��ON����
                                                    FORCED_ENABLE_FORCED_OFF_OPERATION  �¼�0�·���ǿ��OFF����
    BYTE    ucForcedOp1;                            EVENT1��ǿ�ƹ���ѡ��
                                                    FORCED_NO_COMMAND                   �¼�1��Noneǿ�ƹ�������
                                                    FORCED_DISABLE_FORCED_OPERATION     �¼�1�·����˳�ǿ�ƹ�������
                                                    FORCED_ENABLE_FORCED_ON_OPERATION   �¼�1�·���ǿ��ON����
                                                    FORCED_ENABLE_FORCED_OFF_OPERATION  �¼�1�·���ǿ��OFF���� 
    WORD16 wEvt0DlyTm;                              EVENT0��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s
    WORD16 wEvt1DlyTm;                              EVENT1��ʱ����ʱ�䣬ȡֵ��Χ 0~65535s                                  
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE   ucCoNo;                                 /* ͨѶ�����ͨѶ�������    */
    BYTE   ucForcedOp0;                            /* EVENT0��ǿ�ƹ���ѡ��      */
    BYTE   ucForcedOp1;                            /* EVENT1��ǿ�ƹ���ѡ��      */
    WORD16 wEvt0DlyTm;                             /* EVENT0��ʱ����ʱ��        */
    WORD16 wEvt1DlyTm;                             /* EVENT1��ʱ����ʱ��        */
}T_FORCED_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_FORCED_CHANNEL_PARA;
* ������  ǿ�ƿ�������ͨ���Ĳ���
* ������
    BYTE   ucChnlNo;                                ����ͨ����,1-6 
                                                    INPUT_CHANNEL_1
                                                    INPUT_CHANNEL_2
                                                    INPUT_CHANNEL_3
                                                    INPUT_CHANNEL_4
                                                    INPUT_CHANNEL_5
                                                    INPUT_CHANNEL_6
                                                    ע��һ����Ʒ�е�����ͨ����Ҫ������
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;           ����ʹ��ͨѶ������� 
    T_INPUT_CH_DRIVER_PARA  tChannelPara;           ͨ����������                 
    T_FORCED_CO_FUNC_PARA   tForcedCoPara;          ǿ��ͨѶ����Ĳ���            
         
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* ����ͨ����,��1��ʼ          */
    T_BTN_EN_CO_FUNC_PARA   tBtnEnCoPara;        /* ����ʹ��ͨѶ�������        */
    T_INPUT_CH_DRIVER_PARA  tChannelPara;        /* ͨ����������                */
    T_FORCED_CO_FUNC_PARA   tForcedCoPara;       /* ǿ��ͨѶ����Ĳ���          */
}T_FORCED_CHANNEL_PARA;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                 ͨ��ͨ��                                   */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************
* �ṹ����T_INOPERATION_CO_FUNC_PARA;
* ������  �豸ͨ��ͨ������ָʾͨѶ�������
* ������
    BYTE    ucCoNo;                             ͨѶ�����ͨѶ�������   
    BYTE    ucInOpOption;                       ����ָʾ����ѡ��
                                                GENERAL_NO_IN_OPERATION  ����������ָʾ����
                                                GENERAL_PERIODLY_SEND_0  ѭ����"0"
                                                GENERAL_PERIODLY_SEND_1  ѭ����"1"
    WORD16  wInOpPd;                            ����ָʾ�����Ϸ�ʱ�䣬ȡֵ��Χ 1~65535                                
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                                 /* ͨѶ�����ͨѶ�������    */
    BYTE    ucInOpOption;                           /* ����ָʾ����ѡ��          */
    WORD16  wInOpPd;                                /* ����ָʾ�����Ϸ�ʱ��      */
}T_INOPERATION_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_ALLCONTROL_CO_FUNC_PARA;
* ������  �豸ͨ��ͨ��ȫ��ʹ��ͨѶ�������
* ������
    BYTE    ucCoNo;                             ͨѶ�����ͨѶ�������   
    BYTE    ucAllCtrlOption;                    ���ȫ���Ƿ�ʹ��
                                                GENERAL_ALL_CONTROL_DISABLE   ��ʹ�����ȫ�ع���
                                                GENERAL_ALL_CONTROL_ENABLE    ʹ�����ȫ�ع���                                        
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                                 /* ͨѶ�����ͨѶ�������    */
    BYTE    ucAllCtrlOption;                        /* ���ȫ���Ƿ�ʹ��          */
}T_ALLCONTROL_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_GENERAL_CHANNEL_PARA;
* ������  ͨ��ͨ���Ĳ���
* ������
    WORD16                     wPwrUpDelay;             �ϵ���ʱ����ʱ��,ȡֵ��Χ 2~65535s    
    BYTE                       ucTeleLmtEn;             �Ƿ�ʹ�ܱ�������
                                                        GENERAL_TELEGRAM_LIMIT_DISABLE  ��ʹ�ܱ�������
                                                        GENERAL_TELEGRAM_LIMIT_ENABLE   ʹ�ܱ�������
    BYTE                       ucTeleLmtNum;            ��������������ȡֵ��Χ 0~255
    BYTE                       ucTeleLmtPd;             ������������
                                                        GENERAL_LIMIT_TIME_50MS    ������������Ϊ50ms                                                       
                                                        GENERAL_LIMIT_TIME_200MS   ������������Ϊ200ms
                                                        GENERAL_LIMIT_TIME_500MS   ������������Ϊ500ms
                                                        GENERAL_LIMIT_TIME_1000MS  ������������Ϊ1s
                                                        GENERAL_LIMIT_TIME_5000MS  ������������Ϊ5s
                                                        GENERAL_LIMIT_TIME_10000MS ������������Ϊ10s
                                                        GENERAL_LIMIT_TIME_30000MS ������������Ϊ30s
                                                        GENERAL_LIMIT_TIME_60000MS ������������Ϊ1min
    T_INOPERATION_CO_FUNC_PARA tInOpCoPara;             ����ָʾͨѶ����Ĳ���         
         
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    WORD16                     wPwrUpDelay;        /* �ϵ���ʱ����ʱ��       */
    BYTE                       ucTeleLmtEn;        /* �Ƿ�ʹ�ܱ�������       */
    BYTE                       ucTeleLmtNum;       /* ������������           */
    BYTE                       ucTeleLmtPd;        /* ������������           */
    T_INOPERATION_CO_FUNC_PARA tInOpCoPara;        /* ����ָʾͨѶ����Ĳ��� */
    T_ALLCONTROL_CO_FUNC_PARA  tAllCtrlPara;       /* ���ȫ��ͨѶ����Ĳ��� */
}T_GENERAL_CHANNEL_PARA;


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*                                 ���ͨ��                                   */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/****************************************************     
* �ṹ����T_OUTPUT_CO_FUNC_PARA;
* ������  ���ͨѶ�������
* ������
    BYTE    ucCoNo;                             ͨѶ�����ͨѶ�������   
    BYTE    ucOutputMode;                       ���ģʽ
                                                OUTPUT_ONOFF_MODE              ON/OFF���
                                                OUTPUT_FLASH_MODE              ��˸���
    BYTE    ucOnOffPwrUp;                       �ϵ��ON/OFF״̬
                                                OUTPUT_INIT_OFF_STATE          �ϵ�����OFF
                                                OUTPUT_INIT_ON_STATE           �ϵ�����ON
    BYTE    ucOnOffMode;                        ON/OFF��ͨѶ����ֵ��ϵ
                                                OUTPUT_ON_RCV1_AND_OFF_RCV0   �յ�"1" ʱ���ON, �յ�"0" ʱ���OFF
                                                OUTPUT_ON_RCV0_AND_OFF_RCV1   �յ�"0" ʱ���ON, �յ�"1" ʱ���OFF
                                                OUTPUT_ON_RCV1_0_NO_OFF_CMD   �յ�"0"��"1"ʱ���ON�������OFF
    WORD16  wDelayOff;                          ��ʱ�ر����ʱ�䣬ȡֵ��Χ 0~65535s��0Ϊ����ʱ�ر�
    BYTE    ucFlashPwrUp;                       �ϵ����˸״̬
                                                OUTPUT_INIT_STOP_FLASH         �ϵ�������˸
                                                OUTPUT_INIT_START_FLASH        �ϵ�������˸
    BYTE    ucFlashMode;                        ��˸��ͣ��ͨѶ����ֵ��ϵ
                                                OUTPUT_START_RCV1_AND_STOP_RCV0      �յ�"1" ʱ�����˸, �յ�"0" ʱֹͣ��˸
                                                OUTPUT_START_RCV0_AND_STOP_RCV1      �յ�"0" ʱ�����˸, �յ�"1" ʱֹͣ��˸
                                                OUTPUT_START_RCV1_0_AND_NO_STOP_CMD  �յ�"0"��"1"ʱ�����˸����ֹͣ��˸
    WORD16  wFlashPeriod;                       �����˸���ڣ�ȡֵ��Χ 0~65535ms
    WORD16  wFlashCount;                        �����˸������ȡֵ��Χ 0~65535��0Ϊ������˸                                
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE    ucCoNo;                             /* ͨѶ�����ͨѶ�������         */
    BYTE    ucOutputMode;                       /* �������/��˸���              */
    BYTE    ucOnOffPwrUp;                       /* �ϵ�󿪹����״̬             */
    BYTE    ucOnOffMode;                        /* ON/OFF��ͨѶ����ֵ��ϵ         */
    WORD16  wDelayOff;                          /* ��ʱ�ر����ʱ��               */
    BYTE    ucFlashPwrUp;                       /* �ϵ����˸���״̬             */
    BYTE    ucFlashMode;                        /* ��˸��ͣ��ͨѶ����ֵ��ϵ       */
    WORD16  wFlashPeriod;                       /* �����˸����                   */
    WORD16  wFlashCount;                        /* �����˸����                   */
}T_OUTPUT_CO_FUNC_PARA;

/****************************************************
* �ṹ����T_OUTPUT_CHANNEL_PARA;
* ������  ���ͨ���Ĳ���
* ������
    BYTE   ucChnlNo;                                ����ͨ����,1-6 
                                                    OUTPUT_CHANNEL_1
                                                    OUTPUT_CHANNEL_2
                                                    OUTPUT_CHANNEL_3
                                                    OUTPUT_CHANNEL_4
                                                    OUTPUT_CHANNEL_5
                                                    OUTPUT_CHANNEL_6
                                                    OUTPUT_CHANNEL_7
                                                    ע��һ����Ʒ�е�����ͨ����Ҫ������          
    OUTPUT_FUNC             fpOutputOp;             �����������ָ��                
    T_OUTPUT_CO_FUNC_PARA   tOutputCoPara;          ���ͨѶ����Ĳ���              
* ���ߣ�      
* Modified History��
*  2014-7-6        �����ṹ��
****************************************************/
typedef struct
{
    BYTE                    ucChnNo;             /* ����ͨ����,��1��ʼ          */
    OUTPUT_FUNC             fpOutputOp;          /* �����������ָ��            */       
    T_OUTPUT_CO_FUNC_PARA   tOutputCoPara;       /* ���ͨѶ����Ĳ���          */
}T_OUTPUT_CHANNEL_PARA;



#ifdef __cplusplus
}
#endif

#endif /* _APP_COMMON_ */




