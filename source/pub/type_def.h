/******************************************************************************
* VersionOwner (C)2013,Nanjing Shufan Information Technology Co.,Ltd.
*
* FileName：type_def.h
* FileIdentifier：None
* Abstract ：本文件为数据类型统一定义。自开发代码数据类型都以本头文件定义为准。
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

#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif



/* definitions for tcp/ip */
typedef unsigned int             WORD32;
typedef signed   int             SWORD32;
typedef char                     CHAR;
typedef unsigned char            BYTE;
typedef signed   char            SBYTE;
typedef unsigned short           WORD16;
typedef signed   short           SWORD16;
typedef unsigned long long int   WORD64;
typedef signed   long long int   SWORD64;
typedef signed   long int        SWORDPTR; 
typedef unsigned long int        WORDPTR;    /* 32位系统中,长度为4,64位系统中,长度为8 */
/* define the type of vector. */
typedef void (*vector_entry)(void);

#define VOID                     void
typedef SBYTE                    err_t;

#ifndef NULL
    #define NULL ((void *)0)
#endif
#define FALSE                   0            /* Used for boolean */
#define TRUE                    1            /* Used for boolean */

#ifndef TCPIP_DEF
    typedef BYTE    u8_t;
    typedef WORD16  u16_t;
    typedef WORD32  u32_t;
    typedef SBYTE   s8_t;
    typedef SWORD16 s16_t;
#endif /* TCPIP_DEF */

/* definitions for KNX */
// General type defines
#ifndef _BOOL_
#define _BOOL_
typedef unsigned char                BOOL;        //  1 Bit variable
#endif

#ifndef _UCHAR_
#define _UCHAR_
typedef unsigned char                UCHAR;        //  8 Bit variable
#endif

#ifndef _UINT_
#define _UINT_
typedef unsigned short                UINT;        // 16 Bit variable
#endif

#ifndef _ULONG_
#define _ULONG_
typedef unsigned long                ULONG;        // 32 Bit variable
#endif


#ifndef KNX_UNUSED_ARG
    #define KNX_UNUSED_ARG(x) (void)x
#endif


#ifdef __cplusplus
}
#endif

#endif /* _TYPE_DEF_H_ */




