/*
 * \file PmsmFoc_Functions.c
 * \brief Field Oriented Control
 * \ingroup pmsm_foc_controlmodules
 * \version disabled
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

#include "SysSe/Math/IFX_Cf32.h"
#include "PmsmFoc_Functions.h"
#include "HW_Init.h"
#include "PmsmFoc_CurrentDcLinkSense.h"
#include "PmsmFoc_Gatedriver.h"

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Private Variables/Constants------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------Function Implementations--------------------------*/
/******************************************************************************/

void PmsmFoc_initMotorControl(MotorControl* const motorCtrl)
{
	/* Initialize the control variables */
	PmsmFoc_initControlVariables(motorCtrl);

	/* Initialize the peripheral modules */
	PmsmFoc_initHardware(motorCtrl);
#if(POSITION_SENSOR_TYPE == ENCODER)
	/* Reset the encoder calibration status */
	PmsmFoc_resetEncoderCalibrationStatus(motorCtrl);
#else
	/* For other position sensor */
#endif
	/* Reset the current sense calibration status and set initial variable values */
	PmsmFoc_PhaseCurrentSense_resetCalibrationStatus(&motorCtrl->inverter.phaseCurrentSense);

#if(PHASE_CURRENT_RECONSTRUCTION == USER_LOWSIDE_THREE_SHUNT_WITH_HIGHSIDE_MONITORING)
	/* Reset the DC-link current sense calibration status and set initial variable values */
	PmsmFoc_CurrentDCLinkSenseHs_resetCalibrationStatus(&motorCtrl->inverter.highSideCurrentSense);

	/* Set the DC-link current sense gain */
	PmsmFoc_CurrentDCLinkSenseHs_setGain(&motorCtrl->inverter.highSideCurrentSense,
			HighSideCurrentSense_Gain_200VperV);
#endif

#if(DC_LINK_VOLTAGE_MEASUREMENT == ENABLED)
	/* Reset the DC-link voltage sense calibration status and set initial variable values */
	PmsmFoc_DcLinkVoltageSense_resetCalibrationStatus(&motorCtrl->inverter.dcLinkVoltageSense);
#endif

#if(BEMF_MEASUREMENT == ENABLED)
	/* Reset the phase voltage sense calibration status and set initial variable values */
	PmsmFoc_BemfVoltageSense_resetCalibrationStatus(&motorCtrl->inverter.bemfVoltageSense);
#endif
	PmsmFoc_Gatedriver_Enable();
}

