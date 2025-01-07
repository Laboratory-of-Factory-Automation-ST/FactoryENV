/**
  ******************************************************************************
  * @file   out16a1_bus.c
  * @author AMS IPC Application Team
  * @brief  This file provides BSP bus driver functions for Octal High-Side Power
  *          Solid State Switch with both direct input control and SPI interface
  *          for high inductive loads available on the following expansion board
  *           - X-NUCLEO-OUT16A1
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

/* Includes ------------------------------------------------------------------*/
#include "out16a1.h"
#include "out16a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT16A1 OUT16A1
  * @{
  */

/** @addtogroup OUT16A1_BUS OUT16A1_BUS
  * @{
  */

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT16A1_BUS_Functions_Definition OUT16A1_BUS Functions Definition
 * @{
 */

/******************************************************/
/********                                      ********/
/********            GPIO BUS SECTION          ********/
/********                                      ********/
/******************************************************/

#ifdef APP_PAR_IFC
/**
  * @brief  Set the pin status of the specified channel
  * @param  Pin Pointer to pin structure
  * @param  ChanId Channel Id
  * @param  PinStatus Channel pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT16_SetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus)
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
int32_t OUT16_GetChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus)
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
int32_t OUT16_SetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap)
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
int32_t OUT16_GetAllChanInputPin (IPS_SWITCH_Pins_t *Pin, uint8_t *PinStatusBitmap)
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
int32_t OUT16_ReadFaultPin (IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus)
{
  int32_t ret = 0;

  *PinStatus = ((uint8_t)(HAL_GPIO_ReadPin(Pin->FAULT_L_GPort, Pin->FAULT_L_GPin))
               |((uint8_t)HAL_GPIO_ReadPin(Pin->PGOOD_L_GPort, Pin->PGOOD_L_GPin) << 1U)
               |((uint8_t)HAL_GPIO_ReadPin(Pin->TWARN_L_GPort, Pin->TWARN_L_GPin) << 2U));

  return ret;
}

/**
  * @brief  Set the pin status of the specified input pin
  * @param  Pin Pointer to pin structure
  * @param  PinId Input Pin Id
  * @param  PinStatus Input pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT16_SetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus)
{
  int32_t ret;

  UNUSED(Pin);
  UNUSED(PinStatus);
  switch(PinId)
  {
    /* Control pins management */
    case IPS_SWITCH_0_SEL2_L:
    case IPS_SWITCH_0_SEL1:
      ret = (-1);
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
int32_t OUT16_GetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus)
{
  int32_t ret = 0;
  switch(PinId)
  {
    /* Control pins management */
    case IPS_SWITCH_0_SEL2_L:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->SEL2_L_GPort, Pin->SEL2_L_GPin);
      break;
    case IPS_SWITCH_0_SEL1:
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->SEL1_GPort, Pin->SEL1_GPin);
      break;

    default:
      ret = (-1);
      break;
  }
  return ret;
}
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
/**
  * @brief  Set the pin status of the specified input pin
  * @param  Pin Pointer to pin structure
  * @param  PinId Input Pin Id
  * @param  PinStatus Input pin status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t OUT16_SetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus)
{
  int32_t ret = 0;
  switch(PinId)
  {
    /* Control pins management */
