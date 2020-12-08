/*
 * \file OsTasks.c
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
#include MCUCARD_TYPE_PATH
#include INVERTERCARD_TYPE_PATH
#include MOTOR_TYPE_PATH
#include "IfxStm.h"
#include "FreeRTOS.h"
#include "task.h"
#if(TFT_DISPLAYMODE == ENABLED)
	#include "conio_tft.h"
	#include "touch.h"
#endif /* End of TFT_DISPLAYMODE */
#include "PmsmFoc_Functions.h"
#include "Display.h"
#include "PmsmFoc_InitTLE9180.h"
#if(ONE_EYEMODE == ENABLED)
	#include "OneEye_Init.h"
#endif /* End of ONE_EYEMODE*/

#include "PmsmFoc_Interface.h"
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
#if(TFT_DISPLAYMODE == ENABLED)
	extern volatile boolean 		tft_ready;
#endif /* End of TFT_DISPLAYMODE */

extern MotorControl				g_motorControl;

/******************************************************************************/
/*-------------------------Private Variables/Constants------------------------*/
/******************************************************************************/
#define OS_CURRENT_RAMP_TASK_PERIOD_MS				((uint32)(USER_MOTOR_CURRENT_Q_RAMP_PERIOD*1000))
#define OS_CURRENT_RAMP_TASK_PRIORITY				(8)

#define OS_SPEED_CONTROL_TASK_PERIOD_MS				(5)
#define OS_SPEED_CONTROL_TASK_PRIORITY				(8)

#define OS_ONE_EYE_BUFFER_COPY_TASK_PERIOD_MS		(10)
#define OS_ONE_EYE_BUFFER_COPY_TASK_PERIOD_PRIORITY	(7)
#if(TFT_DISPLAYMODE == ENABLED)
	#define OS_TOUCH_CONTROL_TASK_PERIOD_MS				(20)
	#define OS_TOUCH_CONTROL_TASK_PRIORITY				(6)
#endif /* End of TFT_DISPLAYMODE */
#define OS_SPEED_REF_RAMP_TASK_PERIOD_MS			((uint32)(USER_MOTOR_SPEED_RAMP_PERIOD*1000))
#define OS_SPEED_REF_RAMP_TASK_PRIORITY				(5)
#if(TFT_DISPLAYMODE == ENABLED)
	#define OS_CONIO_TASK_PERIOD_MS						(100)
	#define OS_CONIO_TASK_PRIORITY						(4)
#endif /* End of TFT_DISPLAYMODE */
#define OS_DEMO_CONTROL_TASK_PERIOD_MS				(200)
#define OS_DEMO_CONTROL_TASK_PRIORITY				(3)
#if(TFT_DISPLAYMODE == ENABLED)
	#define OS_DISPLAY_TIME_TASK_PERIOD_MS				(1000)
	#define OS_DISPLAY_TIME_TASK_PRIORITY				(2)
#endif /* End of TFT_DISPLAYMODE */




/******************************************************************************/
/*--------------------------Function Implementations--------------------------*/
/******************************************************************************/
/**
 * FreeRTOS Kernel Tick timer setup
 * FreeRTOS needs kernel Tick through an interrupt occurring at configTICK_RATE_HZ rate.
 * The ISR need to call the function vPortSystemTickHandler.
 */
static void OsTasks_setupTimerInterrupt(Ifx_STM *stm)
{
	IfxStm_setCompareControl(stm,
			IfxStm_Comparator_0,
			IfxStm_ComparatorOffset_0,
			IfxStm_ComparatorSize_32Bits,
			IfxStm_ComparatorInterrupt_ir0);

	IfxStm_clearCompareFlag(stm,
			IfxStm_Comparator_0);

	{
		volatile Ifx_SRC_SRCR *src;
		src = IfxStm_getSrcPointer(stm, IfxStm_Comparator_0);
		IfxSrc_init(src, (IfxSrc_Tos)AURIX_ISR_HOST, configKERNEL_INTERRUPT_PRIORITY);
		IfxSrc_enable(src);
	}

	{
		uint32 stmCount= IfxStm_getLower(stm);
		IfxStm_updateCompare(&MODULE_STM0,
				IfxStm_Comparator_0,
				stmCount + configSTM_CLOCK_HZ/configTICK_RATE_HZ );
		IfxStm_enableComparatorInterrupt(stm, IfxStm_Comparator_0);
	}
}

