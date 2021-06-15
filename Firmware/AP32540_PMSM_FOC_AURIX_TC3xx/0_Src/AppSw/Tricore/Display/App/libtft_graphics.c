/**
 * \file libtft_graphics.c
 * \brief Source file for the graphic library we are using with the TFT
 *
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such
 * terms of use are agreed, use of this file is subject to following:


 * Boost Software License - Version 1.0 - August 17th, 2003

 * Permission is hereby granted, free of charge, to any person or
 * organization obtaining a copy of the software and accompanying
 * documentation covered by this license (the "Software") to use, reproduce,
 * display, distribute, execute, and transmit the Software, and to prepare
 * derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:

 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.

 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include <Cpu/Std/Ifx_Types.h>
#include <Cpu/Std/IfxCpu_Intrinsics.h>
#if GENERAL_TFTKIT
#include "Configuration.h"
#endif
#include "Display_Cfg_AppKitTft_TC387A.h"
#include "conio_tft.h"
#include <string.h>
#include <stdio.h>
#include "fifo.h"
#include "IfxCpu_cfg.h"
/******************************************************************************/
/*------------------------Inline Function Prototypes--------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/
#if CPU_WHICH_SERVICE_TFT == 0
    #if defined(__GNUC__)
    #pragma section ".text_cpu0" ax
    #pragma section ".bss_cpu0" awc0
    #endif
    #if defined(__TASKING__)
    #pragma section code    "text_cpu0"
    #pragma section farbss  "bss_cpu0"
    #pragma section fardata "data_cpu0"
    #pragma section farrom  "rodata_cpu0"
    #endif
    #if defined(__DCC__)
    #pragma section CODE ".text_cpu0"
    #pragma section DATA ".data_cpu0" ".bss_cpu0" far-absolute RW
    #pragma section CONST ".rodata_cpu0"
    #endif
    #if defined(__ghs__)
    #pragma ghs section text=".text_cpu0"
    #pragma ghs section bss= ".bss_cpu0"
    #pragma ghs section data=".data_cpu0"
    #pragma ghs section rodata=".rodata_cpu0"
    #endif
#elif ((CPU_WHICH_SERVICE_TFT == 1) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #if defined(__GNUC__)
    #pragma section ".text_cpu1" ax
    #pragma section ".bss_cpu1" awc1
    #endif
    #if defined(__TASKING__)
    #pragma section code    "text_cpu1"
    #pragma section farbss  "bss_cpu1"
    #pragma section fardata "data_cpu1"
    #pragma section farrom  "rodata_cpu1"
    #endif
    #if defined(__DCC__)
    #pragma section CODE ".text_cpu1"
    #pragma section DATA ".data_cpu1" ".bss_cpu1" far-absolute RW
    #pragma section CONST ".rodata_cpu1"
    #endif
    #if defined(__ghs__)
    #pragma ghs section text=".text_cpu1"
    #pragma ghs section bss= ".bss_cpu1"
    #pragma ghs section data=".data_cpu1"
    #pragma ghs section rodata=".rodata_cpu1"
    #endif
#elif ((CPU_WHICH_SERVICE_TFT == 2) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #if defined(__GNUC__)
    #pragma section ".text_cpu2" ax
    #pragma section ".bss_cpu2" awc2
    #endif
    #if defined(__TASKING__)
    #pragma section code    "text_cpu2"
    #pragma section farbss  "bss_cpu2"
    #pragma section fardata "data_cpu2"
    #pragma section farrom  "rodata_cpu2"
    #endif
    #if defined(__DCC__)
    #pragma section CODE ".text_cpu2"
    #pragma section DATA ".data_cpu2" ".bss_cpu2" far-absolute RW
    #pragma section CONST ".rodata_cpu2"
    #endif
    #if defined(__ghs__)
    #pragma ghs section text=".text_cpu2"
    #pragma ghs section bss= ".bss_cpu2"
    #pragma ghs section data=".data_cpu2"
    #pragma ghs section rodata=".rodata_cpu2"
    #endif
#elif ((CPU_WHICH_SERVICE_TFT == 3) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
	#if defined(__GNUC__)
    #pragma section ".text_cpu3" ax
	#pragma section ".bss_cpu3" awc3
	#endif
	#if defined(__TASKING__)
    #pragma section code    "text_cpu3"
    #pragma section farbss  "bss_cpu3"
    #pragma section fardata "data_cpu3"
    #pragma section farrom  "rodata_cpu3"
	#endif
	#if defined(__DCC__)
    #pragma section CODE ".text_cpu3"
	#pragma section DATA ".data_cpu3" ".bss_cpu3" far-absolute RW
    #pragma section CONST ".rodata_cpu3"
	#endif
    #if defined(__ghs__)
    #pragma ghs section text=".text_cpu3"
    #pragma ghs section bss= ".bss_cpu3"
    #pragma ghs section data=".data_cpu3"
    #pragma ghs section rodata=".rodata_cpu3"
    #endif
#elif ((CPU_WHICH_SERVICE_TFT == 4) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
	#if defined(__GNUC__)
    #pragma section ".text_cpu4" ax
	#pragma section ".bss_cpu4" awc4
	#endif
	#if defined(__TASKING__)
    #pragma section code    "text_cpu4"
    #pragma section farbss  "bss_cpu4"
    #pragma section fardata "data_cpu4"
    #pragma section farrom  "rodata_cpu4"
	#endif
	#if defined(__DCC__)
    #pragma section CODE ".text_cpu4"
	#pragma section DATA ".data_cpu4" ".bss_cpu4" far-absolute RW
    #pragma section CONST ".rodata_cpu4"
	#endif
    #if defined(__ghs__)
    #pragma ghs section text=".text_cpu4"
    #pragma ghs section bss= ".bss_cpu4"
    #pragma ghs section data=".data_cpu4"
    #pragma ghs section rodata=".rodata_cpu4"
    #endif
#elif ((CPU_WHICH_SERVICE_TFT == 5) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
	#if defined(__GNUC__)
    #pragma section ".text_cpu5" ax
	#pragma section ".bss_cpu5" awc5
	#endif
	#if defined(__TASKING__)
    #pragma section code    "text_cpu5"
    #pragma section farbss  "bss_cpu5"
    #pragma section fardata "data_cpu5"
    #pragma section farrom  "rodata_cpu5"
	#endif
	#if defined(__DCC__)
    #pragma section CODE ".text_cpu5"
	#pragma section DATA ".data_cpu5" ".bss_cpu5" far-absolute RW
    #pragma section CONST ".rodata_cpu5"
	#endif
    #if defined(__ghs__)
    #pragma ghs section text=".text_cpu5"
    #pragma ghs section bss= ".bss_cpu5"
    #pragma ghs section data=".data_cpu5"
    #pragma ghs section rodata=".rodata_cpu5"
    #endif
#else
#error "Set CPU_WHICH_SERVICE_TFT to a valid value!"
#endif

static TMODE cpy_mode;
static uint8 *cpy_pdisplay;
static uint8 *cpy_pdisplaycolor;

static uint32 YSIZE_cnt;

#if defined(__GNUC__)
    #pragma section // end bss section
    #if CPU_WHICH_SERVICE_TFT == 0
    #pragma section ".data_cpu0" awc0
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 1) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".data_cpu1" awc1
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 2) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".data_cpu2" awc2
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 3) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".data_cpu3" awc3
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 4) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".data_cpu4" awc4
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 5) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".data_cpu5" awc5
    #endif
#endif

TCOLORTABLE colortable_graphics =
{
	COLOR_RGB_BLACK, COLOR_RGB_WHITE, COLOR_RGB_RED, COLOR_RGB_GREEN, COLOR_RGB_BROWN, COLOR_RGB_BLUE, COLOR_RGB_MAGENTA, COLOR_RGB_CYAN,
    COLOR_RGB_LIGHTGRAY, COLOR_RGB_DARKGRAY, COLOR_RGB_LIGHTRED, COLOR_RGB_LIGHTGREEN, COLOR_RGB_YELLOW, COLOR_RGB_LIGHTBLUE,
    COLOR_RGB_LIGHTMAGENTA,
    COLOR_RGB_LIGHTCYAN,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#if defined(__GNUC__)
    #pragma section // end data section
#endif

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
void display_graphics_clrscr (TDISPLAYMODE displaymode)
{
    if (FIFO_DISPLAY_FREE () > 2)
    {
        __disable ();
        PUT_FIFO_DISPLAY (TOKEN_DISPLAY_GRAPHICS_CLRSCR | 0x00020000);
        PUT_FIFO_DISPLAY (displaymode);
        __enable ();

    }
}

void display_graphics_textattr (TDISPLAYMODE displaymode, sint32 color)
{
    if (FIFO_DISPLAY_FREE () > 2)
    {
        __disable ();
        PUT_FIFO_DISPLAY (TOKEN_DISPLAY_GRAPHICS_TEXTATTR | 0x00020000);
        PUT_FIFO_DISPLAY ((displaymode << 16) + color);
        __enable ();

    }
}

void display_graphics_textcolor (TDISPLAYMODE displaymode, sint32 color)
{
    if (FIFO_DISPLAY_FREE () > 2)
    {
        __disable ();
        PUT_FIFO_DISPLAY (TOKEN_DISPLAY_GRAPHICS_TEXTCOLOR | 0x00020000);
        PUT_FIFO_DISPLAY ((displaymode << 16) + color);
        __enable ();
    }
}

void display_graphics_textbackground (TDISPLAYMODE displaymode, sint32 color)
{
    if (FIFO_DISPLAY_FREE () > 2)
    {
        __disable ();
        PUT_FIFO_DISPLAY (TOKEN_DISPLAY_GRAPHICS_TEXTBACKGROUND | 0x00020000);
        PUT_FIFO_DISPLAY ((displaymode << 16) + color);
        __enable ();
    }
}

void display_graphics_gotoxy (TDISPLAYMODE displaymode, sint32 x, sint32 y)
{
    if (FIFO_DISPLAY_FREE () > 3)
    {
        __disable ();
        PUT_FIFO_DISPLAY (TOKEN_DISPLAY_GRAPHICS_GOTOXY | 0x00030000);
        PUT_FIFO_DISPLAY (displaymode);
        PUT_FIFO_DISPLAY ((x << 16) + y);
        __enable ();
    }
}

void display_graphics_cputs (TDISPLAYMODE displaymode, uint8 * s)
{
    sint32 len;
    sint32 i;
    uint32 *pbuf;
    len = strlen ((char *)s);
    if (len > 40)
        len = 40;               //cut it down
    if ((len & 0x03) != 0)
        len = (len | 0x3) + 1;  //always 4byte granaluraty
    len = len >> 2;
    len += 2;
    if (FIFO_DISPLAY_FREE () > len)
    {
        __disable ();
        PUT_FIFO_DISPLAY ((len << 16) + TOKEN_DISPLAY_GRAPHICS_CPUTS);
        PUT_FIFO_DISPLAY ((displaymode << 16));
        pbuf = (uint32 *) & s[0];
        for (i = 0; i < (len - 2); i += 1)
            PUT_FIFO_DISPLAY (pbuf[i]);
        __enable ();

    }
}

void display_graphics_printfxy (TDISPLAYMODE displaymode, sint32 x, sint32 y, const uint8 * format, ...)
{
    sint32 result, len;
    uint8 buffer[80];
    sint32 i;
    uint32 *pbuf;
    va_list ap;
    va_start (ap, format);
    result = vsprintf ((char *)buffer, (char *)format, ap);
    va_end (ap);
    if (result < 0)
        return;
    len = strlen ((char *)buffer) + 1;
    if (len > 40)
        len = 40;               //cut it down
    if ((len & 0x03) != 0)
        len = (len | 0x3) + 1;  //always 4byte granaluraty
    len = len >> 2;
    len += 3;
    if (FIFO_DISPLAY_FREE () > len)
    {
        __disable ();
        PUT_FIFO_DISPLAY ((len << 16) + TOKEN_DISPLAY_GRAPHICS_PRINTFXY);
        PUT_FIFO_DISPLAY (displaymode);
        PUT_FIFO_DISPLAY ((x << 16) + y);
        pbuf = (uint32 *) & buffer[0];
        for (i = 0; i < (len - 3); i += 1)
            PUT_FIFO_DISPLAY (pbuf[i]);
        __enable ();
    }
}

void display_graphics_printf (TDISPLAYMODE displaymode, const uint8 * format, ...)
{
    sint32 result, len;
    uint8 buffer[80];
    sint32 i;
    uint32 *pbuf;
    va_list ap;
    va_start (ap, format);
    result = vsprintf ((char *)buffer, (char *)format, ap);
    va_end (ap);
    if (result < 0)
        return;
    len = strlen ((char *)buffer);
    if (len > 40)
        len = 40;               //cut it down
    if ((len & 0x03) != 0)
        len = (len | 0x3) + 1;  //always 4byte granaluraty
    len = len >> 2;
    len += 2;
    if (FIFO_DISPLAY_FREE () > len)
    {
        __disable ();
        PUT_FIFO_DISPLAY ((len << 16) + TOKEN_DISPLAY_GRAPHICS_PRINTF);
        PUT_FIFO_DISPLAY (displaymode);
        pbuf = (uint32 *) & buffer[0];
        for (i = 0; i < (len - 2); i += 1)
            PUT_FIFO_DISPLAY (pbuf[i]);
        __enable ();
    }
}

void display_graphics_line (TDISPLAYMODE displaymode, sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint8 color)
{
    if (FIFO_DISPLAY_FREE () > 4)
    {
        __disable ();
        PUT_FIFO_DISPLAY (TOKEN_DISPLAY_GRAPHICS_LINE | 0x00040000);
        PUT_FIFO_DISPLAY ((displaymode & 0xFFFF) + (color << 16));
        PUT_FIFO_DISPLAY ((x1 & 0xFFFF) + (y1 << 16));
        PUT_FIFO_DISPLAY ((x2 & 0xFFFF) + (y2 << 16));
        __enable ();
    }
}

/******************************************************************************/
void conio_graphics_setcolortable (uint32 ind, uint32 r, uint32 g, uint32 b)
{
    r = r >> 3;                 //r has only 5bit
    g = g >> 2;                 //g has only 6bit
    b = b >> 3;                 //b has only 5bit

    colortable_graphics[ind] = (r << 11) | (g << 5) | b;
}