/* static */
void PmsmFoc_initControlVariables(MotorControl* const motorCtrl)
{

	LookUp_Init();
	g_motorControl.interface.CurrnetIfMode = CAL_MODE;
	/* Initialization of speed and current reference ramps */
	Ifx_RampF32_init(&motorCtrl->pmsmFoc.speedRamp,
			USER_MOTOR_SPEED_RAMP_SLEW_RATE,
			USER_MOTOR_SPEED_RAMP_PERIOD);
	Ifx_RampF32_init(&motorCtrl->pmsmFoc.iqRefExternalRamp,
			USER_MOTOR_CURRENT_Q_RAMP_SLEW_RATE,
			USER_MOTOR_CURRENT_Q_RAMP_PERIOD);
	Ifx_RampF32_init(&motorCtrl->pmsmFoc.idRefExternalRamp,
			USER_MOTOR_CURRENT_D_RAMP_SLEW_RATE,
			USER_MOTOR_CURRENT_D_RAMP_PERIOD);
	/* Control parameters object initialization */
	motorCtrl->controlParameters.state = StateMachine_PhaseCalibration;
	motorCtrl->controlParameters.alignmentCounter = 0;
	motorCtrl->controlParameters.counter = 0;
	motorCtrl->controlParameters.inverterStatus = 0;
	motorCtrl->controlParameters.nonRealTimeCounter = 0;
	motorCtrl->controlParameters.rampCounter = 0;
	motorCtrl->controlParameters.rotationDir = 0;
#if(FOC_CONTROL_SCHEME == SPEED_CONTROL)
	motorCtrl->controlParameters.controlScheme = ControlScheme_speed;
#elif(FOC_CONTROL_SCHEME == CURRENT_CONTROL)
	motorCtrl->controlParameters.controlScheme = ControlScheme_current;
#endif

	motorCtrl->inverter.status = 0;

	/* Motor parameters object initialization */
	motorCtrl->motor.rs = USER_MOTOR_RESISTANCE_PER_PHASE;
	motorCtrl->motor.ls = USER_MOTOR_INDUCTANCE_PER_PHASE;
	motorCtrl->motor.polePairs = USER_MOTOR_POLE_PAIR;

	/* Open loop object initialization */
	motorCtrl->openLoop.amplitude = 0.0;
	motorCtrl->openLoop.electricalAngleDelta = 0.0;
	motorCtrl->openLoop.electricalAngle = 0.0;
#if(EMOTOR_LIB == MC_EMOTOR)
	motorCtrl->openLoop.modulationIndex = (CplxStdReal) {0.0, 0.0 };
#endif

	/* Position sensor object initialization */
#if(POSITION_SENSOR_TYPE == ENCODER)
	motorCtrl->positionSensor.sensorType = PositionAcquisition_SensorType_Encoder;
	motorCtrl->positionSensor.encoder.encSyncTopZero = TRUE;
	motorCtrl->positionSensor.encoder.calibrationStatus = Encoder_CalibrationStatus_notDone;
#endif
	/* Initialization of speed regulators */
	PmsmFoc_SpeedControl_init(&motorCtrl->pmsmFoc.speedControl);
	PmsmFoc_SpeedControl_setMaxSpeed(&motorCtrl->pmsmFoc.speedControl,
			USER_MOTOR_SPEED_CONTROL_MAX_RPM);
	PmsmFoc_SpeedControl_setMinSpeed(&motorCtrl->pmsmFoc.speedControl,
			USER_MOTOR_SPEED_CONTROL_MIN_RPM);			
	/* Set the PI controller kp and ki parameter (for fixed point calculation). */
	PmsmFoc_SpeedControl_setKpKi(&motorCtrl->pmsmFoc.speedControl,
			USER_MOTOR_SPEED_CONTROL_KP,
			USER_MOTOR_SPEED_CONTROL_KI,
			USER_MOTOR_SPEED_CONTROL_PERIOD);
	/* Set the PI controller limits. */
	PmsmFoc_SpeedControl_setLimit(&motorCtrl->pmsmFoc.speedControl,
			USER_MOTOR_SPEED_CONTROL_MIN,
			USER_MOTOR_SPEED_CONTROL_MAX);

	/* Initialization current regulators */
	Ifx_PicF32_init(&motorCtrl->pmsmFoc.piId);
	Ifx_PicF32_init(&motorCtrl->pmsmFoc.piIq);
	/* Set the PI controller kp and ki parameter (for fixed point calculation). */
	Ifx_PicF32_setKpKi(&motorCtrl->pmsmFoc.piId,
			USER_MOTOR_PI_ID_KP,
			USER_MOTOR_PI_ID_KI,
			USER_MOTOR_PI_ID_CONTROL_PERIOD);
	/* Set the PI controller limits. */
	Ifx_PicF32_setKpKi(&motorCtrl->pmsmFoc.piIq,
			USER_MOTOR_PI_IQ_KP,
			USER_MOTOR_PI_IQ_KP,
			USER_MOTOR_PI_IQ_CONTROL_PERIOD);
	/* Set the PI controller limits. */
	Ifx_PicF32_setLimit(&motorCtrl->pmsmFoc.piId,
			-USER_MOTOR_PI_ID_LIMIT_MAX,
			USER_MOTOR_PI_ID_LIMIT_MAX);
	Ifx_PicF32_setLimit(&motorCtrl->pmsmFoc.piIq,
			-USER_MOTOR_PI_IQ_LIMIT_MAX,
			USER_MOTOR_PI_IQ_LIMIT_MAX);
}

