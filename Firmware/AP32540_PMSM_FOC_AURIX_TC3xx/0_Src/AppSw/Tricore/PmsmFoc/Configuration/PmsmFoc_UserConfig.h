/*
 * \file PmsmFoc_UserConfig.h
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

#ifndef PMSM_FOC_USER_CONFIG_H_
#define PMSM_FOC_USER_CONFIG_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmFoc_Macro.h"
/******************************************************************************/
/*--------------------------------Macros--------------------------------------*/
/******************************************************************************/

#define PMSM_FOC_HARDWARE_KIT				KIT_A2G_TC387_MOTORCTRL
#define TFT_DISPLAYMODE                 	ENABLED
#define ONE_EYEMODE                     	ENABLED
#define TLF35584_DRIVER                 	ENABLED
#define TLE9180_DRIVER                  	ENABLED
#define DBGCTRLMODE                     	ENABLED
#define OUTPUTTEST 							DISABLED

											/*
											 * 1. KIT_A2G_TC387_MOTORCTRL
											 * 2. CUSTOM_KIT (not implemented)
 	 	 	 	 	 	 	 	 	 	 	 */

#define FOC_CONTROL_SCHEME               	SPEED_CONTROL
											/*
											 * 1. SPEED_CONTROL
											 * 2. CURRENT_CONTROL
											 */
#define FOC_VOLTAGE_LIMIT 	 				DISABLED
											/*
											 * 1. ENABLED
											 * 2. DISABLED
											 */

#define FOC_DQ_DECOUPLING 					DISABLED /*(not implemented)*/
#define FOC_MTPA 							DISABLED /*(not implemented)*/
#define FOC_FIELD_WEAKENING 				DISABLED /*(not implemented)*/
#define FOC_MAX_EFFICIENCY 					DISABLED /*(not implemented)*/


#define POSITION_SENSOR_TYPE               	ENCODER
											/*
											 * 1. ENCODER
											 * 2. RESOLVER (not implemented)
											 * 3. HALL (not implemented)
											 * 4. SENSORLESS (not implemented)
											 * 5. xGMR (not implemented)
											 */
#define GTM_USED							GTM_TOM_WITHOUT_DTM_USED
											/*
											 * 1. GTM_TOM_WITHOUT_DTM_USED
											 * 2. GTM_ATOM_WITH_DTM_USED (not implemented)
											 * 3. GTM_ATOM_WITHOUT_DTM_USED (not implemented)
											 */


#if(PMSM_FOC_HARDWARE_KIT == KIT_A2G_TC387_MOTORCTRL)

#define PHASE_CURRENT_RECONSTRUCTION        USER_LOWSIDE_THREE_SHUNT_WITH_HIGHSIDE_MONITORING
											/*
											* 1. USER_LOWSIDE_SINGLE_SHUNT (not implemented)
											* 2. USER_LOWSIDE_THREE_SHUNT_WITHOUT_HIGHSIDE_MONITORING
											* 3. USER_LOWSIDE_THREE_SHUNT_WITH_HIGHSIDE_MONITORING
											* 4. USER_HIGHSIDE_SINGLE_SHUNT (GTM Interrupt for control loop, 2x call back for EVADC, not implemented)
											* 5. USER_LOWSIDE_TWO_SHUNT_MONITORING
											*/
#define BEMF_MEASUREMENT                    ENABLED
#define DC_LINK_VOLTAGE_MEASUREMENT         ENABLED

#endif

#define  EMOTOR_LIB							MC_EMOTOR
											/*
											* 1. MC_EMOTOR
											* 2. CUSTOM (not implemented)
											*/
#define TRACE_MEMORY           				(512U)

#define EC_MAX_SPEED						(6000U) /* Change limit according to application needs, rpm */
#define EC_MIN_SPEED						(0U)	/* Change limit according to application needs, rpm */
/*
 * Hardware kit.
 *
 * KIT_AURIX_TC3XX_MOTORCTR
 * CUSTOM_KIT
 *
*/

/*
 *  MCU Card.
 *
 *  APP_KIT_TC387A
 *  CUSTOM_MCU
*/

/*
 *  Inverter Card
 *
 *	EMOTOR_DRIVE_V_3_1
 *	CUSTOM_INVERTER
 *
*/

/*
 * Motor Type
 *
 * NANOTEC_MOTOR_DB42S02
 * CUSTOM_MOTOR
 *
*/
#if(PMSM_FOC_HARDWARE_KIT == KIT_A2G_TC387_MOTORCTRL)
#define MCUCARD_TYPE                                      APP_KIT_TFT_TC387A
#define MCUCARD_TYPE_PATH                                 "PmsmFoc_AppKitTft_TC387A.h"
#define INVERTERCARD_TYPE                                 EMOTOR_DRIVE_V_3_1
#define INVERTERCARD_TYPE_PATH                            "PmsmFoc_EMotorDrive_v_3_1.h"
#define MOTOR_TYPE                                        NANOTEC_MOTOR_DB42S02
#define MOTOR_TYPE_PATH                                   "PmsmFoc_Motor_Nanotec_DB42S02.h"
#elif(PMSM_FOC_HARDWARE_KIT == CUSTOM_KIT)
#define MCUCARD_TYPE                                      CUSTOM_MCU
#define MCUCARD_TYPE_PATH                                 "PmsmFoc_CUSTOM_MCU.h" 		/* Shall be added by user */
#define INVERTERCARD_TYPE                                 CUSTOM_INVERTER
#define INVERTERCARD_TYPE_PATH                            "PmsmFoc_CUSTOM_INVERTER.h" 	/* Shall be added by user */
#define MOTOR_TYPE                                        CUSTOM_MOTOR
#define MOTOR_TYPE_PATH                                   "PmsmFoc_CUSTOM_MOTOR.h" 		/* Shall be added by user */
#endif



#define SW_NAME 			"PMSM_FOC_AURIX_TC3xx"
#define SW_REVISION         (0x00020000)            		/**< \brief Software version and revision 0x00vvrrpp, with vv the version number and rr the revision number, pp the patch number. even rr are public release */

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

#endif /* _PMSM_FOC_USER_CONFIG_H_ */
