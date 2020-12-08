/*
 * \file PmsmFoc_SensorAdc.h
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

#ifndef PMSMFOC_SENSORADC_H_
#define PMSMFOC_SENSORADC_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "IfxEvadc_Adc.h"
/******************************************************************************/
/*--------------------------------Macros--------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

typedef enum
{
    PmsmFoc_SensorAdc_LimitsStatus_ok,
    PmsmFoc_SensorAdc_LimitsStatus_min,
    PmsmFoc_SensorAdc_LimitsStatus_max,
    PmsmFoc_SensorAdc_LimitsStatus_outOfRange
} PmsmFoc_SensorAdc_LimitsStatus;

typedef enum
{
    PmsmFoc_SensorAdc_CalibrationStatus_notDone = 0,
    PmsmFoc_SensorAdc_CalibrationStatus_done
} PmsmFoc_SensorAdc_CalibrationStatus;

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
typedef void (*PmsmFoc_SensorAdc_LimitsOnOutOfRange)
                 (void *object,
                  PmsmFoc_SensorAdc_LimitsStatus status,
                  uint32 info);

/** \brief Structure for three phase current measurement configuration and handling
 */
typedef struct
{
    uint32                                  info;
    float32                                 min;
    float32                                 max;
    PmsmFoc_SensorAdc_LimitsStatus          status;
    PmsmFoc_SensorAdc_LimitsOnOutOfRange    onOutOfRange;
    void                                    *object;
} PmsmFoc_SensorAdc_Limits;

typedef struct
{
    IfxEvadc_Adc_Channel        adcChannel;
    uint32                      rawvalue;
    float32                     gain;
    float32                     offset;
    float32                     value;
    PmsmFoc_SensorAdc_Limits    limits;
} PmsmFoc_SensorAdc;


typedef struct
{
    float32    gain;
    float32    offset;
    float32    maxLimit;
    float32    minLimit;
} PmsmFoc_SensorAdc_Config;
/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
/** /brief
 *
 * /param curSense Reference to structure that contains instance data members
 * /param cfg Reference to structure that contains instance data members
 *
 * /return
 * /note
 * /see
 * /ingroup
 */
void PmsmFoc_SensorAdc_init(PmsmFoc_SensorAdc *curSense, PmsmFoc_SensorAdc_Config *cfg);
/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/
#endif /* PMSMFOC_SENSORADC_H_ */