void PmsmFoc_doFieldOrientedControl(MotorControl* const motorCtrl)
{
	/* Current reconstruction */
	PmsmFoc_reconstructCurrent(motorCtrl);

	/* Update electrical position and measSpeed*/
	motorCtrl->pmsmFoc.electricalAngle =
			(sint16) PmsmFoc_PositionAcquisition_updatePosition(&motorCtrl->positionSensor);
	motorCtrl->pmsmFoc.speedControl.measSpeed = IfxStdIf_Pos_radsToRpm(
			PmsmFoc_PositionAcquisition_updateSpeed(&motorCtrl->positionSensor));
	/* Clarke Transformation */
	PmsmFoc_doClarkeTransform(&motorCtrl->pmsmFoc);

	/* Park Transformation */
	PmsmFoc_doParkTransform(&motorCtrl->pmsmFoc);

	/* Set Id and Iq reference */
	PmsmFoc_setIdqRef(motorCtrl);

	/* PI Controller #1 -  Iq PI controller of FOC */
	PmsmFoc_doIqControl(&motorCtrl->pmsmFoc);

	/* PI Controller #2 -  Id PI controller of FOC */
	PmsmFoc_doIdControl(&motorCtrl->pmsmFoc);

#if(VOLTAGE_LIMIT == ENABLED)
	/* Recalculate voltage vector magnitude */
	motorCtrl->pmsmFoc.vdqMag = PmsmFoc_getVdqMagnitude(&motorCtrl->pmsmFoc);

	/* Voltage Limit */
	PmsmFoc_doVdqLimit(&motorCtrl->pmsmFoc);
#endif

	/* Inverse Park Transformation */
	PmsmFoc_doInverseParkTransform(&motorCtrl->pmsmFoc);

#if(DQ_DECOUPLING == ENABLED)
	PmsmFoc_doDqDecoupling(&motorCtrl->pmsmFoc);
#endif

	PmsmFoc_SvmStart(&motorCtrl->inverter, motorCtrl->pmsmFoc.modulationIndex);
}

void PmsmFoc_resetEncoderCalibrationStatus(MotorControl* const motorCtrl)
{
	motorCtrl->positionSensor.encoder.encSyncTopZero = TRUE;
	motorCtrl->positionSensor.encoder.calibrationStatus = Encoder_CalibrationStatus_notDone;
}

void PmsmFoc_doEncoderCalibration(MotorControl* const motorCtrl)
{
#if(EMOTOR_LIB == MC_EMOTOR)
	CplxStdReal cossin;
#endif
	/* Update electrical position*/
	motorCtrl->pmsmFoc.electricalAngle =
			(sint16) PmsmFoc_PositionAcquisition_updatePosition(&motorCtrl->positionSensor);
	/* Current reconstruction */
	PmsmFoc_reconstructCurrent(motorCtrl);
	
	/* Clarke Transformation */
	PmsmFoc_doClarkeTransform(&motorCtrl->pmsmFoc);

	if(motorCtrl->positionSensor.encoder.encSyncTopZero == TRUE)
	{
		motorCtrl->controlParameters.encTopZeroCounter++;

		if(motorCtrl->controlParameters.encTopZeroCounter <= 100U)
		{
			motorCtrl->openLoop.amplitude += USER_MOTOR_ENCODER_CAL_TOP_ZERO_AMPL_DELTA;
			motorCtrl->openLoop.electricalAngleDelta = 0U;
		}

		if(motorCtrl->controlParameters.encTopZeroCounter == 100U)
		{
			motorCtrl->openLoop.amplitude = USER_MOTOR_ENCODER_CAL_TOP_ZERO_AMPL_MAX;
			motorCtrl->openLoop.electricalAngleDelta = USER_MOTOR_ENCODER_CAL_TOP_ZERO_ANGLE_DELTA;
		}
		if(motorCtrl->controlParameters.encTopZeroCounter >= 30000U)
		{
			motorCtrl->positionSensor.encoder.encSyncTopZero = FALSE;
			motorCtrl->openLoop.amplitude = 0.0;
			motorCtrl->openLoop.electricalAngle = 0;
			motorCtrl->openLoop.electricalAngleDelta = 0;

			motorCtrl->controlParameters.encTopZeroCounter = 0;

			motorCtrl->openLoop.modulationIndex.real = 0;
			motorCtrl->openLoop.modulationIndex.imag = 0;
			motorCtrl->positionSensor.encoder.encOffsetCal = TRUE;
			motorCtrl->controlParameters.encOffsetCalCounter = 0;
		}
	}

	if(motorCtrl->positionSensor.encoder.encOffsetCal == TRUE)
	{
		motorCtrl->controlParameters.encOffsetCalCounter++;

		if(motorCtrl->controlParameters.encOffsetCalCounter == 1)
		{
			motorCtrl->openLoop.electricalAngleDelta = 0;
			motorCtrl->openLoop.electricalAngle = 0;
			motorCtrl->openLoop.amplitude = 0.0;
		}
		if(motorCtrl->controlParameters.encOffsetCalCounter > 1000)
		{
			motorCtrl->openLoop.amplitude += USER_MOTOR_ENCODER_CAL_OFFSET_AMPL_DELTA;
			if(motorCtrl->openLoop.amplitude > USER_MOTOR_ENCODER_CAL_OFFSET_AMPL_MAX)
				motorCtrl->openLoop.amplitude = USER_MOTOR_ENCODER_CAL_OFFSET_AMPL_MAX;
		}

		if(motorCtrl->controlParameters.encOffsetCalCounter == USER_MOTOR_ENCODER_CAL_OFFSET_COUNTS)
		{
			motorCtrl->positionSensor.encoder.incrEncoder.offset =
					-motorCtrl->positionSensor.encoder.incrEncoder.rawPosition;
			motorCtrl->openLoop.amplitude = 0.0;
			motorCtrl->positionSensor.encoder.encOffsetCal = FALSE;
			motorCtrl->interface.CurrnetIfMode = STOP_MODE;
			motorCtrl->controlParameters.encOffsetCalCounter = 0;
			motorCtrl->positionSensor.encoder.calibrationStatus = Encoder_CalibrationStatus_done;
		}
	}
#if(EMOTOR_LIB == MC_EMOTOR)
	/* Update electrical angle and calculate modulation index */
	sint16 electricAngle;
	motorCtrl->openLoop.electricalAngle += motorCtrl->openLoop.electricalAngleDelta;
	electricAngle= (motorCtrl->openLoop.electricalAngle >> 16) & (COSSIN_TABLE_SIZE - 1);
	cossin = LookUp_CosinusSinus(electricAngle);
#endif

	motorCtrl->openLoop.modulationIndex.real = cossin.real * motorCtrl->openLoop.amplitude;
	motorCtrl->openLoop.modulationIndex.imag = cossin.imag * motorCtrl->openLoop.amplitude;

	PmsmFoc_SvmStart(&motorCtrl->inverter, motorCtrl->openLoop.modulationIndex);
}

