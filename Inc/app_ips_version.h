/**
  ******************************************************************************
  * @file           : app_ips_version.h
  * @author         : AMS IPC Application Team
  * @brief          : Header file for app versioning
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
#ifndef APP_IPS_VERSION_H
#define APP_IPS_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/

/** @addtogroup OUT_16_Example OUT_16_Example
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup OUT_16_Example_Exported_Constants OUT_16_Example Exported Constants
  * @{
  */

/** Current FW major version */
#define OUT16_FW_MAJOR_VERSION (3U)
/** Current FW minor version */
#define OUT16_FW_MINOR_VERSION (0U)
/** Current FW patch version */
#define OUT16_FW_PATCH_VERSION (0U)
/** Current FW version */
#define OUT16_FW_VERSION (uint32_t)((OUT16_FW_MAJOR_VERSION << 16U) |\
                                    (OUT16_FW_MINOR_VERSION << 8U)  |\
                                    (OUT16_FW_PATCH_VERSION))

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

#endif /* APP_IPS_VERSION_H */
