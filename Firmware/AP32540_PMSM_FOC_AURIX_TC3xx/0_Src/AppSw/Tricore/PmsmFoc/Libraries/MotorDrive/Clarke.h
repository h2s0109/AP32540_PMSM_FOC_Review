/**
 * @file Clarke.h
 * @brief Clarke transformation.
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
 * $Revision: 107 $
 * $Date: 2010-06-28 17:35:27 +0200 (Mon, 28 Jun 2010) $
 *
 * @defgroup motor_control_clarke Clarke transformation
 *
 * This module implements the Clarke transformation.
 * @image html "ReferenceFrames.gif"
 * 
 * @note: An assembler optimised version is used if the compiler and assembler 
 * switch CFG_OPTIMIZE is equal to 1. The files Clarke.fixpoint16.opt.asm and 
 * Clarke.float32.opt.asm must be included in the project.
 *
 * @ingroup motor_control
 *
 */

/** @ifnot no_page_src_CLARKE_H
 * @page page_src_CLARKE_H Clarke transformation
 *
 * @image html "Clarke.gif"
 *
 * The Clarke transformation converts the vector coordinates from
 * the three phases system \f$ (a, b, c) \f$ to
 * the two phases system \f$ (\alpha, \beta) \f$ using the following formula:
 *
 * \f$
 *  \begin{bmatrix}
 *  i_{s\alpha} \\
 *  i_{s\beta}
 *  \end{bmatrix}
 *  =
 *  \begin{bmatrix}
 *  i_a \\
 *  \frac{1}{\sqrt{3}}*(i_b-i_c)
 *  \end{bmatrix}
 * \f$.
 *
 * @sourcecode @ref motor_control_clarke
 *
 * @prevnext{page_src_FOC_H,page_src_PARK_H}
 *
 * @endif
 */

#if !defined(CLARKE_H)
#define CLARKE_H
//------------------------------------------------------------------------------
#include "MotorControl.h"
//------------------------------------------------------------------------------

CplxStdReal Clarke(T3Phase *currents);
#endif
