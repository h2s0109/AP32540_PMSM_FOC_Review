/**
 * \file Arith.Integer.h
 * \brief Integer arithmetic library
 *
 * Function naming:
 * __[m][add|sub][m][s]_r<result format>_i<Parameter 1 Format>[_i<...>[_i<Paramter n format>]]
 *     - <result format> : format of the result in the form xI. for example 32 bit value => 32I
 *     - <Parameter n Format> : format of the parameter in the form xI. for example 16 bit value => 16I
 *
 * \note The 16I value must be passed in the lower 16 bits of the data: Value[0..15] = data, Value[16..31] = ignored
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
 * $Revision: $1554.1
 * $Date: $2013-06-26 20:12:46 GMT
 *
 * \defgroup integer_arithmetics Integer arithmetics
 *
 * This module implements Integer arithmetics.
 * \ingroup mod_cpu_arithmetics
 *
 */

#ifndef MC_INTEGER_H
#define MC_INTEGER_H
//------------------------------------------------------------------------------
#include "Cpu/Std/Intrinsics.h"
//------------------------------------------------------------------------------
/** \brief Integer arithmetics: r = Value << Shift;
 * \ingroup integer_arithmetics
 */
IFX_INLINE sint32 __sha_r32I_i32I_i8I(sint32 Value, sint8 Shift)
{
    sint32 Result;

#if !(ARITH_FIX_POINT_OPTIMIZED)

    if (Shift >= 0)
    {
        Result = Value << Shift;
    }
    else
    {
        Result = Value / (1U << -Shift);
    }

#else
    __asm(
        "   sha\t%0, %1, %2  \n"       // Result = Value << Shift
        : "=d" (Result)
        : "d" (Value), "d" (Shift));
#endif
    return Result;
}


/** \brief Expand the sine bit
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \ingroup intrinsic
 */
IFX_INLINE sint32 ExpandSign_SInt32(sint32 value, sint32 shift)
{
    return (value << shift) >> shift;
}


IFX_INLINE FixPoint16 Div_Int16_Int16(sint16 a, sint16 b)
{
    return (FixPoint16)(SInt32_To_FixPoint32(a, 16) / SInt32_To_FixPoint32(b, 16));
}


//------------------------------------------------------------------------------
#endif
