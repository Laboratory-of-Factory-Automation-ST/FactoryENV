/**
  ******************************************************************************
  * @file    out03a1.h
  * @author  AMS IPC Application Team
  * @brief   Header for out03a1.c module
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
#ifndef OUT03A1_H
#define OUT03A1_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out03a1_conf.h"
#include "out03a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT03A1 OUT03A1
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup OUT03A1_Exported_Types OUT03A1 Exported Types
  * @{
  */

/**
 * @brief  SWITCH driver structure definition
 */
typedef struct
{
  /** function pointer to Init function */
  int32_t ( *Init                 ) ( void *);
  /** function pointer to DeInit function */
  int32_t ( *DeInit               ) ( void * );
  /** function pointer to ReadID function */
  int32_t ( *ReadID               ) ( void *, uint16_t * );
  /** function pointer to GetCapabilities function */
  int32_t ( *GetCapabilities      ) ( void *, void * );
  /** function pointer to GetFaultStatus function */
  int32_t ( *GetFaultStatus       ) ( void *, uint8_t * );
  /** function pointer to GetChannelStatus function */
  int32_t ( *GetChannelStatus     ) ( void *, uint8_t , uint8_t * );
  /** function pointer to SetChannelStatus function */
  int32_t ( *SetChannelStatus     ) ( void *, uint8_t , uint8_t );
  /** function pointer to GetAllChannelStatus function */
  int32_t ( *GetAllChannelStatus  ) ( void *, uint8_t * );
  /** function pointer to SetAllChannelStatus function */
  int32_t ( *SetAllChannelStatus  ) ( void *, uint8_t );
  /** function pointer to GetChannelFreq function */
  int32_t ( *GetChannelFreq       ) ( void *, uint8_t , uint16_t * );
  /** function pointer to SetChannelFreq function */
  int32_t ( *SetChannelFreq       ) ( void *, uint8_t , uint16_t );
  /** function pointer to GetChannelDc function */
  int32_t ( *GetChannelDc         ) ( void *, uint8_t , uint8_t * );
  /** function pointer to SetChannelDc function */
  int32_t ( *SetChannelDc         ) ( void *, uint8_t , uint8_t );
  /** function pointer to GetPwmEnable function */
  int32_t ( *GetPwmEnable         ) ( void *, uint8_t, uint8_t * );
  /** function pointer to SetPwmEnable function */
  int32_t ( *SetPwmEnable         ) ( void *, uint8_t, uint8_t );
  /** function pointer to PwmTick function */
  int32_t ( *PwmTick              ) ( void *);
} SWITCH_CommonDrv_t;

/** Structure for initial switch parameters Info */
typedef struct
{
  /** PWM Frequency */
  uint32_t pwmFreq;
} OUT03_SWITCH_Init_Parameters_t;

