/*
 * \file Evadc_Init.h
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

#ifndef EVADC_INIT_H_
#define EVADC_INIT_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmFoc_UserConfig.h"
#include "IfxEVadc_Adc.h"
#include "PmsmFoc_Inverter.h"
/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------------Data Structures------------------------------*/
/******************************************************************************/
typedef struct
{
    IfxEvadc_Adc evadc; /* EVADC handle*/
    IfxEvadc_Adc_Group adcGroup0;
    IfxEvadc_Adc_Group adcGroup1;
    IfxEvadc_Adc_Group adcGroup2;
    IfxEvadc_Adc_Group adcGroup3;
    IfxEvadc_Adc_Group adcGroup4;
    IfxEvadc_Adc_Group adcGroup5;
    IfxEvadc_Adc_Group adcGroup6;
    IfxEvadc_Adc_Group adcGroup7;
    IfxEvadc_Adc_Group adcGroup8;
    IfxEvadc_Adc_Group adcGroup9;
    IfxEvadc_Adc_Group adcGroup10;
    IfxEvadc_Adc_Group adcGroup11;
} Adc_Evadc;

extern Adc_Evadc adcEvadc;

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
/** /brief
 *
 * /param inverter Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Evadc_initEvadc(INVERTER_S * const inverter);

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*----------------------Inline Function Implementations-----------------------*/
/******************************************************************************/

#endif /* EVADC_INIT_H_ */
