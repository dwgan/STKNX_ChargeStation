/*******************************************************************
* (C) Copyright 2016 *********** company.
*
* File Name        : Stm32G0XX_Flash.h
*
* File Description : Header file for stm32g0xx flash definition.
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


#ifndef _STM32G0XX_FLASH_H_
#define _STM32G0XX_FLASH_H_

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
typedef struct
{
    WORD32 dwAccCtrlR;          /* FLASH Access Control register,                     Address offset: 0x00 */
    WORD32 dwRESERVED1;         /* Reserved1,                                         Address offset: 0x04 */
    WORD32 dwKeyR;              /* FLASH Key register,                                Address offset: 0x08 */
    WORD32 dwOptKeyR;           /* FLASH Option Key register,                         Address offset: 0x0C */
    WORD32 dwStR;               /* FLASH Status register,                             Address offset: 0x10 */
    WORD32 dwCtrlR;             /* FLASH Control register,                            Address offset: 0x14 */
    WORD32 dwEccR;              /* FLASH ECC register,                                Address offset: 0x18 */
    WORD32 dwRESERVED2;         /* Reserved2,                                         Address offset: 0x1C */
    WORD32 dwOptByteR;          /* FLASH Option register,                             Address offset: 0x20 */
    WORD32 dwPCROP1ASR;         /* FLASH Bank PCROP area A Start address register,    Address offset: 0x24 */
    WORD32 dwPCROP1AER;         /* FLASH Bank PCROP area A End address register,      Address offset: 0x28 */
    WORD32 dwWrtPrtAR;          /* FLASH Bank WRP area A address register,            Address offset: 0x2C */
    WORD32 dwWrtPrtBR;          /* FLASH Bank WRP area B address register,            Address offset: 0x30 */
    WORD32 dwPCROP1BSR;         /* FLASH Bank PCROP area B Start address register,    Address offset: 0x34 */
    WORD32 dwPCROP1BER;         /* FLASH Bank PCROP area B End address register,      Address offset: 0x38 */
    WORD32 dwRESERVED3[17];     /* Reserved3,                                         Address offset: 0x3C */
    WORD32 dwSec;               /* FLASH security register ,                          Address offset: 0x80 */
}volatile *T_FTFA_MEM_MAP;

/* base address for map memory. */
#define FTFA_BASE_PTR                            ((T_FTFA_MEM_MAP)0x40022000UL)
#define FTFA_ACCCTRL_REG(base)                   ((base)->dwAccCtrlR)
#define FTFA_KEY_REG(base)                       ((base)->dwKeyR)
#define FTFA_OPTKEY_REG(base)                    ((base)->dwOptKeyR)
#define FTFA_ST_REG(base)                        ((base)->dwStR)
#define FTFA_CTRL_REG(base)                      ((base)->dwCtrlR)
#define FTFA_ECCR_REG(base)                      ((base)->dwEccR)
#define FTFA_OPTBYTE_REG(base)                   ((base)->dwOptByteR)
#define FTFA_PCROP1ASR_REG(base)                 ((base)->dwPCROP1ASR)
#define FTFA_PCROP1AER_REG(base)                 ((base)->dwPCROP1AER)
#define FTFA_WRTPRTA_REG(base)                   ((base)->dwWrtPrtAR)
#define FTFA_WRTPRTB_REG(base)                   ((base)->dwWrtPrtBR)
#define FTFA_PCROP1BSR_REG(base)                 ((base)->dwPCROP1BSR)
#define FTFA_PCROP1BER_REG(base)                 ((base)->dwPCROP1BER)

