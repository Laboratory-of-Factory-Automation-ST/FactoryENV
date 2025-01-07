/**
  ******************************************************************************
  * @file    iso8200bq_conf.h
  * @author  AMS IPC IO-Link Application Team
  * @brief   Predefines values for the ISO8200BQ parameters
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
#ifndef ISO8200BQ_CONF_H
#define ISO8200BQ_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stm32f4xx_hal.h"

/** @addtogroup OUT_01_Example OUT_01_Example
  * @{
  */

/** @addtogroup OUT_01_Example_Conf OUT_01_Example Conf
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_01_Example_Conf_Exported_Constants OUT_01_Example Conf Exported Constants
  * @{
  */

/** Maximum number of instances supported */
#define ISO8200BQ_INSTANCES_NBR (1U)

/** Nucleo board related: tw(SYNC) width constant */
#define ISO8200BQ_TW_SYNC_WIDTH (60U)

/** Nucleo board related: tSU(LOAD) width constant */
#define ISO8200BQ_TSU_LOAD_WIDTH (2U)

/** Nucleo board related: tW(LOAD) width constant */
#define ISO8200BQ_TW_LOAD_WIDTH (1U)

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

#endif /* ISO8200BQ_CONF_H */