/* static */
void PmsmFoc_reconstructCurrent(MotorControl* const motorCtrl)
{
	/* Read ADC result of the three shunt current */
	PmsmFoc_PhaseCurrentSense_getRawPhaseCurrentValues(&motorCtrl->inverter.phaseCurrentSense);

	motorCtrl->pmsmFoc.iPhaseMeas.u = motorCtrl->inverter.phaseCurrentSense.curVO1.value;
	motorCtrl->pmsmFoc.iPhaseMeas.v = motorCtrl->inverter.phaseCurrentSense.curVO2.value;
	motorCtrl->pmsmFoc.iPhaseMeas.w = - motorCtrl->pmsmFoc.iPhaseMeas.u - motorCtrl->pmsmFoc.iPhaseMeas.v;
	//motorCtrl->pmsmFoc.iPhaseMeas.w = 1.83*(motorCtrl->inverter.phaseCurrentSense.curVO3.value);
#if(PHASE_CURRENT_RECONSTRUCTION == USER_LOWSIDE_THREE_SHUNT_WITH_HIGHSIDE_MONITORING)
	PmsmFoc_CurrentDCLinkSenseHs_getRawCurrentValue(&motorCtrl->inverter.highSideCurrentSense);
#endif
	//motorCtrl->pmsmFoc.iPhaseMeas.w = 1.83*(motorCtrl->inverter.phaseCurrentSense.curVO3.value)+0.08;
}
/* static */
void PmsmFoc_doClarkeTransform(PmsmFoc* const foc)
{
#if(EMOTOR_LIB == MC_EMOTOR)
	foc->iab = Clarke(&foc->iPhaseMeas);
#endif
	/**< @brief real is Alpha value of current space vector variable */
	/**< @brief imag is Beta value of current space vector variable */
}
/* static */
void PmsmFoc_doParkTransform(PmsmFoc* const foc)
{
#if(EMOTOR_LIB == MC_EMOTOR)
	foc->CurrentAngleCosSin = LookUp_CosinusSinus(foc->electricalAngle);
#endif
#if(EMOTOR_LIB == MC_EMOTOR)
	foc->idqMeas = Park(&foc->iab, &foc->CurrentAngleCosSin);
#endif
}
/* static */
void PmsmFoc_setIdqRef(MotorControl* const motorCtrl)
{
	PmsmFoc* foc = &motorCtrl->pmsmFoc;
#if(FOC_CONTROL_SCHEME == SPEED_CONTROL)
	if(motorCtrl->controlParameters.controlScheme == ControlScheme_speed)
	{
		foc->idqRef.imag = foc->speedControl.piSpeed.uk * USER_MOTOR_IQLIMIT;
		foc->idqRef.real = 0.0;
	}
#elif(FOC_CONTROL_SCHEME == CURRENT_CONTROL)
	if (motorCtrl->controlParameters.controlScheme == ControlScheme_current)
	{
		CplxStdReal temp;
		temp = PmsmFoc_getCurrentRefLinearRamp(&motorCtrl->pmsmFoc);
		foc->idqRef.imag = temp.imag;
		foc->idqRef.real = temp.real;
	}
#endif
	else
	{
		foc->idqRef.imag = 0;
		foc->idqRef.real = 0;
	}

	foc->idqRef.imag = __saturate_stdreal(foc->idqRef.imag,-USER_MOTOR_IQLIMIT, USER_MOTOR_IQLIMIT);
	foc->idqRef.real = __saturate_stdreal(foc->idqRef.real,-USER_MOTOR_IDLIMIT, USER_MOTOR_IDLIMIT);

#if(MTPA == ENABLED)
#elif(FIELD_WEAKENING == ENABLED)
#elif(MAX_EFFICIENCY == ENABLED)
#else
#endif
}
/* static */
void PmsmFoc_doIqControl(PmsmFoc* const foc)
{
	foc->idqError.imag = foc->idqRef.imag - foc->idqMeas.imag;
	Ifx_PicF32_step(&foc->piIq, foc->idqError.imag);
	foc->vdqRef.imag = foc->piIq.uk;
}
/* static */
void PmsmFoc_doIdControl(PmsmFoc* const foc)
{
	foc->idqError.real = foc->idqRef.real - foc->idqMeas.real;
	Ifx_PicF32_step(&foc->piId, foc->idqError.real);
	foc->vdqRef.real = foc->piId.uk;
}
/* static */
StdReal PmsmFoc_getVdqMagnitude(PmsmFoc* const foc)
{
	StdReal vdqMag;
	vdqMag = sqrt((foc->vdqRef.imag * foc->vdqRef.imag) + (foc->vdqRef.real *foc->vdqRef.real));
	return vdqMag;
}
/* static */
void PmsmFoc_doVdqLimit(PmsmFoc* const foc)
{
	StdReal modulationIndexReduction;
	modulationIndexReduction = 0.9 / foc->vdqMag;
	if(modulationIndexReduction < 1.0)
	{
		foc->vdqRef.real = foc->vdqRef.real * modulationIndexReduction;
		foc->vdqRef.imag *= foc->vdqRef.imag * modulationIndexReduction;
		foc->piIq.uk = foc->vdqRef.imag;
		foc->piId.uk = foc->vdqRef.real;
	}
}
/* Not used */
StdReal PmsmFoc_getVdqLimit(PmsmFoc* const foc)
{
	return 0;
}
/* static */
void PmsmFoc_doInverseParkTransform(PmsmFoc* const foc)
{
#if(EMOTOR_LIB == MC_EMOTOR)
	foc->VoltageAngleCosSin = LookUp_CosinusSinus(foc->electricalAngle);
#endif
#if(EMOTOR_LIB == MC_EMOTOR)
	foc->vabRef = Park_Reverse(&foc->vdqRef, &foc->VoltageAngleCosSin);
	foc->modulationIndex = foc->vabRef;
#endif
}

