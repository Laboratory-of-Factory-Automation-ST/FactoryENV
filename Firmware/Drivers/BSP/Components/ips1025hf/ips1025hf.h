/**
  ******************************************************************************
  * @file    ips1025hf.h
  * @author  AMS IPC Application Team
  * @brief   Header for ips1025hf.c module
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
#ifndef IPS1025HF_H
#define IPS1025HF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "ips1025hf_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */


/** @addtogroup IPS1025HF IPS1025HF
  * @{
  */

/* Exported Constants --------------------------------------------------------*/

/** @defgroup IPS1025HF_Exported_Constants IPS1025HF Exported Constants
  * @{
  */

/* Dev capabilities for IPS1025HF */
/** IPS1025HF ID  */
#define IPS1025HF_CHIP_ID (1025U)

/** Maximum number of devices supported */
#define IPS1025HF_DEVICES_NBR (1U)

/** Maximum channel frequency in tenth of Hz */
#define IPS1025HF_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch IPS1025HF */
#define IPS1025HF_MAX_NB_CHANNELS (1U)

/** First control pin by switch IPS1025HF board 0 */
#define IPS1025HF_0_FIRST_CONTROL (0U)

/** First control pin by switch IPS1025HF board 1 */
#define IPS1025HF_1_FIRST_CONTROL (2U)

/** Max number of control pins by switch IPS1025HF */
#define IPS1025HF_MAX_NB_CONTROLS (2U)

/* Dev pins for IPS1025H */
/* Board 0 */
/** Device Chan: IN1 0 */
#define IPS1025HF_0_IN1 (0U)

/** Board Control Pin: Nch_DRV 0 */
#define IPS1025HF_0_NCH_DRV (0U)
/** Board Control Pin: OUT_FB 0 */
#define IPS1025HF_0_OUT_FB (1U)

/** IN1 Port 0 */
#define IPS1025HF_0_IN1_GPIO_PORT IN1_GPIO_Port
/** IN1 Pin 0 */
#define IPS1025HF_0_IN1_GPIO_PIN IN1_Pin
/** FLT1 Port 0 */
#define IPS1025HF_0_FLT1_GPIO_PORT FLT1_GPIO_Port
/** FLT1 Pin 0 */
#define IPS1025HF_0_FLT1_GPIO_PIN FLT1_Pin
/** FLT2 Port 0 */
#define IPS1025HF_0_FLT2_GPIO_PORT FLT2_GPIO_Port
/** FLT2 Pin 0 */
#define IPS1025HF_0_FLT2_GPIO_PIN FLT2_Pin

/** Nch-DRV Port 0 */
#define IPS1025HF_0_NCH_DRV_GPIO_PORT Nch_DRV_GPIO_Port
/** Nch-DRV Pin 0 */
#define IPS1025HF_0_NCH_DRV_GPIO_PIN Nch_DRV_Pin
/** OUT_FB Port 0 */
#define IPS1025HF_0_OUT_FB_GPIO_PORT OUT_FB_GPIO_Port
/** OUT_FB Pin 0 */
#define IPS1025HF_0_OUT_FB_GPIO_PIN OUT_FB_Pin

/* Board 1 */
/** Device Chan: IN1 1 */
#define IPS1025HF_1_IN1 (0U)

/** Board Control Pin: Nch_DRV 1 */
#define IPS1025HF_1_NCH_DRV (2U)
/** Board Control Pin: OUT_FB 1 */
#define IPS1025HF_1_OUT_FB (3U)

/** IN1 Port 1 */
#define IPS1025HF_1_IN1_GPIO_PORT IN1_Alt1_GPIO_Port
/** IN1 Pin 1 */
#define IPS1025HF_1_IN1_GPIO_PIN IN1_Alt1_Pin
/** FLT1 Port 1 */
#define IPS1025HF_1_FLT1_GPIO_PORT FLT1_Alt1_GPIO_Port
/** FLT1 Pin 1 */
#define IPS1025HF_1_FLT1_GPIO_PIN FLT1_Alt1_Pin
/** FLT2 Port 1 */
#define IPS1025HF_1_FLT2_GPIO_PORT FLT2_Alt1_GPIO_Port
/** FLT2 Pin 1 */
#define IPS1025HF_1_FLT2_GPIO_PIN FLT2_Alt1_Pin

/** Nch-DRV Port 1 */
#define IPS1025HF_1_NCH_DRV_GPIO_PORT Nch_DRV_Alt1_GPIO_Port
/** Nch-DRV Pin 1 */
#define IPS1025HF_1_NCH_DRV_GPIO_PIN Nch_DRV_Alt1_Pin
/** OUT_FB Port 1 */
#define IPS1025HF_1_OUT_FB_GPIO_PORT OUT_FB_Alt1_GPIO_Port
/** OUT_FB Pin 1 */
#define IPS1025HF_1_OUT_FB_GPIO_PIN OUT_FB_Alt1_Pin

