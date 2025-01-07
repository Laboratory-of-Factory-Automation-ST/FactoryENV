/**
  ******************************************************************************
  * @file           : out10a1_conf.h
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
#ifndef OUT10A1_CONF_H
#define OUT10A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "ips161hf.h"

/** @addtogroup OUT_10_Example OUT_10_Example
  * @{
  */

/** @addtogroup OUT_10_Example_Conf OUT_10_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_10_Example_Conf_Exported_Constants OUT_10_Example Conf Exported Constants
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
#define IPS_SWITCH_CHIP_ID IPS161HF_CHIP_ID

/** Maximum number of devices supported */
#define IPS_SWITCH_DEVICES_NBR IPS161HF_DEVICES_NBR

/** Maximum channel frequency in tenth of Hz */
#define IPS_SWITCH_MAX_CHAN_FREQ IPS161HF_MAX_CHAN_FREQ

/** Max number of channels by switch IPS161HF */
#define IPS_SWITCH_MAX_NB_CHANNELS IPS161HF_MAX_NB_CHANNELS

/* Dev pins for IPS161HF */
/* Board 0 */
/** Device Chan: IN1 0 */
#define IPS_SWITCH_0_IN1 IPS161HF_0_IN1

/** Board Control Pin: Nch_DRV 0 */
#define IPS_SWITCH_0_NCH_DRV IPS161HF_0_NCH_DRV
/** Board Control Pin: OUT_FB 0 */
#define IPS_SWITCH_0_OUT_FB IPS161HF_0_OUT_FB

/** IN1 Port 0 */
#define IPS_SWITCH_0_IN1_GPIO_PORT IPS161HF_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define IPS_SWITCH_0_IN1_GPIO_PIN IPS161HF_0_IN1_GPIO_PIN
/** DIAG Port 0 */
#define IPS_SWITCH_0_DIAG_GPIO_PORT IPS161HF_0_DIAG_GPIO_PORT
/** DIAG Pin 0 */
#define IPS_SWITCH_0_DIAG_GPIO_PIN IPS161HF_0_DIAG_GPIO_PIN
/** Nch-DRV Port 0 */
#define IPS_SWITCH_0_NCH_DRV_GPIO_PORT IPS161HF_0_NCH_DRV_GPIO_PORT
/** Nch-DRV Pin 0 */
#define IPS_SWITCH_0_NCH_DRV_GPIO_PIN IPS161HF_0_NCH_DRV_GPIO_PIN
/** OUT_FB Port 0 */
#define IPS_SWITCH_0_OUT_FB_GPIO_PORT IPS161HF_0_OUT_FB_GPIO_PORT
/** OUT_FB Pin 0 */
#define IPS_SWITCH_0_OUT_FB_GPIO_PIN IPS161HF_0_OUT_FB_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_10_Example_Conf_Exported_Variables OUT_10_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti9;
extern EXTI_HandleTypeDef hexti0;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_10_Example_Conf_Exported_Macros OUT_10_Example Conf Exported Macros
  * @{
  */

/** Customization of generic driver function */
#define OUT10_GetTick         BSP_GetTick
/** Customization of generic driver function */
#define OUT10_WriteChan       OUT10_SetChanInputPin
/** Customization of generic driver function */
#define OUT10_ReadChan        OUT10_GetChanInputPin
/** Customization of generic driver function */
#define OUT10_WriteAllChan    OUT10_SetAllChanInputPin
/** Customization of generic driver function */
#define OUT10_ReadAllChan     OUT10_GetAllChanInputPin
/** Customization of generic driver function */
#define OUT10_ReadFault       OUT10_ReadFaultPin
/** Customization of generic driver function */
#define OUT10_SetPwm          OUT10_SetTimerForPwm
/** Customization of generic driver function */
#define OUT10_WritePin        OUT10_SetControlPin
/** Customization of generic driver function */
#define OUT10_ReadPin         OUT10_GetControlPin

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_10_Example_Conf_Exported_Functions OUT_10_Example Conf Exported Functions
  * @{
  */

int32_t OUT10_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT10A1_CONF_H */
