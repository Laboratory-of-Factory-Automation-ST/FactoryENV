/**
  ******************************************************************************
  * @file    out16a1.h
  * @author  AMS IPC Application Team
  * @brief   Header for out16a1.c module
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
#ifndef OUT16A1_H
#define OUT16A1_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out16a1_conf.h"
#include "out16a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT16A1 OUT16A1
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup OUT16A1_Exported_Types OUT16A1 Exported Types
  * @{
  */

#ifdef APP_PAR_IFC
/** Structure for initial switch parameters Info */
typedef struct
{
  /** PWM Frequency */
  uint32_t pwmFreq;
  /** Operating mode */
  uint8_t opMode;
} OUT16_SWITCH_Init_Parameters_t;

/** Switch instance Info */
typedef struct
{
  /** Number of supported channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} OUT16_SWITCH_Capabilities_t;
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
  int32_t (*SetOperatingMode)(void *, uint8_t *);
  /** function pointer to GetChipType function */
  int32_t (*GetChipType)(void *, uint8_t *);
} SWITCH_CommonDrv_t;
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
/** Structure for initial relay parameters Info */
typedef struct
{
  /** PWM Frequency */
  uint32_t pwmFreq;
  /** SPI Frequency */
  uint32_t spiFreq;
  /** Tcss delay in us */
  uint8_t timingTcss;
  /** Twd delay in us */
  uint32_t timingTwd;
  /** Twm delay in us */
  uint32_t timingTwm;
  /** Operating mode */
  uint8_t opMode;
} OUT16_RELAY_Init_Parameters_t;


