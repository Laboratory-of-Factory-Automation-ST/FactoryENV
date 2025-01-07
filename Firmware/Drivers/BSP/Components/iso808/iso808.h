/**
  ******************************************************************************
  * @file    iso808.h
  * @author  AMS IPC Application Team
  * @brief   Header for iso808.c module
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
#ifndef ISO808_H
#define ISO808_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "iso808_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup ISO808 ISO808
  * @{
  */

/* Exported Constants --------------------------------------------------------*/

/** @defgroup ISO808_Exported_Constants ISO808 Exported Constants
  * @{
  */

/* Dev capabilities for ISO808 */
/** ISO808 ID  */
#define ISO808_CHIP_ID (808U)

/** Maximum number of devices supported */
#define ISO808_DEVICES_NBR (1U)

/** Maximum channel frequency in tenth of Hz */
#define ISO808_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch ISO808 */
#define ISO808_MAX_NB_CHANNELS (8U)

/** First control pin by switch ISO808 board 0 */
#define ISO808_0_FIRST_CONTROL (0U)

/** Max number of control pins by switch ISO808 */
#define ISO808_MAX_NB_CONTROLS (3U)

/* Dev pins for ISO808 */
/* Board 0 */
/** Input Pin: IN1 */
#define ISO808_0_IN1 (0U)
/** Input Pin: IN2 */
#define ISO808_0_IN2 (1U)
/** Input Pin: IN3 */
#define ISO808_0_IN3 (2U)
/** Input Pin: IN4 */
#define ISO808_0_IN4 (3U)
/** Input Pin: IN5 */
#define ISO808_0_IN5 (4U)
/** Input Pin: IN6 */
#define ISO808_0_IN6 (5U)
/** Input Pin: IN7 */
#define ISO808_0_IN7 (6U)
/** Input Pin: IN8 */
#define ISO808_0_IN8 (7U)
/** Control Pin: LOAD */
#define ISO808_0_CTRL_LOAD (0U)
/** Control Pin: OUT_EN */
#define ISO808_0_CTRL_OUT_EN (1U)
/** Control Pin: SYNCH */
#define ISO808_0_CTRL_SYNCH (2U)

/** IN1 Port 0 */
#define ISO808_0_IN1_GPIO_PORT IN1_GPIO_Port
/** IN1 Pin 0 */
#define ISO808_0_IN1_GPIO_PIN IN1_Pin
/** IN2 Port 0 */
#define ISO808_0_IN2_GPIO_PORT IN2_GPIO_Port
/** IN2 Pin 0 */
#define ISO808_0_IN2_GPIO_PIN IN2_Pin
/** IN3 Port 0 */
#define ISO808_0_IN3_GPIO_PORT IN3_GPIO_Port
/** IN3 Pin 0 */
#define ISO808_0_IN3_GPIO_PIN IN3_Pin
/** IN4 Port 0 */
#define ISO808_0_IN4_GPIO_PORT IN4_GPIO_Port
/** IN4 Pin 0 */
#define ISO808_0_IN4_GPIO_PIN IN4_Pin
/** IN5 Port 0 */
#define ISO808_0_IN5_GPIO_PORT IN5_GPIO_Port
/** IN5 Pin 0 */
#define ISO808_0_IN5_GPIO_PIN IN5_Pin
/** IN6 Port 0 */
#define ISO808_0_IN6_GPIO_PORT IN6_GPIO_Port
/** IN6 Pin 0 */
#define ISO808_0_IN6_GPIO_PIN IN6_Pin
/** IN7 Port 0 */
#define ISO808_0_IN7_GPIO_PORT IN7_GPIO_Port
/** IN7 Pin 0 */
#define ISO808_0_IN7_GPIO_PIN IN7_Pin
/** IN8 Port 0 */
#define ISO808_0_IN8_GPIO_PORT IN8_GPIO_Port
/** IN8 Pin 0 */
#define ISO808_0_IN8_GPIO_PIN IN8_Pin