void conio_graphics_clrscr (TDISPLAYMODE displaymode)
{
    sint32 i;

    switch (conio_driver.display[displaymode].mode)
    {

    case GRAPHICMODE_2COLOR:
        for (i = 0; i < (GRAPHICSWIDTH / 8); i += 1)
        {
            conio_driver.display[displaymode].pdisplay[i] = 0x0;
        }
        break;
    case GRAPHICMODE_4COLOR:
        for (i = 0; i < (GRAPHICSWIDTH / 4); i += 1)
        {
            conio_driver.display[displaymode].pdisplay[i] = 0x0;
        }
        break;
    case GRAPHICMODE_16COLOR:
        {
            for (i = 0; i < (GRAPHICSWIDTH / 2); i += 1)
            {
                conio_driver.display[displaymode].pdisplay[i] = 0x0;
            }
            break;
        }
    case GRAPHICMODE_256COLOR:
        for (i = 0; i < (GRAPHICSWIDTH); i += 1)
        {
            conio_driver.display[displaymode].pdisplay[i] = 0x0;
        }
        break;
    default:
      	/* This is not a valid graphic display */
        __debug ();
        break;
    }
}

void conio_graphics_textattr (TDISPLAYMODE displaymode, sint32 color)
{
    conio_driver.display[displaymode].color = color;
}


