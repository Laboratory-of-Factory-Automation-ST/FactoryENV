/**
  ******************************************************************************
  * @file    ips160hf.h
  * @author  AMS IPC Application Team
  * @brief   Header for ips160hf.c module
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
#ifndef IPS160HF_H
#define IPS160HF_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "ips160hf_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */


/** @addtogroup IPS160HF IPS160HF
  * @{
  */

/* Exported Constants --------------------------------------------------------*/

/** @defgroup IPS160HF_Exported_Constants IPS160HF Exported Constants
  * @{
  */

/* Dev capabilities for IPS160HF/161HF */
/** IPS160HF ID  */
#define IPS160HF_CHIP_ID (160U)

/** Maximum number of devices supported */
#define IPS160HF_DEVICES_NBR (1U)

/** Maximum channel frequency in tenth of Hz */
#define IPS160HF_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch IPS160HF or 161HF*/
#define IPS160HF_MAX_NB_CHANNELS (1U)

/** First control pin by switch IPS160HF board 0 */
#define IPS160HF_0_FIRST_CONTROL (0U)

/** First control pin by switch IPS160HF board 1 */
#define IPS160HF_1_FIRST_CONTROL (2U)

/** First control pin by switch IPS160HF board 2 */
#define IPS160HF_2_FIRST_CONTROL (4U)

/** First control pin by switch IPS160HF board 3 */
#define IPS160HF_3_FIRST_CONTROL (6U)

/** Max number of control pins by switch IPS160HF */
#define IPS160HF_MAX_NB_CONTROLS (2U)

/* Dev pins for IPS160HF */
/* Board 0 */
/** Device Chan: IN1 0 */
#define IPS160HF_0_IN1 (0U)

/** Board Control Pin: Nch_DRV 0 */
#define IPS160HF_0_NCH_DRV (0U)
/** Board Control Pin: OUT_FB 0 */
#define IPS160HF_0_OUT_FB (1U)

/** IN1 Port 0 */
#define IPS160HF_0_IN1_GPIO_PORT IN1_GPIO_Port
/** IN1 Pin 0 */
#define IPS160HF_0_IN1_GPIO_PIN IN1_Pin
/** DIAG Port 0 */
#define IPS160HF_0_DIAG_GPIO_PORT DIAG_GPIO_Port
/** DIAG Pin 0 */
#define IPS160HF_0_DIAG_GPIO_PIN DIAG_Pin

/** Nch-DRV Port 0 */
#define IPS160HF_0_NCH_DRV_GPIO_PORT Nch_DRV_GPIO_Port
/** Nch-DRV Pin 0 */
#define IPS160HF_0_NCH_DRV_GPIO_PIN Nch_DRV_Pin
/** OUT_FB Port 0 */
#define IPS160HF_0_OUT_FB_GPIO_PORT OUT_FB_GPIO_Port
/** OUT_FB Pin 0 */
#define IPS160HF_0_OUT_FB_GPIO_PIN OUT_FB_Pin

/* Board 1 */
/** Device Chan: IN1 1 */
#define IPS160HF_1_IN1 (0U)

/** Board Control Pin: Nch_DRV 1 */
#define IPS160HF_1_NCH_DRV (2U)
/** Board Control Pin: OUT_FB 1 */
#define IPS160HF_1_OUT_FB (3U)

/** IN1 Port 1 */
#define IPS160HF_1_IN1_GPIO_PORT IN1_Alt1_GPIO_Port
/** IN1 Pin 1 */
#define IPS160HF_1_IN1_GPIO_PIN IN1_Alt1_Pin
/** DIAG Port 1 */
#define IPS160HF_1_DIAG_GPIO_PORT DIAG_Alt1_GPIO_Port
/** DIAG Pin 1 */
#define IPS160HF_1_DIAG_GPIO_PIN DIAG_Alt1_Pin

/** Nch-DRV Port 1 */
#define IPS160HF_1_NCH_DRV_GPIO_PORT Nch_DRV_Alt1_GPIO_Port
/** Nch-DRV Pin 1 */
#define IPS160HF_1_NCH_DRV_GPIO_PIN Nch_DRV_Alt1_Pin
/** OUT_FB Port 1 */
#define IPS160HF_1_OUT_FB_GPIO_PORT OUT_FB_Alt1_GPIO_Port
/** OUT_FB Pin 1 */
#define IPS160HF_1_OUT_FB_GPIO_PIN OUT_FB_Alt1_Pin

/* Board 2 */
/** Device Chan: IN1 2 */
#define IPS160HF_2_IN1 (0U)

/** Board Control Pin: Nch_DRV 2 */
#define IPS160HF_2_NCH_DRV (4U)
/** Board Control Pin: OUT_FB 2 */
#define IPS160HF_2_OUT_FB (5U)

