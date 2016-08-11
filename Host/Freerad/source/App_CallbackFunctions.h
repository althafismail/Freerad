/*
 * App_CallbackFunctions.h
 *
 *  Created on: Jul 18, 2016
 *      Author: Althaf.Ismail
 */

#ifndef SOURCE_APP_CALLBACKFUNCTIONS_H_
#define SOURCE_APP_CALLBACKFUNCTIONS_H_

#include "App_Globals.h"

void vExampleTimerCallback(TimerHandle_t xTimer);
void PORTA_IRQHandler(void);
void PORTC_IRQHandler(void);
void FTM2_IRQHandler(void);

#endif /* SOURCE_APP_CALLBACKFUNCTIONS_H_ */
