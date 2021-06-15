/**
 * \file tft_app.c
 * \brief Source file for the TFT application
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
#include <Src/Std/IfxSrc.h>
#include <_Impl/IfxCpu_cfg.h>
#if GENERAL_TFTKIT
#include "Configuration.h"
#include "ConfigurationIsr.h"
#endif
#include "Display_Cfg_AppKitTft_TC387A.h"
#include "conio_tft.h"
#include "touch.h"
#if GENERAL_TFTKIT
//#include "main_appl.h"
#include "Rtc.h"
#endif
#include <stdio.h>


/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/
//typedef uint8 TDISPLAY_GRAPHICS0[GRAPHICSWIDTH/4];    //4 color
typedef uint8 TDISPLAY_GRAPHICS0[GRAPHICSWIDTH/2];      //16 color
//typedef uint8 TDISPLAY_GRAPHICS0[GRAPHICSWIDTH];        //256 color
//typedef uint8 TDISPLAY_GRAPHICS1[GRAPHICSWIDTH];        //256 color

#ifdef TFT_OVER_DAS
#if (!defined(DAS_BUFFER_LEN))
//#define DAS_BUFFER_LEN (TCOLORTABLEASCII_SIZE * 2 + 2* TERMINAL_MAXX + TCOLORTABLE_SIZE * 2+ (GRAPHICSWIDTH / 1))   //maximum information
#define DAS_BUFFER_LEN (TCOLORTABLEASCII_SIZE * 2 + 2* TERMINAL_MAXX + TCOLORTABLE_SIZE * 2 + (GRAPHICSWIDTH / 2))  //maximum information
//#define DAS_BUFFER_LEN (TCOLORTABLEASCII_SIZE * 2 + 2* TERMINAL_MAXX + TCOLORTABLE_SIZE * 2+ (GRAPHICSWIDTH / 4))   //maximum information
#endif
#endif

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

extern void keyboard (sint16 x, sint16 y);
#if GENERAL_TFTKIT
extern void switchoff (sint16 x, sint16 y);
extern void showalarm (sint16 x, sint16 y);
extern void set_time (sint16 x, sint16 y);
extern void set_alarmtime (sint16 x, sint16 y);

extern void slideshow_periodic (void);
extern uint32 start_slideshow(void);
extern void stop_slideshow(void);
#endif /* End of GENERAL_TFTKIT */
/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
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

TCONTROLMENU controlmenu;

extern TTOUCH_DRIVER touch_driver;
extern TCONIO_DRIVER conio_driver;

extern const TDISPLAYENTRY menulist[];
extern const TDISPLAYENTRY stdlist[];

TDISPLAY_GRAPHICS0 display_graphics0 IFX_ALIGN(4);

TDISPLAY display_stdout0 IFX_ALIGN(4);
TDISPLAYCOLOR displaycolor_stdout0 IFX_ALIGN(4);
TDISPLAY display_stdout1 IFX_ALIGN(4);
TDISPLAYCOLOR displaycolor_stdout1 IFX_ALIGN(4);
TDISPLAYBAR display_bar IFX_ALIGN(4);
TDISPLAYBARCOLOR displaycolor_bar IFX_ALIGN(4);
TDISPLAY display_menu IFX_ALIGN(4);
TDISPLAYCOLOR displaycolor_menu IFX_ALIGN(4);
volatile boolean tft_ready = 0;

#ifdef TFT_OVER_DAS
#if DAS_VAR_LOCATION == 0
    #if defined(__GNUC__)
    #pragma section // end bss section
    #pragma section ".bss_cpu0" awc0
    #endif
    #if defined(__TASKING__)
    #pragma section farbss  "bss_cpu0"
    #pragma section fardata "data_cpu0"
    #pragma section farrom  "rodata_cpu0"
    #endif
    #if defined(__DCC__)
    #pragma section DATA ".data_cpu0" ".bss_cpu0" far-absolute RW
    #pragma section CONST ".rodata_cpu0"
    #endif
    #if defined(__ghs__)
    #pragma ghs section bss= ".bss_cpu0"
    #pragma ghs section data=".data_cpu0"
    #pragma ghs section rodata=".rodata_cpu0"
    #endif
#elif ((DAS_VAR_LOCATION == 1) && (DAS_VAR_LOCATION < IFXCPU_NUM_MODULES))
    #if defined(__GNUC__)
    #pragma section // end bss section
    #pragma section ".bss_cpu1" awc1
    #endif
    #if defined(__TASKING__)
    #pragma section farbss  "bss_cpu1"
    #pragma section fardata "data_cpu1"
    #pragma section farrom  "rodata_cpu1"
    #endif
    #if defined(__DCC__)
    #pragma section DATA ".data_cpu1" ".bss_cpu1" far-absolute RW
    #pragma section CONST ".rodata_cpu1"
    #endif
    #if defined(__ghs__)
    #pragma ghs section bss= ".bss_cpu1"
    #pragma ghs section data=".data_cpu1"
    #pragma ghs section rodata=".rodata_cpu1"
    #endif