/**
 * FreeRTOS Kernel Tick interrupt provider
 * FreeRTOS needs kernel Tick through an interrupt occurring at configTICK_RATE_HZ rate.
 * The ISR need to call the function vPortSystemTickHandler.
 */
IFX_INTERRUPT(OsTasks_TickProvider, FREERTOS_CORE_ID, configKERNEL_INTERRUPT_PRIORITY)
{
	uint32 stmCount= IfxStm_getCompare(&MODULE_STM0, IfxStm_Comparator_0);
	IfxStm_updateCompare(&MODULE_STM0,
			IfxStm_Comparator_0,
			stmCount + configSTM_CLOCK_HZ/configTICK_RATE_HZ );
	vPortSystemTickHandler();
}

#if(TFT_DISPLAYMODE == ENABLED)
volatile uint32 touchControlCount= 0UL;

static __attribute__((__noreturn__)) void periodicTouchControlTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{

		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_TOUCH_CONTROL_TASK_PERIOD_MS));
		touchControlCount++;
		{
			/******************************************************************
			 *                      TOUCH CONTROL Task START                  *
			 ******************************************************************/
			/* Call user tasks here */
			if (tft_ready == 1)
			{
				touch_periodic ();
			}
			/******************************************************************
			 *                       TOUCH CONTROL Task END                   *
			 ******************************************************************/
		}
	}
}
#endif /* End of TFT_DISPLAYMODE */

volatile uint32 speedControlCount= 0UL;


static __attribute__((__noreturn__)) void periodicSpeedControlTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_SPEED_CONTROL_TASK_PERIOD_MS));
		speedControlCount++;
		{
			/******************************************************************
			 *                      SPEED CONTROL Task START                  *
			 ******************************************************************/
			/* Call user tasks here */
			PmsmFoc_doSpeedControl(&g_motorControl);

			if(g_motorControl.interface.motorTargetSpeed > EC_MAX_SPEED)
				g_motorControl.interface.motorTargetSpeed = EC_MAX_SPEED;
			if(g_motorControl.interface.motorTargetSpeed < EC_MIN_SPEED)
				g_motorControl.interface.motorTargetSpeed = EC_MIN_SPEED;
			if(g_motorControl.pmsmFoc.speedControl.refSpeed > EC_MAX_SPEED)
				g_motorControl.pmsmFoc.speedControl.refSpeed = EC_MAX_SPEED;
			if(g_motorControl.pmsmFoc.speedControl.refSpeed < EC_MIN_SPEED)
				g_motorControl.pmsmFoc.speedControl.refSpeed = EC_MIN_SPEED;
			/******************************************************************
			 *                       SPEED CONTROL Task END                   *
			 ******************************************************************/

		}
	}
}

volatile uint32 speedRefRampCount= 0UL;

static __attribute__((__noreturn__)) void periodicSpeedRefRampTimeTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();
	float32 refSpeed;
	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_SPEED_REF_RAMP_TASK_PERIOD_MS));
		speedRefRampCount++;
		{
			/******************************************************************
			 *                   SPEED REFERENCE RAMP Task START              *
			 ******************************************************************/
			/* Call user tasks here */
			if(!g_motorControl.interface.demo)
			{
				if (g_motorControl.pmsmFoc.speedControl.enabled != FALSE)
				{
					PmsmFoc_setSpeedRefLinearRamp(&g_motorControl.pmsmFoc,
							g_motorControl.interface.motorTargetSpeed);
				}
				else
				{
					PmsmFoc_setSpeedRefLinearRamp(&g_motorControl.pmsmFoc, 0);
				}

				PmsmFoc_doSpeedRefLinearRamp(&g_motorControl.pmsmFoc);
				refSpeed = PmsmFoc_getSpeedRefLinearRamp(&g_motorControl.pmsmFoc);
				PmsmFoc_SpeedControl_setRefSpeed(&g_motorControl.pmsmFoc.speedControl, refSpeed);
			}
			/******************************************************************
			 *                SPEED REFERENCE RAMP Task END                   *
			 ******************************************************************/
		}
	}
}

volatile uint32 currentRampCount= 0UL;

