/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_LoadCtrl.h
* FileIdentifier：None
* Abstract ：KNX加载控制头文件。
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


#ifndef _KNX_LOADCTRL_H_
#define _KNX_LOADCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif




/* Definition of load state machine */

/* The load states */
#define LOAD_STATE_UNLOADED            0x00    /* unloaded  */
#define LOAD_STATE_LOADED              0x01    /* loaded    */
#define LOAD_STATE_LOADING             0x02    /* loading   */
#define LOAD_STATE_ERROR               0x03    /* Load error*/
#define LOAD_STATE_UNLOADING           0x04    /* unloading */

/* The load events */
#define LOAD_EVENT_NONE                0x00    /* Nothing to do       */
#define LOAD_EVENT_START               0x01    /* Start to load       */
#define LOAD_EVENT_COMPLETE            0x02    /* Loading is complete */
#define LOAD_EVENT_SEGMENT             0x03    /* load segment        */
#define LOAD_EVENT_UNLOAD              0x04    /* Unload              */

/* The segment events */
#define SEG_EVENT_ALLOC                0x00    /* Allocation of abs. memory area       */
#define SEG_EVENT_STACK                0x01    /* Allocation of stack area (dummy)     */
#define SEG_EVENT_CONTROL              0x02    /* Set segment pointer (e.g. user main) */
#define SEG_EVENT_TASK_PTR             0x03    /* Set pointer to user init, save       */
#define SEG_EVENT_TASK_CONTROL1        0x04    /* Set user objects count and pointer   */
#define SEG_EVENT_TASK_CONTROL2        0x05    /* Set AL callback and CO pointer       */

/* Owner types of memory blocks used for memory control blocks MCB. */
#define OWNER_SYS                      0x00    /* Owner is system                      */
#define OWNER_ADDR                     0x01    /* Owner is address table               */
#define OWNER_ASSOC                    0x02    /* Owner is assiciation table           */
#define OWNER_APP                      0x03    /* Owner is application program         */
#define OWNER_PEI                      0x04    /* Owner is PEI program (only in 070x)  */
#define OWNER_ERROR_NONE               0x05    /* Error: Memory does not exist         */
#define OWNER_ERROR_MIXED              0x06    /* Error: Memory has not a unique owner */
#define OWNER_FREE                     0x07    /* Memory is not used                   */
#define OWNER_MAX_VALID                0x04    /* Max ID of a valid owner              */

#define FIRST_MCB_INDEX                0x00    /* First index for memory control records */
#define LAST_MCB_INDEX                 0x0B    /* Max number of memory control records   */
#define END_OF_MCB_INDEX               0xFF    /* Used as return value at end of MCB iteration */


