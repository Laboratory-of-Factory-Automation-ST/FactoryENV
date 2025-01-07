/**
  ******************************************************************************
  * @file           : out03a1_conf.h
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
#ifndef OUT03A1_CONF_H
#define OUT03A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "ips2050h.h"

/** @addtogroup OUT_03_Example OUT_03_Example
  * @{
  */

/** @addtogroup OUT_03_Example_Conf OUT_03_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_03_Example_Conf_Exported_Constants OUT_03_Example Conf Exported Constants
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
/** This is the HW configuration section: IN2_Pin */
#define IN2_Pin GPIO_PIN_5
/** This is the HW configuration section: IN2_GPIO_Port */
#define IN2_GPIO_Port GPIOB

/** CHIP ID */
#define IPS_SWITCH_CHIP_ID IPS2050H_CHIP_ID

/** Maximum number of devices supported */
#define IPS_SWITCH_DEVICES_NBR IPS2050H_DEVICES_NBR

/** Maximum channel frequency in tenth of Hz */
#define IPS_SWITCH_MAX_CHAN_FREQ IPS2050H_MAX_CHAN_FREQ

/** Max number of channels by switch IPS2050H */
#define IPS_SWITCH_MAX_NB_CHANNELS IPS2050H_MAX_NB_CHANNELS

/* Dev pins for IPS2050H */
/* Board 0 */
/** IN1 Port 0 */
#define IPS_SWITCH_0_IN1_GPIO_PORT IPS2050H_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define IPS_SWITCH_0_IN1_GPIO_PIN IPS2050H_0_IN1_GPIO_PIN
/** IN2 Port 0 */
#define IPS_SWITCH_0_IN2_GPIO_PORT IPS2050H_0_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define IPS_SWITCH_0_IN2_GPIO_PIN IPS2050H_0_IN2_GPIO_PIN
/** FLT1 Port 0 */
#define IPS_SWITCH_0_FLT1_GPIO_PORT IPS2050H_0_FLT1_GPIO_PORT
/** FLT1 Pin 0 */
#define IPS_SWITCH_0_FLT1_GPIO_PIN IPS2050H_0_FLT1_GPIO_PIN
/** FLT2 Port 0 */
#define IPS_SWITCH_0_FLT2_GPIO_PORT IPS2050H_0_FLT2_GPIO_PORT
/** FLT2 Pin 0 */
#define IPS_SWITCH_0_FLT2_GPIO_PIN IPS2050H_0_FLT2_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_03_Example_Conf_Exported_Variables OUT_03_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti9;
extern EXTI_HandleTypeDef hexti0;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_03_Example_Conf_Exported_Macros OUT_03_Example Conf Exported Macros
  * @{
  */

/** Customization of generic driver function */
#define OUT03_GetTick         BSP_GetTick
/** Customization of generic driver function */
#define OUT03_WriteChan       OUT03_SetChanInputPin
/** Customization of generic driver function */
#define OUT03_ReadChan        OUT03_GetChanInputPin
/** Customization of generic driver function */
#define OUT03_WriteAllChan    OUT03_SetAllChanInputPin
/** Customization of generic driver function */
#define OUT03_ReadAllChan     OUT03_GetAllChanInputPin
/** Customization of generic driver function */
#define OUT03_ReadFault       OUT03_ReadFaultPin
/** Customization of generic driver function */
#define OUT03_SetPwm          OUT03_SetTimerForPwm

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_03_Example_Conf_Exported_Functions OUT_03_Example Conf Exported Functions
  * @{
  */

int32_t OUT03_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT03A1_CONF_H */
