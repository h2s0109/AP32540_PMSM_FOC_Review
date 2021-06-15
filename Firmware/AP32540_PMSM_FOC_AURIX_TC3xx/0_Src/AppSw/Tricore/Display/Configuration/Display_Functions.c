/*
 * \file Display_Functions.c
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
 *                            IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or 
 * the company in which ordinary course of business you are acting and (ii) 
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by 
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the 
 * Software, and to permit third-parties to whom the Software is furnished to 
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 * 
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
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "Display_Functions.h"
#include "Display_Cfg_AppKitTft_TC387A.h"
#include "IfxPort.h"
#include "IfxCpu.h"
#include "touch.h"
#include "conio_tft.h"
#include "PmsmFoc.h"
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
extern MotorControl g_motorControl;
/******************************************************************************/
/*-------------------------Private Variables/Constants------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------Function Implementations--------------------------*/
/******************************************************************************/
/** \brief TFT application init
 *
 * This function initialises the TFT display via QSPI0 in master mode.
 */
void Dispaly_initDisplay(void)
{
	/* STEVE:disable? enable? */
	IfxCpu_enableInterrupts();
	/* Initialize TFT Display */
	tft_appl_init();
	/* Initialize the background light */
	IfxPort_setPinModeOutput(&MODULE_P15, 0, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
	IfxPort_setPinHigh(&MODULE_P15, 0);
	IfxCpu_disableInterrupts();
}

void Dispaly_touchpin_ready(void)
{
	// CS to touch
	IfxPort_setPinModeInput(TOUCH_USE_CHIPSELECT.pin.port, TOUCH_USE_CHIPSELECT.pin.pinIndex, IfxPort_InputMode_pullUp);
	// CS to tft
	IfxPort_setPinModeInput(TFT_USE_CHIPSELECT.pin.port, TFT_USE_CHIPSELECT.pin.pinIndex, IfxPort_InputMode_pullUp);
	// INT from touch
	IfxPort_setPinModeInput(TOUCH_USE_INT.port, TOUCH_USE_INT.pinIndex, IfxPort_InputMode_pullUp);
}

void Dispaly_stdout0(void)
{
	conio_periodic(touch_driver.xdisp, touch_driver.ydisp, conio_driver.pmenulist, conio_driver.pstdlist);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 0, (uint8 *)SW_NAME);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 1, (uint8 *)"SW: V1.0.2, HW V3.2");
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 3, (uint8 *)"Speed Ref [rpm] = %.1f %c\n", g_motorControl.pmsmFoc.speedControl.refSpeed);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 4, (uint8 *)"Speed Meas[rpm] = %.1f %c\n", g_motorControl.pmsmFoc.speedControl.measSpeed);

	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 6, (uint8 *)"Iu[A] = %.3f %c\n", g_motorControl.inverter.phaseCurrentSense.curVO1.value);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 7, (uint8 *)"Iv[A] = %.3f %c\n", g_motorControl.inverter.phaseCurrentSense.curVO2.value);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 8, (uint8 *)"Iw[A] = %.3f %c\n", g_motorControl.inverter.phaseCurrentSense.curVO3.value);

	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 10, (uint8 *)"IqRef [A] = %.2f %c\n", g_motorControl.pmsmFoc.idqRef.imag);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 11, (uint8 *)"IqMeas[A] = %.2f %c\n", g_motorControl.pmsmFoc.idqMeas.imag);

	conio_ascii_printfxy (DISPLAYSTDOUT0, 20, 10, (uint8 *)"IdRef[A] = %.2f %c\n", g_motorControl.pmsmFoc.idqRef.real);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 20, 11, (uint8 *)"IdMeas[A] = %.2f %c\n", g_motorControl.pmsmFoc.idqMeas.real);

	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 13, (uint8 *)"VqRef [p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vdqRef.imag);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 14, (uint8 *)"VdRef [p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vdqRef.real);

	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 16, (uint8 *)"ValphaRef[p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vabRef.imag);
	conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 17, (uint8 *)"VbetaRef [p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vabRef.real);
}