static __attribute__((__noreturn__)) void periodicCurrentRampTimeTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_CURRENT_RAMP_TASK_PERIOD_MS));
		currentRampCount++;
		{
			/******************************************************************
			 *             CURRENT REFERENCE RAMP Task START                  *
			 ******************************************************************/
			/* Call user tasks here */
			if (g_motorControl.controlParameters.controlScheme == ControlScheme_current)
			{
				CplxStdReal tempIdq ={0.0, 0.0};

				if(g_motorControl.interface.running != FALSE)
				{
					tempIdq.real = g_motorControl.pmsmFoc.idqRefExternal.real;
					tempIdq.imag = g_motorControl.pmsmFoc.idqRefExternal.imag;
				}
				PmsmFoc_setCurrentRefLinearRamp(&g_motorControl.pmsmFoc,tempIdq);
				PmsmFoc_doCurrentRefLinearRamp(&g_motorControl.pmsmFoc);
			}

			/******************************************************************
			 *             CURRENT REFERENCE RAMP Task END                   *
			 ******************************************************************/
		}
	}
}

#if(ONE_EYEMODE == ENABLED)
volatile uint32 OneEyeBufferCopyCount= 0UL;

static __attribute__((__noreturn__)) void periodicOneEyeBufferCopyTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_ONE_EYE_BUFFER_COPY_TASK_PERIOD_MS));
		OneEyeBufferCopyCount++;
		{
			/******************************************************************
			 *                      OneEye Buffer Copy Task START                  *
			 ******************************************************************/
			/* Call user tasks here */
			OneEye_copyRxBuffers();
			/******************************************************************
			 *                       OneEye Buffer Copy Task END                   *
			 ******************************************************************/
		}
	}
}
#endif /* End of ONE_EYEMODE*/

#if(TFT_DISPLAYMODE == ENABLED)
volatile uint32 conioCount= 0UL;

static __attribute__((__noreturn__)) void periodicConioTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_CONIO_TASK_PERIOD_MS));
		conioCount++;
		{
			/******************************************************************
			 *                         CONIO Task START                       *
			 ******************************************************************/
			if (tft_ready == 1)
			{
				conio_periodic(touch_driver.xdisp, touch_driver.ydisp, conio_driver.pmenulist, conio_driver.pstdlist);
				#if(ONE_EYEMODE == ENABLED)
				/*STEVE: not ONE_EYEMODE but has a dependency with ONE_EYEMODE */ 
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 0, (uint8 *)SW_NAME);
				#endif /* End of ONE_EYEMODE*/
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 1, (uint8 *)"SW: V1.0.2, HW V3.2");
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 3, (uint8 *)"Speed Ref [rpm] = %.1f %c\n", g_motorControl.pmsmFoc.speedControl.refSpeed);
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 4, (uint8 *)"Speed Meas[rpm] = %.1f %c\n", g_motorControl.pmsmFoc.speedControl.measSpeed);

				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 6, (uint8 *)"Iu[A] = %.3f %c\n", g_motorControl.inverter.phaseCurrentSense.curVO1.value);
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 7, (uint8 *)"Iv[A] = %.3f %c\n", g_motorControl.inverter.phaseCurrentSense.curVO2.value);
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 8, (uint8 *)"Iw[A] = %.3f %c\n", g_motorControl.inverter.phaseCurrentSense.curVO3.value);

				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 10, (uint8 *)"IqRef [A] = %.2f %c\n", g_motorControl.pmsmFoc.idqRef.imag);
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 11, (uint8 *)"IqMeas[A] = %.2f %c\n", g_motorControl.pmsmFoc.idqMeas.imag);

				conio_ascii_printfxy (DISPLAYSTDOUT0, 20, 10, (uint8 *)"IdRef[A] = %.2f %c\n", g_motorControl.pmsmFoc.idqRef.real);
				conio_ascii_printfxy (DISPLAYSTDOUT0, 20, 11, (uint8 *)"IdMeas[A] = %.2f %c\n", g_motorControl.pmsmFoc.idqMeas.real);

				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 13, (uint8 *)"VqRef [p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vdqRef.imag);
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 14, (uint8 *)"VdRef [p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vdqRef.real);

				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 16, (uint8 *)"ValphaRef[p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vabRef.imag);
				conio_ascii_printfxy (DISPLAYSTDOUT0, 0, 17, (uint8 *)"VbetaRef [p.u.] = %.2f %c\n", g_motorControl.pmsmFoc.vabRef.real);

			}
			/******************************************************************
			 *                          CONIO Task END                        *
			 ******************************************************************/
		}
	}
}
#endif /* End of TFT_DISPLAYMODE */
volatile uint32 demoControlCount= 0UL;

