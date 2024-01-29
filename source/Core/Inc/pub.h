/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName��pub.h
* FileIdentifier��None
* Abstract �����ļ�ΪǶ��ʽϵͳ����������塣
* Other Description��
* Current Version��V1.00
* Author��      
* Completed Date��2013��7��24��
*    
* Modified History1��
*        Modified Date��2013��7��24��
*        Version Number��V1.00
*        Modified Person��      
*        Modified part��Add new public definition.
******************************************************************************/


#ifndef _PUB_H_
#define _PUB_H_

#ifdef __cplusplus
extern "C" {
#endif




/************************* ��Ʒ���붨�� **********************************/
#define TS_PRODUCT_LINE_ENERGY           (0x01)  /* ��Դ���� */
#define TS_PRODUCT_LINE_SMT_CTRL         (0x02)  /* ���ܿ��� */
    
#define TS_ENERGY_NTS_130                (TS_PRODUCT_LINE_ENERGY + 1)        /* NTS-130      */
#define TS_ENERGY_NTS_230                (TS_PRODUCT_LINE_ENERGY + 2)        /* NTS-230      */
#define TS_ENERGY_NTS_210                (TS_PRODUCT_LINE_ENERGY + 3)        /* NTS-210      */
#define TS_ENERGY_NTS_220GS              (TS_PRODUCT_LINE_ENERGY + 4)        /* NTS-220GS0   */
#define TS_ENERGY_NTS_240GS              (TS_PRODUCT_LINE_ENERGY + 5)        /* NTS-240GS    */
#define TS_ENERGY_NTS_240                (TS_PRODUCT_LINE_ENERGY + 6)        /* NTS-240      */
#define TS_ENERGY_NTS_242_OLD            (TS_PRODUCT_LINE_ENERGY + 7)        /* NTS-242-old  */
#define TS_ENERGY_NTS_500                (TS_PRODUCT_LINE_ENERGY + 8)        /* NTS-500      */
#define TS_ENERGY_NTS_600                (TS_PRODUCT_LINE_ENERGY + 9)        /* NTS-600      */
#define TS_ENERGY_NTS_700                (TS_PRODUCT_LINE_ENERGY + 10)       /* NTS-700      */

#define TS_CTRL_TSDM_0102A               (TS_PRODUCT_LINE_SMT_CTRL + 1)      /* TSDM_0102A   */
#define TS_CTRL_TSDM_0316A               (TS_PRODUCT_LINE_SMT_CTRL + 2)      /* TSDM_0316A   */
#define TS_CTRL_TSSD_0816C               (TS_PRODUCT_LINE_SMT_CTRL + 3)      /* TSSD_0816C   */
#define TS_CTRL_TSSD_0416C               (TS_PRODUCT_LINE_SMT_CTRL + 4)      /* TSSD_0416C   */
#define TS_CTRL_TSFC_0102A               (TS_PRODUCT_LINE_SMT_CTRL + 5)      /* TSFC_0102A   */
#define TS_CTRL_TSPS_0102                (TS_PRODUCT_LINE_SMT_CTRL + 6)      /* TSPS_0102    */
#define TS_CTRL_TSBC_01                  (TS_PRODUCT_LINE_SMT_CTRL + 7)      /* TSBC_01      */
#define TS_CTRL_TSBC_02                  (TS_PRODUCT_LINE_SMT_CTRL + 8)      /* TSBC_02      */
#define TS_CTRL_TSLC_A                   (TS_PRODUCT_LINE_SMT_CTRL + 9)      /* TSLC_A       */
#define TS_CTRL_TSCD_0401A               (TS_PRODUCT_LINE_SMT_CTRL + 10)     /* TSCD_0401A   */
#define TS_CTRL_TSPS_0102EO1             (TS_PRODUCT_LINE_SMT_CTRL + 11)     /* TSPS_0102EO1 */
#define TS_CTRL_TSSU_1202                (TS_PRODUCT_LINE_SMT_CTRL + 12)     /* TSSU_1202    */

/****************************** Ӧ�����Ͷ��� *************************************************/
#define SW_APP_KNX             (0x01)        /* KNXӦ��    */
#define SW_APP_KNX_IP          (0x02)        /* KNX IP     */
#define SW_APP_MODBUS          (0x03)        /* MODBUSӦ�� */
#define SW_APP_DLT645          (0x04)        /* Dlt645Ӧ�� */
#define SW_APP_SAVE_MEDIA      (0x05)        /* �洢Ӧ��   */


/****************************** �����ܲ㶨�� ***********************************************/
#define SW_INTERFACE_LAYER_NUM (0x06)        /* �ӿڲ����������������½ӿڲ㣬��Ҫ���Ĵζ��塣*/
#define SW_NA_INTERFACE        (0x00)        /* None�ò�     */
#define SW_SAVE_INTERFACE      (0x01)        /* �洢��     */
#define SW_COMM_INTERFACE      (0x02)        /* ͨѶ��     */
#define SW_MATH_INTERFACE      (0x03)        /* �����     */
#define SW_CONTROL_INTERFACE   (0x04)        /* ���Ʋ�     */
#define SW_DISPLAY_INTERFACE   (0x05)        /* ��ʾ��     */
#define SW_COMMON_DRIVER_LAYER (0x06)        /* ���������� */

/****************************** �ӿڲ�������ģʽ ********************************************/
#define SW_SVR_READ            (0x01)        /* ���ݶ�ȡ   */
#define SW_SVR_WRITE           (0x02)        /* ����д��   */

/************************* ͨ�ô����붨�� *******************************/

#define SW_ERRCODE_BASE           ( 0x00000000 )                                    /* ���������       */
#define SW_APP_ERRCODE_BASE       ( SW_ERRCODE_BASE + (0x01<<24) )                    /* Ӧ�ò��������� */
#define SW_INTERFACE_ERRCODE_BASE ( SW_ERRCODE_BASE + (0x02<<24) )                    /* �ӿڲ��������� */
#define SW_DRIVER_ERRCODE_BASE    ( SW_ERRCODE_BASE + (0x03<<24) )                    /* �������������� */

/************************* Ӧ�ò�����붨�� ****************************/
                          /* Ӧ�ò���ܴ�������� */
#define SW_APP_ENERGY_ERRCODE_BASE      ( SW_APP_ERRCODE_BASE + (1<<16) )            /* Ӧ�ò���������������� */
        #define SW_APP_ENERGY_DATA_ERR  ( SW_APP_ENERGY_ERRCODE_BASE + 1 )          /* �������ݳ���             */
        
                          /* Ӧ�ò�ͨѶ��������� */
#define SW_APP_COMM_ERRCODE_BASE        ( SW_APP_ERRCODE_BASE + (2<<16) )            /* Ӧ�ò�ͨѶ����������   */
        #define SW_APP_COMM_CHECK_ERR   ( SW_APP_COMM_ERRCODE_BASE + 1 )            /* ͨѶ���ݼ��ʧ��         */

/******* ���������붨�壬�����������а������ **************************/

/************************** ͨ�÷����붨�� ********************************/
#define SW_OK               ((WORD32)0x00000000)  /* �����ɹ� */
#define SW_ERR              ((WORD32)0xffffffff)  /* ����ʧ�� */
#define SW_INVALID_PARA     ((WORD32)0xfffffffe)  /* �Ƿ����� */
#define SW_NOT_SUPPORT      ((WORD32)0xfffffffd)  /* �Ƿ����� */

/******************************* ͨ�����ݽṹ���� ***************************/








#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H_ */

/* End-of-file */


