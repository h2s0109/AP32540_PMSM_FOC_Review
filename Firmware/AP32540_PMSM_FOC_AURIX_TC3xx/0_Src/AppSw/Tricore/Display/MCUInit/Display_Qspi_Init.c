/*
 * \file Display_Qspi_Init.c
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
#include "Display_Qspi_Init.h"
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
IfxQspi_SpiMaster           spiMasterQspi0;

/******************************************************************************/
/*-------------------------Private Variables/Constants------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------Function Implementations--------------------------*/
/******************************************************************************/
/** \brief Initialize QSPI0 Module
 *
 */
IFX_INLINE void Spi_initQspi0(void)
{
	/* create SPI0 module config */
	IfxQspi_SpiMaster_Config        spiConfig;
	IfxQspi_SpiMaster_initModuleConfig(&spiConfig, &SPI_0_MODULE);

	/* pin configuration */
	const IfxQspi_SpiMaster_Pins spiPins =
	{
		&SPI_0_CLOCK_PIN,  IfxPort_OutputMode_pushPull,
		&SPI_0_MOSI_PIN,  IfxPort_OutputMode_pushPull,
		&SPI_0_MISO_PIN,  IfxPort_InputMode_pullDown,
		IfxPort_PadDriver_cmosAutomotiveSpeed1
	};

	/* set the maximum baudrate */
	spiConfig.base.maximumBaudrate = 50.0e6;

	/* ISR priorities and interrupt target */
	spiConfig.base.txPriority    = INTERRUPT_PRIORITY_QSPI0_TX;
	spiConfig.base.rxPriority    = INTERRUPT_PRIORITY_QSPI0_RX;
	spiConfig.base.erPriority    = INTERRUPT_PRIORITY_QSPI0_ERR;
	spiConfig.base.isrProvider   = SPI_0_HOST_CPU;
#if (SPI_0_USE_DMA == TRUE)
	spiConfig.dma.txDmaChannelId = SPI_0_TX_DMA_CH;
	spiConfig.dma.rxDmaChannelId = SPI_0_RX_DMA_CH;
	spiConfig.dma.useDma         = TRUE;
#endif
	spiConfig.pins = &spiPins;

	/* initialize module */
	IfxQspi_SpiMaster_initModule(&spiMasterQspi0, &spiConfig);

	{
		volatile Ifx_SRC_SRCR *src = IfxQspi_getErrorSrc(&MODULE_QSPI0);
		IfxSrc_init(src, SPI_0_HOST_CPU, INTERRUPT_PRIORITY_QSPI0_ERR);
		IfxSrc_enable(src);
	}
}

/** \brief Initialize Used SPI Modules
 *
 */
void Display_initSpiModules(void)
{
    Spi_initQspi0();
}

/** \brief QSPI Interrupts
 *
 */