#define FTFA_ACCCTRL                             FTFA_ACCCTRL_REG(FTFA_BASE_PTR)
#define FTFA_KEY                                 FTFA_KEY_REG(FTFA_BASE_PTR)
#define FTFA_OPTKEY                              FTFA_OPTKEY_REG(FTFA_BASE_PTR)
#define FTFA_ST                                  FTFA_ST_REG(FTFA_BASE_PTR)
#define FTFA_CTRL                                FTFA_CTRL_REG(FTFA_BASE_PTR)
#define FTFA_ADDR                                FTFA_ADDR_REG(FTFA_BASE_PTR)
#define FTFA_OPTBYTE                             FTFA_OPTBYTE_REG(FTFA_BASE_PTR)
#define FTFA_WRTPRTA                             FTFA_WRTPRTA_REG(FTFA_BASE_PTR)
#define FTFA_WRTPRTB                             FTFA_WRTPRTB_REG(FTFA_BASE_PTR)
#define FTFA_ECCR                                FTFA_ECCR_REG(FTFA_BASE_PTR)

/* mask definition for register operation. */
#define FLASH_ACR_LATENCY_MASK                   0x00000007u  /* Latency */
#define FLASH_LATENCY_1                          0x01
#define FLASH_LATENCY_2                          0x02
#define FLASH_ACR_PRFTBS_MASK                    0x00000020u  /* Prefetch buffer status */
#define FLASH_ACR_PRFTBE_MASK                    0x00000010u  /* Prefetch buffer enable */
#define FLASH_ACR_HLFCYA_MASK                    0x00000008u  /* Flash half cycle access enable */

#define FLASH_ST_READY                           0x00
#define FLASH_ST_BUSY                            0x01


#define FTFA_CMD_ERASE_TIME                      40           /* flash erasing over time.    */
#define FTFA_CMD_WRITE_TIME                      10           /* flash programing over time. */


/******************  Bit definition for FLASH_KEYR register  ******************/
#define  FLASH_KEYR_FKEYR                    ((uint32_t)0xFFFFFFFF)        /* FPEC Key */

/*****************  Bit definition for FLASH_OPTKEYR register  ****************/
#define  FLASH_OPTKEYR_OPTKEYR               ((uint32_t)0xFFFFFFFF)        /* Option Byte Key */

/******************  FLASH Keys  **********************************************/
#define FLASH_KEY1                           ((uint32_t)0x45670123)        /* unlock key1 */
#define FLASH_KEY2                           ((uint32_t)0xCDEF89AB)        /* unlock key2 */
#define FLASH_RDPRT_KEY                      0x00A5                        /* read option unlock key */
                                                               
#define FLASH_OPTKEY1                        ((uint32_t)0x45670123)        /* Flash option key1 */
#define FLASH_OPTKEY2                        ((uint32_t)0xCDEF89AB)        /* Flash option key2: used with FLASH_OPTKEY1 to
                                                                                unlock the write access to the option byte block */

/******************  Bit definition for FLASH_SR register  *******************/
#define  FLASH_SR_CFGBSY                     ((uint32_t)0x00040000)        /* Programming or erase configuration busy. */
#define  FLASH_SR_BSY                        ((uint32_t)0x00010000)        /* Busy                             */
#define  FLASH_SR_OPTVERR                    ((uint32_t)0x00008000)        /* Option and Engineering bits loading validity error */
#define  FLASH_SR_FASTERR                    ((uint32_t)0x00000200)        /* Fast programming error           */
#define  FLASH_SR_MISSERR                    ((uint32_t)0x00000100)        /* Fast programming data miss Error */
#define  FLASH_SR_PGSERR                     ((uint32_t)0x00000080)        /* programming sequence Error       */
#define  FLASH_SR_SIZEERR                    ((uint32_t)0x00000040)        /* size Error                       */
#define  FLASH_SR_PAGERR                     ((uint32_t)0x00000020)        /* programming alignment Error      */
#define  FLASH_SR_WRPRTERR                   ((uint32_t)0x00000010)        /* Write Protection Error           */
#define  FLASH_SR_PGERR                      ((uint32_t)0x00000008)        /* Programming Error                */
#define  FLASH_SR_OPERR                      ((uint32_t)0x00000002)        /* operation error                  */
#define  FLASH_SR_EOP                        ((uint32_t)0x00000001)        /* End of operation                 */
#define  FLASH_SR_WRPERR                     FLASH_SR_WRPRTERR             /* Legacy of Write Protection Error */

