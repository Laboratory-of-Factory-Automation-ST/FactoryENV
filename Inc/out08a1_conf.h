/**
  ******************************************************************************
  * @file           : out08a1_conf.h
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
#ifndef OUT08A1_CONF_H
#define OUT08A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "ips160hf.h"

/** @addtogroup OUT_08_Example OUT_08_Example
  * @{
  */

/** @addtogroup OUT_08_Example_Conf OUT_08_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_08_Example_Conf_Exported_Constants OUT_08_Example Conf Exported Constants
  * @{
  */

#define USE_BOARD_0 1

#define H_EXTI_LINE_DIAG EXTI_LINE_9
#define H_EXTI_9 hexti9
#define H_EXTI_DIAG hexti9
#define DIAG_Pin  GPIO_PIN_9
#define DIAG_GPIO_Port  GPIOB
#define DIAG_EXTI_IRQn  EXTI9_5_IRQn

#define H_EXTI_LINE_OUT_FB EXTI_LINE_0
#define H_EXTI_0 hexti0
#define H_EXTI_OUT_FB hexti0

/** This is the HW configuration section: OUT_FB_Pin */
#define OUT_FB_Pin GPIO_PIN_0
/** This is the HW configuration section: OUT_FB_GPIO_Port */
#define OUT_FB_GPIO_Port GPIOB
/** This is the HW configuration section: OUT_FB_EXTI_IRQn */
#define OUT_FB_EXTI_IRQn EXTI0_IRQn

/** This is the HW configuration section: Nch_DRV_Pin */
#define Nch_DRV_Pin GPIO_PIN_5
/** This is the HW configuration section: Nch_DRV_GPIO_Port */
#define Nch_DRV_GPIO_Port GPIOB
/** This is the HW configuration section: IN1_Pin */
#define IN1_Pin GPIO_PIN_6
/** This is the HW configuration section: IN1_GPIO_Port */
#define IN1_GPIO_Port GPIOB

/** CHIP ID */
#define IPS_SWITCH_CHIP_ID IPS160HF_CHIP_ID

/** Maximum number of devices supported */
#define IPS_SWITCH_DEVICES_NBR IPS160HF_DEVICES_NBR

/** Maximum channel frequency in tenth of Hz */
#define IPS_SWITCH_MAX_CHAN_FREQ IPS160HF_MAX_CHAN_FREQ

/** Max number of channels by switch IPS160HF */
#define IPS_SWITCH_MAX_NB_CHANNELS IPS160HF_MAX_NB_CHANNELS

/* Dev pins for IPS160HF */
/* Board 0 */
/** Device Chan: IN1 0 */
#define IPS_SWITCH_0_IN1 IPS160HF_0_IN1

/** Board Control Pin: Nch_DRV 0 */
#define IPS_SWITCH_0_NCH_DRV IPS160HF_0_NCH_DRV
/** Board Control Pin: OUT_FB 0 */
#define IPS_SWITCH_0_OUT_FB IPS160HF_0_OUT_FB

/** IN1 Port 0 */
#define IPS_SWITCH_0_IN1_GPIO_PORT IPS160HF_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define IPS_SWITCH_0_IN1_GPIO_PIN IPS160HF_0_IN1_GPIO_PIN
/** DIAG Port 0 */
#define IPS_SWITCH_0_DIAG_GPIO_PORT IPS160HF_0_DIAG_GPIO_PORT
/** DIAG Pin 0 */
#define IPS_SWITCH_0_DIAG_GPIO_PIN IPS160HF_0_DIAG_GPIO_PIN
/** Nch-DRV Port 0 */
#define IPS_SWITCH_0_NCH_DRV_GPIO_PORT IPS160HF_0_NCH_DRV_GPIO_PORT
/** Nch-DRV Pin 0 */
#define IPS_SWITCH_0_NCH_DRV_GPIO_PIN IPS160HF_0_NCH_DRV_GPIO_PIN
/** OUT_FB Port 0 */
#define IPS_SWITCH_0_OUT_FB_GPIO_PORT IPS160HF_0_OUT_FB_GPIO_PORT
/** OUT_FB Pin 0 */
#define IPS_SWITCH_0_OUT_FB_GPIO_PIN IPS160HF_0_OUT_FB_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_08_Example_Conf_Exported_Variables OUT_08_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti9;
extern EXTI_HandleTypeDef hexti0;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_08_Example_Conf_Exported_Macros OUT_08_Example Conf Exported Macros
  * @{
  */

/** Customization of generic driver function */
#define OUT08_GetTick         BSP_GetTick
/** Customization of generic driver function */
#define OUT08_WriteChan       OUT08_SetChanInputPin
/** Customization of generic driver function */
#define OUT08_ReadChan        OUT08_GetChanInputPin
/** Customization of generic driver function */
#define OUT08_WriteAllChan    OUT08_SetAllChanInputPin
/** Customization of generic driver function */
#define OUT08_ReadAllChan     OUT08_GetAllChanInputPin
/** Customization of generic driver function */
#define OUT08_ReadFault       OUT08_ReadFaultPin
/** Customization of generic driver function */
#define OUT08_SetPwm          OUT08_SetTimerForPwm
/** Customization of generic driver function */
#define OUT08_WritePin        OUT08_SetControlPin
/** Customization of generic driver function */
#define OUT08_ReadPin         OUT08_GetControlPin

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_08_Example_Conf_Exported_Functions OUT_08_Example Conf Exported Functions
  * @{
  */

int32_t OUT08_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT08A1_CONF_H */
