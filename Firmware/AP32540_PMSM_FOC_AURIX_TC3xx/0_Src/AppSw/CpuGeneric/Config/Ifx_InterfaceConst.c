/**
 * \file Ifx_InterfaceConst.c
 * \brief Interface constants to provide the indirection pointers to data shared with external devices
 * \ingroup
 *
 *
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
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
#include "Platform_Types.h"
#include "conio_tft.h"
#include "touch.h"

#if defined(__HIGHTEC__)
#pragma section
#pragma section ".interface_const"
#endif
#if defined(__TASKING__)
#pragma section farrom "interface_const"
#pragma protect
#endif
#if defined(__DCC__)
#pragma section CONST ".interface_const" far-absolute R
#endif

extern TCONIO_DRIVER conio_driver;
extern TTOUCH_DASINFO touch_dasinfo;


volatile const uint32 Ifx_interfaceConst[] = {
    /*Address:80000020 */ 0x00000000,
    /*Project info to be used */
    /*Address:80000024 */ 0x00000000,
    /*Project info to be used */
    /*Address:80000028 */ 0x00000000,
    /*Address:8000002C */ 0x00000000,
    /*Address:80000030 */ 0x00000000,
    /*Address:80000034 */ 0x00000000,
    /*Address:80000038 */ 0x00000000,
    /*Address:8000003C */ 0x00000000,
    /*Address:80000040 */ 0x00000000,
    /*Address:80000044 */ 0x00000000,
    /*Address:80000048 */ 0x00000000,
#ifdef TFT_OVER_DAS
    /*Pointer TFT display */
    /*Address:8000004C */ (uint32)&conio_driver,
    /*Address:80000050 */ (uint32)&conio_driver.dasdisplaymode,
    /*Address:80000054 */ (uint32)&conio_driver.dasstatus,
    /*Address:80000058 */ (uint32)&conio_driver.pdasmirror,
    /*Address:8000005C */ (uint32)&touch_dasinfo,
#else
    /*Address:8000004C */ 0x00000000,
    /*Address:80000050 */ 0x00000000,
    /*Address:80000054 */ 0x00000000,
    /*Address:80000058 */ 0x00000000,
    /*Address:8000005C */ 0x00000000,
#endif
    /*Address:80000060 */ 0x00000000,
    /*Address:80000064 */ 0x00000000,
    /*Address:80000068 */ 0x00000000,
    /*Address:8000006C */ 0x00000000,
    /*Address:80000070 */ 0x00000000,
    /*Address:80000074 */ 0x00000000,
    /*Address:80000078 */ 0x00000000,
    /*Address:8000007C */ 0x00000000,
    /*Address:80000080 */ 0x00000000,
    /*Address:80000084 */ 0x00000000,
    /*Address:80000088 */ 0x00000000,
    /*Address:8000008C */ 0x00000000,
    /*Address:80000090 */ 0x00000000,
    /*Address:80000094 */ 0x00000000,
    /*Address:80000098 */ 0x00000000,
    /*Address:8000009C */ 0x00000000,
    /*Address:800000A0 */ 0x00000000,
    /*Address:800000A4 */ 0x00000000,
    /*Address:800000A8 */ 0x00000000,
    /*Address:800000AC */ 0x00000000,
    /*Address:800000B0 */ 0x00000000,
    /*Address:800000B4 */ 0x00000000,
    /*Address:800000B8 */ 0x00000000,
    /*Address:800000BC */ 0x00000000,
    /*Address:800000C0 */ 0x00000000,
    /*Address:800000C4 */ 0x00000000,
    /*Address:800000C8 */ 0x00000000,
    /*Address:800000CC */ 0x00000000,
    /*Address:800000D0 */ 0x00000000,
    /*Address:800000D4 */ 0x00000000,
    /*Address:800000D8 */ 0x00000000,
    /*Address:800000DC */ 0x00000000,
    /*Address:800000E0 */ 0x00000000,
    /*Address:800000E4 */ 0x00000000,
    /*Address:800000E8 */ 0x00000000,
    /*Address:800000EC */ 0x00000000,
    /*Address:800000F0 */ 0x00000000,
    /*Address:800000F4 */ 0x00000000,
    /*Address:800000F8 */ 0x00000000,
    /*Address:800000FC */ 0x00000000
};

#if defined(__HIGHTEC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma endprotect
#endif

