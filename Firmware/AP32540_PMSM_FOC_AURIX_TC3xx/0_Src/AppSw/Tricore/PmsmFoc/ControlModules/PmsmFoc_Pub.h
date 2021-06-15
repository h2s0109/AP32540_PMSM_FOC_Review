/*
 * \file PmsmFoc_Functions.h
 * @brief Field Oriented Control
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

#ifndef PMSMFOC_PUB_H
#define PMSMFOC_PUB_H
#if 0
/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmFoc_UserConfig.h"
#include "Ifx_PicF32.h"
#include "Ifx_RampF32.h"
#include "StdReal.h"

#include "LibMotordrive_pub.h"
#include "PmsmFoc_Inverter.h"
/* STEVE:Is it correct position */
#include "PmsmFoc_Motor.h"
#include "PmsmMid_ext.h"
#include "LibMath_pub.h"

#include "PmsmFoc_SpeedControl.h"
#include MOTOR_TYPE_PATH
#if(DBGCTRLMODE == ENABLED)
	#include "Dbgctrl_pub.h"
#endif

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/
typedef enum StateMachine
{
	StateMachine_calibration = 0,
	StateMachine_focClosedLoop,
	StateMachine_enableInverter,
	StateMachine_vfOpenLoop,
	StateMachine_tuneCurrentRegulators,
	StateMachine_prePositioning,
	StateMachine_motorIdle,
	StateMachine_motorStop,
	StateMachine_motorHold,
	StateMachine_identifyMotorParameters,
	StateMachine_ifOpenLoop,
	StateMachine_dtcClosedLoop,
}StateMachine;

typedef enum ControlScheme
{
	ControlScheme_speed = 0,
	ControlScheme_current,
	ControlScheme_torque,
	ControlScheme_voltage,
}ControlScheme;
/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
/** @brief Interfaces information.
 */
typedef struct
{
	uint32 running;								/**< \brief 1 = the motor is running. 0 = the motor is stopped. */
	uint32 start;								/**< \brief 1 = request to start. 0 = no effect */
	uint32 stop;								/**< \brief 1 = request to stop. 0 = no effect  */
	uint32 demo;								/**< \brief 1 = request to start demo. 0 = no effect  */
	sint32 motorTargetSpeed;					/**< @brief Target speed reference in rpm */
	uint32 hadEmergency;						/**< \brief 1 = an emergency event occurred. 0 = nothing*/
} Interfaces;

/** @brief Interfaces information.
 */
typedef enum
{
	RUNNING_MODE = 0,
	START_MODE,
	STOP_MODE,
	CAL_MODE,
	DEMO_MODE,
} IFMODE;

/** @brief Open loop information.
 */
typedef struct
{
    float32   amplitude;						/**< \brief Vector amplitude in open loop mode. Range=[0,1] */
    uint32    electricalAngleDelta;				/**< \brief Delta angle added. Format Q16.16 */
    uint32    electricalAngle;          		/**< \brief Open loop electrical angle. */
#if(EMOTOR_LIB == MC_EMOTOR)
	CplxStdReal AngleCosSin;					/**< \brief sin(angle) and cos(angle) values */
    CplxStdReal  modulationIndex;				/**< \brief Modulation Index */
#endif
} OpenLoop;


/** @brief FOC information.
 */
