/**
  ******************************************************************************
  * @file    out11a1.h
  * @author  AMS IPC Application Team
  * @brief   Header for out11a1.c module
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
#ifndef OUT11A1_H
#define OUT11A1_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out11a1_conf.h"
#include "out11a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT11A1 OUT11A1
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup OUT11A1_Exported_Types OUT11A1 Exported Types
  * @{
  */

/**
  * @brief  SWITCH driver structure definition
  */
typedef struct
{
  /** function pointer to Init function */
  int32_t (*Init)(void *);
  /** function pointer to DeInit function */
  int32_t (*DeInit)(void *);
  /** function pointer to ReadID function */
  int32_t (*ReadID)(void *, uint16_t *);
  /** function pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(void *, void *);
  /** function pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(void *, uint8_t *);
  /** function pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(void *, uint8_t, uint8_t *);
  /** function pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(void *, uint8_t, uint8_t);
  /** function pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(void *, uint8_t *);
  /** function pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(void *, uint8_t);
  /** function pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(void *, uint8_t, uint16_t *);
  /** function pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(void *, uint8_t, uint16_t);
  /** function pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(void *, uint8_t, uint8_t *);
  /** function pointer to SetChannelDc function */
  int32_t (*SetChannelDc)(void *, uint8_t, uint8_t);
  /** function pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(void *, uint8_t, uint8_t *);
  /** function pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(void *, uint8_t, uint8_t);
  /** function pointer to PwmTick function */
  int32_t (*PwmTick)(void *);
  /** function pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus)(void *, uint8_t, uint8_t *);
  /** function pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus)(void *, uint8_t, uint8_t);
  /** function pointer to SetOperatingMode function */
  int32_t (*SetOperatingMode)(void *, uint8_t);
} SWITCH_CommonDrv_t;

/** Structure for initial switch parameters Info */
typedef struct
{
  /** PWM Frequency */
  uint32_t pwmFreq;
} OUT11_SWITCH_Init_Parameters_t;