/* Return codes */
/** IPS1025HF Ok codes  */
#define IPS_SWITCH_OK (0)

/** IPS1025HF Error code  */
#define IPS_SWITCH_ERROR (-1)

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup IPS1025HF_Exported_Types IPS1025HF Exported Types
  * @{
  */

/** IPS1025HF device pin structure */
typedef struct
{
  /** IN1 GPIO Port definition */
  GPIO_TypeDef *IN1_GPort;
  /** IN1 GPIO Pin definition */
  uint16_t IN1_GPin;
  /** FLT1 GPIO Port definition */
  GPIO_TypeDef *FLT1_GPort;
  /** FLT1 GPIO Pin definition */
  uint16_t FLT1_GPin;
  /** FLT2 GPIO Port definition */
  GPIO_TypeDef *FLT2_GPort;
  /** FLT2 GPIO Pin definition */
  uint16_t FLT2_GPin;

  /** Nch-DRV GPIO Port definition */
  GPIO_TypeDef *Nch_DRV_GPort;
  /** Nch-DRV GPIO Pin definition */
  uint16_t Nch_DRV_GPin;
  /** OUT_FB GPIO Port definition */
  GPIO_TypeDef *OUT_FB_GPort;
  /** OUT_FB GPIO Pin definition */
  uint16_t OUT_FB_GPin;
} IPS_SWITCH_Pins_t;

/** Initialisation function  type*/
typedef int32_t (*IPS1025HF_Init_Func)(void);
/** DeInitialisation function  type*/
typedef int32_t (*IPS1025HF_DeInit_Func)(void);
/** GetTick function  type*/
typedef int32_t (*IPS1025HF_GetTick_Func)(void);
/** Read fault function  type*/
typedef int32_t (*IPS1025HF_Read_Fault_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Write channel function  type*/
typedef int32_t (*IPS1025HF_Write_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read channel function  type*/
typedef int32_t (*IPS1025HF_Read_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);
/** Write all channels function  type*/
typedef int32_t (*IPS1025HF_Write_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t);
/** Read all channels function  type*/
typedef int32_t (*IPS1025HF_Read_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Set PWM function  type*/
typedef int32_t (*IPS1025HF_Set_Pwm_Func)(uint8_t);
/** Write Pin function type */
typedef int32_t (*IPS1025HF_Write_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read Pin function type */
typedef int32_t (*IPS1025HF_Read_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);

/** IPS1025HF IO structure  */
typedef struct
{
  /** Initialisation function */
  IPS1025HF_Init_Func             Init;
  /** DeInitialisation function */
  IPS1025HF_DeInit_Func           DeInit;
  /** Get Tick function */
  IPS1025HF_GetTick_Func          GetTick;
  /** Read fault function */
  IPS1025HF_Read_Fault_Func       ReadFault;
  /** Write Pin status function */
  IPS1025HF_Write_Pin_Func_t      WritePin;
  /** Read Pin status function */
  IPS1025HF_Read_Pin_Func_t       ReadPin;
  /** Write Channel status function */
  IPS1025HF_Write_Chan_Func       WriteChan;
  /** Read Channel status function */
  IPS1025HF_Read_Chan_Func        ReadChan;
  /** Write All Channels status function */
  IPS1025HF_Write_All_Chan_Func   WriteAllChan;
  /** Read All Channels status function */
  IPS1025HF_Read_All_Chan_Func    ReadAllChan;
  /** Set PWM function */
  IPS1025HF_Set_Pwm_Func          SetPwm;
} IPS1025HF_IO_t;

/** IPS1025HF component object structure */
typedef struct
{
  /** IOs substructure */
  IPS1025HF_IO_t IO;
  /** Pins substructure */
  IPS_SWITCH_Pins_t Pin;
  /** number of similar devices */
  uint8_t nbDevices;
  /** number of channels */
  uint8_t nbChannels;
  /** first control pin */
  uint8_t firstCtrl;
  /** number of control pins */
  uint8_t nbCtrls;
  /** is component initialised?*/
  uint8_t is_initialized;
  /** channel Duty cycle*/
  uint8_t channelDc[IPS1025HF_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[IPS1025HF_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[IPS1025HF_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[IPS1025HF_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[IPS1025HF_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[IPS1025HF_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[IPS1025HF_MAX_NB_CHANNELS];
  /** Tick where the next action in PWM mode has to be performed */
  uint32_t pwmTimNextAction;
  /** channel steady state bitmap */
  uint8_t ChanSteadyStateBitmap;
  /** controls steady state bitmap */
  uint8_t ControlPinsBitmap;
  /** Instance of the current object */
  uint8_t Instance;
  /** Board is present flag */
  uint8_t isPresent;
  /** Is Nch-DRV sync with IN PWM enabled? */
  uint8_t NchDrv_isPwmSyncEnabled[IPS1025HF_MAX_NB_CHANNELS];
  /** Nch-DRV ON-period as a percentage of IN PWM OFF-period */
  uint8_t NchDrv_OnPeriod[IPS1025HF_MAX_NB_CHANNELS];
  /** Nch-DRV ON delay as a percentage of IN PWM OFF-period */
  uint8_t NchDrv_OnDelay[IPS1025HF_MAX_NB_CHANNELS];
  /** tick counter for nch_drv sync with out pwm*/
  uint32_t NchDrv_TimTickCnt[IPS1025HF_MAX_NB_CHANNELS];
  /** tick value for nch_drv on*/
  uint32_t NchDrv_TimTickOn[IPS1025HF_MAX_NB_CHANNELS];
  /** tick value for nch_drv off*/
  uint32_t NchDrv_TimTickOff[IPS1025HF_MAX_NB_CHANNELS];
} IPS1025HF_Object_t;

/** IPS1025HF component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} IPS1025HF_Capabilities_t;


/** IPS1025HF common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(IPS1025HF_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(IPS1025HF_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(IPS1025HF_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(IPS1025HF_Object_t *, IPS1025HF_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(IPS1025HF_Object_t *, uint8_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(IPS1025HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(IPS1025HF_Object_t *, uint8_t, uint8_t );
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(IPS1025HF_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(IPS1025HF_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(IPS1025HF_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(IPS1025HF_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(IPS1025HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(IPS1025HF_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(IPS1025HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(IPS1025HF_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(IPS1025HF_Object_t *);
  /** pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus)(IPS1025HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus)(IPS1025HF_Object_t *, uint8_t, uint8_t);
  /** pointer to SetNchDrvSyncEnable function */
  int32_t (*SetNchDrvSyncEnable)(IPS1025HF_Object_t *, uint8_t, uint8_t, uint8_t, uint8_t);
} IPS1025HF_CommonDrv_t;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup IPS1025HF_Exported_Variables IPS1025HF Exported Variables
  * @{
  */

extern IPS1025HF_CommonDrv_t IPS1025HF_COMMON_Driver;
extern uint8_t SWITCH_System_PWMEnable_bitmap;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @defgroup IPS1025HF_Exported_Macros IPS1025HF Exported Macros
  * @{
  */

/** Define TRUE */
#ifndef TRUE
#define TRUE ((uint8_t) 1)
#endif /* #ifndef TRUE */

/** Define FALSE */
#ifndef FALSE
#define FALSE ((uint8_t) 0)
#endif /* #ifndef FALSE */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup IPS1025HF_Exported_Functions IPS1025HF Exported Functions
  * @{
  */
int32_t IPS1025HF_GetAllChannelStatus(IPS1025HF_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t IPS1025HF_GetCapabilities(IPS1025HF_Object_t *pObj, IPS1025HF_Capabilities_t *pCapabilities);
int32_t IPS1025HF_GetChannelDc(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t IPS1025HF_GetChannelFreq(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t IPS1025HF_GetChannelStatus(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t IPS1025HF_GetFaultStatus(IPS1025HF_Object_t *pObj, uint8_t *pFaultStatus);
int32_t IPS1025HF_GetPwmEnable(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t IPS1025HF_DeInit(IPS1025HF_Object_t *pObj);
int32_t IPS1025HF_Init(IPS1025HF_Object_t *pObj);
int32_t IPS1025HF_ReadID(IPS1025HF_Object_t *pObj, uint32_t *pId);
int32_t IPS1025HF_RegisterBusIO(IPS1025HF_Object_t *pObj, IPS1025HF_IO_t *pIO);
int32_t IPS1025HF_SetAllChannelStatus(IPS1025HF_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS1025HF_SetChannelDc(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t IPS1025HF_SetChannelFreq(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t IPS1025HF_SetChannelStatus(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS1025HF_SetPwmEnable(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled);
int32_t IPS1025HF_PwmTick(IPS1025HF_Object_t *pObj);
int32_t IPS1025HF_GetCtrlPinStatus(IPS1025HF_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t IPS1025HF_SetCtrlPinStatus(IPS1025HF_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t IPS1025HF_SetNchDrvSyncEnable(IPS1025HF_Object_t *pObj, uint8_t ChanId, uint8_t Phase, uint8_t Period, uint8_t NchDrvSyncEnabled);

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

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef IPS1025HF_H */
