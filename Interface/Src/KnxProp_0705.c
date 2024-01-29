/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：KnxProp_091a.c
* FileIdentifier：None
* Abstract ：KNX 091a协议栈属性定义源文件。
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
#include "Sw_common.h"
#include "Knx_Auth.h"
#include "Knx_Prop.h"
#include "Application_Data.h"
#include "KnxProp_0705.h"
#include "Knx_M0705.h"
#include "Knx_InternalData.h"
#include "boardctrl.h"


/******************************************** Property value set *************************************************/
/* Property parameter of device object. */
#pragma location = DEV_OBJ_PROP_LOCATION + VIR_TO_REAL_OFFSET
__root const T_0705_DEVOBJ_PARAM gt_DevObj_Prop = \
{
    { 0,OBJECT_DEVICE_ID                  },                      /* aucObjType[2]     */
    { WORD_2_HILOW(VALUE_SERVICE_CONTROL) },                      /* aucSvrCtrl[2]     */
    { VALUE_FIRMWARE_VER                  },                      /* aucFirmVer        */
      VALUE_SERIAL_NUMBER                 ,                       /* aucSeriNum[6]     */
    { WORD_2_HILOW(VALUE_FACTORY_ID)      },                      /* aucFactoryId[2]   */
      VALUE_ORDER_INFO                     ,                      /* aucOrderInfo[10]  */
      VALUE_FACTOR_DATA                    ,                      /* aucFactoryData[4] */
      VALUE_HAEDWARE_TYPE                                         /* aucHardWareType[6]*/
};

/* Property parameter of address table object. */
#pragma location = ADDR_OBJ_PROP_LOCATION + VIR_TO_REAL_OFFSET
__root const T_0705_ADDROBJ_PARAM gt_AddrObj_Prop = \
{
    { 0,OBJECT_ADDR_TABLE_ID              },                      /* aucObjType[2]     */
    { WORD_2_HILOW(VIR_ADDR_TABLE)        }                       /* aucAddrTblRefer[2]*/
};

/* Property parameter of association table object. */
#pragma location = ASSOC_OBJ_PROP_LOCATION + VIR_TO_REAL_OFFSET
__root const T_0705_ASSOCOBJ_PARAM gt_AssocObj_Prop = \
{
    { 0,OBJECT_ASSOC_TABLE_ID             },                      /* aucObjType[2]     */
    { WORD_2_HILOW(VIR_ASSOC_TABLE)       }                       /* aucAssocTblRefer[2]*/
};

/* Property parameter of application object. */
#pragma location = APP_OBJ_PROP_LOCATION + VIR_TO_REAL_OFFSET
__root const T_0705_APPOBJ_PARAM gt_AppObj_Prop = \
{
    { 0,OBJECT_APPLICATION_ID             },                      /* aucObjType[2]     */
    VALUE_MANUFACTURER_APP_VER,                                   /* aucAppVersion[5]  */
    VALUE_PEI_TYPE                                                /* ucPeiType         */
};

/* Property parameter of PEI object. */
#pragma location = PEI_OBJ_PROP_LOCATION + VIR_TO_REAL_OFFSET
__root const T_0705_PEIOBJ_PARAM gt_PeiObj_Prop = \
{
    { 0,OBJECT_INTERFACE_PRGM_ID          },                      /* aucObjType[2]     */
    VALUE_PEI_APP_VER                                             /* aucAppVersion[5]  */
};

/****************************************** Object Property attribute Set *********************************************************/
/* Device Object's properties attributes. */
const T_0705_DEV_OBJ g_tM0705_DevObj = \
{
    M0705_DEVOBJ_PROP_NUM,
    {
        {PID_OBJECT_TYPE       ,PDT_UNSIGNED_INT                         /* 2 */,0,1,ACC_DEV, (WORDPTR)(gt_DevObj_Prop.aucObjType)     - VIR_TO_REAL_OFFSET },
        {PID_SERVICE_CONTROL   ,PROP_WRITE_ENABLE_MASK|PDT_UNSIGNED_INT  /* 2 */,0,1,ACC_DEV, (WORDPTR)(gt_DevObj_Prop.aucSvrCtrl)     - VIR_TO_REAL_OFFSET },
        {PID_FIRMWARE_REVISION ,PDT_UNSIGNED_CHAR                        /* 1 */,0,1,ACC_DEV, (WORDPTR)(&gt_DevObj_Prop.aucFirmVer)    - VIR_TO_REAL_OFFSET },
        {PID_SERIAL_NUMBER     ,PROP_WRITE_ENABLE_MASK|PDT_GENERIC_06    /* 6 */,0,1,ACC_DEV, (WORDPTR)(gt_DevObj_Prop.aucSeriNum)     - VIR_TO_REAL_OFFSET },
        {PID_MANUFACTURER_ID   ,PROP_WRITE_ENABLE_MASK|PDT_UNSIGNED_INT  /* 2 */,0,1,ACC_DEV, (WORDPTR)(gt_DevObj_Prop.aucFactoryId)   - VIR_TO_REAL_OFFSET },
        {PID_DEVICE_CONTROL    ,PROP_WR_FUNC_SET|PDT_GENERIC_01          /* 1 */,0,1,ACC_DEV, (WORDPTR)(PROP_SYSFUNC_DEV_CONTROL)                           },
        {PID_ORDER_INFO        ,PROP_WRITE_ENABLE_MASK|PDT_GENERIC_10    /* 10*/,0,1,ACC_DEV, (WORDPTR)(gt_DevObj_Prop.aucOrderInfo)   - VIR_TO_REAL_OFFSET },
        {PID_PEI_TYPE          ,PROP_WR_FUNC_SET|PDT_UNSIGNED_CHAR       /* 1 */,0,1,ACC_DEV, (WORDPTR)(PROP_SYSFUNC_DEV_PEI_TYPE)                          },
        {PID_MANUFACTURER_DATA ,PROP_WRITE_ENABLE_MASK|PDT_GENERIC_04    /* 4 */,0,1,ACC_DEV, (WORDPTR)(gt_DevObj_Prop.aucFactoryData) - VIR_TO_REAL_OFFSET },
        {PID_HARDWARE_TYPE     ,PROP_WRITE_ENABLE_MASK|PDT_GENERIC_06    /* 6 */,0,1,ACC_DEV, (WORDPTR)(gt_DevObj_Prop.aucHardWareType)- VIR_TO_REAL_OFFSET }
    }
};

/* Address table Object's properties attributes. */
const T_0705_ADDR_OBJ g_tM0705_AddrObj = \
{
    M0705_ADDROBJ_PROP_NUM,
    {
        {PID_OBJECT_TYPE        ,PDT_UNSIGNED_INT                        /* 2 */,0,1,ACC_ADDR, (WORDPTR)(gt_AddrObj_Prop.aucObjType)      - VIR_TO_REAL_OFFSET },
        {PID_LOAD_STATE_CONTROL ,PROP_WR_FUNC_SET|PDT_CONTROL            /* 1 */,0,1,ACC_ADDR, (WORDPTR)(PROP_SYSFUNC_LOAD_CONTROL)                             },
        {PID_TABLE_REFERENCE    ,PROP_WRITE_ENABLE_MASK|PDT_UNSIGNED_INT /* 2 */,0,1,ACC_ADDR, (WORDPTR)(gt_AddrObj_Prop.aucAddrTblRefer) - VIR_TO_REAL_OFFSET },
        {PID_MCB_TABLE          ,PROP_FUNC_SET|PDT_GENERIC_08            /* 8 */,0,1,ACC_ADDR, (WORDPTR)(PROP_SYSFUNC_MCB_TABLE)                                }
    }
};

