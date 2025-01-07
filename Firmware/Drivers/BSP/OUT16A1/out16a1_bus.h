/**
  ******************************************************************************
  * @file           : out16a1_bus.h
  * @author         : AMS IPC IO-Link Application Team
  * @brief          : Bus definitions.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OUT16A1_BUS_H
#define OUT16A1_BUS_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out16a1_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT16A1_BUS OUT16A1_BUS
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT16A1_BUS_Exported_Constants OUT16A1_BUS Exported Constants
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

/** @defgroup OUT16A1_BUS_Exported_Functions OUT16A1_BUS Exported Functions
  * @{
  */

#ifdef APP_PAR_IFC
/* BUS IO driver over GPIO Peripheral */

int32_t OUT16_SetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t PinStatus);
int32_t OUT16_GetChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t ChanId, uint8_t* PinStatus);
int32_t OUT16_SetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinStatusBitmap);
int32_t OUT16_GetAllChanInputPin(IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatusBitmap);
int32_t OUT16_ReadFaultPin(IPS_SWITCH_Pins_t *Pin, uint8_t* PinStatus);
int32_t OUT16_SetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus);
int32_t OUT16_GetControlPin(IPS_SWITCH_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus);
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
/* BUS IO driver over SPI Peripheral */

/* Initialize SPI used for IPS8200HQ */
uint8_t OUT16_Board_SpiInit(uint32_t spiFreq);
/* Deinitialise SPI used for IPS8200HQ */
int32_t OUT16_Board_SpiDeInit(void);
/* SPI write transaction */
uint8_t OUT16_Board_SpiWrite(uint8_t deviceId, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices);

int32_t OUT16_SetAllChanInputPin(IPS_RELAY_Pins_t *Pin, uint8_t PinStatusBitmap);
int32_t OUT16_GetAllChanInputPin(IPS_RELAY_Pins_t *Pin, uint8_t* PinStatusBitmap);
int32_t OUT16_SetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t PinStatus);
int32_t OUT16_GetControlPin(IPS_RELAY_Pins_t *Pin, uint8_t PinId, uint8_t* PinStatus);
int32_t OUT16_ReadFaultPin(IPS_RELAY_Pins_t *Pin, uint8_t* PinStatus);
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


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* OUT16A1_BUS_H */
