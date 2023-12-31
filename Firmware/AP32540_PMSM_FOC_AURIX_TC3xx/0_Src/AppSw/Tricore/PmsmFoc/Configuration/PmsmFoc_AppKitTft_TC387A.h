/*
 * \file PmsmFoc_appKitTft_TC387A.h
 * \brief
 * \ingroup pmsm_foc_configuration
 * \version
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

#ifndef PMSM_FOC_APPKIT_TFT_TC387A_PARAMETERS_H_
#define PMSM_FOC_APPKIT_TFT_TC387A_PARAMETERS_H_
/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "PmsmFoc_UserConfig.h"
#if(PMSM_FOC_HARDWARE_KIT == KIT_A2G_TC387_MOTORCTRL)
#include "IfxGtm_PinMap.h"
#include "IfxGpt12_PinMap.h"
#include "IfxPort_PinMap.h"
#include "IfxQspi_PinMap.h"
#include "IfxSrc_cfg.h"
#include "IfxDma_cfg.h"
#include MOTOR_TYPE_PATH
#include INVERTERCARD_TYPE_PATH
/******************************************************************************/
/*--------------------------------Macros--------------------------------------*/
/******************************************************************************/

/** \brief Interrupt priority assignment for the application 											*/
/** \brief Instruction: Arrange the interrupt defines in ascending order of their priority! 			*/
/** \brief Check if there are two interrupts assigned with same priority (unless they are grouped)  	*/

/** \brief Define the Encoder zero position interrupt priority. */
#define INTERRUPT_PRIORITY_ENCODER_GPT12 (20)
/** \brief Define the resolver (RDC) INTERRUPT_PRIORITY priority. */
#define ISR_PRIORITY_RDC_DS_0       	 (35)

#define ISR_PRIORITY_TLF_QSPI_ER        (45)  /**< \brief Define the TLF error interrupt priority.  */
#define ISR_PRIORITY_TLF_QSPI_TX        (46)  /**< \brief Define the TLF transmit interrupt priority.  */
#define ISR_PRIORITY_TLF_QSPI_RX        (47)  /**< \brief Define the TLF receive interrupt priority.  */

/** \brief Define the QSPI4 transmit interrupt priority. */
#define INTERRUPT_PRIORITY_QSPI4_TX      (50)
/** \brief Define the QSPI4 receive interrupt priority. */
#define INTERRUPT_PRIORITY_QSPI4_RX      (51)
/** \brief Define the QSPI4 error interrupt priority. */
#define INTERRUPT_PRIORITY_QSPI4_ERR     (52)
/** \brief Define the EVADC group conversion. */
#define INTERRUPT_PRIORITY_EVADC_HSCUR   (97)
/** \brief Define the EVADC group conversion. */
#define INTERRUPT_PRIORITY_EVADC_VBEMF   (98)
/** \brief Define the EVADC group conversion. */
#define INTERRUPT_PRIORITY_EVADC_VDCL    (99)
/** \brief Define the EVADC group conversion. */
#define INTERRUPT_PRIORITY_EVADC_CUR     (100)
/** \brief Define the ASC0 receive interrupt priority. */
#define ISR_PRIORITY_ASC0_RX   			 (105)
/** \brief Define the ASC0 transmit interrupt priority. */
#define ISR_PRIORITY_ASC0_TX   			 (106)
/** \brief Define the ASC0 error interrupt priority. */
#define ISR_PRIORITY_ASC0_EX   			 (107)

/* GTM GPIO Resources Configuration */
#if(GTM_USED == GTM_TOM_WITHOUT_DTM_USED)
/** \brief Define the GTM TOM module   */
#define PWM_MODULE         				IfxGtm_Tom_1
/** \brief Define the Reference channel   */
#define REF_CHANNEL                     IfxGtm_Tom_Ch_0
/** \brief Define the phase U high-side PWM output.   */
#define PHASE_U_HS         				&IfxGtm_TOM1_2_TOUT12_P00_3_OUT
/** \brief Define the phase U low-side PWM output.  */
#define PHASE_U_LS         				&IfxGtm_TOM1_1_TOUT11_P00_2_OUT
/** \brief Define the phase V high-side PWM output.  */
#define PHASE_V_HS         				&IfxGtm_TOM1_4_TOUT14_P00_5_OUT
/** \brief Define the phase V low-side PWM output.  */
#define PHASE_V_LS         				&IfxGtm_TOM1_3_TOUT13_P00_4_OUT
/** \brief Define the phase W high-side PWM output.  */
#define PHASE_W_HS        				&IfxGtm_TOM1_6_TOUT16_P00_7_OUT
/** \brief Define the phase W low-side PWM output.  */
#define PHASE_W_LS         				&IfxGtm_TOM1_5_TOUT15_P00_6_OUT
/** \brief Define the ADC trigger channel   */
#define ADC_TRIGGER_CHANNEL             &IfxGtm_TOM1_7_TOUT15_P00_6_OUT