typedef struct
{

#if(EMOTOR_LIB == MC_EMOTOR)
	T3Phase  iPhaseMeas; 						/**< \brief Current of motor phase U, V and W */
	T3Phase  bemf;								/**< \brief Current of motor phase U, V and W */
	CplxStdReal idqRef;							/**< \brief Reference DQ-axis values of current space vector */
	CplxStdReal idqRefExternal;					/**< \brief External reference DQ-axis values of current space vector */
	CplxStdReal idqMeas;						/**< \brief Measured DQ-axis values of current space vector */
	CplxStdReal idqError;						/**< \brief Difference between DQ-axis measured and reference values of current space vector */
	CplxStdReal vdqRef;							/**< \brief Reference DQ-axis values of voltage space vector */

	StdReal  vdqMag;							/**< \brief Magnitude of voltage space vector */
	CplxStdReal iab;							/**< \brief Alpha/Beta values of current space vector */
	CplxStdReal vabRef;							/**< \brief Reference Alpha/Beta values of voltage space vector */


	CplxStdReal CurrentAngleCosSin;				/**< \brief sin(angle) and cos(angle) values */
	CplxStdReal VoltageAngleCosSin;				/**< \brief sin(angle) and cos(angle) values */

	StdReal torqueRef;							/**< \brief Torque reference as command or output of speed regulator */
	StdReal torqueEst;							/**< \brief Torque estimated based on motor parameters and actual current */

	Ifx_PicF32 piId;							/**< \brief PI controller for the direct current */
	Ifx_PicF32 piIq;							/**< \brief PI controller for the quadrature current */

	Ifx_RampF32 speedRamp;						/**< \brief Speed reference ramp */
	Ifx_RampF32 idRefExternalRamp;				/**< \brief External D-axis current reference ramp */
	Ifx_RampF32 iqRefExternalRamp;				/**< \brief External Q-axis current reference ramp */

	#if 0
	float32 mechanicalSpeed;
	float32 vdc;
	sint32 rawMechanicalAngle;
	float32 electricalSpeed;                  /**< \brief Rotor electrical speed (rad/s) */
	float32 electricalAngleConst;
	IfxStdIf_Pos_RawAngle        elAngle;
	#endif

	sint16 electricalAngle;						/**< \brief Rotor angle from Encoder, Resolver, Estimator, etc. */
	SpeedControl speedControl;					/**< \brief Speed control object */
	CplxStdReal modulationIndex;				/**< \brief Modulation Index */
#endif
} PmsmFoc;

typedef struct
{
	uint32 state; 								/**< \brief Motor state (e.g.: V/f, FOC) */
	ControlScheme controlScheme; 				/**< \brief Control scheme (e.g. speed control, current control) */
	uint16 rotationDir; 						/**< \brief Rotation direction of motor (rotor angle increasing, or decreasing) */
	uint16 inverterStatus;						/**< \brief 0 -> Inverter disabled, 1 -> Inverter enabled */
	uint32 counter;								/**< \brief General purpose counter */
	uint32 rampCounter; 						/**< \brief General purpose counter, or counter for motor speed ramp up/down. */
	uint32 alignmentCounter; 					/**< \brief Counter for rotor initial positioning / alignment in V/f */
	uint32 nonRealTimeCounter; 					/**< \brief Counter for tasks that don't need real-time computing */

	uint32 encOffsetCalCounter; 				/**< \brief Counter for calibration */
	uint32 encTopZeroCounter; 					/**< \brief Counter for calibration */

	uint32 tuneCurrentRegsCounter; 				/**< \brief  Counter for calibration */
    boolean tuneCurrentRegs;					/**< \brief 1 = current regulator tuning is enabled. 0 = regulator tuning is disabled. */

} ControlParameters;

typedef struct
{
    boolean    swapped;                  		/**< \brief if true and in @ref DIAG mode, the phases A and B are swapped (FALSE: ABC; TRUE: ACB)  */
    uint16     rotate;                   		/**< \brief range[0,2] (for Swapped=FALSE => 0: ABC; 1: CAB, 2: BCA. for Swapped=TRUE => 0: ACB; 1: BAC, 2: CBA.)  */
    boolean    focControlEnabled;        		/**< \brief Specifies if the F.O.C. is enabled or disabled */
    boolean    encoderEnabled;           		/**< \brief Specifies if the position sensor is enabled */
    uint16     maxTurn;                  		/**< \brief Specifies that the control should stop after the MaxTurn have been detected. In @ref DIAG mode only. */
    sint32     electricalAngleOffset;
    sint32     electricalAngleSensor;
    boolean	   encCalStatus;
}Diagnostic;

typedef struct
{
	IFMODE CurrnetIfMode;
	Interfaces			interface;				/**< \brief Interface parameters object */
	ControlParameters 	controlParameters;		/**< \brief Control parameters object */
	Diagnostic			diagnostic;				/**< \brief Diagnostic object */
	Inverter  			inverter;				/**< \brief Inverter object */
	PmsmFoc   			pmsmFoc;				/**< \brief FOC object */
	OpenLoop  			openLoop;     			/**< \brief Open loop object */
	PositionAcquisition	positionSensor;			/**< \brief Position sensor object */
	MotorParameters		motor;					/**< \brief Motor parameters object */
#if(DBGCTRLMODE == ENABLED)
	st_DbgCtrl 			sDbgCtrl;				/**< \brief Debugger control parameters object */
#endif
} MotorControl;

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
extern MotorControl g_motorControl;
/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/


/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
#endif
#endif /* PMSMFOC_PUB_H */