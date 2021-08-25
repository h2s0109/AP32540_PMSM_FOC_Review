/*
 * \file PmsmFoc_Inverter.h
 * \brief
 * \ingroup
 * \version
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

#ifndef INVERTER_H_
#define INVERTER_H_
/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "PmsmFoc_UserConfig.h"
#include "IfxGtm_Tom_PwmHl.h"

#include "PmsmFoc_CurrentDcLinkSense.h"
#include "PmsmFoc_CurrentThreeshuntSense.h"
#include "PmsmFoc_VoltageSense.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*--------------------------------------------------Enumerations-----------------------------------------------------*/
/*********************************************************************************************************************/
 /** Inverter status  */
typedef enum
{
    Inverter_Status_noFault= 0,    /**< \brief No Fault  */
    Inverter_Status_FaultU= 1,     /**< \brief Fault with phase U */
    Inverter_Status_FaultV= 2,     /**< \brief Fault with phase V */
    Inverter_Status_FaultW= 3      /**< \brief Fault with phase W */
} InverterStatus;


/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/

/** \brief Structure for three phase PWM output configuration and handling
 */
typedef struct
{
    float32          	timerFreq;			/**< \brief Timer frequency */
    IfxGtm_Tom_Timer 	timer;				/**< \brief Timer driver */
    IfxGtm_Tom_Timer 	trigger;			/**< \brief Timer driver */
    IfxGtm_Tom_PwmHl 	pwm;				/**< \brief GTM TOM PWM driver object */
    Ifx_TimerValue      pwmOnTimes[3];		/**< \brief PWM on time for 3 phases */
    Ifx_TimerValue      adcTrigerPoint;		/**< \brief ADC trigger point */
    uint8               sectorSVM;          /**< \brief Space Vector Modulation Sector */
} Pwm3PhaseOutput;


/** @brief Inverter object definition.
 */
typedef struct
{
    Pwm3PhaseOutput         pwm3PhaseOutput;        /**< \brief PWM output object */
    /* #include "PmsmFoc_CurrentThreeshuntSense.h" */
    PhaseCurrentSense       phaseCurrentSense;      /**< \brief Phase current sense object */
    #if(PHASE_CURRENT_RECONSTRUCTION == USER_LOWSIDE_THREE_SHUNT_WITH_HIGHSIDE_MONITORING)
    /* #include "PmsmFoc_CurrentDcLinkSense.h" */
    HighSideCurrentSense    highSideCurrentSense;   /**< \brief High-side DC-Link Current sense object */
    #endif
    #if(PHASE_CURRENT_RECONSTRUCTION == USER_LOWSIDE_SINGLE_SHUNT)
    LowSideCurrentSense     lowSideCurrentSense;    /**< \brief PWM output object */
    #endif
    /* #include "PmsmFoc_VoltageSense.h" */
    #if (DC_LINK_VOLTAGE_MEASUREMENT == ENABLED)
    DcLinkVoltageSense      dcLinkVoltageSense;     /**< \brief PWM output object */
    #endif
    #if (BEMF_MEASUREMENT == ENABLED)
    BemfVoltageSense        bemfVoltageSense;       /**< \brief PWM output object */
    #endif
    InverterStatus          status;                 /**< \brief Current fault status from inverter */
}INVERTER_S ;
/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
 
/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
 
/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/


/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/
/** /brief
 *
 * /param inverter Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE Ifx_TimerValue PmsmFoc_pwm3PhaseOutput_getPeriod(INVERTER_S * const inverter);
/** /brief
 *
 * /param inverter Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE Ifx_TimerValue PmsmFoc_pwm3PhaseOutput_getDeadTime(INVERTER_S * const inverter);


/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/
IFX_INLINE Ifx_TimerValue PmsmFoc_pwm3PhaseOutput_getPeriod(INVERTER_S * const inverter)
{
	return inverter->pwm3PhaseOutput.pwm.timer->base.period;
}

IFX_INLINE Ifx_TimerValue PmsmFoc_pwm3PhaseOutput_getDeadTime(INVERTER_S * const inverter)
{
	return inverter->pwm3PhaseOutput.pwm.base.deadtime;
}

#endif /* INVERTER_H_ */
