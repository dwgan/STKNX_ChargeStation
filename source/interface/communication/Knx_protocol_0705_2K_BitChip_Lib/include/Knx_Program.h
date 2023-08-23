/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：Knx_Prop.h
* FileIdentifier：None
* Abstract ：本文件为KNX编程状态定义。
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



#ifndef _KNX_PROGRAM_H_
#define _KNX_PROGRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* KNX programming key */
#define    KNX_PRG_KEY_OFF                    0x00                /* Key was not pressed            */
#define    KNX_PRG_KEY_NEW                    0x10                /* Key was just pressed           */
#define    KNX_PRG_KEY_ON                     0x20                /* Key was pressed long enough    */
#define    KNX_PRG_KEY_PRESSED                0x80                /* Key actually pressed           */
#define    KNX_PRG_KEY_MASK                   0x30                /* Key state without pressed flag */
#define    KNX_PRG_KEY_MASK_EX                0xF0                /* Key state with pressed flag    */

#define    KNX_KEY_TIME                       50                  /* Debounce time before pressed short */

/* KNX programming led  */
#define    KNX_PRGLED_OFF                     0x00                /* LED is switched off      */
#define    KNX_PRGLED_ON                      0x01                /* LED is switched on       */
#define    KNX_PRGLED_BLINK_SLOW              0x02                /* LED is blinking slow     */
#define    KNX_PRGLED_BLINK_FAST              0x03                /* LED is blinking fast     */
#define    KNX_PRGLED_MASK                    0x03                /* Mask to access LED flags */

#define    TIME_EXP_BLINK_SLOW                9                   /* Blinking time is 2^exp: here 512 ms */
#define    TIME_EXP_BLINK_FAST                6                   /* Blinking time is 2^exp: here  64 ms */



/**************************************************************************************************************
* FunctionName:VOID Knx_GetProgKey(VOID)
* FunctionDescription: checks the KNX key state and stores it.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:it should be called periodically.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_GetProgKey(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_SetPrgLed(VOID)
* FunctionDescription: sets the state of the KNX learning LED according to the state in g_ucProgramState.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:it should be called periodically.
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_SetPrgLed(VOID);

/**************************************************************************************************************
* FunctionName:BYTE Knx_GetPrgLedState(VOID)
* FunctionDescription: retrieves the current state of the programming LED.
* InputParameterBYTE ucState.
* OutputParameterno.
* Return Value：KNX_PRGLED_OFF / KNX_PRGLED_ON
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
BYTE Knx_GetPrgLedState(VOID);

/**************************************************************************************************************
* FunctionName:VOID Knx_SetPrgLedState(BYTE ucState)
* FunctionDescription: set the program LED state.
* InputParameterBYTE ucState.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2014-03-20   V1.00                   Create
***************************************************************************************************************/
VOID Knx_SetPrgLedState(BYTE ucState);













#ifdef __cplusplus
}
#endif

#endif /* _KNX_PROGRAM_H_ */



/* End of file. */