void conio_graphics_textcolor (TDISPLAYMODE displaymode, sint32 color)
{
    conio_driver.display[displaymode].color = (conio_driver.display[displaymode].color & 0xF0) | (color & 0xF);
}

void conio_graphics_textbackground (TDISPLAYMODE displaymode, sint32 color)
{
    conio_driver.display[displaymode].color = (conio_driver.display[displaymode].color & 0xF) | ((color & 0xF) << 4);
}

void conio_graphics_gotoxy (TDISPLAYMODE displaymode, sint32 x, sint32 y)
{
    if ((conio_driver.display[displaymode].mode == RAWMODE) || (conio_driver.display[displaymode].mode == TEXTMODE))
    {
    	/* This is not a graphic display */
    	__debug();
    }
    if (x >= TFT_XSIZE || y >= (TFT_YSIZE - FONT_YSIZE))
        return;
    conio_driver.display[displaymode].x = x;
    conio_driver.display[displaymode].y = y;
}

void conio_graphics_cputs (TDISPLAYMODE displaymode, uint8 * s)
{

    sint32 i = 0;
    if ((conio_driver.display[displaymode].mode == RAWMODE) || (conio_driver.display[displaymode].mode == TEXTMODE))
    {
    	/* This is not a graphic display */
    	__debug();
    }
    while (*s != 0)
    {
        if (s[i] > 0x0D)
        {
            conio_graphics_char (displaymode, conio_driver.display[displaymode].x,
                                 conio_driver.display[displaymode].y, *s++,
                                 conio_driver.display[displaymode].color);
            conio_driver.display[displaymode].x += 8;
            if (conio_driver.display[displaymode].x == TFT_XSIZE)
            {
                conio_driver.display[displaymode].x = 0;
            }
        }
        else
        {
             s++;
        }
    }
}

