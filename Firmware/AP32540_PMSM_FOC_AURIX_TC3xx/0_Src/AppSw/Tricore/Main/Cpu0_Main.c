/**
 * \file Cpu0_Main.c
 * \brief Main function definition for Cpu core 0 .
 *
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Use of this file is subject to the terms of use agreed between (i) you or 
 * the company in which ordinary course of business you are acting and (ii) 
 * Infineon Technologies AG or its licensees. If and as long as no such 
 * terms of use are agreed, use of this file is subject to following:


 * Boost Software License - Version 1.0 - August 17th, 2003

 * Permission is hereby granted, free of charge, to any person or 
 * organization obtaining a copy of the software and accompanying 
 * documentation covered by this license (the "Software") to use, reproduce,
 * display, distribute, execute, and transmit the Software, and to prepare
 * derivative works of the Software, and to permit third-parties to whom the 
 * Software is furnished to do so, all subject to the following:

 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE 
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.

 *
 */
/******************************************************************************/
 /*\title PMSM FOC using AURIX TC3xx
 * \abstract Field Oriented Control (FOC) algorithm used for PMSM control.
 * \description Configurable PMSM FOC.
 * \name AP32540_PMSM_FOC_AURIX_TC3xx
 * \version V1.0.2
 * \board APPLICATION KIT TC3X7 V2.0
 * \keywords PMSM, FOC, AURIX, Motor Control
 * \documents https://www.infineon.com
 * \documents https://www.infineon.com
 * \lastUpdated 2020-10-09
******************************************************************************/

#include "PmsmFoc_UserConfig.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "PmsmFoc_Interface.h"
#include "Mcu_Init.h"
#if(ONE_EYEMODE == ENABLED)
	#include "OneEye_Init.h"
#endif /* End of ONE_EYEMODE*/
#if(TFT_DISPLAYMODE == ENABLED)
	#include "Display_Functions.h"
#endif /* End of TFT_DISPLAYMODE */



/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
MotorControl g_motorControl;		/* Motor control structure  			  */


IFX_ALIGN(4)
IfxCpu_syncEvent cpuSyncEvent= 0;

void core0_main (void)
{
    IfxCpu_enableInterrupts();
    /*
     * !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdog in the demo if it is required and also service the watchdog periodically
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());
    IfxScuWdt_disableSafetyWatchdog (IfxScuWdt_getSafetyWatchdogPassword ());

    /* Cpu sync event wait*/
    IfxCpu_emitEvent(&cpuSyncEvent);
    IfxCpu_waitEvent(&cpuSyncEvent, 1);

	/* Test Pins */
	IfxPort_setPinModeOutput(&MODULE_P13, 0, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);	/* Set Pin13_0 as GP-Out */
	IfxPort_setPinModeOutput(&MODULE_P13, 1, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);	/* Set Pin13_1 as GP-Out */
	IfxPort_setPinModeOutput(&MODULE_P13, 2, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);	/* Set Pin13_2 as GP-Out */
	IfxPort_setPinModeOutput(&MODULE_P13, 3, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);	/* Set Pin13_3 as GP-Out */

	/* Initialize motor control */
	PmsmFoc_initMotorControl(&g_motorControl);
#if(TFT_DISPLAYMODE == ENABLED)
	/* Initialize display */
	Dispaly_initDisplay();
#endif /* End of TFT_DISPLAYMODE */
	/* OneEye: Initialize oscilloscope and serial interface */
#if(ONE_EYEMODE == ENABLED)
	OneEye_init();
#endif /* End of ONE_EYEMODE*/

	/* Initialize operating system tasks */
	extern void OS_Tasks_init(void);
	OS_Tasks_init();

    while (1)
    {
    }
}

