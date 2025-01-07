/**
  ******************************************************************************
  * @file    eval_core.h
  * @brief   This file contains the definition of core hardware evaluation
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APPLICATION_FACTORY_LAB_DRIVER_MODULES_INC_EVAL_CORE_H_
#define APPLICATION_FACTORY_LAB_DRIVER_MODULES_INC_EVAL_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum Board_ctx_t {
	OUT16A1
} BoardContext_Typedef;

typedef enum Setup_ctx_t {
	_default
} SetupContext_Typedef;

typedef struct Pinout_t {
	GPIO_TypeDef * IN1_GPort;
	uint16_t IN1_GPin;
	GPIO_TypeDef * IN2_GPort;
	uint16_t IN2_GPin;
	GPIO_TypeDef * IN3_GPort;
	uint16_t IN3_GPin;
	GPIO_TypeDef * IN4_GPort;
	uint16_t IN4_GPin;
	GPIO_TypeDef * IN5_GPort;
	uint16_t IN5_GPin;
	GPIO_TypeDef * IN6_GPort;
	uint16_t IN6_GPin;
	GPIO_TypeDef * IN7_GPort;
	uint16_t IN7_GPin;
	GPIO_TypeDef * IN8_GPort;
	uint16_t IN8_GPin;
} Pinout_Typedef;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern Pinout_Typedef Pinout;

/* Exported functions prototypes ---------------------------------------------*/
void usr_btn_routine(const uint8_t board_ctx, const uint8_t setup_ctx);
void set_chan_state(const uint8_t board_ctx, const uint8_t chan_state_bits);
void usr_btn_pressed_callback();

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_FACTORY_LAB_DRIVER_MODULES_INC_EVAL_CORE_H_ */
