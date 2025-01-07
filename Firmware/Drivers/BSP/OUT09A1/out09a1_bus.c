/**
  ******************************************************************************
  * @file   out09a1_bus.c
  * @author AMS IPC Application Team
  * @brief  This file provides BSP bus driver functions for High Efficiency
  *         High Side Switch with extended diagnostic and smart driving for
  *         capacitive loads available on the following expansion boards
  *           - X-NUCLEO-OUT09A1
  *           - X-NUCLEO-OUT19A1
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
#include "out09a1.h"
#include "out09a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT09A1 OUT09A1
  * @{
  */

/** @addtogroup OUT09A1_BUS OUT09A1_BUS
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT09A1_BUS_Global_Variables OUT09A1_BUS Global Variables
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

/** @defgroup OUT09A1_BUS_Functions_Definition OUT09A1_BUS Functions Definition
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
int32_t OUT09_SetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus)
{
  int32_t ret = 0;
  switch(ChanId)
  {
    case IPS_SWITCH_0_IN1:
      HAL_GPIO_WritePin(Pin->IN1_GPort, Pin->IN1_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_IN2:
      HAL_GPIO_WritePin(Pin->IN2_GPort, Pin->IN2_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_IN3:
      HAL_GPIO_WritePin(Pin->IN3_GPort, Pin->IN3_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_IN4:
      HAL_GPIO_WritePin(Pin->IN4_GPort, Pin->IN4_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_IN5:
      HAL_GPIO_WritePin(Pin->IN5_GPort, Pin->IN5_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_IN6:
      HAL_GPIO_WritePin(Pin->IN6_GPort, Pin->IN6_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_IN7:
      HAL_GPIO_WritePin(Pin->IN7_GPort, Pin->IN7_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_IN8:
      HAL_GPIO_WritePin(Pin->IN8_GPort, Pin->IN8_GPin, (GPIO_PinState)PinStatus);
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
int32_t OUT09_GetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus)
{
  int32_t ret = 0;

  switch(ChanId)
  {
    case IPS_SWITCH_0_IN1:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN1_GPort, Pin->IN1_GPin);
      break;
    case IPS_SWITCH_0_IN2:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN2_GPort, Pin->IN2_GPin);
      break;
    case IPS_SWITCH_0_IN3:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN3_GPort, Pin->IN3_GPin);
      break;
    case IPS_SWITCH_0_IN4:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN4_GPort, Pin->IN4_GPin);
      break;
    case IPS_SWITCH_0_IN5:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN5_GPort, Pin->IN5_GPin);
      break;
    case IPS_SWITCH_0_IN6:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN6_GPort, Pin->IN6_GPin);
      break;
    case IPS_SWITCH_0_IN7:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN7_GPort, Pin->IN7_GPin);
      break;
    case IPS_SWITCH_0_IN8:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->IN8_GPort, Pin->IN8_GPin);
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
int32_t OUT09_SetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap)
{
  int32_t ret = 0;

  HAL_GPIO_WritePin(Pin->IN1_GPort, Pin->IN1_GPin, (GPIO_PinState)(uint8_t)(PinStatusBitmap & 0x1U));
  HAL_GPIO_WritePin(Pin->IN2_GPort, Pin->IN2_GPin, (GPIO_PinState)(uint8_t)((PinStatusBitmap >> 1U) & 0x1U));
  HAL_GPIO_WritePin(Pin->IN3_GPort, Pin->IN3_GPin, (GPIO_PinState)(uint8_t)((PinStatusBitmap >> 2U) & 0x1U));
  HAL_GPIO_WritePin(Pin->IN4_GPort, Pin->IN4_GPin, (GPIO_PinState)(uint8_t)((PinStatusBitmap >> 3U) & 0x1U));
  HAL_GPIO_WritePin(Pin->IN5_GPort, Pin->IN5_GPin, (GPIO_PinState)(uint8_t)((PinStatusBitmap >> 4U) & 0x1U));
  HAL_GPIO_WritePin(Pin->IN6_GPort, Pin->IN6_GPin, (GPIO_PinState)(uint8_t)((PinStatusBitmap >> 5U) & 0x1U));
  HAL_GPIO_WritePin(Pin->IN7_GPort, Pin->IN7_GPin, (GPIO_PinState)(uint8_t)((PinStatusBitmap >> 6U) & 0x1U));
  HAL_GPIO_WritePin(Pin->IN8_GPort, Pin->IN8_GPin, (GPIO_PinState)(uint8_t)((PinStatusBitmap >> 7U) & 0x1U));

  return ret;
}

/**
  * @brief  Get the status of all channel input Pins
  * @param  Pin Pointer to pin structure
  * @param  PinStatusBitmap Pointer to the channel status bitmap
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT09_GetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t *PinStatusBitmap)
{
  int32_t ret = 0;

  *PinStatusBitmap = (uint8_t)(HAL_GPIO_ReadPin(Pin->IN1_GPort, Pin->IN1_GPin))
                   | ((uint8_t)HAL_GPIO_ReadPin(Pin->IN2_GPort, Pin->IN2_GPin) << 1U)
                   | ((uint8_t)HAL_GPIO_ReadPin(Pin->IN3_GPort, Pin->IN3_GPin) << 2U)
                   | ((uint8_t)HAL_GPIO_ReadPin(Pin->IN4_GPort, Pin->IN4_GPin) << 3U)
                   | ((uint8_t)HAL_GPIO_ReadPin(Pin->IN5_GPort, Pin->IN5_GPin) << 4U)
                   | ((uint8_t)HAL_GPIO_ReadPin(Pin->IN6_GPort, Pin->IN6_GPin) << 5U)
                   | ((uint8_t)HAL_GPIO_ReadPin(Pin->IN7_GPort, Pin->IN7_GPin) << 6U)
                   | ((uint8_t)HAL_GPIO_ReadPin(Pin->IN8_GPort, Pin->IN8_GPin) << 7U);

  return ret;
}

/**
  * @brief  Get the status of the Fault Pin
  * @param  Pin Pointer to pin structure
  * @param  PinStatus Pointer to the Fault pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT09_ReadFaultPin(IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus)
{
  int32_t ret = 0;

  *PinStatus = (uint8_t)(HAL_GPIO_ReadPin(Pin->STATUS_GPort, Pin->STATUS_GPin));
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
