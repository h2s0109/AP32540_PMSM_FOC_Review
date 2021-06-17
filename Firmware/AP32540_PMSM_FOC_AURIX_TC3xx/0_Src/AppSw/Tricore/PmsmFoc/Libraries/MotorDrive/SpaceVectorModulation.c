/**
 * @file SpaceVectorModulation.c
 * @brief Space vector modulation.
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
 *
 * $Revision: 162 $
 * $Date: 2011-04-04 15:43:24 +0200 (Mon, 04 Apr 2011) $
 *
 */

//------------------------------------------------------------------------------

#include "SpaceVectorModulation.h"
#include "Arith.StdReal.h"
#include "Tables.h"
//------------------------------------------------------------------------------
#if !defined(CFG_OPTIMIZE) || (CFG_OPTIMIZE == 0)
/** @brief Space vector modulation.
 *
 * This function returns the "on time" in ticks corresponding to the input vector m for the 3 output channels.
 * The produced voltage is \f$ V = 2 . m . \frac{V_{dc}}{\pi} \f$
 *
 * @param m Specifies the modulation index as a vector. The limit between the continuous and discontinuous mode is defined as follow:
 *  - Continuous mode: \f$ 0 \le \left | m \right | \le 0.906 \f$
 *  - Saturation mode: \f$ 0.906 \ll  \left | m \right | \f$
 * @param Period Specifies the PWM period value in ticks.
 * @param Channels This parameter is filled in by the function with the corresponding "on time" for the 3 output channels. The unit is ticks.
 *
 * @return none
 * @ingroup motor_control_svpwm
 */

#if(1)
uint8 SpaceVectorModulation(CplxStdReal m, Ifx_TimerValue period, Ifx_TimerValue *  tOn)
{
    /* 
    m.real = α
    m.imag = β
    */
    uint8 sector;
    StdReal x;
    Ifx_TimerValue tk, tk1;
    Ifx_TimerValue ts, tm, tb;
    Ifx_TimerValue halfPeriod;
    /* determination of the sector */
    x = __mul_rSR_iSR_iSR(m.imag, (float32)OneOverSqrt3_SR);
    /*  Voltage across  β axis > 0 */
    if (m.imag > 0)
    {   
        /*  Voltage across  α axis > 0 */
        if (m.real > 0)
        {   // Quadrant 1
            /* Check β > Sqrt(3)α */
            if (x < m.real)
            {
                sector=0;
            } 
            else
            {
                sector=1;
            }
        }
        else
        {   // Quadrant 2
            /* Check β > -Sqrt(3)α */
            if (x < __negs_rSR_iSR(m.real))
            {
                sector=2;
            } else
            {
                sector=1;
            }
        }
    }
    else
    {   
        /*  Voltage across  α axis < 0 */
        if (m.real < 0)
        {   // Quadrant 3
            /* Check β > Sqrt(3)α */
            if (x < m.real) 
            {
                sector=4;
            } 
            else    
            {
                sector=3;
            }
        }
        else
        {   // Quadrant 4
            /* Check β > -Sqrt(3)α */
            if (x < __negs_rSR_iSR(m.real))
            {
                sector=4;
            }
            else
            {
                sector=5;
            }
        }
    }
    // Sector range is the Sector number minus 1 (from 0 to 5)
    // Calcul of Tk and Tk+1, k is the sector number
    // Tk=      sin(k)*m.Re     -   Cos(k)*m.Im
    // Tk+1=    Cos(k-1)*m.Im   -   Sin(k-1)*m.Re
    tk  = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector + 1)*2)+0], m.real, sinCosVector[((sector + 1)*2)+1], m.imag), (sint16)period);
    tk1 = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector    )*2)+1], m.imag, sinCosVector[((sector    )*2)+0], m.real), (sint16)period);

    if ((sector & 0x1) != 0)
    {
    	Ifx_TimerValue temp;
        temp = tk;
        tk = tk1;
        tk1 = temp;
    }

    halfPeriod = period >> 1;
    ts = __saturate((halfPeriod  - tk) - tk1, 0, period);
    tm = __saturate((halfPeriod  - tk) + tk1, 0, period);
    tb = __saturate((halfPeriod  + tk) + tk1, 0, period);

    switch (sector)
    {
        case 0:
        	tOn[0] = tb;
        	tOn[1] = tm;
        	tOn[2] = ts;
            break;
        case 1:
        	tOn[0] = tm;
        	tOn[1] = tb;
        	tOn[2] = ts;
            break;
        case 2:
        	tOn[0] = ts;
        	tOn[1] = tb;
        	tOn[2] = tm;
            break;
        case 3:
        	tOn[0] = ts;
        	tOn[1] = tm;
        	tOn[2] = tb;
            break;
        case 4:
        	tOn[0] = tm;
        	tOn[1] = ts;
        	tOn[2] = tb;
            break;
        case 5:
        	tOn[0] = tb;
        	tOn[1] = ts;
        	tOn[2] = tm;
            break;
        default:
            break;
    }


    return(sector);
}
#else
uint8 SpaceVectorModulation(CplxStdReal m, Ifx_TimerValue period, Ifx_TimerValue *  tOn, Ifx_TimerValue *  tshift)
{
    uint8 sector;
    StdReal x;
    Ifx_TimerValue tk, tk1,shift = 0;
    Ifx_TimerValue ts, tm, tb;
    Ifx_TimerValue halfPeriod;

    // determination of the sector
    x = __mul_rSR_iSR_iSR(m.imag, (float32)OneOverSqrt3_SR);
    if (m.imag > 0)
    {   // m.imag>0
        if (m.real > 0)
        {   // Quadrant 1
            if (x < m.real) {sector=0;} else    {sector=1;}
        }
        else
        {   // Quadrant 2
            if (x < __negs_rSR_iSR(m.real)) {sector=2;} else    {sector=1;}
        }
    }
    else
    {   // m.imag<0
        if (m.real < 0)
        {   // Quadrant 3
            if (x < m.real) {sector=4;} else    {sector=3;}
        }
        else
        {   // Quadrant 4
            if (x < __negs_rSR_iSR(m.real)) {sector=4;} else    {sector=5;}
        }
    }
    // Sector range is the Sector number minus 1 (from 0 to 5)
    // Calcul of Tk and Tk+1, k is the sector number
    // Tk=      sin(k)*m.Re     -   Cos(k)*m.Im
    // Tk+1=    Cos(k-1)*m.Im   -   Sin(k-1)*m.Re
    tk  = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector + 1)*2)+0], m.real, sinCosVector[((sector + 1)*2)+1], m.imag), (sint16)period);
    tk1 = __mul_r16I_iSR_i16I(__msubms_rSR_iSR_iSR_iSR_iSR(sinCosVector[((sector    )*2)+1], m.imag, sinCosVector[((sector    )*2)+0], m.real), (sint16)period);

    if ((sector & 0x1) != 0)
    {
    	Ifx_TimerValue temp;
        temp = tk;
        tk = tk1;
        tk1 = temp;
    }
    if(tk < 10)
    {
    	if(tk1 > 10)
    	{
    		shift = (10 - tk);
    	}else
    	{
    		shift = 0;
    	}
    }
    if(tk1<10)
    {
		if(tk > 10)
		{
			shift = (10 - tk1);
		}else
		{
			shift = 0;
		}
	}
