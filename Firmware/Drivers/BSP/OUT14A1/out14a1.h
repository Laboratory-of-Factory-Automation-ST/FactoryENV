/**
  ******************************************************************************
  * @file    out14a1.h
  * @author  AMS IPC Application Team
  * @brief   Header for out14a1.c module
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
#ifndef OUT14A1_H
#define OUT14A1_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out14a1_conf.h"
#include "out14a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT14A1 OUT14A1
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup OUT14A1_Exported_Types OUT14A1 Exported Types
  * @{
  */

/**
  * @brief  RELAY driver structure definition
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
  /** function pointer to GetFaultRegister function */
  int32_t (*GetFaultRegister)(void *, uint8_t *);
  /** function pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(void *, uint8_t, uint8_t *);
  /** function pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(void *, uint8_t, uint8_t);
  /** function pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus     )( void *, uint8_t , uint8_t *);
  /** function pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus     )( void *, uint8_t , uint8_t);
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
  /** function pointer to GuardTimerTick function */
  int32_t (*GuardTimerTick)(void *);
  /** function pointer to QueueChannelStatus function */
  int32_t (*QueueChannelStatus)(void *, uint8_t, uint8_t);
  /** function pointer to QueueAllChannelStatus function */
  int32_t (*QueueAllChannelStatus)(void *, uint8_t);
  /** function pointer to SendQueuedChannelStatus function */
  int32_t (*SendQueuedChannelStatus)(void);
  /** function pointer to GetFaultRegister_DaisyChain function */
  int32_t (*GetFaultRegister_DaisyChain)(uint16_t *);
  /** function pointer to PwmTick_DaisyChain function */
  int32_t (*PwmTick_DaisyChain)(void *);
  /** function pointer to GuardTimerTick_DaisyChain function */
  int32_t (*GuardTimerTick_DaisyChain)(void *);
} RELAY_CommonDrv_t;

/** Structure for initial relay parameters Info */
typedef struct
{
  /** PWM Frequency */
  uint32_t pwmFreq;
  /** SPI Frequency */
  uint32_t spiFreq;
  /** Tcss delay in us */
  uint8_t timingTcss;
  /** Operating mode */
  uint8_t opMode;
} OUT14_RELAY_Init_Parameters_t;


