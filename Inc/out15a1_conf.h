/**
  ******************************************************************************
  * @file           : out15a1_conf.h
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
#ifndef OUT15A1_CONF_H
#define OUT15A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "ips1025hf.h"

/** @addtogroup OUT_15_Example OUT_15_Example
  * @{
  */

/** @addtogroup OUT_15_Example_Conf OUT_15_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_15_Example_Conf_Exported_Constants OUT_15_Example Conf Exported Constants
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

#define H_EXTI_LINE_OUT_FB EXTI_LINE_10
#define H_EXTI_10 hexti10
#define H_EXTI_OUT_FB hexti10

/** This is the HW configuration section: OUT_FB_Pin */
#define OUT_FB_Pin GPIO_PIN_10
/** This is the HW configuration section: OUT_FB_GPIO_Port */
#define OUT_FB_GPIO_Port GPIOA
/** This is the HW configuration section: OUT_FB_EXTI_IRQn */
#define OUT_FB_EXTI_IRQn EXTI15_10_IRQn

/** This is the HW configuration section: Nch_DRV_Pin */
#define Nch_DRV_Pin GPIO_PIN_9
/** This is the HW configuration section: Nch_DRV_GPIO_Port */
#define Nch_DRV_GPIO_Port GPIOA
/** This is the HW configuration section: IN1_Pin */
#define IN1_Pin GPIO_PIN_6
/** This is the HW configuration section: IN1_GPIO_Port */
#define IN1_GPIO_Port GPIOB

/** CHIP ID  */
#define IPS_SWITCH_CHIP_ID IPS1025HF_CHIP_ID

/** Maximum number of devices supported */
#define IPS_SWITCH_DEVICES_NBR IPS1025HF_DEVICES_NBR

/** Maximum channel frequency in tenth of Hz */
#define IPS_SWITCH_MAX_CHAN_FREQ IPS1025HF_MAX_CHAN_FREQ

/** Max number of channels by switch IPS1025HF */
#define IPS_SWITCH_MAX_NB_CHANNELS IPS1025HF_MAX_NB_CHANNELS

/* Dev pins for IPS1025HF */
/* Board 0 */
/** Device Chan: IN1 0 */
#define IPS_SWITCH_0_IN1 IPS1025HF_0_IN1

/** Board Control Pin: Nch_DRV 0 */
#define IPS_SWITCH_0_NCH_DRV IPS1025HF_0_NCH_DRV
/** Board Control Pin: OUT_FB 0 */
#define IPS_SWITCH_0_OUT_FB IPS1025HF_0_OUT_FB

/** IN1 Port 0 */
#define IPS_SWITCH_0_IN1_GPIO_PORT IPS1025HF_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define IPS_SWITCH_0_IN1_GPIO_PIN IPS1025HF_0_IN1_GPIO_PIN
/** FLT1 Port 0 */
#define IPS_SWITCH_0_FLT1_GPIO_PORT IPS1025HF_0_FLT1_GPIO_PORT
/** FLT1 Pin 0 */
#define IPS_SWITCH_0_FLT1_GPIO_PIN IPS1025HF_0_FLT1_GPIO_PIN
/** FLT2 Port 0 */
#define IPS_SWITCH_0_FLT2_GPIO_PORT IPS1025HF_0_FLT2_GPIO_PORT
/** FLT2 Pin 0 */
#define IPS_SWITCH_0_FLT2_GPIO_PIN IPS1025HF_0_FLT2_GPIO_PIN
/** Nch-DRV Port 0 */
#define IPS_SWITCH_0_NCH_DRV_GPIO_PORT IPS1025HF_0_NCH_DRV_GPIO_PORT
/** Nch-DRV Pin 0 */
#define IPS_SWITCH_0_NCH_DRV_GPIO_PIN IPS1025HF_0_NCH_DRV_GPIO_PIN
/** OUT_FB Port 0 */
#define IPS_SWITCH_0_OUT_FB_GPIO_PORT IPS1025HF_0_OUT_FB_GPIO_PORT
/** OUT_FB Pin 0 */
#define IPS_SWITCH_0_OUT_FB_GPIO_PIN IPS1025HF_0_OUT_FB_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_15_Example_Conf_Exported_Variables OUT_15_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti9;
extern EXTI_HandleTypeDef hexti0;
extern EXTI_HandleTypeDef hexti10;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_15_Example_Conf_Exported_Macros OUT_15_Example Conf Exported Macros
  * @{
  */

/** Customization of generic driver function */
#define OUT15_GetTick         BSP_GetTick
/** Customization of generic driver function */
#define OUT15_WriteChan       OUT15_SetChanInputPin
/** Customization of generic driver function */
#define OUT15_ReadChan        OUT15_GetChanInputPin
/** Customization of generic driver function */
#define OUT15_WriteAllChan    OUT15_SetAllChanInputPin
/** Customization of generic driver function */
#define OUT15_ReadAllChan     OUT15_GetAllChanInputPin
/** Customization of generic driver function */
#define OUT15_ReadFault       OUT15_ReadFaultPin
/** Customization of generic driver function */
#define OUT15_SetPwm          OUT15_SetTimerForPwm
/** Customization of generic driver function */
#define OUT15_WritePin        OUT15_SetControlPin
/** Customization of generic driver function */
#define OUT15_ReadPin         OUT15_GetControlPin

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_15_Example_Conf_Exported_Functions OUT_15_Example Conf Exported Functions
  * @{
  */

int32_t OUT15_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT15A1_CONF_H */