/** Switch instance Info */
typedef struct
{
  /** Number of supported channels */
  uint8_t nbChannels;
} OUT03_SWITCH_Capabilities_t;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT03A1_Exported_Constants OUT03A1 Exported Constants
  * @{
  */

/** CHIP ID */
#define OUT03_SWITCH_CHIP_ID IPS_SWITCH_CHIP_ID

/** Number of supported switch instances*/
#define OUT03_SWITCH_INSTANCES_NBR (4U)

/** Number of supported switch devices*/
#define OUT03_SWITCH_DEVICES_NBR IPS_SWITCH_DEVICES_NBR

#ifdef USE_BOARD_0
/* Board 0 */
/** IN1 Port 0 */
#define OUT03_SWITCH_0_IN1_GPIO_PORT IPS_SWITCH_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define OUT03_SWITCH_0_IN1_GPIO_PIN IPS_SWITCH_0_IN1_GPIO_PIN
/** IN2 Port 0 */
#define OUT03_SWITCH_0_IN2_GPIO_PORT IPS_SWITCH_0_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define OUT03_SWITCH_0_IN2_GPIO_PIN IPS_SWITCH_0_IN2_GPIO_PIN
/** FLT1 Port 0 */
#define OUT03_SWITCH_0_FLT1_GPIO_PORT IPS_SWITCH_0_FLT1_GPIO_PORT
/** FLT1 Pin 0 */
#define OUT03_SWITCH_0_FLT1_GPIO_PIN IPS_SWITCH_0_FLT1_GPIO_PIN
/** FLT2 Port 0 */
#define OUT03_SWITCH_0_FLT2_GPIO_PORT IPS_SWITCH_0_FLT2_GPIO_PORT
/** FLT2 Pin 0 */
#define OUT03_SWITCH_0_FLT2_GPIO_PIN IPS_SWITCH_0_FLT2_GPIO_PIN
#endif /* #ifdef USE_BOARD_0 */

#ifdef USE_BOARD_1
/* Board 1 */
/** IN1 Port 0 */
#define OUT03_SWITCH_1_IN1_GPIO_PORT IPS_SWITCH_1_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define OUT03_SWITCH_1_IN1_GPIO_PIN IPS_SWITCH_1_IN1_GPIO_PIN
/** IN2 Port 0 */
#define OUT03_SWITCH_1_IN2_GPIO_PORT IPS_SWITCH_1_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define OUT03_SWITCH_1_IN2_GPIO_PIN IPS_SWITCH_1_IN2_GPIO_PIN
/** FLT1 Port 0 */
#define OUT03_SWITCH_1_FLT1_GPIO_PORT IPS_SWITCH_1_FLT1_GPIO_PORT
/** FLT1 Pin 0 */
#define OUT03_SWITCH_1_FLT1_GPIO_PIN IPS_SWITCH_1_FLT1_GPIO_PIN
/** FLT2 Port 0 */
#define OUT03_SWITCH_1_FLT2_GPIO_PORT IPS_SWITCH_1_FLT2_GPIO_PORT
/** FLT2 Pin 0 */
#define OUT03_SWITCH_1_FLT2_GPIO_PIN IPS_SWITCH_1_FLT2_GPIO_PIN
#endif /* #ifdef USE_BOARD_1 */

#ifdef USE_BOARD_2
/* Board 2 */
/** IN1 Port 0 */
#define OUT03_SWITCH_2_IN1_GPIO_PORT IPS_SWITCH_2_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define OUT03_SWITCH_2_IN1_GPIO_PIN IPS_SWITCH_2_IN1_GPIO_PIN
/** IN2 Port 0 */
#define OUT03_SWITCH_2_IN2_GPIO_PORT IPS_SWITCH_2_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define OUT03_SWITCH_2_IN2_GPIO_PIN IPS_SWITCH_2_IN2_GPIO_PIN
/** FLT1 Port 0 */
#define OUT03_SWITCH_2_FLT1_GPIO_PORT IPS_SWITCH_2_FLT1_GPIO_PORT
/** FLT1 Pin 0 */
#define OUT03_SWITCH_2_FLT1_GPIO_PIN IPS_SWITCH_2_FLT1_GPIO_PIN
/** FLT2 Port 0 */
#define OUT03_SWITCH_2_FLT2_GPIO_PORT IPS_SWITCH_2_FLT2_GPIO_PORT
/** FLT2 Pin 0 */
#define OUT03_SWITCH_2_FLT2_GPIO_PIN IPS_SWITCH_2_FLT2_GPIO_PIN
#endif /* #ifdef USE_BOARD_2 */

#ifdef USE_BOARD_3
/* Board 3 */
/** IN1 Port 0 */
#define OUT03_SWITCH_3_IN1_GPIO_PORT IPS_SWITCH_3_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define OUT03_SWITCH_3_IN1_GPIO_PIN IPS_SWITCH_3_IN1_GPIO_PIN
/** IN2 Port 0 */
#define OUT03_SWITCH_3_IN2_GPIO_PORT IPS_SWITCH_3_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define OUT03_SWITCH_3_IN2_GPIO_PIN IPS_SWITCH_3_IN2_GPIO_PIN
/** FLT1 Port 0 */
#define OUT03_SWITCH_3_FLT1_GPIO_PORT IPS_SWITCH_3_FLT1_GPIO_PORT
/** FLT1 Pin 0 */
#define OUT03_SWITCH_3_FLT1_GPIO_PIN IPS_SWITCH_3_FLT1_GPIO_PIN
/** FLT2 Port 0 */
#define OUT03_SWITCH_3_FLT2_GPIO_PORT IPS_SWITCH_3_FLT2_GPIO_PORT
/** FLT2 Pin 0 */
#define OUT03_SWITCH_3_FLT2_GPIO_PIN IPS_SWITCH_3_FLT2_GPIO_PIN
#endif /* #ifdef USE_BOARD_3 */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT03A1_Exported_Variables OUT03A1 Exported Variables
  * @{
  */

extern void *SWITCH_CompObj[OUT03_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT03A1_Exported_Functions OUT03A1 Exported Functions
  * @{
  */
int32_t OUT03_SWITCH_RegisterCallBack(uint8_t Instance, void (*fault1_isr)(void), void (*fault2_isr)(void));

int32_t BSP_GetTick(void);
int32_t OUT03_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT03_SWITCH_Init_Parameters_t *pInitParam);
int32_t OUT03_SWITCH_DeInit(uint8_t Instance);
int32_t OUT03_SWITCH_GetCapabilities(uint8_t Instance, OUT03_SWITCH_Capabilities_t *pCapabilities);
int32_t OUT03_SWITCH_ReadID(uint8_t Instance, uint16_t *pId);
int32_t OUT03_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc);
int32_t OUT03_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc);
int32_t OUT03_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq);
int32_t OUT03_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq);
int32_t OUT03_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus);
int32_t OUT03_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT03_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap);
int32_t OUT03_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT03_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus);
int32_t OUT03_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable);
int32_t OUT03_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable);
int32_t OUT03_SWITCH_PwmTick(uint8_t Instance);
__weak int32_t OUT03_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT03A1_H */
