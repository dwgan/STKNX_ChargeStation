/********************************************************************
* Right reserved (C 2016) for *********** company.
*
* File Name        : Stm32G0xxx_adc.h
*
* File Description : Header file for stm32f10xx adc definition.
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


#ifndef _STM32G0XXX_ADC_H_
#define _STM32G0XXX_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ADC parameter data field position definition   */
#define ADC_PARA_DEVTYPE_INDEX         0
#define ADC_PARA_DEV_NO_INDEX          1
#define ADC_PARA_CHNL_NO_INDEX         2
#define ADC_PARA_CMD_INDEX             3
#define ADC_PARA_CMD_PARA_INDEX        4
#define ADC_PARA_TRIGGER_INDEX         5
#define ADC_PARA_SAMPLE_CNT_INDEX      6

#define SYSCLK_FREQ_24M                24000000
#define SYSCLK_FREQ_32M                32000000
#define SYSCLK_FREQ_36M                36000000
#define SYSCLK_FREQ_48M                48000000
#define SYSCLK_FREQ_56M                56000000
#define SYSCLK_FREQ_72M                72000000

#define ADC_REGULAOR_TIME              21                                        /* 20us */
#define ADC_MAX_CHL_NUM                19                                        /* we define the total channel number of the ADC. */

#define ADC_TRG_POL_H                  1                                         /* positive edge for triggering. */
#define ADC_TRG_POL_L                  2                                         /* negtive edge for triggering.  */
#define ADC_TRG_POL_HL                 3                                         /* both triggering.              */

#define ADC_TIM1_TRGO2                 0                                         /* Hardware triger source 0      */
#define ADC_TIM1_CC4                   1                                         /* Hardware triger source 1      */
#define ADC_RESERVE1                   2                                         /* Hardware triger source 2      */
#define ADC_TIM3_TRGO                  3                                         /* Hardware triger source 3      */
#define ADC_TIM15_TRGO                 4                                         /* Hardware triger source 4      */
#define ADC_TIM6_TRGO                  5                                         /* Hardware triger source 5      */
#define ADC_RESERVE2                   6                                         /* Hardware triger source 6      */
#define ADC_EXTI_LINE                  7                                         /* Hardware triger source 7      */

#define ADC_OVERSMPLE_0                0                                         /* no oversample.   */
#define ADC_OVERSMPLE_2                1                                         /* 000: 2x   */
#define ADC_OVERSMPLE_4                2                                         /* 001: 4x   */
#define ADC_OVERSMPLE_8                3                                         /* 010: 8x   */
#define ADC_OVERSMPLE_16               4                                         /* 011: 16x  */
#define ADC_OVERSMPLE_32               5                                         /* 100: 32x  */
#define ADC_OVERSMPLE_64               6                                         /* 101: 64x  */
#define ADC_OVERSMPLE_128              7                                         /* 110: 128x */
#define ADC_OVERSMPLE_256              8                                         /* 111: 256x */

/******************************************************************************/
/*                                                                            */
/*                      Analog to Digital Converter (ADC)                     */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for ADC_ISR register  *******************/
#define ADC_ISR_ADRDY_MSK              (0x00000001UL)                            /* ADC ready flag */
#define ADC_ISR_EOSMP_MSK              (0x00000002UL)                            /* ADC group regular end of sampling flag */
#define ADC_ISR_EOC_MSK                (0x00000004UL)                            /* ADC group regular end of unitary conversion flag */
#define ADC_ISR_EOS_MSK                (0x00000008UL)                            /* ADC group regular end of sequence conversions flag */
#define ADC_ISR_OVR_MSK                (0x00000010UL)                            /* ADC group regular overrun flag */
#define ADC_ISR_AWD1_MSK               (0x00000080UL)                            /* ADC analog watchdog 1 flag */
#define ADC_ISR_AWD2_MSK               (0x00000100UL)                            /* ADC analog watchdog 2 flag */
#define ADC_ISR_AWD3_MSK               (0x00000200UL)                            /* ADC analog watchdog 3 flag */
#define ADC_ISR_EOCAL_MSK              (0x00000800UL)                            /* ADC end of calibration flag */
#define ADC_ISR_CCRDY_MSK              (0x00002000UL)                            /* ADC channel configuration ready flag */

/* Legacy defines */
#define ADC_ISR_EOSEQ           (ADC_ISR_EOS)

/********************  Bit definition for ADC_IER register  *******************/
#define ADC_IER_ADRDYIE_MSK            (0x00000001UL)                            /* ADC ready interrupt */
#define ADC_IER_EOSMPIE_MSK            (0x00000002UL)                            /* ADC group regular end of sampling interrupt */
#define ADC_IER_EOCIE_MSK              (0x00000004UL)                            /* ADC group regular end of unitary conversion interrupt */
#define ADC_IER_EOSIE_MSK              (0x00000008UL)                            /* ADC group regular end of sequence conversions interrupt */
#define ADC_IER_OVRIE_MSK              (0x00000010UL)                            /* ADC group regular overrun interrupt */
#define ADC_IER_AWD1IE_MSK             (0x00000080UL)                            /* ADC analog watchdog 1 interrupt */
#define ADC_IER_AWD2IE_MSK             (0x00000100UL)                            /* ADC analog watchdog 2 interrupt */
#define ADC_IER_AWD3IE_MSK             (0x00000200UL)                            /* ADC analog watchdog 3 interrupt */
#define ADC_IER_EOCALIE_MSK            (0x00000800UL)                            /* ADC end of calibration interrupt */
#define ADC_IER_CCRDYIE_MSK            (0x00002000UL)                            /* ADC channel configuration ready interrupt */

/* Legacy defines */
#define ADC_IER_EOSEQIE           (ADC_IER_EOSIE)

/********************  Bit definition for ADC_CR register  ********************/
#define ADC_CR_ADEN_MSK                (0x00000001UL)                            /* ADC enable  */
#define ADC_CR_ADDIS_MSK               (0x00000002UL)                            /* ADC disable */
#define ADC_CR_ADSTART_MSK             (0x00000004UL)                            /* ADC start   */
#define ADC_CR_ADSTP_MSK               (0x00000010UL)                            /* ADC stop    */
#define ADC_CR_ADVREGEN_MSK            (0x10000000UL)                            /* ADC voltage regulator enable */
#define ADC_CR_ADCAL_MSK               (0x80000000UL)                            /* ADC calibration              */

