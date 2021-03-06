/*
 * App_Tasks.h
 *
 *  Created on: Jul 18, 2016
 *      Author: Althaf.Ismail
 */

#ifndef SOURCE_APP_TASKS_H_
#define SOURCE_APP_TASKS_H_

#include "App_Globals.h"

/* Task priorities. */
#define Printf_Task_PRIORITY (tskIDLE_PRIORITY)

#ifdef __cplusplus
extern "C" {
#endif

void Printf_Task(void *pvParameters);
void GPIOA_IRQ_Task(void *pvParameters);
void GPIOC_IRQ_Task(void *pvParameters);
void FTM2_IRQ_Task(void *pvParameters);

#ifdef __cplusplus
}	 // extern "C" {
#endif

#endif /* SOURCE_APP_TASKS_H_ */