void conio_graphics_printfxy (TDISPLAYMODE displaymode, sint32 x, sint32 y, const uint8 * format, ...)
{
    sint32 result, len;
    uint8 buffer[80];
    va_list ap;
    va_start (ap, format);
    result = vsprintf ((char *)buffer, (char *)format, ap);
    va_end (ap);
    if (result < 0)
        return;
    len = strlen ((char *)buffer);
    if (len > 40)
        len = 40;               //cut it down

    conio_graphics_gotoxy (displaymode, x, y);
    conio_graphics_cputs (displaymode, &buffer[0]);
}

void conio_graphics_printf (TDISPLAYMODE displaymode, const uint8 * format, ...)
{
    sint32 result, len;
    uint8 buffer[80];
    va_list ap;
    va_start (ap, format);
    result = vsprintf ((char *)buffer, (char *)format, ap);
    va_end (ap);
    if (result < 0)
        return;
    len = strlen ((char *)buffer);
    if (len > 40)
        len = 40;
    conio_graphics_cputs (displaymode, &buffer[0]);
}


inline void conio_graphics_set_opt (TDISPLAYMODE displaymode, sint32 x, sint32 y, uint8 color)
{
    uint8 *video_data;
    sint32 offs;
    video_data = (uint8 *) conio_driver.display[displaymode].pdisplay;
    if (0 > x || x > TFT_XSIZE) ;
    else
    {
        if (0 > y || y > (TFT_YSIZE - FONT_YSIZE)) ;
        else
        {
            switch (conio_driver.display[displaymode].mode)
            {
            case GRAPHICMODE_2COLOR:
                offs = x + y * TFT_XSIZE;
                if (color == 0)
                    video_data[offs >> 3] &= ~(1 << (offs & 0xF));
                else
                    video_data[offs >> 3] |= (1 << (offs & 0xF));
                break;
            case GRAPHICMODE_4COLOR:
                offs = x + y * TFT_XSIZE;
                if ((offs & 0x3) == 0)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0xFC) | (color & 0x03);
                if ((offs & 0x3) == 1)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0xF3) | ((color << 2) & 0x0C);
                if ((offs & 0x3) == 2)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0xCF) | ((color << 4) & 0x30);
                if ((offs & 0x3) == 3)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0x3F) | ((color << 6) & 0xC0);
                break;
            case GRAPHICMODE_16COLOR:
                offs = x + y * TFT_XSIZE;
                if ((offs & 0x1) == 0)
                    video_data[offs >> 1] = (video_data[offs >> 1] & 0xF0) | (color & 0x0F);
                else
                    video_data[offs >> 1] = (video_data[offs >> 1] & 0x0F) | ((color << 4) & 0xF0);
                break;
            case GRAPHICMODE_256COLOR:
                offs = x + y * TFT_XSIZE;
                video_data[offs] = color;
                break;
            default:
              	/* This is not a valid graphic display */
                __debug();
                break;
            }
        }
    }
}