/********************  Bit definition for ADC_CFGR1 register  *****************/
#define ADC_CFGR1_DMAEN_MSK            (0x00000001UL)                            /* ADC DMA transfer enable */
#define ADC_CFGR1_DMACFG_MSK           (0x00000002UL)                            /* ADC DMA transfer configuration */
#define ADC_CFGR1_SCANDIR_MSK          (0x00000004UL)                            /* ADC group regular sequencer scan direction */
#define ADC_CFGR1_RES_MSK              (0x00000018UL)                            /* ADC data resolution */
#define ADC_CFGR1_RES_0                (0x00000008UL)
#define ADC_CFGR1_RES_1                (0x00000010UL)
#define ADC_CFGR1_ALIGN_MSK            (0x00000020UL)                            /* ADC data alignement */

#define ADC_CFGR1_EXTSEL_SHIFT         6
#define ADC_CFGR1_EXTSEL_MSK           (0x000001C0UL)                            /* ADC group regular external trigger source */
#define ADC_CFGR1_EXTSEL_0             (0x00000040UL)
#define ADC_CFGR1_EXTSEL_1             (0x00000080UL)
#define ADC_CFGR1_EXTSEL_2             (0x00000100UL)

#define ADC_CFGR1_EXTEN_SHIFT          10
#define ADC_CFGR1_EXTEN_MSK            (0x00000C00UL)                            /* ADC group regular external trigger polarity */
#define ADC_CFGR1_EXTEN_0              (0x00000400UL)
#define ADC_CFGR1_EXTEN_1              (0x00000800UL)

#define ADC_CFGR1_OVRMOD_MSK           (0x00001000UL)                            /* ADC group regular overrun configuration */
#define ADC_CFGR1_CONT_MSK             (0x00002000UL)                            /* ADC group regular continuous conversion mode */
#define ADC_CFGR1_WAIT_MSK             (0x00004000UL)                            /* ADC low power auto wait */
#define ADC_CFGR1_AUTOFF_MSK           (0x00008000UL)                            /* ADC low power auto power off */
#define ADC_CFGR1_DISCEN_MSK           (0x00010000UL)                            /* ADC group regular sequencer discontinuous mode */
#define ADC_CFGR1_CHSELRMOD_MSK        (0x00200000UL)                            /* ADC group regular sequencer mode */
#define ADC_CFGR1_AWD1SGL_MSK          (0x00400000UL)                            /* ADC analog watchdog 1 monitoring a single channel or all channels */
#define ADC_CFGR1_AWD1EN_MSK           (0x00800000UL)                            /* ADC analog watchdog 1 enable on scope ADC group regular */

#define ADC_CFGR1_AWD1CH_MSK           (0x7C000000UL)                            /* ADC analog watchdog 1 monitored channel selection */
#define ADC_CFGR1_AWD1CH_0             (0x04000000UL)
#define ADC_CFGR1_AWD1CH_1             (0x08000000UL)
#define ADC_CFGR1_AWD1CH_2             (0x10000000UL)
#define ADC_CFGR1_AWD1CH_3             (0x20000000UL)
#define ADC_CFGR1_AWD1CH_4             (0x40000000UL)

/* Legacy defines */
#define ADC_CFGR1_AUTDLY          (ADC_CFGR1_WAIT)

/********************  Bit definition for ADC_CFGR2 register  *****************/
#define ADC_CFGR2_OVSR_SHIFT           2
#define ADC_CFGR2_OVSS_SHIFT           5
#define ADC_CFGR2_OVSE_MSK             (0x00000001UL)                            /* ADC oversampler enable on scope ADC group regular */
#define ADC_CFGR2_OVSR_MSK             (0x0000001CUL)                            /* ADC oversampling ratio */
#define ADC_CFGR2_OVSR_0               (0x00000004UL)
#define ADC_CFGR2_OVSR_1               (0x00000008UL)
#define ADC_CFGR2_OVSR_2               (0x00000010UL)
#define ADC_CFGR2_OVSS_MSK             (0x000001E0UL)                            /* ADC oversampling shift */
#define ADC_CFGR2_OVSS_0               (0x00000020UL)
#define ADC_CFGR2_OVSS_1               (0x00000040UL)
#define ADC_CFGR2_OVSS_2               (0x00000080UL)
#define ADC_CFGR2_OVSS_3               (0x00000100UL)
#define ADC_CFGR2_TOVS_MSK             (0x00000200UL)                            /* ADC oversampling discontinuous mode (triggered mode) for ADC group regular */
#define ADC_CFGR2_LFTRIG_MSK           (0x20000000UL)                            /* ADC low frequency trigger mode */
#define ADC_CFGR2_CKMODE_MSK           (0xC0000000UL)                            /* ADC clock source and prescaler (prescaler only for clock source synchronous) */
#define ADC_CFGR2_CKMODE_1             (0x80000000UL)
#define ADC_CFGR2_CKMODE_0             (0x40000000UL)

/********************  Bit definition for ADC_SMPR register  ******************/
#define ADC_SMPR_SMP1_MSK              (0x00000007UL)                            /* ADC group of channels sampling time 1 */
#define ADC_SMPR_SMP1_0                (0x00000001UL)
#define ADC_SMPR_SMP1_1                (0x00000002UL)
#define ADC_SMPR_SMP1_2                (0x00000004UL)

#define ADC_SMPR_SMP2_MSK              (0x00000070UL)                            /* ADC group of channels sampling time 2 */
#define ADC_SMPR_SMP2_0                (0x00000010UL)
#define ADC_SMPR_SMP2_1                (0x00000020UL)
#define ADC_SMPR_SMP2_2                (0x00000040UL)

