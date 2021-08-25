/*
 * \file PmsmFoc_Interface.h
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


#ifndef PMSM_FOC_INTERFACE_H_
#define PMSM_FOC_INTERFACE_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmFoc.h"
/******************************************************************************/
/*--------------------------------Macros--------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_vfOpenLoopRampup(MOTORCTRL_S* const motorCtrl);
/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_startMotor(MOTORCTRL_S* const motorCtrl);
/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_calMotor(MOTORCTRL_S* const motorCtrl);

/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_stopMotor(MOTORCTRL_S* const motorCtrl);

/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_setDemo(MOTORCTRL_S* const motorCtrl);

/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_setOpenlooptest(MOTORCTRL_S* const motorCtrl);

/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_brakeMotor(MOTORCTRL_S* const motorCtrl);
/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_disableInverter(MOTORCTRL_S* const motorCtrl);
/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_enableInverter(MOTORCTRL_S* const motorCtrl);
/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN void PmsmFoc_Interface_geVdcLink(MOTORCTRL_S* const motorCtrl);

/** /brief
 *
 * /param motorCtrl Reference to structure that contains instance data members
 * /param motorTargetSpeed Target speed
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN boolean PmsmFoc_Interface_setMotorTargetSpeed(MOTORCTRL_S* motorCtrl, float32 motorTargetSpeed);
IFX_EXTERN boolean PmsmFoc_Interface_plsMotorTargetSpeed(MOTORCTRL_S* motorCtrl);
IFX_EXTERN boolean PmsmFoc_Interface_mnsMotorTargetSpeed(MOTORCTRL_S* motorCtrl);
IFX_EXTERN boolean PmsmFoc_Interface_setStartTargetSpeed(MOTORCTRL_S* motorCtrl);
IFX_EXTERN boolean PmsmFoc_Interface_setStopMotorTargetSpeed(MOTORCTRL_S* motorCtrl);
/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

#endif /* PMSM_FOC_INTERFACE_H_ */