void conio_graphics_line (TDISPLAYMODE displaymode, sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint8 color)
{
    int xofs, yofs, dx,         //deltas
    dy, dx2,                   //scaled deltas
    dy2, ix,                   //increase rate on the x axis
    iy,                        //increase rate on the y axis
    err,                       //the error term
    i;                         //looping variable


    // difference between starting and ending points
    dx = x2 - x1;
    dy = y2 - y1;

    // calculate direction of the vector and store in ix and iy
    if (dx >= 0)
        ix = 1;

    if (dx < 0)
    {
        ix = -1;
        dx = -dx;
    }

    if (dy >= 0)
        //        iy = (pitch >> 1);
        iy = 1;

    if (dy < 0)
    {
        //        iy = -(pitch >> 1);
        iy = -1;
        dy = -dy;
    }

    // scale deltas and store in dx2 and dy2
    dx2 = dx * 2;
    dy2 = dy * 2;
    xofs = 0;
    yofs = 0;
    if (dx > dy)
    {                           // dx is the major axis
        // initialize the error term
        err = dy2 - dx;

        for (i = 0; i <= dx; i++)
        {
            conio_graphics_set_opt (displaymode, x1 + xofs, y1 + yofs, color);
            if (err >= 0)
            {
                err -= dx2;
                //ptr_vid += iy;
                yofs += iy;
            }
            err += dy2;
            //ptr_vid += ix;
            xofs += ix;
        }
    }
    else
    {                           // dy is the major axis
        // initialize the error term
        err = dx2 - dy;

        for (i = 0; i <= dy; i++)
        {
            conio_graphics_set_opt (displaymode, x1 + xofs, y1 + yofs, color);
            if (err >= 0)
            {
                err -= dy2;
                xofs += ix;
            }
            err += dx2;
            //ptr_vid += iy;
            yofs += iy;
        }
    }
}                               // end of Line(...