#define  FLASH_SR_ERR_MASK                   ((uint32_t)0x000083fa)

/*******************  Bit definition for FLASH_CR register  *******************/
#define  FLASH_CR_PG                         ((uint32_t)0x00000001)        /* Programming */
#define  FLASH_CR_PER                        ((uint32_t)0x00000002)        /* Page Erase  */
#define  FLASH_CR_MER                        ((uint32_t)0x00000004)        /* Mass Erase  */
#define  FLASH_CR_PAGE_NUM                   ((uint32_t)0x000001f8)        /* Page number */
#define  FLASH_CR_STRT                       ((uint32_t)0x00010000)        /* Start */
#define  FLASH_CR_OPTPG                      ((uint32_t)0x00020000)        /* Option Byte Programming */
#define  FLASH_CR_FAST_PRG                   ((uint32_t)0x00040000)        /* Fast programming.       */
#define  FLASH_CR_EOPIE                      ((uint32_t)0x01000000)        /* End of operation interrupt enable */
#define  FLASH_CR_ERRIE                      ((uint32_t)0x02000000)        /* Error interrupt enable            */
#define  FLASH_CR_OBL_LAUNCH                 ((uint32_t)0x08000000)        /* Forces the option byte loading    */
#define  FLASH_CR_OPT_LOCK                   ((uint32_t)0x40000000)        /* Options lock                      */
#define  FLASH_CR_LOCK                       ((uint32_t)0x80000000)        /* Lock                              */

/******************************* Flash ECCR Register ***************************/
#define  FLASH_ECCR_ADDR_MASK                ((uint32_t)0x00003fff)        /* address offset. */
#define  FLASH_ECCR_SYSF_ECC                 ((uint32_t)0x00100000)        /* System Flash memory ECC fail.    */
#define  FLASH_ECCR_ECCCIE                   ((uint32_t)0x01000000)        /* ECC correction interrupt enable. */
#define  FLASH_ECCR_ECCC                     ((uint32_t)0x40000000)        /* ECC correction.                  */
#define  FLASH_ECCR_ECCD                     ((uint32_t)0x80000000)        /* ECC detection.                   */

#define  FLASH_ECCR_ERR_MASK                 ((uint32_t)0xc0000000)
/*******************  Bit definition for FLASH_AR register  *******************/
#define  FLASH_AR_FAR                        ((uint32_t)0xFFFFFFFF)        /* Flash Address */


/******************************************************************************/
/*                                                                            */
/*                                    FLASH                                   */
/*                                                                            */
/******************************************************************************/
#define GPIO_NRST_CONFIG_SUPPORT         /*!< GPIO feature available only on specific devices: Configure NRST pin */
#define FLASH_SECURABLE_MEMORY_SUPPORT   /*!< Flash feature available only on specific devices: allow to secure memory */
#define FLASH_PCROP_SUPPORT              /*!< Flash feature available only on specific devices: proprietary code read protection areas selected by option */



