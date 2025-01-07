/**
  ******************************************************************************
  * @file           : out14a1_bus.h
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
#ifndef OUT14A1_BUS_H
#define OUT14A1_BUS_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out14a1_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT14A1_BUS OUT14A1_BUS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT14A1_BUS_Exported_Constants OUT14A1_BUS Exported Constants
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

/** @defgroup OUT14A1_BUS_Exported_Functions OUT14A1_BUS Exported Functions
  * @{
  */

/* BUS IO driver over SPI Peripheral */

/* Initialize SPI used for ISO808A_1 */
uint8_t OUT14_Board_SpiInit(uint32_t spiFreq);
/* Deinitialise SPI used for ISO808A_1 */
int32_t OUT14_Board_SpiDeInit(void);
/* SPI write transaction */
uint8_t OUT14_Board_SpiWrite(uint8_t deviceId, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices);

int32_t OUT14_SetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus);
int32_t OUT14_GetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus);
int32_t OUT14_SetAllChanInputPin(IPS_RELAY_Pins_t *Pin, uint8_t PinStatusBitmap);
int32_t OUT14_GetAllChanInputPin(IPS_RELAY_Pins_t *Pin, uint8_t* PinStatusBitmap);
int32_t OUT14_ReadFaultPin(IPS_RELAY_Pins_t *Pin, uint8_t* PinStatus);

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

#endif /* OUT14A1_BUS_H */