void PmsmFoc_tuneCurrentRegulator(MotorControl* const motorCtrl)
{
	/* Current reconstruction */
	PmsmFoc_reconstructCurrent(motorCtrl);

	/* Clarke Transformation */
	PmsmFoc_doClarkeTransform(&motorCtrl->pmsmFoc);

	/* Park Transformation */
	PmsmFoc_doParkTransform(&motorCtrl->pmsmFoc);

	if(motorCtrl->controlParameters.tuneCurrentRegs == TRUE)
	{
		motorCtrl->controlParameters.tuneCurrentRegsCounter++;
		if(motorCtrl->controlParameters.tuneCurrentRegsCounter >= 10000)
		{
			motorCtrl->controlParameters.tuneCurrentRegsCounter = 0;
			if(motorCtrl->pmsmFoc.idqRef.real == 0.0)
			{
				motorCtrl->pmsmFoc.idqRef.real = 0.5;
				motorCtrl->pmsmFoc.idqRef.imag = 0.0;
			}
			else
			{
				motorCtrl->pmsmFoc.idqRef.real = 0.0;
				motorCtrl->pmsmFoc.idqRef.imag = 0.0;
			}
		}
	}
	if(motorCtrl->controlParameters.tuneCurrentRegs == FALSE)
	{
		motorCtrl->pmsmFoc.idqRef.real = 0.0;
		motorCtrl->pmsmFoc.idqRef.imag = 0.0;
		
		motorCtrl->controlParameters.tuneCurrentRegsCounter = 0;
	}
	/* PI Controller #1 -  Iq PI controller of FOC */
	PmsmFoc_doIqControl(&motorCtrl->pmsmFoc);

	/* PI Controller #2 -  Id PI controller of FOC */
	PmsmFoc_doIdControl(&motorCtrl->pmsmFoc);

	/* Inverse Park Transformation */
	PmsmFoc_doInverseParkTransform(&motorCtrl->pmsmFoc);

#if(DQ_DECOUPLING == ENABLED)
	PmsmFoc_doDqDecoupling(&motorCtrl->pmsmFoc);
#endif

	PmsmFoc_SvmStart(&motorCtrl->inverter, motorCtrl->pmsmFoc.modulationIndex);
}
/* static */
void PmsmFoc_doDqDecoupling(PmsmFoc* const foc)
{

}

