/**
  ******************************************************************************
  * @file   out15a1_bus.c
  * @author AMS IPC Application Team
  * @brief  This file provides BSP bus driver functions for High Efficiency
  *         High Side Switch with extended diagnostic and smart driving for
  *         capacitive loads available on the following expansion board
  *           - X-NUCLEO-OUT15A1
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
#include "out15a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT15A1 OUT15A1
  * @{
  */

/** @addtogroup OUT15A1_BUS OUT15A1_BUS
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT15A1_BUS_Global_Variables OUT15A1_BUS Global Variables
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

/** @defgroup OUT15A1_BUS_Functions_Definition OUT15A1_BUS Functions Definition
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
int32_t OUT15_SetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus)
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
int32_t OUT15_GetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus)
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
int32_t OUT15_SetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap)
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
int32_t OUT15_GetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t *PinStatusBitmap)
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
int32_t OUT15_ReadFaultPin (IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus)
{
  int32_t ret = 0;
  *PinStatus = ((uint8_t)(HAL_GPIO_ReadPin(Pin->FLT1_GPort, Pin->FLT1_GPin))
               |((uint8_t)HAL_GPIO_ReadPin(Pin->FLT2_GPort, Pin->FLT2_GPin) << 1U));
  return ret;
}

/**
  * @brief  Set the pin status of the specified input pin
  * @param  Pin Pointer to pin structure
  * @param  PinId Input Pin Id
  * @param  PinStatus Input pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT15_SetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus)
{
  int32_t ret = 0;
  switch(PinId)
  {
    /* Control pins management */
#ifdef USE_BOARD_0
    case IPS_SWITCH_0_NCH_DRV:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case IPS_SWITCH_1_NCH_DRV:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      HAL_GPIO_WritePin(Pin->Nch_DRV_GPort, Pin->Nch_DRV_GPin, (GPIO_PinState)PinStatus);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
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
int32_t OUT15_GetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus)
{
  int32_t ret = 0;
  switch(PinId)
  {
    /* Control pins management */
#ifdef USE_BOARD_0
    case IPS_SWITCH_0_NCH_DRV:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case IPS_SWITCH_1_NCH_DRV:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->Nch_DRV_GPort, Pin->Nch_DRV_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;
#ifdef USE_BOARD_0
    case IPS_SWITCH_0_OUT_FB:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case IPS_SWITCH_1_OUT_FB:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->OUT_FB_GPort, Pin->OUT_FB_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
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
