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

/* This is a template file for pins configuration created by New Kinetis SDK 2.x Project Wizard. Enjoy! */

// KSDK Includes
#include "pin_mux.h"

// Freerad Includes
#include "App_Globals.h"
#include "App_CallbackFunctions.h"

/* Example port config structure with default values
 * If using default values, use PORT_SetPinMux(),
 * else use PORT_SetPinConfig().
 *
 * port_pin_config_t PORT_Cfg_Example = {
 * 		.pullSelect = kPORT_PullDisable,
 * 		.slewRate = kPORT_FastSlewRate,
 * 		.passiveFilterEnable = kPORT_PassiveFilterDisable,
 * 		.openDrainEnable = kPORT_OpenDrainDisable,
 * 		.driveStrength = kPORT_LowDriveStrength,
 * 		.mux = kPORT_MuxAsGpio,
 * 		.lockRegister = kPORT_UnLockRegister
 * 	};
 *
 * 	Port pin interrupt = kPORT_InterruptOrDMADisabled
 *
 * 	Port digital filter = disabled
*/

port_pin_config_t PORT_Cfg_Switch = {
 		.pullSelect = kPORT_PullUp,
 		.slewRate = kPORT_SlowSlewRate,
 		.passiveFilterEnable = kPORT_PassiveFilterEnable,
 		.openDrainEnable = kPORT_OpenDrainDisable,
 		.driveStrength = kPORT_LowDriveStrength,
 		.mux = kPORT_MuxAsGpio,
 		.lockRegister = kPORT_LockRegister
 	};

port_pin_config_t PORT_Cfg_Encoder = {
 		.pullSelect = kPORT_PullUp,
 		.slewRate = kPORT_SlowSlewRate,
 		.passiveFilterEnable = kPORT_PassiveFilterEnable,
 		.openDrainEnable = kPORT_OpenDrainDisable,
 		.driveStrength = kPORT_LowDriveStrength,
 		.mux = kPORT_MuxAlt6,
 		.lockRegister = kPORT_LockRegister
 	};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize all pins used in this example
 */
void BOARD_InitPins(void)
{
	/* Ungate the port clock */
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortE);
	CLOCK_EnableClock(kCLOCK_Ftm2);

	///////////////////////
	// Enable Interrupts //
	///////////////////////

	NVIC_SetPriority(PORTA_IRQn, 5);		// For the switch
	EnableIRQ(PORTA_IRQn);
	NVIC_SetPriority(PORTC_IRQn, 5);		// For the push button
	EnableIRQ(PORTC_IRQn);
	NVIC_SetPriority(FTM2_IRQn, 5);			// For the encoder
	EnableIRQ(FTM2_IRQn);

	///////////////
	// GPIO Pins //
	///////////////

	PORT_SetPinMux(PORT_RESET_SHARC, kPORT_MuxAsGpio);
	PORT_SetPinConfig(PORT_SWITCH, &PORT_Cfg_Switch);

	PORT_SetPinMux(PORT_RESET_CODEC, kPORT_MuxAsGpio);
	PORT_SetPinConfig(PORT_PUSHBUTTON, &PORT_Cfg_Switch);

	PORT_SetPinMux(PORT_RESET_ULTIMO, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORT_LED_A, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORT_AMP_STANDBY, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORT_LED_B, kPORT_MuxAsGpio);

	///////////////
	// UART Pins //
	///////////////

	/* Initialize UART4 pins */
	PORT_SetPinMux(PORT_UART4_TX, kPORT_MuxAlt3);
	PORT_SetPinMux(PORT_UART4_RX, kPORT_MuxAlt3);

	/////////
	// FTM //
	/////////

	PORT_SetPinConfig(PORT_FTM2_QD_A, &PORT_Cfg_Encoder);
	PORT_SetPinConfig(PORT_FTM2_QD_B, &PORT_Cfg_Encoder);
}
