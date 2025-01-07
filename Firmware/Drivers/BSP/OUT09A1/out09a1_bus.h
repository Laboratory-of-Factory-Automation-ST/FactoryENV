/**
  ******************************************************************************
  * @file           : out09a1_bus.h
  * @author         : AMS IPC IO-Link Application Team
  * @brief          : Bus definitions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OUT09A1_BUS_H
#define OUT09A1_BUS_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out09a1_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT09A1_BUS OUT09A1_BUS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT09A1_BUS_Exported_Constants OUT09A1_BUS Exported Constants
  * @{
  */

/******************************************************************************/
/* Dependent platform definitions                                            */
/******************************************************************************/

/******************************************************************************/
/* Independent platform definitions                                          */
/******************************************************************************/


/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup OUT09A1_BUS_Exported_Functions OUT09A1_BUS Exported Functions
  * @{
  */

int32_t OUT09_SetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus);
int32_t OUT09_GetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus);
int32_t OUT09_SetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap);
int32_t OUT09_GetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatusBitmap);
int32_t OUT09_ReadFaultPin(IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus);

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

#endif /* OUT09A1_BUS_H */