/** IN1 Port 2 */
#define IPS160HF_2_IN1_GPIO_PORT IN1_Alt2_GPIO_Port
/** IN1 Pin 2 */
#define IPS160HF_2_IN1_GPIO_PIN IN1_Alt2_Pin
/** DIAG Port 2 */
#define IPS160HF_2_DIAG_GPIO_PORT DIAG_Alt2_GPIO_Port
/** DIAG Pin 2 */
#define IPS160HF_2_DIAG_GPIO_PIN DIAG_Alt2_Pin

/** Nch-DRV Port 2 */
#define IPS160HF_2_NCH_DRV_GPIO_PORT Nch_DRV_Alt2_GPIO_Port
/** Nch-DRV Pin 2 */
#define IPS160HF_2_NCH_DRV_GPIO_PIN Nch_DRV_Alt2_Pin
/** OUT_FB Port 2 */
#define IPS160HF_2_OUT_FB_GPIO_PORT OUT_FB_Alt2_GPIO_Port
/** OUT_FB Pin 2 */
#define IPS160HF_2_OUT_FB_GPIO_PIN OUT_FB_Alt2_Pin

/* Board 3 */
/** Device Chan: IN1 3 */
#define IPS160HF_3_IN1 (0U)

/** Board Control Pin: Nch_DRV 3 */
#define IPS160HF_3_NCH_DRV (6U)
/** Board Control Pin: OUT_FB 3 */
#define IPS160HF_3_OUT_FB (7U)

/** IN1 Port 3 */
#define IPS160HF_3_IN1_GPIO_PORT IN1_Alt3_GPIO_Port
/** IN1 Pin 3 */
#define IPS160HF_3_IN1_GPIO_PIN IN1_Alt3_Pin
/** DIAG Port 3 */
#define IPS160HF_3_DIAG_GPIO_PORT DIAG_Alt3_GPIO_Port
/** DIAG Pin 3 */
#define IPS160HF_3_DIAG_GPIO_PIN DIAG_Alt3_Pin

/** Nch-DRV Port 3 */
#define IPS160HF_3_NCH_DRV_GPIO_PORT Nch_DRV_Alt3_GPIO_Port
/** Nch-DRV Pin 3 */
#define IPS160HF_3_NCH_DRV_GPIO_PIN Nch_DRV_Alt3_Pin
/** OUT_FB Port 3 */
#define IPS160HF_3_OUT_FB_GPIO_PORT OUT_FB_Alt3_GPIO_Port
/** OUT_FB Pin 3 */
#define IPS160HF_3_OUT_FB_GPIO_PIN OUT_FB_Alt3_Pin

/* Return codes */
/** IPS160HF Ok codes  */
#define IPS_SWITCH_OK (0)

