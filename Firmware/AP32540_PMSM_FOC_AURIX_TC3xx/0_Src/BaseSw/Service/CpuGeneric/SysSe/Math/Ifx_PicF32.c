/**
 * \file Ifx_PicF32.c
 * \brief Proportional integral controller.
 *
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

//------------------------------------------------------------------------------
#include "Ifx_PicF32.h"
//------------------------------------------------------------------------------
/** \brief Initialize the PI controller.
 *
 * This function initialises the PI controller. It must be called before any call to other PI functions.
 *
 * \param pic Specifies PI controller.
 *
 * \return none
 *
 * \see Ifx_PicF32_setKpKi(), Ifx_PicF32_setKpKi(), Ifx_PicF32_setLimit()
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
void Ifx_PicF32_init(Ifx_PicF32 *pic)
{
    pic->a0        = 0;
    pic->a1        = 0;
    pic->ik        = 0;
    pic->uk        = 0;
    pic->lower     = 0;
    pic->upper     = 0;
    pic->hitLimits = FALSE;
}


/** \brief Set the PI controller kp and ki parameter (for fixpoint calculation).
 *
 * This function sets the PI controller kp and ki parameter.
 *
 * \param pic Specifies PI controller.
 * \param kp Specifies the PI controller kp value.
 * \param ki Specifies the PI controller ki value.
 * \param Ts Specifies PI controller sampling time in seconds.
 *
 * \return none
 * \see Ifx_PicF32_getKpKi(), Ifx_PicF32_getKpKi(),
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
void Ifx_PicF32_setKpKi(Ifx_PicF32 *pic, float32 kp, float32 ki, float32 Ts)
{
    if ((kp < 0) || (kp > 0))
    {
        float32 k = (ki / kp) * (Ts / 2);
        pic->a0 = kp * (k - 1);  /* kp.(Wpi.Tsample/2 - 1); Wpi = ki/kp  */
        pic->a1 = kp * (k + 1);  /* kp.(Wpi.Tsample/2 + 1); Wpi = ki/kp  */
    }
    else
    {
        pic->a0 = 0;
        pic->a1 = 0;
    }
}


/** \brief Return the PI controller kp and ki parameter.
 *
 * This function returns the PI controller kp and ki parameter.
 *
 * \param pic Specifies PI controller.
 * \param kp This parameter is filled in by the function with the PI controller kp value.
 * \param ki This parameter is filled in by the function with the PI controller ki value.
 * \param Ts Specifies PI controller sampling time in seconds.
 *
 * \return none
 * \see Ifx_PicF32_setKpKi(), Ifx_PicF32_setKpKi()
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
void Ifx_PicF32_getKpKi(Ifx_PicF32 *pic, float32 *kp, float32 *ki, float32 Ts)
{
    *ki = (pic->a1 + pic->a0) / Ts;
    *kp = (pic->a1 - pic->a0) / 2;
}


/** \brief Set the PI controller limits.
 *
 * This function sets the PI controller limits.
 *
 * \param pic Specifies PI controller.
 * \param lowerLimit Specifies the PI controller lower limit.
 * \param upperLimit Specifies the PI controller upper limit.
 *
 * \return none
 * \see Ifx_PicF32_getLimit()
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
void Ifx_PicF32_setLimit(Ifx_PicF32 *pic, float32 lowerLimit, float32 upperLimit)
{
    pic->lower     = lowerLimit;
    pic->upper     = upperLimit;
    pic->hitLimits = FALSE;
}


/** \brief Return the PI controller limits.
 *
 * This function returns the PI controller limits.
 *
 * \param pic Specifies PI controller.
 * \param lowerLimit This parameter is filled in by the function with the PI controller lower limit.
 * \param upperLimit This parameter is filled in by the function with the PI controller upper limit.
 *
 * \return none
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
void Ifx_PicF32_getLimit(Ifx_PicF32 *pic, float32 *lowerLimit, float32 *upperLimit)
{
    *lowerLimit = pic->lower;
    *upperLimit = pic->upper;
}


/** \brief Test if the PI controller limits have been hit.
 *
 * This function returns TRUE if the PI controller limits have been hit.
 *
 * \param pic Specifies PI controller.
 *
 * \retval TRUE if the PI controller limits have been hit.
 * \retval FALSE if the PI controller limits have not been hit.
 * \see Ifx_PicF32_setLimit()
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
boolean Ifx_PicF32_isLimitsHit(Ifx_PicF32 *pic)
{
    return pic->hitLimits;
}


/** \brief Resets the PI controller limits hit flag.
 *
 * This function resets the PI controller limits hit flag.
 *
 * \param pic Specifies PI controller.
 *
 * \return None.
 * \see Ifx_PicF32_isLimitsHit()
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
void Ifx_PicF32_resetLimitHit(Ifx_PicF32 *pic)
{
    pic->hitLimits = FALSE;
}


/** \brief Update the PI controller with the new error value.
 *
 * This function updates the PI controller and return the new PI output according to the following formula:
 *  U(k+1)= a1 * I(k+1) + a0 * ik + uk
 *
 * \param pic Specifies PI controller.
 * \param Input Specifies the new input error value.
 *
 * \return Returns the new PI output value.
 * \ingroup library_srvsw_sysse_math_f32_pic
 */

//float32 Ifx_Maths_PicFlt32_step(Ifx_PicF32 *pic, float32 Input)		//Float in MC
//float32 Ifx_Maths_PicF32_step(Ifx_PicF32 *pic, float32 Input)		//SAMBA - Fixed Point 32



float32 Ifx_PicF32_step(Ifx_PicF32 *pic, float32 Input)
{
    float32 uk;
    uk      = (pic->a1 * Input) + (pic->a0 * pic->ik) + pic->uk;

    pic->ik = Input;

    if (uk >= pic->upper)
    {
        pic->hitLimits = TRUE;
        pic->uk        = pic->upper;
    }
    else if (uk <= pic->lower)
    {
        pic->hitLimits = TRUE;
        pic->uk        = pic->lower;
    }
    else
    {
        pic->uk = uk;
    }

    return pic->uk;
}


/** \brief Reset the PI controller.
 *
 * This function resets the PI controller by setting the Last error and integral part to 0.
 *
 * \param pic Specifies PI controller.
 *
 * \return none
 * \ingroup library_srvsw_sysse_math_f32_pic
 */
void Ifx_PicF32_reset(Ifx_PicF32 *pic)
{
    pic->ik = 0;
    pic->uk = 0;
}