#define ADC_SMPR_SMPSEL_MSK            (0x07FFFF00UL)                            /* ADC all channels sampling time selection */
#define ADC_SMPR_SMPSEL0_MSK           (0x00000100UL)                            /* ADC channel 0 sampling time selection */
#define ADC_SMPR_SMPSEL1_MSK           (0x00000200UL)                            /* ADC channel 1 sampling time selection */
#define ADC_SMPR_SMPSEL2_MSK           (0x00000400UL)                            /* ADC channel 2 sampling time selection */
#define ADC_SMPR_SMPSEL3_MSK           (0x00000800UL)                            /* ADC channel 3 sampling time selection */
#define ADC_SMPR_SMPSEL4_MSK           (0x00001000UL)                            /* ADC channel 4 sampling time selection */
#define ADC_SMPR_SMPSEL5_MSK           (0x00002000UL)                            /* ADC channel 5 sampling time selection */
#define ADC_SMPR_SMPSEL6_MSK           (0x00004000UL)                            /* ADC channel 6 sampling time selection */
#define ADC_SMPR_SMPSEL7_MSK           (0x00008000UL)                            /* ADC channel 7 sampling time selection */
#define ADC_SMPR_SMPSEL8_MSK           (0x00010000UL)                            /* ADC channel 8 sampling time selection */
#define ADC_SMPR_SMPSEL9_MSK           (0x00020000UL)                            /* ADC channel 9 sampling time selection */
#define ADC_SMPR_SMPSEL10_MSK          (0x00040000UL)                            /* ADC channel 10 sampling time selection */
#define ADC_SMPR_SMPSEL11_MSK          (0x00080000UL)                            /* ADC channel 11 sampling time selection */
#define ADC_SMPR_SMPSEL12_MSK          (0x00100000UL)                            /* ADC channel 12 sampling time selection */
#define ADC_SMPR_SMPSEL13_MSK          (0x00200000UL)                            /* ADC channel 13 sampling time selection */
#define ADC_SMPR_SMPSEL14_MSK          (0x00400000UL)                            /* ADC channel 14 sampling time selection */
#define ADC_SMPR_SMPSEL15_MSK          (0x00800000UL)                            /* ADC channel 15 sampling time selection */
#define ADC_SMPR_SMPSEL16_MSK          (0x01000000UL)                            /* ADC channel 16 sampling time selection */
#define ADC_SMPR_SMPSEL17_MSK          (0x02000000UL)                            /* ADC channel 17 sampling time selection */
#define ADC_SMPR_SMPSEL18_MSK          (0x04000000UL)                            /* ADC channel 18 sampling time selection */

/********************  Bit definition for ADC_TR1 register  *******************/
#define ADC_TR1_LT1_Pos                (0U)
#define ADC_TR1_LT1_MSK                (0xFFFUL << ADC_TR1_LT1_Pos)              /* 0x00000FFF */
#define ADC_TR1_LT1                    ADC_TR1_LT1_MSK                           /* ADC analog watchdog 1 threshold low */
#define ADC_TR1_LT1_0                  (0x001UL << ADC_TR1_LT1_Pos)              /* 0x00000001 */
#define ADC_TR1_LT1_1                  (0x002UL << ADC_TR1_LT1_Pos)              /* 0x00000002 */
#define ADC_TR1_LT1_2                  (0x004UL << ADC_TR1_LT1_Pos)              /* 0x00000004 */
#define ADC_TR1_LT1_3                  (0x008UL << ADC_TR1_LT1_Pos)              /* 0x00000008 */
#define ADC_TR1_LT1_4                  (0x010UL << ADC_TR1_LT1_Pos)              /* 0x00000010 */
#define ADC_TR1_LT1_5                  (0x020UL << ADC_TR1_LT1_Pos)              /* 0x00000020 */
#define ADC_TR1_LT1_6                  (0x040UL << ADC_TR1_LT1_Pos)              /* 0x00000040 */
#define ADC_TR1_LT1_7                  (0x080UL << ADC_TR1_LT1_Pos)              /* 0x00000080 */
#define ADC_TR1_LT1_8                  (0x100UL << ADC_TR1_LT1_Pos)              /* 0x00000100 */
#define ADC_TR1_LT1_9                  (0x200UL << ADC_TR1_LT1_Pos)              /* 0x00000200 */
#define ADC_TR1_LT1_10                 (0x400UL << ADC_TR1_LT1_Pos)              /* 0x00000400 */
#define ADC_TR1_LT1_11                 (0x800UL << ADC_TR1_LT1_Pos)              /* 0x00000800 */

#define ADC_TR1_HT1_Pos                (16U)
#define ADC_TR1_HT1_MSK                (0xFFFUL << ADC_TR1_HT1_Pos)              /* 0x0FFF0000 */
#define ADC_TR1_HT1                    ADC_TR1_HT1_MSK                           /* ADC Analog watchdog 1 threshold high */
#define ADC_TR1_HT1_0                  (0x001UL << ADC_TR1_HT1_Pos)              /* 0x00010000 */
#define ADC_TR1_HT1_1                  (0x002UL << ADC_TR1_HT1_Pos)              /* 0x00020000 */
#define ADC_TR1_HT1_2                  (0x004UL << ADC_TR1_HT1_Pos)              /* 0x00040000 */
#define ADC_TR1_HT1_3                  (0x008UL << ADC_TR1_HT1_Pos)              /* 0x00080000 */
#define ADC_TR1_HT1_4                  (0x010UL << ADC_TR1_HT1_Pos)              /* 0x00100000 */
#define ADC_TR1_HT1_5                  (0x020UL << ADC_TR1_HT1_Pos)              /* 0x00200000 */
#define ADC_TR1_HT1_6                  (0x040UL << ADC_TR1_HT1_Pos)              /* 0x00400000 */
#define ADC_TR1_HT1_7                  (0x080UL << ADC_TR1_HT1_Pos)              /* 0x00800000 */
#define ADC_TR1_HT1_8                  (0x100UL << ADC_TR1_HT1_Pos)              /* 0x01000000 */
#define ADC_TR1_HT1_9                  (0x200UL << ADC_TR1_HT1_Pos)              /* 0x02000000 */
#define ADC_TR1_HT1_10                 (0x400UL << ADC_TR1_HT1_Pos)              /* 0x04000000 */
#define ADC_TR1_HT1_11                 (0x800UL << ADC_TR1_HT1_Pos)              /* 0x08000000 */

