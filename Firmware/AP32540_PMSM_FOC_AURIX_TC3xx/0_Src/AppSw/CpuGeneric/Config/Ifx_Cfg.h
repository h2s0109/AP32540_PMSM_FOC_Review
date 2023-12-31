/**
 * \file Ifx_Cfg.h
 * \brief Project configuration file.
 *
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
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

#ifndef IFX_CFG_H
#define IFX_CFG_H 1
/******************************************************************************/

/*______________________________________________________________________________
** Configuration for IfxScu_cfg.h
**____________________________________________________________________________*/
#define IFX_CFG_SCU_XTAL_FREQUENCY		(20000000)	/**< default supported: 40000000, 25000000, 20000000, 16000000 */
#define IFX_CFG_SCU_PLL_FREQUENCY		(300000000) /**< default supported: 300000000, 200000000, 160000000, 133000000, 80000000 */
#define IFX_CFG_SCU_PLL1_FREQUENCY		(320000000) /**< default supported: 320000000, 160000000 */
#define IFX_CFG_SCU_PLL2_FREQUENCY		(200000000) /**< default supported: 200000000 */

/*______________________________________________________________________________
** Configuration for Software managed interrupt
**____________________________________________________________________________*/

//#define IFX_USE_SW_MANAGED_INT

/*______________________________________________________________________________
** Configuration for Trap Hook Functions' Extensions
**____________________________________________________________________________*/

//#define IFX_CFG_EXTEND_TRAP_HOOKS

/******************************************************************************/
/*______________________________________________________________________________
** Configuration for IfxSdtIf_DPipe.h
**____________________________________________________________________________*/
#    define ENDL                             "\r"
#    define KEY_CR                           "\r"
#define IFX_CFG_STDIF_DPIPE_TIMEOUT (TimeConst_100s) /**<\brief Default DPipe Tx timeout */

/*______________________________________________________________________________
** Configuration for Ifx_Shell.h
**____________________________________________________________________________*/
#define IFX_CFG_SHELL_PROMPT                 ENDL "--------------------------------------------------------------------------------"ENDL "Shell>" /**< \copydoc SHELL_PROMPT */


/*______________________________________________________________________________
** Configuration for Ifx_Osci_Cfg.h
**____________________________________________________________________________*/
#define IFX_OSCI_CFG_MAX_NUM_OF_CHANNELS (10)

/******************************************************************************/

#endif /* IFX_CFG_H */
