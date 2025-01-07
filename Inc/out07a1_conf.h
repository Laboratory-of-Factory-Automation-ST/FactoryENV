/**
  ******************************************************************************
  * @file           : out07a1_conf.h
  * @author         : AMS IPC Application Team
  * @brief          : Header file for the project configuration
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
#ifndef OUT07A1_CONF_H
#define OUT07A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "ips4260l.h"

/** @addtogroup OUT_07_Example OUT_07_Example
  * @{
  */

/** @addtogroup OUT_07_Example_Conf OUT_07_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_07_Example_Conf_Exported_Constants OUT_07_Example Conf Exported Constants
  * @{
  */

#define USE_BOARD_0 1

#define H_EXTI_LINE_DIAG3_L EXTI_LINE_0
#define H_EXTI_0 hexti0
#define H_EXTI_DIAG3_L hexti0
#define H_EXTI_LINE_DIAG4_L EXTI_LINE_1
#define H_EXTI_1 hexti1
#define H_EXTI_DIAG4_L hexti1
#define H_EXTI_LINE_FLT_L EXTI_LINE_4
#define H_EXTI_4 hexti4
#define H_EXTI_FLT_L hexti4
#define H_EXTI_LINE_OL_L EXTI_LINE_5
#define H_EXTI_5 hexti5
#define H_EXTI_OL_L hexti5
#define H_EXTI_LINE_DIAG1_L EXTI_LINE_8
#define H_EXTI_8 hexti8
#define H_EXTI_DIAG1_L hexti8
#define H_EXTI_LINE_DIAG2_L EXTI_LINE_9
#define H_EXTI_9 hexti9
#define H_EXTI_DIAG2_L hexti9

/** This is the HW configuration section: FLT_L_Pin */
#define FLT_L_Pin GPIO_PIN_4
/** This is the HW configuration section: FLT_L_GPIO_Port */
#define FLT_L_GPIO_Port GPIOB
/** This is the HW configuration section: FLT_L_EXTI_IRQn */
#define FLT_L_EXTI_IRQn EXTI4_IRQn

/** This is the HW configuration section: OL_L_Pin */
#define OL_L_Pin GPIO_PIN_5
/** This is the HW configuration section: OL_L_GPIO_Port */
#define OL_L_GPIO_Port GPIOB
/** This is the HW configuration section: OL_L_EXTI_IRQn */
#define OL_L_EXTI_IRQn EXTI9_5_IRQn

/** This is the HW configuration section: DIAG1_L_Pin */
#define DIAG1_L_Pin GPIO_PIN_8
/** This is the HW configuration section: DIAG1_L_GPIO_Port */
#define DIAG1_L_GPIO_Port GPIOB
/** This is the HW configuration section: DIAG1_L_EXTI_IRQn */
#define DIAG1_L_EXTI_IRQn EXTI9_5_IRQn

/** This is the HW configuration section: DIAG2_L_Pin */
#define DIAG2_L_Pin GPIO_PIN_9
/** This is the HW configuration section: DIAG2_L_GPIO_Port */
#define DIAG2_L_GPIO_Port GPIOB
/** This is the HW configuration section: DIAG2_L_EXTI_IRQn */
#define DIAG2_L_EXTI_IRQn EXTI9_5_IRQn

/** This is the HW configuration section: DIAG3_L_Pin */
#define DIAG3_L_Pin GPIO_PIN_0
/** This is the HW configuration section: DIAG3_L_GPIO_Port */
#define DIAG3_L_GPIO_Port GPIOC
/** This is the HW configuration section: DIAG3_L_EXTI_IRQn */
#define DIAG3_L_EXTI_IRQn EXTI0_IRQn

/** This is the HW configuration section: DIAG4_L_Pin */
#define DIAG4_L_Pin GPIO_PIN_1
/** This is the HW configuration section: DIAG4_L_GPIO_Port */
#define DIAG4_L_GPIO_Port GPIOC
/** This is the HW configuration section: DIAG4_L_EXTI_IRQn */
#define DIAG4_L_EXTI_IRQn EXTI1_IRQn

/** This is the HW configuration section: IN1_Pin */
#define IN1_Pin GPIO_PIN_7
/** This is the HW configuration section: IN1_GPIO_Port */
#define IN1_GPIO_Port GPIOC
/** This is the HW configuration section: IN2_Pin */
#define IN2_Pin GPIO_PIN_9
/** This is the HW configuration section: IN2_GPIO_Port */
#define IN2_GPIO_Port GPIOA
/** This is the HW configuration section: IN3_Pin */
#define IN3_Pin GPIO_PIN_8
/** This is the HW configuration section: IN3_GPIO_Port */
#define IN3_GPIO_Port GPIOA
/** This is the HW configuration section: IN4_Pin */
#define IN4_Pin GPIO_PIN_10
/** This is the HW configuration section: IN4_GPIO_Port */
#define IN4_GPIO_Port GPIOB

/** CHIP ID  */
#define IPS_SWITCH_CHIP_ID IPS4260L_CHIP_ID

/** Maximum number of devices supported */
#define IPS_SWITCH_DEVICES_NBR IPS4260L_DEVICES_NBR

/** Maximum channel frequency in tenth of Hz */
#define IPS_SWITCH_MAX_CHAN_FREQ IPS4260L_MAX_CHAN_FREQ