void conio_graphics_set (TDISPLAYMODE displaymode, sint32 x, sint32 y, uint8 color)
{
    uint8 *video_data;
    sint32 offs;
    video_data = (uint8 *) conio_driver.display[displaymode].pdisplay;
    if (0 > x || x > TFT_XSIZE) ;
    else
    {
        if (0 > y || y > (TFT_YSIZE - FONT_YSIZE)) ;
        else
        {
            switch (conio_driver.display[displaymode].mode)
            {
            case GRAPHICMODE_2COLOR:
                offs = x + y * TFT_XSIZE;
                if (color == 0)
                    video_data[offs >> 3] &= ~(1 << (offs & 0xF));
                else
                    video_data[offs >> 3] |= (1 << (offs & 0xF));
                break;
            case GRAPHICMODE_4COLOR:
                offs = x + y * TFT_XSIZE;
                if ((offs & 0x3) == 0)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0xFC) | (color & 0x03);
                if ((offs & 0x3) == 1)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0xF3) | ((color << 2) & 0x0C);
                if ((offs & 0x3) == 2)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0xCF) | ((color << 4) & 0x30);
                if ((offs & 0x3) == 3)
                    video_data[offs >> 2] = (video_data[offs >> 2] & 0x3F) | ((color << 6) & 0xC0);
                break;
            case GRAPHICMODE_16COLOR:
                offs = x + y * TFT_XSIZE;
                if ((offs & 0x1) == 0)
                    video_data[offs >> 1] = (video_data[offs >> 1] & 0xF0) | (color & 0x0F);
                else
                    video_data[offs >> 1] = (video_data[offs >> 1] & 0x0F) | ((color << 4) & 0xF0);
                break;
            case GRAPHICMODE_256COLOR:
                offs = x + y * TFT_XSIZE;
                video_data[offs] = color;
                break;
            default:
              	/* This is not a valid graphic display */
                __debug ();
                break;
            }
        }
    }
}

// based on graphics display
void conio_graphics_char (TDISPLAYMODE displaymode, sint32 x, sint32 y, uint8 ch, uint8 color)
{
    int i, j, ind;
    uint8 mask;
    {
        ind = ch;
        for (i = 0; i < FONT_YSIZE; i += 1)
        {
            mask = 0x80;
            for (j = 0; j < FONT_XSIZE; j += 1)
            {
                if ((__font_bitmap__8_12[(ind * FONT_YSIZE) + i] & mask) != 0)
                {
                    conio_graphics_set_opt (displaymode, x + j, FONT_YSIZE - i + y, color & 0xF);
                }
                else
                {
                    conio_graphics_set_opt (displaymode, x + j, FONT_YSIZE - i + y, (color & 0xF0) >> 4);
                }
                mask = mask >> 1;
            }
        }
    }
}

