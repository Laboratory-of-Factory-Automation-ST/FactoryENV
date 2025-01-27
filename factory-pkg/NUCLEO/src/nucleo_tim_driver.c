/**
  ******************************************************************************
  * @file    nucleo_tim_driver.c
  * @author  ST Power Application Laboratory
  * @version V1.0.0
  * @brief   Provides functions for programmable pulse generation
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "nucleo_tim_driver.h"

#define MICROS 1000000

/**
 * @brief Configures parameters of pulse generating timer
 * @param htim: configured PWM timer handle
 * @param TIM: timer struct
 * @param Channel: timer channel
 * @param Time_Base: duration of a tick in microseconds
 * @param Period_Ticks: duration of a period in ticks
 * @param Pulse_Ticks: duration of a pulse in ticks
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_TIM_PeriodicPulse_Config(TIM_HandleTypeDef * htim, TIM_TypeDef * TIM, uint32_t Channel, uint32_t Time_Base, uint32_t Period_Ticks, uint32_t Pulse_Ticks) {
	/* Clock section */
	uint32_t PCLK1Freq = HAL_RCC_GetPCLK1Freq();
	uint32_t PCLK2Freq = HAL_RCC_GetPCLK2Freq();
	if (PCLK1Freq != PCLK2Freq) Error_Handler();
	uint32_t BusFreq = PCLK1Freq;

	uint32_t Prescaler = (BusFreq/MICROS) * Time_Base;

	__HAL_TIM_SET_PRESCALER(htim, Prescaler);
	__HAL_TIM_SET_AUTORELOAD(htim, Period_Ticks < 2 ? 1 : Period_Ticks - 1);
	__HAL_TIM_SET_COMPARE(htim, Channel, Period_Ticks < 2 && Pulse_Ticks == 1 ? 2 : Pulse_Ticks);

	return HAL_OK;
}

/**
 * @brief starts pulse generating timer
 * @param htim: timer handle
 * @param channel: timer channel
 * @retval None
 */
void NUCLEO_TIM_PeriodicPulse_Start(TIM_HandleTypeDef * htim, uint32_t channel) {
	HAL_TIM_PWM_Start(htim, channel);
}

/**
 * @brief stops pulse generating timer
 * @param htim: timer handle
 * @param channel: timer channel
 * @retval None
 */
void NUCLEO_TIM_PeriodicPulse_Stop(TIM_HandleTypeDef * htim, uint32_t channel) {
	HAL_TIM_PWM_Stop(htim, channel);
}

/**
 * @brief starts pulse generating timer in interrupt mode
 * @param htim: timer handle
 * @param channel: timer channel
 * @retval None
 */
void NUCLEO_TIM_PeriodicPulse_Start_IT(TIM_HandleTypeDef * htim, uint32_t channel) {
	HAL_TIM_Base_Start_IT(htim);
	HAL_TIM_PWM_Start_IT(htim, channel);
}

/**
 * @brief runs custom pulse generating timer
 * @param handle: timer handle
 * @param tmr: timer designator
 * @param channel: timer channel
 * @param tick: tick duration in microseconds
 * @param period_ticks: number of ticks in a period
 * @param pulse ticks: number of ticks in a pulse
 * @retval None
 */
void NUCLEO_TIM_RunPeriodicPulse_IT(TIM_HandleTypeDef * handle, TIM_TypeDef * tmr, uint32_t channel, uint32_t tick, uint32_t period_ticks, uint32_t pulse_ticks) {
	NUCLEO_TIM_PeriodicPulse_Config(handle, tmr, channel, tick, period_ticks,
			pulse_ticks);
	NUCLEO_TIM_PeriodicPulse_Start_IT(handle, channel);
}

/**
 * @brief stops pulse generating timer in interrupt mode
 * @param htim: timer handle
 * @param channel: timer channel
 * @retval None
 */
void NUCLEO_TIM_PeriodicPulse_Stop_IT(TIM_HandleTypeDef * htim, uint32_t channel) {
	HAL_TIM_PWM_Stop_IT(htim, channel);
	HAL_TIM_Base_Stop_IT(htim);
}
