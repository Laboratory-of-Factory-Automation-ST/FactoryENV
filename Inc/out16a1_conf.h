/**
  ******************************************************************************
  * @file           : out16a1_conf.h
  * @author         : AMS IPC Application Team
  * @brief          : Header file for the project configuration
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OUT16A1_CONF_H
#define OUT16A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_bus.h"
#include "ips8200hq.h"

/** @addtogroup OUT_16_Example OUT_16_Example
  * @{
  */

/** @addtogroup OUT_16_Example_Conf OUT_16_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_16_Example_Conf_Exported_Constants OUT_16_Example Conf Exported Constants
  * @{
  */

#define USE_BOARD_0 1

#define H_EXTI_LINE_FAULT_L EXTI_LINE_8
#define H_EXTI_8 hexti8
#define H_EXTI_FAULT_L hexti8
/** This is the HW configuration section: FAULT_L_Pin */
#define FAULT_L_Pin GPIO_PIN_8
/** This is the HW configuration section: FAULT_L_GPIO_Port */
#define FAULT_L_GPIO_Port GPIOB
/** This is the HW configuration section: FAULT_L_EXTI_IRQn */
#define FAULT_L_EXTI_IRQn EXTI9_5_IRQn

#define H_EXTI_LINE_PGOOD_L EXTI_LINE_9
#define H_EXTI_9 hexti9
#define H_EXTI_PGOOD_L hexti9
/** This is the HW configuration section: PGOOD_L_Pin */
#define PGOOD_L_Pin GPIO_PIN_9
/** This is the HW configuration section: PGOOD_L_GPIO_Port */
#define PGOOD_L_GPIO_Port GPIOB
/** This is the HW configuration section: PGOOD_L_EXTI_IRQn */
#define PGOOD_L_EXTI_IRQn EXTI9_5_IRQn

#define H_EXTI_LINE_TWARN_L EXTI_LINE_1
#define H_EXTI_1 hexti1
#define H_EXTI_TWARN_L hexti1
/** This is the HW configuration section: TWARN_L_Pin */
#define TWARN_L_Pin GPIO_PIN_1
/** This is the HW configuration section: TWARN_L_GPIO_Port */
#define TWARN_L_GPIO_Port GPIOC
/** This is the HW configuration section: TWARN_L_EXTI_IRQn */
#define TWARN_L_EXTI_IRQn EXTI1_IRQn

/** This is the HW configuration section: SPI_SS_Pin */
#define SPI_SS_Pin GPIO_PIN_6
/** This is the HW configuration section: SPI_SS_GPIO_Port */
#define SPI_SS_GPIO_Port GPIOB
/** This is the HW configuration section: OUT_EN_Pin */
#define OUT_EN_Pin GPIO_PIN_1
/** This is the HW configuration section: OUT_EN_GPIO_Port */
#define OUT_EN_GPIO_Port GPIOA
/** This is the HW configuration section: WD_Pin */
#define WD_Pin GPIO_PIN_4
/** This is the HW configuration section: WD_GPIO_Port */
#define WD_GPIO_Port GPIOA
/** This is the HW configuration section: WDEN_Pin */
#define WDEN_Pin GPIO_PIN_3
/** This is the HW configuration section: WDEN_GPIO_Port */
#define WDEN_GPIO_Port GPIOB

/** This is the HW configuration section: SEL2_L_Pin */
#define SEL2_L_Pin GPIO_PIN_0
/** This is the HW configuration section: SEL2_L_GPIO_Port */
#define SEL2_L_GPIO_Port GPIOA
/** This is the HW configuration section: SEL1_Pin */
#define SEL1_Pin GPIO_PIN_0
/** This is the HW configuration section: SEL1_GPIO_Port */
#define SEL1_GPIO_Port GPIOC

/** CHIP ID */
#define IPS_RELAY_CHIP_ID IPS8200HQ_CHIP_ID

/** Number of supported relay devices*/
#define IPS_RELAY_DEVICES_NBR IPS8200HQ_DEVICES_NBR

/** Maximum number of instances supported */
#define IPS_INSTANCES_NBR IPS8200HQ_INSTANCES_NBR

/** SPI frequency for relay */
#define IPS_RELAY_CONF_PARAM_SPI_FREQ IPS8200HQ_CONF_PARAM_SPI_FREQ

/** Guard Timer tick frequency */
#define IPS_RELAY_GUARD_TIMER_FREQ IPS8200HQ_GUARD_TIMER_FREQ

/** Watchdog Timer tick frequency */
#define IPS_RELAY_WATCHDOG_TIMER_FREQ IPS8200HQ_WATCHDOG_TIMER_FREQ

