/*
 * \file Evadc_InitCurSenseLsSingleShunt.h
 * \brief
 * \ingroup
 * \version 
 * \copyright Copyright (c) 2020 Infineon Technologies AG. All rights reserved.
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


#ifndef EVADC_INITCURSENSELSSINGLESHUNT_H_
#define EVADC_INITCURSENSELSSINGLESHUNT_H_

/******************************************************************************/
/*-----------------------------------Includes---------------------------------*/
/******************************************************************************/
#include "PmsmFoc_UserConfig.h"
#if(PHASE_CURRENT_RECONSTRUCTION == USER_LOWSIDE_SINGLE_SHUNT)
#include MCUCARD_TYPE_PATH
#include INVERTERCARD_TYPE_PATH
#include "Evadc_Init.h"
/******************************************************************************/
/*------------------------------------Macros----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*---------------------------------Enumerations-------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*----------------------------------Data Types--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Exported variables----------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------Global Function Prototypes------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------Inline Function Prototypes------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Inline Function Implementations---------------------*/
/******************************************************************************/

/** /brief
 * This function initialize the ADC channels for the ADC current measurements
 * with below topology
 * Three phase current sense with low-side single shunt resistor.
 * AN0   EVADCG0.CH0   Queue0  VO1 (IDC_LS)
 * AN8   EVADCG1.CH0   Queue0  VRO (OFFSET)
 *
 * /param encoder Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initCurrentSenseChannels(INVERTER_S * const inverter)
{
    IfxEvadc_Adc_ChannelConfig adcChConfig;

    {   // Initialize the channel AN0 (G0.CH0) for Phase Current Sense U (V01)
        adcChConfig.channelId = IfxEvadc_ChannelId_0;
        adcChConfig.resultRegister = IfxEvadc_ChannelResult_0;
        adcChConfig.resultPriority = INTERRUPT_PRIORITY_EVADC_CUR;

        IfxEvadc_Adc_initChannel (
            &inverter->phaseCurrentSense.curVO1.adcChannel, &adcChConfig);

        // Add the channel to Queue0
        IfxEvadc_Adc_addToQueue (&inverter->lowSideCurrentSense.input.adcChannel,
            IfxEvadc_RequestSource_queue0,
			USER_INVERTER_PHASECURSENSE_REFILL_TRIG);
    }

    {   // Initialize the channel AN8 (G1.CH0) for Phase Current Sense VRO
        IfxEvadc_Adc_initChannelConfig (&adcChConfig, &adcEvadc.adcGroup1);
        adcChConfig.channelId = IfxEvadc_ChannelId_0;
        adcChConfig.resultRegister = IfxEvadc_ChannelResult_0;

        IfxEvadc_Adc_initChannel (
            &inverter->phaseCurrentSense.curVRO.adcChannel, &adcChConfig);

        // Add the channel to Queue0
        IfxEvadc_Adc_addToQueue (&inverter->lowSideCurrentSense.refInput.adcChannel,
            IfxEvadc_RequestSource_queue0,
			USER_INVERTER_PHASECURSENSE_REFILL_TRIG);
    }
}

/** /brief
 * This function initialize Queue0 for the ADC current measurements
 *
 * /param adcGroupConfig Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initGroupXQueue0CurrentSenseTriShuntHsMon(IfxEvadc_Adc_GroupConfig *adcGroupConfig)
{
    /*Queue0 is enabled, enable the request slot for the arbiter*/
    adcGroupConfig->arbiter.requestSlotQueue0Enabled= TRUE;

    /* Configure the Queue0 with required values */
    adcGroupConfig->queueRequest[0].requestSlotPrio=
        IfxEvadc_RequestSlotPriority_highest;
    adcGroupConfig->queueRequest[0].requestSlotStartMode=
        IfxEvadc_RequestSlotStartMode_cancelInjectRepeat;
    adcGroupConfig->queueRequest[0].triggerConfig.gatingMode=
        IfxEvadc_GatingMode_always;             //No gate signal is required
    adcGroupConfig->queueRequest[0].triggerConfig.triggerMode=
        IfxEvadc_TriggerMode_uponFallingEdge;
    adcGroupConfig->queueRequest[0].triggerConfig.triggerSource=
        IfxEvadc_TriggerSource_9;               //GTM ADC trigger 1
}

/** /brief
 * This function initialize the ADC Group0 Queue0 for the ADC current measurements
 * with below topology
 * Three phase current sense with (per phase) low-side shunt resistors.
 * G0.Queue0    Priority-Highest    Triggered by TOM1-CH7 (GTM ADC trigger 1)
 *
 * /param adcGroupConfig Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initGroup0Queue0(IfxEvadc_Adc_GroupConfig *adcGroupConfig)
{
	PmsmFoc_Evadc_initGroupXQueue0CurrentSenseTriShuntHsMon(adcGroupConfig);
}

/** /brief
 * This function initialize the ADC Group1 Queue0 for the ADC current measurements
 * with below topology
 * Three phase current sense with (per phase) low-side shunt resistors.
 * G1.Queue0    Priority-Highest    Triggered by TOM1-CH7 (GTM ADC trigger 1)
 *
 * /param encoder Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initGroup1Queue0(IfxEvadc_Adc_GroupConfig *adcGroupConfig)
{
	PmsmFoc_Evadc_initGroupXQueue0CurrentSenseTriShuntHsMon(adcGroupConfig);
}
#endif /* End of (PHASE_CURRENT_RECONSTRUCTION == USER_LOWSIDE_SINGLE_SHUNT) */

#endif /* EVADC_INITCURSENSELSSINGLESHUNT_H_ */