/*
 * \file test.c
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
#include "PmsmFoc_PwmSvm.h"
#include "IfxGtm_Tom_PwmHl.h"

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Private Variables/Constants------------------------*/
/******************************************************************************/
static void PmsmFoc_SvmPwmUpdate(Pwm3PhaseOutput* const pwmoutputi);
/******************************************************************************/
/*--------------------------Function Implementations--------------------------*/
/******************************************************************************/
static void PmsmFoc_SvmPwmUpdate(Pwm3PhaseOutput* const pwmoutputi)
{
	/* Set the period and duty value to GTM HW */
	//iLLD GTM functions
#if(GTM_USED == GTM_ATOM_WITH_DTM_USED )
	//ATOM with DTM
#elif(GTM_USED == GTM_ATOM_WITHOUT_DTM_USED)

#elif(GTM_USED == GTM_TOM_WITHOUT_DTM_USED)
	//TOM without DTM, two Channel per phase
	/* set the GLB_CTRL to Disable */
    IfxGtm_Tom_Timer_disableUpdate(&pwmoutputi->timer);
    IfxGtm_Tom_Timer_setTrigger(&pwmoutputi->timer,
    							pwmoutputi->adcTrigerPoint +
								pwmoutputi->pwm.base.deadtime + 5);
	/* Write the value to the SR0, SR1 */
	/* IfxGtm_Tom_PwmHl_setOnTime is assigned to IfxGtm_Tom_PwmHl_updateCenterAligned */
    IfxGtm_Tom_PwmHl_setOnTime(&pwmoutputi->pwm, pwmoutputi->pwmOnTimes);
	/* set the GLB_CTRL to enable */
    IfxGtm_Tom_Timer_applyUpdate(&pwmoutputi->timer);
#endif
}

void PmsmFoc_SvmStart(INVERTER_S * const inverter, CplxStdReal modulationIndex)
{

	Ifx_TimerValue period;
	Pwm3PhaseOutput* pwmoutput;
	uint8 Sector;
	period = inverter->pwm3PhaseOutput.pwm.timer->base.period;
	pwmoutput = &inverter->pwm3PhaseOutput;
#if(EMOTOR_LIB == MC_EMOTOR)
	/* Sector identification */
	Sector = SpaceVectorModulation(modulationIndex,period,inverter->pwm3PhaseOutput.pwmOnTimes);
#endif
	// inverter->pwm3PhaseOutput.adcTrigerPoint= period>>1;
	// inverter->pwm3PhaseOutput.sectorSVM = Sector;
	pwmoutput->adcTrigerPoint= period>>1;
	pwmoutput->sectorSVM = Sector;
	PmsmFoc_SvmPwmUpdate(pwmoutput);
}

void PmsmFoc_SvmStop(INVERTER_S * const inverter)
{
	inverter->pwm3PhaseOutput.pwmOnTimes[0] = 0;
	inverter->pwm3PhaseOutput.pwmOnTimes[1] = 0;
	inverter->pwm3PhaseOutput.pwmOnTimes[2] = 0;
	IfxGtm_Tom_PwmHl_setOnTime(&inverter->pwm3PhaseOutput.pwm,inverter->pwm3PhaseOutput.pwmOnTimes);
	IfxGtm_Tom_Timer_applyUpdate(&inverter->pwm3PhaseOutput.timer);
}