void PmsmFoc_doVfControl(MotorControl* const motorCtrl)
{
#if(EMOTOR_LIB == MC_EMOTOR)
	CplxStdReal cossin;
#endif
	/* Update electrical position and measSpeed*/
	motorCtrl->pmsmFoc.electricalAngle =
			(sint16) PmsmFoc_PositionAcquisition_updatePosition(&motorCtrl->positionSensor);
	motorCtrl->pmsmFoc.speedControl.measSpeed = IfxStdIf_Pos_radsToRpm(
			PmsmFoc_PositionAcquisition_updateSpeed(&motorCtrl->positionSensor));

	/* Current reconstruction */
	PmsmFoc_reconstructCurrent(motorCtrl);
	if(motorCtrl->interface.CurrnetIfMode == RUNNING_MODE)
	{
		PmsmFoc_Gatedriver_Enable();
		/* Update electrical angle and calculate modulation index */
#if(EMOTOR_LIB == MC_EMOTOR)
		sint16 electricAngle;
		motorCtrl->openLoop.electricalAngle += motorCtrl->openLoop.electricalAngleDelta;
		electricAngle= (motorCtrl->openLoop.electricalAngle >> 16) & (COSSIN_TABLE_SIZE - 1);
		cossin = LookUp_CosinusSinus(electricAngle);
#endif
		motorCtrl->openLoop.modulationIndex.real = cossin.real * motorCtrl->openLoop.amplitude;
		motorCtrl->openLoop.modulationIndex.imag = cossin.imag * motorCtrl->openLoop.amplitude;
	}
	
	if(motorCtrl->interface.CurrnetIfMode == STOP_MODE)
	{
		motorCtrl->openLoop.electricalAngle = 0;
		motorCtrl->openLoop.electricalAngleDelta = 0;
		motorCtrl->openLoop.amplitude = 0.0;
		motorCtrl->openLoop.modulationIndex.real = 0;
		motorCtrl->openLoop.modulationIndex.imag = 0;
		PmsmFoc_Gatedriver_Disable();
	}

	PmsmFoc_SvmStart(&motorCtrl->inverter, motorCtrl->openLoop.modulationIndex);
}
/* Not used */
void PmsmFoc_doMiscWorks(MotorControl* const motorCtrl)
{

}
