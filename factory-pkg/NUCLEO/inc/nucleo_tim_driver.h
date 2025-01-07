/*
 * nucleo_tim_driver.h
 *
 *  Created on: Jan 3, 2025
 *      Author: marek novotny
 */

#ifndef DRIVERS_BSP_NUCLEO_INC_NUCLEO_TIM_DRIVER_H_
#define DRIVERS_BSP_NUCLEO_INC_NUCLEO_TIM_DRIVER_H_

#include "main.h"

/* Exported vars -------------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

HAL_StatusTypeDef NUCLEO_TIM_PeriodicPulse_Config(TIM_HandleTypeDef * htim, TIM_TypeDef * TIM, uint32_t Channel, uint32_t Time_Base, uint32_t Period_Ticks, uint32_t Pulse_Ticks);
void NUCLEO_TIM_PeriodicPulse_Start(TIM_HandleTypeDef * htim, uint32_t channel);
void NUCLEO_TIM_PeriodicPulse_Stop(TIM_HandleTypeDef *htim, uint32_t channel);
void NUCLEO_TIM_PeriodicPulse_Start_IT(TIM_HandleTypeDef * htim, uint32_t channel);
void NUCLEO_TIM_PeriodicPulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t channel);
void NUCLEO_TIM_PeriodicPulse_IT(TIM_HandleTypeDef * handle, TIM_TypeDef * tmr, uint32_t channel, uint32_t tick, uint32_t period_ticks, uint32_t pulse_ticks);
void NUCLEO_TIM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void NUCLEO_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* DRIVERS_BSP_NUCLEO_INC_NUCLEO_TIM_DRIVER_H_ */
