/********************************************************************
* Right reserved (C 2016) for *********** company.
*
* File Name        : Stm32F10XX_adc.h
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


#ifndef _STM32F10XX_ADC_H_
#define _STM32F10XX_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ADC_DEVICE_NUM                  (2)                                /* Max number of adc           */
#define SYSCLK_FREQ_24M                     24000000
#define SYSCLK_FREQ_36M                     36000000
#define SYSCLK_FREQ_48M                     48000000
#define SYSCLK_FREQ_56M                     56000000
#define SYSCLK_FREQ_72M                     72000000

/* ADC parameter data field position definition   */
#define ADC_DEV_NO_POS                      (1)                                /* Field of adc nubmer         */
#define ADC_PORT_CH_POS                     (2)                                /* Field of Port channel       */
#define ADC_START_POS                       (3)                                /* Field of start/stop         */
#define ADC_SAMPLE_CNT                      (4)                                /* Field of sampling count     */

/* ADC number */
#define ADC_1                                  (1)
#define ADC_2                                  (2)

/* ADC base addresses */
#define ADC1_BASE                           ((T_ADC_MEM_MAP)0x40012400u)       /* Address of base register for ADC1 */
#define ADC2_BASE                           ((T_ADC_MEM_MAP)0x40012800u)       /* Address of base register for ADC2 */

#define ADCX_BASE(n)                        ((T_ADC_MEM_MAP)(0x40012400u + 0x400 * (n - 1)))

/* ADC Register accessors */
#define ADCX_SR(n)                          (ADCX_BASE(n)->SR)                 /* Address of Status register                       */
#define ADCX_CR1(n)                         (ADCX_BASE(n)->CR1)                /* Address of Control register 1                    */
#define ADCX_CR2(n)                         (ADCX_BASE(n)->CR2)                /* Address of Control regitset 2                    */
#define ADCX_SMPR1(n)                       (ADCX_BASE(n)->SMPR1)              /* Address of Sample time register 1                */
#define ADCX_SMPR2(n)                       (ADCX_BASE(n)->SMPR2)              /* Address of Sample time register 2                */
#define ADCX_JOFR1(n)                       (ADCX_BASE(n)->JOFR1)              /* Address of Inject channel data offset register 1 */
#define ADCX_JOFR2(n)                       (ADCX_BASE(n)->JOFR2)              /* Address of Inject channel data offset register 2 */
#define ADCX_JOFR3(n)                       (ADCX_BASE(n)->JOFR3)              /* Address of Inject channel data offset register 3 */
#define ADCX_JOFR4(n)                       (ADCX_BASE(n)->JOFR4)              /* Address of Inject channel data offset register 4 */
#define ADCX_HTR(n)                         (ADCX_BASE(n)->HTR)                /* Address of Watchdog high threshold register 1    */
#define ADCX_LTR(n)                         (ADCX_BASE(n)->LTR)                /* Address of Watchdog low threshold register 2     */
#define ADCX_SQR1(n)                        (ADCX_BASE(n)->SQR1)               /* Address of Regular sequence register 1           */
#define ADCX_SQR2(n)                        (ADCX_BASE(n)->SQR2)               /* Address of Regular sequence register 2           */
#define ADCX_SQR3(n)                        (ADCX_BASE(n)->SQR3)               /* Address of Regular sequence register 3           */
#define ADCX_JSQR(n)                        (ADCX_BASE(n)->JSQR)               /* Address of Inject sequence register              */
#define ADCX_JDR1(n)                        (ADCX_BASE(n)->JDR1)               /* Address of Inject data register 1                */
#define ADCX_JDR2(n)                        (ADCX_BASE(n)->JDR2)               /* Address of Inject data register 2                */
#define ADCX_JDR3(n)                        (ADCX_BASE(n)->JDR3)               /* Address of Inject data register 3                */
#define ADCX_JDR4(n)                        (ADCX_BASE(n)->JDR4)               /* Address of Inject data register 4                */
#define ADCX_DR(n)                          (ADCX_BASE(n)->DR)                 /* Address of Regular data register                 */


/* ADC Register accessors for each ADC */
/* ADC1 */
#define ADC1_SR                             (ADCX_SR(ADC_1))                   /* Address of Status register                       */
#define ADC1_CR1                            (ADCX_CR1(ADC_1))                  /* Address of Control register 1                    */
#define ADC1_CR2                            (ADCX_CR2(ADC_1))                  /* Address of Control regitset 2                    */
#define ADC1_SMPR1                          (ADCX_SMPR1(ADC_1))                /* Address of Sample time register 1                */
#define ADC1_SMPR2                          (ADCX_SMPR2(ADC_1))                /* Address of Sample time register 2                */
#define ADC1_JOFR1                          (ADCX_JOFR1(ADC_1))                /* Address of Inject channel data offset register 1 */
#define ADC1_JOFR2                          (ADCX_JOFR2(ADC_1))                /* Address of Inject channel data offset register 2 */
#define ADC1_JOFR3                          (ADCX_JOFR3(ADC_1))                /* Address of Inject channel data offset register 3 */
#define ADC1_JOFR4                          (ADCX_JOFR4(ADC_1))                /* Address of Inject channel data offset register 4 */
#define ADC1_HTR                            (ADCX_HTR(ADC_1))                  /* Address of Watchdog high threshold register 1    */
#define ADC1_LTR                            (ADCX_LTR(ADC_1))                  /* Address of Watchdog low threshold register 2     */
#define ADC1_SQR1                           (ADCX_SQR1(ADC_1))                 /* Address of Regular sequence register 1           */
#define ADC1_SQR2                           (ADCX_SQR2(ADC_1))                 /* Address of Regular sequence register 2           */
#define ADC1_SQR3                           (ADCX_SQR3(ADC_1))                 /* Address of Regular sequence register 3           */
#define ADC1_JSQR                           (ADCX_JSQR(ADC_1))                 /* Address of Inject sequence register              */
#define ADC1_JDR1                           (ADCX_JDR1(ADC_1))                 /* Address of Inject data register 1                */
#define ADC1_JDR2                           (ADCX_JDR2(ADC_1))                 /* Address of Inject data register 2                */
#define ADC1_JDR3                           (ADCX_JDR3(ADC_1))                 /* Address of Inject data register 3                */
#define ADC1_JDR4                           (ADCX_JDR4(ADC_1))                 /* Address of Inject data register 4                */
#define ADC1_DR                             (ADCX_DR(ADC_1))                   /* Address of Regular data register                 */

