/**
  ******************************************************************************
  * @file    out10a1.h
  * @author  AMS IPC Application Team
  * @brief   Header for out10a1.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OUT10A1_H
#define OUT10A1_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "out10a1_conf.h"
#include "out10a1_bus.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT10A1 OUT10A1
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup OUT10A1_Exported_Types OUT10A1 Exported Types
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
  /** function pointer to GetCtrlPinStatus function */
  int32_t ( *GetCtrlPinStatus     ) ( void *, uint8_t , uint8_t * );
  /** function pointer to SetCtrlPinStatus function */
  int32_t ( *SetCtrlPinStatus     ) ( void *, uint8_t , uint8_t );
  /** function pointer to SetNchDrvSyncEnable function */
  int32_t ( *SetNchDrvSyncEnable  ) (void *, uint8_t, uint8_t, uint8_t, uint8_t);
} SWITCH_CommonDrv_t;

/** Structure for initial switch parameters Info */
typedef struct
{
  /** PWM Frequency */
  uint32_t pwmFreq;
} OUT10_SWITCH_Init_Parameters_t;


/** Switch instance Info */
typedef struct
{
  /** Number of supported channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} OUT10_SWITCH_Capabilities_t;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup OUT10A1_Exported_Constants OUT10A1 Exported Constants
  * @{
  */

/** CHIP ID */
#define OUT10_SWITCH_CHIP_ID  IPS161HF_CHIP_ID

/** Number of supported switch instances */
#define OUT10_SWITCH_INSTANCES_NBR (4U)

/** Number of supported switch devices */
#define OUT10_SWITCH_DEVICES_NBR IPS_SWITCH_DEVICES_NBR

#ifdef USE_BOARD_0
/* Board 0 */
/** Device Chan: IN1 0 */
#define OUT10_SWITCH_0_IN1 IPS_SWITCH_0_IN1

/** Board Control Pin: Nch_DRV 0 */
#define OUT10_SWITCH_0_NCH_DRV IPS_SWITCH_0_NCH_DRV
/** Board Control Pin: OUT_FB 0 */
#define OUT10_SWITCH_0_OUT_FB IPS_SWITCH_0_OUT_FB

/** IN1 Port 0 */
#define OUT10_SWITCH_0_IN1_GPIO_PORT IPS_SWITCH_0_IN1_GPIO_PORT
/** IN1 Pin 0 */
#define OUT10_SWITCH_0_IN1_GPIO_PIN IPS_SWITCH_0_IN1_GPIO_PIN
/** DIAG Port 0 */
#define OUT10_SWITCH_0_DIAG_GPIO_PORT IPS_SWITCH_0_DIAG_GPIO_PORT
/** DIAG Pin 0 */
#define OUT10_SWITCH_0_DIAG_GPIO_PIN IPS_SWITCH_0_DIAG_GPIO_PIN
/** Nch-DRV Port 0 */
#define OUT10_SWITCH_0_NCH_DRV_GPIO_PORT IPS_SWITCH_0_NCH_DRV_GPIO_PORT
/** Nch-DRV Pin 0 */
#define OUT10_SWITCH_0_NCH_DRV_GPIO_PIN IPS_SWITCH_0_NCH_DRV_GPIO_PIN
/** OUT_FB Port 0 */
#define OUT10_SWITCH_0_OUT_FB_GPIO_PORT IPS_SWITCH_0_OUT_FB_GPIO_PORT
/** OUT_FB Pin 0 */
#define OUT10_SWITCH_0_OUT_FB_GPIO_PIN IPS_SWITCH_0_OUT_FB_GPIO_PIN
#endif /* #ifdef USE_BOARD_0 */

#ifdef USE_BOARD_1
/* Board 1 */
/** Device Chan: IN1 1 */
#define OUT10_SWITCH_1_IN1 IPS_SWITCH_1_IN1

/** Board Control Pin: Nch_DRV 1 */
#define OUT10_SWITCH_1_NCH_DRV IPS_SWITCH_1_NCH_DRV
/** Board Control Pin: OUT_FB 1 */
#define OUT10_SWITCH_1_OUT_FB IPS_SWITCH_1_OUT_FB

/** IN1 Port 1 */
#define OUT10_SWITCH_1_IN1_GPIO_PORT IPS_SWITCH_1_IN1_GPIO_PORT
/** IN1 Pin 1 */
#define OUT10_SWITCH_1_IN1_GPIO_PIN IPS_SWITCH_1_IN1_GPIO_PIN
/** DIAG Port 1 */
#define OUT10_SWITCH_1_DIAG_GPIO_PORT IPS_SWITCH_1_DIAG_GPIO_PORT
/** DIAG Pin 1 */
#define OUT10_SWITCH_1_DIAG_GPIO_PIN IPS_SWITCH_1_DIAG_GPIO_PIN
/** Nch-DRV Port 1 */
#define OUT10_SWITCH_1_NCH_DRV_GPIO_PORT IPS_SWITCH_1_NCH_DRV_GPIO_PORT
/** Nch-DRV Pin 1 */
#define OUT10_SWITCH_1_NCH_DRV_GPIO_PIN IPS_SWITCH_1_NCH_DRV_GPIO_PIN
/** OUT_FB Port 1 */
#define OUT10_SWITCH_1_OUT_FB_GPIO_PORT IPS_SWITCH_1_OUT_FB_GPIO_PORT
/** OUT_FB Pin 1 */
#define OUT10_SWITCH_1_OUT_FB_GPIO_PIN IPS_SWITCH_1_OUT_FB_GPIO_PIN
#endif /* #ifdef USE_BOARD_1 */

#ifdef USE_BOARD_2
/* Board 2 */
/** Device Chan: IN1 2 */
#define OUT10_SWITCH_2_IN1 IPS_SWITCH_2_IN1

/** Board Control Pin: Nch_DRV 2 */
#define OUT10_SWITCH_2_NCH_DRV IPS_SWITCH_2_NCH_DRV
/** Board Control Pin: OUT_FB 2 */
#define OUT10_SWITCH_2_OUT_FB IPS_SWITCH_2_OUT_FB

/** IN1 Port 2 */
#define OUT10_SWITCH_2_IN1_GPIO_PORT IPS_SWITCH_2_IN1_GPIO_PORT
/** IN1 Pin 2 */
#define OUT10_SWITCH_2_IN1_GPIO_PIN IPS_SWITCH_2_IN1_GPIO_PIN
/** DIAG Port 2 */
#define OUT10_SWITCH_2_DIAG_GPIO_PORT IPS_SWITCH_2_DIAG_GPIO_PORT
/** DIAG Pin 2 */
#define OUT10_SWITCH_2_DIAG_GPIO_PIN IPS_SWITCH_2_DIAG_GPIO_PIN
/** Nch-DRV Port 2 */
#define OUT10_SWITCH_2_NCH_DRV_GPIO_PORT IPS_SWITCH_2_NCH_DRV_GPIO_PORT
/** Nch-DRV Pin 2 */
#define OUT10_SWITCH_2_NCH_DRV_GPIO_PIN IPS_SWITCH_2_NCH_DRV_GPIO_PIN
/** OUT_FB Port 2 */
#define OUT10_SWITCH_2_OUT_FB_GPIO_PORT IPS_SWITCH_2_OUT_FB_GPIO_PORT
/** OUT_FB Pin 2 */
#define OUT10_SWITCH_2_OUT_FB_GPIO_PIN IPS_SWITCH_2_OUT_FB_GPIO_PIN
#endif /* #ifdef USE_BOARD_2 */

#ifdef USE_BOARD_3
/* Board 3 */
/** Device Chan: IN1 3 */
#define OUT10_SWITCH_3_IN1 IPS_SWITCH_3_IN1

/** Board Control Pin: Nch_DRV 3 */
#define OUT10_SWITCH_3_NCH_DRV IPS_SWITCH_3_NCH_DRV
/** Board Control Pin: OUT_FB 3 */
#define OUT10_SWITCH_3_OUT_FB IPS_SWITCH_3_OUT_FB

/** IN1 Port 3 */
#define OUT10_SWITCH_3_IN1_GPIO_PORT IPS_SWITCH_3_IN1_GPIO_PORT
/** IN1 Pin 3 */
#define OUT10_SWITCH_3_IN1_GPIO_PIN IPS_SWITCH_3_IN1_GPIO_PIN
/** DIAG Port 3 */
#define OUT10_SWITCH_3_DIAG_GPIO_PORT IPS_SWITCH_3_DIAG_GPIO_PORT
/** DIAG Pin 3 */
#define OUT10_SWITCH_3_DIAG_GPIO_PIN IPS_SWITCH_3_DIAG_GPIO_PIN
/** Nch-DRV Port 3 */
#define OUT10_SWITCH_3_NCH_DRV_GPIO_PORT IPS_SWITCH_3_NCH_DRV_GPIO_PORT
/** Nch-DRV Pin 3 */
#define OUT10_SWITCH_3_NCH_DRV_GPIO_PIN IPS_SWITCH_3_NCH_DRV_GPIO_PIN
/** OUT_FB Port 3 */
#define OUT10_SWITCH_3_OUT_FB_GPIO_PORT IPS_SWITCH_3_OUT_FB_GPIO_PORT
/** OUT_FB Pin 3 */
#define OUT10_SWITCH_3_OUT_FB_GPIO_PIN IPS_SWITCH_3_OUT_FB_GPIO_PIN
#endif /* #ifdef USE_BOARD_3 */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup OUT10A1_Exported_Variables OUT10A1 Exported Variables
  * @{
  */

extern void *SWITCH_CompObj[OUT10_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @defgroup OUT10A1_Exported_Functions OUT10A1 Exported Functions
  * @{
  */
int32_t BSP_GetTick(void);
int32_t OUT10_SWITCH_RegisterCallBack(uint8_t Instance, void (*out_fb_isr)(void), void (*diag_isr)(void));

int32_t OUT10_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT10_SWITCH_Init_Parameters_t *pInitParam);
int32_t OUT10_SWITCH_DeInit(uint8_t Instance);
int32_t OUT10_SWITCH_GetCapabilities(uint8_t Instance, OUT10_SWITCH_Capabilities_t *pCapabilities);
int32_t OUT10_SWITCH_ReadID(uint8_t Instance, uint16_t *pId);
int32_t OUT10_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc);
int32_t OUT10_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc);
int32_t OUT10_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq);
int32_t OUT10_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq);
int32_t OUT10_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus);
int32_t OUT10_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus);
int32_t OUT10_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap);
int32_t OUT10_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap);
int32_t OUT10_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus);
int32_t OUT10_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable);
int32_t OUT10_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable);
int32_t OUT10_SWITCH_PwmTick(uint8_t Instance);
int32_t OUT10_SWITCH_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t OUT10_SWITCH_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t OUT10_SWITCH_SetNchDrvSyncEnable(uint8_t Instance, uint8_t ChanId, uint8_t phase, uint8_t duty, uint8_t syncEnable);
__weak int32_t OUT10_SetTimerForPwm(uint8_t pwmEnable);

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

#endif /* OUT10A1_H */
