/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_M0705.h
* FileIdentifier：None
* Abstract ：本文件为KNX协议栈描述的公共定义。
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



#ifndef _KNX_M0705_H_
#define _KNX_M0705_H_

#ifdef __cplusplus
extern "C" {
#endif



/* The device descriptor (mask version) */
#define DEV_DESC_0705            0x0705        /* The mask version of the device */
#define DEV_DESC_MASK              0x3F
#define DEV_DESC_ERROR             0x3F        /* The error type */
#define PEI_TYPE_0                 0           /* default PEI type. */
#define PEI_TYPE_MAX               20          /* PEI type: Shortcut, Download mode */

/* 0705 virtual flash memory definitions. we should alloc this memory in link file.
    and we should pay attention to the relationship between the memory boundary definition
    and the real memory(in a total memory page.). */
#define VIR_BEG_USER_EE           0x4000        /* Begin of flash memory availale for user */
#define VIR_END_USER_EE           0x5FFF        /* End of flash memory availale for user   */

/***********************************************
 First part of virtual flash room for tables and
 dummy application:
       0x4000-0x4FFF
 Size: 4k bytes.
 This memory is accessible via  bus(DMA).
************************************************/
#define VIR_ADDR_TABLE            0x4000        /* Address table's begin address.  */
#define VIR_ADDR_TABLE_LENGTH     0x4000        /* Address table's length address. */
#define VIR_PHY_ADDR              0x4001        /* Physical address's address.     */
#define VIR_PHY_ADDR_HI           0x4001        /* Physical address high byte's address. */
#define VIR_PHY_ADDR_LOW          0x4002        /* Physical address low byte's address.  */
#define VIR_GROUP_ADDR_BEGIN      0x4003        /* Hibyte of the first group address.    */

#define VIR_ASSOC_TABLE           0x4200        /* Association table's begin address.  */
#define VIR_ASSOC_TABLE_LENGTH    0x4200        /* Association table's length address. */
#define VIR_ASSOC_TABLE_GRP1      0x4201        /* the address of the first group address's index in Assoc. talbe. */
#define VIR_ASSOC_TABLE_CO1       0x4202        /* the address of the first Co. No. in Assoc. talbe.  */

#define VIR_COMMOB_TABLE          0x4400        /* communication object table begin address. */
#define VIR_USER_DATA_END         VIR_END_USER_EE
/* other application data should be defined behind 0x4800. */

/************************************************
 Second part of virtual flash room for system data.
 Size: 1k bytes.
*************************************************/
#define VIR_BEG_SYS_EE            0xB000        /* Start of system flash memory.            */
#define VIR_END_SYS_EE            0xBBFF        /* End of flash memory reserved for system. */
#define VIR_BEG_SYS3_EE           0xB560        /* system 3 memory start for association table object. */
#define VIR_END_SYS3_EE           0xB57F        /* system 3 memory end.   */
#define VIR_BEG_SYS4_EE           0xB580        /* system 4 memory start for application object. */
#define VIR_END_SYS4_EE           0xB59F        /* system 4 memory end.   */
#define VIR_BEG_SYS5_EE           0xB5A0        /* system 5 memory start for PEI object. */
#define VIR_END_SYS5_EE           0xB5BF        /* system 5 memory end.   */
#define VIR_BEG_SYS6_EE           0xB600        /* system 6 memory start for others. */
#define VIR_END_SYS6_EE           0xB6DD        /* system 6 memory end.   */
#define VIR_BEG_SYS7_EE           0xB6DE        /* system 7 memory start for others. */
#define VIR_END_SYS7_EE           0xB6F1        /* system 7 memory end.   */
#define VIR_BEG_SYS8_EE           0xB6F2        /* system 8 memory start for others. */
#define VIR_END_SYS8_EE           0xB7FF        /* system 8 memory end.   */

#define VIR_BEG_SYS1_EE           0xB800        /* system 1 memory start for device object. */
#define VIR_END_SYS1_EE           0xB83F        /* system 1 memory end.   */
#define VIR_BEG_SYS2_EE           0xB840        /* system 2 memory start for address table object. */
#define VIR_END_SYS2_EE           0xB85F        /* system 2 memory end.   */

#define VIR_BEG_REC_EE            0xC000        /* record table begin */
#define VIR_END_REC_EE            0xC7FF        /* record table begin */

/* Size of every part of memory area. */
#define VIR_SYS1_SIZE            (VIR_END_SYS1_EE - VIR_BEG_SYS1_EE + 1)
#define VIR_SYS2_SIZE            (VIR_END_SYS2_EE - VIR_BEG_SYS2_EE + 1)
#define VIR_SYS3_SIZE            (VIR_END_SYS3_EE - VIR_BEG_SYS3_EE + 1)
#define VIR_SYS4_SIZE            (VIR_END_SYS4_EE - VIR_BEG_SYS4_EE + 1)
#define VIR_SYS5_SIZE            (VIR_END_SYS5_EE - VIR_BEG_SYS5_EE + 1)
#define VIR_SYS6_SIZE            (VIR_END_SYS6_EE - VIR_BEG_SYS6_EE + 1)
#define VIR_SYS7_SIZE            (VIR_END_SYS7_EE - VIR_BEG_SYS7_EE + 1)

#define BEG_USER_RAM              0x0700        /* Begin of RAM area */
#define END_USER_RAM              0x3FFF        /* End of RAM area   */

/* specification defining vitual memory locations(fixed address). */
#define RAM_STATUS_BYTE            0x0060        /* Device status byte                    */
#define RAM_BEG_CONTROLS           0x0100        /* Start of special controls bytes       */
#define RAM_SAVE_STATE             0x0100        /* Safe state byte (only at 070x)        */
#define RAM_RUN_STATE_APP          0x0101        /* Run state appliation (only at 070x)   */
#define RAM_RUN_STATE_PEI          0x0102        /* Run state PEI program (only at 070x)  */
#define RAM_RUN_CONTROL_APP        0x0103        /* Run control application (only at 070x)*/
#define RAM_LOAD_CONTROL           0x0104        /* Load state 10 bytes (only at 070x)    */
#define RAM_END_CONTROLS           0x0119        /* End of special controls bytes         */


/*************************************************************
 Second part-1
 Begin address:VIR_BEG_SYS1_EE 0xB800
 End address  :VIR_END_SYS1_EE 0xB83F
 size         :64 bytes
 Discription  :used for 0705 device object property data.
**************************************************************/
#define VIR_SYS1_BEGIN          VIR_BEG_SYS1_EE
#define VIR_DEVOBJ_TYPE         VIR_SYS1_BEGIN       /* device object type.2 bytes      */
                                                     /* 0xB801 : low object type byte.  */
#define VIR_SERV_CNTRL          0xB802               /* Service control word (2 bytes). */
                                                     /* 0xB803 : low service control byte. */
#define VIR_FIRMWARE_REV        0xB804               /* Firmware revision.                  */
#define VIR_SERIAL_NO           0xB805               /* First byte of serial number. */
                                                     /* 0xB80A : Last byte of serial number (complete: 6 bytes).*/
#define VIR_MANUFACT_ID         0xB80B               /* KNX manufacturer code  (2 bytes). */
                                                     /* 0xB80C : low manufacturer code byte. */
/* Device control is a function. */
#define VIR_ORDER_INFO          0xB80D               /* Manufacturer order info (10 Bytes).     */
                                                     /* 0xB816 : Last byte of order info (1 reserved byte). */
/* Pei type is a function. */
#define VIR_MAN_DATA            0xB817               /* Start of manufacturer data. */
                                                     /* 0xB81A : Last byte of manufacturer data (complete: 4 bytes).*/
#define VIR_HW_TYPE             0xB81B               /* First byte of hardware type. */
                                                     /* 0xB820 : Last byte of hardware type (complete: 6 bytes)*/
/* 33 bytes. */
/* 0xB521 - 0xB53F reserved. */
#define VIR_SYS1_END            VIR_END_SYS1_EE
#define DEV_OBJ_PROP_LOCATION   VIR_SYS1_BEGIN       /* device object loaction. */

/*************************************************************
 Second part-2
 Begin address:VIR_BEG_SYS2_EE 0xB840
 End address  :VIR_END_SYS2_EE 0xB85F
 size         :32 bytes
 Discription  :used for 0705 address table object property data.
**************************************************************/
#define VIR_SYS2_BEGIN          VIR_BEG_SYS2_EE
#define VIR_ADDROBJ_TYPE        VIR_SYS2_BEGIN       /* address table object type.2 bytes */
                                                     /* 0xB841 : low object type byte.    */
/* Load status control is a function. */
#define VIR_ADDR_TAB_REF        0xB842               /* Pointer to address table (2 bytes).  */
                                                     /* 0xB843 : low table reference byte.   */
/* Mcb table is a function. */
/* 0xB544 - 0xB55F reserved. */
#define VIR_SYS2_END            VIR_END_SYS2_EE
#define ADDR_OBJ_PROP_LOCATION  VIR_SYS2_BEGIN       /* address table object location. */

/***********************************************************************
 Second part-3
 Begin address:VIR_BEG_SYS3_EE 0xB560
 End address  :VIR_END_SYS3_EE 0xB57F
 size         :32 bytes
 Discription  :Used for 0705 association table object property data.
************************************************************************/
#define VIR_SYS3_BEGIN          VIR_BEG_SYS3_EE
#define VIR_ASSOCOBJ_TYPE       VIR_SYS3_BEGIN       /* association table object type.2 bytes */
                                                     /* 0xB561 : low object type byte.        */
/* Load status control is a function. */
#define VIR_ASSOC_TAB_REF       0xB562               /* Pointer to association table (2 bytes). */
                                                     /* 0xB563 : low table reference byte.      */
/* Mcb table is a function. */
/* 0xB564 - 0xB57F reserved. */
#define VIR_SYS3_END            VIR_END_SYS3_EE
#define ASSOC_OBJ_PROP_LOCATION VIR_SYS3_BEGIN

/************************************************************
 Second part-4
 Begin address:VIR_BEG_SYS4_EE 0xB580
 End address  :VIR_END_SYS4_EE 0xB59F
 size         :32 bytes
 Discription  :Used for application object property data.
*************************************************************/
#define VIR_SYS4_BEGIN          VIR_BEG_SYS4_EE
#define VIR_APPOBJ_TYPE         VIR_SYS4_BEGIN      /* application object type.2 bytes */
                                                    /* 0xB581 : low object type byte.  */
/* Load state control is a function. */
/* Run state control is a function.  */
#define VIR_APPLICATION_VER     0xB582              /* the application code(=manufacturer ID),5 bytes */
/* Alternative names */
#define   VIR_APP_ID              0xB584              /* Application ID (2 Byte). which application?internal or external? manufacturer set it. */
#define   VIR_APP_VERSION         0xB586              /* Application version. application's version.manufacturer set it. */

#define VIR_PEI_TYPE            0xB587              /* Required PEI type. */
/* Mcb table is a function. */
/* 0xB588 - 0xB59F reserved. */
#define VIR_SYS4_END            VIR_END_SYS4_EE
#define APP_OBJ_PROP_LOCATION   VIR_SYS4_BEGIN

/************************************************************
 Second part-5
 Begin address:VIR_BEG_SYS5_EE 0xB5A0
 End address  :VIR_END_SYS5_EE 0xB5BF
 size         :32 bytes
 Discription  :Used for PEI object property data.
*************************************************************/
#define VIR_SYS5_BEGIN          VIR_BEG_SYS5_EE
#define VIR_PEIOBJ_TYPE         VIR_SYS5_BEGIN      /* application object type.2 bytes */
                                                    /* 0xB5A1 : low object type byte.  */
/* Load state control is a function. */
/* Run state control is a function.  */
#define VIR_PEI_SW_VER          0xB5A2              /* the application version,5 bytes */
                                                    /* 0xB5A6 : low application version byte. */
/* Mcb table is a function. */
/* 0xB5A6 - 0xB5BF reserved. */
#define VIR_SYS5_END            VIR_END_SYS5_EE
#define PEI_OBJ_PROP_LOCATION   VIR_PEIOBJ_TYPE

/************************************************************
 Second part-6
 Begin address:VIR_BEG_SYS6_EE 0xB600
 End address  :VIR_END_SYS6_EE 0xB6DD
 size         :222bytes
 Discription  :Used for MCB etc..
*************************************************************/
#define VIR_APP_MAIN             0xB600               /* Pointer to user main function (2 bytes). */
#define VIR_INTOB_TAB_REF        0xB602               /* Pointer to interface object pointer table (2 bytes). */
#define VIR_INTOB_COUNT          0xB604               /* The number of entries in interface object pointer table. */

/* Memory space for access keys,15 keys per 4-bytes. */
#define VIR_KEY_START            0xB610               /* Authentification key.           */
                                                      /* 0xB64B : Last byte of all keys. */
/* Memory space for memory control blocks. 12 blocks per 10-byte.*/
#define MAX_MCB_COUNT            12                   /* The max. count of MCBs */
#define VIR_MCB_START            0xB650               /* Start of the first MCB */
#define VIR_MCB_00               0xB650               /* Start of MCB  0        */
#define VIR_MCB_01               0xB65A               /* Start of MCB  0        */
#define VIR_MCB_02               0xB664               /* Start of MCB  1        */
#define VIR_MCB_03               0xB66E               /* Start of MCB  2        */
#define VIR_MCB_04               0xB678               /* Start of MCB  3        */
#define VIR_MCB_05               0xB682               /* Start of MCB  4        */
#define VIR_MCB_06               0xB68C               /* Start of MCB  5        */
#define VIR_MCB_07               0xB696               /* Start of MCB  6        */
#define VIR_MCB_08               0xB6A0               /* Start of MCB  7        */
#define VIR_MCB_09               0xB6AA               /* Start of MCB  8        */
#define VIR_MCB_10               0xB6B4               /* Start of MCB  9        */
#define VIR_MCB_11               0xB6BE               /* Start of MCB 10        */
#define VIR_MCB_END              0xB6C7               /* Last byte of MCBs      */
/* 0xB6D2 ~ 0xB6DD reserved. */


/************************************************************
 Second part-6
 Begin address:VIR_BEG_SYS7_EE 0xB6DE
 End address  :VIR_END_SYS7_EE 0xB6F1
 size         :20bytes
 Discription  :Used for load ctrl etc..
*************************************************************/
#define VIR_KNX_PROT             0xB6DE        /* KNX protocol type (2 bytes). */
#define VIR_FAC_ID               0xB6E0        /* facid (2bytes).              */

/* Fixed in sepcification. */
#define VIR_LOAD_STATE_ADDR      0xB6EA        /* Load state for addr table object.  */
#define VIR_LOAD_STATE_ASSOC     0xB6EB        /* Load state for assoc table object. */
#define VIR_LOAD_STATE_APP       0xB6EC        /* Load state for application object. */
#define VIR_LOAD_STATE_PEI       0xB6ED        /* Load state for PEI program object. */
#define VIR_ENABLE_PHYS_ADDR     0xB6EE        /* Authorize flag for physical addr.  */
#define VIR_ENABLE_RESET         0xB6EF        /* Authorize flag for reset APCI.     */
#define VIR_PEI_SERIAL_CONF      0xB6F0        /* Hibyte of configuration of serial protocol. */
                                               /* 0xB6F1 : Lobyte of configuration of serial protocol */

/* Defines for access protection */
#define ACCESS_HIGHEST            0x00        /* The access level the the highest rights. */
#define ACCESS_LOWEST             0x0F        /* The access level the the lowest rights.  */
#define OPCODE_RTS                0x3900      /* Opcode "return sub routine" for HC11 uC. */

/********************************************************
 Defines for memory type,also used by load state machine
 Attention: 0x01 - 0x03 are definitions made by KNXA!
*********************************************************/
#define MEM_TYPE_EE_SYS              0x00        /* Memory is located in system EEPROM. */
#define MEM_TYPE_LORAM               0x01        /* Memory is located in zero page RAM. */
#define MEM_TYPE_HIRAM               0x02        /* Memory is located in high RAM.      */
#define MEM_TYPE_EE_USER             0x03        /* Memory is located in user EEPROM.   */
#define MEM_TYPE_ERROR               0xFF        /* Memory does not exist or is mixed.  */
/* Defines for KNX status byte (addr. 0x60).  */
#define KNX_STATUS_PROG              0x01        /* Status bit:  Programming mode. */
#define KNX_STATUS_RESET             0xC0        /* Status byte: Reset request.    */
/* Define for delete user msg in byte route count. */
#define DELETE_USER_MSG              0x80        /* Delete user message enabled. */
/* Attenttion: The following flag is coded invers to device model 0201. */
#define SC_PHYS_ADDR_WRITE_EN        0x04        /* device control: Setting phys address enable. */
/* Defines for temporary control field device control. */
#define DC_USER_STOPPED              0x01        /* Device control: User stopped. */
#define DC_DUPL_PHYS_ADDR_RCVD       0x02        /* Device control: Duplicate phys address rcvd. */
#define DC_VERIFY_MODE               0x04        /* Device control: Verify mode active.  */
#define DC_RESERVED                  0xF8        /* Device control: Reserved, must be 0. */

/***************************************************************
  Defines for our dummy application used only defined in stack 
  implementation. device model 070x.
****************************************************************/
#define APP_MAIN_SIZE                 7          /* Size of application header. */
#define POS_APP_KEY                   0          /* Offset for app key (2 bytes). */
#define POS_APP_STACK_TYPE            2          /* Offset for stack type.M0705 */
#define POS_APP_CO_TAB_REF            4          /* Offset for communication object table (2 bytes). */
#define POS_APP_STACK_VERSION         6          /* Offset for stack version. */

/* Defines of info IDs.*/
#define IID_RESERVED0                 0x00       /* Info ID resverved. */
#define IID_DEV_DESC0                 0x01       /* Info ID device descriptor 0. */
#define IID_CW_API_VERSION            0x02       /* Info ID Version of API Cw. */
#define IID_ESCAPE                    0xFF       /* Info ID reserved. */


/****************************************************
*   结构名：T_ADDRESS_TABLE
*   描述：  Mask 0705's address table. 
*   参数：  
            BYTE ucAddrTblLen      : address table length including physical address.
            BYTE aucPhyAddr[2]     : physical address,index0-address high byte,index1-address low  byte. 
            BYTE aucGrpAddr[254][2]: group address,[high byte][low byte]
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE ucAddrTblLen;         /* address table length including physical address. */
    union
    {
        struct
        {
            BYTE aucPhyAddr[2];        /* physical address,index0-address high byte,index1-address low  byte. */
            BYTE aucGrpAddr[254][2];   /* group address,[high byte][low byte] */
        }tPhyGrpAddr;
        BYTE aucAddr[255][2];
    }tAddr;
}T_ADDRESS_TABLE;
#pragma pack()

