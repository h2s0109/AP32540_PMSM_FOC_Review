/*
 * \file PmsmFoc_SpeedControl.h
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


#ifndef PMSMFOC_SPEEDCONTROL_H_
#define PMSMFOC_SPEEDCONTROL_H_

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "Ifx_PicF32.h"
#include "IfxCpu_Intrinsics.h"
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
 /** @brief speed control object.
 */
typedef struct
{
	Ifx_PicF32 piSpeed;              /**< @brief Speed PI controller */
    float32 measSpeed;               /**< @brief Speed acquired from position sensor */
    float32 refSpeed;                /**< @brief Speed reference in rpm */
    float32 maxSpeed;                /**< @brief Absolute value of the max allowed speed reference in rpm. Range=[0, +INF] */
    float32 minSpeed;                /**< @brief Absolute value of the min allowed speed reference in rpm. Range=[0, +INF] */
    boolean enabled;                 /**< @brief Speed control enable flag. TRUE: the speed control is enabled. FALSE the speed control is disabled */
} SpeedControl;
/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/
void PmsmFoc_SpeedControl_init(SpeedControl *speedControl);
float32 PmsmFoc_SpeedControl_do(SpeedControl *speedControl);
/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/
/** @brief Reset the speed controller.
 *
 * @param SpeedControl Specifies the speed control object.
 *
 * @return none
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_reset(SpeedControl *speedControl)
{
    speedControl->refSpeed = 0;
    Ifx_PicF32_reset(&speedControl->piSpeed);
}

/** @brief Enable the speed controller.
 *
 * @param SpeedControl Specifies the speed control object.
 *
 * @return none
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_enable(SpeedControl *speedControl)
{
    speedControl->enabled = TRUE;
}
/** @brief Return the status of the speed controller (Enabled / Disabled).
 *
 * @param SpeedControl Specifies the speed control object.
 *
 * @retval TRUE Returns TRUE if the speed controller is enabled
 * @retval FALSE Returns FALSE if the speed controller is disabled
 * @ingroup app_speed_control
 */
IFX_INLINE boolean PmsmFoc_SpeedControl_isEnabled(SpeedControl *speedControl)
{
    return speedControl->enabled;
}
/** @brief Disable the speed controller.
 *
 * @param SpeedControl Specifies the speed control object.
 *
 * @return none
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_disable(SpeedControl *speedControl)
{
    speedControl->enabled = FALSE;
    PmsmFoc_SpeedControl_reset(speedControl);
}

/** @brief Reset the speed controller limit flag.
 *
 * @param SpeedControl Specifies the speed control object.
 *
 * @return none
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_resetLimitFlag(SpeedControl *speedControl)
{
	Ifx_PicF32_resetLimitHit(&speedControl->piSpeed);
}

/** @brief Set the speed controller limits.
 *
 * @param SpeedControl Specifies the speed control object.
 * @param Min Specifies the PI controller min value.
 * @param Max Specifies the PI controller max value.
 *
 * @return none
 * @see Pic_SetLimit()
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_setLimit(SpeedControl *speedControl, float32 min, float32 max)
{
	Ifx_PicF32_setLimit(&speedControl->piSpeed, min, max);
}
/** @brief Set the speed controller max ref speed.
 *
 * @param SpeedControl Specifies the speed control object.
 * @param Max Specifies the speed controller max ref speed value.
 *
 * @return none
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_setMaxSpeed(SpeedControl *speedControl, float32 max)
{
    speedControl->maxSpeed = max;
}

/** @brief Set the speed controller max ref speed.
 *
 * @param SpeedControl Specifies the speed control object.
 * @param Max Specifies the speed controller max ref speed value.
 *
 * @return none
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_setMinSpeed(SpeedControl *speedControl, float32 min)
{
    speedControl->minSpeed = min;
}

/** @brief Set the speed controller reference speed.
 *
 * @param SpeedControl Specifies the speed control object.
 * @param Speed Specifies the speed controller reference speed value.
 *
 * @retval TRUE Returns TRUE if the reference speed could be set
 * @retval FALSE Returns FALSE if the reference speed is out of range
 * @ingroup app_speed_control
 */