/*******************  Bits definition for FLASH_SR register  ******************/
#define FLASH_SR_EOP_Pos                       (0U)
#define FLASH_SR_EOP_Msk                       (0x1UL << FLASH_SR_EOP_Pos)      /*!< 0x00000001 */
#define FLASH_SR_OPERR_Pos                     (1U)
#define FLASH_SR_OPERR_Msk                     (0x1UL << FLASH_SR_OPERR_Pos)    /*!< 0x00000002 */
#define FLASH_SR_PROGERR_Pos                   (3U)
#define FLASH_SR_PROGERR_Msk                   (0x1UL << FLASH_SR_PROGERR_Pos)  /*!< 0x00000008 */
#define FLASH_SR_PROGERR                       FLASH_SR_PROGERR_Msk
#define FLASH_SR_WRPERR_Pos                    (4U)
#define FLASH_SR_WRPERR_Msk                    (0x1UL << FLASH_SR_WRPERR_Pos)   /*!< 0x00000010 */
#define FLASH_SR_PGAERR_Pos                    (5U)
#define FLASH_SR_PGAERR_Msk                    (0x1UL << FLASH_SR_PGAERR_Pos)   /*!< 0x00000020 */
#define FLASH_SR_PGAERR                        FLASH_SR_PGAERR_Msk
#define FLASH_SR_SIZERR_Pos                    (6U)
#define FLASH_SR_SIZERR_Msk                    (0x1UL << FLASH_SR_SIZERR_Pos)   /*!< 0x00000040 */
#define FLASH_SR_SIZERR                        FLASH_SR_SIZERR_Msk
#define FLASH_SR_PGSERR_Pos                    (7U)
#define FLASH_SR_PGSERR_Msk                    (0x1UL << FLASH_SR_PGSERR_Pos)   /*!< 0x00000080 */
#define FLASH_SR_MISERR_Pos                    (8U)
#define FLASH_SR_MISERR_Msk                    (0x1UL << FLASH_SR_MISERR_Pos)   /*!< 0x00000100 */
#define FLASH_SR_MISERR                        FLASH_SR_MISERR_Msk
#define FLASH_SR_FASTERR_Pos                   (9U)
#define FLASH_SR_FASTERR_Msk                   (0x1UL << FLASH_SR_FASTERR_Pos)  /*!< 0x00000200 */
#define FLASH_SR_RDERR_Pos                     (14U)
#define FLASH_SR_RDERR_Msk                     (0x1UL << FLASH_SR_RDERR_Pos)    /*!< 0x00004000 */
#define FLASH_SR_RDERR                         FLASH_SR_RDERR_Msk
#define FLASH_SR_OPTVERR_Pos                   (15U)
#define FLASH_SR_OPTVERR_Msk                   (0x1UL << FLASH_SR_OPTVERR_Pos)  /*!< 0x00008000 */
#define FLASH_SR_BSY1_Pos                      (16U)
#define FLASH_SR_BSY1_Msk                      (0x1UL << FLASH_SR_BSY1_Pos)     /*!< 0x00010000 */
#define FLASH_SR_BSY1                          FLASH_SR_BSY1_Msk
#define FLASH_SR_CFGBSY_Pos                    (18U)
#define FLASH_SR_CFGBSY_Msk                    (0x1UL << FLASH_SR_CFGBSY_Pos)   /*!< 0x00040000 */

