/*
 * App_Globals.h
 *
 *  Created on: Jul 21, 2016
 *      Author: Althaf.Ismail
 */

#ifndef SOURCE_APP_GLOBALS_H_
#define SOURCE_APP_GLOBALS_H_

// KSDK includes
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"
#include "fsl_smc.h"
#include "fsl_ftm.h"

// FreeRTOS kernel includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/////////////
// Defines //
/////////////

// Pinouts
#define PIN_RESET_SHARC		GPIOA, 6
#define BIT_RESET_SHARC		GPIOA, 1<<6
#define PORT_RESET_SHARC	PORTA, 6

#define PIN_SWITCH			GPIOA, 9
#define BIT_SWITCH			GPIOA, 1<<9
#define PORT_SWITCH			PORTA, 9

#define PIN_RESET_CODEC		GPIOC, 1
#define BIT_RESET_CODEC		GPIOC, 1<<1
#define PORT_RESET_CODEC	PORTC, 1

#define PIN_PUSHBUTTON		GPIOC, 6
#define BIT_PUSHBUTTON		GPIOC, 1<<6
#define PORT_PUSHBUTTON		PORTC, 6

#define PIN_RESET_ULTIMO	GPIOE, 3
#define BIT_RESET_ULTIMO	GPIOE, 1<<3
#define PORT_RESET_ULTIMO	PORTE, 3

#define PIN_LED_A			GPIOE, 4
#define BIT_LED_A			GPIOE, 1<<4
#define PORT_LED_A			PORTE, 4

#define PIN_AMP_STANDBY		GPIOE, 7
#define BIT_AMP_STANDBY		GPIOE, 1<<7
#define PORT_AMP_STANDBY	PORTE, 7

#define PIN_LED_B			GPIOE, 27
#define BIT_LED_B			GPIOE, 1<<27
#define PORT_LED_B			PORTE, 27

#define PORT_UART4_RX		PORTC, 14
#define PORT_UART4_TX		PORTC, 15

#define PORT_FTM2_QD_A		PORTA, 10
#define PORT_FTM2_QD_B		PORTA, 11

//////////////////////
// Constant Defines //
//////////////////////

#define PRINTF_STRING_SIZE	0x80



////////////////
// Prototypes //
////////////////

#ifdef __cplusplus
extern "C"
{
#endif

extern QueueHandle_t Q_Printf;

extern TaskHandle_t GPIOA_IRQ_TaskHandle;
extern TaskHandle_t GPIOC_IRQ_TaskHandle;
extern TaskHandle_t FTM2_IRQ_TaskHandle;

extern char logString[PRINTF_STRING_SIZE];

#ifdef __cplusplus
}
#endif	// __cplusplus

#endif /* SOURCE_APP_GLOBALS_H_ */