/* ADC2 */
#define ADC2_SR                             (ADCX_SR(ADC_2))                   /* Address of Status register                       */
#define ADC2_CR1                            (ADCX_CR1(ADC_2))                  /* Address of Control register 1                    */
#define ADC2_CR2                            (ADCX_CR2(ADC_2))                  /* Address of Control regitset 2                    */
#define ADC2_SMPR1                          (ADCX_SMPR1(ADC_2))                /* Address of Sample time register 1                */
#define ADC2_SMPR2                          (ADCX_SMPR2(ADC_2))                /* Address of Sample time register 2                */
#define ADC2_JOFR1                          (ADCX_JOFR1(ADC_2))                /* Address of Inject channel data offset register 1 */
#define ADC2_JOFR2                          (ADCX_JOFR2(ADC_2))                /* Address of Inject channel data offset register 2 */
#define ADC2_JOFR3                          (ADCX_JOFR3(ADC_2))                /* Address of Inject channel data offset register 3 */
#define ADC2_JOFR4                          (ADCX_JOFR4(ADC_2))                /* Address of Inject channel data offset register 4 */
#define ADC2_HTR                            (ADCX_HTR(ADC_2))                  /* Address of Watchdog high threshold register 1    */
#define ADC2_LTR                            (ADCX_LTR(ADC_2))                  /* Address of Watchdog low threshold register 2     */
#define ADC2_SQR1                           (ADCX_SQR1(ADC_2))                 /* Address of Regular sequence register 1           */
#define ADC2_SQR2                           (ADCX_SQR2(ADC_2))                 /* Address of Regular sequence register 2           */
#define ADC2_SQR3                           (ADCX_SQR3(ADC_2))                 /* Address of Regular sequence register 3           */
#define ADC2_JSQR                           (ADCX_JSQR(ADC_2))                 /* Address of Inject sequence register              */
#define ADC2_JDR1                           (ADCX_JDR1(ADC_2))                 /* Address of Inject data register 1                */
#define ADC2_JDR2                           (ADCX_JDR2(ADC_2))                 /* Address of Inject data register 2                */
#define ADC2_JDR3                           (ADCX_JDR3(ADC_2))                 /* Address of Inject data register 3                */
#define ADC2_JDR4                           (ADCX_JDR4(ADC_2))                 /* Address of Inject data register 4                */
#define ADC2_DR                             (ADCX_DR(ADC_2))                   /* Address of Regular data register                 */



/* Bit definition for ADC_SR register */
#define ADC_SR_AWD_POS                      (0U)                               
#define ADC_SR_AWD_MASK                     (0x00000001)                       /* 0x00000001                 */
#define ADC_SR_AWD                          (ADC_SR_AWD_MASK)                  /* ADC analog watchdog 1 flag */
#define ADC_SR_EOS_POS                      (1U)                               
#define ADC_SR_EOS_MASK                     (0x00000002)                       /* 0x00000002                                         */
#define ADC_SR_EOS                          (ADC_SR_EOS_MASK)                  /* ADC group regular end of sequence conversions flag */
#define ADC_SR_JEOS_POS                     (2U)                               
#define ADC_SR_JEOS_MASK                    (0x00000004)                       /* 0x00000004                                          */
#define ADC_SR_JEOS                         (ADC_SR_JEOS_MASK                  /* ADC group injected end of sequence conversions flag */
#define ADC_SR_JSTRT_POS                    (3U)                               
#define ADC_SR_JSTRT_MASK                   (0x00000008)                       /* 0x00000008                               */
#define ADC_SR_JSTRT                        (ADC_SR_JSTRT_MASK)                /* ADC group injected conversion start flag */
#define ADC_SR_STRT_POS                     (4U)                               
#define ADC_SR_STRT_MASK                    (0x00000010)                       /* 0x00000010                              */
#define ADC_SR_STRT                         (ADC_SR_STRT_MASK)                 /* ADC group regular conversion start flag */

/* Legacy defines */
#define ADC_SR_EOC                          (ADC_SR_EOS)
#define ADC_SR_JEOC                         (ADC_SR_JEOS)

/* Bit definition for ADC_CR1 register */
#define ADC_CR1_AWDCH_POS                   (0U)                               
#define ADC_CR1_AWDCH_MASK                  (0x0000001F)                       /* 0x0000001F                                        */
#define ADC_CR1_AWDCH                       (ADC_CR1_AWDCH_MASK)               /* ADC analog watchdog 1 monitored channel selection */
#define ADC_CR1_AWDCH_0                     (0x00000001)                       /* 0x00000001                                        */
#define ADC_CR1_AWDCH_1                     (0x00000002)                       /* 0x00000002                                        */
#define ADC_CR1_AWDCH_2                     (0x00000004)                       /* 0x00000004                                        */
#define ADC_CR1_AWDCH_3                     (0x00000008)                       /* 0x00000008                                        */
#define ADC_CR1_AWDCH_4                     (0x00000010)                       /* 0x00000010                                        */

#define ADC_CR1_EOSIE_POS                   (5U)                               
#define ADC_CR1_EOSIE_MASK                  (0x00000020)                       /* 0x00000020                                              */
#define ADC_CR1_EOSIE                       (ADC_CR1_EOSIE_MASK)               /* ADC group regular end of sequence conversions interrupt */
#define ADC_CR1_AWDIE_POS                   (6U)                               
#define ADC_CR1_AWDIE_MASK                  (0x00000040)                       /* 0x00000040                      */
#define ADC_CR1_AWDIE                       (ADC_CR1_AWDIE_MASK)               /* ADC analog watchdog 1 interrupt */
#define ADC_CR1_JEOSIE_POS                  (7U)                               
#define ADC_CR1_JEOSIE_MASK                 (0x00000080)                       /* 0x00000080                                               */
#define ADC_CR1_JEOSIE                      (ADC_CR1_JEOSIE_MASK)              /* ADC group injected end of sequence conversions interrupt */
#define ADC_CR1_SCAN_POS                    (8U)                               
#define ADC_CR1_SCAN_MASK                   (0x00000100)                       /* 0x00000100    */
#define ADC_CR1_SCAN                        (ADC_CR1_SCAN_MASK)                /* ADC scan mode */
#define ADC_CR1_AWDSGL_POS                  (9U)                               
#define ADC_CR1_AWDSGL_MASK                 (0x00000200)                       /* 0x00000200                                                        */
#define ADC_CR1_AWDSGL                      (ADC_CR1_AWDSGL_MASK)              /* ADC analog watchdog 1 monitoring a single channel or all channels */
#define ADC_CR1_JAUTO_POS                   (10U)                              
#define ADC_CR1_JAUTO_MASK                  (0x00000400)                       /* 0x00000400                                */
#define ADC_CR1_JAUTO                       (ADC_CR1_JAUTO_MASK)               /* ADC group injected automatic trigger mode */
#define ADC_CR1_DISCEN_POS                  (11U)                              
#define ADC_CR1_DISCEN_MASK                 (0x00000800)                       /* 0x00000800                                     */
#define ADC_CR1_DISCEN                      (ADC_CR1_DISCEN_MASK)              /* ADC group regular sequencer discontinuous mode */
#define ADC_CR1_JDISCEN_POS                 (12U)                              
#define ADC_CR1_JDISCEN_MASK                (0x00001000)                       /* 0x00001000                                      */
#define ADC_CR1_JDISCEN                     (ADC_CR1_JDISCEN_MASK)             /* ADC group injected sequencer discontinuous mode */

#define ADC_CR1_DISCNUM_POS                 (13U)                              
#define ADC_CR1_DISCNUM_MASK                (0x0000E000)                       /* 0x0000E000                                                */
#define ADC_CR1_DISCNUM                     (ADC_CR1_DISCNUM_MASK)             /* ADC group regular sequencer discontinuous number of ranks */
#define ADC_CR1_DISCNUM_0                   (0x00002000)                       /* 0x00002000                                                */
#define ADC_CR1_DISCNUM_1                   (0x00004000)                       /* 0x00004000                                                */
#define ADC_CR1_DISCNUM_2                   (0x00008000)                       /* 0x00008000                                                */