/** LOAD Port 0 */
#define ISO808_0_LOAD_GPIO_PORT LOAD_GPIO_Port
/** LOAD Pin 0 */
#define ISO808_0_LOAD_GPIO_PIN LOAD_Pin
/** OUT_EN Port 0 */
#define ISO808_0_OUT_EN_GPIO_PORT OUT_EN_GPIO_Port
/** OUT_EN Pin 0 */
#define ISO808_0_OUT_EN_GPIO_PIN OUT_EN_Pin
/** SYNCH Port 0 */
#define ISO808_0_SYNCH_GPIO_PORT SYNCH_GPIO_Port
/** SYNCH Pin 0 */
#define ISO808_0_SYNCH_GPIO_PIN SYNCH_Pin

/** STATUS Port 0 */
#define ISO808_0_STATUS_GPIO_PORT STATUS_GPIO_Port
/** STATUS Pin 0 */
#define ISO808_0_STATUS_GPIO_PIN STATUS_Pin

/* Return codes */
/** ISO808 Ok codes  */
#define IPS_SWITCH_OK (0)

/** ISO808 Error code  */
#define IPS_SWITCH_ERROR (-1)

typedef enum {
  /** ISO808 Direct Control Mode */
  ISO808_DCM,
  /** ISO808 Synchronous Control Mode */
  ISO808_SCM,
} IPS_CtrlMode_t;

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup ISO808_Exported_Types ISO808 Exported Types
  * @{
  */

/** ISO808 device pin structure */
typedef struct
{
  /** IN1 GPIO Port definition */
  GPIO_TypeDef *IN1_GPort;
  /** IN1 GPIO Pin definition */
  uint16_t IN1_GPin;
  /** IN2 GPIO Port definition */
  GPIO_TypeDef *IN2_GPort;
  /** IN2 GPIO Pin definition */
  uint16_t IN2_GPin;
  /** IN3 GPIO Port definition */
  GPIO_TypeDef *IN3_GPort;
  /** IN3 GPIO Pin definition */
  uint16_t IN3_GPin;
  /** IN4 GPIO Port definition */
  GPIO_TypeDef *IN4_GPort;
  /** IN4 GPIO Pin definition */
  uint16_t IN4_GPin;
  /** IN5 GPIO Port definition */
  GPIO_TypeDef *IN5_GPort;
  /** IN5 GPIO Pin definition */
  uint16_t IN5_GPin;
  /** IN6 GPIO Port definition */
  GPIO_TypeDef *IN6_GPort;
  /** IN6 GPIO Pin definition */
  uint16_t IN6_GPin;
  /** IN7 GPIO Port definition */
  GPIO_TypeDef *IN7_GPort;
  /** IN7 GPIO Pin definition */
  uint16_t IN7_GPin;
  /** IN8 GPIO Port definition */
  GPIO_TypeDef *IN8_GPort;
  /** IN8 GPIO Pin definition */
  uint16_t IN8_GPin;

  /** LOAD GPIO Port definition */
  GPIO_TypeDef *LOAD_GPort;
  /** LOAD GPIO Pin definition */
  uint16_t LOAD_GPin;
  /** OUT_EN GPIO Port definition */
  GPIO_TypeDef *OUT_EN_GPort;
  /** OUT_EN GPIO Pin definition */
  uint16_t OUT_EN_GPin;
  /** SYNCH GPIO Port definition */
  GPIO_TypeDef *SYNCH_GPort;
  /** SYNCH GPIO Pin definition */
  uint16_t SYNCH_GPin;

  /** STATUS GPIO Port definition */
  GPIO_TypeDef *STATUS_GPort;
  /** STATUS GPIO Pin definition */
  uint16_t STATUS_GPin;
} IPS_SWITCH_Pins_t;

/** Initialisation function  type*/
typedef int32_t (*ISO808_Init_Func)(void);
/** DeInitialisation function  type*/
typedef int32_t (*ISO808_DeInit_Func)(void);
/** GetTick function  type*/
typedef int32_t (*ISO808_GetTick_Func)(void);
/** Read fault function  type*/
typedef int32_t (*ISO808_Read_Fault_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Write channel function  type*/
typedef int32_t (*ISO808_Write_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read channel function  type*/
typedef int32_t (*ISO808_Read_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);
/** Write all channels function  type*/
typedef int32_t (*ISO808_Write_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t);
/** Read all channels function  type*/
typedef int32_t (*ISO808_Read_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Set PWM function  type*/
typedef int32_t (*ISO808_Set_Pwm_Func)(uint8_t);
/** Write Pin function type */
typedef int32_t (*ISO808_Write_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read Pin function type */
typedef int32_t (*ISO808_Read_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);

/** ISO808 IO structure  */
typedef struct
{
  /** Initialisation function */
  ISO808_Init_Func             Init;
  /** DeInitialisation function */
  ISO808_DeInit_Func           DeInit;
  /** Get Tick function */
  ISO808_GetTick_Func          GetTick;
  /** Read fault function */
  ISO808_Read_Fault_Func       ReadFault;
  /** Write Pin status function */
  ISO808_Write_Pin_Func_t      WritePin;
  /** Read Pin status function */
  ISO808_Read_Pin_Func_t       ReadPin;
  /** Write Channel status function */
  ISO808_Write_Chan_Func       WriteChan;
  /** Read Channel status function */
  ISO808_Read_Chan_Func        ReadChan;
  /** Write All Channels status function */
  ISO808_Write_All_Chan_Func   WriteAllChan;
  /** Read All Channels status function */
  ISO808_Read_All_Chan_Func    ReadAllChan;
  /** Set PWM */
  ISO808_Set_Pwm_Func          SetPwm;
} ISO808_IO_t;

/** ISO808 component object structure  */
typedef struct
{
  /** IOs substructure */
  ISO808_IO_t IO;
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
  uint8_t channelDc[ISO808_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[ISO808_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[ISO808_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[ISO808_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[ISO808_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[ISO808_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[ISO808_MAX_NB_CHANNELS];
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
  /** Control Mode flag (Direct or Synchronous) */
  uint8_t ctrlMode;
} ISO808_Object_t;

/** ISO808 component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} ISO808_Capabilities_t;


/** ISO808 common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(ISO808_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(ISO808_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(ISO808_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(ISO808_Object_t *, ISO808_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(ISO808_Object_t *, uint8_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(ISO808_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(ISO808_Object_t *, uint8_t, uint8_t);
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(ISO808_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(ISO808_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(ISO808_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(ISO808_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(ISO808_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(ISO808_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(ISO808_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(ISO808_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(ISO808_Object_t *);
  /** pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus)(ISO808_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus)(ISO808_Object_t *, uint8_t, uint8_t);
  /** pointer to SetOperatingMode function */
  int32_t (*SetOperatingMode)(ISO808_Object_t *, uint8_t);
} ISO808_CommonDrv_t;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup ISO808_Exported_Variables ISO808 Exported Variables
  * @{
  */

extern ISO808_CommonDrv_t ISO808_COMMON_Driver;
extern uint8_t SWITCH_System_PWMEnable_bitmap;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @defgroup ISO808_Exported_Macros ISO808 Exported Macros
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

/** @defgroup ISO808_Exported_Functions ISO808 Exported Functions
  * @{
  */

int32_t ISO808_GetAllChannelStatus(ISO808_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t ISO808_GetCapabilities(ISO808_Object_t *pObj, ISO808_Capabilities_t *pCapabilities);
int32_t ISO808_GetChannelDc(ISO808_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t ISO808_GetChannelFreq(ISO808_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t ISO808_GetChannelStatus(ISO808_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t ISO808_GetFaultStatus(ISO808_Object_t *pObj, uint8_t *pFaultStatus);
int32_t ISO808_GetPwmEnable(ISO808_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t ISO808_DeInit(ISO808_Object_t *pObj);
int32_t ISO808_Init(ISO808_Object_t *pObj);
int32_t ISO808_ReadID(ISO808_Object_t *pObj, uint32_t *pId);
int32_t ISO808_RegisterBusIO(ISO808_Object_t *pObj, ISO808_IO_t *pIO);
int32_t ISO808_SetAllChannelStatus(ISO808_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t ISO808_SetChannelDc(ISO808_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t ISO808_SetChannelFreq(ISO808_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t ISO808_SetChannelStatus(ISO808_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t ISO808_SetPwmEnable(ISO808_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled);
int32_t ISO808_PwmTick(ISO808_Object_t *pObj);
int32_t ISO808_GetCtrlPinStatus(ISO808_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t ISO808_SetCtrlPinStatus(ISO808_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t ISO808_SetOperatingMode(ISO808_Object_t *pObj, uint8_t opMode);

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

#endif /* #ifndef ISO808_H */