/* Association table Object's properties attributes. */
const T_0705_ASSOC_OBJ g_tM0705_AssocObj = \
{
    M0705_ASSOCOBJ_PROP_NUM,
    {
        {PID_OBJECT_TYPE        ,PDT_UNSIGNED_INT                        /* 2 */,0,1,ACC_ASSOC, (WORDPTR)(gt_AssocObj_Prop.aucObjType)       - VIR_TO_REAL_OFFSET },
        {PID_LOAD_STATE_CONTROL ,PROP_WR_FUNC_SET|PDT_CONTROL            /* 1 */,0,1,ACC_ASSOC, (WORDPTR)(PROP_SYSFUNC_LOAD_CONTROL)                              },
        {PID_TABLE_REFERENCE    ,PROP_WRITE_ENABLE_MASK|PDT_UNSIGNED_INT /* 2 */,0,1,ACC_ASSOC, (WORDPTR)(gt_AssocObj_Prop.aucAssocTblRefer) - VIR_TO_REAL_OFFSET },
        {PID_MCB_TABLE          ,PROP_FUNC_SET|PDT_GENERIC_08            /* 8 */,0,1,ACC_ASSOC, (WORDPTR)(PROP_SYSFUNC_MCB_TABLE)                                 }
    }
};

/* Application Object's properties attributes. */
const T_0705_APP_OBJ g_tM0705_AppObj = \
{
    M0705_APP_PROP_NUM,
    {
        {PID_OBJECT_TYPE        ,PDT_UNSIGNED_INT                         /* 2 */,0,1,ACC_APP ,(WORDPTR)(gt_AppObj_Prop.aucObjType)    - VIR_TO_REAL_OFFSET },
        {PID_LOAD_STATE_CONTROL ,PROP_WR_FUNC_SET|PDT_CONTROL             /* 1 */,0,1,ACC_APP ,(WORDPTR)(PROP_SYSFUNC_LOAD_CONTROL)                         },
        {PID_RUN_STATE_CONTROL  ,PROP_WR_FUNC_SET|PDT_CONTROL             /* 1 */,0,1,ACC_APP ,(WORDPTR)(PROP_SYSFUNC_RUN_CONTROL_APP)                      },
        {PID_PROGRAM_VERSION    ,PROP_WRITE_ENABLE_MASK|PDT_GENERIC_05      /* 1 */,0,1,ACC_APP ,(WORDPTR)(gt_AppObj_Prop.aucAppVersion) - VIR_TO_REAL_OFFSET },
        {PID_PEI_TYPE           ,PROP_WRITE_ENABLE_MASK|PDT_UNSIGNED_CHAR /* 2 */,0,1,ACC_APP ,(WORDPTR)(&gt_AppObj_Prop.ucPeiType)     - VIR_TO_REAL_OFFSET },
        {PID_MCB_TABLE          ,PROP_FUNC_SET|PDT_GENERIC_08             /* 8 */,0,1,ACC_APP ,(WORDPTR)(PROP_SYSFUNC_MCB_TABLE)                            }
    }
};

/* PEI Object's properties attributes. */
const T_0705_PEI_OBJ g_tM0705_PeiObj = \
{
    M0705_PEI_PROP_NUM,
    {
        {PID_OBJECT_TYPE        ,PDT_UNSIGNED_INT                         /* 2 */,0,1,ACC_PEI, (WORDPTR)(gt_PeiObj_Prop.aucObjType)    - VIR_TO_REAL_OFFSET },
        {PID_LOAD_STATE_CONTROL ,PROP_WR_FUNC_SET|PDT_CONTROL             /* 1 */,0,1,ACC_PEI, (WORDPTR)(PROP_SYSFUNC_LOAD_CONTROL)                         },
        {PID_RUN_STATE_CONTROL  ,PROP_WR_FUNC_SET|PDT_CONTROL             /* 1 */,0,1,ACC_PEI, (WORDPTR)(PROP_SYSFUNC_RUN_CONTROL_APP)                      },
        {PID_PROGRAM_VERSION    ,PROP_WRITE_ENABLE_MASK|PDT_GENERIC_05    /* 1 */,0,1,ACC_PEI, (WORDPTR)(gt_PeiObj_Prop.aucAppVersion) - VIR_TO_REAL_OFFSET },
        {PID_MCB_TABLE          ,PROP_FUNC_SET|PDT_GENERIC_08             /* 8 */,0,1,ACC_PEI, (WORDPTR)(PROP_SYSFUNC_MCB_TABLE)                            }
    }
};

