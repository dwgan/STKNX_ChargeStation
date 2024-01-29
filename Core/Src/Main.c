/******************************************************************************
* VersionOwner (C)2022,STMicroelectronics(ShenZhen)R&D Co.,Ltd.
*
* FileName：Main.c
* FileIdentifier：None
* Abstract ：KNX应用源主函数文件，应用入口。
* Other Description：The code only for prestudy,No forwarding without permission
* Current Version：V1.00
* Author：
* Completed Date：2022年4月12日
*
* Modified History1：
*        Modified Date：2022年4月12日
*        Version Number：V1.00
*        Modified Person：
*        Modified part：Add new public definition.
******************************************************************************/



#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "Hardware.h"

#include "boardctrl.h"
#include "Knx_Run.h"
#include "Rec_Table.h"
#include "App_Api.h"
#include "stm32f10xx_iwdg.h"
#include "system_stm32f10x.h"
#include "HMI_Proc.h"

uint8_t test[10] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55};


/**************************************************************************************************************
* FunctionName:void main(void)
* FunctionDescription: device software start entry.
* InputParameterno.
* OutputParameterno.
* Return Value：no.
* Other Description:
* Modified Date VersionNumber Author ModifiedContent
* -------------------------------------------------------------------------------------------------------------
* 2022年4月12日    1.00              Create
***************************************************************************************************************/
#pragma location = "APP_INTERNAL_SEG"
void main( void )
{
    unsigned int i, j;
    static unsigned int count = 0;

    system_base_clk();

    for( i = 0; i < 10000; i++ )
    {
        for( j = 0 ; j <= 1000; j++ )
        {
            count++;
        }
    }
    /* initializing productor board control . */
    BoardCtrl_Init();

    /* set the device working handler and parameters. */
    BoardCtrl_Set();

    /*Initializing UART peripherial */
    UARTCtrl_init();

    //HMI_Init();

    while( 1 )
    {
        /* renew the cycle time. */
        API_KnxTm_UpdateCycle();
        /* get the programming key state and store it. */
        API_Knx_GetProgKey();
        /* set the programming LED. */
        API_Knx_SetPrgLed();
        /* process messages. */
        if( API_Knx_GetRunStateEx() < RUNSTATE_FLAG_SAVE_SUPPLY )
        {
            /* knx messages handling. */
            API_Knx_MsgProcess();
        }
        /* Run status management. */
        API_Knx_RunProcess();
        /* wdg. */
        Stm32F10xx_Iwdg_Reset();

        test[0] = test[0] + 1;
    }
}


// End of Main.c

