/**
  ******************************************************************************
  * @file   out01a2_bus.c
  * @author AMS IPC Application Team
  * @brief  This file provides BSP bus driver functions for High Efficiency
  *         High Side Switch with extended diagnostic and smart driving for
  *         capacitive loads available on the following expansion board
  *           - X-NUCLEO-OUT01A2
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
#include "out01a2.h"
#include "out01a2_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT01A2 OUT01A2
  * @{
  */

/** @addtogroup OUT01A2_BUS OUT01A2_BUS
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT01A2_BUS_Global_Variables OUT01A2_BUS Global Variables
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

/** @defgroup OUT01A2_BUS_Functions_Definition OUT01A2_BUS Functions Definition
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
int32_t OUT01_SetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus)
{
  int32_t ret = 0;

  switch(ChanId)
  {
    /* Input pins management */
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
int32_t OUT01_GetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus)
{
  int32_t ret = 0;

  switch(ChanId)
  {
    /* Input pins management */
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
int32_t OUT01_SetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap)
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
int32_t OUT01_GetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t *PinStatusBitmap)
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
int32_t OUT01_ReadFaultPin (IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus)
{
  int32_t ret = 0;

  *PinStatus = (uint8_t)(HAL_GPIO_ReadPin(Pin->STATUS_GPort, Pin->STATUS_GPin));
  return ret;
}

/**
  * @brief  Set the pin status of the specified input pin
  * @param  Pin Pointer to pin structure
  * @param  PinId Input Pin Id
  * @param  PinStatus Input pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT01_SetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus)
{
  int32_t ret = 0;

  switch(PinId)
  {
    /* Control pins management */
    case IPS_SWITCH_0_CTRL_LOAD:
      HAL_GPIO_WritePin(Pin->LOAD_GPort, Pin->LOAD_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_CTRL_OUT_EN:
      HAL_GPIO_WritePin(Pin->OUT_EN_GPort, Pin->OUT_EN_GPin, (GPIO_PinState)PinStatus);
      break;
    case IPS_SWITCH_0_CTRL_SYNCH:
      HAL_GPIO_WritePin(Pin->SYNCH_GPort, Pin->SYNCH_GPin, (GPIO_PinState)PinStatus);
      break;

    default:
      ret = (-1);
      break;
  }
  return ret;
}

/**
  * @brief  Get the pin status of the specified input pin
  * @param  Pin Pointer to pin structure
  * @param  PinId Input Pin Id
  * @param  PinStatus Pointer to the input pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT01_GetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus)
{
  int32_t ret = 0;
  switch(PinId)
  {
    /* Control pins management */
    case IPS_SWITCH_0_CTRL_LOAD:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->LOAD_GPort, Pin->LOAD_GPin);
      break;
    case IPS_SWITCH_0_CTRL_OUT_EN:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->OUT_EN_GPort, Pin->OUT_EN_GPin);
      break;
    case IPS_SWITCH_0_CTRL_SYNCH:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->SYNCH_GPort, Pin->SYNCH_GPin);
      break;
    case IPS_SWITCH_0_CTRL_ISO_DRV:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->ISO_DRV_GPort, Pin->ISO_DRV_GPin);
      break;

    default:
      ret = (-1);
      break;
  }
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
