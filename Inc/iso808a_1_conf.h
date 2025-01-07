/**
  ******************************************************************************
  * @file    iso808a_1_conf.h
  * @author  AMS IPC IO-Link Application Team
  * @brief   Predefines values for the ISO808A-1 parameters
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
#ifndef ISO808A_1_CONF_H
#define ISO808A_1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stm32f4xx_hal.h"

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

/** Guard Timer tick frequency */
#define GUARD_TIMER_FREQ 1000000

/** SPI access timeout*/
#define SPI_TIMEOUT_MAX ((uint32_t)0x0A)

/** Maximum number of instances supported */
#define ISO808A_1_INSTANCES_NBR (2U)

/** Maximum number of devices supported */
#define ISO808A_1_DEVICES_NBR (1U)

/** SPI TX buffer size */
#define SPI_TX_MAX_NB_BYTES (2U)

/** SPI RX buffer size */
#define SPI_RX_MAX_NB_BYTES (2U)

/** SPI Frequency in Hz */
#define ISO808A_1_CONF_PARAM_SPI_FREQ (5U * 1048576U)

/** Tcss delay in us */
#define ISO808A_1_CONF_PARAM_TIMING_TCSS (40U)

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

#endif /* ISO808A_1_CONF_H */
