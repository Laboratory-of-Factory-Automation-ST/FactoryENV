/**
  ******************************************************************************
  * @file           : out08a1_bus.h
  * @author         : AMS IPC IO-Link Application Team
  * @brief          : Bus definitions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OUT08A1_BUS_H
#define OUT08A1_BUS_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out08a1_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT08A1_BUS OUT08A1_BUS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT08A1_BUS_Exported_Constants OUT08A1_BUS Exported Constants
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

/** @defgroup OUT08A1_BUS_Exported_Functions OUT08A1_BUS Exported Functions
  * @{
  */

int32_t OUT08_SetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus);
int32_t OUT08_GetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus);
int32_t OUT08_SetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap);
int32_t OUT08_GetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatusBitmap);
int32_t OUT08_ReadFaultPin(IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus);
int32_t OUT08_SetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus);
int32_t OUT08_GetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus);

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

#endif /* OUT08A1_BUS_H */
