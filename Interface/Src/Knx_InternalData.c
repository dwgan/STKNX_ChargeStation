/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_InternalData.c
* FileIdentifier：None
* Abstract ：Protocol mask processing。
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


#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "Hardware.h"

#include "boardctrl.h"
#include "Knx_Prop.h"
#include "Application_Data.h"
#include "Knx_M0705.h"
#include "Knx_InternalData.h"
#include "Knx_LoadCtrl.h"
#include "Knx_Auth.h"
#include "Application.h"

#pragma location = VIR_ADDR_TABLE + VIR_TO_REAL_OFFSET
__root const T_ADDRESS_TABLE  g_AddrTable = \
{
         10,           /* actual address table length. */
    0x10, 0x01,             /* physical address      */
    0x00, 0x01,             /* Grp. address,Index 1  */
    0x00, 0x02,             /* Grp. address,Index 2  */
    0x00, 0x03,             /* Grp. address,Index 3  */
    0x00, 0x04,             /* Grp. address,Index 4  */
    0x00, 0x05,             /* Grp. address,Index 5  */
    0x00, 0x06,             /* Grp. address,Index 6  */
    0x00, 0x07,             /* Grp. address,Index 7  */
    0x00, 0x08,             /* Grp. address,Index 8  */
    0x00, 0x09,             /* Grp. address,Index 9  */
    0x00, 0x0a,             /* Grp. address,Index 10 */
    0x10, 0x0b,             /* Grp. address,Index 11 */
    0x10, 0x0c              /* Grp. address,Index 12 */
};

#pragma location = VIR_ASSOC_TABLE + VIR_TO_REAL_OFFSET
__root const T_ASSOC_TABLE g_AssocTable = \
{
                      8,
/* Grp. addr index. */        /* Co. No. */
         0x01,                   CHARGE_CONNECT_STATUS_CO,
         0x02,                   CHARGE_RUNNING_STATUS_CO,
         0x03,                   CHARGE_BATTERY_PERCENT_CO,
         0x04,                   CHARGE_CURRENT_VALUE_CO,
         0x05,                   CHARGE_POWER_VALUE_CO,
         0x06,                   CHARGED_TIME_CO,
         0x07,                   REMAINING_CHARGE_TIME_CO,
         0x08,                   CHARGE_TEMPERATURE_CO,
};

#pragma location = VIR_KEY_START + VIR_TO_REAL_OFFSET
__root const BYTE aucAccKeys[15*4] =
{
    ACC_KEY_LEVEL0,
    ACC_KEY_LEVEL1,
    ACC_KEY_LEVEL2,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF
};


/* parameter set. */
#pragma location = VIR_KNX_PROT + VIR_TO_REAL_OFFSET
__root const BYTE g_ucKnxPrt[2] = {0,0};

#pragma location = VIR_FAC_ID + VIR_TO_REAL_OFFSET
__root const BYTE g_aucFacId[2] = {GET_HIBYTE(VALUE_FACTORY_ID),GET_LOWBYTE(VALUE_FACTORY_ID)};

#pragma location = VIR_LOAD_STATE_ADDR + VIR_TO_REAL_OFFSET
__root const BYTE g_ucAddrLoad = LOAD_STATE_LOADED;

#pragma location = VIR_LOAD_STATE_ASSOC + VIR_TO_REAL_OFFSET
__root const BYTE g_ucAssocLoad = LOAD_STATE_LOADED;

#pragma location = VIR_LOAD_STATE_APP + VIR_TO_REAL_OFFSET
__root const BYTE g_ucAppLoad = LOAD_STATE_LOADED;

#pragma location = VIR_LOAD_STATE_PEI + VIR_TO_REAL_OFFSET
__root const BYTE g_ucPeiLoad = LOAD_STATE_LOADED;

#pragma location = VIR_ENABLE_PHYS_ADDR + VIR_TO_REAL_OFFSET
__root const BYTE g_ucPgyAddrEn = 0;

#pragma location = VIR_ENABLE_RESET + VIR_TO_REAL_OFFSET
__root const BYTE g_ucResetEn = 0;

#pragma location = VIR_PEI_SERIAL_CONF + VIR_TO_REAL_OFFSET
__root const BYTE g_ucPeiSeriConf[2] = {0,0};

