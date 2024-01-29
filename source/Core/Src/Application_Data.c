/******************************************************************************
* VersionOwner (C)2022,STMicroelectronics(ShenZhen)R&D Co.,Ltd.
*
* FileName：Application_Data.c
* FileIdentifier：None
* Abstract ：Protocol mask processing。
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


#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "App_common.h"
#include "Boardctrl.h"
#include "Knx_Prop.h"
#include "Knx_M0705.h"
#include "Application_Data.h"
#include "Hardware.h"

#include "Application.h"
#include "Knx_InternalData.h"
#include "Knx_AlApp.h"
#include "Knx_Auth.h"
#include "Knx_LoadCtrl.h"

#pragma location = APP_COM_OBJ_TABLE_REF + VIR_TO_REAL_OFFSET
__root const T_COMOBJ_TABLE g_tComObjTable = \
{
    COMM_OBJECT_COUNT,
    {HI_BYTE(RAM_FLAGS_REF),LOW_BYTE(RAM_FLAGS_REF)},
    {
		 /* inputx communication object parameter. */
	    {HI_BYTE(VALUE_REF_CO0),LOW_BYTE(VALUE_REF_CO0),COM_ALL|PRIO_LOW,TYPE_UINT1  }, //charge point connection status
	    {HI_BYTE(VALUE_REF_CO1),LOW_BYTE(VALUE_REF_CO1),COM_ALL|PRIO_LOW,TYPE_UINT1  }, //charge running status
	    {HI_BYTE(VALUE_REF_CO2),LOW_BYTE(VALUE_REF_CO2),COM_ALL|PRIO_LOW,TYPE_UINT8  }, //charge battery percent status
	    {HI_BYTE(VALUE_REF_CO3),LOW_BYTE(VALUE_REF_CO3),COM_ALL|PRIO_LOW,TYPE_UINT16  }, //charge current
		{HI_BYTE(VALUE_REF_CO4),LOW_BYTE(VALUE_REF_CO4),COM_ALL|PRIO_LOW,TYPE_FLOAT	 }, //charge power 4 byte
		{HI_BYTE(VALUE_REF_CO5),LOW_BYTE(VALUE_REF_CO5),COM_ALL|PRIO_LOW,TYPE_UINT16 },//has charged time
		{HI_BYTE(VALUE_REF_CO6),LOW_BYTE(VALUE_REF_CO6),COM_ALL|PRIO_LOW,TYPE_UINT16 },//has charged time
		{HI_BYTE(VALUE_REF_CO7),LOW_BYTE(VALUE_REF_CO7),COM_ALL|PRIO_LOW,TYPE_UINT16 }, //charge temperature			
		{HI_BYTE(VALUE_REF_CO8),LOW_BYTE(VALUE_REF_CO8),COM_ALL|PRIO_LOW,TYPE_FLOAT }, //charged energy	4 bytes	
		{HI_BYTE(VALUE_REF_CO9),LOW_BYTE(VALUE_REF_CO9),COM_ALL|PRIO_LOW,TYPE_DOUBLE }, //datetime 8 bytes
	    {HI_BYTE(VALUE_REF_CO10),LOW_BYTE(VALUE_REF_CO10),COM_ALL|PRIO_LOW,TYPE_MAXDATA}, //charging ID 14 bytes

	/* outputx communication object parameter. */
		 
		{HI_BYTE(VALUE_REF_CO11),LOW_BYTE(VALUE_REF_CO11),COM_ALL|PRIO_LOW,TYPE_UINT8 },//dimming ASC value

		/*Temperature and Humidity communication boject*/
		{HI_BYTE(VALUE_REF_CO12),LOW_BYTE(VALUE_REF_CO12),COM_ALL|PRIO_LOW,TYPE_UINT16   }, //Temperature value
		{HI_BYTE(VALUE_REF_CO13),LOW_BYTE(VALUE_REF_CO13),COM_ALL|PRIO_LOW,TYPE_UINT16   },//Humidity value

		/*Colorvalue	communication object*/
		{HI_BYTE(VALUE_REF_CO14),LOW_BYTE(VALUE_REF_CO14),COM_ALL|PRIO_LOW,TYPE_TIME_DATE	 }, //Color value
    }
};
/************* Application configure parameter area *******************************/
/* switch type parameter virtual address define. */
#pragma location = (DEVICE_ID_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucIn1Type = KNX_APP_TOGGLE;                             /* if this channel is working,it will always send ON. */

#pragma location = (IN2_SWFUNC_TYPE_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucIn2Type = KNX_APP_TOGGLE;                             /* if this channel is working,it will always send OFF. */

#pragma location = (IN3_SWFUNC_TYPE_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucIn3Type = KNX_APP_TOGGLE;                             /* if this channel is working,it will always toggle the output. */