/** Tcss delay in us */
#define IPS_RELAY_CONF_PARAM_TIMING_TCSS IPS8200HQ_CONF_PARAM_TIMING_TCSS

/** Twd delay in us */
#define IPS_RELAY_CONF_PARAM_TIMING_TWD IPS8200HQ_CONF_PARAM_TIMING_TWD

/** Twm delay in us */
#define IPS_RELAY_CONF_PARAM_TIMING_TWM IPS8200HQ_CONF_PARAM_TIMING_TWM

/** Fully populated system in daisy chain mode */
#define IPS_SPI_DC_FULLSYS IPS8200HQ_SPI_DC_FULLSYS

/* Control Mode settings */

/** Undefined Control mode setting */
#define IPS_UNDEF_CTRL_MODE IPS8200HQ_UNDEF_CTRL_MODE

/** Parallel Control mode setting */
#define IPS_PAR_CTRL_MODE IPS8200HQ_PAR_CTRL_MODE

/** SPI Control mode setting */
#define IPS_SPI_CTRL_MODE IPS8200HQ_SPI_CTRL_MODE

/** SPI Daisy Chain Control mode setting */
#define IPS_SPI_DC_CTRL_MODE IPS8200HQ_SPI_DC_CTRL_MODE

/* SPI Width settings */

/** Undefined SPI Width setting */
#define IPS_SPI_W_NONE IPS8200HQ_SPI_W_NONE

/** SPI 8bit Width setting */
#define IPS_SPI_W_8BIT IPS8200HQ_SPI_W_8BIT

/** SPI 16bit Width setting */
#define IPS_SPI_W_16BIT IPS8200HQ_SPI_W_16BIT

/* Dev pins for IPS8200HQ (SPI Interface) */
/* Board 0 */
/** Device Chan: IN1 */
#define IPS_RELAY_0_IN1 IPS8200HQ_0_IN1
/** Device Chan: IN2 */
#define IPS_RELAY_0_IN2 IPS8200HQ_0_IN2
/** Device Chan: IN3 */
#define IPS_RELAY_0_IN3 IPS8200HQ_0_IN3
/** Device Chan: IN4 */
#define IPS_RELAY_0_IN4 IPS8200HQ_0_IN4
/** Device Chan: IN5 */
#define IPS_RELAY_0_IN5 IPS8200HQ_0_IN5
/** Device Chan: IN6 */
#define IPS_RELAY_0_IN6 IPS8200HQ_0_IN6
/** Device Chan: IN7 */
#define IPS_RELAY_0_IN7 IPS8200HQ_0_IN7
/** Device Chan: IN8 */
#define IPS_RELAY_0_IN8 IPS8200HQ_0_IN8

/** Input Pin: SPI_CLK */
#define IPS_RELAY_0_SPI_CLK IPS8200HQ_0_SPI_CLK
/** Input Pin: SPI_MISO */
#define IPS_RELAY_0_SPI_MISO IPS8200HQ_0_SPI_MISO
/** Input Pin: SPI_MOSI */
#define IPS_RELAY_0_SPI_MOSI IPS8200HQ_0_SPI_MOSI

/** Control Pin: SEL2_L */
#define IPS_RELAY_0_SEL2_L IPS8200HQ_0_SEL2_L
/** Control Pin: SEL1 */
#define IPS_RELAY_0_SEL1 IPS8200HQ_0_SEL1
/** Control Pin: SPI_SS */
#define IPS_RELAY_0_SPI_SS IPS8200HQ_0_SPI_SS
/** Control Pin: OUT_EN */
#define IPS_RELAY_0_OUT_EN IPS8200HQ_0_OUT_EN
/** Control Pin: WD */
#define IPS_RELAY_0_WD IPS8200HQ_0_WD
/** Control Pin: WDEN */
#define IPS_RELAY_0_WDEN IPS8200HQ_0_WDEN