#pragma location = VIR_APP_MAIN + VIR_TO_REAL_OFFSET
__root const BYTE g_aucAppMainRef[2] = {HI_BYTE(APP_HEADER_MAIN_REF),LOW_BYTE(APP_HEADER_MAIN_REF)};

#pragma location = VIR_INTOB_TAB_REF + VIR_TO_REAL_OFFSET
__root const BYTE g_aucUserIntObjTbl[2] = {HI_BYTE(USER_INTOBJ_TABLE_REF),LOW_BYTE(USER_INTOBJ_TABLE_REF)};

#pragma location = VIR_INTOB_COUNT + VIR_TO_REAL_OFFSET
__root const BYTE g_ucUserIntObjCunt = USER_OBJECT_COUNT;

/********************************* MCB define ***********************************/
#pragma location = VIR_MCB_00 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tDevObjMcb = \
{
    VIR_BEG_SYS1_EE,\
    VIR_SYS1_SIZE,  \
    ACC_APP,        \
    FALSE,          \
    0,              \
    MEM_TYPE_EE_SYS,\
    OWNER_SYS,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_01 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAppObjMcb = \
{
    VIR_BEG_SYS4_EE,\
    VIR_SYS4_SIZE,  \
    ACC_APP,        \
    FALSE,          \
    0,              \
    MEM_TYPE_EE_SYS,\
    OWNER_SYS,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_02 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tPeiObjMcb = \
{
    VIR_BEG_SYS5_EE,\
    VIR_SYS5_SIZE,  \
    ACC_APP,        \
    FALSE,          \
    0,              \
    MEM_TYPE_EE_SYS,\
    OWNER_SYS,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_03 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tSys7Mcb = \
{
    VIR_BEG_SYS7_EE,\
    VIR_SYS7_SIZE,  \
    ACC_APP,        \
    FALSE,          \
    0,              \
    MEM_TYPE_EE_SYS,\
    OWNER_SYS,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_04 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAddrTblMcb = \
{
    APP_ADDR_TABLE_REF,\
    ADDR_TABLE_SIZE,   \
    ACC_ADDR,          \
    TRUE,              \
    0,              \
    MEM_TYPE_EE_USER,  \
    OWNER_ADDR,        \
    0,              \
    0x0000
};

#pragma location = VIR_MCB_05 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAssocTblMcb = \
{
    APP_ASSOC_TABLE_REF,\
    ASSOC_TABLE_SIZE,   \
    ACC_ASSOC,          \
    TRUE,               \
    0,              \
    MEM_TYPE_EE_USER,   \
    OWNER_ASSOC,        \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_06 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAppRamMcb = \
{
    APP_RAM_BEGIN, \
    APP_RAM_SIZE,  \
    ACC_APP,       \
    FALSE,         \
    0,              \
    MEM_TYPE_HIRAM,\
    OWNER_APP,     \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_07 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAppMem1Mcb = \
{
    APP_MEM1_REF,\
    APP_MEM1_SIZE,\
    ACC_APP,\
    TRUE,            \
    0,              \
    MEM_TYPE_EE_USER,\
    OWNER_APP,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_08 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAppMem2Mcb = \
{
    APP_MEM2_REF,\
    APP_MEM2_SIZE,\
    ACC_PAR,\
    FALSE,            \
    0,              \
    MEM_TYPE_EE_USER,\
    OWNER_APP,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_09 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAppMem3Mcb = \
{
    0x0000FFFF,\
    0xFFFF,    \
    0xFF,      \
    TRUE,      \
    0,              \
    MEM_TYPE_EE_USER,\
    OWNER_FREE,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_10 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAppMem4Mcb = \
{
    0x0000FFFF,\
    0xFFFF,    \
    0xFF,      \
    TRUE,      \
    0,              \
    MEM_TYPE_EE_USER,\
    OWNER_FREE,      \
    0,              \
    0xFFFF
};

#pragma location = VIR_MCB_11 + VIR_TO_REAL_OFFSET
__root const T_KNXMEM_MCB g_tAppMem5Mcb = \
{
    0x0000FFFF,\
    0xFFFF,    \
    0xFF,      \
    TRUE,      \
    0,              \
    MEM_TYPE_EE_USER,\
    OWNER_FREE,      \
    0,              \
    0xFFFF
};
/********************************************************************************/




/* end of file */

