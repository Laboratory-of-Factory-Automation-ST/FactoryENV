/**
  ******************************************************************************
  * @file           : out14a1_conf.h
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
#ifndef OUT14A1_CONF_H
#define OUT14A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_bus.h"
#include "iso808a_1.h"

/** @addtogroup OUT_14_Example OUT_14_Example
  * @{
  */

/** @addtogroup OUT_14_Example_Conf OUT_14_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_14_Example_Conf_Exported_Constants OUT_14_Example Conf Exported Constants
  * @{
  */

#define USE_BOARD_0 1
#define USE_BOARD_1 1

#define H_EXTI_LINE_PGOOD EXTI_LINE_9
#define H_EXTI_9 hexti9
#define H_EXTI_PGOOD hexti9
#define PGOOD_Pin  GPIO_PIN_9
#define PGOOD_GPIO_Port  GPIOB
#define PGOOD_EXTI_IRQn  EXTI9_5_IRQn

#define H_EXTI_LINE_STATUS EXTI_LINE_8
#define H_EXTI_8 hexti8
#define H_EXTI_STATUS hexti8

/** This is the HW configuration section: STATUS_Pin */
#define STATUS_Pin GPIO_PIN_8
/** This is the HW configuration section: STATUS_GPIO_Port */
#define STATUS_GPIO_Port GPIOB
/** This is the HW configuration section: STATUS_EXTI_IRQn */
#define STATUS_EXTI_IRQn EXTI9_5_IRQn

/** This is the HW configuration section: SPI_SS_Pin */
#define SPI_SS_Pin GPIO_PIN_6
/** This is the HW configuration section: SPI_SS_GPIO_Port */
#define SPI_SS_GPIO_Port GPIOB
/** This is the HW configuration section: OUT_EN_Pin */
#define OUT_EN_Pin GPIO_PIN_1
/** This is the HW configuration section: OUT_EN_GPIO_Port */
#define OUT_EN_GPIO_Port GPIOA

#define H_EXTI_LINE_PGOOD_Alt1 EXTI_LINE_5
#define H_EXTI_5 hexti5
#define H_EXTI_PGOOD_Alt1 hexti5
#define PGOOD_Alt1_Pin GPIO_PIN_5
#define PGOOD_Alt1_GPIO_Port  GPIOB
#define PGOOD_Alt1_EXTI_IRQn  EXTI9_5_IRQn

#define H_EXTI_LINE_STATUS_Alt1 EXTI_LINE_10
#define H_EXTI_10 hexti10
#define H_EXTI_STATUS_Alt1 hexti10

/** This is the HW configuration section: STATUS_Alt1_Pin */
#define STATUS_Alt1_Pin GPIO_PIN_10
/** This is the HW configuration section: STATUS_Alt1_GPIO_Port */
#define STATUS_Alt1_GPIO_Port GPIOB
/** This is the HW configuration section: STATUS_Alt1_EXTI_IRQn */
#define STATUS_Alt1_EXTI_IRQn EXTI15_10_IRQn

/** This is the HW configuration section: SPI_SS_Alt1_Pin */
#define SPI_SS_Alt1_Pin GPIO_PIN_8
/** This is the HW configuration section: SPI_SS_Alt1_GPIO_Port */
#define SPI_SS_Alt1_GPIO_Port GPIOA
/** This is the HW configuration section: OUT_EN_Alt1_Pin */
#define OUT_EN_Alt1_Pin GPIO_PIN_10
/** This is the HW configuration section: OUT_EN_Alt1_GPIO_Port */
#define OUT_EN_Alt1_GPIO_Port GPIOA

/** CHIP ID  */
#define IPS_RELAY_CHIP_ID ISO808A_1_CHIP_ID

/** Number of supported relay devices*/
#define IPS_RELAY_DEVICES_NBR ISO808A_1_DEVICES_NBR

/** Undefined Control mode setting */
#define IPS_RELAY_UNDEF_MODE ISO808A_1_NONE

/** Regular (Parallel Independent) mode setting */
#define IPS_RELAY_PAR_IND_MODE ISO808A_1_PIM

/** Daisy Chain mode setting */
#define IPS_RELAY_DAISY_CHAIN_MODE ISO808A_1_DCM

