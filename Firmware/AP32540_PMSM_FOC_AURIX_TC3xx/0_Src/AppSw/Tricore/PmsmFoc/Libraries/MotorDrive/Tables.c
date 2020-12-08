/**
 * @file tables.c
 * @brief Lookup tables.
 * @license
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
 * $Revision: 162 $
 * $Date: 2011-04-04 15:43:24 +0200 (Mon, 04 Apr 2011) $
 *
 */
#include "Tables.h"
#include "Math.h"



StdReal sinCosVector[14];

#if CONST_LOOKUP_TABLES == 0
#if STD_REAL_TYPE == STD_REAL_FIX_POINT_16
LOOKUP_TABLE uint16 sinCosTable[COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)];
#elif STD_REAL_TYPE == STD_REAL_FIX_POINT_32
LOOKUP_TABLE uint32 sinCosTable[COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)];
#else
LOOKUP_TABLE StdReal sinCosTable[COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)];
#endif
#endif

LOOKUP_TABLE StdReal* cosTable = &(sinCosTable[COSSIN_TABLE_SIZE / 4]);

/*
ArctanTableLow[0..512[  = atan(x) for x = [0, 4[, step = 8 / 512. Factor x=128
ArctanTableHigh[0..512[ = atan(x) for x = [0, 64[, step = 64 / 512. Factor x= 8
*/


#if STD_REAL_TYPE == STD_REAL_FLOAT_32
#define ARCTAN_LIMIT_LOW_SR         ((StdRealLong)ARCTAN_LIMIT_LOW)
#define ARCTAN_LIMIT_HIGH_SR        ((StdRealLong)ARCTAN_LIMIT_HIGH)
#else
#define ARCTAN_LIMIT_LOW_SR         ((StdRealLong)(FORMAT_INT_TO_FIXPOINT32(ARCTAN_LIMIT_LOW / 65536)))    // Format Q16.16
#define ARCTAN_LIMIT_HIGH_SR        ((StdRealLong)(FORMAT_INT_TO_FIXPOINT32(ARCTAN_LIMIT_HIGH / 65536)))    // Format Q16.16

#endif

#if CONST_LOOKUP_TABLES == 0
sint16 arctanTableLow[ARCTAN_TABLE_LOW_SIZE];
sint16 arctanTableHigh[ARCTAN_TABLE_HIGH_SIZE];
#endif

#ifndef OBJECT_NO_INIT
void LookUp_Init(void)
{
    sint32 k;

    for (k = 1; k <= 6; k++)
    {
        sinCosVector[((k-1)*2)]   = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*sin(((k-1)*PI)/3), STD_REAL_SHIFT_Q1_y);
        sinCosVector[((k-1)*2)+1] = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*cos(((k-1)*PI)/3), STD_REAL_SHIFT_Q1_y);
    }
    sinCosVector[12] = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*sin(((1-1)*PI)/3), STD_REAL_SHIFT_Q1_y);
    sinCosVector[13] = FLOAT32_TO_STD_REAL((sqrt(3)/PI)*cos(((1-1)*PI)/3), STD_REAL_SHIFT_Q1_y);

    cosTable = (LOOKUP_TABLE StdReal*) &sinCosTable[COSSIN_TABLE_SIZE / 4];

#if CONST_LOOKUP_TABLES == 0
    for (k = 0; k < (COSSIN_TABLE_SIZE + (COSSIN_TABLE_SIZE / 4)); k++)
    {
        sinCosTable[k] = FLOAT32_TO_STD_REAL(sin((k * 2 * PI) / COSSIN_TABLE_SIZE), STD_REAL_SHIFT_Q1_y);
    }
    {
        float32 Step;
        Step = ARCTAN_LIMIT_LOW / ARCTAN_TABLE_LOW_SIZE;
        for (k = 0; k < ARCTAN_TABLE_LOW_SIZE; k++) 
        {
            arctanTableLow[k] = (sint16)(( (atan(k * Step) / (2.0 * PI)) * (2 * INDEX_PI)));
        }

        Step = ARCTAN_LIMIT_HIGH / ARCTAN_TABLE_HIGH_SIZE;
        for (k = 0; k < ARCTAN_TABLE_HIGH_SIZE; k++) 
        {
            arctanTableHigh[k] = (sint16)(( (atan(k * Step) / (2.0 * PI)) * (2 * INDEX_PI)));
        }

    }
#endif
}
#endif

// return atan(y/x) but also check the quadrant, result range is [0, 2.PI]
sint16 LookUp_Arctan(StdReal x, StdReal y)
{
    sint16 index;

    if ((x < 0) || (x > 0))
    {
        StdRealLong qdiv ;
        StdRealLong abs_div;
        qdiv = __div_rLSR_iSR_iSR(y, x); // Q16.16
        abs_div = __abss_rLSR_iLSR(qdiv);

        if(abs_div < ARCTAN_LIMIT_LOW_SR)
        {
            index = arctanTableLow[__floors_r32I_iLSR(__muls_128_rLSR_iLSR(abs_div), STD_REAL_SHIFT_Q16)];
        }
        else if(abs_div < ARCTAN_LIMIT_HIGH_SR)
        {
            index = arctanTableHigh[__floors_r32I_iLSR(__muls_8_rLSR_iLSR(abs_div), STD_REAL_SHIFT_Q16)];
        }
        else
        {
            index = INDEX_PI / 2;
        }

        if (qdiv < 0)
        {
            index = -index;
        }

        if (x < 0)
        {
            index += INDEX_PI;
        }
        else if (index < 0)
        {
            index += 2 * INDEX_PI;
        }
        else {}
    }
    else
    {
        if (y > 0)
        {
            index = INDEX_PI / 2;
        }
        else
        {
            index = (3 * INDEX_PI) / 2;
        }
    }
    return index;
}
