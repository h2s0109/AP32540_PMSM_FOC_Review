/**
 * \file showalarm.c
 * \brief Source file for alarm dialog (if alarm occurred)
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

#if GENERAL_TFTKIT
#include <Cpu/Std/Ifx_Types.h>
#include "Configuration.h"
#include "conio_tft.h"
#include "touch.h"
#include "RTC.h"
#include "Beeper.h"

/******************************************************************************/
/*------------------------Inline Function Prototypes--------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/
#define SHOWALARM_BUTTONS   2

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
void showalarm_display (sint32 ind, TDISPLAYENTRY * pdisplayentry);
sint32 showalarm_input (sint32 ind, TDISPLAYENTRY * pdisplayentry);
void showalarm_select_reset (sint32 ind, TDISPLAYENTRY * pdisplayentry);      //special call back for reset the alarm
void showalarm_select_ignore (sint32 ind, TDISPLAYENTRY * pdisplayentry);  //special call back for ignore the alarm

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/
// *INDENT-OFF*
const uint8 showalarm_outline[9][30] = {
{0xDA,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xBF},
{0xB3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB3},
{0xB3,0x00, 'R', ' ', 'T', ' ', 'C', ' ', ' ',  'A', ' ', 'L', ' ', 'A', ' ', 'R', ' ', 'M', ' ','A', ' ', 'C', ' ', 'T', ' ', 'I', ' ', 'V',0x00,0xB3},
{0xB3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB3},
{0xB3,0x00,0x00,0xDA,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xBF,0x00,0x00,0x00,0xDA,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xBF,0x00,0x00,0xB3},
{0xB3,0x00,0x00,0xB3,0x00,0x00, 'R', 'E', 'S', 'E', 'T',0x00,0x00,0xB3,0x00,0x00,0x00,0xB3,0x00, 'I', 'G', 'N', 'O', 'R', 'E',0x00,0xB3,0x00,0x00,0xB3},
{0xB3,0x00,0x00,0xC0,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xD9,0x00,0x00,0x00,0xC0,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xD9,0x00,0x00,0xB3},
{0xB3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB3},
{0xC0,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xC4,0xD9}
};



const TDISPLAYENTRY showalarmlist[SHOWALARM_BUTTONS] = {
{(COLOR_RED << 4) | COLOR_BLACK, (COLOR_BLACK << 4) | COLOR_YELLOW, 9, 17, 10, &showalarm_select_reset, &showalarm_display, &showalarm_input,"", 0x0},
{(COLOR_RED << 4) | COLOR_BLACK, (COLOR_BLACK << 4) | COLOR_YELLOW, 23, 30, 10, &showalarm_select_ignore, &showalarm_display, &showalarm_input,"", 0x0}
};
// *INDENT-ON*
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
uint32 periodic_count = 0;

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/



void showalarm_display (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    sint32 j;
    for (j = showalarmlist[ind].xmin; j <= showalarmlist[ind].xmax; j += 1)
    {
        conio_ascii_gotoxy (conio_driver.displaymode, j, showalarmlist[ind].y);
        conio_ascii_textchangecolor (conio_driver.displaymode, showalarmlist[ind].color_display);
    }
}

sint32 showalarm_input (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    __debug ();
    return (0);
}

void showalarm_select_reset (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    uint32 j;
    for (j = showalarmlist[ind].xmin; j <= showalarmlist[ind].xmax; j += 1)
    {
        conio_ascii_gotoxy (conio_driver.displaymode, j, showalarmlist[ind].y);
        conio_ascii_textchangecolor (conio_driver.displaymode, showalarmlist[ind].color_select);
    }
    if ((touch_driver.touchmode & MASK_TOUCH_UP) != 0)
    {
        touch_driver.touchmode &= ~MASK_TOUCH_UP;   //clear
        conio_driver.dialogmode = DIALOGOFF;
        beeper_off();
        rtc_alarm_onoff(0, 0);
        rtc_reset_alarmflag (0);
        display_ascii_clrscr(conio_driver.displaymode);
        touch_event.status = TOUCH_UP; // reset touch status to the correct last status
    }
}

void showalarm_select_ignore (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    uint32 j;
    for (j = showalarmlist[ind].xmin; j <= showalarmlist[ind].xmax; j += 1)
    {
        conio_ascii_gotoxy (conio_driver.displaymode, j, showalarmlist[ind].y);
        conio_ascii_textchangecolor (conio_driver.displaymode, showalarmlist[ind].color_select);
    }
    if ((touch_driver.touchmode & MASK_TOUCH_UP) != 0)
    {
        touch_driver.touchmode &= ~MASK_TOUCH_UP;   //clear
        conio_driver.dialogmode = DIALOGOFF;
        beeper_off();
        conio_ascii_clrscr(conio_driver.displaymode);
        touch_event.status = TOUCH_UP; // reset touch status to the correct last status
    }
}

void showalarm (sint16 x, sint16 y)
{
    sint32 i, j;
    periodic_count++;
    touch_event.status = TOUCH_MOVE; // this is needed that our backlight will be switched on
    conio_ascii_textcolor (DISPLAYMENU, COLOR_BLACK);
    if (periodic_count & 0x4)
    {
    	conio_ascii_textbackground (DISPLAYMENU, COLOR_RED);
        beeper_on();
    }
    else
    {
    	conio_ascii_textbackground (DISPLAYMENU, COLOR_LIGHTRED);
        beeper_off();
    }
    for (j = 0; j < 9; j += 1)
    {
        conio_ascii_gotoxy (conio_driver.displaymode, 5, 5+j);
        for (i = 0; i < 30; i += 1)
        {
            conio_ascii_putch (conio_driver.displaymode, showalarm_outline[j][i]);
        }
    }
    conio_ascii_gotoxy (conio_driver.displaymode, 5, 0);
    /* for all buttons */
    for (i = 0; i < SHOWALARM_BUTTONS; i += 1)
    {
        if ((x >= showalarmlist[i].xmin) && (x <= showalarmlist[i].xmax) && (y == showalarmlist[i].y))
        {
        	showalarmlist[i].select (i, (struct DISPLAYENTRY *) &showalarmlist[i]);
        }
        else
        {
        	showalarmlist[i].display (i, (struct DISPLAYENTRY *) &showalarmlist[i]);
        }
    }
}
#endif /* End of GENERAL_TFTKIT */