/** Fully populated system in daisy chain mode */
#define IPS_RELAY_DAISY_CHAIN_FULLSYS ISO808A_1_DCM_FULLSYS

/** SPI frequency for relay */
#define IPS_RELAY_CONF_PARAM_SPI_FREQ ISO808A_1_CONF_PARAM_SPI_FREQ

/** Tcss delay in us */
#define IPS_RELAY_CONF_PARAM_TIMING_TCSS ISO808A_1_CONF_PARAM_TIMING_TCSS

/* Dev pins for ISO808A_1 */
/* Board 0 */
/** Device Chan: IN1 */
#define IPS_RELAY_0_IN1 ISO808A_1_0_IN1
/** Device Chan: IN2 */
#define IPS_RELAY_0_IN2 ISO808A_1_0_IN2
/** Device Chan: IN3 */
#define IPS_RELAY_0_IN3 ISO808A_1_0_IN3
/** Device Chan: IN4 */
#define IPS_RELAY_0_IN4 ISO808A_1_0_IN4
/** Device Chan: IN5 */
#define IPS_RELAY_0_IN5 ISO808A_1_0_IN5
/** Device Chan: IN6 */
#define IPS_RELAY_0_IN6 ISO808A_1_0_IN6
/** Device Chan: IN7 */
#define IPS_RELAY_0_IN7 ISO808A_1_0_IN7
/** Device Chan: IN8 */
#define IPS_RELAY_0_IN8 ISO808A_1_0_IN8

/** Input Pin: SPI_CLK */
#define IPS_RELAY_0_SPI_CLK ISO808A_1_0_SPI_CLK
/** Input Pin: SPI_MISO */
#define IPS_RELAY_0_SPI_MISO ISO808A_1_0_SPI_MISO
/** Input Pin: SPI_MOSI */
#define IPS_RELAY_0_SPI_MOSI ISO808A_1_0_SPI_MOSI

/** Control Pin: SPI_SS */
#define IPS_RELAY_0_SPI_SS ISO808A_1_0_SPI_SS
/** Control Pin: OUT_EN */
#define IPS_RELAY_0_OUT_EN ISO808A_1_0_OUT_EN

/** SPI_SS Port 0 */
#define IPS_RELAY_0_SPI_SS_GPIO_PORT ISO808A_1_0_SPI_SS_GPIO_PORT
/** SPI_SS Pin 0 */
#define IPS_RELAY_0_SPI_SS_GPIO_PIN ISO808A_1_0_SPI_SS_GPIO_PIN
/** OUT_EN Port 0 */
#define IPS_RELAY_0_OUT_EN_GPIO_PORT ISO808A_1_0_OUT_EN_GPIO_PORT
/** OUT_EN Pin 0 */
#define IPS_RELAY_0_OUT_EN_GPIO_PIN ISO808A_1_0_OUT_EN_GPIO_PIN

/** STATUS Port 0 */
#define IPS_RELAY_0_STATUS_GPIO_PORT ISO808A_1_0_STATUS_GPIO_PORT
/** STATUS Pin 0 */
#define IPS_RELAY_0_STATUS_GPIO_PIN ISO808A_1_0_STATUS_GPIO_PIN
/** PGOOD Port 0 */
#define IPS_RELAY_0_PGOOD_GPIO_PORT ISO808A_1_0_PGOOD_GPIO_PORT
/** PGOOD Pin 0 */
#define IPS_RELAY_0_PGOOD_GPIO_PIN ISO808A_1_0_PGOOD_GPIO_PIN

/* Board 1 */
/** Device Chan: IN1 */
#define IPS_RELAY_1_IN1 ISO808A_1_1_IN1
/** Device Chan: IN2 */
#define IPS_RELAY_1_IN2 ISO808A_1_1_IN2
/** Device Chan: IN3 */
#define IPS_RELAY_1_IN3 ISO808A_1_1_IN3
/** Device Chan: IN4 */
#define IPS_RELAY_1_IN4 ISO808A_1_1_IN4
/** Device Chan: IN5 */
#define IPS_RELAY_1_IN5 ISO808A_1_1_IN5
/** Device Chan: IN6 */
#define IPS_RELAY_1_IN6 ISO808A_1_1_IN6
/** Device Chan: IN7 */
#define IPS_RELAY_1_IN7 ISO808A_1_1_IN7
/** Device Chan: IN8 */
#define IPS_RELAY_1_IN8 ISO808A_1_1_IN8