//    tk = __maxf(tk,10);
//   tk1 = __maxf(tk1,10);

    halfPeriod = period >> 1;
    ts = __saturate((halfPeriod  - tk) - tk1, 0, period);
    tm = __saturate((halfPeriod  - tk) + tk1, 0, period);
    tb = __saturate((halfPeriod  + tk) + tk1, 0, period);

    switch (sector)
    {
        case 0:
        	tOn[0] = tb;
        	tOn[1] = tm;
        	tOn[2] = ts;
        	tshift[0] = 0;
        	tshift[1] = shift;
        	tshift[2] = 0;
            break;
        case 1:
        	tOn[0] = tm;
        	tOn[1] = tb;
        	tOn[2] = ts;
        	tshift[0] = shift;
			tshift[1] = 0;
			tshift[2] = 0;
            break;
        case 2:
        	tOn[0] = ts;
        	tOn[1] = tb;
        	tOn[2] = tm;
        	tshift[0] = 0;
			tshift[1] = 0;
			tshift[2] = shift;
            break;
        case 3:
        	tOn[0] = ts;
        	tOn[1] = tm;
        	tOn[2] = tb;
        	tshift[0] = 0;
        	tshift[1] = shift;
        	tshift[2] = 0;
            break;
        case 4:
        	tOn[0] = tm;
        	tOn[1] = ts;
        	tOn[2] = tb;
        	tshift[0] = shift;
			tshift[1] = 0;
			tshift[2] = 0;
            break;
        case 5:
        	tOn[0] = tb;
        	tOn[1] = ts;
        	tOn[2] = tm;
        	tshift[0] = 0;
			tshift[1] = 0;
			tshift[2] = shift;
            break;
        default:
            break;
    }
   	tOn[3] = tb;

    return(sector);
}
#endif

#endif
/** @brief Return the reference voltage.
 *
 * The reference voltage is \f$ V_{ref} = 2 . m . \frac{V_{dc}}{\pi} \f$
 *
 * @param m Specifies the modulation index as a vector.
 * @param Vdc Specifies the DC link voltage. The unit is arbitrary, the same unit will be returned by the function
 *
 * @return return the reference voltage. The unit is the same as the Vdc parameter
 * @ingroup motor_control_svpwm
 */
CplxStdReal SpaceVectorModulation_GetVoltages(CplxStdReal m, StdReal vdc)
{
    CplxStdReal vRef;
    StdReal factor = __mul_rSR_iSR_iSR(vdc, (float32)TwoOverPi_SR);
    vRef.real = __mul_rSR_iSR_iSR(m.real, factor);
    vRef.imag = __mul_rSR_iSR_iSR(m.imag, factor);
    return vRef;
}
