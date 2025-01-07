/**
  ******************************************************************************
  * @file   out06a1_bus.c
  * @author AMS IPC Application Team
  * @brief  This file provides BSP bus driver functions for IPS device on
  *         the following expansion board
  *           - X-NUCLEO-OUT06A1
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

/* Includes ------------------------------------------------------------------*/
#include "out06a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT06A1 OUT06A1
  * @{
  */

/** @defgroup OUT06A1_BUS OUT06A1_BUS
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT06A1_BUS_Global_Variables OUT06A1_BUS Global Variables
  * @{
  */

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT06A1_BUS_Functions_Definition OUT06A1_BUS Functions Definition
  * @{
  */

/******************************************************/
/********                                      ********/
/********            GPIO BUS SECTION          ********/
/********                                      ********/
/******************************************************/

/**
  * @brief  Set the pin status of the specified channel
  * @param  Pin Pointer to pin structure
  * @param  ChanId Channel Id
  * @param  PinStatus Channel pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT06_SetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus)
{
  int32_t ret = 0;
  switch(ChanId)
  {
    case 0:
      HAL_GPIO_WritePin(Pin->IN1_GPort, Pin->IN1_GPin, (GPIO_PinState)PinStatus);
      break;
    default:
      ret = (-1);
      break;
  }
  return ret;
}

/**
  * @brief  Get the pin status of the specified channel
  * @param  Pin Pointer to pin structure
  * @param  ChanId Channel Id
  * @param  PinStatus Pointer to the channel pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT06_GetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus)
{
  int32_t ret = 0;
  switch(ChanId)
  {
    case 0:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN1_GPort, Pin->IN1_GPin);
      break;
    default:
      ret = (-1);
      break;
  }
  return ret;
}

/**
  * @brief  Set the pin status of all channels
  * @param  Pin Pointer to pin structure
  * @param  PinStatusBitmap Channel pin status bitmap
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT06_SetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap)
{
  int32_t ret = 0;
  HAL_GPIO_WritePin(Pin->IN1_GPort, Pin->IN1_GPin, (GPIO_PinState)(uint8_t)(PinStatusBitmap & 0x1U));

  return ret;
}

/**
  * @brief  Get the status of all channel input Pins
  * @param  Pin Pointer to pin structure
  * @param  PinStatusBitmap Pointer to the channel status bitmap
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT06_GetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t *PinStatusBitmap)
{
  int32_t ret = 0;
  *PinStatusBitmap = (uint8_t)(HAL_GPIO_ReadPin(Pin->IN1_GPort, Pin->IN1_GPin));
  return ret;
}

/**
  * @brief  Get the status of the Fault Pin
  * @param  Pin Pointer to pin structure
  * @param  PinStatus Pointer to the Fault pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT06_ReadFaultPin (IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus)
{
  int32_t ret = 0;
  *PinStatus = ((uint8_t)(HAL_GPIO_ReadPin(Pin->FLT1_GPort, Pin->FLT1_GPin))
               |((uint8_t)HAL_GPIO_ReadPin(Pin->FLT2_GPort, Pin->FLT2_GPin) << 1U));
  return ret;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