#define ADC_CR1_DUALMOD_POS                 (16U)                              
#define ADC_CR1_DUALMOD_MASK                (0x000F0000)                       /* 0x000F0000                   */
#define ADC_CR1_DUALMOD                     (ADC_CR1_DUALMOD_MASK)             /* ADC multimode mode selection */
#define ADC_CR1_DUALMOD_0                   (0x00010000)                       /* 0x00010000                   */
#define ADC_CR1_DUALMOD_1                   (0x00020000)                       /* 0x00020000                   */
#define ADC_CR1_DUALMOD_2                   (0x00040000)                       /* 0x00040000                   */
#define ADC_CR1_DUALMOD_3                   (0x00080000)                       /* 0x00080000                   */

#define ADC_CR1_JAWDEN_POS                  (22U)                              
#define ADC_CR1_JAWDEN_MASK                 (0x00400000)                       /* 0x00400000                                               */
#define ADC_CR1_JAWDEN                      (ADC_CR1_JAWDEN_MASK)              /* ADC analog watchdog 1 enable on scope ADC group injected */
#define ADC_CR1_AWDEN_POS                   (23U)                              
#define ADC_CR1_AWDEN_MASK                  (0x00800000)                       /* 0x00800000                                              */
#define ADC_CR1_AWDEN                       (ADC_CR1_AWDEN_MASK)               /* ADC analog watchdog 1 enable on scope ADC group regular */

/* Legacy defines */
#define  ADC_CR1_EOCIE                       (ADC_CR1_EOSIE)
#define  ADC_CR1_JEOCIE                      (ADC_CR1_JEOSIE)

/* Bit definition for ADC_CR2 register */
#define ADC_CR2_ADON_POS                    (0U)                               
#define ADC_CR2_ADON_MASK                   (0x00000001)                       /* 0x00000001                                   */
#define ADC_CR2_ADON                        (ADC_CR2_ADON_MASK)                /* ADC enable                                   */
#define ADC_CR2_CONT_POS                    (1U)                               
#define ADC_CR2_CONT_MASK                   (0x00000002)                       /* 0x00000002                                   */
#define ADC_CR2_CONT                        (ADC_CR2_CONT_MASK)                /* ADC group regular continuous conversion mode */
#define ADC_CR2_CAL_POS                     (2U)                               
#define ADC_CR2_CAL_MASK                    (0x00000004)                       /* 0x00000004            */
#define ADC_CR2_CAL                         (ADC_CR2_CAL_MASK)                 /* ADC calibration start */
#define ADC_CR2_RSTCAL_POS                  (3U)                               
#define ADC_CR2_RSTCAL_MASK                 (0x00000008)                       /* 0x00000008            */
#define ADC_CR2_RSTCAL                      (ADC_CR2_RSTCAL_MASK)              /* ADC calibration reset */
#define ADC_CR2_DMA_POS                     (8U)                               
#define ADC_CR2_DMA_MASK                    (0x00000100)                       /* 0x00000100              */
#define ADC_CR2_DMA                         (ADC_CR2_DMA_MASK)                 /* ADC DMA transfer enable */
#define ADC_CR2_ALIGN_POS                   (11U)                              
#define ADC_CR2_ALIGN_MASK                  (0x00000800)                       /* 0x00000800          */
#define ADC_CR2_ALIGN                       (ADC_CR2_ALIGN_MASK)               /* ADC data alignement */

#define ADC_CR2_JEXTSEL_POS                 (12U)                              
#define ADC_CR2_JEXTSEL_MASK                (0x00007000)                       /* 0x00007000                                 */
#define ADC_CR2_JEXTSEL                     (ADC_CR2_JEXTSEL_MASK)             /* ADC group injected external trigger source */
#define ADC_CR2_JEXTSEL_0                   (0x00001000)                       /* 0x00001000                                 */
#define ADC_CR2_JEXTSEL_1                   (0x00002000)                       /* 0x00002000                                 */
#define ADC_CR2_JEXTSEL_2                   (0x00004000)                       /* 0x00004000                                 */

#define ADC_CR2_JEXTTRIG_POS                (15U)                              
#define ADC_CR2_JEXTTRIG_MASK               (0x00008000)                       /* 0x00008000                                 */
#define ADC_CR2_JEXTTRIG                    (ADC_CR2_JEXTTRIG_MASK)            /* ADC group injected external trigger enable */

#define ADC_CR2_EXTSEL_POS                  (17U)                              
#define ADC_CR2_EXTSEL_MASK                 (0x000E0000)                       /* 0x000E0000                                */
#define ADC_CR2_EXTSEL                      (ADC_CR2_EXTSEL_MASK)              /* ADC group regular external trigger source */
#define ADC_CR2_EXTSEL_0                    (0x00020000)                       /* 0x00020000                                */
#define ADC_CR2_EXTSEL_1                    (0x00040000)                       /* 0x00040000                                */
#define ADC_CR2_EXTSEL_2                    (0x00080000)                       /* 0x00080000                                */

#define ADC_CR2_EXTSEL_SWSTART              (0x000E0000)                       /* 0x000E0000                                */

#define ADC_CR2_EXTTRIG_POS                 (20U)                              
#define ADC_CR2_EXTTRIG_MASK                (0x00100000)                       /* 0x00100000                                */
#define ADC_CR2_EXTTRIG                     (ADC_CR2_EXTTRIG_MASK)             /* ADC group regular external trigger enable */
#define ADC_CR2_JSWSTART_POS                (21U)                              
#define ADC_CR2_JSWSTART_MASK               (0x00200000)                       /* 0x00200000                          */
#define ADC_CR2_JSWSTART                    (ADC_CR2_JSWSTART_MASK)            /* ADC group injected conversion start */
#define ADC_CR2_SWSTART_POS                 (22U)                              
#define ADC_CR2_SWSTART_MASK                (0x00400000)                       /* 0x00400000                         */
#define ADC_CR2_SWSTART                     (ADC_CR2_SWSTART_MASK)             /* ADC group regular conversion start */
#define ADC_CR2_TSVREFE_POS                 (23U)                              
#define ADC_CR2_TSVREFE_MASK                (0x00800000)                       /* 0x00800000                                                 */
#define ADC_CR2_TSVREFE                     (ADC_CR2_TSVREFE_MASK)             /* ADC internal path to VrefInt and temperature sensor enable */

/* Bit definition for ADC_SMPR1 register */
#define ADC_SMPR1_SMP10_POS                 (0U)                               
#define ADC_SMPR1_SMP10_MASK                (0x00000007)                       /* 0x00000007                             */
#define ADC_SMPR1_SMP10                     (ADC_SMPR1_SMP10_MASK)             /* ADC channel 10 sampling time selection */
#define ADC_SMPR1_SMP10_0                   (0x00000001)                       /* 0x00000001                             */
#define ADC_SMPR1_SMP10_1                   (0x00000002)                       /* 0x00000002                             */
#define ADC_SMPR1_SMP10_2                   (0x00000004)                       /* 0x00000004                             */

#define ADC_SMPR1_SMP10_SEL(a)              ((a) << ADC_SMPR1_SMP10_POS)

#define ADC_SMPR1_SMP11_POS                 (3U)                               
#define ADC_SMPR1_SMP11_MASK                (0x00000038)                       /* 0x00000038                             */
#define ADC_SMPR1_SMP11                     (ADC_SMPR1_SMP11_MASK)             /* ADC channel 11 sampling time selection */
#define ADC_SMPR1_SMP11_0                   (0x00000008)                       /* 0x00000008                             */
#define ADC_SMPR1_SMP11_1                   (0x00000010)                       /* 0x00000010                             */
#define ADC_SMPR1_SMP11_2                   (0x00000020)                       /* 0x00000020                             */

