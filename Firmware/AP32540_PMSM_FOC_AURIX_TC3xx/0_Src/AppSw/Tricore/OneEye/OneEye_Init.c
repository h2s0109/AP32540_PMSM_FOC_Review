/*
 * \file OneEye_Init.c
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
#include "PmsmFoc_UserConfig.h"
#if(ONE_EYEMODE == ENABLED)
#include "OneEye_Init.h"
#include "IfxAsclin_Asc.h"
#include "Ifx_Shell.h"
#include "Ifx_Osci.h"
#include "Ifx_OsciBb.h"
#include "Ifx_ShellBb.h"
#include "DataStreaming.h"
#include "IfxGlobal_cfg.h"
#include "Ifx_DebugPipe.h"
#include "IfxStdIf_DPipe.h"
#include "PmsmFoc_Interface.h"
#include MCUCARD_TYPE_PATH
#include INVERTERCARD_TYPE_PATH
/******************************************************************************/
/*------------------------------Type Definitions------------------------------*/
/******************************************************************************/
/** \brief Application information */
typedef struct
{

	struct
	{
		IfxAsclin_Asc asc0;                         /**< \brief ASC 0 interface */
		Ifx_Shell       shell;		                /**< \brief Shell driver */
		SyncProtocol bb;
		Ifx_Osci osci;
		Ifx_OsciBb osciBb;
		Ifx_ShellBb shellBb;
		DataStreaming dataStreaming;
	}drivers;

	struct
	{
	        IfxStdIf_DPipe asc0;
	        IfxStdIf_DPipe debugPipe;
	} stdif;
	float32 testParam;
} OneEye;

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
OneEye g_oneEye; 				/**< \brief CPU 0 global data */
Ifx_DebugPipe g_debugPipe;

#define CFG_ASC0_RX_BUFFER_SIZE                              (128)      /**< \brief Define the Rx buffer size in byte. */
#define CFG_ASC0_TX_BUFFER_SIZE                              (10000)     /**< \brief Define the Tx buffer size in byte. */
#define CFG_ASC0_BAUDRATE                                    (256000.0) /**< \brief Define the Baudrate */
#define CFG_CONSOLE_TAB                                      (4)
//#define CFG_ASC0_BAUDRATE                                    (115200.0) /**< \brief Define the Baudrate */

/* BB protocol configuration */
#define BB_LOCAL_PORT_OSCILLOSCOPE     (1)
#define BB_REMOTE_PORT_OSCILLOSCOPE    (1)
#define BB_LOCAL_PORT_SHELL     	   (2)
#define BB_REMOTE_PORT_SHELL           (2)
#define BB_LOCAL_PORT_DATA_STREAMING   (3)
#define BB_REMOTE_PORT_DATA_STREAMING  (3)
#define BB_REMOTE_TIMEOUT (1000)
#define OSCI_SIGNAL_NAME_SPEED "Speed"
#define OSCI_SIGNAL_NAME_CURRENT_U "Current U"
#define OSCI_SIGNAL_NAME_CURRENT_V "Current V"
#define OSCI_SIGNAL_NAME_CURRENT_W "Current W"
#define OSCI_SIGNAL_NAME_CURRENT_ID_REF "Id Ref"
#define OSCI_SIGNAL_NAME_CURRENT_IQ_REF "Iq Ref"
#define OSCI_SIGNAL_NAME_CURRENT_ID_MEAS "Id Meas"
#define OSCI_SIGNAL_NAME_CURRENT_IQ_MEAS "Iq Meas"

/** \brief Build the ISR configuration object
 * \param no interrupt priority
 * \param cpu assign CPU number
 */
#define ISR_ASSIGN(no, cpu)  ((no << 8) + cpu)

/** \brief extract the priority out of the ISR object */
#define ISR_PRIORITY(no_cpu) (no_cpu >> 8)

/** \brief extract the service provider  out of the ISR object */
#define ISR_PROVIDER(no_cpu) (no_cpu % 8)

