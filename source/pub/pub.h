/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：pub.h
* FileIdentifier：None
* Abstract ：本文件为嵌入式系统软件公共定义。
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


#ifndef _PUB_H_
#define _PUB_H_

#ifdef __cplusplus
extern "C" {
#endif




/************************* 产品代码定义 **********************************/
#define TS_PRODUCT_LINE_ENERGY           (0x01)  /* 能源管理 */
#define TS_PRODUCT_LINE_SMT_CTRL         (0x02)  /* 智能控制 */
    
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

/****************************** 应用类型定义 *************************************************/
#define SW_APP_KNX             (0x01)        /* KNX应用    */
#define SW_APP_KNX_IP          (0x02)        /* KNX IP     */
#define SW_APP_MODBUS          (0x03)        /* MODBUS应用 */
#define SW_APP_DLT645          (0x04)        /* Dlt645应用 */
#define SW_APP_SAVE_MEDIA      (0x05)        /* 存储应用   */


/****************************** 软件框架层定义 ***********************************************/
#define SW_INTERFACE_LAYER_NUM (0x06)        /* 接口层总数，后续增加新接口层，需要更改次定义。*/
#define SW_NA_INTERFACE        (0x00)        /* None用层     */
#define SW_SAVE_INTERFACE      (0x01)        /* 存储层     */
#define SW_COMM_INTERFACE      (0x02)        /* 通讯层     */
#define SW_MATH_INTERFACE      (0x03)        /* 运算层     */
#define SW_CONTROL_INTERFACE   (0x04)        /* 控制层     */
#define SW_DISPLAY_INTERFACE   (0x05)        /* 显示层     */
#define SW_COMMON_DRIVER_LAYER (0x06)        /* 公共驱动层 */

/****************************** 接口层服务操作模式 ********************************************/
#define SW_SVR_READ            (0x01)        /* 数据读取   */
#define SW_SVR_WRITE           (0x02)        /* 数据写入   */

/************************* 通用错误码定义 *******************************/

#define SW_ERRCODE_BASE           ( 0x00000000 )                                    /* 错误码基码       */
#define SW_APP_ERRCODE_BASE       ( SW_ERRCODE_BASE + (0x01<<24) )                    /* 应用层错误码基码 */
#define SW_INTERFACE_ERRCODE_BASE ( SW_ERRCODE_BASE + (0x02<<24) )                    /* 接口层错误码基码 */
#define SW_DRIVER_ERRCODE_BASE    ( SW_ERRCODE_BASE + (0x03<<24) )                    /* 驱动层错误码基码 */

/************************* 应用层错误码定义 ****************************/
                          /* 应用层电能处理错误码 */
#define SW_APP_ENERGY_ERRCODE_BASE      ( SW_APP_ERRCODE_BASE + (1<<16) )            /* 应用层电能量处理错误基码 */
        #define SW_APP_ENERGY_DATA_ERR  ( SW_APP_ENERGY_ERRCODE_BASE + 1 )          /* 电能数据出错             */
        
                          /* 应用层通讯处理错误码 */
#define SW_APP_COMM_ERRCODE_BASE        ( SW_APP_ERRCODE_BASE + (2<<16) )            /* 应用层通讯处理错误基码   */
        #define SW_APP_COMM_CHECK_ERR   ( SW_APP_COMM_ERRCODE_BASE + 1 )            /* 通讯数据检查失败         */

/******* 后续错误码定义，在上述定义中按序添加 **************************/

/************************** 通用返回码定义 ********************************/
#define SW_OK               ((WORD32)0x00000000)  /* 操作成功 */
#define SW_ERR              ((WORD32)0xffffffff)  /* 操作失败 */
#define SW_INVALID_PARA     ((WORD32)0xfffffffe)  /* 非法参数 */
#define SW_NOT_SUPPORT      ((WORD32)0xfffffffd)  /* 非法操作 */

/******************************* 通用数据结构定义 ***************************/








#ifdef __cplusplus
}
#endif

#endif /* _COMMON_H_ */

/* End-of-file */


