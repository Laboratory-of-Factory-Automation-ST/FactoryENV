/**
  ******************************************************************************
  * @file           : app_ips_custom.h
  * @author         : AMS IPC Application Team
  * @brief          : Header file for app_ips_custom.c module
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
#ifndef APP_IPS_CUSTOM_H
#define APP_IPS_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "app_ips_switch.h"

/** @addtogroup OUT_16_Example OUT_16_Example
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_16_Example_Exported_Constants OUT_16_Example Exported Constants
  * @{
  */

/** Board 0 identifier */
#define OUT16_BOARD_0 0U
/** Board 1 identifier */
#define OUT16_BOARD_1 1U

/** Board 0 and 1 in Daisy Chain conf identifier */
#define OUT16_BOARD_0_1_DS 3U

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* APP_IPS_CUSTOM_H */