/** Switch instance Info */
typedef struct
{
  /** Number of supported channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} OUT11_SWITCH_Capabilities_t;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT11A1_Exported_Constants OUT11A1 Exported Constants
  * @{
  */

/** CHIP ID  */
#define OUT11_SWITCH_CHIP_ID IPS_SWITCH_CHIP_ID

/** Number of supported switch instances*/
#define OUT11_SWITCH_INSTANCES_NBR (1U)

/** Number of supported switch devices*/
#define OUT11_SWITCH_DEVICES_NBR IPS_SWITCH_DEVICES_NBR

/** Direct Control mode setting */
#define OUT11_SWITCH_DIRECT_CTRL_MODE IPS_SWITCH_DIRECT_CTRL_MODE

/** Synchronous Control mode setting */
#define OUT11_SWITCH_SYNC_CTRL_MODE IPS_SWITCH_SYNC_CTRL_MODE

/* Board 0 */
/** Input Pin: IN1 */
#define OUT11_SWITCH_0_IN1 IPS_SWITCH_0_IN1
/** Input Pin: IN2 */
#define OUT11_SWITCH_0_IN2 IPS_SWITCH_0_IN2
/** Input Pin: IN3 */
#define OUT11_SWITCH_0_IN3 IPS_SWITCH_0_IN3
/** Input Pin: IN4 */
#define OUT11_SWITCH_0_IN4 IPS_SWITCH_0_IN4
/** Input Pin: IN5 */
#define OUT11_SWITCH_0_IN5 IPS_SWITCH_0_IN5
/** Input Pin: IN6 */
#define OUT11_SWITCH_0_IN6 IPS_SWITCH_0_IN6
/** Input Pin: IN7 */
#define OUT11_SWITCH_0_IN7 IPS_SWITCH_0_IN7
/** Input Pin: IN8 */
#define OUT11_SWITCH_0_IN8 IPS_SWITCH_0_IN8
/** Control Pin: LOAD */
#define OUT11_SWITCH_0_CTRL_LOAD IPS_SWITCH_0_CTRL_LOAD
/** Control Pin: OUT_EN */
#define OUT11_SWITCH_0_CTRL_OUT_EN IPS_SWITCH_0_CTRL_OUT_EN
/** Control Pin: SYNCH */
#define OUT11_SWITCH_0_CTRL_SYNCH IPS_SWITCH_0_CTRL_SYNCH

/** IN1 Port 0 */
#define OUT11_SWITCH_0_IN1_GPIO_PORT IPS_SWITCH_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define OUT11_SWITCH_0_IN1_GPIO_PIN IPS_SWITCH_0_IN1_GPIO_PIN
/** IN2 Port 0 */
#define OUT11_SWITCH_0_IN2_GPIO_PORT IPS_SWITCH_0_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define OUT11_SWITCH_0_IN2_GPIO_PIN IPS_SWITCH_0_IN2_GPIO_PIN
/** IN3 Port 0 */
#define OUT11_SWITCH_0_IN3_GPIO_PORT IPS_SWITCH_0_IN3_GPIO_PORT
/** IN3 Pin 0 */
#define OUT11_SWITCH_0_IN3_GPIO_PIN IPS_SWITCH_0_IN3_GPIO_PIN
/** IN4 Port 0 */
#define OUT11_SWITCH_0_IN4_GPIO_PORT IPS_SWITCH_0_IN4_GPIO_PORT
/** IN4 Pin 0 */
#define OUT11_SWITCH_0_IN4_GPIO_PIN IPS_SWITCH_0_IN4_GPIO_PIN
/** IN5 Port 0 */
#define OUT11_SWITCH_0_IN5_GPIO_PORT IPS_SWITCH_0_IN5_GPIO_PORT
/** IN5 Pin 0 */
#define OUT11_SWITCH_0_IN5_GPIO_PIN IPS_SWITCH_0_IN5_GPIO_PIN
/** IN6 Port 0 */
#define OUT11_SWITCH_0_IN6_GPIO_PORT IPS_SWITCH_0_IN6_GPIO_PORT
/** IN6 Pin 0 */
#define OUT11_SWITCH_0_IN6_GPIO_PIN IPS_SWITCH_0_IN6_GPIO_PIN
/** IN7 Port 0 */
#define OUT11_SWITCH_0_IN7_GPIO_PORT IPS_SWITCH_0_IN7_GPIO_PORT
/** IN7 Pin 0 */
#define OUT11_SWITCH_0_IN7_GPIO_PIN IPS_SWITCH_0_IN7_GPIO_PIN
/** IN8 Port 0 */
#define OUT11_SWITCH_0_IN8_GPIO_PORT IPS_SWITCH_0_IN8_GPIO_PORT
/** IN8 Pin 0 */
#define OUT11_SWITCH_0_IN8_GPIO_PIN IPS_SWITCH_0_IN8_GPIO_PIN

/** LOAD Port 0 */
#define OUT11_SWITCH_0_LOAD_GPIO_PORT IPS_SWITCH_0_LOAD_GPIO_PORT
/** LOAD Pin 0 */
#define OUT11_SWITCH_0_LOAD_GPIO_PIN IPS_SWITCH_0_LOAD_GPIO_PIN
/** OUT_EN Port 0 */
#define OUT11_SWITCH_0_OUT_EN_GPIO_PORT IPS_SWITCH_0_OUT_EN_GPIO_PORT
/** OUT_EN Pin 0 */
#define OUT11_SWITCH_0_OUT_EN_GPIO_PIN IPS_SWITCH_0_OUT_EN_GPIO_PIN
/** SYNCH Port 0 */
#define OUT11_SWITCH_0_SYNCH_GPIO_PORT IPS_SWITCH_0_SYNCH_GPIO_PORT
/** SYNCH Pin 0 */
#define OUT11_SWITCH_0_SYNCH_GPIO_PIN IPS_SWITCH_0_SYNCH_GPIO_PIN

/** STATUS Port 0 */
#define OUT11_SWITCH_0_STATUS_GPIO_PORT IPS_SWITCH_0_STATUS_GPIO_PORT
/** STATUS Pin 0 */
#define OUT11_SWITCH_0_STATUS_GPIO_PIN IPS_SWITCH_0_STATUS_GPIO_PIN

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT11A1_Exported_Variables OUT11A1 Exported Variables
  * @{
  */

extern void *SWITCH_CompObj[OUT11_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT11A1_Exported_Functions OUT11A1 Exported Functions
  * @{
  */
int32_t BSP_GetTick(void);

int32_t OUT11_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT11_SWITCH_Init_Parameters_t *pInitParam);
int32_t OUT11_SWITCH_DeInit(uint8_t Instance);
int32_t OUT11_SWITCH_GetCapabilities(uint8_t Instance, OUT11_SWITCH_Capabilities_t *pCapabilities);
int32_t OUT11_SWITCH_ReadID(uint8_t Instance, uint16_t *pId);
int32_t OUT11_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc);
int32_t OUT11_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc);
int32_t OUT11_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq);
int32_t OUT11_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq);
int32_t OUT11_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus);
int32_t OUT11_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT11_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap);
int32_t OUT11_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT11_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus);
int32_t OUT11_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable);
int32_t OUT11_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable);
int32_t OUT11_SWITCH_PwmTick(uint8_t Instance);
int32_t OUT11_SWITCH_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t OUT11_SWITCH_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t OUT11_SWITCH_SetOperatingMode(uint8_t Instance, uint8_t opMode);
__weak int32_t OUT11_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT11A1_H */