#elif ((DAS_VAR_LOCATION == 2) && (DAS_VAR_LOCATION < IFXCPU_NUM_MODULES))
    #if defined(__GNUC__)
    #pragma section // end bss section
    #pragma section ".bss_cpu2" awc2
    #endif
    #if defined(__TASKING__)
    #pragma section farbss  "bss_cpu2"
    #pragma section fardata "data_cpu2"
    #pragma section farrom  "rodata_cpu2"
    #pragma section CONST ".rodata_cpu2"
    #endif
    #if defined(__DCC__)
    #pragma section DATA ".data_cpu2" ".bss_cpu2" far-absolute RW
    #endif
    #if defined(__ghs__)
    #pragma ghs section bss= ".bss_cpu2"
    #pragma ghs section data=".data_cpu2"
    #pragma ghs section rodata=".rodata_cpu2"
    #endif
#elif ((DAS_VAR_LOCATION == 3) && (DAS_VAR_LOCATION < IFXCPU_NUM_MODULES))
	#if defined(__GNUC__)
    #pragma section // end bss section
	#pragma section ".bss_cpu3" awc3
	#endif
	#if defined(__TASKING__)
    #pragma section farbss  "bss_cpu3"
    #pragma section fardata "data_cpu3"
    #pragma section farrom  "rodata_cpu3"
	#endif
	#if defined(__DCC__)
	#pragma section DATA ".data_cpu3" ".bss_cpu3" far-absolute RW
    #pragma section CONST ".rodata_cpu3"
	#endif
    #if defined(__ghs__)
    #pragma ghs section bss= ".bss_cpu3"
    #pragma ghs section data=".data_cpu3"
    #pragma ghs section rodata=".rodata_cpu3"
    #endif
#elif ((DAS_VAR_LOCATION == 4) && (DAS_VAR_LOCATION < IFXCPU_NUM_MODULES))
	#if defined(__GNUC__)
    #pragma section // end bss section
	#pragma section ".bss_cpu4" awc4
	#endif
	#if defined(__TASKING__)
    #pragma section farbss  "bss_cpu4"
    #pragma section fardata "data_cpu4"
    #pragma section farrom  "rodata_cpu4"
	#endif
	#if defined(__DCC__)
	#pragma section DATA ".data_cpu4" ".bss_cpu4" far-absolute RW
    #pragma section CONST ".rodata_cpu4"
	#endif
    #if defined(__ghs__)
    #pragma ghs section bss= ".bss_cpu4"
    #pragma ghs section data=".data_cpu4"
    #pragma ghs section rodata=".rodata_cpu4"
    #endif
#elif ((DAS_VAR_LOCATION == 5) && (DAS_VAR_LOCATION < IFXCPU_NUM_MODULES))
	#if defined(__GNUC__)
    #pragma section // end bss section
	#pragma section ".bss_cpu5" awc5
	#endif
	#if defined(__TASKING__)
    #pragma section farbss  "bss_cpu5"
    #pragma section fardata "data_cpu5"
    #pragma section farrom  "rodata_cpu5"
	#endif
	#if defined(__DCC__)
	#pragma section DATA ".data_cpu5" ".bss_cpu5" far-absolute RW
    #pragma section CONST ".rodata_cpu5"
	#endif
    #if defined(__ghs__)
    #pragma ghs section bss= ".bss_cpu5"
    #pragma ghs section data=".data_cpu5"
    #pragma ghs section rodata=".rodata_cpu5"
    #endif
#else
#error "Set DAS_VAR_LOCATION to a valid value!"
#endif

uint32 das_buffer[DAS_BUFFER_LEN >> 2];

#endif

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/
#if defined(__GNUC__)
    #pragma section // end bss section
    #if CPU_WHICH_SERVICE_TFT == 0
    #pragma section ".rodata_cpu0" ac0
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 1) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".rodata_cpu1" ac1
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 2) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".rodata_cpu2" ac2
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 3) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".rodata_cpu3" ac3
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 4) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".rodata_cpu4" ac4
    #endif
    #if ((CPU_WHICH_SERVICE_TFT == 5) && (CPU_WHICH_SERVICE_TFT < IFXCPU_NUM_MODULES))
    #pragma section ".rodata_cpu5" ac5
    #endif
#endif
const TCONIODLGENTRY conio_dialog_list[CONIO_DLG_ENTRIES] =
{
    { KEYBOARDON, &keyboard }
    // { KEYBOARDON, &keyboard },
    // { SWITCHOFFON, &switchoff },
    // { SHOWALARMON, &showalarm },
    // { SETTIMEON, &set_time },
    // { SETALARMTIME, &set_alarmtime }
};

