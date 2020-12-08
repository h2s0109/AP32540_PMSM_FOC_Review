/*
 * \file PmsmFoc_Motor_Nanotec_DB42S02.h
 * \brief
 * \ingroup pmsm_foc_configuration
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

#ifndef PMSM_FOC_MOTOR_NANOTEC_DB42S02_H_
#define PMSM_FOC_MOTOR_NANOTEC_DB42S02_H_
/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmFoc_UserConfig.h"

/******************************************************************************/
/*--------------------------------Macros--------------------------------------*/
/******************************************************************************/



#if(MOTOR_TYPE == NANOTEC_MOTOR_DB42S02)
/** \brief Define the motor pole pairs number. */
#define USER_MOTOR_POLE_PAIR                       	(4U)
/** \brief Define the motor resistance/phase to phase, in Ohm */
#define USER_MOTOR_RESISTANCE_PHASE_TO_PHASE       	(0.19f)
/** \brief Define the motor inductance/phase to phase, in H */
#define USER_MOTOR_INDUCTANCE_PHASE_TO_PHASE        (0.245e-3)
/** \brief Define the Motor wiring Connection */
#define USER_MOTOR_WIRING_CONNECTION				DELTA

#if (USER_MOTOR_WIRING_CONNECTION == DELTA)
/** \brief Define the motor resistance per phase in Ohm */
#define USER_MOTOR_RESISTANCE_PER_PHASE             (USER_MOTOR_RESISTANCE_PHASE_TO_PHASE*3/2)
/** \brief Define the motor inductance per phase in H */
#define USER_MOTOR_INDUCTANCE_PER_PHASE             (USER_MOTOR_INDUCTANCE_PHASE_TO_PHASE*3/2)
#elif(USER_MOTOR_WIRING_CONNECTION == WYE)
/** \brief Define the motor resistance per phase in Ohm */
#define USER_MOTOR_RESISTANCE_PER_PHASE             (USER_MOTOR_RESISTANCE_PHASE_TO_PHASE/2)
/** \brief Define the motor inductance per phase in H */
#define USER_MOTOR_INDUCTANCE_PER_PHASE             (USER_MOTOR_INDUCTANCE_PHASE_TO_PHASE/2)
#endif

/** \brief Define the speed point when switching from one to another position sensing method value. */
#define USER_MOTOR_SPEED_PULSE_COUNTING_RPM         (1200.0f)
/** \brief Define the initial incremental encoder offset value. */
#define USER_MOTOR_ENCODER_OFFSET					(-855)
/** \brief Define the incremental encoder pulses per revolution value.*/
#define USER_MOTOR_ENCODER_PULSES_PER_REVOLUTION	(1000U)

#define USER_MOTOR_ENCODER_CAL_TOP_ZERO_AMPL_DELTA	(0.0005f)
#define USER_MOTOR_ENCODER_CAL_TOP_ZERO_AMPL_MAX	(0.05f)
#define USER_MOTOR_ENCODER_CAL_TOP_ZERO_ANGLE_DELTA	(45000U)
#define USER_MOTOR_ENCODER_CAL_TOP_ZERO_COUNTS		(1000U)

#define USER_MOTOR_ENCODER_CAL_OFFSET_AMPL_DELTA	(0.00025f)
#define USER_MOTOR_ENCODER_CAL_OFFSET_AMPL_MAX		(0.1f)
#define USER_MOTOR_ENCODER_CAL_OFFSET_ANGLE_DELTA	(1000U)
#define USER_MOTOR_ENCODER_CAL_OFFSET_COUNTS		(30000U)

/** \brief Define the incremental encoder maximum speed value. */
#define USER_MOTOR_ENCODER_MAX_RPM			        (6000.0f)

/** \brief Define the motor min speed limit value. */
#define USER_MOTOR_SPEED_LOW_LIMIT_RPM              (1.0f)
/** \brief Define the motor max speed limit value, based on maximum speed of used incremental encoder */
#define USER_MOTOR_SPEED_HIGH_LIMIT_RPM             (USER_MOTOR_ENCODER_MAX_RPM)

/** \brief Define the D-axis current regulator Kp parameter adjustment value.  */
#define USER_MOTOR_KPD_MULTI 						(0.50f)
/** \brief Define the D-axis current regulator Ki parameter adjustment value.  */
#define USER_MOTOR_KID_MULTI 						(1.0f)
/** \brief Define the Q-axis current regulator Kp parameter adjustment value.  */
#define USER_MOTOR_KPQ_MULTI 						(0.5f)
/** \brief Define the Q-axis current regulator Ki parameter adjustment value.  */
#define USER_MOTOR_KIQ_MULTI 						(1.0f)
/** \brief Define the Bandwidth of the PI Controller [Hz]. */
#define USER_MOTOR_CURRENT_PI_CONTROLLER_BANDWITH 	(1000.0f)
/** \brief Define the stator time constant. */
#define USER_MOTOR_FOC_CALC_TSTATOR    				(USER_MOTOR_INDUCTANCE_PER_PHASE) \
													/(USER_MOTOR_RESISTANCE_PER_PHASE)
/** \brief Define the DQ-axis current controller parameter scaling value.  */
#define USER_MOTOR_FOC_K_FACTOR						(1.0/(USER_INVERTER_VDC_LINK_V*IFX_TWO_OVER_PI))
/** \brief Define the DQ-axis current controller Ki parameter value. */
#define USER_MOTOR_FOC_CALC_KI						(USER_MOTOR_RESISTANCE_PER_PHASE)/ \
													(1/(2*IFX_PI*USER_MOTOR_CURRENT_PI_CONTROLLER_BANDWITH))\
													*USER_MOTOR_FOC_K_FACTOR