/** Max number of channels supported */
#define IPS_SWITCH_MAX_NB_CHANNELS IPS4260L_MAX_NB_CHANNELS

/* Dev pins for IPS4260L */
/* Board 0 */
/** Input Pin: IN1 */
#define IPS_SWITCH_0_IN1 IPS4260L_0_IN1
/** Input Pin: IN2 */
#define IPS_SWITCH_0_IN2 IPS4260L_0_IN2
/** Input Pin: IN3 */
#define IPS_SWITCH_0_IN3 IPS4260L_0_IN3
/** Input Pin: IN4 */
#define IPS_SWITCH_0_IN4 IPS4260L_0_IN4

/** IN1 Port 0 */
#define IPS_SWITCH_0_IN1_GPIO_PORT IPS4260L_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define IPS_SWITCH_0_IN1_GPIO_PIN IPS4260L_0_IN1_GPIO_PIN
/** IN2 Port 0 */
#define IPS_SWITCH_0_IN2_GPIO_PORT IPS4260L_0_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define IPS_SWITCH_0_IN2_GPIO_PIN IPS4260L_0_IN2_GPIO_PIN
/** IN3 Port 0 */
#define IPS_SWITCH_0_IN3_GPIO_PORT IPS4260L_0_IN3_GPIO_PORT
/** IN3 Pin 0 */
#define IPS_SWITCH_0_IN3_GPIO_PIN IPS4260L_0_IN3_GPIO_PIN
/** IN4 Port 0 */
#define IPS_SWITCH_0_IN4_GPIO_PORT IPS4260L_0_IN4_GPIO_PORT
/** IN4 Pin 0 */
#define IPS_SWITCH_0_IN4_GPIO_PIN IPS4260L_0_IN4_GPIO_PIN

/** FLT_L Port 0 */
#define IPS_SWITCH_0_FLT_L_GPIO_PORT IPS4260L_0_FLT_L_GPIO_PORT
/** FLT_L Pin 0 */
#define IPS_SWITCH_0_FLT_L_GPIO_PIN IPS4260L_0_FLT_L_GPIO_PIN
/** OL_L Port 0 */
#define IPS_SWITCH_0_OL_L_GPIO_PORT IPS4260L_0_OL_L_GPIO_PORT
/** OL_L Pin 0 */
#define IPS_SWITCH_0_OL_L_GPIO_PIN IPS4260L_0_OL_L_GPIO_PIN
/** DIAG1_L Port 0 */
#define IPS_SWITCH_0_DIAG1_L_GPIO_PORT IPS4260L_0_DIAG1_L_GPIO_PORT
/** DIAG1_L Pin 0 */
#define IPS_SWITCH_0_DIAG1_L_GPIO_PIN IPS4260L_0_DIAG1_L_GPIO_PIN
/** DIAG2_L Port 0 */
#define IPS_SWITCH_0_DIAG2_L_GPIO_PORT IPS4260L_0_DIAG2_L_GPIO_PORT
/** DIAG2_L Pin 0 */
#define IPS_SWITCH_0_DIAG2_L_GPIO_PIN IPS4260L_0_DIAG2_L_GPIO_PIN
/** DIAG3_L Port 0 */
#define IPS_SWITCH_0_DIAG3_L_GPIO_PORT IPS4260L_0_DIAG3_L_GPIO_PORT
/** DIAG3_L Pin 0 */
#define IPS_SWITCH_0_DIAG3_L_GPIO_PIN IPS4260L_0_DIAG3_L_GPIO_PIN
/** DIAG4_L Port 0 */
#define IPS_SWITCH_0_DIAG4_L_GPIO_PORT IPS4260L_0_DIAG4_L_GPIO_PORT
/** DIAG4_L Pin 0 */
#define IPS_SWITCH_0_DIAG4_L_GPIO_PIN IPS4260L_0_DIAG4_L_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_07_Example_Conf_Exported_Variables OUT_07_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti0;
extern EXTI_HandleTypeDef hexti1;
extern EXTI_HandleTypeDef hexti4;
extern EXTI_HandleTypeDef hexti5;
extern EXTI_HandleTypeDef hexti8;
extern EXTI_HandleTypeDef hexti9;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_07_Example_Conf_Exported_Macros OUT_07_Example Conf Exported Macros
  * @{
  */

/** Customization of generic driver function */
#define OUT07_GetTick         BSP_GetTick
/** Customization of generic driver function */
#define OUT07_WriteChan       OUT07_SetChanInputPin
/** Customization of generic driver function */
#define OUT07_ReadChan        OUT07_GetChanInputPin
/** Customization of generic driver function */
#define OUT07_WriteAllChan    OUT07_SetAllChanInputPin
/** Customization of generic driver function */
#define OUT07_ReadAllChan     OUT07_GetAllChanInputPin
/** Customization of generic driver function */
#define OUT07_ReadFault       OUT07_ReadFaultPin
/** Customization of generic driver function */
#define OUT07_SetPwm          OUT07_SetTimerForPwm

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_07_Example_Conf_Exported_Functions OUT_07_Example Conf Exported Functions
  * @{
  */

int32_t OUT07_SetTimerForPwm(uint8_t pwmEnable);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* OUT07A1_CONF_H */