static void tft_prepare_graphics_lines (TMODE mode, uint8 * pdisplay, uint8 * pdisplaycolor)
{
    sint32 i, cnt;

    cnt = YSIZE_cnt*TFT_XSIZE;

    switch (mode)
    {
    case GRAPHICMODE_2COLOR:

        for (i = 0; i < TFT_XSIZE * FONT_YSIZE; i++)
        {
            uint8 temp = 0;
            if ((i & 0xF) == 0)
                temp = (pdisplay[cnt >> 1] & 0x01) >> 0;
            else if ((i & 0xF) == 1)
                temp = (pdisplay[cnt >> 1] & 0x02) >> 1;
            else if ((i & 0xF) == 2)
                temp = (pdisplay[cnt >> 1] & 0x04) >> 2;
            else if ((i & 0xF) == 3)
                temp = (pdisplay[cnt >> 1] & 0x08) >> 3;
            else if ((i & 0xF) == 4)
                temp = (pdisplay[cnt >> 1] & 0x10) >> 4;
            else if ((i & 0xF) == 5)
                temp = (pdisplay[cnt >> 1] & 0x20) >> 5;
            else if ((i & 0xF) == 6)
                temp = (pdisplay[cnt >> 1] & 0x40) >> 6;
            else if ((i & 0xF) == 7)
                temp = (pdisplay[cnt >> 1] & 0x80) >> 7;

            Row_Buff[i] = colortable_graphics[temp];
            cnt += 1;
        }
        break;

    case GRAPHICMODE_4COLOR:

        for (i = 0; i < TFT_XSIZE * FONT_YSIZE; i++)
        {
            uint8 temp = 0;
            if ((i & 3) == 0)
                temp = (pdisplay[cnt >> 2] & 0x03) >> 0;
            else if ((i & 3) == 1)
                temp = (pdisplay[cnt >> 2] & 0x0C) >> 2;
            else if ((i & 3) == 2)
                temp = (pdisplay[cnt >> 2] & 0x30) >> 4;
            else if ((i & 3) == 3)
                temp = (pdisplay[cnt >> 2] & 0xC0) >> 6;

            Row_Buff[i] = colortable_graphics[temp];
            cnt += 1;
        }
        break;

    case GRAPHICMODE_16COLOR:
        for (i = 0; i < TFT_XSIZE * FONT_YSIZE; i++)
        {
            uint8 temp = 0;
            if ((i & 1) == 1)
                temp = pdisplay[cnt >> 1] & 0xF;
            else
                temp = (pdisplay[cnt >> 1] & 0xF0) >> 4;

            Row_Buff[i] = colortable_graphics[temp];
            cnt += 1;
        }

        break;

    case GRAPHICMODE_256COLOR:

        for (i = 0; i < TFT_XSIZE * FONT_YSIZE; i++)
        {
            uint8 temp = 0;
            temp = pdisplay[cnt];
            if ((i & 1) == 1)
            	Row_Buff[i-1] = colortable_graphics[temp];
            else
            	Row_Buff[i+1] = colortable_graphics[temp];
            cnt += 1;
        }
        break;
    default:
        break;
    }
}

static uint32 tft_graphics_lines_written(void)
{
    // we prepare the ascii line
	tft_prepare_graphics_lines (cpy_mode, cpy_pdisplay, cpy_pdisplaycolor);

    YSIZE_cnt += FONT_YSIZE;             //ROW counter

    if (YSIZE_cnt > (TFT_YSIZE - 2*FONT_YSIZE))
	{
		// this are our last graphics lines
		// we send the Row_Buff to the display without callback function
	    tft_flush_row_buff( (void *)0, FONT_YSIZE*TERMINAL_MAXX*FONT_XSIZE);
	}
	else
	{
		// this are not our last graphics lines
		// we send the Row_Buff to the display with callback function
	    tft_flush_row_buff( &tft_graphics_lines_written, FONT_YSIZE*TERMINAL_MAXX*FONT_XSIZE);
	}
	return 0;
}

void tft_graphic (TMODE mode, uint8 * pdisplay, uint8 * pdisplaycolor)
{
    //copy values in global variables for tft_prepare_graphics_lines
    cpy_mode = mode;
    cpy_pdisplay = pdisplay;
    cpy_pdisplaycolor = pdisplaycolor;
	// we remove one line from display which is used by bar
	YSIZE_cnt = 0;
	// send the
	tft_graphics_lines_written();
}

#if defined(__GNUC__)
#pragma section // end text section
#endif
#if defined(__TASKING__)
#pragma section code restore
#pragma section fardata restore
#pragma section farbss restore
#pragma section farrom restore
#endif
#if defined(__DCC__)
#pragma section CODE
#pragma section DATA RW
#pragma section CONST
#endif
#if defined(__ghs__)
#pragma ghs section text=default
#pragma ghs section data=default
#pragma ghs section bss=default
#pragma ghs section rodata=default
#endif
