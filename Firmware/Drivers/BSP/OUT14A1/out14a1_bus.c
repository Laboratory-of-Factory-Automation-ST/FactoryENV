/**
  ******************************************************************************
  * @file   out14a1_bus.c
  * @author AMS IPC Application Team
  * @brief  This file provides BSP bus driver functions for Galvanic Isolated
  *         Octal High-Side Power Solid State Relay with SPI interface for high
  *         inductive loads available on the following expansion board
  *           - X-NUCLEO-OUT14A1
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
#include "out14a1.h"
#include "out14a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT14A1 OUT14A1
  * @{
  */

/** @addtogroup OUT14A1_BUS OUT14A1_BUS
  * @{
  */

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT14A1_BUS_Functions_Definition OUT14A1_BUS Functions Definition
 * @{
 */

/******************************************************/
/********                                      ********/
/********            SPI BUS SECTION           ********/
/********                                      ********/
/******************************************************/


/**
  * @brief   Write and read SPI byte to the Iso808a-1's
  * @param   deviceId Device Id (instance of the device object)
  * @param   pByteToTransmit pointer to the byte to transmit
  * @param   pReceivedByte pointer to the received byte
  * @param   nbDevices Number of device in the SPI chain
  * @retval  0 in case of success, an error code otherwise
  */
uint8_t OUT14_Board_SpiWrite(uint8_t deviceId, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices)
{
  int32_t status = 0;

  switch(deviceId)
  {
    case 0U:
#ifdef USE_BOARD_0
      HAL_GPIO_WritePin(OUT14_RELAY_0_SPI_SS_GPIO_PORT, OUT14_RELAY_0_SPI_SS_GPIO_PIN, GPIO_PIN_RESET);
#endif /* #ifdef USE_BOARD_0 */
      break;

    case 1U:
#ifdef USE_BOARD_1
      HAL_GPIO_WritePin(OUT14_RELAY_1_SPI_SS_GPIO_PORT, OUT14_RELAY_1_SPI_SS_GPIO_PIN, GPIO_PIN_RESET);
#endif /* #ifdef USE_BOARD_1 */
      break;

    default:
      status = (-1);
      break;
  }

  if (status == 0)
  {
    uint32_t i;
    for (i = 0; i < nbDevices; i++)
    {
      status = OUT14_Spi_SendRecv( pByteToTransmit, pReceivedByte, 1U);
      if (status != 0)
      {
        break;
      }
      pByteToTransmit++;
      pReceivedByte++;
    }

    switch(deviceId)
    {
      case 0U:
#ifdef USE_BOARD_0
        HAL_GPIO_WritePin(OUT14_RELAY_0_SPI_SS_GPIO_PORT, OUT14_RELAY_0_SPI_SS_GPIO_PIN, GPIO_PIN_SET);
#endif /* #ifdef USE_BOARD_0 */
        break;

      case 1U:
#ifdef USE_BOARD_1
        HAL_GPIO_WritePin(OUT14_RELAY_1_SPI_SS_GPIO_PORT, OUT14_RELAY_1_SPI_SS_GPIO_PIN, GPIO_PIN_SET);
#endif /* #ifdef USE_BOARD_1 */
        break;

      default:
        status = (-1);
        break;
    }
  }

  return (uint8_t)status;
}

/******************************************************/
/********                                      ********/
/********            GPIO BUS SECTION          ********/
/********                                      ********/
/******************************************************/

/**
  * @brief  Set the pin status of the specified input pin
  * @param  Pin Pointer to pin structure
  * @param  PinId Input Pin Id
  * @param  PinStatus Input pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT14_SetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus)
{
  int32_t ret = 0;
  switch(PinId)
  {
    /* Control pins management */
#ifdef USE_BOARD_0
    case OUT14_RELAY_0_SPI_SS:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT14_RELAY_1_SPI_SS:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      HAL_GPIO_WritePin(Pin->SPI_SS_GPort, Pin->SPI_SS_GPin, (GPIO_PinState)PinStatus);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT14_RELAY_0_OUT_EN:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT14_RELAY_1_OUT_EN:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      HAL_GPIO_WritePin(Pin->OUT_EN_GPort, Pin->OUT_EN_GPin, (GPIO_PinState)PinStatus);
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
int32_t OUT14_GetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus)
{
  int32_t ret = 0;
  switch(PinId)
  {
    /* Control pins management */
#ifdef USE_BOARD_0
    case OUT14_RELAY_0_SPI_SS:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT14_RELAY_1_SPI_SS:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->SPI_SS_GPort, Pin->SPI_SS_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT14_RELAY_0_OUT_EN:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT14_RELAY_1_OUT_EN:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->OUT_EN_GPort, Pin->OUT_EN_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

    default:
      ret = (-1);
      break;
  }
  return ret;
}

/**
  * @brief  Get the status of the Fault Pin
  * @param  Pin Pointer to pin structure
  * @param  PinStatus Pointer to the Fault pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT14_ReadFaultPin(IPS_RELAY_Pins_t *Pin, uint8_t* PinStatus)
{
  int32_t ret = 0;
  *PinStatus = ((uint8_t)(HAL_GPIO_ReadPin(Pin->STATUS_GPort, Pin->STATUS_GPin))
               |((uint8_t)HAL_GPIO_ReadPin(Pin->PGOOD_GPort, Pin->PGOOD_GPin) << 1U));
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