#define ADC_SMPR1_SMP11_SEL(a)              ((a) << ADC_SMPR1_SMP11_POS)

#define ADC_SMPR1_SMP12_POS                 (6U)                               
#define ADC_SMPR1_SMP12_MASK                (0x000001C0)                       /* 0x000001C0                              */
#define ADC_SMPR1_SMP12                     (ADC_SMPR1_SMP12_MASK)             /* ADC channel 12 sampling time selection  */
#define ADC_SMPR1_SMP12_0                   (0x00000040)                       /* 0x00000040                              */
#define ADC_SMPR1_SMP12_1                   (0x00000080)                       /* 0x00000080                              */
#define ADC_SMPR1_SMP12_2                   (0x00000100)                       /* 0x00000100                              */

#define ADC_SMPR1_SMP12_SEL(a)              ((a) << ADC_SMPR1_SMP12_POS)

#define ADC_SMPR1_SMP13_POS                 (9U)                               
#define ADC_SMPR1_SMP13_MASK                (0x00000E00)                       /* 0x00000E00                              */
#define ADC_SMPR1_SMP13                     (ADC_SMPR1_SMP13_MASK)             /* ADC channel 13 sampling time selection  */
#define ADC_SMPR1_SMP13_0                   (0x00000200)                       /* 0x00000200                              */
#define ADC_SMPR1_SMP13_1                   (0x00000400)                       /* 0x00000400                              */
#define ADC_SMPR1_SMP13_2                   (0x00000800)                       /* 0x00000800                              */

#define ADC_SMPR1_SMP13_SEL(a)              ((a) << ADC_SMPR1_SMP13_POS)

#define ADC_SMPR1_SMP14_POS                 (12U)                              
#define ADC_SMPR1_SMP14_MASK                (0x00007000)                       /* 0x00007000                              */
#define ADC_SMPR1_SMP14                     (ADC_SMPR1_SMP14_MASK)             /* ADC channel 14 sampling time selection  */
#define ADC_SMPR1_SMP14_0                   (0x00001000)                       /* 0x00001000                              */
#define ADC_SMPR1_SMP14_1                   (0x00002000)                       /* 0x00002000                              */
#define ADC_SMPR1_SMP14_2                   (0x00004000)                       /* 0x00004000                              */

#define ADC_SMPR1_SMP14_SEL(a)              ((a) << ADC_SMPR1_SMP14_POS)

#define ADC_SMPR1_SMP15_POS                 (15U)                              
#define ADC_SMPR1_SMP15_MASK                (0x00038000)                       /* 0x00038000 */
#define ADC_SMPR1_SMP15                     (ADC_SMPR1_SMP15_MASK)             /* ADC channel 15 sampling time selection  */
#define ADC_SMPR1_SMP15_0                   (0x00008000)                       /* 0x00008000                              */
#define ADC_SMPR1_SMP15_1                   (0x00010000)                       /* 0x00010000                              */
#define ADC_SMPR1_SMP15_2                   (0x00020000)                       /* 0x00020000                              */

#define ADC_SMPR1_SMP15_SEL(a)              ((a) << ADC_SMPR1_SMP15_POS)

#define ADC_SMPR1_SMP16_POS                 (18U)                              
#define ADC_SMPR1_SMP16_MASK                (0x001C0000)                       /* 0x001C0000 */
#define ADC_SMPR1_SMP16                     (ADC_SMPR1_SMP16_MASK)             /* ADC channel 16 sampling time selection  */
#define ADC_SMPR1_SMP16_0                   (0x00040000)                       /* 0x00040000                              */
#define ADC_SMPR1_SMP16_1                   (0x00080000)                       /* 0x00080000                              */
#define ADC_SMPR1_SMP16_2                   (0x00100000)                       /* 0x00100000                              */

#define ADC_SMPR1_SMP16_SEL(a)              ((a) << ADC_SMPR1_SMP16_POS)

#define ADC_SMPR1_SMP17_POS                 (21U)                              
#define ADC_SMPR1_SMP17_MASK                (0x00E00000)                       /* 0x00E00000                              */
#define ADC_SMPR1_SMP17                     (ADC_SMPR1_SMP17_MASK)             /* ADC channel 17 sampling time selection  */
#define ADC_SMPR1_SMP17_0                   (0x00200000)                       /* 0x00200000                              */
#define ADC_SMPR1_SMP17_1                   (0x00400000)                       /* 0x00400000                              */
#define ADC_SMPR1_SMP17_2                   (0x00800000)                       /* 0x00800000                              */

#define ADC_SMPR1_SMP17_SEL(a)              ((a) << ADC_SMPR1_SMP17_POS)        

/* Bit definition for ADC_SMPR2 register */
#define ADC_SMPR2_SMP0_POS                  (0U)                               
#define ADC_SMPR2_SMP0_MASK                 (0x00000007)                       /* 0x00000007                              */
#define ADC_SMPR2_SMP0                      (ADC_SMPR2_SMP0_MASK)              /* ADC channel 0 sampling time selection   */
#define ADC_SMPR2_SMP0_0                    (0x00000001)                       /* 0x00000001                              */
#define ADC_SMPR2_SMP0_1                    (0x00000002)                       /* 0x00000002                              */
#define ADC_SMPR2_SMP0_2                    (0x00000004)                       /* 0x00000004                              */

#define ADC_SMPR2_SMP0_SEL(a)               ((a) << ADC_SMPR2_SMP0_POS)        

#define ADC_SMPR2_SMP1_POS                  (3U)                               
#define ADC_SMPR2_SMP1_MASK                 (0x00000038)                       /* 0x00000038 */
#define ADC_SMPR2_SMP1                      (ADC_SMPR2_SMP1_MASK)              /* ADC channel 1 sampling time selection   */
#define ADC_SMPR2_SMP1_0                    (0x00000008)                       /* 0x00000008                              */
#define ADC_SMPR2_SMP1_1                    (0x00000010)                       /* 0x00000010                              */
#define ADC_SMPR2_SMP1_2                    (0x00000020)                       /* 0x00000020                              */

#define ADC_SMPR2_SMP1_SEL(a)               ((a) << ADC_SMPR2_SMP1_POS)        

#define ADC_SMPR2_SMP2_POS                  (6U)                               
#define ADC_SMPR2_SMP2_MASK                 (0x000001C0)                       /* 0x000001C0                              */
#define ADC_SMPR2_SMP2                      (ADC_SMPR2_SMP2_MASK)              /* ADC channel 2 sampling time selection   */
#define ADC_SMPR2_SMP2_0                    (0x00000040)                       /* 0x00000040                              */
#define ADC_SMPR2_SMP2_1                    (0x00000080)                       /* 0x00000080                              */
#define ADC_SMPR2_SMP2_2                    (0x00000100)                       /* 0x00000100                              */

#define ADC_SMPR2_SMP2_SEL(a)               ((a) << ADC_SMPR2_SMP2_POS)        

#define ADC_SMPR2_SMP3_POS                  (9U)                               
#define ADC_SMPR2_SMP3_MASK                 (0x00000E00)                       /* 0x00000E00                              */
#define ADC_SMPR2_SMP3                      (ADC_SMPR2_SMP3_MASK)              /* ADC channel 3 sampling time selection   */
#define ADC_SMPR2_SMP3_0                    (0x00000200)                       /* 0x00000200                              */
#define ADC_SMPR2_SMP3_1                    (0x00000400)                       /* 0x00000400                              */
#define ADC_SMPR2_SMP3_2                    (0x00000800)                       /* 0x00000800                              */