/********************  Bit definition for ADC_TR2 register  *******************/
#define ADC_TR2_LT2_Pos                (0U)
#define ADC_TR2_LT2_MSK                (0xFFFUL << ADC_TR2_LT2_Pos)              /* 0x00000FFF */
#define ADC_TR2_LT2                    ADC_TR2_LT2_MSK                           /* ADC analog watchdog 2 threshold low */
#define ADC_TR2_LT2_0                  (0x001UL << ADC_TR2_LT2_Pos)              /* 0x00000001 */
#define ADC_TR2_LT2_1                  (0x002UL << ADC_TR2_LT2_Pos)              /* 0x00000002 */
#define ADC_TR2_LT2_2                  (0x004UL << ADC_TR2_LT2_Pos)              /* 0x00000004 */
#define ADC_TR2_LT2_3                  (0x008UL << ADC_TR2_LT2_Pos)              /* 0x00000008 */
#define ADC_TR2_LT2_4                  (0x010UL << ADC_TR2_LT2_Pos)              /* 0x00000010 */
#define ADC_TR2_LT2_5                  (0x020UL << ADC_TR2_LT2_Pos)              /* 0x00000020 */
#define ADC_TR2_LT2_6                  (0x040UL << ADC_TR2_LT2_Pos)              /* 0x00000040 */
#define ADC_TR2_LT2_7                  (0x080UL << ADC_TR2_LT2_Pos)              /* 0x00000080 */
#define ADC_TR2_LT2_8                  (0x100UL << ADC_TR2_LT2_Pos)              /* 0x00000100 */
#define ADC_TR2_LT2_9                  (0x200UL << ADC_TR2_LT2_Pos)              /* 0x00000200 */
#define ADC_TR2_LT2_10                 (0x400UL << ADC_TR2_LT2_Pos)              /* 0x00000400 */
#define ADC_TR2_LT2_11                 (0x800UL << ADC_TR2_LT2_Pos)              /* 0x00000800 */

#define ADC_TR2_HT2_Pos                (16U)
#define ADC_TR2_HT2_MSK                (0xFFFUL << ADC_TR2_HT2_Pos)              /* 0x0FFF0000 */
#define ADC_TR2_HT2                    ADC_TR2_HT2_MSK                           /* ADC analog watchdog 2 threshold high */
#define ADC_TR2_HT2_0                  (0x001UL << ADC_TR2_HT2_Pos)              /* 0x00010000 */
#define ADC_TR2_HT2_1                  (0x002UL << ADC_TR2_HT2_Pos)              /* 0x00020000 */
#define ADC_TR2_HT2_2                  (0x004UL << ADC_TR2_HT2_Pos)              /* 0x00040000 */
#define ADC_TR2_HT2_3                  (0x008UL << ADC_TR2_HT2_Pos)              /* 0x00080000 */
#define ADC_TR2_HT2_4                  (0x010UL << ADC_TR2_HT2_Pos)              /* 0x00100000 */
#define ADC_TR2_HT2_5                  (0x020UL << ADC_TR2_HT2_Pos)              /* 0x00200000 */
#define ADC_TR2_HT2_6                  (0x040UL << ADC_TR2_HT2_Pos)              /* 0x00400000 */
#define ADC_TR2_HT2_7                  (0x080UL << ADC_TR2_HT2_Pos)              /* 0x00800000 */
#define ADC_TR2_HT2_8                  (0x100UL << ADC_TR2_HT2_Pos)              /* 0x01000000 */
#define ADC_TR2_HT2_9                  (0x200UL << ADC_TR2_HT2_Pos)              /* 0x02000000 */
#define ADC_TR2_HT2_10                 (0x400UL << ADC_TR2_HT2_Pos)              /* 0x04000000 */
#define ADC_TR2_HT2_11                 (0x800UL << ADC_TR2_HT2_Pos)              /* 0x08000000 */

/********************  Bit definition for ADC_CHSELR register  ****************/
#define ADC_CHSELR_CHSEL_MSK           (0x0007FFFFUL)                            /* ADC group regular sequencer channels, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL18_MSK         (0x00040000UL)                            /* ADC group regular sequencer channel 18, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL17_MSK         (0x00020000UL)                            /* ADC group regular sequencer channel 17, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL16_MSK         (0x00010000UL)                            /* ADC group regular sequencer channel 16, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL15_MSK         (0x00008000UL)                            /* ADC group regular sequencer channel 15, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL14_MSK         (0x00004000UL)                            /* ADC group regular sequencer channel 14, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL13_MSK         (0x00002000UL)                            /* ADC group regular sequencer channel 13, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL12_MSK         (0x00001000UL)                            /* ADC group regular sequencer channel 12, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL11_MSK         (0x00000800UL)                            /* ADC group regular sequencer channel 11, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL10_MSK         (0x00000400UL)                            /* ADC group regular sequencer channel 10, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL9_MSK          (0x00000200UL)                            /* ADC group regular sequencer channel 9, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL8_MSK          (0x00000100UL)                            /* ADC group regular sequencer channel 8, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL7_MSK          (0x00000080UL)                            /* ADC group regular sequencer channel 7, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL6_MSK          (0x00000040UL)                            /* ADC group regular sequencer channel 6, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL5_MSK          (0x00000020UL)                            /* ADC group regular sequencer channel 5, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL4_MSK          (0x00000010UL)                            /* ADC group regular sequencer channel 4, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL3_MSK          (0x00000008UL)                            /* ADC group regular sequencer channel 3, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL2_MSK          (0x00000004UL)                            /* ADC group regular sequencer channel 2, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL1_MSK          (0x00000002UL)                            /* ADC group regular sequencer channel 1, available when ADC_CFGR1_CHSELRMOD is reset */
#define ADC_CHSELR_CHSEL0_MSK          (0x00000001UL)                            /* ADC group regular sequencer channel 0, available when ADC_CFGR1_CHSELRMOD is reset */

#define ADC_CHSELR_SQ_ALL_MSK          (0xFFFFFFFFUL)                            /* ADC group regular sequencer all ranks, available when ADC_CFGR1_CHSELRMOD is set */

#define ADC_CHSELR_SQ8_MSK             (0xF0000000UL)                            /* ADC group regular sequencer rank 8, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ8_0               (0x10000000UL)
#define ADC_CHSELR_SQ8_1               (0x20000000UL)
#define ADC_CHSELR_SQ8_2               (0x40000000UL)
#define ADC_CHSELR_SQ8_3               (0x80000000UL)

