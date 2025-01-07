/**
  ******************************************************************************
  * @file           : out11a1_conf.h
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
#ifndef OUT11A1_CONF_H
#define OUT11A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "iso808.h"

/** @addtogroup OUT_11_Example OUT_11_Example
  * @{
  */

/** @addtogroup OUT_11_Example_Conf OUT_11_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_11_Example_Conf_Exported_Constants OUT_11_Example Conf Exported Constants
  * @{
  */

#define H_EXTI_LINE_STATUS EXTI_LINE_8
#define H_EXTI_8 hexti8
#define H_EXTI_STATUS hexti8

/** This is the HW configuration section: STATUS_Pin */
#define STATUS_Pin GPIO_PIN_8
/** This is the HW configuration section: STATUS_GPIO_Port */
#define STATUS_GPIO_Port GPIOB
/** This is the HW configuration section: STATUS_EXTI_IRQn */
#define STATUS_EXTI_IRQn EXTI9_5_IRQn

/** This is the HW configuration section: SYNCH_Pin */
#define SYNCH_Pin GPIO_PIN_4
/** This is the HW configuration section: SYNCH_GPIO_Port */
#define SYNCH_GPIO_Port GPIOA
/** This is the HW configuration section: OUT_EN_Pin */
#define OUT_EN_Pin GPIO_PIN_1
/** This is the HW configuration section: OUT_EN_GPIO_Port */
#define OUT_EN_GPIO_Port GPIOA
/** This is the HW configuration section: LOAD_Pin */
#define LOAD_Pin GPIO_PIN_1
/** This is the HW configuration section: LOAD_GPIO_Port */
#define LOAD_GPIO_Port GPIOC
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
/** This is the HW configuration section: IN5_Pin */
#define IN5_Pin GPIO_PIN_4
/** This is the HW configuration section: IN5_GPIO_Port */
#define IN5_GPIO_Port GPIOB
/** This is the HW configuration section: IN6_Pin */
#define IN6_Pin GPIO_PIN_5
/** This is the HW configuration section: IN6_GPIO_Port */
#define IN6_GPIO_Port GPIOB
/** This is the HW configuration section: IN7_Pin */
#define IN7_Pin GPIO_PIN_3
/** This is the HW configuration section: IN7_GPIO_Port */
#define IN7_GPIO_Port GPIOB
/** This is the HW configuration section: IN8_Pin */
#define IN8_Pin GPIO_PIN_10
/** This is the HW configuration section: IN8_GPIO_Port */
#define IN8_GPIO_Port GPIOA

/** CHIP ID  */
#define IPS_SWITCH_CHIP_ID ISO808_CHIP_ID

/** Maximum number of devices supported */
#define IPS_SWITCH_DEVICES_NBR ISO808_DEVICES_NBR

/** Maximum channel frequency in tenth of Hz */
#define IPS_SWITCH_MAX_CHAN_FREQ ISO808_MAX_CHAN_FREQ

/** Max number of channels supported */
#define IPS_SWITCH_MAX_NB_CHANNELS ISO808_MAX_NB_CHANNELS

/** Max number of control pins supported */
#define IPS_SWITCH_MAX_NB_CONTROLS ISO808_MAX_NB_CONTROLS

/** First control pin index */
#define IPS_SWITCH_FIRST_CONTROL ISO808_0_FIRST_CONTROL

/** Synchronous Control mode setting */
#define IPS_SWITCH_SYNC_CTRL_MODE ISO808_SCM

/** Direct Control mode setting */
#define IPS_SWITCH_DIRECT_CTRL_MODE ISO808_DCM

/* Dev pins for ISO808 */
/* Board 0 */
/** Input Pin: IN1 */
#define IPS_SWITCH_0_IN1 ISO808_0_IN1
/** Input Pin: IN2 */
#define IPS_SWITCH_0_IN2 ISO808_0_IN2
/** Input Pin: IN3 */
#define IPS_SWITCH_0_IN3 ISO808_0_IN3
/** Input Pin: IN4 */
#define IPS_SWITCH_0_IN4 ISO808_0_IN4
/** Input Pin: IN5 */
#define IPS_SWITCH_0_IN5 ISO808_0_IN5
/** Input Pin: IN6 */
#define IPS_SWITCH_0_IN6 ISO808_0_IN6
/** Input Pin: IN7 */
#define IPS_SWITCH_0_IN7 ISO808_0_IN7
/** Input Pin: IN8 */
#define IPS_SWITCH_0_IN8 ISO808_0_IN8
/** Control Pin: LOAD */
#define IPS_SWITCH_0_CTRL_LOAD ISO808_0_CTRL_LOAD
/** Control Pin: OUT_EN */
#define IPS_SWITCH_0_CTRL_OUT_EN ISO808_0_CTRL_OUT_EN
/** Control Pin: SYNCH */
#define IPS_SWITCH_0_CTRL_SYNCH ISO808_0_CTRL_SYNCH

