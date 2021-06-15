/*
 * \file Evadc_InitVoltageSenseBemf.h
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


#ifndef EVADC_INITVOLTAGESENSEBEMF_H_
#define EVADC_INITVOLTAGESENSEBEMF_H_

/******************************************************************************/
/*-----------------------------------Includes---------------------------------*/
/******************************************************************************/
#include "PmsmFoc_UserConfig.h"
#include INVERTERCARD_TYPE_PATH
#include "Evadc_Init.h"
#include "PmsmFoc_Inverter.h"

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
 * This function initialize the ADC channels for the phase BEMF measurements
 * with below topology
 * Three phase voltage sense.
 * AN19  EVADCG2.CH3   Queue2  VO1 (BEMF_V)
 * AN13  EVADCG1.CH5   Queue2  VO2 (BEMF_U)
 * AN25  EVADCG3.CH1   Queue2  VO3 (BEMF_W)
 *
 * /param inverter Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initBemfVoltageSenseChannels(Inverter * const inverter)
{
    IfxEvadc_Adc_ChannelConfig adcChConfig;

    {   /* Initialize the channel AN19 (G2.CH3) for Phase Voltage Sense BEMF_V */
        IfxEvadc_Adc_initChannelConfig(&adcChConfig, &adcEvadc.adcGroup2);

        adcChConfig.channelId= IfxEvadc_ChannelId_3;
        adcChConfig.resultRegister= IfxEvadc_ChannelResult_3;
        adcChConfig.resultPriority= INTERRUPT_PRIORITY_EVADC_VBEMF;

        IfxEvadc_Adc_initChannel(&inverter->bemfVoltageSense.inputV.adcChannel,
                                 &adcChConfig);

        /* Add the channel to the queue 2 */
        IfxEvadc_Adc_addToQueue(&inverter->bemfVoltageSense.inputV.adcChannel,
                                IfxEvadc_RequestSource_queue2,
								USER_INVERTER_PHASECURSENSE_REFILL_TRIG);
    }

    {   /* Initialize the channel AN13 (G1.CH5) for Phase Voltage Sense BEMF_U */
        IfxEvadc_Adc_initChannelConfig(&adcChConfig, &adcEvadc.adcGroup1);

        adcChConfig.channelId= IfxEvadc_ChannelId_5;
        adcChConfig.resultRegister= IfxEvadc_ChannelResult_5;


        IfxEvadc_Adc_initChannel(&inverter->bemfVoltageSense.inputU.adcChannel,
                                 &adcChConfig);

        /* Add the channel to the queue 2 */
        IfxEvadc_Adc_addToQueue(&inverter->bemfVoltageSense.inputU.adcChannel,
                                IfxEvadc_RequestSource_queue2,
								USER_INVERTER_PHASECURSENSE_REFILL_TRIG);
    }

    {   /* Initialize the channel AN25 (G3.CH1) for Phase Voltage Sense BEMF_W */
        IfxEvadc_Adc_initChannelConfig(&adcChConfig, &adcEvadc.adcGroup3);

        adcChConfig.channelId= IfxEvadc_ChannelId_1;
        adcChConfig.resultRegister= IfxEvadc_ChannelResult_1;

        IfxEvadc_Adc_initChannel(&inverter->bemfVoltageSense.inputW.adcChannel,
                                 &adcChConfig);

        /* Add the channel to the queue 2 */
        IfxEvadc_Adc_addToQueue(&inverter->bemfVoltageSense.inputW.adcChannel,
                                IfxEvadc_RequestSource_queue2,
								USER_INVERTER_PHASECURSENSE_REFILL_TRIG);
    }
}

/** /brief
 *
 * This function initialize Queue2 for the BEMF measurements
 *
 * /param encoder Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initGroupXQueue2VoltageSenseBemf(IfxEvadc_Adc_GroupConfig *adcGroupConfig)
{
    /* Queue2 is enabled, enable the request slot for the arbiter */
    adcGroupConfig->arbiter.requestSlotQueue2Enabled= TRUE;

    /* Configure the Queue0 with required values */
    adcGroupConfig->queueRequest[2].requestSlotPrio=
        IfxEvadc_RequestSlotPriority_low;
    adcGroupConfig->queueRequest[2].requestSlotStartMode=
        IfxEvadc_RequestSlotStartMode_cancelInjectRepeat;
    adcGroupConfig->queueRequest[2].triggerConfig.gatingMode=
        IfxEvadc_GatingMode_always;             /* No gate signal is required */
    adcGroupConfig->queueRequest[2].triggerConfig.triggerMode=
        IfxEvadc_TriggerMode_uponFallingEdge;
    adcGroupConfig->queueRequest[2].triggerConfig.triggerSource=
        IfxEvadc_TriggerSource_9;               /* GTM ADC trigger 1 */
}

/** /brief
 * This function initialize the ADC Group1 Queue2 for the BEMF measurements
 * with below topology
 * Three phase current sense with (per phase) low-side shunt resistors.
 *
 * G1.Queue2    Priority-Low    Triggered by TOM1-CH7 (GTM ADC trigger 1)
 * /param adcGroupConfig Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initGroup1Queue2(IfxEvadc_Adc_GroupConfig *adcGroupConfig)
{
	PmsmFoc_Evadc_initGroupXQueue2VoltageSenseBemf(adcGroupConfig);
}

/** /brief
 * This function initialize the ADC Group2 Queue2 for the BEMF measurements
 * with below topology
 * Three phase current sense with (per phase) low-side shunt resistors.
 * G2.Queue0    Priority-Low    Triggered by TOM1-CH7 (GTM ADC trigger 1)
 * /param encoder Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initGroup2Queue2(IfxEvadc_Adc_GroupConfig *adcGroupConfig)
{
	PmsmFoc_Evadc_initGroupXQueue2VoltageSenseBemf(adcGroupConfig);
}

/** /brief
 * This function initialize the ADC Group3 Queue2 for the BEMF measurements
 * with below topology
 * Three phase current sense with (per phase) low-side shunt resistors.
 * G2.Queue0    Priority-Low    Triggered by TOM1-CH7 (GTM ADC trigger 1)
 *
 * /param encoder Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_INLINE void PmsmFoc_Evadc_initGroup3Queue2(IfxEvadc_Adc_GroupConfig *adcGroupConfig)
{

	PmsmFoc_Evadc_initGroupXQueue2VoltageSenseBemf(adcGroupConfig);
}

#endif /* EVADC_INITVOLTAGESENSEBEMF_H_ */