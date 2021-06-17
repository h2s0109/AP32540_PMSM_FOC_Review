/*
 * \file PmsmFoc_PositionAndSpeedAcquisition.h
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

#ifndef PMSM_FOC_POSITION_SPEED_AQUISITION_H_
#define PMSM_FOC_POSITION_SPEED_AQUISITION_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmFoc_UserConfig.h"
#include MOTOR_TYPE_PATH
#include "IfxGpt12_IncrEnc.h"
#include "Gpt12_Init.h"
/******************************************************************************/
/*--------------------------------Macros--------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/
/** @brief Position acquisition mode
 */
typedef enum
{
	PositionAcquisition_SensorType_Hall = 0,                /**< \brief Hall sensor is used */
	PositionAcquisition_SensorType_Encoder = 1,             /**< \brief Encoder & Hall sensors are used */
	PositionAcquisition_SensorType_Resolver = 2,            /**< \brief Resolver	sensor is used */
	PositionAcquisition_SensorType_Sensorless = 3,			/**< \brief Sensorless method is used */
	PositionAcquisition_SensorType_Encoder_and_Resolver = 4 /**< \brief Encoder and Resolver sensors are used */
} POSACQUIRE_SENSORTYPE_E;

typedef enum
{
	ENC_FIND_INDEX = 0,
	ENC_FIND_OFFSET,
	ENC_CAL_DONE
} ENC_CAL_STATUS_E;
/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
typedef struct
{
	uint32 dummy;
} POSACQUIRE_HALL_S;

typedef struct
{
	uint32 dummy;
} POSACQUIRE_SENSORLESS_S;

typedef struct
{
	boolean	encOffsetCal;						/**< \brief encoder offset calibration: 1 =  enabled, 0 = disabled. */
	uint16	encFwdCnt;
	uint16 	encOffsetCalCounter; 				/**< \brief Counter for calibration */
	IfxGpt12_IncrEnc incrEncoder;
	ENC_CAL_STATUS_E calibrationStatus;
} POSACQUIRE_ENC_S;

typedef struct
{
	uint32 dummy;
} POSACQUIRE_RESOLVER_S;


/** @brief Position acquisition object
 */
typedef struct
{
	POSACQUIRE_ENC_S     		encoder;     	/**< \brief Pointer to the Encoder handler*/
	//POSACQUIRE_HALL_S       	hall;        	/**< \brief Pointer to the Hall sensor handler */
	//POSACQUIRE_RESOLVER_S    	resolver;    	/**< \brief Pointer to the Resolver handler */
	//POSACQUIRE_SENSORLESS_S 	sensorless;  	/**< \brief Pointer to the Sensorless handler */
	POSACQUIRE_SENSORTYPE_E 	sensorType;   	/**< \brief Position sensor used */
	boolean                     statusOk;     	/**< \brief Position sensor status*/
    uint32    					electricalAngle;/**< \brief Electrical angle. */
	float32						rotorSpeed;		/*< @brief Motor shaft speed */
} POSACQUIRE_S;
/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
/** /brief
 *
 * /param positionAcquisition Reference to structure that contains instance data members
 * /param sensorType Specifies the sensor type (e.g. Encoder, Resolve, Hall, Sensorless,..)
 *
 * /return
 * /note
 * /see
 * /ingroup
 */

IFX_EXTERN void PmsmFoc_PositionAcquisition_init(POSACQUIRE_S* positionAcquisition, POSACQUIRE_SENSORTYPE_E sensorType);
/** /brief
 *
 * /param positionAcquisition Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN sint32 PmsmFoc_PositionAcquisition_updatePosition(POSACQUIRE_S* positionAcquisition);
/** /brief
 *
 * /param positionAcquisition Reference to structure that contains instance data members
 * /return
 * /note
 * /see
 * /ingroup
 */
IFX_EXTERN float32 PmsmFoc_PositionAcquisition_updateSpeed(POSACQUIRE_S* positionAcquisition);

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

#endif /* PMSM_FOC_POSITION_SPEED_AQUISITION_H_ */
