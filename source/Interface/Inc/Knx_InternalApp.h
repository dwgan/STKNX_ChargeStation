/****************************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_InternalApp.h
* FileIdentifier：None
* Abstract ：knx internal application source file header file.
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
*******************************************************************************************/


#ifndef _KNX_INTERNALAPP_H_
#define _KNX_INTERNALAPP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define APP_MAIN_FUNC               0xFA           /* application main function ID        */
#define APP_MAIN_INIT_FUNC          0xFB           /* application main init. function ID  */
#define APP_SAVE_FUNC               0xFC           /* application save function ID.       */

#define APP_HANDLER_MAIN            0x01           /* application entry */
#define APP_HANDLER_INIT            0x02           /* application initialize entry.    */
#define APP_HANDLER_SAVE            0x03           /* application save handling entry. */
#define APP_HANDLER_BUS_SAVE        0x04           /* application save handling when bus voltage down.  */
#define APP_HANDLER_POWER_SAVE      0x05           /* application save handling when power supply down. */
#define APP_HANDLER_WDG_RESET       0x06           /* application reset watchdog entry. */
#define APP_HANDLER_RESET_CPU       0x07           /* CPU reset entry.         */
#define APP_HANDLER_PRGM_LED_OFF    0x08           /* OFF program LED entry.   */
#define APP_HANDLER_PRGM_LED_ON     0x09           /* light program LED entry. */
#define APP_HANDLER_PRGM_KEY        0x0a           /* program key check entry. */
#define APP_HANDLER_BUS_POWER_CHECK 0x0b           /* bus power check entry.   */
#define APP_HANDLER_ADC_OP          0x0c           /* adc operation entry. */



/*****************************************************************************************************************
* FunctionName:VOID Knx_UserAppHandler_Set(APP_HANDLER pfHandler,BYTE ucHandlerType)
* FunctionDescription: application set handler relate to the device design.
* InputParameterAPP_HANDLER pfHandler:application handler.
            BYTE ucHandlerType   :handler type.
                 APP_HANDLER_MAIN            0x01           application entry
                 APP_HANDLER_INIT            0x02           application initialize entry.
                 APP_HANDLER_SAVE            0x03           application save handling entry.
                 APP_HANDLER_BUS_SAVE        0x04           application save handling when bus voltage down.
                 APP_HANDLER_POWER_SAVE      0x05           application save handling when power supply down.
                 APP_HANDLER_WDG_RESET       0x06           application reset watchdog entry.
                 APP_HANDLER_RESET_CPU       0x07           CPU reset entry.
                 APP_HANDLER_PRGM_LED_OFF    0x08           OFF program LED entry.
                 APP_HANDLER_PRGM_LED_ON     0x09           light program LED entry.
                 APP_HANDLER_PRGM_KEY        0x0a           program key check entry.
                 APP_HANDLER_BUS_POWER_CHECK 0x0b           bus power check entry.
* OutputParameterno.
* Return Value：no.
* Other Description:application realize the design in self source files.these handler will be used by KNX protocol
            stack internally.
* Modified Date VersionNumber Author ModifiedContent
* ------------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                  Create
********************************************************************************************************************/
VOID Knx_UserAppHandler_Set(VOID *pfHandler,BYTE ucHandlerType);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_BusSave(VOID)
* FunctionDescription: the internal bus save entry used for calling user extenal bus save function when bus voltage down.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_BusSave(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_SupplySave(VOID)
* FunctionDescription: the internal supply save entry used for calling user extenal supply save function when supply down.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_SupplySave(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_InteralApp_Main(VOID)
* FunctionDescription: internal application entry,used to call the user registering extenal application entry.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_InteralApp_Main(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_InternalApp_Init(VOID)
* FunctionDescription: the internal app init. entry used for calling user's application initializing function.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_InternalApp_Init(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_ResetDog(VOID)
* FunctionDescription: the internal dog handle entry used for calling user's dog handler.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_ResetDog(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_ResetDev(VOID)
* FunctionDescription: the internal device reset entry used for calling user's device reset function.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_ResetDev(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_PrgmLedOff(VOID)
* FunctionDescription: the internal entry for switching off the program LED.it will call the user's program led handler.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_PrgmLedOff(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_PrgmLedOn(VOID)
* FunctionDescription: the internal entry for switching on the program LED.it will call the user's program led handler.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_PrgmLedOn(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_PrgmKey(VOID)
* FunctionDescription: the internal entry for check the program key.it will call the user's program key handler.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_PrgmKey(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_Internal_BusPowerCheck(VOID)
* FunctionDescription: the internal entry for checking the bus power.it will call the user's bus power handler.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_Internal_BusPowerCheck(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_InternalApp_Save(VOID)
* FunctionDescription: the internal entry for application save.
* InputParameterno.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_InternalApp_Save(VOID);

/**************************************************************************************************************
* FunctionName:BOOL Knx_InternalApp_Entry(BYTE ucFuncId)
* FunctionDescription: the internal application entry used to call different internal function.
* InputParameterBYTE ucFuncId:internal function ID.
                 APP_MAIN_FUNC      : internal application main function.
                 APP_MAIN_INIT_FUNC : internal application initializing function.
                 APP_SAVE_FUNC      : internal application save function.
* OutputParameterno.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_InternalApp_Entry(BYTE ucFuncId);

/**************************************************************************************************************
* FunctionName:BOOL Knx_InternalApp_Adc(BYTE ucLogDevNo,BYTE ucLogChnl,BYTE ucCunt,WORD16 *pwData)
* FunctionDescription: the internal ADC operation entry for application.
* InputParameterBYTE ucChnl:channel no.
            BYTE ucCunt:sample count.
            WORD16 *pwData:return data pointer.
* OutputParameterWORD16 *pwData:return data.
* Return Value：TRUE / FALSE.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BOOL Knx_InternalApp_Adc(BYTE ucLogDevNo,BYTE ucLogChnl,BYTE ucCunt,WORD16 *pwData);




#ifdef __cplusplus
}
#endif

#endif /* _KNX_INTERNALAPP_H_ */



/* end of file. */