#define ISR_PROVIDER_ASC0      IfxSrc_Tos_cpu0        /**< \brief Define the ASC0 interrupt provider.  */
#define INTERRUPT_ASC0_RX      ISR_ASSIGN(ISR_PRIORITY_ASC0_RX, ISR_PROVIDER_ASC0)            /**< \brief Define the ASC0 receive interrupt priority.  */
#define INTERRUPT_ASC0_TX      ISR_ASSIGN(ISR_PRIORITY_ASC0_TX, ISR_PROVIDER_ASC0)            /**< \brief Define the ASC0 transmit interrupt priority.  */
#define INTERRUPT_ASC0_EX      ISR_ASSIGN(ISR_PRIORITY_ASC0_EX, ISR_PROVIDER_ASC0)            /**< \brief Define the ASC0 error interrupt priority.  */

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
boolean shellCmdSet(pchar args, void *data, IfxStdIf_DPipe *io);
boolean shellCmdGet(pchar args, void *data, IfxStdIf_DPipe *io);
boolean shellCmdOneeye(pchar args, void *data, IfxStdIf_DPipe *io);
boolean shellCmdInfo(pchar args, void *data, IfxStdIf_DPipe *io);
void OneEye_copyTxBuffer(void);
/******************************************************************************/
/*-------------------------Private Variables/Constants------------------------*/
/******************************************************************************/
/* *INDENT-OFF* */
const Ifx_Shell_Command AppShell_g_commands[] =
{
	{"help",         SHELL_HELP_DESCRIPTION_TEXT                             , &g_oneEye.drivers.shell, &Ifx_Shell_showHelp,       },
	{"info", "     : Show the application information (welcome screen)"      , &g_oneEye,   &shellCmdInfo,       },
	{"set", "      : Set  parameter"ENDL
			"/s set testParam <value>: request to set the testParam parameter"ENDL
				"/p <value>: Range=float32"ENDL


			, &g_oneEye,   &shellCmdSet,       },
	{"get", "      : Get parameter"ENDL
			"/s get all: Request to send all parameter"ENDL
			"/s get testParam: Request to send the testParam parameter"ENDL
			, &g_oneEye,   &shellCmdGet,       },


    {"!", "        : OneEye command"                                         , &g_oneEye.drivers.shell,   		 &shellCmdOneeye,       },
    IFX_SHELL_COMMAND_LIST_END
};
/* *INDENT-ON* */


volatile uint32 ctr_ISR_ASCLIN0_Rx;
IFX_INTERRUPT(ISR_ASCLIN0_Rx, 0, ISR_PRIORITY_ASC0_RX)
{
	__enable();
	ctr_ISR_ASCLIN0_Rx++;
	/* IfxStdIf_DPipe_onReceive is disabled because we use the DebugPipe to communicate with the computer */
	//IfxStdIf_DPipe_onReceive(&g_oneEye.stdif.asc0);
}

volatile uint32 ctr_ISR_ASCLIN0_Tx;
IFX_INTERRUPT(ISR_ASCLIN0_Tx, 0, ISR_PRIORITY_ASC0_TX)
{
	__enable();
    ctr_ISR_ASCLIN0_Tx++;
    OneEye_copyTxBuffer();
    /* IfxStdIf_DPipe_onTransmit still called because once the ASC buffer has been moved to DebugPipe, we need the ASC driver to update its internal state to empty & not transmitting */
    IfxStdIf_DPipe_onTransmit(&g_oneEye.stdif.asc0);
}

volatile uint32 ctr_ISR_ASCLIN0_Ex;
IFX_INTERRUPT(ISR_ASCLIN0_Ex, 0, ISR_PRIORITY_ASC0_EX)
{
	__enable();
	ctr_ISR_ASCLIN0_Ex++;
    /* IfxStdIf_DPipe_onError is disabled because we use the DebugPipe to communicate with the computer */
	//IfxStdIf_DPipe_onError(&g_oneEye.stdif.asc0);
}