#define ADC_CHSELR_SQ7_MSK             (0x0F000000UL)                            /* ADC group regular sequencer rank 7, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ7_0               (0x01000000UL)
#define ADC_CHSELR_SQ7_1               (0x02000000UL)
#define ADC_CHSELR_SQ7_2               (0x04000000UL)
#define ADC_CHSELR_SQ7_3               (0x08000000UL)

#define ADC_CHSELR_SQ6_MSK             (0x00F00000UL)                            /* ADC group regular sequencer rank 6, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ6_0               (0x00100000UL)
#define ADC_CHSELR_SQ6_1               (0x00200000UL)
#define ADC_CHSELR_SQ6_2               (0x00400000UL)
#define ADC_CHSELR_SQ6_3               (0x00800000UL)

#define ADC_CHSELR_SQ5_MSK             (0x000F0000UL)                            /* ADC group regular sequencer rank 5, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ5_0               (0x00010000UL)
#define ADC_CHSELR_SQ5_1               (0x00020000UL)
#define ADC_CHSELR_SQ5_2               (0x00040000UL)
#define ADC_CHSELR_SQ5_3               (0x00080000UL)

#define ADC_CHSELR_SQ4_MSK             (0x0000F000UL)                            /* ADC group regular sequencer rank 4, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ4_0               (0x00001000UL)
#define ADC_CHSELR_SQ4_1               (0x00002000UL)
#define ADC_CHSELR_SQ4_2               (0x00004000UL)
#define ADC_CHSELR_SQ4_3               (0x00008000UL)

#define ADC_CHSELR_SQ3_MSK             (0x00000F00UL)                            /* ADC group regular sequencer rank 3, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ3_0               (0x00000100UL)
#define ADC_CHSELR_SQ3_1               (0x00000200UL)
#define ADC_CHSELR_SQ3_2               (0x00000400UL)
#define ADC_CHSELR_SQ3_3               (0x00000800UL)

#define ADC_CHSELR_SQ2_MSK             (0x000000F0UL)                            /* ADC group regular sequencer rank 2, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ2_0               (0x00000010UL)
#define ADC_CHSELR_SQ2_1               (0x00000020UL)
#define ADC_CHSELR_SQ2_2               (0x00000040UL)
#define ADC_CHSELR_SQ2_3               (0x00000080UL)

#define ADC_CHSELR_SQ1_MSK             (0x0000000FUL)                            /* ADC group regular sequencer rank 1, available when ADC_CFGR1_CHSELRMOD is set */
#define ADC_CHSELR_SQ1_0               (0x00000001UL)
#define ADC_CHSELR_SQ1_1               (0x00000002UL)
#define ADC_CHSELR_SQ1_2               (0x00000004UL)
#define ADC_CHSELR_SQ1_3               (0x00000008UL)

/********************  Bit definition for ADC_TR3 register  *******************/
#define ADC_TR3_LT3_Pos                (0U)
#define ADC_TR3_LT3_MSK                (0xFFFUL << ADC_TR3_LT3_Pos)            /* 0x00000FFF */
#define ADC_TR3_LT3                    ADC_TR3_LT3_MSK                         /* ADC analog watchdog 3 threshold low */
#define ADC_TR3_LT3_0                  (0x001UL << ADC_TR3_LT3_Pos)            /* 0x00000001 */
#define ADC_TR3_LT3_1                  (0x002UL << ADC_TR3_LT3_Pos)            /* 0x00000002 */
#define ADC_TR3_LT3_2                  (0x004UL << ADC_TR3_LT3_Pos)            /* 0x00000004 */
#define ADC_TR3_LT3_3                  (0x008UL << ADC_TR3_LT3_Pos)            /* 0x00000008 */
#define ADC_TR3_LT3_4                  (0x010UL << ADC_TR3_LT3_Pos)            /* 0x00000010 */
#define ADC_TR3_LT3_5                  (0x020UL << ADC_TR3_LT3_Pos)            /* 0x00000020 */
#define ADC_TR3_LT3_6                  (0x040UL << ADC_TR3_LT3_Pos)            /* 0x00000040 */
#define ADC_TR3_LT3_7                  (0x080UL << ADC_TR3_LT3_Pos)            /* 0x00000080 */
#define ADC_TR3_LT3_8                  (0x100UL << ADC_TR3_LT3_Pos)            /* 0x00000100 */
#define ADC_TR3_LT3_9                  (0x200UL << ADC_TR3_LT3_Pos)            /* 0x00000200 */
#define ADC_TR3_LT3_10                 (0x400UL << ADC_TR3_LT3_Pos)            /* 0x00000400 */
#define ADC_TR3_LT3_11                 (0x800UL << ADC_TR3_LT3_Pos)            /* 0x00000800 */

#define ADC_TR3_HT3_Pos                (16U)
#define ADC_TR3_HT3_MSK                (0xFFFUL << ADC_TR3_HT3_Pos)            /* 0x0FFF0000 */
#define ADC_TR3_HT3                    ADC_TR3_HT3_MSK                         /* ADC analog watchdog 3 threshold high */
#define ADC_TR3_HT3_0                  (0x001UL << ADC_TR3_HT3_Pos)            /* 0x00010000 */
#define ADC_TR3_HT3_1                  (0x002UL << ADC_TR3_HT3_Pos)            /* 0x00020000 */
#define ADC_TR3_HT3_2                  (0x004UL << ADC_TR3_HT3_Pos)            /* 0x00040000 */
#define ADC_TR3_HT3_3                  (0x008UL << ADC_TR3_HT3_Pos)            /* 0x00080000 */
#define ADC_TR3_HT3_4                  (0x010UL << ADC_TR3_HT3_Pos)            /* 0x00100000 */
#define ADC_TR3_HT3_5                  (0x020UL << ADC_TR3_HT3_Pos)            /* 0x00200000 */
#define ADC_TR3_HT3_6                  (0x040UL << ADC_TR3_HT3_Pos)            /* 0x00400000 */
#define ADC_TR3_HT3_7                  (0x080UL << ADC_TR3_HT3_Pos)            /* 0x00800000 */
#define ADC_TR3_HT3_8                  (0x100UL << ADC_TR3_HT3_Pos)            /* 0x01000000 */
#define ADC_TR3_HT3_9                  (0x200UL << ADC_TR3_HT3_Pos)            /* 0x02000000 */
#define ADC_TR3_HT3_10                 (0x400UL << ADC_TR3_HT3_Pos)            /* 0x04000000 */
#define ADC_TR3_HT3_11                 (0x800UL << ADC_TR3_HT3_Pos)            /* 0x08000000 */