/** IN1 Port 0 */
#define IPS_SWITCH_0_IN1_GPIO_PORT ISO808_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define IPS_SWITCH_0_IN1_GPIO_PIN ISO808_0_IN1_GPIO_PIN
/** IN2 Port 0 */
#define IPS_SWITCH_0_IN2_GPIO_PORT ISO808_0_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define IPS_SWITCH_0_IN2_GPIO_PIN ISO808_0_IN2_GPIO_PIN
/** IN3 Port 0 */
#define IPS_SWITCH_0_IN3_GPIO_PORT ISO808_0_IN3_GPIO_PORT
/** IN3 Pin 0 */
#define IPS_SWITCH_0_IN3_GPIO_PIN ISO808_0_IN3_GPIO_PIN
/** IN4 Port 0 */
#define IPS_SWITCH_0_IN4_GPIO_PORT ISO808_0_IN4_GPIO_PORT
/** IN4 Pin 0 */
#define IPS_SWITCH_0_IN4_GPIO_PIN ISO808_0_IN4_GPIO_PIN
/** IN5 Port 0 */
#define IPS_SWITCH_0_IN5_GPIO_PORT ISO808_0_IN5_GPIO_PORT
/** IN5 Pin 0 */
#define IPS_SWITCH_0_IN5_GPIO_PIN ISO808_0_IN5_GPIO_PIN
/** IN6 Port 0 */
#define IPS_SWITCH_0_IN6_GPIO_PORT ISO808_0_IN6_GPIO_PORT
/** IN6 Pin 0 */
#define IPS_SWITCH_0_IN6_GPIO_PIN ISO808_0_IN6_GPIO_PIN
/** IN7 Port 0 */
#define IPS_SWITCH_0_IN7_GPIO_PORT ISO808_0_IN7_GPIO_PORT
/** IN7 Pin 0 */
#define IPS_SWITCH_0_IN7_GPIO_PIN ISO808_0_IN7_GPIO_PIN
/** IN8 Port 0 */
#define IPS_SWITCH_0_IN8_GPIO_PORT ISO808_0_IN8_GPIO_PORT
/** IN8 Pin 0 */
#define IPS_SWITCH_0_IN8_GPIO_PIN ISO808_0_IN8_GPIO_PIN

/** LOAD Port 0 */
#define IPS_SWITCH_0_LOAD_GPIO_PORT ISO808_0_LOAD_GPIO_PORT
/** LOAD Pin 0 */
#define IPS_SWITCH_0_LOAD_GPIO_PIN ISO808_0_LOAD_GPIO_PIN
/** OUT_EN Port 0 */
#define IPS_SWITCH_0_OUT_EN_GPIO_PORT ISO808_0_OUT_EN_GPIO_PORT
/** OUT_EN Pin 0 */
#define IPS_SWITCH_0_OUT_EN_GPIO_PIN ISO808_0_OUT_EN_GPIO_PIN
/** SYNCH Port 0 */
#define IPS_SWITCH_0_SYNCH_GPIO_PORT ISO808_0_SYNCH_GPIO_PORT
/** SYNCH Pin 0 */
#define IPS_SWITCH_0_SYNCH_GPIO_PIN ISO808_0_SYNCH_GPIO_PIN

/** STATUS Port 0 */
#define IPS_SWITCH_0_STATUS_GPIO_PORT ISO808_0_STATUS_GPIO_PORT
/** STATUS Pin 0 */
#define IPS_SWITCH_0_STATUS_GPIO_PIN ISO808_0_STATUS_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_11_Example_Conf_Exported_Variables OUT_11_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti8;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_11_Example_Conf_Exported_Macros OUT_11_Example Conf Exported Macros
  * @{
  */

/** Customization of generic driver function */
#define OUT11_GetTick         BSP_GetTick
/** Customization of generic driver function */
#define OUT11_WriteChan       OUT11_SetChanInputPin
/** Customization of generic driver function */
#define OUT11_ReadChan        OUT11_GetChanInputPin
/** Customization of generic driver function */
#define OUT11_WriteAllChan    OUT11_SetAllChanInputPin
/** Customization of generic driver function */
#define OUT11_ReadAllChan     OUT11_GetAllChanInputPin
/** Customization of generic driver function */
#define OUT11_ReadFault       OUT11_ReadFaultPin
/** Customization of generic driver function */
#define OUT11_SetPwm          OUT11_SetTimerForPwm
/** Customization of generic driver function */
#define OUT11_WritePin        OUT11_SetControlPin
/** Customization of generic driver function */
#define OUT11_ReadPin         OUT11_GetControlPin

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_11_Example_Conf_Exported_Functions OUT_11_Example Conf Exported Functions
  * @{
  */

int32_t OUT11_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT11A1_CONF_H */