/******************************************************************************/
/*--------------------------Function Implementations--------------------------*/
/******************************************************************************/
boolean OneEye_initAsclin(void)
{
    boolean              result = TRUE;
    /** - Standard IO and main CONSOLE */
    IfxAsclin_Asc_Config ascConfig;
    IfxAsclin_Asc_initModuleConfig(&ascConfig, &MODULE_ASCLIN0);
    ascConfig.baudrate.baudrate             = CFG_ASC0_BAUDRATE;
    ascConfig.baudrate.oversampling         = IfxAsclin_OversamplingFactor_16;
    ascConfig.bitTiming.medianFilter        = IfxAsclin_SamplesPerBit_three;
    ascConfig.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;
    ascConfig.frame.parityBit               = FALSE;
    ascConfig.frame.parityType              = IfxAsclin_ParityType_even;
    ascConfig.interrupt.rxPriority          = ISR_PRIORITY(INTERRUPT_ASC0_RX);
    ascConfig.interrupt.txPriority          = ISR_PRIORITY(INTERRUPT_ASC0_TX);
    ascConfig.interrupt.erPriority          = ISR_PRIORITY(INTERRUPT_ASC0_EX);
    ascConfig.interrupt.typeOfService       = ISR_PROVIDER_ASC0;
    IfxAsclin_Asc_Pins ascPins = {
        .cts       = NULL_PTR,
        .ctsMode   = IfxPort_InputMode_noPullDevice,
        .rx        = &IfxAsclin0_RXA_P14_1_IN,
        .rxMode    = IfxPort_InputMode_noPullDevice,
        .rts       = NULL_PTR,
        .rtsMode   = IfxPort_OutputMode_pushPull,
        .tx        = &IfxAsclin0_TX_P14_0_OUT,
        .txMode    = IfxPort_OutputMode_pushPull,
        .pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConfig.pins           = &ascPins;
    ascConfig.txBufferSize   = SyncProtocol_getFifoSize();
    ascConfig.rxBufferSize   = SyncProtocol_getFifoSize();
    ascConfig.dataBufferMode = Ifx_DataBufferMode_normal;
    result                   = IfxAsclin_Asc_initModule(&g_oneEye.drivers.asc0, &ascConfig) == IfxAsclin_Status_noError;

    /* Connect the standard asc interface to the device driver*/
    IfxAsclin_Asc_stdIfDPipeInit(&g_oneEye.stdif.asc0, &g_oneEye.drivers.asc0);


    /* Initialize the Shell */
    Ifx_DebugPipeConfig dPipeCfg;
    dPipeCfg.size = 255;


    Ifx_DebugPipe_Init(&g_debugPipe, &dPipeCfg);
    Ifx_DebugPipe_stdIfDPipeInit(&g_oneEye.stdif.debugPipe, &g_debugPipe);


#if 1
    /* Initialize the BB protocol */
    SyncProtocol_init(&g_oneEye.drivers.bb, BB_REMOTE_TIMEOUT, g_oneEye.drivers.asc0.rx, g_oneEye.drivers.asc0.tx);

    /* Initialize the BB protocol channel assigned to the oscilloscope */
    Ifx_OsciBb_init(&g_oneEye.drivers.osciBb, &g_oneEye.drivers.osci, &g_oneEye.drivers.bb, BB_LOCAL_PORT_OSCILLOSCOPE, BB_REMOTE_PORT_OSCILLOSCOPE);


    /* Initialize the BB protocol channel assigned to the shell */
    Ifx_ShellBb_init(&g_oneEye.drivers.shellBb, &g_oneEye.drivers.shell, &g_oneEye.drivers.bb, BB_LOCAL_PORT_SHELL, BB_REMOTE_PORT_SHELL, CFG_ASC0_RX_BUFFER_SIZE, CFG_ASC0_TX_BUFFER_SIZE);

    /* Initialize the BB protocol channel assigned to the data streaming (graph) */
    DataStreaming_init(&g_oneEye.drivers.dataStreaming, TimeConst_100ms, &g_oneEye.drivers.bb, BB_LOCAL_PORT_DATA_STREAMING, BB_REMOTE_PORT_DATA_STREAMING);
#endif

    Ifx_Shell_Config config;
    Ifx_Shell_initConfig(&config);
    config.standardIo         = &g_oneEye.drivers.shellBb._dPipe.stdif;
    //config.standardIo           = &g_oneEye.stdif.asc0;
    //config.showPrompt = FALSE;
    //config.echo = FALSE;


    /** Command lists used: */
    config.commandList[0] = &AppShell_g_commands[0];         /** - \ref AppShell_g_commands */

    Ifx_Shell_init(&g_oneEye.drivers.shell, &config);



    /* Print Info */
    shellCmdInfo("", &g_oneEye, &g_oneEye.drivers.shellBb._dPipe.stdif);

    /* Send software version information */

	IfxStdIf_DPipe_print(g_oneEye.drivers.shell.io, "! ecu swVersion %d.%02d.%02d"KEY_CR,
    		((SW_REVISION >> 16) & 0xFF),
    		((SW_REVISION >> 8) & 0xFF),
    		((SW_REVISION >> 0) & 0xFF)
    		);

	IfxStdIf_DPipe_print(g_oneEye.drivers.shell.io, "! ecu swName %s"KEY_CR,
    		SW_NAME
    		);

    return result;
}

boolean shellCmdSet(pchar args, void *data, IfxStdIf_DPipe *io)
{
	boolean result = FALSE;
	//OneEye *app = (OneEye*)data;

	if (Ifx_Shell_matchToken(&args, "ecu") != FALSE)
	{
		if (Ifx_Shell_matchToken(&args, "refSpeed") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.speedControl.refSpeed) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu refSpeed %f"KEY_CR, g_motorCtrl.pmsmFoc.speedControl.refSpeed);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "kpSpeedReg") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.speedControl.piSpeed.a0) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu kpSpeedReg %f"KEY_CR, g_motorCtrl.pmsmFoc.speedControl.piSpeed.a0);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "kiSpeedReg") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.speedControl.piSpeed.a1) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu kiSpeedReg %f"KEY_CR, g_motorCtrl.pmsmFoc.speedControl.piSpeed.a0);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "kpIdReg") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.piId.a0) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu kpIdReg %f"KEY_CR, g_motorCtrl.pmsmFoc.piId.a0);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "kiIdReg") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.piId.a1) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu kiIdReg %f"KEY_CR, g_motorCtrl.pmsmFoc.piId.a1);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "kpIqReg") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.piIq.a0) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu kpIqReg %f"KEY_CR, g_motorCtrl.pmsmFoc.piIq.a0);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "kiIqReg") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.piIq.a1) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu kiIqReg %f"KEY_CR, g_motorCtrl.pmsmFoc.piIq.a1);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "run") != FALSE)
		{
			uint32 run;
			if (Ifx_Shell_parseUInt32(&args, &run, FALSE) != FALSE)
			{
				if (run)
				{
					/* Go to STATE_focClosedLoop orSTATE_PhaseCalibration */
					PmsmFoc_Interface_startMotor(&g_motorCtrl);
				}
				else
				{
					/* Go to STATE_motorStop */
					PmsmFoc_Interface_stopMotor(&g_motorCtrl);
				}
				//IfxStdIf_DPipe_print(io, "! ecu run %f"KEY_CR, velocityControl.ref);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "cal") != FALSE)
		{
			uint32 cal;
			if (Ifx_Shell_parseUInt32(&args, &cal, FALSE) != FALSE)
			{
				if (cal)
				{
					/* Go to STATE_PhaseCalibration */
					PmsmFoc_Interface_calMotor(&g_motorCtrl);
				}
				//IfxStdIf_DPipe_print(io, "! ecu run %f"KEY_CR, velocityControl.ref);

				result                  = TRUE;
			}
		}
	}
	return result;
}