/********************  Bit definition for ADC_DR register  ********************/
#define ADC_DR_DATA_MSK                (0x0000FFFFUL)                          /* ADC group regular conversion data */
#define ADC_DR_DATA_0                  (0x00000001UL)
#define ADC_DR_DATA_1                  (0x00000002UL)
#define ADC_DR_DATA_2                  (0x00000004UL)
#define ADC_DR_DATA_3                  (0x00000008UL)
#define ADC_DR_DATA_4                  (0x00000010UL)
#define ADC_DR_DATA_5                  (0x00000020UL)
#define ADC_DR_DATA_6                  (0x00000040UL)
#define ADC_DR_DATA_7                  (0x00000080UL)
#define ADC_DR_DATA_8                  (0x00000100UL)
#define ADC_DR_DATA_9                  (0x00000200UL)
#define ADC_DR_DATA_10                 (0x00000400UL)
#define ADC_DR_DATA_11                 (0x00000800UL)
#define ADC_DR_DATA_12                 (0x00001000UL)
#define ADC_DR_DATA_13                 (0x00002000UL)
#define ADC_DR_DATA_14                 (0x00004000UL)
#define ADC_DR_DATA_15                 (0x00008000UL)

/********************  Bit definition for ADC_AWD2CR register  ****************/
#define ADC_AWD2CR_AWD2CH_Pos          (0U)
#define ADC_AWD2CR_AWD2CH_MSK          (0x0007FFFF)                              /* ADC analog watchdog 2 monitored channel selection */
#define ADC_AWD2CR_AWD2CH_0            (0x00000001)                              /* 0x00000001 */
#define ADC_AWD2CR_AWD2CH_1            (0x00000002)                              /* 0x00000002 */
#define ADC_AWD2CR_AWD2CH_2            (0x00000004)                              /* 0x00000004 */
#define ADC_AWD2CR_AWD2CH_3            (0x00000008)                              /* 0x00000008 */
#define ADC_AWD2CR_AWD2CH_4            (0x00000010)                              /* 0x00000010 */
#define ADC_AWD2CR_AWD2CH_5            (0x00000020)                              /* 0x00000020 */
#define ADC_AWD2CR_AWD2CH_6            (0x00000040)                              /* 0x00000040 */
#define ADC_AWD2CR_AWD2CH_7            (0x00000080)                              /* 0x00000080 */
#define ADC_AWD2CR_AWD2CH_8            (0x00000100)                              /* 0x00000100 */
#define ADC_AWD2CR_AWD2CH_9            (0x00000200)                              /* 0x00000200 */
#define ADC_AWD2CR_AWD2CH_10           (0x00000400)                              /* 0x00000400 */
#define ADC_AWD2CR_AWD2CH_11           (0x00000800)                              /* 0x00000800 */
#define ADC_AWD2CR_AWD2CH_12           (0x00001000)                              /* 0x00001000 */
#define ADC_AWD2CR_AWD2CH_13           (0x00002000)                              /* 0x00002000 */
#define ADC_AWD2CR_AWD2CH_14           (0x00004000)                              /* 0x00004000 */
#define ADC_AWD2CR_AWD2CH_15           (0x00008000)                              /* 0x00008000 */
#define ADC_AWD2CR_AWD2CH_16           (0x00010000)                              /* 0x00010000 */
#define ADC_AWD2CR_AWD2CH_17           (0x00020000)                              /* 0x00020000 */
#define ADC_AWD2CR_AWD2CH_18           (0x00040000)                              /* 0x00040000 */

/********************  Bit definition for ADC_AWD3CR register  ****************/
#define ADC_AWD3CR_AWD3CH_Pos          (0U)
#define ADC_AWD3CR_AWD3CH_MSK          (0x7FFFFUL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x0007FFFF */
#define ADC_AWD3CR_AWD3CH              ADC_AWD3CR_AWD3CH_MSK                   /* ADC analog watchdog 3 monitored channel selection */
#define ADC_AWD3CR_AWD3CH_0            (0x00001UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000001 */
#define ADC_AWD3CR_AWD3CH_1            (0x00002UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000002 */
#define ADC_AWD3CR_AWD3CH_2            (0x00004UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000004 */
#define ADC_AWD3CR_AWD3CH_3            (0x00008UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000008 */
#define ADC_AWD3CR_AWD3CH_4            (0x00010UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000010 */
#define ADC_AWD3CR_AWD3CH_5            (0x00020UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000020 */
#define ADC_AWD3CR_AWD3CH_6            (0x00040UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000040 */
#define ADC_AWD3CR_AWD3CH_7            (0x00080UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000080 */
#define ADC_AWD3CR_AWD3CH_8            (0x00100UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000100 */
#define ADC_AWD3CR_AWD3CH_9            (0x00200UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000200 */
#define ADC_AWD3CR_AWD3CH_10           (0x00400UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000400 */
#define ADC_AWD3CR_AWD3CH_11           (0x00800UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00000800 */
#define ADC_AWD3CR_AWD3CH_12           (0x01000UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00001000 */
#define ADC_AWD3CR_AWD3CH_13           (0x02000UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00002000 */
#define ADC_AWD3CR_AWD3CH_14           (0x04000UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00004000 */
#define ADC_AWD3CR_AWD3CH_15           (0x08000UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00008000 */
#define ADC_AWD3CR_AWD3CH_16           (0x10000UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00010000 */
#define ADC_AWD3CR_AWD3CH_17           (0x20000UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00020000 */
#define ADC_AWD3CR_AWD3CH_18           (0x40000UL << ADC_AWD3CR_AWD3CH_Pos)    /* 0x00040000 */