#ifdef USE_BOARD_0
    case OUT16_RELAY_0_SPI_SS:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_SPI_SS:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      HAL_GPIO_WritePin(Pin->SPI_SS_GPort, Pin->SPI_SS_GPin, (GPIO_PinState)PinStatus);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT16_RELAY_0_OUT_EN:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_OUT_EN:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      HAL_GPIO_WritePin(Pin->OUT_EN_GPort, Pin->OUT_EN_GPin, (GPIO_PinState)PinStatus);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT16_RELAY_0_WD:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_WD:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      HAL_GPIO_WritePin(Pin->WD_GPort, Pin->WD_GPin, (GPIO_PinState)PinStatus);
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
int32_t OUT16_GetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus)
{
  int32_t ret = 0;

  switch(PinId)
  {
    /* Control pins management */
#ifdef USE_BOARD_0
    case OUT16_RELAY_0_SPI_SS:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_SPI_SS:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->SPI_SS_GPort, Pin->SPI_SS_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT16_RELAY_0_OUT_EN:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_OUT_EN:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->OUT_EN_GPort, Pin->OUT_EN_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT16_RELAY_0_WD:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_WD:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->WD_GPort, Pin->WD_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT16_RELAY_0_SEL2_L:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_SEL2_L:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->SEL2_L_GPort, Pin->SEL2_L_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT16_RELAY_0_SEL1:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_SEL1:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->SEL1_GPort, Pin->SEL1_GPin);
#endif /* #ifdef (USE_BOARD_0||USE_BOARD_1) */
      break;

#ifdef USE_BOARD_0
    case OUT16_RELAY_0_WDEN:
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
    case OUT16_RELAY_1_WDEN:
#endif /* #ifdef USE_BOARD_1 */
#if (USE_BOARD_0||USE_BOARD_1)
      *PinStatus = (uint8_t) HAL_GPIO_ReadPin(Pin->WDEN_GPort, Pin->WDEN_GPin);
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
int32_t OUT16_ReadFaultPin(IPS_RELAY_Pins_t *Pin, uint8_t* PinStatus)
{
  int32_t ret = 0;
  *PinStatus = ((uint8_t)(HAL_GPIO_ReadPin(Pin->FAULT_L_GPort, Pin->FAULT_L_GPin))
               |((uint8_t)HAL_GPIO_ReadPin(Pin->PGOOD_L_GPort, Pin->PGOOD_L_GPin) << 1U)
               |((uint8_t)HAL_GPIO_ReadPin(Pin->TWARN_L_GPort, Pin->TWARN_L_GPin) << 2U));
  return ret;
}

/******************************************************/
/********                                      ********/
/********            SPI BUS SECTION           ********/
/********                                      ********/
/******************************************************/

/**
  * @brief   Write and read SPI byte to the IPS8200HQ's
  * @param   deviceId Device Id (instance of the device object)
  * @param   pByteToTransmit pointer to the byte to transmit
  * @param   pReceivedByte pointer to the received byte
  * @param   nbDevices Number of device in the SPI chain
  * @retval  0 in case of success, an error code otherwise
  */
uint8_t OUT16_Board_SpiWrite(uint8_t deviceId, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices)
{
  int32_t status = 0;

  switch(deviceId)
  {
    case 0U:
#ifdef USE_BOARD_0
      HAL_GPIO_WritePin(OUT16_RELAY_0_SPI_SS_GPIO_PORT, OUT16_RELAY_0_SPI_SS_GPIO_PIN, GPIO_PIN_RESET);
#endif /* #ifdef USE_BOARD_0 */
      break;

    case 1U:
#ifdef USE_BOARD_1
      HAL_GPIO_WritePin(OUT16_RELAY_1_SPI_SS_GPIO_PORT, OUT16_RELAY_1_SPI_SS_GPIO_PIN, GPIO_PIN_RESET);
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
      status = OUT16_Spi_SendRecv(pByteToTransmit, pReceivedByte, 1U);
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
        HAL_GPIO_WritePin(OUT16_RELAY_0_SPI_SS_GPIO_PORT, OUT16_RELAY_0_SPI_SS_GPIO_PIN, GPIO_PIN_SET);
#endif /* #ifdef USE_BOARD_0 */
        break;

      case 1U:
#ifdef USE_BOARD_1
        HAL_GPIO_WritePin(OUT16_RELAY_1_SPI_SS_GPIO_PORT, OUT16_RELAY_1_SPI_SS_GPIO_PIN, GPIO_PIN_SET);
#endif /* #ifdef USE_BOARD_1 */
        break;

      default:
        status = (-1);
        break;
    }
  }

  return (uint8_t)status;
}
#endif /* #ifdef APP_SPI_IFC */

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