boolean shellCmdGet(pchar args, void *data, IfxStdIf_DPipe *io)
{
	boolean result = FALSE;
	OneEye *app = (OneEye*)data;

	if (Ifx_Shell_matchToken(&args, "all") != FALSE)
	{
		IfxStdIf_DPipe_print(io, "! ecu testParam %f"KEY_CR, app->testParam);
		result                  = TRUE;

	}
	else if (Ifx_Shell_matchToken(&args, "testParam") != FALSE)
	{
		IfxStdIf_DPipe_print(io, "! ecu testParam %f"KEY_CR, app->testParam);
		result                  = TRUE;

	}
	else if (Ifx_Shell_matchToken(&args, "ecu") != FALSE)
	{
		if (Ifx_Shell_matchToken(&args, "refSpeed") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.speedControl.refSpeed) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu refSpeed %f"KEY_CR, g_motorCtrl.pmsmFoc.speedControl.refSpeed);

				result                  = TRUE;
			}
		}
		else if (Ifx_Shell_matchToken(&args, "Speed") != FALSE)
		{
			if (Ifx_Shell_parseFloat32(&args, &g_motorCtrl.pmsmFoc.speedControl.measSpeed) != FALSE)
			{
				IfxStdIf_DPipe_print(io, "! ecu Speed %f"KEY_CR, g_motorCtrl.pmsmFoc.speedControl.measSpeed);

				result                  = TRUE;
			}
		}
	}

	return result;
}