/*******************  Bits definition for FLASH_CR register  ******************/
#define FLASH_CR_PG_Pos                        (0U)
#define FLASH_CR_PG_Msk                        (0x1UL << FLASH_CR_PG_Pos)       /*!< 0x00000001 */
#define FLASH_CR_PER_Pos                       (1U)
#define FLASH_CR_PER_Msk                       (0x1UL << FLASH_CR_PER_Pos)      /*!< 0x00000002 */
#define FLASH_CR_MER1_Pos                      (2U)
#define FLASH_CR_MER1_Msk                      (0x1UL << FLASH_CR_MER1_Pos)     /*!< 0x00000004 */
#define FLASH_CR_MER1                          FLASH_CR_MER1_Msk
#define FLASH_CR_PNB_Pos                       (3U)
#define FLASH_CR_PNB_Msk                       (0x3FUL << FLASH_CR_PNB_Pos)     /*!< 0x000001F8 */
#define FLASH_CR_PNB                           FLASH_CR_PNB_Msk
#define FLASH_CR_STRT_Pos                      (16U)
#define FLASH_CR_STRT_Msk                      (0x1UL << FLASH_CR_STRT_Pos)     /*!< 0x00010000 */
#define FLASH_CR_OPTSTRT_Pos                   (17U)
#define FLASH_CR_OPTSTRT_Msk                   (0x1UL << FLASH_CR_OPTSTRT_Pos)  /*!< 0x00020000 */
#define FLASH_CR_OPTSTRT                       FLASH_CR_OPTSTRT_Msk
#define FLASH_CR_FSTPG_Pos                     (18U)
#define FLASH_CR_FSTPG_Msk                     (0x1UL << FLASH_CR_FSTPG_Pos)    /*!< 0x00040000 */
#define FLASH_CR_FSTPG                         FLASH_CR_FSTPG_Msk
#define FLASH_CR_EOPIE_Pos                     (24U)
#define FLASH_CR_EOPIE_Msk                     (0x1UL << FLASH_CR_EOPIE_Pos)    /*!< 0x01000000 */
#define FLASH_CR_ERRIE_Pos                     (25U)
#define FLASH_CR_ERRIE_Msk                     (0x1UL << FLASH_CR_ERRIE_Pos)    /*!< 0x02000000 */
#define FLASH_CR_RDERRIE_Pos                   (26U)
#define FLASH_CR_RDERRIE_Msk                   (0x1UL << FLASH_CR_RDERRIE_Pos)  /*!< 0x04000000 */
#define FLASH_CR_RDERRIE                       FLASH_CR_RDERRIE_Msk
#define FLASH_CR_OBL_LAUNCH_Pos                (27U)
#define FLASH_CR_OBL_LAUNCH_Msk                (0x1UL << FLASH_CR_OBL_LAUNCH_Pos) /*!< 0x08000000 */
#define FLASH_CR_SEC_PROT_Pos                  (28U)
#define FLASH_CR_SEC_PROT_Msk                  (0x1UL << FLASH_CR_SEC_PROT_Pos) /*!< 0x10000000 */
#define FLASH_CR_SEC_PROT                      FLASH_CR_SEC_PROT_Msk
#define FLASH_CR_OPTLOCK_Pos                   (30U)
#define FLASH_CR_OPTLOCK_Msk                   (0x1UL << FLASH_CR_OPTLOCK_Pos)  /*!< 0x40000000 */
#define FLASH_CR_OPTLOCK                       FLASH_CR_OPTLOCK_Msk
#define FLASH_CR_LOCK_Pos                      (31U)
#define FLASH_CR_LOCK_Msk                      (0x1UL << FLASH_CR_LOCK_Pos)     /*!< 0x80000000 */

/*******************  Bits definition for FLASH_ECCR register  ****************/
#define FLASH_ECCR_ADDR_ECC_Pos                (0U)
#define FLASH_ECCR_ADDR_ECC_Msk                (0x3FFFUL << FLASH_ECCR_ADDR_ECC_Pos) /*!< 0x00003FFF */
#define FLASH_ECCR_ADDR_ECC                    FLASH_ECCR_ADDR_ECC_Msk
#define FLASH_ECCR_SYSF_ECC_Pos                (20U)
#define FLASH_ECCR_SYSF_ECC_Msk                (0x1UL << FLASH_ECCR_SYSF_ECC_Pos) /*!< 0x00100000 */
#define FLASH_ECCR_ECCCIE_Pos                  (24U)
#define FLASH_ECCR_ECCCIE_Msk                  (0x1UL << FLASH_ECCR_ECCCIE_Pos) /*!< 0x01000000 */
#define FLASH_ECCR_ECCC_Pos                    (30U)
#define FLASH_ECCR_ECCC_Msk                    (0x1UL << FLASH_ECCR_ECCC_Pos)   /*!< 0x40000000 */
#define FLASH_ECCR_ECCD_Pos                    (31U)
#define FLASH_ECCR_ECCD_Msk                    (0x1UL << FLASH_ECCR_ECCD_Pos)   /*!< 0x80000000 */

