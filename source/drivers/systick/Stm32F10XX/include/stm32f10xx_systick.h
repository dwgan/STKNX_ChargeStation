/******************************************************************************
* File       : systick.h
* Function   : Systick driver for stm32f10x
* description: This driver realise the basic function of systick initialization.
* Version    : V1.00
* Author     : Ian
* Date       : 31sr Jul 2016
* History    :  No.  When           Who           What
*               1    31/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _STM32F10XX_SYSTICK_H_
#define _STM32F10XX_SYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif


/* SysTick parameter data field position definition */
#define SYSTICK_TMR_TYPE_ID_POS                 (0)                            /* Field of device type ID          */
#define SYSTICK_DEV_NO_POS                      (1)                            /* Field of device logic No.        */
#define SYSTICK_TMR_MODE_POS                    (2)                            /* Field of timer working mode      */
#define SYSTICK_INT_PERIOD_POS                  (3)                            /* Field of interrupt period        */
#define SYSTICK_INT_PERIOD_SCALE                (4)                            /* Field of interrupt scale         */


/* SysTick base addresses */
#define SYSTICK_BASE                            ((T_SYSTICK_MEM_MAP)0xE000E010)/* SysTick Base Address             */

/* SysTick Register accessors */
#define SYSTICK_CTRL                            (SYSTICK_BASE->CTRL)           /* SysTick configuration struct     */
#define SYSTICK_LOAD                            (SYSTICK_BASE->LOAD)           /* SysTick configuration struct     */
#define SYSTICK_VAL                             (SYSTICK_BASE->VAL)            /* SysTick configuration struct     */
#define SYSTICK_CALIB                           (SYSTICK_BASE->CALIB)          /* SysTick configuration struct     */


/* SysTick Control / Status Register Definitions */
#define SYSTICK_CTRL_COUNTFLAG_POS              (16)                           /* SysTick CTRL: COUNTFLAG Position */
#define SYSTICK_CTRL_COUNTFLAG_MASK             (0x00010000)                   /* SysTick CTRL: COUNTFLAG Mask     */

#define SYSTICK_CTRL_CLKSOURCE_POS              (2)                            /* SysTick CTRL: CLKSOURCE Position */
#define SYSTICK_CTRL_CLKSOURCE_MASK             (0x00000004)                   /* SysTick CTRL: CLKSOURCE Mask     */

#define SYSTICK_CTRL_TICKINT_POS                (1)                            /* SysTick CTRL: TICKINT Position   */
#define SYSTICK_CTRL_TICKINT_MASK               (0x00000002)                   /* SysTick CTRL: TICKINT Mask       */

#define SYSTICK_CTRL_ENABLE_POS                 (0)                            /* SysTick CTRL: ENABLE Position    */
#define SYSTICK_CTRL_ENABLE_MASK                (0x00000001)                   /* SysTick CTRL: ENABLE Mask        */

/* SysTick Reload Register Definitions */
#define SYSTICK_LOAD_RELOAD_POS                 (0)                            /* SysTick LOAD: RELOAD Position    */
#define SYSTICK_LOAD_RELOAD_MASK                (0x00FFFFFF)                   /* SysTick LOAD: RELOAD Mask        */

/* SysTick Current Register Definitions */
#define SYSTICK_VAL_CURRENT_POS                 (0)                            /* SysTick VAL: CURRENT Position    */
#define SYSTICK_VAL_CURRENT_MASK                (0x00FFFFFF)                   /* SysTick VAL: CURRENT Mask        */

/* SysTick Calibration Register Definitions */
#define SYSTICK_CALIB_NOREF_POS                 (31)                           /* SysTick CALIB: NOREF Position    */
#define SYSTICK_CALIB_NOREF_MASK                (0x80000000)                   /* SysTick CALIB: NOREF Mask        */

#define SYSTICK_CALIB_SKEW_POS                  (30)                           /* SysTick CALIB: SKEW Position     */
#define SYSTICK_CALIB_SKEW_MASK                 (0x40000000)                   /* SysTick CALIB: SKEW Mask         */

#define SYSTICK_CALIB_TENMS_POS                 (0)                            /* SysTick CALIB: TENMS Position    */
#define SYSTICK_CALIB_TENMS_MASK                (0x00FFFFFF)                   /* SysTick CALIB: TENMS Mask        */


/* Data structure definition */
/****************************************************
*   Structure£º  T_SYSTICK_MEM_MAP
*   Description£ºMemory map of SysTick registers.
*   Parameter:    WORD32 CTRL;         SysTick Control and Status Register 
*                 WORD32 LOAD;         SysTick Reload Value Register       
*                 WORD32 VAL;          SysTick Current Value Register      
*                 WORD32 CALIB;        SysTick Calibration Register    
*   Authour£º    Ian
*   Modify record:
*   Date:  2016-7-31 creat.
****************************************************/
typedef struct _T_SYSTICK_MEM_MAP
{
    WORD32 CTRL;         /* SysTick Control and Status Register */
    WORD32 LOAD;         /* SysTick Reload Value Register       */
    WORD32 VAL;          /* SysTick Current Value Register      */
    WORD32 CALIB;        /* SysTick Calibration Register        */
}volatile *T_SYSTICK_MEM_MAP;



/* Declaration of functions */
/**************************************************************************
* Funciton: void SysTick_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
* Descrip.: Register system ticker.
* Input   : BYTE ucLogNo      Device logic No.
*           BYTE ucDevNo      Device physical No.
*           VOID *ptPara      None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
void SysTick_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara);

/**************************************************************************
* Funciton: void SysTick_Timer_isr(void)
* Descrip.: interrupt process function of SysTick
* Input   : None
* Output  : None
* Return  : None
* Note    : None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
**************************************************************************/
void SysTick_Timer_isr(void);


#ifdef __cplusplus
}
#endif

#endif /* _STM32F10XX_SYSTICK_H_ */