/********************  Bit definition for ADC_CALFACT register  ***************/
#define ADC_CALFACT_CALFACT_MSK        (0x0000007F)                            /* ADC calibration factor in single-ended mode */
#define ADC_CALFACT_CALFACT_0          (0x00000001UL)
#define ADC_CALFACT_CALFACT_1          (0x00000002UL)
#define ADC_CALFACT_CALFACT_2          (0x00000004UL)
#define ADC_CALFACT_CALFACT_3          (0x00000008UL)
#define ADC_CALFACT_CALFACT_4          (0x00000010UL)
#define ADC_CALFACT_CALFACT_5          (0x00000020UL)
#define ADC_CALFACT_CALFACT_6          (0x00000040UL)

/*************************  ADC Common registers  *****************************/
/********************  Bit definition for ADC_CCR register  *******************/
#define ADC_CCR_PRESC_MSK              (0x003C0000)                            /* ADC common clock prescaler, only for clock source asynchronous */
#define ADC_CCR_PRESC_DIV2             (0x00040000UL)
#define ADC_CCR_PRESC_DIV4             (0x00080000UL)
#define ADC_CCR_PRESC_DIV6             (0x000c0000UL)
#define ADC_CCR_PRESC_DIV8             (0x00100000UL)
#define ADC_CCR_PRESC_DIV10            (0x00140000UL)
#define ADC_CCR_PRESC_DIV12            (0x00180000UL)
#define ADC_CCR_PRESC_DIV16            (0x001c0000UL)
#define ADC_CCR_PRESC_DIV32            (0x00200000UL)
#define ADC_CCR_PRESC_DIV64            (0x00240000UL)
#define ADC_CCR_PRESC_DIV128           (0x00280000UL)
#define ADC_CCR_PRESC_DIV256           (0x002c0000UL)


#define ADC_CCR_VREFEN_MSK             (0x00400000)                              /* ADC internal path to VrefInt enable */
#define ADC_CCR_TSEN_MSK               (0x00800000)                              /* ADC internal path to temperature sensor enable */
#define ADC_CCR_VBATEN_MSK             (0x01000000)                              /* ADC internal path to battery voltage enable */

/* Legacy */
#define ADC_CCR_LFMEN_MSK              (0x02000000)                              /* Legacy feature, useless on STM32G0 (ADC common clock low frequency mode is automatically managed by ADC peripheral on STM32G0) */


/* Data structure definition */
/****************************************************
*   Structure£º  T_ADC_MEM_MAP
*   Description£ºMemory map of ADC registers.
*   Parameter:   
*   Authour£º    Ian
*   Modify record:
*   Date:  2016-7-31 creat.
****************************************************/
typedef struct _T_ADC_MEM_MAP
{
    WORD32 ISR;          /* ADC interrupt and status register,             Address offset: 0x00 */
    WORD32 IER;          /* ADC interrupt enable register,                 Address offset: 0x04 */
    WORD32 CR;           /* ADC control register,                          Address offset: 0x08 */
    WORD32 CFGR1;        /* ADC configuration register 1,                  Address offset: 0x0C */
    WORD32 CFGR2;        /* ADC configuration register 2,                  Address offset: 0x10 */
    WORD32 SMPR;         /* ADC sampling time register,                    Address offset: 0x14 */
    WORD32 RESERVED1;    /* Reserved,                                                      0x18 */
    WORD32 RESERVED2;    /* Reserved,                                                      0x1C */
    WORD32 TR1;          /* ADC analog watchdog 1 threshold register,      Address offset: 0x20 */
    WORD32 TR2;          /* ADC analog watchdog 2 threshold register,      Address offset: 0x24 */
    WORD32 CHSELR;       /* ADC group regular sequencer register,          Address offset: 0x28 */
    WORD32 TR3;          /* ADC analog watchdog 3 threshold register,      Address offset: 0x2C */
    WORD32 RESERVED3[4]; /* Reserved,                                               0x30 - 0x3C */
    WORD32 DR;           /* ADC group regular data register,               Address offset: 0x40 */
    WORD32 RESERVED4[23];/* Reserved,                                               0x44 - 0x9C */
    WORD32 AWD2CR;       /* ADC analog watchdog 2 configuration register,  Address offset: 0xA0 */
    WORD32 AWD3CR;       /* ADC analog watchdog 3 configuration register,  Address offset: 0xA4 */
    WORD32 RESERVED5[3]; /* Reserved,                                               0xA8 - 0xB0 */
    WORD32 CALFACT;      /* ADC Calibration factor register,               Address offset: 0xB4 */
}volatile *T_ADC_MEM_MAP;

#define ADC_ISR         (ADC1->ISR)
#define ADC_IER         (ADC1->IER)
#define ADC_CR          (ADC1->CR)
#define ADC_CFGR1       (ADC1->CFGR1)
#define ADC_CFGR2       (ADC1->CFGR2)
#define ADC_SMPR        (ADC1->SMPR)
#define ADC_TR1         (ADC1->TR1)
#define ADC_TR2         (ADC1->TR2)
#define ADC_CHSELR      (ADC1->CHSELR)
#define ADC_TR3         (ADC1->TR3)
#define ADC_DR          (ADC1->DR)
#define ADC_AWD2CR      (ADC1->AWD2CR)
#define ADC_AWD3CR      (ADC1->AWD3CR)
#define ADC_CALFACT     (ADC1->CALFACT)
#define ADC_CCR         *(WORD32*)(ADC1_BASE + 0x308)

/* timer handler for flash operation. */
typedef struct
{
    WORD32 (*pfGetMs)(VOID);            /* the handler for getting ms-time. */
    WORD32 (*pfGetDlyMs)(WORD32);       /* the handler for getting ms-delay base an old ms-time. */
}T_ADC_TMOPER;