/****************************************************
*   结构名：T_ASSOC_TABLE
*   描述：  Mask 0705's association table. 
*   参数：
            BYTE ucAssocTblLen        : association table length.
               BYTE aucAssocTbl[255][2]  : association table,[Grp addr index][Co. No].
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    BYTE ucAssocTblLen;        /* association table length.                  */
    BYTE aucAssocTbl[255][2];  /* association table,[Grp addr index][Co. No] */
}T_ASSOC_TABLE;
#pragma pack()

/****************************************************
*   结构名：T_KNXMEM_MCB
*   描述：  KNX memory MCB。
*   参数：  
            WORD16 wStart;               Start of the block in virtual address space
            WORD16 wLength;              Length of the block in bytes               
            BYTE   ucAccess;             Access-Levels R/W                          
            BYTE   ucEnCRC:1;            The block has CRC-check                    
            BYTE   :1;                   Reserved                                     
            BYTE   ucMemType:2;          Type of memory                             
            BYTE   ucOwner:3;            Owner of the block                         
            BYTE   :1;                   Reserved                                     
            WORD16 wCrc;                 Checksum of block (CRC16 CCITT)            
*   作者：  Jackson
*   Modified History：
*   2013-7-24  Jackson  新增结构；
****************************************************/
#pragma pack(1)
typedef struct
{
    WORDPTR wStart;              /* Start of the block in virtual address space  */
    WORD16 wLength;              /* Length of the block in bytes                 */
    BYTE   ucAccess;             /* Access-Levels R/W                            */
    BYTE   ucEnCRC:1;            /* The block has CRC-check                      */
    BYTE   ucRsv1:1;             /* Unused                                       */
    BYTE   ucMemType:2;          /* Type of memory                               */
    BYTE   ucOwner:3;            /* Owner of the block                           */
    BYTE   ucRsv2:1;             /* Unused                                       */
    WORD16 wCrc;                 /* Checksum of block (CRC16 CCITT)              */
}T_KNXMEM_MCB;
#pragma pack()

