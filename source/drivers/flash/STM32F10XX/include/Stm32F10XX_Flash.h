/*******************************************************************
* (C) Copyright 2016 *********** company.
*
* File Name        : Stm32F10XX_Flash.h
*
* File Description : Header file for stm32f10xx flash definition.
*
* Other Description: No.
*
* Version          : 1.00
*
* Author           : 
*
* Data             : 2016.7.28
*
* Modification Rec.:
*   Modify Data    : 2016.7.28
*   Operator       :
*   Version        : 1.00
*   Action         : Creation.
*
********************************************************************/


#ifndef _STM32F10XX_FLASH_H_
#define _STM32F10XX_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif






/****************************************************
*   Structure£º  T_FTFA_MEM_MAP
*   Description£ºmemory map of flash management register.
*   Parameter:
*   Authour£º
*   Modify record:
*   Date:  2016-8-2 creat.
****************************************************/
typedef struct FTFA_MemMap {
    WORD32 dwAccCtrlR;
    WORD32 dwKeyR;
    WORD32 dwOptKeyR;
    WORD32 dwStR;
    WORD32 dwCtrlR;
    WORD32 dwAddrR;
    WORD32 dwRsv;
    WORD32 dwOptByteR;
    WORD32 dwWrtPrtR;
} volatile *T_FTFA_MEM_MAP;

/* base address for map memory. */
#define FTFA_BASE_PTR                            ((T_FTFA_MEM_MAP)0x40022000u)
#define FTFA_ACCCTRL_REG(base)                   ((base)->dwAccCtrlR)
#define FTFA_KEY_REG(base)                       ((base)->dwKeyR)
#define FTFA_OPTKEY_REG(base)                    ((base)->dwOptKeyR)
#define FTFA_ST_REG(base)                        ((base)->dwStR)
#define FTFA_CTRL_REG(base)                      ((base)->dwCtrlR)
#define FTFA_ADDR_REG(base)                      ((base)->dwAddrR)
#define FTFA_OPTBYTE_REG(base)                   ((base)->dwOptByteR)
#define FTFA_WRTPRT_REG(base)                    ((base)->dwWrtPrtR)

#define FTFA_ACCCTRL                             FTFA_ACCCTRL_REG(FTFA_BASE_PTR)
#define FTFA_KEY                                 FTFA_KEY_REG(FTFA_BASE_PTR)
#define FTFA_OPTKEY                              FTFA_OPTKEY_REG(FTFA_BASE_PTR)
#define FTFA_ST                                  FTFA_ST_REG(FTFA_BASE_PTR)
#define FTFA_CTRL                                FTFA_CTRL_REG(FTFA_BASE_PTR)
#define FTFA_ADDR                                FTFA_ADDR_REG(FTFA_BASE_PTR)
#define FTFA_OPTBYTE                             FTFA_OPTBYTE_REG(FTFA_BASE_PTR)
#define FTFA_WRTPRT                              FTFA_WRTPRT_REG(FTFA_BASE_PTR)

/* mask definition for register operation. */
#define FLASH_ACR_LATENCY_MASK              0x00000007u  /* Latency */
#define FLASH_LATENCY_1                     0x01
#define FLASH_LATENCY_2                     0x02
#define FLASH_ACR_PRFTBS_MASK               0x00000020u  /* Prefetch buffer status */
#define FLASH_ACR_PRFTBE_MASK               0x00000010u  /* Prefetch buffer enable */
#define FLASH_ACR_HLFCYA_MASK               0x00000008u  /* Flash half cycle access enable */

#define FLASH_ST_READY                      0x00
#define FLASH_ST_BUSY                       0x01

/* parameter definition for stm32f10xx flash. */
#define FLASH_KEY1             0x45670123   /* unlock key1 */
#define FLASH_KEY2             0xCDEF89AB   /* unlock key2 */
#define FLASH_RDPRT_KEY        0x00A5       /* read option unlock key */

#define FTFA_CMD_ERASE_TIME    40           /* flash erasing over time.    */
#define FTFA_CMD_WRITE_TIME    10           /* flash programing over time. */


/* timer handler for flash operation. */
typedef struct
{
    BOOL   (*pfAppCheck)(VOID);         /* application needs to be checked for true before erasing or programing. TRUE means waiting. */
    WORD32 (*pfGetMs)(VOID);            /* the handler for getting ms-time. */
    WORD32 (*pfGetDlyMs)(WORD32);       /* the handler for getting ms-delay base an old ms-time. */
}T_FLASH_TMOPER;




/*************************************************************************************
* function name   : VOID Stm32F10xx_Flash_Reg(BYTE ucLogNo,BYTE ucDevNo,VOID *ptPara)
* Description     : register the flash driver to the up layer.
* Input parameter : BYTE ucLogNo : flash logical no.
                    BYTE ucDevNo : flash physical no.
                    VOID *ptPara : timer handler for time operation.
* Output parameter: no.
* Return          : no.
* Other description:
     this function used to register the flash driver to the managerment layer.
     in order to operate the timer, caller should hang the handler of timer
     by *ptPara.
* Modify date     Ver.     Modifier      Action
* -----------------------------------------------------------------------------------
* 2016-08-03      V1.00                 Creation
*************************************************************************************/
VOID Stm32F10xx_Flash_Reg(BYTE ucLogNo,BYTE ucDevNo,VOID *ptPara);


#ifdef __cplusplus
}
#endif

#endif // _STM32F10XX_FLASH_H_

// End of Flash.h