#pragma location = (IN4_SWFUNC_TYPE_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucIn4Type = KNX_APP_TOGGLE;                             /* if this channel is working,it will always send ON. */

/* output type parameter virtual address define. */
#pragma location = (OUT1_FUNC_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucOut1Type = OUTPUT_FLASH;                          /* according to the value of the Co. to output. */

#pragma location = (OUT2_FUNC_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucOut2Type = OUTPUT_FLASH;                          /* flash output.time is 500ms. */

#pragma location = (OUT3_FUNC_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucOut3Type = OUTPUT_FLASH;                          /* flash output.time is 500ms. */

#pragma location = (OUT4_FUNC_REF + VIR_TO_REAL_OFFSET)
__root const BYTE g_ucOut4Type = OUTPUT_FLASH;                          /* according to the value of the Co. to output. */

/************************** parameter area end. *************************************/

/* scene parameter define area(add scene parameter here). */
#pragma location = (CH1_MEM_SCENES + VIR_TO_REAL_OFFSET)
__root const BYTE g_aucCh1Scene[CH_MEM_SCENE_SIZE] = {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};

#pragma location = (CH2_MEM_SCENES + VIR_TO_REAL_OFFSET)
__root const BYTE g_aucCh2Scene[CH_MEM_SCENE_SIZE] = {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0};

#pragma location = (CH3_MEM_SCENES + VIR_TO_REAL_OFFSET)
__root const BYTE g_aucCh3Scene[CH_MEM_SCENE_SIZE] = {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};

#pragma location = (CH4_MEM_SCENES + VIR_TO_REAL_OFFSET)
__root const BYTE g_aucCh4Scene[CH_MEM_SCENE_SIZE] = {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};

/****** scene parameter define end ***************************************************/

/***************************** User's interface Object ******************************/
/* user defining interface object reference table . */
#pragma location = USER_INTOBJ_TABLE_REF + VIR_TO_REAL_OFFSET
__root const BYTE g_aucUserIntObjTblRef[USER_INTOBJ_TABLE_SIZE] = {HI_BYTE(USER_INTOBJ15_DESC_REF),LOW_BYTE(USER_INTOBJ15_DESC_REF)};

/* user defining interface object's description. */
#pragma location = USER_INTOBJ15_DESC_REF + VIR_TO_REAL_OFFSET
__root const T_0705_USER_OBJ15 g_tUserIntObj15 = \
{
    PROP_COUNT_OF_INTOB15,
    {
        {PID_OBJECT_TYPE    ,PDT_UNSIGNED_INT                       /* 2 */,0,1,READ_L_FREE, (WORDPTR)USER_INTOBJ15_VALUE0_REF },\
        {USER_OBJ15_PROP1   ,PROP_WRITE_ENABLE_MASK|PDT_GENERIC_01  /* 1 */,0,1,WR_FREE    , (WORDPTR)APP_MEM_WRITE_BLOCKED    },\
    }
};
/* user defining interface object15's ID. */
#pragma location = USER_INTOBJ15_VALUE0_REF + VIR_TO_REAL_OFFSET
__root const BYTE g_aucUserIntObj15Id[USER_INTOBJ15_VAL0_SIZE] = {HI_BYTE(USER_OBJ15_ID),LOW_BYTE(USER_OBJ15_ID)};
/*************************************************************************************/

/********************** Application header define,Note:Do not change anything here. ************************************/
/* Application header parameter define. */
#pragma location = APP_HEADER_KEY_REF + VIR_TO_REAL_OFFSET
__root const BYTE g_aucAppHeaderKey[2] = {KNX_APP_KEY0,KNX_APP_KEY1};
/* stack type 0705 */
#pragma location = APP_HEADER_STACK_TYPE_REF + VIR_TO_REAL_OFFSET
__root const BYTE g_aucAppHeaderStack[2] = {HI_BYTE(DEV_DESC_0705),LOW_BYTE(DEV_DESC_0705)};
/* communication object table reference. */
#pragma location = APP_HEADER_COTABLE_REF + VIR_TO_REAL_OFFSET
__root const BYTE g_aucAppHeaderCoTbl[2] = {HI_BYTE(APP_COM_OBJ_TABLE_REF),LOW_BYTE(APP_COM_OBJ_TABLE_REF)};
/* stack version. */
#pragma location = APP_HEADER_STACK_VER_REF + VIR_TO_REAL_OFFSET
__root const BYTE g_ucAppHeaderStkVer = {APP_STACK_API_VERSION};
/************************************************************************************/

/****** parameter for data information.Note:Do not change anything here. **************/
#pragma location = KNX_API_S19_PARA_START
__root const BYTE g_aucMaskOffsetInfo[4] = {HI_BYTE(VIR_MANUFACT_ID),LOW_BYTE(VIR_MANUFACT_ID),HI_BYTE(VIR_TO_REAL_OFFSET),LOW_BYTE(VIR_TO_REAL_OFFSET)};