/*******************  Bits definition for FLASH_OPTR register  ****************/
#define FLASH_OPTR_RDP_Pos                     (0U)
#define FLASH_OPTR_RDP_Msk                     (0xFFUL << FLASH_OPTR_RDP_Pos)   /*!< 0x000000FF */
#define FLASH_OPTR_RDP                         FLASH_OPTR_RDP_Msk
#define FLASH_OPTR_BOR_EN_Pos                  (8U)
#define FLASH_OPTR_BOR_EN_Msk                  (0x1UL << FLASH_OPTR_BOR_EN_Pos) /*!< 0x00000100 */
#define FLASH_OPTR_BOR_EN                      FLASH_OPTR_BOR_EN_Msk
#define FLASH_OPTR_BORF_LEV_Pos                (9U)
#define FLASH_OPTR_BORF_LEV_Msk                (0x3UL << FLASH_OPTR_BORF_LEV_Pos) /*!< 0x00000600 */
#define FLASH_OPTR_BORF_LEV                    FLASH_OPTR_BORF_LEV_Msk
#define FLASH_OPTR_BORF_LEV_0                  (0x1UL << FLASH_OPTR_BORF_LEV_Pos) /*!< 0x00000200 */
#define FLASH_OPTR_BORF_LEV_1                  (0x2UL << FLASH_OPTR_BORF_LEV_Pos) /*!< 0x00000400 */
#define FLASH_OPTR_BORR_LEV_Pos                (11U)
#define FLASH_OPTR_BORR_LEV_Msk                (0x3UL << FLASH_OPTR_BORR_LEV_Pos) /*!< 0x00001800 */
#define FLASH_OPTR_BORR_LEV                    FLASH_OPTR_BORR_LEV_Msk
#define FLASH_OPTR_BORR_LEV_0                  (0x1UL << FLASH_OPTR_BORR_LEV_Pos) /*!< 0x00000800 */
#define FLASH_OPTR_BORR_LEV_1                  (0x2UL << FLASH_OPTR_BORR_LEV_Pos) /*!< 0x00001000 */
#define FLASH_OPTR_nRST_STOP_Pos               (13U)
#define FLASH_OPTR_nRST_STOP_Msk               (0x1UL << FLASH_OPTR_nRST_STOP_Pos) /*!< 0x00002000 */
#define FLASH_OPTR_nRST_STOP                   FLASH_OPTR_nRST_STOP_Msk
#define FLASH_OPTR_nRST_STDBY_Pos              (14U)
#define FLASH_OPTR_nRST_STDBY_Msk              (0x1UL << FLASH_OPTR_nRST_STDBY_Pos) /*!< 0x00004000 */
#define FLASH_OPTR_nRST_STDBY                  FLASH_OPTR_nRST_STDBY_Msk
#define FLASH_OPTR_nRST_SHDW_Pos               (15U)
#define FLASH_OPTR_nRST_SHDW_Msk               (0x1UL << FLASH_OPTR_nRST_SHDW_Pos) /*!< 0x00008000 */
#define FLASH_OPTR_nRST_SHDW                   FLASH_OPTR_nRST_SHDW_Msk
#define FLASH_OPTR_IWDG_SW_Pos                 (16U)
#define FLASH_OPTR_IWDG_SW_Msk                 (0x1UL << FLASH_OPTR_IWDG_SW_Pos)   /*!< 0x00010000 */
#define FLASH_OPTR_IWDG_SW                     FLASH_OPTR_IWDG_SW_Msk
#define FLASH_OPTR_IWDG_STOP_Pos               (17U)
#define FLASH_OPTR_IWDG_STOP_Msk               (0x1UL << FLASH_OPTR_IWDG_STOP_Pos) /*!< 0x00020000 */
#define FLASH_OPTR_IWDG_STOP                   FLASH_OPTR_IWDG_STOP_Msk
#define FLASH_OPTR_IWDG_STDBY_Pos              (18U)
#define FLASH_OPTR_IWDG_STDBY_Msk              (0x1UL << FLASH_OPTR_IWDG_STDBY_Pos) /*!< 0x00040000 */
#define FLASH_OPTR_IWDG_STDBY                  FLASH_OPTR_IWDG_STDBY_Msk
#define FLASH_OPTR_WWDG_SW_Pos                 (19U)
#define FLASH_OPTR_WWDG_SW_Msk                 (0x1UL << FLASH_OPTR_WWDG_SW_Pos) /*!< 0x00080000 */
#define FLASH_OPTR_WWDG_SW                     FLASH_OPTR_WWDG_SW_Msk
#define FLASH_OPTR_RAM_PARITY_CHECK_Pos        (22U)
#define FLASH_OPTR_RAM_PARITY_CHECK_Msk        (0x1UL << FLASH_OPTR_RAM_PARITY_CHECK_Pos) /*!< 0x00400000 */
#define FLASH_OPTR_RAM_PARITY_CHECK            FLASH_OPTR_RAM_PARITY_CHECK_Msk
#define FLASH_OPTR_nBOOT_SEL_Pos               (24U)
#define FLASH_OPTR_nBOOT_SEL_Msk               (0x1UL << FLASH_OPTR_nBOOT_SEL_Pos) /*!< 0x01000000 */
#define FLASH_OPTR_nBOOT_SEL                   FLASH_OPTR_nBOOT_SEL_Msk
#define FLASH_OPTR_nBOOT1_Pos                  (25U)
#define FLASH_OPTR_nBOOT1_Msk                  (0x1UL << FLASH_OPTR_nBOOT1_Pos) /*!< 0x02000000 */
#define FLASH_OPTR_nBOOT1                      FLASH_OPTR_nBOOT1_Msk
#define FLASH_OPTR_nBOOT0_Pos                  (26U)
#define FLASH_OPTR_nBOOT0_Msk                  (0x1UL << FLASH_OPTR_nBOOT0_Pos) /*!< 0x04000000 */
#define FLASH_OPTR_nBOOT0                      FLASH_OPTR_nBOOT0_Msk
#define FLASH_OPTR_NRST_MODE_Pos               (27U)
#define FLASH_OPTR_NRST_MODE_Msk               (0x3UL << FLASH_OPTR_NRST_MODE_Pos) /*!< 0x18000000 */
#define FLASH_OPTR_NRST_MODE                   FLASH_OPTR_NRST_MODE_Msk
#define FLASH_OPTR_NRST_MODE_0                 (0x1UL << FLASH_OPTR_NRST_MODE_Pos) /*!< 0x08000000 */
#define FLASH_OPTR_NRST_MODE_1                 (0x2UL << FLASH_OPTR_NRST_MODE_Pos) /*!< 0x10000000 */
#define FLASH_OPTR_IRHEN_Pos                   (29U)
#define FLASH_OPTR_IRHEN_Msk                   (0x1UL << FLASH_OPTR_IRHEN_Pos) /*!< 0x20000000 */
#define FLASH_OPTR_IRHEN                       FLASH_OPTR_IRHEN_Msk

