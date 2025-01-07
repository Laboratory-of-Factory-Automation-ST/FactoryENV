/**
  ******************************************************************************
  * @file    eval_core.c
  * @brief   This file containts the implementation of core hardware evaluation
  * 		 utilities.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "../../exclude/inc/eval_core.h"

#include "main.h"
#include "app_ips_custom.h"
#include "out16a1.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define ROUTINE_CONTEXT(board_ctx, setup_ctx, step) ((board_ctx << 16) + (setup_ctx << 8) + step)

/* Private variables ---------------------------------------------------------*/
_Bool usr_btn_pressed = 0;
uint8_t usr_btn_routine_step = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
Pinout_Typedef Pinout = {
	.IN1_GPort = IN1_GPIO_Port,
	.IN1_GPin = IN1_Pin,
	.IN2_GPort = IN2_GPIO_Port,
	.IN2_GPin = IN2_Pin,
	.IN3_GPort = IN3_GPIO_Port,
	.IN3_GPin = IN3_Pin,
	.IN4_GPort = IN4_GPIO_Port,
	.IN4_GPin = IN4_Pin,
	.IN5_GPort = IN5_GPIO_Port,
	.IN5_GPin = IN5_Pin,
	.IN6_GPort = IN6_GPIO_Port,
	.IN6_GPin = IN6_Pin,
	.IN7_GPort = SPI_SS_IN7_GPIO_Port,
	.IN7_GPin = SPI_SS_IN7_Pin,
	.IN8_GPort = IN8_GPIO_Port,
	.IN8_GPin = IN8_Pin
};

/*
 * @brief Main implementation of user button routine
 * @param Board context specifier from Board_ctx_t enumeration
 * @param Setup context specifier from Setup_ctx_t enumeration
 * @retval None
 */
void usr_btn_routine(const uint8_t board_ctx, const uint8_t setup_ctx) {
	uint8_t ctrlMode;
	if (usr_btn_pressed != 0) {
		/* Debouncing */
		HAL_Delay(50);

		/* Wait until the button is released */
		while ((HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN) == GPIO_PIN_RESET));

		/* Debouncing */
		HAL_Delay(50);

		usr_btn_pressed = 0;

		switch (ROUTINE_CONTEXT(board_ctx, setup_ctx, usr_btn_routine_step)) {
			case ROUTINE_CONTEXT(OUT16A1, _default, 0):
				OUT16_RELAY_SetOperatingMode(OUT16_BOARD_0, &ctrlMode);
				OUT16_RELAY_SetCtrlPinStatus(OUT16_BOARD_0, OUT16_RELAY_0_OUT_EN, 1U);
//				OUT16_RELAY_SetAllChannelStatus(OUT16_BOARD_0, 0xFFU);
				set_chan_state(OUT16A1, 0xFFU);
				usr_btn_routine_step += 1;
				break;
			case ROUTINE_CONTEXT(OUT16A1, _default, 1):
//				OUT16_RELAY_SetAllChannelStatus(OUT16_BOARD_0, 0x00U);
				set_chan_state(OUT16A1, 0x00U);
				usr_btn_routine_step += 1;
				break;
			case ROUTINE_CONTEXT(OUT16A1, _default, 2):
				OUT16_RELAY_SetChannelFreq(OUT16_BOARD_0, OUT16_RELAY_0_IN1, 100U);
				OUT16_RELAY_SetChannelDc(OUT16_BOARD_0, OUT16_RELAY_0_IN1, 20U);
				OUT16_RELAY_SetPwmEnable(OUT16_BOARD_0, OUT16_RELAY_0_IN1, 1U);
				usr_btn_routine_step += 1;
				break;
			default:
				OUT16_RELAY_SetCtrlPinStatus(OUT16_BOARD_0, OUT16_RELAY_0_OUT_EN, 0U);
				usr_btn_routine_step = 0;
				break;
		}
	}
}

/*
 * @brief Universal function for changing channel state
 * @param Board context specifier from Board_ctx_t enumeration
 * @param Bits representing the state of all channels
 * @retval None
 */
void set_chan_state(const uint8_t board_ctx, const uint8_t chan_state_bits) {
	_Bool is_serial = HAL_GPIO_ReadPin(SEL2_GPIO_Port, SEL2_Pin);

	if (is_serial) {
		switch (board_ctx) {
			case OUT16A1:
				OUT16_RELAY_SetAllChannelStatus(OUT16_BOARD_0, chan_state_bits);
				break;
			default:
				break;
		}
	} else {
		switch (board_ctx) {
			case OUT16A1:
				HAL_GPIO_WritePin(Pinout.IN1_GPort, Pinout.IN1_GPin, (GPIO_PinState)(chan_state_bits & 0x1U));
				HAL_GPIO_WritePin(Pinout.IN2_GPort, Pinout.IN2_GPin, (GPIO_PinState)((chan_state_bits >> 1U) & 0x1U));
				HAL_GPIO_WritePin(Pinout.IN3_GPort, Pinout.IN3_GPin, (GPIO_PinState)((chan_state_bits >> 2U) & 0x1U));
				HAL_GPIO_WritePin(Pinout.IN4_GPort, Pinout.IN4_GPin, (GPIO_PinState)((chan_state_bits >> 3U) & 0x1U));
				HAL_GPIO_WritePin(Pinout.IN5_GPort, Pinout.IN5_GPin, (GPIO_PinState)((chan_state_bits >> 4U) & 0x1U));
				HAL_GPIO_WritePin(Pinout.IN6_GPort, Pinout.IN6_GPin, (GPIO_PinState)((chan_state_bits >> 5U) & 0x1U));
				HAL_GPIO_WritePin(Pinout.IN7_GPort, Pinout.IN7_GPin, (GPIO_PinState)((chan_state_bits >> 6U) & 0x1U));
				HAL_GPIO_WritePin(Pinout.IN8_GPort, Pinout.IN8_GPin, (GPIO_PinState)((chan_state_bits >> 7U) & 0x1U));
				break;
			default:
				break;
		}
	}
}

/*
 * @brief Custom callback handler of user button presses
 * @retval None
 */
void usr_btn_pressed_callback() {
	usr_btn_pressed = 1;
}

/*
 * @brief Override of timer callback on elapsed period
 * @param Timer handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

}