/** Relay instance Info */
typedef struct
{
  /** Number of supported channels */
  uint8_t nbChannels;
} OUT16_RELAY_Capabilities_t;

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
  int32_t (*GetFaultRegister)(void *, uint16_t *);
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
  /** function pointer to WatchdogTimerTick function */
  int32_t (*WatchdogTimerTick)(void *);
  /** function pointer to QueueChannelStatus function */
  int32_t (*QueueChannelStatus)(void *, uint8_t, uint8_t);
  /** function pointer to QueueAllChannelStatus function */
  int32_t (*QueueAllChannelStatus)(void *, uint8_t);
  /** function pointer to SendQueuedChannelStatus function */
  int32_t (*SendQueuedChannelStatus)(void);
  /** function pointer to GetFaultRegister_DaisyChain function */
  int32_t (*GetFaultRegister_DaisyChain)(uint32_t *);
  /** function pointer to PwmTick_DaisyChain function */
  int32_t (*PwmTick_DaisyChain)(void *);
  /** function pointer to GuardTimerTick_DaisyChain function */
  int32_t (*GuardTimerTick_DaisyChain)(void *);
  /** function pointer to SetOperatingMode function */
  int32_t (*SetOperatingMode)(void *, uint8_t *);
  /** function pointer to GetChipType function */
  int32_t (*GetChipType)(void *, uint8_t *);
  /** function pointer to EnableDaisyChain function */
  int32_t (*EnableDaisyChain)(void *, uint8_t);
} RELAY_CommonDrv_t;
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT16A1_Exported_Constants OUT16A1 Exported Constants
  * @{
  */

/** Number of supported switch instances */
#define OUT16_INSTANCES_NBR IPS_INSTANCES_NBR

#ifdef APP_PAR_IFC
/** CHIP ID  */
#define OUT16_SWITCH_CHIP_ID IPS_SWITCH_CHIP_ID

/** Number of supported switch devices */
#define OUT16_SWITCH_DEVICES_NBR IPS_SWITCH_DEVICES_NBR

/* Board 0 */
/** Input Pin: IN1 */
#define OUT16_SWITCH_0_IN1 IPS_SWITCH_0_IN1
/** Input Pin: IN2 */
#define OUT16_SWITCH_0_IN2 IPS_SWITCH_0_IN2
/** Input Pin: IN3 */
#define OUT16_SWITCH_0_IN3 IPS_SWITCH_0_IN3
/** Input Pin: IN4 */
#define OUT16_SWITCH_0_IN4 IPS_SWITCH_0_IN4
/** Input Pin: IN5 */
#define OUT16_SWITCH_0_IN5 IPS_SWITCH_0_IN5
/** Input Pin: IN6 */
#define OUT16_SWITCH_0_IN6 IPS_SWITCH_0_IN6
/** Input Pin: IN7 */
#define OUT16_SWITCH_0_IN7 IPS_SWITCH_0_IN7
/** Input Pin: IN8 */
#define OUT16_SWITCH_0_IN8 IPS_SWITCH_0_IN8

/** IN1 Port 0 */
#define OUT16_SWITCH_0_IN1_GPIO_PORT IPS_SWITCH_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define OUT16_SWITCH_0_IN1_GPIO_PIN IPS_SWITCH_0_IN1_GPIO_PIN
/** IN2 Port 0 */
#define OUT16_SWITCH_0_IN2_GPIO_PORT IPS_SWITCH_0_IN2_GPIO_PORT
/** IN2 Pin 0 */
#define OUT16_SWITCH_0_IN2_GPIO_PIN IPS_SWITCH_0_IN2_GPIO_PIN
/** IN3 Port 0 */
#define OUT16_SWITCH_0_IN3_GPIO_PORT IPS_SWITCH_0_IN3_GPIO_PORT
/** IN3 Pin 0 */
#define OUT16_SWITCH_0_IN3_GPIO_PIN IPS_SWITCH_0_IN3_GPIO_PIN
/** IN4 Port 0 */
#define OUT16_SWITCH_0_IN4_GPIO_PORT IPS_SWITCH_0_IN4_GPIO_PORT
/** IN4 Pin 0 */
#define OUT16_SWITCH_0_IN4_GPIO_PIN IPS_SWITCH_0_IN4_GPIO_PIN
/** IN5 Port 0 */
#define OUT16_SWITCH_0_IN5_GPIO_PORT IPS_SWITCH_0_IN5_GPIO_PORT
/** IN5 Pin 0 */
#define OUT16_SWITCH_0_IN5_GPIO_PIN IPS_SWITCH_0_IN5_GPIO_PIN
/** IN6 Port 0 */
#define OUT16_SWITCH_0_IN6_GPIO_PORT IPS_SWITCH_0_IN6_GPIO_PORT
/** IN6 Pin 0 */
#define OUT16_SWITCH_0_IN6_GPIO_PIN IPS_SWITCH_0_IN6_GPIO_PIN
/** IN7 Port 0 */
#define OUT16_SWITCH_0_IN7_GPIO_PORT IPS_SWITCH_0_IN7_GPIO_PORT
/** IN7 Pin 0 */
#define OUT16_SWITCH_0_IN7_GPIO_PIN IPS_SWITCH_0_IN7_GPIO_PIN
/** IN8 Port 0 */
#define OUT16_SWITCH_0_IN8_GPIO_PORT IPS_SWITCH_0_IN8_GPIO_PORT
/** IN8 Pin 0 */
#define OUT16_SWITCH_0_IN8_GPIO_PIN IPS_SWITCH_0_IN8_GPIO_PIN

/** SEL2_L Port 0 */
#define OUT16_SWITCH_0_SEL2_L_GPIO_PORT IPS_SWITCH_0_SEL2_L_GPIO_PORT
/** SEL2_L Pin 0 */
#define OUT16_SWITCH_0_SEL2_L_GPIO_PIN IPS_SWITCH_0_SEL2_L_GPIO_PIN
/** SEL1 Port 0 */
#define OUT16_SWITCH_0_SEL1_GPIO_PORT IPS_SWITCH_0_SEL1_GPIO_PORT
/** SEL1 Pin 0 */
#define OUT16_SWITCH_0_SEL1_GPIO_PIN IPS_SWITCH_0_SEL1_GPIO_PIN

/** FAULT_L Port 0 */
#define OUT16_SWITCH_0_FAULT_L_GPIO_PORT IPS_SWITCH_0_FAULT_L_GPIO_PORT
/** FAULT_L Pin 0 */
#define OUT16_SWITCH_0_FAULT_L_GPIO_PIN IPS_SWITCH_0_FAULT_L_GPIO_PIN
/** PGOOD_L Port 0 */
#define OUT16_SWITCH_0_PGOOD_L_GPIO_PORT IPS_SWITCH_0_PGOOD_L_GPIO_PORT
/** PGOOD_L Pin 0 */
#define OUT16_SWITCH_0_PGOOD_L_GPIO_PIN IPS_SWITCH_0_PGOOD_L_GPIO_PIN
/** TWARN_L Port 0 */
#define OUT16_SWITCH_0_TWARN_L_GPIO_PORT IPS_SWITCH_0_TWARN_L_GPIO_PORT
/** TWARN_L Pin 0 */
#define OUT16_SWITCH_0_TWARN_L_GPIO_PIN IPS_SWITCH_0_TWARN_L_GPIO_PIN
#endif /* #ifdef APP_PAR_IFC */

/* Control Mode settings */

/** Undefined Control mode setting */
#define OUT16_UNDEF_CTRL_MODE IPS_UNDEF_CTRL_MODE

/** Parallel Control mode setting */
#define OUT16_PAR_CTRL_MODE IPS_PAR_CTRL_MODE

/** SPI Control mode setting */
#define OUT16_SPI_CTRL_MODE IPS_SPI_CTRL_MODE

/** SPI Daisy Chain Control mode setting */
#define OUT16_SPI_DC_CTRL_MODE IPS_SPI_DC_CTRL_MODE

/* SPI Width settings */

/** Undefined SPI Width setting */
#define  OUT16_SPI_W_NONE IPS_SPI_W_NONE

/** SPI 8bit Width setting */
#define  OUT16_SPI_W_8BIT IPS_SPI_W_8BIT

/** SPI 16bit Width setting */
#define  OUT16_SPI_W_16BIT IPS_SPI_W_16BIT

#ifdef APP_SPI_IFC
/** CHIP ID  */
#define OUT16_RELAY_CHIP_ID IPS_RELAY_CHIP_ID

/** Number of supported relay devices*/
#define OUT16_RELAY_DEVICES_NBR IPS_RELAY_DEVICES_NBR

/** Fully populated system in daisy chain mode */
#define OUT16_SPI_DC_FULLSYS IPS_SPI_DC_FULLSYS

/** SPI frequency for relay */
#define OUT16_RELAY_CONF_PARAM_SPI_FREQ IPS_RELAY_CONF_PARAM_SPI_FREQ

/** Tcss delay in us */
#define OUT16_RELAY_CONF_PARAM_TIMING_TCSS IPS_RELAY_CONF_PARAM_TIMING_TCSS

/** Twd delay in us */
#define OUT16_RELAY_CONF_PARAM_TIMING_TWD IPS_RELAY_CONF_PARAM_TIMING_TWD

/** Twm delay in us */
#define OUT16_RELAY_CONF_PARAM_TIMING_TWM IPS_RELAY_CONF_PARAM_TIMING_TWM

/* Dev pins */
#ifdef USE_BOARD_0
/* Board 0 */
/** Device Chan: IN1 */
#define OUT16_RELAY_0_IN1 IPS_RELAY_0_IN1
/** Device Chan: IN2 */
#define OUT16_RELAY_0_IN2 IPS_RELAY_0_IN2
/** Device Chan: IN3 */
#define OUT16_RELAY_0_IN3 IPS_RELAY_0_IN3
/** Device Chan: IN4 */
#define OUT16_RELAY_0_IN4 IPS_RELAY_0_IN4
/** Device Chan: IN5 */
#define OUT16_RELAY_0_IN5 IPS_RELAY_0_IN5
/** Device Chan: IN6 */
#define OUT16_RELAY_0_IN6 IPS_RELAY_0_IN6
/** Device Chan: IN7 */
#define OUT16_RELAY_0_IN7 IPS_RELAY_0_IN7
/** Device Chan: IN8 */
#define OUT16_RELAY_0_IN8 IPS_RELAY_0_IN8

/** Input Pin: SPI_CLK */
#define OUT16_RELAY_0_SPI_CLK IPS_RELAY_0_SPI_CLK
/** Input Pin: SPI_MISO */
#define OUT16_RELAY_0_SPI_MISO IPS_RELAY_0_SPI_MISO
/** Input Pin: SPI_MOSI */
#define OUT16_RELAY_0_SPI_MOSI IPS_RELAY_0_SPI_MOSI

/** Control Pin: SEL2_L */
#define OUT16_RELAY_0_SEL2_L IPS_RELAY_0_SEL2_L
/** Control Pin: SEL1 */
#define OUT16_RELAY_0_SEL1 IPS_RELAY_0_SEL1
/** Control Pin: SPI_SS */
#define OUT16_RELAY_0_SPI_SS IPS_RELAY_0_SPI_SS
/** Control Pin: OUT_EN */
#define OUT16_RELAY_0_OUT_EN IPS_RELAY_0_OUT_EN
/** Control Pin: WD */
#define OUT16_RELAY_0_WD IPS_RELAY_0_WD
/** Control Pin: WDEN */
#define OUT16_RELAY_0_WDEN IPS_RELAY_0_WDEN

/** SEL2_L Port 0 */
#define OUT16_RELAY_0_SEL2_L_GPIO_PORT IPS_RELAY_0_SEL2_L_GPIO_PORT
/** SEL2_L Pin 0 */
#define OUT16_RELAY_0_SEL2_L_GPIO_PIN IPS_RELAY_0_SEL2_L_GPIO_PIN
/** SEL1 Port 0 */
#define OUT16_RELAY_0_SEL1_GPIO_PORT IPS_RELAY_0_SEL1_GPIO_PORT
/** SEL1 Pin 0 */
#define OUT16_RELAY_0_SEL1_GPIO_PIN IPS_RELAY_0_SEL1_GPIO_PIN
/** SPI_SS Port 0 */
#define OUT16_RELAY_0_SPI_SS_GPIO_PORT IPS_RELAY_0_SPI_SS_GPIO_PORT
/** SPI_SS Pin 0 */
#define OUT16_RELAY_0_SPI_SS_GPIO_PIN IPS_RELAY_0_SPI_SS_GPIO_PIN
/** OUT_EN Port 0 */
#define OUT16_RELAY_0_OUT_EN_GPIO_PORT IPS_RELAY_0_OUT_EN_GPIO_PORT
/** OUT_EN Pin 0 */
#define OUT16_RELAY_0_OUT_EN_GPIO_PIN IPS_RELAY_0_OUT_EN_GPIO_PIN
/** WD Port 0 */
#define OUT16_RELAY_0_WD_GPIO_PORT IPS_RELAY_0_WD_GPIO_PORT
/** WD Pin 0 */
#define OUT16_RELAY_0_WD_GPIO_PIN IPS_RELAY_0_WD_GPIO_PIN
/** WDEN Port 0 */
#define OUT16_RELAY_0_WDEN_GPIO_PORT IPS_RELAY_0_WDEN_GPIO_PORT
/** WDEN Pin 0 */
#define OUT16_RELAY_0_WDEN_GPIO_PIN IPS_RELAY_0_WDEN_GPIO_PIN

/** FAULT_L Port 0 */
#define OUT16_RELAY_0_FAULT_L_GPIO_PORT IPS_RELAY_0_FAULT_L_GPIO_PORT
/** FAULT_L Pin 0 */
#define OUT16_RELAY_0_FAULT_L_GPIO_PIN IPS_RELAY_0_FAULT_L_GPIO_PIN
/** PGOOD_L Port 0 */
#define OUT16_RELAY_0_PGOOD_L_GPIO_PORT IPS_RELAY_0_PGOOD_L_GPIO_PORT
/** PGOOD_L Pin 0 */
#define OUT16_RELAY_0_PGOOD_L_GPIO_PIN IPS_RELAY_0_PGOOD_L_GPIO_PIN
/** TWARN_L Port 0 */
#define OUT16_RELAY_0_TWARN_L_GPIO_PORT IPS_RELAY_0_TWARN_L_GPIO_PORT
/** TWARN__L Pin 0 */
#define OUT16_RELAY_0_TWARN_L_GPIO_PIN IPS_RELAY_0_TWARN_L_GPIO_PIN
#endif /* #ifdef USE_BOARD_0 */

#ifdef USE_BOARD_1
/* Board 1 */
/** Device Chan: IN1 */
#define OUT16_RELAY_1_IN1 IPS_RELAY_1_IN1
/** Device Chan: IN2 */
#define OUT16_RELAY_1_IN2 IPS_RELAY_1_IN2
/** Device Chan: IN3 */
#define OUT16_RELAY_1_IN3 IPS_RELAY_1_IN3
/** Device Chan: IN4 */
#define OUT16_RELAY_1_IN4 IPS_RELAY_1_IN4
/** Device Chan: IN5 */
#define OUT16_RELAY_1_IN5 IPS_RELAY_1_IN5
/** Device Chan: IN6 */
#define OUT16_RELAY_1_IN6 IPS_RELAY_1_IN6
/** Device Chan: IN7 */
#define OUT16_RELAY_1_IN7 IPS_RELAY_1_IN7
/** Device Chan: IN8 */
#define OUT16_RELAY_1_IN8 IPS_RELAY_1_IN8

/** Input Pin: SPI_CLK */
#define OUT16_RELAY_1_SPI_CLK IPS_RELAY_1_SPI_CLK
/** Input Pin: SPI_MISO */
#define OUT16_RELAY_1_SPI_MISO IPS_RELAY_1_SPI_MISO
/** Input Pin: SPI_MOSI */
#define OUT16_RELAY_1_SPI_MOSI IPS_RELAY_1_SPI_MOSI

/** Control Pin: SEL2_L */
#define OUT16_RELAY_1_SEL2_L IPS_RELAY_1_SEL2_L
/** Control Pin: SEL1 */
#define OUT16_RELAY_1_SEL1 IPS_RELAY_1_SEL1
/** Control Pin: SPI_SS */
#define OUT16_RELAY_1_SPI_SS IPS_RELAY_1_SPI_SS
/** Control Pin: OUT_EN */
#define OUT16_RELAY_1_OUT_EN IPS_RELAY_1_OUT_EN
/** Control Pin: WD */
#define OUT16_RELAY_1_WD IPS_RELAY_1_WD
/** Control Pin: WDEN */
#define OUT16_RELAY_1_WDEN IPS_RELAY_1_WDEN

/** SPI_SS Port 1 */
#define OUT16_RELAY_1_SPI_SS_GPIO_PORT IPS_RELAY_1_SPI_SS_GPIO_PORT
/** SPI_SS Pin 1 */
#define OUT16_RELAY_1_SPI_SS_GPIO_PIN IPS_RELAY_1_SPI_SS_GPIO_PIN
/** OUT_EN Port 1 */
#define OUT16_RELAY_1_OUT_EN_GPIO_PORT IPS_RELAY_1_OUT_EN_GPIO_PORT
/** OUT_EN Pin 1 */
#define OUT16_RELAY_1_OUT_EN_GPIO_PIN IPS_RELAY_1_OUT_EN_GPIO_PIN
/** WD Port 1 */
#define OUT16_RELAY_1_WD_GPIO_PORT IPS_RELAY_1_WD_GPIO_PORT
/** WD Pin 1 */
#define OUT16_RELAY_1_WD_GPIO_PIN IPS_RELAY_1_WD_GPIO_PIN
/** SEL2_L Port 1 */
#define OUT16_RELAY_1_SEL2_L_GPIO_PORT IPS_RELAY_1_SEL2_L_GPIO_PORT
/** SEL2_L Pin 1 */
#define OUT16_RELAY_1_SEL2_L_GPIO_PIN IPS_RELAY_1_SEL2_L_GPIO_PIN
/** SEL1 Port 1 */
#define OUT16_RELAY_1_SEL1_GPIO_PORT IPS_RELAY_1_SEL1_GPIO_PORT
/** SEL1 Pin 1 */
#define OUT16_RELAY_1_SEL1_GPIO_PIN IPS_RELAY_1_SEL1_GPIO_PIN
/** WDEN Port 1 */
#define OUT16_RELAY_1_WDEN_GPIO_PORT IPS_RELAY_1_WDEN_GPIO_PORT
/** WDEN Pin 1 */
#define OUT16_RELAY_1_WDEN_GPIO_PIN IPS_RELAY_1_WDEN_GPIO_PIN

/** FAULT_L Port 1 */
#define OUT16_RELAY_1_FAULT_L_GPIO_PORT IPS_RELAY_1_FAULT_L_GPIO_PORT
/** FAULT_L Pin 1 */
#define OUT16_RELAY_1_FAULT_L_GPIO_PIN IPS_RELAY_1_FAULT_L_GPIO_PIN
/** PGOOD_L Port 1 */
#define OUT16_RELAY_1_PGOOD_L_GPIO_PORT IPS_RELAY_1_PGOOD_L_GPIO_PORT
/** PGOOD_L Pin 1 */
#define OUT16_RELAY_1_PGOOD_L_GPIO_PIN IPS_RELAY_1_PGOOD_L_GPIO_PIN
/** TWARN_L Port 1 */
#define OUT16_RELAY_1_TWARN_L_GPIO_PORT IPS_RELAY_1_TWARN_L_GPIO_PORT
/** TWARN_L Pin 1 */
#define OUT16_RELAY_1_TWARN_L_GPIO_PIN IPS_RELAY_1_TWARN_L_GPIO_PIN
#endif /* #ifdef USE_BOARD_1 */
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup OUT16A1_Exported_Variables OUT16A1 Exported Variables
  * @{
  */

#ifdef APP_PAR_IFC
extern void *SWITCH_CompObj[OUT16_INSTANCES_NBR];
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
extern void *RELAY_CompObj[OUT16_INSTANCES_NBR];
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @addtogroup OUT16A1_Exported_Functions OUT16A1 Exported Functions
  * @{
  */

#ifdef APP_PAR_IFC
/* ----------------- Parallel Interface API functions ----------------- */
int32_t OUT16_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT16_SWITCH_Init_Parameters_t *pInitParam);
int32_t OUT16_SWITCH_DeInit(uint8_t Instance);
int32_t OUT16_SWITCH_GetCapabilities(uint8_t Instance, OUT16_SWITCH_Capabilities_t *pCapabilities);
int32_t OUT16_SWITCH_ReadID(uint8_t Instance, uint16_t *pId);
int32_t OUT16_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus);
int32_t OUT16_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc);
int32_t OUT16_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc);
int32_t OUT16_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq);
int32_t OUT16_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq);
int32_t OUT16_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus);
int32_t OUT16_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT16_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap);
int32_t OUT16_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT16_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable);
int32_t OUT16_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable);
int32_t OUT16_SWITCH_PwmTick(uint8_t Instance);
int32_t OUT16_SWITCH_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t OUT16_SWITCH_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t OUT16_SWITCH_SetOperatingMode(uint8_t Instance, uint8_t *pCtrlMode);
__weak int32_t OUT16_SetTimerForPwm(uint8_t pwmEnable);
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
/* ----------------- SPI Interface PAI functions ----------------- */
/* Common functions */
int32_t OUT16_RELAY_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT16_RELAY_Init_Parameters_t *pInitParam);
int32_t OUT16_RELAY_DeInit(uint8_t Instance);
int32_t OUT16_RELAY_GetCapabilities(uint8_t Instance, OUT16_RELAY_Capabilities_t *pCapabilities);
int32_t OUT16_RELAY_ReadID(uint8_t Instance, uint16_t *pId);
int32_t OUT16_RELAY_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc);
int32_t OUT16_RELAY_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc);
int32_t OUT16_RELAY_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq);
int32_t OUT16_RELAY_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq);
int32_t OUT16_RELAY_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus);
int32_t OUT16_RELAY_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT16_RELAY_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap);
int32_t OUT16_RELAY_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT16_RELAY_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus);
int32_t OUT16_RELAY_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable);
int32_t OUT16_RELAY_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable);
int32_t OUT16_RELAY_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t OUT16_RELAY_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t OUT16_RELAY_SetOperatingMode(uint8_t Instance, uint8_t *pCtrlMode);
int32_t OUT16_RELAY_EnableDaisyChain(uint8_t Instance, uint8_t DcEnable);

