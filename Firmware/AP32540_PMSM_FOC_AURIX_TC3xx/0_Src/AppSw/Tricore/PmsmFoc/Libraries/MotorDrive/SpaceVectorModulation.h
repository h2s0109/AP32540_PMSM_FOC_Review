/**
 * @file SpaceVectorModulation.h
 * @brief Space vector PWM.
 *
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
 *
 * $Revision: 72 $
 * $Date: 2009-09-14 17:58:55 +0200 (Mon, 14 Sep 2009) $
 *
 * @defgroup motor_control_svpwm Space vector modulation
 *
 * This module implements the space vector modulation.
 * @note: An assembler optimised version is used if the compiler and assembler 
 * switch CFG_OPTIMIZE is equal to 1. The files SpaceVectorModulation.fixpoint16.opt.asm and 
 * SpaceVectorModulation.float32.opt.asm must be included in the project.
 *
 * @ingroup motor_control
 *
 */

/** @ifnot no_page_src_SPACE_VECTOR_MODULATION_H
 * @page page_src_SPACE_VECTOR_MODULATION_H Space vector modulation
 *
 * The space vector modulation is used to generate a three phase sinusoidal PWM signal,
 * in order to drive the power switches.
 *
 * @section section_inverter The inverter
 *
 * The three phases inverter, is made of three half bridges with a total of 6 switches
 * as shown in the figure @ref figure_inverter "Inverter in state [001]".
 * We define by the vector [CBA] the state of the inverter, where C represent the state
 * of the top switch c with 0 for opened and 1 for closed, B the state of the switch b
 * and A the state of the switch a. We obtain the following 8 possible vectors:
 * \f$ \vec {v_0} = [000],
 * \vec {v_1} = [001],
 * \vec {v_2} = [010],
 * \vec {v_3} = [011],
 * \vec {v_4} = [100],
 * \vec {v_5} = [101], \f$
 * \f$ \vec {v_6} = [110],
 * \vec {v_7} = [111] \f$.
 *
 * @anchor figure_inverter
 * @image html "Svpwm-Inverter.gif" "Inverter in state [001]"
 *
 * The vectors [000] and [111] are said NULL vectors as the stator is in short circuit.
 * All other vectors produces a space vector equals to
 * \f$ \vec V_k = \frac{2}{3}.V_{dc}.e^{j.\frac{(k-1).\pi}{3}} \f$ where k=[1,6].
 * Those vectors can be represented in the \f$ (\alpha, \beta) \f$ stationary reference
 * frame and define 6 areas named "sectors" (sector 1 to sector 6).
 *
 * @image html "Svpwm-sectors.gif" "Inverter in state [001]"
 *
 *  Any space vector voltage \f$ \overrightarrow{V_{\alpha\beta}} \f$ can be represented as the weighted average of two adjacent
 * space vector and the vector NULL vectors.
 *
 * @image html "svpwm-pwm.gif" "Space vector modulation pulses"
 *
 * The space vector algorithm produces the following phase potentials:
 *
 *
 * \f$
 * \begin{array}{lcl}
 * V_a(\omega.t) & = &
 * \begin{cases}
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_{\alpha\beta}} \right | \cos(\omega.t-\frac{\pi}{3})
 * , & \mbox{if } 0 \le \omega.t \ll \frac{\pi}{3} \\
 *
 * \frac{3}{2} \left | \overrightarrow{V_{\alpha\beta}} \right | \cos(\omega.t)
 * , & \mbox{if } \frac{\pi}{3} \ll \omega.t \le \frac{2.\pi}{3} \\
 *
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_{\alpha\beta}} \right | \cos(\omega.t+\frac{\pi}{3})
 * , & \mbox{if } \frac{2.\pi}{3} \ll \omega.t \le \pi \\
 *
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_{\alpha\beta}} \right | \cos(\omega.t-\frac{\pi}{3})
 * , & \mbox{if } \pi \le \omega.t \ll \frac{4.\pi}{3} \\
 *
 * \frac{3}{2} \left | \overrightarrow{V_{\alpha\beta}} \right | \cos(\omega.t)
 * , & \mbox{if } \frac{4.\pi}{3} \ll \omega.t \le \frac{5.\pi}{3} \\
 *
 * \frac{\sqrt{3}}{2} \left | \overrightarrow{V_{\alpha\beta}} \right | \cos(\omega.t+\frac{\pi}{3})
 * , & \mbox{if } \frac{5.\pi}{3} \ll \omega.t \le 2.\pi
 *
 * \end{cases}
 * \\
 * V_b(\omega.t) & = & V_a(\omega.t - \frac{2.\pi}{3}) \\
 * V_c(\omega.t) & = & V_a(\omega.t + \frac{2.\pi}{3})
 *
 * \end{array}
 *
 * \f$
 *
 * And the following line to line voltages:
 *
 * \f$
 * \begin{array}{lcl}
 * V_{ab}(\omega.t) & = & \sqrt{3} \left | \overrightarrow{V_{\alpha\beta}} \sin(\omega.t+\frac{\pi}{3}) \right | \\
 * V_{bc}(\omega.t) & = & V_{ab}(\omega.t - \frac{2.\pi}{3}) \\
 * V_{ca}(\omega.t) & = & V_{ab}(\omega.t + \frac{2.\pi}{3})
 *
 * \end{array}
 *
 * \f$
 *
 * @section section_limitation Continuous and discontinuous SVM
 * The range available for the continuous space vector modulation, is represented by the
 * disc inscribe into the hexagon, and correspond to a modulation index of
 * 0.906% (\f$ \frac{\pi}{2\sqrt{3}}\f$), because the output voltage is limited by the
 * DC-link voltage. The total hexagon area can still be used for saturated
 * space vector modulation but introduces more harmonics.
 *
 * In the continuous domain, the maximum fundamental phase voltage that can be produced
 * by the inverter for a given DC link voltage is \f$ V_{max} = \frac{2.V_{dc}}{\pi}\f$.
 *
 * @image html "Svpwm-Continuous.gif" "Continuous vs. discontinuous area"
 *
 *
 * @sourcecode @ref motor_control_svpwm
 *
 * @prevnext{page_src_PARK_H,@lnk_next_page_src_SPACE_VECTOR_MODULATION_H}
 * @endif
 */


#if !defined(SPACE_VECTOR_MODULATION_H)
#define SPACE_VECTOR_MODULATION_H
//------------------------------------------------------------------------------
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "Arith.StdReal.h"
//------------------------------------------------------------------------------
#if(1)
uint8 SpaceVectorModulation(CplxStdReal m, Ifx_TimerValue period, Ifx_TimerValue *  tOn);
#else
 uint8 SpaceVectorModulation(CplxStdReal m, Ifx_TimerValue period, Ifx_TimerValue *  tOn,Ifx_TimerValue *  tshift);
#endif
CplxStdReal SpaceVectorModulation_GetVoltages(CplxStdReal m, StdReal vdc);
//------------------------------------------------------------------------------
#endif