#define REF_TESTOUPUT_CHANNEL           &IfxGtm_TOM1_0_TOUT18_P00_9_OUT

#elif(GTM_USED == GTM_ATOM_WITH_DTM_USED)
/** \brief Define the phase U high-side PWM output.  */
#define PHASE_U_HS         				&IfxGtm_ATOM0_2_TOUT12_P00_3_OUT
/** \brief Define the phase U low-side PWM output.  */
#define PHASE_U_LS         				&IfxGtm_ATOM0_1_TOUT11_P00_2_OUT
/** \brief Define the phase V high-side PWM output.  */
#define PHASE_V_HS         				&IfxGtm_ATOM0_1N_TOUT14_P00_5_OUT
/** \brief Define the phase V low-side PWM output.  */
#define PHASE_V_LS         				&IfxGtm_ATOM0_3_TOUT13_P00_4_OUT
/** \brief Define the phase W high-side PWM output.  */
#define PHASE_W_HS        				&IfxGtm_ATOM0_3N_TOUT16_P00_7_OUT
/** \brief Define the phase W low-side PWM output.  */
#define PHASE_W_LS         				&IfxGtm_ATOM0_2N_TOUT15_P00_6_OUT
#endif

#if (POSITION_SENSOR_TYPE == ENCODER)
/* Encoder GPT12 define */
/** \brief Define the encoder pin A.  */
#define ENCODER_GPT12_PIN_A				&IfxGpt120_T3INA_P02_6_IN
/** \brief Define the encoder pin B.   */
#define ENCODER_GPT12_PIN_B				&IfxGpt120_T3EUDA_P02_7_IN
/** \brief Define the encoder pin Z.   */
#define ENCODER_GPT12_PIN_Z				&IfxGpt120_T4INA_P02_8_IN
/** \brief Encoder reversed. */
#define ENCODER_REVERSED        		TRUE
/** \brief Define the encoder resolution. */
#define ENCODER_RESOLUTION      		USER_MOTOR_ENCODER_PULSES_PER_REVOLUTION
/** \brief Define the encoder fold */
#define ENCODER_FOLD    		        USER_MOTOR_ENCODER_FOLD
/** \brief Define the encoder function update period. */
#define ENCODER_UPDATE_PERIOD           (1/ ((float32)USER_INVERTER_PWM_FREQ_HZ))
/** \brief Use pulse counting if there is less than user defined counting rpm (1200 rpm). */
#define ENCODER_SPEED_MODE_THRESHOLD    2 * IFX_PI * USER_MOTOR_SPEED_PULSE_COUNTING_RPM / 60
/** \brief Define the minimum base speed*/
#define ENCODER_BASE_MIN_SPEED          (float32) (USER_MOTOR_SPEED_LOW_LIMIT_RPM / 60.0 * 2 * IFX_PI)
/** \brief Define the maximum base speed */
#define ENCODER_BASE_MAX_SPEED          (float32) (USER_MOTOR_SPEED_HIGH_LIMIT_RPM / 60.0 * 2 * IFX_PI)
/** \brief Define the GPT12 host CPU.   */
#define ENCODER_GPT12_HOST_CPU    		IfxSrc_Tos_cpu0

#elif(POSITION_SENSOR_TYPE == RESOLVER)
/* Resolver SIN/COS Sensing EDSAC define */

#elif(POSITION_SENSOR_TYPE == HALL)
/* HALL define */

#endif

