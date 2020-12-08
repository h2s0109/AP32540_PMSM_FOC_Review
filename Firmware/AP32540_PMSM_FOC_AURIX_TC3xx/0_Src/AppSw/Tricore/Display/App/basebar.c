/**
 * \file basebar.c
 * \brief Source file for our basebar on each display
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "Cpu/Std/Ifx_Types.h"
#include "conio_tft.h"
#include "touch.h"

/******************************************************************************/
/*------------------------Inline Function Prototypes--------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
void bar_select_menu (sint32 ind, TDISPLAYENTRY * pdisplayentry);
void bar_select_stdout0 (sint32 ind, TDISPLAYENTRY * pdisplayentry);
void bar_select_stdout1 (sint32 ind, TDISPLAYENTRY * pdisplayentry);
void bar_select_graph0 (sint32 ind, TDISPLAYENTRY * pdisplayentry);
void bar_select_off (sint32 ind, TDISPLAYENTRY * pdisplayentry);
sint32 bar_input (sint32 ind, TDISPLAYENTRY * pdisplayentry);

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
// *INDENT-OFF*
const TDISPLAYENTRY stdlist[6] = {
  {(CYAN << 4) | BLACK, (BLACK << 4) | YELLOW, 0, 6, (TERMINAL_MAXY-1), &bar_select_menu, 0, &bar_input, " iMENU "},
  {(CYAN << 4) | BLACK, (BLACK << 4) | YELLOW, 8, 16, (TERMINAL_MAXY-1), &bar_select_stdout0, 0, &bar_input, " STDOUT0 "},
 // {(CYAN << 4) | BLACK, (BLACK << 4) | YELLOW, 18, 26, (TERMINAL_MAXY-1), &bar_select_stdout1, 0, &bar_input, " STDOUT1 "},
 // {(CYAN << 4) | BLACK, (BLACK << 4) | YELLOW, 28, 35, (TERMINAL_MAXY-1), &bar_select_graph0, 0, &bar_input, " GRAPH0 "},
 // {(CYAN << 4) | BLACK, (BLACK << 4) | YELLOW, 37, 40, (TERMINAL_MAXY-1), &bar_select_off, 0, &bar_input, "OFF"},
  {0, 0, 0, 0, 0, 0, 0, 0, " "}
};
// *INDENT-ON*
/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
void bar_select_menu (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    conio_ascii_textattr (DISPLAYBAR, pdisplayentry->color_select);
    conio_ascii_gotoxy (DISPLAYBAR, pdisplayentry->xmin, 0);
    conio_ascii_cputs (DISPLAYBAR, &pdisplayentry->text[0]);
    if ((touch_driver.touchmode & MASK_TOUCH_UP) != 0)
    {
        conio_driver.displaymode = DISPLAYMENU; //Menu
        touch_driver.touchmode &= ~MASK_TOUCH_UP;   //clear
    }
}

void bar_select_stdout0 (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    conio_ascii_textattr (DISPLAYBAR, pdisplayentry->color_select);
    conio_ascii_gotoxy (DISPLAYBAR, pdisplayentry->xmin, 0);
    conio_ascii_cputs (DISPLAYBAR, &pdisplayentry->text[0]);
    if ((touch_driver.touchmode & MASK_TOUCH_UP) != 0)
    {
        conio_driver.displaymode = DISPLAYSTDOUT0;  //stdout0
        touch_driver.touchmode &= ~MASK_TOUCH_UP;   //clear
    }
}

void bar_select_stdout1 (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    conio_ascii_textattr (DISPLAYBAR, pdisplayentry->color_select);
    conio_ascii_gotoxy (DISPLAYBAR, pdisplayentry->xmin, 0);
    conio_ascii_cputs (DISPLAYBAR, &pdisplayentry->text[0]);
    if ((touch_driver.touchmode & MASK_TOUCH_UP) != 0)
    {
        conio_driver.displaymode = DISPLAYSTDOUT1;  //stdout1
        touch_driver.touchmode &= ~MASK_TOUCH_UP;   //clear
    }
}

void bar_select_graph0 (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    conio_ascii_textattr (DISPLAYBAR, pdisplayentry->color_select);
    conio_ascii_gotoxy (DISPLAYBAR, pdisplayentry->xmin, 0);
    conio_ascii_cputs (DISPLAYBAR, &pdisplayentry->text[0]);
    if ((touch_driver.touchmode & MASK_TOUCH_UP) != 0)
    {
        conio_driver.displaymode = DISPLAYGRAPHICS0;    //graph0
        touch_driver.touchmode &= ~MASK_TOUCH_UP;   //clear
    }
}

void bar_select_off (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    conio_ascii_textattr (DISPLAYBAR, pdisplayentry->color_select);
    conio_ascii_gotoxy (DISPLAYBAR, pdisplayentry->xmin, 0);
    conio_ascii_cputs (DISPLAYBAR, &pdisplayentry->text[0]);
    if ((touch_driver.touchmode & MASK_TOUCH_UP) != 0)
    {
//        conio_driver.dialogmode = SWITCHOFFON;    //open confirmation window for switchoff
        // we switch to display menu if we are in graphics
        if (conio_driver.displaymode == DISPLAYGRAPHICS0)
            conio_driver.displaymode = DISPLAYMENU; //Menu
        touch_driver.touchmode &= ~MASK_TOUCH_UP;   //clear
    }
}

sint32 bar_input (sint32 ind, TDISPLAYENTRY * pdisplayentry)
{
    __debug ();
    return (0);
}
