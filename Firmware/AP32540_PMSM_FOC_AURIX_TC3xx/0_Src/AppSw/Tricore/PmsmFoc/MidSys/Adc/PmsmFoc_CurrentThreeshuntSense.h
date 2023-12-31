/*
 * \file PmsmFoc_CurrentThreeshuntSense.h
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

#ifndef MIDSYS_PMSM_FOC_CURRENT_THREESHUNT_H_
#define MIDSYS_PMSM_FOC_CURRENT_THREESHUNT_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmMid_internal.h"
/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/
//typedef enum
//{
//    PhaseCurrentSense_LimitsStatus_ok,
//	PhaseCurrentSense_LimitsStatus_min,
//	PhaseCurrentSense_LimitsStatus_max,
//	PhaseCurrentSense_LimitsStatus_outOfRange
//} PhaseCurrentSense_LimitsStatus;
//
//typedef enum
//{
//	PhaseCurrentSense_CalibrationStatus_notDone = 0,
//	PhaseCurrentSense_CalibrationStatus_done
//} PhaseCurrentSense_CalibrationStatus;

//typedef void (*PhaseCurrentSense_LimitsOnOutOfRange)(void *object, PhaseCurrentSense_LimitsStatus status, uint32 info);

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \brief Structure for three phase current measurement configuration and handling
 */
//typedef struct
//{
//    uint32        info;
//    float32       min;
//    float32       max;
//    PhaseCurrentSense_LimitsStatus  status;
//    PhaseCurrentSense_LimitsOnOutOfRange onOutOfRange;
//    void         *object;
//} PhaseCurrentSense_Limits;
//
//typedef struct
//{
//    IfxEvadc_Adc_Channel  adcChannel;
//    uint32                rawvalue;
//    float32               gain;
//    float32               offset;
//    float32               value;
//    PhaseCurrentSense_Limits  limits;
//} PhaseCurrentSense_AdcChannel;

/** @brief Calibration data.
 */
typedef struct
{
    sint32 curVO1;                      /**< \brief Current phase A raw sum */
    sint32 curVO2;                      /**< \brief Current phase B raw sum */
    sint32 curVO3;                      /**< \brief Current phase C raw sum */
    sint32 offset;                      /**< \brief Offset if BridgeDriver has a seperate Offset output like: TLE9180;*/

    sint32 offsetV01;                   /**< \brief Offset if BridgeDriver has a seperate Offset output like: TLE9180;*/
    sint32 offsetV02;                   /**< \brief Offset if BridgeDriver has a seperate Offset output like: TLE9180;*/
    sint32 offsetV03;                   /**< \brief Offset if BridgeDriver has a seperate Offset output like: TLE9180;*/
    sint32 count;                       /**< \brief Calibration index */
    PmsmFoc_SensorAdc_CalibrationStatus status;
    uint8                            calwait;
} PhaseCurrentSense_Calibration;

typedef struct
{
	PmsmFoc_SensorAdc                curVO1;
	PmsmFoc_SensorAdc                curVO2;
	PmsmFoc_SensorAdc                curVO3;
	PmsmFoc_SensorAdc                curVRO;
	PhaseCurrentSense_Calibration    calibration;
} PhaseCurrentSense;


/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
/** /brief
 *
 * /param phaseCurrentSense Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_PhaseCurrentSense_doCalibration(PhaseCurrentSense* const phaseCurrentSense);
/** /brief
 *
 * /param phaseCurrentSense Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_PhaseCurrentSense_resetCalibrationStatus(PhaseCurrentSense* const phaseCurrentSense);
/** /brief
 *
 * /param phaseCurrentSense Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
PmsmFoc_SensorAdc_CalibrationStatus PmsmFoc_PhaseCurrentSense_getCalibrationStatus(PhaseCurrentSense* const phaseCurrentSense);
/** /brief
 *
 * /param phaseCurrentSense Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_PhaseCurrentSense_getRawPhaseCurrentValues(PhaseCurrentSense* const phaseCurrentSense);
/** /brief
 *
 * /param phaseCurrentSense Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN float32 PmsmFoc_PhaseCurrentSense_updateAnalogInput(PmsmFoc_SensorAdc* const phaseCurrentCh);
/** /brief
 *
 * /param phaseCurrentSense Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN float32 PmsmFoc_PhaseCurrentSense_updateAnalogInputDRC(PmsmFoc_SensorAdc* const phaseCurrentCh);

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/




#endif /* MIDSYS_PMSM_FOC_CURRENT_THREESHUNT_H_ */
