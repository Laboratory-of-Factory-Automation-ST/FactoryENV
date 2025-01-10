/**
  ******************************************************************************
  * @file    do41a1_mapping.h
  * @brief   This file contains mapping definitions for X-NUCLEO-DO41A1 board.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FACTORY_PKG_DO41A1_INC_DO41A1_MAPPING_H_
#define FACTORY_PKG_DO41A1_INC_DO41A1_MAPPING_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
#include "nucleo_tim_driver.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define DO41A1_IN1_GPIO_Handle "PC7"
#define DO41A1_IN1_GPIO_Port GPIOC
#define DO41A1_IN1_GPIO_Pin	GPIO_PIN_7

#define DO41A1_IN2_GPIO_Handle "PA9"
#define DO41A1_IN2_GPIO_Port GPIOA
#define DO41A1_IN2_GPIO_Pin GPIO_PIN_9

#define DO41A1_IN3_GPIO_Handle "PA8"
#define DO41A1_IN3_GPIO_Port GPIOA
#define DO41A1_IN3_GPIO_Pin GPIO_PIN_8

#define DO41A1_IN4_GPIO_Handle "PB10"
#define DO41A1_IN4_GPIO_Port GPIOB
#define DO41A1_IN4_GPIO_Pin GPIO_PIN_10

#define DO41A1_STATUS1_GPIO_Handle "PB8"
#define DO41A1_STATUS1_GPIO_Port GPIOB
#define DO41A1_STATUS1_GPIO_Pin GPIO_PIN_8

#define DO41A1_STATUS2_GPIO_Handle "PB9"
#define DO41A1_STATUS2_GPIO_Port GPIOB
#define DO41A1_STATUS2_GPIO_Pin GPIO_PIN_9

#define DO41A1_STATUS3_GPIO_Handle "PC0"
#define DO41A1_STATUS3_GPIO_Port GPIOC
#define DO41A1_STATUS3_GPIO_Pin GPIO_PIN_0

#define DO41A1_STATUS4_GPIO_Handle "PC1"
#define DO41A1_STATUS4_GPIO_Port GPIOC
#define DO41A1_STATUS4_GPIO_Pin GPIO_PIN_1

#define DO41A1_IN1_TIMx TIM3
#define DO41A1_IN1_CHx TIM_CHANNEL_2
#define DO41A1_IN1_TIM_Handle &htim3

#define DO41A1_IN2_TIMx TIM1
#define DO41A1_IN2_CHx TIM_CHANNEL_2
#define DO41A1_IN2_TIM_Handle &htim1

#define DO41A1_IN3_TIMx TIM1
#define DO41A1_IN3_CHx TIM_CHANNEL_1
#define DO41A1_IN3_TIM_Handle &htim1

#define DO41A1_IN4_TIMx TIM2
#define DO41A1_IN4_CHx TIM_CHANNEL_3
#define DO41A1_IN4_TIM_Handle &htim2

/* Exported functions prototypes ---------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif
