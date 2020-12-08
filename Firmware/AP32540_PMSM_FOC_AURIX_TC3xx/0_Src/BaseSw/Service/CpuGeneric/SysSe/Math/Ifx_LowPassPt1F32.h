/**
 * \file Ifx_LowPassPt1F32.h
 * \brief Low pass filter PT1
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
 *
 * \defgroup library_srvsw_sysse_math_f32_lowpasspt1 Low-pass Filter: Type PT1
 * This module implements a PT1 low pass filter.
 * http://de.wikipedia.org/wiki/PT1-Glied
 *
 * Formula: \n
 * \f$ y_k = y_{k-1} + a * x_k - b * y_{k-1} \f$ \n
 * with \f$(T^* = \frac{T_s}{T+T_s})\f$, \f$(a = K*T^*)\f$, \f$(b = T^*)\f$
 * with \f$(T_s: Sample time)\f$, \f$(K: Gain)\f$, \f$(T = \frac{1}{\omega_0})\f$
 *
 * \ingroup library_srvsw_sysse_math_f32
 *
 */

#if !defined(IFX_LOWPASSPT1F32)
#define IFX_LOWPASSPT1F32
//------------------------------------------------------------------------------
#include "Cpu/Std/Ifx_Types.h"
//------------------------------------------------------------------------------

/** \brief PT1 object definition.
 */
typedef struct
{
    float32 a;              /**< \brief a parameter */
    float32 b;              /**< \brief b parameter */
    float32 out;            /**< \brief last output */
} Ifx_LowPassPt1F32;

/** \brief PT1 configuration */
typedef struct
{
    float32 cutOffFrequency; /**< \brief Cut off frequency */
    float32 gain;            /**< \brief Gain */
    float32 samplingTime;    /**< \brief Sampling time */
} Ifx_LowPassPt1F32_Config;

//------------------------------------------------------------------------------

/** \addtogroup  library_srvsw_sysse_math_f32_lowpasspt1
 * \{ */
IFX_EXTERN void    Ifx_LowPassPt1F32_init(Ifx_LowPassPt1F32 *filter, const Ifx_LowPassPt1F32_Config *config);
IFX_INLINE void    Ifx_LowPassPt1F32_reset(Ifx_LowPassPt1F32 *filter);
IFX_EXTERN float32 Ifx_LowPassPt1F32_do(Ifx_LowPassPt1F32 *filter, float32 input);
/** \} */

//------------------------------------------------------------------------------

/** \brief Reset the internal filter variable
 * \param filter Specifies PT1 filter.
 */
IFX_INLINE void Ifx_LowPassPt1F32_reset(Ifx_LowPassPt1F32 *filter)
{
    filter->out = 0.0;
}


//------------------------------------------------------------------------------
#endif
