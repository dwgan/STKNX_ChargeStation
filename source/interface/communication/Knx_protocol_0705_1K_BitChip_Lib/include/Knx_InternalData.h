/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_InternalData.h
* FileIdentifier：None
* Abstract ：本文件由用户来定义KNX协议栈中用户定义的数据。
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



#ifndef _KNX_INTERNALDATA_H_
#define _KNX_INTERNALDATA_H_

#ifdef __cplusplus
extern "C" {
#endif

extern const T_ADDRESS_TABLE g_AddrTable;
extern const T_ASSOC_TABLE   g_AssocTable;
extern const T_KNXMEM_MCB    g_tAddrTblMcb;
extern const T_KNXMEM_MCB    g_tAssocTblMcb;
extern const T_KNXMEM_MCB    g_tAppRamMcb;
extern const T_KNXMEM_MCB    g_tAppMem1Mcb;
extern const T_KNXMEM_MCB    g_tAppMem2Mcb;

#define FLASH_PAGE_SIZE                   1024
#define KNX_SYSDATA_REAL_BASE             0x08004000

/* authentic key. */
#define ACC_KEY_LEVEL0                    0xFF,0xFF,0xFF,0xFF
#define ACC_KEY_LEVEL1                    0xFF,0xFF,0xFF,0xFF
#define ACC_KEY_LEVEL2                    0xFF,0xFF,0xFF,0xFF


/*****************************************************************
Operation definition.
******************************************************************/
/* (g_AddrTable.ucAddrTblLen)                     get address table length.  */
#define GET_ADDR_TBL_LEN                  (KnxMem_GetByte(VIR_ADDR_TABLE_LENGTH))

/* (g_AddrTable.tAddr.tPhyGrpAddr.aucPhyAddr[0])  get physical address high. */
#define GET_PHY_ADDR_HIGH                 (KnxMem_GetByte(VIR_PHY_ADDR_HI))

/* (g_AddrTable.tAddr.tPhyGrpAddr.aucPhyAddr[1])  get physical address low.  */
#define GET_PHY_ADDR_LOW                  (KnxMem_GetByte(VIR_PHY_ADDR_LOW))

/* ((g_AddrTable.tAddr.aucAddr[0][0]<<8) + g_AddrTable.tAddr.aucAddr[0][1]) get total physical address. */
#define GET_PHY_ADDRESS                   (KnxMem_GetWord(VIR_PHY_ADDR))

/* get the group address by the group address index. index >= 1. */
#define GET_GRP_ADDR_HIGH(ucGrpIndex)     (g_AddrTable.tAddr.aucAddr[ucGrpIndex][0])
#define GET_GRP_ADDR_LOW(ucGrpIndex)      (g_AddrTable.tAddr.aucAddr[ucGrpIndex][1])
#define GET_GRP_ADDRESS(ucGrpIndex)       ((((WORD16)GET_GRP_ADDR_HIGH(ucGrpIndex))<<8) + GET_GRP_ADDR_LOW(ucGrpIndex))
/* get the association table parameter. */
#define GET_ASSOC_TBL_LEN                 (g_AssocTable.ucAssocTblLen)
#define GET_ASSOC_GRPINDEX(ucIndex)       (g_AssocTable.aucAssocTbl[ucIndex][0])
#define GET_ASSOC_COMOBJNO(ucIndex)       (g_AssocTable.aucAssocTbl[ucIndex][1])
#define HI_BYTE(wData)                    ((BYTE)(((WORD16)(wData) >> 8) & 0x00FF))
#define LOW_BYTE(wData)                   ((BYTE)((WORD16)(wData) & 0x00FF))
#define VIR_TO_REAL_OFFSET                (KNX_SYSDATA_REAL_BASE - VIR_BEG_USER_EE)     /* the offset between real and virtual.    */
#define GET_VIR_OF_REAL(wRealAddr)        ((WORDPTR)(wRealAddr) - VIR_TO_REAL_OFFSET)   /* get one real address's virtual address. */
#define GET_REAL_OF_VIR(wVirAddr)         ((WORDPTR)(wVirAddr) + VIR_TO_REAL_OFFSET)    /* get one virtual address's real address. */
#define FAC_1                             (0x01)
#define FAC_2                             (0xbf)

#ifdef __cplusplus
}
#endif

#endif /* _KNX_INTERNALDATA_H_ */



/* End of file. */