/** OneEye command "!"
 *
 */
boolean shellCmdOneeye(pchar args, void *data, IfxStdIf_DPipe *io)
{
	Ifx_Shell       *shell = (Ifx_Shell*) data;
	/* OneEye command detected, switch echo and prompt off */
	shell->control.echo = 0;
	shell->control.showPrompt = 0;

	return Ifx_Shell_execute(data, args) == 0;
}


boolean shellCmdInfo(pchar args, void *data, IfxStdIf_DPipe *io)
{
    IfxStdIf_DPipe_print(io, ENDL ""ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    IfxStdIf_DPipe_print(io, "*******                                                                *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******  Infineon "IFXGLOBAL_DERIVATIVE_NAME " uC                                            *******"ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    IfxStdIf_DPipe_print(io, "*******  Copyright (C) 2015 Infineon Technologies A.G.                 *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******                                                                *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******  You can use this program under the terms of the IFX License.  *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******                                                                *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******  This program is distributed in the hope that it will be       *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******  useful, but WITHOUT ANY WARRANTY; without even the            *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******  implied warranty of MERCHANTABILITY or FITNESS FOR            *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******  A PARTICULAR PURPOSE. See the IFX License for more            *******"ENDL);
    IfxStdIf_DPipe_print(io, "*******  details (IFX_License.txt).                                    *******"ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    IfxStdIf_DPipe_print(io, "*******  Software Compile Date : %s                           *******"ENDL, __DATE__);
    IfxStdIf_DPipe_print(io, "*******  Software Compile Time : %s                              *******"ENDL, __TIME__);
    IfxStdIf_DPipe_print(io, "*******  Software Version      : %2d.%02d.%2d                              *******"ENDL, (SW_REVISION >> 16) & 0xFF, (SW_REVISION >> 8) & 0xFF, (SW_REVISION >> 0) & 0xFF);
    IfxStdIf_DPipe_print(io, "*******  Software Name         : %s                 *******"ENDL, SW_NAME);
#if 0
#if defined(__GNUC__) && !defined(__TASKING__)
    IfxStdIf_DPipe_print(io, "*******  Compiler              : %-5s, %-30s *******" ENDL,
            COMPILER_NAME, COMPILER_VERSION);
#else
    IfxStdIf_DPipe_print(io, "*******  Compiler              : %10s, %ld.%1dr%1d  *******" ENDL,
            COMPILER_NAME,
            (COMPILER_VERSION / 1000), (COMPILER_VERSION % 1000), COMPILER_REVISION);
#endif
#endif
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    return TRUE;
}

void OneEye_osciStep(void)
{
	/* Update Oscilloscope */
    Ifx_Osci_step(&g_oneEye.drivers.osci);
}

void OneEye_init(void)
{
    Ifx_Osci *osci = &g_oneEye.drivers.osci;

    Ifx_Osci_Config config;
    Ifx_Osci_initConfig(&config);
    config.autoAddChannels = TRUE;
    Ifx_Osci_init(osci, &config);

    Ifx_Osci_setSamplingPeriod(osci, 1.0/USER_INVERTER_PWM_FREQ_HZ);

    /* Add Signals */
    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_CURRENT_U, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.iPhaseMeas.u, 0);
    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_CURRENT_V, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.iPhaseMeas.v, 0);
    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_CURRENT_W, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.iPhaseMeas.w, 0);
    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_SPEED, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.speedControl.measSpeed, 0);

    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_CURRENT_ID_REF, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.idqRef.real, 0);
    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_CURRENT_ID_MEAS, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.idqMeas.real, 0);
    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_CURRENT_IQ_REF, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.idqRef.imag, 0);
    Ifx_Osci_addSignal(osci, OSCI_SIGNAL_NAME_CURRENT_IQ_MEAS, Ifx_Osci_DataType_Float32, &g_motorCtrl.pmsmFoc.idqMeas.imag, 0);



    /* Associate signals to channels */
    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_CURRENT_U),            0);
    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_CURRENT_V),            1);
    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_CURRENT_W),            2);
    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_SPEED),                3);

    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_CURRENT_ID_REF),       4);
    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_CURRENT_ID_MEAS),      5);
    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_CURRENT_IQ_REF),       6);
    Ifx_Osci_associateSignalToChannel(osci, Ifx_Osci_getSignalIdFromName(osci, OSCI_SIGNAL_NAME_CURRENT_IQ_MEAS),      7);

    /* Configure the default settings */
    Ifx_Osci_setTriggerSingle(osci, FALSE);
    Ifx_Osci_setTriggerMode(osci, Ifx_Osci_TriggerMode_automatic);
    Ifx_Osci_setTriggerLevel(osci, 0);
    Ifx_Osci_setTriggerEdge(osci, Ifx_Osci_TriggerEdge_rising);
    Ifx_Osci_start(osci);

    OneEye_initAsclin();

}

