/*
 * App_Globals.cpp
 *
 *  Created on: Jul 21, 2016
 *      Author: Althaf.Ismail
 */

// Freerad Includes
#include "App_Globals.h"

QueueHandle_t Q_Printf = NULL;

TaskHandle_t GPIOA_IRQ_TaskHandle;
TaskHandle_t GPIOC_IRQ_TaskHandle;
TaskHandle_t FTM2_IRQ_TaskHandle;

char logString[PRINTF_STRING_SIZE] = {0};