/* Regular (parallel independent) mode specific functions */
int32_t OUT16_RELAY_GetFaultRegister(uint8_t Instance, uint16_t *pFaultRegister);
int32_t OUT16_RELAY_PwmTick(uint8_t Instance);
int32_t OUT16_RELAY_GuardTimerTick(uint8_t Instance);
int32_t OUT16_RELAY_WatchdogTimerTick(uint8_t Instance);

/* Daisy Chain mode specific functions */
int32_t OUT16_RELAY_QueueChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT16_RELAY_QueueAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT16_RELAY_SendQueuedChannelStatus(uint8_t Instance);
int32_t OUT16_RELAY_GetFaultRegister_DaisyChain(uint8_t Instance, uint32_t *pFaultRegister);
int32_t OUT16_RELAY_PwmTick_DaisyChain(void);
int32_t OUT16_RELAY_GuardTimerTick_DaisyChain(void);

void OUT16_EnableIrq(void);
void OUT16_DisableIrq(void);
__weak int32_t OUT16_SetTimerForPwm(uint8_t pwmEnable);
__weak int32_t OUT16_GuardTimerStart(void);
__weak int32_t OUT16_GuardTimerStop(void);
#endif /* #ifdef APP_SPI_IFC */

int32_t BSP_GetTick(void);
int32_t OUT16_RegisterCallBack(uint8_t Instance, void (*fault_isr)(void), void (*pgood_isr)(void), void (*twarn_isr)(void));

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

#endif /* OUT16A1_H */
