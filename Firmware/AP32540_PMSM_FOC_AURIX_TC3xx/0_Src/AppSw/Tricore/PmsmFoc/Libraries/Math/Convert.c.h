/**
 * \file Convert.c.h
 * \brief Number conversion functions in C
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
 */

#ifndef MC_CONVERT_C_H
#define MC_CONVERT_C_H

#include "StdReal.h"

/** \brief Convert sint32 to FixPoint32
 *
 * This function converts a value from a sint32 format to a FixPoint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the FixPoint32 format
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE FixPoint32 SInt32_To_FixPoint32(sint32 value, sint32 shift)
{
    sint32 result;

    if ((value & (0xFFFFFFFFUL << shift)) == 0)
    {
        result = value << (31 - shift);
    }
    else
    {
        result = (value < 0) ? -2147483647L : 2147483647L;
    }

    return result;
}


/** \brief Convert FixPoint32 to sint32
 *
 * This function converts a value from a FixPoint32 format to a sint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \see FixPoint32_To_Float32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE sint32 FixPoint32_To_SInt32(FixPoint32 value, sint32 shift)
{
    sint32 result = (*((sint32 *)&value)) >> (31 - shift);

    return result;
}


/** \brief Convert float32 to FixPoint32
 *
 * This function converts a value from a float32 format to a FixPoint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the FixPoint32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE FixPoint32 Float32_To_FixPoint32(float32 value, sint32 shift)
{
    sint32 result;

    value = value * 2147483648.0F / (1U << shift);

    if (value < -2147483648.0F)
    {
        result = -2147483647L;
    }
    else if (value > 2147483647.0F)
    {
        result = 2147483647L;
    }
    else
    {
        result = (sint32)value;
    }

    return result;
}


/** \brief Convert float32 to FixPoint16
 *
 * This function converts a value from a float32 format to a FixPoint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the FixPoint32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE FixPoint16 Float32_To_FixPoint16(float32 value, sint32 shift)
{
    FixPoint16 result;

    value = value * 32768.0F / (1U << shift);

    if (value < -32768.0F)
    {
        result = -32768;
    }
    else if (value > 32767.0F)
    {
        result = 32767;
    }
    else
    {
        result = (FixPoint16)value;
    }

    return result;
}


/** \brief Convert FixPoint32 to float32
 *
 * This function converts a value from a FixPoint32 format to a float32 format.
 *
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the float32 format.
 *
 * \see FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE float32 FixPoint32_To_Float32(FixPoint32 value, sint32 shift)
{
    float32 result = (float32)value;

    result = result * (1U << shift) / 2147483648.0F;
    return result;
}


/** \brief Convert FixPoint16 to float32
 *
 * This function converts a value from a FixPoint32 format to a float32 format.
 *
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the float32 format.
 *
 * \see FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE float32 FixPoint16_To_Float32(FixPoint16 value, sint32 shift)
{
    float32 result = (float32)value;

    result = result * (1U << shift) / 32768.0F;
    return result;
}


/** \brief Convert float32 to sint32
 *
 * This function converts a value from a float32 format to a sint32 format,
 * the result is saturated to a 32 bit signed integer value.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE sint32 Float32_To_SInt32(float32 value)
{
    sint32 result;

    value  = __saturatef(value, -2147483648.0F, 2147483647.0F);
    result = (sint32)value;

    return result;
}


/** \brief Convert sint32 to float32
 *
 * This function converts a value from a sint32 format to a float32 format.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the float32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE float32 SInt32_To_Float32(sint32 value)
{
    return (float32)value;
}


/** \brief Convert float32 to uint32
 *
 * This function converts a value from a float32 format to a uint32 format,
 * the result is saturated to a 32 bit unsigned integer value.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the uint32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE uint32 Float32_To_UInt32(float32 value)
{
    uint32 result;

    value  = __saturatef(value, 0, 4294967295.0F);
    result = (uint32)value;

    return result;
}


/** \brief Convert uint32 to float32
 *
 * This function converts a value from a uint32 format to a float32 format.
 *
 * \param value value to be converted.
 *
 * \return Returns the converted value in the float32 format.
 *
 * \see FixPoint32_To_Float32(), FixPoint32_To_SInt32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE float32 UInt32_To_Float32(uint32 value)
{
    return (float32)value;
}


/** \brief Convert FixPoint32 to FixPoint32
 *
 * This function converts a value from a FixPoint32 format to a FixPoint32 format,
 * taking in account the saturation.
 *
 * the result is saturated to a 32 bit value.
 *
 * \param value value to be converted.
 * \param inputShift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 * \param outputShift position of the fix point. Range = [-32, 31] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the sint32 format.
 *
 * \see FixPoint32_To_Float32(), Float32_To_FixPoint32(),
 * Float32_To_SInt32(), Float32_To_UInt32(), SInt32_To_FixPoint32(), SInt32_To_Float32(),
 * UInt32_To_Float32()
 * \ingroup mod_cpu_convert
 */
IFX_INLINE FixPoint32 FixPoint32_To_FixPoint32(FixPoint32 value, sint32 inputShift, sint32 outputShift)
{
    if (inputShift >= outputShift)
    {
        return value >> (inputShift - outputShift); /* FIXME: saturate to 32-bit */
    }
    else
    {
        return value << (outputShift - inputShift);
    }
}


#endif /* MC_CONVERT_C_H */