/* Property parameter of device object. */
const T_0705_DEVOBJ_PARAM tDevObj_Prop_Dflt = \
{
    { 0,OBJECT_DEVICE_ID                  },                      /* aucObjType[2]     */
    { WORD_2_HILOW(VALUE_SERVICE_CONTROL) },                      /* aucSvrCtrl[2]     */
    { VALUE_FIRMWARE_VER                  },                      /* aucFirmVer        */
      VALUE_SERIAL_NUMBER                  ,                      /* aucSeriNum[6]     */
    { WORD_2_HILOW(VALUE_FACTORY_ID)      },                      /* aucFactoryId[2]   */
      VALUE_ORDER_INFO                     ,                      /* aucOrderInfo[10]  */
      VALUE_FACTOR_DATA                    ,                      /* aucFactoryData[4] */
      VALUE_HAEDWARE_TYPE                                         /* aucHardWareType[6]   */
};

/* Property parameter of address table object. */
const T_0705_ADDROBJ_PARAM tAddrObj_Prop_Dflt = \
{
    { 0,OBJECT_ADDR_TABLE_ID              },                      /* aucObjType[2]     */
    { WORD_2_HILOW(VIR_ADDR_TABLE)        }                       /* aucAddrTblRefer[2]*/
};

/* Property parameter of association table object. */
const T_0705_ASSOCOBJ_PARAM tAssocObj_Prop_Dflt = \
{
    { 0,OBJECT_ASSOC_TABLE_ID             },                      /* aucObjType[2]     */
    { WORD_2_HILOW(VIR_ASSOC_TABLE)       }                       /* aucAssocTblRefer[2]*/
};

/* Property parameter of application object. */
const T_0705_APPOBJ_PARAM tAppObj_Prop_Dflt = \
{
    { 0,OBJECT_APPLICATION_ID             },                      /* aucObjType[2]     */
    VALUE_MANUFACTURER_APP_VER,                                   /* aucAppVersion[5]  */
    VALUE_PEI_TYPE                                                /* ucPeiType         */
};

/* Property parameter of PEI object. */
const T_0705_PEIOBJ_PARAM tPeiObj_Prop_Dflt = \
{
    { 0,OBJECT_INTERFACE_PRGM_ID          },                      /* aucObjType[2]     */
    VALUE_PEI_APP_VER                                             /* aucAppVersion[5]  */
};

/**************************************************************************************************************
* FunctionName:WORDPTR KnxProp_GetSysObjectRef(BYTE ucObIndex)
* FunctionDescription: Get the system object pointer.
* InputParameterBYTE ucObIndex:the object index.
* OutputParameterno.
* Return Value：the pointer of the object.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
WORDPTR KnxProp_GetSysObjectRef(BYTE ucObjIndex)
{
    WORDPTR dwObjRef = 0;

    switch(ucObjIndex)
    {
        case OBJECT_DEVICE_ID:
        {
            dwObjRef = (WORDPTR)(&g_tM0705_DevObj);
            break;
        }
        case OBJECT_ADDR_TABLE_ID:
        {
            dwObjRef = (WORDPTR)(&g_tM0705_AddrObj);
            break;
        }
        case OBJECT_ASSOC_TABLE_ID:
        {
            dwObjRef = (WORDPTR)(&g_tM0705_AssocObj);
            break;
        }
        case OBJECT_APPLICATION_ID:
        {
            dwObjRef = (WORDPTR)(&g_tM0705_AppObj);
            break;
        }
        case OBJECT_INTERFACE_PRGM_ID:
        {
            dwObjRef = (WORDPTR)(&g_tM0705_PeiObj);
            break;
        }
    }
    
    return dwObjRef;
}










/* end of file */

