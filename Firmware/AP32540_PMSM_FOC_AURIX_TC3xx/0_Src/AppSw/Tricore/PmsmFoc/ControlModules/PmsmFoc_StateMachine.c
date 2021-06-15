/*
 * \file PmsmFoc_StateMachine.c
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
#include "PmsmFoc_StateMachine.h"
#if(TLE9180_DRIVER == ENABLED)
#include "TLE9180.h"
#endif /* End of TLE9180_DRIVER */
#include "Cpu/Std/IfxCpu.h"
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Private Variables/Constants------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------Function Implementations--------------------------*/
/******************************************************************************/

void PmsmFoc_StateMacine_doControlLoop(MotorControl* const motorCtrl)
{
	switch (motorCtrl->controlParameters.state)
	{
	case StateMachine_calibration:
		/* From reset: 	PmsmFoc_initControlVariables */
		/* From TFT:	Menue_CalibrateSel */
		/* From OneEye:	Ifx_Shell_matchToken(&args, "cal") */	
#if(POSITION_SENSOR_TYPE == ENCODER)
		if((motorCtrl->inverter.phaseCurrentSense.calibration.status == PmsmFoc_SensorAdc_CalibrationStatus_notDone) &
				(motorCtrl->positionSensor.encoder.calibrationStatus == Encoder_CalibrationStatus_notDone))
		{
		#if(TLE9180_DRIVER == ENABLED)
			IfxTLE9180_activateEnable(&Tle9180Ctrl.driver);
		#endif /* End of TLE9180_DRIVER */
		}
		if(motorCtrl->inverter.phaseCurrentSense.calibration.status == PmsmFoc_SensorAdc_CalibrationStatus_notDone)
		{
			PmsmFoc_PhaseCurrentSense_getRawPhaseCurrentValues(&motorCtrl->inverter.phaseCurrentSense);
			PmsmFoc_PhaseCurrentSense_doCalibration(&motorCtrl->inverter.phaseCurrentSense);
		}
		if(motorCtrl->inverter.phaseCurrentSense.calibration.status == PmsmFoc_SensorAdc_CalibrationStatus_done)
		{
			PmsmFoc_doEncoderCalibration(motorCtrl);
		}
		if((motorCtrl->inverter.phaseCurrentSense.calibration.status == PmsmFoc_SensorAdc_CalibrationStatus_done) &
				(motorCtrl->positionSensor.encoder.calibrationStatus == Encoder_CalibrationStatus_done))
		{
		#if(TLE9180_DRIVER == ENABLED)
			IfxTLE9180_deactivateEnable(&Tle9180Ctrl.driver);
		#endif /* End of TLE9180_DRIVER */
			motorCtrl->controlParameters.state = StateMachine_motorStop;
		}
#else /* Middle of POSITION_SENSOR_TYPE */
		if(motorCtrl->inverter.phaseCurrentSense.calibration.status == PmsmFoc_SensorAdc_CalibrationStatus_notDone)
		{
		#if(TLE9180_DRIVER == ENABLED)
			IfxTLE9180_activateEnable(&Tle9180Ctrl.driver);
		#endif /* End of TLE9180_DRIVER */
		}
		if(motorCtrl->inverter.phaseCurrentSense.calibration.status == PmsmFoc_SensorAdc_CalibrationStatus_notDone)
		{
			PmsmFoc_PhaseCurSense_getRawPhaseCurrentValues(&motorCtrl->inverter.phaseCurrentSense);
			PmsmFoc_PhaseCurrentSense_doCalibration(&motorCtrl->inverter.phaseCurrentSense);
		}
		if(motorCtrl->inverter.phaseCurrentSense.calibration.status == PmsmFoc_SensorAdc_CalibrationStatus_done)
		{
		#if(TLE9180_DRIVER == ENABLED)
			IfxTLE9180_deactivateEnable(&Tle9180Ctrl.driver);
		#endif /* End of TLE9180_DRIVER */
			motorCtrl->controlParameters.state = StateMachine_motorStop;
		}
#endif /* End of POSITION_SENSOR_TYPE */
		break;
	case StateMachine_focClosedLoop:
		/* From TFT: 	PmsmFoc_Interface_setDemo */
		/* From TFT:	Menue_StartSel */
		/* From OneEye:	Ifx_Shell_matchToken(&args, "run") */
		/* FOC controller. */
		PmsmFoc_doFieldOrientedControl(motorCtrl);
		/* Update GTM TOM/ATOM duty cycles. */
		PmsmFoc_doPwmSvmUpdate(&motorCtrl->inverter);
		break;

	case StateMachine_tuneCurrentRegulators:
		/* Not used*/
		PmsmFoc_tuneCurrentRegulator(motorCtrl);
		break;
	case StateMachine_prePositioning:
		/* Not used*/
		break;
	case StateMachine_motorStop:
		/* From state machine: 	StateMachine_calibration */
		/* From periodic task: 	PmsmFoc_Interface_doDemo */
		/* Current reconstruction */
        /* STEVE: functionlity overlapped */
        #if 0
		PmsmFoc_reconstructCurrent(motorCtrl);

		/* Clarke Transformation */
		PmsmFoc_doClarkeTransform(&motorCtrl->pmsmFoc);

		/* Update electrical position */
		motorCtrl->pmsmFoc.electricalAngle =
				(sint16) PmsmFoc_PositionAcquisition_updatePosition(&motorCtrl->positionSensor);

		/* Park Transformation */
		PmsmFoc_doParkTransform(&motorCtrl->pmsmFoc);
        #endif
		break;
	case StateMachine_motorIdle:
		/* Not used*/
		/* Current measurement calibration */
		break;
	case StateMachine_vfOpenLoop:
		/* Not used*/
		PmsmFoc_doVfControl(motorCtrl);
		break;
	case StateMachine_enableInverter:
		/* Not used*/
		break;
	default:
		break;
	}
}