IFX_INLINE boolean PmsmFoc_SpeedControl_setRefSpeed(SpeedControl *speedControl, float32 speed)
{
    boolean result;
    if ((__absf(speed)) > (speedControl->maxSpeed))
    {
        speedControl->refSpeed = speedControl->maxSpeed;
        result = FALSE;
    }
    else if ((__absf(speed)) < (speedControl->minSpeed))
    {
        speedControl->refSpeed = speedControl->minSpeed;
        result = FALSE;
    }
    else
    {
        speedControl->refSpeed = speed;
        result = TRUE;
    }
    return result;
}

IFX_INLINE boolean PmsmFoc_SpeedControl_setStopRefSpeed(SpeedControl *speedControl, float32 speed)
{
    boolean result;
    if ((__absf(speed)) > (speedControl->maxSpeed))
    {
        speedControl->refSpeed = speedControl->maxSpeed;
        result = FALSE;
    }
    else if ((__absf(speed)) < 0)
    {
        speedControl->refSpeed = 0;
        result = FALSE;
    }
    else
    {
        speedControl->refSpeed = speed;
        result = TRUE;
    }
    return result;
}

/** @brief Return the speed controller max ref speed.
 *
 * @param SpeedControl Specifies the speed control object.
 *
 * @return Return the max allowed ref speed
 * @ingroup app_speed_control
 */
IFX_INLINE float32 PmsmFoc_SpeedControl_getMaxSpeed(SpeedControl *speedControl)
{
    return speedControl->maxSpeed;
}

/** @brief Return the speed controller min ref speed.
 *
 * @param SpeedControl Specifies the speed control object.
 *
 * @return Return the min allowed ref speed
 * @ingroup app_speed_control
 */
IFX_INLINE float32 PmsmFoc_SpeedControl_getMinSpeed(SpeedControl *speedControl)
{
    return speedControl->minSpeed;
}

/** @brief Return the speed controller ref speed.
 *
 *  @param SpeedControl Specifies the speed control object.
 *  
 *  @return Return the ref speed
 *  @ingroup app_speed_control
 */
IFX_INLINE float32 PmsmFoc_SpeedControl_getRefSpeed(SpeedControl *speedControl)
{
    return speedControl->refSpeed;
}
/** @brief Return a copy of the speed controller PI controller.
 *
 *  @param SpeedControl Specifies the speed control object.
 *  @param Pi Specifies the location where the copy must be saved.
 *  
 *  @return Return the max allowed ref speed
 *  @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_getPi(SpeedControl *speedControl, Ifx_PicF32 *pi)
{
    *pi = speedControl->piSpeed;
}
/** @brief Set the speed controller PI parameters
 *
 * @param SpeedControl Specifies the speed control object.
 * @param Kp Specifies the PI controller Kp value.
 * @param Ki Specifies the PI controller Ki value.
 * @param Period Specifies PI controller period time in seconds.
 * @param ShiftCoef position of the fix point for the A0 and A1 parameters. Range = [-256, 255]. In case TStdReal type is float32, this parameter is ignored
 * @param ShiftResult Shift done on the result for fixpoint calculation. Range = [-32, 31]. In case TStdReal type is float32, this parameter is ignored
 *
 * @return None.
 * @see Pic_SetKpKi_StdReal()
 * @ingroup app_speed_control
 */
IFX_INLINE void PmsmFoc_SpeedControl_setKpKi(SpeedControl *speedControl, float32 kp, float32 ki, float32 period)
{
	Ifx_PicF32_setKpKi(&speedControl->piSpeed, kp, ki, period);
}

IFX_INLINE float32 PmsmFoc_SpeedControl_getSpeed(SpeedControl *speedControl)
{
    return speedControl->measSpeed;
}

#endif /* PMSMFOC_SPEEDCONTROL_H_ */
