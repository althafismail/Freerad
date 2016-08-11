/*
 * App_CallbackFunctions.c
 *
 *  Created on: Jul 18, 2016
 *      Author: Althaf.Ismail
 */

// C/C++ Includes
#include <stdio.h>

// Freerad includes
#include "App_CallbackFunctions.h"

/*!
 * @brief Timer callback.
 */
void vExampleTimerCallback(TimerHandle_t xTimer)
{
	GPIO_TogglePinsOutput(BIT_LED_A);
}

void PORTA_IRQHandler(void)
{
	uint32_t temp = GPIO_GetPinsInterruptFlags(GPIOA);
	BaseType_t wakeUp = pdFALSE;
	GPIO_ClearPinsInterruptFlags(GPIOA, 0xFFFFFFFF);
	xTaskNotifyFromISR(GPIOA_IRQ_TaskHandle, temp, eSetBits, &wakeUp);
	if(wakeUp == pdTRUE)
		taskYIELD();
}

void PORTC_IRQHandler(void)
{
	uint32_t temp = GPIO_GetPinsInterruptFlags(GPIOC);
	BaseType_t wakeUp = pdFALSE;
	GPIO_ClearPinsInterruptFlags(GPIOC, 0xFFFFFFFF);
	xTaskNotifyFromISR(GPIOC_IRQ_TaskHandle, temp, eSetBits, &wakeUp);
	if(wakeUp == pdTRUE)
		taskYIELD();
}

void FTM2_IRQHandler(void)
{
	uint32_t temp = (FTM2->QDCTRL << 16) | FTM2->CNT;
	BaseType_t wakeUp = pdFALSE;
	FTM2->SC &= 0xFFFFFF7F;
	xTaskNotifyFromISR(FTM2_IRQ_TaskHandle, temp, eSetBits, &wakeUp);
	if(wakeUp == pdTRUE)
		taskYIELD();
}