/** IPS160HF Error code  */
#define IPS_SWITCH_ERROR (-1)

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup IPS160HF_Exported_Types IPS160HF Exported Types
  * @{
  */

/** IPS160HF_CONF_H device pin structure */
typedef struct
{
  /** IN1 GPIO Port definition */
  GPIO_TypeDef *IN1_GPort;
  /** IN1 GPIO Pin definition */
  uint16_t IN1_GPin;
  /** DIAG GPIO Port definition */
  GPIO_TypeDef *DIAG_GPort;
  /** DIAG GPIO Pin definition */
  uint16_t DIAG_GPin;

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
typedef int32_t (*IPS160HF_Init_Func)(void);
/** DeInitialisation function  type*/
typedef int32_t (*IPS160HF_DeInit_Func)(void);
/** GetTick function  type*/
typedef int32_t (*IPS160HF_GetTick_Func)(void);
/** Read fault function  type*/
typedef int32_t (*IPS160HF_Read_Fault_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Write channel function  type*/
typedef int32_t (*IPS160HF_Write_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read channel function  type*/
typedef int32_t (*IPS160HF_Read_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);
/** Write all channels function  type*/
typedef int32_t (*IPS160HF_Write_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t);
/** Read all channels function  type*/
typedef int32_t (*IPS160HF_Read_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Set PWM function  type*/
typedef int32_t (*IPS160HF_Set_Pwm_Func)(uint8_t);
/** Write Pin function type */
typedef int32_t (*IPS160HF_Write_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read Pin function type */
typedef int32_t (*IPS160HF_Read_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);

/** IPS160HF IO structure  */
typedef struct
{
  /** Initialisation function */
  IPS160HF_Init_Func             Init;
  /** DeInitialisation function */
  IPS160HF_DeInit_Func           DeInit;
  /** Get Tick function */
  IPS160HF_GetTick_Func          GetTick;
  /** Read fault function */
  IPS160HF_Read_Fault_Func       ReadFault;
  /** Write Pin status function */
  IPS160HF_Write_Pin_Func_t      WritePin;
  /** Read Pin status function */
  IPS160HF_Read_Pin_Func_t       ReadPin;
  /** Write Channel status function */
  IPS160HF_Write_Chan_Func       WriteChan;
  /** Read Channel status function */
  IPS160HF_Read_Chan_Func        ReadChan;
  /** Write All Channels status function */
  IPS160HF_Write_All_Chan_Func   WriteAllChan;
  /** Read All Channels status function */
  IPS160HF_Read_All_Chan_Func    ReadAllChan;
  /** Set PWM function */
  IPS160HF_Set_Pwm_Func          SetPwm;
} IPS160HF_IO_t;

/** IPS160HF component object structure */
typedef struct
{
  /** IOs substructure */
  IPS160HF_IO_t IO;
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
  uint8_t channelDc[IPS160HF_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[IPS160HF_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[IPS160HF_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[IPS160HF_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[IPS160HF_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[IPS160HF_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[IPS160HF_MAX_NB_CHANNELS];
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
  uint8_t NchDrv_isPwmSyncEnabled[IPS160HF_MAX_NB_CHANNELS];
  /** Nch-DRV ON-period as a percentage of IN PWM OFF-period */
  uint8_t NchDrv_OnPeriod[IPS160HF_MAX_NB_CHANNELS];
  /** Nch-DRV ON delay as a percentage of IN PWM OFF-period */
  uint8_t NchDrv_OnDelay[IPS160HF_MAX_NB_CHANNELS];
  /** tick counter for nch_drv sync with out pwm*/
  uint32_t NchDrv_TimTickCnt[IPS160HF_MAX_NB_CHANNELS];
  /** tick value for nch_drv on*/
  uint32_t NchDrv_TimTickOn[IPS160HF_MAX_NB_CHANNELS];
  /** tick value for nch_drv off*/
  uint32_t NchDrv_TimTickOff[IPS160HF_MAX_NB_CHANNELS];
} IPS160HF_Object_t;


/** IPS160HF component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} IPS160HF_Capabilities_t;


/** IPS160H_161H common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(IPS160HF_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(IPS160HF_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(IPS160HF_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(IPS160HF_Object_t *, IPS160HF_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(IPS160HF_Object_t *, uint8_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(IPS160HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(IPS160HF_Object_t *, uint8_t, uint8_t );
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(IPS160HF_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(IPS160HF_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(IPS160HF_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(IPS160HF_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(IPS160HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(IPS160HF_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(IPS160HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(IPS160HF_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(IPS160HF_Object_t *);
  /** pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus)(IPS160HF_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus)(IPS160HF_Object_t *, uint8_t, uint8_t);
  /** pointer to SetNchDrvSyncEnable function */
  int32_t (*SetNchDrvSyncEnable)(IPS160HF_Object_t *, uint8_t, uint8_t, uint8_t, uint8_t);
} IPS160HF_CommonDrv_t;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup IPS160HF_Exported_Variables IPS160HF Exported Variables
  * @{
  */

extern IPS160HF_CommonDrv_t IPS160HF_COMMON_Driver;
extern uint8_t SWITCH_System_PWMEnable_bitmap;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @defgroup IPS160HF_Exported_Macros IPS160HF Exported Macros
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

/** @defgroup IPS160HF_Exported_Functions IPS160HF Exported Functions
  * @{
  */
int32_t IPS160HF_GetAllChannelStatus(IPS160HF_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t IPS160HF_GetCapabilities(IPS160HF_Object_t *pObj, IPS160HF_Capabilities_t *pCapabilities);
int32_t IPS160HF_GetChannelDc(IPS160HF_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t IPS160HF_GetChannelFreq(IPS160HF_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t IPS160HF_GetChannelStatus(IPS160HF_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t IPS160HF_GetFaultStatus(IPS160HF_Object_t *pObj, uint8_t *pFaultStatus);
int32_t IPS160HF_GetPwmEnable(IPS160HF_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t IPS160HF_DeInit(IPS160HF_Object_t *pObj);
int32_t IPS160HF_Init(IPS160HF_Object_t *pObj);
int32_t IPS160HF_ReadID(IPS160HF_Object_t *pObj, uint32_t *pId);
int32_t IPS160HF_RegisterBusIO(IPS160HF_Object_t *pObj, IPS160HF_IO_t *pIO);
int32_t IPS160HF_SetAllChannelStatus(IPS160HF_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS160HF_SetChannelDc(IPS160HF_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t IPS160HF_SetChannelFreq(IPS160HF_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t IPS160HF_SetChannelStatus(IPS160HF_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS160HF_SetPwmEnable(IPS160HF_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled);
int32_t IPS160HF_PwmTick(IPS160HF_Object_t *pObj);
int32_t IPS160HF_GetCtrlPinStatus(IPS160HF_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t IPS160HF_SetCtrlPinStatus(IPS160HF_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t IPS160HF_SetNchDrvSyncEnable(IPS160HF_Object_t *pObj, uint8_t ChanId, uint8_t Phase, uint8_t Period, uint8_t NchDrvSyncEnabled);

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

#endif /* #ifndef IPS160HF_H */
