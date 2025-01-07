/**
  ******************************************************************************
  * @file    ips2050h_conf.h
  * @author  AMS IPC IO-Link Application Team
  * @brief   Predefines values for the IPS2050H parameters
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
#ifndef IPS2050H_CONF_H
#define IPS2050H_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stm32f4xx_hal.h"

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

/** Maximum number of boards actually used */
#define IPS2050H_INSTANCES_NBR (1U)

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

#endif /* IPS2050H_CONF_H */