#define ADC_SMPR2_SMP3_SEL(a)               ((a) << ADC_SMPR2_SMP3_POS)        

#define ADC_SMPR2_SMP4_POS                  (12U)                              
#define ADC_SMPR2_SMP4_MASK                 (0x00007000)                       /* 0x00007000                              */
#define ADC_SMPR2_SMP4                      (ADC_SMPR2_SMP4_MASK)              /* ADC channel 4 sampling time selection   */
#define ADC_SMPR2_SMP4_0                    (0x00001000)                       /* 0x00001000                              */
#define ADC_SMPR2_SMP4_1                    (0x00002000)                       /* 0x00002000                              */
#define ADC_SMPR2_SMP4_2                    (0x00004000)                       /* 0x00004000                              */

#define ADC_SMPR2_SMP4_SEL(a)               ((a) << ADC_SMPR2_SMP4_POS)        

#define ADC_SMPR2_SMP5_POS                  (15U)                              
#define ADC_SMPR2_SMP5_MASK                 (0x00038000)                       /* 0x00038000                              */
#define ADC_SMPR2_SMP5                      (ADC_SMPR2_SMP5_MASK)              /* ADC channel 5 sampling time selection   */
#define ADC_SMPR2_SMP5_0                    (0x00008000)                       /* 0x00008000                              */
#define ADC_SMPR2_SMP5_1                    (0x00010000)                       /* 0x00010000                              */
#define ADC_SMPR2_SMP5_2                    (0x00020000)                       /* 0x00020000                              */

#define ADC_SMPR2_SMP5_SEL(a)               ((a) << ADC_SMPR2_SMP5_POS)        

#define ADC_SMPR2_SMP6_POS                  (18U)                              
#define ADC_SMPR2_SMP6_MASK                 (0x001C0000)                       /* 0x001C0000                              */
#define ADC_SMPR2_SMP6                      (ADC_SMPR2_SMP6_MASK)              /* ADC channel 6 sampling time selection   */
#define ADC_SMPR2_SMP6_0                    (0x00040000)                       /* 0x00040000                              */
#define ADC_SMPR2_SMP6_1                    (0x00080000)                       /* 0x00080000                              */
#define ADC_SMPR2_SMP6_2                    (0x00100000)                       /* 0x00100000                              */

#define ADC_SMPR2_SMP6_SEL(a)               ((a) << ADC_SMPR2_SMP6_POS)        

#define ADC_SMPR2_SMP7_POS                  (21U)                              
#define ADC_SMPR2_SMP7_MASK                 (0x00E00000)                       /* 0x00E00000                              */
#define ADC_SMPR2_SMP7                      (ADC_SMPR2_SMP7_MASK)              /* ADC channel 7 sampling time selection   */
#define ADC_SMPR2_SMP7_0                    (0x00200000)                       /* 0x00200000                              */
#define ADC_SMPR2_SMP7_1                    (0x00400000)                       /* 0x00400000                              */
#define ADC_SMPR2_SMP7_2                    (0x00800000)                       /* 0x00800000                              */

#define ADC_SMPR2_SMP7_SEL(a)               ((a) << ADC_SMPR2_SMP7_POS)        

#define ADC_SMPR2_SMP8_POS                  (24U)                              
#define ADC_SMPR2_SMP8_MASK                 (0x07000000)                       /* 0x07000000                              */
#define ADC_SMPR2_SMP8                      (ADC_SMPR2_SMP8_MASK)              /* ADC channel 8 sampling time selection   */
#define ADC_SMPR2_SMP8_0                    (0x01000000)                       /* 0x01000000                              */
#define ADC_SMPR2_SMP8_1                    (0x02000000)                       /* 0x02000000                              */
#define ADC_SMPR2_SMP8_2                    (0x04000000)                       /* 0x04000000                              */

#define ADC_SMPR2_SMP8_SEL(a)               ((a) << ADC_SMPR2_SMP8_POS)        

#define ADC_SMPR2_SMP9_POS                  (27U)                              
#define ADC_SMPR2_SMP9_MASK                 (0x38000000)                       /* 0x38000000                              */
#define ADC_SMPR2_SMP9                      (ADC_SMPR2_SMP9_MASK)              /* ADC channel 9 sampling time selection   */
#define ADC_SMPR2_SMP9_0                    (0x08000000)                       /* 0x08000000                              */
#define ADC_SMPR2_SMP9_1                    (0x10000000)                       /* 0x10000000                              */
#define ADC_SMPR2_SMP9_2                    (0x20000000)                       /* 0x20000000                              */

#define ADC_SMPR2_SMP9_SEL(a)               ((a) << ADC_SMPR2_SMP9_POS)        

/* Bit definition for ADC_JOFR1 register */
#define ADC_JOFR1_JOFFSET1_POS              (0U)                               
#define ADC_JOFR1_JOFFSET1_MASK             (0x00000FFF)                       /* 0x00000FFF                                       */
#define ADC_JOFR1_JOFFSET1                  (ADC_JOFR1_JOFFSET1_MASK)          /* ADC group injected sequencer rank 1 offset value */

/* Bit definition for ADC_JOFR2 register */
#define ADC_JOFR2_JOFFSET2_POS              (0U)                               
#define ADC_JOFR2_JOFFSET2_MASK             (0x00000FFF)                       /* 0x00000FFF                                       */
#define ADC_JOFR2_JOFFSET2                  (ADC_JOFR2_JOFFSET2_MASK)          /* ADC group injected sequencer rank 2 offset value */

/* Bit definition for ADC_JOFR3 register */
#define ADC_JOFR3_JOFFSET3_POS              (0U)                               
#define ADC_JOFR3_JOFFSET3_MASK             (0x00000FFF)                       /* 0x00000FFF                                       */
#define ADC_JOFR3_JOFFSET3                  (ADC_JOFR3_JOFFSET3_MASK)          /* ADC group injected sequencer rank 3 offset value */

/* Bit definition for ADC_JOFR4 register */
#define ADC_JOFR4_JOFFSET4_POS              (0U)                               
#define ADC_JOFR4_JOFFSET4_MASK             (0x00000FFF)                       /* 0x00000FFF                                       */
#define ADC_JOFR4_JOFFSET4                  (ADC_JOFR4_JOFFSET4_MASK)          /* ADC group injected sequencer rank 4 offset value */

/* Bit definition for ADC_HTR register */
#define ADC_HTR_HT_POS                      (0U)                               
#define ADC_HTR_HT_MASK                     (0x00000FFF)                       /* 0x00000FFF                           */
#define ADC_HTR_HT                          (ADC_HTR_HT_MASK)                  /* ADC analog watchdog 1 threshold high */

/* Bit definition for ADC_LTR register */
#define ADC_LTR_LT_POS                      (0U)                               
#define ADC_LTR_LT_MASK                     (0x00000FFF)                       /* 0x00000FFF                          */
#define ADC_LTR_LT                          (ADC_LTR_LT_MASK)                  /* ADC analog watchdog 1 threshold low */

