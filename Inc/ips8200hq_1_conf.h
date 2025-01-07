/**
  ******************************************************************************
  * @file    ips8200hq_1_conf.h
  * @author  AMS IPC IO-Link Application Team
  * @brief   Predefines values for the IPS8200HQ-1 parameters
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
#ifndef IPS8200HQ_1_CONF_H
#define IPS8200HQ_1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stm32f4xx_hal.h"

/** @addtogroup OUT_17_Example OUT_17_Example
  * @{
  */

/** @addtogroup OUT_17_Example_Conf OUT_17_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_17_Example_Conf_Exported_Constants OUT_17_Example Conf Exported Constants
  * @{
  */

/** Guard Timer tick frequency */
#define IPS8200HQ_1_GUARD_TIMER_FREQ 1000000

/** Watchdog Timer tick frequency */
#define IPS8200HQ_1_WATCHDOG_TIMER_FREQ 100000

/** SPI access timeout*/
#define IPS8200HQ_1_SPI_TIMEOUT_MAX ((uint32_t)0x0A)

/** Maximum number of instances supported */
#define IPS8200HQ_1_INSTANCES_NBR (2U)

/** SPI TX buffer size */
#define IPS8200HQ_1_SPI_TX_MAX_NB_BYTES (4U)

/** SPI RX buffer size */
#define IPS8200HQ_1_SPI_RX_MAX_NB_BYTES (4U)

/** SPI Frequency in Hz */
#define IPS8200HQ_1_CONF_PARAM_SPI_FREQ (1U * 1048576U)

/** Tcss delay in us */
#define IPS8200HQ_1_CONF_PARAM_TIMING_TCSS (10U)

/** Twd delay in us */
#define IPS8200HQ_1_CONF_PARAM_TIMING_TWD (50U)

/** Twm delay in us */
#define IPS8200HQ_1_CONF_PARAM_TIMING_TWM (80000U)

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* IPS8200HQ_1_CONF_H */