/** \brief Define the DQ-axis current controller Kp parameter value. */
#define USER_MOTOR_FOC_CALC_KP						(USER_MOTOR_FOC_CALC_KI*USER_MOTOR_FOC_CALC_TSTATOR)
/** \brief Define the D-axis current regulator adjusted Kp parameter value. */
#define USER_MOTOR_PI_ID_KP 						(USER_MOTOR_KPD_MULTI*(USER_MOTOR_FOC_CALC_KP))
/** \brief Define the D-axis current regulator adjusted Ki parameter value. */
#define USER_MOTOR_PI_ID_KI 						(USER_MOTOR_KID_MULTI*(USER_MOTOR_FOC_CALC_KI))
/** \brief Define the Q-axis current regulator Kp parameter value. */
#define USER_MOTOR_PI_IQ_KP 						(USER_MOTOR_KPQ_MULTI*(USER_MOTOR_FOC_CALC_KP))
/** \brief Define the Q-axis current regulator Ki parameter value. */
#define USER_MOTOR_PI_IQ_KI 						(USER_MOTOR_KIQ_MULTI*(USER_MOTOR_FOC_CALC_KI))
/** \brief Define the D-axis current regulator max limit value. */
#define USER_MOTOR_PI_ID_LIMIT_MAX  				(0.85f)
/** \brief Define the Q-axis current regulator max limit value. */
#define USER_MOTOR_PI_IQ_LIMIT_MAX  				(0.85f)
/** \brief Define the D-axis current regulator control period value. */
#define USER_MOTOR_PI_ID_CONTROL_PERIOD 			(50e-6)
/** \brief Define the Q-axis current regulator control period value. */
#define USER_MOTOR_PI_IQ_CONTROL_PERIOD 			(50e-6)
/** \brief Define the max limit value of Q-axis current reference. */
#define USER_MOTOR_IQLIMIT         					(5.0f)
/** \brief Define the max limit value of D-axis current reference. */
#define USER_MOTOR_IDLIMIT         					(4.0f)
/** \brief Empirical value, should be changed after fine tuning. */
#define USER_MOTOR_SPEED_KP_MULTI            		(0.000005f)
/** \brief Empirical value, should be changed after fine tuning. */
#define USER_MOTOR_SPEED_KI_MULTI            		(0.00004f)
/** \brief Define the Kp parameter value. */
#define USER_MOTOR_SPEED_CONTROL_KP          		(USER_MOTOR_SPEED_KP_MULTI*(USER_MOTOR_FOC_CALC_KP))
/** \brief Define the Ki parameter value. */
#define USER_MOTOR_SPEED_CONTROL_KI          		(USER_MOTOR_SPEED_KI_MULTI*(USER_MOTOR_FOC_CALC_KI))
/** \brief Define the Pi Controller Out minimum value. */
#define USER_MOTOR_SPEED_CONTROL_MIN         		(-0.3f)
/** \brief Define the Pi Controller Out maximum value. */
#define USER_MOTOR_SPEED_CONTROL_MAX         		(1.0f)
/** \brief Define the max rpm in 1/min value. */
#define USER_MOTOR_SPEED_CONTROL_MAX_RPM     		(USER_MOTOR_SPEED_HIGH_LIMIT_RPM)
/** \brief Define the min rpm in 1/min value. */
#define USER_MOTOR_SPEED_CONTROL_MIN_RPM     		(200.0f)
/** \brief Define the controller period in seconds value. */
#define USER_MOTOR_SPEED_CONTROL_PERIOD      		(5e-3)
/** \brief Define the initial motor speed reference value. Unit is rpm or 1/min. */
#define USER_MOTOR_SPEED_CONTROL_REF         		(0.0f)
/** \brief Define the open loop position increment value. */
#define USER_MOTOR_OPENLOOPSPEED     				(45000U)
/** \brief Define the open loop amplitude value. */
#define USER_MOTOR_OPENLOOPAMPLITUDE 				(0.1)
/** \brief Define the of turns to get top zero value. */
#define USER_MOTOR_GOTTOPZERO        				(3)
/** \brief Define the number of fails before motor is stopped. */
#define USER_MOTOR_NUMOFFAILS        				(20U)
/** \brief Define the delta between reference speed and nominal speed. */
#define USER_MOTOR_DELTASPEED        				(1000.0f)
/** \brief Define the maximum speed slew rate, value per second. */
#define USER_MOTOR_SPEED_RAMP_SLEW_RATE        		(500.0f)
/** \brief Define the sampling period of the speed ramp function. */
#define USER_MOTOR_SPEED_RAMP_PERIOD        		(50e-3f)
/** \brief Define the maximum d-axis current slew rate, value per second. */
#define USER_MOTOR_CURRENT_D_RAMP_SLEW_RATE        	(100e-3f)
/** \brief Define the sampling period of the d-axis current ramp function. */
#define USER_MOTOR_CURRENT_D_RAMP_PERIOD        	(5e-3f)
/** \brief Define the maximum q-axis current slew rate, value per second. */
#define USER_MOTOR_CURRENT_Q_RAMP_SLEW_RATE        	(100e-3f)
/** \brief Define the sampling period of the q-axis current ramp function. */
#define USER_MOTOR_CURRENT_Q_RAMP_PERIOD        	(5e-3f)
#endif

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

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/
#endif /* PMSM_FOC_MOTOR_NANOTEC_DB42S02_H_ */