/* Bit definition for ADC_SQR1 register */
#define ADC_SQR1_SQ13_POS                   (0U)                               
#define ADC_SQR1_SQ13_MASK                  (0x0000001F)                       /* 0x0000001F                          */
#define ADC_SQR1_SQ13                       (ADC_SQR1_SQ13_MASK)               /* ADC group regular sequencer rank 13 */
#define ADC_SQR1_SQ13_0                     (0x00000001)                       /* 0x00000001                          */
#define ADC_SQR1_SQ13_1                     (0x00000002)                       /* 0x00000002                          */
#define ADC_SQR1_SQ13_2                     (0x00000004)                       /* 0x00000004                          */
#define ADC_SQR1_SQ13_3                     (0x00000008)                       /* 0x00000008                          */
#define ADC_SQR1_SQ13_4                     (0x00000010)                       /* 0x00000010                          */

#define ADC_SQR1_SQ14_POS                   (5U)                               
#define ADC_SQR1_SQ14_MASK                  (0x000003E0)                       /* 0x000003E0                          */
#define ADC_SQR1_SQ14                       (ADC_SQR1_SQ14_MASK)               /* ADC group regular sequencer rank 14 */
#define ADC_SQR1_SQ14_0                     (0x00000020)                       /* 0x00000020                          */
#define ADC_SQR1_SQ14_1                     (0x00000040)                       /* 0x00000040                          */
#define ADC_SQR1_SQ14_2                     (0x00000080)                       /* 0x00000080                          */
#define ADC_SQR1_SQ14_3                     (0x00000100)                       /* 0x00000100                          */
#define ADC_SQR1_SQ14_4                     (0x00000200)                       /* 0x00000200                          */

#define ADC_SQR1_SQ15_POS                   (10U)                              
#define ADC_SQR1_SQ15_MASK                  (0x00007C00)                       /* 0x00007C00                          */
#define ADC_SQR1_SQ15                       (ADC_SQR1_SQ15_MASK)               /* ADC group regular sequencer rank 15 */
#define ADC_SQR1_SQ15_0                     (0x00000400)                       /* 0x00000400                          */
#define ADC_SQR1_SQ15_1                     (0x00000800)                       /* 0x00000800                          */
#define ADC_SQR1_SQ15_2                     (0x00001000)                       /* 0x00001000                          */
#define ADC_SQR1_SQ15_3                     (0x00002000)                       /* 0x00002000                          */
#define ADC_SQR1_SQ15_4                     (0x00004000)                       /* 0x00004000                          */

#define ADC_SQR1_SQ16_POS                   (15U)                              
#define ADC_SQR1_SQ16_MASK                  (0x000F8000)                       /* 0x000F8000                          */
#define ADC_SQR1_SQ16                       (ADC_SQR1_SQ16_MASK)               /* ADC group regular sequencer rank 16 */
#define ADC_SQR1_SQ16_0                     (0x00008000)                       /* 0x00008000                          */
#define ADC_SQR1_SQ16_1                     (0x00010000)                       /* 0x00010000                          */
#define ADC_SQR1_SQ16_2                     (0x00020000)                       /* 0x00020000                          */
#define ADC_SQR1_SQ16_3                     (0x00040000)                       /* 0x00040000                          */
#define ADC_SQR1_SQ16_4                     (0x00080000)                       /* 0x00080000                          */

#define ADC_SQR1_L_POS                      (20U)                              
#define ADC_SQR1_L_MASK                     (0x00F00000)                       /* 0x00F00000                              */
#define ADC_SQR1_L                          (ADC_SQR1_L_MASK)                  /* ADC group regular sequencer scan length */
#define ADC_SQR1_L_0                        (0x00100000)                       /* 0x00100000                              */
#define ADC_SQR1_L_1                        (0x00200000)                       /* 0x00200000                              */
#define ADC_SQR1_L_2                        (0x00400000)                       /* 0x00400000                              */
#define ADC_SQR1_L_3                        (0x00800000)                       /* 0x00800000                              */

/* Bit definition for ADC_SQR2 register */
#define ADC_SQR2_SQ7_POS                    (0U)                               
#define ADC_SQR2_SQ7_MASK                   (0x0000001F)                       /* 0x0000001F                          */
#define ADC_SQR2_SQ7                        (ADC_SQR2_SQ7_MASK)                /* ADC group regular sequencer rank 7  */
#define ADC_SQR2_SQ7_0                      (0x00000001)                       /* 0x00000001                          */
#define ADC_SQR2_SQ7_1                      (0x00000002)                       /* 0x00000002                          */
#define ADC_SQR2_SQ7_2                      (0x00000004)                       /* 0x00000004                          */
#define ADC_SQR2_SQ7_3                      (0x00000008)                       /* 0x00000008                          */
#define ADC_SQR2_SQ7_4                      (0x00000010)                       /* 0x00000010                          */

#define ADC_SQR2_SQ8_POS                    (5U)                               
#define ADC_SQR2_SQ8_MASK                   (0x000003E0)                       /* 0x000003E0                          */
#define ADC_SQR2_SQ8                        (ADC_SQR2_SQ8_MASK)                /* ADC group regular sequencer rank 8  */
#define ADC_SQR2_SQ8_0                      (0x00000020)                       /* 0x00000020                          */
#define ADC_SQR2_SQ8_1                      (0x00000040)                       /* 0x00000040                          */
#define ADC_SQR2_SQ8_2                      (0x00000080)                       /* 0x00000080                          */
#define ADC_SQR2_SQ8_3                      (0x00000100)                       /* 0x00000100                          */
#define ADC_SQR2_SQ8_4                      (0x00000200)                       /* 0x00000200                          */

#define ADC_SQR2_SQ9_POS                    (10U)                              
#define ADC_SQR2_SQ9_MASK                   (0x00007C00)                       /* 0x00007C00                          */
#define ADC_SQR2_SQ9                        (ADC_SQR2_SQ9_MASK)                /* ADC group regular sequencer rank 9  */
#define ADC_SQR2_SQ9_0                      (0x00000400)                       /* 0x00000400                          */
#define ADC_SQR2_SQ9_1                      (0x00000800)                       /* 0x00000800                          */
#define ADC_SQR2_SQ9_2                      (0x00001000)                       /* 0x00001000                          */
#define ADC_SQR2_SQ9_3                      (0x00002000)                       /* 0x00002000                          */
#define ADC_SQR2_SQ9_4                      (0x00004000)                       /* 0x00004000                          */

#define ADC_SQR2_SQ10_POS                   (15U)                              
#define ADC_SQR2_SQ10_MASK                  (0x000F8000)                       /* 0x000F8000                          */
#define ADC_SQR2_SQ10                       (ADC_SQR2_SQ10_MASK)               /* ADC group regular sequencer rank 10 */
#define ADC_SQR2_SQ10_0                     (0x00008000)                       /* 0x00008000                          */
#define ADC_SQR2_SQ10_1                     (0x00010000)                       /* 0x00010000                          */
#define ADC_SQR2_SQ10_2                     (0x00020000)                       /* 0x00020000                          */
#define ADC_SQR2_SQ10_3                     (0x00040000)                       /* 0x00040000                          */
#define ADC_SQR2_SQ10_4                     (0x00080000)                       /* 0x00080000                          */

#define ADC_SQR2_SQ11_POS                   (20U)                              
#define ADC_SQR2_SQ11_MASK                  (0x01F00000)                       /* 0x01F00000                          */
#define ADC_SQR2_SQ11                       (ADC_SQR2_SQ11_MASK)               /* ADC group regular sequencer rank 11 */
#define ADC_SQR2_SQ11_0                     (0x00100000)                       /* 0x00100000                          */
#define ADC_SQR2_SQ11_1                     (0x00200000)                       /* 0x00200000                          */
#define ADC_SQR2_SQ11_2                     (0x00400000)                       /* 0x00400000                          */
#define ADC_SQR2_SQ11_3                     (0x00800000)                       /* 0x00800000                          */
#define ADC_SQR2_SQ11_4                     (0x01000000)                       /* 0x01000000                          */