/** Relay instance Info */
typedef struct
{
  /** Number of supported channels */
  uint8_t nbChannels;
} OUT14_RELAY_Capabilities_t;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT14A1_Exported_Constants OUT14A1 Exported Constants
  * @{
  */

/** CHIP ID  */
#define OUT14_RELAY_CHIP_ID IPS_RELAY_CHIP_ID

/** Number of supported relay instances*/
#define OUT14_RELAY_INSTANCES_NBR (2U)

/** Number of supported relay devices*/
#define OUT14_RELAY_DEVICES_NBR IPS_RELAY_DEVICES_NBR

/** Undefined Control mode setting */
#define OUT14_RELAY_UNDEF_MODE IPS_RELAY_UNDEF_MODE

/** Synchronous Control mode setting */
#define OUT14_RELAY_PAR_IND_MODE IPS_RELAY_PAR_IND_MODE

/** Direct Control mode setting */
#define OUT14_RELAY_DAISY_CHAIN_MODE IPS_RELAY_DAISY_CHAIN_MODE

/** Fully populated system in daisy chain mode */
#define OUT14_RELAY_DAISY_CHAIN_FULLSYS IPS_RELAY_DAISY_CHAIN_FULLSYS

/** SPI frequency for relay */
#define OUT14_RELAY_CONF_PARAM_SPI_FREQ IPS_RELAY_CONF_PARAM_SPI_FREQ

/** Tcss delay in us */
#define OUT14_RELAY_CONF_PARAM_TIMING_TCSS IPS_RELAY_CONF_PARAM_TIMING_TCSS

/* Dev pins */
#ifdef USE_BOARD_0
/* Board 0 */
/** Device Chan: IN1 */
#define OUT14_RELAY_0_IN1 IPS_RELAY_0_IN1
/** Device Chan: IN2 */
#define OUT14_RELAY_0_IN2 IPS_RELAY_0_IN2
/** Device Chan: IN3 */
#define OUT14_RELAY_0_IN3 IPS_RELAY_0_IN3
/** Device Chan: IN4 */
#define OUT14_RELAY_0_IN4 IPS_RELAY_0_IN4
/** Device Chan: IN5 */
#define OUT14_RELAY_0_IN5 IPS_RELAY_0_IN5
/** Device Chan: IN6 */
#define OUT14_RELAY_0_IN6 IPS_RELAY_0_IN6
/** Device Chan: IN7 */
#define OUT14_RELAY_0_IN7 IPS_RELAY_0_IN7
/** Device Chan: IN8 */
#define OUT14_RELAY_0_IN8 IPS_RELAY_0_IN8

/** Input Pin: SPI_CLK */
#define OUT14_RELAY_0_SPI_CLK IPS_RELAY_0_SPI_CLK
/** Input Pin: SPI_MISO */
#define OUT14_RELAY_0_SPI_MISO IPS_RELAY_0_SPI_MISO
/** Input Pin: SPI_MOSI */
#define OUT14_RELAY_0_SPI_MOSI IPS_RELAY_0_SPI_MOSI

/** Control Pin: SPI_SS */
#define OUT14_RELAY_0_SPI_SS IPS_RELAY_0_SPI_SS
/** Control Pin: OUT_EN */
#define OUT14_RELAY_0_OUT_EN IPS_RELAY_0_OUT_EN

/** SPI_SS Port 0 */
#define OUT14_RELAY_0_SPI_SS_GPIO_PORT IPS_RELAY_0_SPI_SS_GPIO_PORT
/** SPI_SS Pin 0 */
#define OUT14_RELAY_0_SPI_SS_GPIO_PIN IPS_RELAY_0_SPI_SS_GPIO_PIN
/** OUT_EN Port 0 */
#define OUT14_RELAY_0_OUT_EN_GPIO_PORT IPS_RELAY_0_OUT_EN_GPIO_PORT
/** OUT_EN Pin 0 */
#define OUT14_RELAY_0_OUT_EN_GPIO_PIN IPS_RELAY_0_OUT_EN_GPIO_PIN

/** STATUS Port 0 */
#define OUT14_RELAY_0_STATUS_GPIO_PORT IPS_RELAY_0_STATUS_GPIO_PORT
/** STATUS Pin 0 */
#define OUT14_RELAY_0_STATUS_GPIO_PIN IPS_RELAY_0_STATUS_GPIO_PIN
/** PGOOD Port 0 */
#define OUT14_RELAY_0_PGOOD_GPIO_PORT IPS_RELAY_0_PGOOD_GPIO_PORT
/** PGOOD Pin 0 */
#define OUT14_RELAY_0_PGOOD_GPIO_PIN IPS_RELAY_0_PGOOD_GPIO_PIN
#endif /* #ifdef USE_BOARD_0 */

#ifdef USE_BOARD_1
/* Board 1 */
/** Device Chan: IN1 */
#define OUT14_RELAY_1_IN1 IPS_RELAY_1_IN1
/** Device Chan: IN2 */
#define OUT14_RELAY_1_IN2 IPS_RELAY_1_IN2
/** Device Chan: IN3 */
#define OUT14_RELAY_1_IN3 IPS_RELAY_1_IN3
/** Device Chan: IN4 */
#define OUT14_RELAY_1_IN4 IPS_RELAY_1_IN4
/** Device Chan: IN5 */
#define OUT14_RELAY_1_IN5 IPS_RELAY_1_IN5
/** Device Chan: IN6 */
#define OUT14_RELAY_1_IN6 IPS_RELAY_1_IN6
/** Device Chan: IN7 */
#define OUT14_RELAY_1_IN7 IPS_RELAY_1_IN7
/** Device Chan: IN8 */
#define OUT14_RELAY_1_IN8 IPS_RELAY_1_IN8

/** Input Pin: SPI_CLK */
#define OUT14_RELAY_1_SPI_CLK IPS_RELAY_1_SPI_CLK
/** Input Pin: SPI_MISO */
#define OUT14_RELAY_1_SPI_MISO IPS_RELAY_1_SPI_MISO
/** Input Pin: SPI_MOSI */
#define OUT14_RELAY_1_SPI_MOSI IPS_RELAY_1_SPI_MOSI

/** Control Pin: SPI_SS */
#define OUT14_RELAY_1_SPI_SS IPS_RELAY_1_SPI_SS
/** Control Pin: OUT_EN_Alt1 */
#define OUT14_RELAY_1_OUT_EN IPS_RELAY_1_OUT_EN

/** SPI_SS Port 0 */
#define OUT14_RELAY_1_SPI_SS_GPIO_PORT IPS_RELAY_1_SPI_SS_GPIO_PORT
/** SPI_SS Pin 0 */
#define OUT14_RELAY_1_SPI_SS_GPIO_PIN IPS_RELAY_1_SPI_SS_GPIO_PIN
/** OUT_EN Port 0 */
#define OUT14_RELAY_1_OUT_EN_GPIO_PORT IPS_RELAY_1_OUT_EN_GPIO_PORT
/** OUT_EN Pin 0 */
#define OUT14_RELAY_1_OUT_EN_GPIO_PIN IPS_RELAY_1_OUT_EN_GPIO_PIN

/** STATUS Port 0 */
#define OUT14_RELAY_1_STATUS_GPIO_PORT IPS_RELAY_1_STATUS_GPIO_PORT
/** STATUS Pin 0 */
#define OUT14_RELAY_1_STATUS_GPIO_PIN IPS_RELAY_1_STATUS_GPIO_PIN
/** PGOOD Port 0 */
#define OUT14_RELAY_1_PGOOD_GPIO_PORT IPS_RELAY_1_PGOOD_GPIO_PORT
/** PGOOD Pin 0 */
#define OUT14_RELAY_1_PGOOD_GPIO_PIN IPS_RELAY_1_PGOOD_GPIO_PIN
#endif /* #ifdef USE_BOARD_1 */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT14A1_Exported_Variables OUT14A1 Exported Variables
  * @{
  */

extern void *RELAY_CompObj[OUT14_RELAY_INSTANCES_NBR];

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT14A1_Exported_Functions OUT14A1 Exported Functions
  * @{
  */
/* Common functions */
int32_t OUT14_RELAY_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, uint8_t opMode, OUT14_RELAY_Init_Parameters_t *pInitParam);
int32_t OUT14_RELAY_DeInit(uint8_t Instance);
int32_t OUT14_RELAY_GetCapabilities(uint8_t Instance, OUT14_RELAY_Capabilities_t *pCapabilities);
int32_t OUT14_RELAY_ReadID(uint8_t Instance, uint16_t *pId);
int32_t OUT14_RELAY_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc);
int32_t OUT14_RELAY_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc);
int32_t OUT14_RELAY_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq);
int32_t OUT14_RELAY_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq);
int32_t OUT14_RELAY_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus);
int32_t OUT14_RELAY_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT14_RELAY_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap);
int32_t OUT14_RELAY_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT14_RELAY_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus);
int32_t OUT14_RELAY_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable);
int32_t OUT14_RELAY_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable);
int32_t OUT14_RELAY_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t OUT14_RELAY_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus);