/******************  Bits definition for FLASH_PCROP1ASR register  ************/
#define FLASH_PCROP1ASR_PCROP1A_STRT_Pos       (0U)
#define FLASH_PCROP1ASR_PCROP1A_STRT_Msk       (0xFFUL << FLASH_PCROP1ASR_PCROP1A_STRT_Pos) /*!< 0x000000FF */
#define FLASH_PCROP1ASR_PCROP1A_STRT           FLASH_PCROP1ASR_PCROP1A_STRT_Msk

/******************  Bits definition for FLASH_PCROP1AER register  ************/
#define FLASH_PCROP1AER_PCROP1A_END_Pos        (0U)
#define FLASH_PCROP1AER_PCROP1A_END_Msk        (0xFFUL << FLASH_PCROP1AER_PCROP1A_END_Pos) /*!< 0x000000FF */
#define FLASH_PCROP1AER_PCROP1A_END            FLASH_PCROP1AER_PCROP1A_END_Msk
#define FLASH_PCROP1AER_PCROP_RDP_Pos          (31U)
#define FLASH_PCROP1AER_PCROP_RDP_Msk          (0x1UL << FLASH_PCROP1AER_PCROP_RDP_Pos) /*!< 0x80000000 */
#define FLASH_PCROP1AER_PCROP_RDP              FLASH_PCROP1AER_PCROP_RDP_Msk

/******************  Bits definition for FLASH_WRP1AR register  ***************/
#define FLASH_WRP1AR_WRP1A_STRT_Pos            (0U)
#define FLASH_WRP1AR_WRP1A_STRT_Msk            (0x3FUL << FLASH_WRP1AR_WRP1A_STRT_Pos) /*!< 0x0000003F */
#define FLASH_WRP1AR_WRP1A_STRT                FLASH_WRP1AR_WRP1A_STRT_Msk
#define FLASH_WRP1AR_WRP1A_END_Pos             (16U)
#define FLASH_WRP1AR_WRP1A_END_Msk             (0x3FUL << FLASH_WRP1AR_WRP1A_END_Pos) /*!< 0x003F0000 */
#define FLASH_WRP1AR_WRP1A_END                 FLASH_WRP1AR_WRP1A_END_Msk