const TCONIODMENTRY conio_displaymode_list[CONIO_MAXDISPLAYS] =
{
    { DISPLAYBAR, {(uint8 *) & display_bar, (uint8 *) & displaycolor_bar, TEXTMODE, COLOR_WHITE, TERMINAL_MAXX, 1, 0, 0} },
    { DISPLAYMENU, {(uint8 *) & display_menu, (uint8 *) & displaycolor_menu, TEXTMODE, COLOR_WHITE, TERMINAL_MAXX, TERMINAL_MAXY-1, 0, 0} },
    { DISPLAYSTDOUT0, {(uint8 *) & display_stdout0, (uint8 *) & displaycolor_stdout0, TEXTMODE, COLOR_WHITE, TERMINAL_MAXX, TERMINAL_MAXY-1, 0, 0} },
    { DISPLAYSTDOUT1, {(uint8 *) & display_stdout1, (uint8 *) & displaycolor_stdout1, TEXTMODE, COLOR_WHITE, TERMINAL_MAXX, TERMINAL_MAXY-1, 0, 0} },
    { DISPLAYGRAPHICS0, {(uint8 *) & display_graphics0, 0, GRAPHICMODE_16COLOR, COLOR_WHITE, TERMINAL_MAXX, TERMINAL_MAXY, 0, 0} }
};

#if defined(__GNUC__)
    #pragma section // end rodata section
#endif

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
/** \brief TFT application init
 *
 * This function initialises the TFT display via QSPI in master mode.
 */
void tft_appl_init (void)
{
    #if GENERAL_TFTKIT
    /* setup our general interrupt to call the tft routines periodically */
	if (CPU_WHICH_SERVICE_TFT)
		IfxSrc_init(&TFT_UPDATE_IRQ, (IfxSrc_Tos)(CPU_WHICH_SERVICE_TFT+1), ISR_PRIORITY_CPUSRV0);
	else
		IfxSrc_init(&TFT_UPDATE_IRQ, (IfxSrc_Tos)CPU_WHICH_SERVICE_TFT, ISR_PRIORITY_CPUSRV0);
    IfxSrc_enable(&TFT_UPDATE_IRQ);
    /* First we check that there is an alarm activ */
    if (IfxPort_getPinState(RTC_ALARM_PIN_INPUT.pin.port,RTC_ALARM_PIN_INPUT.pin.pinIndex) == FALSE) conio_driver.dialogmode = SHOWALARMON;
    else conio_driver.dialogmode = DIALOGOFF;
    /* overwrite the dialog if time need to set, ignore any alarm */
    if (RtcRunning == 0)
    {
    	conio_driver.dialogmode = SETTIMEON;
    	/* call start of RTC calibration */
        rtc_calibration();
    }
    #endif /* End of GENERAL_TFTKIT */
    conio_driver.dialogmode = DIALOGOFF;
    conio_driver.pmenulist = (TDISPLAYENTRY *)&menulist[0];
    conio_driver.pstdlist = (TDISPLAYENTRY *)&stdlist[0];

    tft_init ();                //initializes tft driver+touch driver
    conio_init ((pTCONIODMENTRY)conio_displaymode_list);
#ifdef TFT_OVER_DAS
    conio_driver.pdasmirror = &das_buffer[0];   //a buffer is available for PC sharing
    conio_driver.dasstatus = 0; //we can update
#endif
#if GENERAL_TFTKIT
	// we check that there is a sd card inside
    if (IfxPort_getPinState(SDCARD_USE_CD.port, SDCARD_USE_CD.pinIndex) == FALSE)
	{
        /* first we start the slideshow to make sure that our sdcard is mounted */
    	/* if slideshow can start, then the conio_driver.dialogmode is set to SLIDESHOW */
        if (start_slideshow())
        	/* there is an error, we must stop the slideshow */
        	stop_slideshow();
	}
#endif /* End of GENERAL_TFTKIT */
    controlmenu.cpusecondsdelta = 0.1f;
    tft_ready = TRUE;
}

/** \brief periodic function to get touch values and to change the conio displays
 *
 * This function calls the receive of the actual touch values and change the conio displays.
 */
IFX_INTERRUPT (cpu_service0Irq, CPU_WHICH_SERVICE_TFT, ISR_PRIORITY_CPUSRV0)
{

	__enable();
	if (tft_ready == 0) return;
    touch_periodic ();
    #if GENERAL_TFTKIT
    if (conio_driver.dialogmode == SLIDESHOW) slideshow_periodic();
    else conio_periodic (touch_driver.xdisp, touch_driver.ydisp, conio_driver.pmenulist, conio_driver.pstdlist);
    conio_driver.blinky += 1;
    #endif /* End of GENERAL_TFTKIT */
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