/* This functions copies the ASC transmit buffer to the DebugPipe transmit buffer, for direct read via MCD.
 * It must be called from the ASC Tx interrupt before calling the ASC transmit function, so that the ASC Tx buffer is emptied (moce to debug pipe)
 * and the ASC transmit function will reset the ASC internal states to be ready for a next transmission.
 */
void OneEye_copyTxBuffer(){
    uint8 ascData[255];
    IfxAsclin_Asc *asclin = &g_oneEye.drivers.asc0;
    if (Ifx_Fifo_isEmpty(asclin->tx) == FALSE)
    {
        uint16 toSend = Ifx_Fifo_readCount(asclin->tx); /*SW FIFO fill level*/
        while(toSend > 0){
            Ifx_SizeT chunk = toSend > g_debugPipe.tx.size ? g_debugPipe.tx.size : toSend;
            toSend -= chunk;

            Ifx_Fifo_read(asclin->tx, &ascData[0], chunk, TIME_NULL);

            while(IfxStdIf_DPipe_canWriteCount(&g_oneEye.stdif.debugPipe, chunk, 0 ) == FALSE){
                /* wait for fifo to be free enough */
            }

            IfxStdIf_DPipe_write(&g_oneEye.stdif.debugPipe, ascData, &chunk, 0);
        }
    }

}


/* This functions copies the DebugPipe reception buffer to the ASC reception buffer, to simulate ASC reception instead of the actual direct access over MCD.
 * It must be called periodically and be able to interrupt functions using ASC transmission (i.e. backgroun task in this project).
 */
void OneEye_copyRxBuffers(void)
{

    uint8 ascData[255];
    IfxAsclin_Asc *asclin = &g_oneEye.drivers.asc0;
    sint32 toRead = IfxStdIf_DPipe_getReadCount(&g_oneEye.stdif.debugPipe);

    if(toRead > 0){
        if(IfxStdIf_DPipe_read(&g_oneEye.stdif.debugPipe, ascData, (Ifx_SizeT *)&toRead, 0)){
            Ifx_Fifo_write(asclin->rx, &ascData[0], (Ifx_SizeT)toRead, TIME_NULL);
        }
    }
}


void OneEye_processDataStream(void)
{

#if 1

    /* make sure all Tx buffer have been sent */
    OneEye_copyTxBuffer();

	/* Process the BB protocol */
    SyncProtocol_execute(&g_oneEye.drivers.bb);

    /* Process the BB channel for the oscilloscope */
    Ifx_OsciBb_processMessages(&g_oneEye.drivers.osciBb);

    /* Process the BB channel for the shell */
    Ifx_ShellBb_processMessages(&g_oneEye.drivers.shellBb);

    /* Process the BB channel for the data streaming */
    //DataStreaming_processMessages(&g_oneEye.drivers.dataStreaming);

	/* Process the shell commands */
	Ifx_Shell_process(&g_oneEye.drivers.shell);
#endif

}
#endif /* End of ONE_EYEMODE*/