/* Declaration of functions */
/**************************************************************************
* Funciton: void ADC_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara)
* Descrip.: Register ADC
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
void ADC_Reg(BYTE ucLogNo, BYTE ucDevNo, VOID *ptPara);

/*****************************************************************************************************************************************
* Function: WORD32 ADCx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara)
* Descrip.: Control and configuration of ADC
* Input   : T_SW_DEVICEDRIVER_PARA *ptPara
*              ucPara[0]      BYTE      SW_PERIPHERAL_AD         Device type.              ADC_PARA_DEVTYPE_INDEX
*              ucPara[1]      BYTE      0                        Device physical number.   ADC_PARA_DEV_NO_INDEX
*              ucPara[2]      BYTE      0                        Channel physical number.  ADC_PARA_CHNL_NO_INDEX
*              ucPara[3]      BYTE      control command.         adc control command.      ADC_PARA_CMD_INDEX
*                                          SW_ADC_SOFT_STOP
*                                          SW_ADC_SOFT_START
*                                          SW_ADC_CONFIGURE
*              ucPara[4]      BYTE      command parameter.                                 ADC_PARA_CMD_PARA_INDEX
*                                          if ucPara[3] == SW_ADC_CONFIGURE then
*                                             ucPara[4] =  configure data;
*
*                                             if SW_ADC_LOWEST_SPEED then
*                                                sampling is in the lowest speed.
*                                             elif SW_ADC_MIDDLE_SPEED then
*                                                sampling is in the middle speed.
*                                             elif SW_ADC_HIGHEST_SPPED then
*                                                sampling is in the highest speed.
*                                             endif
*
*                                             if SW_ADC_LOWPW_EN then
*                                                nothing.
*                                             endif
*
*                                             if SW_ADC_TRIGGER_HARDWARE then
*                                                ucPara[5].bit0-bit2 device's hardware trigger number.   ADC_PARA_TRIGGER_INDEX
*                                                        ADC_TIM1_TRGO2
*                                                        ADC_TIM1_CC4  
*                                                        ADC_RESERVE1  
*                                                        ADC_TIM3_TRGO 
*                                                        ADC_TIM15_TRGO
*                                                        ADC_TIM6_TRGO 
*                                                        ADC_RESERVE2  
*                                                        ADC_EXTI_LINE 
*                                                ucPara[5].bit3-bit4 trigger polarity setting in hardware trigger mode.
*                                                        ADC_TRG_POL_H
*                                                        ADC_TRG_POL_L
*                                                        ADC_TRG_POL_HL
*                                             elif SW_ADC_TRIGGER_SOFT then
*                                                 conversion is triggered by software.
*                                             endif
*
*                                             if SW_ADC_SINGLE_CHL then
*                                                 one trigger one time sampling on the next one channel.
*                                             elif SW_ADC_GROUP_CHL then
*                                                 nothing.
*                                             elif SW_ADC_BURST_CHL then
*                                                 nothing.
*                                             endif
*
*                                             if SW_ADC_INT_EN then
*                                                 use interrupt to handle ADC,else not.
*                                             endif
*
*                                             if SW_ADC_DMA_EN then
*                                                 use DMA to handle ADC,else not. in this mode, only BUST mode is used.
*                                                 we shold enable ADC's interrupt and disable ADC interrupt in NVIC.
*                                             endif
*                                             
*                                             ucPara[6] =  sample number;         ADC_PARA_SAMPLE_CNT_INDEX
*                                                 if 0== ucPara[6] then ADC does not need to oversample.
*                                                 else ADC oversamples. ucPara[6] =  ADC_OVERSMPLE_0
*                                                                                    ADC_OVERSMPLE_2  
*                                                                                    ADC_OVERSMPLE_4  
*                                                                                    ADC_OVERSMPLE_8  
*                                                                                    ADC_OVERSMPLE_16 
*                                                                                    ADC_OVERSMPLE_32 
*                                                                                    ADC_OVERSMPLE_64 
*                                                                                    ADC_OVERSMPLE_128
*                                                                                    ADC_OVERSMPLE_256
*                                             pdwPara[0] : channel shoose.
*                                               pdwPara[0].bit0~bit18 <--> phy. channel 0  ~ phy. channel 18
*                                                          bit x = 1   --> phy. channel x is used. 
*                                               it is NOT logical channel. it means a physical channel is used.
*                                          endif
*
*                                          if ucPara[3] == SW_ADC_SOFT_START / SW_ADC_SOFT_STOP then
*                                             ucPara[2] =  channel number. Attention : it's a physical channel number beginning from 0.
*                                          endif
* Output  : no.
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    £ºNone
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------------------------------
* 2016/07/31       V1.0         Ian          Create 
*****************************************************************************************************************************************/
WORD32 ADCx_Ctrl(T_SW_DEVICEDRIVER_PARA *ptPara);

/*****************************************************************************************************************
* Funciton: void Adcx_isr(void)
* Descrip.: interrupt process function of adc. used for sequence handling. it can not be used with software trigger
*           at the same time.
* Input   : no.
* Output  : no.
* Return  : no.
* Note    : This ISR will call the application callback function.the description of callback function's parameter
*           is as below:
*           T_SW_INT_EVENT  tReason
*             ucAppType        :   SW_MATH_INTERFACE.
*             ucDevId          :   SW_PERIPHERAL_AD
*             ucDevNo          :   device's physical No.
*             ucEvent          :   INTERRUPT_EVENT_RX
*                                        ucBuffer[0] is the physical channel No. begin with 0.
*                                        ucBuffer[1] is the low 8 bits of sampling data.
*                                        ucBuffer[2] is the up 4 bits of sampling data.
* Date             Version     Author        Content
* ---------------------------------------------------------------------------------------------------------------
* 2018/06/06        V1.0      Danny.cao      creation
*****************************************************************************************************************/
void Adcx_isr(void);

/*****************************************************************************************************************
* Funciton: WORD32 ADCx_Read(T_DATA_OPERARTION  *ptData)
* Descrip.: Get data from ADC data register
* Input   : None.
* Output  : T_DATA_OPERARTION  *ptData: 
*              ucDevNo       0              Device No.
*              pucBuffer     0~255          Low 8-bit of ADC data
*              pucBuffer+1   0~255          High 8-bit of ADC data
*              wDataLength   0~65535        The length of ADC data
* Return  : SW_OK    Successful
            SW_ERR   Failed
* Note    : None
* Date             Version     Author        Content
* ----------------------------------------------------------------------------------------------------------------
* 2016/07/31       V1.0       Danny.cao      Create 
*****************************************************************************************************************/
WORD32 ADCx_Read(T_DATA_OPERARTION  *ptData);

#ifdef __cplusplus
}
#endif

#endif /* _STM32G0XXX_ADC_H_ */



