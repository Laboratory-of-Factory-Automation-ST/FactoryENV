/**
  ******************************************************************************
  * @file           : out06a1_conf.h
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
#ifndef OUT06A1_CONF_H
#define OUT06A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "ips1025h_32.h"

/** @addtogroup OUT_06_Example OUT_06_Example
  * @{
  */

/** @addtogroup OUT_06_Example_Conf OUT_06_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_06_Example_Conf_Exported_Constants OUT_06_Example Conf Exported Constants
  * @{
  */

#define USE_BOARD_0 1

#define H_EXTI_LINE_FLT1 EXTI_LINE_9
#define H_EXTI_9 hexti9
#define H_EXTI_FLT1 hexti9
#define FLT1_Pin  GPIO_PIN_9
#define FLT1_GPIO_Port  GPIOB
#define FLT1_EXTI_IRQn  EXTI9_5_IRQn

#define H_EXTI_LINE_FLT2 EXTI_LINE_0
#define H_EXTI_0 hexti0
#define H_EXTI_FLT2 hexti0
#define FLT2_Pin  GPIO_PIN_0
#define FLT2_GPIO_Port  GPIOB
#define FLT2_EXTI_IRQn  EXTI0_IRQn

/** This is the HW configuration section: IN1_Pin */
#define IN1_Pin GPIO_PIN_6
/** This is the HW configuration section: IN1_GPIO_Port */
#define IN1_GPIO_Port GPIOB

/** CHIP ID */
#define IPS_SWITCH_CHIP_ID IPS1025H_32_CHIP_ID

/** Maximum number of devices supported */
#define IPS_SWITCH_DEVICES_NBR IPS1025H_32_DEVICES_NBR

/** Maximum channel frequency in tenth of Hz */
#define IPS_SWITCH_MAX_CHAN_FREQ IPS1025H_32_MAX_CHAN_FREQ

/** Max number of channels by switch IPS1025H_32 */
#define IPS_SWITCH_MAX_NB_CHANNELS IPS1025H_32_MAX_NB_CHANNELS

/* Dev pins for IPS1025H_32 */
/* Board 0 */
/** IN1 Port 0 */
#define IPS_SWITCH_0_IN1_GPIO_PORT IPS1025H_32_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define IPS_SWITCH_0_IN1_GPIO_PIN IPS1025H_32_0_IN1_GPIO_PIN
/** FLT1 Port 0 */
#define IPS_SWITCH_0_FLT1_GPIO_PORT IPS1025H_32_0_FLT1_GPIO_PORT
/** FLT1 Pin 0 */
#define IPS_SWITCH_0_FLT1_GPIO_PIN IPS1025H_32_0_FLT1_GPIO_PIN
/** FLT2 Port 0 */
#define IPS_SWITCH_0_FLT2_GPIO_PORT IPS1025H_32_0_FLT2_GPIO_PORT
/** FLT2 Pin 0 */
#define IPS_SWITCH_0_FLT2_GPIO_PIN IPS1025H_32_0_FLT2_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_06_Example_Conf_Exported_Variables OUT_06_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti9;
extern EXTI_HandleTypeDef hexti0;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_06_Example_Conf_Exported_Macros OUT_06_Example Conf Exported Macros
  * @{
  */

/** Customization of generic driver function */
#define OUT06_GetTick         BSP_GetTick
/** Customization of generic driver function */
#define OUT06_WriteChan       OUT06_SetChanInputPin
/** Customization of generic driver function */
#define OUT06_ReadChan        OUT06_GetChanInputPin
/** Customization of generic driver function */
#define OUT06_WriteAllChan    OUT06_SetAllChanInputPin
/** Customization of generic driver function */
#define OUT06_ReadAllChan     OUT06_GetAllChanInputPin
/** Customization of generic driver function */
#define OUT06_ReadFault       OUT06_ReadFaultPin
/** Customization of generic driver function */
#define OUT06_SetPwm          OUT06_SetTimerForPwm

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_06_Example_Conf_Exported_Functions OUT_06_Example Conf Exported Functions
  * @{
  */

int32_t OUT06_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT06A1_CONF_H */