/* Regular (parallel independent) mode specific functions */
int32_t OUT14_RELAY_GetFaultRegister(uint8_t Instance, uint8_t *pFaultRegister);
int32_t OUT14_RELAY_PwmTick(uint8_t Instance);
int32_t OUT14_RELAY_GuardTimerTick(uint8_t Instance);

/* Daisy Chain mode specific functions */
int32_t OUT14_RELAY_QueueChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT14_RELAY_QueueAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT14_RELAY_SendQueuedChannelStatus(uint8_t Instance);
int32_t OUT14_RELAY_GetFaultRegister_DaisyChain(uint8_t Instance, uint16_t *pFaultRegister);
int32_t OUT14_RELAY_PwmTick_DaisyChain(void);
int32_t OUT14_RELAY_GuardTimerTick_DaisyChain(void);

void OUT14_EnableIrq(void);
void OUT14_DisableIrq(void);

int32_t OUT14_RELAY_RegisterCallBack(uint8_t Instance, void (*status_isr)(void), void (*pgood_isr)(void));
__weak int32_t OUT14_SetTimerForPwm(uint8_t pwmEnable);
__weak int32_t OUT14_GuardTimerStart(void);
__weak int32_t OUT14_GuardTimerStop(void);

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

#endif /* OUT14A1_H */