/******************  Bits definition for FLASH_WRP1BR register  ***************/
#define FLASH_WRP1BR_WRP1B_STRT_Pos            (0U)
#define FLASH_WRP1BR_WRP1B_STRT_Msk            (0x3FUL << FLASH_WRP1BR_WRP1B_STRT_Pos) /*!< 0x0000003F */
#define FLASH_WRP1BR_WRP1B_STRT                FLASH_WRP1BR_WRP1B_STRT_Msk
#define FLASH_WRP1BR_WRP1B_END_Pos             (16U)
#define FLASH_WRP1BR_WRP1B_END_Msk             (0x3FUL << FLASH_WRP1BR_WRP1B_END_Pos) /*!< 0x003F0000 */
#define FLASH_WRP1BR_WRP1B_END                 FLASH_WRP1BR_WRP1B_END_Msk

/******************  Bits definition for FLASH_PCROP1BSR register  ************/
#define FLASH_PCROP1BSR_PCROP1B_STRT_Pos       (0U)
#define FLASH_PCROP1BSR_PCROP1B_STRT_Msk       (0xFFUL << FLASH_PCROP1BSR_PCROP1B_STRT_Pos) /*!< 0x000000FF */
#define FLASH_PCROP1BSR_PCROP1B_STRT           FLASH_PCROP1BSR_PCROP1B_STRT_Msk

/******************  Bits definition for FLASH_PCROP1BER register  ************/
#define FLASH_PCROP1BER_PCROP1B_END_Pos        (0U)
#define FLASH_PCROP1BER_PCROP1B_END_Msk        (0xFFUL << FLASH_PCROP1BER_PCROP1B_END_Pos)  /*!< 0x000000FF */
#define FLASH_PCROP1BER_PCROP1B_END            FLASH_PCROP1BER_PCROP1B_END_Msk

/******************  Bits definition for FLASH_SECR register  *****************/
#define FLASH_SECR_SEC_SIZE_Pos                (0U)
#define FLASH_SECR_SEC_SIZE_Msk                (0x7FUL << FLASH_SECR_SEC_SIZE_Pos) /*!< 0x0000007F */
#define FLASH_SECR_SEC_SIZE                    FLASH_SECR_SEC_SIZE_Msk
#define FLASH_SECR_BOOT_LOCK_Pos               (16U)
#define FLASH_SECR_BOOT_LOCK_Msk               (0x1UL << FLASH_SECR_BOOT_LOCK_Pos) /*!< 0x00010000 */
#define FLASH_SECR_BOOT_LOCK                   FLASH_SECR_BOOT_LOCK_Msk



/******************  Bit definition for FLASH_WRPR register  ******************/
#define  FLASH_WRPR_WRP                      ((uint32_t)0xFFFFFFFF)        /* Write Protect */

/* timer handler for flash operation. */
typedef struct
{
    BOOL   (*pfAppCheck)(VOID);         /* application needs to be checked for true before erasing or programing. TRUE means waiting. */
    WORD32 (*pfGetMs)(VOID);            /* the handler for getting ms-time. */
    WORD32 (*pfGetDlyMs)(WORD32);       /* the handler for getting ms-delay base an old ms-time. */
}T_FLASH_TMOPER;




/*************************************************************************************
* function name   : VOID Stm32G0xxx_Flash_Reg(BYTE ucLogNo,BYTE ucDevNo,VOID *ptPara)
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
VOID Stm32G0xxx_Flash_Reg(BYTE ucLogNo,BYTE ucDevNo,VOID *ptPara);


#ifdef __cplusplus
}
#endif

#endif // _STM32G0XX_FLASH_H_

// End of Flash.h