/** Input Pin: SPI_CLK */
#define IPS_RELAY_1_SPI_CLK ISO808A_1_1_SPI_CLK
/** Input Pin: SPI_MISO */
#define IPS_RELAY_1_SPI_MISO ISO808A_1_1_SPI_MISO
/** Input Pin: SPI_MOSI */
#define IPS_RELAY_1_SPI_MOSI ISO808A_1_1_SPI_MOSI

/** Control Pin: SPI_SS */
#define IPS_RELAY_1_SPI_SS ISO808A_1_1_SPI_SS
/** Control Pin: OUT_EN_Alt1 */
#define IPS_RELAY_1_OUT_EN ISO808A_1_1_OUT_EN

/** SPI_SS Port 1 */
#define IPS_RELAY_1_SPI_SS_GPIO_PORT ISO808A_1_1_SPI_SS_GPIO_PORT
/** SPI_SS Pin 1 */
#define IPS_RELAY_1_SPI_SS_GPIO_PIN ISO808A_1_1_SPI_SS_GPIO_PIN
/** OUT_EN Port 1 */
#define IPS_RELAY_1_OUT_EN_GPIO_PORT ISO808A_1_1_OUT_EN_GPIO_PORT
/** OUT_EN Pin 1 */
#define IPS_RELAY_1_OUT_EN_GPIO_PIN ISO808A_1_1_OUT_EN_GPIO_PIN

/** STATUS Port 1 */
#define IPS_RELAY_1_STATUS_GPIO_PORT ISO808A_1_1_STATUS_GPIO_PORT
/** STATUS Pin 1 */
#define IPS_RELAY_1_STATUS_GPIO_PIN ISO808A_1_1_STATUS_GPIO_PIN
/** PGOOD Port 1 */
#define IPS_RELAY_1_PGOOD_GPIO_PORT ISO808A_1_1_PGOOD_GPIO_PORT
/** PGOOD Pin 1 */
#define IPS_RELAY_1_PGOOD_GPIO_PIN ISO808A_1_1_PGOOD_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_14_Example_Conf_Exported_Variables OUT_14_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti9;
extern EXTI_HandleTypeDef hexti8;
extern EXTI_HandleTypeDef hexti5;
extern EXTI_HandleTypeDef hexti10;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_14_Example_Conf_Exported_Macros OUT_14_Example Conf Exported Macros
  * @{
  */

#define OUT14_BUS_SPI_SS_0_GPIO_Port  SPI_SS_GPIO_Port
#define OUT14_BUS_SPI_SS_0_Pin        SPI_SS_Pin
#define OUT14_BUS_SPI_SS_1_GPIO_Port  SPI_SS_Alt1_GPIO_Port
#define OUT14_BUS_SPI_SS_1_Pin        SPI_SS_Alt1_Pin

/** SPI init function */
#define OUT14_SpiInit           BSP_SPI1_Init
/** SPI deinit function */
#define OUT14_SpiDeInit         BSP_SPI1_DeInit
/** SPI write function */
#define OUT14_SpiWrite          OUT14_Board_SpiWrite

#define OUT14_Spi_SendRecv      BSP_SPI1_SendRecv

/** Customization of generic driver function */
#define OUT14_GetTick           BSP_GetTick
/** Customization of generic driver function */
#define OUT14_WritePin          OUT14_SetControlPin
/** Customization of generic driver function */
#define OUT14_ReadPin           OUT14_GetControlPin
/** Customization of generic driver function */
#define OUT14_ReadFault         OUT14_ReadFaultPin
/** Customization of generic driver function */
#define OUT14_SetPwm            OUT14_SetTimerForPwm
/** Customization of generic driver function */
#define OUT14_GuardTimerEnable  OUT14_GuardTimerStart
/** Customization of generic driver function */
#define OUT14_GuardTimerDisable OUT14_GuardTimerStop

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_14_Example_Conf_Exported_Functions OUT_14_Example Conf Exported Functions
  * @{
  */

int32_t OUT14_SetTimerForPwm(uint8_t pwmEnable);
int32_t OUT14_GuardTimerStart(void);
int32_t OUT14_GuardTimerStop(void);

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

#endif /* OUT14A1_CONF_H */