#define POS_MCB_TYPE_OWNER             (sizeof(WORDPTR)+3)       /* type and owner position in structure MCB. */
#define POS_MCB_CRC                    (sizeof(WORDPTR)+4)       /* check sum position in structure MCB.      */

/**************************************************************************************************************
* FunctionName:BYTE KnxMask_GetMemTypeOfRange(WORDPTR dwStart,WORD16 wLength)
* FunctionDescription: rectrieves the memory type of a given address range in virtual memory space.
* InputParameterWORD16 wAddr : the memory address.
* OutputParameterno.
* Return Value：MEM_TYPE_EEPROM : the address in flash area.
            MEM_TYPE_RAM    : the address in RAM area.
            MEM_TYPE_ERROR  : wrong address.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxMask_GetMemTypeOfRange(WORDPTR dwStart,WORD16 wLength);

/**************************************************************************************************************
* FunctionName:BYTE KnxMask_GetMemTypeOfByte(WORDPTR dwAddr)
* FunctionDescription: rectrieves the memory type of a given address in virtual memory space.
* InputParameterWORD16 wAddr : the memory address.
* OutputParameterno.
* Return Value：MEM_TYPE_EEPROM : the address in flash area.
            MEM_TYPE_RAM    : the address in RAM area.
            MEM_TYPE_ERROR  : wrong address.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE KnxMask_GetMemTypeOfByte(WORDPTR dwAddr);


#ifdef __cplusplus
}
#endif

#endif /* _KNX_M0705_H_ */



/* End of file. */