#define ADC_SQR2_SQ12_POS                   (25U)                              
#define ADC_SQR2_SQ12_MASK                  (0x3E000000)                       /* 0x3E000000                          */
#define ADC_SQR2_SQ12                       (ADC_SQR2_SQ12_MASK)               /* ADC group regular sequencer rank 12 */
#define ADC_SQR2_SQ12_0                     (0x02000000)                       /* 0x02000000                          */
#define ADC_SQR2_SQ12_1                     (0x04000000)                       /* 0x04000000                          */
#define ADC_SQR2_SQ12_2                     (0x08000000)                       /* 0x08000000                          */
#define ADC_SQR2_SQ12_3                     (0x10000000)                       /* 0x10000000                          */
#define ADC_SQR2_SQ12_4                     (0x20000000)                       /* 0x20000000                          */

/* Bit definition for ADC_SQR3 register */
#define ADC_SQR3_SQ1_POS                    (0U)                               
#define ADC_SQR3_SQ1_MASK                   (0x0000001F)                       /* 0x0000001F                          */
#define ADC_SQR3_SQ1                        (ADC_SQR3_SQ1_MASK)                /* ADC group regular sequencer rank 1  */
#define ADC_SQR3_SQ1_0                      (0x00000001)                       /* 0x00000001                          */
#define ADC_SQR3_SQ1_1                      (0x00000002)                       /* 0x00000002                          */
#define ADC_SQR3_SQ1_2                      (0x00000004)                       /* 0x00000004                          */
#define ADC_SQR3_SQ1_3                      (0x00000008)                       /* 0x00000008                          */
#define ADC_SQR3_SQ1_4                      (0x00000010)                       /* 0x00000010                          */

#define ADC_SQR3_SQ2_POS                    (5U)                               
#define ADC_SQR3_SQ2_MASK                   (0x000003E0)                       /* 0x000003E0                          */
#define ADC_SQR3_SQ2                        (ADC_SQR3_SQ2_MASK)                /* ADC group regular sequencer rank 2  */
#define ADC_SQR3_SQ2_0                      (0x00000020)                       /* 0x00000020                          */
#define ADC_SQR3_SQ2_1                      (0x00000040)                       /* 0x00000040                          */
#define ADC_SQR3_SQ2_2                      (0x00000080)                       /* 0x00000080                          */
#define ADC_SQR3_SQ2_3                      (0x00000100)                       /* 0x00000100                          */
#define ADC_SQR3_SQ2_4                      (0x00000200)                       /* 0x00000200                          */

#define ADC_SQR3_SQ3_POS                    (10U)                              
#define ADC_SQR3_SQ3_MASK                   (0x00007C00)                       /* 0x00007C00                          */
#define ADC_SQR3_SQ3                        (ADC_SQR3_SQ3_MASK)                /* ADC group regular sequencer rank 3  */
#define ADC_SQR3_SQ3_0                      (0x00000400)                       /* 0x00000400                          */
#define ADC_SQR3_SQ3_1                      (0x00000800)                       /* 0x00000800                          */
#define ADC_SQR3_SQ3_2                      (0x00001000)                       /* 0x00001000                          */
#define ADC_SQR3_SQ3_3                      (0x00002000)                       /* 0x00002000                          */
#define ADC_SQR3_SQ3_4                      (0x00004000)                       /* 0x00004000                          */

#define ADC_SQR3_SQ4_POS                    (15U)                              
#define ADC_SQR3_SQ4_MASK                   (0x000F8000)                       /* 0x000F8000                          */
#define ADC_SQR3_SQ4                        (ADC_SQR3_SQ4_MASK)                /* ADC group regular sequencer rank 4  */
#define ADC_SQR3_SQ4_0                      (0x00008000)                       /* 0x00008000                          */
#define ADC_SQR3_SQ4_1                      (0x00010000)                       /* 0x00010000                          */
#define ADC_SQR3_SQ4_2                      (0x00020000)                       /* 0x00020000                          */
#define ADC_SQR3_SQ4_3                      (0x00040000)                       /* 0x00040000                          */
#define ADC_SQR3_SQ4_4                      (0x00080000)                       /* 0x00080000                          */

#define ADC_SQR3_SQ5_POS                    (20U)                              
#define ADC_SQR3_SQ5_MASK                   (0x01F00000)                       /* 0x01F00000                          */
#define ADC_SQR3_SQ5                        (ADC_SQR3_SQ5_MASK)                /* ADC group regular sequencer rank 5  */
#define ADC_SQR3_SQ5_0                      (0x00100000)                       /* 0x00100000                          */
#define ADC_SQR3_SQ5_1                      (0x00200000)                       /* 0x00200000                          */
#define ADC_SQR3_SQ5_2                      (0x00400000)                       /* 0x00400000                          */
#define ADC_SQR3_SQ5_3                      (0x00800000)                       /* 0x00800000                          */
#define ADC_SQR3_SQ5_4                      (0x01000000)                       /* 0x01000000                          */

#define ADC_SQR3_SQ6_POS                    (25U)                              
#define ADC_SQR3_SQ6_MASK                   (0x3E000000)                       /* 0x3E000000                          */
#define ADC_SQR3_SQ6                        (ADC_SQR3_SQ6_MASK)                /* ADC group regular sequencer rank 6  */
#define ADC_SQR3_SQ6_0                      (0x02000000)                       /* 0x02000000                          */
#define ADC_SQR3_SQ6_1                      (0x04000000)                       /* 0x04000000                          */
#define ADC_SQR3_SQ6_2                      (0x08000000)                       /* 0x08000000                          */
#define ADC_SQR3_SQ6_3                      (0x10000000)                       /* 0x10000000                          */
#define ADC_SQR3_SQ6_4                      (0x20000000)                       /* 0x20000000                          */

/* Bit definition for ADC_JSQR register */
#define ADC_JSQR_JSQ1_POS                   (0U)                               
#define ADC_JSQR_JSQ1_MASK                  (0x0000001F)                       /* 0x0000001F                          */
#define ADC_JSQR_JSQ1                       (ADC_JSQR_JSQ1_MASK)               /* ADC group injected sequencer rank 1 */
#define ADC_JSQR_JSQ1_0                     (0x00000001)                       /* 0x00000001                          */
#define ADC_JSQR_JSQ1_1                     (0x00000002)                       /* 0x00000002                          */
#define ADC_JSQR_JSQ1_2                     (0x00000004)                       /* 0x00000004                          */
#define ADC_JSQR_JSQ1_3                     (0x00000008)                       /* 0x00000008                          */
#define ADC_JSQR_JSQ1_4                     (0x00000010)                       /* 0x00000010                          */

#define ADC_JSQR_JSQ2_POS                   (5U)                               
#define ADC_JSQR_JSQ2_MASK                  (0x000003E0)                       /* 0x000003E0                          */
#define ADC_JSQR_JSQ2                       (ADC_JSQR_JSQ2_MASK)               /* ADC group injected sequencer rank 2 */
#define ADC_JSQR_JSQ2_0                     (0x00000020)                       /* 0x00000020                          */
#define ADC_JSQR_JSQ2_1                     (0x00000040)                       /* 0x00000040                          */
#define ADC_JSQR_JSQ2_2                     (0x00000080)                       /* 0x00000080                          */
#define ADC_JSQR_JSQ2_3                     (0x00000100)                       /* 0x00000100                          */
#define ADC_JSQR_JSQ2_4                     (0x00000200)                       /* 0x00000200                          */