/* TLE9180 GPIO and QSPI define */
/** \brief Define the DMA channel no for the QSPI receive */
/* TLE9180 GPIO and QSPI define */
#define CPU_WHICH_SERVICE_TLE9180        0     /**< \brief Define the CPU which service the Tlf3xx8x and where functions/variables are located.  */
/* TLE9180 GPIO define */
/** \brief Define the TLE9180 Enable Pin GPIO.  */
#define TLE9180_ENABLE_PIN				&IfxPort_P33_11
/** \brief Define the TLE9180 Error Pin GPIO.  */
#define TLE9180_ERROR_PIN				&IfxPort_P15_2
/** \brief Define the TLE9180 Inhibit Pin GPIO.  */
#define TLE9180_INHIBIT_PIN				&IfxPort_P20_0
/** \brief Define the TLE9180 Safe Off Pin GPIO.  */
#define TLE9180_SAFEOFF_PIN				&IfxPort_P33_10
/* TLE9180 QSPI define */
/** \brief Define the QSPI slave select pin. */
#define TLE9180_SPI_CS_PIN     			IfxQspi4_SLSO3_P22_2_OUT
/** \brief Define the QSPI object */
#define TLE9180_SPI_MODULE              MODULE_QSPI4
/** \brief Define the QSPI SLCK out pin */
#define TLE9180_SPI_CLOCK_PIN           IfxQspi4_SCLK_P22_3_OUT
/** \brief Define the QSPI MTSR out pin */
#define TLE9180_SPI_MOSI_PIN            IfxQspi4_MTSR_P22_0_OUT
/** \brief Define the QSPI MRSTA input pin */
#define TLE9180_SPI_MISO_PIN            IfxQspi4_MRSTB_P22_1_IN
/** \brief Define the handler of the interrupts*/
#define TLE9180_SPI_HOST_CPU            IfxSrc_Tos_cpu0
/** \brief Define the use of DMA for Data transfer/s */
#define TLE9180_SPI_USE_DMA             FALSE
/** \brief Define the DMA channel no for the QSPI transmit */
#define TLE9180_SPI_TX_DMA_CH           IfxDma_ChannelId_none
/** \brief Define the DMA channel no for the QSPI receive */
#define TLE9180_SPI_RX_DMA_CH           IfxDma_ChannelId_none

/* TLF35584 GPIO and QSPI define */
#define CPU_WHICH_SERVICE_TLF          0     /**< \brief Define the CPU which service the Tlf3xx8x and where functions/variables are located.  */
/* set here the used pins for TLF3xx8x (QSPI2) */
#define TLF_QSPI_MAX_BAUDRATE       50000000  // maximum baudrate which is possible to get a small time quantum
#define TLF_SCLK_PIN	            IfxQspi2_SCLK_P15_8_OUT
#define TLF_MTSR_PIN	            IfxQspi2_MTSR_P15_6_OUT      // for Application Kit TC3X7
#define TLF_MRST_PIN	            IfxQspi2_MRSTB_P15_7_IN
//#define TLF_USE_DMA  // uncomment line for using DMA
//#define DMA_CH_TLF_TX             TLF_DMA_CH_TXBUFF_TO_TXFIFO
//#define DMA_CH_TLF_RX             TLF_DMA_CH_RXBUFF_FROM_RXFIFO

#define TLF_CS_PIN                  IfxQspi2_SLSO1_P14_2_OUT

/** \brief Define the INA225AIDGK gain selection pin 0 GPIO.  */
#define INA225AIDGK_GS0					&IfxPort_P33_2
/** \brief Define the INA225AIDGK gain selection pin 1 GPIO.  */
#define INA225AIDGK_GS1					&IfxPort_P33_4
/** \brief Define the LED107_PORT GPIO pin.  */
#define LED107_PORT					        &IfxPort_P13_0
/** \brief Define the LED108_PORT GPIO pin.  */
#define LED108_PORT					        &IfxPort_P13_1
/** \brief Define the LED109_PORT GPIO pin.  */
#define LED109_PORT					        &IfxPort_P13_2
/** \brief Define the LED110_PORT GPIO pin.  */
#define LED110_PORT					        &IfxPort_P13_3

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/
#endif /* End of KIT_A2G_TC387_MOTORCTRL */

#endif /* PMSM_FOC_APPKIT_TFT_TC397B_PARAMETERS_H_ */