static __attribute__((__noreturn__)) void periodicDemoControlTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_DEMO_CONTROL_TASK_PERIOD_MS));
		demoControlCount++;
		{
			/******************************************************************
			 *                      DEMO CONTROL Task START                   *
			 ******************************************************************/
			PmsmFoc_Interface_doDemo(&g_motorControl);


			/******************************************************************
			 *                       DEMO CONTROL Task END                    *
			 ******************************************************************/
		}
	}
}

#if(TFT_DISPLAYMODE == ENABLED)
volatile uint32 displayTimeCount= 0UL;

static __attribute__((__noreturn__)) void periodicDisplayTimeTask(void *arg)
{
	TickType_t xLastWakeTime;
	(void)arg;
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(OS_DISPLAY_TIME_TASK_PERIOD_MS));
		displayTimeCount++;
		{
			/******************************************************************
			 *                      DISPLAY TIME Task START                   *
			 ******************************************************************/
			displayTime.sec++;
			if((displayTime.sec % 60)==0)
			{
				displayTime.sec= 0;
				displayTime.min++;
				if((displayTime.min % 60)==0)
				{
					displayTime.min= 0;
					displayTime.hour++;
				}
			}
			/******************************************************************
			 *                      DISPLAY TIME Task END                     *
			 ******************************************************************/
		}
	}
}
#endif /* End of TFT_DISPLAYMODE */

volatile uint32 ulIdleCycleCount = 0UL;
void vApplicationIdleHook( void )
{
	/* This hook function does nothing but increment a counter. */
	ulIdleCycleCount++;
	{
		/******************************************************************
		 *                        IDLE Task START                         *
		 ******************************************************************/
		#if(ONE_EYEMODE == ENABLED)
			OneEye_processDataStream();
		#endif /* End of ONE_EYEMODE*/
		/******************************************************************
		 *                         IDLE Task END                          *
		 ******************************************************************/
	}
}

void OS_Tasks_init(void)
{
	/* Create tasks. */
#if(TFT_DISPLAYMODE == ENABLED)	
	xTaskCreate(periodicTouchControlTask,
			"Touch Control",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_TOUCH_CONTROL_TASK_PRIORITY,
			NULL);
#endif /* End of TFT_DISPLAYMODE */

	xTaskCreate(periodicSpeedControlTask,
			"Speed Control",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_SPEED_CONTROL_TASK_PRIORITY,
			NULL);

#if(ONE_EYEMODE == ENABLED)
	xTaskCreate(periodicOneEyeBufferCopyTask,
			"One Eye Buffer Copy",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_SPEED_CONTROL_TASK_PRIORITY,
			NULL);
#endif /* End of ONE_EYEMODE*/

	xTaskCreate(periodicSpeedRefRampTimeTask,
			"Speed Ref Ramp Time",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_SPEED_REF_RAMP_TASK_PRIORITY,
			NULL);

#if(TFT_DISPLAYMODE == ENABLED)
	xTaskCreate(periodicConioTask,
			"ConIO Task",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_CONIO_TASK_PRIORITY,
			NULL);
#endif /* End of TFT_DISPLAYMODE */

	xTaskCreate(periodicDemoControlTask,
			"Demo Control",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_DEMO_CONTROL_TASK_PRIORITY,
			NULL);
#if(TFT_DISPLAYMODE == ENABLED)
	xTaskCreate(periodicDisplayTimeTask,
			"Display Time",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_DISPLAY_TIME_TASK_PRIORITY,
			NULL);
#endif /* End of TFT_DISPLAYMODE */

	xTaskCreate(periodicCurrentRampTimeTask,
			"Current Ramp Time",
			configMINIMAL_STACK_SIZE,
			NULL,
			OS_CURRENT_RAMP_TASK_PRIORITY,
			NULL);

	/* Set the Kernel interrupt and timer interrupt */
	OsTasks_setupTimerInterrupt(&MODULE_STM0);

	/* Start the tasks running. */
	vTaskStartScheduler();
}
