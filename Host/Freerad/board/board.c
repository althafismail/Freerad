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

/* This is a template for board specific configuration created by New Kinetis SDK 2.x Project Wizard. Enjoy! */

// C/C++ Includes
#include <stdint.h>

// KSDK Includes
#include "board.h"

// Freerad Includes
#include "App_Globals.h"

/* Define the init structure for the GPIO pins */
const gpio_pin_config_t GPIO_Cfg_Input = { kGPIO_DigitalInput, 0 };
const gpio_pin_config_t GPIO_Cfg_OutputLo = { kGPIO_DigitalOutput, 0 };
const gpio_pin_config_t GPIO_Cfg_OutputHi = { kGPIO_DigitalOutput, 1 };

/* Define the config structure for the FTM pins */
const ftm_config_t FTM_Cfg_Encoder = {
		.prescale = kFTM_Prescale_Divide_1,			/*!< FTM clock prescale value */
		.bdmMode = kFTM_BdmMode_0,						/*!< FTM behavior in BDM mode */
		.pwmSyncMode = kFTM_SoftwareTrigger,			/*!< Synchronization methods to use to update buffered registers; Multiple
															update modes can be used by providing an OR'ed list of options
															available in enumeration ::ftm_pwm_sync_method_t. */
		.reloadPoints = 0,								/*!< FTM reload points; When using this, the PWM
															synchronization is not required. Multiple reload points can be used by providing
															an OR'ed list of options available in
															enumeration ::ftm_reload_point_t. */
		.faultMode = kFTM_Fault_Disable,				/*!< FTM fault control mode */
		.faultFilterValue = 0,							/*!< Fault input filter value */
		.deadTimePrescale = kFTM_Deadtime_Prescale_1,	/*!< The dead time prescalar value */
		.deadTimeValue = 0,								/*!< The dead time value */
		.extTriggers = 0,								/*!< External triggers to enable. Multiple trigger sources can be
															enabled by providing an OR'ed list of options available in
															enumeration ::ftm_external_trigger_t. */
		.chnlInitState = 0,								/*!< Defines the initialization value of the channels in OUTINT register */
		.chnlPolarity = 0,								/*!< Defines the output polarity of the channels in POL register */
		.useGlobalTimeBase = false						/*!< True: Use of an external global time base is enabled;
															False: disabled */
};

const ftm_phase_params_t FTM_Cfg_Enc_Phase = {
		.enablePhaseFilter = true,				/*!< True: enable phase filter; false: disable filter */
		.phaseFilterVal = 0x8,					/*!< Filter value, used only if phase filter is enabled */
		.phasePolarity = kFTM_QuadPhaseNormal	/*!< Phase polarity */
};

/*!
 * @brief initialize peripherals
 */
void BOARD_InitPeripherals(void)
{
	///////////////////
	// Debug Console //
	///////////////////

	uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;
	DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);

	//////////
	// GPIO //
	//////////

	GPIO_PinInit(PIN_RESET_SHARC, &GPIO_Cfg_OutputLo);
	GPIO_PinInit(PIN_RESET_SHARC, &GPIO_Cfg_Input);

	GPIO_PinInit(PIN_RESET_CODEC, &GPIO_Cfg_OutputLo);
	GPIO_PinInit(PIN_PUSHBUTTON, &GPIO_Cfg_Input);

	GPIO_PinInit(PIN_RESET_ULTIMO, &GPIO_Cfg_OutputLo);
	GPIO_PinInit(PIN_LED_A, &GPIO_Cfg_OutputLo);
	GPIO_PinInit(PIN_AMP_STANDBY, &GPIO_Cfg_OutputHi);
	GPIO_PinInit(PIN_LED_B, &GPIO_Cfg_OutputLo);

	/////////
	// FTM //
	/////////

	FTM_Init(FTM2, &FTM_Cfg_Encoder);
	FTM2->MOD = 0x3;
	FTM2->CNT = 0x1;
	FTM_SetupQuadDecode(FTM2, &FTM_Cfg_Enc_Phase, &FTM_Cfg_Enc_Phase, kFTM_QuadPhaseEncode);
	FTM_StartTimer(FTM2, kFTM_SystemClock);
	FTM2->SC &= 0xFFFFFF7F;
}