#define ADC_JSQR_JSQ3_POS                   (10U)                              
#define ADC_JSQR_JSQ3_MASK                  (0x00007C00)                       /* 0x00007C00                          */
#define ADC_JSQR_JSQ3                       (ADC_JSQR_JSQ3_MASK)               /* ADC group injected sequencer rank 3 */
#define ADC_JSQR_JSQ3_0                     (0x00000400)                       /* 0x00000400                          */
#define ADC_JSQR_JSQ3_1                     (0x00000800)                       /* 0x00000800                          */
#define ADC_JSQR_JSQ3_2                     (0x00001000)                       /* 0x00001000                          */
#define ADC_JSQR_JSQ3_3                     (0x00002000)                       /* 0x00002000                          */
#define ADC_JSQR_JSQ3_4                     (0x00004000)                       /* 0x00004000                          */

#define ADC_JSQR_JSQ4_POS                   (15U)                              
#define ADC_JSQR_JSQ4_MASK                  (0x000F8000)                       /* 0x000F8000                          */
#define ADC_JSQR_JSQ4                       (ADC_JSQR_JSQ4_MASK)               /* ADC group injected sequencer rank 4 */
#define ADC_JSQR_JSQ4_0                     (0x00008000)                       /* 0x00008000                          */
#define ADC_JSQR_JSQ4_1                     (0x00010000)                       /* 0x00010000                          */
#define ADC_JSQR_JSQ4_2                     (0x00020000)                       /* 0x00020000                          */
#define ADC_JSQR_JSQ4_3                     (0x00040000)                       /* 0x00040000                          */
#define ADC_JSQR_JSQ4_4                     (0x00080000)                       /* 0x00080000                          */

#define ADC_JSQR_JL_POS                     (20U)                              
#define ADC_JSQR_JL_MASK                    (0x00300000)                       /* 0x00300000                               */
#define ADC_JSQR_JL                         (ADC_JSQR_JL_MASK)                 /* ADC group injected sequencer scan length */
#define ADC_JSQR_JL_0                       (0x00100000)                       /* 0x00100000                               */
#define ADC_JSQR_JL_1                       (0x00200000)                       /* 0x00200000                               */

/* Bit definition for ADC_JDR1 register */
#define ADC_JDR1_JDATA_POS                  (0U)                               
#define ADC_JDR1_JDATA_MASK                 (0x0000FFFF)                       /* 0x0000FFFF                                          */
#define ADC_JDR1_JDATA                      (ADC_JDR1_JDATA_MASK)              /* ADC group injected sequencer rank 1 conversion data */

/* Bit definition for ADC_JDR2 register */
#define ADC_JDR2_JDATA_POS                  (0U)                               
#define ADC_JDR2_JDATA_MASK                 (0x0000FFFF)                       /* 0x0000FFFF                                          */
#define ADC_JDR2_JDATA                      (ADC_JDR2_JDATA_MASK)              /* ADC group injected sequencer rank 2 conversion data */

/* Bit definition for ADC_JDR3 register */
#define ADC_JDR3_JDATA_POS                  (0U)                               
#define ADC_JDR3_JDATA_MASK                 (0x0000FFFF)                       /* 0x0000FFFF                                          */
#define ADC_JDR3_JDATA                      (ADC_JDR3_JDATA_MASK)              /* ADC group injected sequencer rank 3 conversion data */

/* Bit definition for ADC_JDR4 register */
#define ADC_JDR4_JDATA_POS                  (0U)                               
#define ADC_JDR4_JDATA_MASK                 (0x0000FFFF)                       /* 0x0000FFFF                                          */
#define ADC_JDR4_JDATA                      (ADC_JDR4_JDATA_MASK)              /* ADC group injected sequencer rank 4 conversion data */

/** Bit definition for ADC_DR register */
#define ADC_DR_DATA_POS                     (0U)                               
#define ADC_DR_DATA_MASK                    (0x0000FFFF)                       /* 0x0000FFFF                        */
#define ADC_DR_DATA                         (ADC_DR_DATA_MASK)                 /* ADC group regular conversion data */
#define ADC_DR_ADC2DATA_POS                 (16U)                              
#define ADC_DR_ADC2DATA_MASK                (0xFFFF0000)                       /* 0xFFFF0000                                                    */
#define ADC_DR_ADC2DATA                     (ADC_DR_ADC2DATA_MASK)             /* ADC group regular conversion data for ADC slave, in multimode */




/* Data structure definition */
/****************************************************
*   Structure£º  T_ADC_MEM_MAP
*   Description£ºMemory map of ADC registers.
*   Parameter:   WORD32 SR         Status register   
*                WORD32 CR1        Control register 1                    
*                WORD32 CR2        Control regitset 2                    
*                WORD32 SMPR1      Sample time register 1                
*                WORD32 SMPR2      Sample time register 2                
*                WORD32 JOFR1      Inject channel data offset register 1 
*                WORD32 JOFR2      Inject channel data offset register 2 
*                WORD32 JOFR3      Inject channel data offset register 3 
*                WORD32 JOFR4      Inject channel data offset register 4 
*                WORD32 HTR        Watchdog high threshold register 1    
*                WORD32 LTR        Watchdog low threshold register 2     
*                WORD32 SQR1       Regular sequence register 1           
*                WORD32 SQR2       Regular sequence register 2           
*                WORD32 SQR3       Regular sequence register 3           
*                WORD32 JSQR       Inject sequence register              
*                WORD32 JDR1       Inject data register 1                
*                WORD32 JDR2       Inject data register 2                
*                WORD32 JDR3       Inject data register 3                
*                WORD32 JDR4       Inject data register 4                
*                WORD32 DR         Regular data register   
*   Authour£º    Ian
*   Modify record:
*   Date:  2016-7-31 creat.
****************************************************/
typedef struct _T_ADC_MEM_MAP
{
    WORD32 SR;        /* Status register                       */
    WORD32 CR1;       /* Control register 1                    */
    WORD32 CR2;       /* Control regitset 2                    */
    WORD32 SMPR1;     /* Sample time register 1                */
    WORD32 SMPR2;     /* Sample time register 2                */
    WORD32 JOFR1;     /* Inject channel data offset register 1 */
    WORD32 JOFR2;     /* Inject channel data offset register 2 */
    WORD32 JOFR3;     /* Inject channel data offset register 3 */
    WORD32 JOFR4;     /* Inject channel data offset register 4 */
    WORD32 HTR;       /* Watchdog high threshold register 1    */
    WORD32 LTR;       /* Watchdog low threshold register 2     */
    WORD32 SQR1;      /* Regular sequence register 1           */
    WORD32 SQR2;      /* Regular sequence register 2           */
    WORD32 SQR3;      /* Regular sequence register 3           */
    WORD32 JSQR;      /* Inject sequence register              */
    WORD32 JDR1;      /* Inject data register 1                */
    WORD32 JDR2;      /* Inject data register 2                */
    WORD32 JDR3;      /* Inject data register 3                */
    WORD32 JDR4;      /* Inject data register 4                */
    WORD32 DR;        /* Regular data register                 */
}volatile *T_ADC_MEM_MAP;



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



#ifdef __cplusplus
}
#endif

#endif /* STM32F10XX_H_ */