/* T_KNXMEM_MCB g_tAddrTblMcb */
#pragma location = (KNX_API_S19_PARA_START + 4)
__root const BYTE g_aucAddrTblRef[4] = {HI_BYTE(APP_ADDR_TABLE_REF),LOW_BYTE(APP_ADDR_TABLE_REF),HI_BYTE(ADDR_TABLE_SIZE),LOW_BYTE(ADDR_TABLE_SIZE)};
#pragma location = (KNX_API_S19_PARA_START + 8)
__root const BYTE g_aucAddrTblAttr[4]= {OWNER_ADDR,ACC_ADDR,MEM_TYPE_EE_USER,0x80};

/* T_KNXMEM_MCB g_tAssocTblMcb */
#pragma location = (KNX_API_S19_PARA_START + 12)
__root const BYTE g_aucAssocTblRef[4] = {HI_BYTE(APP_ASSOC_TABLE_REF),LOW_BYTE(APP_ASSOC_TABLE_REF),HI_BYTE(ASSOC_TABLE_SIZE),LOW_BYTE(ASSOC_TABLE_SIZE)};
#pragma location = (KNX_API_S19_PARA_START + 16)
__root const BYTE g_aucAssocTblAttr[4]= {OWNER_ASSOC,ACC_ASSOC,MEM_TYPE_EE_USER,0x80};

/* T_KNXMEM_MCB g_tAppRamMcb */
#pragma location = (KNX_API_S19_PARA_START + 20)
__root const BYTE g_aucAppRamRef[4] = {HI_BYTE(APP_RAM_BEGIN),LOW_BYTE(APP_RAM_BEGIN),HI_BYTE(APP_RAM_SIZE),LOW_BYTE(APP_RAM_SIZE)};
#pragma location = (KNX_API_S19_PARA_START + 24)
__root const BYTE g_aucAppRamAttr[4]= {OWNER_APP,ACC_APP,MEM_TYPE_HIRAM,0x00};

/* T_KNXMEM_MCB g_tAppMem1Mcb */
#pragma location = (KNX_API_S19_PARA_START + 28)
__root const BYTE g_aucAppMem1Ref[4] = {HI_BYTE(APP_MEM1_REF),LOW_BYTE(APP_MEM1_REF),HI_BYTE(APP_MEM1_SIZE),LOW_BYTE(APP_MEM1_SIZE)};
#pragma location = (KNX_API_S19_PARA_START + 32)
__root const BYTE g_aucAppMem1Attr[4]= {OWNER_APP,ACC_APP,MEM_TYPE_EE_USER,0x80};

/* T_KNXMEM_MCB g_tAppMem2Mcb */
#pragma location = (KNX_API_S19_PARA_START + 36)
__root const BYTE g_aucAppMem2Ref[4] = {HI_BYTE(APP_MEM2_REF),LOW_BYTE(APP_MEM2_REF),HI_BYTE(APP_MEM2_SIZE),LOW_BYTE(APP_MEM2_SIZE)};
#pragma location = (KNX_API_S19_PARA_START + 40)
__root const BYTE g_aucAppMem2Attr[4]= {OWNER_APP,ACC_PAR,MEM_TYPE_EE_USER,0x00};

/* Application header & user interface object. */
#pragma location = (KNX_API_S19_PARA_START + 44)
__root const BYTE g_aucAppHeaderObj[4]= {HI_BYTE(APP_HEADER_MAIN_REF),LOW_BYTE(APP_HEADER_MAIN_REF),HI_BYTE(USER_INTOBJ_TABLE_REF),LOW_BYTE(USER_INTOBJ_TABLE_REF)};


#if(DEBUG_ONOFF)
WORDPTR g_dwParaRef;
WORDPTR g_dwInt5TableRef;
WORDPTR g_dwAppRawRef;
WORDPTR g_dwAppMainRef;
WORDPTR g_dwAppMem1EndRef;
WORD16  g_wAppMem1Size;
WORDPTR g_dwAppMem2Ref;
WORDPTR g_dwAppMemEndRef;
VOID Application_Para_Debug(VOID)
{
    g_dwParaRef      = APP_PARA_AREA_REF;
    g_dwInt5TableRef = USER_INTOBJ_TABLE_REF;
    g_dwAppRawRef    = APP_HEADER_RAW_REF;
    g_dwAppMainRef   = APP_HEADER_MAIN_REF;
    g_dwAppMem1EndRef= APP_MEM1_END_REF;
    g_wAppMem1Size   = APP_MEM1_SIZE;
    g_dwAppMem2Ref   = APP_MEM2_REF;
    g_dwAppMemEndRef = APP_MEM_END;
}
#endif




/* end of file */