/**************************************************************************************************************
* FunctionName:BOOL Knx_LoadControl(BYTE* pucUpFrame,BYTE *pucDwFrame)
* FunctionDescription: Handling the load control requests sent by property write to PID_LOAD_STATE_CONTROL Load state 
            machine according to AN080.
* InputParameterBYTE *pucUpFrame:up frame buffer's pointer.
            BYTE *pucDwFrame:down frame buffer's pointer.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_LoadControl(BYTE* pucUpFrame);

/**************************************************************************************************************
* FunctionName:BOOL Knx_LoadStart(BYTE ucObjIndex)
* FunctionDescription: This function handles the load start request.
* InputParameterBYTE ucObjIndex:object index.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_LoadStart(BYTE ucObjIndex);

/**************************************************************************************************************
* FunctionName:BOOL Knx_LoadComplete(BYTE ucObjIndex)
* FunctionDescription: This function handles the load complete request.
* InputParameterBYTE ucObjIndex:object index.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_LoadComplete(BYTE ucObjIndex);

/**************************************************************************************************************
* FunctionName:BOOL Knx_GetNextMcb(BYTE *pucIndex, T_KNXMEM_MCB *ptMcb)
* FunctionDescription: This function retrieves the next memory control block beginning from the given index.
            This function may be used for an iteration through all MCBs.
* InputParameterBYTE *pucIndex     :MCB index.
            T_KNXMEM_MCB *ptMcb:MCB block.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:The function does not check whether the returned block is valid.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_GetNextMcb(BYTE *pucIndex, T_KNXMEM_MCB *ptMcb);

/**************************************************************************************************************
* FunctionName:BOOL Knx_WriteMcb(BYTE ucIndex, T_KNXMEM_MCB* pMcb)
* FunctionDescription: This function writes the MCB to the location given by nIndex.
* InputParameterBYTE *pucIndex     :MCB index.
            T_KNXMEM_MCB *ptMcb:MCB block.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:The function does not check whether the returned block is valid.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_WriteMcb(BYTE ucIndex, T_KNXMEM_MCB* ptMcb);

/**************************************************************************************************************
* FunctionName:BOOL Knx_WriteChecksum(BYTE ucIndex, WORD16 wChecksum)
* FunctionDescription: This function writes the checksum into the MCB given by ucIndex
* InputParameterBYTE ucIndex     :MCB index.
            WORD16 wChecksum : check sum.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:In the device model 070x, the memory checksums are stored in the corresponding MCB.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_WriteChecksum(BYTE ucIndex, WORD16 wChecksum);

/**************************************************************************************************************
* FunctionName:BOOL Knx_LoadUnload(BYTE ucObjIndex)
* FunctionDescription: This function handles the unload request
* InputParameterBYTE ucObjIndex : object index.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_LoadUnload(BYTE ucObjIndex);

/**************************************************************************************************************
* FunctionName:BOOL Knx_LoadSegment(BYTE* pucUpFrame)
* FunctionDescription: This function handles the load segment requests.
* InputParameterBYTE* pucUpFrame : frame buffer pointer.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_LoadSegment(BYTE* pucUpFrame);

/**************************************************************************************************************
* FunctionName:BOOL Knx_SegAllocation(BYTE *pucUpFrame)
* FunctionDescription: This function handles the load segment request "Absolute Code/Data Allocation Record"
* InputParameterBYTE* pucUpFrame : frame buffer pointer.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_SegAllocation(BYTE *pucUpFrame);

/**************************************************************************************************************
* FunctionName:BOOL Knx_SegControl(BYTE* pucUpFrame)
* FunctionDescription: This function handles the load segment request "Segment Control Record".
* InputParameterBYTE* pucUpFrame : frame buffer pointer.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_SegControl(BYTE* pucUpFrame);

/**************************************************************************************************************
* FunctionName:BOOL Knx_SegControl(BYTE* pucUpFrame)
* FunctionDescription: This function handles the load segment request "Task Control Record-1".
* InputParameterBYTE* pucUpFrame : frame buffer pointer.
* OutputParameterno.
* Return Value：TRUE or FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_SegTaskControl1(BYTE* pucUpFrame);

/**************************************************************************************************************
* FunctionName:BYTE Knx_GetMcbOwner(WORD16 wAddr, WORD16 wLength)
* FunctionDescription: return the owner of a given memory location in eeprom memory space.
* InputParameterBYTE* pucUpFrame : frame buffer pointer.
* OutputParameterno.
* Return Value：ID.
* Other Description:Only unused blocks can be allocated.The maximum of MCBs are defined in LAST_MCB_INDEX
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE Knx_GetMcbOwner(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* FunctionName:BYTE Knx_GetMcb(WORD16 wAddr, WORD16 wLength, T_KNXMEM_MCB *ptMcb)
* FunctionDescription: This function returns the owner of a given memory block in virtual memory space and retrieves the
            MCB data copied to pMcb.This pointer must point to a valid buffer with size of MCB.
* InputParameterWORD16 wAddr  : memory address.
            WORD16 wLength:memory length.
            T_KNXMEM_MCB *ptMcb:ginven MCB.
* OutputParameterno.
* Return Value：ID.
* Other Description:The maximum of MCBs are defined in LAST_MCB_INDEX
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE Knx_GetMcb(WORD16 wAddr, WORD16 wLength, T_KNXMEM_MCB *ptMcb);

/**************************************************************************************************************
* FunctionName:BOOL Knx_CheckLoadStates(VOID)
* FunctionDescription: This function checks whether the load states are ok.
* InputParameterno.
* OutputParameterno.
* Return Value：ID.
* Other Description:It is called at startup an on disconnect.Never call this function during a download,because the 
            load states may be set to error.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_CheckLoadStates(VOID);

/**************************************************************************************************************
* FunctionName:BYTE Knx_GetLoadState(BYTE ucObjIndex)
* FunctionDescription: This function returns the load state of the given object.
* InputParameterno.
* OutputParameterno.
* Return Value：load state.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE Knx_GetLoadState(BYTE ucObjIndex);

/**************************************************************************************************************
* FunctionName:BOOL Knx_SetLoadState(BYTE ucObjIndex, BYTE ucLoadState)
* FunctionDescription: This function sets the load state of the given object.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FLASE.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_SetLoadState(BYTE ucObjIndex, BYTE ucLoadState);

/**************************************************************************************************************
* FunctionName:BOOL KnxLc_IsReadingAllowed(WORD16 wAddr, WORD16 wLength)
* FunctionDescription: This function checks whether a read operation is allowed.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FLASE.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_IsReadingAllowed(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* FunctionName:BOOL Knx_IsWritingAllowed(WORD16 wAddr, WORD16 wLength)
* FunctionDescription: This function checks whether a write operation is allowed.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FLASE.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_IsWritingAllowed(WORD16 wAddr, WORD16 wLength);

/**************************************************************************************************************
* FunctionName:BOOL Knx_GetRamAlloc(BYTE ucRamType, WORD16 *pwAddr, WORD16 *pwLength)
* FunctionDescription: This function retrieves the start address and the size of the virtual RAM memory allocated via 
            load controls.
* InputParameterBYTE ucRamType : ram type.
            WORD16 *pwAddr : ram address.
            WORD16 *pwLength:ram length.
* OutputParameterno.
* Return Value：TRUE / FLASE.
* Other Description:no.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_GetRamAlloc(BYTE ucRamType, WORDPTR *pwAddr, WORD16 *pwLength);








#ifdef __cplusplus
}
#endif

#endif /* _KNX_LOADCTRL_H_ */



/* end of file */