/** SEL2_L Port 0 */
#define IPS_RELAY_0_SEL2_L_GPIO_PORT IPS8200HQ_0_SEL2_L_GPIO_PORT
/** SEL2_L Pin 0 */
#define IPS_RELAY_0_SEL2_L_GPIO_PIN IPS8200HQ_0_SEL2_L_GPIO_PIN
/** SEL1 Port 0 */
#define IPS_RELAY_0_SEL1_GPIO_PORT IPS8200HQ_0_SEL1_GPIO_PORT
/** SEL1 Pin 0 */
#define IPS_RELAY_0_SEL1_GPIO_PIN IPS8200HQ_0_SEL1_GPIO_PIN
/** SPI_SS Port 0 */
#define IPS_RELAY_0_SPI_SS_GPIO_PORT IPS8200HQ_0_SPI_SS_GPIO_PORT
/** SPI_SS Pin 0 */
#define IPS_RELAY_0_SPI_SS_GPIO_PIN IPS8200HQ_0_SPI_SS_GPIO_PIN
/** OUT_EN Port 0 */
#define IPS_RELAY_0_OUT_EN_GPIO_PORT IPS8200HQ_0_OUT_EN_GPIO_PORT
/** OUT_EN Pin 0 */
#define IPS_RELAY_0_OUT_EN_GPIO_PIN IPS8200HQ_0_OUT_EN_GPIO_PIN
/** WD Port 0 */
#define IPS_RELAY_0_WD_GPIO_PORT IPS8200HQ_0_WD_GPIO_PORT
/** WD Pin 0 */
#define IPS_RELAY_0_WD_GPIO_PIN IPS8200HQ_0_WD_GPIO_PIN
/** WDEN Port 0 */
#define IPS_RELAY_0_WDEN_GPIO_PORT IPS8200HQ_0_WDEN_GPIO_PORT
/** WDEN Pin 0 */
#define IPS_RELAY_0_WDEN_GPIO_PIN IPS8200HQ_0_WDEN_GPIO_PIN

/** FAULT_L Port 0 */
#define IPS_RELAY_0_FAULT_L_GPIO_PORT IPS8200HQ_0_FAULT_L_GPIO_PORT
/** FAULT_L Pin 0 */
#define IPS_RELAY_0_FAULT_L_GPIO_PIN IPS8200HQ_0_FAULT_L_GPIO_PIN
/** PGOOD_L Port 0 */
#define IPS_RELAY_0_PGOOD_L_GPIO_PORT IPS8200HQ_0_PGOOD_L_GPIO_PORT
/** PGOOD_L Pin 0 */
#define IPS_RELAY_0_PGOOD_L_GPIO_PIN IPS8200HQ_0_PGOOD_L_GPIO_PIN
/** TWARN_L Port 0 */
#define IPS_RELAY_0_TWARN_L_GPIO_PORT IPS8200HQ_0_TWARN_L_GPIO_PORT
/** TWARN_L Pin 0 */
#define IPS_RELAY_0_TWARN_L_GPIO_PIN IPS8200HQ_0_TWARN_L_GPIO_PIN

#define OUT16_BUS_SPI_SS_0_GPIO_Port  SPI_SS_GPIO_Port
#define OUT16_BUS_SPI_SS_0_Pin        SPI_SS_Pin

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT_16_Example_Conf_Exported_Variables OUT_16_Example Conf Exported Variables
  * @{
  */

extern EXTI_HandleTypeDef hexti8;
extern EXTI_HandleTypeDef hexti9;
extern EXTI_HandleTypeDef hexti1;

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @addtogroup OUT_16_Example_Conf_Exported_Macros OUT_16_Example Conf Exported Macros
  * @{
  */

/** SPI init function */
#define OUT16_SpiInit           BSP_SPI1_Init
/** SPI deinit function */
#define OUT16_SpiDeInit         BSP_SPI1_DeInit
/** SPI write function */
#define OUT16_SpiWrite          OUT16_Board_SpiWrite
/** SPI send receive function */
#define OUT16_Spi_SendRecv      BSP_SPI1_SendRecv

/** Customization of generic driver function */
#define OUT16_GetTick           BSP_GetTick
/** Customization of generic driver function */
#define OUT16_WritePin          OUT16_SetControlPin
/** Customization of generic driver function */
#define OUT16_ReadPin           OUT16_GetControlPin
/** Customization of generic driver function */
#define OUT16_ReadFault         OUT16_ReadFaultPin
/** Customization of generic driver function */
#define OUT16_SetPwm            OUT16_SetTimerForPwm
/** Customization of generic driver function */
#define OUT16_GuardTimerEnable  OUT16_GuardTimerStart
/** Customization of generic driver function */
#define OUT16_GuardTimerDisable OUT16_GuardTimerStop

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT_16_Example_Conf_Exported_Functions OUT_16_Example Conf Exported Functions
  * @{
  */

int32_t OUT16_SetTimerForPwm(uint8_t pwmEnable);
int32_t OUT16_GuardTimerStart(void);
int32_t OUT16_GuardTimerStop(void);
int32_t OUT16_SPI_WatchdogTimerStart(void);
int32_t OUT16_SPI_WatchdogTimerStop(void);

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

#endif /* OUT16A1_CONF_H */
