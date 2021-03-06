/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

// C/C++ Library Includes
#include <stdio.h>

// KSDK Includes
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

// Freerad Application includes
#include "App_Tasks.h"
#include "App_CallbackFunctions.h"
#include "App_Globals.h"

/*!
 * @brief Application entry point.
 */
int main(void)
{
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitPeripherals();

	printf("\r\n////////////////////////////////////////////\r\n");
	printf("//  Freerad Project %s %s  //\r\n", __DATE__, __TIME__);
	printf("////////////////////////////////////////////\r\n\r\n");

    /* Create the software timer, then start it. */
	TimerHandle_t xTimer_HeartbeatLed = xTimerCreate("Timer_HeartbeatLed", 500, pdTRUE, (void *)0, vExampleTimerCallback);
    xTimerStart(xTimer_HeartbeatLed, 0);

    /* Create queues */
	Q_Printf = xQueueCreate(32, PRINTF_STRING_SIZE);

	/* Create RTOS task */
	printf("Printf Task: %i @ %08x\r\n", (int)
			xTaskCreate(Printf_Task, "Printf_Task", configMINIMAL_STACK_SIZE, NULL, Printf_Task_PRIORITY, NULL),
			(unsigned int)NULL);
	printf("FTM2 Task: %i @ %08x\r\n", (int)
			xTaskCreate(FTM2_IRQ_Task, "FTM2_IRQ_Task", 2*configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES-1, &FTM2_IRQ_TaskHandle),
			(unsigned int)FTM2_IRQ_TaskHandle);
	printf("GPIOA Task: %i @ %08x\r\n", (int)
			xTaskCreate(GPIOA_IRQ_Task, "GPIOA_IRQ_Task", 2*configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES-1, &GPIOA_IRQ_TaskHandle),
			(unsigned int)GPIOA_IRQ_TaskHandle);
	printf("GPIOC Task: %i @ %08x\r\n", (int)
			xTaskCreate(GPIOC_IRQ_Task, "GPIOC_IRQ_Task", 2*configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES-1, &GPIOC_IRQ_TaskHandle),
			(unsigned int)GPIOC_IRQ_TaskHandle);

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details.  */
	for(;;) { /* Infinite loop to avoid leaving the main function */
		__asm("NOP"); /* something to use as a breakpoint stop while looping */
	}
}





